/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _FSL_MCAN_H_
#define _FSL_MCAN_H_

#include "fsl_common.h"

/*!
 * @addtogroup mcan
 * @{
 */

/******************************************************************************
 * Definitions
 *****************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief MCAN driver version 2.0.0. */
#define MCAN_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*! @brief MCAN transfer status. */
enum _mcan_status
{
    kStatus_MCAN_TxBusy = MAKE_STATUS(kStatusGroup_MCAN, 0),            /*!< Tx Buffer is Busy. */
    kStatus_MCAN_TxIdle = MAKE_STATUS(kStatusGroup_MCAN, 1),            /*!< Tx Buffer is Idle. */
    kStatus_MCAN_RxBusy = MAKE_STATUS(kStatusGroup_MCAN, 2),            /*!< Rx Buffer is Busy. */
    kStatus_MCAN_RxIdle = MAKE_STATUS(kStatusGroup_MCAN, 3),            /*!< Rx Buffer is Idle. */
    kStatus_MCAN_RxFifo0New = MAKE_STATUS(kStatusGroup_MCAN, 4),        /*!< New message written to Rx FIFO 0. */
    kStatus_MCAN_RxFifo0Idle = MAKE_STATUS(kStatusGroup_MCAN, 5),       /*!< Rx FIFO 0 is Idle. */
    kStatus_MCAN_RxFifo0Watermark = MAKE_STATUS(kStatusGroup_MCAN, 6),  /*!< Rx FIFO 0 fill level reached watermark. */
    kStatus_MCAN_RxFifo0Full = MAKE_STATUS(kStatusGroup_MCAN, 7),       /*!< Rx FIFO 0 full. */
    kStatus_MCAN_RxFifo0Lost = MAKE_STATUS(kStatusGroup_MCAN, 8),       /*!< Rx FIFO 0 message lost. */
    kStatus_MCAN_RxFifo1New = MAKE_STATUS(kStatusGroup_MCAN, 9),        /*!< New message written to Rx FIFO 1. */
    kStatus_MCAN_RxFifo1Idle = MAKE_STATUS(kStatusGroup_MCAN, 10),      /*!< Rx FIFO 1 is Idle. */
    kStatus_MCAN_RxFifo1Watermark = MAKE_STATUS(kStatusGroup_MCAN, 11), /*!< Rx FIFO 1 fill level reached watermark. */
    kStatus_MCAN_RxFifo1Full = MAKE_STATUS(kStatusGroup_MCAN, 12),      /*!< Rx FIFO 1 full. */
    kStatus_MCAN_RxFifo1Lost = MAKE_STATUS(kStatusGroup_MCAN, 13),      /*!< Rx FIFO 1 message lost. */
    kStatus_MCAN_RxFifo0Busy = MAKE_STATUS(kStatusGroup_MCAN, 14),      /*!< Rx FIFO 0 is busy. */
    kStatus_MCAN_RxFifo1Busy = MAKE_STATUS(kStatusGroup_MCAN, 15),      /*!< Rx FIFO 1 is busy. */
    kStatus_MCAN_ErrorStatus = MAKE_STATUS(kStatusGroup_MCAN, 16),      /*!< MCAN Module Error and Status. */
    kStatus_MCAN_UnHandled = MAKE_STATUS(kStatusGroup_MCAN, 17),        /*!< UnHadled Interrupt asserted. */
};

/*!
 * @brief MCAN status flags.
 *
 * This provides constants for the MCAN status flags for use in the MCAN functions.
 * Note: The CPU read action clears MCAN_ErrorFlag, therefore user need to
 * read MCAN_ErrorFlag and distinguish which error is occur using
 * @ref _mcan_error_flags enumerations.
 */
enum _mcan_flags
{
    kMCAN_AccesstoRsvdFlag = CAN_IR_ARA_MASK,    /*!< CAN Synchronization Status. */
    kMCAN_ProtocolErrDIntFlag = CAN_IR_PED_MASK, /*!< Tx Warning Interrupt Flag. */
    kMCAN_ProtocolErrAIntFlag = CAN_IR_PEA_MASK, /*!< Rx Warning Interrupt Flag. */
    kMCAN_BusOffIntFlag = CAN_IR_BO_MASK,        /*!< Tx Error Warning Status. */
    kMCAN_ErrorWarningIntFlag = CAN_IR_EW_MASK,  /*!< Rx Error Warning Status. */
    kMCAN_ErrorPassiveIntFlag = CAN_IR_EP_MASK,  /*!< Rx Error Warning Status. */
};

/*!
 * @brief MCAN Rx FIFO status flags.
 *
 * The MCAN Rx FIFO Status enumerations are used to determine the status of the
 * Rx FIFO.
 */
