/**
  ******************************************************************************
  * @file    stm32g0xx_hal_fdcan.h
  * @author  MCD Application Team
  * @brief   Header file of FDCAN HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G0xx_HAL_FDCAN_H
#define STM32G0xx_HAL_FDCAN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal_def.h"

#if defined(FDCAN1)

/** @addtogroup STM32G0xx_HAL_Driver
  * @{
  */

/** @addtogroup FDCAN
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup FDCAN_Exported_Types FDCAN Exported Types
  * @{
  */

/**
  * @brief HAL State structures definition
  */
typedef enum
{
  HAL_FDCAN_STATE_RESET      = 0x00U, /*!< FDCAN not yet initialized or disabled */
  HAL_FDCAN_STATE_READY      = 0x01U, /*!< FDCAN initialized and ready for use   */
  HAL_FDCAN_STATE_BUSY       = 0x02U, /*!< FDCAN process is ongoing              */
  HAL_FDCAN_STATE_ERROR      = 0x03U  /*!< FDCAN error state                     */
} HAL_FDCAN_StateTypeDef;

/**
  * @brief FDCAN Init structure definition
  */
typedef struct
{
  uint32_t ClockDivider;                 /*!< Specifies the FDCAN kernel clock divider.
                                              The clock is common to all FDCAN instances.
                                              This parameter is applied only at initialisation of
                                              first FDCAN instance.
                                              This parameter can be a value of @ref FDCAN_clock_divider.   */

  uint32_t FrameFormat;                  /*!< Specifies the FDCAN frame format.
                                              This parameter can be a value of @ref FDCAN_frame_format     */

  uint32_t Mode;                         /*!< Specifies the FDCAN mode.
                                              This parameter can be a value of @ref FDCAN_operating_mode   */

  FunctionalState AutoRetransmission;    /*!< Enable or disable the automatic retransmission mode.
                                              This parameter can be set to ENABLE or DISABLE               */

  FunctionalState TransmitPause;         /*!< Enable or disable the Transmit Pause feature.
                                              This parameter can be set to ENABLE or DISABLE               */

  FunctionalState ProtocolException;      /*!< Enable or disable the Protocol Exception Handling.
                                              This parameter can be set to ENABLE or DISABLE               */

  uint32_t NominalPrescaler;             /*!< Specifies the value by which the oscillator frequency is
                                              divided for generating the nominal bit time quanta.
                                              This parameter must be a number between 1 and 512            */

  uint32_t NominalSyncJumpWidth;         /*!< Specifies the maximum number of time quanta the FDCAN
                                              hardware is allowed to lengthen or shorten a bit to perform
                                              resynchronization.
                                              This parameter must be a number between 1 and 128            */

  uint32_t NominalTimeSeg1;              /*!< Specifies the number of time quanta in Bit Segment 1.
                                              This parameter must be a number between 2 and 256            */

  uint32_t NominalTimeSeg2;              /*!< Specifies the number of time quanta in Bit Segment 2.
                                              This parameter must be a number between 2 and 128            */

  uint32_t DataPrescaler;                /*!< Specifies the value by which the oscillator frequency is
                                              divided for generating the data bit time quanta.
                                              This parameter must be a number between 1 and 32             */

  uint32_t DataSyncJumpWidth;            /*!< Specifies the maximum number of time quanta the FDCAN
                                              hardware is allowed to lengthen or shorten a data bit to
                                              perform resynchronization.
                                              This parameter must be a number between 1 and 16             */

  uint32_t DataTimeSeg1;                 /*!< Specifies the number of time quanta in Data Bit Segment 1.
                                              This parameter must be a number between 1 and 32             */

  uint32_t DataTimeSeg2;                 /*!< Specifies the number of time quanta in Data Bit Segment 2.
                                              This parameter must be a number between 1 and 16             */

  uint32_t StdFiltersNbr;                /*!< Specifies the number of standard Message ID filters.
                                              This parameter must be a number between 0 and 28             */

  uint32_t ExtFiltersNbr;                /*!< Specifies the number of extended Message ID filters.
                                              This parameter must be a number between 0 and 8             */

  uint32_t TxFifoQueueMode;              /*!< Tx FIFO/Queue Mode selection.
                                              This parameter can be a value of @ref FDCAN_txFifoQueue_Mode */

} FDCAN_InitTypeDef;

/**
  * @brief  FDCAN filter structure definition
  */
typedef struct
{
  uint32_t IdType;           /*!< Specifies the identifier type.
                                  This parameter can be a value of @ref FDCAN_id_type       */

  uint32_t FilterIndex;      /*!< Specifies the filter which will be initialized.
                                  This parameter must be a number between:
                                   - 0 and (SRAMCAN_FLS_NBR-1), if IdType is FDCAN_STANDARD_ID
                                   - 0 and (SRAMCAN_FLE_NBR-1), if IdType is FDCAN_EXTENDED_ID */

  uint32_t FilterType;       /*!< Specifies the filter type.
                                  This parameter can be a value of @ref FDCAN_filter_type.
                                  The value FDCAN_FILTER_RANGE_NO_EIDM is permitted
                                  only when IdType is FDCAN_EXTENDED_ID.                    */

  uint32_t FilterConfig;     /*!< Specifies the filter configuration.
                                  This parameter can be a value of @ref FDCAN_filter_config */

  uint32_t FilterID1;        /*!< Specifies the filter identification 1.
                                  This parameter must be a number between:
                                   - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                   - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID       */

  uint32_t FilterID2;        /*!< Specifies the filter identification 2.
                                  This parameter must be a number between:
                                   - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                   - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID       */

} FDCAN_FilterTypeDef;

/**
  * @brief  FDCAN Tx header structure definition
  */
typedef struct
{
  uint32_t Identifier;          /*!< Specifies the identifier.
                                     This parameter must be a number between:
                                      - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                      - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID               */

  uint32_t IdType;              /*!< Specifies the identifier type for the message that will be
                                     transmitted.
                                     This parameter can be a value of @ref FDCAN_id_type               */

  uint32_t TxFrameType;         /*!< Specifies the frame type of the message that will be transmitted.
                                     This parameter can be a value of @ref FDCAN_frame_type            */

  uint32_t DataLength;          /*!< Specifies the length of the frame that will be transmitted.
                                      This parameter can be a value of @ref FDCAN_data_length_code     */

  uint32_t ErrorStateIndicator; /*!< Specifies the error state indicator.
                                     This parameter can be a value of @ref FDCAN_error_state_indicator */

  uint32_t BitRateSwitch;       /*!< Specifies whether the Tx frame will be transmitted with or without
                                     bit rate switching.
                                     This parameter can be a value of @ref FDCAN_bit_rate_switching    */

  uint32_t FDFormat;            /*!< Specifies whether the Tx frame will be transmitted in classic or
                                     FD format.
                                     This parameter can be a value of @ref FDCAN_format                */

  uint32_t TxEventFifoControl;  /*!< Specifies the event FIFO control.
                                     This parameter can be a value of @ref FDCAN_EFC                   */

  uint32_t MessageMarker;       /*!< Specifies the message marker to be copied into Tx Event FIFO
                                     element for identification of Tx message status.
                                     This parameter must be a number between 0 and 0xFF                */

} FDCAN_TxHeaderTypeDef;

/**
  * @brief  FDCAN Rx header structure definition
  */
typedef struct
{
  uint32_t Identifier;            /*!< Specifies the identifier.
                                       This parameter must be a number between:
                                        - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                        - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID               */

  uint32_t IdType;                /*!< Specifies the identifier type of the received message.
                                       This parameter can be a value of @ref FDCAN_id_type               */

  uint32_t RxFrameType;           /*!< Specifies the the received message frame type.
                                       This parameter can be a value of @ref FDCAN_frame_type            */

  uint32_t DataLength;            /*!< Specifies the received frame length.
                                        This parameter can be a value of @ref FDCAN_data_length_code     */

  uint32_t ErrorStateIndicator;   /*!< Specifies the error state indicator.
                                       This parameter can be a value of @ref FDCAN_error_state_indicator */

  uint32_t BitRateSwitch;         /*!< Specifies whether the Rx frame is received with or without bit
                                       rate switching.
                                       This parameter can be a value of @ref FDCAN_bit_rate_switching    */

  uint32_t FDFormat;              /*!< Specifies whether the Rx frame is received in classic or FD
                                       format.
                                       This parameter can be a value of @ref FDCAN_format                */

  uint32_t RxTimestamp;           /*!< Specifies the timestamp counter value captured on start of frame
                                       reception.
                                       This parameter must be a number between 0 and 0xFFFF              */

  uint32_t FilterIndex;           /*!< Specifies the index of matching Rx acceptance filter element.
                                       This parameter must be a number between:
                                        - 0 and (SRAMCAN_FLS_NBR-1), if IdType is FDCAN_STANDARD_ID
                                        - 0 and (SRAMCAN_FLE_NBR-1), if IdType is FDCAN_EXTENDED_ID */

  uint32_t IsFilterMatchingFrame; /*!< Specifies whether the accepted frame did not match any Rx filter.
                                         Acceptance of non-matching frames may be enabled via
                                         HAL_FDCAN_ConfigGlobalFilter().
                                         This parameter can be 0 or 1                                    */

} FDCAN_RxHeaderTypeDef;

/**
  * @brief  FDCAN Tx event FIFO structure definition
  */
typedef struct
{
  uint32_t Identifier;          /*!< Specifies the identifier.
                                     This parameter must be a number between:
                                      - 0 and 0x7FF, if IdType is FDCAN_STANDARD_ID
                                      - 0 and 0x1FFFFFFF, if IdType is FDCAN_EXTENDED_ID               */

  uint32_t IdType;              /*!< Specifies the identifier type for the transmitted message.
                                     This parameter can be a value of @ref FDCAN_id_type               */

  uint32_t TxFrameType;         /*!< Specifies the frame type of the transmitted message.
                                     This parameter can be a value of @ref FDCAN_frame_type            */

  uint32_t DataLength;          /*!< Specifies the length of the transmitted frame.
                                     This parameter can be a value of @ref FDCAN_data_length_code      */

  uint32_t ErrorStateIndicator; /*!< Specifies the error state indicator.
                                     This parameter can be a value of @ref FDCAN_error_state_indicator */

  uint32_t BitRateSwitch;       /*!< Specifies whether the Tx frame is transmitted with or without bit
                                     rate switching.
                                     This parameter can be a value of @ref FDCAN_bit_rate_switching    */

  uint32_t FDFormat;            /*!< Specifies whether the Tx frame is transmitted in classic or FD
                                     format.
                                     This parameter can be a value of @ref FDCAN_format                */

  uint32_t TxTimestamp;         /*!< Specifies the timestamp counter value captured on start of frame
                                     transmission.
                                     This parameter must be a number between 0 and 0xFFFF              */

  uint32_t MessageMarker;       /*!< Specifies the message marker copied into Tx Event FIFO element
                                     for identification of Tx message status.
                                     This parameter must be a number between 0 and 0xFF                */

  uint32_t EventType;           /*!< Specifies the event type.
                                     This parameter can be a value of @ref FDCAN_event_type            */

} FDCAN_TxEventFifoTypeDef;

