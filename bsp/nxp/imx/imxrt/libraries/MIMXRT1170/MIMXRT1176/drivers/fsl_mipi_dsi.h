/*
 * Copyright 2020-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_MIPI_DSI_H_
#define _FSL_MIPI_DSI_H_

#include "fsl_common.h"

/*!
 * @addtogroup mipi_dsi
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_MIPI_DSI_DRIVER_VERSION (MAKE_VERSION(2, 2, 2))
/*@}*/

/* The max APB transfer size. */
#define FSL_DSI_TX_MAX_PAYLOAD_BYTE (64U * 4U)
#define FSL_DSI_RX_MAX_PAYLOAD_BYTE (64U * 4U)

/*! @brief MIPI DSI structure definition. */
typedef struct
{
    DSI_HOST_Type *host;                        /*!< Pointer to HOST registers. */
    DSI_HOST_APB_PKT_IF_Type *apb;              /*!< Pointer to APB registers. */
    DSI_HOST_DPI_INTFC_Type *dpi;               /*!< Pointer to DPI registers. */
    DSI_HOST_NXP_FDSOI28_DPHY_INTFC_Type *dphy; /*!< Pointer to DPHY registers. */
} MIPI_DSI_Type;

/*! @brief Error codes for the MIPI DSI driver. */
enum
{
    kStatus_DSI_Busy                = MAKE_STATUS(kStatusGroup_MIPI_DSI, 0), /*!< DSI is busy. */
    kStatus_DSI_RxDataError         = MAKE_STATUS(kStatusGroup_MIPI_DSI, 1), /*!< Read data error. */
    kStatus_DSI_ErrorReportReceived = MAKE_STATUS(kStatusGroup_MIPI_DSI, 2), /*!< Error report package received. */
    kStatus_DSI_NotSupported        = MAKE_STATUS(kStatusGroup_MIPI_DSI, 3), /*!< The transfer type not supported. */
};

/*! @brief MIPI DSI controller configuration. */
typedef struct _dsi_config
{
    uint8_t numLanes;              /*!< Number of lanes. */
    bool enableNonContinuousHsClk; /*!< In enabled, the high speed clock will enter
                                       low power mode between transmissions. */
    bool enableTxUlps;             /*!< Enable the TX ULPS. */
    bool autoInsertEoTp;           /*!< Insert an EoTp short package when switching from HS to LP. */
    uint8_t numExtraEoTp;          /*!< How many extra EoTp to send after the end of a packet. */
    uint32_t htxTo_ByteClk;        /*!< HS TX timeout count (HTX_TO) in byte clock. */
    uint32_t lrxHostTo_ByteClk;    /*!< LP RX host timeout count (LRX-H_TO) in byte clock. */
    uint32_t btaTo_ByteClk;        /*!< Bus turn around timeout count (TA_TO) in byte clock. */
} dsi_config_t;

/*! @brief MIPI DPI interface color coding. */
typedef enum _dsi_dpi_color_coding
{
    kDSI_Dpi16BitConfig1 = 0U, /*!< 16-bit configuration 1. RGB565: XXXXXXXX_RRRRRGGG_GGGBBBBB. */
    kDSI_Dpi16BitConfig2 = 1U, /*!< 16-bit configuration 2. RGB565: XXXRRRRR_XXGGGGGG_XXXBBBBB. */
    kDSI_Dpi16BitConfig3 = 2U, /*!< 16-bit configuration 3. RGB565: XXRRRRRX_XXGGGGGG_XXBBBBBX. */
    kDSI_Dpi18BitConfig1 = 3U, /*!< 18-bit configuration 1. RGB666: XXXXXXRR_RRRRGGGG_GGBBBBBB. */
    kDSI_Dpi18BitConfig2 = 4U, /*!< 18-bit configuration 2. RGB666: XXRRRRRR_XXGGGGGG_XXBBBBBB. */
    kDSI_Dpi24Bit        = 5U, /*!< 24-bit. */
} dsi_dpi_color_coding_t;

/*! @brief MIPI DSI pixel packet type send through DPI interface. */
typedef enum _dsi_dpi_pixel_packet
{
    kDSI_PixelPacket16Bit        = 0U, /*!< 16 bit RGB565. */
    kDSI_PixelPacket18Bit        = 1U, /*!< 18 bit RGB666 packed. */
    kDSI_PixelPacket18BitLoosely = 2U, /*!< 18 bit RGB666 loosely packed into three bytes. */
    kDSI_PixelPacket24Bit        = 3U, /*!< 24 bit RGB888, each pixel uses three bytes. */
} dsi_dpi_pixel_packet_t;

/*! @brief _dsi_dpi_polarity_flag DPI signal polarity. */
enum
{
    kDSI_DpiVsyncActiveLow  = 0U,         /*!< VSYNC active low. */
    kDSI_DpiHsyncActiveLow  = 0U,         /*!< HSYNC active low. */
    kDSI_DpiVsyncActiveHigh = (1U << 0U), /*!< VSYNC active high. */
    kDSI_DpiHsyncActiveHigh = (1U << 1U), /*!< HSYNC active high. */
};

