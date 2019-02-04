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
//  Constants
//==============================================================================
#define DEBOUNCE_THRESH (5)

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

#endif//__APPLICATION_