/**
  * @brief  FDCAN High Priority Message Status structure definition
  */
typedef struct
{
  uint32_t FilterList;     /*!< Specifies the filter list of the matching filter element.
                                This parameter can be:
                                 - 0 : Standard Filter List
                                 - 1 : Extended Filter List                                */

  uint32_t FilterIndex;    /*!< Specifies the index of matching filter element.
                                This parameter can be a number between:
                                - 0 and (SRAMCAN_FLS_NBR-1), if FilterList is 0 (Standard)
                                - 0 and (SRAMCAN_FLE_NBR-1), if FilterList is 1 (Extended) */

  uint32_t MessageStorage; /*!< Specifies the HP Message Storage.
                                This parameter can be a value of @ref FDCAN_hp_msg_storage */

  uint32_t MessageIndex;   /*!< Specifies the Index of Rx FIFO element to which the
                                message was stored.
                                This parameter is valid only when MessageStorage is:
                                  FDCAN_HP_STORAGE_RXFIFO0
                                 or
                                  FDCAN_HP_STORAGE_RXFIFO1                                 */

} FDCAN_HpMsgStatusTypeDef;

/**
  * @brief FDCAN Protocol Status structure definition
  */
typedef struct
{
  uint32_t LastErrorCode;     /*!< Specifies the type of the last error that occurred on the FDCAN bus.
                                   This parameter can be a value of @ref FDCAN_protocol_error_code                           */

  uint32_t DataLastErrorCode; /*!< Specifies the type of the last error that occurred in the data phase of a CAN FD format
                                   frame with its BRS flag set.
                                   This parameter can be a value of @ref FDCAN_protocol_error_code                           */

  uint32_t Activity;          /*!< Specifies the FDCAN module communication state.
                                   This parameter can be a value of @ref FDCAN_communication_state                           */

  uint32_t ErrorPassive;      /*!< Specifies the FDCAN module error status.
                                   This parameter can be:
                                    - 0 : The FDCAN is in Error_Active state
                                    - 1 : The FDCAN is in Error_Passive state                                                */

  uint32_t Warning;           /*!< Specifies the FDCAN module warning status.
                                   This parameter can be:
                                    - 0 : error counters (RxErrorCnt and TxErrorCnt) are below the Error_Warning limit of 96
                                    - 1 : at least one of error counters has reached the Error_Warning limit of 96           */

  uint32_t BusOff;            /*!< Specifies the FDCAN module Bus_Off status.
                                   This parameter can be:
                                    - 0 : The FDCAN is not in Bus_Off state
                                    - 1 : The FDCAN is in Bus_Off state                                                      */

  uint32_t RxESIflag;         /*!< Specifies ESI flag of last received CAN FD message.
                                   This parameter can be:
                                    - 0 : Last received CAN FD message did not have its ESI flag set
                                    - 1 : Last received CAN FD message had its ESI flag set                                  */

  uint32_t RxBRSflag;         /*!< Specifies BRS flag of last received CAN FD message.
                                   This parameter can be:
                                    - 0 : Last received CAN FD message did not have its BRS flag set
                                    - 1 : Last received CAN FD message had its BRS flag set                                  */

  uint32_t RxFDFflag;         /*!< Specifies if CAN FD message (FDF flag set) has been received since last protocol status
                                   This parameter can be:
                                    - 0 : No CAN FD message received
                                    - 1 : CAN FD message received                                                            */

  uint32_t ProtocolException; /*!< Specifies the FDCAN module Protocol Exception status.
                                   This parameter can be:
                                    - 0 : No protocol exception event occurred since last read access
                                    - 1 : Protocol exception event occurred                                                  */

  uint32_t TDCvalue;          /*!< Specifies the Transmitter Delay Compensation Value.
                                   This parameter can be a number between 0 and 127                                          */

} FDCAN_ProtocolStatusTypeDef;

/**
  * @brief FDCAN Error Counters structure definition
  */
typedef struct
{
  uint32_t TxErrorCnt;     /*!< Specifies the Transmit Error Counter Value.
                                This parameter can be a number between 0 and 255                                         */

  uint32_t RxErrorCnt;     /*!< Specifies the Receive Error Counter Value.
                                This parameter can be a number between 0 and 127                                         */

  uint32_t RxErrorPassive; /*!< Specifies the Receive Error Passive status.
                                This parameter can be:
                                 - 0 : The Receive Error Counter (RxErrorCnt) is below the error passive level of 128
                                 - 1 : The Receive Error Counter (RxErrorCnt) has reached the error passive level of 128 */

  uint32_t ErrorLogging;   /*!< Specifies the Transmit/Receive error logging counter value.
                                This parameter can be a number between 0 and 255.
                                This counter is incremented each time when a FDCAN protocol error causes the TxErrorCnt
                                or the RxErrorCnt to be incremented. The counter stops at 255; the next increment of
                                TxErrorCnt or RxErrorCnt sets interrupt flag FDCAN_FLAG_ERROR_LOGGING_OVERFLOW           */

} FDCAN_ErrorCountersTypeDef;

/**
  * @brief  FDCAN Message RAM blocks
  */
typedef struct
{
  uint32_t StandardFilterSA; /*!< Specifies the Standard Filter List Start Address.
                                  This parameter must be a 32-bit word address      */

  uint32_t ExtendedFilterSA; /*!< Specifies the Extended Filter List Start Address.
                                  This parameter must be a 32-bit word address      */

  uint32_t RxFIFO0SA;        /*!< Specifies the Rx FIFO 0 Start Address.
                                  This parameter must be a 32-bit word address      */

  uint32_t RxFIFO1SA;        /*!< Specifies the Rx FIFO 1 Start Address.
                                  This parameter must be a 32-bit word address      */

  uint32_t TxEventFIFOSA;    /*!< Specifies the Tx Event FIFO Start Address.
                                  This parameter must be a 32-bit word address      */

  uint32_t TxFIFOQSA;        /*!< Specifies the Tx FIFO/Queue Start Address.
                                  This parameter must be a 32-bit word address      */

} FDCAN_MsgRamAddressTypeDef;

/**
  * @brief  FDCAN handle structure definition
  */
#if USE_HAL_FDCAN_REGISTER_CALLBACKS == 1
typedef struct __FDCAN_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
{
  FDCAN_GlobalTypeDef         *Instance;        /*!< Register base address     */

  FDCAN_InitTypeDef           Init;             /*!< FDCAN required parameters */

  FDCAN_MsgRamAddressTypeDef  msgRam;           /*!< FDCAN Message RAM blocks  */

  uint32_t                    LatestTxFifoQRequest; /*!< FDCAN Tx buffer index
                                               of latest Tx FIFO/Queue request */

  __IO HAL_FDCAN_StateTypeDef State;            /*!< FDCAN communication state */

  HAL_LockTypeDef             Lock;             /*!< FDCAN locking object      */

  __IO uint32_t               ErrorCode;        /*!< FDCAN Error code          */

#if USE_HAL_FDCAN_REGISTER_CALLBACKS == 1
  void (* TxEventFifoCallback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t TxEventFifoITs);     /*!< FDCAN Tx Event Fifo callback         */
  void (* RxFifo0Callback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);             /*!< FDCAN Rx Fifo 0 callback             */
  void (* RxFifo1Callback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs);             /*!< FDCAN Rx Fifo 1 callback             */
  void (* TxFifoEmptyCallback)(struct __FDCAN_HandleTypeDef *hfdcan);                              /*!< FDCAN Tx Fifo Empty callback         */
  void (* TxBufferCompleteCallback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes); /*!< FDCAN Tx Buffer complete callback    */
  void (* TxBufferAbortCallback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes);    /*!< FDCAN Tx Buffer abort callback       */
  void (* HighPriorityMessageCallback)(struct __FDCAN_HandleTypeDef *hfdcan);                      /*!< FDCAN High priority message callback */
  void (* TimestampWraparoundCallback)(struct __FDCAN_HandleTypeDef *hfdcan);                      /*!< FDCAN Timestamp wraparound callback  */
  void (* TimeoutOccurredCallback)(struct __FDCAN_HandleTypeDef *hfdcan);                          /*!< FDCAN Timeout occurred callback      */
  void (* ErrorCallback)(struct __FDCAN_HandleTypeDef *hfdcan);                                    /*!< FDCAN Error callback                 */
  void (* ErrorStatusCallback)(struct __FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs);     /*!< FDCAN Error status callback          */

  void (* MspInitCallback)(struct __FDCAN_HandleTypeDef *hfdcan);                                  /*!< FDCAN Msp Init callback              */
  void (* MspDeInitCallback)(struct __FDCAN_HandleTypeDef *hfdcan);                                /*!< FDCAN Msp DeInit callback            */

#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */

} FDCAN_HandleTypeDef;

#if USE_HAL_FDCAN_REGISTER_CALLBACKS == 1
/**
  * @brief  HAL FDCAN common Callback ID enumeration definition
  */
typedef enum
{
  HAL_FDCAN_TX_FIFO_EMPTY_CB_ID        = 0x00U,    /*!< FDCAN Tx Fifo Empty callback ID         */
  HAL_FDCAN_HIGH_PRIO_MESSAGE_CB_ID    = 0x01U,    /*!< FDCAN High priority message callback ID */
  HAL_FDCAN_TIMESTAMP_WRAPAROUND_CB_ID = 0x02U,    /*!< FDCAN Timestamp wraparound callback ID  */
  HAL_FDCAN_TIMEOUT_OCCURRED_CB_ID     = 0x03U,    /*!< FDCAN Timeout occurred callback ID      */
  HAL_FDCAN_ERROR_CALLBACK_CB_ID       = 0x04U,    /*!< FDCAN Error callback ID                 */

  HAL_FDCAN_MSPINIT_CB_ID              = 0x05U,    /*!< FDCAN MspInit callback ID               */
  HAL_FDCAN_MSPDEINIT_CB_ID            = 0x06U,    /*!< FDCAN MspDeInit callback ID             */

} HAL_FDCAN_CallbackIDTypeDef;

