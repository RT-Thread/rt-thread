/*!
 * @file        apm32f0xx_cec.h
 *
 * @brief       This file contains all the functions prototypes for the CEC firmware library
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
#ifndef __APM32F0XX_CEC_H
#define __APM32F0XX_CEC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup CEC_Driver
  @{
*/

/** @defgroup CEC_Macros Macros
  @{
*/

/**@} end of group CEC_Macros */

/** @defgroup CEC_Enumerations Enumerations
  @{
*/

/**
 * @brief    CEC_Signal_Free_Time
 */
typedef enum
{
    CEC_SINGANL_FREETIME_STANDARD = 0x00, /*!< none nominal data bit periods */
    CEC_SINGANL_FREETIME_1T       = 0x01, /*!< 0.5 nominal data bit periods */
    CEC_SINGANL_FREETIME_2T       = 0x02, /*!< 1.5 nominal data bit periods */
    CEC_SINGANL_FREETIME_3T       = 0x03, /*!< 2.5 nominal data bit periods */
    CEC_SINGANL_FREETIME_4T       = 0x04, /*!< 3.5 nominal data bit periods */
    CEC_SINGANL_FREETIME_5T       = 0x05, /*!< 4.5 nominal data bit periods */
    CEC_SINGANL_FREETIME_6T       = 0x06, /*!< 5.5 nominal data bit periods */
    CEC_SINGANL_FREETIME_7T       = 0x07, /*!< 6.5 nominal data bit periods */
} CEC_SIGNAL_FREETIME_T;

/**
 * @brief    CEC_RxTolerance
 */
typedef enum
{
    CEC_RX_TOLERANCE_STANDARD  =  0x00,   /*!< Standard tolerance margin */
    CEC_RX_TOLERANCE_EXTENDED  =  0x01    /*!< Extended Tolerance */
} CEC_RX_TOLERANCE_T;

/**
 * @brief    CEC_Stop_Reception
 */
typedef enum
{
    CEC_STOP_RECEPTION_OFF,           /*!< CEC Stop Reception Off */
    CEC_STOP_RECEPTION_ON             /*!< CEC Stop Reception On */
} CEC_STOP_RECEPTION_T;

/**
 * @brief     CEC_Bit_Rising_Error_Generation
 */
typedef enum
{
    CEC_BIT_RISING_ERR_OFF,           /*!< BRE detection does not generate an Error-Bit on the CEC line */
    CEC_BIT_RISING_ERR_ON             /*!< BRE detection generates an Error-Bit on the CEC line (if BRESTP is set) */
} CEC_BIT_RISING_ERR_T;

/**
 * @brief     CEC_Long_Bit_Error_Generation
 */
typedef enum
{
    CEC_LONG_PERIOD_ERR_OFF,         /*!< LBPE detection does not generate an Error-Bit on the CEC line */
    CEC_LONG_PERIOD_ERR_ON           /*!< LBPE detection generates an Error-Bit on the CEC line */
} CEC_LONG_PERIOD_ERR_T;

/**
 * @brief     CEC_BDR_No_Gen
 */
typedef enum
{
    CEC_BROADCAST_NO_ERR_OFF,         /*!< Broadcast Bit Rising Error generation turned Off */
    CEC_BROADCAST_NO_ERR_ON           /*!< Broadcast Bit Rising Error generation turned On */
} CEC_BROADCAST_NO_ERR_T;

/**
 * @brief     CEC_SFT_Option
 */
typedef enum
{
    CEC_SIGNAL_FREETIME_OPTION_OFF,   /*!< SFTCFG timer starts when TXSOM is set by software */
    CEC_SIGNAL_FREETIME_OPTION_ON     /*!< SFTCFG timer starts automatically at the end of message transmission/reception */
} CEC_SIGNAL_FREETIME_OPTION_T;

/**
 * @brief    CEC_Interrupt_Configuration_definition
 */
typedef enum
{
    CEC_INT_RXBR   = ((uint32_t)0x00000001), /*!< Rx-Byte Received Interrupt */
    CEC_INT_RXEND  = ((uint32_t)0x00000002), /*!< End Of Reception Interrupt */
    CEC_INT_RXOVR  = ((uint32_t)0x00000004), /*!< Rx-Buffer Overrun Interrupt */
    CEC_INT_BRE    = ((uint32_t)0x00000008), /*!< Bit Rising Error Interrupt */
    CEC_INT_SBPE   = ((uint32_t)0x00000010), /*!< Short Bit Period Error Interrupt */
    CEC_INT_LBPE   = ((uint32_t)0x00000020), /*!< Long Bit Period Error Interrupt */
    CEC_INT_RXACKE = ((uint32_t)0x00000040), /*!< Rx-Missing Acknowledge Error Interrupt */
    CEC_INT_ARBLST = ((uint32_t)0x00000080), /*!< Arbitration Lost Interrupt */
    CEC_INT_TXBR   = ((uint32_t)0x00000100), /*!< Tx-Byte Request Interrupt */
    CEC_INT_TXEND  = ((uint32_t)0x00000200), /*!< Tx-End Of Message Interrupt */
    CEC_INT_TXUDR  = ((uint32_t)0x00000400), /*!< Tx-Underrun Interrupt */
    CEC_INT_TXERR  = ((uint32_t)0x00000800), /*!< Tx-Error Interrupt */
    CEC_INT_TXACKE = ((uint32_t)0x00001000), /*!< Tx-Missing Acknowledge Error Interrupt */
} CEC_INT_T;

