
#include "stagekeys.h"

#include "audio/bgm/sequence/tracknumbers.h"

LevelEntry levels[NUMBER_OF_LEVELS] = {
  { "tut1_move", TRACK_13_WARMING_UP, 0x0 },
  { "tut2_rooks", TRACK_13_WARMING_UP, "first_rest" },
  { "tut3_bishops", TRACK_13_WARMING_UP, "second_rest" },
  { "tut4_knights", TRACK_13_WARMING_UP, 0x0 },
  { "tut5_king", TRACK_13_WARMING_UP, "third_rest" },
  { "solveit", TRACK_01_PUZZLE_TIME, 0x0 },
  { "singlefile", TRACK_01_PUZZLE_TIME, "fb1" },

  { "1toad", TRACK_01_PUZZLE_TIME, 0x0 },
  { "2toad", TRACK_01_PUZZLE_TIME, "fb2" },
  { "jumper", TRACK_01_PUZZLE_TIME, 0x0 },
  { "snake", TRACK_02_ODD_BOARD, 0x0 },
  { "ogre", TRACK_02_ODD_BOARD, "test_scene" },

  { "twoogres", TRACK_02_ODD_BOARD, "grass" },

  { "lines", TRACK_02_ODD_BOARD, "dreamscene" },

  // We need a cutscene here where Zatt has a bad dream


  { "oneweirdtrick", TRACK_02_ODD_BOARD, "odd" },

  // also include flashback


  { "finale", TRACK_12_TOP_OF_THE_TOWER, 0x0 },
};