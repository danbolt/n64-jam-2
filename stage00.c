#include <assert.h>
#include <nusys.h>

#include "constants.h"
#include "dialogue.h"
#include "displaytext.h"
#include "main.h"
#include "gamemath.h"
#include "graphic.h"
#include "mapdata.h"
#include "maps/maplookup.h"
#include "monsters.h"
#include "nustdfuncs.h"
#include "tracknumbers.h"
#include "segmentinfo.h"
#include "stagekeys.h"
#include "board.h"
#include "pieces.h"

#ifdef N_AUDIO
#include <nualsgi_n.h>
#else
#include <nualsgi.h>
#endif

static float gameplayTimePassed;

// TODO: break some of this into its own file later
typedef void (*MonsterUpdateCall)(int index);

static Vec2 positions[NUMBER_OF_INGAME_ENTITIES];
static Vec2 velocities[NUMBER_OF_INGAME_ENTITIES];
static u8 isActive[NUMBER_OF_INGAME_ENTITIES];
static int health[NUMBER_OF_INGAME_ENTITIES];
static float orientations[NUMBER_OF_INGAME_ENTITIES];
static float radiiSquared[NUMBER_OF_INGAME_ENTITIES];
static float knockbackTimesRemaining[NUMBER_OF_INGAME_ENTITIES];
static u8 isKnockingBackStates[NUMBER_OF_INGAME_ENTITIES];
static u8 lineOfSightVisible[NUMBER_OF_INGAME_ENTITIES];
static MonsterUpdateCall updateFunctions[NUMBER_OF_INGAME_ENTITIES];
static Gfx* renderCommands[NUMBER_OF_INGAME_ENTITIES];
static Mtx monsterSpecificTransforms[NUMBER_OF_INGAME_ENTITIES];

// The player is always index zero; the remaining are monsters
#define playerPosition (positions[0])
#define playerVelocity (velocities[0])
#define playerOrientation (orientations[0])
#define playerHealth (health[0])
#define isPlayerKnockingBack (isKnockingBackStates[0])
#define playerKnockbackTimeRemaining (knockbackTimesRemaining[0])
#define playerRadiusSquared (radiiSquared[0])

#define OGRE_WALK_SPEED 0.5f
void updateOgre(int index) {
  if (isKnockingBackStates[index]) {
    return;
  }

  if (!(lineOfSightVisible[index])) {
    velocities[index].x = 0.f;
    velocities[index].y = 0.f;
    return;
  }

  velocities[index] = (Vec2){ playerPosition.x - positions[index].x, playerPosition.y - positions[index].y };
  normalize(&(velocities[index]));
  orientations[index] = nu_atan2(velocities[index].y, velocities[index].x) + M_PI_2;
  velocities[index].x *= OGRE_WALK_SPEED;
  velocities[index].y *= OGRE_WALK_SPEED;
}

#define TOAD_WALK_SPEED 2.1616f
void updateToad(int index) {
  if (isKnockingBackStates[index]) {
    return;
  }

  const float t = sinf(gameplayTimePassed * 14.f) ;
  guRotateRPY(&(monsterSpecificTransforms[index]), t * 20.f, t * 6.f, 0.f);

  int shouldChangeDirections = 0;

  Vec2 checkPoint = positions[index];
  if (velocities[index].x > 0.f) {
    checkPoint.x += 0.25f;
  } else {
    checkPoint.x -= 0.25f;
  }

  if ((checkPoint.x <= 0.01f) || (checkPoint.x > (BOARD_WIDTH - 0.01f))) {
    shouldChangeDirections = 1;
  }

  if (isSpaceOccupiedButIgnoreMovingPieces((int)(checkPoint.x), (int)(checkPoint.y)) > -1) {
    shouldChangeDirections = 1;
  }


  if (shouldChangeDirections) {
    velocities[index].x *= -1;

    orientations[index] = M_PI_2 * (velocities[index].x < 0.f ? -1.f : 1.f);
  }
}

#define PLAYER_HEIGHT_ABOVE_GROUND 0.26f
#define PLAYER_WALK_SPEED 3.f
#define PLAYER_TURN_SPEED 3.f

#define PLAYER_MAX_HEALTH 5
#define INV_MAX_HEALTH (1.f / PLAYER_MAX_HEALTH)

#define CHESS_PIECE_RADIUS 1.f
#define CHESS_PIECE_RADIUS_SQ (CHESS_PIECE_RADIUS * CHESS_PIECE_RADIUS)

#define KNOCKBACK_SPEED 7.5f
#define KNOCKBACK_TIME 0.216f

#define PLAYER_RADIUS 0.5f

#define PUZZLE_GLYPH_ROTATION_SPEED 64.f
static Pos2 puzzleSpaceSpots[MAX_NUMBER_OF_PUZZLE_SPACES];
static u32 numberOfPuzzleSpaces;
static float puzzleGlyphRotation;

static float cursorRotation;


#define FADE_OUT_TIME 1.f

#define GAME_STATE_ACTIVE 0
#define GAME_STATE_PLAYER_WINS 1
#define GAME_STATE_PLAYER_LOSES 2
static u8 gameState;
static float gameStateTime;

static float playerHealthDisplay;

static float cosCameraRot;
static float sinCameraRot;

static int lineOfSightCheckIndex;

#define BOARD_CONTROL_NO_SELECTED 0
#define BOARD_CONTROL_PIECE_SELECTED 1
static u32 boardControlState;
static u8 legalDestinationState[NUMBER_OF_BOARD_CELLS];

static Pos2 chessboardSpotHighlighted;
static u8 lerpingAngleToCursor;

static int selectedPiece;

static u8 isStagePaused;

#define TIME_BANNER_ONSCREEN 3.f
static const char* bannerMessageText;
static float bannerMessageTime;

#define VERTS_PER_FLOOR_TILE 4
#define NUMBER_OF_FLOOR_VERTS (NUMBER_OF_BOARD_CELLS * VERTS_PER_FLOOR_TILE)
static Vtx floorVerts[NUMBER_OF_FLOOR_VERTS];

static u8 floorTexture[TMEM_SIZE_BYTES] __attribute__((aligned(8)));

static u8 hudIconsTexture[TMEM_SIZE_BYTES] __attribute__((aligned(8)));

static u8 hudNoiseBackgroundsTextre[TMEM_SIZE_BYTES] __attribute__((aligned(8)));

#define NUMBER_OF_HUD_BACKGROUND_TILES 16
static u32 hudBackgroundTextureIndex;

#define INV_BOARD_WIDTH (1.f / (float)BOARD_WIDTH)
#define INV_BOARD_HEIGHT (1.f / (float)BOARD_HEIGHT)

#define VERT_BUFFER_SIZE 64

#define COMMANDS_END_DL_SIZE 1
static Gfx floorDL[(NUMBER_OF_BOARD_CELLS * 2) + COMMANDS_END_DL_SIZE];

static char floorStartBanner[32];

static Vtx wallVerts[((BOARD_WIDTH * 2) + (BOARD_HEIGHT * 2)) * VERTS_PER_FLOOR_TILE];
static Gfx wallDL[(BOARD_WIDTH * 2) + (BOARD_HEIGHT * 2) + 4 + COMMANDS_END_DL_SIZE];

const char* highlightedPieceText;

static Vtx puzzleSpaceVerts[] = {
  { -1, -1,  0, 0,  97 << 5,  0 << 5, 0x5B, 0xff, 0xff, 0xff },
  {  1, -1,  0, 0, 128 << 5,  0 << 5, 0x5B, 0xff, 0xff, 0xff },
  {  1,  1,  0, 0, 128 << 5, 32 << 5, 0x5B, 0xff, 0xff, 0xff },
  { -1,  1,  0, 0,  97 << 5, 32 << 5, 0x5B, 0xff, 0xff, 0xff },
};

static Gfx renderPuzzleSpaceCommands[] = {
  gsSPVertex(puzzleSpaceVerts, 16, 0),
  gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
  gsSPEndDisplayList()
};