/**
  * @brief  HAL FDCAN Callback pointer definition
  */
typedef  void (*pFDCAN_CallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan);                                         /*!< pointer to a common FDCAN callback function           */
typedef  void (*pFDCAN_TxEventFifoCallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t TxEventFifoITs);     /*!< pointer to Tx event Fifo FDCAN callback function      */
typedef  void (*pFDCAN_RxFifo0CallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);             /*!< pointer to Rx Fifo 0 FDCAN callback function          */
typedef  void (*pFDCAN_RxFifo1CallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs);             /*!< pointer to Rx Fifo 1 FDCAN callback function          */
typedef  void (*pFDCAN_TxBufferCompleteCallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes); /*!< pointer to Tx Buffer complete FDCAN callback function */
typedef  void (*pFDCAN_TxBufferAbortCallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes);    /*!< pointer to Tx Buffer abort FDCAN callback function    */
typedef  void (*pFDCAN_ErrorStatusCallbackTypeDef)(FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs);     /*!< pointer to Error Status callback function             */

#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FDCAN_Exported_Constants FDCAN Exported Constants
  * @{
  */

/** @defgroup HAL_FDCAN_Error_Code HAL FDCAN Error Code
  * @{
  */
#define HAL_FDCAN_ERROR_NONE            ((uint32_t)0x00000000U) /*!< No error                                                               */
#define HAL_FDCAN_ERROR_TIMEOUT         ((uint32_t)0x00000001U) /*!< Timeout error                                                          */
#define HAL_FDCAN_ERROR_NOT_INITIALIZED ((uint32_t)0x00000002U) /*!< Peripheral not initialized                                             */
#define HAL_FDCAN_ERROR_NOT_READY       ((uint32_t)0x00000004U) /*!< Peripheral not ready                                                   */
#define HAL_FDCAN_ERROR_NOT_STARTED     ((uint32_t)0x00000008U) /*!< Peripheral not started                                                 */
#define HAL_FDCAN_ERROR_NOT_SUPPORTED   ((uint32_t)0x00000010U) /*!< Mode not supported                                                     */
#define HAL_FDCAN_ERROR_PARAM           ((uint32_t)0x00000020U) /*!< Parameter error                                                        */
#define HAL_FDCAN_ERROR_PENDING         ((uint32_t)0x00000040U) /*!< Pending operation                                                      */
#define HAL_FDCAN_ERROR_RAM_ACCESS      ((uint32_t)0x00000080U) /*!< Message RAM Access Failure                                             */
#define HAL_FDCAN_ERROR_FIFO_EMPTY      ((uint32_t)0x00000100U) /*!< Put element in full FIFO                                               */
#define HAL_FDCAN_ERROR_FIFO_FULL       ((uint32_t)0x00000200U) /*!< Get element from empty FIFO                                            */
#define HAL_FDCAN_ERROR_LOG_OVERFLOW    FDCAN_IR_ELO            /*!< Overflow of CAN Error Logging Counter                                  */
#define HAL_FDCAN_ERROR_RAM_WDG         FDCAN_IR_WDI            /*!< Message RAM Watchdog event occurred                                    */
#define HAL_FDCAN_ERROR_PROTOCOL_ARBT   FDCAN_IR_PEA            /*!< Protocol Error in Arbitration Phase (Nominal Bit Time is used)         */
#define HAL_FDCAN_ERROR_PROTOCOL_DATA   FDCAN_IR_PED            /*!< Protocol Error in Data Phase (Data Bit Time is used)                   */
#define HAL_FDCAN_ERROR_RESERVED_AREA   FDCAN_IR_ARA            /*!< Access to Reserved Address                                             */

#if USE_HAL_FDCAN_REGISTER_CALLBACKS == 1
#define HAL_FDCAN_ERROR_INVALID_CALLBACK ((uint32_t)0x00000100U) /*!< Invalid Callback error                                                */
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup FDCAN_frame_format FDCAN Frame Format
  * @{
  */
#define FDCAN_FRAME_CLASSIC   ((uint32_t)0x00000000U)                         /*!< Classic mode                      */
#define FDCAN_FRAME_FD_NO_BRS ((uint32_t)FDCAN_CCCR_FDOE)                     /*!< FD mode without BitRate Switching */
#define FDCAN_FRAME_FD_BRS    ((uint32_t)(FDCAN_CCCR_FDOE | FDCAN_CCCR_BRSE)) /*!< FD mode with BitRate Switching    */
/**
  * @}
  */

/** @defgroup FDCAN_operating_mode FDCAN Operating Mode
  * @{
  */
#define FDCAN_MODE_NORMAL               ((uint32_t)0x00000000U) /*!< Normal mode               */
#define FDCAN_MODE_RESTRICTED_OPERATION ((uint32_t)0x00000001U) /*!< Restricted Operation mode */
#define FDCAN_MODE_BUS_MONITORING       ((uint32_t)0x00000002U) /*!< Bus Monitoring mode       */
#define FDCAN_MODE_INTERNAL_LOOPBACK    ((uint32_t)0x00000003U) /*!< Internal LoopBack mode    */
#define FDCAN_MODE_EXTERNAL_LOOPBACK    ((uint32_t)0x00000004U) /*!< External LoopBack mode    */
/**
  * @}
  */

/** @defgroup FDCAN_clock_divider FDCAN Clock Divider
  * @{
  */
#define FDCAN_CLOCK_DIV1  ((uint32_t)0x00000000U) /*!< Divide kernel clock by 1  */
#define FDCAN_CLOCK_DIV2  ((uint32_t)0x00000001U) /*!< Divide kernel clock by 2  */
#define FDCAN_CLOCK_DIV4  ((uint32_t)0x00000002U) /*!< Divide kernel clock by 4  */
#define FDCAN_CLOCK_DIV6  ((uint32_t)0x00000003U) /*!< Divide kernel clock by 6  */
#define FDCAN_CLOCK_DIV8  ((uint32_t)0x00000004U) /*!< Divide kernel clock by 8  */
#define FDCAN_CLOCK_DIV10 ((uint32_t)0x00000005U) /*!< Divide kernel clock by 10 */
#define FDCAN_CLOCK_DIV12 ((uint32_t)0x00000006U) /*!< Divide kernel clock by 12 */
#define FDCAN_CLOCK_DIV14 ((uint32_t)0x00000007U) /*!< Divide kernel clock by 14 */
#define FDCAN_CLOCK_DIV16 ((uint32_t)0x00000008U) /*!< Divide kernel clock by 16 */
#define FDCAN_CLOCK_DIV18 ((uint32_t)0x00000009U) /*!< Divide kernel clock by 18 */
#define FDCAN_CLOCK_DIV20 ((uint32_t)0x0000000AU) /*!< Divide kernel clock by 20 */
#define FDCAN_CLOCK_DIV22 ((uint32_t)0x0000000BU) /*!< Divide kernel clock by 22 */
#define FDCAN_CLOCK_DIV24 ((uint32_t)0x0000000CU) /*!< Divide kernel clock by 24 */
#define FDCAN_CLOCK_DIV26 ((uint32_t)0x0000000DU) /*!< Divide kernel clock by 26 */
#define FDCAN_CLOCK_DIV28 ((uint32_t)0x0000000EU) /*!< Divide kernel clock by 28 */
#define FDCAN_CLOCK_DIV30 ((uint32_t)0x0000000FU) /*!< Divide kernel clock by 30 */
/**
  * @}
  */

/** @defgroup FDCAN_txFifoQueue_Mode FDCAN Tx FIFO/Queue Mode
  * @{
  */
#define FDCAN_TX_FIFO_OPERATION  ((uint32_t)0x00000000U)     /*!< FIFO mode  */
#define FDCAN_TX_QUEUE_OPERATION ((uint32_t)FDCAN_TXBC_TFQM) /*!< Queue mode */
/**
  * @}
  */

/** @defgroup FDCAN_id_type FDCAN ID Type
  * @{
  */
#define FDCAN_STANDARD_ID ((uint32_t)0x00000000U) /*!< Standard ID element */
#define FDCAN_EXTENDED_ID ((uint32_t)0x40000000U) /*!< Extended ID element */
/**
  * @}
  */

/** @defgroup FDCAN_frame_type FDCAN Frame Type
  * @{
  */
#define FDCAN_DATA_FRAME   ((uint32_t)0x00000000U)  /*!< Data frame   */
#define FDCAN_REMOTE_FRAME ((uint32_t)0x20000000U)  /*!< Remote frame */
/**
  * @}
  */

/** @defgroup FDCAN_data_length_code FDCAN Data Length Code
  * @{
  */
#define FDCAN_DLC_BYTES_0  ((uint32_t)0x00000000U) /*!< 0 bytes data field  */
#define FDCAN_DLC_BYTES_1  ((uint32_t)0x00010000U) /*!< 1 bytes data field  */
#define FDCAN_DLC_BYTES_2  ((uint32_t)0x00020000U) /*!< 2 bytes data field  */
#define FDCAN_DLC_BYTES_3  ((uint32_t)0x00030000U) /*!< 3 bytes data field  */
#define FDCAN_DLC_BYTES_4  ((uint32_t)0x00040000U) /*!< 4 bytes data field  */
#define FDCAN_DLC_BYTES_5  ((uint32_t)0x00050000U) /*!< 5 bytes data field  */
#define FDCAN_DLC_BYTES_6  ((uint32_t)0x00060000U) /*!< 6 bytes data field  */
#define FDCAN_DLC_BYTES_7  ((uint32_t)0x00070000U) /*!< 7 bytes data field  */
#define FDCAN_DLC_BYTES_8  ((uint32_t)0x00080000U) /*!< 8 bytes data field  */
#define FDCAN_DLC_BYTES_12 ((uint32_t)0x00090000U) /*!< 12 bytes data field */
#define FDCAN_DLC_BYTES_16 ((uint32_t)0x000A0000U) /*!< 16 bytes data field */
#define FDCAN_DLC_BYTES_20 ((uint32_t)0x000B0000U) /*!< 20 bytes data field */
#define FDCAN_DLC_BYTES_24 ((uint32_t)0x000C0000U) /*!< 24 bytes data field */
#define FDCAN_DLC_BYTES_32 ((uint32_t)0x000D0000U) /*!< 32 bytes data field */
#define FDCAN_DLC_BYTES_48 ((uint32_t)0x000E0000U) /*!< 48 bytes data field */
#define FDCAN_DLC_BYTES_64 ((uint32_t)0x000F0000U) /*!< 64 bytes data field */
/**
  * @}
  */

/** @defgroup FDCAN_error_state_indicator FDCAN Error State Indicator
  * @{
  */
#define FDCAN_ESI_ACTIVE  ((uint32_t)0x00000000U) /*!< Transmitting node is error active  */
#define FDCAN_ESI_PASSIVE ((uint32_t)0x80000000U) /*!< Transmitting node is error passive */
/**
  * @}
  */

/** @defgroup FDCAN_bit_rate_switching FDCAN Bit Rate Switching
  * @{
  */
#define FDCAN_BRS_OFF ((uint32_t)0x00000000U) /*!< FDCAN frames transmitted/received without bit rate switching */
#define FDCAN_BRS_ON  ((uint32_t)0x00100000U) /*!< FDCAN frames transmitted/received with bit rate switching    */
/**
  * @}
  */

/** @defgroup FDCAN_format FDCAN format
  * @{
  */
#define FDCAN_CLASSIC_CAN ((uint32_t)0x00000000U) /*!< Frame transmitted/received in Classic CAN format */
#define FDCAN_FD_CAN      ((uint32_t)0x00200000U) /*!< Frame transmitted/received in FDCAN format       */
/**
  * @}
  */

/** @defgroup FDCAN_EFC FDCAN Event FIFO control
  * @{
  */
#define FDCAN_NO_TX_EVENTS    ((uint32_t)0x00000000U) /*!< Do not store Tx events */
#define FDCAN_STORE_TX_EVENTS ((uint32_t)0x00800000U) /*!< Store Tx events        */
/**
  * @}
  */

/** @defgroup FDCAN_filter_type FDCAN Filter Type
  * @{
  */
#define FDCAN_FILTER_RANGE         ((uint32_t)0x00000000U) /*!< Range filter from FilterID1 to FilterID2                        */
#define FDCAN_FILTER_DUAL          ((uint32_t)0x00000001U) /*!< Dual ID filter for FilterID1 or FilterID2                       */
#define FDCAN_FILTER_MASK          ((uint32_t)0x00000002U) /*!< Classic filter: FilterID1 = filter, FilterID2 = mask            */
#define FDCAN_FILTER_RANGE_NO_EIDM ((uint32_t)0x00000003U) /*!< Range filter from FilterID1 to FilterID2, EIDM mask not applied */
/**
  * @}
  */

/** @defgroup FDCAN_filter_config FDCAN Filter Configuration
  * @{
  */
#define FDCAN_FILTER_DISABLE       ((uint32_t)0x00000000U) /*!< Disable filter element                                    */
#define FDCAN_FILTER_TO_RXFIFO0    ((uint32_t)0x00000001U) /*!< Store in Rx FIFO 0 if filter matches                      */
#define FDCAN_FILTER_TO_RXFIFO1    ((uint32_t)0x00000002U) /*!< Store in Rx FIFO 1 if filter matches                      */
#define FDCAN_FILTER_REJECT        ((uint32_t)0x00000003U) /*!< Reject ID if filter matches                               */
#define FDCAN_FILTER_HP            ((uint32_t)0x00000004U) /*!< Set high priority if filter matches                       */
#define FDCAN_FILTER_TO_RXFIFO0_HP ((uint32_t)0x00000005U) /*!< Set high priority and store in FIFO 0 if filter matches   */
#define FDCAN_FILTER_TO_RXFIFO1_HP ((uint32_t)0x00000006U) /*!< Set high priority and store in FIFO 1 if filter matches   */
/**
  * @}
  */

/** @defgroup FDCAN_Tx_location FDCAN Tx Location
  * @{
  */
#define FDCAN_TX_BUFFER0  ((uint32_t)0x00000001U) /*!< Add message to Tx Buffer 0  */
#define FDCAN_TX_BUFFER1  ((uint32_t)0x00000002U) /*!< Add message to Tx Buffer 1  */
#define FDCAN_TX_BUFFER2  ((uint32_t)0x00000004U) /*!< Add message to Tx Buffer 2  */
/**
  * @}
  */

/** @defgroup FDCAN_Rx_location FDCAN Rx Location
  * @{
  */
#define FDCAN_RX_FIFO0    ((uint32_t)0x00000040U) /*!< Get received message from Rx FIFO 0    */
#define FDCAN_RX_FIFO1    ((uint32_t)0x00000041U) /*!< Get received message from Rx FIFO 1    */
/**
  * @}
  */

/** @defgroup FDCAN_event_type FDCAN Event Type
  * @{
  */
#define FDCAN_TX_EVENT             ((uint32_t)0x00400000U) /*!< Tx event                              */
#define FDCAN_TX_IN_SPITE_OF_ABORT ((uint32_t)0x00800000U) /*!< Transmission in spite of cancellation */
/**
  * @}
  */

/** @defgroup FDCAN_hp_msg_storage FDCAN High Priority Message Storage
  * @{
  */
#define FDCAN_HP_STORAGE_NO_FIFO  ((uint32_t)0x00000000U) /*!< No FIFO selected         */
#define FDCAN_HP_STORAGE_MSG_LOST ((uint32_t)0x00000040U) /*!< FIFO message lost        */
#define FDCAN_HP_STORAGE_RXFIFO0  ((uint32_t)0x00000080U) /*!< Message stored in FIFO 0 */
#define FDCAN_HP_STORAGE_RXFIFO1  ((uint32_t)0x000000C0U) /*!< Message stored in FIFO 1 */
/**
  * @}
  */

/** @defgroup FDCAN_protocol_error_code FDCAN protocol error code
  * @{
  */
#define FDCAN_PROTOCOL_ERROR_NONE      ((uint32_t)0x00000000U) /*!< No error occurred         */
#define FDCAN_PROTOCOL_ERROR_STUFF     ((uint32_t)0x00000001U) /*!< Stuff error               */
#define FDCAN_PROTOCOL_ERROR_FORM      ((uint32_t)0x00000002U) /*!< Form error                */
#define FDCAN_PROTOCOL_ERROR_ACK       ((uint32_t)0x00000003U) /*!< Acknowledge error         */
#define FDCAN_PROTOCOL_ERROR_BIT1      ((uint32_t)0x00000004U) /*!< Bit 1 (recessive) error   */
#define FDCAN_PROTOCOL_ERROR_BIT0      ((uint32_t)0x00000005U) /*!< Bit 0 (dominant) error    */
#define FDCAN_PROTOCOL_ERROR_CRC       ((uint32_t)0x00000006U) /*!< CRC check sum error       */
#define FDCAN_PROTOCOL_ERROR_NO_CHANGE ((uint32_t)0x00000007U) /*!< No change since last read */
/**
  * @}
  */

/** @defgroup FDCAN_communication_state FDCAN communication state
  * @{
  */
#define FDCAN_COM_STATE_SYNC ((uint32_t)0x00000000U) /*!< Node is synchronizing on CAN communication */
#define FDCAN_COM_STATE_IDLE ((uint32_t)0x00000008U) /*!< Node is neither receiver nor transmitter   */
#define FDCAN_COM_STATE_RX   ((uint32_t)0x00000010U) /*!< Node is operating as receiver              */
#define FDCAN_COM_STATE_TX   ((uint32_t)0x00000018U) /*!< Node is operating as transmitter           */
/**
  * @}
  */

/** @defgroup FDCAN_Rx_FIFO_operation_mode FDCAN FIFO operation mode
  * @{
  */
#define FDCAN_RX_FIFO_BLOCKING  ((uint32_t)0x00000000U) /*!< Rx FIFO blocking mode  */
#define FDCAN_RX_FIFO_OVERWRITE ((uint32_t)0x00000001U) /*!< Rx FIFO overwrite mode */
/**
  * @}
  */

/** @defgroup FDCAN_Non_Matching_Frames FDCAN non-matching frames
  * @{
  */
#define FDCAN_ACCEPT_IN_RX_FIFO0 ((uint32_t)0x00000000U) /*!< Accept in Rx FIFO 0 */
#define FDCAN_ACCEPT_IN_RX_FIFO1 ((uint32_t)0x00000001U) /*!< Accept in Rx FIFO 1 */
#define FDCAN_REJECT             ((uint32_t)0x00000002U) /*!< Reject              */
/**
  * @}
  */

/** @defgroup FDCAN_Reject_Remote_Frames FDCAN reject remote frames
  * @{
  */
#define FDCAN_FILTER_REMOTE ((uint32_t)0x00000000U) /*!< Filter remote frames */
#define FDCAN_REJECT_REMOTE ((uint32_t)0x00000001U) /*!< Reject all remote frames */
/**
  * @}
  */

/** @defgroup FDCAN_Interrupt_Line FDCAN interrupt line
  * @{
  */
#define FDCAN_INTERRUPT_LINE0 ((uint32_t)0x00000001U) /*!< Interrupt Line 0 */
#define FDCAN_INTERRUPT_LINE1 ((uint32_t)0x00000002U) /*!< Interrupt Line 1 */
/**
  * @}
  */

/** @defgroup FDCAN_Timestamp FDCAN timestamp
  * @{
  */
#define FDCAN_TIMESTAMP_INTERNAL ((uint32_t)0x00000001U) /*!< Timestamp counter value incremented according to TCP */
#define FDCAN_TIMESTAMP_EXTERNAL ((uint32_t)0x00000002U) /*!< External timestamp counter value used                */
/**
  * @}
  */

/** @defgroup FDCAN_Timestamp_Prescaler FDCAN timestamp prescaler
  * @{
  */
#define FDCAN_TIMESTAMP_PRESC_1  ((uint32_t)0x00000000U) /*!< Timestamp counter time unit in equal to CAN bit time                 */
#define FDCAN_TIMESTAMP_PRESC_2  ((uint32_t)0x00010000U) /*!< Timestamp counter time unit in equal to CAN bit time multiplied by 2  */
#define FDCAN_TIMESTAMP_PRESC_3  ((uint32_t)0x00020000U) /*!< Timestamp counter time unit in equal to CAN bit time multiplied by 3  */
#define FDCAN_TIMESTAMP_PRESC_4  ((uint32_t)0x00030000U) /*!< Timestamp counter time unit in equal to CAN bit time multiplied by 4  */
#define FDCAN_TIMESTAMP_PRESC_5  ((uint32_t)0x00040000U) /*!< Timestamp counter time unit in equal to CAN bit time multiplied by 5  */
#define FDCAN_TIMESTAMP_PRESC_6  ((uint32_t)0x00050000U) /*!< Timestamp counter time unit in equal to CAN bit time multiplied by 6  */
#define FDCAN_TIMESTAMP_PRESC_7  ((uint32_t)0x00060000U) /*!< Timestamp counter time unit in equal to CAN bit time multiplied by 7  */
#define FDCAN_TIMESTAMP_PRESC_8  ((uint32_t)0x00070000U) /*!< Timestamp counter time unit in equal to CAN bit time multiplied by 8  */
#define FDCAN_TIMESTAMP_PRESC_9  ((uint32_t)0x00080000U) /*!< Timestamp counter time unit in equal to CAN bit time multiplied by 9  */
#define FDCAN_TIMESTAMP_PRESC_10 ((uint32_t)0x00090000U) /*!< Timestamp counter time unit in equal to CAN bit time multiplied by 10 */
#define FDCAN_TIMESTAMP_PRESC_11 ((uint32_t)0x000A0000U) /*!< Timestamp counter time unit in equal to CAN bit time multiplied by 11 */
#define FDCAN_TIMESTAMP_PRESC_12 ((uint32_t)0x000B0000U) /*!< Timestamp counter time unit in equal to CAN bit time multiplied by 12 */
#define FDCAN_TIMESTAMP_PRESC_13 ((uint32_t)0x000C0000U) /*!< Timestamp counter time unit in equal to CAN bit time multiplied by 13 */
#define FDCAN_TIMESTAMP_PRESC_14 ((uint32_t)0x000D0000U) /*!< Timestamp counter time unit in equal to CAN bit time multiplied by 14 */
#define FDCAN_TIMESTAMP_PRESC_15 ((uint32_t)0x000E0000U) /*!< Timestamp counter time unit in equal to CAN bit time multiplied by 15 */
#define FDCAN_TIMESTAMP_PRESC_16 ((uint32_t)0x000F0000U) /*!< Timestamp counter time unit in equal to CAN bit time multiplied by 16 */
/**
  * @}
  */

/** @defgroup FDCAN_Timeout_Operation FDCAN timeout operation
  * @{
  */
#define FDCAN_TIMEOUT_CONTINUOUS    ((uint32_t)0x00000000U) /*!< Timeout continuous operation        */
#define FDCAN_TIMEOUT_TX_EVENT_FIFO ((uint32_t)0x00000002U) /*!< Timeout controlled by Tx Event FIFO */
#define FDCAN_TIMEOUT_RX_FIFO0      ((uint32_t)0x00000004U) /*!< Timeout controlled by Rx FIFO 0     */
#define FDCAN_TIMEOUT_RX_FIFO1      ((uint32_t)0x00000006U) /*!< Timeout controlled by Rx FIFO 1     */
/**
  * @}
  */

/** @defgroup Interrupt_Masks Interrupt masks
  * @{
  */
#define FDCAN_IR_MASK ((uint32_t)0x00FFFFFFU) /*!< FDCAN interrupts mask */
#define FDCAN_ILS_MASK ((uint32_t)0x0000007FU) /*!< FDCAN interrupts group mask */
/**
  * @}
  */

/** @defgroup FDCAN_flags FDCAN Flags
  * @{
  */
#define FDCAN_FLAG_TX_COMPLETE             FDCAN_IR_TC             /*!< Transmission Completed                                */
#define FDCAN_FLAG_TX_ABORT_COMPLETE       FDCAN_IR_TCF            /*!< Transmission Cancellation Finished                    */
#define FDCAN_FLAG_TX_FIFO_EMPTY           FDCAN_IR_TFE            /*!< Tx FIFO Empty                                         */
#define FDCAN_FLAG_RX_HIGH_PRIORITY_MSG    FDCAN_IR_HPM            /*!< High priority message received                        */
#define FDCAN_FLAG_TX_EVT_FIFO_ELT_LOST    FDCAN_IR_TEFL           /*!< Tx Event FIFO element lost                            */
#define FDCAN_FLAG_TX_EVT_FIFO_FULL        FDCAN_IR_TEFF           /*!< Tx Event FIFO full                                    */
#define FDCAN_FLAG_TX_EVT_FIFO_NEW_DATA    FDCAN_IR_TEFN           /*!< Tx Handler wrote Tx Event FIFO element                */
#define FDCAN_FLAG_RX_FIFO0_MESSAGE_LOST   FDCAN_IR_RF0L           /*!< Rx FIFO 0 message lost                                */
#define FDCAN_FLAG_RX_FIFO0_FULL           FDCAN_IR_RF0F           /*!< Rx FIFO 0 full                                        */
#define FDCAN_FLAG_RX_FIFO0_NEW_MESSAGE    FDCAN_IR_RF0N           /*!< New message written to Rx FIFO 0                      */
#define FDCAN_FLAG_RX_FIFO1_MESSAGE_LOST   FDCAN_IR_RF1L           /*!< Rx FIFO 1 message lost                                */
#define FDCAN_FLAG_RX_FIFO1_FULL           FDCAN_IR_RF1F           /*!< Rx FIFO 1 full                                        */
#define FDCAN_FLAG_RX_FIFO1_NEW_MESSAGE    FDCAN_IR_RF1N           /*!< New message written to Rx FIFO 1                      */
#define FDCAN_FLAG_RAM_ACCESS_FAILURE      FDCAN_IR_MRAF           /*!< Message RAM access failure occurred                   */
#define FDCAN_FLAG_ERROR_LOGGING_OVERFLOW  FDCAN_IR_ELO            /*!< Overflow of FDCAN Error Logging Counter occurred      */
#define FDCAN_FLAG_ERROR_PASSIVE           FDCAN_IR_EP             /*!< Error_Passive status changed                          */
#define FDCAN_FLAG_ERROR_WARNING           FDCAN_IR_EW             /*!< Error_Warning status changed                          */
#define FDCAN_FLAG_BUS_OFF                 FDCAN_IR_BO             /*!< Bus_Off status changed                                */
#define FDCAN_FLAG_RAM_WATCHDOG            FDCAN_IR_WDI            /*!< Message RAM Watchdog event due to missing READY       */
#define FDCAN_FLAG_ARB_PROTOCOL_ERROR      FDCAN_IR_PEA            /*!< Protocol error in arbitration phase detected          */
#define FDCAN_FLAG_DATA_PROTOCOL_ERROR     FDCAN_IR_PED            /*!< Protocol error in data phase detected                 */
#define FDCAN_FLAG_RESERVED_ADDRESS_ACCESS FDCAN_IR_ARA            /*!< Access to reserved address occurred                   */
#define FDCAN_FLAG_TIMESTAMP_WRAPAROUND    FDCAN_IR_TSW            /*!< Timestamp counter wrapped around                      */
#define FDCAN_FLAG_TIMEOUT_OCCURRED        FDCAN_IR_TOO            /*!< Timeout reached                                       */
/**
  * @}
  */

/** @defgroup FDCAN_Interrupts FDCAN Interrupts
  * @{
  */

/** @defgroup FDCAN_Tx_Interrupts FDCAN Tx Interrupts
  * @{
  */
#define FDCAN_IT_TX_COMPLETE           FDCAN_IE_TCE   /*!< Transmission Completed                                */
#define FDCAN_IT_TX_ABORT_COMPLETE     FDCAN_IE_TCFE  /*!< Transmission Cancellation Finished                    */
#define FDCAN_IT_TX_FIFO_EMPTY         FDCAN_IE_TFEE  /*!< Tx FIFO Empty                                         */
/**
  * @}
  */

/** @defgroup FDCAN_Rx_Interrupts FDCAN Rx Interrupts
  * @{
  */
#define FDCAN_IT_RX_HIGH_PRIORITY_MSG  FDCAN_IE_HPME  /*!< High priority message received                        */
/**
  * @}
  */

/** @defgroup FDCAN_Counter_Interrupts FDCAN Counter Interrupts
  * @{
  */
#define FDCAN_IT_TIMESTAMP_WRAPAROUND  FDCAN_IE_TSWE  /*!< Timestamp counter wrapped around                      */
#define FDCAN_IT_TIMEOUT_OCCURRED      FDCAN_IE_TOOE  /*!< Timeout reached                                       */
/**
  * @}
  */

/** @defgroup FDCAN_Tx_Event_Fifo_Interrupts FDCAN Tx Event FIFO Interrupts
  * @{
  */
#define FDCAN_IT_TX_EVT_FIFO_ELT_LOST  FDCAN_IE_TEFLE /*!< Tx Event FIFO element lost                 */
#define FDCAN_IT_TX_EVT_FIFO_FULL      FDCAN_IE_TEFFE /*!< Tx Event FIFO full                         */
#define FDCAN_IT_TX_EVT_FIFO_NEW_DATA  FDCAN_IE_TEFNE /*!< Tx Handler wrote Tx Event FIFO element     */
/**
  * @}
  */

/** @defgroup FDCAN_Rx_Fifo0_Interrupts FDCAN Rx FIFO 0 Interrupts
  * @{
  */
#define FDCAN_IT_RX_FIFO0_MESSAGE_LOST FDCAN_IE_RF0LE /*!< Rx FIFO 0 message lost                 */
#define FDCAN_IT_RX_FIFO0_FULL         FDCAN_IE_RF0FE /*!< Rx FIFO 0 full                         */
#define FDCAN_IT_RX_FIFO0_NEW_MESSAGE  FDCAN_IE_RF0NE /*!< New message written to Rx FIFO 0       */
/**
  * @}
  */

/** @defgroup FDCAN_Rx_Fifo1_Interrupts FDCAN Rx FIFO 1 Interrupts
  * @{
  */
#define FDCAN_IT_RX_FIFO1_MESSAGE_LOST FDCAN_IE_RF1LE /*!< Rx FIFO 1 message lost                 */
#define FDCAN_IT_RX_FIFO1_FULL         FDCAN_IE_RF1FE /*!< Rx FIFO 1 full                         */
#define FDCAN_IT_RX_FIFO1_NEW_MESSAGE  FDCAN_IE_RF1NE /*!< New message written to Rx FIFO 1       */
/**
  * @}
  */

/** @defgroup FDCAN_Error_Interrupts FDCAN Error Interrupts
  * @{
  */
#define FDCAN_IT_RAM_ACCESS_FAILURE      FDCAN_IE_MRAFE /*!< Message RAM access failure occurred              */
#define FDCAN_IT_ERROR_LOGGING_OVERFLOW  FDCAN_IE_ELOE  /*!< Overflow of FDCAN Error Logging Counter occurred */
#define FDCAN_IT_RAM_WATCHDOG            FDCAN_IE_WDIE  /*!< Message RAM Watchdog event due to missing READY  */
#define FDCAN_IT_ARB_PROTOCOL_ERROR      FDCAN_IE_PEAE  /*!< Protocol error in arbitration phase detected     */
#define FDCAN_IT_DATA_PROTOCOL_ERROR     FDCAN_IE_PEDE  /*!< Protocol error in data phase detected            */
#define FDCAN_IT_RESERVED_ADDRESS_ACCESS FDCAN_IE_ARAE  /*!< Access to reserved address occurred              */
/**
  * @}
  */

/** @defgroup FDCAN_Error_Status_Interrupts FDCAN Error Status Interrupts
  * @{
  */
#define FDCAN_IT_ERROR_PASSIVE           FDCAN_IE_EPE   /*!< Error_Passive status changed      */
#define FDCAN_IT_ERROR_WARNING           FDCAN_IE_EWE   /*!< Error_Warning status changed      */
#define FDCAN_IT_BUS_OFF                 FDCAN_IE_BOE   /*!< Bus_Off status changed            */
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup FDCAN_Interrupts_List FDCAN Interrupts List
  * @{
  */
#define FDCAN_IT_LIST_RX_FIFO0         (FDCAN_IT_RX_FIFO0_MESSAGE_LOST | \
                                        FDCAN_IT_RX_FIFO0_FULL         | \
                                        FDCAN_IT_RX_FIFO0_NEW_MESSAGE)       /*!< RX FIFO 0 Interrupts List          */
#define FDCAN_IT_LIST_RX_FIFO1         (FDCAN_IT_RX_FIFO1_MESSAGE_LOST | \
                                        FDCAN_IT_RX_FIFO1_FULL         | \
                                        FDCAN_IT_RX_FIFO1_NEW_MESSAGE)       /*!< RX FIFO 1 Interrupts List          */
#define FDCAN_IT_LIST_SMSG             (FDCAN_IT_TX_ABORT_COMPLETE | \
                                        FDCAN_IT_TX_COMPLETE | \
                                        FDCAN_IT_RX_HIGH_PRIORITY_MSG)       /*!< Status Message Interrupts List     */
