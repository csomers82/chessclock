//==============================================================================
//
//  filename: application.h
//   summary:
//
//   created: Thu Jan 31 22:40:54 CST 2019
//    author: Clifton Somers, user: cliff
//   contact: purduecliffsomers@gmail.com
//
//==============================================================================
#ifndef __APPLICATION_
#define __APPLICATION_

#include "main.h"
#include "basic.h"
#include "timestr.h"
#include "stm32f0xx_hal.h"
#include <inttypes.h>
#include "JHD162A.h"

//==============================================================================
//  Structs
//==============================================================================
struct BellCode {
  int i;// instruction
  int t;// duration
};

enum Bell_Progs { 
  CHIME_S, 
  CHIME_L,
  ALARM_1,
  ALARM_2,
  CHIRP
};

enum ColorScheme {
  BVG,// blue versus green
  YVM,// yellow versus magenta
  WTR // white then red
};

enum SoundSettings {
  BELL_MENUSOUNDS,
  BELL_PLAYERTOGGLE,
  BELL_SECALARM,
  BELL_STARTFINISH
};

//==============================================================================
//  Constants
//==============================================================================

// program system tweekables
#define THRESH_TENTHS       (210)

// mcu system tweekables
#define TS_DEB_THRESH       (3)
#define TS_DEB_ATTEMPTS     (5)
#define PB_DEB_THRESH       (2)
#define PB_DEB_ATTEMPTS     (4)

// bell handler "opcodes"
#define BELL_PLAY (2)
#define BELL_REST (1)
#define BELL_HALT (0)

//==============================================================================
//  Functions
//==============================================================================

/*--------------------------------------------------------------------------*\
 | app_timestr_print
 |    output the time characters via the lcd
\*--------------------------------------------------------------------------*/
void app_timestr_print(char line);

/*--------------------------------------------------------------------------*\
 | app_timestr_init
 |    set time characters to provided integer 
\*--------------------------------------------------------------------------*/
void app_timestr_init(int32_t t0);

/*--------------------------------------------------------------------------*\
 | app_debounce_ts 
 |    handle toggle switch states following ISR
\*--------------------------------------------------------------------------*/
void app_debounce_ts(uint8_t p);

/*--------------------------------------------------------------------------*\
 | app_debounce_pb
 |    handle push button states following ISR
\*--------------------------------------------------------------------------*/
void app_debounce_pb(void);

/*--------------------------------------------------------------------------*\
 | app_bell_start
 |    play the selected bell program 
\*--------------------------------------------------------------------------*/
void app_bell_start(int program);

/*--------------------------------------------------------------------------*\
 | app_bell_read
 |    read the current bell instruction
\*--------------------------------------------------------------------------*/
int app_bell_read(void);

#endif//__APPLICATION_
