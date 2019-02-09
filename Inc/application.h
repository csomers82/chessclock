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
  ALARM_1
};


//==============================================================================
//  Constants
//==============================================================================
#define THRESH_DEBOUNCE     (5)
#define THRESH_TENTHS       (210)

// bell handler "opcodes"
#define BELL_PLAY (2)
#define BELL_REST (1)
#define BELL_HALT (0)

#define app_mcu_sleep()     (HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFE))

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
 | app_debounce 
 |    handle button states following ISR
\*--------------------------------------------------------------------------*/
void app_debounce(uint8_t p);

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
