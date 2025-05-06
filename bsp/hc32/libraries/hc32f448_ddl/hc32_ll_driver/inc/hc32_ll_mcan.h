/**
 *******************************************************************************
 * @file  hc32_ll_mcan.h
 * @brief This file contains all the functions prototypes of the MCAN driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
   2023-12-15       CDT             Removed definitions related to BEC and BEU.
                                    Optimized driver:
                                    1. Integrated stc_mcan_classic_config_t and stc_mcan_fd_config_t into stc_mcan_bit_time_config_t
                                    2. Integrated u32FdIso into u32FrameFormat.
                                    3. Removed API MCAN_SetFdIsoOperation(), added API MCAN_SetFrameFormat().
                                    4. Optimized the handling of the parameter stc_mcan_filter_t.u32FilterIndex
                                    5. Add 5 APIs for better get protocol status(register PSR):
                                       MCAN_GetTdcValue(), MCAN_GetDataLastErrorCode(), MCAN_GetLastErrorCode(),
                                       MCAN_GetComState(), MCAN_GetProtocolFlagStatus()
                                    6. Changed u8Activity of stc_mcan_protocol_status_t to u8ComState.
                                    7. Changed MCAN_Comm_State to MCAN_Com_State and optimized the macros definitions.
                                    8. Changed u8MsgStorageIndex of stc_mcan_hpm_status_t to u8MsgIndex. Optimized MCAN_HPM_Storage macros definitions.
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_MCAN_H__
#define __HC32_LL_MCAN_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"
/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_MCAN
 * @{
 */
