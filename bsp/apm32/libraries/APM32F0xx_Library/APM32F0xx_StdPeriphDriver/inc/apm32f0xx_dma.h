/*!
 * @file        apm32f0xx_dma.h
 *
 * @brief       This file contains all the functions prototypes for the DMA firmware
 *
 * @version     V1.0.3
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
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
#ifndef __APM32F0XX_DMA_H
#define __APM32F0XX_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup DMA_Driver
  @{
*/

/** @defgroup DMA_Macros Macros
  @{
*/

/**@} end of group DMA_Macros*/

/** @defgroup DMA_Enumerations Enumerations
  @{
*/

/**
 * @brief   DMA data transfer direction
 */
typedef enum
{
    DMA_DIR_PERIPHERAL   = ((uint8_t)0),  /*!< Peripheral to memory */
    DMA_DIR_MEMORY       = ((uint8_t)1),  /*!< Memory to peripheral */
} DMA_DIR_T;

/**
 * @brief   DMA peripheral increment mode
 */
typedef enum
{
    DMA_PERIPHERAL_INC_DISABLE  = ((uint8_t)0),  /*!< Disable peripheral address increment mode */
    DMA_PERIPHERAL_INC_ENABLE   = ((uint8_t)1),  /*!< Enable peripheral address increment mode */
} DMA_PERIPHERAL_INC_T;

/**
 * @brief   DMA memory increment mode
 */
typedef enum
{
    DMA_MEMORY_INC_DISABLE  = ((uint8_t)0),  /*!< Disable memory address increment mode */
    DMA_MEMORY_INC_ENABLE   = ((uint8_t)1),  /*!< Enable memory address increment mode */
} DMA_MEMORY_INC_T;

/**
 * @brief   DMA peripheral data size
 */
typedef enum
{
    DMA_PERIPHERAL_DATASIZE_BYTE       = ((uint8_t)0x00),  /*!< Set peripheral data size to byte */
    DMA_PERIPHERAL_DATASIZE_HALFWORD   = ((uint8_t)0x01),  /*!< Set peripheral data size to half-word */
    DMA_PERIPHERAL_DATASIZE_WORD       = ((uint8_t)0x02),  /*!< Set peripheral data size to word */
} DMA_PERIPHERAL_DATASIZE_T;

/**
 * @brief   DMA memory data size
 */
typedef enum
{
    DMA_MEMORY_DATASIZE_BYTE       = ((uint8_t)0x00),  /*!< Set memory data size to byte */
    DMA_MEMORY_DATASIZE_HALFWORD   = ((uint8_t)0x01),  /*!< Set memory data size to half-word */
    DMA_MEMORY_DATASIZE_WORD       = ((uint8_t)0x02),  /*!< Set memory data size to word */
} DMA_MEMORY_DATASIZE_T;

/**
 * @brief   DMA circular mode
 */
typedef enum
{
    DMA_CIRCULAR_DISABLE  = ((uint8_t)0),  /*!< Disable circular mode */
    DMA_CIRCULAR_ENABLE   = ((uint8_t)1),  /*!< Enable circular mode */
} DMA_CIRCULAR_T;

/**
 * @brief   DMA priority level
 */
typedef enum
{
    DMA_PRIORITY_LEVEL_LOW      = ((uint8_t)0x00),  /*!< Set priority level to low */
    DMA_PRIORITY_LEVEL_MEDIUM   = ((uint8_t)0x01),  /*!< Set priority level to medium */
    DMA_PRIORITY_LEVEL_HIGHT    = ((uint8_t)0x02),  /*!< Set priority level to high */
    DMA_PRIORITY_LEVEL_VERYHIGH = ((uint8_t)0x03),  /*!< Set priority level to very high */
} DMA_PRIORITY_LEVEL_T;

/**
 * @brief   DMA memory to memory
 */
typedef enum
{
    DMA_M2M_DISABLE  = ((uint8_t)0),  /*!< Disable memory to memory mode */
    DMA_M2M_ENABLE   = ((uint8_t)1),  /*!< Enable memory to memory mode */
} DMA_M2M_T;

/**
 * @brief    DMA channels remapping definition
 */
