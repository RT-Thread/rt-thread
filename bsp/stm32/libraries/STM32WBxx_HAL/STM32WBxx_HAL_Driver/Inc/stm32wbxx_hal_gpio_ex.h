/**
  ******************************************************************************
  * @file    stm32wbxx_hal_gpio_ex.h
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
#ifndef STM32WBxx_HAL_GPIO_EX_H
#define STM32WBxx_HAL_GPIO_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbxx_hal_def.h"

/** @addtogroup STM32WBxx_HAL_Driver
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


/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */

#if defined (STM32WB55xx) || defined (STM32WB5Mxx)
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO Alternate Function mapping                 */
#define GPIO_AF0_LSCO          ((uint8_t)0x00)  /*!< LSCO Alternate Function mapping                */
#define GPIO_AF0_JTMS_SWDIO    ((uint8_t)0x00)  /*!< JTMS-SWDIO Alternate Function mapping          */
#define GPIO_AF0_JTCK_SWCLK    ((uint8_t)0x00)  /*!< JTCK-SWCLK Alternate Function mapping          */
#define GPIO_AF0_JTDI          ((uint8_t)0x00)  /*!< JTDI Alternate Function mapping                */
#define GPIO_AF0_RTC_OUT       ((uint8_t)0x00)  /*!< RCT_OUT Alternate Function mapping             */
#define GPIO_AF0_JTD_TRACE     ((uint8_t)0x00)  /*!< JTDO-TRACESWO Alternate Function mapping       */
#define GPIO_AF0_NJTRST        ((uint8_t)0x00)  /*!< NJTRST Alternate Function mapping              */
#define GPIO_AF0_RTC_REFIN     ((uint8_t)0x00)  /*!< RTC_REFIN Alternate Function mapping           */
#define GPIO_AF0_TRACED0       ((uint8_t)0x00)  /*!< TRACED0 Alternate Function mapping             */
#define GPIO_AF0_TRACED1       ((uint8_t)0x00)  /*!< TRACED1 Alternate Function mapping             */
#define GPIO_AF0_TRACED2       ((uint8_t)0x00)  /*!< TRACED2 Alternate Function mapping             */
#define GPIO_AF0_TRACED3       ((uint8_t)0x00)  /*!< TRACED3 Alternate Function mapping             */
#define GPIO_AF0_TRIG_INOUT    ((uint8_t)0x00)  /*!< TRIG_INOUT Alternate Function mapping          */
#define GPIO_AF0_TRACECK       ((uint8_t)0x00)  /*!< TRACECK Alternate Function mapping             */
#define GPIO_AF0_SYS           ((uint8_t)0x00)  /*!< System Function mapping                        */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_TIM1           ((uint8_t)0x01)  /*!< TIM1 Alternate Function mapping           */
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /*!< TIM2 Alternate Function mapping            */
#define GPIO_AF1_LPTIM1         ((uint8_t)0x01)  /*!< LPTIM1 Alternate Function mapping          */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_TIM2           ((uint8_t)0x02)  /*!< TIM2 Alternate Function mapping           */
#define GPIO_AF2_TIM1           ((uint8_t)0x02)  /*!< TIM1 Alternate Function mapping         */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_SAI1           ((uint8_t)0x03)  /*!< SAI1_CK1 Alternate Function mapping           */
#define GPIO_AF3_SPI2           ((uint8_t)0x03)  /*!< SPI2 Alternate Function mapping          */
#define GPIO_AF3_TIM1           ((uint8_t)0x03)  /*!< TIM1 Alternate Function mapping          */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_I2C1           ((uint8_t)0x04)  /*!< I2C1 Alternate Function mapping         */
#define GPIO_AF4_I2C3           ((uint8_t)0x04)  /*!< I2C3 Alternate Function mapping          */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_SPI1           ((uint8_t)0x05)  /*!< SPI1 Alternate Function mapping        */
#define GPIO_AF5_SPI2           ((uint8_t)0x05)  /*!< SPI2 Alternate Function mapping        */
/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_MCO            ((uint8_t)0x06)  /*!< MCO Alternate Function mapping       */
#define GPIO_AF6_LSCO           ((uint8_t)0x06)  /*!< LSCO Alternate Function mapping      */
#define GPIO_AF6_RF_DTB0        ((uint8_t)0x06)  /*!< RF_DTB0 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB1        ((uint8_t)0x06)  /*!< RF_DTB1 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB2        ((uint8_t)0x06)  /*!< RF_DTB2 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB3        ((uint8_t)0x06)  /*!< RF_DTB3 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB4        ((uint8_t)0x06)  /*!< RF_DTB4 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB5        ((uint8_t)0x06)  /*!< RF_DTB5 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB6        ((uint8_t)0x06)  /*!< RF_DTB6 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB7        ((uint8_t)0x06)  /*!< RF_DTB7 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB8        ((uint8_t)0x06)  /*!< RF_DTB8 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB9        ((uint8_t)0x06)  /*!< RF_DTB9 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB10       ((uint8_t)0x06)  /*!< RF_DTB10 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB11       ((uint8_t)0x06)  /*!< RF_DTB11 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB12       ((uint8_t)0x06)  /*!< RF_DTB12 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB13       ((uint8_t)0x06)  /*!< RF_DTB13 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB14       ((uint8_t)0x06)  /*!< RF_DTB14 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB15       ((uint8_t)0x06)  /*!< RF_DTB15 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB16       ((uint8_t)0x06)  /*!< RF_DTB16 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB17       ((uint8_t)0x06)  /*!< RF_DTB17 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB18       ((uint8_t)0x06)  /*!< RF_DTB18 Alternate Function mapping  */
#define GPIO_AF6_RF_MISO        ((uint8_t)0x06)  /*!< RF_MISO Alternate Function mapping   */
#define GPIO_AF6_RF_MOSI        ((uint8_t)0x06)  /*!< RF_MOSI Alternate Function mapping   */
#define GPIO_AF6_RF_SCK         ((uint8_t)0x06)  /*!< RF_SCK Alternate Function mapping    */
#define GPIO_AF6_RF_NSS         ((uint8_t)0x06)  /*!< RF_NSS Alternate Function mapping    */
/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_USART1         ((uint8_t)0x07)  /*!< USART1 Alternate Function mapping     */