#if (LL_MCAN_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup MCAN_Global_Types MCAN Global Types
 * @{
 */
/**
 * @brief MCAN bit time configuration structure definition
 */
typedef struct {
    /* Nominal bit time configuration, used for classic CAN frame or arbitration phase of CAN FD frame */
    uint32_t u32NominalPrescaler;           /*!< Specifies the nominal bit rate prescaler.
                                                 This parameter must be a number between 1 and 512 */
    uint32_t u32NominalTimeSeg1;            /*!< Specifies the nominal time segment before sample point(the sum of Sync_Seg,
                                                 Prop_Seg and Phase_Seg1).
                                                 This parameter must be a number between 3 and 257 */
    uint32_t u32NominalTimeSeg2;            /*!< Specifies the nominal time segment after sample point(Phase_Seg2).
                                                 This parameter must be a number between 2 and 128 */
    uint32_t u32NominalSyncJumpWidth;       /*!< Specifies the nominal (re)synchronization jump width(SJW).
                                                 This parameter must be a number between 1 and 128 */

    /* FD bit time configuration, used for data phase of CAN FD frame */
    uint32_t u32DataPrescaler;              /*!< Specifies the data bit rate prescaler.
                                                 This parameter must be a number between 1 and 32
                                                 NOTE: when u32TDC is MCAN_FD_TDC_ENABLE, the range is limited to 1, 2 */
    uint32_t u32DataTimeSeg1;               /*!< Specifies the data time segment before sample point(the sum of Sync_Seg,
                                                 Prop_Seg and Phase_Seg1).
                                                 This parameter must be a number between 2 and 33 */
    uint32_t u32DataTimeSeg2;               /*!< Specifies the data time segment after sample point(Phase_Seg2).
                                                 This parameter must be a number between 1 and 16 */
    uint32_t u32DataSyncJumpWidth;          /*!< Specifies the data (re)synchronization jump width(SJW).
                                                 This parameter must be a number between 1 and 16 */

    /* FD TDC(Transmitter Delay Compensation) configuration */
    uint32_t u32TDC;                        /*!< Enable or disable TDC(Transmitter Delay Compensation).
                                                 This parameter can be a value of @ref MCAN_TDC_Enable */
    uint32_t u32SspOffset;                  /*!< Specifies the transmitter delay compensation SSP offset.
                                                 This parameter must be a number between 0 and 127(MCAN clock) */
    uint32_t u32TdcFilter;                  /*!< Specifies the transmitter delay compensation filter window length.
                                                 This parameter defines the minimum value for the SSP position.
                                                 The feature is enabled when this parameter is configured to a value
                                                 greater than u32SspOffset.
                                                 This parameter must be a number between 0 and 127(MCAN clock) */
} stc_mcan_bit_time_config_t;

/**
 * @brief MCAN message RAM address blocks
 */
typedef struct {
    uint32_t u32StdFilterStartAddr;         /*!< Output parameter. Indicates the standard filter list start address. */
    uint32_t u32ExtFilterStartAddr;         /*!< Output parameter. Indicates the extended filter list start address. */
    uint32_t u32RxFifo0StartAddr;           /*!< Output parameter. Indicates the Rx FIFO 0 start address. */
    uint32_t u32RxFifo1StartAddr;           /*!< Output parameter. Indicates the Rx FIFO 1 start address. */
    uint32_t u32RxBufferStartAddr;          /*!< Output parameter. Indicates the Rx buffer start address. */
    uint32_t u32TxEventStartAddr;           /*!< Output parameter. Indicates the Tx event FIFO start address. */
    uint32_t u32TxBufferStartAddr;          /*!< Output parameter. Indicates the Tx buffers start address. */
    uint32_t u32TxFifoQueueStartAddr;       /*!< Output parameter. Indicates the Tx FIFO/Queue start address. */
    uint32_t u32EndAddr;                    /*!< Output parameter. Indicates the end address of the allocated RAM. */
    uint32_t *pu32StdFilterAddrList;        /*!< Pointer to an address that used to store each standard ID filter element address.
                                                 Set it to NULL if you do not need the element address information. */
    uint32_t *pu32ExtFilterAddrList;        /*!< Pointer to an address that used to store each extended ID filter element address.
                                                 Set it to NULL if you do not need the element address information. */
    uint32_t *pu32RxFifo0AddrList;          /*!< Pointer to an address that used to store each Rx FIFO0 element address.
                                                 Set it to NULL if you do not need the element address information. */
    uint32_t *pu32RxFifo1AddrList;          /*!< Pointer to an address that used to store each Rx FIFO1 element address.
                                                 Set it to NULL if you do not need the element address information. */
    uint32_t *pu32RxBufferAddrList;         /*!< Pointer to an address that used to store each Rx buffer element address.
                                                 Set it to NULL if you do not need the element address information. */
    uint32_t *pu32TxEventAddrList;          /*!< Pointer to an address that used to store each Tx event FIFO element address.
                                                 Set it to NULL if you do not need the element address information. */
    uint32_t *pu32TxBufferAddrList;         /*!< Pointer to an address that used to store each dedicated Tx buffer element address.
                                                 Set it to NULL if you do not need the element address information. */
    uint32_t *pu32TxFifoQueueAddrList;      /*!< Pointer to an address that used to store each Tx FIFO/queue element address.
                                                 Set it to NULL if you do not need the element address information. */
} stc_mcan_msg_ram_addr_t;

/**
 * @brief MCAN message RAM configuration structure definition
 */
typedef struct {
    uint32_t u32AddrOffset;                 /*!< Specifies the message RAM start address.
                                                 NOTE: The message RAM is 2K bytes and shared by MCAN1 and MCAN2. */
    uint32_t u32StdFilterNum;               /*!< Specifies the number of standard message ID filters.
                                                 This parameter is used to allocate RAM to standard ID filters.
                                                 This parameter must be a number between 0 and 128 */
    uint32_t u32ExtFilterNum;               /*!< Specifies the number of extended message ID filters.
                                                 This parameter is used to allocate RAM to extended ID filters.
                                                 This parameter must be a number between 0 and 64 */
    uint32_t u32RxFifo0Num;                 /*!< Specifies the number of Rx FIFO0 elements.
                                                 u32RxFifo0Num and u32RxFifo0DataSize are used to allocate RAM to Rx FIFO0.
                                                 This parameter must be a number between 0 and 64 */
    uint32_t u32RxFifo0DataSize;            /*!< Specifies the data field size in an Rx FIFO 0 element.
                                                 This parameter can be a value of @ref MCAN_Data_Field_Size  */
    uint32_t u32RxFifo1Num;                 /*!< Specifies the number of Rx FIFO 1 elements.
                                                 u32RxFifo1Num and u32RxFifo1DataSize are used to allocate RAM to Rx FIFO1.
                                                 This parameter must be a number between 0 and 64 */
    uint32_t u32RxFifo1DataSize;            /*!< Specifies the data field size in an Rx FIFO 1 element.
                                                 This parameter can be a value of @ref MCAN_Data_Field_Size  */
    uint32_t u32RxBufferNum;                /*!< Specifies the number of dedicated Rx buffer elements.
                                                 u32RxBufferNum and u32RxBufferDataSize are used to allocate RAM to Rx buffer.
                                                 This parameter must be a number between 0 and 64 */
    uint32_t u32RxBufferDataSize;           /*!< Specifies the data field size in an Rx buffer element.
                                                 This parameter can be a value of @ref MCAN_Data_Field_Size  */
    uint32_t u32TxEventNum;                 /*!< Specifies the number of Tx event FIFO elements.
                                                 This parameter is used to allocate RAM to Tx event FIFO.
                                                 This parameter must be a number between 0 and 32 */
    uint32_t u32TxBufferNum;                /*!< Specifies the number of dedicated Tx buffers.
                                                 u32TxBufferNum and u32TxFifoQueueNum and u32TxDataSize are used to allocate RAM for Tx messages.
                                                 The sum of u32TxBufferNum and u32TxFifoQueueNum must be a number between 0 and 32 */
    uint32_t u32TxFifoQueueNum;             /*!< Specifies the number of Tx buffers used for Tx FIFO/queue.
                                                 The sum of u32TxFifoQueueNum and u32TxBufferNum must be a number between 0 and 32 */
    uint32_t u32TxFifoQueueMode;            /*!< Specifies Tx FIFO/Queue operation mode.
                                                 This parameter can be a value of @ref MCAN_Tx_FIFO_Queue_Mode */
    uint32_t u32TxDataSize;                 /*!< Specifies the data field size in a Tx element.
                                                 This parameter can be a value of @ref MCAN_Data_Field_Size */
    uint32_t u32AllocatedSize;              /*!< Output parameter. Indicates the message RAM size that allocated to the configured MCAN.
                                                 It is also the address offset of the MCAN to be configured. */
} stc_mcan_msg_ram_config_t;

/**
 * @brief MCAN filter structure definition
 */
typedef struct {
    uint32_t u32IdType;                     /*!< Specifies the ID type.
                                                 This parameter can be a value of @ref MCAN_ID_Type */
    uint32_t u32FilterIndex;                /*!< Specifies the filter which will be initialized.
                                                 This parameter must be a number between:
                                                 - 0 and stc_mcan_msg_ram_config_t.u32StdFilterNum-1(@ref stc_mcan_msg_ram_config_t), if u32IdType is MCAN_STD_ID.
                                                 - 0 and stc_mcan_msg_ram_config_t.u32ExtFilterNum-1(@ref stc_mcan_msg_ram_config_t), if u32IdType is MCAN_EXT_ID.
                                                 NOTE: When configuring filter elements sequence by calling API MCAN_Init(), this parameter can be ignored. The local function
                                                       will handle this parameter.
                                                       When configuring filter element one by one by calling API MCAN_FilterConfig(), it is required to specify
                                                       the index of the target filter through this parameter. */
    uint32_t u32FilterType;                 /*!< Specifies the filter type.
                                                 This parameter can be a value of @ref MCAN_Filter_Type
                                                 The value MCAN_FILTER_RANGE_NO_EIDM is permitted only when u32IdType is MCAN_EXT_ID.
                                                 This parameter is ignored if u32FilterConfig is set to MCAN_FILTER_TO_RX_BUF */
    uint32_t u32FilterConfig;               /*!< Specifies the filter configuration.
                                                 This parameter can be a value of @ref MCAN_Filter_Config */
    uint32_t u32FilterId1;                  /*!< Specifies the filter ID1.
                                                 This parameter must be a number between:
                                                 - 0 and 0x7FF, if u32IdType is MCAN_STD_ID
                                                 - 0 and 0x1FFFFFFF, if u32IdType is MCAN_EXT_ID */
    uint32_t u32FilterId2;                  /*!< Specifies the filter ID2.
                                                 This parameter is ignored if u32FilterConfig is set to MCAN_FILTER_TO_RX_BUF.
                                                 This parameter must be a number between:
                                                 - 0 and 0x7FF, if u32IdType is MCAN_STD_ID
                                                 - 0 and 0x1FFFFFFF, if u32IdType is MCAN_EXT_ID */
    uint32_t u32RxBufferIndex;              /*!< Specifies the dedicated Rx buffer in which the matching message will be stored.
                                                 This parameter must be a number between 0 and 63, and less than or equal to
                                                 u32RxBufferNum of @ref stc_mcan_msg_ram_config_t
                                                 This parameter is ignored if u32FilterConfig is different from MCAN_FILTER_TO_RX_BUF */
} stc_mcan_filter_t;

/**
 * @brief MCAN filter initialization structure definition
 */
typedef struct {
    stc_mcan_filter_t *pstcStdFilterList;   /*!< Pointer to the standard ID filter elements list.
                                                 These filter elements can be configured only when:
                                                 pstcStdFilterList != NULL and
                                                 u32StdFilterConfigNum > 0 and
                                                 u32StdFilterConfigNum <= u32StdFilterNum of @ref stc_mcan_msg_ram_config_t */
    stc_mcan_filter_t *pstcExtFilterList;   /*!< Pointer to the extended ID filter elements list.
                                                 These filter elements can be configured only when:
                                                 pstcExtFilterList != NULL and
                                                 u32ExtFilterConfigNum > 0 and
                                                 u32ExtFilterConfigNum <= u32ExtFilterNum of @ref stc_mcan_msg_ram_config_t */
    uint32_t u32StdFilterConfigNum;         /*!< Number of the standard ID filter elements which to be configured.
                                                 This parameter must less than or equal to u32StdFilterNum
                                                 of @ref stc_mcan_msg_ram_config_t */
    uint32_t u32ExtFilterConfigNum;         /*!< Number of the extended ID filter elements which to be configured.
                                                 This parameter must less than or equal to u32ExtFilterNum
                                                 of @ref stc_mcan_msg_ram_config_t */
} stc_mcan_filter_config_t;

/**
 * @brief MCAN initialization structure
 */
typedef struct {
    uint32_t u32Mode;                           /*!< Specifies MCAN operating mode.
                                                     This parameter can be a value of @ref MCAN_Operating_Mode */
    uint32_t u32FrameFormat;                    /*!< Specifies the frame format supported by MCAN hardware.
                                                     This parameter can be a value of @ref MCAN_Frame_Format */
    uint32_t u32AutoRetx;                       /*!< Enable or disable automatic retransmission.
                                                     This parameter can be a value of @ref MCAN_Auto_Retx_Enable */
    uint32_t u32TxPause;                        /*!< Enable or disable transmit pause.
                                                     If transmit pause is enabled, MCAN pauses for two CAN bit times before starting
                                                     the next transmission after itself has successfully transmitted a frame.
                                                     This parameter can be a value of @ref MCAN_Tx_Pause_Enable */
    uint32_t u32ProtocolException;              /*!< Enable or disable protocol exception handling.
                                                     When this function is disabled, MCAN will transmit an error frame
                                                     when it detects a protocol exception condition.
                                                     This parameter can be a value of @ref MCAN_Protocol_Exception_Enable */
    stc_mcan_bit_time_config_t stcBitTime;      /*!< MCAN bit time configuration structure */
    stc_mcan_msg_ram_config_t stcMsgRam;        /*!< Message RAM configuration structure. */
    stc_mcan_filter_config_t stcFilter;         /*!< Acceptance filter configuration structure. */
} stc_mcan_init_t;

/**
 * @brief MCAN Tx message structure definition
 */
typedef struct {
    uint32_t ID;                            /*!< Specifies the ID.
                                                 This parameter must be a number between:
                                                 - 0 and 0x7FF, if IDE is 0
                                                 - 0 and 0x1FFFFFFF, if IDE is 1 */
    uint32_t IDE;                           /*!< IDentifier Extension bit. Specifies the ID type for the transmitted message.
                                                 This parameter can be a value of:
                                                 - 0: 11-bit standard ID
                                                 - 1: 29-bit extended ID */
    uint32_t RTR;                           /*!< Remote Transmission Request. Specifies the frame type of the transmitted message.
                                                 This parameter can be a value of:
                                                 - 0: Data frame to be transmitted
                                                 - 1: Remote frame to be transmitted */
    uint32_t DLC;                           /*!< Data Length Code. Specifies the length of the data field of the transmitted frame.
                                                 This parameter can be a value of @ref MCAN_Data_Length_Code */
    uint32_t ESI;                           /*!< Error State Indicator. Specifies the error state indicator.
                                                 This parameter can be a value of:
                                                 - 0: Transmitting node is error active
                                                 - 1: Transmitting node is error passive */
    uint32_t BRS;                           /*!< Bit Rate Switch. Specifies whether the Tx frame is transmitted with or without bit rate switching.
                                                 This parameter can be a value of:
                                                 - 0: Frame transmitted without bit rate switching
                                                 - 1: Frame transmitted with bit rate switching */
    uint32_t FDF;                           /*!< FD Format indicator. Specifies whether the Tx frame is transmitted in classic or FD format.
                                                 This parameter can be a value of:
                                                 - 0: Classical CAN frame format
                                                 - 1: CAN FD frame format (new DLC-coding and CRC) */
    uint32_t u32StoreTxEvent;               /*!< Specifies the event FIFO control.
                                                 This parameter can be a value of:
                                                 - 0: DO NOT store tx event
                                                 - 1: Store tx event into TX event FIFO */
    uint32_t u32MsgMarker;                  /*!< Specifies the message marker to be copied into Tx event FIFO
                                                 element for identification of Tx message status.
                                                 This parameter must be a number between:
                                                 - 0 and 0xFF if 8-bit message marker used(CCCR.WMM == 0)
                                                 - 0 and 0xFFFF if 16-bit-width message marker used(CCCR.WMM == 1) */
    uint32_t u32TxBuffer;                   /*!< Specifies the dedicated Tx buffer that used to transmit the message.
                                                 This parameter can be a value of @ref MCAN_Tx_Location
                                                 This parameter valid when Tx via dedicated Tx buffer. */
    uint8_t au8Data[64U];                   /*!< Data payload of the message that to be transmitted. */
    uint32_t u32LastTxFifoQueueRequest;     /*!< Ouput parameter of Tx buffer index of last Tx FIFO/queue request.
                                                 This parameter valid when Tx via FIFO or queue. */
} stc_mcan_tx_msg_t;

/**
 * @brief MCAN Rx message structure definition
 */
typedef struct {
    uint32_t ID;                        /*!< Specifies the ID.
                                             This parameter must be a number between:
                                             - 0 and 0x7FF, if IDE is 0
                                             - 0 and 0x1FFFFFFF, if IDE is 1 */
    uint32_t IDE;                       /*!< IDentifier Extension bit. Specifies the ID type for the received message.
                                             This parameter can be a value of:
                                             - 0: 11-bit standard ID
                                             - 1: 29-bit extended ID */
    uint32_t RTR;                       /*!< Remote Transmission Request. Specifies the frame type of the received message.
                                             This parameter can be a value of:
                                             - 0: Data frame received
                                             - 1: Remote frame received */
    uint32_t DLC;                       /*!< Data Length Code. Specifies the length of data filed of the received frame.
                                             This parameter can be a value of @ref MCAN_Data_Length_Code */
    uint32_t ESI;                       /*!< Error State Indicator. Specifies the error state indicator.
                                             This parameter can be a value of:
                                             - 0: Transmitting node is error active
                                             - 1: Transmitting node is error passive */
    uint32_t BRS;                       /*!< Bit Rate Switch. Specifies whether the Tx frame is received with or without bit rate switching.
                                             This parameter can be a value of:
                                             - 0: Frame received without bit rate switching
                                             - 1: Frame received with bit rate switching */
    uint32_t FDF;                       /*!< FD Format indicator. Specifies whether the Tx frame is received in classic or FD format.
                                             This parameter can be a value of:
                                             - 0: Classical CAN frame format
                                             - 1: CAN FD frame format (new DLC-coding and CRC) */
    uint32_t u32RxTimestamp;            /*!< Specifies the timestamp counter value captured on start of frame reception.
                                             This parameter must be a number between 0 and 0xFFFF */
    uint32_t u32FilterIndex;            /*!< Specifies the index of matching Rx acceptance filter element.
                                             This parameter must be a number between:
                                             - 0 and 127, if IDE is 0
                                             - 0 and 63, if IDE is 1 */
    uint32_t u32NmfFlag;                /*!< Specifies whether the accepted frame did not match any Rx filter.
                                             Acceptance of non-matching frames may be configured via @ref MCAN_GlobalFilterConfig()
                                             This parameter can be:
                                             - 0: Received frame matching filter index u32FilterIndex
                                             - 1: Received frame did not match any Rx filter element */
    uint8_t au8Data[64U];               /*!< Data payload of the received message */
    uint32_t u32DataSize;               /*!< Size of Rx data payload */
} stc_mcan_rx_msg_t;

/**
 * @brief MCAN Tx event structure definition
 */
typedef struct {
    uint32_t ID;                        /*!< Specifies the ID.
                                             This parameter must be a number between:
                                             - 0 and 0x7FF, if IDE is 0
                                             - 0 and 0x1FFFFFFF, if IDE is 1 */
    uint32_t IDE;                       /*!< IDentifier Extension bit. Specifies the ID type for the transmitted message.
                                             This parameter can be a value of:
                                             - 0: 11-bit standard ID
                                             - 1: 29-bit extended ID */
    uint32_t RTR;                       /*!< Remote Transmission Request. Specifies the frame type of the transmitted message.
                                             This parameter can be a value of:
                                             - 0: Data frame transmitted
                                             - 1: Remote frame transmitted */
    uint32_t DLC;                       /*!< Data Length Code. Specifies the length of the transmitted frame.
                                             This parameter can be a value of @ref MCAN_Data_Length_Code */
    uint32_t ESI;                       /*!< Error State Indicator. Specifies the error state indicator.
                                             This parameter can be a value of:
                                             - 0: Transmitting node is error active
                                             - 1: Transmitting node is error passive */
    uint32_t BRS;                       /*!< Bit Rate Switch. Specifies whether the Tx frame is transmitted with or without bit rate switching.
                                             This parameter can be a value of:
                                             - 0: Frame transmitted without bit rate switching
                                             - 1: Frame transmitted with bit rate switching */
    uint32_t FDF;                       /*!< FD Format indicator. Specifies whether the Tx frame is transmitted in classic or FD format.
                                             This parameter can be a value of:
                                             - 0: Classical CAN frame format
                                             - 1: CAN FD frame format (new DLC-coding and CRC) */
    uint32_t u32TxTimestamp;            /*!< Specifies the timestamp counter value captured on start of frame transmission.
                                             This parameter is valid only when 8-bit message marker used.
                                             This parameter must be a number between 0 and 0xFFFF. */
    uint32_t u32MsgMarker;              /*!< Specifies the message marker copied into Tx Event FIFO element for identification of Tx message status.
                                             This parameter must be a number between:
                                             - 0 and 0xFF if 8-bit message marker used(CCCR.WMM == 0)
                                             - 0 and 0xFFFF if 16-bit-width message marker used(CCCR.WMM == 1) */
    uint32_t u32EventType;              /*!< Specifies the event type.
                                             This parameter can be a value of @ref MCAN_Evt_Type */
} stc_mcan_tx_event_t;

/**
 * @brief MCAN high priority message status structure definition
 */
typedef struct {
    uint8_t u8FilterListType;           /*!< Specifies the filter list of the matching filter element.
                                             This parameter can be:
                                             - 0: Standard filter list
                                             - 1: Extended filter list */
    uint8_t u8FilterIndex;              /*!< Specifies the index of matching filter element.
                                             This parameter can be a number between:
                                             - 0 and 127, if u8FilterListType is 0 (Standard)
                                             - 0 and 63, if u8FilterListType is 1 (Extended) */
    uint8_t u8MsgStorage;               /*!< Specifies the high priority message storage.
                                             This parameter can be a value of @ref MCAN_HPM_Storage */
    uint8_t u8MsgIndex;                 /*!< Specifies the index of Rx FIFO element to which the message was stored.
                                             This parameter is valid only when u8MsgStorage is:
                                             MCAN_HPM_STORED_IN_RX_FIFO0 or MCAN_HPM_STORED_IN_RX_FIFO1 */
} stc_mcan_hpm_status_t;

/**
 * @brief MCAN protocol status structure definition
 */
typedef struct {
    uint8_t u8LastErrorCode;            /*!< Specifies the type of the last error that occurred on the CAN bus.
                                             This parameter can be a value of @ref MCAN_Protocol_Error_Code */
    uint8_t u8DataLastErrorCode;        /*!< Specifies the type of the last error that occurred in the data phase of a CAN FD format
                                             frame with its BRS flag set.
                                             This parameter can be a value of @ref MCAN_Protocol_Error_Code */
    uint8_t u8ComState;                 /*!< Specifies the CAN module communication state.
                                             This parameter can be a value of @ref MCAN_Com_State */
    uint8_t u8ErrorPassiveFlag;         /*!< Specifies the CAN module error status.
                                             This parameter can be:
                                             - 0: The CAN is in the Error_Active state
                                             - 1: The CAN is in the Error_Passive state */
    uint8_t u8WarningFlag;              /*!< Specifies the CAN module warning status.
                                             This parameter can be:
                                             - 0: Both error counters are below the Error_Warning limit of 96
                                             - 1: At least one of error counter has reached the Error_Warning limit of 96 */
    uint8_t u8BusOffFlag;               /*!< Specifies the CAN module Bus_Off status.
                                             This parameter can be:
                                             - 0: The CAN is not in Bus_Off state
                                             - 1: The CAN is in Bus_Off state */
    uint8_t u8RxESIFlag;                /*!< Specifies ESI flag of last received CAN FD message.
                                             This parameter can be:
                                             - 0: Last received CAN FD message did not have its ESI flag set
                                             - 1: Last received CAN FD message had its ESI flag set */
    uint8_t u8RxBRSFlag;                /*!< Specifies BRS flag of last received CAN FD message.
                                             This parameter can be:
                                             - 0: Last received CAN FD message did not have its BRS flag set
                                             - 1: Last received CAN FD message had its BRS flag set */
    uint8_t u8RxFDFFlag;                /*!< Specifies if CAN FD message (FDF flag set) has been received since last protocol status.
                                             This parameter can be:
                                             - 0: Since this bit was reset by the CPU, no CAN FD message has been received
                                             - 1: Message in CAN FD format with FDF flag set has been received */
    uint8_t u8ProtocolExceptionFlag;    /*!< Specifies the CAN module protocol exception status.
                                             This parameter can be:
                                             - 0: No protocol exception event occurred since last read access
                                             - 1: Protocol exception event occurred */
    uint8_t u8TdcValue;                 /*!< Specifies the Transmitter Delay Compensation Value.
                                             This parameter can be a number between 0 and 127 */

} stc_mcan_protocol_status_t;

/**
 * @brief MCAN error counters structure definition
 */
typedef struct {
    uint8_t u8TxErrorCount;             /*!< Specifies the Transmit Error Counter Value.
                                             This parameter can be a number between 0 and 255 */
    uint8_t u8RxErrorCount;             /*!< Specifies the Receive Error Counter Value.
                                             This parameter can be a number between 0 and 127 */
    uint8_t u8RxErrorPassive;           /*!< Specifies the Receive Error Passive status.
                                             This parameter can be:
                                             - 0: The Receive Error Counter (u8RxErrorCount) is below the error passive level of 128
                                             - 1: The Receive Error Counter (u8RxErrorCount) has reached the error passive level of 128 */
    uint8_t u8ErrorLogging;             /*!< Specifies the Transmit/Receive error logging counter value.
                                             This parameter can be a number between 0 and 255.
                                             This counter is incremented each time when a CAN protocol error causes the u8TxErrorCount
                                             or the u8RxErrorCount to be incremented. The counter stops at 255; the next increment of
                                             u8TxErrorCount or u8RxErrorCount sets interrupt flag MCAN_FLAG_ERR_LOG_OVF */
} stc_mcan_error_counter_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup MCAN_Global_Macros MCAN Global Macros
 * @{
 */
/**
 * @defgroup MCAN_Operating_Mode MCAN Operating Mode
 * @{
 */
#define MCAN_MD_NORMAL                  (0U)                /*!< Normal mode */
#define MCAN_MD_RESTRICTED_OP           (1U)                /*!< Restricted operation mode */
#define MCAN_MD_BUS_MON                 (2U)                /*!< Bus monitoring mode */
#define MCAN_MD_INTERN_LOOPBACK         (3U)                /*!< Internal loopBack mode */
#define MCAN_MD_EXTERN_LOOPBACK         (4U)                /*!< External loopBack mode */
/**
 * @}
 */

/**
 * @defgroup MCAN_Msg_RAM_Info MCAN Message RAM Information
 * @{
 */
#define MCAN_MSG_RAM_BASE               (0x4002B000UL)      /*!< MCAN message RAM start address */
#define MCAN_MSG_RAM_SIZE               (1024UL * 2UL)      /*!< MCAN message RAM size */
#define MCAN_MSG_RAM_END                (MCAN_MSG_RAM_BASE + \
                                         MCAN_MSG_RAM_SIZE) /*!< MCAN message RAM end address */
/**
 * @}
 */

/**
 * @defgroup MCAN_ID_Type MCAN ID Type
 * @{
 */
#define MCAN_STD_ID                     (0U)                /*!< Standard ID */
#define MCAN_EXT_ID                     (1U)                /*!< Extended ID */
/**
 * @}
 */

/**
 * @defgroup MCAN_ID_Mask MCAN ID Mask
 * @{
 */
#define MCAN_STD_ID_MASK                (0x7FFUL)           /*!< Standard ID mask */
#define MCAN_EXT_ID_MASK                (0x1FFFFFFFUL)      /*!< Extended ID mask */
/**
 * @}
 */

/**
 * @defgroup MCAN_Frame_Format MCAN Frame Format
 * @{
 */
#define MCAN_FRAME_CLASSIC              (0x0U)              /*!< Classic CAN mode */
#define MCAN_FRAME_ISO_FD_NO_BRS        (MCAN_CCCR_FDOE)    /*!< ISO CAN FD mode without bit rate switching */
#define MCAN_FRAME_ISO_FD_BRS           (MCAN_CCCR_FDOE | \
                                         MCAN_CCCR_BRSE)    /*!< ISO CAN FD mode with bit rate switching */