/*! @brief DPI video mode. */
typedef enum _dsi_dpi_video_mode
{
    kDSI_DpiNonBurstWithSyncPulse = 0U, /*!< Non-Burst mode with Sync Pulses. */
    kDSI_DpiNonBurstWithSyncEvent = 1U, /*!< Non-Burst mode with Sync Events. */
    kDSI_DpiBurst                 = 2U, /*!< Burst mode. */
} dsi_dpi_video_mode_t;

/*! @brief Behavior in BLLP (Blanking or Low-Power Interval). */
typedef enum _dsi_dpi_bllp_mode
{
    kDSI_DpiBllpLowPower, /*!< LP mode used in BLLP periods. */
    kDSI_DpiBllpBlanking, /*!< Blanking packets used in BLLP periods. */
    kDSI_DpiBllpNull,     /*!< Null packets used in BLLP periods. */
} dsi_dpi_bllp_mode_t;

/*! @brief MIPI DSI controller DPI interface configuration. */
typedef struct _dsi_dpi_config
{
    uint16_t pixelPayloadSize;             /*!< Maximum number of pixels that should be sent
                                              as one DSI packet. Recommended that the line size
                                              (in pixels) is evenly divisible by this parameter. */
    dsi_dpi_color_coding_t dpiColorCoding; /*!< DPI color coding. */
    dsi_dpi_pixel_packet_t pixelPacket;    /*!< Pixel packet format. */

    dsi_dpi_video_mode_t videoMode; /*!< Video mode. */
    dsi_dpi_bllp_mode_t bllpMode;   /*!< Behavior in BLLP. */

    uint8_t polarityFlags; /*!< OR'ed value of _dsi_dpi_polarity_flag controls signal polarity. */
    uint16_t hfp;          /*!< Horizontal front porch, in dpi pixel clock. */
    uint16_t hbp;          /*!< Horizontal back porch, in dpi pixel clock. */
    uint16_t hsw;          /*!< Horizontal sync width, in dpi pixel clock. */
    uint8_t vfp;           /*!< Number of lines in vertical front porch. */
    uint8_t vbp;           /*!< Number of lines in vertical back porch. */
    uint16_t panelHeight;  /*!< Line number in vertical active area. */

    uint8_t virtualChannel; /*!< Virtual channel. */
} dsi_dpi_config_t;

/*! @brief MIPI DSI D-PHY configuration. */
typedef struct _dsi_dphy_config
{
    uint32_t txHsBitClk_Hz; /*!< The generated HS TX bit clock in Hz. */

    uint8_t tClkPre_ByteClk;        /*!< TLPX + TCLK-PREPARE + TCLK-ZERO + TCLK-PRE in byte clock.
                                         Set how long the controller
                                         will wait after enabling clock lane for HS before
                                         enabling data lanes for HS. */
    uint8_t tClkPost_ByteClk;       /*!< TCLK-POST + T_CLK-TRAIL in byte clock. Set how long the controller
                                        will wait before putting clock lane into LP mode after
                                        data lanes detected in stop state. */
    uint8_t tHsExit_ByteClk;        /*!< THS-EXIT in byte clock. Set how long the controller
                                          will wait after the clock lane has been put into LP
                                          mode before enabling clock lane for HS again. */
    uint32_t tWakeup_EscClk;        /*!< Number of clk_esc clock periods to keep a clock
                                         or data lane in Mark-1 state after exiting ULPS. */
    uint8_t tHsPrepare_HalfEscClk;  /*!< THS-PREPARE in clk_esc/2. Set how long
                                      to drive the LP-00 state before HS transmissions,
                                      available values are 2, 3, 4, 5. */
    uint8_t tClkPrepare_HalfEscClk; /*!< TCLK-PREPARE in clk_esc/2. Set how long
                                     to drive the LP-00 state before HS transmissions,
                                     available values are 2, 3. */
    uint8_t tHsZero_ByteClk;        /*!< THS-ZERO in clk_byte. Set how long that controller
                                      drives data lane HS-0 state before transmit
                                      the Sync sequence. Available values are 6, 7, ..., 37. */
    uint8_t tClkZero_ByteClk;       /*!< TCLK-ZERO in clk_byte. Set how long that controller
                                      drives clock lane HS-0 state before transmit
                                      the Sync sequence. Available values are 3, 4, ..., 66. */
    uint8_t tHsTrail_ByteClk;       /*!< THS-TRAIL + 4*UI in clk_byte. Set the time
                                       of the flipped differential state after last payload
                                       data bit of HS transmission burst. Available values
                                       are 0, 1, ..., 15. */
    uint8_t tClkTrail_ByteClk;      /*!< TCLK-TRAIL + 4*UI in clk_byte. Set the time
                                       of the flipped differential state after last payload
                                       data bit of HS transmission burst. Available values
                                       are 0, 1, ..., 15. */
} dsi_dphy_config_t;

