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
#include "stm32f0xx_hal.h"
#include <inttypes.h>

#include "basic.h"
#include "timestr.h"
#include "application.h"
#include "chessclock.h"
#include "JHD162A.h"

/*--------------------------------------------------------------------------*\
 | External Variable Definitions
\*--------------------------------------------------------------------------*/

extern uint8_t *  timestr;          // for timestr functions
extern char       itoaBuffer[6];    // for func: itoa_intobuffer

extern TIM_HandleTypeDef htim1;

extern struct BellCode bell_program1[2];
extern struct BellCode bell_program2[2];
extern struct BellCode bell_program3[4];
extern struct BellCode bell_program4[9];

/*==========================================================================*\
 | MAIN MCU RAM  
\*==========================================================================*/
int                 tenth_flag      = FALSE;
int                 tenths          = 0;
int                 game_active     = TRUE;
int                 game_result     = 0;
int                 active_player   = 0;
int                 toggle_player   = 0;
int                 button_flag[2]  = {0};
int                 count_player[2] = {0};
int                 timing_modern   = TRUE;
int                 timing_limit    = SECONDS(600);
uint8_t             timing_add      = 30U;
int                 line            = LINE1;
int                 ts_debounce[2]  = {0};
int                 pb_debounce[2]  = {0};
int                 toggle_check[2] = {0};
int                 button_check[2] = {0};
int                 bell_count      = 0;
struct BellCode    *bell_pc         = 0;//null
TIM_HandleTypeDef  *bellTIM         = &htim1; 
uint32_t            bellCH          = TIM_CHANNEL_2;



/*==========================================================================*\
 | ASSISTANT FUNCTIONS 
\*==========================================================================*/

/*--------------------------------------------------------------------------*\
 | app_timestr_print
 |    output the time characters via the lcd
\*--------------------------------------------------------------------------*/
void app_timestr_print(char line) {
  chgline(line);   
  if(count_player[active_player] >= 6000) {
    print_c(timestr[4]);
    print_c(timestr[3]);
    print_c(':');
    print_c(timestr[2]);
    print_c(timestr[1]);
  }
  else if(count_player[active_player] > THRESH_TENTHS) {
    print_c(' ');
    print_c(timestr[3]);
    print_c(':');
    print_c(timestr[2]);
    print_c(timestr[1]);
  }
  else {
    print_c(' ');
    print_c(timestr[3]);
    print_c(':');
    print_c(timestr[2]);
    print_c(timestr[1]);
    print_c('.');
    print_c(timestr[0]);
  }
  return;
}

/*--------------------------------------------------------------------------*\
 | app_timestr_init
 |    set time characters to provided integer 
\*--------------------------------------------------------------------------*/
void app_timestr_init(int32_t t0) {
  itoa_intoBuffer(t0);
  count_player[active_player] = timestr_ttoi(t0);
  timestr[0] = itoaBuffer[4];
  timestr[1] = itoaBuffer[3];
  timestr[2] = itoaBuffer[2];
  timestr[3] = itoaBuffer[1];
  timestr[4] = itoaBuffer[0];
  return;
}

/*--------------------------------------------------------------------------*\
 | app_bell_start
 |    play the selected bell program 
\*--------------------------------------------------------------------------*/
void app_bell_start(int program) {
  // mv bell ptr to selected rhythm
  switch(program) {
    case CHIME_S: bell_pc = bell_program1; break;
    case CHIME_L: bell_pc = bell_program2; break;
    case ALARM_1: bell_pc = bell_program3; break;
    case ALARM_2: bell_pc = bell_program4; break;
  }

  // read the opening instruction
  bell_count = bell_pc->t;
  if (bell_pc->i == BELL_PLAY) {
    HAL_TIM_PWM_Start(bellTIM, bellCH);
  }
  return;
}

/*--------------------------------------------------------------------------*\
 | app_bell_read
 |    read the current bell instruction
\*--------------------------------------------------------------------------*/
int app_bell_read() {
  if (bell_pc->i != BELL_HALT) {
    // is instruction over?
    if (bell_count == 0) {
      bell_pc += 1;
      bell_count = bell_pc->t;
      // switch play state
      switch (bell_pc->i) {
        case BELL_PLAY:
          HAL_TIM_PWM_Start(bellTIM, bellCH);
          break;
        case BELL_REST:
        case BELL_HALT:
          HAL_TIM_PWM_Stop(bellTIM, bellCH);
          break;
      }
    }
  }
  return(bell_pc->i);
}
/*--------------------------------------------------------------------------*\
 | app_debounce_ts 
 |    handle toggle switch states following ISR
\*--------------------------------------------------------------------------*/
void app_debounce_ts(uint8_t p) {
  GPIO_TypeDef *Port;
  uint16_t      Pin;
  Port = (p == 0) ? TGLA_GPIO_Port  : TGLB_GPIO_Port;
  Pin  = (p == 0) ? TGLA_Pin        : TGLB_Pin;

  // filter if mistep
  if (active_player == (1 - p)) {
    toggle_check[p] = FALSE;
    ts_debounce[p]  = 0;
  }
  // check pin state, inc success, quit fail
  if (HAL_GPIO_ReadPin(Port, Pin)) {
    ++ts_debounce[p];
  }
  else {
    toggle_check[p] = FALSE;
    ts_debounce[p]  = 0;
  }
  // success exit
  if(ts_debounce[p] == TS_DEB_THRESH) {
    toggle_check[p] = FALSE;
    ts_debounce[p]  = 0;
    toggle_player   = TRUE;
  }
  return;
}

/*--------------------------------------------------------------------------*\
 | app_debounce_pb
 |    handle push button states following ISR
\*--------------------------------------------------------------------------*/
void app_debounce_pb() {
  uint32_t portB = ~stm32f0_read_gpio(GPIOB);

  // check pin state, inc success, quit fail
  if (portB & BTNA_Pin) {
    ++pb_debounce[0];
  }
  // check end condition
  if (button_check[0]) {
    if ((--button_check[0] == 0) || 
        (pb_debounce[0] >= PB_DEB_THRESH))  
    {
      if (pb_debounce[0] >= PB_DEB_THRESH) {
        button_flag[0]  = TRUE;
      }
      pb_debounce[0]  = 0; 
    }
  }
  
  // check pin state, inc success, quit fail
  if (portB & BTNA_Pin) {
    ++pb_debounce[1];
  }
  // check end condition
  if (button_check[1]) {
    if ((--button_check[1] == 0) || 
        (pb_debounce[1] >= PB_DEB_THRESH))  
    {
      if (pb_debounce[1] >= PB_DEB_THRESH) {
        button_flag[1]  = TRUE;
      }
      pb_debounce[1]  = 0; 
    }
  }
  return;
}