#define FDCAN_IT_LIST_TX_FIFO_ERROR    (FDCAN_IT_TX_EVT_FIFO_ELT_LOST | \
                                        FDCAN_IT_TX_EVT_FIFO_FULL | \
                                        FDCAN_IT_TX_EVT_FIFO_NEW_DATA | \
                                        FDCAN_IT_TX_FIFO_EMPTY)              /*!< TX FIFO Error Interrupts List      */
#define FDCAN_IT_LIST_MISC             (FDCAN_IT_TIMEOUT_OCCURRED | \
                                        FDCAN_IT_RAM_ACCESS_FAILURE | \
                                        FDCAN_IT_TIMESTAMP_WRAPAROUND)       /*!< Misc. Interrupts List              */
#define FDCAN_IT_LIST_BIT_LINE_ERROR   (FDCAN_IT_ERROR_PASSIVE | \
                                        FDCAN_IT_ERROR_LOGGING_OVERFLOW)     /*!< Bit and Line Error Interrupts List */
#define FDCAN_IT_LIST_PROTOCOL_ERROR   (FDCAN_IT_RESERVED_ADDRESS_ACCESS | \
                                        FDCAN_IT_DATA_PROTOCOL_ERROR | \
                                        FDCAN_IT_ARB_PROTOCOL_ERROR | \
                                        FDCAN_IT_RAM_WATCHDOG | \
                                        FDCAN_IT_BUS_OFF | \
                                        FDCAN_IT_ERROR_WARNING)              /*!< Protocol Error Interrupts List     */