typedef enum
{
    DMA1_CHANNEL1_DEFAULT   = (uint32_t)0x00000000,    /*!< DMA1 channel1 remapping DEFAULT   */
    DMA1_CHANNEL1_ADC       = (uint32_t)0x00000001,    /*!< DMA1 channel1 remapping ADC       */
    DMA1_CHANNEL1_TMR17_CH1 = (uint32_t)0x00000007,    /*!< DMA1 channel1 remapping TMR17_CH1 */
    DMA1_CHANNEL1_TMR17_UP  = (uint32_t)0x00000007,    /*!< DMA1 channel1 remapping TMR17_UP  */
    DMA1_CHANNEL1_USART1_RX = (uint32_t)0x00000008,    /*!< DMA1 channel1 remapping USART1_RX */
    DMA1_CHANNEL1_USART2_RX = (uint32_t)0x00000009,    /*!< DMA1 channel1 remapping USART2_RX */
    DMA1_CHANNEL1_USART3_RX = (uint32_t)0x0000000A,    /*!< DMA1 channel1 remapping USART3_RX */
    DMA1_CHANNEL1_USART4_RX = (uint32_t)0x0000000B,    /*!< DMA1 channel1 remapping USART4_RX */
    DMA1_CHANNEL1_USART5_RX = (uint32_t)0x0000000C,    /*!< DMA1 channel1 remapping USART5_RX */
    DMA1_CHANNEL1_USART6_RX = (uint32_t)0x0000000D,    /*!< DMA1 channel1 remapping USART6_RX */
    DMA1_CHANNEL1_USART7_RX = (uint32_t)0x0000000E,    /*!< DMA1 channel1 remapping USART7_RX */
    DMA1_CHANNEL1_USART8_RX = (uint32_t)0x0000000F,    /*!< DMA1 channel1 remapping USART8_RX */

    DMA1_CHANNEL2_DEFAULT   = (uint32_t)0x10000000,    /*!< DMA1 channel2 remapping DEFAULT   */
    DMA1_CHANNEL2_ADC       = (uint32_t)0x10000010,    /*!< DMA1 channel2 remapping ADC       */
    DMA1_CHANNEL2_I2C1_TX   = (uint32_t)0x10000020,    /*!< DMA1 channel2 remapping I2C1_TX   */
    DMA1_CHANNEL2_SPI1_RX   = (uint32_t)0x10000030,    /*!< DMA1 channel2 remapping SPI1_RX   */
    DMA1_CHANNEL2_TMR1_CH1  = (uint32_t)0x10000040,    /*!< DMA1 channel2 remapping TMR1_CH1  */
    DMA1_CHANNEL2_TMR17_CH1 = (uint32_t)0x10000070,    /*!< DMA1 channel2 remapping TMR17_CH1 */
    DMA1_CHANNEL2_TMR17_UP  = (uint32_t)0x10000070,    /*!< DMA1 channel2 remapping TMR17_UP  */
    DMA1_CHANNEL2_USART1_TX = (uint32_t)0x10000080,    /*!< DMA1 channel2 remapping USART1_TX */
    DMA1_CHANNEL2_USART2_TX = (uint32_t)0x10000090,    /*!< DMA1 channel2 remapping USART2_TX */
    DMA1_CHANNEL2_USART3_TX = (uint32_t)0x100000A0,    /*!< DMA1 channel2 remapping USART3_TX */
    DMA1_CHANNEL2_USART4_TX = (uint32_t)0x100000B0,    /*!< DMA1 channel2 remapping USART4_TX */
    DMA1_CHANNEL2_USART5_TX = (uint32_t)0x100000C0,    /*!< DMA1 channel2 remapping USART5_TX */
    DMA1_CHANNEL2_USART6_TX = (uint32_t)0x100000D0,    /*!< DMA1 channel2 remapping USART6_TX */
    DMA1_CHANNEL2_USART7_TX = (uint32_t)0x100000E0,    /*!< DMA1 channel2 remapping USART7_TX */
    DMA1_CHANNEL2_USART8_TX = (uint32_t)0x100000F0,    /*!< DMA1 channel2 remapping USART8_TX */

    DMA1_CHANNEL3_DEFAULT   = (uint32_t)0x20000000,    /*!< DMA1 channel3 remapping DEFAULT   */
    DMA1_CHANNEL3_TMR6_UP   = (uint32_t)0x20000100,    /*!< DMA1 channel3 remapping TMR6_UP   */
    DMA1_CHANNEL3_DAC_CH1   = (uint32_t)0x20000100,    /*!< DMA1 channel3 remapping DAC_CH1   */
    DMA1_CHANNEL3_I2C1_RX   = (uint32_t)0x20000200,    /*!< DMA1 channel3 remapping I2C1_RX   */
    DMA1_CHANNEL3_SPI1_TX   = (uint32_t)0x20000300,    /*!< DMA1 channel3 remapping SPI1_TX   */
    DMA1_CHANNEL3_TMR1_CH2  = (uint32_t)0x20000400,    /*!< DMA1 channel3 remapping TMR1_CH2  */
    DMA1_CHANNEL3_TMR2_CH2  = (uint32_t)0x20000500,    /*!< DMA1 channel3 remapping TMR2_CH2  */
    DMA1_CHANNEL3_TMR16_CH1 = (uint32_t)0x20000700,    /*!< DMA1 channel3 remapping TMR16_CH1 */
    DMA1_CHANNEL3_TMR16_UP  = (uint32_t)0x20000700,    /*!< DMA1 channel3 remapping TMR16_UP  */
    DMA1_CHANNEL3_USART1_RX = (uint32_t)0x20000800,    /*!< DMA1 channel3 remapping USART1_RX */
    DMA1_CHANNEL3_USART2_RX = (uint32_t)0x20000900,    /*!< DMA1 channel3 remapping USART2_RX */
    DMA1_CHANNEL3_USART3_RX = (uint32_t)0x20000A00,    /*!< DMA1 channel3 remapping USART3_RX */
    DMA1_CHANNEL3_USART4_RX = (uint32_t)0x20000B00,    /*!< DMA1 channel3 remapping USART4_RX */
    DMA1_CHANNEL3_USART5_RX = (uint32_t)0x20000C00,    /*!< DMA1 channel3 remapping USART5_RX */
    DMA1_CHANNEL3_USART6_RX = (uint32_t)0x20000D00,    /*!< DMA1 channel3 remapping USART6_RX */
    DMA1_CHANNEL3_USART7_RX = (uint32_t)0x20000E00,    /*!< DMA1 channel3 remapping USART7_RX */
    DMA1_CHANNEL3_USART8_RX = (uint32_t)0x20000F00,    /*!< DMA1 channel3 remapping USART8_RX */

    DMA1_CHANNEL4_DEFAULT   = (uint32_t)0x30000000,    /*!< DMA1 channel4 remapping DEFAULT   */
    DMA1_CHANNEL4_TMR7_UP   = (uint32_t)0x30001000,    /*!< DMA1 channel4 remapping TMR7_UP   */
    DMA1_CHANNEL4_DAC_CH2   = (uint32_t)0x30001000,    /*!< DMA1 channel4 remapping DAC_CH2   */
    DMA1_CHANNEL4_I2C2_TX   = (uint32_t)0x30002000,    /*!< DMA1 channel4 remapping I2C2_TX   */
    DMA1_CHANNEL4_SPI2_RX   = (uint32_t)0x30003000,    /*!< DMA1 channel4 remapping SPI2_RX   */
    DMA1_CHANNEL4_TMR2_CH4  = (uint32_t)0x30005000,    /*!< DMA1 channel4 remapping TMR2_CH4  */
    DMA1_CHANNEL4_TMR3_CH1  = (uint32_t)0x30006000,    /*!< DMA1 channel4 remapping TMR3_CH1  */
    DMA1_CHANNEL4_TMR3_TRIG = (uint32_t)0x30006000,    /*!< DMA1 channel4 remapping TMR3_TRIG */
    DMA1_CHANNEL4_TMR16_CH1 = (uint32_t)0x30007000,    /*!< DMA1 channel4 remapping TMR16_CH1 */
    DMA1_CHANNEL4_TMR16_UP  = (uint32_t)0x30007000,    /*!< DMA1 channel4 remapping TMR16_UP  */
    DMA1_CHANNEL4_USART1_TX = (uint32_t)0x30008000,    /*!< DMA1 channel4 remapping USART1_TX */
    DMA1_CHANNEL4_USART2_TX = (uint32_t)0x30009000,    /*!< DMA1 channel4 remapping USART2_TX */
    DMA1_CHANNEL4_USART3_TX = (uint32_t)0x3000A000,    /*!< DMA1 channel4 remapping USART3_TX */
    DMA1_CHANNEL4_USART4_TX = (uint32_t)0x3000B000,    /*!< DMA1 channel4 remapping USART4_TX */
    DMA1_CHANNEL4_USART5_TX = (uint32_t)0x3000C000,    /*!< DMA1 channel4 remapping USART5_TX */
    DMA1_CHANNEL4_USART6_TX = (uint32_t)0x3000D000,    /*!< DMA1 channel4 remapping USART6_TX */
    DMA1_CHANNEL4_USART7_TX = (uint32_t)0x3000E000,    /*!< DMA1 channel4 remapping USART7_TX */
    DMA1_CHANNEL4_USART8_TX = (uint32_t)0x3000F000,    /*!< DMA1 channel4 remapping USART8_TX */

    DMA1_CHANNEL5_DEFAULT   = (uint32_t)0x40000000,    /*!< DMA1 channel5 remapping DEFAULT   */
    DMA1_CHANNEL5_I2C2_RX   = (uint32_t)0x40020000,    /*!< DMA1 channel5 remapping I2C2_RX   */
    DMA1_CHANNEL5_SPI2_TX   = (uint32_t)0x40030000,    /*!< DMA1 channel5 remapping SPI2_TX   */
    DMA1_CHANNEL5_TMR1_CH3  = (uint32_t)0x40040000,    /*!< DMA1 channel5 remapping TMR1_CH3  */
    DMA1_CHANNEL5_USART1_RX = (uint32_t)0x40080000,    /*!< DMA1 channel5 remapping USART1_RX */
    DMA1_CHANNEL5_USART2_RX = (uint32_t)0x40090000,    /*!< DMA1 channel5 remapping USART2_RX */
    DMA1_CHANNEL5_USART3_RX = (uint32_t)0x400A0000,    /*!< DMA1 channel5 remapping USART3_RX */
    DMA1_CHANNEL5_USART4_RX = (uint32_t)0x400B0000,    /*!< DMA1 channel5 remapping USART4_RX */
    DMA1_CHANNEL5_USART5_RX = (uint32_t)0x400C0000,    /*!< DMA1 channel5 remapping USART5_RX */
    DMA1_CHANNEL5_USART6_RX = (uint32_t)0x400D0000,    /*!< DMA1 channel5 remapping USART6_RX */
    DMA1_CHANNEL5_USART7_RX = (uint32_t)0x400E0000,    /*!< DMA1 channel5 remapping USART7_RX */
    DMA1_CHANNEL5_USART8_RX = (uint32_t)0x400F0000,    /*!< DMA1 channel5 remapping USART8_RX */

    DMA1_CHANNEL6_DEFAULT   = (uint32_t)0x50000000,    /*!< DMA1 channel6 remapping DEFAULT   */
    DMA1_CHANNEL6_I2C1_TX   = (uint32_t)0x50200000,    /*!< DMA1 channel6 remapping I2C1_TX   */
    DMA1_CHANNEL6_SPI2_RX   = (uint32_t)0x50300000,    /*!< DMA1 channel6 remapping SPI2_RX   */
    DMA1_CHANNEL6_TMR1_CH1  = (uint32_t)0x50400000,    /*!< DMA1 channel6 remapping TMR1_CH1  */
    DMA1_CHANNEL6_TMR1_CH2  = (uint32_t)0x50400000,    /*!< DMA1 channel6 remapping TMR1_CH2  */
    DMA1_CHANNEL6_TMR1_CH3  = (uint32_t)0x50400000,    /*!< DMA1 channel6 remapping TMR1_CH3  */
    DMA1_CHANNEL6_TMR3_CH1  = (uint32_t)0x50600000,    /*!< DMA1 channel6 remapping TMR3_CH1  */
    DMA1_CHANNEL6_TMR3_TRIG = (uint32_t)0x50600000,    /*!< DMA1 channel6 remapping TMR3_TRIG */
    DMA1_CHANNEL6_TMR16_CH1 = (uint32_t)0x50700000,    /*!< DMA1 channel6 remapping TMR16_CH1 */
    DMA1_CHANNEL6_TMR16_UP  = (uint32_t)0x50700000,    /*!< DMA1 channel6 remapping TMR16_UP  */
    DMA1_CHANNEL6_USART1_RX = (uint32_t)0x50800000,    /*!< DMA1 channel6 remapping USART1_RX */
    DMA1_CHANNEL6_USART2_RX = (uint32_t)0x50900000,    /*!< DMA1 channel6 remapping USART2_RX */
    DMA1_CHANNEL6_USART3_RX = (uint32_t)0x50A00000,    /*!< DMA1 channel6 remapping USART3_RX */
    DMA1_CHANNEL6_USART4_RX = (uint32_t)0x50B00000,    /*!< DMA1 channel6 remapping USART4_RX */
    DMA1_CHANNEL6_USART5_RX = (uint32_t)0x50C00000,    /*!< DMA1 channel6 remapping USART5_RX */
    DMA1_CHANNEL6_USART6_RX = (uint32_t)0x50D00000,    /*!< DMA1 channel6 remapping USART6_RX */
    DMA1_CHANNEL6_USART7_RX = (uint32_t)0x50E00000,    /*!< DMA1 channel6 remapping USART7_RX */
    DMA1_CHANNEL6_USART8_RX = (uint32_t)0x50F00000,    /*!< DMA1 channel6 remapping USART8_RX */

    DMA1_CHANNEL7_DEFAULT   = (uint32_t)0x60000000,    /*!< DMA1 channel7 remapping DEFAULT   */
    DMA1_CHANNEL7_I2C1_RX   = (uint32_t)0x62000000,    /*!< DMA1 channel7 remapping I2C1_RX   */
    DMA1_CHANNEL7_SPI2_TX   = (uint32_t)0x63000000,    /*!< DMA1 channel7 remapping SPI2_TX   */
    DMA1_CHANNEL7_TMR2_CH2  = (uint32_t)0x65000000,    /*!< DMA1 channel7 remapping TMR2_CH2  */
    DMA1_CHANNEL7_TMR2_CH4  = (uint32_t)0x65000000,    /*!< DMA1 channel7 remapping TMR2_CH4  */
    DMA1_CHANNEL7_TMR17_CH1 = (uint32_t)0x67000000,    /*!< DMA1 channel7 remapping TMR17_CH1 */
    DMA1_CHANNEL7_TMR17_UP  = (uint32_t)0x67000000,    /*!< DMA1 channel7 remapping TMR17_UP  */
    DMA1_CHANNEL7_USART1_TX = (uint32_t)0x68000000,    /*!< DMA1 channel7 remapping USART1_TX */
    DMA1_CHANNEL7_USART2_TX = (uint32_t)0x69000000,    /*!< DMA1 channel7 remapping USART2_TX */
    DMA1_CHANNEL7_USART3_TX = (uint32_t)0x6A000000,    /*!< DMA1 channel7 remapping USART3_TX */
    DMA1_CHANNEL7_USART4_TX = (uint32_t)0x6B000000,    /*!< DMA1 channel7 remapping USART4_TX */
    DMA1_CHANNEL7_USART5_TX = (uint32_t)0x6C000000,    /*!< DMA1 channel7 remapping USART5_TX */
    DMA1_CHANNEL7_USART6_TX = (uint32_t)0x6D000000,    /*!< DMA1 channel7 remapping USART6_TX */
    DMA1_CHANNEL7_USART7_TX = (uint32_t)0x6E000000,    /*!< DMA1 channel7 remapping USART7_TX */
    DMA1_CHANNEL7_USART8_TX = (uint32_t)0x6F000000,    /*!< DMA1 channel7 remapping USART8_TX */

    DMA2_CHANNEL1_DEFAULT   = (uint32_t)0x00000000,    /*!< DMA2 channel1 remapping DEFAULT   */
    DMA2_CHANNEL1_I2C2_TX   = (uint32_t)0x00000002,    /*!< DMA2 channel1 remapping I2C2_TX   */
    DMA2_CHANNEL1_USART1_TX = (uint32_t)0x00000008,    /*!< DMA2 channel1 remapping USART1_TX */
    DMA2_CHANNEL1_USART2_TX = (uint32_t)0x00000009,    /*!< DMA2 channel1 remapping USART2_TX */
    DMA2_CHANNEL1_USART3_TX = (uint32_t)0x0000000A,    /*!< DMA2 channel1 remapping USART3_TX */
    DMA2_CHANNEL1_USART4_TX = (uint32_t)0x0000000B,    /*!< DMA2 channel1 remapping USART4_TX */
    DMA2_CHANNEL1_USART5_TX = (uint32_t)0x0000000C,    /*!< DMA2 channel1 remapping USART5_TX */
    DMA2_CHANNEL1_USART6_TX = (uint32_t)0x0000000D,    /*!< DMA2 channel1 remapping USART6_TX */
    DMA2_CHANNEL1_USART7_TX = (uint32_t)0x0000000E,    /*!< DMA2 channel1 remapping USART7_TX */
    DMA2_CHANNEL1_USART8_TX = (uint32_t)0x0000000F,    /*!< DMA2 channel1 remapping USART8_TX */

    DMA2_CHANNEL2_DEFAULT   = (uint32_t)0x00000000,    /*!< DMA2 channel2 remapping DEFAULT   */
    DMA2_CHANNEL2_I2C2_RX   = (uint32_t)0x00000020,    /*!< DMA2 channel2 remapping I2C2_RX   */
    DMA2_CHANNEL2_USART1_RX = (uint32_t)0x00000080,    /*!< DMA2 channel2 remapping USART1_RX */
    DMA2_CHANNEL2_USART2_RX = (uint32_t)0x00000090,    /*!< DMA2 channel2 remapping USART2_RX */
    DMA2_CHANNEL2_USART3_RX = (uint32_t)0x000000A0,    /*!< DMA2 channel2 remapping USART3_RX */
    DMA2_CHANNEL2_USART4_RX = (uint32_t)0x000000B0,    /*!< DMA2 channel2 remapping USART4_RX */
    DMA2_CHANNEL2_USART5_RX = (uint32_t)0x000000C0,    /*!< DMA2 channel2 remapping USART5_RX */
    DMA2_CHANNEL2_USART6_RX = (uint32_t)0x000000D0,    /*!< DMA2 channel2 remapping USART6_RX */
    DMA2_CHANNEL2_USART7_RX = (uint32_t)0x000000E0,    /*!< DMA2 channel2 remapping USART7_RX */
    DMA2_CHANNEL2_USART8_RX = (uint32_t)0x000000F0,    /*!< DMA2 channel2 remapping USART8_RX */

    DMA2_CHANNEL3_DEFAULT   = (uint32_t)0x00000000,    /*!< DMA2 channel3 remapping DEFAULT   */
    DMA2_CHANNEL3_TMR6_UP   = (uint32_t)0x00000100,    /*!< DMA2 channel3 remapping TMR6_UP   */
    DMA2_CHANNEL3_DAC_CH1   = (uint32_t)0x00000100,    /*!< DMA2 channel3 remapping DAC_CH1   */
    DMA2_CHANNEL3_SPI1_RX   = (uint32_t)0x00000300,    /*!< DMA2 channel3 remapping SPI1_RX   */
    DMA2_CHANNEL3_USART1_RX = (uint32_t)0x00000800,    /*!< DMA2 channel3 remapping USART1_RX */
    DMA2_CHANNEL3_USART2_RX = (uint32_t)0x00000900,    /*!< DMA2 channel3 remapping USART2_RX */
    DMA2_CHANNEL3_USART3_RX = (uint32_t)0x00000A00,    /*!< DMA2 channel3 remapping USART3_RX */
    DMA2_CHANNEL3_USART4_RX = (uint32_t)0x00000B00,    /*!< DMA2 channel3 remapping USART4_RX */
    DMA2_CHANNEL3_USART5_RX = (uint32_t)0x00000C00,    /*!< DMA2 channel3 remapping USART5_RX */
    DMA2_CHANNEL3_USART6_RX = (uint32_t)0x00000D00,    /*!< DMA2 channel3 remapping USART6_RX */
    DMA2_CHANNEL3_USART7_RX = (uint32_t)0x00000E00,    /*!< DMA2 channel3 remapping USART7_RX */
    DMA2_CHANNEL3_USART8_RX = (uint32_t)0x00000F00,    /*!< DMA2 channel3 remapping USART8_RX */

    DMA2_CHANNEL4_DEFAULT   = (uint32_t)0x00000000,    /*!< DMA2 channel4 remapping DEFAULT   */
    DMA2_CHANNEL4_TMR7_UP   = (uint32_t)0x00001000,    /*!< DMA2 channel4 remapping TMR7_UP   */
    DMA2_CHANNEL4_DAC_CH2   = (uint32_t)0x00001000,    /*!< DMA2 channel4 remapping DAC_CH2   */
    DMA2_CHANNEL4_SPI1_TX   = (uint32_t)0x00003000,    /*!< DMA2 channel4 remapping SPI1_TX   */
    DMA2_CHANNEL4_USART1_TX = (uint32_t)0x00008000,    /*!< DMA2 channel4 remapping USART1_TX */
    DMA2_CHANNEL4_USART2_TX = (uint32_t)0x00009000,    /*!< DMA2 channel4 remapping USART2_TX */
    DMA2_CHANNEL4_USART3_TX = (uint32_t)0x0000A000,    /*!< DMA2 channel4 remapping USART3_TX */
    DMA2_CHANNEL4_USART4_TX = (uint32_t)0x0000B000,    /*!< DMA2 channel4 remapping USART4_TX */
    DMA2_CHANNEL4_USART5_TX = (uint32_t)0x0000C000,    /*!< DMA2 channel4 remapping USART5_TX */
    DMA2_CHANNEL4_USART6_TX = (uint32_t)0x0000D000,    /*!< DMA2 channel4 remapping USART6_TX */
    DMA2_CHANNEL4_USART7_TX = (uint32_t)0x0000E000,    /*!< DMA2 channel4 remapping USART7_TX */
    DMA2_CHANNEL4_USART8_TX = (uint32_t)0x0000F000,    /*!< DMA2 channel4 remapping USART8_TX */

    DMA2_CHANNEL5_DEFAULT   = (uint32_t)0x00000000,    /*!< DMA2 channel5 remapping DEFAULT   */
    DMA2_CHANNEL5_ADC       = (uint32_t)0x00010000,    /*!< DMA2 channel5 remapping ADC       */
    DMA2_CHANNEL5_USART1_TX = (uint32_t)0x00080000,    /*!< DMA2 channel5 remapping USART1_TX */
    DMA2_CHANNEL5_USART2_TX = (uint32_t)0x00090000,    /*!< DMA2 channel5 remapping USART2_TX */
    DMA2_CHANNEL5_USART3_TX = (uint32_t)0x000A0000,    /*!< DMA2 channel5 remapping USART3_TX */
    DMA2_CHANNEL5_USART4_TX = (uint32_t)0x000B0000,    /*!< DMA2 channel5 remapping USART4_TX */
    DMA2_CHANNEL5_USART5_TX = (uint32_t)0x000C0000,    /*!< DMA2 channel5 remapping USART5_TX */
    DMA2_CHANNEL5_USART6_TX = (uint32_t)0x000D0000,    /*!< DMA2 channel5 remapping USART6_TX */
    DMA2_CHANNEL5_USART7_TX = (uint32_t)0x000E0000,    /*!< DMA2 channel5 remapping USART7_TX */
    DMA2_CHANNEL5_USART8_TX = (uint32_t)0x000F0000,    /*!< DMA2 channel5 remapping USART8_TX */
} DMA_CHANNEL_REMAP_T;

