/*!
 * @file       apm32e10x_gpio.h
 *
 * @brief      This file contains all the functions prototypes for the GPIO firmware library
 *
 * @version     V1.0.2
 *
 * @date        2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2021-2023 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __APM32E10X_GPIO_H
#define __APM32E10X_GPIO_H

/* Includes */
#include "apm32e10x.h"

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup APM32E10x_StdPeriphDriver
  @{
*/

/** @addtogroup GPIO_Driver
  @{
*/

/** @defgroup GPIO_Enumerations Enumerations
  @{
*/

/**
 * @brief   GPIO Output Maximum frequency selection
 */
typedef enum
{
   GPIO_SPEED_10MHz = 1,
   GPIO_SPEED_2MHz,
   GPIO_SPEED_50MHz
}GPIO_SPEED_T;

/**
 * @brief   Configuration Mode enumeration
 */
typedef enum
{
    GPIO_MODE_ANALOG      = 0x0,   /*!< Analog mode */
    GPIO_MODE_IN_FLOATING = 0x04,  /*!< Floating input */
    GPIO_MODE_IN_PD       = 0x28,  /*!< Input with pull-down */
    GPIO_MODE_IN_PU       = 0x48,  /*!< Input with pull-up */
    GPIO_MODE_OUT_PP      = 0x80,  /*!< General purpose output push-pull */
    GPIO_MODE_OUT_OD      = 0x84,  /*!< General purpose output Open-drain */
    GPIO_MODE_AF_PP       = 0x88,  /*!< Alternate function output Push-pull */
    GPIO_MODE_AF_OD       = 0x8C,  /*!< Alternate function output Open-drain */
}GPIO_MODE_T;

/**
 * @brief    Definition of the GPIO pins
 */
typedef enum
{
    GPIO_PIN_0   = ((uint16_t)BIT0),
    GPIO_PIN_1   = ((uint16_t)BIT1),
    GPIO_PIN_2   = ((uint16_t)BIT2),
    GPIO_PIN_3   = ((uint16_t)BIT3),
    GPIO_PIN_4   = ((uint16_t)BIT4),
    GPIO_PIN_5   = ((uint16_t)BIT5),
    GPIO_PIN_6   = ((uint16_t)BIT6),
    GPIO_PIN_7   = ((uint16_t)BIT7),
    GPIO_PIN_8   = ((uint16_t)BIT8),
    GPIO_PIN_9   = ((uint16_t)BIT9),
    GPIO_PIN_10  = ((uint16_t)BIT10),
    GPIO_PIN_11  = ((uint16_t)BIT11),
    GPIO_PIN_12  = ((uint16_t)BIT12),
    GPIO_PIN_13  = ((uint16_t)BIT13),
    GPIO_PIN_14  = ((uint16_t)BIT14),
    GPIO_PIN_15  = ((uint16_t)BIT15),
    GPIO_PIN_ALL = ((uint32_t)0XFFFF)
} GPIO_PIN_T;

/**
 * @brief   GPIO remap type define
 */
typedef enum
{
   GPIO_NO_REMAP_SPI1          = 0x00000010,
   GPIO_REMAP_SPI1             = 0x00000011,

   GPIO_NO_REMAP_I2C1          = 0x00000110,
   GPIO_REMAP_I2C1             = 0x00000111,

   GPIO_NO_REMAP_USART1        = 0x00000210,
   GPIO_REMAP_USART1           = 0x00000211,

   GPIO_NO_REMAP_USART2        = 0x00000310,
   GPIO_REMAP_USART2           = 0x00000311,

   GPIO_NO_REMAP_USART3        = 0x00000430,
   GPIO_PARTIAL_REMAP_USART3   = 0x00000431,
   GPIO_FULL_REMAP_USART3      = 0x00000433,

   GPIO_NO_REMAP_TMR1          = 0x00000630,
   GPIO_PARTIAL_REMAP_TMR1     = 0x00000631,
   GPIO_FULL_REMAP_TMR1        = 0x00000633,

   GPIO_NO_REMAP_TMR2          = 0x00000830,
   GPIO_PARTIAL_REMAP1_TMR2    = 0x00000831,
   GPIO_PARTIAL_REMAP2_TMR2    = 0x00000832,
   GPIO_FULL_REMAP_TMR2        = 0x00000833,

   GPIO_NO_REMAP_TMR3          = 0x00000A30,
   GPIO_PARTIAL_REMAP_TMR3     = 0x00000A32,
   GPIO_FULL_REMAP_TMR3        = 0x00000A33,

   GPIO_NO_REMAP_TMR4          = 0x00000C10,
   GPIO_REMAP_TMR4             = 0x00000C11,

   GPIO_NO_REMAP_CAN1          = 0x00000D30,
   GPIO_REMAP1_CAN1            = 0x00000D32,
   GPIO_REMAP2_CAN1            = 0x00000D33,

   GPIO_NO_REMAP_PD01          = 0x00000F10,
   GPIO_REMAP_PD01             = 0x00000F11,

   GPIO_NO_REMAP_TMR5CH4_LSI   = 0x00001010,
   GPIO_REMAP_TMR5CH4_LSI      = 0x00001011,

   GPIO_NO_REMAP_ADC1_ETRGINJ  = 0x00001110,
   GPIO_REMAP_ADC1_ETRGINJ     = 0x00001111,

   GPIO_NO_REMAP_ADC1_ETRGREG  = 0x00001210,
   GPIO_REMAP_ADC1_ETRGREG     = 0x00001211,

   GPIO_NO_REMAP_ADC2_ETRGINJ  = 0x00001310,
   GPIO_REMAP_ADC2_ETRGINJ     = 0x00001311,

   GPIO_NO_REMAP_ADC2_ETRGREG  = 0x00001410,
   GPIO_REMAP_ADC2_ETRGREG     = 0x00001411,

   GPIO_NO_REMAP_CAN2          = 0x00001610,
   GPIO_REMAP_CAN2             = 0x00001611,

   GPIO_NO_REMAP_SWJ           = 0x00001870,
   GPIO_REMAP_SWJ_NOJTRST      = 0x00001871,
   GPIO_REMAP_SWJ_JTAGDISABLE  = 0x00001872,
   GPIO_REMAP_SWJ_DISABLE      = 0x00001874,

   GPIO_NO_REMAP_EMMC_NADV     = 0x00010A10,
   GPIO_REMAP_EMMC_NADV        = 0x00010A11
}GPIO_REMAP_T;

/**
 * @brief   gpio port source define
 */
typedef enum
{
   GPIO_PORT_SOURCE_A,
   GPIO_PORT_SOURCE_B,
   GPIO_PORT_SOURCE_C,
   GPIO_PORT_SOURCE_D,
   GPIO_PORT_SOURCE_E,
   GPIO_PORT_SOURCE_F,
   GPIO_PORT_SOURCE_G
}GPIO_PORT_SOURCE_T;

/**
 * @brief   gpio pin source define
 */
typedef enum
{
   GPIO_PIN_SOURCE_0,
   GPIO_PIN_SOURCE_1,
   GPIO_PIN_SOURCE_2,
   GPIO_PIN_SOURCE_3,
   GPIO_PIN_SOURCE_4,
   GPIO_PIN_SOURCE_5,
   GPIO_PIN_SOURCE_6,
   GPIO_PIN_SOURCE_7,
   GPIO_PIN_SOURCE_8,
   GPIO_PIN_SOURCE_9,
   GPIO_PIN_SOURCE_10,
   GPIO_PIN_SOURCE_11,
   GPIO_PIN_SOURCE_12,
   GPIO_PIN_SOURCE_13,
   GPIO_PIN_SOURCE_14,
   GPIO_PIN_SOURCE_15
}GPIO_PIN_SOURCE_T;

/**@} end of group GPIO_Enumerations */


/** @defgroup GPIO_Structures Structures
  @{
*/

/**
 * @brief   GPIO Config structure definition
 */
typedef struct
{
   uint16_t         pin;
   GPIO_SPEED_T     speed;
   GPIO_MODE_T      mode;
}GPIO_Config_T;

/**@} end of group GPIO_Structures */

/** @defgroup GPIO_Functions Functions
  @{
*/

/* Reset and common Configuration */
void GPIO_Reset(GPIO_T* port);
void GPIO_AFIOReset(void);
void GPIO_Config(GPIO_T* port, GPIO_Config_T* gpioConfig);
void GPIO_ConfigStructInit(GPIO_Config_T* gpioConfig);

/* Read */
uint8_t GPIO_ReadInputBit(GPIO_T* port, uint16_t pin);
uint16_t GPIO_ReadInputPort(GPIO_T* port);
uint8_t GPIO_ReadOutputBit(GPIO_T* port, uint16_t pin);
uint16_t GPIO_ReadOutputPort(GPIO_T* port);

/* Write */
void GPIO_SetBit(GPIO_T* port, uint16_t pin);
void GPIO_ResetBit(GPIO_T* port, uint16_t pin);
void GPIO_WriteOutputPort(GPIO_T* port, uint16_t portValue);
void GPIO_WriteBitValue(GPIO_T* port, uint16_t pin, uint8_t bitVal);

/* GPIO Configuration */
void GPIO_ConfigPinLock(GPIO_T* port, uint16_t pin);
void GPIO_ConfigEventOutput(GPIO_PORT_SOURCE_T portSource, GPIO_PIN_SOURCE_T pinSource);
void GPIO_EnableEventOutput(void);
void GPIO_DisableEventOutput(void);
void GPIO_ConfigPinRemap(GPIO_REMAP_T remap);
void GPIO_ConfigEINTLine(GPIO_PORT_SOURCE_T portSource, GPIO_PIN_SOURCE_T pinSource);

/**@} end of group GPIO_Functions */
/**@} end of group GPIO_Driver */
/**@} end of group APM32E10x_StdPeriphDriver*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32E10X_GPIO_H */
