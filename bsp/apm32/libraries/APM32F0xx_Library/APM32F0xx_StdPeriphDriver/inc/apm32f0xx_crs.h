/*!
 * @file        apm32f0xx_crs.h
 *
 * @brief       This file contains all the functions prototypes for the CRS firmware library
 *
 * @note        It's only for APM32F072 and APM32F091 devices
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
#ifndef __APM32F0XX_CRS_H
#define __APM32F0XX_CRS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup CRS_Driver
  @{
*/

/** @defgroup CRS_Macros Macros
  @{
*/

/**@} end of group CRS_Macros */

/** @defgroup CRS_Enumerations Enumerations
  @{
*/

/**
 * @brief    CRS_Interrupt_Sources
 */
typedef enum
{
    CRS_INT_SYNCOK    = ((uint32_t)0x00000001),  /*!<SYNC event OK interrupt */
    CRS_INT_SYNCWARN  = ((uint32_t)0x00000002),  /*!<SYNC warning interrupt */
    CRS_INT_ERR       = ((uint32_t)0x00000004),  /*!<Synchronization or trimming error interrupt */
    CRS_INT_ESYNC     = ((uint32_t)0x00000008),  /*!<Expected SYNC interrupt */
    CRS_INT_SYNCERR   = ((uint32_t)0x00000100),  /*!<SYNC error */
    CRS_INT_SYNCMISS  = ((uint32_t)0x00000200),  /*!<SYNC missed */
    CRS_INT_TRIMOVF   = ((uint32_t)0x00000400),  /*!<Trimming overflow or underflow */
} CRS_INT_T;

/**
 * @brief    CRS_Flags
 */
typedef enum
{
    CRS_FLAG_SYNCOK    = ((uint32_t)0x00000001),  /*!<SYNC event OK flag */
    CRS_FLAG_SYNCWARN  = ((uint32_t)0x00000002),  /*!<SYNC warning flag */
    CRS_FLAG_ERR       = ((uint32_t)0x00000004),  /*!<Synchronization or trimming error flag */
    CRS_FLAG_ESYNC     = ((uint32_t)0x00000008),  /*!<Expected SYNC flag */
    CRS_FLAG_SYNCERR   = ((uint32_t)0x00000100),  /*!<SYNC error flag */
    CRS_FLAG_SYNCMISS  = ((uint32_t)0x00000200),  /*!<SYNC missed flag */
    CRS_FLAG_TRIMOVF   = ((uint32_t)0x00000400),  /*!<Trimming overflow or underflow falg */
} CRS_FLAG_T;

/**
 * @brief    CRS_Synchro_Source
 */
typedef enum
{
    CRS_SYNC_SOURCE_GPIO =  0x00, /*!<GPIO selected as SYNC signal source */
    CRS_SYNC_SOURCE_LSE  =  0x01, /*!<LSE selected as SYNC signal source */
    CRS_SYNC_SOURCE_USB  =  0x02, /*!<USB SNFLG selected as SYNC signal source (default) */
} CRS_SYNC_SOURCE_T;

/**
 * @brief    CRS_Synchro_Source
 */
typedef enum
{
    CRS_SYNC_DIV1   =  0x00, /*!<Synchro Signal not divided (default) */
    CRS_SYNC_DIV2   =  0x01, /*!<Synchro Signal divided by 2 */
    CRS_SYNC_DIV4   =  0x02, /*!<Synchro Signal divided by 4 */
    CRS_SYNC_DIV8   =  0x03, /*!<Synchro Signal divided by 8 */
    CRS_SYNC_DIV16  =  0x04, /*!<Synchro Signal divided by 16 */
    CRS_SYNC_DIV32  =  0x05, /*!<Synchro Signal divided by 32 */
    CRS_SYNC_DIV64  =  0x06, /*!<Synchro Signal divided by 64 */
    CRS_SYNC_DIV128 =  0x07, /*!<Synchro Signal divided by 128 */
} CRS_SYNC_DIV_T;

/**@} end of group CRS_Enumerations */

/** @defgroup CRS_Structures Structures
  @{
*/

/**
 * @brief    CRS_SynchroPolarity
 */
typedef enum
{
    CRS_SYNC_POL_RISING, /*!<Synchro active on rising edge */
    CRS_SYNC_POL_FALLING /*!<Synchro active on falling edge */
} CRS_SYNC_POL_T;

/**@} end of group CRS_Structures */

/** @defgroup CRS_Variables Variables
  @{
*/

/**@} end of group CRS_Variables */

/** @defgroup CRS_Functions Functions
  @{
*/

/* Configuration of the CRS */
void CRS_Reset(void);
void CRS_AdjustHSI48CalibrationValue(uint8_t calibrationVal);
void CRS_EnableFrequencyErrorCounter(void);
void CRS_DisableFrequencyErrorCounter(void);
void CRS_EnableAutomaticCalibration(void);
void CRS_DisableAutomaticCalibration(void);
void CRS_GenerateSoftwareSynchronization(void);
void CRS_FrequencyErrorCounterReloadValue(uint16_t reloadVal);
void CRS_ConfigFrequencyErrorLimit(uint8_t errLimitVal);
void CRS_ConfigSynchronizationPrescaler(CRS_SYNC_DIV_T div);
void CRS_ConfigSynchronizationSource(CRS_SYNC_SOURCE_T source);
void CRS_ConfigSynchronizationPolarity(CRS_SYNC_POL_T polarity);
uint32_t CRS_ReadReloadValue(void);
uint32_t CRS_ReadHSI48CalibrationValue(void);
uint32_t CRS_ReadFrequencyErrorValue(void);
uint32_t CRS_ReadFrequencyErrorDirection(void);

/* Interrupts and flags management functions */
void CRS_EnableInterrupt(CRS_INT_T interrupt);
void CRS_DisableInterrupt(CRS_INT_T interrupt);
uint8_t CRS_ReadStatusFlag(CRS_FLAG_T flag);
void CRS_ClearStatusFlag(CRS_FLAG_T flag);
uint8_t CRS_ReadIntFlag(CRS_INT_T flag);
void CRS_ClearIntFlag(CRS_INT_T intFlag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_CRS_H */

/**@} end of group CRS_Functions */
/**@} end of group CRS_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
