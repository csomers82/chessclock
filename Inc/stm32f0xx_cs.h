//==============================================================================
//
//  filename: ../Inc/stm32f0xx_cs.h
//   summary:
//
//   created: Mon Feb 11 19:30:28 CST 2019
//    author: Clifton Somers, user: cliff
//   contact: purduecliffsomers@gmail.com
//
//==============================================================================
#ifndef ___STM32F0XX_CS_
#define ___STM32F0XX_CS_

#include <inttypes.h>
#include "main.h"
#include "stm32f0xx_hal.h"
#include "system_stm32f0xx.h"    /* STM32F0xx System Header */
#include "stm32f030x8.h"


uint32_t stm32f0_read_gpio (
    GPIO_TypeDef   *GPIOx
);

void stm32f0_write_gpio (
    GPIO_TypeDef   *GPIOx,
    uint32_t        out
);

#endif//___STM32F0XX_CS_
