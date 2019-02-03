//==============================================================================
//
//  filename: timestr.h
//   summary:
//
//   created: Thu Jan 31 21:52:16 CST 2019
//    author: Clifton Somers, user: cliff
//   contact: purduecliffsomers@gmail.com
//
//==============================================================================
#ifndef __TIMESTR_
#define __TIMESTR_

#include <inttypes.h>

/*--------------------------------------------------------------------------*\
 | Constant Definitions 
\*--------------------------------------------------------------------------*/
#define ASCII_0 (48)
#define ASCII_5 (54)
#define ASCII_9 (57)

#define TIMESTR_DIGS (5)
#define TIMESTR_CHANS (2)

/*--------------------------------------------------------------------------*\
 | timestr_setch: 
 |    Sets the timestr pointer to the indicated index 
 |    Channel numbers range from 0:TIMESTR_CHANS-1
\*--------------------------------------------------------------------------*/
void timestr_setch(uint8_t chidx);

/*--------------------------------------------------------------------------*\
 | timestr_add: 
 |    Adds the argument to the global character string 
 |    Assumption is that x is less than 100 
\*--------------------------------------------------------------------------*/
void timestr_add(uint8_t carry);

/*--------------------------------------------------------------------------*\
 | timestr_add: 
 |    Adds the argument to the global character string 
 |    Assumption is that x is less than 100 
\*--------------------------------------------------------------------------*/
void timestr_add(uint8_t carry);

/*--------------------------------------------------------------------------*\
 | timestr_sub: 
 |    Subtracts x from the global character string 
 |    Assumption is that x is less than 48 
\*--------------------------------------------------------------------------*/
void timestr_sub(uint8_t borrow);

/*--------------------------------------------------------------------------*\
 | timestr_add_xs: 
 |    Subtracts 10 from the global character string 
 |    Is a slight optimization (common case)
\*--------------------------------------------------------------------------*/
void timestr_add_xs();

/*--------------------------------------------------------------------------*\
 | timestr_dec_1s: 
 |    Subtracts 10 from the global character string 
 |    Is a slight optimization (common case)
\*--------------------------------------------------------------------------*/
void timestr_dec_1s();


#endif//__TIMESTR_
