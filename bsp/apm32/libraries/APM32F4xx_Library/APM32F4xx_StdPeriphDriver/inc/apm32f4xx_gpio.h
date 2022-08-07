/*!
 * @file        apm32f4xx_gpio.h
 *
 * @brief       This file provides all the GPIO firmware functions
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __APM32F4XX_GPIO_H
#define __APM32F4XX_GPIO_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup GPIO_Driver
  @{
*/

/** @defgroup GPIO_Enumerations
  @{
*/

/**
 * @brief GPIO Configuration Mode enumeration
 */
typedef enum
{
    GPIO_MODE_IN   = 0x00, /*!< GPIO Input Mode */
    GPIO_MODE_OUT  = 0x01, /*!< GPIO Output Mode */
    GPIO_MODE_AF   = 0x02, /*!< GPIO Alternate function Mode */
    GPIO_MODE_AN   = 0x03  /*!< GPIO Analog Mode */
} GPIO_MODE_T;

/**
 * @brief GPIO Output type enumeration
 */
typedef enum
{
    GPIO_OTYPE_PP = 0x00,   /*!< GPIO push-pull mode */
    GPIO_OTYPE_OD = 0x01    /*!< GPIO open drain mode */
} GPIO_OTYPE_T;

/**
 * @brief GPIO Output Maximum frequency enumeration
 */
typedef enum
{
    GPIO_SPEED_2MHz      = 0x00,      /*!< Low speed */
    GPIO_SPEED_25MHz     = 0x01,      /*!< Medium speed */
    GPIO_SPEED_50MHz     = 0x02,      /*!< Fast speed */
    GPIO_SPEED_100MHz    = 0x03       /*!< High speed */
} GPIO_SPEED_T;

/**
 * @brief GPIO Configuration PullUp PullDown enumeration
 */
typedef enum
{
    GPIO_PUPD_NOPULL = 0x00,    /*!< GPIO no pull mode */
    GPIO_PUPD_UP     = 0x01,    /*!< GPIO pull-up mode */
    GPIO_PUPD_DOWN   = 0x02     /*!< GPIO pull-down mode */
} GPIO_PUPD_T;

/**
 * @brief GPIO Pins
 */
typedef enum
{
    GPIO_PIN_0   = ((uint16_t)BIT0),    /*!< GPIO pin 0 selected */
    GPIO_PIN_1   = ((uint16_t)BIT1),    /*!< GPIO pin 1 selected */
    GPIO_PIN_2   = ((uint16_t)BIT2),    /*!< GPIO pin 2 selected */
    GPIO_PIN_3   = ((uint16_t)BIT3),    /*!< GPIO pin 3 selected */
    GPIO_PIN_4   = ((uint16_t)BIT4),    /*!< GPIO pin 4 selected */
    GPIO_PIN_5   = ((uint16_t)BIT5),    /*!< GPIO pin 5 selected */
    GPIO_PIN_6   = ((uint16_t)BIT6),    /*!< GPIO pin 6 selected */
    GPIO_PIN_7   = ((uint16_t)BIT7),    /*!< GPIO pin 7 selected */
    GPIO_PIN_8   = ((uint16_t)BIT8),    /*!< GPIO pin 8 selected */
    GPIO_PIN_9   = ((uint16_t)BIT9),    /*!< GPIO pin 9 selected */
    GPIO_PIN_10  = ((uint16_t)BIT10),   /*!< GPIO pin 10 selected */
    GPIO_PIN_11  = ((uint16_t)BIT11),   /*!< GPIO pin 11 selected */
    GPIO_PIN_12  = ((uint16_t)BIT12),   /*!< GPIO pin 12 selected */
    GPIO_PIN_13  = ((uint16_t)BIT13),   /*!< GPIO pin 13 selected */
    GPIO_PIN_14  = ((uint16_t)BIT14),   /*!< GPIO pin 14 selected */
    GPIO_PIN_15  = ((uint16_t)BIT15),   /*!< GPIO pin 15 selected */
    GPIO_PIN_ALL = ((uint32_t)0XFFFF),  /*!< GPIO all pins selected */
} GPIO_PIN_T;

/**
 * @brief GPIO Pin sources
 */