enum _mcan_rx_fifo_flags
{
    kMCAN_RxFifo0NewFlag = CAN_IR_RF0N_MASK,       /*!< Rx FIFO 0 new message flag. */
    kMCAN_RxFifo0WatermarkFlag = CAN_IR_RF0W_MASK, /*!< Rx FIFO 0 watermark reached flag. */
    kMCAN_RxFifo0FullFlag = CAN_IR_RF0F_MASK,      /*!< Rx FIFO 0 full flag. */
    kMCAN_RxFifo0LostFlag = CAN_IR_RF0L_MASK,      /*!< Rx FIFO 0 message lost flag. */
    kMCAN_RxFifo1NewFlag = CAN_IR_RF1N_MASK,       /*!< Rx FIFO 0 new message flag. */
    kMCAN_RxFifo1WatermarkFlag = CAN_IR_RF1W_MASK, /*!< Rx FIFO 0 watermark reached flag. */
    kMCAN_RxFifo1FullFlag = CAN_IR_RF1F_MASK,      /*!< Rx FIFO 0 full flag. */
    kMCAN_RxFifo1LostFlag = CAN_IR_RF1L_MASK,      /*!< Rx FIFO 0 message lost flag. */
};

/*!
 * @brief MCAN Tx status flags.
 *
 * The MCAN Tx Status enumerations are used to determine the status of the
 * Tx Buffer/Event FIFO.
 */
enum _mcan_tx_flags
{
    kMCAN_TxTransmitCompleteFlag = CAN_IR_TC_MASK,      /*!< Transmission completed flag. */
    kMCAN_TxTransmitCancelFinishFlag = CAN_IR_TCF_MASK, /*!< Transmission cancellation finished flag. */
    kMCAN_TxEventFifoLostFlag = CAN_IR_TEFL_MASK,       /*!< Tx Event FIFO element lost. */
    kMCAN_TxEventFifoFullFlag = CAN_IR_TEFF_MASK,       /*!< Tx Event FIFO full. */
    kMCAN_TxEventFifoWatermarkFlag = CAN_IR_TEFW_MASK,  /*!< Tx Event FIFO fill level reached watermark. */
    kMCAN_TxEventFifoNewFlag = CAN_IR_TEFN_MASK,        /*!< Tx Handler wrote Tx Event FIFO element flag. */
    kMCAN_TxEventFifoEmptyFlag = CAN_IR_TFE_MASK,       /*!< Tx FIFO empty flag. */
};

/*!
 * @brief MCAN interrupt configuration structure, default settings all disabled.
 *
 * This structure contains the settings for all of the MCAN Module interrupt configurations.
 */
enum _mcan_interrupt_enable
{
    kMCAN_BusOffInterruptEnable = CAN_IE_BOE_MASK,  /*!< Bus Off interrupt. */
    kMCAN_ErrorInterruptEnable = CAN_IE_EPE_MASK,   /*!< Error interrupt. */
    kMCAN_WarningInterruptEnable = CAN_IE_EWE_MASK, /*!< Rx Warning interrupt. */
};

/*! @brief MCAN frame format. */
typedef enum _mcan_frame_idformat
{
    kMCAN_FrameIDStandard = 0x0U, /*!< Standard frame format attribute. */
    kMCAN_FrameIDExtend = 0x1U,   /*!< Extend frame format attribute. */
} mcan_frame_idformat_t;

/*! @brief MCAN frame type. */
typedef enum _mcan_frame_type
{
    kMCAN_FrameTypeData = 0x0U,   /*!< Data frame type attribute. */
    kMCAN_FrameTypeRemote = 0x1U, /*!< Remote frame type attribute. */
} mcan_frame_type_t;

/*! @brief MCAN frame datafield size. */
typedef enum _mcan_bytes_in_datafield
{
    kMCAN_8ByteDatafield = 0x0U,  /*!< 8 byte data field. */
    kMCAN_12ByteDatafield = 0x1U, /*!< 12 byte data field. */
    kMCAN_16ByteDatafield = 0x2U, /*!< 16 byte data field. */
    kMCAN_20ByteDatafield = 0x3U, /*!< 20 byte data field. */
    kMCAN_24ByteDatafield = 0x4U, /*!< 24 byte data field. */
    kMCAN_32ByteDatafield = 0x5U, /*!< 32 byte data field. */
    kMCAN_48ByteDatafield = 0x6U, /*!< 48 byte data field. */
    kMCAN_64ByteDatafield = 0x7U, /*!< 64 byte data field. */
} mcan_bytes_in_datafield_t;

#if defined(__CC_ARM)
#pragma anon_unions
#endif
/*! @brief MCAN Tx Buffer structure. */
typedef struct _mcan_tx_buffer_frame
{
    struct
    {
        uint32_t id : 29; /*!< CAN Frame Identifier. */
        uint32_t rtr : 1; /*!< CAN Frame Type(DATA or REMOTE). */
        uint32_t xtd : 1; /*!< CAN Frame Type(STD or EXT). */
        uint32_t esi : 1; /*!< CAN Frame Error State Indicator. */
    };
    struct
    {
        uint32_t : 16;
        uint32_t dlc : 4; /*!< Data Length Code. */
        uint32_t brs : 1; /*!< Bit Rate Switch. */
        uint32_t fdf : 1; /*!< CAN FD format. */
        uint32_t : 1;     /*!< Reserved. */
        uint32_t efc : 1; /*!< Event FIFO control. */
        uint32_t mm : 8;  /*!< Message Marker. */
    };
    uint8_t *data;
    uint8_t size;
} mcan_tx_buffer_frame_t;

