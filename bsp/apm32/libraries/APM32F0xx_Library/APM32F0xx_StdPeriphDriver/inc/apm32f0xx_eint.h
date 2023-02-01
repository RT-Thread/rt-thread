/*!
 * @file        apm32f0xx_eint.h
 *
 * @brief       This file contains all the functions prototypes for the EINT firmware library
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
#ifndef __APM32F0XX_EINT_H
#define __APM32F0XX_EINT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
  */

/** @addtogroup EINT_Driver
  @{
  */

/** @defgroup EINT_Macros Macros
  @{
  */

/* No interrupt selected */
#define EINT_LINENONE                  ((uint32_t)0x00000)       /*!< clear EINT line config */

/* EINT register reset value */
#if defined (APM32F030) || defined (APM32F051)
#define EINT_INTMASK_RESET_VALUE       ((uint32_t)(0x0F940000))
#elif defined (APM32F091) || defined (APM32F072) || defined (APM32F071) || defined (APM32F070)
#define EINT_INTMASK_RESET_VALUE       ((uint32_t)(0x7F840000))
#endif
#define EINT_EVTMASK_RESET_VALUE       ((uint32_t)(0x00000000))  /*!< EINT Event MASK register reset value */
#define EINT_RTSEL_RESET_VALUE         ((uint32_t)(0x00000000))  /*!< EINT Rising Trigger enable register reset value */
#define EINT_FTSEL_RESET_VALUE         ((uint32_t)(0x00000000))  /*!< EINT Falling Trigger enable register reset value */
#define EINT_PEND_RESET_VALUE          ((uint32_t)(0x00000000))  /*!< EINT Interrupt Pending register reset value */

/**@} end of group EINT_Macros */

/** @defgroup EINT_Enumerations Enumerations
  @{
  */

/*!
 * @brief   EINT mode
 */
typedef enum
{
    EINT_MODE_INTERRUPT    = ((uint8_t)0x00), /*!< EINT mode select interrupt */
    EINT_MODE_EVENT        = ((uint8_t)0x01), /*!< EINT mode select event */
} EINT_MODE_T;

/*!
 * @brief   EINT trigger mode
 */
typedef enum
{
    EINT_TRIGGER_RISING    = ((uint8_t)0x00), /*!< EINT trigger select rising edge */
    EINT_TRIGGER_FALLING   = ((uint8_t)0x01), /*!< EINT trigger select falling edge */
    EINT_TRIGGER_ALL       = ((uint8_t)0x02), /*!< EINT trigger select rising and falling edge */
} EINT_TRIGGER_T;

/*!
 * @brief   EINT line
 */