/*! @brief _dsi_apb_status Status of APB to packet interface. */
enum
{
    kDSI_ApbNotIdle          = (1U << 0U), /*!< State machine not idle */
    kDSI_ApbTxDone           = (1U << 1U), /*!< Tx packet done */
    kDSI_ApbRxControl        = (1U << 2U), /*!< DPHY direction 0 - tx had control, 1 - rx has control */
    kDSI_ApbTxOverflow       = (1U << 3U), /*!< TX fifo overflow */
    kDSI_ApbTxUnderflow      = (1U << 4U), /*!< TX fifo underflow */
    kDSI_ApbRxOverflow       = (1U << 5U), /*!< RX fifo overflow */
    kDSI_ApbRxUnderflow      = (1U << 6U), /*!< RX fifo underflow */
    kDSI_ApbRxHeaderReceived = (1U << 7U), /*!< RX packet header has been received */
    kDSI_ApbRxPacketReceived = (1U << 8U), /*!< All RX packet payload data has been received */
};

/*! @brief _dsi_rx_error_status Host receive error status. */
enum
{
    kDSI_RxErrorEccOneBit   = (1U << 0U), /*!< ECC single bit error detected. */
    kDSI_RxErrorEccMultiBit = (1U << 1U), /*!< ECC multi bit error detected. */
    kDSI_RxErrorCrc         = (1U << 7U), /*!< CRC error detected. */
    kDSI_RxErrorHtxTo       = (1U << 8U), /*!< High Speed forward TX timeout detected. */
    kDSI_RxErrorLrxTo       = (1U << 9U), /*!< Reverse Low power data receive timeout detected. */
    kDSI_RxErrorBtaTo       = (1U << 10U) /*!< BTA timeout detected. */
};

/*! @brief DSI host controller status (status_out) */
enum _dsi_host_status
{
    kDSI_HostSoTError           = (1U << 0U),  /*!< SoT error from peripheral error report. */
    kDSI_HostSoTSyncError       = (1U << 1U),  /*!< SoT Sync error from peripheral error report. */
    kDSI_HostEoTSyncError       = (1U << 2U),  /*!< EoT Sync error from peripheral error report. */
    kDSI_HostEscEntryCmdError   = (1U << 3U),  /*!< Escape Mode Entry Command Error from peripheral error report. */
    kDSI_HostLpTxSyncError      = (1U << 4U),  /*!< Low-power transmit Sync Error from peripheral error report. */
    kDSI_HostPeriphToError      = (1U << 5U),  /*!< Peripheral timeout error from peripheral error report. */
    kDSI_HostFalseControlError  = (1U << 6U),  /*!< False control error from peripheral error report. */
    kDSI_HostContentionDetected = (1U << 7U),  /*!< Contention detected from peripheral error report. */
    kDSI_HostEccErrorOneBit     = (1U << 8U),  /*!< Single bit ECC error (corrected) from peripheral error report. */
    kDSI_HostEccErrorMultiBit   = (1U << 9U),  /*!< Multi bit ECC error (not corrected) from peripheral error report. */
    kDSI_HostChecksumError      = (1U << 10U), /*!< Checksum error from peripheral error report. */
    kDSI_HostInvalidDataType    = (1U << 11U), /*!< DSI data type not recognized. */
    kDSI_HostInvalidVcId        = (1U << 12U), /*!< DSI VC ID invalid. */
    kDSI_HostInvalidTxLength    = (1U << 13U), /*!< Invalid transmission length. */
    kDSI_HostProtocalViolation  = (1U << 15U), /*!< DSI protocal violation. */
    kDSI_HostResetTriggerReceived = (1U << 16U), /*!< Reset trigger received. */
    kDSI_HostTearTriggerReceived  = (1U << 17U), /*!< Tear effect trigger receive. */
    kDSI_HostAckTriggerReceived   = (1U << 18U), /*!< Acknowledge trigger message received. */
};