/*! @brief MCAN Rx FIFO/Buffer structure. */
typedef struct _mcan_rx_buffer_frame
{
    struct
    {
        uint32_t id : 29; /*!< CAN Frame Identifier. */
        uint32_t rtr : 1; /*!< CAN Frame Type(DATA or REMOTE). */
        uint32_t xtd : 1; /*!< CAN Frame Type(STD or EXT). */
        uint32_t esi : 1; /*!< CAN Frame Error State Indicator. */
    };
    struct
    {
        uint32_t rxts : 16; /*!< Rx Timestamp. */
        uint32_t dlc : 4;   /*!< Data Length Code. */
        uint32_t brs : 1;   /*!< Bit Rate Switch. */
        uint32_t fdf : 1;   /*!< CAN FD format. */
        uint32_t : 2;       /*!< Reserved. */
        uint32_t fidx : 7;  /*!< Filter Index. */
        uint32_t anmf : 1;  /*!< Accepted Non-matching Frame. */
    };
    uint8_t *data;
    uint8_t size;
} mcan_rx_buffer_frame_t;

/*! @brief MCAN Rx FIFO block number. */
typedef enum _mcan_fifo_type
{
    kMCAN_Fifo0 = 0x0U, /*!< CAN Rx FIFO 0. */
    kMCAN_Fifo1 = 0x1U, /*!< CAN Rx FIFO 1. */
} mcan_fifo_type_t;

/*! @brief MCAN FIFO Operation Mode. */
typedef enum _mcan_fifo_opmode_config
{
    kMCAN_FifoBlocking = 0,  /*!< FIFO blocking mode. */
    kMCAN_FifoOverwrite = 1, /*!< FIFO overwrite mode. */
} mcan_fifo_opmode_config_t;

/*! @brief MCAN Tx FIFO/Queue Mode. */
typedef enum _mcan_txmode_config
{
    kMCAN_txFifo = 0,  /*!< Tx FIFO operation. */
    kMCAN_txQueue = 1, /*!< Tx Queue operation. */
} mcan_txmode_config_t;

/*! @brief MCAN remote frames treatment. */
typedef enum _mcan_remote_frame_config
{
    kMCAN_filterFrame = 0, /*!< Filter remote frames. */
    kMCAN_rejectFrame = 1, /*!< Reject all remote frames. */
} mcan_remote_frame_config_t;

/*! @brief MCAN non-masking frames treatment. */
typedef enum _mcan_nonmasking_frame_config
{
    kMCAN_acceptinFifo0 = 0, /*!< Accept non-masking frames in Rx FIFO 0. */
    kMCAN_acceptinFifo1 = 1, /*!< Accept non-masking frames in Rx FIFO 1. */
    kMCAN_reject0 = 2,       /*!< Reject non-masking frames. */
    kMCAN_reject1 = 3,       /*!< Reject non-masking frames. */
} mcan_nonmasking_frame_config_t;

/*! @brief MCAN Filter Element Configuration. */
typedef enum _mcan_fec_config
{
    kMCAN_disable = 0,       /*!< Disable filter element. */
    kMCAN_storeinFifo0 = 1,  /*!< Store in Rx FIFO 0 if filter matches. */
    kMCAN_storeinFifo1 = 2,  /*!< Store in Rx FIFO 1 if filter matches. */
    kMCAN_reject = 3,        /*!< Reject ID if filter matches. */
    kMCAN_setprio = 4,       /*!< Set priority if filter matches. */
    kMCAN_setpriofifo0 = 5,  /*!< Set priority and store in FIFO 0 if filter matches. */
    kMCAN_setpriofifo1 = 6,  /*!< Set priority and store in FIFO 1 if filter matches. */
    kMCAN_storeinbuffer = 7, /*!< Store into Rx Buffer or as debug message. */
} mcan_fec_config_t;

/*! @brief MCAN Rx FIFO configuration. */
typedef struct _mcan_rx_fifo_config
{
    uint32_t address;                        /*!< FIFOn start address. */
    uint32_t elementSize;                    /*!< FIFOn element number. */
    uint32_t watermark;                      /*!< FIFOn watermark level. */
    mcan_fifo_opmode_config_t opmode;        /*!< FIFOn blocking/overwrite mode. */
    mcan_bytes_in_datafield_t datafieldSize; /*!< Data field size per frame, size>8 is for CANFD. */
} mcan_rx_fifo_config_t;

/*! @brief MCAN Rx Buffer configuration. */
typedef struct _mcan_rx_buffer_config
{
    uint32_t address;                        /*!< Rx Buffer start address. */
    mcan_bytes_in_datafield_t datafieldSize; /*!< Data field size per frame, size>8 is for CANFD. */
} mcan_rx_buffer_config_t;

