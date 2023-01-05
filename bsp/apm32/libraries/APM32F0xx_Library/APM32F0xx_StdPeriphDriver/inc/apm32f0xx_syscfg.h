/*!
 * @file        apm32f0xx_syscfg.h
 *
 * @brief       This file contains all the functions prototypes for the SYSCFG firmware library
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

#ifndef __APM32F0XX_SYSCFG_H
#define __APM32F0XX_SYSCFG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup SYSCFG_Driver SYSCFG Driver
  @{
*/

/** @defgroup SYSCFG_Macros Macros
  @{
*/

/** Macros description */
#define SYSCFG_CFG1_MEMMODE      ((uint32_t)0x00000003);   /*!< SYSCFG_Memory Remap Config */

/**@} end of group SYSCFG_Macros*/

/** @defgroup SYSCFG_Enumerations Enumerations
  @{
*/

/**
 * @brief   SYSCFG EINT Port Sources
 */
typedef enum
{
    SYSCFG_PORT_GPIOA   = ((uint8_t)0x00),   /*!< Port Source GPIOA */
    SYSCFG_PORT_GPIOB   = ((uint8_t)0x01),   /*!< Port Source GPIOB */
    SYSCFG_PORT_GPIOC   = ((uint8_t)0x02),   /*!< Port Source GPIOC */
    SYSCFG_PORT_GPIOD   = ((uint8_t)0x03),   /*!< Port Source GPIOD */
    SYSCFG_PORT_GPIOE   = ((uint8_t)0x04),   /*!< Port Source GPIOE (only for APM32F072 and APM32F091 devices) */
    SYSCFG_PORT_GPIOF   = ((uint8_t)0x05),   /*!< Port Source GPIOF */
} SYSCFG_PORT_T;

/**
 * @brief   SYSCFG EINT Pin Sources
 */
typedef enum
{
    SYSCFG_PIN_0    = ((uint8_t)0x00),       /*!< Pin Source 0 */
    SYSCFG_PIN_1    = ((uint8_t)0x01),       /*!< Pin Source 1 */
    SYSCFG_PIN_2    = ((uint8_t)0x02),       /*!< Pin Source 2 */
    SYSCFG_PIN_3    = ((uint8_t)0x03),       /*!< Pin Source 3 */
    SYSCFG_PIN_4    = ((uint8_t)0x04),       /*!< Pin Source 4 */
    SYSCFG_PIN_5    = ((uint8_t)0x05),       /*!< Pin Source 5 */
    SYSCFG_PIN_6    = ((uint8_t)0x06),       /*!< Pin Source 6 */
    SYSCFG_PIN_7    = ((uint8_t)0x07),       /*!< Pin Source 7 */
    SYSCFG_PIN_8    = ((uint8_t)0x08),       /*!< Pin Source 8 */
    SYSCFG_PIN_9    = ((uint8_t)0x09),       /*!< Pin Source 9 */
    SYSCFG_PIN_10   = ((uint8_t)0x0A),       /*!< Pin Source 10 */
    SYSCFG_PIN_11   = ((uint8_t)0x0B),       /*!< Pin Source 11 */
    SYSCFG_PIN_12   = ((uint8_t)0x0C),       /*!< Pin Source 12 */
    SYSCFG_PIN_13   = ((uint8_t)0x0D),       /*!< Pin Source 13 */
    SYSCFG_PIN_14   = ((uint8_t)0x0E),       /*!< Pin Source 14 */
    SYSCFG_PIN_15   = ((uint8_t)0x0F),       /*!< Pin Source 15 */
} SYSCFG_PIN_T;

/**
 * @brief   SYSCFG Memory Remap Config
 */
typedef enum
{
    SYSCFG_MEMORY_REMAP_FMC     = ((uint8_t)0x00),         /*!< SYSCFG MemoryRemap Flash */
    SYSCFG_MEMORY_REMAP_SYSTEM  = ((uint8_t)0x01),         /*!< SYSCFG MemoryRemap SystemMemory */
    SYSCFG_MEMORY_REMAP_SRAM    = ((uint8_t)0x03),         /*!< SYSCFG MemoryRemap SRAM */
} SYSCFG_MEMORY_REMAP_T;

/**
 * @brief   SYSCFG DMA Remap Config
 */
typedef enum
{
    SYSCFG_DAM_REMAP_ADC       = ((uint32_t)0x00000100),   /*!< ADC DMA remap */
    SYSCFG_DAM_REMAP_USART1TX  = ((uint32_t)0x00000200),   /*!< USART1 TX DMA remap */
    SYSCFG_DAM_REMAP_USART1RX  = ((uint32_t)0x00000400),   /*!< USART1 RX DMA remap */
    SYSCFG_DAM_REMAP_TMR16     = ((uint32_t)0x00000800),   /*!< Timer 16 DMA remap */
    SYSCFG_DAM_REMAP_TMR17     = ((uint32_t)0x00001000),   /*!< Timer 17 DMA remap */
    SYSCFG_DAM_REMAP_TMR16_2   = ((uint32_t)0x00002000),   /*!< Timer 16 DMA remap2(only for APM32F072) */
    SYSCFG_DAM_REMAP_TMR17_2   = ((uint32_t)0x00004000),   /*!< Timer 17 DMA remap2(only for APM32F072) */
    SYSCFG_DAM_REMAP_SPI2      = ((uint32_t)0x01000000),   /*!< SPI2 DMA remap(only for APM32F072) */
    SYSCFG_DAM_REMAP_USART2    = ((uint32_t)0x02000000),   /*!< USART2 DMA remap(only for APM32F072) */
    SYSCFG_DAM_REMAP_USART3    = ((uint32_t)0x04000000),   /*!< USART3 DMA remap(only for APM32F072) */
    SYSCFG_DAM_REMAP_I2C1      = ((uint32_t)0x08000000),   /*!< I2C1 DMA remap(only for APM32F072) */
    SYSCFG_DAM_REMAP_TMR1      = ((uint32_t)0x10000000),   /*!< TMR1 DMA remap(only for APM32F072) */
    SYSCFG_DAM_REMAP_TMR2      = ((uint32_t)0x20000000),   /*!< TMR2 DMA remap(only for APM32F072) */
    SYSCFG_DAM_REMAP_TMR3      = ((uint32_t)0x40000000),   /*!< TMR3 DMA remap(only for APM32F072) */
} SYSCFG_DAM_REMAP_T;

