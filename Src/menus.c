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

#define WIDTH           (16)
#define N_MENU_STRS     (31)
#define N_MENUS         (7)
#define PREGAME_SCREEN  (255)

/*--------------------------------------------------------------------------*\
 | External Variable Definitions
\*--------------------------------------------------------------------------*/
extern int        timing_modern;
extern int        timing_limit;
extern uint8_t    timing_add;

/*--------------------------------------------------------------------------*\
 | Internal "Data Segment"
\*--------------------------------------------------------------------------*/

char menu_str[WIDTH][N_MENU_STRS] = {
// ================,
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
}               

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
      menu_str[4][14] = (bell_on) ? '*': ' ';
      bell_on         = (bell_on) ?  0 :  1;
      return(1);
  }
}


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
      return(1);
  }
}

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
      return(2);
    case 10: // yel vs mag
      menu_str[10][14]  = '*';
      color_scheme      = YVM; 
      return(2);
    case 11: // wht, red@30s
      menu_str[11][14]  = '*';
      color_scheme      = WTR; 
      return(2);
    case 12: // back
      return(0);
  }
}

int menu_game_format () {
  switch ( menu_index ) { 
    case 16: // back     
    case 21: // back     
    case 25: // back     
    case 30: // back     
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