/**
 * @brief    DMA flag definition
 */
typedef enum
{
    DMA1_FLAG_AL1    = ((uint32_t)0x00000001),  /*!< Channel 1 All flag */
    DMA1_FLAG_TF1    = ((uint32_t)0X00000002),  /*!< Channel 1 Transfer Complete flag */
    DMA1_FLAG_HT1    = ((uint32_t)0X00000004),  /*!< Channel 1 Half Transfer Complete flag */
    DMA1_FLAG_TE1    = ((uint32_t)0X00000008),  /*!< Channel 1 Transfer Error flag */

    DMA1_FLAG_AL2    = ((uint32_t)0x00000010),  /*!< Channel 2 All flag */
    DMA1_FLAG_TF2    = ((uint32_t)0x00000020),  /*!< Channel 2 Transfer Complete flag */
    DMA1_FLAG_HT2    = ((uint32_t)0x00000040),  /*!< Channel 2 Half Transfer Complete flag */
    DMA1_FLAG_TE2    = ((uint32_t)0x00000080),  /*!< Channel 2 Transfer Error flag */

    DMA1_FLAG_AL3    = ((uint32_t)0x00000100),  /*!< Channel 3 All flag */
    DMA1_FLAG_TF3    = ((uint32_t)0x00000200),  /*!< Channel 3 Transfer Complete flag */
    DMA1_FLAG_HT3    = ((uint32_t)0x00000400),  /*!< Channel 3 Half Transfer Complete flag */
    DMA1_FLAG_TE3    = ((uint32_t)0x00000800),  /*!< Channel 3 Transfer Error flag */

    DMA1_FLAG_AL4    = ((uint32_t)0x00001000),  /*!< Channel 4 All flag */
    DMA1_FLAG_TF4    = ((uint32_t)0x00002000),  /*!< Channel 4 Transfer Complete flag */
    DMA1_FLAG_HT4    = ((uint32_t)0x00004000),  /*!< Channel 4 Half Transfer Complete flag */
    DMA1_FLAG_TE4    = ((uint32_t)0x00008000),  /*!< Channel 4 Transfer Error flag */

    DMA1_FLAG_AL5    = ((uint32_t)0x00010000),  /*!< Channel 5 All flag */
    DMA1_FLAG_TF5    = ((uint32_t)0x00020000),  /*!< Channel 5 Transfer Complete flag */
    DMA1_FLAG_HT5    = ((uint32_t)0x00040000),  /*!< Channel 5 Half Transfer Complete flag */
    DMA1_FLAG_TE5    = ((uint32_t)0x00080000),  /*!< Channel 5 Transfer Error flag */
    /* Only for APM32F072 and APM32F091 devices */
    DMA1_FLAG_AL6    = ((uint32_t)0x00100000),  /*!< Channel 6 All flag */
    DMA1_FLAG_TF6    = ((uint32_t)0x00200000),  /*!< Channel 6 Transfer Complete flag */
    DMA1_FLAG_HT6    = ((uint32_t)0x00400000),  /*!< Channel 6 Half Transfer Complete flag */
    DMA1_FLAG_TE6    = ((uint32_t)0x00800000),  /*!< Channel 6 Transfer Error flag */
    /* Only for APM32F072 and APM32F091 devices */
    DMA1_FLAG_AL7    = ((uint32_t)0x01000000),  /*!< Channel 7 All flag */
    DMA1_FLAG_TF7    = ((uint32_t)0x02000000),  /*!< Channel 7 Transfer Complete flag */
    DMA1_FLAG_HT7    = ((uint32_t)0x04000000),  /*!< Channel 7 Half Transfer Complete flag */
    DMA1_FLAG_TE7    = ((uint32_t)0x08000000),  /*!< Channel 7 Transfer Error flag */
    /* Only for APM32F091 devices */
    DMA2_FLAG_AL1    = ((uint32_t)0x10000001),  /*!< Channel 1 All flag */
    DMA2_FLAG_TF1    = ((uint32_t)0X00000002),  /*!< Channel 1 Transfer Complete flag */
    DMA2_FLAG_HT1    = ((uint32_t)0X00000004),  /*!< Channel 1 Half Transfer Complete flag */
    DMA2_FLAG_TE1    = ((uint32_t)0X00000008),  /*!< Channel 1 Transfer Error flag */
    /* Only for APM32F091 devices */
    DMA2_FLAG_AL2    = ((uint32_t)0x10000010),  /*!< Channel 2 All flag */
    DMA2_FLAG_TF2    = ((uint32_t)0x10000020),  /*!< Channel 2 Transfer Complete flag */
    DMA2_FLAG_HT2    = ((uint32_t)0x10000040),  /*!< Channel 2 Half Transfer Complete flag */
    DMA2_FLAG_TE2    = ((uint32_t)0x10000080),  /*!< Channel 2 Transfer Error flag */
    /* Only for APM32F091 devices */
    DMA2_FLAG_AL3    = ((uint32_t)0x10000100),  /*!< Channel 3 All flag */
    DMA2_FLAG_TF3    = ((uint32_t)0x10000200),  /*!< Channel 3 Transfer Complete flag */
    DMA2_FLAG_HT3    = ((uint32_t)0x10000400),  /*!< Channel 3 Half Transfer Complete flag */
    DMA2_FLAG_TE3    = ((uint32_t)0x10000800),  /*!< Channel 3 Transfer Error flag */
    /* Only for APM32F091 devices */
    DMA2_FLAG_AL4    = ((uint32_t)0x10001000),  /*!< Channel 4 All flag */
    DMA2_FLAG_TF4    = ((uint32_t)0x10002000),  /*!< Channel 4 Transfer Complete flag */
    DMA2_FLAG_HT4    = ((uint32_t)0x10004000),  /*!< Channel 4 Half Transfer Complete flag */
    DMA2_FLAG_TE4    = ((uint32_t)0x10008000),  /*!< Channel 4 Transfer Error flag */
    /* Only for APM32F091 devices */
    DMA2_FLAG_AL5    = ((uint32_t)0x10010000),  /*!< Channel 5 All flag */
    DMA2_FLAG_TF5    = ((uint32_t)0x10020000),  /*!< Channel 5 Transfer Complete flag */
    DMA2_FLAG_HT5    = ((uint32_t)0x10040000),  /*!< Channel 5 Half Transfer Complete flag */
    DMA2_FLAG_TE5    = ((uint32_t)0x10080000),  /*!< Channel 5 Transfer Error flag */
} DMA_FLAG_T;