/**
  * @brief   AF 8 selection
  */
#define GPIO_AF8_LPUART1        ((uint8_t)0x08)  /*!< LPUART1 Alternate Function mapping      */
#define GPIO_AF8_IR             ((uint8_t)0x08)  /*!< IR Alternate Function mapping          */

/**
  * @brief   AF 9 selection
  */
#define GPIO_AF9_TSC           ((uint8_t)0x09)  /*!< TSC Alternate Function mapping      */

/**
  * @brief   AF 10 selection
  */
#define GPIO_AF10_QUADSPI       ((uint8_t)0x0a)  /*!< QUADSPI Alternate Function mapping  */
#define GPIO_AF10_USB           ((uint8_t)0x0a)  /*!< USB Alternate Function mapping      */

/**
   * @brief   AF 11 selection
   */
#define GPIO_AF11_LCD           ((uint8_t)0x0b)  /*!< LCD Alternate Function mapping      */

/**
  * @brief   AF 12 selection
  */
#define GPIO_AF12_COMP1         ((uint8_t)0x0c)  /*!< COMP1 Alternate Function mapping      */
#define GPIO_AF12_COMP2         ((uint8_t)0x0c)  /*!< COMP2 Alternate Function mapping      */
#define GPIO_AF12_TIM1          ((uint8_t)0x0c)  /*!< TIM1 Alternate Function mapping      */

/**
  * @brief   AF 13 selection
  */
#define GPIO_AF13_SAI1          ((uint8_t)0x0d)  /*!< SAI1 Alternate Function mapping      */

/**
  * @brief   AF 14 selection
  */
#define GPIO_AF14_TIM2          ((uint8_t)0x0e)  /*!< TIM2 Alternate Function mapping       */
#define GPIO_AF14_TIM16         ((uint8_t)0x0e)  /*!< TIM16 Alternate Function mapping      */
#define GPIO_AF14_TIM17         ((uint8_t)0x0e)  /*!< TIM17 Alternate Function mapping      */
#define GPIO_AF14_LPTIM2        ((uint8_t)0x0e)  /*!< LPTIM2 Alternate Function mapping     */


