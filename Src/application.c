//==============================================================================
//
//  filename: application.c
//   summary:
//
//   created: Thu Jan 31 21:37:30 CST 2019
//    author: Clifton Somers, user: cliff
//   contact: purduecliffsomers@gmail.com
//
//==============================================================================

#include "main.h"
#include "basic.h"
#include "timestr.h"
#include "application.h"
#include "stm32f0xx_hal.h"
#include <inttypes.h>
#include "JHD162A.h"

/*--------------------------------------------------------------------------*\
 | External Variable Definitions
\*--------------------------------------------------------------------------*/

extern uint8_t *  timestr;          // for timestr functions
extern char       itoaBuffer[6];    // for func: itoa_intobuffer
extern int        toggle_player;
extern int        active_player;
extern int        debounce[2];    
extern int        toggle_check[2];

/*--------------------------------------------------------------------------*\
 | app_timestr_print
 |    output the time characters via the lcd
\*--------------------------------------------------------------------------*/
void app_timestr_print(char line) {
  chgline(line);   
  print_c(timestr[4]);
  print_c(timestr[3]);
  print_c(':');
  print_c(timestr[2]);
  print_c(timestr[1]);
  print_c('.');
  print_c(timestr[0]);
  return;
}

/*--------------------------------------------------------------------------*\
 | app_timestr_init
 |    set time characters to provided integer 
\*--------------------------------------------------------------------------*/
void app_timestr_init(int32_t t0) {
  itoa_intoBuffer(t0);
  timestr[0] = itoaBuffer[4];
  timestr[1] = itoaBuffer[3];
  timestr[2] = itoaBuffer[2];
  timestr[3] = itoaBuffer[1];
  timestr[4] = itoaBuffer[0];
  return;
}

/*--------------------------------------------------------------------------*\
 | app_debounce 
 |    handle button states following ISR
\*--------------------------------------------------------------------------*/
void app_debounce(uint8_t p) {
  int Port, Pin;
  Port = (p == 0) ? TGLA_GPIO_Port  : TGLB_GPIO_Port;
  Pin  = (p == 0) ? TGLA_Pin        : TGLB_Pin;

  // filter if mistep
  if (active_player == (1 - p)) {
    toggle_check[p] = 0;
    debounce[p]     = 0;
  }
  // check pin state, inc success, quit fail
  if (HAL_GPIO_ReadPin(Port, Pin)) {
    ++debounce[p];
  }
  else {
    toggle_check[p] = 0;
    debounce[p]     = 0;
  }
  // success exit
  if(debounce[p] == DEBOUNCE_THRESH) {
    toggle_check[p] = 0;
    debounce[p]     = 0;
    toggle_player = 1;
  }
  return;
}



