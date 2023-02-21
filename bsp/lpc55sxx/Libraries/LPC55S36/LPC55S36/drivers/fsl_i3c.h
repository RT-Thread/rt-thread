/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_I3C_H_
#define _FSL_I3C_H_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @addtogroup i3c
 * @{
 */

/*! @name Driver version */
/*@{*/
/*! @brief I3C driver version */
#define FSL_I3C_DRIVER_VERSION (MAKE_VERSION(2, 5, 2))
/*@}*/

/*! @brief Timeout times for waiting flag. */
#ifndef I3C_RETRY_TIMES
#define I3C_RETRY_TIMES 0U /* Define to zero means keep waiting until the flag is assert/deassert. */
#endif

#define I3C_MAX_DEVCNT 10U

#ifndef I3C_IBI_BUFF_SIZE
#define I3C_IBI_BUFF_SIZE 10U
#endif

/*! @brief I3C status return codes. */
enum
{
    kStatus_I3C_Busy = MAKE_STATUS(kStatusGroup_I3C, 0), /*!< The master is already performing a transfer. */
    kStatus_I3C_Idle = MAKE_STATUS(kStatusGroup_I3C, 1), /*!< The slave driver is idle. */
    kStatus_I3C_Nak  = MAKE_STATUS(kStatusGroup_I3C, 2), /*!< The slave device sent a NAK in response to an address. */
    kStatus_I3C_WriteAbort =
        MAKE_STATUS(kStatusGroup_I3C, 3), /*!< The slave device sent a NAK in response to a write. */
    kStatus_I3C_Term           = MAKE_STATUS(kStatusGroup_I3C, 4), /*!< The master terminates slave read. */
    kStatus_I3C_HdrParityError = MAKE_STATUS(kStatusGroup_I3C, 5), /*!< Parity error from DDR read. */
    kStatus_I3C_CrcError       = MAKE_STATUS(kStatusGroup_I3C, 6), /*!< CRC error from DDR read. */
    kStatus_I3C_ReadFifoError  = MAKE_STATUS(kStatusGroup_I3C, 7), /*!< Read from M/SRDATAB register when FIFO empty. */
    kStatus_I3C_WriteFifoError = MAKE_STATUS(kStatusGroup_I3C, 8), /*!< Write to M/SWDATAB register when FIFO full. */
    kStatus_I3C_MsgError =
        MAKE_STATUS(kStatusGroup_I3C, 9), /*!< Message SDR/DDR mismatch or read/write message in wrong state */
    kStatus_I3C_InvalidReq = MAKE_STATUS(kStatusGroup_I3C, 10), /*!< Invalid use of request. */
    kStatus_I3C_Timeout    = MAKE_STATUS(kStatusGroup_I3C, 11), /*!< The module has stalled too long in a frame. */
    kStatus_I3C_SlaveCountExceed =
        MAKE_STATUS(kStatusGroup_I3C, 12), /*!< The I3C slave count has exceed the definition in I3C_MAX_DEVCNT. */
    kStatus_I3C_IBIWon = MAKE_STATUS(
        kStatusGroup_I3C, 13), /*!< The I3C slave event IBI or MR or HJ won the arbitration on a header address. */
    kStatus_I3C_OverrunError  = MAKE_STATUS(kStatusGroup_I3C, 14), /*!< Slave internal from-bus buffer/FIFO overrun. */
    kStatus_I3C_UnderrunError = MAKE_STATUS(kStatusGroup_I3C, 15), /*!< Slave internal to-bus buffer/FIFO underrun */
    kStatus_I3C_UnderrunNak =
        MAKE_STATUS(kStatusGroup_I3C, 16), /*!< Slave internal from-bus buffer/FIFO underrun and NACK error */
    kStatus_I3C_InvalidStart   = MAKE_STATUS(kStatusGroup_I3C, 17), /*!< Slave invalid start flag */
    kStatus_I3C_SdrParityError = MAKE_STATUS(kStatusGroup_I3C, 18), /*!< SDR parity error */
    kStatus_I3C_S0S1Error      = MAKE_STATUS(kStatusGroup_I3C, 19), /*!< S0 or S1 error */
};

/*! @brief I3C HDR modes. */
typedef enum _i3c_hdr_mode
{
    kI3C_HDRModeNone = 0x00U, /* Do not support HDR mode. */
    kI3C_HDRModeDDR  = 0x01U, /* HDR-DDR Mode. */
    kI3C_HDRModeTSP  = 0x02U, /* HDR-TSP Mode. */
    kI3C_HDRModeTSL  = 0x04U, /* HDR-TSL Mode. */
} i3c_hdr_mode_t;

/*! @brief I3C device information. */
typedef struct _i3c_device_info
{
    uint8_t dynamicAddr;     /*!< Device dynamic address. */
    uint8_t staticAddr;      /*!< Static address. */
    uint8_t dcr;             /*!< Device characteristics register information. */
    uint8_t bcr;             /*!< Bus characteristics register information. */
    uint16_t vendorID;       /*!< Device vendor ID(manufacture ID). */
    uint32_t partNumber;     /*!< Device part number info */
    uint16_t maxReadLength;  /*!< Maximum read length. */
    uint16_t maxWriteLength; /*!< Maximum write length. */
    uint8_t hdrMode;         /*!< Support hdr mode, could be OR logic in i3c_hdr_mode. */
} i3c_device_info_t;

/*! @} */

/*!
 * @addtogroup i3c_master_driver
 * @{
 */

/*!
 * @brief I3C master peripheral flags.
 *
 * The following status register flags can be cleared:
 * - #kI3C_MasterSlaveStartFlag
 * - #kI3C_MasterControlDoneFlag
 * - #kI3C_MasterCompleteFlag
 * - #kI3C_MasterArbitrationWonFlag
 * - #kI3C_MasterSlave2MasterFlag
 *
 * All flags except #kI3C_MasterBetweenFlag and #kI3C_MasterNackDetectFlag can be enabled as
 * interrupts.
 *
 * @note These enums are meant to be OR'd together to form a bit mask.
 */
enum _i3c_master_flags
{
    kI3C_MasterBetweenFlag        = I3C_MSTATUS_BETWEEN_MASK,   /*!< Between messages/DAAs flag */
    kI3C_MasterNackDetectFlag     = I3C_MSTATUS_NACKED_MASK,    /*!< NACK detected flag */
    kI3C_MasterSlaveStartFlag     = I3C_MSTATUS_SLVSTART_MASK,  /*!< Slave request start flag */
    kI3C_MasterControlDoneFlag    = I3C_MSTATUS_MCTRLDONE_MASK, /*!< Master request complete flag */
    kI3C_MasterCompleteFlag       = I3C_MSTATUS_COMPLETE_MASK,  /*!< Transfer complete flag */
    kI3C_MasterRxReadyFlag        = I3C_MSTATUS_RXPEND_MASK,    /*!< Rx data ready in Rx buffer flag */
    kI3C_MasterTxReadyFlag        = I3C_MSTATUS_TXNOTFULL_MASK, /*!< Tx buffer ready for Tx data flag */
    kI3C_MasterArbitrationWonFlag = I3C_MSTATUS_IBIWON_MASK,    /*!< Header address won arbitration flag */
    kI3C_MasterErrorFlag          = I3C_MSTATUS_ERRWARN_MASK,   /*!< Error occurred flag */
    kI3C_MasterSlave2MasterFlag   = I3C_MSTATUS_NOWMASTER_MASK, /*!< Switch from slave to master flag */
    kI3C_MasterClearFlags         = kI3C_MasterSlaveStartFlag | kI3C_MasterControlDoneFlag | kI3C_MasterCompleteFlag |
                            kI3C_MasterArbitrationWonFlag | kI3C_MasterSlave2MasterFlag | kI3C_MasterErrorFlag,
};

/*!
 * @brief I3C master error flags to indicate the causes.
 *
 * @note These enums are meant to be OR'd together to form a bit mask.
 */
enum _i3c_master_error_flags
{
    kI3C_MasterErrorNackFlag       = I3C_MERRWARN_NACK_MASK,  /*!< Slave NACKed the last address */
    kI3C_MasterErrorWriteAbortFlag = I3C_MERRWARN_WRABT_MASK, /*!< Slave NACKed the write data */
#if !defined(FSL_FEATURE_I3C_HAS_NO_MERRWARN_TERM) || (!FSL_FEATURE_I3C_HAS_NO_MERRWARN_TERM)
    kI3C_MasterErrorTermFlag = I3C_MERRWARN_TERM_MASK, /*!< Master terminates slave read */
#endif
    kI3C_MasterErrorParityFlag = I3C_MERRWARN_HPAR_MASK,        /*!< Parity error from DDR read */
    kI3C_MasterErrorCrcFlag    = I3C_MERRWARN_HCRC_MASK,        /*!< CRC error from DDR read */
    kI3C_MasterErrorReadFlag   = I3C_MERRWARN_OREAD_MASK,       /*!< Read from MRDATAB register when FIFO empty */
    kI3C_MasterErrorWriteFlag  = I3C_MERRWARN_OWRITE_MASK,      /*!< Write to MWDATAB register when FIFO full */
    kI3C_MasterErrorMsgFlag    = I3C_MERRWARN_MSGERR_MASK,      /*!< Message SDR/DDR mismatch or
            read/write message in wrong state */
    kI3C_MasterErrorInvalidReqFlag = I3C_MERRWARN_INVREQ_MASK,  /*!< Invalid use of request */
    kI3C_MasterErrorTimeoutFlag    = I3C_MERRWARN_TIMEOUT_MASK, /*!< The module has stalled too long in a frame */
    kI3C_MasterAllErrorFlags       = kI3C_MasterErrorNackFlag | kI3C_MasterErrorWriteAbortFlag |
#if !defined(FSL_FEATURE_I3C_HAS_NO_MERRWARN_TERM) || (!FSL_FEATURE_I3C_HAS_NO_MERRWARN_TERM)
                               kI3C_MasterErrorTermFlag |
#endif
                               kI3C_MasterErrorParityFlag | kI3C_MasterErrorCrcFlag | kI3C_MasterErrorReadFlag |
                               kI3C_MasterErrorWriteFlag | kI3C_MasterErrorMsgFlag | kI3C_MasterErrorInvalidReqFlag |
                               kI3C_MasterErrorTimeoutFlag, /*!< All error flags */
};

/*! @brief I3C working master state. */
typedef enum _i3c_master_state
{
    kI3C_MasterStateIdle    = 0U, /*!< Bus stopped. */
    kI3C_MasterStateSlvReq  = 1U, /*!< Bus stopped but slave holding SDA low. */
    kI3C_MasterStateMsgSdr  = 2U, /*!< In SDR Message mode from using MWMSG_SDR. */
    kI3C_MasterStateNormAct = 3U, /*!< In normal active SDR mode. */
    kI3C_MasterStateDdr     = 4U, /*!< In DDR Message mode. */
    kI3C_MasterStateDaa     = 5U, /*!< In ENTDAA mode. */
    kI3C_MasterStateIbiAck  = 6U, /*!< Waiting on IBI ACK/NACK decision. */
    kI3C_MasterStateIbiRcv  = 7U, /*!< receiving IBI. */
} i3c_master_state_t;

/*! @brief I3C master enable configuration. */
typedef enum _i3c_master_enable
{
    kI3C_MasterOff     = 0U, /*!< Master off. */
    kI3C_MasterOn      = 1U, /*!< Master on. */
    kI3C_MasterCapable = 2U  /*!< Master capable. */
} i3c_master_enable_t;

/*! @brief I3C high keeper configuration. */
typedef enum _i3c_master_hkeep
{
    kI3C_MasterHighKeeperNone    = 0U, /*!< Use PUR to hold SCL high. */
    kI3C_MasterHighKeeperWiredIn = 1U, /*!< Use pin_HK controls. */
    kI3C_MasterPassiveSDA        = 2U, /*!< Hi-Z for Bus Free and hold SDA. */
    kI3C_MasterPassiveSDASCL     = 3U  /*!< Hi-Z both for Bus Free, and can Hi-Z SDA for hold. */
} i3c_master_hkeep_t;

/*! @brief Emits the requested operation when doing in pieces vs. by message. */
typedef enum _i3c_bus_request
{
    kI3C_RequestNone          = 0U, /*!< No request. */
    kI3C_RequestEmitStartAddr = 1U, /*!< Request to emit start and address on bus. */
    kI3C_RequestEmitStop      = 2U, /*!< Request to emit stop on bus. */
    kI3C_RequestIbiAckNack    = 3U, /*!< Manual IBI ACK or NACK. */
    kI3C_RequestProcessDAA    = 4U, /*!< Process DAA. */
    kI3C_RequestForceExit     = 6U, /*!< Request to force exit. */
    kI3C_RequestAutoIbi       = 7U, /*!< Hold in stopped state, but Auto-emit START,7E. */
} i3c_bus_request_t;

/*! @brief Bus type with EmitStartAddr. */
typedef enum _i3c_bus_type
{
    kI3C_TypeI3CSdr = 0U, /*!< SDR mode of I3C. */
    kI3C_TypeI2C    = 1U, /*!< Standard i2c protocol. */
    kI3C_TypeI3CDdr = 2U, /*!< HDR-DDR mode of I3C. */
} i3c_bus_type_t;

/*! @brief IBI response. */
typedef enum _i3c_ibi_response
{
    kI3C_IbiRespAck          = 0U, /*!< ACK with no mandatory byte. */
    kI3C_IbiRespNack         = 1U, /*!< NACK. */
    kI3C_IbiRespAckMandatory = 2U, /*!< ACK with mandatory byte. */
    kI3C_IbiRespManual       = 3U, /*!< Reserved. */
} i3c_ibi_response_t;

/*! @brief IBI type. */
typedef enum _i3c_ibi_type
{
    kI3C_IbiNormal        = 0U, /*!< In-band interrupt. */
    kI3C_IbiHotJoin       = 1U, /*!< slave hot join. */
    kI3C_IbiMasterRequest = 2U, /*!< slave master ship request. */
} i3c_ibi_type_t;

/*! @brief IBI state. */
typedef enum _i3c_ibi_state
{
    kI3C_IbiReady          = 0U, /*!< In-band interrupt ready state, ready for user to handle. */
    kI3C_IbiDataBuffNeed   = 1U, /*!< In-band interrupt need data buffer for data receive. */
    kI3C_IbiAckNackPending = 2U, /*!< In-band interrupt Ack/Nack pending for decision. */
} i3c_ibi_state_t;

/*! @brief Direction of master and slave transfers. */
typedef enum _i3c_direction
{
    kI3C_Write = 0U, /*!< Master transmit. */
    kI3C_Read  = 1U  /*!< Master receive. */
} i3c_direction_t;

/*! @brief Watermark of TX int/dma trigger level. */
typedef enum _i3c_tx_trigger_level
{
    kI3C_TxTriggerOnEmpty               = 0U, /*!< Trigger on empty. */
    kI3C_TxTriggerUntilOneQuarterOrLess = 1U, /*!< Trigger on 1/4 full or less. */
    kI3C_TxTriggerUntilOneHalfOrLess    = 2U, /*!< Trigger on 1/2 full or less. */
    kI3C_TxTriggerUntilOneLessThanFull  = 3U, /*!< Trigger on 1 less than full or less. */
} i3c_tx_trigger_level_t;

/*! @brief Watermark of RX int/dma trigger level. */
typedef enum _i3c_rx_trigger_level
{
    kI3C_RxTriggerOnNotEmpty              = 0U, /*!< Trigger on not empty. */
    kI3C_RxTriggerUntilOneQuarterOrMore   = 1U, /*!< Trigger on 1/4 full or more. */
    kI3C_RxTriggerUntilOneHalfOrMore      = 2U, /*!< Trigger on 1/2 full or more. */
    kI3C_RxTriggerUntilThreeQuarterOrMore = 3U, /*!< Trigger on 3/4 full or more. */
} i3c_rx_trigger_level_t;

/*! @brief Structure with setting master IBI rules and slave registry. */
typedef struct _i3c_register_ibi_addr
{
    uint8_t address[5]; /*!< Address array for registry. */
    bool ibiHasPayload; /*!< Whether the address array has mandatory IBI byte. */
} i3c_register_ibi_addr_t;

/*! @brief Structure with I3C baudrate settings. */
typedef struct _i3c_baudrate
{
    uint32_t i2cBaud;          /*!< Desired I2C baud rate in Hertz. */
    uint32_t i3cPushPullBaud;  /*!< Desired I3C push-pull baud rate in Hertz. */
    uint32_t i3cOpenDrainBaud; /*!< Desired I3C open-drain baud rate in Hertz. */
} i3c_baudrate_hz_t;

/*!
 * @brief Structure with settings to initialize the I3C master module.
 *
 * This structure holds configuration settings for the I3C peripheral. To initialize this
 * structure to reasonable defaults, call the I3C_MasterGetDefaultConfig() function and
 * pass a pointer to your configuration structure instance.
 *
 * The configuration structure can be made constant so it resides in flash.
 */
typedef struct _i3c_master_config
{
    i3c_master_enable_t enableMaster; /*!< Enable master mode. */
    bool disableTimeout;              /*!< Whether to disable timeout to prevent the ERRWARN. */
    i3c_master_hkeep_t hKeep;         /*!< High keeper mode setting. */
    bool enableOpenDrainStop;         /*!< Whether to emit open-drain speed STOP. */
    bool enableOpenDrainHigh;         /*!< Enable Open-Drain High to be 1 PPBAUD count for i3c messages, or 1 ODBAUD. */
    i3c_baudrate_hz_t baudRate_Hz;    /*!< Desired baud rate settings. */
} i3c_master_config_t;

/* Forward declaration of the transfer descriptor and handle typedefs. */
typedef struct _i3c_master_transfer i3c_master_transfer_t;
typedef struct _i3c_master_handle i3c_master_handle_t;

/*! @brief i3c master callback functions. */
typedef struct _i3c_master_transfer_callback
{
    void (*slave2Master)(I3C_Type *base, void *userData); /*!< Transfer complete callback */
    void (*ibiCallback)(I3C_Type *base,
                        i3c_master_handle_t *handle,
                        i3c_ibi_type_t ibiType,
                        i3c_ibi_state_t ibiState); /*!< IBI event callback */
    void (*transferComplete)(I3C_Type *base,
                             i3c_master_handle_t *handle,
                             status_t completionStatus,
                             void *userData); /*!< Transfer complete callback */
} i3c_master_transfer_callback_t;
/*!
 * @brief Transfer option flags.
 *
 * @note These enumerations are intended to be OR'd together to form a bit mask of options for
 * the #_i3c_master_transfer::flags field.
 */
enum _i3c_master_transfer_flags
{
    kI3C_TransferDefaultFlag       = 0x00U, /*!< Transfer starts with a start signal, stops with a stop signal. */
    kI3C_TransferNoStartFlag       = 0x01U, /*!< Don't send a start condition, address, and sub address */
    kI3C_TransferRepeatedStartFlag = 0x02U, /*!< Send a repeated start condition */
    kI3C_TransferNoStopFlag        = 0x04U, /*!< Don't send a stop condition. */
    kI3C_TransferWordsFlag         = 0x08U, /*!< Transfer in words, else transfer in bytes. */
};

/*!
 * @brief Non-blocking transfer descriptor structure.
 *
 * This structure is used to pass transaction parameters to the I3C_MasterTransferNonBlocking() API.
 */
struct _i3c_master_transfer
{
    uint32_t flags; /*!< Bit mask of options for the transfer. See enumeration #_i3c_master_transfer_flags for available
                       options. Set to 0 or #kI3C_TransferDefaultFlag for normal transfers. */
    uint8_t slaveAddress;           /*!< The 7-bit slave address. */
    i3c_direction_t direction;      /*!< Either #kI3C_Read or #kI3C_Write. */
    uint32_t subaddress;            /*!< Sub address. Transferred MSB first. */
    size_t subaddressSize;          /*!< Length of sub address to send in bytes. Maximum size is 4 bytes. */
    void *data;                     /*!< Pointer to data to transfer. */
    size_t dataSize;                /*!< Number of bytes to transfer. */
    i3c_bus_type_t busType;         /*!< bus type. */
    i3c_ibi_response_t ibiResponse; /*!< ibi response during transfer. */
};

/*!
 * @brief Driver handle for master non-blocking APIs.
 * @note The contents of this structure are private and subject to change.
 */
struct _i3c_master_handle
{
    uint8_t state;                           /*!< Transfer state machine current state. */
    uint32_t remainingBytes;                 /*!< Remaining byte count in current state. */
    bool isReadTerm;                         /*!< Is readterm configured. */
    i3c_master_transfer_t transfer;          /*!< Copy of the current transfer info. */
    uint8_t ibiAddress;                      /*!< Slave address which request IBI. */
    uint8_t *ibiBuff;                        /*!< Pointer to IBI buffer to keep ibi bytes. */
    size_t ibiPayloadSize;                   /*!< IBI payload size. */
    i3c_ibi_type_t ibiType;                  /*!< IBI type. */
    i3c_master_transfer_callback_t callback; /*!< Callback functions pointer. */
    void *userData;                          /*!< Application data passed to callback. */
};

/*! @brief Typedef for master interrupt handler. */
typedef void (*i3c_master_isr_t)(I3C_Type *base, i3c_master_handle_t *handle);

/*! @} */

/*!
 * @addtogroup i3c_slave_driver
 * @{
 */

/*!
 * @brief I3C slave peripheral flags.
 *
 * The following status register flags can be cleared:
 * - #kI3C_SlaveBusStartFlag
 * - #kI3C_SlaveMatchedFlag
 * - #kI3C_SlaveBusStopFlag
 *
 * Only below flags can be enabled as interrupts.
 * - #kI3C_SlaveBusStartFlag
 * - #kI3C_SlaveMatchedFlag
 * - #kI3C_SlaveBusStopFlag
 * - #kI3C_SlaveRxReadyFlag
 * - #kI3C_SlaveTxReadyFlag
 * - #kI3C_SlaveDynamicAddrChangedFlag
 * - #kI3C_SlaveReceivedCCCFlag
 * - #kI3C_SlaveErrorFlag
 * - #kI3C_SlaveHDRCommandMatchFlag
 * - #kI3C_SlaveCCCHandledFlag
 * - #kI3C_SlaveEventSentFlag

 * @note These enums are meant to be OR'd together to form a bit mask.
 */
enum _i3c_slave_flags
{
    kI3C_SlaveNotStopFlag = I3C_SSTATUS_STNOTSTOP_MASK,     /*!< Slave status not stop flag */
    kI3C_SlaveMessageFlag = I3C_SSTATUS_STMSG_MASK,         /*!< Slave status message, indicating slave is
                                                                     listening to the bus traffic or responding */
    kI3C_SlaveRequiredReadFlag = I3C_SSTATUS_STREQRD_MASK,  /*!< Slave status required, either is master doing SDR
                                                               read from slave, or is IBI pushing out. */
    kI3C_SlaveRequiredWriteFlag = I3C_SSTATUS_STREQWR_MASK, /*!< Slave status request write, master is doing SDR
                                                               write to slave, except slave in ENTDAA mode */
    kI3C_SlaveBusDAAFlag     = I3C_SSTATUS_STDAA_MASK,      /*!< I3C bus is in ENTDAA mode */
    kI3C_SlaveBusHDRModeFlag = I3C_SSTATUS_STHDR_MASK,      /*!< I3C bus is in HDR mode */
    kI3C_SlaveBusStartFlag = I3C_SSTATUS_START_MASK, /*!< Start/Re-start event is seen since the bus was last cleared */
    kI3C_SlaveMatchedFlag  = I3C_SSTATUS_MATCHED_MASK, /*!< Slave address(dynamic/static) matched since last cleared */
    kI3C_SlaveBusStopFlag  = I3C_SSTATUS_STOP_MASK,    /*!<Stop event is seen since the bus was last cleared */
    kI3C_SlaveRxReadyFlag  = I3C_SSTATUS_RX_PEND_MASK, /*!< Rx data ready in rx buffer flag */
    kI3C_SlaveTxReadyFlag  = I3C_SSTATUS_TXNOTFULL_MASK, /*!< Tx buffer ready for Tx data flag */
    kI3C_SlaveDynamicAddrChangedFlag =
        I3C_SSTATUS_DACHG_MASK, /*!< Slave dynamic address has been assigned, re-assigned, or lost */
    kI3C_SlaveReceivedCCCFlag     = I3C_SSTATUS_CCC_MASK,      /*!< Slave received Common command code */
    kI3C_SlaveErrorFlag           = I3C_SSTATUS_ERRWARN_MASK,  /*!< Error occurred flag */
    kI3C_SlaveHDRCommandMatchFlag = I3C_SSTATUS_HDRMATCH_MASK, /*!< High data rate command match */
    kI3C_SlaveCCCHandledFlag =
        I3C_SSTATUS_CHANDLED_MASK, /*!< Slave received Common command code is handled by I3C module */
    kI3C_SlaveEventSentFlag             = I3C_SSTATUS_EVENT_MASK,  /*!< Slave IBI/P2P/MR/HJ event has been sent */
    kI3C_SlaveIbiDisableFlag            = I3C_SSTATUS_IBIDIS_MASK, /*!< Slave in band interrupt is disabled. */
    kI3C_SlaveMasterRequestDisabledFlag = I3C_SSTATUS_MRDIS_MASK,  /*!< Slave master request is disabled. */
    kI3C_SlaveHotJoinDisabledFlag       = I3C_SSTATUS_HJDIS_MASK,  /*!< Slave Hot-Join is disabled. */
    /*! All flags which are cleared by the driver upon starting a transfer. */
    kI3C_SlaveClearFlags = kI3C_SlaveBusStartFlag | kI3C_SlaveMatchedFlag | kI3C_SlaveBusStopFlag,

    kI3C_SlaveAllIrqFlags = kI3C_SlaveBusStartFlag | kI3C_SlaveMatchedFlag | kI3C_SlaveBusStopFlag |
                            kI3C_SlaveRxReadyFlag | kI3C_SlaveTxReadyFlag | kI3C_SlaveDynamicAddrChangedFlag |
                            kI3C_SlaveReceivedCCCFlag | kI3C_SlaveErrorFlag | kI3C_SlaveHDRCommandMatchFlag |
                            kI3C_SlaveCCCHandledFlag | kI3C_SlaveEventSentFlag,

};

/*!
 * @brief I3C slave error flags to indicate the causes.
 *
 * @note These enums are meant to be OR'd together to form a bit mask.
 */
enum _i3c_slave_error_flags
{
    kI3C_SlaveErrorOverrunFlag  = I3C_SERRWARN_ORUN_MASK, /*!< Slave internal from-bus buffer/FIFO overrun. */
    kI3C_SlaveErrorUnderrunFlag = I3C_SERRWARN_URUN_MASK, /*!< Slave internal to-bus buffer/FIFO underrun */
    kI3C_SlaveErrorUnderrunNakFlag =
        I3C_SERRWARN_URUNNACK_MASK, /*!< Slave internal from-bus buffer/FIFO underrun and NACK error */
    kI3C_SlaveErrorTermFlag         = I3C_SERRWARN_TERM_MASK,     /*!< Terminate error from master */
    kI3C_SlaveErrorInvalidStartFlag = I3C_SERRWARN_INVSTART_MASK, /*!< Slave invalid start flag */
    kI3C_SlaveErrorSdrParityFlag    = I3C_SERRWARN_SPAR_MASK,     /*!< SDR parity error */
    kI3C_SlaveErrorHdrParityFlag    = I3C_SERRWARN_HPAR_MASK,     /*!< HDR parity error */
    kI3C_SlaveErrorHdrCRCFlag       = I3C_SERRWARN_HCRC_MASK,     /*!< HDR-DDR CRC error */
    kI3C_SlaveErrorS0S1Flag         = I3C_SERRWARN_S0S1_MASK,     /*!< S0 or S1 error */
    kI3C_SlaveErrorOverreadFlag     = I3C_SERRWARN_OREAD_MASK,    /*!< Over-read error */
    kI3C_SlaveErrorOverwriteFlag    = I3C_SERRWARN_OWRITE_MASK,   /*!< Over-write error */
};

/*! @brief I3C slave.event */
typedef enum _i3c_slave_event
{
    kI3C_SlaveEventNormal     = 0U, /*!< Normal mode. */
    kI3C_SlaveEventIBI        = 1U, /*!< In band interrupt event. */
    kI3C_SlaveEventMasterReq  = 2U, /*!< Master request event. */
    kI3C_SlaveEventHotJoinReq = 3U, /*!< Hot-join event. */
} i3c_slave_event_t;

/*! @brief I3C slave.activity state */
typedef enum _i3c_slave_activity_state
{
    kI3C_SlaveNoLatency    = 0U, /*!< Normal bus operation */
    kI3C_SlaveLatency1Ms   = 1U, /*!< 1ms of latency. */
    kI3C_SlaveLatency100Ms = 2U, /*!< 100ms of latency. */
    kI3C_SlaveLatency10S   = 3U, /*!< 10s latency. */
} i3c_slave_activity_state_t;

/*!
 * @brief Structure with settings to initialize the I3C slave module.
 *
 * This structure holds configuration settings for the I3C peripheral. To initialize this
 * structure to reasonable defaults, call the I3C_SlaveGetDefaultConfig() function and
 * pass a pointer to your configuration structure instance.
 *
 * The configuration structure can be made constant so it resides in flash.
 */
typedef struct _i3c_slave_config
{
    bool enableSlave;      /*!< Whether to enable slave. */
    bool isHotJoin;        /*!< Whether to enable slave hotjoin before enable slave. */
    uint8_t staticAddr;    /*!< Static address. */
    uint16_t vendorID;     /*!< Device vendor ID(manufacture ID). */
    bool enableRandomPart; /*!< Whether to generate random part number, if using random part number,
                                the partNumber variable setting is meaningless. */
    uint32_t partNumber;   /*!< Device part number info */
    uint8_t dcr;           /*!< Device characteristics register information. */
    uint8_t bcr;           /*!< Bus characteristics register information. */
    uint8_t hdrMode;       /*!< Support hdr mode, could be OR logic in enumeration:i3c_hdr_mode_t. */
    bool nakAllRequest;    /*!< Whether to reply NAK to all requests except broadcast CCC. */
    bool ignoreS0S1Error;  /*!< Whether to ignore S0/S1 error in SDR mode. */
    bool offline; /*!< Whether to wait 60 us of bus quiet or HDR request to ensure slave track SDR mode safely. */
    bool matchSlaveStartStop; /*!< Whether to assert start/stop status only the time slave is addressed. */
    uint32_t maxWriteLength;  /*!< Maximum write length. */
    uint32_t maxReadLength;   /*!< Maximum read length. */
} i3c_slave_config_t;

/*!
 * @brief Set of events sent to the callback for non blocking slave transfers.
 *
 * These event enumerations are used for two related purposes. First, a bit mask created by OR'ing together
 * events is passed to I3C_SlaveTransferNonBlocking() in order to specify which events to enable.
 * Then, when the slave callback is invoked, it is passed the current event through its @a transfer
 * parameter.
 *
 * @note These enumerations are meant to be OR'd together to form a bit mask of events.
 */
typedef enum _i3c_slave_transfer_event
{
    kI3C_SlaveAddressMatchEvent = 0x01U,     /*!< Received the slave address after a start or repeated start. */
    kI3C_SlaveTransmitEvent     = 0x02U,     /*!< Callback is requested to provide data to transmit
                                                    (slave-transmitter role). */
    kI3C_SlaveReceiveEvent = 0x04U,          /*!< Callback is requested to provide a buffer in which to place received
                                                     data (slave-receiver role). */
    kI3C_SlaveRequiredTransmitEvent = 0x08U, /*!< Callback is requested to provide a buffer in which to place received
                                               data (slave-receiver role). */
    kI3C_SlaveStartEvent           = 0x10U,  /*!< A start/repeated start was detected. */
    kI3C_SlaveHDRCommandMatchEvent = 0x20U,  /*!< Slave Match HDR Command. */
    kI3C_SlaveCompletionEvent      = 0x40U,  /*!< A stop was detected, completing the transfer. */
    kI3C_SlaveRequestSentEvent     = 0x80U,  /*!< Slave request event sent. */
    kI3C_SlaveReceivedCCCEvent     = 0x100L, /*!< Slave received CCC event, need to handle by application. */

    /*! Bit mask of all available events. */
    kI3C_SlaveAllEvents = kI3C_SlaveAddressMatchEvent | kI3C_SlaveTransmitEvent | kI3C_SlaveReceiveEvent |
                          kI3C_SlaveStartEvent | kI3C_SlaveHDRCommandMatchEvent | kI3C_SlaveCompletionEvent |
                          kI3C_SlaveRequestSentEvent | kI3C_SlaveReceivedCCCEvent,
} i3c_slave_transfer_event_t;

/*! @brief I3C slave transfer structure */
typedef struct _i3c_slave_transfer
{
    uint32_t event;            /*!< Reason the callback is being invoked. */
    uint8_t *txData;           /*!< Transfer buffer */
    size_t txDataSize;         /*!< Transfer size */
    uint8_t *rxData;           /*!< Transfer buffer */
    size_t rxDataSize;         /*!< Transfer size */
    status_t completionStatus; /*!< Success or error code describing how the transfer completed. Only applies for
                                  #kI3C_SlaveCompletionEvent. */
    size_t transferredCount;   /*!< Number of bytes actually transferred since start or last repeated start. */
} i3c_slave_transfer_t;

/* Forward declaration. */
typedef struct _i3c_slave_handle i3c_slave_handle_t;

/*!
 * @brief Slave event callback function pointer type.
 *
 * This callback is used only for the slave non-blocking transfer API. To install a callback,
 * use the I3C_SlaveSetCallback() function after you have created a handle.
 *
 * @param base Base address for the I3C instance on which the event occurred.
 * @param transfer Pointer to transfer descriptor containing values passed to and/or from the callback.
 * @param userData Arbitrary pointer-sized value passed from the application.
 */
typedef void (*i3c_slave_transfer_callback_t)(I3C_Type *base, i3c_slave_transfer_t *transfer, void *userData);

/*!
 * @brief I3C slave handle structure.
 * @note The contents of this structure are private and subject to change.
 */
struct _i3c_slave_handle
{
    i3c_slave_transfer_t transfer;          /*!< I3C slave transfer copy. */
    bool isBusy;                            /*!< Whether transfer is busy. */
    bool wasTransmit;                       /*!< Whether the last transfer was a transmit. */
    uint32_t eventMask;                     /*!< Mask of enabled events. */
    uint32_t transferredCount;              /*!< Count of bytes transferred. */
    i3c_slave_transfer_callback_t callback; /*!< Callback function called at transfer event. */
    void *userData;                         /*!< Callback parameter passed to callback. */
    uint8_t *ibiData;                       /*!< IBI data buffer */
    size_t ibiDataSize;                     /*!< IBI data size */
};

/*! @} */

/*!
 * @addtogroup i3c_common_driver
 * @{
 */

/*!
 * @brief Structure with settings to initialize the I3C module, could both initialize master and slave functionality.
 *
 * This structure holds configuration settings for the I3C peripheral. To initialize this
 * structure to reasonable defaults, call the I3C_GetDefaultConfig() function and
 * pass a pointer to your configuration structure instance.
 *
 * The configuration structure can be made constant so it resides in flash.
 */
typedef struct _i3c_config
{
    i3c_master_enable_t enableMaster; /*!< Enable master mode. */
    bool disableTimeout;              /*!< Whether to disable timeout to prevent the ERRWARN. */
    i3c_master_hkeep_t hKeep;         /*!< High keeper mode setting. */
    bool enableOpenDrainStop;         /*!< Whether to emit open-drain speed STOP. */
    bool enableOpenDrainHigh;         /*!< Enable Open-Drain High to be 1 PPBAUD count for i3c messages, or 1 ODBAUD. */
    i3c_baudrate_hz_t baudRate_Hz;    /*!< Desired baud rate settings. */
    uint8_t masterDynamicAddress;     /*!< Main master dynamic address configuration. */
    uint32_t slowClock_Hz;            /*!< Slow clock frequency for time control. */
    uint32_t maxWriteLength;          /*!< Maximum write length. */
    uint32_t maxReadLength;           /*!< Maximum read length. */
    bool enableSlave;                 /*!< Whether to enable slave. */
    uint8_t staticAddr;               /*!< Static address. */
    uint16_t vendorID;                /*!< Device vendor ID(manufacture ID). */
    bool enableRandomPart;            /*!< Whether to generate random part number, if using random part number,
                                           the partNumber variable setting is meaningless. */
    uint32_t partNumber;              /*!< Device part number info */
    uint8_t dcr;                      /*!< Device characteristics register information. */
    uint8_t bcr;                      /*!< Bus characteristics register information. */
    uint8_t hdrMode;                  /*!< Support hdr mode, could be OR logic in enumeration:i3c_hdr_mode_t. */
    bool nakAllRequest;               /*!< Whether to reply NAK to all requests except broadcast CCC. */
    bool ignoreS0S1Error;             /*!< Whether to ignore S0/S1 error in SDR mode. */
    bool offline; /*!< Whether to wait 60 us of bus quiet or HDR request to ensure slave track SDR mode safely. */
    bool matchSlaveStartStop; /*!< Whether to assert start/stop status only the time slave is addressed. */
} i3c_config_t;

/*! @} */

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! Array to map I3C instance number to IRQ number. */
extern IRQn_Type const kI3cIrqs[];

/*! Pointer to master IRQ handler for each instance. */
extern i3c_master_isr_t s_i3cMasterIsr;

/*! Pointers to master handles for each instance. */
extern void *s_i3cMasterHandle[];

/*! Pointers to slave handles for each instance. */
extern i3c_slave_handle_t *s_i3cSlaveHandle[];

/*******************************************************************************
 * API
 ******************************************************************************/
#
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @addtogroup i3c_common_driver
 * @{
 */
/*!
 * @brief Get which instance current I3C is used.
 * @param base The I3C peripheral base address.
 */
uint32_t I3C_GetInstance(I3C_Type *base);
/*!
 * @brief Provides a default configuration for the I3C peripheral, the configuration covers both master
 * functionality and slave functionality.
 *
 * This function provides the following default configuration for I3C:
 * @code
 *    config->enableMaster                 = kI3C_MasterCapable;
 *    config->disableTimeout               = false;
 *    config->hKeep                        = kI3C_MasterHighKeeperNone;
 *    config->enableOpenDrainStop          = true;
 *    config->enableOpenDrainHigh          = true;
 *    config->baudRate_Hz.i2cBaud          = 400000U;
 *    config->baudRate_Hz.i3cPushPullBaud  = 12500000U;
 *    config->baudRate_Hz.i3cOpenDrainBaud = 2500000U;
 *    config->masterDynamicAddress         = 0x0AU;
 *    config->slowClock_Hz                 = 1000000U;
 *    config->enableSlave                  = true;
 *    config->vendorID                     = 0x11BU;
 *    config->enableRandomPart             = false;
 *    config->partNumber                   = 0;
 *    config->dcr                          = 0;
 *    config->bcr = 0;
 *    config->hdrMode             = (uint8_t)kI3C_HDRModeDDR;
 *    config->nakAllRequest       = false;
 *    config->ignoreS0S1Error     = false;
 *    config->offline             = false;
 *    config->matchSlaveStartStop = false;
 * @endcode
 *
 * After calling this function, you can override any settings in order to customize the configuration,
 * prior to initializing the common I3C driver with I3C_Init().
 *
 * @param[out] config User provided configuration structure for default values. Refer to #i3c_config_t.
 */
void I3C_GetDefaultConfig(i3c_config_t *config);

/*!
 * @brief Initializes the I3C peripheral.
 * This function enables the peripheral clock and initializes the I3C peripheral as described by the user
 * provided configuration. This will initialize both the master peripheral and slave peripheral so that I3C
 * module could work as pure master, pure slave or secondary master, etc.
 * A software reset is performed prior to configuration.
 *
 * @param base The I3C peripheral base address.
 * @param config User provided peripheral configuration. Use I3C_GetDefaultConfig() to get a set of
 * defaults that you can override.
 * @param sourceClock_Hz Frequency in Hertz of the I3C functional clock. Used to calculate the baud rate divisors,
 *      filter widths, and timeout periods.
 */
void I3C_Init(I3C_Type *base, const i3c_config_t *config, uint32_t sourceClock_Hz);

/*! @} */

/*!
 * @addtogroup i3c_master_driver
 * @{
 */

/*! @name Initialization and deinitialization */
/*@{*/

/*!
 * @brief Provides a default configuration for the I3C master peripheral.
 *
 * This function provides the following default configuration for the I3C master peripheral:
 * @code
 *  masterConfig->enableMaster            = kI3C_MasterOn;
 *  masterConfig->disableTimeout          = false;
 *  masterConfig->hKeep                   = kI3C_MasterHighKeeperNone;
 *  masterConfig->enableOpenDrainStop     = true;
 *  masterConfig->enableOpenDrainHigh     = true;
 *  masterConfig->baudRate_Hz             = 100000U;
 *  masterConfig->busType                 = kI3C_TypeI2C;
 * @endcode
 *
 * After calling this function, you can override any settings in order to customize the configuration,
 * prior to initializing the master driver with I3C_MasterInit().
 *
 * @param[out] masterConfig User provided configuration structure for default values. Refer to #i3c_master_config_t.
 */
void I3C_MasterGetDefaultConfig(i3c_master_config_t *masterConfig);

/*!
 * @brief Initializes the I3C master peripheral.
 *
 * This function enables the peripheral clock and initializes the I3C master peripheral as described by the user
 * provided configuration. A software reset is performed prior to configuration.
 *
 * @param base The I3C peripheral base address.
 * @param masterConfig User provided peripheral configuration. Use I3C_MasterGetDefaultConfig() to get a set of
 * defaults that you can override.
 * @param sourceClock_Hz Frequency in Hertz of the I3C functional clock. Used to calculate the baud rate divisors,
 *      filter widths, and timeout periods.
 */
void I3C_MasterInit(I3C_Type *base, const i3c_master_config_t *masterConfig, uint32_t sourceClock_Hz);

/*!
 * @brief Deinitializes the I3C master peripheral.
 *
 * This function disables the I3C master peripheral and gates the clock. It also performs a software
 * reset to restore the peripheral to reset conditions.
 *
 * @param base The I3C peripheral base address.
 */
void I3C_MasterDeinit(I3C_Type *base);

/* Not static so it can be used from fsl_i3c_dma.c. */
status_t I3C_MasterCheckAndClearError(I3C_Type *base, uint32_t status);

/* Not static so it can be used from fsl_i3c_dma.c. */
status_t I3C_CheckForBusyBus(I3C_Type *base);

/*!
 * @brief Set I3C module master mode.
 *
 * @param base The I3C peripheral base address.
 * @param enable Enable master mode.
 */
static inline void I3C_MasterEnable(I3C_Type *base, i3c_master_enable_t enable)
{
    base->MCONFIG = (base->MCONFIG & ~I3C_MCONFIG_MSTENA_MASK) | I3C_MCONFIG_MSTENA(enable);
}

/*@}*/

/*! @name Status */
/*@{*/

/*!
 * @brief Gets the I3C master status flags.
 *
 * A bit mask with the state of all I3C master status flags is returned. For each flag, the corresponding bit
 * in the return value is set if the flag is asserted.
 *
 * @param base The I3C peripheral base address.
 * @return State of the status flags:
 *         - 1: related status flag is set.
 *         - 0: related status flag is not set.
 * @see _i3c_master_flags
 */
static inline uint32_t I3C_MasterGetStatusFlags(I3C_Type *base)
{
    return base->MSTATUS & ~(I3C_MSTATUS_STATE_MASK | I3C_MSTATUS_IBITYPE_MASK);
}

/*!
 * @brief Clears the I3C master status flag state.
 *
 * The following status register flags can be cleared:
 * - #kI3C_MasterSlaveStartFlag
 * - #kI3C_MasterControlDoneFlag
 * - #kI3C_MasterCompleteFlag
 * - #kI3C_MasterArbitrationWonFlag
 * - #kI3C_MasterSlave2MasterFlag
 *
 * Attempts to clear other flags has no effect.
 *
 * @param base The I3C peripheral base address.
 * @param statusMask A bitmask of status flags that are to be cleared. The mask is composed of
 *  #_i3c_master_flags enumerators OR'd together. You may pass the result of a previous call to
 *  I3C_MasterGetStatusFlags().
 * @see _i3c_master_flags.
 */
static inline void I3C_MasterClearStatusFlags(I3C_Type *base, uint32_t statusMask)
{
    base->MSTATUS = statusMask;
}

/*!
 * @brief Gets the I3C master error status flags.
 *
 * A bit mask with the state of all I3C master error status flags is returned. For each flag, the corresponding bit
 * in the return value is set if the flag is asserted.
 *
 * @param base The I3C peripheral base address.
 * @return State of the error status flags:
 *         - 1: related status flag is set.
 *         - 0: related status flag is not set.
 * @see _i3c_master_error_flags
 */
static inline uint32_t I3C_MasterGetErrorStatusFlags(I3C_Type *base)
{
    return base->MERRWARN;
}

/*!
 * @brief Clears the I3C master error status flag state.
 *
 * @param base The I3C peripheral base address.
 * @param statusMask A bitmask of error status flags that are to be cleared. The mask is composed of
 *  #_i3c_master_error_flags enumerators OR'd together. You may pass the result of a previous call to
 *  I3C_MasterGetStatusFlags().
 * @see _i3c_master_error_flags.
 */
static inline void I3C_MasterClearErrorStatusFlags(I3C_Type *base, uint32_t statusMask)
{
    base->MERRWARN = statusMask;
    while ((base->MERRWARN & statusMask) != 0U)
    {
    }
}

/*!
 * @brief Gets the I3C master state.
 *
 * @param base The I3C peripheral base address.
 * @return I3C master state.
 */
i3c_master_state_t I3C_MasterGetState(I3C_Type *base);

/*@}*/

/*! @name Interrupts */
/*@{*/

/*!
 * @brief Enables the I3C master interrupt requests.
 *
 * All flags except #kI3C_MasterBetweenFlag and #kI3C_MasterNackDetectFlag can be enabled as
 * interrupts.
 *
 * @param base The I3C peripheral base address.
 * @param interruptMask Bit mask of interrupts to enable. See #_i3c_master_flags for the set
 *      of constants that should be OR'd together to form the bit mask.
 */
static inline void I3C_MasterEnableInterrupts(I3C_Type *base, uint32_t interruptMask)
{
    base->MINTSET |= interruptMask;
}

/*!
 * @brief Disables the I3C master interrupt requests.
 *
 * All flags except #kI3C_MasterBetweenFlag and #kI3C_MasterNackDetectFlag can be enabled as
 * interrupts.
 *
 * @param base The I3C peripheral base address.
 * @param interruptMask Bit mask of interrupts to disable. See #_i3c_master_flags for the set
 *      of constants that should be OR'd together to form the bit mask.
 */
static inline void I3C_MasterDisableInterrupts(I3C_Type *base, uint32_t interruptMask)
{
    base->MINTCLR = interruptMask;
}

/*!
 * @brief Returns the set of currently enabled I3C master interrupt requests.
 *
 * @param base The I3C peripheral base address.
 * @return A bitmask composed of #_i3c_master_flags enumerators OR'd together to indicate the
 *      set of enabled interrupts.
 */
static inline uint32_t I3C_MasterGetEnabledInterrupts(I3C_Type *base)
{
    return base->MINTSET;
}

/*!
 * @brief Returns the set of pending I3C master interrupt requests.
 *
 * @param base The I3C peripheral base address.
 * @return A bitmask composed of #_i3c_master_flags enumerators OR'd together to indicate the
 *      set of pending interrupts.
 */
static inline uint32_t I3C_MasterGetPendingInterrupts(I3C_Type *base)
{
    return base->MINTMASKED;
}

/*@}*/

/*! @name DMA control */
/*@{*/

/*!
 * @brief Enables or disables I3C master DMA requests.
 *
 * @param base The I3C peripheral base address.
 * @param enableTx Enable flag for transmit DMA request. Pass true for enable, false for disable.
 * @param enableRx Enable flag for receive DMA request. Pass true for enable, false for disable.
 * @param width DMA read/write unit in bytes.
 */
static inline void I3C_MasterEnableDMA(I3C_Type *base, bool enableTx, bool enableRx, uint32_t width)
{
    assert(width <= 2U);
    base->MDMACTRL =
        I3C_MDMACTRL_DMAFB(enableRx ? 2U : 0U) | I3C_MDMACTRL_DMATB(enableTx ? 2U : 0U) | I3C_MDMACTRL_DMAWIDTH(width);
}

/*!
 * @brief Gets I3C master transmit data register address for DMA transfer.
 *
 * @param base The I3C peripheral base address.
 * @param width DMA read/write unit in bytes.
 * @return The I3C Master Transmit Data Register address.
 */
static inline uint32_t I3C_MasterGetTxFifoAddress(I3C_Type *base, uint32_t width)
{
    assert(width <= 2U);
    return (uint32_t)((width == 2U) ? &base->MWDATAH : &base->MWDATAB);
}

/*!
 * @brief Gets I3C master receive data register address for DMA transfer.
 *
 * @param base The I3C peripheral base address.
 * @param width DMA read/write unit in bytes.
 * @return The I3C Master Receive Data Register address.
 */
static inline uint32_t I3C_MasterGetRxFifoAddress(I3C_Type *base, uint32_t width)
{
    assert(width <= 2U);
    return (uint32_t)((width == 2U) ? &base->MRDATAH : &base->MRDATAB);
}

/*@}*/

/*! @name FIFO control */
/*@{*/

/*!
 * @brief Sets the watermarks for I3C master FIFOs.
 *
 * @param base The I3C peripheral base address.
 * @param txLvl Transmit FIFO watermark level. The #kI3C_MasterTxReadyFlag flag is set whenever
 *      the number of words in the transmit FIFO reaches @a txLvl.
 * @param rxLvl Receive FIFO watermark level. The #kI3C_MasterRxReadyFlag flag is set whenever
 *      the number of words in the receive FIFO reaches @a rxLvl.
 * @param flushTx true if TX FIFO is to be cleared, otherwise TX FIFO remains unchanged.
 * @param flushRx true if RX FIFO is to be cleared, otherwise RX FIFO remains unchanged.
 */
static inline void I3C_MasterSetWatermarks(
    I3C_Type *base, i3c_tx_trigger_level_t txLvl, i3c_rx_trigger_level_t rxLvl, bool flushTx, bool flushRx)
{
    base->MDATACTRL = I3C_MDATACTRL_UNLOCK_MASK | I3C_MDATACTRL_TXTRIG(txLvl) | I3C_MDATACTRL_RXTRIG(rxLvl) |
                      (flushTx ? I3C_MDATACTRL_FLUSHTB_MASK : 0U) | (flushRx ? I3C_MDATACTRL_FLUSHFB_MASK : 0U);
}

/*!
 * @brief Gets the current number of bytes in the I3C master FIFOs.
 *
 * @param base The I3C peripheral base address.
 * @param[out] txCount Pointer through which the current number of bytes in the transmit FIFO is returned.
 *      Pass NULL if this value is not required.
 * @param[out] rxCount Pointer through which the current number of bytes in the receive FIFO is returned.
 *      Pass NULL if this value is not required.
 */
static inline void I3C_MasterGetFifoCounts(I3C_Type *base, size_t *rxCount, size_t *txCount)
{
    if (NULL != txCount)
    {
        *txCount = (base->MDATACTRL & I3C_MDATACTRL_TXCOUNT_MASK) >> I3C_MDATACTRL_TXCOUNT_SHIFT;
    }
    if (NULL != rxCount)
    {
        *rxCount = (base->MDATACTRL & I3C_MDATACTRL_RXCOUNT_MASK) >> I3C_MDATACTRL_RXCOUNT_SHIFT;
    }
}

/*@}*/

/*! @name Bus operations */
/*@{*/

/*!
 * @brief Sets the I3C bus frequency for master transactions.
 *
 * The I3C master is automatically disabled and re-enabled as necessary to configure the baud
 * rate. Do not call this function during a transfer, or the transfer is aborted.
 *
 * @param base The I3C peripheral base address.
 * @param baudRate_Hz Pointer to structure of requested bus frequency in Hertz.
 * @param sourceClock_Hz I3C functional clock frequency in Hertz.
 */
void I3C_MasterSetBaudRate(I3C_Type *base, const i3c_baudrate_hz_t *baudRate_Hz, uint32_t sourceClock_Hz);

/*!
 * @brief Returns whether the bus is idle.
 *
 * Requires the master mode to be enabled.
 *
 * @param base The I3C peripheral base address.
 * @retval true Bus is busy.
 * @retval false Bus is idle.
 */
static inline bool I3C_MasterGetBusIdleState(I3C_Type *base)
{
    return ((base->MSTATUS & I3C_MSTATUS_STATE_MASK) == (uint32_t)kI3C_MasterStateIdle ? true : false);
}

/*!
 * @brief Sends a START signal and slave address on the I2C/I3C bus.
 *
 * This function is used to initiate a new master mode transfer. First, the bus state is checked to ensure
 * that another master is not occupying the bus. Then a START signal is transmitted, followed by the
 * 7-bit address specified in the @a address parameter. Note that this function does not actually wait
 * until the START and address are successfully sent on the bus before returning.
 *
 * @param base The I3C peripheral base address.
 * @param type The bus type to use in this transaction.
 * @param address 7-bit slave device address, in bits [6:0].
 * @param dir Master transfer direction, either #kI3C_Read or #kI3C_Write. This parameter is used to set
 *      the R/w bit (bit 0) in the transmitted slave address.
 * @retval #kStatus_Success START signal and address were successfully enqueued in the transmit FIFO.
 * @retval #kStatus_I3C_Busy Another master is currently utilizing the bus.
 */
status_t I3C_MasterStart(I3C_Type *base, i3c_bus_type_t type, uint8_t address, i3c_direction_t dir);

/*!
 * @brief Sends a repeated START signal and slave address on the I2C/I3C bus.
 *
 * This function is used to send a Repeated START signal when a transfer is already in progress. Like
 * I3C_MasterStart(), it also sends the specified 7-bit address.
 *
 * @note This function exists primarily to maintain compatible APIs between I3C and I2C drivers,
 *      as well as to better document the intent of code that uses these APIs.
 *
 * @param base The I3C peripheral base address.
 * @param type The bus type to use in this transaction.
 * @param address 7-bit slave device address, in bits [6:0].
 * @param dir Master transfer direction, either #kI3C_Read or #kI3C_Write. This parameter is used to set
 *      the R/w bit (bit 0) in the transmitted slave address.
 * @retval #kStatus_Success Repeated START signal and address were successfully enqueued in the transmit FIFO.
 */
status_t I3C_MasterRepeatedStart(I3C_Type *base, i3c_bus_type_t type, uint8_t address, i3c_direction_t dir);

/*!
 * @brief Sends a repeated START signal and slave address on the I2C/I3C bus, receive size is also specified
 * in the call.
 *
 * This function is used to send a Repeated START signal when a transfer is already in progress. Like
 * I3C_MasterStart(), it also sends the specified 7-bit address. Call this API also configures the read
 * terminate size for the following read transfer. For example, set the rxSize = 2, the following read transfer
 * will be terminated after two bytes of data received. Write transfer will not be affected by the rxSize
 * configuration.
 *
 * @note This function exists primarily to maintain compatible APIs between I3C and I2C drivers,
 *      as well as to better document the intent of code that uses these APIs.
 *
 * @param base The I3C peripheral base address.
 * @param type The bus type to use in this transaction.
 * @param address 7-bit slave device address, in bits [6:0].
 * @param dir Master transfer direction, either #kI3C_Read or #kI3C_Write. This parameter is used to set
 *      the R/w bit (bit 0) in the transmitted slave address.
 * @param rxSize Read terminate size for the followed read transfer, limit to 255 bytes.
 * @retval #kStatus_Success Repeated START signal and address were successfully enqueued in the transmit FIFO.
 */
status_t I3C_MasterRepeatedStartWithRxSize(
    I3C_Type *base, i3c_bus_type_t type, uint8_t address, i3c_direction_t dir, uint8_t rxSize);

/*!
 * @brief Performs a polling send transfer on the I2C/I3C bus.
 *
 * Sends up to @a txSize number of bytes to the previously addressed slave device. The slave may
 * reply with a NAK to any byte in order to terminate the transfer early. If this happens, this
 * function returns #kStatus_I3C_Nak.
 *
 * @param base  The I3C peripheral base address.
 * @param txBuff The pointer to the data to be transferred.
 * @param txSize The length in bytes of the data to be transferred.
 * @param flags Bit mask of options for the transfer. See enumeration #_i3c_master_transfer_flags for available options.
 * @retval #kStatus_Success Data was sent successfully.
 * @retval #kStatus_I3C_Busy Another master is currently utilizing the bus.
 * @retval #kStatus_I3C_Timeout The module has stalled too long in a frame.
 * @retval #kStatus_I3C_Nak The slave device sent a NAK in response to an address.
 * @retval #kStatus_I3C_WriteAbort The slave device sent a NAK in response to a write.
 * @retval #kStatus_I3C_MsgError Message SDR/DDR mismatch or read/write message in wrong state.
 * @retval #kStatus_I3C_WriteFifoError Write to M/SWDATAB register when FIFO full.
 * @retval #kStatus_I3C_InvalidReq Invalid use of request.
 */
status_t I3C_MasterSend(I3C_Type *base, const void *txBuff, size_t txSize, uint32_t flags);

/*!
 * @brief Performs a polling receive transfer on the I2C/I3C bus.
 *
 * @param base  The I3C peripheral base address.
 * @param rxBuff The pointer to the data to be transferred.
 * @param rxSize The length in bytes of the data to be transferred.
 * @param flags Bit mask of options for the transfer. See enumeration #_i3c_master_transfer_flags for available options.
 * @retval #kStatus_Success Data was received successfully.
 * @retval #kStatus_I3C_Busy Another master is currently utilizing the bus.
 * @retval #kStatus_I3C_Timeout The module has stalled too long in a frame.
 * @retval #kStatus_I3C_Term The master terminates slave read.
 * @retval #kStatus_I3C_HdrParityError Parity error from DDR read.
 * @retval #kStatus_I3C_CrcError CRC error from DDR read.
 * @retval #kStatus_I3C_MsgError Message SDR/DDR mismatch or read/write message in wrong state.
 * @retval #kStatus_I3C_ReadFifoError Read from M/SRDATAB register when FIFO empty.
 * @retval #kStatus_I3C_InvalidReq Invalid use of request.
 */
status_t I3C_MasterReceive(I3C_Type *base, void *rxBuff, size_t rxSize, uint32_t flags);

/*!
 * @brief Sends a STOP signal on the I2C/I3C bus.
 *
 * This function does not return until the STOP signal is seen on the bus, or an error occurs.
 *
 * @param base The I3C peripheral base address.
 * @retval #kStatus_Success The STOP signal was successfully sent on the bus and the transaction terminated.
 * @retval #kStatus_I3C_Busy Another master is currently utilizing the bus.
 * @retval #kStatus_I3C_Timeout The module has stalled too long in a frame.
 * @retval #kStatus_I3C_InvalidReq Invalid use of request.
 */
status_t I3C_MasterStop(I3C_Type *base);

/*!
 * @brief I3C master emit request.
 *
 * @param base The I3C peripheral base address.
 * @param masterReq  I3C master request of type #i3c_bus_request_t
 */
void I3C_MasterEmitRequest(I3C_Type *base, i3c_bus_request_t masterReq);

/*!
 * @brief I3C master emit request.
 *
 * @param base The I3C peripheral base address.
 * @param ibiResponse  I3C master emit IBI response of type #i3c_ibi_response_t
 */
static inline void I3C_MasterEmitIBIResponse(I3C_Type *base, i3c_ibi_response_t ibiResponse)
{
    uint32_t ctrlVal = base->MCTRL;
    ctrlVal &= ~(I3C_MCTRL_IBIRESP_MASK | I3C_MCTRL_REQUEST_MASK);
    ctrlVal |= I3C_MCTRL_IBIRESP((uint32_t)ibiResponse) | I3C_MCTRL_REQUEST(kI3C_RequestIbiAckNack);
    base->MCTRL = ctrlVal;
}

/*!
 * @brief I3C master register IBI rule.
 *
 * @param base The I3C peripheral base address.
 * @param ibiRule Pointer to ibi rule description of type #i3c_register_ibi_addr_t
 */
void I3C_MasterRegisterIBI(I3C_Type *base, i3c_register_ibi_addr_t *ibiRule);

/*!
 * @brief I3C master get IBI rule.
 *
 * @param base The I3C peripheral base address.
 * @param ibiRule Pointer to store the read out ibi rule description.
 */
void I3C_MasterGetIBIRules(I3C_Type *base, i3c_register_ibi_addr_t *ibiRule);

/*!
 * @brief Performs a DAA in the i3c bus
 *
 * @param base The I3C peripheral base address.
 * @param addressList The pointer for address list which is used to do DAA.
 * @param count The address count in the address list.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_I3C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 * @retval #kStatus_I3C_SlaveCountExceed The I3C slave count has exceed the definition in I3C_MAX_DEVCNT.
 */
status_t I3C_MasterProcessDAA(I3C_Type *base, uint8_t *addressList, uint32_t count);

/*!
 * @brief Performs a master polling transfer on the I2C/I3C bus.
 *
 * @note The API does not return until the transfer succeeds or fails due
 * to error happens during transfer.
 *
 * @param base The I3C peripheral base address.
 * @param transfer Pointer to the transfer structure.
 * @retval #kStatus_Success Data was received successfully.
 * @retval #kStatus_I3C_Busy Another master is currently utilizing the bus.
 * @retval #kStatus_I3C_IBIWon The I3C slave event IBI or MR or HJ won the arbitration on a header address.
 * @retval #kStatus_I3C_Timeout The module has stalled too long in a frame.
 * @retval #kStatus_I3C_Nak The slave device sent a NAK in response to an address.
 * @retval #kStatus_I3C_WriteAbort The slave device sent a NAK in response to a write.
 * @retval #kStatus_I3C_Term The master terminates slave read.
 * @retval #kStatus_I3C_HdrParityError Parity error from DDR read.
 * @retval #kStatus_I3C_CrcError CRC error from DDR read.
 * @retval #kStatus_I3C_MsgError Message SDR/DDR mismatch or read/write message in wrong state.
 * @retval #kStatus_I3C_ReadFifoError Read from M/SRDATAB register when FIFO empty.
 * @retval #kStatus_I3C_WriteFifoError Write to M/SWDATAB register when FIFO full.
 * @retval #kStatus_I3C_InvalidReq Invalid use of request.
 */
status_t I3C_MasterTransferBlocking(I3C_Type *base, i3c_master_transfer_t *transfer);

/*@}*/

/*! @name Non-blocking */
/*@{*/

/*!
 * @brief Creates a new handle for the I3C master non-blocking APIs.
 *
 * The creation of a handle is for use with the non-blocking APIs. Once a handle
 * is created, there is not a corresponding destroy handle. If the user wants to
 * terminate a transfer, the I3C_MasterTransferAbort() API shall be called.
 *
 *
 * @note The function also enables the NVIC IRQ for the input I3C. Need to notice
 * that on some SoCs the I3C IRQ is connected to INTMUX, in this case user needs to
 * enable the associated INTMUX IRQ in application.
 *
 * @param base The I3C peripheral base address.
 * @param[out] handle Pointer to the I3C master driver handle.
 * @param callback User provided pointer to the asynchronous callback function.
 * @param userData User provided pointer to the application callback data.
 */
void I3C_MasterTransferCreateHandle(I3C_Type *base,
                                    i3c_master_handle_t *handle,
                                    const i3c_master_transfer_callback_t *callback,
                                    void *userData);

/*!
 * @brief Performs a non-blocking transaction on the I2C/I3C bus.
 *
 * @param base The I3C peripheral base address.
 * @param handle Pointer to the I3C master driver handle.
 * @param transfer The pointer to the transfer descriptor.
 * @retval #kStatus_Success The transaction was started successfully.
 * @retval #kStatus_I3C_Busy Either another master is currently utilizing the bus, or a non-blocking
 *      transaction is already in progress.
 */
status_t I3C_MasterTransferNonBlocking(I3C_Type *base, i3c_master_handle_t *handle, i3c_master_transfer_t *transfer);

/*!
 * @brief Returns number of bytes transferred so far.
 * @param base The I3C peripheral base address.
 * @param handle Pointer to the I3C master driver handle.
 * @param[out] count Number of bytes transferred so far by the non-blocking transaction.
 * @retval #kStatus_Success
 * @retval #kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t I3C_MasterTransferGetCount(I3C_Type *base, i3c_master_handle_t *handle, size_t *count);

/*!
 * @brief Terminates a non-blocking I3C master transmission early.
 *
 * @note It is not safe to call this function from an IRQ handler that has a higher priority than the
 *      I3C peripheral's IRQ priority.
 *
 * @param base The I3C peripheral base address.
 * @param handle Pointer to the I3C master driver handle.
 * @retval #kStatus_Success A transaction was successfully aborted.
 * @retval #kStatus_I3C_Idle There is not a non-blocking transaction currently in progress.
 */
void I3C_MasterTransferAbort(I3C_Type *base, i3c_master_handle_t *handle);

/*@}*/

/*! @name IRQ handler */
/*@{*/

/*!
 * @brief Reusable routine to handle master interrupts.
 * @note This function does not need to be called unless you are reimplementing the
 *  nonblocking API's interrupt handler routines to add special functionality.
 * @param base The I3C peripheral base address.
 * @param handle Pointer to the I3C master driver handle.
 */
void I3C_MasterTransferHandleIRQ(I3C_Type *base, i3c_master_handle_t *handle);

/*@}*/

/*! @} */

/*!
 * @addtogroup i3c_slave_driver
 * @{
 */

/*! @name Initialization and deinitialization */
/*@{*/

/*!
 * @brief Provides a default configuration for the I3C slave peripheral.
 *
 * This function provides the following default configuration for the I3C slave peripheral:
 * @code
 *  slaveConfig->enableslave             = true;
 * @endcode
 *
 * After calling this function, you can override any settings in order to customize the configuration,
 * prior to initializing the slave driver with I3C_SlaveInit().
 *
 * @param[out] slaveConfig User provided configuration structure for default values. Refer to #i3c_slave_config_t.
 */
void I3C_SlaveGetDefaultConfig(i3c_slave_config_t *slaveConfig);

/*!
 * @brief Initializes the I3C slave peripheral.
 *
 * This function enables the peripheral clock and initializes the I3C slave peripheral as described by the user
 * provided configuration.
 *
 * @param base The I3C peripheral base address.
 * @param slaveConfig User provided peripheral configuration. Use I3C_SlaveGetDefaultConfig() to get a set of
 * defaults that you can override.
 * @param slowClock_Hz Frequency in Hertz of the I3C slow clock. Used to calculate the bus match condition values.
 */
void I3C_SlaveInit(I3C_Type *base, const i3c_slave_config_t *slaveConfig, uint32_t slowClock_Hz);

/*!
 * @brief Deinitializes the I3C slave peripheral.
 *
 * This function disables the I3C slave peripheral and gates the clock.
 *
 * @param base The I3C peripheral base address.
 */
void I3C_SlaveDeinit(I3C_Type *base);

/*!
 * @brief Enable/Disable Slave.
 *
 * @param base The I3C peripheral base address.
 * @param isEnable Enable or disable.
 */
static inline void I3C_SlaveEnable(I3C_Type *base, bool isEnable)
{
    base->SCONFIG = (base->SCONFIG & ~I3C_SCONFIG_SLVENA_MASK) | I3C_SCONFIG_SLVENA(isEnable);
}

/*@}*/

/*! @name Status */
/*@{*/

/*!
 * @brief Gets the I3C slave status flags.
 *
 * A bit mask with the state of all I3C slave status flags is returned. For each flag, the corresponding bit
 * in the return value is set if the flag is asserted.
 *
 * @param base The I3C peripheral base address.
 * @return State of the status flags:
 *         - 1: related status flag is set.
 *         - 0: related status flag is not set.
 * @see _i3c_slave_flags
 */
static inline uint32_t I3C_SlaveGetStatusFlags(I3C_Type *base)
{
    return base->SSTATUS & ~(I3C_SSTATUS_EVDET_MASK | I3C_SSTATUS_ACTSTATE_MASK | I3C_SSTATUS_TIMECTRL_MASK);
}

/*!
 * @brief Clears the I3C slave status flag state.
 *
 * The following status register flags can be cleared:
 * - #kI3C_SlaveBusStartFlag
 * - #kI3C_SlaveMatchedFlag
 * - #kI3C_SlaveBusStopFlag
 *
 * Attempts to clear other flags has no effect.
 *
 * @param base The I3C peripheral base address.
 * @param statusMask A bitmask of status flags that are to be cleared. The mask is composed of
 *  #_i3c_slave_flags enumerators OR'd together. You may pass the result of a previous call to
 *  I3C_SlaveGetStatusFlags().
 * @see _i3c_slave_flags.
 */
static inline void I3C_SlaveClearStatusFlags(I3C_Type *base, uint32_t statusMask)
{
    base->SSTATUS = statusMask;
}

/*!
 * @brief Gets the I3C slave error status flags.
 *
 * A bit mask with the state of all I3C slave error status flags is returned. For each flag, the corresponding bit
 * in the return value is set if the flag is asserted.
 *
 * @param base The I3C peripheral base address.
 * @return State of the error status flags:
 *         - 1: related status flag is set.
 *         - 0: related status flag is not set.
 * @see _i3c_slave_error_flags
 */
static inline uint32_t I3C_SlaveGetErrorStatusFlags(I3C_Type *base)
{
    return base->SERRWARN;
}

/*!
 * @brief Clears the I3C slave error status flag state.
 *
 * @param base The I3C peripheral base address.
 * @param statusMask A bitmask of error status flags that are to be cleared. The mask is composed of
 *  #_i3c_slave_error_flags enumerators OR'd together. You may pass the result of a previous call to
 *  I3C_SlaveGetErrorStatusFlags().
 * @see _i3c_slave_error_flags.
 */
static inline void I3C_SlaveClearErrorStatusFlags(I3C_Type *base, uint32_t statusMask)
{
    base->SERRWARN = statusMask;
}

/*!
 * @brief Gets the I3C slave state.
 *
 * @param base The I3C peripheral base address.
 * @return I3C slave activity state, refer #i3c_slave_activity_state_t.
 */
i3c_slave_activity_state_t I3C_SlaveGetActivityState(I3C_Type *base);
/*@}*/

/*! @name Interrupts */
/*@{*/

/*!
 * @brief Enables the I3C slave interrupt requests.
 *
 * Only below flags can be enabled as interrupts.
 * - #kI3C_SlaveBusStartFlag
 * - #kI3C_SlaveMatchedFlag
 * - #kI3C_SlaveBusStopFlag
 * - #kI3C_SlaveRxReadyFlag
 * - #kI3C_SlaveTxReadyFlag
 * - #kI3C_SlaveDynamicAddrChangedFlag
 * - #kI3C_SlaveReceivedCCCFlag
 * - #kI3C_SlaveErrorFlag
 * - #kI3C_SlaveHDRCommandMatchFlag
 * - #kI3C_SlaveCCCHandledFlag
 * - #kI3C_SlaveEventSentFlag
 *
 * @param base The I3C peripheral base address.
 * @param interruptMask Bit mask of interrupts to enable. See #_i3c_slave_flags for the set
 *      of constants that should be OR'd together to form the bit mask.
 */
static inline void I3C_SlaveEnableInterrupts(I3C_Type *base, uint32_t interruptMask)
{
    base->SINTSET |= interruptMask;
}

/*!
 * @brief Disables the I3C slave interrupt requests.
 *
 * Only below flags can be disabled as interrupts.
 * - #kI3C_SlaveBusStartFlag
 * - #kI3C_SlaveMatchedFlag
 * - #kI3C_SlaveBusStopFlag
 * - #kI3C_SlaveRxReadyFlag
 * - #kI3C_SlaveTxReadyFlag
 * - #kI3C_SlaveDynamicAddrChangedFlag
 * - #kI3C_SlaveReceivedCCCFlag
 * - #kI3C_SlaveErrorFlag
 * - #kI3C_SlaveHDRCommandMatchFlag
 * - #kI3C_SlaveCCCHandledFlag
 * - #kI3C_SlaveEventSentFlag
 *
 * @param base The I3C peripheral base address.
 * @param interruptMask Bit mask of interrupts to disable. See #_i3c_slave_flags for the set
 *      of constants that should be OR'd together to form the bit mask.
 */
static inline void I3C_SlaveDisableInterrupts(I3C_Type *base, uint32_t interruptMask)
{
    base->SINTCLR = interruptMask;
}

/*!
 * @brief Returns the set of currently enabled I3C slave interrupt requests.
 *
 * @param base The I3C peripheral base address.
 * @return A bitmask composed of #_i3c_slave_flags enumerators OR'd together to indicate the
 *      set of enabled interrupts.
 */
static inline uint32_t I3C_SlaveGetEnabledInterrupts(I3C_Type *base)
{
    return base->SINTSET;
}

/*!
 * @brief Returns the set of pending I3C slave interrupt requests.
 *
 * @param base The I3C peripheral base address.
 * @return A bitmask composed of #_i3c_slave_flags enumerators OR'd together to indicate the
 *      set of pending interrupts.
 */
static inline uint32_t I3C_SlaveGetPendingInterrupts(I3C_Type *base)
{
    return base->SINTMASKED;
}

/*@}*/

/*! @name DMA control */
/*@{*/

/*!
 * @brief Enables or disables I3C slave DMA requests.
 *
 * @param base The I3C peripheral base address.
 * @param enableTx Enable flag for transmit DMA request. Pass true for enable, false for disable.
 * @param enableRx Enable flag for receive DMA request. Pass true for enable, false for disable.
 * @param width DMA read/write unit in bytes.
 */
static inline void I3C_SlaveEnableDMA(I3C_Type *base, bool enableTx, bool enableRx, uint32_t width)
{
    assert(width <= 2U);
    base->SDMACTRL =
        I3C_SDMACTRL_DMAFB(enableRx ? 2U : 0U) | I3C_SDMACTRL_DMATB(enableTx ? 2U : 0U) | I3C_SDMACTRL_DMAWIDTH(width);
}

/*!
 * @brief Gets I3C slave transmit data register address for DMA transfer.
 *
 * @param base The I3C peripheral base address.
 * @param width DMA read/write unit in bytes.
 * @return The I3C Slave Transmit Data Register address.
 */
static inline uint32_t I3C_SlaveGetTxFifoAddress(I3C_Type *base, uint32_t width)
{
    assert(width <= 2U);
    return (uint32_t)((width == 2U) ? &base->SWDATAH : &base->SWDATAB);
}

/*!
 * @brief Gets I3C slave receive data register address for DMA transfer.
 *
 * @param base The I3C peripheral base address.
 * @param width DMA read/write unit in bytes.
 * @return The I3C Slave Receive Data Register address.
 */
static inline uint32_t I3C_SlaveGetRxFifoAddress(I3C_Type *base, uint32_t width)
{
    assert(width <= 2U);
    return (uint32_t)((width == 2U) ? &base->SRDATAH : &base->SRDATAB);
}

/*@}*/

/*! @name FIFO control */
/*@{*/

/*!
 * @brief Sets the watermarks for I3C slave FIFOs.
 *
 * @param base The I3C peripheral base address.
 * @param txLvl Transmit FIFO watermark level. The #kI3C_SlaveTxReadyFlag flag is set whenever
 *      the number of words in the transmit FIFO reaches @a txLvl.
 * @param rxLvl Receive FIFO watermark level. The #kI3C_SlaveRxReadyFlag flag is set whenever
 *      the number of words in the receive FIFO reaches @a rxLvl.
 * @param flushTx true if TX FIFO is to be cleared, otherwise TX FIFO remains unchanged.
 * @param flushRx true if RX FIFO is to be cleared, otherwise RX FIFO remains unchanged.
 */
static inline void I3C_SlaveSetWatermarks(
    I3C_Type *base, i3c_tx_trigger_level_t txLvl, i3c_rx_trigger_level_t rxLvl, bool flushTx, bool flushRx)
{
    base->SDATACTRL = I3C_SDATACTRL_UNLOCK_MASK | I3C_SDATACTRL_TXTRIG(txLvl) | I3C_SDATACTRL_RXTRIG(rxLvl) |
                      (flushTx ? I3C_SDATACTRL_FLUSHTB_MASK : 0U) | (flushRx ? I3C_SDATACTRL_FLUSHFB_MASK : 0U);
}

/*!
 * @brief Gets the current number of bytes in the I3C slave FIFOs.
 *
 * @param base The I3C peripheral base address.
 * @param[out] txCount Pointer through which the current number of bytes in the transmit FIFO is returned.
 *      Pass NULL if this value is not required.
 * @param[out] rxCount Pointer through which the current number of bytes in the receive FIFO is returned.
 *      Pass NULL if this value is not required.
 */
static inline void I3C_SlaveGetFifoCounts(I3C_Type *base, size_t *rxCount, size_t *txCount)
{
    if (NULL != txCount)
    {
        *txCount = (base->SDATACTRL & I3C_SDATACTRL_TXCOUNT_MASK) >> I3C_SDATACTRL_TXCOUNT_SHIFT;
    }
    if (NULL != rxCount)
    {
        *rxCount = (base->SDATACTRL & I3C_SDATACTRL_RXCOUNT_MASK) >> I3C_SDATACTRL_RXCOUNT_SHIFT;
    }
}

/*@}*/

/*! @name Bus operations */
/*@{*/

/*!
 * @brief I3C slave request event.
 *
 * @param base The I3C peripheral base address.
 * @param event I3C slave event of type #i3c_slave_event_t
 */
void I3C_SlaveRequestEvent(I3C_Type *base, i3c_slave_event_t event);

/*!
 * @brief Performs a polling send transfer on the I3C bus.
 *
 * @param base  The I3C peripheral base address.
 * @param txBuff The pointer to the data to be transferred.
 * @param txSize The length in bytes of the data to be transferred.
 * @return Error or success status returned by API.
 */
status_t I3C_SlaveSend(I3C_Type *base, const void *txBuff, size_t txSize);

/*!
 * @brief Performs a polling receive transfer on the I3C bus.
 *
 * @param base  The I3C peripheral base address.
 * @param rxBuff The pointer to the data to be transferred.
 * @param rxSize The length in bytes of the data to be transferred.
 * @return Error or success status returned by API.
 */
status_t I3C_SlaveReceive(I3C_Type *base, void *rxBuff, size_t rxSize);

/*@}*/

/*! @name Slave non-blocking */
/*@{*/

/*!
 * @brief Creates a new handle for the I3C slave non-blocking APIs.
 *
 * The creation of a handle is for use with the non-blocking APIs. Once a handle
 * is created, there is not a corresponding destroy handle. If the user wants to
 * terminate a transfer, the I3C_SlaveTransferAbort() API shall be called.
 *
 * @note The function also enables the NVIC IRQ for the input I3C. Need to notice
 * that on some SoCs the I3C IRQ is connected to INTMUX, in this case user needs to
 * enable the associated INTMUX IRQ in application.

 * @param base The I3C peripheral base address.
 * @param[out] handle Pointer to the I3C slave driver handle.
 * @param callback User provided pointer to the asynchronous callback function.
 * @param userData User provided pointer to the application callback data.
 */
void I3C_SlaveTransferCreateHandle(I3C_Type *base,
                                   i3c_slave_handle_t *handle,
                                   i3c_slave_transfer_callback_t callback,
                                   void *userData);

/*!
 * @brief Starts accepting slave transfers.
 *
 * Call this API after calling I2C_SlaveInit() and I3C_SlaveTransferCreateHandle() to start processing
 * transactions driven by an I2C master. The slave monitors the I2C bus and pass events to the
 * callback that was passed into the call to I3C_SlaveTransferCreateHandle(). The callback is always invoked
 * from the interrupt context.
 *
 * The set of events received by the callback is customizable. To do so, set the @a eventMask parameter to
 * the OR'd combination of #i3c_slave_transfer_event_t enumerators for the events you wish to receive.
 * The #kI3C_SlaveTransmitEvent and #kI3C_SlaveReceiveEvent events are always enabled and do not need
 * to be included in the mask. Alternatively, you can pass 0 to get a default set of only the transmit and
 * receive events that are always enabled. In addition, the #kI3C_SlaveAllEvents constant is provided as
 * a convenient way to enable all events.
 *
 * @param base The I3C peripheral base address.
 * @param handle Pointer to struct: _i3c_slave_handle structure which stores the transfer state.
 * @param eventMask Bit mask formed by OR'ing together #i3c_slave_transfer_event_t enumerators to specify
 *      which events to send to the callback. Other accepted values are 0 to get a default set of
 *      only the transmit and receive events, and #kI3C_SlaveAllEvents to enable all events.
 *
 * @retval #kStatus_Success Slave transfers were successfully started.
 * @retval #kStatus_I3C_Busy Slave transfers have already been started on this handle.
 */
status_t I3C_SlaveTransferNonBlocking(I3C_Type *base, i3c_slave_handle_t *handle, uint32_t eventMask);

/*!
 * @brief Gets the slave transfer status during a non-blocking transfer.
 * @param base The I3C peripheral base address.
 * @param handle Pointer to i2c_slave_handle_t structure.
 * @param[out] count Pointer to a value to hold the number of bytes transferred. May be NULL if the count is not
 *      required.
 * @retval #kStatus_Success
 * @retval #kStatus_NoTransferInProgress
 */
status_t I3C_SlaveTransferGetCount(I3C_Type *base, i3c_slave_handle_t *handle, size_t *count);

/*!
 * @brief Aborts the slave non-blocking transfers.
 * @note This API could be called at any time to stop slave for handling the bus events.
 * @param base The I3C peripheral base address.
 * @param handle Pointer to struct: _i3c_slave_handle structure which stores the transfer state.
 * @retval #kStatus_Success
 * @retval #kStatus_I3C_Idle
 */
void I3C_SlaveTransferAbort(I3C_Type *base, i3c_slave_handle_t *handle);

/*@}*/

/*! @name Slave IRQ handler */
/*@{*/

/*!
 * @brief Reusable routine to handle slave interrupts.
 * @note This function does not need to be called unless you are reimplementing the
 *  non blocking API's interrupt handler routines to add special functionality.
 * @param base The I3C peripheral base address.
 * @param handle Pointer to struct: _i3c_slave_handle structure which stores the transfer state.
 */
void I3C_SlaveTransferHandleIRQ(I3C_Type *base, i3c_slave_handle_t *handle);

/*!
 * @brief I3C slave request IBI event with payload.
 *
 * @param base The I3C peripheral base address.
 * @param handle Pointer to struct: _i3c_slave_handle structure which stores the transfer state.
 * @param data Pointer to IBI data to be sent in the request.
 * @param dataSize IBI data size.
 */
void I3C_SlaveRequestIBIWithData(I3C_Type *base, i3c_slave_handle_t *handle, uint8_t *data, size_t dataSize);
/*@}*/
/*! @} */
#if defined(__cplusplus)
}
#endif

#endif /* _FSL_I3C_H_ */
