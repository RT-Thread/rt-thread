/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_conf.h
* Author             : MCD Application Team
* Version            : V1.1.2
* Date               : 09/22/2008
* Description        : Library configuration file.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_CONF_H
#define __STM32F10x_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_type.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line below to compile the library in DEBUG mode, this will expanse
   the "assert_param" macro in the firmware library code (see "Exported macro"
   section below) */
/* #define DEBUG    1*/

/* Comment the line below to disable the specific peripheral inclusion */
/************************************* ADC ************************************/
#define _ADC
#define _ADC1

/************************************* BKP ************************************/
#define _BKP

/************************************* CAN ************************************/
#define _CAN

/************************************* CRC ************************************/
#define _CRC

/************************************* DAC ************************************/
#define _DAC

/************************************* DBGMCU *********************************/
#define _DBGMCU

/************************************* DMA ************************************/
#define _DMA
#define _DMA1_Channel1
#define _DMA1_Channel2
#define _DMA1_Channel3
#define _DMA1_Channel4
#define _DMA1_Channel5
#define _DMA1_Channel6
#define _DMA1_Channel7

/************************************* EXTI ***********************************/
#define _EXTI

/************************************* FLASH and Option Bytes *****************/
#define _FLASH
/* Uncomment the line below to enable FLASH program/erase/protections functions,
   otherwise only FLASH configuration (latency, prefetch, half cycle) functions
   are enabled */
/* #define _FLASH_PROG */

/************************************* GPIO ***********************************/
#define _GPIO
#define _GPIOA
#define _GPIOB
#define _GPIOC
#define _GPIOD
#define _GPIOE
#define _GPIOF
#define _GPIOG
#define _AFIO

/************************************* I2C ************************************/
#define _I2C
#define _I2C1
#define _I2C2

/************************************* IWDG ***********************************/
#define _IWDG

/************************************* NVIC ***********************************/
#define _NVIC

/************************************* PWR ************************************/
#define _PWR

/************************************* RCC ************************************/
#define _RCC

/************************************* RTC ************************************/
#define _RTC

/************************************* SPI ************************************/
#define _SPI
#define _SPI1
#define _SPI2

/************************************* SysTick ********************************/
#define _SysTick

/************************************* TIM ************************************/
#define _TIM
#define _TIM1
#define _TIM2
#define _TIM3
#define _TIM4

/************************************* USART **********************************/
#define _USART
#define _USART1
#define _USART2
#define _USART3

/************************************* WWDG ***********************************/
#define _WWDG

/* In the following line adjust the value of External High Speed oscillator (HSE)
   used in your application */
#define HSE_Value    ((u32)8000000) /* Value of the External oscillator in Hz*/

/* In the following line adjust the External High Speed oscillator (HSE) Startup
   Timeout value */
#define HSEStartUp_TimeOut    ((u16)0x0500) /* Time out for HSE start up */

/* Exported macro ------------------------------------------------------------*/
#ifdef  DEBUG
/*******************************************************************************
* Macro Name     : assert_param
* Description    : The assert_param macro is used for function's parameters check.
*                  It is used only if the library is compiled in DEBUG mode.
* Input          : - expr: If expr is false, it calls assert_failed function
*                    which reports the name of the source file and the source
*                    line number of the call that failed.
*                    If expr is true, it returns no value.
* Return         : None
*******************************************************************************/
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((u8 *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(u8* file, u32 line);
#else
  #define assert_param(expr) ((void)0)
#endif /* DEBUG */

#endif /* __STM32F10x_CONF_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