typedef enum
{
    EINT_LINE0   = ((uint32_t)0x00000001),  /*!< External interrupt line 0 */
    EINT_LINE1   = ((uint32_t)0x00000002),  /*!< External interrupt line 1 */
    EINT_LINE2   = ((uint32_t)0x00000004),  /*!< External interrupt line 2 */
    EINT_LINE3   = ((uint32_t)0x00000008),  /*!< External interrupt line 3 */
    EINT_LINE4   = ((uint32_t)0x00000010),  /*!< External interrupt line 4 */
    EINT_LINE5   = ((uint32_t)0x00000020),  /*!< External interrupt line 5 */
    EINT_LINE6   = ((uint32_t)0x00000040),  /*!< External interrupt line 6 */
    EINT_LINE7   = ((uint32_t)0x00000080),  /*!< External interrupt line 7 */
    EINT_LINE8   = ((uint32_t)0x00000100),  /*!< External interrupt line 8 */
    EINT_LINE9   = ((uint32_t)0x00000200),  /*!< External interrupt line 9 */
    EINT_LINE10  = ((uint32_t)0x00000400),  /*!< External interrupt line 10 */
    EINT_LINE11  = ((uint32_t)0x00000800),  /*!< External interrupt line 11 */
    EINT_LINE12  = ((uint32_t)0x00001000),  /*!< External interrupt line 12 */
    EINT_LINE13  = ((uint32_t)0x00002000),  /*!< External interrupt line 13 */
    EINT_LINE14  = ((uint32_t)0x00004000),  /*!< External interrupt line 14 */
    EINT_LINE15  = ((uint32_t)0x00008000),  /*!< External interrupt line 15 */
    EINT_LINE16  = ((uint32_t)0x00010000),  /*!< External interrupt line 16 Connected to the PVD Output, not applicable for 030 */
    EINT_LINE17  = ((uint32_t)0x00020000),  /*!< External interrupt line 17 Connected to the RTC Alarm event */
    EINT_LINE18  = ((uint32_t)0x00040000),  /*!< External interrupt line 18 Connected to the RTC Alarm event, only applicable for 072 devices */
    EINT_LINE19  = ((uint32_t)0x00080000),  /*!< External interrupt line 19 Connected to the RTC Tamper and TimeStamp events */
    EINT_LINE20  = ((uint32_t)0x00100000),  /*!< External interrupt line 20 Connected to the RTC wakeup event,only applicable for 072 and 091 */
    EINT_LINE21  = ((uint32_t)0x00200000),  /*!< External interrupt line 21 Connected to the Comparator 1 event,only applicable for 072 and 091 */
    EINT_LINE22  = ((uint32_t)0x00400000),  /*!< External interrupt line 22 Connected to the Comparator 2 event,only applicable for 072 and 091 */
    EINT_LINE23  = ((uint32_t)0x00800000),  /*!< External interrupt line 23 Connected to the I2C1 wakeup event,not applicable for 030 */
    EINT_LINE25  = ((uint32_t)0x02000000),  /*!< External interrupt line 25 Connected to the USART1 wakeup event,not applicable for 030 */
    EINT_LINE26  = ((uint32_t)0x04000000),  /*!< External interrupt line 26 Connected to the USART2 wakeup event,only applicable for 072 and 091 */
    EINT_LINE27  = ((uint32_t)0x08000000),  /*!< External interrupt line 27 Connected to the CEC wakeup event,only applicable for 072*/
    EINT_LINE28  = ((uint32_t)0x10000000),  /*!< External interrupt line 28 Connected to the USART3 wakeup event,only applicable for 091 */
    EINT_LINE31  = ((int)0x80000000),       /*!< External interrupt line 31 Connected to the VDD USB monitor,only applicable for 072 */
} EINT_LINE_T;

/**@} end of group EINT_Enumerations */

/** @defgroup EINT_Structures Structures
  @{
  */

/*!
 * @brief   EINT Config struct definition
 */
typedef struct
{
    uint32_t        line;        /*!< Specifies the new state of the selected EINT lines. */
    EINT_MODE_T     mode;        /*!< Specifies the mode for the EINT lines. */
    EINT_TRIGGER_T  trigger;     /*!< Specifies the trigger signal active edge for the EINT lines. */
    uint8_t         lineCmd;     /*!< Specifies the EINT lines to be enabled or disabled. */
} EINT_Config_T;

/**@} end of group EINT_Structures */

/** @defgroup EINT_Variables Variables
  @{
  */

/**@} end of group EINT_Variables */

/** @defgroup EINT_Functions Functions
  @{
  */

/* Reset and configuration */
void EINT_Reset(void);
void EINT_Config(EINT_Config_T* eintConfig);
void EINT_ConfigStructInit(EINT_Config_T* eintConfig);

/* Interrupt */
void EINT_SelectSWInterrupt(uint32_t line);

/* Flag */
uint8_t EINT_ReadStatusFlag(uint32_t line);
void    EINT_ClearStatusFlag(uint32_t line);
uint8_t EINT_ReadIntFlag(uint32_t line);
void    EINT_ClearIntFlag(uint32_t line);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_EINT_H */

/**@} end of group EINT_Functions */
/**@} end of group EINT_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
