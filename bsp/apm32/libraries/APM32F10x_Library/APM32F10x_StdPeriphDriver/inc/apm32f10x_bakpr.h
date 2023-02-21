/*!
 * @file        apm32f10x_bakr.h
 *
 * @brief       This file contains all the functions prototypes for the BAKPR firmware library.
 *
 * @version     V1.0.4
 *
 * @date        2022-12-01
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

#ifndef __APM32F10X_BAKPR_H
#define __APM32F10X_BAKPR_H

/* Includes */
#include "apm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup APM32F10x_StdPeriphDriver
  @{
*/

/** @addtogroup BAKPR_Driver BAKPR Driver
  @{
*/

/** @defgroup BAKPR_Enumerations Enumerations
  @{
*/

/**
 * @brief BAKPR TAMPER Pin Active Level
 */
typedef enum
{
    BAKPR_TAMPER_PIN_LEVEL_HIGH,
    BAKPR_TAMPER_PIN_LEVEL_LOW
} BAKPR_TAMPER_PIN_LEVEL_T;

/**
 * @brief BAKPR RTC output source
 */
typedef enum
{
    BAKPR_RTC_OUTPUT_SOURCE_NONE,
    BAKPR_RTC_OUTPUT_SOURCE_CALIBRATION_CLOCK,
    BAKPR_RTC_OUTPUT_SOURCE_ALARM,
    BAKPR_RTC_OUTPUT_SOURCE_SECOND
} BAKPR_RTC_OUTPUT_SOURCE_T;

/**
 * @brief BAKPR DATA register Addr
 */
typedef enum
{
    BAKPR_DATA1  = ((uint16_t)0x0004),
    BAKPR_DATA2  = ((uint16_t)0x0008),
    BAKPR_DATA3  = ((uint16_t)0x000C),
    BAKPR_DATA4  = ((uint16_t)0x0010),
    BAKPR_DATA5  = ((uint16_t)0x0014),
    BAKPR_DATA6  = ((uint16_t)0x0018),
    BAKPR_DATA7  = ((uint16_t)0x001C),
    BAKPR_DATA8  = ((uint16_t)0x0020),
    BAKPR_DATA9  = ((uint16_t)0x0024),
    BAKPR_DATA10 = ((uint16_t)0x0028),
    BAKPR_DATA11 = ((uint16_t)0x0040),
    BAKPR_DATA12 = ((uint16_t)0x0044),
    BAKPR_DATA13 = ((uint16_t)0x0048),
    BAKPR_DATA14 = ((uint16_t)0x004C),
    BAKPR_DATA15 = ((uint16_t)0x0050),
    BAKPR_DATA16 = ((uint16_t)0x0054),
    BAKPR_DATA17 = ((uint16_t)0x0058),
    BAKPR_DATA18 = ((uint16_t)0x005C),
    BAKPR_DATA19 = ((uint16_t)0x0060),
    BAKPR_DATA20 = ((uint16_t)0x0064),
    BAKPR_DATA21 = ((uint16_t)0x0068),
    BAKPR_DATA22 = ((uint16_t)0x006C),
    BAKPR_DATA23 = ((uint16_t)0x0070),
    BAKPR_DATA24 = ((uint16_t)0x0074),
    BAKPR_DATA25 = ((uint16_t)0x0078),
    BAKPR_DATA26 = ((uint16_t)0x007C),
    BAKPR_DATA27 = ((uint16_t)0x0080),
    BAKPR_DATA28 = ((uint16_t)0x0084),
    BAKPR_DATA29 = ((uint16_t)0x0088),
    BAKPR_DATA30 = ((uint16_t)0x008C),
    BAKPR_DATA31 = ((uint16_t)0x0090),
    BAKPR_DATA32 = ((uint16_t)0x0094),
    BAKPR_DATA33 = ((uint16_t)0x0098),
    BAKPR_DATA34 = ((uint16_t)0x009C),
    BAKPR_DATA35 = ((uint16_t)0x00A0),
    BAKPR_DATA36 = ((uint16_t)0x00A4),
    BAKPR_DATA37 = ((uint16_t)0x00A8),
    BAKPR_DATA38 = ((uint16_t)0x00AC),
    BAKPR_DATA39 = ((uint16_t)0x00B0),
    BAKPR_DATA40 = ((uint16_t)0x00B4),
    BAKPR_DATA41 = ((uint16_t)0x00B8),
    BAKPR_DATA42 = ((uint16_t)0x00BC)
} BAKPR_DATA_T;

/**@} end of group BAKPR_Enumerations*/


/** @defgroup BAKPR_Functions Functions
  @{
*/

/* BAKPR reset and configuration */
void BAKPR_Reset(void);
void BAKPR_ConfigTamperPinLevel(BAKPR_TAMPER_PIN_LEVEL_T value);
void BAKPR_EnableTamperPin(void);
void BAKPR_DisableTamperPin(void);
void BAKPR_ConfigRTCOutput(BAKPR_RTC_OUTPUT_SOURCE_T soure);
void BAKPR_ConfigRTCCalibrationValue(uint8_t calibrationValue);
void BAKPR_ConfigBackupRegister(BAKPR_DATA_T bakrData, uint16_t data);
uint16_t BAKPR_ReadBackupRegister(BAKPR_DATA_T bakrData);

/* Interrupts and flags */
void BAKPR_EnableInterrupt(void);
void BAKPR_DisableInterrupt(void);
uint8_t BAKPR_ReadStatusFlag(void);
void BAKPR_ClearStatusFlag(void);
uint8_t BAKPR_ReadIntFlag(void);
void BAKPR_ClearIntFlag(void);

/**@} end of group BAKPR_Functions*/
/**@} end of group BAKPR_Driver */
/**@} end of group APM32F10x_StdPeriphDriver */

#ifdef __cplusplus
}
#endif

#endif /* __APM32F10X_BAKPR_H */