// TODO: let us customize/randomize the textures for this on init time
void generateFloorTiles() {
  Gfx* commands = floorDL;
  Vtx* verts = floorVerts;
  Vtx* lastLoad = verts;

  gDPSetCombineMode(commands++, G_CC_MODULATEIA, G_CC_MODULATEIA);
  gDPSetRenderMode(commands++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
  gDPLoadTextureBlock(commands++,  OS_K0_TO_PHYSICAL(floorTexture), G_IM_FMT_IA, G_IM_SIZ_8b, 128, 32, 0, G_TX_NOMIRROR, G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
  gDPPipeSync(commands++);
  gSPTexture(commands++, 0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);

  for (int i = 0; i < NUMBER_OF_BOARD_CELLS; i++) {
    const int x = (i % BOARD_WIDTH);
    const int y = (i / BOARD_WIDTH);

    if (tileIsDark(x, y)) {
      *(verts++) = (Vtx){ x + 0, y + 0,  0, 0,  0 << 5,  0 << 5, 0x33, 0x33, 0x88 - ((i / BOARD_WIDTH) * 14), 0xff };
      *(verts++) = (Vtx){ x + 1, y + 0,  0, 0, 32 << 5,  0 << 5, 0x33, 0x33, 0x88 - ((i / BOARD_WIDTH) * 14), 0xff };
      *(verts++) = (Vtx){ x + 1, y + 1,  0, 0, 32 << 5, 32 << 5, 0x33, 0x33, 0x88 - ((i / BOARD_WIDTH) * 14), 0xff };
      *(verts++) = (Vtx){ x + 0, y + 1,  0, 0,  0 << 5, 32 << 5, 0x33, 0x33, 0x88 - ((i / BOARD_WIDTH) * 14), 0xff };
    } else {
      *(verts++) = (Vtx){ x + 0, y + 0,  0, 0,  0 << 5,  0 << 5, 0xbf, 0xbf, 0xbf - (y * 15), 0xff };
      *(verts++) = (Vtx){ x + 1, y + 0,  0, 0, 32 << 5,  0 << 5, 0xbf, 0xbf, 0xbf - (y * 15), 0xff };
      *(verts++) = (Vtx){ x + 1, y + 1,  0, 0, 32 << 5, 32 << 5, 0xbf, 0xbf, 0xbf - (y * 15), 0xff };
      *(verts++) = (Vtx){ x + 0, y + 1,  0, 0,  0 << 5, 32 << 5, 0xbf, 0xbf, 0xbf - (y * 15), 0xff };
    }

    if ((verts - lastLoad) >= VERT_BUFFER_SIZE) {
      gSPVertex(commands++, &(lastLoad[0]), VERT_BUFFER_SIZE, 0);
      for (int j = 0; j < VERT_BUFFER_SIZE; j += 4) {
        gSP2Triangles(commands++, j + 0, j + 1, j + 2, 0, j + 0, j + 2, j + 3, 0);
      }

      lastLoad = verts;
    }
  }

  gSPEndDisplayList(commands++);
}

#define WALL_HEIGHT 1

// TODO: let us customize/randomize the textures for this on init time
void generateWalls() {
  Gfx* commands = wallDL;
  Vtx* verts = wallVerts;
  Vtx* lastLoad = verts;

  for (int i = 0; i < BOARD_WIDTH; i++) {
    *(verts++) = (Vtx){ i + 1, 0,  0, 0,  64 << 5,  0 << 5, 0x46, 0x55, 0x6b, 0xff };
    *(verts++) = (Vtx){ i + 0, 0,  0, 0,  96 << 5,  0 << 5, 0x46, 0x55, 0x6b, 0xff };
    *(verts++) = (Vtx){ i + 0, 0,  WALL_HEIGHT, 0,  96 << 5, 32 << 5, 0x46, 0x55, 0x6b, 0xff };
    *(verts++) = (Vtx){ i + 1, 0,  WALL_HEIGHT, 0,  64 << 5, 32 << 5, 0x46, 0x55, 0x6b, 0xff };
  }
  gSPVertex(commands++, &(lastLoad[0]), (BOARD_WIDTH * 4), 0);
  for (int j = 0; j < (BOARD_WIDTH * 4); j += 4) {
    gSP2Triangles(commands++, j + 0, j + 1, j + 2, 0, j + 0, j + 2, j + 3, 0);
  }
  lastLoad = verts;

  for (int i = 0; i < BOARD_WIDTH; i++) {
    *(verts++) = (Vtx){ i + 0, BOARD_HEIGHT,  0, 0,  64 << 5,  0 << 5, 0x46, 0x55, 0x6b, 0xff };
    *(verts++) = (Vtx){ i + 1, BOARD_HEIGHT,  0, 0,  96 << 5,  0 << 5, 0x46, 0x55, 0x6b, 0xff };
    *(verts++) = (Vtx){ i + 1, BOARD_HEIGHT,  WALL_HEIGHT, 0,  96 << 5, 32 << 5, 0x46, 0x55, 0x6b, 0xff };
    *(verts++) = (Vtx){ i + 0, BOARD_HEIGHT,  WALL_HEIGHT, 0,  64 << 5, 32 << 5, 0x46, 0x55, 0x6b, 0xff };
  }
  gSPVertex(commands++, &(lastLoad[0]), (BOARD_WIDTH * 4), 0);
  for (int j = 0; j < (BOARD_WIDTH * 4); j += 4) {
    gSP2Triangles(commands++, j + 0, j + 1, j + 2, 0, j + 0, j + 2, j + 3, 0);
  }
  lastLoad = verts;

  for (int i = 0; i < BOARD_HEIGHT; i++) {
    *(verts++) = (Vtx){ 0, i + 0,  0, 0,  64 << 5,  0 << 5, 0x46, 0x55, 0x6b, 0xff };
    *(verts++) = (Vtx){ 0, i + 1,  0, 0,  96 << 5,  0 << 5, 0x46, 0x55, 0x6b, 0xff };
    *(verts++) = (Vtx){ 0, i + 1,  WALL_HEIGHT, 0,  96 << 5, 32 << 5, 0x46, 0x55, 0x6b, 0xff };
    *(verts++) = (Vtx){ 0, i + 0,  WALL_HEIGHT, 0,  64 << 5, 32 << 5, 0x46, 0x55, 0x6b, 0xff };
  }
  gSPVertex(commands++, &(lastLoad[0]), (BOARD_HEIGHT * 4), 0);
  for (int j = 0; j < (BOARD_HEIGHT * 4); j += 4) {
    gSP2Triangles(commands++, j + 0, j + 1, j + 2, 0, j + 0, j + 2, j + 3, 0);
  }
  lastLoad = verts;

  for (int i = 0; i < BOARD_HEIGHT; i++) {
    *(verts++) = (Vtx){ BOARD_WIDTH, i + 1,  0, 0,  64 << 5,  0 << 5, 0x46, 0x55, 0x6b, 0xff };
    *(verts++) = (Vtx){ BOARD_WIDTH, i + 0,  0, 0,  96 << 5,  0 << 5, 0x46, 0x55, 0x6b, 0xff };
    *(verts++) = (Vtx){ BOARD_WIDTH, i + 0,  WALL_HEIGHT, 0,  96 << 5, 32 << 5, 0x46, 0x55, 0x6b, 0xff };
    *(verts++) = (Vtx){ BOARD_WIDTH, i + 1,  WALL_HEIGHT, 0,  64 << 5, 32 << 5, 0x46, 0x55, 0x6b, 0xff };
  }
  gSPVertex(commands++, &(lastLoad[0]), (BOARD_HEIGHT * 4), 0);
  for (int j = 0; j < (BOARD_HEIGHT * 4); j += 4) {
    gSP2Triangles(commands++, j + 0, j + 1, j + 2, 0, j + 0, j + 2, j + 3, 0);
  }
  lastLoad = verts;

  gSPEndDisplayList(commands++);
}


static Vtx HUDBackgroundVerts[] = {
  {             ACTION_SAFE_HORIZONTAL,                    0,  0, 0,               ACTION_SAFE_HORIZONTAL << 5,  0 << 5, 0x1d, 0x61, 0x50, 0xff },
  { SCREEN_WD - ACTION_SAFE_HORIZONTAL,                    0,  0, 0, (SCREEN_WD - ACTION_SAFE_HORIZONTAL) << 5,  0 << 5, 0x1d, 0x61, 0x50, 0xff },
  { SCREEN_WD - ACTION_SAFE_HORIZONTAL, ACTION_SAFE_VERTICAL,  0, 0, (SCREEN_WD - ACTION_SAFE_HORIZONTAL) << 5, (ACTION_SAFE_VERTICAL) << 5, 0x1d, 0x61, 0x50, 0xff },
  {             ACTION_SAFE_HORIZONTAL, ACTION_SAFE_VERTICAL,  0, 0,               ACTION_SAFE_HORIZONTAL << 5, (ACTION_SAFE_VERTICAL) << 5, 0x1d, 0x61, 0x50, 0xff },

  {                      0,                0,  0, 0,  0 << 5,         0 << 5, 0x1d, 0x61, 0x50, 0xff },
  { ACTION_SAFE_HORIZONTAL,                0,  0, 0, 16 << 5,         0 << 5, 0x1d, 0x61, 0x50, 0xff },
  { ACTION_SAFE_HORIZONTAL,        SCREEN_HT,  0, 0, 16 << 5, SCREEN_HT << 5, 0x1d, 0x61, 0x50, 0xff },
  {                      0,        SCREEN_HT,  0, 0,  0 << 5, SCREEN_HT << 5, 0x1d, 0x61, 0x50, 0xff },

  { SCREEN_WD - ACTION_SAFE_HORIZONTAL,                0,  0, 0,  0 << 5,         0 << 5, 0x1d, 0x61, 0x50, 0xff },
  { SCREEN_WD                         ,                0,  0, 0, 16 << 5,         0 << 5, 0x1d, 0x61, 0x50, 0xff },
  { SCREEN_WD                         ,        SCREEN_HT,  0, 0, 16 << 5, SCREEN_HT << 5, 0x1d, 0x61, 0x50, 0xff },
  { SCREEN_WD - ACTION_SAFE_HORIZONTAL,        SCREEN_HT,  0, 0,  0 << 5, SCREEN_HT << 5, 0x1d, 0x61, 0x50, 0xff },

  {         0,   SCREEN_HT - 80,  0, 0,         0 << 5,         (SCREEN_HT - 80) << 5, 0x1d, 0x61, 0x50, 0xff },
  { SCREEN_WD,   SCREEN_HT - 80,  0, 0, SCREEN_WD << 5,         (SCREEN_HT - 80) << 5, 0x1d, 0x61, 0x50, 0xff },
  { SCREEN_WD,        SCREEN_HT,  0, 0, SCREEN_WD << 5, SCREEN_HT << 5, 0x1d, 0x61, 0x50, 0xff },
  {         0,        SCREEN_HT,  0, 0,         0 << 5, SCREEN_HT << 5, 0x1d, 0x61, 0x50, 0xff },
};

static Gfx renderHudBackgroundCommands[] = {
  gsSPVertex(HUDBackgroundVerts, 16, 0),
  gsSP2Triangles(0, 2, 1, 0, 0, 3, 2, 0),
  gsSP2Triangles(4, 6, 5, 0, 4, 7, 6, 0),
  gsSP2Triangles(8, 10, 9, 0, 8, 11, 10, 0),
  gsSP2Triangles(12, 14, 13, 0, 12, 15, 14, 0),
  gsSPEndDisplayList()
};

#define HUD_CELL_WIDTH 16
#define HUD_CELL_HEIGHT 10

#define HUD_CHESSBOARD_WIDTH (HUD_CELL_WIDTH * BOARD_WIDTH)
#define HUD_CHESSBOARD_HEIGHT (BOARD_HEIGHT * HUD_CELL_HEIGHT)
#define HUD_CHESSBOARD_X (SCREEN_WD - HUD_CHESSBOARD_WIDTH - TITLE_SAFE_HORIZONTAL)
#define HUD_CHESSBOARD_Y (SCREEN_HT - HUD_CHESSBOARD_HEIGHT - TITLE_SAFE_VERTICAL)


static Vtx onscreenChessboardVerts[NUMBER_OF_FLOOR_VERTS];
static Gfx onscreenChessboardCommands[(NUMBER_OF_BOARD_CELLS * 2) + COMMANDS_END_DL_SIZE];

void generateHUDChessboard() {
  Gfx* commands = onscreenChessboardCommands;
  Vtx* verts = onscreenChessboardVerts;
  Vtx* lastLoad = verts;

  for (int i = 0; i < NUMBER_OF_BOARD_CELLS; i++) {
    const int x = ((i % BOARD_WIDTH) * HUD_CELL_WIDTH) + HUD_CHESSBOARD_X;
    const int y = HUD_CHESSBOARD_HEIGHT - ((i / BOARD_WIDTH) * HUD_CELL_HEIGHT) + HUD_CHESSBOARD_Y;

    if (tileIsDark(i % BOARD_WIDTH, i / BOARD_WIDTH)) {
      *(verts++) = (Vtx){ x + 0             , y + 0              ,  0, 0,  0 << 5,  0 << 5, 0x60, 0x60, 0x91 - ((i / BOARD_WIDTH) * 10), 0xff };
      *(verts++) = (Vtx){ x + HUD_CELL_WIDTH, y + 0              ,  0, 0, 32 << 5,  0 << 5, 0x60, 0x60, 0x91 - ((i / BOARD_WIDTH) * 10), 0xff };
      *(verts++) = (Vtx){ x + HUD_CELL_WIDTH, y - HUD_CELL_HEIGHT,  0, 0, 32 << 5, 32 << 5, 0x60, 0x60, 0x91 - ((i / BOARD_WIDTH) * 10), 0xff };
      *(verts++) = (Vtx){ x + 0             , y - HUD_CELL_HEIGHT,  0, 0,  0 << 5, 32 << 5, 0x60, 0x60, 0x91 - ((i / BOARD_WIDTH) * 10), 0xff };
    } else {
      *(verts++) = (Vtx){ x + 0             , y + 0              ,  0, 0,  0 << 5,  0 << 5, 0xbf, 0xbf, 0xbf - ((i / BOARD_WIDTH) * 12), 0xff };
      *(verts++) = (Vtx){ x + HUD_CELL_WIDTH, y + 0              ,  0, 0, 32 << 5,  0 << 5, 0xbf, 0xbf, 0xbf - ((i / BOARD_WIDTH) * 12), 0xff };
      *(verts++) = (Vtx){ x + HUD_CELL_WIDTH, y - HUD_CELL_HEIGHT,  0, 0, 32 << 5, 32 << 5, 0xbf, 0xbf, 0xbf - ((i / BOARD_WIDTH) * 12), 0xff };
      *(verts++) = (Vtx){ x + 0             , y - HUD_CELL_HEIGHT,  0, 0,  0 << 5, 32 << 5, 0xbf, 0xbf, 0xbf - ((i / BOARD_WIDTH) * 12), 0xff };
    }

    if ((verts - lastLoad) >= VERT_BUFFER_SIZE) {
      gSPVertex(commands++, &(lastLoad[0]), VERT_BUFFER_SIZE, 0);
      for (int j = 0; j < VERT_BUFFER_SIZE; j += 4) {
        gSP2Triangles(commands++, j + 0, j + 1, j + 2, 0, j + 0, j + 2, j + 3, 0);
      }

      lastLoad = verts;
    }
  }

  gSPEndDisplayList(commands++);
}

static Vtx playerFOVHUDVerts[] = {
  {  0,  20,  0, 0, 128 << 5,  0 << 5, 0xff, 0xff, 0xff, 0xff },
  { 20,  20,  0, 0, 144 << 5,  0 << 5, 0xff, 0xff, 0xff, 0xff },
  { 20, -20,  0, 0, 144 << 5, 16 << 5, 0xff, 0xff, 0xff, 0xff },
  {  0, -20,  0, 0, 128 << 5, 16 << 5, 0xff, 0xff, 0xff, 0xff },
};

void loadInTextures() {
  nuPiReadRom((u32)(_hud_iconsSegmentRomStart), (void*)(hudIconsTexture), TMEM_SIZE_BYTES);
  nuPiReadRom((u32)(_floor_tilesSegmentRomStart), (void*)(floorTexture), TMEM_SIZE_BYTES);
  nuPiReadRom((u32)(_noise_backgroundsSegmentRomStart), (void*)(hudNoiseBackgroundsTextre), TMEM_SIZE_BYTES);
}

void initMonsterStates() {
  lineOfSightCheckIndex = 0;

  for (int i = MONSTER_START_INDEX; i < NUMBER_OF_INGAME_ENTITIES; i++) {
    isActive[i] = 0;
    positions[i] = (Vec2){ 0.f, 0.f };
    velocities[i] = (Vec2){ 0.f, 0.f };
    orientations[i] = 0.f;
    radiiSquared[i] = (0.7f * 0.7f);
    health[i] = 1;
    isKnockingBackStates[i] = 0;
    knockbackTimesRemaining[i] = 0.f;
    lineOfSightVisible[i] = 0;
    guMtxIdent(&(monsterSpecificTransforms[i]));
  }
}

void initializeMonsters(const MapData* map) {
  initMonsterStates();


  for (int i = 0; i < MAX_NUMBER_OF_INGAME_MONSTERS; i++) {
    if (!(map->activeMonsters[i])) {
      continue;
    }

    isActive[i + 1] = map->activeMonsters[i];
    positions[i + 1] = (Vec2){ map->monsterX[i] + 0.5f, map->monsterY[i] + 0.5f };
    const u8 type = map->monsterType[i];
    if (type == MONSTER_TYPE_OGRE) {
      updateFunctions[i + 1] = updateOgre;
      renderCommands[i + 1] = ogre_commands;
      health[i + 1] = 2;
    } else if (type == MONSTER_TYPE_TOAD) {
      updateFunctions[i + 1] = updateToad;
      renderCommands[i + 1] = toad_commands;
      velocities[i + 1].x = TOAD_WALK_SPEED;
      orientations[i + 1] = M_PI_2;
      health[i + 1] = 1;
    }
  }

}

void initializeStartingPieces(const MapData* map) {
  initPieceStates();

  for (int i = 0; i < MAX_NUMBER_OF_INGAME_PIECES; i++) {
    if (!(map->activePieces[i])) {
      continue;
    }

    piecesActive[i] = map->activePieces[i];
    piecePositions[i] = (Pos2){ map->pieceX[i], map->pieceY[i] };
    pieceViewPos[i] = (Vec2){ piecePositions[i].x + 0.5f, piecePositions[i].y + 0.5f };
    pieceData[i].type = (PieceType)(map->pieceType[i]);
    pieceData[i].selectable = 1;

    switch (pieceData[i].type) {
      case PAWN:
        pieceData[i].type = PAWN;
        pieceData[i].legalCheck = pawnLegalMove;
        pieceData[i].renderCommands = pawn_commands;
        pieceData[i].displayName = "PAWN";
        break;
      case ROOK:
        pieceData[i].type = ROOK;
        pieceData[i].legalCheck = rookLegalMove;
        pieceData[i].renderCommands = rook_commands;
        pieceData[i].displayName = "ROOK";
        break;
      case KNIGHT:
        pieceData[i].type = KNIGHT;
        pieceData[i].legalCheck = knightLegalMove;
        pieceData[i].renderCommands = knight_commands;
        pieceData[i].displayName = "KNIGHT";
        break;
      case BISHOP:
        pieceData[i].type = BISHOP;
        pieceData[i].legalCheck = bishopLegalMove;
        pieceData[i].renderCommands = pawn_commands;
        pieceData[i].displayName = "BISHOP";
        break;
      case QUEEN:
        pieceData[i].type = QUEEN;
        pieceData[i].legalCheck = queenLegalMove;
        pieceData[i].renderCommands = queen_commands;
        pieceData[i].displayName = "QUEEN";
        break;
      case KING:
        pieceData[i].type = KING;
        pieceData[i].legalCheck = kingLegalMove;
        pieceData[i].renderCommands = king_commands;
        pieceData[i].displayName = "KING";
        break;
      default:
        pieceData[i].selectable = 0;
        pieceData[i].type = WALL;
        pieceData[i].legalCheck = wallLegalMove;
        pieceData[i].renderCommands = wall_commands;
        pieceData[i].displayName = "";
    }
  }

}

void initPuzzleStates() {
  puzzleGlyphRotation = 0.f;
  numberOfPuzzleSpaces = 0;
  for (int i = 0; i < MAX_NUMBER_OF_PUZZLE_SPACES; i++) {
    puzzleSpaceSpots[i] = (Pos2){ 0, 0 };
  }
}

void initializePuzzleSpots(const MapData* map) {
  initPuzzleStates();

  numberOfPuzzleSpaces = map->numberOfPuzzleSpots;
  for (int i = 0; i < map->numberOfPuzzleSpots; i++) {
    puzzleSpaceSpots[i] = (Pos2){ map->puzzleSpotX[i], map->puzzleSpotY[i] };
  }
}

static MapData mapInformation __attribute__((aligned(8)));

void initializeMapFromROM(const char* mapKey) {
  struct dialogueMappingData* mapOffsetInfo = getMapDataOffset(mapKey, _nstrlen(mapKey));
  if (mapOffsetInfo != 0x0) {
    nuPiReadRom((u32)(_map_dataSegmentRomStart + mapOffsetInfo->offset), &mapInformation, sizeof(MapData));
  }

  // TODO: Maybe we should stub this in some way?
}

/* The initialization of stage 0 */
void initStage00(void)
{
  isStagePaused = 0;
  gameplayTimePassed = 0.f;

  gameState = GAME_STATE_ACTIVE;
  gameStateTime = 0.f;

  initializeMapFromROM(levels[(currentLevel % NUMBER_OF_LEVELS)].levelKey);

  isActive[0] = 1; // player is always active
  initializeMonsters(&mapInformation);
  initializePuzzleSpots(&mapInformation);
  initializeStartingPieces(&mapInformation);
  generateWalls();
  generateHUDChessboard();
  generateFloorTiles();
  loadInTextures();

  highlightedPieceText = "";

  hudBackgroundTextureIndex = currentLevel % NUMBER_OF_HUD_BACKGROUND_TILES;

  playerPosition = (Vec2){ mapInformation.playerX + 0.5f, mapInformation.playerY + 0.5f };
  playerVelocity = (Vec2){ 0.f, 0.f };
  playerOrientation = mapInformation.playerRotation / 256.f * M_PI * 2.f;
  isPlayerKnockingBack = 0;
  playerKnockbackTimeRemaining = 0.f;
  playerRadiusSquared = PLAYER_RADIUS * PLAYER_RADIUS;

  cosCameraRot = cosf(playerOrientation);
  sinCameraRot = sinf(playerOrientation);

  if (mapInformation.startLevelDialogue[0] != '\0') {
    startDialogue(mapInformation.startLevelDialogue);
  }

  playerHealth = PLAYER_MAX_HEALTH;
  playerHealthDisplay = 0.f;

  chessboardSpotHighlighted = (Pos2){ 2, 2 };
  for (int i = 0; i < NUMBER_OF_BOARD_CELLS; i++) {
    legalDestinationState[i] = 0;
  }
  cursorRotation = 0.f;

  selectedPiece = -1;

  sprintf(floorStartBanner, "FLOOR %d START!", (currentLevel + 1));
  bannerMessageText = floorStartBanner;
  bannerMessageTime = 0.f;
}

/* Make the display list and activate the task */
void makeDL00(void)
{
  Dynamic* dynamicp;
  char conbuf[20]; 

  /* Specify the display list buffer */
  dynamicp = &gfx_dynamic[gfx_gtask_no];
  glistp = &gfx_glist[gfx_gtask_no][0];

  /* Initialize RCP */
  gfxRCPInit();

  /* Clear the frame and Z-buffer */
  gfxClearCfb();

  // This is used for `gSPPerspNormalize` 
  u16 perspectiveNorm = 0;

  guScale(&dynamicp->blenderExportScale, BLENDER_EXPORT_MODEL_SCALE, BLENDER_EXPORT_MODEL_SCALE, BLENDER_EXPORT_MODEL_SCALE);

  guOrtho(&dynamicp->ortho, 0.f, SCREEN_WD, SCREEN_HT, 0.f, 1.0F, 10.0F, 1.0F);
  guPerspective(&dynamicp->projection, &perspectiveNorm, ingameFOV, ((float)SCREEN_WD)/((float)SCREEN_HT), 0.1f, 100.f, 1.f);
  guLookAt(&dynamicp->camera, playerPosition.x + (sinCameraRot * 1.f), playerPosition.y - (cosCameraRot * 1.f), PLAYER_HEIGHT_ABOVE_GROUND + 0.25f, playerPosition.x, playerPosition.y, PLAYER_HEIGHT_ABOVE_GROUND, 0.f, 0.f, 1.f);
  guMtxIdent(&dynamicp->modelling);

  guTranslate(&dynamicp->cursorTranslate, chessboardSpotHighlighted.x + 0.5f, chessboardSpotHighlighted.y + 0.5f, 0.f);
  guRotate(&dynamicp->cursorRotate, cursorRotation * M_RTOD, 0.f, 0.f, 1.f);

  gSPMatrix(glistp++,OS_K0_TO_PHYSICAL(&(dynamicp->projection)), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
  gSPMatrix(glistp++,OS_K0_TO_PHYSICAL(&(dynamicp->camera)), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH );

  gDPSetCycleType(glistp++,G_CYC_1CYCLE);
  gDPSetTexturePersp(glistp++, G_TP_PERSP);
  gDPSetTextureFilter(glistp++, G_TF_POINT);
  gDPSetRenderMode(glistp++,G_RM_OPA_SURF, G_RM_OPA_SURF2);
  gDPPipeSync(glistp++);
  gSPClearGeometryMode(glistp++,0xFFFFFFFF);
  gSPSetGeometryMode(glistp++,G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK);
  gSPClipRatio(glistp++, FRUSTRATIO_6);

  gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(floorDL));

  guScale(&dynamicp->puzzleSpaceScale, 0.5f, 0.5f, 0.5f);
  guRotate(&dynamicp->puzzleSpaceRotation, puzzleGlyphRotation, 0.f, 0.f, 1.f);
  for (int i = 0; i < numberOfPuzzleSpaces; i++) {
    guTranslate(&(dynamicp->puzzleSpaceTranslations[i]), puzzleSpaceSpots[i].x + 0.5f, puzzleSpaceSpots[i].y + 0.5f, 0.f);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->puzzleSpaceTranslations[i])), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&dynamicp->puzzleSpaceRotation), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&dynamicp->puzzleSpaceScale), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

    gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(renderPuzzleSpaceCommands));

    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
  }

  gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(wallDL));

  gSPTexture(glistp++, 0xffff, 0xffff, 0, G_TX_RENDERTILE, G_OFF);

  gDPPipeSync(glistp++);
  gDPSetCombineMode(glistp++, G_CC_SHADE, G_CC_SHADE);
  gDPSetRenderMode(glistp++,G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2);
  gSPSetGeometryMode(glistp++, G_ZBUFFER);

  for (int i = 0; i < MAX_NUMBER_OF_INGAME_PIECES; i++) {
    if (!(piecesActive[i])) {
      continue;
    }

    guTranslate(&(dynamicp->pieceTransforms[i]), pieceViewPos[i].x, pieceViewPos[i].y, 0.f);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->pieceTransforms[i])), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&dynamicp->blenderExportScale), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

    gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(pieceData[i].renderCommands));

    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
  }

  for (int i = MONSTER_START_INDEX; i < NUMBER_OF_INGAME_ENTITIES; i++) {
    if (!(isActive[i])) {
      continue;
    }


    guTranslate(&(dynamicp->monsterTranslations[i - 1]), positions[i].x, positions[i].y, 0.f);
    guRotate(&(dynamicp->monsterRotations[i - 1]), orientations[i] * INV_PI * 180, 0.f, 0.f, 1.f);
    dynamicp->customTransforms[i - 1] = monsterSpecificTransforms[i];
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->monsterTranslations[i - 1])), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->customTransforms[i - 1])), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&dynamicp->monsterRotations[i - 1]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&dynamicp->blenderExportScale), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

    gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(renderCommands[i]));

    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
  }


  // Draw the cursor
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->cursorTranslate)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->cursorRotate)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
  gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&dynamicp->blenderExportScale), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
  gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(&(cursor_commands)));
  gSPPopMatrix(glistp++, G_MTX_MODELVIEW);

  gSPClearGeometryMode(glistp++, G_ZBUFFER);
  gDPPipeSync(glistp++);
  gDPSetRenderMode(glistp++, G_RM_OPA_SURF, G_RM_OPA_SURF2);


  // drawing the HUD
  gSPMatrix(glistp++,OS_K0_TO_PHYSICAL(&(dynamicp->ortho)), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
  gSPMatrix(glistp++,OS_K0_TO_PHYSICAL(&(dynamicp->modelling)), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH );

  gDPPipeSync(glistp++);
  gDPSetCombineMode(glistp++, G_CC_MODULATEI, G_CC_MODULATEI);
  gDPSetRenderMode(glistp++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
  gDPSetTexturePersp(glistp++, G_TP_NONE);
  gDPLoadTextureTile(glistp++,  OS_K0_TO_PHYSICAL(hudNoiseBackgroundsTextre + (16 * 16 * hudBackgroundTextureIndex)), G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, 0 << 2, 0 << 2, (0 + 15) << 2, (15) << 2, 0, G_TX_NOMIRROR, G_TX_NOMIRROR, 4, 4, G_TX_NOLOD, G_TX_NOLOD);
  gSPTexture(glistp++, 0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);
  gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(renderHudBackgroundCommands));


  gDPPipeSync(glistp++);
  // gDPSetCombineMode(glistp++, G_CC_SHADE, G_CC_SHADE);
  // gDPSetRenderMode(glistp++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
  // gSPTexture(glistp++, 0xffff, 0xffff, 0, G_TX_RENDERTILE, G_OFF);
  gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(onscreenChessboardCommands));
  
  gDPSetCombineMode(glistp++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
  gDPSetRenderMode(glistp++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
  gDPLoadTextureBlock(glistp++, OS_K0_TO_PHYSICAL(hudIconsTexture), G_IM_FMT_IA, G_IM_SIZ_8b, 256, 16, 0, G_TX_NOMIRROR, G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
  gDPPipeSync(glistp++);
  gSPTexture(glistp++, 0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);

  const u32 playerHUDXPos = (playerPosition.x * INV_BOARD_WIDTH * HUD_CHESSBOARD_WIDTH + HUD_CHESSBOARD_X) - 8;
  const u32 playerHUDYPos = ((BOARD_HEIGHT - playerPosition.y) * INV_BOARD_HEIGHT * HUD_CHESSBOARD_HEIGHT + HUD_CHESSBOARD_Y) - 8;

  // Render the player's FOV
  {
    guTranslate(&(dynamicp->playerFOVTranslate), playerHUDXPos + 8, playerHUDYPos + 8, 0.f);
    guRotate(&(dynamicp->playerFOVRotate), (playerOrientation * -INV_PI * 180.f) - 90.f, 0.f, 0.f, 1.f);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->playerFOVTranslate)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&(dynamicp->playerFOVRotate)), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

    gDPPipeSync(glistp++);
    gDPSetTexturePersp(glistp++, G_TP_PERSP);
    
    gDPSetPrimColor(glistp++, 0, 0, 0xCC, 0x77, 0x22, 0xff);
    gSPVertex(glistp++, &(playerFOVHUDVerts[0]), 4, 0);
    gSP2Triangles(glistp++, 0, 1, 2, 0, 0, 2, 3, 0);

    gDPPipeSync(glistp++);
    gDPSetTexturePersp(glistp++, G_TP_NONE);

    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
  }

  // Render the puzzle spaces
  gDPSetPrimColor(glistp++, 0, 0, 0x00, 0xff, 0xff, 0xff);
  for (int i = 0; i < numberOfPuzzleSpaces; i++) {

    const u32 puzzleSpotX = HUD_CHESSBOARD_X + ((puzzleSpaceSpots[i].x) * HUD_CELL_WIDTH);
    const u32 puzzleSpotY = HUD_CHESSBOARD_Y + ((BOARD_HEIGHT - 1 - puzzleSpaceSpots[i].y) * HUD_CELL_HEIGHT) - ((16 - HUD_CELL_HEIGHT) / 2);

    gSPTextureRectangle(glistp++, (puzzleSpotX) << 2, (puzzleSpotY) << 2, (puzzleSpotX + 16) << 2, (puzzleSpotY + 16) << 2, 0, (208) << 5, 0 << 5, 1 << 10, 1 << 10);
  }

  // Render the piece locations on the HUD
  gDPSetPrimColor(glistp++, 0, 0, 0xCC, 0xCC, 0xCC, 0xff);
  for (int i = 0; i < MAX_NUMBER_OF_INGAME_PIECES; i++) {
    if (!(piecesActive[i])) {
      continue;
    }

    const u32 pieceHUDSpotX = HUD_CHESSBOARD_X + ((pieceViewPos[i].x - 0.5f) * HUD_CELL_WIDTH);
    const u32 pieceHUDSpotY = HUD_CHESSBOARD_Y + ((BOARD_HEIGHT - pieceViewPos[i].y - 0.5f) * HUD_CELL_HEIGHT) - ((16 - HUD_CELL_HEIGHT) / 2);

    gSPTextureRectangle(glistp++, (pieceHUDSpotX) << 2, (pieceHUDSpotY) << 2, (pieceHUDSpotX + 16) << 2, (pieceHUDSpotY + 16) << 2, 0, ((int)(pieceData[i].type) * 16) << 5, 0 << 5, 1 << 10, 1 << 10);
  }

  // Render the monster icons
  gDPSetPrimColor(glistp++, 0, 0, 0x99, 0x3a, 0x00, 0xff);
  for (int i = MONSTER_START_INDEX; i < NUMBER_OF_INGAME_ENTITIES; i++) {
    if (!(isActive[i])) {
      continue;
    }

    if (!(lineOfSightVisible[i])) {
      continue;
    }

    const u32 monsterHUDSpotX = HUD_CHESSBOARD_X + (positions[i].x * HUD_CELL_WIDTH) - 8;
    const u32 monsterHUDSpotY = HUD_CHESSBOARD_Y + ((BOARD_HEIGHT - positions[i].y) * HUD_CELL_HEIGHT) - 8;

    gSPTextureRectangle(glistp++, monsterHUDSpotX << 2, monsterHUDSpotY << 2, (monsterHUDSpotX + 16) << 2, (monsterHUDSpotY + 16) << 2, 0, 144 << 5, 0 << 5, 1 << 10, 1 << 10);
  }

  // Render the player location on the HUD
  {
    gDPSetPrimColor(glistp++, 0, 0, 0x11, 0x99, 0x22, 0xff);
    gSPTextureRectangle(glistp++, (playerHUDXPos) << 2, (playerHUDYPos) << 2, (playerHUDXPos + 16) << 2, (playerHUDYPos + 16) << 2, 0, 112 << 5, 0 << 5, 1 << 10, 1 << 10);
    gDPSetPrimColor(glistp++, 0, 0, 0xAC, 0x84, 0x40, 0xff);
    gSPTextureRectangle(glistp++, (playerHUDXPos) << 2, (playerHUDYPos) << 2, (playerHUDXPos + 16) << 2, (playerHUDYPos + 16) << 2, 0,  96 << 5, 0 << 5, 1 << 10, 1 << 10);
  }

  // Render legal move spots
  if (boardControlState == BOARD_CONTROL_PIECE_SELECTED) {
    gDPSetPrimColor(glistp++, 0, 0, 0xFF, 0x00, 0x00, 0xff);
    for (int i = 0; i < NUMBER_OF_BOARD_CELLS; i++) {
      if ((selectedPiece > -1) && (piecePositions[selectedPiece].x == (i % BOARD_WIDTH)) && (piecePositions[selectedPiece].y == (i / BOARD_WIDTH))) {
        continue;
      }

      if (!(legalDestinationState[i])) {
        const u32 noSpotX = HUD_CHESSBOARD_X + ((i % BOARD_WIDTH) * HUD_CELL_WIDTH);
        const u32 noSpotY = HUD_CHESSBOARD_Y + ((BOARD_HEIGHT - 1 - (i / BOARD_WIDTH)) * HUD_CELL_HEIGHT) - ((16 - HUD_CELL_HEIGHT) / 2);
        gSPTextureRectangle(glistp++, (noSpotX) << 2, (noSpotY) << 2, (noSpotX + 16) << 2, (noSpotY + 16) << 2, 0, 192 << 5, 0 << 5, 1 << 10, 1 << 10);
      }
    }
  }

  // Render the cursor's location on the HUD
  {
    const u32 highightedSpotX = HUD_CHESSBOARD_X + (chessboardSpotHighlighted.x * HUD_CELL_WIDTH);
    const u32 highightedSpotY = (HUD_CHESSBOARD_Y + ((BOARD_HEIGHT - 1 - chessboardSpotHighlighted.y) * HUD_CELL_HEIGHT)) - ((16 - HUD_CELL_HEIGHT) / 2);

    gDPSetPrimColor(glistp++, 0, 0, N64_C_BUTTONS_RED, N64_C_BUTTONS_GREEN, N64_C_BUTTONS_BLUE, 0xff);
    gSPTextureRectangle(glistp++, (highightedSpotX) << 2, (highightedSpotY) << 2, (highightedSpotX + 16) << 2, (highightedSpotY + 16) << 2, 0,  176 << 5, 0 << 5, 1 << 10, 1 << 10);
  }

  gDPLoadTextureBlock_4b(glistp++, OS_K0_TO_PHYSICAL(displayTextTexture), G_IM_FMT_IA, 512, 16, 0, G_TX_NOMIRROR, G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
  
  char cursorSpotString[] = { '\0', '\0', '\0'};
  boardPosToLetter(&chessboardSpotHighlighted, &(cursorSpotString[0]), &(cursorSpotString[1]));
  gDPSetPrimColor(glistp++, 0, 0, N64_C_BUTTONS_RED, N64_C_BUTTONS_GREEN, N64_C_BUTTONS_BLUE, 0xff);
  renderDisplayText(HUD_CHESSBOARD_X - (27), HUD_CHESSBOARD_Y + 18 + 16, cursorSpotString);

  gDPSetPrimColor(glistp++, 0, 0, 0xff, 0xff, 0xff, 0xff);
  if (selectedPiece > -1) {
    renderDisplayText(HUD_CHESSBOARD_X - (27) - (30), HUD_CHESSBOARD_Y + 18 + 16, "TO");
  }

  renderDisplayText(HUD_CHESSBOARD_X - (12 * 8), HUD_CHESSBOARD_Y + 18, highlightedPieceText);

  gDPPipeSync(glistp++);
  gDPSetCycleType(glistp++, G_CYC_FILL);
  gDPSetFillColor(glistp++, GPACK_RGBA5551(0x21,0,0,1) << 16 | GPACK_RGBA5551(0x21,0,0,1));
  gDPFillRectangle(glistp++, (HUD_CHESSBOARD_X - 72), (SCREEN_HT - TITLE_SAFE_VERTICAL - 16), (HUD_CHESSBOARD_X - 7), (SCREEN_HT - TITLE_SAFE_VERTICAL));
  gDPPipeSync(glistp++);
  gDPSetFillColor(glistp++, GPACK_RGBA5551(0x33,0xc0,0x22,1) << 16 | GPACK_RGBA5551(0x33,0xc0,0x22,1));
  gDPFillRectangle(glistp++, (HUD_CHESSBOARD_X - 72), (SCREEN_HT - TITLE_SAFE_VERTICAL - 16), (HUD_CHESSBOARD_X - 72) + MAX(0, playerHealthDisplay * INV_MAX_HEALTH * 65.f), (SCREEN_HT - TITLE_SAFE_VERTICAL));

  gDPPipeSync(glistp++);
  gDPSetCycleType(glistp++, G_CYC_1CYCLE);
  renderDisplayText((HUD_CHESSBOARD_X - 72) + 2, (SCREEN_HT - TITLE_SAFE_VERTICAL - 16) - 4, "LIFE");

  if (gameState == GAME_STATE_PLAYER_LOSES) {
    renderDisplayText(SCREEN_WD / 2 - ((5 * 13) / 2), SCREEN_HT / 2, "DEATH");
  } else if (gameState == GAME_STATE_PLAYER_WINS) {
    renderDisplayText(SCREEN_WD / 2 - ((11 * 13) / 2), SCREEN_HT / 2, "FLOOR CLEAR!");
  } else if (isStagePaused) {
    renderDisplayText(SCREEN_WD / 2 - ((6 * 13) / 2), SCREEN_HT / 2, "PAUSED");
  } else if (bannerMessageText != NULL) {

    // TODO: clean this up!
    if (bannerMessageTime < 0.25f) {
      renderDisplayText(((SCREEN_WD / 2) * bannerMessageTime / 0.25f) - (((_nstrlen(bannerMessageText)) * 13) / 2), SCREEN_HT / 2, bannerMessageText);
    } else if (bannerMessageTime > (TIME_BANNER_ONSCREEN - 0.25f)) {
      renderDisplayText((SCREEN_WD / 2)  + ((SCREEN_WD / 2) * (((bannerMessageTime - (TIME_BANNER_ONSCREEN - 0.25f)) / 0.25f))) - (((_nstrlen(bannerMessageText)) * 13) / 2), SCREEN_HT / 2, bannerMessageText);
    } else {
      renderDisplayText(SCREEN_WD / 2 - (((_nstrlen(bannerMessageText)) * 13) / 2), SCREEN_HT / 2, bannerMessageText);
    }

    
  }

  renderDialogueToDisplayList();

  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  assert((glistp - gfx_glist[gfx_gtask_no]) < GFX_GLIST_LEN);

  nuGfxTaskStart(&gfx_glist[gfx_gtask_no][0], (s32)(glistp - gfx_glist[gfx_gtask_no]) * sizeof (Gfx), NU_GFX_UCODE_F3DLP_REJ , NU_SC_NOSWAPBUFFER);

  nuDebConClear(0);
  nuDebConTextPos(0,4,23);
  sprintf(conbuf,"DL: %04d/%04d", (glistp - gfx_glist[gfx_gtask_no]), GFX_GLIST_LEN);
  nuDebConCPuts(0, conbuf);
  nuDebConTextPos(0,4,24);
  sprintf(conbuf,"delta: %3.5f", deltaTimeSeconds);
  nuDebConCPuts(0, conbuf);
    
  /* Display characters on the frame buffer */
  nuDebConDisp(NU_SC_SWAPBUFFER);

  /* Switch display list buffers */
  gfx_gtask_no = (gfx_gtask_no + 1) % BUFFER_COUNT;
}

void updatePlayerInput() {
  Vec2 inputDir = { 0.f, 0.f };

  // Update rotation
  if (
      ((contdata[0].button & R_TRIG) && (contdata[0].trigger & L_TRIG)) ||
      ((contdata[0].button & L_TRIG) && (contdata[0].trigger & R_TRIG)) ||
      (contdata[0].trigger & Z_TRIG) 
      ) {
    chessboardSpotHighlighted.x = (int)(playerPosition.x - (sinCameraRot * 1.51f));
    chessboardSpotHighlighted.y = (int)(playerPosition.y + (cosCameraRot * 1.51f));

  } else if (((contdata[0].button & (L_TRIG | R_TRIG)) == (L_TRIG | R_TRIG)) || (contdata[0].button & Z_TRIG)) {
    cursorRotation = lerpAngle(cursorRotation, playerOrientation, 0.3f);

  } else if((contdata[0].button & L_TRIG) || (contdata[0].stick_x < -7)) {
    playerOrientation += PLAYER_TURN_SPEED * deltaTimeSeconds;

    if (playerOrientation > M_PI) {
      playerOrientation = -M_PI;
    }
    cursorRotation = lerpAngle(cursorRotation, 0.f, 0.34f);
  } else if((contdata[0].button & R_TRIG) || (contdata[0].stick_x > 7)) {
    playerOrientation -= PLAYER_TURN_SPEED * deltaTimeSeconds;

    if (playerOrientation < -M_PI) {
      playerOrientation = M_PI;
    }
    cursorRotation = lerpAngle(cursorRotation, 0.f, 0.34f);
  } else {
    cursorRotation = lerpAngle(cursorRotation, 0.f, 0.34f);
  }
  cosCameraRot = cosf(playerOrientation);
  sinCameraRot = sinf(playerOrientation);

  // We don't need to continue if we're being knocked back
  if (isPlayerKnockingBack) {
    return;
  }


  if (contdata[0].stick_y > 7) {
    inputDir.y = 1.f;
  } else if (contdata[0].stick_y < -7) {
    inputDir.y = -1.f;
  }

  // Update position
  if(contdata[0].button & U_JPAD) {
    inputDir.y = 1.f;
  } else if(contdata[0].button & D_JPAD) {
    inputDir.y = -1.f;
  }

  if((contdata[0].button & R_JPAD) || (((contdata[0].button & Z_TRIG) || ((contdata[0].button & (L_TRIG | R_TRIG)) == (L_TRIG | R_TRIG))) && (contdata[0].stick_x > 7))) {
    inputDir.x = 1.f;
  } else if((contdata[0].button & L_JPAD) || (((contdata[0].button & Z_TRIG) || ((contdata[0].button & (L_TRIG | R_TRIG)) == (L_TRIG | R_TRIG))) && (contdata[0].stick_x < -7))) {
    inputDir.x = -1.f;
  }

  const float rotatedXStep = (cosCameraRot * inputDir.x) - (sinCameraRot * inputDir.y);
  const float rotatedYStep = (sinCameraRot * inputDir.x) + (cosCameraRot * inputDir.y);
  playerVelocity.x = rotatedXStep * PLAYER_WALK_SPEED;
  playerVelocity.y = rotatedYStep * PLAYER_WALK_SPEED;
}

void updateMovement() {
  for (int i = 0; i < NUMBER_OF_INGAME_ENTITIES; i++) {
    if (!(isActive[i])) {
      continue;
    }

    Vec2 desiredSpot = { positions[i].x + (velocities[i].x * deltaTimeSeconds), positions[i].y + (velocities[i].y * deltaTimeSeconds) };

    // step x
    if (isSpaceOccupiedButIgnoreMovingPieces((int)(desiredSpot.x), (int)(positions[i].y)) > -1) {
      if (velocities[i].x > 0.f) {
        desiredSpot.x = (float)((int)(desiredSpot.x) - 1) + 0.999f;
      } else if (velocities[i].x < 0.f) {
        desiredSpot.x = (float)((int)(desiredSpot.x) + 1);
      }
    }

    // step y
    if (isSpaceOccupiedButIgnoreMovingPieces((int)(desiredSpot.x), (int)(desiredSpot.y)) > -1) {
      if (velocities[i].y > 0.f) {
        desiredSpot.y = (float)((int)(desiredSpot.y) - 1) + 0.999f;
      } else if (velocities[i].y < 0.f) {
        desiredSpot.y = (float)((int)(desiredSpot.y) + 1);
      }
    }

    positions[i].x = desiredSpot.x;
    positions[i].y = desiredSpot.y;

    // Don't let the entity leave the playing area
    positions[i].x = clamp(positions[i].x, 0.f, (float)BOARD_WIDTH);
    positions[i].y = clamp(positions[i].y, 0.f, (float)BOARD_HEIGHT);
  }
}

void updateBoardControlInput() {
  if (((contdata[0].button & (L_TRIG | R_TRIG)) == (L_TRIG | R_TRIG)) || (contdata[0].button & Z_TRIG)) {
    Vec2 fstep = { 0, 0 };

    if(contdata[0].trigger & U_CBUTTONS) {
      fstep.y = 1.51f;
    } else if(contdata[0].trigger & D_CBUTTONS) {
      fstep.y = -1.51f;
    }

    if(contdata[0].trigger & R_CBUTTONS) {
      fstep.x = 1.51f;
    } else if(contdata[0].trigger & L_CBUTTONS) {
      fstep.x = -1.51f;
    }

    Pos2 step = (Pos2){ (int)((cosCameraRot * fstep.x) - (sinCameraRot * fstep.y)), (int)((sinCameraRot * fstep.x) + (cosCameraRot * fstep.y)) };

    chessboardSpotHighlighted.x =  (chessboardSpotHighlighted.x + step.x + BOARD_WIDTH) % BOARD_WIDTH;
    chessboardSpotHighlighted.y =  (chessboardSpotHighlighted.y + step.y + BOARD_HEIGHT) % BOARD_HEIGHT;
  } else {
    if(contdata[0].trigger & U_CBUTTONS) {
      chessboardSpotHighlighted.y = (chessboardSpotHighlighted.y + 1) % BOARD_HEIGHT;
    } else if(contdata[0].trigger & D_CBUTTONS) {
      chessboardSpotHighlighted.y = (chessboardSpotHighlighted.y - 1 + BOARD_HEIGHT) % BOARD_HEIGHT;
    }

    if(contdata[0].trigger & R_CBUTTONS) {
      chessboardSpotHighlighted.x = (chessboardSpotHighlighted.x + 1) % BOARD_WIDTH;
    } else if(contdata[0].trigger & L_CBUTTONS) {
      chessboardSpotHighlighted.x = (chessboardSpotHighlighted.x - 1 + BOARD_WIDTH) % BOARD_WIDTH;
    }
  }

  if (boardControlState == BOARD_CONTROL_NO_SELECTED) {
    if (contdata[0].trigger & A_BUTTON) {
      const int pieceAtCursorSpot = isSpaceOccupied(chessboardSpotHighlighted.x, chessboardSpotHighlighted.y);

      if (pieceAtCursorSpot >= 0 && pieceData[pieceAtCursorSpot].selectable) {
        // TODO: unselectable pieces

        boardControlState = BOARD_CONTROL_PIECE_SELECTED;
        selectedPiece = pieceAtCursorSpot;

        for (int i = 0; i < NUMBER_OF_BOARD_CELLS; i++) {
          legalDestinationState[i] = 0;
        }
        pieceData[selectedPiece].legalCheck(selectedPiece, piecesActive, piecePositions, legalDestinationState);
      }
    }
  } else if (boardControlState == BOARD_CONTROL_PIECE_SELECTED) {
    if (contdata[0].trigger & B_BUTTON) {
      selectedPiece = -1;
      boardControlState = BOARD_CONTROL_NO_SELECTED;
      //
    } else if (contdata[0].trigger & A_BUTTON) {
      assert(selectedPiece >= 0); // we should have a selected piece here
      const int pieceAtCursorSpot = isSpaceOccupied(chessboardSpotHighlighted.x, chessboardSpotHighlighted.y);

      int isSelectedSpotValid = pieceAtCursorSpot < 0;

      // If the destination isn't legal we can't place it there
      if (!(legalDestinationState[(chessboardSpotHighlighted.x % BOARD_WIDTH) + (chessboardSpotHighlighted.y * BOARD_WIDTH)])) {
        isSelectedSpotValid = 0;
      }

      if (isSelectedSpotValid) {
        oldPiecePos[selectedPiece] = (Vec2){ piecePositions[selectedPiece].x + 0.5f, piecePositions[selectedPiece].y + 0.5f };

        piecePositions[selectedPiece] = chessboardSpotHighlighted;
        pieceIsLerping[selectedPiece] = 1;
        pieceLerpValue[selectedPiece] = 0.f;

        // TODO: play a "complete" sound
      } else {
        // TODO: play a "wrong" sound
      }

      selectedPiece = -1;
      boardControlState = BOARD_CONTROL_NO_SELECTED;
    }
  }
}

void updateMovingPieces() {
  for (int i = 0; i < MAX_NUMBER_OF_INGAME_PIECES; i++) {
    if (!(piecesActive[i])) {
      continue;
    }

    if (!(pieceIsLerping[i])) {
      continue;
    }

    pieceLerpValue[i] += 0.05f;

    if (pieceLerpValue[i] >= 1.f) {
      pieceLerpValue[i] = 0.f;
      pieceIsLerping[i] = 0;

      pieceViewPos[i] = (Vec2){ piecePositions[i].x + 0.5f, piecePositions[i].y + 0.5f };
    } else {

      // Knights have a more disjoint way of travelling
      if (pieceData[i].type == KNIGHT) {
        const Vec2 delta = { (piecePositions[i].x + 0.5f) - oldPiecePos[i].x, (piecePositions[i].y + 0.5f) - oldPiecePos[i].y };
        if (fabsf(delta.x) > fabsf(delta.y)) {
          if (pieceLerpValue[i] < 0.75f) {
            pieceViewPos[i] = (Vec2){ lerp(oldPiecePos[i].x, piecePositions[i].x + 0.5f, pieceLerpValue[i] * 1.3333333f), oldPiecePos[i].y };
          } else {
            pieceViewPos[i] = (Vec2){ piecePositions[i].x + 0.5f, lerp(oldPiecePos[i].y, piecePositions[i].y + 0.5f, (pieceLerpValue[i] - 0.75f) / 0.333f) };
          }
        } else {
          if (pieceLerpValue[i] < 0.75f) {
            pieceViewPos[i] = (Vec2){ oldPiecePos[i].x, lerp(oldPiecePos[i].y, piecePositions[i].y + 0.5f, pieceLerpValue[i] * 1.3333333f) };
          } else {
            pieceViewPos[i] = (Vec2){ lerp(oldPiecePos[i].x, piecePositions[i].x + 0.5f, (pieceLerpValue[i] - 0.75f) / 0.333f), piecePositions[i].y + 0.5f };
          }
        }
      } else {
        pieceViewPos[i] = (Vec2){ lerp(oldPiecePos[i].x, piecePositions[i].x + 0.5f, pieceLerpValue[i]), lerp(oldPiecePos[i].y, piecePositions[i].y + 0.5f, pieceLerpValue[i]) };
      }
    }
  }
}

void updateHUDInformation() {
  // Update the text for the selected piece
  if (boardControlState == BOARD_CONTROL_NO_SELECTED) {
    const int pieceAtCursorSpot = isSpaceOccupied(chessboardSpotHighlighted.x, chessboardSpotHighlighted.y);
    if (pieceAtCursorSpot > -1) {
      highlightedPieceText = pieceData[pieceAtCursorSpot].displayName;
    } else {
      highlightedPieceText = "";
    }
  }

  // Lerp the player's healthbar to their health;
  playerHealthDisplay = lerp(playerHealthDisplay, playerHealth, 0.13f);
}

void checkCollisionWithPieces() {
  for (int i = 0; i < MAX_NUMBER_OF_INGAME_PIECES; i++) {
    if (!(piecesActive[i])) {
      continue;
    }

    if (!(pieceIsLerping[i])) {
      continue;
    }

    for (int j = 0; j < NUMBER_OF_INGAME_ENTITIES; j++) {
      if (isKnockingBackStates[j]) {
        continue;
      }

      // Radius check
      const float distanceSquared = distanceSq(&positions[j], &(pieceViewPos[i]));
      if (distanceSquared > MAX(radiiSquared[j], CHESS_PIECE_RADIUS_SQ)) {
        continue;
      }

      isKnockingBackStates[j] = 1;
      knockbackTimesRemaining[j] = KNOCKBACK_TIME;

      health[j] = MAX(health[j] - 1, 0);
      if ((j > 0) && (health[j] < 1)) {
        isActive[j] = 0;
      }

      // Fly back away from the piece
      // TODO: perhaps make this perpindicular via a cross product?
      velocities[j] = (Vec2){ positions[j].x - pieceViewPos[i].x, positions[j].y - pieceViewPos[i].y };
      normalize(&velocities[j]);
      velocities[j].x *= KNOCKBACK_SPEED;
      velocities[j].y *= KNOCKBACK_SPEED;
    }

  }
}

void updateKnockback() {
  for (int i = 0; i < NUMBER_OF_INGAME_ENTITIES; i++) {
    if (!(isKnockingBackStates[i])) {
      continue;
    }

    knockbackTimesRemaining[i] -= deltaTimeSeconds;
    if (knockbackTimesRemaining[i] <= 0.f) {
      isKnockingBackStates[i] = 0;
      velocities[i] = (Vec2){ 0.f, 0.f };
    }
  }
}

#define LINE_OF_SIGHT_CHECK_STEP 0.06f

void checkLineOfSight(int index) {
  // Skip inactive monsters
  if (!(isActive[index])) {
    return;
  }

  // No need to check the player
  if (index == 0) {
    return;
  }

  const Vec2* monsterPos = &(positions[index]);

  for (float i = 0.f; i < 1.f; i += LINE_OF_SIGHT_CHECK_STEP ) {
    const Vec2 checkPos = { lerp(playerPosition.x, monsterPos->x, i), lerp(playerPosition.y, monsterPos->y, i) };
    int occupiedSpaceIndex = isSpaceOccupied(((int)checkPos.x), ((int)checkPos.y));
    if (occupiedSpaceIndex > -1) {
      if (pieceData[occupiedSpaceIndex].type != WALL) {
        continue;
      }

      lineOfSightVisible[index] = 0;
      return;
    }
  }

  lineOfSightVisible[index] = 1;
}

void tickLineOfSight() {
  checkLineOfSight(lineOfSightCheckIndex);
  lineOfSightCheckIndex = (lineOfSightCheckIndex + 1) % NUMBER_OF_INGAME_ENTITIES;
}

void updateMonsters() {
  tickLineOfSight();

  for (int i = MONSTER_START_INDEX; i < NUMBER_OF_INGAME_ENTITIES; i++) {
    if (!(isActive[i])) {
      continue;
    }

    updateFunctions[i](i);
  }
}

void checkCollisionWithMonsters() {
  if (playerHealth <= 0) {
    return;
  }

  if (isPlayerKnockingBack) {
    return;
  }

  for (int i = MONSTER_START_INDEX; i < NUMBER_OF_INGAME_ENTITIES; i++) {
    if (!(isActive[i])) {
      continue;
    }

    if (isKnockingBackStates[i]) {
      continue;
    }

    const float distanceSquared = distanceSq(&playerPosition, &(positions[i]));
    if (distanceSquared > MAX(radiiSquared[i], playerRadiusSquared)) {
      continue;
    }

    playerHealth = MAX(playerHealth - 1, 0);

    isPlayerKnockingBack = 1;
    playerKnockbackTimeRemaining = KNOCKBACK_TIME;
    playerVelocity = (Vec2){ playerPosition.x - positions[i].x, playerPosition.y - positions[i].y };
    normalize(&(playerVelocity));
    playerVelocity.x *= KNOCKBACK_SPEED;
    playerVelocity.y *= KNOCKBACK_SPEED;
  }
}

void checkGameState() {
  // Check if all the monsters have been defeated
  u32 monstersAlive = 0;
  {
    // TODO: for chess puzzle floors, we need to do more than check monster status
    for (int i = MONSTER_START_INDEX; i < NUMBER_OF_INGAME_ENTITIES; i++) {
      if (isActive[i]) {
        monstersAlive = 1;
        break;
      }
    }
  }

  // Check if all the puzzle spaces are covered
  u32 allPuzzleSpacesAreCovered = 1;
  {
    for (int i = 0; i < numberOfPuzzleSpaces; i++) {
      const Pos2* puzzleSpot = &(puzzleSpaceSpots[i]);

      u32 puzzleSpaceIsCovered = 0;
      for (int j = 0; j < MAX_NUMBER_OF_INGAME_PIECES; j++) {
        if (!(piecesActive[j])) {
          continue;
        }

        // If the piece is moving, don't worry about it for now
        if (pieceIsLerping[j]) {
          continue;
        }

        if ((piecePositions[j].x == puzzleSpot->x) && (piecePositions[j].y == puzzleSpot->y)) {
          puzzleSpaceIsCovered = 1;
          break;
        }
      }

      if (!puzzleSpaceIsCovered) {
        allPuzzleSpacesAreCovered = 0;
        break;
      }
    }
  }

  if (playerHealth <= 0) {
    gameState = GAME_STATE_PLAYER_LOSES;
  }

  if ((!monstersAlive) && allPuzzleSpacesAreCovered) {
    gameState = GAME_STATE_PLAYER_WINS;
  }
}

void checkPawnsForPromotion() {
  for (int i = 0; i < MAX_NUMBER_OF_INGAME_PIECES; i++) {
    if (pieceData[i].type != PAWN) {
      continue;
    }

    if (!(piecesActive[i])) {
      continue;
    }

    if (pieceIsLerping[i]) {
      continue;
    }

    if (piecePositions[i].y < (BOARD_HEIGHT - 1)) {
      continue;
    }

    // If we've made it here, promote this pawn to a queen
    pieceData[i].type = QUEEN;
    pieceData[i].renderCommands = queen_commands;
    pieceData[i].legalCheck = queenLegalMove;
    pieceData[i].displayName = "QUEEN";

    bannerMessageTime = 0.f;
    bannerMessageText = "PROMOTION";
  }
}

void updateTransition() {
  gameStateTime += deltaTimeSeconds;

  if (gameStateTime > FADE_OUT_TIME) {
    nextStage = &levelSelectStage;
    changeScreensFlag = 1;
    return;
  }
}

void updateBannerMessageText() {
  if (bannerMessageText == NULL) {
    return;
  }

  bannerMessageTime += deltaTimeSeconds;
  if (bannerMessageTime > TIME_BANNER_ONSCREEN) {
    bannerMessageTime = 0.f;
    bannerMessageText = NULL;
  }
}

void updatePausedState() {
  if (!(contdata[0].trigger & START_BUTTON)) {
    return;
  }

  isStagePaused = !isStagePaused;
}

void updateGame00(void)
{
  nuContDataGetEx(contdata,0);

  if (dialogueState == DIALOGUE_STATE_SHOWING) {
    return;
  }

  gameplayTimePassed += deltaTimeSeconds;
  
  if (gameState == GAME_STATE_ACTIVE) {
    updatePausedState();
    if (isStagePaused) {
      return;
    }

    updatePlayerInput();
    updateBoardControlInput();
  }
  updateMonsters();

  updateMovement();
  updateMovingPieces();
  checkPawnsForPromotion();
  checkCollisionWithPieces();
  checkCollisionWithMonsters();
  updateKnockback();

  if (gameState == GAME_STATE_ACTIVE) {
    checkGameState();
  } else {
    updateTransition();
  }

  puzzleGlyphRotation += deltaTimeSeconds * PUZZLE_GLYPH_ROTATION_SPEED;
  if (puzzleGlyphRotation > 180.f) {
    puzzleGlyphRotation = -180.f;
  }
  
  updateBannerMessageText();
  updateHUDInformation();
}