/**
  * @brief   AF 15 selection
  */
#define GPIO_AF15_EVENTOUT          ((uint8_t)0x0f)  /*!< EVENTOUT Alternate Function mapping      */

#define IS_GPIO_AF(AF)              ((AF) <= (uint8_t)0x0f)

#endif


#if defined (STM32WB50xx)
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO Alternate Function mapping                 */
#define GPIO_AF0_LSCO          ((uint8_t)0x00)  /*!< LSCO Alternate Function mapping                */
#define GPIO_AF0_JTMS_SWDIO    ((uint8_t)0x00)  /*!< JTMS-SWDIO Alternate Function mapping          */
#define GPIO_AF0_JTCK_SWCLK    ((uint8_t)0x00)  /*!< JTCK-SWCLK Alternate Function mapping          */
#define GPIO_AF0_JTDI          ((uint8_t)0x00)  /*!< JTDI Alternate Function mapping                */
#define GPIO_AF0_RTC_OUT       ((uint8_t)0x00)  /*!< RCT_OUT Alternate Function mapping             */
#define GPIO_AF0_JTD_TRACE     ((uint8_t)0x00)  /*!< JTDO-TRACESWO Alternate Function mapping       */
#define GPIO_AF0_NJTRST        ((uint8_t)0x00)  /*!< NJTRST Alternate Function mapping              */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_TIM1           ((uint8_t)0x01)  /*!< TIM1 Alternate Function mapping           */
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /*!< TIM2 Alternate Function mapping            */
#define GPIO_AF1_LPTIM1         ((uint8_t)0x01)  /*!< LPTIM1 Alternate Function mapping          */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_TIM1           ((uint8_t)0x02)  /*!< TIM1 Alternate Function mapping         */
#define GPIO_AF2_TIM2           ((uint8_t)0x02)  /*!< TIM2 Alternate Function mapping           */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_TIM1           ((uint8_t)0x03)  /*!< TIM1 Alternate Function mapping          */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_I2C1           ((uint8_t)0x04)  /*!< I2C1 Alternate Function mapping         */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_SPI1           ((uint8_t)0x05)  /*!< SPI1 Alternate Function mapping        */
/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_MCO            ((uint8_t)0x06)  /*!< MCO Alternate Function mapping       */
#define GPIO_AF6_LSCO           ((uint8_t)0x06)  /*!< LSCO Alternate Function mapping      */
#define GPIO_AF6_RF_DTB0        ((uint8_t)0x06)  /*!< RF_DTB0 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB1        ((uint8_t)0x06)  /*!< RF_DTB1 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB2        ((uint8_t)0x06)  /*!< RF_DTB2 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB3        ((uint8_t)0x06)  /*!< RF_DTB3 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB4        ((uint8_t)0x06)  /*!< RF_DTB4 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB5        ((uint8_t)0x06)  /*!< RF_DTB5 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB6        ((uint8_t)0x06)  /*!< RF_DTB6 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB7        ((uint8_t)0x06)  /*!< RF_DTB7 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB8        ((uint8_t)0x06)  /*!< RF_DTB8 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB9        ((uint8_t)0x06)  /*!< RF_DTB9 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB10       ((uint8_t)0x06)  /*!< RF_DTB10 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB11       ((uint8_t)0x06)  /*!< RF_DTB11 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB12       ((uint8_t)0x06)  /*!< RF_DTB12 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB13       ((uint8_t)0x06)  /*!< RF_DTB13 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB14       ((uint8_t)0x06)  /*!< RF_DTB14 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB15       ((uint8_t)0x06)  /*!< RF_DTB15 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB16       ((uint8_t)0x06)  /*!< RF_DTB16 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB17       ((uint8_t)0x06)  /*!< RF_DTB17 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB18       ((uint8_t)0x06)  /*!< RF_DTB18 Alternate Function mapping  */
#define GPIO_AF6_RF_MISO        ((uint8_t)0x06)  /*!< RF_MISO Alternate Function mapping   */
#define GPIO_AF6_RF_MOSI        ((uint8_t)0x06)  /*!< RF_MOSI Alternate Function mapping   */
#define GPIO_AF6_RF_SCK         ((uint8_t)0x06)  /*!< RF_SCK Alternate Function mapping    */
#define GPIO_AF6_RF_NSS         ((uint8_t)0x06)  /*!< RF_NSS Alternate Function mapping    */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_USART1         ((uint8_t)0x07)  /*!< USART1 Alternate Function mapping     */

