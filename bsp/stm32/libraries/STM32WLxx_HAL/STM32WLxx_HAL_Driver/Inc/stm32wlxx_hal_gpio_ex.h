/**
  ******************************************************************************
  * @file    stm32wlxx_hal_gpio_ex.h
  * @author  MCD Application Team
  * @brief   Header file of GPIO HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#ifndef STM32WLxx_HAL_GPIO_EX_H
#define STM32WLxx_HAL_GPIO_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal_def.h"

/** @addtogroup STM32WLxx_HAL_Driver
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
#define GPIO_AF0_MCO                        ((uint8_t)0x00)  /*!< MCO Alternate Function mapping       */
#define GPIO_AF0_LSCO                       ((uint8_t)0x00)  /*!< LSCO Alternate Function mapping      */
#define GPIO_AF0_JTAG                       ((uint8_t)0x00)  /*!< JTAG Alternate Function mapping      */
#define GPIO_AF0_SWD                        ((uint8_t)0x00)  /*!< SWD Alternate Function mapping       */
#define GPIO_AF0_RTC                        ((uint8_t)0x00)  /*!< RCT_OUT Alternate Function mapping   */

/**
  * @brief   AF 1 selection
 */
#define GPIO_AF1_LPTIM1                     ((uint8_t)0x01)  /*!< LPTIM3 Alternate Function mapping    */
#define GPIO_AF1_TIM1                       ((uint8_t)0x01)  /*!< TIM1 Alternate Function mapping      */
#define GPIO_AF1_TIM2                       ((uint8_t)0x01)  /*!< TIM2 Alternate Function mapping      */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_TIM2                       ((uint8_t)0x02)  /*!< TIM2 Alternate Function mapping      */
#define GPIO_AF2_TIM1                       ((uint8_t)0x02)  /*!< TIM1 Alternate Function mapping      */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_SPI2                       ((uint8_t)0x03)  /*!< SPI2 Alternate Function mapping      */
#define GPIO_AF3_LPTIM3                     ((uint8_t)0x03)  /*!< LPTIM3 Alternate Function mapping    */
#define GPIO_AF3_TIM1                       ((uint8_t)0x03)  /*!< TIM1 Alternate Function mapping      */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_I2C1                       ((uint8_t)0x04)  /*!< I2C1 Alternate Function mapping      */
#define GPIO_AF4_I2C2                       ((uint8_t)0x04)  /*!< I2C1 Alternate Function mapping      */
#define GPIO_AF4_I2C3                       ((uint8_t)0x04)  /*!< I2C3 Alternate Function mapping      */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_SPI1                       ((uint8_t)0x05)  /*!< SPI1 Alternate Function mapping      */
#define GPIO_AF5_SPI2                       ((uint8_t)0x05)  /*!< SPI2 Alternate Function mapping      */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_RF_BUSY                    ((uint8_t)0x06)  /*!< RF_BUSY Alternate Function mapping   */

/**
  * @brief  AF 7 selection
  */
#define GPIO_AF7_USART1                     ((uint8_t)0x07) /*!< USART1 Alternate Function mapping     */
#define GPIO_AF7_USART2                     ((uint8_t)0x07) /*!< USART1 Alternate Function mapping     */

/**
  * @brief  AF 8 selection
  */
#define GPIO_AF8_LPUART1                    ((uint8_t)0x08) /*!< LPUART1 Alternate Function mapping    */
#define GPIO_AF8_IR                         ((uint8_t)0x08) /*!< IR Alternate Function mapping         */

/**
  * @brief  AF 12 selection
  */
#define GPIO_AF12_COMP1                     ((uint8_t)0x0C)  /*!< COMP1 Alternate Function mapping     */
#define GPIO_AF12_COMP2                     ((uint8_t)0x0C)  /*!< COMP2 Alternate Function mapping     */
#define GPIO_AF12_TIM1                      ((uint8_t)0x0C)  /*!< TIM1 Alternate Function mapping      */

/**
  * @brief  AF 13 selection
  */
#define GPIO_AF13_DEBUG_PWR                 ((uint8_t)0x0D) /*!< Debug PWR Alternate Function mapping       */
#define GPIO_AF13_DEBUG_RF                  ((uint8_t)0x0D) /*!< Debug RF Alternate Function mapping        */
#define GPIO_AF13_DEBUG_SUBGHZSPI           ((uint8_t)0x0D) /*!< Debug SUBGHZSPI Alternate Function mapping */

/**
  * @brief  AF 14 selection
  */
#define GPIO_AF14_LPTIM2                    ((uint8_t)0x0E) /*!< LPTIM2 Alternate Function mapping     */
#define GPIO_AF14_TIM2                      ((uint8_t)0x0E) /*!< TIM2 Alternate Function mapping       */
#define GPIO_AF14_TIM16                     ((uint8_t)0x0E) /*!< TIM16 Alternate Function mapping      */
#define GPIO_AF14_TIM17                     ((uint8_t)0x0E) /*!< TIM17 Alternate Function mapping      */

/**
  * @brief  AF 15 selection
  */

#define GPIO_AF15_EVENTOUT                  ((uint8_t)0x0F) /*!< EVENTOUT Alternate Function mapping   */

#define IS_GPIO_AF(AF)                      ((AF) <= (uint8_t)0x0F)


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

#define GPIO_GET_INDEX(__GPIOx__)           (((__GPIOx__) == (GPIOA))? 0uL :\
                                             ((__GPIOx__) == (GPIOB))? 1uL :\
                                             ((__GPIOx__) == (GPIOC))? 2uL : 7uL)

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

#endif /* STM32WLxx_HAL_GPIO_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
