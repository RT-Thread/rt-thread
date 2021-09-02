/**
  ******************************************************************************
  * @file    stm32g4xx_hal_gpio_ex.h
  * @author  MCD Application Team
  * @brief   Header file of GPIO HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G4xx_HAL_GPIO_EX_H
#define STM32G4xx_HAL_GPIO_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal_def.h"

/** @addtogroup STM32G4xx_HAL_Driver
  * @{
  */

/** @defgroup GPIOEx GPIOEx
  * @brief GPIO Extended HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIOEx_Exported_Constants GPIOEx Exported Constants
  * @{
  */

/** @defgroup GPIOEx_Alternate_function_selection GPIOEx Alternate function selection
  * @{
  */

/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)  /* RTC_50Hz Alternate Function mapping                       */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping                          */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_TIM2          ((uint8_t)0x01)  /* TIM2 Alternate Function mapping   */
#if defined(TIM5)
#define GPIO_AF1_TIM5          ((uint8_t)0x01)  /* TIM5 Alternate Function mapping   */
#endif /* TIM5 */
#define GPIO_AF1_TIM16         ((uint8_t)0x01)  /* TIM16 Alternate Function mapping  */
#define GPIO_AF1_TIM17         ((uint8_t)0x01)  /* TIM17 Alternate Function mapping  */
#define GPIO_AF1_TIM17_COMP1   ((uint8_t)0x01)  /* TIM17/COMP1 Break in Alternate Function mapping  */
#define GPIO_AF1_TIM15         ((uint8_t)0x01)  /* TIM15 Alternate Function mapping  */
#define GPIO_AF1_LPTIM1        ((uint8_t)0x01)  /* LPTIM1 Alternate Function mapping */
#define GPIO_AF1_IR            ((uint8_t)0x01)  /* IR Alternate Function mapping     */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_TIM1          ((uint8_t)0x02)  /* TIM1 Alternate Function mapping  */
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /* TIM2 Alternate Function mapping  */
#define GPIO_AF2_TIM3          ((uint8_t)0x02)  /* TIM3 Alternate Function mapping  */
#define GPIO_AF2_TIM4          ((uint8_t)0x02)  /* TIM4 Alternate Function mapping  */
#if defined(TIM5)
#define GPIO_AF2_TIM5          ((uint8_t)0x02)  /* TIM5 Alternate Function mapping  */
#endif /* TIM5 */
#define GPIO_AF2_TIM8          ((uint8_t)0x02)  /* TIM8 Alternate Function mapping  */
#define GPIO_AF2_TIM15         ((uint8_t)0x02)  /* TIM15 Alternate Function mapping */
#define GPIO_AF2_TIM16         ((uint8_t)0x02)  /* TIM16 Alternate Function mapping */
#if defined(TIM20)
#define GPIO_AF2_TIM20         ((uint8_t)0x02)  /* TIM20 Alternate Function mapping */
#endif /* TIM20 */
#define GPIO_AF2_TIM1_COMP1    ((uint8_t)0x02)  /* TIM1/COMP1 Break in Alternate Function mapping   */
#define GPIO_AF2_TIM15_COMP1   ((uint8_t)0x02)  /* TIM15/COMP1 Break in Alternate Function mapping  */
#define GPIO_AF2_TIM16_COMP1   ((uint8_t)0x02)  /* TIM16/COMP1 Break in Alternate Function mapping  */
#if defined(TIM20)
#define GPIO_AF2_TIM20_COMP1   ((uint8_t)0x02)  /* TIM20/COMP1 Break in Alternate Function mapping  */
#define GPIO_AF2_TIM20_COMP2   ((uint8_t)0x02)  /* TIM20/COMP2 Break in Alternate Function mapping  */
#endif /* TIM20 */
#define GPIO_AF2_I2C3          ((uint8_t)0x02)  /* I2C3 Alternate Function mapping  */
#define GPIO_AF2_COMP1         ((uint8_t)0x02)  /* COMP1 Alternate Function mapping */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_TIM15         ((uint8_t)0x03)  /* TIM15 Alternate Function mapping   */
#if defined(TIM20)
#define GPIO_AF3_TIM20         ((uint8_t)0x03)  /* TIM20 Alternate Function mapping   */
#endif /* TIM20 */
#define GPIO_AF3_UCPD1         ((uint8_t)0x03)  /* UCPD1 Alternate Function mapping   */
#define GPIO_AF3_I2C3          ((uint8_t)0x03)  /* I2C3 Alternate Function mapping    */
#if defined(I2C4)
#define GPIO_AF3_I2C4          ((uint8_t)0x03)  /* I2C4 Alternate Function mapping    */
#endif /* I2C4 */
#if defined(HRTIM1)
#define GPIO_AF3_HRTIM1        ((uint8_t)0x03)  /* HRTIM1 Alternate Function mapping  */
#endif /* HRTIM1 */
#if defined(QUADSPI)
#define GPIO_AF3_QUADSPI       ((uint8_t)0x03)  /* QUADSPI Alternate Function mapping */
#endif /* QUADSPI */
#define GPIO_AF3_TIM8          ((uint8_t)0x03)  /* TIM8 Alternate Function mapping    */
#define GPIO_AF3_SAI1          ((uint8_t)0x03)  /* SAI1 Alternate Function mapping  */
#define GPIO_AF3_COMP3         ((uint8_t)0x03)  /* COMP3 Alternate Function mapping */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_TIM1          ((uint8_t)0x04)  /* TIM1 Alternate Function mapping    */
#define GPIO_AF4_TIM8          ((uint8_t)0x04)  /* TIM8 Alternate Function mapping    */
#define GPIO_AF4_TIM16         ((uint8_t)0x04)  /* TIM16 Alternate Function mapping   */
#define GPIO_AF4_TIM17         ((uint8_t)0x04)  /* TIM17 Alternate Function mapping   */
#define GPIO_AF4_TIM8_COMP1    ((uint8_t)0x04)  /* TIM8/COMP1 Break in Alternate Function mapping  */
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping    */
#define GPIO_AF4_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping    */
#define GPIO_AF4_I2C3          ((uint8_t)0x04)  /* I2C3 Alternate Function mapping    */
#if defined(I2C4)
#define GPIO_AF4_I2C4          ((uint8_t)0x04)  /* I2C4 Alternate Function mapping    */
#endif /* I2C4 */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1 Alternate Function mapping       */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2 Alternate Function mapping       */
#if defined(SPI4)
#define GPIO_AF5_SPI4          ((uint8_t)0x05)  /* SPI4 Alternate Function mapping       */
#endif /* SPI4 */
#define GPIO_AF5_IR            ((uint8_t)0x05)  /* IR Alternate Function mapping         */
#define GPIO_AF5_TIM8          ((uint8_t)0x05)  /* TIM8 Alternate Function mapping       */
#define GPIO_AF5_TIM8_COMP1    ((uint8_t)0x05)  /* TIM8/COMP1 Break in Alternate Function mapping  */
#define GPIO_AF5_UART4         ((uint8_t)0x05)  /* UART4 Alternate Function mapping      */
#if defined(UART5)
#define GPIO_AF5_UART5         ((uint8_t)0x05)  /* UART5 Alternate Function mapping      */
#endif /* UART5 */
#define GPIO_AF5_I2S2ext       ((uint8_t)0x05)  /* I2S2ext_SD Alternate Function mapping */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_SPI2          ((uint8_t)0x06)  /* SPI2 Alternate Function mapping       */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /* SPI3 Alternate Function mapping       */
#define GPIO_AF6_TIM1          ((uint8_t)0x06)  /* TIM1 Alternate Function mapping       */
#if defined(TIM5)
#define GPIO_AF6_TIM5          ((uint8_t)0x06)  /* TIM5 Alternate Function mapping       */
#endif /* TIM5 */
#define GPIO_AF6_TIM8          ((uint8_t)0x06)  /* TIM8 Alternate Function mapping       */
#if defined(TIM20)
#define GPIO_AF6_TIM20         ((uint8_t)0x06)  /* TIM20 Alternate Function mapping      */
#endif /* TIM20 */
#define GPIO_AF6_TIM1_COMP1    ((uint8_t)0x06)  /* TIM1/COMP1 Break in Alternate Function mapping  */
#define GPIO_AF6_TIM1_COMP2    ((uint8_t)0x06)  /* TIM1/COMP2 Break in Alternate Function mapping  */
#define GPIO_AF6_TIM8_COMP2    ((uint8_t)0x06)  /* TIM8/COMP2 Break in Alternate Function mapping  */
#define GPIO_AF6_IR            ((uint8_t)0x06)  /* IR Alternate Function mapping         */
#define GPIO_AF6_I2S3ext       ((uint8_t)0x06)  /* I2S3ext_SD Alternate Function mapping */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping  */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping  */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping  */
#if defined(COMP5)
#define GPIO_AF7_COMP5         ((uint8_t)0x07)  /* COMP5 Alternate Function mapping   */
#endif /* COMP5 */
#if defined(COMP6)
#define GPIO_AF7_COMP6         ((uint8_t)0x07)  /* COMP6 Alternate Function mapping   */
#endif /* COMP6 */
#if defined(COMP7)
#define GPIO_AF7_COMP7         ((uint8_t)0x07)  /* COMP7 Alternate Function mapping   */
#endif /* COMP7 */

