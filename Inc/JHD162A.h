//==============================================================================
//
//  filename: JHD162A.h
//   summary:
//
//   created: Sun Jan 27 13:47:27 CST 2019
//    author: Clifton Somers, user: cliff
//   contact: purduecliffsomers@gmail.com
//
//==============================================================================
#ifndef __JHD162A_
#define __JHD162A_

#include <inttypes.h>
#include "main.h"
#include "stm32f0xx_hal.h"

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*\
 * Function Prototypes
\*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* basic debug lcd function */
//void shiftout(char x);
void lcdwait();
void send_byte(char x);
void send_i(char x);
void chgline(char x);
void print_c(char x);
void lcdprint(char str[]);
void lcdinit();
void itoa_intoBuffer(int32_t in);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*\
 * Important Constants 
\*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#define CURMOV  0xFE
#define LCDON   0x0F
#define TWOLINE 0x38
#define LCDCLR  0x01
#define LINE1   0x80
#define LINE2   0xC0

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*\
 * Macros  
\*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#define assert_cs() (HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET))
#define assert_rw() (HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_SET))
#define assert_dc() (HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET))

#define clear__cs() (HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET))
#define clear__rw() (HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET))
#define clear__dc() (HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET))


#endif//__JHD162A_
