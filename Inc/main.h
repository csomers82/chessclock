/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/
#define GLCD_PER 1000
#define GLCD_PRE 20
#define GLCD_DUTY 500
#define DB_PRE 200 
#define DB_PER 10000

#define E_Pin GPIO_PIN_0
#define E_GPIO_Port GPIOA
#define RW_Pin GPIO_PIN_1
#define RW_GPIO_Port GPIOA
#define LED__Pin GPIO_PIN_2
#define LED__GPIO_Port GPIOA
#define RS_Pin GPIO_PIN_4
#define RS_GPIO_Port GPIOA
#define SHC_595_Pin GPIO_PIN_5
#define SHC_595_GPIO_Port GPIOA
#define STC_595_Pin GPIO_PIN_6
#define STC_595_GPIO_Port GPIOA
#define SDI_595_Pin GPIO_PIN_7
#define SDI_595_GPIO_Port GPIOA
#define MEM_NHOLD_Pin GPIO_PIN_1
#define MEM_NHOLD_GPIO_Port GPIOB
#define MEM_NWP_Pin GPIO_PIN_2
#define MEM_NWP_GPIO_Port GPIOB
#define BTNA_Pin GPIO_PIN_10
#define BTNA_GPIO_Port GPIOB
#define BTNA_EXTI_IRQn EXTI4_15_IRQn
#define BTNB_Pin GPIO_PIN_11
#define BTNB_GPIO_Port GPIOB
#define BTNB_EXTI_IRQn EXTI4_15_IRQn
#define BUZZ_Pin GPIO_PIN_9
#define BUZZ_GPIO_Port GPIOA
#define TEST_Pin GPIO_PIN_12
#define TEST_GPIO_Port GPIOA
#define TGLA_Pin GPIO_PIN_7
#define TGLA_GPIO_Port GPIOB
#define TGLA_EXTI_IRQn EXTI4_15_IRQn
#define TGLB_Pin GPIO_PIN_9
#define TGLB_GPIO_Port GPIOB
#define TGLB_EXTI_IRQn EXTI4_15_IRQn

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */
#define BONUS_GPIO_Port TEST_GPIO_Port
#define BONUS_Pin TEST_Pin
/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