/*! @brief MCAN Tx Event FIFO configuration. */
typedef struct _mcan_tx_fifo_config
{
    uint32_t address;     /*!< Event fifo start address. */
    uint32_t elementSize; /*!< FIFOn element number. */
    uint32_t watermark;   /*!< FIFOn watermark level. */
} mcan_tx_fifo_config_t;

/*! @brief MCAN Tx Buffer configuration. */
typedef struct _mcan_tx_buffer_config
{
    uint32_t address;                        /*!< Tx Buffers Start Address. */
    uint32_t dedicatedSize;                  /*!< Number of Dedicated Transmit Buffers. */
    uint32_t fqSize;                         /*!< Transmit FIFO/Queue Size. */
    mcan_txmode_config_t mode;               /*!< Tx FIFO/Queue Mode.*/
    mcan_bytes_in_datafield_t datafieldSize; /*!< Data field size per frame, size>8 is for CANFD. */
} mcan_tx_buffer_config_t;

/*! @brief MCAN Filter Type. */
typedef enum _mcan_std_filter_type
{
    kMCAN_range = 0,           /*!< Range filter from SFID1 to SFID2. */
    kMCAN_dual = 1,            /*!< Dual ID filter for SFID1 or SFID2. */
    kMCAN_classic = 2,         /*!< Classic filter: SFID1 = filter, SFID2 = mask. */
    kMCAN_disableORrange2 = 3, /*!< Filter element disabled for standard filter
                                    or Range filter, XIDAM mask not applied for extended filter. */
} mcan_filter_type_t;

/*! @brief MCAN Standard Message ID Filter Element. */
typedef struct _mcan_std_filter_element_config
{
    uint32_t sfid2 : 11;        /*!< Standard Filter ID 2. */
    uint32_t : 5;               /*!< Reserved. */
    uint32_t sfid1 : 11;        /*!< Standard Filter ID 1. */
    mcan_fec_config_t sfec : 3; /*!< Standard Filter Element Configuration. */
    mcan_filter_type_t sft : 2; /*!<  Standard Filter Type/ */
} mcan_std_filter_element_config_t;

/*! @brief MCAN Extended Message ID Filter Element. */
typedef struct _mcan_ext_filter_element_config
{
    uint32_t efid1 : 29;        /*!< Extended Filter ID 1. */
    mcan_fec_config_t efec : 3; /*!< Extended Filter Element Configuration. */
    uint32_t efid2 : 29;        /*!< Extended Filter ID 2. */
    uint32_t : 1;               /*!< Reserved. */
    mcan_filter_type_t eft : 2; /*!< Extended Filter Type. */
} mcan_ext_filter_element_config_t;

/*! @brief MCAN Rx filter configuration. */
typedef struct _mcan_frame_filter_config
{
    uint32_t address;                       /*!< Filter start address. */
    uint32_t listSize;                      /*!< Filter list size. */
    mcan_frame_idformat_t idFormat;         /*!< Frame format. */
    mcan_remote_frame_config_t remFrame;    /*!< Remote frame treatment. */
    mcan_nonmasking_frame_config_t nmFrame; /*!< Non-masking frame treatment. */
} mcan_frame_filter_config_t;

/*! @brief MCAN module configuration structure. */
typedef struct _mcan_config
{
    uint32_t baudRateA;     /*!< Baud rate of Arbitration phase in bps. */
    uint32_t baudRateD;     /*!< Baud rate of Data phase in bps. */
    bool enableCanfdNormal; /*!< Enable or Disable CANFD normal. */
    bool enableCanfdSwitch; /*!< Enable or Disable CANFD with baudrate switch. */
    bool enableLoopBackInt; /*!< Enable or Disable Internal Back. */
    bool enableLoopBackExt; /*!< Enable or Disable External Loop Back. */
    bool enableBusMon;      /*!< Enable or Disable Bus Monitoring Mode. */
} mcan_config_t;

/*! @brief MCAN protocol timing characteristic configuration structure. */
typedef struct _mcan_timing_config
{
    uint16_t preDivider; /*!< Clock Pre-scaler Division Factor. */
    uint8_t rJumpwidth;  /*!< Re-sync Jump Width. */
    uint8_t seg1;        /*!< Data Time Segment 1. */
    uint8_t seg2;        /*!< Data Time Segment 2. */
} mcan_timing_config_t;

/*! @brief MCAN Buffer transfer. */
typedef struct _mcan_buffer_transfer
{
    mcan_tx_buffer_frame_t *frame; /*!< The buffer of CAN Message to be transfer. */
    uint8_t bufferIdx;             /*!< The index of Message buffer used to transfer Message. */
} mcan_buffer_transfer_t;

/*! @brief MCAN Rx FIFO transfer. */
typedef struct _mcan_fifo_transfer
{
    mcan_rx_buffer_frame_t *frame; /*!< The buffer of CAN Message to be received from Rx FIFO. */
} mcan_fifo_transfer_t;

/*! @brief MCAN handle structure definition. */
typedef struct _mcan_handle mcan_handle_t;

