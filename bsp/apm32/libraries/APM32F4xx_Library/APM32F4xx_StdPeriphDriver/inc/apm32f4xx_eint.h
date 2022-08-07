/*!
 * @file        apm32f4xx_eint.h
 *
 * @brief       This file contains all the functions prototypes for the EINT firmware library.
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
#ifndef __APM32F4XX_EINT_H
#define __APM32F4XX_EINT_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup EINT_Driver
  @{
*/

/** @defgroup EINT_Enumerations
  @{
*/

/**
 * @brief EINT mode enumeration
 */
typedef enum
{
    EINT_MODE_INTERRUPT = 0x00, /*!< Interrupt request mode */
    EINT_MODE_EVENT     = 0x04  /*!< Event request mode */
} EINT_MODE_T;

/**
 * @brief EINT Trigger enumeration
 */
typedef enum
{
    EINT_TRIGGER_RISING         = 0x08, /*!< Rising trigger */
    EINT_TRIGGER_FALLING        = 0x0C, /*!< Falling trigger */
    EINT_TRIGGER_RISING_FALLING = 0x10  /*!< Rising and falling trigger */
} EINT_TRIGGER_T;

typedef enum
{
    EINT_LINENONE = 0x00000,      /*!< No interrupt selected */
    EINT_LINE_0   = 0x00001,      /*!< External interrupt line 0 */
    EINT_LINE_1   = 0x00002,      /*!< External interrupt line 1 */
    EINT_LINE_2   = 0x00004,      /*!< External interrupt line 2 */
    EINT_LINE_3   = 0x00008,      /*!< External interrupt line 3 */
    EINT_LINE_4   = 0x00010,      /*!< External interrupt line 4 */
    EINT_LINE_5   = 0x00020,      /*!< External interrupt line 5 */
    EINT_LINE_6   = 0x00040,      /*!< External interrupt line 6 */
    EINT_LINE_7   = 0x00080,      /*!< External interrupt line 7 */
    EINT_LINE_8   = 0x00100,      /*!< External interrupt line 8 */
    EINT_LINE_9   = 0x00200,      /*!< External interrupt line 9 */
    EINT_LINE_10  = 0x00400,      /*!< External interrupt line 10 */
    EINT_LINE_11  = 0x00800,      /*!< External interrupt line 11 */
    EINT_LINE_12  = 0x01000,      /*!< External interrupt line 12 */
    EINT_LINE_13  = 0x02000,      /*!< External interrupt line 13 */
    EINT_LINE_14  = 0x04000,      /*!< External interrupt line 14 */
    EINT_LINE_15  = 0x08000,      /*!< External interrupt line 15 */
    EINT_LINE_16  = 0x10000,      /*!< External interrupt line 16 Connected to the PVD Output */
    EINT_LINE_17  = 0x20000,      /*!< External interrupt line 17 Connected to the RTC Alarm event */
    EINT_LINE_18  = 0x40000,      /*!< External interrupt line 18 Connected to the USB Device */
    EINT_LINE_19  = 0x80000,      /*!< External interrupt line 19 Connected to the Ethernet Wakeup event */
    EINT_LINE_20  = 0x00100000,   /*!< External interrupt line 20 Connected to the USB OTG HS (configured in FS) */
    EINT_LINE_21  = 0x00200000,   /*!< External interrupt line 21 Connected to the RTC Tamper and Time Stamp even */
    EINT_LINE_22  = 0x00400000,   /*!< External interrupt line 22 Connected to the RTC Wakeup event */
} EINT_LINE_T;

/**@} end of group EINT_Enumerations*/

/** @addtogroup EINT_Structure Data Structure
  @{
*/

/**
 * @brief    EINT Config structure definition
 */
typedef struct
{
    EINT_LINE_T     line;       /*!< External interrupt line selection */
    EINT_MODE_T     mode;       /*!< External interrupt or event mode selection */
    EINT_TRIGGER_T  trigger;    /*!< External trigger mode */
    uint8_t         lineCmd;    /*!< External interrupt line command */
} EINT_Config_T;

/**@} end of group EINT_Structure*/

/** @defgroup EINT_Functions
  @{
*/

/* Reset and configuration */
void EINT_Reset(void);
void EINT_Config( EINT_Config_T* eintConfig);
void EINT_ConfigStructInit(EINT_Config_T* eintConfig);

/* Interrupt and flag */
void EINT_SelectSWInterrupt(uint32_t line);
uint8_t EINT_ReadStatusFlag(EINT_LINE_T line);
void EINT_ClearStatusFlag(uint32_t line);
uint8_t EINT_ReadIntFlag(EINT_LINE_T line);
void EINT_ClearIntFlag(uint32_t line);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F4XX_EINT_H */

/**@} end of group EINT_Enumerations */
/**@} end of group EINT_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
