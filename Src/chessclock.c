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
#include "menus.h"
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
extern int        menu_index;
extern int        menu_title;
extern int        menu_event;
extern int        tenth_flag;
extern int        tenths;
extern int        game_active;
extern int        game_result;
extern int        bell_on;
extern int        active_player;
extern int        toggle_player;
extern int        button_flag[2];
extern int        count_player[2];
extern int        timing_modern;
extern uint8_t    timing_add;
extern int        line;
extern int        toggle_check[2];
extern int        button_check[2];
extern uint8_t   *timezf;

/*--------------------------------------------------------------------------*\
 | chessclock_menu
 |    handle menu navigation and input events until game setup 
\*--------------------------------------------------------------------------*/
void chessclock_menu() {
  // menu screen always enters from main menu
  menu_index      = 1;
  menu_title      = 0;
  // draw menu screen on enter
  menu_event      = TRUE;

  while (! game_active ) {
    //------------------------------
    // handle navigation
    //------------------------------
    if (menu_event) {
      if (bell_on) {
        app_bell_start(CHIME_S);
      }
      menu_event = FALSE;
      menu_draw(menu_title, menu_index);
    }

    //------------------------------
    // handle input
    //------------------------------
    if (tenth_flag) {
      // time logic
      tenth_flag = FALSE;
    }

    // update the buzzer
    app_bell_read();

    // toggle check 
    if (toggle_check[0]) {
      app_debounce_ts(0);
    }
    else if (toggle_check[1]) {
      app_debounce_ts(1);
    }
    
    // button check
    if (button_check[0] || button_check[1]) {
      app_debounce_pb();
      if (button_flag[0]) {
        button_flag[0] = FALSE;
        HAL_GPIO_WritePin(BONUS_GPIO_Port, BONUS_Pin, GPIO_PIN_SET);
      } 
      else if (button_flag[1]) {
        button_flag[1] = FALSE;
        HAL_GPIO_WritePin(BONUS_GPIO_Port, BONUS_Pin, GPIO_PIN_RESET);
      }
    }
        
    //------------------------------
    // sleep till next event
    //------------------------------
    app_mcu_sleep();
  }
  return;
}
/*--------------------------------------------------------------------------*\
 | chessclock_traditional 
 |    time never increases, linear burndown
\*--------------------------------------------------------------------------*/
void chessclock_traditional() {
  return;
}
/*--------------------------------------------------------------------------*\
 | chessclock_modern 
 |    time control is incremental 
\*--------------------------------------------------------------------------*/
void chessclock_modern() {
  while (game_active) {
    // spend less time w/ proc active
    app_mcu_sleep();

    // handle the passing of time
    if (tenth_flag) {
      // time logic
      tenth_flag = FALSE;
      count_player[active_player] -= 1; 
      // display logic
      if (count_player[active_player] < THRESH_TENTHS) {
        tenths = 0;
        timestr_sub(1U);
        app_timestr_print(line);
      }
      else {
        if (count_player[active_player] == THRESH_TENTHS) {
          app_bell_start(ALARM_1);
        }
        if (tenths == 10) {
          tenths = 0;
          timestr_sub(10U);
          app_timestr_print(line);
        }
      }
    }

    // update the buzzer
    app_bell_read();

    // toggle check 
    if (toggle_check[0]) {
      app_debounce_ts(0);
    }
    else if (toggle_check[1]) {
      app_debounce_ts(1);
    }
    
    // button check
    if (button_check[0] || button_check[1]) {
      app_debounce_pb();
      if (button_flag[0]) {
        button_flag[0] = FALSE;
        HAL_GPIO_WritePin(BONUS_GPIO_Port, BONUS_Pin, GPIO_PIN_SET);
      } 
      else if (button_flag[1]) {
        button_flag[1] = FALSE;
        HAL_GPIO_WritePin(BONUS_GPIO_Port, BONUS_Pin, GPIO_PIN_RESET);
      }
    }

    // handle the toggle of players
    if (toggle_player) {
      timestr_add(timing_add);
      count_player[active_player] += timing_add;
      app_timestr_print(line);
      active_player = 1 - active_player;
      timestr_setch(active_player);
      line = (line == LINE1) ? LINE2 : LINE1;
      toggle_player = FALSE;
      app_bell_start(CHIME_S);
    }

    // check gameover
    if (*timezf) {
      game_active = FALSE;
      game_result = GAMEOVER_TEXP + active_player;
    } 
  }// while (game_active), modern timing        
  return;
}

/*--------------------------------------------------------------------------*\
 | chessclock_setup
 |    initializes the clocks and settings for the game 
\*--------------------------------------------------------------------------*/
void chessclock_setup(uint32_t t) {
  
  // initialize player two's clock
  timestr_setch(1);
  app_timestr_init(t);
  app_timestr_print(LINE2);

  timestr_setch(0);
  app_timestr_init(t);
  app_timestr_print(LINE1);
}

/*==========================================================================*\
 | main: 
\*==========================================================================*/
void chessclock_main() {

  // start of play 
  chessclock_setup(MINUTES(3) + SECONDS(31));
  app_bell_start(CHIME_S);
  while(1) {
    if (timing_modern) {
      chessclock_modern();
    }
    else {
      chessclock_traditional();
    }

    // wait for alarm off
    app_bell_start(ALARM_2);
    while (app_bell_read()) {
      app_mcu_sleep();
    }
    app_bell_start(ALARM_2);
    while (app_bell_read()) {
      app_mcu_sleep();
    }

    // wait for new game
    while (!game_active) {
      app_mcu_sleep();
    }
    
  }
  // never return, else error
  return;
}