#define MCAN_FRAME_NON_ISO_FD_NO_BRS    (MCAN_CCCR_NISO | \
                                         MCAN_CCCR_FDOE)    /*!< Non-ISO CAN FD mode without bit rate switching */
#define MCAN_FRAME_NON_ISO_FD_BRS       (MCAN_CCCR_NISO | \
                                         MCAN_CCCR_FDOE | \
                                         MCAN_CCCR_BRSE)    /*!< Non-ISO CAN FD mode with bit rate switching */
/**
 * @}
 */

/**
 * @defgroup MCAN_Auto_Retx_Enable MCAN Automatic Retransmission Enable
 * @{
 */
#define MCAN_AUTO_RETX_DISABLE          (MCAN_CCCR_DAR)     /*!< Disable automatic retransmission */
#define MCAN_AUTO_RETX_ENABLE           (0x0U)              /*!< Automatic retransmission of messages not transmitted successfully */
/**
 * @}
 */

/**
 * @defgroup MCAN_Tx_Pause_Enable MCAN Tx Pause Enable
 * @{
 */
#define MCAN_TX_PAUSE_DISABLE           (0x0U)              /*!< Disable transmit pause */
#define MCAN_TX_PAUSE_ENABLE            (MCAN_CCCR_TXP)     /*!< Enable transmit pause */
/**
 * @}
 */