/**
  * @brief   AF 8 selection
  */
#define GPIO_AF8_IR             ((uint8_t)0x08)  /*!< IR Alternate Function mapping          */

/**
  * @brief   AF 12 selection
  */
#define GPIO_AF12_TIM1          ((uint8_t)0x0c)  /*!< TIM1 Alternate Function mapping      */

/**
  * @brief   AF 14 selection
  */
#define GPIO_AF14_TIM2          ((uint8_t)0x0e)  /*!< TIM2 Alternate Function mapping       */
#define GPIO_AF14_TIM16         ((uint8_t)0x0e)  /*!< TIM16 Alternate Function mapping      */
#define GPIO_AF14_TIM17         ((uint8_t)0x0e)  /*!< TIM17 Alternate Function mapping      */
#define GPIO_AF14_LPTIM2        ((uint8_t)0x0e)  /*!< LPTIM2 Alternate Function mapping     */

/**
  * @brief   AF 15 selection
  */
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0f)  /*!< EVENTOUT Alternate Function mapping      */

#define IS_GPIO_AF(AF)          (((AF) <= (uint8_t)0x0F)\
                                 && ((AF) != (uint8_t)0x09) && ((AF) != (uint8_t)0x0A) && ((AF) != (uint8_t)0x0B) && ((AF) != (uint8_t)0x0D))

#endif


#if defined (STM32WB35xx)
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO Alternate Function mapping                 */
#define GPIO_AF0_LSCO          ((uint8_t)0x00)  /*!< LSCO Alternate Function mapping                */
#define GPIO_AF0_JTMS_SWDIO    ((uint8_t)0x00)  /*!< JTMS-SWDIO Alternate Function mapping          */
#define GPIO_AF0_JTCK_SWCLK    ((uint8_t)0x00)  /*!< JTCK-SWCLK Alternate Function mapping          */
#define GPIO_AF0_JTDI          ((uint8_t)0x00)  /*!< JTDI Alternate Function mapping                */
#define GPIO_AF0_RTC_OUT       ((uint8_t)0x00)  /*!< RCT_OUT Alternate Function mapping             */
#define GPIO_AF0_JTD_TRACE     ((uint8_t)0x00)  /*!< JTDO-TRACESWO Alternate Function mapping       */
#define GPIO_AF0_NJTRST        ((uint8_t)0x00)  /*!< NJTRST Alternate Function mapping              */
#define GPIO_AF0_TRACED0       ((uint8_t)0x00)  /*!< TRACED0 Alternate Function mapping             */
#define GPIO_AF0_TRACED1       ((uint8_t)0x00)  /*!< TRACED1 Alternate Function mapping             */
#define GPIO_AF0_TRACED2       ((uint8_t)0x00)  /*!< TRACED2 Alternate Function mapping             */
#define GPIO_AF0_TRACED3       ((uint8_t)0x00)  /*!< TRACED3 Alternate Function mapping             */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_TIM1           ((uint8_t)0x01)  /*!< TIM1 Alternate Function mapping       */
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /*!< TIM2 Alternate Function mapping       */
#define GPIO_AF1_LPTIM1         ((uint8_t)0x01)  /*!< LPTIM1 Alternate Function mapping     */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_TIM1           ((uint8_t)0x02)  /*!< TIM1 Alternate Function mapping       */
#define GPIO_AF2_TIM2           ((uint8_t)0x02)  /*!< TIM2 Alternate Function mapping       */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_SAI1           ((uint8_t)0x03)  /*!< SAI1_CK1 Alternate Function mapping   */
#define GPIO_AF3_TIM1           ((uint8_t)0x03)  /*!< TIM1 Alternate Function mapping       */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_I2C1           ((uint8_t)0x04)  /*!< I2C1 Alternate Function mapping       */
#define GPIO_AF4_I2C3           ((uint8_t)0x04)  /*!< I2C3 Alternate Function mapping       */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_SPI1           ((uint8_t)0x05)  /*!< SPI1 Alternate Function mapping       */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_MCO            ((uint8_t)0x06)  /*!< MCO Alternate Function mapping        */
#define GPIO_AF6_LSCO           ((uint8_t)0x06)  /*!< LSCO Alternate Function mapping       */
#define GPIO_AF6_RF_DTB0        ((uint8_t)0x06)  /*!< RF_DTB0 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB1        ((uint8_t)0x06)  /*!< RF_DTB1 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB2        ((uint8_t)0x06)  /*!< RF_DTB2 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB3        ((uint8_t)0x06)  /*!< RF_DTB3 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB4        ((uint8_t)0x06)  /*!< RF_DTB4 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB5        ((uint8_t)0x06)  /*!< RF_DTB5 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB6        ((uint8_t)0x06)  /*!< RF_DTB6 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB7        ((uint8_t)0x06)  /*!< RF_DTB7 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB8        ((uint8_t)0x06)  /*!< RF_DTB8 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB9        ((uint8_t)0x06)  /*!< RF_DTB9 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB10       ((uint8_t)0x06)  /*!< RF_DTB10 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB11       ((uint8_t)0x06)  /*!< RF_DTB11 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB12       ((uint8_t)0x06)  /*!< RF_DTB12 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB13       ((uint8_t)0x06)  /*!< RF_DTB13 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB14       ((uint8_t)0x06)  /*!< RF_DTB14 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB15       ((uint8_t)0x06)  /*!< RF_DTB15 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB16       ((uint8_t)0x06)  /*!< RF_DTB16 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB17       ((uint8_t)0x06)  /*!< RF_DTB17 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB18       ((uint8_t)0x06)  /*!< RF_DTB18 Alternate Function mapping   */
#define GPIO_AF6_RF_MISO        ((uint8_t)0x06)  /*!< RF_MISO Alternate Function mapping    */
#define GPIO_AF6_RF_MOSI        ((uint8_t)0x06)  /*!< RF_MOSI Alternate Function mapping    */
#define GPIO_AF6_RF_SCK         ((uint8_t)0x06)  /*!< RF_SCK Alternate Function mapping     */
#define GPIO_AF6_RF_NSS         ((uint8_t)0x06)  /*!< RF_NSS Alternate Function mapping     */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_USART1         ((uint8_t)0x07)  /*!< USART1 Alternate Function mapping     */

