
#include "titlescreen.h"

#include <nusys.h>

#include "main.h"
#include "graphic.h"
#include "segmentinfo.h"
#include "stagekeys.h"

static float timePassed;

static u8 downPressed;
static u8 upPressed;
static u8 stickInDeadzone;

void initTitleScreen() {
  timePassed = 0.f;

  downPressed = 0;
  upPressed = 0;
  stickInDeadzone = 0;
}

void makeTitleScreenDL() {
  Dynamic* dynamicp;
  char conbuf[20]; 

  /* Specify the display list buffer */
  dynamicp = &gfx_dynamic[gfx_gtask_no];
  glistp = &gfx_glist[gfx_gtask_no][0];

  /* Initialize RCP */
  gfxRCPInit();

  /* Clear the frame and Z-buffer */
  gfxClearCfb();

  guOrtho(&dynamicp->ortho, 0.f, SCREEN_WD, SCREEN_HT, 0.f, 1.0F, 10.0F, 1.0F);

  guMtxIdent(&dynamicp->modelling);

  gDPPipeSync(glistp++);
  gDPSetCycleType(glistp++,G_CYC_1CYCLE);
  gDPSetTexturePersp(glistp++, G_TP_NONE);
  gDPSetTextureFilter(glistp++, G_TF_POINT);
  gDPSetCombineMode(glistp++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
  gDPSetRenderMode(glistp++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
  gSPClearGeometryMode(glistp++,0xFFFFFFFF);
  gSPSetGeometryMode(glistp++,G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK);
  gSPTexture(glistp++, 0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);
  gSPClipRatio(glistp++, FRUSTRATIO_2);

  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  nuGfxTaskStart(&gfx_glist[gfx_gtask_no][0], (s32)(glistp - gfx_glist[gfx_gtask_no]) * sizeof (Gfx), NU_GFX_UCODE_F3DLP_REJ , NU_SC_NOSWAPBUFFER);

  nuDebConClear(0);
  nuDebConTextPos(0,4,4);
  sprintf(conbuf,"title screen");
  nuDebConCPuts(0, conbuf);
    
  /* Display characters on the frame buffer */
  nuDebConDisp(NU_SC_SWAPBUFFER);

  gfx_gtask_no = (gfx_gtask_no + 1) % BUFFER_COUNT;
}

void updateTitleScreen() {
  nuContDataGetEx(contdata,0);

  timePassed += deltaTimeSeconds;

  if(contdata[0].trigger & U_JPAD) {
    upPressed = 1;
  } else if(contdata[0].trigger & D_JPAD) {
    downPressed = 1;
  } else {
    upPressed = 0;
    downPressed = 0;
  }

  if (!stickInDeadzone && (contdata[0].stick_y > -7) && (contdata[0].stick_y < 7)) {
    stickInDeadzone = 1;
  }

  if (stickInDeadzone) {
    if (contdata[0].stick_y < -7) {
      upPressed = 1;
      stickInDeadzone = 0;
    } else if (contdata[0].stick_y > 7) {
      downPressed = 1;
      stickInDeadzone = 0;
    }

  }


  if (upPressed) {
    upPressed = 0;
  }
  if (downPressed) {
    downPressed = 1;
  }

  if (contdata[0].trigger & A_BUTTON) {
    nextStage = &levelSelectStage;
    changeScreensFlag = 1;
  }
}