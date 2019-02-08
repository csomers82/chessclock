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
#include "JHD162A.h"

/*==========================================================================*\
 | MAIN MCU RAM  
\*==========================================================================*/
int               tenths          = 0;
int               game_active     = 1;
int               active_player   = 0;
int               toggle_player   = 0;
int               timing_modern   = 1;
uint8_t           timing_add      = 30U;
int               line            = LINE1;
int               debounce[2]     = {0};
int               toggle_check[2] = {0};
int               bell_count      = 0;

/*--------------------------------------------------------------------------*\
 | External Variable Definitions
\*--------------------------------------------------------------------------*/

extern uint8_t *  timestr;          // for timestr functions
extern uint8_t *  timezf;           // for timestr functions
extern char       itoaBuffer[6];    // for func: itoa_intobuffer

extern TIM_HandleTypeDef htim1;

/*==========================================================================*\
 | ASSISTANT FUNCTIONS 
\*==========================================================================*/

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
 | app_bell
 |    make sound with the pwm at buzzer
\*--------------------------------------------------------------------------*/
void app_bell(int dur) {
  //turn on the buzzer
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  //hold for 'dur' tenths of a sec
  bell_count = dur;
  return;
}

/*--------------------------------------------------------------------------*\
 | app_debounce 
 |    handle button states following ISR
\*--------------------------------------------------------------------------*/
void app_debounce(uint8_t p) {
  int *Port, Pin;
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


/*==========================================================================*\
 | main: 
\*==========================================================================*/
void app_main() {
  app_bell(20);
  while(1) {
    if (timing_modern) {
      while (game_active)
      {
        HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFE);

        // handle the passing of time
        if (tenths == 10) {
          timestr_sub(10U);
          app_timestr_print(line);
          tenths = 0;
        }

        // update the buzzer
        if (bell_count) {
          if (--bell_count == 0) {
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
          } 
        }

        // toggle check 
        if (toggle_check[0]) {
          app_debounce(0);
        }
        else if (toggle_check[1]) {
          app_debounce(1);
        }

        // handle the toggle of players
        if (toggle_player) {
          timestr_add(timing_add);
          app_timestr_print(line);
          active_player = 1 - active_player;
          timestr_setch(active_player);
          line = (line == LINE1) ? LINE2 : LINE1;
          toggle_player = 0;
          app_bell(20);
        }

        // check gameover
        if (timezf[active_player]) {
          app_bell(60);
          game_active = 0;
        } 
      }// while (game_active), modern timing        
    }
    // wait for alarm off
    while(bell_count) {
      --bell_count;
      HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFE);
    }
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);

    // wait for new game
    while (!game_active) {
      HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFE);
    }
    
  }
  // never return, else error
  return;
}
