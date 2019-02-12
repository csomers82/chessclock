//==============================================================================
//
//  filename: stm32f0xx_cs.c
//   summary: low level drivers for stm32f0
//
//   created: Mon Feb 11 19:23:24 CST 2019
//    author: Clifton Somers, user: cliff
//   contact: purduecliffsomers@gmail.com
//
//==============================================================================

#include "main.h"
#include "stm32f0xx_hal.h"
#include "stm32f0xx_cs.h"
#include <inttypes.h>
#include "system_stm32f0xx.h"    /* STM32F0xx System Header */
#include "stm32f030x8.h"


uint32_t stm32f0_read_gpio(GPIO_TypeDef * GPIOx) {
  return ((uint32_t) GPIOx->IDR);
}

void stm32f0_write_gpio(GPIO_TypeDef * GPIOx, uint32_t out) {
  GPIOx->ODR = out;
  return;
}