/*! @brief MCAN transfer callback function.
 *
 *  The MCAN transfer callback returns a value from the underlying layer.
 *  If the status equals to kStatus_MCAN_ErrorStatus, the result parameter is the Content of
 *  MCAN status register which can be used to get the working status(or error status) of MCAN module.
 *  If the status equals to other MCAN Message Buffer transfer status, the result is the index of
 *  Message Buffer that generate transfer event.
 *  If the status equals to other MCAN Message Buffer transfer status, the result is meaningless and should be
 *  Ignored.
 */
typedef void (*mcan_transfer_callback_t)(
    CAN_Type *base, mcan_handle_t *handle, status_t status, uint32_t result, void *userData);

/*! @brief MCAN handle structure. */
struct _mcan_handle
{
    mcan_transfer_callback_t callback;                   /*!< Callback function. */
    void *userData;                                      /*!< MCAN callback function parameter.*/
    mcan_tx_buffer_frame_t *volatile bufferFrameBuf[64]; /*!< The buffer for received data from Buffers. */
    mcan_rx_buffer_frame_t *volatile rxFifoFrameBuf;     /*!< The buffer for received data from Rx FIFO. */
    volatile uint8_t txbufferIdx;                        /*!< Message Buffer transfer state. */
    volatile uint8_t bufferState[64];                    /*!< Message Buffer transfer state. */
    volatile uint8_t rxFifoState;                        /*!< Rx FIFO transfer state. */
};

/******************************************************************************
 * API
 *****************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initializes an MCAN instance.
 *
 * This function initializes the MCAN module with user-defined settings.
 * This example shows how to set up the mcan_config_t parameters and how
 * to call the MCAN_Init function by passing in these parameters.
 *  @code
 *   mcan_config_t config;
 *   config->baudRateA = 500000U;
 *   config->baudRateD = 500000U;
 *   config->enableCanfdNormal = false;
 *   config->enableCanfdSwitch = false;
 *   config->enableLoopBackInt = false;
 *   config->enableLoopBackExt = false;
 *   config->enableBusMon = false;
 *   MCAN_Init(CANFD0, &config, 8000000UL);
 *   @endcode
 *
 * @param base MCAN peripheral base address.
 * @param config Pointer to the user-defined configuration structure.
 * @param sourceClock_Hz MCAN Protocol Engine clock source frequency in Hz.
 */
void MCAN_Init(CAN_Type *base, const mcan_config_t *config, uint32_t sourceClock_Hz);

/*!
 * @brief Deinitializes an MCAN instance.
 *
 * This function deinitializes the MCAN module.
 *
 * @param base MCAN peripheral base address.
 */
void MCAN_Deinit(CAN_Type *base);

/*!
 * @brief Gets the default configuration structure.
 *
 * This function initializes the MCAN configuration structure to default values. The default
 * values are as follows.
 *   config->baudRateA = 500000U;
 *   config->baudRateD = 500000U;
 *   config->enableCanfdNormal = false;
 *   config->enableCanfdSwitch = false;
 *   config->enableLoopBackInt = false;
 *   config->enableLoopBackExt = false;
 *   config->enableBusMon = false;
 *
 * @param config Pointer to the MCAN configuration structure.
 */
void MCAN_GetDefaultConfig(mcan_config_t *config);

/*!
 * @brief MCAN enters normal mode.
 *
 * After initialization, INIT bit in CCCR register must be cleared to enter
 * normal mode thus synchronizes to the CAN bus and ready for communication.
 *
 * @param base MCAN peripheral base address.
 */
void MCAN_EnterNormalMode(CAN_Type *base);

/*!
 * @name Configuration.
 * @{
 */

/*!
 * @brief Sets the MCAN Message RAM base address.
 *
 * This function sets the Message RAM base address.
 *
 * @param base MCAN peripheral base address.
 * @param value Desired Message RAM base.
 */
static inline void MCAN_SetMsgRAMBase(CAN_Type *base, uint32_t value)
{
    assert((value >= 0x20000000U) && (value <= 0x20027FFFU));

    base->MRBA = CAN_MRBA_BA(value);
}

/*!
 * @brief Gets the MCAN Message RAM base address.
 *
 * This function gets the Message RAM base address.
 *
 * @param base MCAN peripheral base address.
 * @return Message RAM base address.
 */
static inline uint32_t MCAN_GetMsgRAMBase(CAN_Type *base)
{
    return base->MRBA;
}

/*!
 * @brief Sets the MCAN protocol arbitration phase timing characteristic.
 *
 * This function gives user settings to CAN bus timing characteristic.
 * The function is for an experienced user. For less experienced users, call
 * the MCAN_Init() and fill the baud rate field with a desired value.
 * This provides the default arbitration phase timing characteristics.
 *
 * Note that calling MCAN_SetArbitrationTimingConfig() overrides the baud rate
 * set in MCAN_Init().
 *
 * @param base MCAN peripheral base address.
 * @param config Pointer to the timing configuration structure.
 */
