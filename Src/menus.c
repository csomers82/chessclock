//==============================================================================
//
//  filename: Src/menus.c
//   summary: data for the menus
//
//   created: Mon Feb 25 16:14:19 CST 2019
//    author: Clifton Somers, user: cliff
//   contact: purduecliffsomers@gmail.com
//
//==============================================================================

#include "application.h"
#include "chessclock.h"

#define N_MENU_CHARS    (16)
#define N_MENU_STRS     (31)
#define N_MENUS         (8)
#define PREGAME_SCREEN  (255)

/*--------------------------------------------------------------------------*\
 | External Variable Definitions
\*--------------------------------------------------------------------------*/
extern int              timing_modern;
extern int              timing_limit;
extern uint8_t          timing_add;
extern int              menu_index;
extern int              menu_title;
extern int              menu_start;
extern int              menu_flag;
extern int              bell_on;
extern int              active_player;
extern int              button_flag[2];
extern int              toggle_player;
extern enum ColorScheme color_scheme;

/*--------------------------------------------------------------------------*\
 | Internal "Data Segment"
\*--------------------------------------------------------------------------*/

int  menu_len[N_MENUS] = {
  3,//main menu
  5,//select game
  4,//color scheme
  0,//mute sounds 
    // *item present so menu_title is an index*
  4,//bullet chess
  5,//blitz chess
  5,//rapid chess
  5 //classic chess
};

int  menu_parent[N_MENUS] = {
  0,//main menu (no parent)
  0,//select game
  0,//color scheme
  0,//mute sounds 
    // *item present so menu_title is an index*
  3,//bullet chess
  3,//blitz chess
  3,//rapid chess
  3 //classic chess
};

char menu_str[N_MENU_STRS][N_MENU_CHARS+1] = {
//"0123456789abcdef" \0
  "main menu       ", // 0
  " select game    ", // 1
  " color scheme   ", // 2
  " mute sounds    ", // 3
  "  bullet chess  ", // 4
  "  blitz chess   ", // 5
  "  rapid chess   ", // 6
  "  classic chess ", // 7
  "  back          ", // 8
  "  blu vs grn    ", // 9
  "  yel vs mag    ", // 10
  "  wht, red@30s  ", // 11
  "  back          ", // 12
  "   30s +  1s    ", // 13
  "    1m +  0s    ", // 14
  "    2m +  1s    ", // 15
  "   back         ", // 16
  "    3m +  0s    ", // 17
  "    3m +  2s    ", // 18
  "    5m +  0s    ", // 19
  "    5m +  2s    ", // 20
  "   back         ", // 21
  "   10m +  0s    ", // 22
  "   10m + 10s    ", // 23
  "   15m + 15s    ", // 24
  "   back         ", // 25
  "   20m +  0s    ", // 26
  "   20m + 20s    ", // 27
  "   30m +  0s    ", // 28 
  "   30m + 30s    ", // 29
  "   back         "  // 30
};

/*--------------------------------------------------------------------------*\
 | Menu Navigation Functions 
\*--------------------------------------------------------------------------*/

int menu_main() {
  switch ( menu_index ) {
    case 1:// select game
      return(4);
    case 2:// color scheme
      return(9);
    case 3:// mute sounds
      menu_str[3][14] = (bell_on) ? '*': ' ';
      bell_on         = (bell_on) ?  0 :  1;
      menu_flag       = TRUE;
  }
  return(menu_index);
}


/*--------------------------------------------------------------------------*\
 | menu_select_game
\*--------------------------------------------------------------------------*/
int menu_select_game() {
  switch ( menu_index ) {
    case 4: // bullet chess
      return(13);
    case 5: // blitz chess
      return(17);
    case 6: // rapid chess
      return(22);
    case 7: // classic chess
      return(26);
    case 8: // back
      menu_index = 0;
      return(1);
  }
  return(menu_index);
}

/*--------------------------------------------------------------------------*\
 | menu_color_scheme
\*--------------------------------------------------------------------------*/
int menu_color_scheme() {
  switch ( menu_index ) {
    case 9 : // blu vs grn
    case 10: // yel vs mag
    case 11: // wht, red@30s
      menu_str[ 9][14] = ' ';
      menu_str[10][14] = ' ';
      menu_str[11][14] = ' ';
  }
  switch ( menu_index ) {
    case 9 : // blu vs grn
      menu_str[ 9][14]  = '*';
      color_scheme      = BVG; 
      menu_flag         = TRUE;
      break;
    case 10: // yel vs mag
      menu_str[10][14]  = '*';
      color_scheme      = YVM; 
      menu_flag         = TRUE;
      break;
    case 11: // wht, red@30s
      menu_str[11][14]  = '*';
      color_scheme      = WTR; 
      menu_flag         = TRUE;
      break;
    case 12: // back
      menu_index = 0;
      return(1);
  }
  return(menu_index);
}