/**
 * @defgroup MCAN_Msg_Marker_Cfg MCAN Message Marker Configuration
 * @{
 */
#define MCAN_MSG_MARKER_8BIT            (0U)                /*!< 8-bit message marker used */
#define MCAN_MSG_MARKER_16BIT           (MCAN_CCCR_WMM)     /*!< 16-bit Message Marker used, replacing 16-bit timestamps in Tx Event FIFO */
/**
 * @}
 */

/**
 * @defgroup MCAN_Protocol_Exception_Enable MCAN Protocol Exception Enable
 * @{
 */
#define MCAN_PROTOCOL_EXP_DISABLE       (MCAN_CCCR_PXHD)    /*!< Disable protocol exception handling */
#define MCAN_PROTOCOL_EXP_ENABLE        (0x0U)              /*!< Enable protocol exception handling */
/**
 * @}
 */

/**
 * @defgroup MCAN_TDC_Enable MCAN Transmitter Delay Compensation Enable
 * @{
 */
#define MCAN_FD_TDC_DISABLE             (0x0U)              /*!< Disable transmitter delay compensation. */
#define MCAN_FD_TDC_ENABLE              (MCAN_DBTP_TDC)     /*!< Enable transmitter delay compensation.  */
/**
 * @}
 */

/**
 * @defgroup MCAN_Tx_Pin_Ctrl MCAN Tx Pin Control
 * @{
 */
#define MCAN_TX_PIN_NORMAL              (0U)                /*!< Tx pin controlled by the CAN Core, updated at the end of the CAN bit time */
#define MCAN_TX_PIN_MONITOR             (MCAN_TEST_TX_0)    /*!< Sample Point can be monitored at Tx pin */
#define MCAN_TX_PIN_DOMINANT            (MCAN_TEST_TX_1)    /*!< Dominant ('0') level at Tx pin */
#define MCAN_TX_PIN_RECESSIVE           (MCAN_TEST_TX)      /*!< Recessive ('1') level at Tx pin */
/**
 * @}
 */

/**
 * @defgroup MCAN_Data_Length_Code MCAN Data Length Code
 * @{
 */
#define MCAN_DLC0                       (0x0U)              /*!< Classic-CAN and FD-CAN: data field size is 0 bytes. */
#define MCAN_DLC1                       (0x1U)              /*!< Classic-CAN and FD-CAN: data field size is 1 bytes. */
#define MCAN_DLC2                       (0x2U)              /*!< Classic-CAN and FD-CAN: data field size is 2 bytes. */
#define MCAN_DLC3                       (0x3U)              /*!< Classic-CAN and FD-CAN: data field size is 3 bytes. */
#define MCAN_DLC4                       (0x4U)              /*!< Classic-CAN and FD-CAN: data field size is 4 bytes. */
#define MCAN_DLC5                       (0x5U)              /*!< Classic-CAN and FD-CAN: data field size is 5 bytes. */
#define MCAN_DLC6                       (0x6U)              /*!< Classic-CAN and FD-CAN: data field size is 6 bytes. */
#define MCAN_DLC7                       (0x7U)              /*!< Classic-CAN and FD-CAN: data field size is 7 bytes. */
#define MCAN_DLC8                       (0x8U)              /*!< Classic-CAN and FD-CAN: data field size is 8 bytes. */
#define MCAN_DLC12                      (0x9U)              /*!< Classic-CAN: data field size is 8 bytes; FD-CAN: data field size is 12 bytes. */
#define MCAN_DLC16                      (0xAU)              /*!< Classic-CAN: data field size is 8 bytes; FD-CAN: data field size is 16 bytes. */
#define MCAN_DLC20                      (0xBU)              /*!< Classic-CAN: data field size is 8 bytes; FD-CAN: data field size is 20 bytes. */
#define MCAN_DLC24                      (0xCU)              /*!< Classic-CAN: data field size is 8 bytes; FD-CAN: data field size is 24 bytes. */
#define MCAN_DLC32                      (0xDU)              /*!< Classic-CAN: data field size is 8 bytes; FD-CAN: data field size is 32 bytes. */
#define MCAN_DLC48                      (0xEU)              /*!< Classic-CAN: data field size is 8 bytes; FD-CAN: data field size is 48 bytes. */
#define MCAN_DLC64                      (0xFU)              /*!< Classic-CAN: data field size is 8 bytes; FD-CAN: data field size is 64 bytes. */
/**
 * @}
 */

/**
 * @defgroup MCAN_Data_Field_Size  MCAN Data Field Size
 * @{
 */
#define MCAN_DATA_SIZE_8BYTE            (0x0U)              /*!< 8 bytes data field */
#define MCAN_DATA_SIZE_12BYTE           (0x1U)              /*!< 12 bytes data field */
#define MCAN_DATA_SIZE_16BYTE           (0x2U)              /*!< 16 bytes data field */
#define MCAN_DATA_SIZE_20BYTE           (0x3U)              /*!< 20 bytes data field */
#define MCAN_DATA_SIZE_24BYTE           (0x4U)              /*!< 24 bytes data field */
#define MCAN_DATA_SIZE_32BYTE           (0x5U)              /*!< 32 bytes data field */
#define MCAN_DATA_SIZE_48BYTE           (0x6U)              /*!< 48 bytes data field */
#define MCAN_DATA_SIZE_64BYTE           (0x7U)              /*!< 64 bytes data field */
/**
 * @}
 */

