/*!
 * @file        apm32e10x_can.h
 *
 * @brief       This file contains all the functions prototypes for the CAN firmware library
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
#ifndef __APM32E10X_CAN_H
#define __APM32E10X_CAN_H

/* Includes */
#include "apm32e10x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup APM32E10x_StdPeriphDriver
  @{
*/

/** @addtogroup CAN_Driver CAN Driver
  @{
*/

/** @defgroup CAN_Enumerations
  @{
*/

/**
 * @brief CAN mode
 */
typedef enum
{
    CAN_MODE_NORMAL          = ((uint8_t)0x00),  /*!< normal mode */
    CAN_MODE_LOOPBACK        = ((uint8_t)0x01),  /*!< loopback mode */
    CAN_MODE_SILENT          = ((uint8_t)0x02),  /*!< silent mode */
    CAN_MODE_SILENT_LOOPBACK = ((uint8_t)0x03)   /*!< loopback combined with silent mode */
} CAN_MODE_T;

/**
 * @brief CAN synchronisation jump width
 */
typedef enum
{
    CAN_SJW_1 = ((uint8_t)0x00),  /*!< 1 time quantum */
    CAN_SJW_2 = ((uint8_t)0x01),  /*!< 2 time quantum */
    CAN_SJW_3 = ((uint8_t)0x02),  /*!< 3 time quantum */
    CAN_SJW_4 = ((uint8_t)0x03)   /*!< 4 time quantum */
} CAN_SJW_T;

/**
 * @brief CAN time quantum in bit segment 1
 */
typedef enum
{
    CAN_TIME_SEGMENT1_1  = ((uint8_t)0x00),  /*!< 1  time quanta */
    CAN_TIME_SEGMENT1_2  = ((uint8_t)0x01),  /*!< 2  time quanta */
    CAN_TIME_SEGMENT1_3  = ((uint8_t)0x02),  /*!< 3  time quanta */
    CAN_TIME_SEGMENT1_4  = ((uint8_t)0x03),  /*!< 4  time quanta */
    CAN_TIME_SEGMENT1_5  = ((uint8_t)0x04),  /*!< 5  time quanta */
    CAN_TIME_SEGMENT1_6  = ((uint8_t)0x05),  /*!< 6  time quanta */
    CAN_TIME_SEGMENT1_7  = ((uint8_t)0x06),  /*!< 7  time quanta */
    CAN_TIME_SEGMENT1_8  = ((uint8_t)0x07),  /*!< 8  time quanta */
    CAN_TIME_SEGMENT1_9  = ((uint8_t)0x08),  /*!< 9  time quanta */
    CAN_TIME_SEGMENT1_10 = ((uint8_t)0x09),  /*!< 10 time quanta */
    CAN_TIME_SEGMENT1_11 = ((uint8_t)0x0A),  /*!< 11 time quanta */
    CAN_TIME_SEGMENT1_12 = ((uint8_t)0x0B),  /*!< 12 time quanta */
    CAN_TIME_SEGMENT1_13 = ((uint8_t)0x0C),  /*!< 13 time quanta */
    CAN_TIME_SEGMENT1_14 = ((uint8_t)0x0D),  /*!< 14 time quanta */
    CAN_TIME_SEGMENT1_15 = ((uint8_t)0x0E),  /*!< 15 time quanta */
    CAN_TIME_SEGMENT1_16 = ((uint8_t)0x0F)   /*!< 16 time quanta */
} CAN_TIME_SEGMENT1_T;

/**
 * @brief CAN time quantum in bit segment 2
 */
typedef enum
{
    CAN_TIME_SEGMENT2_1 = (uint8_t)0x00,     /*!< 1  time quanta */
    CAN_TIME_SEGMENT2_2 = (uint8_t)0x01,     /*!< 2  time quanta */
    CAN_TIME_SEGMENT2_3 = (uint8_t)0x02,     /*!< 3  time quanta */
    CAN_TIME_SEGMENT2_4 = (uint8_t)0x03,     /*!< 4  time quanta */
    CAN_TIME_SEGMENT2_5 = (uint8_t)0x04,     /*!< 5  time quanta */
    CAN_TIME_SEGMENT2_6 = (uint8_t)0x05,     /*!< 6  time quanta */
    CAN_TIME_SEGMENT2_7 = (uint8_t)0x06,     /*!< 7  time quanta */
    CAN_TIME_SEGMENT2_8 = (uint8_t)0x07      /*!< 8  time quanta */
} CAN_TIME_SEGMENT2_T;

/**
 * @brief CAN filter FIFO
 */
typedef enum
{
    CAN_FILTER_FIFO_0 = ((uint8_t)0x00),     /*!< filter FIFO 0 */
    CAN_FILTER_FIFO_1 = ((uint8_t)0x01)      /*!< filter FIFO 1 */
} CAN_FILTER_FIFO_T;

/**
 * @brief CAN filter mode
 */
typedef enum
{
    CAN_FILTER_MODE_IDMASK = ((uint8_t)0x00),/*!< identifier/mask mode */
    CAN_FILTER_MODE_IDLIST = ((uint8_t)0x01) /*!< identifier list mode */
} CAN_FILTER_MODE_T;

/**
 * @brief CAN filter scale
 */
typedef enum
{
    CAN_FILTER_SCALE_16BIT = ((uint8_t)0x00), /*!< Two 16-bit filters */
    CAN_FILTER_SCALE_32BIT = ((uint8_t)0x01)  /*!< One 32-bit filter */
} CAN_FILTER_SCALE_T;

/**
 * @brief CAN identifier type
 */
typedef enum
{
    CAN_TYPEID_STD = ((uint32_t)0x00000000), /*!< Standard Id */
    CAN_TYPEID_EXT = ((uint32_t)0x00000004)  /*!< Extended Id */
} CAN_TYPEID_T;

/**
 * @brief CAN_remote_transmission_request
 */
typedef enum
{
    CAN_RTXR_DATA   = ((uint32_t)0x00000000), /*!< Data frame */
    CAN_RTXR_REMOTE = ((uint32_t)0x00000002)  /*!< Remote frame */
} CAN_RTXR_T;

/**
 * @brief Mailboxes definition
 */
typedef enum
{
    CAN_TX_MAILBIX_0 = ((uint8_t)0x00), /*!< Tx mailbox0 */
    CAN_TX_MAILBIX_1 = ((uint8_t)0x01), /*!< Tx mailbox1 */
    CAN_TX_MAILBIX_2 = ((uint8_t)0x02)  /*!< Tx mailbox2 */
} CAN_TX_MAILBIX_T;

/**
 * @brief CAN receive FIFO number constants
 */
typedef enum
{
    CAN_RX_FIFO_0 = ((uint8_t)0x00), /*!< receive FIFO 0 */
    CAN_RX_FIFO_1 = ((uint8_t)0x01)  /*!< receive FIFO 1 */
} CAN_RX_FIFO_T;

/**
 * @brief CAN Operating Mode
 */
typedef enum
{
    CAN_OPERATING_MODE_INIT   = ((uint8_t)0x00), /*!< Initialization mode */
    CAN_OPERATING_MODE_NORMAL = ((uint8_t)0x01), /*!< Normal mode */
    CAN_OPERATING_MODE_SLEEP  = ((uint8_t)0x02)  /*!< sleep mode */
} CAN_OPERATING_MODE_T;

/**
 * @brief CAN Interrupts
 */
typedef enum
{
    CAN_INT_TXME   = ((uint32_t)0x00000001), /*!< Transmit mailbox empty Interrupt */
    CAN_INT_F0MP   = ((uint32_t)0x00000002), /*!< FIFO 0 message pending Interrupt */
    CAN_INT_F0FULL = ((uint32_t)0x00000004), /*!< FIFO 0 full Interrupt */
    CAN_INT_F0OVR  = ((uint32_t)0x00000008), /*!< FIFO 0 overrun Interrupt */
    CAN_INT_F1MP   = ((uint32_t)0x00000010), /*!< FIFO 1 message pending Interrupt */
    CAN_INT_F1FULL = ((uint32_t)0x00000020), /*!< FIFO 1 full Interrupt */
    CAN_INT_F1OVR  = ((uint32_t)0x00000040), /*!< FIFO 1 overrun Interrupt */
    CAN_INT_ERRW   = ((uint32_t)0x00000100), /*!< Error warning Interrupt */
    CAN_INT_ERRP   = ((uint32_t)0x00000200), /*!< Error passive Interrupt */
    CAN_INT_BOF    = ((uint32_t)0x00000400), /*!< Bus-off Interrupt */
    CAN_INT_LEC    = ((uint32_t)0x00000800), /*!< Last error record code Interrupt */
    CAN_INT_ERR    = ((uint32_t)0x00008000), /*!< Error Interrupt */
    CAN_INT_WUP    = ((uint32_t)0x00010000), /*!< Wake-up Interrupt */
    CAN_INT_SLEEP  = ((uint32_t)0x00020000)  /*!< Sleep acknowledge Interrupt */
} CAN_INT_T;

/**
 * @brief CAN Flags
 */
typedef enum
{
    /** Error flag*/
    CAN_FLAG_ERRW   = ((uint32_t)0x10F00001),  /*!< Error Warning Flag */
    CAN_FLAG_ERRP   = ((uint32_t)0x10F00002),  /*!< Error Passive Flag */
    CAN_FLAG_BOF    = ((uint32_t)0x10F00004),  /*!< Bus-Off Flag */
    CAN_FLAG_LERRC  = ((uint32_t)0x30F00070),  /*!< Last error record code Flag */
    /** Operating Mode Flags */
    CAN_FLAG_WUPI   = ((uint32_t)0x31000008),  /*!< Wake up Flag */
    CAN_FLAG_SLEEP  = ((uint32_t)0x31000012),  /*!< Sleep acknowledge Flag */
    /** Receive Flags */
    CAN_FLAG_F0MP   = ((uint32_t)0x12000003),  /*!< FIFO 0 Message Pending Flag */
    CAN_FLAG_F0FULL = ((uint32_t)0x32000008),  /*!< FIFO 0 Full Flag */
    CAN_FLAG_F0OVR  = ((uint32_t)0x32000010),  /*!< FIFO 0 Overrun Flag */
    CAN_FLAG_F1MP   = ((uint32_t)0x14000003),  /*!< FIFO 1 Message Pending Flag */
    CAN_FLAG_F1FULL = ((uint32_t)0x34000008),  /*!< FIFO 1 Full Flag */
    CAN_FLAG_F1OVR  = ((uint32_t)0x34000010),  /*!< FIFO 1 Overrun Flag */
    /** Transmit Flags */
    CAN_FLAG_REQC0  = ((uint32_t)0x38000001),  /*!< Request MailBox0 Flag */
    CAN_FLAG_REQC1  = ((uint32_t)0x38000100),  /*!< Request MailBox1 Flag */
    CAN_FLAG_REQC2  = ((uint32_t)0x38010000)   /*!< Request MailBox2 Flag */
} CAN_FLAG_T;

/**@} end of group CAN_Enumerations*/

/** @defgroup CAN_Structure
  @{
*/

/**
 * @brief    CAN Config structure definition
 */

/**
 * @brief CAN config structure definition
 */
typedef struct
{
    uint8_t      autoBusOffManage;    /*!< Enable or disable the automatic bus-off management. */
    uint8_t      autoWakeUpMode;      /*!< Enable or disable the automatic wake-up mode. */
    uint8_t      nonAutoRetran;       /*!< Enable or disable the non-automatic retransmission mode. */
    uint8_t      rxFIFOLockMode;      /*!< Enable or disable the Receive FIFO Locked mode. */
    uint8_t      txFIFOPriority;      /*!< Enable or disable the transmit FIFO priority. */
    CAN_MODE_T   mode;                /*!< Specifies the CAN operating mode. */
    CAN_SJW_T    syncJumpWidth;       /* Specifies the maximum number of time quanta the CAN hardware
                                         is allowed to lengthen or shorten a bit to perform resynchronization.
                                       */
    CAN_TIME_SEGMENT1_T timeSegment1; /*!< Specifies the number of time quanta in Bit Segment 1. */
    CAN_TIME_SEGMENT2_T timeSegment2; /*!< Specifies the number of time quanta in Bit Segment 2. */
    uint16_t            prescaler;    /*!< Specifies the length of a time quantum. It can be 1 to 1024. */
} CAN_Config_T;

/**
 * @brief  CAN Tx message structure definition
 */
typedef struct
{
    uint32_t            stdID;         /*!< Specifies the standard identifier. It can be 0 to 0x7FF. */
    uint32_t            extID;         /*!< Specifies the extended identifier. It can be 0 to 0x1FFFFFFF. */
    CAN_TYPEID_T        typeID;
    CAN_RTXR_T          remoteTxReq;
    uint8_t             dataLengthCode;/*!< Specifies the data length code.       It can be 0 to 8. */
    uint8_t             data[8];       /*!< Specifies the data to be transmitted. It can be 0 to 0xFF. */
} CAN_TxMessage_T;

/**
 * @brief  CAN Rx message structure definition
 */
typedef struct
{
    uint32_t            stdID;           /*!< Specifies the standard identifier. It can be 0 to 0x7FF. */
    uint32_t            extID;           /*!< Specifies the extended identifier. It can be 0 to 0x1FFFFFFF. */
    uint32_t            typeID;
    uint32_t            remoteTxReq;
    uint8_t             dataLengthCode;  /*!< Specifies the data length code.       It can be 0 to 8. */
    uint8_t             data[8];         /*!< Specifies the data to be transmitted. It can be 0 to 0xFF. */
    uint8_t             filterMatchIndex;/*!< Specifies the filter match index.     It can be 0 to 0xFF. */
} CAN_RxMessage_T;

/**
 * @brief     CAN filter config structure definition
 */
typedef struct
{
    uint8_t             filterNumber;      /*!< Specifies the filter number. It can be 0 to 13. */
    uint16_t            filterIdHigh;      /*!< Specifies the filter identification number.It can be 0 to 0xFFFF. */
    uint16_t            filterIdLow;       /*!< Specifies the filter identification number.It can be 0 to 0xFFFF. */
    uint16_t            filterMaskIdHigh;  /*!< Specifies the filter mask identification.  It can be 0 to 0xFFFF. */
    uint16_t            filterMaskIdLow;   /*!< Specifies the filter mask identification.  It can be 0 to 0xFFFF. */
    uint16_t            filterActivation;  /*!< Specifies the filter Activation. It can be ENABLE or DISABLE. */
    CAN_FILTER_FIFO_T   filterFIFO;
    CAN_FILTER_MODE_T   filterMode;
    CAN_FILTER_SCALE_T  filterScale;
} CAN_FilterConfig_T;

/**@} end of group CAN_Structure*/


/** @defgroup CAN_Functions
  @{
*/

/* CAN reset and configuration */
void CAN_Reset(CAN_T* can);
uint8_t CAN_Config(CAN_T* can, CAN_Config_T* canConfig);
void CAN_ConfigFilter(CAN_T* can, CAN_FilterConfig_T* filterConfig);
void CAN_ConfigStructInit(CAN_Config_T* canConfig);
void CAN_EnableDBGFreeze(CAN_T* can);
void CAN_DisableDBGFreeze(CAN_T* can);


/* CAN frames transmit */
uint8_t CAN_TxMessage(CAN_T* can, CAN_TxMessage_T* TxMessage);
uint8_t CAN_TxMessageStatus(CAN_T* can, CAN_TX_MAILBIX_T TxMailbox);
void CAN_CancelTxMailbox(CAN_T* can, CAN_TX_MAILBIX_T TxMailbox);

/* CAN frames receive */
void CAN_RxMessage(CAN_T* can, CAN_RX_FIFO_T FIFONumber, CAN_RxMessage_T* RxMessage);
void CAN_ReleaseFIFO(CAN_T* can, CAN_RX_FIFO_T FIFONumber);
uint8_t CAN_PendingMessage(CAN_T* can, CAN_RX_FIFO_T FIFONumber);

/* CAN operation modes */
uint8_t CAN_OperatingMode(CAN_T* can, CAN_OPERATING_MODE_T operatingMode);
uint8_t CAN_SleepMode(CAN_T* can);
uint8_t CAN_WakeUpMode(CAN_T* can);

/* CAN bus error management */
uint8_t CAN_ReadLastErrorCode(CAN_T* can);
uint8_t CAN_ReadRxErrorCounter(CAN_T* can);
uint8_t CAN_ReadLSBTxErrorCounter(CAN_T* can);

/* CAN interrupt and flag */
void CAN_EnableInterrupt(CAN_T* can, uint32_t interrupt);
void CAN_DisableInterrupt(CAN_T* can, uint32_t interrupt);
uint8_t CAN_ReadStatusFlag(CAN_T* can, CAN_FLAG_T flag);
void CAN_ClearStatusFlag(CAN_T* can, CAN_FLAG_T flag);
uint8_t CAN_ReadIntFlag(CAN_T* can, CAN_INT_T flag);
void CAN_ClearIntFlag(CAN_T* can, CAN_INT_T flag);

/**@} end of group CAN_Functions*/
/**@} end of group CAN_Driver */
/**@} end of group APM32E10x_StdPeriphDriver */

#ifdef __cplusplus
}
#endif

#endif /* __APM32E10X_CAN_H */