void MCAN_SetArbitrationTimingConfig(CAN_Type *base, const mcan_timing_config_t *config);

#if (defined(FSL_FEATURE_CAN_SUPPORT_CANFD) && FSL_FEATURE_CAN_SUPPORT_CANFD)
/*!
 * @brief Sets the MCAN protocol data phase timing characteristic.
 *
 * This function gives user settings to CAN bus timing characteristic.
 * The function is for an experienced user. For less experienced users, call
 * the MCAN_Init() and fill the baud rate field with a desired value.
 * This provides the default data phase timing characteristics.
 *
 * Note that calling MCAN_SetArbitrationTimingConfig() overrides the baud rate
 * set in MCAN_Init().
 *
 * @param base MCAN peripheral base address.
 * @param config Pointer to the timing configuration structure.
 */
void MCAN_SetDataTimingConfig(CAN_Type *base, const mcan_timing_config_t *config);
#endif /* FSL_FEATURE_CAN_SUPPORT_CANFD */

/*!
 * @brief Configures an MCAN receive fifo 0 buffer.
 *
 * This function sets start address, element size, watermark, operation mode
 * and datafield size of the recieve fifo 0.
 *
 * @param base MCAN peripheral base address.
 * @param config The receive fifo 0 configuration structure.
 */
void MCAN_SetRxFifo0Config(CAN_Type *base, const mcan_rx_fifo_config_t *config);

/*!
 * @brief Configures an MCAN receive fifo 1 buffer.
 *
 * This function sets start address, element size, watermark, operation mode
 * and datafield size of the recieve fifo 1.
 *
 * @param base MCAN peripheral base address.
 * @param config The receive fifo 1 configuration structure.
 */
void MCAN_SetRxFifo1Config(CAN_Type *base, const mcan_rx_fifo_config_t *config);

/*!
 * @brief Configures an MCAN receive buffer.
 *
 * This function sets start address and datafield size of the recieve buffer.
 *
 * @param base MCAN peripheral base address.
 * @param config The receive buffer configuration structure.
 */
void MCAN_SetRxBufferConfig(CAN_Type *base, const mcan_rx_buffer_config_t *config);

/*!
 * @brief Configures an MCAN transmit event fifo.
 *
 * This function sets start address, element size, watermark of the transmit event fifo.
 *
 * @param base MCAN peripheral base address.
 * @param config The transmit event fifo configuration structure.
 */
void MCAN_SetTxEventfifoConfig(CAN_Type *base, const mcan_tx_fifo_config_t *config);

/*!
 * @brief Configures an MCAN transmit buffer.
 *
 * This function sets start address, element size, fifo/queue mode and datafield
 * size of the transmit buffer.
 *
 * @param base MCAN peripheral base address.
 * @param config The transmit buffer configuration structure.
 */
void MCAN_SetTxBufferConfig(CAN_Type *base, const mcan_tx_buffer_config_t *config);

/*!
 * @brief Set filter configuration.
 *
 * This function sets remote and non masking frames in global filter configuration,
 * also the start address, list size in standard/extended ID filter configuration.
 *
 * @param base MCAN peripheral base address.
 * @param config The MCAN filter configuration.
 */
void MCAN_SetFilterConfig(CAN_Type *base, const mcan_frame_filter_config_t *config);

/*!
 * @brief Set filter configuration.
 *
 * This function sets remote and non masking frames in global filter configuration,
 * also the start address, list size in standard/extended ID filter configuration.
 *
 * @param base MCAN peripheral base address.
 * @param config The MCAN filter configuration.
 */
void MCAN_SetSTDFilterElement(CAN_Type *base,
                              const mcan_frame_filter_config_t *config,
                              const mcan_std_filter_element_config_t *filter,
                              uint8_t idx);

/*!
 * @brief Set filter configuration.
 *
 * This function sets remote and non masking frames in global filter configuration,
 * also the start address, list size in standard/extended ID filter configuration.
 *
 * @param base MCAN peripheral base address.
 * @param config The MCAN filter configuration.
 */
void MCAN_SetEXTFilterElement(CAN_Type *base,
                              const mcan_frame_filter_config_t *config,
                              const mcan_ext_filter_element_config_t *filter,
                              uint8_t idx);

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the MCAN module interrupt flags.
 *
 * This function gets all MCAN interrupt status flags.
 *
 * @param base MCAN peripheral base address.
 * @param mask The ORed MCAN interrupt mask.
 * @return MCAN status flags which are ORed.
 */
static inline uint32_t MCAN_GetStatusFlag(CAN_Type *base, uint32_t mask)
{
    return (bool)(base->IR & mask);
}

/*!
 * @brief Clears the MCAN module interrupt flags.
 *
 * This function clears MCAN interrupt status flags.
 *
 * @param base MCAN peripheral base address.
 * @param mask The ORed MCAN interrupt mask.
 */
static inline void MCAN_ClearStatusFlag(CAN_Type *base, uint32_t mask)
{
    /* Write 1 to clear status flag. */
    base->IR |= mask;
}

