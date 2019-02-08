#include "main.h"
#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_spi.h"
#include "basic.h"

extern SPI_HandleTypeDef hspi1;

char itoaBuffer[6] = {0};// for func: itoa_intobuffer
int   spi_busy = 1;


/*
***********************************************************************
  blink:
***********************************************************************
*/
void blink(uint16_t t) {  
    while(1) {
        HAL_Delay(t);
        HAL_GPIO_TogglePin(BONUS_GPIO_Port, BONUS_Pin);
    }
}
void wink(uint16_t t) {  
    HAL_Delay(t);
    HAL_GPIO_TogglePin(BONUS_GPIO_Port, BONUS_Pin);
    HAL_Delay(t);
    HAL_GPIO_TogglePin(BONUS_GPIO_Port, BONUS_Pin);   
}



/*
***********************************************************************
  spinwaiting: bogus processor wait
***********************************************************************
*/
void spinwaiting(char loops) {
	int i, j;
	for(i = 0; i < loops; ++i) {
		for(j = 0; j < 10; ++j) {}
	}
}

/*
***********************************************************************
|  shiftout: Transmits the character x to external shift
|            register using the SPI.  It should shift LSB first.
|
|            MISO = PA7
|            SCK  = PA5
|            RCLK = shift registers update-input input signal
***********************************************************************
*/
void shiftout(unsigned char x) {
#ifndef __USE_SPI1_ISR
    HAL_GPIO_WritePin(STC_595_GPIO_Port, STC_595_Pin, GPIO_PIN_RESET);
    // read something to see if transmit data register is empty
    HAL_SPI_Transmit(&hspi1, &x, 1, 200); // write 1 character
    // wait for at least 30 cycles for data to be written
    //HAL_Delay(1);
    spinwaiting(30);
    HAL_GPIO_WritePin(STC_595_GPIO_Port, STC_595_Pin, GPIO_PIN_SET);
    spinwaiting(3);
    HAL_GPIO_WritePin(STC_595_GPIO_Port, STC_595_Pin, GPIO_PIN_RESET);
#else
    HAL_GPIO_WritePin(STC_595_GPIO_Port, STC_595_Pin, GPIO_PIN_RESET);
    spi_busy = 1;
    HAL_SPI_Transmit_IT(&hspi1, &x, 1); // write 1 character
    // sleep processor until transmitted
    do {
        HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFE);
    } while(spi_busy);
    HAL_GPIO_WritePin(STC_595_GPIO_Port, STC_595_Pin, GPIO_PIN_SET);
    spinwaiting(3);
    HAL_GPIO_WritePin(STC_595_GPIO_Port, STC_595_Pin, GPIO_PIN_RESET);
#endif
}


/*
***********************************************************************
  itoa_intoBuffer: converts integer into string
***********************************************************************
*/
void itoa_intoBuffer(int32_t in) {
    int i, digit;
    char c;
    int cbuf = (in < 0)? -in: in;
    for(i = 0; i < 5; ++i) {
        digit = cbuf % 10;
        switch(digit) {
            case 0: c = '0'; break;
            case 1: c = '1'; break;
            case 2: c = '2'; break;
            case 3: c = '3'; break;
            case 4: c = '4'; break;
            case 5: c = '5'; break;
            case 6: c = '6'; break;
            case 7: c = '7'; break;
            case 8: c = '8'; break;
            case 9: c = '9'; break;
            default: c = 'X';
        }
        itoaBuffer[4-i] = c;
        cbuf = cbuf / 10;
    }
    for(i = 0; i < 4; ++i) {
        if(itoaBuffer[i] != '0')
            break;
        itoaBuffer[i] = ' ';
    }
    if(in < 0) {
        if(i > 0) itoaBuffer[i-1] = '-';
    }
    itoaBuffer[5] = '\0';

} 