/**
  * @brief   AF 8 selection
  */
#define GPIO_AF8_COMP1         ((uint8_t)0x08)  /* COMP1 Alternate Function mapping   */
#define GPIO_AF8_COMP2         ((uint8_t)0x08)  /* COMP2 Alternate Function mapping   */
#define GPIO_AF8_COMP3         ((uint8_t)0x08)  /* COMP3 Alternate Function mapping   */
#define GPIO_AF8_COMP4         ((uint8_t)0x08)  /* COMP4 Alternate Function mapping   */
#if defined(COMP5)
#define GPIO_AF8_COMP5         ((uint8_t)0x08)  /* COMP5 Alternate Function mapping   */
#endif /* COMP5 */
#if defined(COMP6)
#define GPIO_AF8_COMP6         ((uint8_t)0x08)  /* COMP6 Alternate Function mapping   */
#endif /* COMP6 */
#if defined(COMP7)
#define GPIO_AF8_COMP7         ((uint8_t)0x08)  /* COMP7 Alternate Function mapping   */
#endif /* COMP7 */
#define GPIO_AF8_I2C3          ((uint8_t)0x08)  /* I2C3 Alternate Function mapping    */
#if defined(I2C4)
#define GPIO_AF8_I2C4          ((uint8_t)0x08)  /* I2C4 Alternate Function mapping    */
#endif /* I2C4 */
#define GPIO_AF8_LPUART1       ((uint8_t)0x08)  /* LPUART1 Alternate Function mapping */
#define GPIO_AF8_UART4         ((uint8_t)0x08)  /* UART4 Alternate Function mapping   */
#if defined(UART5)
#define GPIO_AF8_UART5         ((uint8_t)0x08)  /* UART5 Alternate Function mapping   */
#endif /* UART5 */