/**
  * @brief   AF 8 selection
  */
#define GPIO_AF8_IR             ((uint8_t)0x08)  /*!< IR Alternate Function mapping         */
#define GPIO_AF8_LPUART1        ((uint8_t)0x08)  /*!< LPUART1 Alternate Function mapping    */

/**
  * @brief   AF 10 selection
  */
#define GPIO_AF10_QUADSPI       ((uint8_t)0x0A)  /*!< QUADSPI Alternate Function mapping    */
#define GPIO_AF10_USB           ((uint8_t)0x0A)  /*!< USB Alternate Function mapping        */

/**
  * @brief   AF 12 selection
  */
#define GPIO_AF12_COMP1         ((uint8_t)0x0C)  /*!< COMP1 Alternate Function mapping      */
#define GPIO_AF12_COMP2         ((uint8_t)0x0C)  /*!< COMP2 Alternate Function mapping      */
#define GPIO_AF12_TIM1          ((uint8_t)0x0C)  /*!< TIM1 Alternate Function mapping       */

/**
  * @brief   AF 13 selection
  */
#define GPIO_AF13_SAI1          ((uint8_t)0x0d)  /*!< SAI1 Alternate Function mapping      */

/**
  * @brief   AF 14 selection
  */
#define GPIO_AF14_LPTIM2        ((uint8_t)0x0E)  /*!< LPTIM2 Alternate Function mapping     */
#define GPIO_AF14_TIM2          ((uint8_t)0x0E)  /*!< TIM2 Alternate Function mapping       */
#define GPIO_AF14_TIM16         ((uint8_t)0x0E)  /*!< TIM16 Alternate Function mapping      */
#define GPIO_AF14_TIM17         ((uint8_t)0x0E)  /*!< TIM17 Alternate Function mapping      */

/**
  * @brief   AF 15 selection
  */
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /*!< EVENTOUT Alternate Function mapping   */