/*!
 * @brief Gets the new data flag of specific Rx Buffer.
 *
 * This function gets new data flag of specific Rx Buffer.
 *
 * @param base MCAN peripheral base address.
 * @param idx Rx Buffer index.
 * @return Rx Buffer new data status flag.
 */
static inline bool MCAN_GetRxBufferStatusFlag(CAN_Type *base, uint8_t idx)
{
    assert(idx <= 63U);

    if (idx <= 31U)
    {
        return (bool)(base->NDAT1 & (1U << idx));
    }
    else
    {
        return (bool)(base->NDAT2 & (1U << (idx - 31U)));
    }
}

/*!
 * @brief Clears the new data flag of specific Rx Buffer.
 *
 * This function clears new data flag of specific Rx Buffer.
 *
 * @param base MCAN peripheral base address.
 * @param idx Rx Buffer index.
 */
static inline void MCAN_ClearRxBufferStatusFlag(CAN_Type *base, uint8_t idx)
{
    assert(idx <= 63U);

    if (idx <= 31U)
    {
        base->NDAT1 &= ~(1U << idx);
    }
    else
    {
        base->NDAT2 &= ~(1U << (idx - 31U));
    }
}

/* @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables MCAN interrupts according to the provided interrupt line and mask.
 *
 * This function enables the MCAN interrupts according to the provided interrupt line and mask.
 * The mask is a logical OR of enumeration members.
 *
 * @param base MCAN peripheral base address.
 * @param line Interrupt line number, 0 or 1.
 * @param mask The interrupts to enable.
 */
static inline void MCAN_EnableInterrupts(CAN_Type *base, uint32_t line, uint32_t mask)
{
    base->ILE |= (1U << line);
    if (0 == line)
    {
        base->ILS &= ~mask;
    }
    else
    {
        base->ILS |= mask;
    }
    base->IE |= mask;
}

/*!
 * @brief Enables MCAN Tx Buffer interrupts according to the provided index.
 *
 * This function enables the MCAN Tx Buffer interrupts.
 *
 * @param base MCAN peripheral base address.
 * @param idx Tx Buffer index.
 */
static inline void MCAN_EnableTransmitBufferInterrupts(CAN_Type *base, uint8_t idx)
{
    base->TXBTIE |= (uint32_t)(1U << idx);
}

/*!
 * @brief Disables MCAN Tx Buffer interrupts according to the provided index.
 *
 * This function disables the MCAN Tx Buffer interrupts.
 *
 * @param base MCAN peripheral base address.
 * @param idx Tx Buffer index.
 */
static inline void MCAN_DisableTransmitBufferInterrupts(CAN_Type *base, uint8_t idx)
{
    base->TXBTIE &= (uint32_t)(~(1U << idx));
}

/*!
 * @brief Disables MCAN interrupts according to the provided mask.
 *
 * This function disables the MCAN interrupts according to the provided mask.
 * The mask is a logical OR of enumeration members.
 *
 * @param base MCAN peripheral base address.
 * @param mask The interrupts to disable.
 */
static inline void MCAN_DisableInterrupts(CAN_Type *base, uint32_t mask)
{
    base->IE &= ~mask;
}

/* @} */

/*!
 * @name Bus Operations
 * @{
 */

/*!
 * @brief Writes an MCAN Message to the Transmit Buffer.
 *
 * This function writes a CAN Message to the specified Transmit Message Buffer
 * and changes the Message Buffer state to start CAN Message transmit. After
 * that the function returns immediately.
 *
 * @param base MCAN peripheral base address.
 * @param idx The MCAN Tx Buffer index.
 * @param txFrame Pointer to CAN message frame to be sent.
 */
status_t MCAN_WriteTxBuffer(CAN_Type *base, uint8_t idx, const mcan_tx_buffer_frame_t *txFrame);

/*!
 * @brief Reads an MCAN Message from Rx FIFO.
 *
 * This function reads a CAN message from the Rx FIFO in the Message RAM.
 *
 * @param base MCAN peripheral base address.
 * @param fifoBlock Rx FIFO block 0 or 1.
 * @param rxFrame Pointer to CAN message frame structure for reception.
 * @retval kStatus_Success - Read Message from Rx FIFO successfully.
 */
status_t MCAN_ReadRxFifo(CAN_Type *base, uint8_t fifoBlock, mcan_rx_buffer_frame_t *rxFrame);

/* @} */

/*!
 * @name Transactional
 * @{
 */

/*!
 * @brief Tx Buffer add request to send message out.
 *
 * This function add sending request to corresponding Tx Buffer.
 *
 * @param base MCAN peripheral base address.
 * @param idx Tx Buffer index.
 */
static inline void MCAN_TransmitAddRequest(CAN_Type *base, uint8_t idx)
{
    base->TXBAR |= (uint32_t)(1U << idx);
}

/*!
 * @brief Tx Buffer cancel sending request.
 *
 * This function clears Tx buffer request pending bit.
 *
 * @param base MCAN peripheral base address.
 * @param idx Tx Buffer index.
 */
