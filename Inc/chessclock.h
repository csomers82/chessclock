//==============================================================================
//
//  filename: Inc/chessclock.h
//   summary:
//
//   created: Sat Feb  9 12:34:26 CST 2019
//    author: Clifton Somers, user: cliff
//   contact: purduecliffsomers@gmail.com
//
//==============================================================================
#ifndef __CHESSCLOCK_
#define __CHESSCLOCK_

//==============================================================================
//  Constants
//==============================================================================

#define GAMEOVER_TE   (0)
#define GAMEOVER_CM   (2)
#define GAMEOVER_RG   (4)
#define GAMEOVER_IM   (6)
#define GAMEOVER_SM   (8)
#define GAMEOVER_DA   (10)

//==============================================================================
//  Types 
//==============================================================================

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GameRes :  allows a case statement to 
 *            capture end of game result
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
enum GameRes {
  GAMEOVER_WTE = GAMEOVER_TE, GAMEOVER_BTE, // ~ Time Expired ~
  GAMEOVER_WCM = GAMEOVER_CM, GAMEOVER_BCM, // ~= Checkmate. =~
  GAMEOVER_WRG = GAMEOVER_RG, GAMEOVER_BRG, //   Resign Game: 
  GAMEOVER_WIM = GAMEOVER_IM, GAMEOVER_BIM, // = Illegal Move =
  GAMEOVER_WSM = GAMEOVER_SM, GAMEOVER_BSM, //    Stalement:   
  GAMEOVER_WDA = GAMEOVER_DA, GAMEOVER_BDA  // Offer Accepted: 
};

//==============================================================================
//  Macros 
//==============================================================================

#define SECONDS(t) ((uint32_t)(t) * (uint32_t)(10u))
#define MINUTES(t) ((uint32_t)(t) * (uint32_t)(1000u))

//==============================================================================
//  Functions
//==============================================================================

/*--------------------------------------------------------------------------*\
 | chessclock_menu
 |    handle menu navigation and input events until game setup 
\*--------------------------------------------------------------------------*/
void chessclock_menu(void);

/*--------------------------------------------------------------------------*\
 | chessclock_modern 
 |    time control is incremental 
 |    
 |    time update
 |    bell update
 |    toggling debounce
 |    toggle handling (w/ addition)
 |    gamestate update
\*--------------------------------------------------------------------------*/
void chessclock_modern(void);

/*--------------------------------------------------------------------------*\
 | chessclock_traditional 
 |    time never increases, linear burndown
 |    
 |    time update
 |    bell update
 |    toggling debounce
 |    toggle handling (w/o addition)
 |    gamestate update
\*--------------------------------------------------------------------------*/
void chessclock_traditional(void);

/*--------------------------------------------------------------------------*\
 | chessclock_setup
 |    initializes the clocks and setting for the game 
 |
 |    set clock p1, p2
 |    set white marker
\*--------------------------------------------------------------------------*/
void chessclock_setup(uint32_t);

/*--------------------------------------------------------------------------*\
 | chessclock_main
 |    a sub-main to subvert sloppy stmcubemx functionallity 
 |
 |    menu_subroutine, 
 |    game_subroutine, 
 |    end_of_game handling
\*--------------------------------------------------------------------------*/
void chessclock_main(void);

#endif//__CHESSCLOCK_