/*! @brief _dsi_interrupt DSI interrupt. */
enum
{
    kDSI_InterruptGroup1ApbNotIdle          = (1U << 0U),   /*!< State machine not idle */
    kDSI_InterruptGroup1ApbTxDone           = (1U << 1U),   /*!< Tx packet done */
    kDSI_InterruptGroup1ApbRxControl        = (1U << 2U),   /*!< DPHY direction 0 - tx control, 1 - rx control */
    kDSI_InterruptGroup1ApbTxOverflow       = (1U << 3U),   /*!< TX fifo overflow */
    kDSI_InterruptGroup1ApbTxUnderflow      = (1U << 4U),   /*!< TX fifo underflow */
    kDSI_InterruptGroup1ApbRxOverflow       = (1U << 5U),   /*!< RX fifo overflow */
    kDSI_InterruptGroup1ApbRxUnderflow      = (1U << 6U),   /*!< RX fifo underflow */
    kDSI_InterruptGroup1ApbRxHeaderReceived = (1U << 7U),   /*!< RX packet header has been received */
    kDSI_InterruptGroup1ApbRxPacketReceived = (1U << 8U),   /*!< All RX packet payload data has been received */
    kDSI_InterruptGroup1SoTError            = (1U << 9U),   /*!< SoT error from peripheral error report. */
    kDSI_InterruptGroup1SoTSyncError        = (1U << 10U),  /*!< SoT Sync error from peripheral error report. */
    kDSI_InterruptGroup1EoTSyncError        = (1U << 11U),  /*!< EoT Sync error from peripheral error report. */
    kDSI_InterruptGroup1EscEntryCmdError    = (1U << 12U),  /*!< Escape Mode Entry Command Error
                                                                   from peripheral error report. */
    kDSI_InterruptGroup1LpTxSyncError = (1U << 13U),        /*!< Low-power transmit Sync Error from
                                                                   peripheral error report. */
    kDSI_InterruptGroup1PeriphToError = (1U << 14U),        /*!< Peripheral timeout error from
                                                                   peripheral error report. */
    kDSI_InterruptGroup1FalseControlError  = (1U << 15U),   /*!< False control error from peripheral error report. */
    kDSI_InterruptGroup1ContentionDetected = (1U << 16U),   /*!< Contention detected from peripheral error report. */
    kDSI_InterruptGroup1EccErrorOneBit     = (1U << 17U),   /*!< Single bit ECC error (corrected) from
                                                                   peripheral error report. */
    kDSI_InterruptGroup1EccErrorMultiBit = (1U << 18U),     /*!< Multi bit ECC error (not corrected) from
                                                               peripheral error report. */
    kDSI_InterruptGroup1ChecksumError        = (1U << 19U), /*!< Checksum error from peripheral error report. */
    kDSI_InterruptGroup1InvalidDataType      = (1U << 20U), /*!< DSI data type not recognized. */
    kDSI_InterruptGroup1InvalidVcId          = (1U << 21U), /*!< DSI VC ID invalid. */
    kDSI_InterruptGroup1InvalidTxLength      = (1U << 22U), /*!< Invalid transmission length. */
    kDSI_InterruptGroup1ProtocalViolation    = (1U << 24U), /*!< DSI protocal violation. */
    kDSI_InterruptGroup1ResetTriggerReceived = (1U << 25U), /*!< Reset trigger received. */
    kDSI_InterruptGroup1TearTriggerReceived  = (1U << 26U), /*!< Tear effect trigger receive. */
    kDSI_InterruptGroup1AckTriggerReceived   = (1U << 27U), /*!< Acknowledge trigger message received. */
    kDSI_InterruptGroup1HtxTo                = (1U << 29U), /*!< High speed TX timeout. */
    kDSI_InterruptGroup1LrxTo                = (1U << 30U), /*!< Low power RX timeout. */
    kDSI_InterruptGroup1BtaTo                = (1U << 31U), /*!< Host BTA timeout. */
    kDSI_InterruptGroup2EccOneBit            = (1U << 0U),  /*!< Sinle bit ECC error. */
    kDSI_InterruptGroup2EccMultiBit          = (1U << 1U),  /*!< Multi bit ECC error. */
    kDSI_InterruptGroup2CrcError             = (1U << 2U),  /*!< CRC error. */
};

/*! @brief DSI TX data type. */
typedef enum _dsi_tx_data_type
{
    kDSI_TxDataVsyncStart          = 0x01U, /*!< V Sync start. */
    kDSI_TxDataVsyncEnd            = 0x11U, /*!< V Sync end. */
    kDSI_TxDataHsyncStart          = 0x21U, /*!< H Sync start. */
    kDSI_TxDataHsyncEnd            = 0x31U, /*!< H Sync end. */
    kDSI_TxDataEoTp                = 0x08U, /*!< End of transmission packet. */
    kDSI_TxDataCmOff               = 0x02U, /*!< Color mode off. */
    kDSI_TxDataCmOn                = 0x12U, /*!< Color mode on. */
    kDSI_TxDataShutDownPeriph      = 0x22U, /*!< Shut down peripheral. */
    kDSI_TxDataTurnOnPeriph        = 0x32U, /*!< Turn on peripheral. */
    kDSI_TxDataGenShortWrNoParam   = 0x03U, /*!< Generic Short WRITE, no parameters. */
    kDSI_TxDataGenShortWrOneParam  = 0x13U, /*!< Generic Short WRITE, one parameter. */
    kDSI_TxDataGenShortWrTwoParam  = 0x23U, /*!< Generic Short WRITE, two parameter. */
    kDSI_TxDataGenShortRdNoParam   = 0x04U, /*!< Generic Short READ, no parameters. */
    kDSI_TxDataGenShortRdOneParam  = 0x14U, /*!< Generic Short READ, one parameter. */
    kDSI_TxDataGenShortRdTwoParam  = 0x24U, /*!< Generic Short READ, two parameter. */
    kDSI_TxDataDcsShortWrNoParam   = 0x05U, /*!< DCS Short WRITE, no parameters. */
    kDSI_TxDataDcsShortWrOneParam  = 0x15U, /*!< DCS Short WRITE, one parameter. */
    kDSI_TxDataDcsShortRdNoParam   = 0x06U, /*!< DCS Short READ, no parameters. */
    kDSI_TxDataSetMaxReturnPktSize = 0x37U, /*!< Set the Maximum Return Packet Size. */

    kDSI_TxDataNull                         = 0x09U, /*!< Null Packet, no data. */
    kDSI_TxDataBlanking                     = 0x19U, /*!< Blanking Packet, no data. */
    kDSI_TxDataGenLongWr                    = 0x29U, /*!< Generic long write. */
    kDSI_TxDataDcsLongWr                    = 0x39U, /*!< DCS Long Write/write_LUT Command Packet. */
    kDSI_TxDataLooselyPackedPixel20BitYCbCr = 0x0CU, /*!< Loosely Packed Pixel Stream, 20-bit YCbCr, 4:2:2 Format. */
    kDSI_TxDataPackedPixel24BitYCbCr        = 0x1CU, /*!< Packed Pixel Stream, 24-bit YCbCr, 4:2:2 Format. */
    kDSI_TxDataPackedPixel16BitYCbCr        = 0x2CU, /*!< Packed Pixel Stream, 16-bit YCbCr, 4:2:2 Format. */
    kDSI_TxDataPackedPixel30BitRGB          = 0x0DU, /*!< Packed Pixel Stream, 30-bit RGB, 10-10-10 Format. */
    kDSI_TxDataPackedPixel36BitRGB          = 0x1DU, /*!< Packed Pixel Stream, 36-bit RGB, 12-12-12 Format. */
    kDSI_TxDataPackedPixel12BitYCrCb        = 0x3DU, /*!< Packed Pixel Stream, 12-bit YCbCr, 4:2:0 Format. */
    kDSI_TxDataPackedPixel16BitRGB          = 0x0EU, /*!< Packed Pixel Stream, 16-bit RGB, 5-6-5 Format. */
    kDSI_TxDataPackedPixel18BitRGB          = 0x1EU, /*!< Packed Pixel Stream, 18-bit RGB, 6-6-6 Format. */
    kDSI_TxDataLooselyPackedPixel18BitRGB   = 0x2EU, /*!< Loosely Packed Pixel Stream, 18-bit RGB, 6-6-6 Format. */
    kDSI_TxDataPackedPixel24BitRGB          = 0x3EU, /*!< Packed Pixel Stream, 24-bit RGB, 8-8-8 Format. */
} dsi_tx_data_type_t;