/**
 * @brief   CEC_STS_register_flags_definition
 */
typedef enum
{
    CEC_FLAG_RXBR   = ((uint32_t)0x00000001),  /*!< Rx-Byte Received Flag */
    CEC_FLAG_RXEND  = ((uint32_t)0x00000002),  /*!< End Of Reception Flag */
    CEC_FLAG_RXOVR  = ((uint32_t)0x00000004),  /*!< Rx-Buffer Overrun Flag */
    CEC_FLAG_BRE    = ((uint32_t)0x00000008),  /*!< Bit Rising Error Flag */
    CEC_FLAG_SBPE   = ((uint32_t)0x00000010),  /*!< Short Bit Period Error Flag */
    CEC_FLAG_LBPE   = ((uint32_t)0x00000020),  /*!< Long Bit Period Error Flag */
    CEC_FLAG_RXACKE = ((uint32_t)0x00000040),  /*!< Rx-Missing Acknowledge Error Flag */
    CEC_FLAG_ARBLST = ((uint32_t)0x00000080),  /*!< Arbitration Lost Flag */
    CEC_FLAG_TXBR   = ((uint32_t)0x00000100),  /*!< Tx-Byte Request Flag */
    CEC_FLAG_TXEND  = ((uint32_t)0x00000200),  /*!< Tx-End Of Message Flag */
    CEC_FLAG_TXUDR  = ((uint32_t)0x00000400),  /*!< Tx-Underrun Flag */
    CEC_FLAG_TXERR  = ((uint32_t)0x00000800),  /*!< Tx-Error Flag */
    CEC_FLAG_TXACKE = ((uint32_t)0x00001000),  /*!< Tx-Missing Acknowledge Error Flag */
} CEC_FLAG_T;

/**@} end of group CEC_Enumerations */

/** @defgroup CEC_Structures Structures
  @{
*/

/**
  * @brief CEC Init structure definition
  */
typedef struct
{
    CEC_SIGNAL_FREETIME_T  signalFreeTime;     /*!< Signal Free Time */
    CEC_RX_TOLERANCE_T     RxTolerance;        /*!< Rx-Tolerance */
    CEC_STOP_RECEPTION_T   stopReception;      /*!< Rx-Stop on Bit Rising Error */
    CEC_BIT_RISING_ERR_T   bitRisingError;     /*!< Generate Error-Bit on Bit Rising Error */
    CEC_LONG_PERIOD_ERR_T  longPeriodError;    /*!< Generate Error-Bit on Long Bit Period Error */
    CEC_BROADCAST_NO_ERR_T broadcastrNoGen;    /*!< Avoid Error-Bit Generation in Broadcast */
    CEC_SIGNAL_FREETIME_OPTION_T signalFreeTimeOption;/*!< Signal Free Time optional */
} CEC_Config_T;

/**@} end of group CEC_Structures */

/** @defgroup CEC_Variables Variables
  @{
*/

/**@} end of group CEC_Variables */

/** @defgroup CEC_Functions Functions
  @{
*/

/* CEC reset and configuration */
void CEC_Reset(void);
void CEC_Config(CEC_Config_T* cecConfig);
void CEC_ConfigStructInit(CEC_Config_T* cecConfig);
void CEC_Enable(void);
void CEC_Disable(void);
void CEC_EnableListenMode(void);
void CEC_DisableListenMode(void);
void CEC_ConfigOwnAddress(uint8_t ownAddress);
void CEC_ClearQwnAddress(void);

/* Transmit and receive */
void CEC_TxData(uint8_t Data);
uint8_t CEC_RxData(void);

/* Config Message */
void CEC_StartNewMessage(void);
void CEC_CompleteMessage(void);

/* Interrupt and Flag*/
void CEC_EnableInterrupt(uint32_t interrupt);
void CEC_DisableInterrupt(uint32_t interrupt);
uint8_t CEC_ReadStatusFlag(uint32_t flag);
void CEC_ClearStatusFlag(uint32_t flag);
uint8_t CEC_ReadIntFlag(uint16_t flag);
void CEC_ClearIntFlag(uint16_t flag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_CEC_H */

/**@} end of group CEC_Functions */
/**@} end of group CEC_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
