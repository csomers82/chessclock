//==============================================================================
//
//  filename: swclock.c
//   summary: 
//
//   created: Thu Jan 31 19:52:27 CST 2019
//    author: Clifton Somers, user: cliff
//   contact: purduecliffsomers@gmail.com
//
//==============================================================================

#include <inttypes.h>
#include "timestr.h"

/*--------------------------------------------------------------------------*\
 | External Variable Definitions
\*--------------------------------------------------------------------------*/
//(none)

/*--------------------------------------------------------------------------*\
 | Global Variables Declarations 
\*--------------------------------------------------------------------------*/

uint8_t   timestrbank[TIMESTR_DIGS * TIMESTR_CHANS] = {0};
uint8_t * timestr;
uint8_t   timezeroflags[TIMESTR_CHANS] = {0};
uint8_t * timezf;
uint8_t   timefullflags[TIMESTR_CHANS] = {0};
uint8_t * timeff;

/*--------------------------------------------------------------------------*\
 | timestr_itot: 
 |    takes total tenths of seconds and encodes it into decimal 
 |    (so each digit would match the clock, (mm:ss:t)
\*--------------------------------------------------------------------------*/
int timestr_itot(int total) {
  int clockdisp;
  
  clockdisp = total % 10;// tenths do not affect min
  total     = total / 10;// lop off tenths, total in s
  
  clockdisp +=   10 * (total % 60);// seconds
  clockdisp += 1000 * (total / 60);// minutes

  return(clockdisp);
}
/*--------------------------------------------------------------------------*\
 | timestr_ttoi: 
 |    takes a human readable set of clock numbers (think decimal encoded time) 
 |    returns what those clock digits are as a total of tenth seconds
 |    (assumption is that clockdisp has 5 digits
 |        (including tenth seconds))
\*--------------------------------------------------------------------------*/
int timestr_ttoi(int clockdisp) {
  int total = 0;
  //no base change up till minutes, add straigth
  total += (clockdisp % 1000);
  clockdisp /= 1000;

  //with minutes, convert base to decimal
  total += (clockdisp * 600);

  return(total);
}

/*--------------------------------------------------------------------------*\
 | timestr_setch: 
 |    Sets the timestr pointer to the indicated index 
 |    Channel numbers range from 0:TIMESTR_CHANS-1
\*--------------------------------------------------------------------------*/
void timestr_setch(uint8_t chidx) {
  timestr = &timestrbank[TIMESTR_DIGS * chidx];
  timezf  = &timezeroflags[chidx];
  timeff  = &timefullflags[chidx];
}

/*--------------------------------------------------------------------------*\
 | timestr_add: 
 |    Adds the argument to the global character string 
 |    Assumption is that x is less than 100 
\*--------------------------------------------------------------------------*/
void timestr_add(uint8_t carry) {
  // qualify the addition
  if (*timeff) 
    return;

  // carry will always be nonzero
  *timezf = 0;

  // tents
  timestr[0] += carry;
  carry       = 0;
  while (timestr[0] > ASCII_9) {
    timestr[0]  -= 10;
    carry       += 1;
  }
  if(!carry)
    return;
  
  // seconds
  timestr[1] += carry;
  if (timestr[1] <= ASCII_9) 
    return;
  timestr[1]  -= 10;
  carry       = 1;
  
  // tenzicants
  timestr[2] += carry;
  if (timestr[2] <= ASCII_5) 
    return;
  timestr[2]  -= 10;

  // minutes 
  timestr[3] += carry;
  if (timestr[3] <= ASCII_9) 
    return;
  timestr[3]  -= 10;

  // tenzimutes 
  timestr[4] += carry;
  if (timestr[4] <= ASCII_9) 
    return;

  // cannot add any more!
  *timeff    = 1;
  timestr[0] = ASCII_9;
  timestr[1] = ASCII_9;
  timestr[2] = ASCII_5;
  timestr[3] = ASCII_9;
  timestr[4] = ASCII_9;
  return;
}

/*--------------------------------------------------------------------------*\
 | timestr_sub: 
 |    Subtracts x from the global character string 
 |    Assumption is that x is less than 48 
\*--------------------------------------------------------------------------*/
void timestr_sub(uint8_t borrow) {
  // qualify the subtraction
  if (*timezf) 
    return;

  // borrow will always be nonzero
  *timeff = 0;

  // tents
  timestr[0] -= borrow;
  borrow      = 0;
  while (timestr[0] < ASCII_0) {
    timestr[0]  += 10;
    borrow      += 1;
  }
  if(!borrow)
    return;
  
  // seconds
  timestr[1] -= borrow;
  if (timestr[1] >= ASCII_0)
    return;
  timestr[1] += 10;
  borrow      = 1;
  
  // tenzicants
  timestr[2] -= borrow;
  if (timestr[2] >= ASCII_0)
    return;
  timestr[2] += 6;

  // minutes 
  timestr[3] -= borrow;
  if (timestr[3] >= ASCII_0)
    return;
  timestr[3] += 10;

  // tenzimutes 
  timestr[4] -= borrow;
  if (timestr[4] >= ASCII_0)
    return;

  // cannot subtract any more!
  *timezf    = 1;
  timestr[0] = ASCII_0;
  timestr[1] = ASCII_0;
  timestr[2] = ASCII_0;
  timestr[3] = ASCII_0;
  timestr[4] = ASCII_0;
  return;
}

/*--------------------------------------------------------------------------*\
 | timestr_add_xs: 
 |    Subtracts 10 from the global character string 
 |    Is a slight optimization (common case)
\*--------------------------------------------------------------------------*/
void timestr_add_xs() {
  return;
}

/*--------------------------------------------------------------------------*\
 | timestr_dec_1s: 
 |    Subtracts 10 from the global character string 
 |    Is a slight optimization (common case)
\*--------------------------------------------------------------------------*/
void timestr_dec_1s() {
  return;
}


