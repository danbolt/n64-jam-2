
#include "stagekeys.h"

#include "audio/bgm/sequence/tracknumbers.h"

LevelEntry levels[NUMBER_OF_LEVELS] = {
  { "twoogres", TRACK_13_WARMING_UP, 0x0 },
  { "tut2_rooks", TRACK_13_WARMING_UP, 0x0 },
  { "tut3_bishops", TRACK_13_WARMING_UP, 0x0 },
  { "tut4_knights", TRACK_13_WARMING_UP, 0x0 },
  { "tut5_king", TRACK_13_WARMING_UP, 0x0 },
  { "solveit", TRACK_13_WARMING_UP, 0x0 },
  { "singlefile", TRACK_13_WARMING_UP, 0x0 },
  { "tut1_move", TRACK_13_WARMING_UP, 0x0 },
  { "1toad", TRACK_13_WARMING_UP, 0x0 },
  { "2toad", TRACK_13_WARMING_UP, 0x0 },
  { "jumper", TRACK_13_WARMING_UP, 0x0 },
  { "snake", TRACK_13_WARMING_UP, 0x0 },
  { "ogre", TRACK_13_WARMING_UP, 0x0 },
  { "lines", TRACK_13_WARMING_UP, 0x0 },
  { "hop", TRACK_13_WARMING_UP, 0x0 },
  { "oneweirdtrick", TRACK_13_WARMING_UP, 0x0 },
  { "adv", TRACK_13_WARMING_UP, 0x0 },
};

float best_times[NUMBER_OF_LEVELS] = { 9999.f };
u32 best_move_count[NUMBER_OF_LEVELS] = { 100 };