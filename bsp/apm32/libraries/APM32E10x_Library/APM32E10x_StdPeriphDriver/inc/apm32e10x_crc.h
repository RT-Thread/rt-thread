/*!
 * @file       apm32e10x_crc.h
 *
 * @brief      This file contains all the functions prototypes for the CRC firmware library
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
#ifndef __APM32E10X_CRC_H
#define __APM32E10X_CRC_H

/* Includes */
#include "apm32e10x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup APM32E10x_StdPeriphDriver
  @{
*/

/** @addtogroup CRC_Driver
  @{
*/

/** @defgroup CRC_Functions Functions
  @{
*/

/* Reset DATA */
void CRC_ResetDATA(void);

/* Operation functions */
uint32_t CRC_CalculateCRC(uint32_t data);
uint32_t CRC_CalculateBlockCRC(uint32_t *buf, uint32_t bufLen);
uint32_t CRC_ReadCRC(void);
void CRC_WriteIDRegister(uint8_t inData);
uint8_t CRC_ReadIDRegister(void);

/**@} end of group CRC_Functions*/
/**@} end of group CRC_Driver */
/**@} end of group APM32E10x_StdPeriphDriver */

#ifdef __cplusplus
}
#endif

#endif /* __APM32E10X_CRC_H */