/**
 * @defgroup MCAN_Tx_FIFO_Queue_Mode MCAN Tx FIFO/Queue Mode
 * @{
 */
#define MCAN_TX_FIFO_MD                 (0x0U)              /*!< Tx FIFO operation mode */
#define MCAN_TX_QUEUE_MD                (MCAN_TXBC_TFQM)    /*!< Tx Queue operation mode */
/**
 * @}
 */

/**
 * @defgroup MCAN_Filter_Type MCAN Filter Type
 * @{
 */
#define MCAN_FILTER_RANGE               (0x0U)              /*!< Range filter from filter ID1 to filter ID2 */
#define MCAN_FILTER_DUAL                (0x1U)              /*!< Dual ID filter for filter ID1 or filter ID2 */
#define MCAN_FILTER_MASK                (0x2U)              /*!< Classic filter: filter ID1 = filter, filter ID2 = mask */
#define MCAN_FILTER_RANGE_NO_EIDM       (0x3U)              /*!< Range filter from filter ID1 to filter ID2, EIDM mask not applied */
/**
 * @}
 */

/**
 * @defgroup MCAN_Filter_Config MCAN Filter Configuration
 * @{
 */
#define MCAN_FILTER_DISABLE             (0x0U)              /*!< Disable filter element */
#define MCAN_FILTER_TO_RX_FIFO0         (0x1U)              /*!< Store in Rx FIFO 0 if filter matches */
#define MCAN_FILTER_TO_RX_FIFO1         (0x2U)              /*!< Store in Rx FIFO 1 if filter matches */
#define MCAN_FILTER_REJECT              (0x3U)              /*!< Reject ID if filter matches */
#define MCAN_FILTER_HP_NO_STORAGE       (0x4U)              /*!< Set high priority if filter matches, no storage */
#define MCAN_FILTER_HP_TO_RX_FIFO0      (0x5U)              /*!< Set high priority and store in FIFO 0 if filter matches */
#define MCAN_FILTER_HP_TO_RX_FIFO1      (0x6U)              /*!< Set high priority and store in FIFO 1 if filter matches */
#define MCAN_FILTER_TO_RX_BUF           (0x7U)              /*!< Store into Rx buffer, configuration of @ref MCAN_Filter_Type ignored */
/**
 * @}
 */

/**
 * @defgroup MCAN_Tx_Location MCAN Tx Location
 * @{
 */
#define MCAN_TX_BUF0                    (0x1UL << 0U)       /*!< Add message to Tx buffer 0  */
#define MCAN_TX_BUF1                    (0x1UL << 1U)       /*!< Add message to Tx buffer 1  */
#define MCAN_TX_BUF2                    (0x1UL << 2U)       /*!< Add message to Tx buffer 2  */
#define MCAN_TX_BUF3                    (0x1UL << 3U)       /*!< Add message to Tx buffer 3  */
#define MCAN_TX_BUF4                    (0x1UL << 4U)       /*!< Add message to Tx buffer 4  */
#define MCAN_TX_BUF5                    (0x1UL << 5U)       /*!< Add message to Tx buffer 5  */
#define MCAN_TX_BUF6                    (0x1UL << 6U)       /*!< Add message to Tx buffer 6  */
#define MCAN_TX_BUF7                    (0x1UL << 7U)       /*!< Add message to Tx buffer 7  */
#define MCAN_TX_BUF8                    (0x1UL << 8U)       /*!< Add message to Tx buffer 8  */
#define MCAN_TX_BUF9                    (0x1UL << 9U)       /*!< Add message to Tx buffer 9  */
#define MCAN_TX_BUF10                   (0x1UL << 10U)      /*!< Add message to Tx buffer 10 */
#define MCAN_TX_BUF11                   (0x1UL << 11U)      /*!< Add message to Tx buffer 11 */
#define MCAN_TX_BUF12                   (0x1UL << 12U)      /*!< Add message to Tx buffer 12 */
#define MCAN_TX_BUF13                   (0x1UL << 13U)      /*!< Add message to Tx buffer 13 */
#define MCAN_TX_BUF14                   (0x1UL << 14U)      /*!< Add message to Tx buffer 14 */
#define MCAN_TX_BUF15                   (0x1UL << 15U)      /*!< Add message to Tx buffer 15 */
#define MCAN_TX_BUF16                   (0x1UL << 16U)      /*!< Add message to Tx buffer 16 */
#define MCAN_TX_BUF17                   (0x1UL << 17U)      /*!< Add message to Tx buffer 17 */
#define MCAN_TX_BUF18                   (0x1UL << 18U)      /*!< Add message to Tx buffer 18 */
#define MCAN_TX_BUF19                   (0x1UL << 19U)      /*!< Add message to Tx buffer 19 */
#define MCAN_TX_BUF20                   (0x1UL << 20U)      /*!< Add message to Tx buffer 20 */
#define MCAN_TX_BUF21                   (0x1UL << 21U)      /*!< Add message to Tx buffer 21 */
#define MCAN_TX_BUF22                   (0x1UL << 22U)      /*!< Add message to Tx buffer 22 */
#define MCAN_TX_BUF23                   (0x1UL << 23U)      /*!< Add message to Tx buffer 23 */
#define MCAN_TX_BUF24                   (0x1UL << 24U)      /*!< Add message to Tx buffer 24 */
#define MCAN_TX_BUF25                   (0x1UL << 25U)      /*!< Add message to Tx buffer 25 */
#define MCAN_TX_BUF26                   (0x1UL << 26U)      /*!< Add message to Tx buffer 26 */
#define MCAN_TX_BUF27                   (0x1UL << 27U)      /*!< Add message to Tx buffer 27 */
#define MCAN_TX_BUF28                   (0x1UL << 28U)      /*!< Add message to Tx buffer 28 */
#define MCAN_TX_BUF29                   (0x1UL << 29U)      /*!< Add message to Tx buffer 29 */
#define MCAN_TX_BUF30                   (0x1UL << 30U)      /*!< Add message to Tx buffer 30 */
#define MCAN_TX_BUF31                   (0x1UL << 31U)      /*!< Add message to Tx buffer 31 */
#define MCAN_TX_BUF_ALL                 (0xFFFFFFFFUL)
/**
 * @}
 */

/**
 * @defgroup MCAN_Rx_Location MCAN Rx Location
 * @{
 */