/*! @brief DSI RX data type. */
typedef enum _dsi_rx_data_type
{
    kDSI_RxDataAckAndErrorReport         = 0x02U, /*!< Acknowledge and Error Report */
    kDSI_RxDataEoTp                      = 0x08U, /*!< End of Transmission packet. */
    kDSI_RxDataGenShortRdResponseOneByte = 0x11U, /*!< Generic Short READ Response, 1 byte returned. */
    kDSI_RxDataGenShortRdResponseTwoByte = 0x12U, /*!< Generic Short READ Response, 2 byte returned. */
    kDSI_RxDataGenLongRdResponse         = 0x1AU, /*!< Generic Long READ Response. */
    kDSI_RxDataDcsLongRdResponse         = 0x1CU, /*!< DCS Long READ Response. */
    kDSI_RxDataDcsShortRdResponseOneByte = 0x21U, /*!< DCS Short READ Response, 1 byte returned. */
    kDSI_RxDataDcsShortRdResponseTwoByte = 0x22U, /*!< DCS Short READ Response, 2 byte returned. */
} dsi_rx_data_type_t;

/*! @brief _dsi_transfer_flags DSI transfer control flags. */
enum
{
    kDSI_TransferUseHighSpeed = (1U << 0U), /*!< Use high speed mode or not. */
    kDSI_TransferPerformBTA   = (1U << 1U), /*!< Perform BTA or not. */
};

/*! @brief Structure for the data transfer. */
typedef struct _dsi_transfer
{
    uint8_t virtualChannel;        /*!< Virtual channel. */
    dsi_tx_data_type_t txDataType; /*!< TX data type. */
    uint8_t flags;                 /*!< Flags to control the transfer, see _dsi_transfer_flags. */
    const uint8_t *txData;         /*!< The TX data buffer. */
    uint8_t *rxData;               /*!< The TX data buffer. */
    uint16_t txDataSize;           /*!< Size of the TX data. */
    uint16_t rxDataSize;           /*!< Size of the RX data. */
    bool sendDscCmd;               /*!< If set to true, the DSC command is specified by @ref dscCmd, otherwise
                                        the DSC command is included in the @ref txData. */
    uint8_t dscCmd;                /*!< The DSC command to send, only valid when @ref sendDscCmd is true. */
} dsi_transfer_t;

/*! @brief MIPI DSI transfer handle. */
typedef struct _dsi_handle dsi_handle_t;

/*!
 * @brief MIPI DSI callback for finished transfer.
 *
 * When transfer finished, one of these status values will be passed to the user:
 * - @ref kStatus_Success Data transfer finished with no error.
 * - @ref kStatus_Timeout Transfer failed because of timeout.
 * - @ref kStatus_DSI_RxDataError RX data error, user could use @ref DSI_GetRxErrorStatus
 *        to check the error details.
 * - @ref kStatus_DSI_ErrorReportReceived Error Report packet received, user could use
 *        @ref DSI_GetAndClearHostStatus to check the error report status.
 * - @ref kStatus_Fail Transfer failed for other reasons.
 */
typedef void (*dsi_callback_t)(const MIPI_DSI_Type *base, dsi_handle_t *handle, status_t status, void *userData);

