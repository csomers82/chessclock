//==============================================================================
//
//  filename: Inc/menus.h
//   summary:
//
//   created: Mon Feb 25 20:17:13 CST 2019
//    author: Clifton Somers, user: cliff
//   contact: purduecliffsomers@gmail.com
//
//==============================================================================
#ifndef __MENUS_
#define __MENUS_


/* -------------------------------------------------------------------------*\
 | menu constants 
\* -------------------------------------------------------------------------*/
#define N_MENU_CHARS    (16)
#define N_MENU_STRS     (51)
#define N_MENUS         (10)
#define PREGAME_SCREEN  (255)
#define BACK_STR        ("return -^     ")
#define __MENU_TEST__

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * enum MenuStr :  for identifying each menu
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
enum MenuStr {
  S_MAINMENU,
  S_CHOOSEGAME,
  S_COLORSCHEME,
  S_SOUNDMENU,
  S_BULLETCHESS,
  S_BLITZCHESS,
  S_RAPIDCHESS,
  S_CLASSICCHESS,
  S_BLUVSGRN,
  S_YELVSMAG,
  S_WHTREDAT30S,
  S_T30S_I01S,
  S_T01M_I00S,
  S_T02M_I01S,
  S_T03M_I00S,
  S_T03M_I02S,
  S_T05M_I00S,
  S_T05M_I02S,
  S_T10M_I00S,
  S_T10M_I10S,
  S_T15M_I15S,
  S_T20M_I00S,
  S_T20M_I20S,
  S_T30M_I00S,
  S_T30M_I30S,
  S_MENUSOUNDS,
  S_PLAYERTOGGLE,
  S_SECALARM,
  S_STARTFINISH,
  S_PREGAMEINST,
  S_PREGAMEBTNS,
  S_ENDGAME_TE,
  S_ENDGAME_TE2,
  S_ENDGAME_CM,
  S_ENDGAME_CM2,
  S_ENDGAME_WR,
  S_ENDGAME_BR,
  S_ENDGAME_IM,
  S_ENDGAME_IM2,
  S_ENDGAME_SM,
  S_ENDGAME_SM2,
  S_ENDGAME_DA,
  S_RESULT_WINS,
  S_RESULT_BINS,
  S_RESULT_DRAW,
  S_RESULT_TITLE,
  S_RESULT_STR,
  S_RESULT_TIMES,
  S_RESULT_DUR,
  S_RESULT_TURNS
};
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Menublk :  for identifying each menu
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
enum MenuIdx {
  B_MAINMENU,
  B_CHOOSEGAME,
  B_COLORSCHEME,
  B_SOUNDMENU,
  B_BULLETCHESS,
  B_BLITZCHESS,
  B_RAPIDCHESS,
  B_CLASSICCHESS,
  B_PREGAME,
  B_GAMEOVER
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * MenuType : allows a case statement to 
 *            enrich menu functionality    
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
enum MenuType {
  NAVIGATE, // ordinary menu, no actions req
  COLOR,    // set color scheme variables
  SOUND,    // mute / play options
  GAMETYPE  // set time and increment
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * MenuBlock :  organizes the tree structure of
 *              to allow for a more scalable system   
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
struct MenuBlock {
  enum MenuIdx  parent;   // dest of back (mb[0] doesn't care, no back)
  int           len;      // number of menu options minus back
  enum MenuStr  title;    // index of title string
  enum MenuStr  start;    // index of first menu item
  enum MenuType type;     // switch for menu actions
};

/*--------------------------------------------------------------------------*\
 | menu functions
 |    ... are case statements that properly handle the selection of each 
 |    menu item. :: The main menu just navigates, while game format may 
 |    select the program values that describe gameplay.
 |
 |    they return the next menu index
\*--------------------------------------------------------------------------*/
int menu_navigate(int mi, int si);
int menu_game_format(int mi, int si);
int menu_sound(int si);
int menu_color(int si);

/*--------------------------------------------------------------------------*\
 | menu_draw
 |  reads the indices and outputs the correct lcd display info
\*--------------------------------------------------------------------------*/
void  menu_draw(void);

/*--------------------------------------------------------------------------*\
 | menu_input
 |    handles select, rotate, and other inputs during menu mode
\*--------------------------------------------------------------------------*/
int   menu_input(void);

/*--------------------------------------------------------------------------*\
 | menu_select
 |    encapsules the selection logic
 |    [reads enum MenuType and does action]
\*--------------------------------------------------------------------------*/
void menu_select(void);

/*--------------------------------------------------------------------------*\
 | menu_ro tate
 |    encapsules the menu radix logic
 |    [toggle switches determine up/down]
\*--------------------------------------------------------------------------*/
void menu_rotate(int *si, int max);

/*--------------------------------------------------------------------------*\
 | menu_endgame
 |   sets the appropriate strings for the "endgame menu"
 |
 |   set menu_index to B_GAMEOVER
 |   into S_RESULT_TITLE  copy matching from menu_str
 |   into S_RESULT_STR    copy matching from menu_str
 |   into S_RESULT_TIMES  write end timestr vals
 |   into S_RESULT_DUR    write 2*time_limit-playertimes
 |   into S_RESULT_TURNS  write game_turncnt
\*--------------------------------------------------------------------------*/
void menu_endgame(void);

#endif//__MENUS_

