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
#include "menus.h"
#include "basic.h"

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
extern int              scroll_index;
extern int              menu_index;
extern int              bell_on[4];
extern int              active_player;
extern int              button_flag[2];
extern int              toggle_player;
extern enum ColorScheme color_scheme;
extern int              game_active;

/*--------------------------------------------------------------------------*\
 | Internal "Data Segment"
\*--------------------------------------------------------------------------*/

char menu_str[N_MENU_STRS][N_MENU_CHARS+1] = {
//"0123456789abcdef" \0
  "main menu     ", 
  "select game   ", 
  "color scheme  ", 
  "sound menu    ", 

//"0123456789abcdef" \0
  "bullet chess  ", 
  "blitz chess   ", 
  "rapid chess   ", 
  "classic chess ", 

//"0123456789abcdef" \0
  "blu vs grn   *", 
  "yel vs mag    ", 
  "wht, 30s=red  ", 

//"0123456789abcdef" \0
  "30s +  1s     ", 
  " 1m +  0s     ", 
  " 2m +  1s     ", 

//"0123456789abcdef" \0
  " 3m +  0s     ", 
  " 3m +  2s     ", 
  " 5m +  0s     ", 
  " 5m +  2s     ", 

//"0123456789abcdef" \0
  "10m +  0s     ", 
  "10m + 10s     ", 
  "15m + 15s     ", 

//"0123456789abcdef" \0
  "20m +  0s     ", 
  "20m + 20s     ", 
  "30m +  0s     ", 
  "30m + 30s     ", 

//"0123456789abcdef" \0
  "menu sounds  T", 
  "toggle beep  T", 
  "30sec alarm  T", 
  "start/finish T",  

//"0123456789abcdef" \0
  "Toggle white up.",
  "[back] [begin]",

};

/*--------------------------------------------------------------------------*\
 | Menu Navigation Functions 
\*--------------------------------------------------------------------------*/
struct MenuBlock menu[9] = {
//{parent       , len, title         , start        , type    }
  {0            , 3-1, S_MAINMENU    , S_CHOOSEGAME , NAVIGATE},
  {B_MAINMENU   ,   4, S_CHOOSEGAME  , S_BULLETCHESS, NAVIGATE},
  {B_MAINMENU   ,   3, S_COLORSCHEME , S_BLUVSGRN   , COLOR   },
  {B_MAINMENU   ,   4, S_SOUNDMENU   , S_MENUSOUNDS , SOUND   },
  {B_CHOOSEGAME ,   3, S_BULLETCHESS , S_T30S_I01S  , GAMETYPE},
  {B_CHOOSEGAME ,   4, S_BLITZCHESS  , S_T03M_I00S  , GAMETYPE},
  {B_CHOOSEGAME ,   3, S_RAPIDCHESS  , S_T10M_I00S  , GAMETYPE},
  {B_CHOOSEGAME ,   4, S_CLASSICCHESS, S_T20M_I00S  , GAMETYPE},
  {B_CHOOSEGAME ,   1, S_PREGAMEHIGH , S_PREGAMELOW , 0       }
};

/*--------------------------------------------------------------------------*\
 | Menu Navigation Functions 
\*--------------------------------------------------------------------------*/
int menu_navigate(int mi, int si) {
  switch (mi) {
    case B_MAINMENU:
      // S_CHOOSEGAME,
      // S_COLORSCHEME,
      // S_MUTESOUNDS,
      switch (si) {
        case 0: menu_index = B_CHOOSEGAME; break; 
        case 1: menu_index = B_COLORSCHEME; break; 
        case 2: menu_index = B_SOUNDMENU; break; 
      }
      break;

    case B_CHOOSEGAME:
      // S_BULLETCHESS,
      // S_BLITZCHESS,
      // S_RAPIDCHESS,
      // S_CLASSICCHESS,
      switch (si) {
        case 0: menu_index = B_BULLETCHESS; break; 
        case 1: menu_index = B_BLITZCHESS; break; 
        case 2: menu_index = B_RAPIDCHESS; break; 
        case 3: menu_index = B_CLASSICCHESS; break; 
      }
      break;
  }
  scroll_index = 0;
  return(TRUE);
}


/*--------------------------------------------------------------------------*\
 | menu_color
\*--------------------------------------------------------------------------*/
int menu_color(int si) {
  switch ( si ) {
    case 0: // blu vs grn
    case 1: // yel vs mag
    case 2: // wht, red@30s
      menu_str[S_BLUVSGRN   ][13] = ' ';
      menu_str[S_YELVSMAG   ][13] = ' ';
      menu_str[S_WHTREDAT30S][13] = ' ';
  }
  switch ( si ) {
    case 0: // blu vs grn
      menu_str[S_BLUVSGRN   ][13] = '*';
      color_scheme                = BVG; 
      break;
    case 1: // yel vs mag
      menu_str[S_YELVSMAG   ][13] = '*';
      color_scheme                = YVM; 
      break;
    case 2: // wht, red@30s
      menu_str[S_WHTREDAT30S][13] = '*';
      color_scheme                = WTR; 
      break;
  }
  return(FALSE);
}