#define IS_GPIO_AF(AF)          (((AF) <= (uint8_t)0x0F) && ((AF) != (uint8_t)0x0B) && ((AF) != (uint8_t)0x0D))

#endif

#if defined (STM32WB30xx)
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO Alternate Function mapping                 */
#define GPIO_AF0_LSCO          ((uint8_t)0x00)  /*!< LSCO Alternate Function mapping                */
#define GPIO_AF0_JTMS_SWDIO    ((uint8_t)0x00)  /*!< JTMS-SWDIO Alternate Function mapping          */
#define GPIO_AF0_JTCK_SWCLK    ((uint8_t)0x00)  /*!< JTCK-SWCLK Alternate Function mapping          */
#define GPIO_AF0_JTDI          ((uint8_t)0x00)  /*!< JTDI Alternate Function mapping                */
#define GPIO_AF0_RTC_OUT       ((uint8_t)0x00)  /*!< RCT_OUT Alternate Function mapping             */
#define GPIO_AF0_JTD_TRACE     ((uint8_t)0x00)  /*!< JTDO-TRACESWO Alternate Function mapping       */
#define GPIO_AF0_NJTRST        ((uint8_t)0x00)  /*!< NJTRST Alternate Function mapping              */
#define GPIO_AF0_TRACED0       ((uint8_t)0x00)  /*!< TRACED0 Alternate Function mapping             */
#define GPIO_AF0_TRACED1       ((uint8_t)0x00)  /*!< TRACED1 Alternate Function mapping             */
#define GPIO_AF0_TRACED2       ((uint8_t)0x00)  /*!< TRACED2 Alternate Function mapping             */
#define GPIO_AF0_TRACED3       ((uint8_t)0x00)  /*!< TRACED3 Alternate Function mapping             */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_TIM1           ((uint8_t)0x01)  /*!< TIM1 Alternate Function mapping       */
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /*!< TIM2 Alternate Function mapping       */
#define GPIO_AF1_LPTIM1         ((uint8_t)0x01)  /*!< LPTIM1 Alternate Function mapping     */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_TIM1           ((uint8_t)0x02)  /*!< TIM1 Alternate Function mapping       */
#define GPIO_AF2_TIM2           ((uint8_t)0x02)  /*!< TIM2 Alternate Function mapping       */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_TIM1           ((uint8_t)0x03)  /*!< TIM1 Alternate Function mapping       */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_I2C1           ((uint8_t)0x04)  /*!< I2C1 Alternate Function mapping       */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_SPI1           ((uint8_t)0x05)  /*!< SPI1 Alternate Function mapping       */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_MCO            ((uint8_t)0x06)  /*!< MCO Alternate Function mapping        */
#define GPIO_AF6_LSCO           ((uint8_t)0x06)  /*!< LSCO Alternate Function mapping       */
#define GPIO_AF6_RF_DTB0        ((uint8_t)0x06)  /*!< RF_DTB0 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB1        ((uint8_t)0x06)  /*!< RF_DTB1 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB2        ((uint8_t)0x06)  /*!< RF_DTB2 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB3        ((uint8_t)0x06)  /*!< RF_DTB3 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB4        ((uint8_t)0x06)  /*!< RF_DTB4 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB5        ((uint8_t)0x06)  /*!< RF_DTB5 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB6        ((uint8_t)0x06)  /*!< RF_DTB6 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB7        ((uint8_t)0x06)  /*!< RF_DTB7 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB8        ((uint8_t)0x06)  /*!< RF_DTB8 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB9        ((uint8_t)0x06)  /*!< RF_DTB9 Alternate Function mapping    */
#define GPIO_AF6_RF_DTB10       ((uint8_t)0x06)  /*!< RF_DTB10 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB11       ((uint8_t)0x06)  /*!< RF_DTB11 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB12       ((uint8_t)0x06)  /*!< RF_DTB12 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB13       ((uint8_t)0x06)  /*!< RF_DTB13 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB14       ((uint8_t)0x06)  /*!< RF_DTB14 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB15       ((uint8_t)0x06)  /*!< RF_DTB15 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB16       ((uint8_t)0x06)  /*!< RF_DTB16 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB17       ((uint8_t)0x06)  /*!< RF_DTB17 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB18       ((uint8_t)0x06)  /*!< RF_DTB18 Alternate Function mapping   */
#define GPIO_AF6_RF_MISO        ((uint8_t)0x06)  /*!< RF_MISO Alternate Function mapping    */
#define GPIO_AF6_RF_MOSI        ((uint8_t)0x06)  /*!< RF_MOSI Alternate Function mapping    */
#define GPIO_AF6_RF_SCK         ((uint8_t)0x06)  /*!< RF_SCK Alternate Function mapping     */
#define GPIO_AF6_RF_NSS         ((uint8_t)0x06)  /*!< RF_NSS Alternate Function mapping     */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_USART1         ((uint8_t)0x07)  /*!< USART1 Alternate Function mapping     */

