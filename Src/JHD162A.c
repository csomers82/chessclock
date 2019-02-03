//==============================================================================
//
//  filename: JHD162A.c
//   summary: A manually cleaned up version of example 16x2 LCD Drivers
//
//   created: Sun Jan 27 13:43:32 CST 2019
//    author: Clifton Somers, user: cliff
//   contact: purduecliffsomers@gmail.com
//
//==============================================================================
#include "main.h"
#include "basic.h"
#include "stm32f0xx_hal.h"
#include <inttypes.h>
#include "JHD162A.h"

/*****************************************************************************
 * External Variable Definitions
 ****************************************************************************/

/*****************************************************************************
 * Global Variable Declarations
 ****************************************************************************/

/*****************************************************************************
 * shiftout: Transmits the character x to external shift
 *           register using the SPI.  It should shift LSB first.
 *
 *           MISO = PA7
 *           SCK  = PA5
 *           RCLK = shift registers update-input input signal
 ****************************************************************************/
//void shiftout(char x){
//    HAL_GPIO_WritePin(STC_595_GPIO_Port, STC_595_Pin, GPIO_PIN_RESET);
//    // read something to see if transmit data register is empty
//    HAL_SPI_Transmit(&hspi1, &x, 1, 200); // write 1 character
//    // wait for at least 30 cycles for data to be written
//    spinwaiting(2);
//    HAL_GPIO_WritePin(STC_595_GPIO_Port, STC_595_Pin, GPIO_PIN_SET);
//    spinwaiting(1);
//    HAL_GPIO_WritePin(STC_595_GPIO_Port, STC_595_Pin, GPIO_PIN_RESET);
//}


/*****************************************************************************
 * lcdinit: the calls to initialize a 2X16 chardisp
 ****************************************************************************/
void lcdinit() {
  HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
  send_i(LCDON);
  HAL_Delay(100);
  send_i(TWOLINE);
  HAL_Delay(100);
  send_i(LCDCLR);
  HAL_Delay(100);
  HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
}

/*****************************************************************************
 * send_byte: writes character x to the LCD
 *    shift out character
 *    pulse LCD clock line low->high->low
 *    wait 2 ms for LCD to process data
 ****************************************************************************/
void send_byte(char x){
    shiftout(x);
    clear__cs(); 
    spinwaiting(3);
    assert_cs();
    spinwaiting(3);
    clear__cs(); 
    HAL_Delay(5);
}

/*****************************************************************************
 * send_i: Sends instruction byte x to LCD
 *    set the register select line low (instruction data)
 *    send byte of instruction
 ****************************************************************************/
void send_i(char x){
    clear__dc(); 
    spinwaiting(3);
    send_byte(x);  
}

/*****************************************************************************
 * chgline: Move LCD cursor to position x
 *    NOTE: Cursor positions are encoded in the LINE1/LINE2 variables
 ****************************************************************************/
void chgline(char x){
    send_i(CURMOV);
    send_i(x);
}

/*****************************************************************************
 * print_c: Print (single) character x on LCD
 *    set register select line high for character
 *    write character to LCD
 ****************************************************************************/

void print_c(char x){
    assert_dc();
    send_byte(x);  // write the character
}

/*****************************************************************************
 * pmsglcd: print character string str[] on LCD
 ****************************************************************************/
void lcdprint(char str[]){
    int i = 0;
    while (str[i] != '\0'){
        print_c(str[i++]);
    }
}