/**
  * @}
  */

/** @defgroup FDCAN_Interrupts_Group FDCAN Interrupts Group
  * @{
  */
#define FDCAN_IT_GROUP_RX_FIFO0          FDCAN_ILS_RXFIFO0 /*!< RX FIFO 0 Interrupts Group:
                                                                  RF0LL: Rx FIFO 0 Message Lost
                                                                  RF0FL: Rx FIFO 0 is Full
                                                                  RF0NL: Rx FIFO 0 Has New Message            */
#define FDCAN_IT_GROUP_RX_FIFO1          FDCAN_ILS_RXFIFO1 /*!< RX FIFO 1 Interrupts Group:
                                                                  RF1LL: Rx FIFO 1 Message Lost
                                                                  RF1FL: Rx FIFO 1 is Full
                                                                  RF1NL: Rx FIFO 1 Has New Message            */
#define FDCAN_IT_GROUP_SMSG              FDCAN_ILS_SMSG    /*!< Status Message Interrupts Group:
                                                                  TCFL: Transmission Cancellation Finished
                                                                  TCL: Transmission Completed
                                                                  HPML: High Priority Message                 */
#define FDCAN_IT_GROUP_TX_FIFO_ERROR     FDCAN_ILS_TFERR   /*!< TX FIFO Error Interrupts Group:
                                                                  TEFLL: Tx Event FIFO Element Lost
                                                                  TEFFL: Tx Event FIFO Full
                                                                  TEFNL: Tx Event FIFO New Entry
                                                                  TFEL: Tx FIFO Empty Interrupt Line          */