#define MCAN_RX_FIFO0                   (0x40U)             /*!< Get received message from Rx FIFO 0 */
#define MCAN_RX_FIFO1                   (0x41U)             /*!< Get received message from Rx FIFO 1 */
#define MCAN_RX_BUF0                    (0x00U)             /*!< Get received message from Rx buffer 0 */
#define MCAN_RX_BUF1                    (0x01U)             /*!< Get received message from Rx buffer 1 */
#define MCAN_RX_BUF2                    (0x02U)             /*!< Get received message from Rx buffer 2 */
#define MCAN_RX_BUF3                    (0x03U)             /*!< Get received message from Rx buffer 3 */
#define MCAN_RX_BUF4                    (0x04U)             /*!< Get received message from Rx buffer 4 */
#define MCAN_RX_BUF5                    (0x05U)             /*!< Get received message from Rx buffer 5 */
#define MCAN_RX_BUF6                    (0x06U)             /*!< Get received message from Rx buffer 6 */
#define MCAN_RX_BUF7                    (0x07U)             /*!< Get received message from Rx buffer 7 */
#define MCAN_RX_BUF8                    (0x08U)             /*!< Get received message from Rx buffer 8 */
#define MCAN_RX_BUF9                    (0x09U)             /*!< Get received message from Rx buffer 9 */
#define MCAN_RX_BUF10                   (0x0AU)             /*!< Get received message from Rx buffer 10 */
#define MCAN_RX_BUF11                   (0x0BU)             /*!< Get received message from Rx buffer 11 */
#define MCAN_RX_BUF12                   (0x0CU)             /*!< Get received message from Rx buffer 12 */
#define MCAN_RX_BUF13                   (0x0DU)             /*!< Get received message from Rx buffer 13 */
#define MCAN_RX_BUF14                   (0x0EU)             /*!< Get received message from Rx buffer 14 */
#define MCAN_RX_BUF15                   (0x0FU)             /*!< Get received message from Rx buffer 15 */
#define MCAN_RX_BUF16                   (0x10U)             /*!< Get received message from Rx buffer 16 */
#define MCAN_RX_BUF17                   (0x11U)             /*!< Get received message from Rx buffer 17 */
#define MCAN_RX_BUF18                   (0x12U)             /*!< Get received message from Rx buffer 18 */
#define MCAN_RX_BUF19                   (0x13U)             /*!< Get received message from Rx buffer 19 */
#define MCAN_RX_BUF20                   (0x14U)             /*!< Get received message from Rx buffer 20 */
#define MCAN_RX_BUF21                   (0x15U)             /*!< Get received message from Rx buffer 21 */
#define MCAN_RX_BUF22                   (0x16U)             /*!< Get received message from Rx buffer 22 */
#define MCAN_RX_BUF23                   (0x17U)             /*!< Get received message from Rx buffer 23 */
#define MCAN_RX_BUF24                   (0x18U)             /*!< Get received message from Rx buffer 24 */
#define MCAN_RX_BUF25                   (0x19U)             /*!< Get received message from Rx buffer 25 */
#define MCAN_RX_BUF26                   (0x1AU)             /*!< Get received message from Rx buffer 26 */
#define MCAN_RX_BUF27                   (0x1BU)             /*!< Get received message from Rx buffer 27 */
#define MCAN_RX_BUF28                   (0x1CU)             /*!< Get received message from Rx buffer 28 */
#define MCAN_RX_BUF29                   (0x1DU)             /*!< Get received message from Rx buffer 29 */
#define MCAN_RX_BUF30                   (0x1EU)             /*!< Get received message from Rx buffer 30 */
#define MCAN_RX_BUF31                   (0x1FU)             /*!< Get received message from Rx buffer 31 */
#define MCAN_RX_BUF32                   (0x20U)             /*!< Get received message from Rx buffer 32 */
#define MCAN_RX_BUF33                   (0x21U)             /*!< Get received message from Rx buffer 33 */
#define MCAN_RX_BUF34                   (0x22U)             /*!< Get received message from Rx buffer 34 */
#define MCAN_RX_BUF35                   (0x23U)             /*!< Get received message from Rx buffer 35 */
#define MCAN_RX_BUF36                   (0x24U)             /*!< Get received message from Rx buffer 36 */
#define MCAN_RX_BUF37                   (0x25U)             /*!< Get received message from Rx buffer 37 */
#define MCAN_RX_BUF38                   (0x26U)             /*!< Get received message from Rx buffer 38 */
#define MCAN_RX_BUF39                   (0x27U)             /*!< Get received message from Rx buffer 39 */
#define MCAN_RX_BUF40                   (0x28U)             /*!< Get received message from Rx buffer 40 */
#define MCAN_RX_BUF41                   (0x29U)             /*!< Get received message from Rx buffer 41 */
#define MCAN_RX_BUF42                   (0x2AU)             /*!< Get received message from Rx buffer 42 */
#define MCAN_RX_BUF43                   (0x2BU)             /*!< Get received message from Rx buffer 43 */
#define MCAN_RX_BUF44                   (0x2CU)             /*!< Get received message from Rx buffer 44 */
#define MCAN_RX_BUF45                   (0x2DU)             /*!< Get received message from Rx buffer 45 */
#define MCAN_RX_BUF46                   (0x2EU)             /*!< Get received message from Rx buffer 46 */
#define MCAN_RX_BUF47                   (0x2FU)             /*!< Get received message from Rx buffer 47 */
#define MCAN_RX_BUF48                   (0x30U)             /*!< Get received message from Rx buffer 48 */
#define MCAN_RX_BUF49                   (0x31U)             /*!< Get received message from Rx buffer 49 */
#define MCAN_RX_BUF50                   (0x32U)             /*!< Get received message from Rx buffer 50 */
#define MCAN_RX_BUF51                   (0x33U)             /*!< Get received message from Rx buffer 51 */
#define MCAN_RX_BUF52                   (0x34U)             /*!< Get received message from Rx buffer 52 */
#define MCAN_RX_BUF53                   (0x35U)             /*!< Get received message from Rx buffer 53 */
#define MCAN_RX_BUF54                   (0x36U)             /*!< Get received message from Rx buffer 54 */
#define MCAN_RX_BUF55                   (0x37U)             /*!< Get received message from Rx buffer 55 */
#define MCAN_RX_BUF56                   (0x38U)             /*!< Get received message from Rx buffer 56 */
#define MCAN_RX_BUF57                   (0x39U)             /*!< Get received message from Rx buffer 57 */
#define MCAN_RX_BUF58                   (0x3AU)             /*!< Get received message from Rx buffer 58 */
#define MCAN_RX_BUF59                   (0x3BU)             /*!< Get received message from Rx buffer 59 */
#define MCAN_RX_BUF60                   (0x3CU)             /*!< Get received message from Rx buffer 60 */
#define MCAN_RX_BUF61                   (0x3DU)             /*!< Get received message from Rx buffer 61 */
#define MCAN_RX_BUF62                   (0x3EU)             /*!< Get received message from Rx buffer 62 */
#define MCAN_RX_BUF63                   (0x3FU)             /*!< Get received message from Rx buffer 63 */
#define MCAN_RX_BUF_MAX                 MCAN_RX_BUF63
/**
 * @}
 */

/**
 * @defgroup MCAN_HPM_Storage MCAN High Priority Message Storage
 * @{
 */
#define MCAN_HPM_NO_STORAGE             (0x0U)              /*!< No FIFO selected */
#define MCAN_HPM_LOST                   (0x1U)              /*!< FIFO message lost */
#define MCAN_HPM_STORED_IN_RX_FIFO0     (0x2U)              /*!< Message stored in FIFO 0 */
#define MCAN_HPM_STORED_IN_RX_FIFO1     (0x3U)              /*!< Message stored in FIFO 1 */
/**
 * @}
 */

/**
 * @defgroup MCAN_Protocol_Error_Code MCAN Protocol Error Code
 * @{
 */
#define MCAN_PROTOCOL_NONE_ERR          (0x0U)              /*!< No error occurred */
#define MCAN_PROTOCOL_STUFF_ERR         (0x1U)              /*!< Stuff error */
#define MCAN_PROTOCOL_FORM_ERR          (0x2U)              /*!< Form error */
#define MCAN_PROTOCOL_ACK_ERR           (0x3U)              /*!< Acknowledge error */
#define MCAN_PROTOCOL_BIT1_ERR          (0x4U)              /*!< Bit 1 (recessive) error */
#define MCAN_PROTOCOL_BIT0_ERR          (0x5U)              /*!< Bit 0 (dominant) error */
#define MCAN_PROTOCOL_CRC_ERR           (0x6U)              /*!< CRC check sum error */
#define MCAN_PROTOCOL_ERR_NO_CHANGE     (0x7U)              /*!< No change since last read */
/**
 * @}
 */

/**
 * @defgroup MCAN_Com_State MCAN Communication State
 * @{
 */
#define MCAN_COM_STATE_SYNC             (0x0U)              /*!< Node is synchronizing on CAN communication */
#define MCAN_COM_STATE_IDLE             (0x1U)              /*!< Node is neither receiver nor transmitter */
#define MCAN_COM_STATE_RX               (0x2U)              /*!< Node is operating as receiver */
#define MCAN_COM_STATE_TX               (0x3U)              /*!< Node is operating as transmitter */
/**
 * @}
 */

/**
 * @defgroup MCAN_Protocol_Flag MCAN Protocol Status Flag
 * @{
 */
#define MCAN_PROTOCOL_FLAG_PROTOCOL_EXCEPTION   (MCAN_PSR_PXE)      /*!< Protocol exception event occurred */
#define MCAN_PROTOCOL_FLAG_RX_FDF               (MCAN_PSR_RFDF)     /*!< Message in CAN FD format with FDF flag set has been received */
#define MCAN_PROTOCOL_FLAG_RX_BRS               (MCAN_PSR_RBRS)     /*!< Last received CAN FD message had its BRS flag set */
#define MCAN_PROTOCOL_FLAG_RX_ESI               (MCAN_PSR_RESI)     /*!< Last received CAN FD message had its ESI flag set */
#define MCAN_PROTOCOL_FLAG_BUS_OFF              (MCAN_PSR_BO)       /*!< The MCAN is in Bus_Off state */
#define MCAN_PROTOCOL_FLAG_ERR_WARNING          (MCAN_PSR_EW)       /*!< At least one of error counter has reached the Error_Warning limit of 96 */
#define MCAN_PROTOCOL_FLAG_ERR_PASSIVE          (MCAN_PSR_EP)       /*!< The MCAN is in the Error_Passive state */
#define MCAN_PROTOCOL_FLAG_ALL                  (MCAN_PROTOCOL_FLAG_PROTOCOL_EXCEPTION | MCAN_PROTOCOL_FLAG_RX_FDF | \
                                                 MCAN_PROTOCOL_FLAG_RX_BRS | MCAN_PROTOCOL_FLAG_RX_ESI | \
                                                 MCAN_PROTOCOL_FLAG_BUS_OFF | MCAN_PROTOCOL_FLAG_ERR_WARNING | \
                                                 MCAN_PROTOCOL_FLAG_ERR_PASSIVE)
/**
 * @}
 */

/**
 * @defgroup MCAN_Watermark_Fifo MCAN Watermark FIFO
 * @{
 */
#define MCAN_WATERMARK_RX_FIFO0         (0x0U)              /*!< Rx FIFO0 */
#define MCAN_WATERMARK_RX_FIFO1         (0x1U)              /*!< Rx FIFO1 */
#define MCAN_WATERMARK_TX_EVT_FIFO      (0x2U)              /*!< Tx event FIFO */
/**
 * @}
 */

/**
 * @defgroup MCAN_Rx_Fifo_Operation_Mode MCAN FIFO Operation Mode
 * @{
 */
#define MCAN_RX_FIFO_BLOCKING           (0x0U)              /*!< Rx FIFO blocking mode.
                                                                 New received message will be discarded. */
#define MCAN_RX_FIFO_OVERWRITE          (MCAN_RXF0C_F0OM)   /*!< Rx FIFO overwrite mode.
                                                                 New received message will overwrite the oldest received message. */