/*--------------------------------------------------------------------------*\
 | menu_game_format
\*--------------------------------------------------------------------------*/
int menu_game_format () {
  switch ( menu_index ) { 
    case 16: // back     
    case 21: // back     
    case 25: // back     
    case 30: // back     
      menu_index = 3;
      return(4);
  }
  switch ( menu_index ) {
    case 13: // 30s +  1s
      timing_limit = SECONDS(30); break; 
    case 14: //  1m +  0s 
      timing_limit = MINUTES(1); break; 
    case 15: //  2m +  1s 
      timing_limit = MINUTES(2); break; 
    case 17: //  3m +  0s 
    case 18: //  3m +  2s 
      timing_limit = MINUTES(3); break; 
    case 19: //  5m +  0s 
    case 20: //  5m +  2s 
      timing_limit = MINUTES(5); break; 
    case 22: // 10m +  0s
    case 23: // 10m + 10s
      timing_limit = MINUTES(10); break; 
    case 24: // 15m + 15s
      timing_limit = MINUTES(15); break; 
    case 26: // 20m +  0s
    case 27: // 20m + 20s
      timing_limit = MINUTES(20); break; 
    case 28: // 30m +  0s
    case 29: // 30m + 30s
      timing_limit = MINUTES(30); break; 
  }
  switch ( menu_index ) {
    case 14: //  1m +  0s 
    case 17: //  3m +  0s 
    case 19: //  5m +  0s 
    case 22: // 10m +  0s
    case 26: // 20m +  0s
    case 28: // 30m +  0s
    case 13: // 30s +  1s
      timing_modern = FALSE;
      timing_add    = SECONDS(0);
      return(PREGAME_SCREEN);
  }
  timing_modern = TRUE;

  switch ( menu_index ) {
    case 13: // 30s +  1s
    case 15: //  2m +  1s 
      timing_add = SECONDS(1); break;
    case 18: //  3m +  2s 
    case 20: //  5m +  2s 
      timing_add = SECONDS(2); break;
    case 23: // 10m + 10s
      timing_add = SECONDS(10); break;
    case 24: // 15m + 15s
      timing_add = SECONDS(15); break;
    case 27: // 20m + 20s
      timing_add = SECONDS(20); break;
    case 29: // 30m + 30s
      timing_add = SECONDS(30); break;
  }
  return(PREGAME_SCREEN);
}

/*--------------------------------------------------------------------------*\
 | menu_draw
\*--------------------------------------------------------------------------*/
void menu_draw(int title, int index) {
  chgline(LINE1);
  lcdprint(menu_str[title]);
  chgline(LINE2);
  lcdprint(menu_str[index]);
  return;
}

/*--------------------------------------------------------------------------*\
 | menu_input
\*--------------------------------------------------------------------------*/
int menu_input() {
  int is_event = FALSE;
  int start    = 0;

  // toggle/rotate button 
  if (button_flag[0]) {
    // handle input
    button_flag[0]  = FALSE;
    is_event        = TRUE;
    basic_devled_on();
    
    // handle navigation
    switch (menu_title) {
      case 7: //  classic chess 
      case 6: //  rapid chess   
      case 5: //  blitz chess   
      case 4: //  bullet chess  
        start = menu_game_format(); 
        break;

      case 2: // color scheme   
        start = menu_color_scheme(); 
        break;

      case 1: // select game    
        start = menu_select_game(); 
        break;

      case 0: //main menu       
      default:
        start = menu_main(); 
    }
    // new title = last selected menu item
    //menu_last  = menu_title;
    if (! menu_flag ) {
      menu_start = start;
      menu_title = menu_index;
      // new index = start of submenu
      menu_index = menu_start;
    }
    menu_flag = FALSE;
  } 

  // select button
  else if (button_flag[1]) {
    button_flag[1]  = FALSE;
    is_event        = TRUE;
    basic_devled_off();

    //-=-=-=-=-=-=-=-=-=-=
    // ROTATION LOGIC
    //-=-=-=-=-=-=-=-=-=-=
    if (active_player == 0) {
      // rotate forward
      menu_index += 1;

      // check roll over condition
      if (menu_index >= menu_start + menu_len[menu_title]) {
        menu_index = menu_start;
      }
    }
    else {
      // rotate backward 
      menu_index -= 1;

      // check roll over condition
      if (menu_index < menu_start) {
        menu_index = (menu_start + menu_len[menu_title] - 1);
      }
    }
  }

  // direction button
  else if (toggle_player) {
    active_player   = (1 - active_player);
  }
  
  return(is_event);
}