#define FDCAN_IT_GROUP_MISC              FDCAN_ILS_MISC    /*!< Misc. Interrupts Group:
                                                                  TOOL: Timeout Occurred
                                                                  MRAFL: Message RAM Access Failure
                                                                  TSWL: Timestamp Wraparound                  */
#define FDCAN_IT_GROUP_BIT_LINE_ERROR    FDCAN_ILS_BERR    /*!< Bit and Line Error Interrupts Group:
                                                                  EPL: Error Passive
                                                                  ELOL: Error Logging Overflow                */
#define FDCAN_IT_GROUP_PROTOCOL_ERROR    FDCAN_ILS_PERR    /*!< Protocol Error Group:
                                                                  ARAL: Access to Reserved Address Line
                                                                  PEDL: Protocol Error in Data Phase Line
                                                                  PEAL: Protocol Error in Arbitration Phase Line
                                                                  WDIL: Watchdog Interrupt Line
                                                                  BOL: Bus_Off Status
                                                                  EWL: Warning Status                         */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup FDCAN_Exported_Macros FDCAN Exported Macros
  * @{
  */

/** @brief  Reset FDCAN handle state.
  * @param  __HANDLE__ FDCAN handle.
  * @retval None
  */
#if USE_HAL_FDCAN_REGISTER_CALLBACKS == 1
#define __HAL_FDCAN_RESET_HANDLE_STATE(__HANDLE__) do{                                                \
                                                      (__HANDLE__)->State = HAL_FDCAN_STATE_RESET;    \
                                                      (__HANDLE__)->MspInitCallback = NULL;           \
                                                      (__HANDLE__)->MspDeInitCallback = NULL;         \
                                                     } while(0)
#else
#define __HAL_FDCAN_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_FDCAN_STATE_RESET)
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */

/**
  * @brief  Enable the specified FDCAN interrupts.
  * @param  __HANDLE__ FDCAN handle.
  * @param  __INTERRUPT__ FDCAN interrupt.
  *         This parameter can be any combination of @arg FDCAN_Interrupts
  * @retval None
  */
#define __HAL_FDCAN_ENABLE_IT(__HANDLE__, __INTERRUPT__)             \
  (__HANDLE__)->Instance->IE |= (__INTERRUPT__)

/**
  * @brief  Disable the specified FDCAN interrupts.
  * @param  __HANDLE__ FDCAN handle.
  * @param  __INTERRUPT__ FDCAN interrupt.
  *         This parameter can be any combination of @arg FDCAN_Interrupts
  * @retval None
  */
#define __HAL_FDCAN_DISABLE_IT(__HANDLE__, __INTERRUPT__)               \
  ((__HANDLE__)->Instance->IE) &= ~(__INTERRUPT__)

/**
  * @brief  Check whether the specified FDCAN interrupt is set or not.
  * @param  __HANDLE__ FDCAN handle.
  * @param  __INTERRUPT__ FDCAN interrupt.
  *         This parameter can be one of @arg FDCAN_Interrupts
  * @retval ITStatus
  */
#define __HAL_FDCAN_GET_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IR & (__INTERRUPT__))

/**
  * @brief  Clear the specified FDCAN interrupts.
  * @param  __HANDLE__ FDCAN handle.
  * @param  __INTERRUPT__ specifies the interrupts to clear.
  *         This parameter can be any combination of @arg FDCAN_Interrupts
  * @retval None
  */
#define __HAL_FDCAN_CLEAR_IT(__HANDLE__, __INTERRUPT__)             \
  ((__HANDLE__)->Instance->IR) = (__INTERRUPT__)

/**
  * @brief  Check whether the specified FDCAN flag is set or not.
  * @param  __HANDLE__ FDCAN handle.
  * @param  __FLAG__ FDCAN flag.
  *         This parameter can be one of @arg FDCAN_flags
  * @retval FlagStatus
  */
#define __HAL_FDCAN_GET_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->IR & (__FLAG__))

/**
  * @brief  Clear the specified FDCAN flags.
  * @param  __HANDLE__ FDCAN handle.
  * @param  __FLAG__ specifies the flags to clear.
  *         This parameter can be any combination of @arg FDCAN_flags
  * @retval None
  */
