//==============================================================================
//
//  filename: Src/bell_code.c
//   summary:
//
//   created: Sat Feb  9 15:12:22 CST 2019
//    author: Clifton Somers, user: cliff
//   contact: purduecliffsomers@gmail.com
//
//==============================================================================

#include "application.h"

//------------------
// bell subroutines:
//------------------

struct BellCode bell_program1[2] = {
  //
  // program1: chime, short 
  //
  {BELL_PLAY, 5},             
  {BELL_HALT, 0}
};

struct BellCode bell_program2[2] = {
  //
  // program2: chime, long
  //
  {BELL_PLAY, 20},
  {BELL_HALT, 0}
};

struct BellCode bell_program3[9] = {
  //
  // program3: alarm2
  // beep beep, beep beep
  //
  {BELL_PLAY, 1},
  {BELL_REST, 1},
  {BELL_PLAY, 1},
  {BELL_REST, 5},
  {BELL_PLAY, 1},
  {BELL_REST, 1},
  {BELL_PLAY, 1},
  {BELL_REST, 13},
  {BELL_HALT, 0}
};

struct BellCode bell_program4[4] = {
  //
  // program4: alarm1
  // beep beep, beep beep
  //
  {BELL_PLAY, 1},
  {BELL_REST, 1},
  {BELL_PLAY, 1},
  {BELL_HALT, 0}
};

struct BellCode bell_program5[2] = {
  //
  // program1: chirp
  //
  {BELL_PLAY, 1},             
  {BELL_HALT, 0}
};