/**
 * @brief    DMA interrupt flag definition
 */
typedef enum
{
    DMA1_INT_FLAG_AL1 = ((uint32_t)0x00000001),  /*!< Channel 1 All interrupt flag */
    DMA1_INT_FLAG_TF1 = ((uint32_t)0x00000002),  /*!< Channel 1 Transfer Complete interrupt flag */
    DMA1_INT_FLAG_HT1 = ((uint32_t)0x00000004),  /*!< Channel 1 Half Transfer Complete interrupt flag */
    DMA1_INT_FLAG_TE1 = ((uint32_t)0x00000008),  /*!< Channel 1 Transfer Error interrupt flag */

    DMA1_INT_FLAG_AL2 = ((uint32_t)0x00000010),  /*!< Channel 2 All interrupt flag */
    DMA1_INT_FLAG_TF2 = ((uint32_t)0x00000020),  /*!< Channel 2 Transfer Complete interrupt flag */
    DMA1_INT_FLAG_HT2 = ((uint32_t)0x00000040),  /*!< Channel 2 Half Transfer Complete interrupt flag */
    DMA1_INT_FLAG_TE2 = ((uint32_t)0x00000080),  /*!< Channel 2 Transfer Error interrupt flag */

    DMA1_INT_FLAG_AL3 = ((uint32_t)0x00000100),  /*!< Channel 3 All interrupt flag */
    DMA1_INT_FLAG_TF3 = ((uint32_t)0x00000200),  /*!< Channel 3 Transfer Complete interrupt flag */
    DMA1_INT_FLAG_HT3 = ((uint32_t)0x00000400),  /*!< Channel 3 Half Transfer Complete interrupt flag */
    DMA1_INT_FLAG_TE3 = ((uint32_t)0x00000800),  /*!< Channel 3 Transfer Error interrupt flag */

    DMA1_INT_FLAG_AL4 = ((uint32_t)0x00001000),  /*!< Channel 4 All interrupt flag */
    DMA1_INT_FLAG_TF4 = ((uint32_t)0x00002000),  /*!< Channel 4 Transfer Complete interrupt flag */
    DMA1_INT_FLAG_HT4 = ((uint32_t)0x00004000),  /*!< Channel 4 Half Transfer Complete interrupt flag */
    DMA1_INT_FLAG_TE4 = ((uint32_t)0x00008000),  /*!< Channel 4 Transfer Error interrupt flag */

    DMA1_INT_FLAG_AL5 = ((uint32_t)0x00010000),  /*!< Channel 5 All interrupt flag */
    DMA1_INT_FLAG_TF5 = ((uint32_t)0x00020000),  /*!< Channel 5 Transfer Complete interrupt flag */
    DMA1_INT_FLAG_HT5 = ((uint32_t)0x00040000),  /*!< Channel 5 Half Transfer Complete interrupt flag */
    DMA1_INT_FLAG_TE5 = ((uint32_t)0x00080000),  /*!< Channel 5 Transfer Error interrupt flag */
    /* Only for APM32F072 and APM32F091 devices */
    DMA1_INT_FLAG_AL6 = ((uint32_t)0x00100000),  /*!< Channel 6 All interrupt flag */
    DMA1_INT_FLAG_TF6 = ((uint32_t)0x00200000),  /*!< Channel 6 Transfer Complete interrupt flag */
    DMA1_INT_FLAG_HT6 = ((uint32_t)0x00400000),  /*!< Channel 6 Half Transfer Complete interrupt flag */
    DMA1_INT_FLAG_TE6 = ((uint32_t)0x00800000),  /*!< Channel 6 Transfer Error interrupt flag */
    /* Only for APM32F072 and APM32F091 devices */
    DMA1_INT_FLAG_AL7 = ((uint32_t)0x01000000),  /*!< Channel 7 All interrupt flag */
    DMA1_INT_FLAG_TF7 = ((uint32_t)0x02000000),  /*!< Channel 7 Transfer Complete interrupt flag */
    DMA1_INT_FLAG_HT7 = ((uint32_t)0x04000000),  /*!< Channel 7 Half Transfer Complete interrupt flag */
    DMA1_INT_FLAG_TE7 = ((uint32_t)0x08000000),  /*!< Channel 7 Transfer Error interrupt flag */
    /* Only for APM32F091 devices */
    DMA2_INT_FLAG_AL1 = ((uint32_t)0x10000001),  /*!< Channel 1 All interrupt flag */
    DMA2_INT_FLAG_TF1 = ((uint32_t)0x10000002),  /*!< Channel 1 Transfer Complete interrupt flag */
    DMA2_INT_FLAG_HT1 = ((uint32_t)0x10000004),  /*!< Channel 1 Half Transfer Complete interrupt flag */
    DMA2_INT_FLAG_TE1 = ((uint32_t)0x10000008),  /*!< Channel 1 Transfer Error interrupt flag */
    /* Only for APM32F091 devices */
    DMA2_INT_FLAG_AL2 = ((uint32_t)0x10000010),  /*!< Channel 2 All interrupt flag */
    DMA2_INT_FLAG_TF2 = ((uint32_t)0x10000020),  /*!< Channel 2 Transfer Complete interrupt flag */
    DMA2_INT_FLAG_HT2 = ((uint32_t)0x10000040),  /*!< Channel 2 Half Transfer Complete interrupt flag */
    DMA2_INT_FLAG_TE2 = ((uint32_t)0x10000080),  /*!< Channel 2 Transfer Error interrupt flag */
    /* Only for APM32F091 devices */
    DMA2_INT_FLAG_AL3 = ((uint32_t)0x10000100),  /*!< Channel 3 All interrupt flag */
    DMA2_INT_FLAG_TF3 = ((uint32_t)0x10000200),  /*!< Channel 3 Transfer Complete interrupt flag */
    DMA2_INT_FLAG_HT3 = ((uint32_t)0x10000400),  /*!< Channel 3 Half Transfer Complete interrupt flag */
    DMA2_INT_FLAG_TE3 = ((uint32_t)0x10000800),  /*!< Channel 3 Transfer Error interrupt flag */
    /* Only for APM32F091 devices */
    DMA2_INT_FLAG_AL4 = ((uint32_t)0x10001000),  /*!< Channel 4 All interrupt flag */
    DMA2_INT_FLAG_TF4 = ((uint32_t)0x10002000),  /*!< Channel 4 Transfer Complete interrupt flag */
    DMA2_INT_FLAG_HT4 = ((uint32_t)0x10004000),  /*!< Channel 4 Half Transfer Complete interrupt flag */
    DMA2_INT_FLAG_TE4 = ((uint32_t)0x10008000),  /*!< Channel 4 Transfer Error interrupt flag */
    /* Only for APM32F091 devices */
    DMA2_INT_FLAG_AL5 = ((uint32_t)0x10010000),  /*!< Channel 5 All interrupt flag */
    DMA2_INT_FLAG_TF5 = ((uint32_t)0x10020000),  /*!< Channel 5 Transfer Complete interrupt flag */
    DMA2_INT_FLAG_HT5 = ((uint32_t)0x10040000),  /*!< Channel 5 Half Transfer Complete interrupt flag */
    DMA2_INT_FLAG_TE5 = ((uint32_t)0x10080000),  /*!< Channel 5 Transfer Error interrupt flag */
} DMA_INT_FLAG_T;