/**
 * @}
 */

/**
 * @defgroup MCAN_NMF_Operation MCAN Non-matching Frame Operation
 * @{
 */
#define MCAN_NMF_ACCEPT_IN_RX_FIFO0     (0x0U)              /*!< Accept in Rx FIFO 0 */
#define MCAN_NMF_ACCEPT_IN_RX_FIFO1     (0x1U)              /*!< Accept in Rx FIFO 1 */
#define MCAN_NMF_REJECT                 (0x2U)              /*!< Reject all non-matching frames */
/**
 * @}
 */

/**
 * @defgroup MCAN_Remote_Frame_Operation MCAN Remote Frame Operation
 * @{
 */
#define MCAN_REMOTE_FRAME_FILTER        (0x0U)              /*!< Filter remote frames with ID */
#define MCAN_REMOTE_FRAME_REJECT        (0x1U)              /*!< Reject all remote frames */
/**
 * @}
 */

/**
 * @defgroup MCAN_Interrupt_Line MCAN Interrupt Line
 * @{
 */
#define MCAN_INT_LINE0                  (0x1U)              /*!< Interrupt line 0 */
#define MCAN_INT_LINE1                  (0x2U)              /*!< Interrupt line 1 */
/**
 * @}
 */

/**
 * @defgroup MCAN_Timeout_Select MCAN Timeout Select
 * @{
 */
#define MCAN_TIMEOUT_CONT               (0x0U)              /*!< Timeout continuous operation */
#define MCAN_TIMEOUT_TX_EVT_FIFO        (MCAN_TOCC_TOS_0)   /*!< Timeout controlled by Tx event FIFO */
#define MCAN_TIMEOUT_RX_FIFO0           (MCAN_TOCC_TOS_1)   /*!< Timeout controlled by Rx FIFO0 */
#define MCAN_TIMEOUT_RX_FIFO1           (MCAN_TOCC_TOS)     /*!< Timeout controlled by Rx FIFO1 */
/**
 * @}
 */

/**
 * @defgroup MCAN_Interrupt MCAN Interrupt
 * @{
 */
#define MCAN_INT_RX_FIFO0_NEW_MSG       (MCAN_IE_RF0NE)     /*!< New message written to Rx FIFO 0 */
#define MCAN_INT_RX_FIFO0_WATERMARK     (MCAN_IE_RF0WE)     /*!< Rx FIFO 0 fill level reached watermark */
#define MCAN_INT_RX_FIFO0_FULL          (MCAN_IE_RF0FE)     /*!< Rx FIFO 0 full */
#define MCAN_INT_RX_FIFO0_MSG_LOST      (MCAN_IE_RF0LE)     /*!< Rx FIFO 0 message lost */
#define MCAN_INT_RX_FIFO1_NEW_MSG       (MCAN_IE_RF1NE)     /*!< New message written to Rx FIFO 1 */
#define MCAN_INT_RX_FIFO1_WATERMARK     (MCAN_IE_RF1WE)     /*!< Rx FIFO 1 fill level reached watermark */
#define MCAN_INT_RX_FIFO1_FULL          (MCAN_IE_RF1FE)     /*!< Rx FIFO 1 full */
#define MCAN_INT_RX_FIFO1_MSG_LOST      (MCAN_IE_RF1LE)     /*!< Rx FIFO 1 message lost */
#define MCAN_INT_RX_HPM                 (MCAN_IE_HPME)      /*!< High priority message received */
#define MCAN_INT_TX_CPLT                (MCAN_IE_TCE)       /*!< Transmission completed */
#define MCAN_INT_TX_ABORT_CPLT          (MCAN_IE_TCFE)      /*!< Transmission cancellation finished */
#define MCAN_INT_TX_FIFO_EMPTY          (MCAN_IE_TFEE)      /*!< Tx FIFO empty */
#define MCAN_INT_TX_EVT_FIFO_NEW_DATA   (MCAN_IE_TEFNE)     /*!< Tx handler wrote Tx event FIFO element */
#define MCAN_INT_TX_EVT_FIFO_WATERMARK  (MCAN_IE_TEFWE)     /*!< Tx event FIFO fill level reached watermark */
#define MCAN_INT_TX_EVT_FIFO_FULL       (MCAN_IE_TEFFE)     /*!< Tx event FIFO full */
#define MCAN_INT_TX_EVT_FIFO_LOST       (MCAN_IE_TEFLE)     /*!< Tx event FIFO element lost */
#define MCAN_INT_TIMESTAMP_WRAPAROUND   (MCAN_IE_TSWE)      /*!< Timestamp counter wrapped around */
#define MCAN_INT_RAM_ACCESS_FAILURE     (MCAN_IE_MRAFE)     /*!< Message RAM access failure occurred */
#define MCAN_INT_TIMEOUT                (MCAN_IE_TOOE)      /*!< Timeout reached */
#define MCAN_INT_RX_BUF_NEW_MSG         (MCAN_IE_DRXE)      /*!< At least one received message stored into a Rx buffer */
#define MCAN_INT_ERR_LOG_OVF            (MCAN_IE_ELOE)      /*!< Overflow of CAN error logging counter occurred */
#define MCAN_INT_ERR_PASSIVE            (MCAN_IE_EPE)       /*!< Error_Passive status changed */
#define MCAN_INT_ERR_WARNING            (MCAN_IE_EWE)       /*!< Error_Warning status changed */
#define MCAN_INT_BUS_OFF                (MCAN_IE_BOE)       /*!< Bus_Off status changed */
#define MCAN_INT_RAM_WDT                (MCAN_IE_WDIE)      /*!< Message RAM Watchdog event due to missing READY */
#define MCAN_INT_ARB_PHASE_ERROR        (MCAN_IE_PEAE)      /*!< Protocol error in arbitration phase detected */
#define MCAN_INT_DATA_PHASE_ERROR       (MCAN_IE_PEDE)      /*!< Protocol error in data phase detected */
#define MCAN_INT_RSVD_ADDR_ACCESS       (MCAN_IE_ARAE)      /*!< Access to reserved address occurred */
#define MCAN_INT_ALL                    (0x3FCFFFFFUL)
/**
 * @}
 */

/**
 * @defgroup MCAN_Interrupt_Flag MCAN Interrupt Flag
 * @{
 */
#define MCAN_FLAG_RX_FIFO0_NEW_MSG      (MCAN_IR_RF0N)      /*!< New message written to Rx FIFO 0 */
#define MCAN_FLAG_RX_FIFO0_WATERMARK    (MCAN_IR_RF0W)      /*!< Rx FIFO 0 fill level reached watermark */
#define MCAN_FLAG_RX_FIFO0_FULL         (MCAN_IR_RF0F)      /*!< Rx FIFO 0 full */
#define MCAN_FLAG_RX_FIFO0_MSG_LOST     (MCAN_IR_RF0L)      /*!< Rx FIFO 0 message lost */
#define MCAN_FLAG_RX_FIFO1_NEW_MSG      (MCAN_IR_RF1N)      /*!< New message written to Rx FIFO 1 */
#define MCAN_FLAG_RX_FIFO1_WATERMARK    (MCAN_IR_RF1W)      /*!< Rx FIFO 1 fill level reached watermark */
#define MCAN_FLAG_RX_FIFO1_FULL         (MCAN_IR_RF1F)      /*!< Rx FIFO 1 full */
#define MCAN_FLAG_RX_FIFO1_MSG_LOST     (MCAN_IR_RF1L)      /*!< Rx FIFO 1 message lost */
#define MCAN_FLAG_RX_HPM                (MCAN_IR_HPM)       /*!< High priority message received */
#define MCAN_FLAG_TX_CPLT               (MCAN_IR_TC)        /*!< Transmission completed */
#define MCAN_FLAG_TX_ABORT_CPLT         (MCAN_IR_TCF)       /*!< Transmission cancellation finished */
#define MCAN_FLAG_TX_FIFO_EMPTY         (MCAN_IR_TFE)       /*!< Tx FIFO empty */
#define MCAN_FLAG_TX_EVT_FIFO_NEW_DATA  (MCAN_IR_TEFN)      /*!< Tx handler wrote Tx event FIFO element */
#define MCAN_FLAG_TX_EVT_FIFO_WATERMARK (MCAN_IR_TEFW)      /*!< Tx event FIFO fill level reached watermark */
#define MCAN_FLAG_TX_EVT_FIFO_FULL      (MCAN_IR_TEFF)      /*!< Tx event FIFO full */
#define MCAN_FLAG_TX_EVT_FIFO_LOST      (MCAN_IR_TEFL)      /*!< Tx event FIFO element lost */
#define MCAN_FLAG_TIMESTAMP_WRAPAROUND  (MCAN_IR_TSW)       /*!< Timestamp counter wrapped around */
#define MCAN_FLAG_RAM_ACCESS_FAILURE    (MCAN_IR_MRAF)      /*!< Message RAM access failure occurred */
#define MCAN_FLAG_TIMEOUT               (MCAN_IR_TOO)       /*!< Timeout reached */
#define MCAN_FLAG_RX_BUF_NEW_MSG        (MCAN_IR_DRX)       /*!< At least one received message stored into a Rx buffer */
#define MCAN_FLAG_ERR_LOG_OVF           (MCAN_IR_ELO)       /*!< Overflow of CAN error logging counter occurred */
#define MCAN_FLAG_ERR_PASSIVE           (MCAN_IR_EP)        /*!< Error_Passive status changed */
#define MCAN_FLAG_ERR_WARNING           (MCAN_IR_EW)        /*!< Error_Warning status changed */
#define MCAN_FLAG_BUS_OFF               (MCAN_IR_BO)        /*!< Bus_Off status changed */
#define MCAN_FLAG_RAM_WDT               (MCAN_IR_WDI)       /*!< Message RAM Watchdog event due to missing READY */
#define MCAN_FLAG_ARB_PHASE_ERROR       (MCAN_IR_PEA)       /*!< Protocol error in arbitration phase detected */
#define MCAN_FLAG_DATA_PHASE_ERROR      (MCAN_IR_PED)       /*!< Protocol error in data phase detected */
#define MCAN_FLAG_RSVD_ADDR_ACCESS      (MCAN_IR_ARA)       /*!< Access to reserved address occurred */
#define MCAN_FLAG_ALL                   (0x3FCFFFFFUL)
/**
 * @}
 */