typedef enum
{
    GPIO_PIN_SOURCE_0,  /*!< GPIO pin source 0 */
    GPIO_PIN_SOURCE_1,  /*!< GPIO pin source 1 */
    GPIO_PIN_SOURCE_2,  /*!< GPIO pin source 2 */
    GPIO_PIN_SOURCE_3,  /*!< GPIO pin source 3 */
    GPIO_PIN_SOURCE_4,  /*!< GPIO pin source 4 */
    GPIO_PIN_SOURCE_5,  /*!< GPIO pin source 5 */
    GPIO_PIN_SOURCE_6,  /*!< GPIO pin source 6 */
    GPIO_PIN_SOURCE_7,  /*!< GPIO pin source 7 */
    GPIO_PIN_SOURCE_8,  /*!< GPIO pin source 8 */
    GPIO_PIN_SOURCE_9,  /*!< GPIO pin source 9 */
    GPIO_PIN_SOURCE_10, /*!< GPIO pin source 10 */
    GPIO_PIN_SOURCE_11, /*!< GPIO pin source 11 */
    GPIO_PIN_SOURCE_12, /*!< GPIO pin source 12 */
    GPIO_PIN_SOURCE_13, /*!< GPIO pin source 13 */
    GPIO_PIN_SOURCE_14, /*!< GPIO pin source 14 */
    GPIO_PIN_SOURCE_15, /*!< GPIO pin source 15 */
} GPIO_PIN_SOURCE_T;

/**
 * @brief GPIO Alternat function selection
 */
typedef enum
{
    GPIO_AF_RTC_50Hz            = 0x00, /*!< RTC_50Hz Alternate Function mapping */
    GPIO_AF_MCO                 = 0x00, /*!< MCO (MCO1 and MCO2) Alternate Function mapping */
    GPIO_AF_TAMPER              = 0x00, /*!< TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
    GPIO_AF_SWJ                 = 0x00, /*!< SWJ (SWD and JTAG) Alternate Function mapping */
    GPIO_AF_TRACE               = 0x00, /*!< TRACE Alternate Function mapping */

    GPIO_AF_TMR1                = 0x01, /*!< TMR1 Alternate Function mapping */
    GPIO_AF_TMR2                = 0x01, /*!< TMR2 Alternate Function mapping */
    GPIO_AF_LPTMR               = 0x01, /*!< LPTMR Alternate Function mapping */

    GPIO_AF_TMR3                = 0x02, /*!< TMR3 Alternate Function mapping */
    GPIO_AF_TMR4                = 0x02, /*!< TMR4 Alternate Function mapping */
    GPIO_AF_TMR5                = 0x02, /*!< TMR5 Alternate Function mapping */

    GPIO_AF_TMR8                = 0x03, /*!< TMR8 Alternate Function mapping */
    GPIO_AF_TMR9                = 0x03, /*!< TMR9 Alternate Function mapping */
    GPIO_AF_TMR10               = 0x03, /*!< TMR10 Alternate Function mapping */
    GPIO_AF_TMR11               = 0x03, /*!< TMR11 Alternate Function mapping */

    GPIO_AF_I2C1                = 0x04, /*!< I2C1 Alternate Function mapping */
    GPIO_AF_I2C2                = 0x04, /*!< I2C2 Alternate Function mapping */
    GPIO_AF_I2C3                = 0x04, /*!< I2C3 Alternate Function mapping */
    GPIO_AF_FMPI2C              = 0x04, /*!< FMPI2C Alternate Function mapping */

    GPIO_AF_SPI1                = 0x05, /*!< SPI1/I2S1 Alternate Function mapping */
    GPIO_AF_SPI2                = 0x05, /*!< SPI2/I2S2 Alternate Function mapping */
    GPIO_AF5_SPI3               = 0x05, /*!< SPI3/I2S3 Alternate Function mapping */
    GPIO_AF_SPI4                = 0x05, /*!< SPI4/I2S4 Alternate Function mapping */
    GPIO_AF_SPI5                = 0x05, /*!< SPI5 Alternate Function mapping */
    GPIO_AF_SPI6                = 0x05, /*!< SPI6 Alternate Function mapping */

    GPIO_AF_SPI3                = 0x06, /*!< SPI3/I2S3 Alternate Function mapping */
    GPIO_AF6_SPI1               = 0x06, /*!< SPI1 Alternate Function mapping */
    GPIO_AF6_SPI2               = 0x06, /*!< SPI2 Alternate Function mapping */
    GPIO_AF6_SPI4               = 0x06, /*!< SPI4 Alternate Function mapping */
    GPIO_AF6_SPI5               = 0x06, /*!< SPI5 Alternate Function mapping */
    GPIO_AF_SAI1                = 0x06, /*!< SAI1 Alternate Function mapping */
    GPIO_AF_I2S2ext             = 0x06, /*!< I2S2ext_SD Alternate Function mapping */

    GPIO_AF_USART1              = 0x07, /*!< USART1 Alternate Function mapping */
    GPIO_AF_USART2              = 0x07, /*!< USART2 Alternate Function mapping */
    GPIO_AF_USART3              = 0x07, /*!< USART3 Alternate Function mapping */
    GPIO_AF7_SPI3               = 0x07, /*!< SPI3/I2S3ext Alternate Function mapping */

    GPIO_AF_UART4               = 0x08, /*!< UART4 Alternate Function mapping */
    GPIO_AF_UART5               = 0x08, /*!< UART5 Alternate Function mapping */
    GPIO_AF_USART6              = 0x08, /*!< USART6 Alternate Function mapping */
    GPIO_AF_UART7               = 0x08, /*!< UART7 Alternate Function mapping */
    GPIO_AF_UART8               = 0x08, /*!< UART8 Alternate Function mapping */
    GPIO_AF8_USART3             = 0x08, /*!< USART3 Alternate Function mapping */
    GPIO_AF8_CAN1               = 0x08, /*!< CAN1 Alternate Function mapping */

    GPIO_AF_CAN1                = 0x09, /*!< CAN1 Alternate Function mapping */
    GPIO_AF_CAN2                = 0x09, /*!< CAN2 Alternate Function mapping */
    GPIO_AF_TMR12               = 0x09, /*!< TMR12 Alternate Function mapping */
    GPIO_AF_TMR13               = 0x09, /*!< TMR13 Alternate Function mapping */
    GPIO_AF_TMR14               = 0x09, /*!< TMR14 Alternate Function mapping */
    GPIO_AF9_I2C2               = 0x09, /*!< I2C2 Alternate Function mapping */
    GPIO_AF9_I2C3               = 0x09, /*!< I2C3 Alternate Function mapping */

    GPIO_AF_OTG_FS              = 0x0A, /*!< OTG_FS Alternate Function mapping */
    GPIO_AF_OTG_HS              = 0x0A, /*!< OTG_HS Alternate Function mapping */

    GPIO_AF_ETH                 = 0x0B, /*!< ETHERNET Alternate Function mapping */

    GPIO_AF_FSMC                = 0x0C, /*!< FSMC Alternate Function mapping */
    GPIO_AF_OTG_HS_FS           = 0x0C, /*!< OTG HS configured in FS, Alternate Function mapping */
    GPIO_AF_SDIO                = 0x0C, /*!< SDIO Alternate Function mapping */

    GPIO_AF_DCMI                = 0x0D, /*!< DCMI Alternate Function mapping */

    GPIO_AF14_RNG               = 0x0E, /*!< RNG Alternate Function mapping */

    GPIO_AF_EVENTOUT            = 0x0F, /*!< EVENTOUT Alternate Function mapping */
} GPIO_AF_T;