/*! @brief MIPI DSI transfer handle structure */
struct _dsi_handle
{
    volatile bool isBusy;     /*!< MIPI DSI is busy with APB data transfer. */
    dsi_transfer_t xfer;      /*!< Transfer information. */
    dsi_callback_t callback;  /*!< DSI callback */
    void *userData;           /*!< Callback parameter */
    const MIPI_DSI_Type *dsi; /*!< Pointer to MIPI DSI peripheral. */
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name MIPI_DSI host initialization.
 * @{
 */

/*!
 * @brief Initializes an MIPI DSI host with the user configuration.
 *
 * This function initializes the MIPI DSI host with the configuration, it should
 * be called first before other MIPI DSI driver functions.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param config Pointer to a user-defined configuration structure.
 */
void DSI_Init(const MIPI_DSI_Type *base, const dsi_config_t *config);

/*!
 * @brief Deinitializes an MIPI DSI host.
 *
 * This function should be called after all bother MIPI DSI driver functions.
 *
 * @param base MIPI DSI host peripheral base address.
 */
void DSI_Deinit(const MIPI_DSI_Type *base);

/*!
 * @brief Get the default configuration to initialize the MIPI DSI host.
 *
 * The default value is:
 * @code
    config->numLanes = 4;
    config->enableNonContinuousHsClk = false;
    config->enableTxUlps = false;
    config->autoInsertEoTp = true;
    config->numExtraEoTp = 0;
    config->htxTo_ByteClk = 0;
    config->lrxHostTo_ByteClk = 0;
    config->btaTo_ByteClk = 0;
   @endcode
 *
 * @param config Pointer to a user-defined configuration structure.
 */
void DSI_GetDefaultConfig(dsi_config_t *config);

/*! @} */

/*!
 * @name DPI interface
 * @{
 */

/*!
 * @brief Configure the DPI interface core.
 *
 * This function sets the DPI interface configuration, it should be used in
 * video mode.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param config Pointer to the DPI interface configuration.
 * @param numLanes Lane number, should be same with the setting in @ref dsi_dpi_config_t.
 * @param dpiPixelClkFreq_Hz The DPI pixel clock frequency in Hz.
 * @param dsiHsBitClkFreq_Hz The DSI high speed bit clock frequency in Hz. It is
 * the same with DPHY PLL output.
 */
void DSI_SetDpiConfig(const MIPI_DSI_Type *base,
                      const dsi_dpi_config_t *config,
                      uint8_t numLanes,
                      uint32_t dpiPixelClkFreq_Hz,
                      uint32_t dsiHsBitClkFreq_Hz);

/*! @} */

/*!
 * @name D-PHY configuration.
 * @{
 */

/*!
 * @brief Initializes the D-PHY
 *
 * This function configures the D-PHY timing and setups the D-PHY PLL based on
 * user configuration. The configuration structure could be got by the function
 * @ref DSI_GetDphyDefaultConfig.
 *
 * For some platforms there is not dedicated D-PHY PLL, indicated by the macro
 * FSL_FEATURE_MIPI_DSI_NO_DPHY_PLL. For these platforms, the @p refClkFreq_Hz
 * is useless.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param config Pointer to the D-PHY configuration.
 * @param refClkFreq_Hz The REFCLK frequency in Hz.
 * @return The actual D-PHY PLL output frequency. If could not configure the
 * PLL to the target frequency, the return value is 0.
 */
uint32_t DSI_InitDphy(const MIPI_DSI_Type *base, const dsi_dphy_config_t *config, uint32_t refClkFreq_Hz);

/*!
 * @brief Deinitializes the D-PHY
 *
 * Power down the D-PHY PLL and shut down D-PHY.
 *
 * @param base MIPI DSI host peripheral base address.
 */
void DSI_DeinitDphy(const MIPI_DSI_Type *base);

/*!
 * @brief Get the default D-PHY configuration.
 *
 * Gets the default D-PHY configuration, the timing parameters are set according
 * to D-PHY specification. User could use the configuration directly, or change
 * some parameters according to the special device.
 *
 * @param config Pointer to the D-PHY configuration.
 * @param txHsBitClk_Hz High speed bit clock in Hz.
 * @param txEscClk_Hz Esc clock in Hz.
 */
void DSI_GetDphyDefaultConfig(dsi_dphy_config_t *config, uint32_t txHsBitClk_Hz, uint32_t txEscClk_Hz);

/*! @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enable the interrupts.
 *
 * The interrupts to enable are passed in as OR'ed mask value of _dsi_interrupt.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param intGroup1 Interrupts to enable in group 1.
 * @param intGroup2 Interrupts to enable in group 2.
 */
static inline void DSI_EnableInterrupts(const MIPI_DSI_Type *base, uint32_t intGroup1, uint32_t intGroup2)
{
    base->apb->IRQ_MASK &= ~intGroup1;
    base->apb->IRQ_MASK2 &= ~intGroup2;
}

/*!
 * @brief Disable the interrupts.
 *
 * The interrupts to disable are passed in as OR'ed mask value of _dsi_interrupt.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param intGroup1 Interrupts to disable in group 1.
 * @param intGroup2 Interrupts to disable in group 2.
 */
static inline void DSI_DisableInterrupts(const MIPI_DSI_Type *base, uint32_t intGroup1, uint32_t intGroup2)
{
    base->apb->IRQ_MASK |= intGroup1;
    base->apb->IRQ_MASK2 |= intGroup2;
}

/*!
 * @brief Get and clear the interrupt status.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param intGroup1 Group 1 interrupt status.
 * @param intGroup2 Group 2 interrupt status.
 */
static inline void DSI_GetAndClearInterruptStatus(const MIPI_DSI_Type *base, uint32_t *intGroup1, uint32_t *intGroup2)
{
    *intGroup2 = base->apb->IRQ_STATUS2;
    *intGroup1 = base->apb->IRQ_STATUS;
}

/*! @} */

/*!
 * @name MIPI DSI APB
 * @{
 */

/*!
 * @brief Configure the APB packet to send.
 *
 * This function configures the next APB packet transfer. After configuration,
 * the packet transfer could be started with function @ref DSI_SendApbPacket.
 * If the packet is long packet, Use @ref DSI_WriteApbTxPayload to fill the payload
 * before start transfer.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param wordCount For long packet, this is the byte count of the payload.
 * For short packet, this is (data1 << 8) | data0.
 * @param virtualChannel Virtual channel.
 * @param dataType The packet data type, (DI).
 * @param flags The transfer control flags, see _dsi_transfer_flags.
 */
void DSI_SetApbPacketControl(
    const MIPI_DSI_Type *base, uint16_t wordCount, uint8_t virtualChannel, dsi_tx_data_type_t dataType, uint8_t flags);

/*!
 * @brief Fill the long APB packet payload.
 *
 * Write the long packet payload to TX FIFO.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param payload Pointer to the payload.
 * @param payloadSize Payload size in byte.
 */
void DSI_WriteApbTxPayload(const MIPI_DSI_Type *base, const uint8_t *payload, uint16_t payloadSize);

/*!
 * @brief Extended function to fill the payload to TX FIFO.
 *
 * Write the long packet payload to TX FIFO. This function could be used in two ways
 *
 * 1. Include the DSC command in parameter @p payload. In this case, the DSC command
 *    is the first byte of @p payload. The parameter @p sendDscCmd is set to false,
 *    the @p dscCmd is not used. This function is the same as @ref DSI_WriteApbTxPayload
 *    when used in this way.
 *
 * 2. The DSC command in not in parameter @p payload, but specified by parameter @p dscCmd.
 *    In this case, the parameter @p sendDscCmd is set to true, the @p dscCmd is the DSC
 *    command to send. The @p payload is sent after @p dscCmd.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param payload Pointer to the payload.
 * @param payloadSize Payload size in byte.
 * @param sendDscCmd If set to true, the DSC command is specified by @p dscCmd,
 *        otherwise the DSC command is included in the @p payload.
 * @param dscCmd The DSC command to send, only used when @p sendDscCmd is true.
 */
void DSI_WriteApbTxPayloadExt(
    const MIPI_DSI_Type *base, const uint8_t *payload, uint16_t payloadSize, bool sendDscCmd, uint8_t dscCmd);

/*!
 * @brief Read the long APB packet payload.
 *
 * Read the long packet payload from RX FIFO. This function reads directly but
 * does not check the RX FIFO status. Upper layer should make sure there are
 * available data.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param payload Pointer to the payload.
 * @param payloadSize Payload size in byte.
 */
void DSI_ReadApbRxPayload(const MIPI_DSI_Type *base, uint8_t *payload, uint16_t payloadSize);

/*!
 * @brief Trigger the controller to send out APB packet.
 *
 * Send the packet set by @ref DSI_SetApbPacketControl.
 *
 * @param base MIPI DSI host peripheral base address.
 */
static inline void DSI_SendApbPacket(const MIPI_DSI_Type *base)
{
    base->apb->SEND_PACKET = 0x1U;
}

/*!
 * @brief Get the APB status.
 *
 * The return value is OR'ed value of _dsi_apb_status.
 *
 * @param base MIPI DSI host peripheral base address.
 * @return The APB status.
 */
static inline uint32_t DSI_GetApbStatus(const MIPI_DSI_Type *base)
{
    return base->apb->PKT_STATUS;
}

/*!
 * @brief Get the error status during data transfer.
 *
 * The return value is OR'ed value of _dsi_rx_error_status.
 *
 * @param base MIPI DSI host peripheral base address.
 * @return The error status.
 */
static inline uint32_t DSI_GetRxErrorStatus(const MIPI_DSI_Type *base)
{
    return base->host->RX_ERROR_STATUS;
}

/*!
 * @brief Get the one-bit RX ECC error position.
 *
 * When one-bit ECC RX error detected using @ref DSI_GetRxErrorStatus, this
 * function could be used to get the error bit position.
 *
 * @code
   uint8_t eccErrorPos;
   uint32_t rxErrorStatus = DSI_GetRxErrorStatus(MIPI_DSI);
   if (kDSI_RxErrorEccOneBit & rxErrorStatus)
   {
       eccErrorPos = DSI_GetEccRxErrorPosition(rxErrorStatus);
   }
   @endcode
 *
 * @param rxErrorStatus The error status returned by @ref DSI_GetRxErrorStatus.
 * @return The 1-bit ECC error position.
 */
static inline uint8_t DSI_GetEccRxErrorPosition(uint32_t rxErrorStatus)
{
    return (uint8_t)((rxErrorStatus >> 2U) & 0x1FU);
}

/*!
 * @brief Get and clear the DSI host status.
 *
 * The host status are returned as mask value of @ref _dsi_host_status.
 *
 * @param base MIPI DSI host peripheral base address.
 * @return The DSI host status.
 */
static inline uint32_t DSI_GetAndClearHostStatus(const MIPI_DSI_Type *base)
{
    return base->host->CFG_STATUS_OUT;
}

/*!
 * @brief Get the RX packet header.
 *
 * @param base MIPI DSI host peripheral base address.
 * @return The RX packet header.
 */
static inline uint32_t DSI_GetRxPacketHeader(const MIPI_DSI_Type *base)
{
    return base->apb->PKT_RX_PKT_HEADER;
}

/*!
 * @brief Extract the RX packet type from the packet header.
 *
 * Extract the RX packet type from the packet header get by @ref DSI_GetRxPacketHeader.
 *
 * @param rxPktHeader The RX packet header get by @ref DSI_GetRxPacketHeader.
 * @return The RX packet type.
 */
static inline dsi_rx_data_type_t DSI_GetRxPacketType(uint32_t rxPktHeader)
{
    return (dsi_rx_data_type_t)(uint8_t)((rxPktHeader >> 16U) & 0x3FU);
}

/*!
 * @brief Extract the RX packet word count from the packet header.
 *
 * Extract the RX packet word count from the packet header get by @ref DSI_GetRxPacketHeader.
 *
 * @param rxPktHeader The RX packet header get by @ref DSI_GetRxPacketHeader.
 * @return For long packet, return the payload word count (byte). For short packet,
 * return the (data0 << 8) | data1.
 */
static inline uint16_t DSI_GetRxPacketWordCount(uint32_t rxPktHeader)
{
    return (uint16_t)(rxPktHeader & 0xFFFFU);
}

/*!
 * @brief Extract the RX packet virtual channel from the packet header.
 *
 * Extract the RX packet virtual channel from the packet header get by @ref DSI_GetRxPacketHeader.
 *
 * @param rxPktHeader The RX packet header get by @ref DSI_GetRxPacketHeader.
 * @return The virtual channel.
 */
static inline uint8_t DSI_GetRxPacketVirtualChannel(uint32_t rxPktHeader)
{
    return (uint8_t)((rxPktHeader >> 22U) & 0x3U);
}

/*!
 * @brief APB data transfer using blocking method.
 *
 * Perform APB data transfer using blocking method. This function waits until all
 * data send or received, or timeout happens.
 *
 * When using this API to read data, the actually read data count could be got
 * from xfer->rxDataSize.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param xfer Pointer to the transfer structure.
 * @retval kStatus_Success Data transfer finished with no error.
 * @retval kStatus_Timeout Transfer failed because of timeout.
 * @retval kStatus_DSI_RxDataError RX data error, user could use @ref DSI_GetRxErrorStatus
 * to check the error details.
 * @retval kStatus_DSI_ErrorReportReceived Error Report packet received, user could use
 *        @ref DSI_GetAndClearHostStatus to check the error report status.
 * @retval kStatus_DSI_NotSupported Transfer format not supported.
 * @retval kStatus_DSI_Fail Transfer failed for other reasons.
 */
status_t DSI_TransferBlocking(const MIPI_DSI_Type *base, dsi_transfer_t *xfer);

/*! @} */

/*!
 * @name Transactional
 * @{
 */

/*!
 * @brief Create the MIPI DSI handle.
 *
 * This function initializes the MIPI DSI handle which can be used for other transactional APIs.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param handle Handle pointer.
 * @param callback Callback function.
 * @param userData User data.
 */
status_t DSI_TransferCreateHandle(const MIPI_DSI_Type *base,
                                  dsi_handle_t *handle,
                                  dsi_callback_t callback,
                                  void *userData);

/*!
 * @brief APB data transfer using interrupt method.
 *
 * Perform APB data transfer using interrupt method, when transfer finished,
 * upper layer could be informed through callback function.
 *
 * When using this API to read data, the actually read data count could be got
 * from handle->xfer->rxDataSize after read finished.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param handle pointer to dsi_handle_t structure which stores the transfer state.
 * @param xfer Pointer to the transfer structure.
 *
 * @retval kStatus_Success Data transfer started successfully.
 * @retval kStatus_DSI_Busy Failed to start transfer because DSI is busy with pervious transfer.
 * @retval kStatus_DSI_NotSupported Transfer format not supported.
 */
status_t DSI_TransferNonBlocking(const MIPI_DSI_Type *base, dsi_handle_t *handle, dsi_transfer_t *xfer);

/*!
 * @brief Abort current APB data transfer.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param handle pointer to dsi_handle_t structure which stores the transfer state.
 */
void DSI_TransferAbort(const MIPI_DSI_Type *base, dsi_handle_t *handle);

/*!
 * @brief Interrupt handler for the DSI.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param handle pointer to dsi_handle_t structure which stores the transfer state.
 */
void DSI_TransferHandleIRQ(const MIPI_DSI_Type *base, dsi_handle_t *handle);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_MIPI_DSI_H_ */