static inline void MCAN_TransmitCancelRequest(CAN_Type *base, uint8_t idx)
{
    base->TXBCR |= (uint32_t)(1U << idx);
}

/*!
 * @brief Performs a polling send transaction on the CAN bus.
 *
 * Note that a transfer handle does not need to be created  before calling this API.
 *
 * @param base MCAN peripheral base pointer.
 * @param idx The MCAN buffer index.
 * @param txFrame Pointer to CAN message frame to be sent.
 * @retval kStatus_Success - Write Tx Message Buffer Successfully.
 * @retval kStatus_Fail    - Tx Message Buffer is currently in use.
 */
status_t MCAN_TransferSendBlocking(CAN_Type *base, uint8_t idx, mcan_tx_buffer_frame_t *txFrame);

/*!
 * @brief Performs a polling receive transaction from Rx FIFO on the CAN bus.
 *
 * Note that a transfer handle does not need to be created before calling this API.
 *
 * @param base MCAN peripheral base pointer.
 * @param fifoBlock Rx FIFO block, 0 or 1.
 * @param rxFrame Pointer to CAN message frame structure for reception.
 * @retval kStatus_Success - Read Message from Rx FIFO successfully.
 * @retval kStatus_Fail    - No new message in Rx FIFO.
 */
status_t MCAN_TransferReceiveFifoBlocking(CAN_Type *base, uint8_t fifoBlock, mcan_rx_buffer_frame_t *rxFrame);

/*!
 * @brief Initializes the MCAN handle.
 *
 * This function initializes the MCAN handle, which can be used for other MCAN
 * transactional APIs. Usually, for a specified MCAN instance,
 * call this API once to get the initialized handle.
 *
 * @param base MCAN peripheral base address.
 * @param handle MCAN handle pointer.
 * @param callback The callback function.
 * @param userData The parameter of the callback function.
 */
void MCAN_TransferCreateHandle(CAN_Type *base,
                               mcan_handle_t *handle,
                               mcan_transfer_callback_t callback,
                               void *userData);

/*!
 * @brief Sends a message using IRQ.
 *
 * This function sends a message using IRQ. This is a non-blocking function, which returns
 * right away. When messages have been sent out, the send callback function is called.
 *
 * @param base MCAN peripheral base address.
 * @param handle MCAN handle pointer.
 * @param xfer MCAN Buffer transfer structure. See the #mcan_buffer_transfer_t.
 * @retval kStatus_Success        Start Tx Buffer sending process successfully.
 * @retval kStatus_Fail           Write Tx Buffer failed.
 * @retval kStatus_MCAN_TxBusy Tx Buffer is in use.
 */
status_t MCAN_TransferSendNonBlocking(CAN_Type *base, mcan_handle_t *handle, mcan_buffer_transfer_t *xfer);

/*!
 * @brief Receives a message from Rx FIFO using IRQ.
 *
 * This function receives a message using IRQ. This is a non-blocking function, which returns
 * right away. When all messages have been received, the receive callback function is called.
 *
 * @param base MCAN peripheral base address.
 * @param handle MCAN handle pointer.
 * @param fifoBlock Rx FIFO block, 0 or 1.
 * @param xfer MCAN Rx FIFO transfer structure. See the @ref mcan_fifo_transfer_t.
 * @retval kStatus_Success            - Start Rx FIFO receiving process successfully.
 * @retval kStatus_MCAN_RxFifo0Busy - Rx FIFO 0 is currently in use.
 * @retval kStatus_MCAN_RxFifo1Busy - Rx FIFO 1 is currently in use.
 */
status_t MCAN_TransferReceiveFifoNonBlocking(CAN_Type *base,
                                             uint8_t fifoBlock,
                                             mcan_handle_t *handle,
                                             mcan_fifo_transfer_t *xfer);

/*!
 * @brief Aborts the interrupt driven message send process.
 *
 * This function aborts the interrupt driven message send process.
 *
 * @param base MCAN peripheral base address.
 * @param handle MCAN handle pointer.
 * @param bufferIdx The MCAN Buffer index.
 */
void MCAN_TransferAbortSend(CAN_Type *base, mcan_handle_t *handle, uint8_t bufferIdx);

/*!
 * @brief Aborts the interrupt driven message receive from Rx FIFO process.
 *
 * This function aborts the interrupt driven message receive from Rx FIFO process.
 *
 * @param base MCAN peripheral base address.
 * @param fifoBlock MCAN Fifo block, 0 or 1.
 * @param handle MCAN handle pointer.
 */
void MCAN_TransferAbortReceiveFifo(CAN_Type *base, uint8_t fifoBlock, mcan_handle_t *handle);

/*!
 * @brief MCAN IRQ handle function.
 *
 * This function handles the MCAN Error, the Buffer, and the Rx FIFO IRQ request.
 *
 * @param base MCAN peripheral base address.
 * @param handle MCAN handle pointer.
 */
void MCAN_TransferHandleIRQ(CAN_Type *base, mcan_handle_t *handle);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_MCAN_H_ */