/**
 * @brief   DMA interrupt source
 */
typedef enum
{
    DMA_INT_TFIE    = BIT1,  /*!< Transfer complete interrupt enable */
    DMA_INT_HTIE    = BIT2,  /*!< Half Transfer interrupt enable */
    DMA_INT_TEIE    = BIT3,  /*!< Transfer error interrupt enable */
} DMA_INT_T;

/**@} end of group DMA_Enumerations */

/** @defgroup DMA_Structures Structures
  @{
*/

/**
 * @brief   DMA Config struct definition
 */
typedef struct
{
    uint32_t                    memoryAddress;        /*!< Specifies the DMA memory base address */
    uint32_t                    peripheralAddress;    /*!< Specifies the DMA peripheral base address */
    DMA_DIR_T                   direction;            /*!< Specifies the DMA data transfer direction */
    uint32_t                    bufferSize;           /*!< Specifies the DMA buffer size */
    DMA_MEMORY_DATASIZE_T       memoryDataSize;       /*!< Specifies the DMA memory data size */
    DMA_PERIPHERAL_DATASIZE_T   peripheralDataSize;   /*!< Specifies the DMA peripheral data size */
    DMA_MEMORY_INC_T            memoryInc;            /*!< Specifies the DMA memory address increment */
    DMA_PERIPHERAL_INC_T        peripheralInc;        /*!< Specifies the DMA peripheral address increment */
    DMA_CIRCULAR_T              circular;             /*!< Specifies the DMA circular mode */
    DMA_PRIORITY_LEVEL_T        priority;             /*!< Specifies the DMA software priority */
    DMA_M2M_T                   memoryTomemory;       /*!< Specifies the DMA memory-to-memory transfer */
} DMA_Config_T;