/**@} end of group GPIO_Enumerations*/

/** @addtogroup GPIO_Macros Macros
  @{
*/
#define GPIO_Mode_AIN           GPIO_Mode_AN

#define GPIO_AF_I2S3ext         GPIO_AF7_SPI3
#define GPIO_AF_OTG1_FS         GPIO_AF_OTG_FS
#define GPIO_AF_OTG2_HS         GPIO_AF_OTG_HS
#define GPIO_AF_OTG2_FS         GPIO_AF_OTG_HS_FS

/**@} end of group GPIO_Macros*/

/** @addtogroup GPIO_Structure Data Structure
  @{
*/

/**
 * @brief GPIO Init structure definition
 */
typedef struct
{
    uint16_t      pin;      //!< Specifies the GPIO pins to be configured.
    GPIO_MODE_T   mode;     //!< Specifies the operating mode for the selected pins.
    GPIO_SPEED_T  speed;    //!< Specifies the speed for the selected pins.
    GPIO_OTYPE_T  otype;    //!< Specifies the operating output type for the selected pins.
    GPIO_PUPD_T   pupd;     //!< Specifies the operating Pull-up/Pull down for the selected pins.
} GPIO_Config_T;

/**@} end of group GPIO_Structure*/

/** @defgroup GPIO_Functions
  @{
*/

/* Reset and common Configuration */
void GPIO_Reset(GPIO_T* port);
void GPIO_Config(GPIO_T* port, GPIO_Config_T* gpioConfig);
void GPIO_ConfigStructInit(GPIO_Config_T* gpioConfig);

/* GPIO Read functions */
uint8_t GPIO_ReadInputBit(GPIO_T* port, uint16_t pin);
uint8_t GPIO_ReadOutputBit(GPIO_T* port, uint16_t pin);

uint16_t GPIO_ReadInputPort(GPIO_T* port);
uint16_t GPIO_ReadOutputPort(GPIO_T* port);

/* GPIO Write functions */
void GPIO_SetBit(GPIO_T* port, uint16_t pin);
void GPIO_ResetBit(GPIO_T* port, uint16_t pin);
void GPIO_WriteBitValue(GPIO_T* port, uint16_t pin, uint8_t bitVal);
void GPIO_WriteOutputPort(GPIO_T* port, uint16_t portValue);

/* GPIO Other functions */
void GPIO_ToggleBit(GPIO_T* port, uint16_t pin);
void GPIO_ConfigPinLock(GPIO_T* port, uint16_t pin);
void GPIO_ConfigPinAF(GPIO_T* port, GPIO_PIN_SOURCE_T gpioPinSource, GPIO_AF_T gpioAf);

#ifdef __cplusplus
}
#endif

#endif /*__APM32F4XX_GPIO_H */

/**@} end of group GPIO_Enumerations */
/**@} end of group GPIO_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