/**
  * @brief   AF 9 selection
  */
#define GPIO_AF9_TIM1          ((uint8_t)0x09)  /* TIM1 Alternate Function mapping    */
#define GPIO_AF9_TIM8          ((uint8_t)0x09)  /* TIM8 Alternate Function mapping    */
#define GPIO_AF9_TIM15         ((uint8_t)0x09)  /* TIM15 Alternate Function mapping   */
#define GPIO_AF9_TIM1_COMP1    ((uint8_t)0x09)  /* TIM1/COMP1 Break in Alternate Function mapping   */
#define GPIO_AF9_TIM8_COMP1    ((uint8_t)0x09)  /* TIM8/COMP1 Break in Alternate Function mapping   */
#define GPIO_AF9_TIM15_COMP1   ((uint8_t)0x09)  /* TIM15/COMP1 Break in Alternate Function mapping  */
#define GPIO_AF9_FDCAN1        ((uint8_t)0x09)  /* FDCAN1 Alternate Function mapping  */
#if defined(FDCAN2)
#define GPIO_AF9_FDCAN2        ((uint8_t)0x09)  /* FDCAN2 Alternate Function mapping  */
#endif /* FDCAN2 */

/**
  * @brief   AF 10 selection
  */
#define GPIO_AF10_TIM2         ((uint8_t)0x0A)  /* TIM2 Alternate Function mapping    */
#define GPIO_AF10_TIM3         ((uint8_t)0x0A)  /* TIM3 Alternate Function mapping    */
#define GPIO_AF10_TIM4         ((uint8_t)0x0A)  /* TIM4 Alternate Function mapping    */
#define GPIO_AF10_TIM8         ((uint8_t)0x0A)  /* TIM8 Alternate Function mapping    */
#define GPIO_AF10_TIM17        ((uint8_t)0x0A)  /* TIM17 Alternate Function mapping   */
#define GPIO_AF10_TIM8_COMP2   ((uint8_t)0x0A)  /* TIM8/COMP2 Break in Alternate Function mapping    */
#define GPIO_AF10_TIM17_COMP1  ((uint8_t)0x0A)  /* TIM17/COMP1 Break in Alternate Function mapping   */
#if defined(QUADSPI)
#define GPIO_AF10_QUADSPI      ((uint8_t)0x0A)  /* OctoSPI Manager Port 1 Alternate Function mapping */
#endif /* QUADSPI */