/**
  * @brief   AF 8 selection
  */
#define GPIO_AF8_IR             ((uint8_t)0x08)  /*!< IR Alternate Function mapping         */

/**
  * @brief   AF 12 selection
  */
#define GPIO_AF12_TIM1          ((uint8_t)0x0C)  /*!< TIM1 Alternate Function mapping       */

/**
  * @brief   AF 14 selection
  */
#define GPIO_AF14_LPTIM2        ((uint8_t)0x0E)  /*!< LPTIM2 Alternate Function mapping     */
#define GPIO_AF14_TIM2          ((uint8_t)0x0E)  /*!< TIM2 Alternate Function mapping       */
#define GPIO_AF14_TIM16         ((uint8_t)0x0E)  /*!< TIM16 Alternate Function mapping      */
#define GPIO_AF14_TIM17         ((uint8_t)0x0E)  /*!< TIM17 Alternate Function mapping      */

/**
  * @brief   AF 15 selection
  */
#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)  /*!< EVENTOUT Alternate Function mapping   */

#define IS_GPIO_AF(AF)          (((AF) <= (uint8_t)0x0F)\
                                 && ((AF) != (uint8_t)0x0A) && ((AF) != (uint8_t)0x0B) && ((AF) != (uint8_t)0x0D))

#endif

