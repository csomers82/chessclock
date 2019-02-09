//==============================================================================
//
//  filename: chessclock.c
//   summary: main program constructs
//
//   created: Sat Feb  9 12:30:07 CST 2019
//    author: Clifton Somers, user: cliff
//   contact: purduecliffsomers@gmail.com
//
//==============================================================================

#include "main.h"
#include "basic.h"
#include "timestr.h"
#include "application.h"
#include "chessclock.h"
#include "stm32f0xx_hal.h"
#include <inttypes.h>
#include "JHD162A.h"

/*--------------------------------------------------------------------------*\
 | External Variable Definitions
\*--------------------------------------------------------------------------*/
extern int        tenths;
extern int        game_active;
extern int        game_result;
extern int        active_player;
extern int        toggle_player;
extern int        timing_modern;
extern uint8_t    timing_add;
extern int        line;
extern int        toggle_check[2];
extern int		 *timezf;

/*--------------------------------------------------------------------------*\
 | chessclock_traditional 
 |    time never increases, linear burndown
\*--------------------------------------------------------------------------*/
void chessclock_traditional() {
  while (game_active)
  {
    // spend less time w/ proc active
    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFE);

    // handle the passing of time
    if (tenths == 10) {
      tenths = 0;
      timestr_sub(10U);
      app_timestr_print(line);
    }

    // update the buzzer
    app_bell_read();

    // toggle check 
    if (toggle_check[0]) {
      app_debounce(0);
    }
    else if (toggle_check[1]) {
      app_debounce(1);
    }

    // handle the toggle of players
    if (toggle_player) {
      toggle_player = 0;
      app_timestr_print(line);
      active_player = 1 - active_player;
      timestr_setch(active_player);
      line = (line == LINE1) ? LINE2 : LINE1;
      app_bell_start(CHIME_S);
    }

    // check gameover
    if (timezf[active_player]) {
      game_active = 0;
    } 
  }// while (game_active), modern timing        
  return;
}
/*--------------------------------------------------------------------------*\
 | chessclock_modern 
 |    time control is incremental 
\*--------------------------------------------------------------------------*/
void chessclock_modern() {
  while (game_active)
  {
    // spend less time w/ proc active
    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFE);

    // handle the passing of time
    if (tenths == 10) {
      tenths = 0;
      timestr_sub(10U);
      app_timestr_print(line);
    }

    // update the buzzer
    app_bell_read();

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
      app_bell_start(CHIME_S);
    }

    // check gameover
    if (timezf[active_player]) {
      game_active = 0;
      game_result = GAMEOVER_TEXP + active_player;
    } 
  }// while (game_active), modern timing        
  return;
}

/*==========================================================================*\
 | main: 
\*==========================================================================*/
void chessclock_main() {
  app_bell_start(CHIME_S);
  while(1) {
    if (timing_modern) {
      chessclock_modern();
    }
    else {
      chessclock_traditional();
    }

    // wait for alarm off
    app_bell_start(ALARM_1);
    while(app_bell_read()) {
      HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFE);
    }
    app_bell_start(ALARM_1);
    while(app_bell_read()) {
      HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFE);
    }

    // wait for new game
    while (!game_active) {
      HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFE);
    }
    
  }
  // never return, else error
  return;
}