/**
 * @defgroup MCAN_Evt_Type MCAN Event Type
 * @{
 */
#define MCAN_EVT_TX_EVT                 (0x01U)             /*!< Tx event */
#define MCAN_EVT_TX_WHEN_ABORTED        (0x02U)             /*!< Transmission in spite of cancellation (always set for transmissions in DAR mode) */
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup MCAN_Global_Functions
 * @{
 */
/* Initialization and de-initialization functions *****************************/
int32_t MCAN_Init(CM_MCAN_TypeDef *MCANx, stc_mcan_init_t *pstcMcanInit);
int32_t MCAN_StructInit(stc_mcan_init_t *pstcMcanInit);
void MCAN_DeInit(CM_MCAN_TypeDef *MCANx);
void MCAN_Start(CM_MCAN_TypeDef *MCANx);
int32_t MCAN_Stop(CM_MCAN_TypeDef *MCANx);
int32_t MCAN_EnterSleepMode(CM_MCAN_TypeDef *MCANx);
int32_t MCAN_ExitSleepMode(CM_MCAN_TypeDef *MCANx);
int32_t MCAN_GetMsgRamAddr(const CM_MCAN_TypeDef *MCANx, stc_mcan_msg_ram_addr_t *pstcAddr);

/* Configuration functions ****************************************************/
int32_t MCAN_FilterConfig(const CM_MCAN_TypeDef *MCANx, const stc_mcan_filter_t *pstcFilter);
void MCAN_GlobalFilterConfig(CM_MCAN_TypeDef *MCANx, \
                             uint32_t u32StdNmfOperation, uint32_t u32ExtNmfOperation, \
                             uint32_t u32StdRemoteOperation, uint32_t u32ExtRemoteOperation);
void MCAN_SetExtIDMask(CM_MCAN_TypeDef *MCANx, uint32_t u32Mask);
void MCAN_RxFifoOperationModeConfig(CM_MCAN_TypeDef *MCANx, uint32_t u32RxFifo, uint32_t u32OperationMode);
void MCAN_SetFifoWatermark(CM_MCAN_TypeDef *MCANx, uint32_t u32Fifo, uint32_t u32Watermark);
void MCAN_RamWatchdogConfig(CM_MCAN_TypeDef *MCANx, uint32_t u32StartValue);
uint8_t MCAN_GetRamWatchdogCountValue(const CM_MCAN_TypeDef *MCANx);
void MCAN_TimestampCounterConfig(CM_MCAN_TypeDef *MCANx, uint32_t u32TsPrescaler);
void MCAN_TimestampCounterCmd(CM_MCAN_TypeDef *MCANx, en_functional_state_t enNewState);
uint16_t MCAN_GetTimestampCounter(const CM_MCAN_TypeDef *MCANx);
void MCAN_ResetTimestampCounter(CM_MCAN_TypeDef *MCANx);
void MCAN_TimeoutCounterConfig(CM_MCAN_TypeDef *MCANx, uint32_t u32ToSelect, uint32_t u32ToPeriod);
void MCAN_TimeoutCounterCmd(CM_MCAN_TypeDef *MCANx, en_functional_state_t enNewState);
uint16_t MCAN_GetTimeoutCounter(const CM_MCAN_TypeDef *MCANx);
void MCAN_ResetTimeoutCounter(CM_MCAN_TypeDef *MCANx);
void MCAN_TxDelayCompensationConfig(CM_MCAN_TypeDef *MCANx, uint32_t u32SspOffset, uint32_t u32TdcFilter);
void MCAN_TxDelayCompensationCmd(CM_MCAN_TypeDef *MCANx, en_functional_state_t enNewState);
void MCAN_SetFrameFormat(CM_MCAN_TypeDef *MCANx, uint32_t u32FrameFormat);
void MCAN_EdgeFilteringCmd(CM_MCAN_TypeDef *MCANx, en_functional_state_t enNewState);
void MCAN_TxEventMsgMarkerConfig(CM_MCAN_TypeDef *MCANx, uint32_t u32MsgMarker);

/* Control functions **********************************************************/
int32_t MCAN_AddMsgToTxFifoQueue(CM_MCAN_TypeDef *MCANx, stc_mcan_tx_msg_t *pTxMsg);
int32_t MCAN_AddMsgToTxBuffer(CM_MCAN_TypeDef *MCANx, stc_mcan_tx_msg_t *pTxMsg);
void MCAN_EnableTxBufferRequest(CM_MCAN_TypeDef *MCANx, uint32_t u32TxBuffer);
void MCAN_AbortTxRequest(CM_MCAN_TypeDef *MCANx, uint32_t u32TxBuffer);
int32_t MCAN_GetRxMsg(CM_MCAN_TypeDef *MCANx, uint32_t u32RxLocation, stc_mcan_rx_msg_t *pRxMsg);
int32_t MCAN_GetTxEvent(CM_MCAN_TypeDef *MCANx, stc_mcan_tx_event_t *pTxEvent);
int32_t MCAN_GetHighPriorityMsgStatus(const CM_MCAN_TypeDef *MCANx, stc_mcan_hpm_status_t *pHpmStatus);

int32_t MCAN_GetProtocolStatus(const CM_MCAN_TypeDef *MCANx, stc_mcan_protocol_status_t *pProtocolStatus);
uint8_t MCAN_GetTdcValue(const CM_MCAN_TypeDef *MCANx);
uint8_t MCAN_GetDataLastErrorCode(const CM_MCAN_TypeDef *MCANx);
uint8_t MCAN_GetLastErrorCode(const CM_MCAN_TypeDef *MCANx);
uint8_t MCAN_GetComState(const CM_MCAN_TypeDef *MCANx);
en_flag_status_t MCAN_GetProtocolFlagStatus(const CM_MCAN_TypeDef *MCANx, uint32_t u32PsFlag);
int32_t MCAN_GetErrorCounter(const CM_MCAN_TypeDef *MCANx, stc_mcan_error_counter_t *pErrorCounter);

en_flag_status_t MCAN_GetStatus(const CM_MCAN_TypeDef *MCANx, uint32_t u32Flag);
void MCAN_ClearStatus(CM_MCAN_TypeDef *MCANx, uint32_t u32Flag);
uint32_t MCAN_GetTxOccurredList(const CM_MCAN_TypeDef *MCANx);
uint32_t MCAN_GetTxAbortedList(const CM_MCAN_TypeDef *MCANx);
int32_t MCAN_CheckTxOccurred(const CM_MCAN_TypeDef *MCANx, uint32_t u32TxBuffer);
int32_t MCAN_CheckTxAborted(const CM_MCAN_TypeDef *MCANx, uint32_t u32TxBuffer);

int32_t MCAN_CheckRxBufferMsgAvailable(CM_MCAN_TypeDef *MCANx, uint32_t u32RxBufferIndex);
int32_t MCAN_CheckTxBufferPending(const CM_MCAN_TypeDef *MCANx, uint32_t u32TxBuffer);
uint32_t MCAN_GetRxFifoFillLevel(const CM_MCAN_TypeDef *MCANx, uint32_t u32RxFifo);
uint32_t MCAN_GetTxFifoFreeLevel(const CM_MCAN_TypeDef *MCANx);
int32_t MCAN_CheckRestrictedOperationMode(const CM_MCAN_TypeDef *MCANx);
void MCAN_ExitRestrictedOperationMode(CM_MCAN_TypeDef *MCANx);

uint8_t MCAN_GetStartedTxBufferNum(const CM_MCAN_TypeDef *MCANx);
uint8_t MCAN_GetPreparedTxBufferNum(const CM_MCAN_TypeDef *MCANx);
uint8_t MCAN_GetBusLogicalState(const CM_MCAN_TypeDef *MCANx);
void MCAN_TxPinControl(CM_MCAN_TypeDef *MCANx, uint32_t u32PinCtrl);

/* Interrupts management ******************************************************/
void MCAN_IntCmd(CM_MCAN_TypeDef *MCANx, uint32_t u32IntType, uint32_t u32IntLine, \
                 en_functional_state_t enNewState);
void MCAN_TxBufferNotificationCmd(CM_MCAN_TypeDef *MCANx, uint32_t u32TxBuffer, \
                                  uint32_t u32Notification, en_functional_state_t enNewState);

/**
 * @}
 */

#endif /* LL_MCAN_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_MCAN_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