#if defined (STM32WB15xx) || defined (STM32WB10xx)
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO Alternate Function mapping                 */
#define GPIO_AF0_LSCO          ((uint8_t)0x00)  /*!< LSCO Alternate Function mapping                */
#define GPIO_AF0_JTMS_SWDIO    ((uint8_t)0x00)  /*!< JTMS-SWDIO Alternate Function mapping          */
#define GPIO_AF0_JTCK_SWCLK    ((uint8_t)0x00)  /*!< JTCK-SWCLK Alternate Function mapping          */
#define GPIO_AF0_JTDI          ((uint8_t)0x00)  /*!< JTDI Alternate Function mapping                */
#define GPIO_AF0_RTC_OUT       ((uint8_t)0x00)  /*!< RCT_OUT Alternate Function mapping             */
#define GPIO_AF0_JTD_TRACE     ((uint8_t)0x00)  /*!< JTDO-TRACESWO Alternate Function mapping       */
#define GPIO_AF0_NJTRST        ((uint8_t)0x00)  /*!< NJTRST Alternate Function mapping              */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_TIM1           ((uint8_t)0x01)  /*!< TIM1 Alternate Function mapping           */
#define GPIO_AF1_TIM2           ((uint8_t)0x01)  /*!< TIM2 Alternate Function mapping            */
#define GPIO_AF1_LPTIM1         ((uint8_t)0x01)  /*!< LPTIM1 Alternate Function mapping          */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_TIM2           ((uint8_t)0x02)  /*!< TIM2 Alternate Function mapping           */
#define GPIO_AF2_TIM1           ((uint8_t)0x02)  /*!< TIM1 Alternate Function mapping         */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_TIM1           ((uint8_t)0x03)  /*!< TIM1 Alternate Function mapping          */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_I2C1           ((uint8_t)0x04)  /*!< I2C1 Alternate Function mapping         */
#define GPIO_AF4_SPI1           ((uint8_t)0x04)  /*!< SPI1 Alternate Function mapping        */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_SPI1           ((uint8_t)0x05)  /*!< SPI1 Alternate Function mapping        */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_MCO            ((uint8_t)0x06)  /*!< MCO Alternate Function mapping       */
#define GPIO_AF6_RF_DTB0        ((uint8_t)0x06)  /*!< RF_DTB0 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB1        ((uint8_t)0x06)  /*!< RF_DTB1 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB2        ((uint8_t)0x06)  /*!< RF_DTB2 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB3        ((uint8_t)0x06)  /*!< RF_DTB3 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB4        ((uint8_t)0x06)  /*!< RF_DTB4 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB5        ((uint8_t)0x06)  /*!< RF_DTB5 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB6        ((uint8_t)0x06)  /*!< RF_DTB6 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB7        ((uint8_t)0x06)  /*!< RF_DTB7 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB8        ((uint8_t)0x06)  /*!< RF_DTB8 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB9        ((uint8_t)0x06)  /*!< RF_DTB9 Alternate Function mapping   */
#define GPIO_AF6_RF_DTB10       ((uint8_t)0x06)  /*!< RF_DTB10 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB11       ((uint8_t)0x06)  /*!< RF_DTB11 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB12       ((uint8_t)0x06)  /*!< RF_DTB12 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB13       ((uint8_t)0x06)  /*!< RF_DTB13 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB14       ((uint8_t)0x06)  /*!< RF_DTB14 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB15       ((uint8_t)0x06)  /*!< RF_DTB15 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB16       ((uint8_t)0x06)  /*!< RF_DTB16 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB17       ((uint8_t)0x06)  /*!< RF_DTB17 Alternate Function mapping  */
#define GPIO_AF6_RF_DTB18       ((uint8_t)0x06)  /*!< RF_DTB18 Alternate Function mapping  */
#define GPIO_AF6_RF_MISO        ((uint8_t)0x06)  /*!< RF_MISO Alternate Function mapping   */
#define GPIO_AF6_RF_MOSI        ((uint8_t)0x06)  /*!< RF_MOSI Alternate Function mapping   */
#define GPIO_AF6_RF_SCK         ((uint8_t)0x06)  /*!< RF_SCK Alternate Function mapping    */
#define GPIO_AF6_RF_NSS         ((uint8_t)0x06)  /*!< RF_NSS Alternate Function mapping    */
/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_USART1         ((uint8_t)0x07)  /*!< USART1 Alternate Function mapping     */

/**
  * @brief   AF 8 selection
  */
#define GPIO_AF8_LPUART1        ((uint8_t)0x08)  /*!< LPUART1 Alternate Function mapping      */

/**
  * @brief   AF 9 selection
  */
#define GPIO_AF9_TSC           ((uint8_t)0x09)  /*!< TSC Alternate Function mapping      */

/**
  * @brief   AF 12 selection
  */
#define GPIO_AF12_COMP1         ((uint8_t)0x0c)  /*!< COMP1 Alternate Function mapping      */
#define GPIO_AF12_TIM1          ((uint8_t)0x0c)  /*!< TIM1 Alternate Function mapping      */

/**
  * @brief   AF 14 selection
  */
#define GPIO_AF14_TIM2          ((uint8_t)0x0e)  /*!< TIM2 Alternate Function mapping       */
#define GPIO_AF14_LPTIM2        ((uint8_t)0x0e)  /*!< LPTIM2 Alternate Function mapping     */


/**
  * @brief   AF 15 selection
  */
#define GPIO_AF15_EVENTOUT          ((uint8_t)0x0f)  /*!< EVENTOUT Alternate Function mapping      */

#define IS_GPIO_AF(AF)              ((AF) <= (uint8_t)0x0f)
#endif

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
#if defined (STM32WB55xx) || defined (STM32WB5Mxx)
#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0uL :\
                                      ((__GPIOx__) == (GPIOB))? 1uL :\
                                      ((__GPIOx__) == (GPIOC))? 2uL :\
                                      ((__GPIOx__) == (GPIOD))? 3uL :\
                                      ((__GPIOx__) == (GPIOE))? 4uL : 7uL)
#else
#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0uL :\
                                      ((__GPIOx__) == (GPIOB))? 1uL :\
                                      ((__GPIOx__) == (GPIOC))? 2uL :\
                                      ((__GPIOx__) == (GPIOE))? 4uL : 7uL)
#endif
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

#endif /* STM32WBxx_HAL_GPIO_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