/**
  * @brief   AF 11 selection
  */
#define GPIO_AF11_FDCAN1       ((uint8_t)0x0B)  /* FDCAN1 Alternate Function mapping  */
#if defined(FDCAN3)
#define GPIO_AF11_FDCAN3       ((uint8_t)0x0B)  /* FDCAN3 Alternate Function mapping  */
#endif /* FDCAN3 */
#define GPIO_AF11_TIM1         ((uint8_t)0x0B)  /* TIM1 Alternate Function mapping    */
#define GPIO_AF11_TIM8         ((uint8_t)0x0B)  /* TIM8 Alternate Function mapping    */
#define GPIO_AF11_TIM8_COMP1   ((uint8_t)0x0B)  /* TIM8/COMP1 Break in Alternate Function mapping  */
#define GPIO_AF11_LPTIM1       ((uint8_t)0x0B)  /* LPTIM1 Alternate Function mapping  */

/**
  * @brief   AF 12 selection
  */
#define GPIO_AF12_LPUART1      ((uint8_t)0x0C)  /* LPUART1 Alternate Function mapping */
#define GPIO_AF12_TIM1         ((uint8_t)0x0C)  /* TIM1 Alternate Function mapping    */
#define GPIO_AF12_TIM1_COMP1   ((uint8_t)0x0C)  /* TIM1/COMP1 Break in Alternate Function mapping  */
#define GPIO_AF12_TIM1_COMP2   ((uint8_t)0x0C)  /* TIM1/COMP2 Break in Alternate Function mapping  */
#if defined(HRTIM1)
#define GPIO_AF12_HRTIM1       ((uint8_t)0x0C)  /* HRTIM1 Alternate Function mapping  */
#endif /* HRTIM1 */
#if defined(FMC_BANK1)
#define GPIO_AF12_FMC          ((uint8_t)0x0C)  /* FMC Alternate Function mapping     */
#endif /* FMC_BANK1 */
#define GPIO_AF12_SAI1         ((uint8_t)0x0C)  /* SAI1 Alternate Function mapping  */

/**
  * @brief   AF 13 selection
  */
#if defined(HRTIM1)
#define GPIO_AF13_HRTIM1       ((uint8_t)0x0D)  /* HRTIM1 Alternate Function mapping  */
#endif /* HRTIM1 */
#define GPIO_AF13_SAI1         ((uint8_t)0x0D)  /* SAI1 Alternate Function mapping  */

/**
  * @brief   AF 14 selection
  */
#define GPIO_AF14_TIM2         ((uint8_t)0x0E)  /* TIM2 Alternate Function mapping   */
#define GPIO_AF14_TIM15        ((uint8_t)0x0E)  /* TIM15 Alternate Function mapping   */
#define GPIO_AF14_UCPD1        ((uint8_t)0x0E)  /* UCPD1 Alternate Function mapping  */
#define GPIO_AF14_SAI1         ((uint8_t)0x0E)  /* SAI1 Alternate Function mapping  */
#define GPIO_AF14_UART4        ((uint8_t)0x0E)  /* UART4 Alternate Function mapping      */
#if defined(UART5)
#define GPIO_AF14_UART5        ((uint8_t)0x0E)  /* UART5 Alternate Function mapping      */
#endif /* UART5 */

/**
  * @brief   AF 15 selection
  */
#define GPIO_AF15_EVENTOUT     ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */

#define IS_GPIO_AF(AF)   ((AF) <= (uint8_t)0x0F)

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup GPIOEx_Exported_Macros GPIOEx Exported Macros
  * @{
  */

/** @defgroup GPIOEx_Get_Port_Index GPIOEx Get Port Index
  * @{
  */
#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0UL :\
                                      ((__GPIOx__) == (GPIOB))? 1UL :\
                                      ((__GPIOx__) == (GPIOC))? 2UL :\
                                      ((__GPIOx__) == (GPIOD))? 3UL :\
                                      ((__GPIOx__) == (GPIOE))? 4UL :\
                                      ((__GPIOx__) == (GPIOF))? 5UL : 6UL)

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32G4xx_HAL_GPIO_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