#define __HAL_FDCAN_CLEAR_FLAG(__HANDLE__, __FLAG__)             \
  ((__HANDLE__)->Instance->IR) = (__FLAG__)

/** @brief  Check if the specified FDCAN interrupt source is enabled or disabled.
  * @param  __HANDLE__ FDCAN handle.
  * @param  __INTERRUPT__ specifies the FDCAN interrupt source to check.
  *         This parameter can be a value of @arg FDCAN_Interrupts
  * @retval ITStatus
  */
#define __HAL_FDCAN_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->IE & (__INTERRUPT__))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FDCAN_Exported_Functions
  * @{
  */

/** @addtogroup FDCAN_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions *****************************/
HAL_StatusTypeDef HAL_FDCAN_Init(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_DeInit(FDCAN_HandleTypeDef *hfdcan);
void              HAL_FDCAN_MspInit(FDCAN_HandleTypeDef *hfdcan);
void              HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_EnterPowerDownMode(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_ExitPowerDownMode(FDCAN_HandleTypeDef *hfdcan);

#if USE_HAL_FDCAN_REGISTER_CALLBACKS == 1
/* Callbacks Register/UnRegister functions  ***********************************/
HAL_StatusTypeDef HAL_FDCAN_RegisterCallback(FDCAN_HandleTypeDef *hfdcan, HAL_FDCAN_CallbackIDTypeDef CallbackID, pFDCAN_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterCallback(FDCAN_HandleTypeDef *hfdcan, HAL_FDCAN_CallbackIDTypeDef CallbackID);
HAL_StatusTypeDef HAL_FDCAN_RegisterTxEventFifoCallback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_TxEventFifoCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterTxEventFifoCallback(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_RegisterRxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_RxFifo0CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterRxFifo0Callback(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_RegisterRxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_RxFifo1CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterRxFifo1Callback(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_RegisterTxBufferCompleteCallback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_TxBufferCompleteCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterTxBufferCompleteCallback(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_RegisterTxBufferAbortCallback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_TxBufferAbortCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterTxBufferAbortCallback(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_RegisterErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan, pFDCAN_ErrorStatusCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FDCAN_UnRegisterErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan);
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @addtogroup FDCAN_Exported_Functions_Group2
  * @{
  */
/* Configuration functions ****************************************************/
HAL_StatusTypeDef HAL_FDCAN_ConfigFilter(FDCAN_HandleTypeDef *hfdcan, FDCAN_FilterTypeDef *sFilterConfig);
HAL_StatusTypeDef HAL_FDCAN_ConfigGlobalFilter(FDCAN_HandleTypeDef *hfdcan, uint32_t NonMatchingStd, uint32_t NonMatchingExt, uint32_t RejectRemoteStd, uint32_t RejectRemoteExt);
HAL_StatusTypeDef HAL_FDCAN_ConfigExtendedIdMask(FDCAN_HandleTypeDef *hfdcan, uint32_t Mask);
HAL_StatusTypeDef HAL_FDCAN_ConfigRxFifoOverwrite(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo, uint32_t OperationMode);
HAL_StatusTypeDef HAL_FDCAN_ConfigRamWatchdog(FDCAN_HandleTypeDef *hfdcan, uint32_t CounterStartValue);
HAL_StatusTypeDef HAL_FDCAN_ConfigTimestampCounter(FDCAN_HandleTypeDef *hfdcan, uint32_t TimestampPrescaler);
HAL_StatusTypeDef HAL_FDCAN_EnableTimestampCounter(FDCAN_HandleTypeDef *hfdcan, uint32_t TimestampOperation);
HAL_StatusTypeDef HAL_FDCAN_DisableTimestampCounter(FDCAN_HandleTypeDef *hfdcan);
uint16_t          HAL_FDCAN_GetTimestampCounter(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_ResetTimestampCounter(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_ConfigTimeoutCounter(FDCAN_HandleTypeDef *hfdcan, uint32_t TimeoutOperation, uint32_t TimeoutPeriod);
HAL_StatusTypeDef HAL_FDCAN_EnableTimeoutCounter(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_DisableTimeoutCounter(FDCAN_HandleTypeDef *hfdcan);
uint16_t          HAL_FDCAN_GetTimeoutCounter(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_ResetTimeoutCounter(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_ConfigTxDelayCompensation(FDCAN_HandleTypeDef *hfdcan, uint32_t TdcOffset, uint32_t TdcFilter);
HAL_StatusTypeDef HAL_FDCAN_EnableTxDelayCompensation(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_DisableTxDelayCompensation(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_EnableISOMode(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_DisableISOMode(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_EnableEdgeFiltering(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_DisableEdgeFiltering(FDCAN_HandleTypeDef *hfdcan);
/**
  * @}
  */

/** @addtogroup FDCAN_Exported_Functions_Group3
  * @{
  */
/* Control functions **********************************************************/
HAL_StatusTypeDef HAL_FDCAN_Start(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_Stop(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_AddMessageToTxFifoQ(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxHeaderTypeDef *pTxHeader, uint8_t *pTxData);
uint32_t HAL_FDCAN_GetLatestTxFifoQRequestBuffer(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_AbortTxRequest(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndex);
HAL_StatusTypeDef HAL_FDCAN_GetRxMessage(FDCAN_HandleTypeDef *hfdcan, uint32_t RxLocation, FDCAN_RxHeaderTypeDef *pRxHeader, uint8_t *pRxData);
HAL_StatusTypeDef HAL_FDCAN_GetTxEvent(FDCAN_HandleTypeDef *hfdcan, FDCAN_TxEventFifoTypeDef *pTxEvent);
HAL_StatusTypeDef HAL_FDCAN_GetHighPriorityMessageStatus(FDCAN_HandleTypeDef *hfdcan, FDCAN_HpMsgStatusTypeDef *HpMsgStatus);
HAL_StatusTypeDef HAL_FDCAN_GetProtocolStatus(FDCAN_HandleTypeDef *hfdcan, FDCAN_ProtocolStatusTypeDef *ProtocolStatus);
HAL_StatusTypeDef HAL_FDCAN_GetErrorCounters(FDCAN_HandleTypeDef *hfdcan, FDCAN_ErrorCountersTypeDef *ErrorCounters);
uint32_t HAL_FDCAN_IsTxBufferMessagePending(FDCAN_HandleTypeDef *hfdcan, uint32_t TxBufferIndex);
uint32_t HAL_FDCAN_GetRxFifoFillLevel(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo);
uint32_t HAL_FDCAN_GetTxFifoFreeLevel(FDCAN_HandleTypeDef *hfdcan);
uint32_t HAL_FDCAN_IsRestrictedOperationMode(FDCAN_HandleTypeDef *hfdcan);
HAL_StatusTypeDef HAL_FDCAN_ExitRestrictedOperationMode(FDCAN_HandleTypeDef *hfdcan);
/**
  * @}
  */

/** @addtogroup FDCAN_Exported_Functions_Group4
  * @{
  */
/* Interrupts management ******************************************************/
HAL_StatusTypeDef HAL_FDCAN_ConfigInterruptLines(FDCAN_HandleTypeDef *hfdcan, uint32_t ITList, uint32_t InterruptLine);
HAL_StatusTypeDef HAL_FDCAN_ActivateNotification(FDCAN_HandleTypeDef *hfdcan, uint32_t ActiveITs, uint32_t BufferIndexes);
HAL_StatusTypeDef HAL_FDCAN_DeactivateNotification(FDCAN_HandleTypeDef *hfdcan, uint32_t InactiveITs);
void              HAL_FDCAN_IRQHandler(FDCAN_HandleTypeDef *hfdcan);
/**
  * @}
  */

/** @addtogroup FDCAN_Exported_Functions_Group5
  * @{
  */
/* Callback functions *********************************************************/
void HAL_FDCAN_TxEventFifoCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t TxEventFifoITs);
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs);
void HAL_FDCAN_TxFifoEmptyCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_TxBufferCompleteCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes);
void HAL_FDCAN_TxBufferAbortCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes);
void HAL_FDCAN_HighPriorityMessageCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_TimestampWraparoundCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_TimeoutOccurredCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_ErrorCallback(FDCAN_HandleTypeDef *hfdcan);
void HAL_FDCAN_ErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs);
/**
  * @}
  */

/** @addtogroup FDCAN_Exported_Functions_Group6
  * @{
  */
/* Peripheral State functions *************************************************/
uint32_t HAL_FDCAN_GetError(FDCAN_HandleTypeDef *hfdcan);
HAL_FDCAN_StateTypeDef HAL_FDCAN_GetState(FDCAN_HandleTypeDef *hfdcan);
/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/** @defgroup FDCAN_Private_Types FDCAN Private Types
  * @{
  */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup FDCAN_Private_Variables FDCAN Private Variables
  * @{
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup FDCAN_Private_Constants FDCAN Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FDCAN_Private_Macros FDCAN Private Macros
  * @{
  */
#define IS_FDCAN_FRAME_FORMAT(FORMAT) (((FORMAT) == FDCAN_FRAME_CLASSIC  ) || \
                                       ((FORMAT) == FDCAN_FRAME_FD_NO_BRS) || \
                                       ((FORMAT) == FDCAN_FRAME_FD_BRS   ))
#define IS_FDCAN_MODE(MODE) (((MODE) == FDCAN_MODE_NORMAL              ) || \
                             ((MODE) == FDCAN_MODE_RESTRICTED_OPERATION) || \
                             ((MODE) == FDCAN_MODE_BUS_MONITORING      ) || \
                             ((MODE) == FDCAN_MODE_INTERNAL_LOOPBACK   ) || \
                             ((MODE) == FDCAN_MODE_EXTERNAL_LOOPBACK   ))
#define IS_FDCAN_CKDIV(CKDIV) (((CKDIV) == FDCAN_CLOCK_DIV1 ) || \
                               ((CKDIV) == FDCAN_CLOCK_DIV2 ) || \
                               ((CKDIV) == FDCAN_CLOCK_DIV4 ) || \
                               ((CKDIV) == FDCAN_CLOCK_DIV6 ) || \
                               ((CKDIV) == FDCAN_CLOCK_DIV8 ) || \
                               ((CKDIV) == FDCAN_CLOCK_DIV10) || \
                               ((CKDIV) == FDCAN_CLOCK_DIV12) || \
                               ((CKDIV) == FDCAN_CLOCK_DIV14) || \
                               ((CKDIV) == FDCAN_CLOCK_DIV16) || \
                               ((CKDIV) == FDCAN_CLOCK_DIV18) || \
                               ((CKDIV) == FDCAN_CLOCK_DIV20) || \
                               ((CKDIV) == FDCAN_CLOCK_DIV22) || \
                               ((CKDIV) == FDCAN_CLOCK_DIV24) || \
                               ((CKDIV) == FDCAN_CLOCK_DIV26) || \
                               ((CKDIV) == FDCAN_CLOCK_DIV28) || \
                               ((CKDIV) == FDCAN_CLOCK_DIV30))
#define IS_FDCAN_NOMINAL_PRESCALER(PRESCALER) (((PRESCALER) >= 1U) && ((PRESCALER) <= 512U))
#define IS_FDCAN_NOMINAL_SJW(SJW) (((SJW) >= 1U) && ((SJW) <= 128U))
#define IS_FDCAN_NOMINAL_TSEG1(TSEG1) (((TSEG1) >= 1U) && ((TSEG1) <= 256U))
#define IS_FDCAN_NOMINAL_TSEG2(TSEG2) (((TSEG2) >= 1U) && ((TSEG2) <= 128U))
#define IS_FDCAN_DATA_PRESCALER(PRESCALER) (((PRESCALER) >= 1U) && ((PRESCALER) <= 32U))
#define IS_FDCAN_DATA_SJW(SJW) (((SJW) >= 1U) && ((SJW) <= 16U))
#define IS_FDCAN_DATA_TSEG1(TSEG1) (((TSEG1) >= 1U) && ((TSEG1) <= 32U))
#define IS_FDCAN_DATA_TSEG2(TSEG2) (((TSEG2) >= 1U) && ((TSEG2) <= 16U))
#define IS_FDCAN_MAX_VALUE(VALUE, MAX) ((VALUE) <= (MAX))
#define IS_FDCAN_MIN_VALUE(VALUE, MIN) ((VALUE) >= (MIN))
#define IS_FDCAN_TX_FIFO_QUEUE_MODE(MODE) (((MODE) == FDCAN_TX_FIFO_OPERATION ) || \
                                           ((MODE) == FDCAN_TX_QUEUE_OPERATION))
#define IS_FDCAN_ID_TYPE(ID_TYPE) (((ID_TYPE) == FDCAN_STANDARD_ID) || \
                                   ((ID_TYPE) == FDCAN_EXTENDED_ID))
#define IS_FDCAN_FILTER_CFG(CONFIG) (((CONFIG) == FDCAN_FILTER_DISABLE      ) || \
                                     ((CONFIG) == FDCAN_FILTER_TO_RXFIFO0   ) || \
                                     ((CONFIG) == FDCAN_FILTER_TO_RXFIFO1   ) || \
                                     ((CONFIG) == FDCAN_FILTER_REJECT       ) || \
                                     ((CONFIG) == FDCAN_FILTER_HP           ) || \
                                     ((CONFIG) == FDCAN_FILTER_TO_RXFIFO0_HP) || \
                                     ((CONFIG) == FDCAN_FILTER_TO_RXFIFO1_HP))
#define IS_FDCAN_TX_LOCATION(LOCATION) (((LOCATION) == FDCAN_TX_BUFFER0 ) || ((LOCATION) == FDCAN_TX_BUFFER1 ) || \
                                        ((LOCATION) == FDCAN_TX_BUFFER2 ))
#define IS_FDCAN_TX_LOCATION_LIST(LOCATION) (((LOCATION) >= FDCAN_TX_BUFFER0) && \
                                             ((LOCATION) <= (FDCAN_TX_BUFFER0 | FDCAN_TX_BUFFER1 | FDCAN_TX_BUFFER2)))
#define IS_FDCAN_RX_FIFO(FIFO) (((FIFO) == FDCAN_RX_FIFO0) || \
                                ((FIFO) == FDCAN_RX_FIFO1))
#define IS_FDCAN_RX_FIFO_MODE(MODE) (((MODE) == FDCAN_RX_FIFO_BLOCKING ) || \
                                     ((MODE) == FDCAN_RX_FIFO_OVERWRITE))
#define IS_FDCAN_STD_FILTER_TYPE(TYPE) (((TYPE) == FDCAN_FILTER_RANGE) || \
                                        ((TYPE) == FDCAN_FILTER_DUAL ) || \
                                        ((TYPE) == FDCAN_FILTER_MASK ))
#define IS_FDCAN_EXT_FILTER_TYPE(TYPE) (((TYPE) == FDCAN_FILTER_RANGE        ) || \
                                        ((TYPE) == FDCAN_FILTER_DUAL         ) || \
                                        ((TYPE) == FDCAN_FILTER_MASK         ) || \
                                        ((TYPE) == FDCAN_FILTER_RANGE_NO_EIDM))
#define IS_FDCAN_FRAME_TYPE(TYPE) (((TYPE) == FDCAN_DATA_FRAME  ) || \
                                   ((TYPE) == FDCAN_REMOTE_FRAME))
#define IS_FDCAN_DLC(DLC) (((DLC) == FDCAN_DLC_BYTES_0 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_1 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_2 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_3 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_4 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_5 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_6 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_7 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_8 ) || \
                           ((DLC) == FDCAN_DLC_BYTES_12) || \
                           ((DLC) == FDCAN_DLC_BYTES_16) || \
                           ((DLC) == FDCAN_DLC_BYTES_20) || \
                           ((DLC) == FDCAN_DLC_BYTES_24) || \
                           ((DLC) == FDCAN_DLC_BYTES_32) || \
                           ((DLC) == FDCAN_DLC_BYTES_48) || \
                           ((DLC) == FDCAN_DLC_BYTES_64))
#define IS_FDCAN_ESI(ESI) (((ESI) == FDCAN_ESI_ACTIVE ) || \
                           ((ESI) == FDCAN_ESI_PASSIVE))
#define IS_FDCAN_BRS(BRS) (((BRS) == FDCAN_BRS_OFF) || \
                           ((BRS) == FDCAN_BRS_ON ))
#define IS_FDCAN_FDF(FDF) (((FDF) == FDCAN_CLASSIC_CAN) || \
                           ((FDF) == FDCAN_FD_CAN     ))
#define IS_FDCAN_EFC(EFC) (((EFC) == FDCAN_NO_TX_EVENTS   ) || \
                           ((EFC) == FDCAN_STORE_TX_EVENTS))
#define IS_FDCAN_IT(IT) (((IT) & ~(FDCAN_IR_MASK)) == 0U)
#define IS_FDCAN_IT_GROUP(IT_GROUP) (((IT_GROUP) & ~(FDCAN_ILS_MASK)) == 0U)
#define IS_FDCAN_NON_MATCHING(DESTINATION) (((DESTINATION) == FDCAN_ACCEPT_IN_RX_FIFO0) || \
                                            ((DESTINATION) == FDCAN_ACCEPT_IN_RX_FIFO1) || \
                                            ((DESTINATION) == FDCAN_REJECT            ))
