/*!
 * @file        apm32f0xx_can.h
 *
 * @brief       This file contains all the functions prototypes for the CAN firmware library
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
#ifndef __APM32F0XX_CAN_H
#define __APM32F0XX_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup CAN_Driver
  @{
*/

/** @defgroup CAN_Macros Macros
  @{
*/

/**@} end of group CAN_Macros */

/** @defgroup CAN_Enumerations Enumerations
  @{
*/

/**
 * @brief   CAN operating mode
 */
typedef enum
{
    CAN_OPERATING_MODE_INIT   = ((uint8_t)00), /*!< Initialization mode */
    CAN_OPERATING_MODE_NORMAL = ((uint8_t)01), /*!< Normal mode */
    CAN_OPERATING_MODE_SLEEP  = ((uint8_t)02), /*!< sleep mode */
} CAN_OPERATING_MODE_T;

/**
 * @brief   CAN test mode
 */
typedef enum
{
    CAN_MODE_NORMAL          = ((uint8_t)00),  /*!< normal mode */
    CAN_MODE_LOOPBACK        = ((uint8_t)01),  /*!< loopback mode */
    CAN_MODE_SILENT          = ((uint8_t)02),  /*!< silent mode */
    CAN_MODE_SILENT_LOOPBACK = ((uint8_t)03),  /*!< loopback combined with silent mode */
} CAN_MODE_T;

/**
 * @brief   CAN filter mode
 */
typedef enum
{
    CAN_FILTER_MODE_IDMASK  = ((uint8_t)00),   /*!< identifier/mask mode */
    CAN_FILTER_MODE_IDLIST  = ((uint8_t)01),   /*!< identifier list mode */
} CAN_FILTER_MODE_T;

/**
 * @brief   CAN synchronisation jump width
 */
typedef enum
{
    CAN_SJW_1 = ((uint8_t)00),                 /*!< 1 time quantum */
    CAN_SJW_2 = ((uint8_t)01),                 /*!< 2 time quantum */
    CAN_SJW_3 = ((uint8_t)02),                 /*!< 3 time quantum */
    CAN_SJW_4 = ((uint8_t)03),                 /*!< 4 time quantum */
} CAN_SJW_T;

/**
 * @brief   CAN_time quantum in bit_segment_1
 */
typedef enum
{
    CAN_TIME_SEGMENT1_1  = (uint8_t)0x00,      /*!< 1  time quanta */
    CAN_TIME_SEGMENT1_2  = (uint8_t)0x01,      /*!< 2  time quanta */
    CAN_TIME_SEGMENT1_3  = (uint8_t)0x02,      /*!< 3  time quanta */
    CAN_TIME_SEGMENT1_4  = (uint8_t)0x03,      /*!< 4  time quanta */
    CAN_TIME_SEGMENT1_5  = (uint8_t)0x04,      /*!< 5  time quanta */
    CAN_TIME_SEGMENT1_6  = (uint8_t)0x05,      /*!< 6  time quanta */
    CAN_TIME_SEGMENT1_7  = (uint8_t)0x06,      /*!< 7  time quanta */
    CAN_TIME_SEGMENT1_8  = (uint8_t)0x07,      /*!< 8  time quanta */
    CAN_TIME_SEGMENT1_9  = (uint8_t)0x08,      /*!< 9  time quanta */
    CAN_TIME_SEGMENT1_10 = (uint8_t)0x09,      /*!< 10 time quanta */
    CAN_TIME_SEGMENT1_11 = (uint8_t)0x0A,      /*!< 11 time quanta */
    CAN_TIME_SEGMENT1_12 = (uint8_t)0x0B,      /*!< 12 time quanta */
    CAN_TIME_SEGMENT1_13 = (uint8_t)0x0C,      /*!< 13 time quanta */
    CAN_TIME_SEGMENT1_14 = (uint8_t)0x0D,      /*!< 14 time quanta */
    CAN_TIME_SEGMENT1_15 = (uint8_t)0x0E,      /*!< 15 time quanta */
    CAN_TIME_SEGMENT1_16 = (uint8_t)0x0F,      /*!< 16 time quanta */
} CAN_TIME_SEGMENT1_T;

/**
 * @brief   CAN_time_quantum_in_bit_segment_2
 */
typedef enum
{
    CAN_TIME_SEGMENT2_1 = (uint8_t)0x00,       /*!< 1  time quanta */
    CAN_TIME_SEGMENT2_2 = (uint8_t)0x01,       /*!< 2  time quanta */
    CAN_TIME_SEGMENT2_3 = (uint8_t)0x02,       /*!< 3  time quanta */
    CAN_TIME_SEGMENT2_4 = (uint8_t)0x03,       /*!< 4  time quanta */
    CAN_TIME_SEGMENT2_5 = (uint8_t)0x04,       /*!< 5  time quanta */
    CAN_TIME_SEGMENT2_6 = (uint8_t)0x05,       /*!< 6  time quanta */
    CAN_TIME_SEGMENT2_7 = (uint8_t)0x06,       /*!< 7  time quanta */
    CAN_TIME_SEGMENT2_8 = (uint8_t)0x07,       /*!< 8  time quanta */
} CAN_TIME_SEGMENT2_T;

/**
 * @brief   CAN_filter_scale
 */
typedef enum
{
    CAN_FILTER_SCALE_16BIT = ((uint8_t)0x00),  /*!< Two 16-bit filters */
    CAN_FILTER_SCALE_32BIT = ((uint8_t)0x01),  /*!< One 32-bit filter */
} CAN_FILTER_SCALE_T;

/**
 * @brief   CAN identifier type
 */
typedef enum
{
    CAN_TYPEID_STD = ((uint32_t)0x00000000),   /*!< Standard Id */
    CAN_TYPEID_EXT = ((uint32_t)0x00000004),   /*!< Extended Id */
} CAN_TYPEID_T;

/**
 * @brief   CAN_remote_transmission_request
 */
typedef enum
{
    CAN_RTXR_DATA   = ((uint32_t)0x00000000),  /*!< Data frame */
    CAN_RTXR_REMOTE = ((uint32_t)0x00000002),  /*!< Remote frame */
} CAN_RTXR_T;

/**
 * @brief   CAN_transmit_constants
 */
typedef enum
{
    CAN_TX_FAILED       = ((uint8_t)0x00),     /*!< CAN transmission failed */
    CAN_TX_OK           = ((uint8_t)0x01),     /*!< CAN transmission succeeded */
    CAN_TX_WAITING      = ((uint8_t)0x02),     /*!< CAN waiting for transmission */
    CAN_TX_MAILBOX_FULL = ((uint8_t)0x04),     /*!< CAN cell did not provide */
} CAN_TX_T;

/**
 * @brief   CAN sleep constants
 */
typedef enum
{
    CAN_SLEEP_FAILED = ((uint8_t)0x00),        /*!< CAN did not enter the sleep mode */
    CAN_SLEEP_OK     = ((uint8_t)0x01),        /*!< CAN entered the sleep mode */
} CAN_SLEEP_T;

/**
 * @brief   CAN wake up constants
 */
typedef enum
{
    CAN_WAKEUP_FAILED = ((uint8_t)0x00),       /*!< CAN did not leave the sleep mode */
    CAN_WAKEUP_OK     = ((uint8_t)0x01),       /*!< CAN leaved the sleep mode */
} CAN_WUP_T;

/**
 * @brief   CAN receive FIFO
 */
typedef enum
{
    CAN_FIFO_0 = ((uint8_t)0x00),              /*!< CAN FIFO 0 used to receive */
    CAN_FIFO_1 = ((uint8_t)0x01),              /*!< CAN FIFO 1 used to receive */
} CAN_FIFO_T;

/**
 * @brief   CAN_error_Code_constants
 */
typedef enum
{
    CAN_ERROR_CODE_NOERR           = ((uint8_t)0x00), /*!< No Error */
    CAN_ERROR_CODE_STUFFERR        = ((uint8_t)0x10), /*!< Stuff Error */
    CAN_ERROR_CODE_FORMERR         = ((uint8_t)0x20), /*!< Form Error */
    CAN_ERROR_CODE_ACKERR          = ((uint8_t)0x30), /*!< Acknowledgment Error */
    CAN_ERROR_CODE_BITRECESSIVEERR = ((uint8_t)0x40), /*!< Bit Recessive Error */
    CAN_ERROR_CODE_BITDOMINANTERR  = ((uint8_t)0x50), /*!< Bit Dominant Error */
    CAN_ERROR_CODE_CRCERR          = ((uint8_t)0x60), /*!< CRC Error */
    CAN_ERROR_CODE_SOFTWARESETERR  = ((uint8_t)0x70), /*!< Software Set Error */
} CAN_ERROR_CODE_T;

/**
 * @brief   Flags
 */
typedef enum
{
    /* Error Flags */
    CAN_FLAG_EWF = ((uint32_t)0x10F00001),   /*!< Error Warning Flag */
    CAN_FLAG_EPF = ((uint32_t)0x10F00002),   /*!< Error Passive Flag */
    CAN_FLAG_BOF = ((uint32_t)0x10F00004),   /*!< Bus-Off Flag */
    CAN_FLAG_LEC = ((uint32_t)0x30F00070),   /*!< Last error code Flag */
    /* Operating Mode Flags */
    CAN_FLAG_WUP  = ((uint32_t)0x31000008),  /*!< Wake up Flag */
    CAN_FLAG_SLAK = ((uint32_t)0x31000012),  /*!< Sleep acknowledge Flag */
    /* Transmit Flags */
    CAN_FLAG_RQCP0 = ((uint32_t)0x32000001), /*!< Request MailBox0 Flag */
    CAN_FLAG_RQCP1 = ((uint32_t)0x32000100), /*!< Request MailBox1 Flag */
    CAN_FLAG_RQCP2 = ((uint32_t)0x32010000), /*!< Request MailBox2 Flag */
    /* Receive Flags */
    CAN_FLAG_FMP0 = ((uint32_t)0x14000003),  /*!< FIFO 0 Message Pending Flag */
    CAN_FLAG_FF0  = ((uint32_t)0x34000008),  /*!< FIFO 0 Full Flag */
    CAN_FLAG_FOV0 = ((uint32_t)0x34000010),  /*!< FIFO 0 Overrun Flag */
    CAN_FLAG_FMP1 = ((uint32_t)0x18000003),  /*!< FIFO 1 Message Pending Flag */
    CAN_FLAG_FF1  = ((uint32_t)0x38000008),  /*!< FIFO 1 Full Flag */
    CAN_FLAG_FOV1 = ((uint32_t)0x38000010),  /*!< FIFO 1 Overrun Flag */
} CAN_FLAG_T;

/**
 * @brief   CAN interrupts
 */
typedef enum
{
    CAN_INT_TXME  = BIT0,  /*!< Transmit mailbox empty Interrupt */
    CAN_INT_F0MP  = BIT1,  /*!< FIFO 0 message pending Interrupt */
    CAN_INT_F0FUL = BIT2,  /*!< FIFO 0 full Interrupt */
    CAN_INT_F0OVR = BIT3,  /*!< FIFO 0 overrun Interrupt */
    CAN_INT_F1MP  = BIT4,  /*!< FIFO 1 message pending Interrupt */
    CAN_INT_F1FUL = BIT5,  /*!< FIFO 1 full Interrupt */
    CAN_INT_F1OVR = BIT6,  /*!< FIFO 1 overrun Interrupt */
    CAN_INT_EWIE  = BIT8,  /*!< Error warning Interrupt */
    CAN_INT_EPIE  = BIT9,  /*!< Error passive Interrupt */
    CAN_INT_BOIE  = BIT10, /*!< Bus-off Interrupt */
    CAN_INT_LEC   = BIT11, /*!< Last error code Interrupt */
    CAN_INT_ERR   = BIT15, /*!< Error Interrupt */
    CAN_INT_WUP   = BIT16, /*!< Wake-up Interrupt */
    CAN_INT_SLE   = BIT17, /*!< Sleep acknowledge Interrupt */
} CAN_INT_T;

typedef enum
{
    CAN_FILTER_NUMBER_0 = 0, /*!< Number 0 of filters */
    CAN_FILTER_NUMBER_1,     /*!< Number 1 of filters */
    CAN_FILTER_NUMBER_2,     /*!< Number 2 of filters */
    CAN_FILTER_NUMBER_3,     /*!< Number 3 of filters */
    CAN_FILTER_NUMBER_4,     /*!< Number 4 of filters */
    CAN_FILTER_NUMBER_5,     /*!< Number 5 of filters */
    CAN_FILTER_NUMBER_6,     /*!< Number 6 of filters */
    CAN_FILTER_NUMBER_7,     /*!< Number 7 of filters */
    CAN_FILTER_NUMBER_8,     /*!< Number 8 of filters */
    CAN_FILTER_NUMBER_9,     /*!< Number 9 of filters */
    CAN_FILTER_NUMBER_10,    /*!< Number 10 of filters */
    CAN_FILTER_NUMBER_11,    /*!< Number 11 of filters */
    CAN_FILTER_NUMBER_12,    /*!< Number 12 of filters */
    CAN_FILTER_NUMBER_13,    /*!< Number 13 of filters */
} CAN_FILTER_NUMBER_T;

typedef enum
{
    CAN_MAILBOX_0 = ((uint8_t)0x00), /*!< Tx mailbox0 */
    CAN_MAILBOX_1 = ((uint8_t)0x01), /*!< Tx mailbox1 */
    CAN_MAILBOX_2 = ((uint8_t)0x02), /*!< Tx mailbox2 */
} CAN_MAILBOX_T;

/**@} end of group CAN_Enumerations */

/** @defgroup CAN_Structures Structures
  @{
*/

/**
 * @brief   CAN config structure definition
 */
typedef struct
{
    uint8_t      timeTrigComMode;     /*!< Enable or disable the time triggered communication mode */
    uint8_t      autoBusOffManage;    /*!< Enable or disable the automatic bus-off management */
    uint8_t      autoWakeUpMode;      /*!< Enable or disable the automatic wake-up mode */
    uint8_t      nonAutoRetran;       /*!< Enable or disable the non-automatic retransmission mode */
    uint8_t      rxFIFOLockMode;      /*!< Enable or disable the Receive FIFO Locked mode */
    uint32_t     txFIFOPriority;      /*!< Enable or disable the transmit FIFO priority */
    CAN_MODE_T   mode;                /*!< Specifies the CAN operating mode */
    CAN_SJW_T    syncJumpWidth;       /*!< Specifies the maximum number of time quanta the CAN hardware
                                         is allowed to lengthen or shorten a bit to perform resynchronization. */
    CAN_TIME_SEGMENT1_T timeSegment1; /*!< Specifies the number of time quanta in Bit Segment 1 */
    CAN_TIME_SEGMENT2_T timeSegment2; /*!< Specifies the number of time quanta in Bit Segment 2 */
    uint16_t            prescaler;    /*!< Specifies the length of a time quantum. It can be 1 to 1024 */
} CAN_Config_T;

/**
 * @brief   CAN filter config structure definition
 */
typedef struct
{
    uint16_t            filterIdHigh;        /*!< Specifies the filter identification number. */
    uint16_t            filterIdLow;         /*!< Specifies the filter identification number. */
    uint16_t            filterMaskIdHigh;    /*!< Specifies the filter mask number or identification number. */
    uint16_t            filterMaskIdLow;     /*!< Specifies the filter mask number or identification number. */
    CAN_FIFO_T          filterFIFO;          /*!< Specifies the FIFO which will be assigned to the filter. */
    CAN_FILTER_NUMBER_T filterNumber;        /*!< Specifies the filter which will be configured. It ranges from 0 to 13. */
    CAN_FILTER_MODE_T   filterMode;          /*!< Specifies the filter mode to be configured. */
    CAN_FILTER_SCALE_T  filterScale;         /*!< Specifies the filter scale. */
    uint8_t             filterActivation;    /*!< Enable or disable the filter. */
} CAN_FilterConfig_T;

/**
 * @brief   CAN Tx message structure definition
 */
typedef struct
{
    uint32_t    stanID;         /*!< Specifies the standard identifier. */
    uint32_t    extenID;        /*!< Specifies the extended identifier. */
    CAN_TYPEID_T typeID;        /*!< Specifies the type of identifier for the message. */
    CAN_RTXR_T  remoteTxReq;    /*!< Specifies the type of frame for the message. */
    uint8_t     dataLengthCode; /*!< Specifies the length of the frame. It can be a value between 0 to 8. */
    uint8_t     data[8];        /*!< Contains the data to be transmitted. It ranges from 0 to 0xFF. */
} CAN_Tx_Message;

/**
 * @brief   CAN Rx message structure definition
 */
typedef struct
{
    uint32_t    stanID;             /*!< Specifies the standard identifier. */
    uint32_t    extenID;            /*!< Specifies the extended identifier. */
    CAN_TYPEID_T typeID;            /*!< Specifies the type of identifier for the message. */
    CAN_RTXR_T  remoteTxReq;        /*!< Specifies the type of frame for the message. */
    uint8_t     dataLengthCode;     /*!< Specifies the length of the frame. It can be a value between 0 to 8. */
    uint8_t     data[8];            /*!< Contains the data to be transmitted. It ranges from 0 to 0xFF. */
    uint8_t     filterMatchIndex;   /*!< Specifies the index of the filter the message stored in the mailbox passes through. */
} CAN_Rx_Message;

/**@} end of group CAN_Structures */

/** @defgroup CAN_Variables Variables
  @{
*/

/**@} end of group CAN_Variables */

/** @defgroup CAN_Functions Functions
  @{
*/

/* CAN reset and configuration */
void CAN_Reset(void);
uint8_t CAN_Config(CAN_Config_T* canConfig);
void CAN_ConfigFilter(CAN_FilterConfig_T* filterConfig);
void CAN_ConfigStructInit(CAN_Config_T* canConfig);
void CAN_StartBankSlave(uint8_t bankNumber);
void CAN_EnableDebugFreeze(void);
void CAN_DisableDebugFreeze(void);
void CAN_EnableTTComMode(void);
void CAN_DisableTTComMode(void);

/* CAN frames transmission */
uint8_t CAN_TxMessage(CAN_Tx_Message* TxMessage);
uint8_t CAN_TxMessageStatus(CAN_MAILBOX_T TxMailbox);
void CAN_CancelTx(CAN_MAILBOX_T TxMailbox);

/* CAN frames reception */
void CAN_RxMessage(uint8_t FIFONumber, CAN_Rx_Message* RxMessage);
void CAN_ReleaseFIFO(uint8_t FIFONumber);
uint8_t CAN_PendingMessage(uint8_t FIFONumber);

/* CAN operation modes */
uint8_t CAN_OperatingMode(CAN_OPERATING_MODE_T operatingMode);
uint8_t CAN_SleepMode(void);
uint8_t CAN_WakeUpMode(void);

/* CAN bus error management */
uint8_t CAN_ReadLastErrorCode(void);
uint8_t CAN_ReadRxErrorCounter(void);
uint8_t CAN_ReadLSBTxErrorCounter(void);

/* CAN interrupt and flag */
void CAN_EnableInterrupt(uint32_t interrupt);
void CAN_DisableInterrupt(uint32_t interrupt);
uint8_t CAN_ReadStatusFlag(CAN_FLAG_T CAN_FLAG);
void CAN_ClearStatusFlag(CAN_FLAG_T flag);
uint8_t CAN_ReadIntFlag(CAN_INT_T interrupt);
void CAN_ClearIntFlag(uint32_t interrupt);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_CAN_H */

/**@} end of group CAN_Functions */
/**@} end of group CAN_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