/**@} end of group DMA_Structures */

/** @defgroup DMA_Variables Variables
  @{
*/

/**@} end of group DMA_Variables*/

/** @defgroup DMA_Functions Functions
  @{
*/

/* Reset and configuration */
void DMA_Reset(DMA_CHANNEL_T* channel);
void DMA_Config(DMA_CHANNEL_T* channel, DMA_Config_T* dmaConfig);
void DMA_ConfigStructInit(DMA_Config_T* dmaConfig);
void DMA_Enable(DMA_CHANNEL_T* channel);
void DMA_Disable(DMA_CHANNEL_T* channel);

/* Data number */
void DMA_SetDataNumber(DMA_CHANNEL_T* channel, uint32_t dataNumber);
uint32_t DMA_ReadDataNumber(DMA_CHANNEL_T* channel);

/* Channel remap (Only for APM32F091 devices) */
void DMA_ConfigRemap(DMA_T* dma, DMA_CHANNEL_REMAP_T remap);

/* interrupt */
void DMA_EnableInterrupt(DMA_CHANNEL_T* channel, uint32_t interrupt);
void DMA_DisableInterrupt(DMA_CHANNEL_T* channel, uint32_t interrupt);

/* Flag */
uint8_t DMA_ReadStatusFlag(DMA_FLAG_T flag);
void DMA_ClearStatusFlag(uint32_t flag);
uint8_t DMA_ReadIntFlag(DMA_INT_FLAG_T flag);
void DMA_ClearIntFlag(uint32_t flag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_DMA_H */

/**@} end of group DMA_Functions */
/**@} end of group DMA_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