#define IS_FDCAN_REJECT_REMOTE(DESTINATION) (((DESTINATION) == FDCAN_FILTER_REMOTE) || \
                                             ((DESTINATION) == FDCAN_REJECT_REMOTE))
#define IS_FDCAN_IT_LINE(IT_LINE) (((IT_LINE) == FDCAN_INTERRUPT_LINE0) || \
                                   ((IT_LINE) == FDCAN_INTERRUPT_LINE1))
#define IS_FDCAN_TIMESTAMP(OPERATION) (((OPERATION) == FDCAN_TIMESTAMP_INTERNAL) || \
                                       ((OPERATION) == FDCAN_TIMESTAMP_EXTERNAL))
#define IS_FDCAN_TIMESTAMP_PRESCALER(PRESCALER) (((PRESCALER) == FDCAN_TIMESTAMP_PRESC_1 ) || \
                                                 ((PRESCALER) == FDCAN_TIMESTAMP_PRESC_2 ) || \
                                                 ((PRESCALER) == FDCAN_TIMESTAMP_PRESC_3 ) || \
                                                 ((PRESCALER) == FDCAN_TIMESTAMP_PRESC_4 ) || \
                                                 ((PRESCALER) == FDCAN_TIMESTAMP_PRESC_5 ) || \
                                                 ((PRESCALER) == FDCAN_TIMESTAMP_PRESC_6 ) || \
                                                 ((PRESCALER) == FDCAN_TIMESTAMP_PRESC_7 ) || \
                                                 ((PRESCALER) == FDCAN_TIMESTAMP_PRESC_8 ) || \
                                                 ((PRESCALER) == FDCAN_TIMESTAMP_PRESC_9 ) || \
                                                 ((PRESCALER) == FDCAN_TIMESTAMP_PRESC_10) || \
                                                 ((PRESCALER) == FDCAN_TIMESTAMP_PRESC_11) || \
                                                 ((PRESCALER) == FDCAN_TIMESTAMP_PRESC_12) || \
                                                 ((PRESCALER) == FDCAN_TIMESTAMP_PRESC_13) || \
                                                 ((PRESCALER) == FDCAN_TIMESTAMP_PRESC_14) || \
                                                 ((PRESCALER) == FDCAN_TIMESTAMP_PRESC_15) || \
                                                 ((PRESCALER) == FDCAN_TIMESTAMP_PRESC_16))
#define IS_FDCAN_TIMEOUT(OPERATION) (((OPERATION) == FDCAN_TIMEOUT_CONTINUOUS   ) || \
                                     ((OPERATION) == FDCAN_TIMEOUT_TX_EVENT_FIFO) || \
                                     ((OPERATION) == FDCAN_TIMEOUT_RX_FIFO0     ) || \
                                     ((OPERATION) == FDCAN_TIMEOUT_RX_FIFO1     ))
/**
  * @}
  */

/* Private functions prototypes ----------------------------------------------*/
/** @defgroup FDCAN_Private_Functions_Prototypes FDCAN Private Functions Prototypes
  * @{
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup FDCAN_Private_Functions FDCAN Private Functions
  * @{
  */

/**
  * @}
  */
/**
  * @}
  */

/**
  * @}
  */
#endif /* FDCAN1 */

#ifdef __cplusplus
}
#endif

#endif /* STM32G0xx_HAL_FDCAN_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