/**
 * @brief   SYSCFG I2C FastModePlus Config
 */
typedef enum
{
    SYSCFG_I2C_FMP_PB6       = ((uint32_t)0x00010000),     /*!< I2C PB6 Fast mode plus */
    SYSCFG_I2C_FMP_PB7       = ((uint32_t)0x00020000),     /*!< I2C PB7 Fast mode plus */
    SYSCFG_I2C_FMP_PB8       = ((uint32_t)0x00040000),     /*!< I2C PB8 Fast mode plus */
    SYSCFG_I2C_FMP_PB9       = ((uint32_t)0x00080000),     /*!< I2C PB9 Fast mode plus */
    SYSCFG_I2C_FMP_I2C1      = ((uint32_t)0x00100000),     /*!< Enable Fast Mode Plus on PB10, PB11, PF6 and PF7(only for APM32F030) */
    SYSCFG_I2C_FMP_I2C2      = ((uint32_t)0x00200000),     /*!< Enable Fast Mode Plus on I2C2 pins(only for APM32F072 and APM32F091) */
    SYSCFG_I2C_FMP_PA9       = ((uint32_t)0x00400000),     /*!< I2C PA9 Fast mode plus(only for APM32F030 and APM32F091) */
    SYSCFG_I2C_FMP_PA10      = ((uint32_t)0x00800000),     /*!< I2C PA10 Fast mode plus(only for APM32F030 and APM32F091) */
} SYSCFG_I2C_FMP_T;

/**
 * @brief   SYSCFG Lock Config
 */
typedef enum
{
    SYSCFG_LOCK_LOCKUP     = ((uint32_t)0x00000001),       /*!< Cortex-M0 LOCKUP bit enable */
    SYSCFG_LOCK_SRAM       = ((uint32_t)0x00000002),       /*!< SRAM parity lock bit */
    SYSCFG_LOCK_PVD        = ((uint32_t)0x00000004),       /*!< PVD lock enable bit, not available for APM32F030 devices */
} SYSCFG_LOCK_T;

/**
 * @brief   IRDA ENV SOURCE
 */
typedef enum
{
    SYSCFG_IRDA_ENV_TMR16      = ((uint32_t)0x000000C0),   /*!< Timer16 as IRDA Modulation envelope source */
    SYSCFG_IRDA_ENV_USART1     = ((uint32_t)0x00000040),   /*!< USART1 as IRDA Modulation envelope source */
    SYSCFG_IRDA_ENV_USART4     = ((uint32_t)0x00000080),   /*!< USART4 as IRDA Modulation envelope source */
} SYSCFG_IRDA_ENV_T;

/**
 * @brief   SYSCFG flag
 */
typedef enum
{
    SYSCFG_CFG2_SRAMPEF     = ((uint32_t)0x00000100),      /*!< SRAM Parity error flag */
} SYSCFG_FLAG_T;

/**@} end of group SYSCFG_Enumerations*/

/** @defgroup SYSCFG_Structures Structures
  @{
*/

/**@} end of group SYSCFG_Structures */

/** @defgroup SYSCFG_Variables Variables
  @{
*/

/**@} end of group SYSCFG_Variables */

/** @defgroup SYSCFG_Functions Functions
  @{
*/
/* Reset */
void SYSCFG_Reset(void);

/* Memory Remap selects */
void SYSCFG_MemoryRemapSelect(uint8_t memory);

/* DMA Channel Remap */
void SYSCFG_EnableDMAChannelRemap(uint32_t channel);
void SYSCFG_DisableDMAChannelRemap(uint32_t channel);

/* I2C Fast Mode Plus */
void SYSCFG_EnableI2CFastModePlus(uint32_t pin);
void SYSCFG_DisableI2CFastModePlus(uint32_t pin);

/* IRDA Envelope */
void SYSCFG_SelectIRDAEnv(SYSCFG_IRDA_ENV_T IRDAEnv);

/* Eint Line */
void SYSCFG_EINTLine(SYSCFG_PORT_T port, SYSCFG_PIN_T pin);

/* Break lock */
void SYSCFG_BreakLock(uint32_t lock);

/* Flag */
uint8_t SYSCFG_ReadStatusFlag(uint32_t flag);
void SYSCFG_ClearStatusFlag(uint8_t flag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_SYSCFG_H */

/**@} end of group SYSCFG_Functions */
/**@} end of group SYSCFG_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */

