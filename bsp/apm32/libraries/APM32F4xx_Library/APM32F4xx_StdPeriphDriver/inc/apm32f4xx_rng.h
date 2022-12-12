/*!
 * @file        apm32f4xx_rng.h
 *
 * @brief       This file contains all the functions prototypes for the Random Number Generator(RNG) firmware library.
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
#ifndef __APM32F4XX_RNG_H
#define __APM32F4XX_RNG_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup RNG_Driver
  @{
*/

/** @defgroup RNG_Enumerations
  @{
*/

/**
 * @brief RNG flags definition
 */
typedef enum
{
    RNG_FLAG_DATARDY    = (uint8_t)BIT0, /*!< Data ready flag */
    RNG_FLAG_CLKERCSTS  = (uint8_t)BIT1, /*!< RNG clock error flag */
    RNG_FLAG_FSCSTS     = (uint8_t)BIT2, /*!< Faulty sequence flag */
}RNG_FLAG_T;

/**
 * @brief RNG interrupts definition
 */
 typedef enum
{
    RNG_INT_FLAG_CLKERINT  = (uint8_t)BIT5, /*!< RNG clock Error interrupt */
    RNG_INT_FLAG_FSINT     = (uint8_t)BIT6, /*!< Faulty Sequence Interrupt */
}RNG_INT_FLAG_T;

/**@} end of group RNG_Enumerations*/

/** @defgroup RNG_Functions
  @{
*/

/* RNG Reset and Configuration */
void RNG_Reset(void);
void RNG_Enable(void);
void RNG_Disable(void);

/* Get 32 bit Random number */
uint32_t RNG_ReadRandomNumber(void);

/* Interrupts and flags */
void EnableInterrupt(void);
void DisableInterrupt(void);
uint8_t RNG_ReadStatusFlag(RNG_FLAG_T flag);
void RNG_ClearStatusFlag(uint8_t flag);
uint8_t RNG_ReadIntFlag(RNG_INT_FLAG_T flag);
void RNG_ClearIntFlag(uint8_t flag);

#ifdef __cplusplus
}
#endif

#endif /*__APM32F4XX_RNG_H */

/**@} end of group RNG_Enumerations */
/**@} end of group RNG_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