/*--------------------------------------------------------------------------*\
 | menu_sound
\*--------------------------------------------------------------------------*/
int menu_sound(int si) {
  int was = bell_on[si];
  switch ( si ) {
    case 0:// BELL_MENUSOUNDS,
    case 1:// BELL_PLAYERTOGGLE,
    case 2:// BELL_SECALARM,
    case 3:// BELL_STARTFINISH
      bell_on[si]                     = (was) ? FALSE : TRUE;
      menu_str[si + S_MENUSOUNDS][13] = (was) ? 'F' : 'T';  
      return(FALSE);
  }
  return(TRUE);
}
/*--------------------------------------------------------------------------*\
 | menu_game_format
\*--------------------------------------------------------------------------*/
int menu_game_format (int mi, int si) {
  // transform the scroll_index to the MenuStr index
  si += menu[mi].start; 
  switch (si) {
    case S_T30S_I01S:
      timing_limit = SECONDS(30);
      timing_add   = 1;
      break;      
    case S_T01M_I00S:
      timing_limit = MINUTES(1);
      timing_add   = 0;
      break;      
    case S_T02M_I01S:
      timing_limit = MINUTES(2);
      timing_add   = 1;
      break;      
    case S_T03M_I00S:
      timing_limit = MINUTES(3);
      timing_add   = 0;
      break;      
    case S_T03M_I02S:
      timing_limit = MINUTES(3);
      timing_add   = 2;
      break;      
    case S_T05M_I00S:
      timing_limit = MINUTES(5);
      timing_add   = 0;
      break;      
    case S_T05M_I02S:
      timing_limit = MINUTES(5);
      timing_add   = 2;
      break;      
    case S_T10M_I00S:
      timing_limit = MINUTES(10);
      timing_add   = 0;
      break;      
    case S_T10M_I10S:
      timing_limit = MINUTES(10);
      timing_add   = 10;
      break;      
    case S_T15M_I15S:
      timing_limit = MINUTES(15);
      timing_add   = 15;
      break;      
    case S_T20M_I00S:
      timing_limit = MINUTES(20);
      timing_add   = 0;
      break;      
    case S_T20M_I20S:
      timing_limit = MINUTES(20);
      timing_add   = 20;
      break;      
    case S_T30M_I00S:
      timing_limit = MINUTES(30);
      timing_add   = 0;
      break;      
    case S_T30M_I30S:
      timing_limit = MINUTES(30);
      timing_add   = 30;
      break;      
  }
  menu_index   = B_PREGAME; 
  scroll_index = 0;
  return(TRUE);
}

/*--------------------------------------------------------------------------*\
 | menu_draw
\*--------------------------------------------------------------------------*/
void menu_draw() {
  struct MenuBlock m = menu[menu_index];
  chgline(LINE1);
  lcdprint(menu_str[m.title]);
  print_c(' ');
  print_c(' ');

  chgline(LINE2);
  print_c(' ');
  print_c(' ');
  if (menu_index == B_MAINMENU) 
    lcdprint(menu_str[m.start + scroll_index]);
  else if (scroll_index < m.len) 
    lcdprint(menu_str[m.start + scroll_index]);
  else
    lcdprint("back -^       ");
  return;
}

/*--------------------------------------------------------------------------*\
 | menu_input
\*--------------------------------------------------------------------------*/
int menu_input() {
  int is_event = FALSE;

  if (menu_index != B_PREGAME) {
    // select button
    if (button_flag[0]) {
      // handle input
      button_flag[0]  = FALSE;
      is_event        = TRUE;
      menu_select();
    } 

    // toggle/rotate button 
    else if (button_flag[1]) {
      button_flag[1]  = FALSE;
      is_event        = TRUE;
      menu_rotate(&scroll_index, menu[menu_index].len);
    }

    // direction button
    else if (toggle_player) {
      toggle_player   = FALSE;
      active_player   = (1 - active_player);

      if(active_player == 1) 
        basic_devled_on();
      else if (active_player == 0)
        basic_devled_off();
    }
  }
  else { 
    // select button
    if (button_flag[0]) {
      // handle input
      button_flag[0]  = FALSE;
      is_event        = TRUE;
      game_active     = TRUE;
    } 

    // toggle/rotate button 
    else if (button_flag[1]) {
      button_flag[1]  = FALSE;
      is_event        = TRUE;
      menu_index      = menu[menu_index].parent;
      scroll_index    = 0;
    }

    // direction button
    //if (toggle_player)  do nothing.
    
  }
  return(is_event);
}

/*--------------------------------------------------------------------------*\
 | menu_select
 |    encapsules the selection logic
\*--------------------------------------------------------------------------*/
void menu_select() {
  struct MenuBlock m = menu[menu_index];
  int nav = FALSE;

  // handle navigation
  if ((menu_index != B_MAINMENU) && 
      (scroll_index == menu[menu_index].len)) {
    menu_index    = menu[menu_index].parent;
    scroll_index  = 0;
    nav           = TRUE;
  }
  else {
    switch (m.type) {
      case GAMETYPE: 
        nav = menu_game_format(menu_index, scroll_index); break;
      case COLOR: 
        nav = menu_color(scroll_index); break;
      case SOUND: 
        nav = menu_sound(scroll_index); break;
      case NAVIGATE: 
        nav = menu_navigate(menu_index, scroll_index); break;
    }
  }

  return;
}



/*--------------------------------------------------------------------------*\
 | menu_rotate
 |    encapsules the menu radix logic
\*--------------------------------------------------------------------------*/
void menu_rotate(int *si, int max) {

  // rotate forward
  if (active_player == 0) {
    *si += 1;

    // check roll over condition
    if (*si > max) {
      *si = 0;
    }
  }

  // rotate backward 
  else if (active_player == 1) {
    *si -= 1;

    // check roll over condition
    if (*si < 0) {
      *si = max; 
    }
  }
  return;
}
