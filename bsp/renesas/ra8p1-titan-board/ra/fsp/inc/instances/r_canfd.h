/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_CANFD_H
#define R_CANFD_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_canfd_cfg.h"
#include "r_can_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup CANFD
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#if BSP_FEATURE_CANFD_LITE
 #define R_CANFD_NUM_COMMON_FIFOS    (1U)
#else
 #define R_CANFD_NUM_COMMON_FIFOS    (6U)
#endif

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** CANFD Status */
typedef enum e_canfd_status
{
    CANFD_STATUS_RESET_MODE    = 0x001, ///< Channel in Reset mode
    CANFD_STATUS_HALT_MODE     = 0x002, ///< Channel in Halt mode
    CANFD_STATUS_SLEEP_MODE    = 0x004, ///< Channel in Sleep mode
    CANFD_STATUS_ERROR_PASSIVE = 0x008, ///< Channel in error-passive state
    CANFD_STATUS_BUS_OFF       = 0x010, ///< Channel in bus-off state
    CANFD_STATUS_TRANSMITTING  = 0x020, ///< Channel is transmitting
    CANFD_STATUS_RECEIVING     = 0x040, ///< Channel is receiving
    CANFD_STATUS_READY         = 0x080, ///< Channel is ready for communication
    CANFD_STATUS_ESI           = 0x100, ///< At least one CAN-FD message was received with the ESI flag set
} canfd_status_t;

/** CANFD Error Code */
typedef enum e_canfd_error
{
    CANFD_ERROR_CHANNEL_BUS              = 0x00000001, ///< Bus Error
    CANFD_ERROR_CHANNEL_WARNING          = 0x00000002, ///< Error Warning (TX/RX error count over 0x5F)
    CANFD_ERROR_CHANNEL_PASSIVE          = 0x00000004, ///< Error Passive (TX/RX error count over 0x7F)
    CANFD_ERROR_CHANNEL_BUS_OFF_ENTRY    = 0x00000008, ///< Bus-Off State Entry
    CANFD_ERROR_CHANNEL_BUS_OFF_RECOVERY = 0x00000010, ///< Recovery from Bus-Off State
    CANFD_ERROR_CHANNEL_OVERLOAD         = 0x00000020, ///< Overload
    CANFD_ERROR_CHANNEL_BUS_LOCK         = 0x00000040, ///< Bus Locked
    CANFD_ERROR_CHANNEL_ARBITRATION_LOSS = 0x00000080, ///< Arbitration Lost
    CANFD_ERROR_CHANNEL_STUFF            = 0x00000100, ///< Stuff Error
    CANFD_ERROR_CHANNEL_FORM             = 0x00000200, ///< Form Error
    CANFD_ERROR_CHANNEL_ACK              = 0x00000400, ///< ACK Error
    CANFD_ERROR_CHANNEL_CRC              = 0x00000800, ///< CRC Error
    CANFD_ERROR_CHANNEL_BIT_RECESSIVE    = 0x00001000, ///< Bit Error (recessive) Error
    CANFD_ERROR_CHANNEL_BIT_DOMINANT     = 0x00002000, ///< Bit Error (dominant) Error
    CANFD_ERROR_CHANNEL_ACK_DELIMITER    = 0x00004000, ///< ACK Delimiter Error
    CANFD_ERROR_GLOBAL_DLC               = 0x00010000, ///< DLC Error
    CANFD_ERROR_GLOBAL_MESSAGE_LOST      = 0x00020000, ///< Message Lost
    CANFD_ERROR_GLOBAL_PAYLOAD_OVERFLOW  = 0x00080000, ///< FD Payload Overflow
    CANFD_ERROR_GLOBAL_TXQ_OVERWRITE     = 0x00100000, ///< TX Queue Message Overwrite
    CANFD_ERROR_GLOBAL_TXQ_MESSAGE_LOST  = 0x00400000, ///< TX Queue Message Lost
    CANFD_ERROR_GLOBAL_CH0_SCAN_FAIL     = 0x01000000, ///< Channel 0 RX Scan Failure
    CANFD_ERROR_GLOBAL_CH1_SCAN_FAIL     = 0x02000000, ///< Channel 1 RX Scan Failure
    CANFD_ERROR_GLOBAL_CH0_ECC           = 0x10000000, ///< Channel 0 ECC Error
    CANFD_ERROR_GLOBAL_CH1_ECC           = 0x20000000, ///< Channel 1 ECC Error
} canfd_error_t;

/** CANFD Transmit Buffer (MB + CFIFO) */
typedef enum e_canfd_tx_buffer
{
    CANFD_TX_BUFFER_0 = 0,
    CANFD_TX_BUFFER_1 = 1,
    CANFD_TX_BUFFER_2 = 2,
    CANFD_TX_BUFFER_3 = 3,
#if !BSP_FEATURE_CANFD_LITE
    CANFD_TX_BUFFER_4  = 4,
    CANFD_TX_BUFFER_5  = 5,
    CANFD_TX_BUFFER_6  = 6,
    CANFD_TX_BUFFER_7  = 7,
    CANFD_TX_BUFFER_32 = 32,
    CANFD_TX_BUFFER_33 = 33,
    CANFD_TX_BUFFER_34 = 34,
    CANFD_TX_BUFFER_35 = 35,
    CANFD_TX_BUFFER_36 = 36,
    CANFD_TX_BUFFER_37 = 37,
    CANFD_TX_BUFFER_38 = 38,
    CANFD_TX_BUFFER_39 = 39,
#endif
    CANFD_TX_BUFFER_FIFO_COMMON_0 = 40,
#if !BSP_FEATURE_CANFD_LITE
    CANFD_TX_BUFFER_FIFO_COMMON_1 = 41,
    CANFD_TX_BUFFER_FIFO_COMMON_2 = 42,
#endif
} canfd_tx_buffer_t;

/** CANFD Transmit Message Buffer (TX MB) */
typedef enum e_canfd_tx_mb
{
    CANFD_TX_MB_0 = 0,
    CANFD_TX_MB_1 = 1,
    CANFD_TX_MB_2 = 2,
    CANFD_TX_MB_3 = 3,
#if !BSP_FEATURE_CANFD_LITE
    CANFD_TX_MB_4  = 4,
    CANFD_TX_MB_5  = 5,
    CANFD_TX_MB_6  = 6,
    CANFD_TX_MB_7  = 7,
    CANFD_TX_MB_32 = 32,
    CANFD_TX_MB_33 = 33,
    CANFD_TX_MB_34 = 34,
    CANFD_TX_MB_35 = 35,
    CANFD_TX_MB_36 = 36,
    CANFD_TX_MB_37 = 37,
    CANFD_TX_MB_38 = 38,
    CANFD_TX_MB_39 = 39,
#endif
} canfd_tx_mb_t;

/** CANFD Receive Buffer (MB + FIFO + CFIFO) */
typedef enum e_canfd_rx_buffer
{
    CANFD_RX_BUFFER_MB_0   = 0,
    CANFD_RX_BUFFER_MB_1   = 1,
    CANFD_RX_BUFFER_MB_2   = 2,
    CANFD_RX_BUFFER_MB_3   = 3,
    CANFD_RX_BUFFER_MB_4   = 4,
    CANFD_RX_BUFFER_MB_5   = 5,
    CANFD_RX_BUFFER_MB_6   = 6,
    CANFD_RX_BUFFER_MB_7   = 7,
    CANFD_RX_BUFFER_MB_8   = 8,
    CANFD_RX_BUFFER_MB_9   = 9,
    CANFD_RX_BUFFER_MB_10  = 10,
    CANFD_RX_BUFFER_MB_11  = 11,
    CANFD_RX_BUFFER_MB_12  = 12,
    CANFD_RX_BUFFER_MB_13  = 13,
    CANFD_RX_BUFFER_MB_14  = 14,
    CANFD_RX_BUFFER_MB_15  = 15,
    CANFD_RX_BUFFER_MB_16  = 16,
    CANFD_RX_BUFFER_MB_17  = 17,
    CANFD_RX_BUFFER_MB_18  = 18,
    CANFD_RX_BUFFER_MB_19  = 19,
    CANFD_RX_BUFFER_MB_20  = 20,
    CANFD_RX_BUFFER_MB_21  = 21,
    CANFD_RX_BUFFER_MB_22  = 22,
    CANFD_RX_BUFFER_MB_23  = 23,
    CANFD_RX_BUFFER_MB_24  = 24,
    CANFD_RX_BUFFER_MB_25  = 25,
    CANFD_RX_BUFFER_MB_26  = 26,
    CANFD_RX_BUFFER_MB_27  = 27,
    CANFD_RX_BUFFER_MB_28  = 28,
    CANFD_RX_BUFFER_MB_29  = 29,
    CANFD_RX_BUFFER_MB_30  = 30,
    CANFD_RX_BUFFER_MB_31  = 31,
    CANFD_RX_BUFFER_FIFO_0 = 32,
    CANFD_RX_BUFFER_FIFO_1 = 33,
#if !BSP_FEATURE_CANFD_LITE
    CANFD_RX_BUFFER_FIFO_2 = 34,
    CANFD_RX_BUFFER_FIFO_3 = 35,
    CANFD_RX_BUFFER_FIFO_4 = 36,
    CANFD_RX_BUFFER_FIFO_5 = 37,
    CANFD_RX_BUFFER_FIFO_6 = 38,
    CANFD_RX_BUFFER_FIFO_7 = 39,
#endif
    CANFD_RX_BUFFER_FIFO_COMMON_0 = 40,
#if !BSP_FEATURE_CANFD_LITE
    CANFD_RX_BUFFER_FIFO_COMMON_1 = 41,
    CANFD_RX_BUFFER_FIFO_COMMON_2 = 42,
#endif
} canfd_rx_buffer_t;

/** CANFD Receive Message Buffer (RX MB) */
typedef enum e_canfd_rx_mb
{
    CANFD_RX_MB_NONE = 0,
    CANFD_RX_MB_0    = 0x80,
    CANFD_RX_MB_1    = 0x80 + 1,
    CANFD_RX_MB_2    = 0x80 + 2,
    CANFD_RX_MB_3    = 0x80 + 3,
    CANFD_RX_MB_4    = 0x80 + 4,
    CANFD_RX_MB_5    = 0x80 + 5,
    CANFD_RX_MB_6    = 0x80 + 6,
    CANFD_RX_MB_7    = 0x80 + 7,
    CANFD_RX_MB_8    = 0x80 + 8,
    CANFD_RX_MB_9    = 0x80 + 9,
    CANFD_RX_MB_10   = 0x80 + 10,
    CANFD_RX_MB_11   = 0x80 + 11,
    CANFD_RX_MB_12   = 0x80 + 12,
    CANFD_RX_MB_13   = 0x80 + 13,
    CANFD_RX_MB_14   = 0x80 + 14,
    CANFD_RX_MB_15   = 0x80 + 15,
    CANFD_RX_MB_16   = 0x80 + 16,
    CANFD_RX_MB_17   = 0x80 + 17,
    CANFD_RX_MB_18   = 0x80 + 18,
    CANFD_RX_MB_19   = 0x80 + 19,
    CANFD_RX_MB_20   = 0x80 + 20,
    CANFD_RX_MB_21   = 0x80 + 21,
    CANFD_RX_MB_22   = 0x80 + 22,
    CANFD_RX_MB_23   = 0x80 + 23,
    CANFD_RX_MB_24   = 0x80 + 24,
    CANFD_RX_MB_25   = 0x80 + 25,
    CANFD_RX_MB_26   = 0x80 + 26,
    CANFD_RX_MB_27   = 0x80 + 27,
    CANFD_RX_MB_28   = 0x80 + 28,
    CANFD_RX_MB_29   = 0x80 + 29,
    CANFD_RX_MB_30   = 0x80 + 30,
    CANFD_RX_MB_31   = 0x80 + 31,
} canfd_rx_mb_t;

/** CANFD Receive FIFO (RX FIFO) */
typedef enum e_canfd_rx_fifo
{
    CANFD_RX_FIFO_0 = (1U),
    CANFD_RX_FIFO_1 = (1U << 1),
#if !BSP_FEATURE_CANFD_LITE
    CANFD_RX_FIFO_2 = (1U << 2),
    CANFD_RX_FIFO_3 = (1U << 3),
    CANFD_RX_FIFO_4 = (1U << 4),
    CANFD_RX_FIFO_5 = (1U << 5),
    CANFD_RX_FIFO_6 = (1U << 6),
    CANFD_RX_FIFO_7 = (1U << 7),
#endif
    CANFD_RX_FIFO_COMMON_0 = (1U << 8),
#if !BSP_FEATURE_CANFD_LITE
    CANFD_RX_FIFO_COMMON_1 = (1U << 9),
    CANFD_RX_FIFO_COMMON_2 = (1U << 10),
    CANFD_RX_FIFO_COMMON_3 = (1U << 11),
    CANFD_RX_FIFO_COMMON_4 = (1U << 12),
    CANFD_RX_FIFO_COMMON_5 = (1U << 13),
#endif
} canfd_rx_fifo_t;

/** CANFD AFL Minimum DLC settings */
typedef enum e_canfd_minimum_dlc
{
    CANFD_MINIMUM_DLC_0 = 0,
    CANFD_MINIMUM_DLC_1,
    CANFD_MINIMUM_DLC_2,
    CANFD_MINIMUM_DLC_3,
    CANFD_MINIMUM_DLC_4,
    CANFD_MINIMUM_DLC_5,
    CANFD_MINIMUM_DLC_6,
    CANFD_MINIMUM_DLC_7,
    CANFD_MINIMUM_DLC_8,
    CANFD_MINIMUM_DLC_12,
    CANFD_MINIMUM_DLC_16,
    CANFD_MINIMUM_DLC_20,
    CANFD_MINIMUM_DLC_24,
    CANFD_MINIMUM_DLC_32,
    CANFD_MINIMUM_DLC_48,
    CANFD_MINIMUM_DLC_64,
} canfd_minimum_dlc_t;

/** CANFD Frame Options */
typedef enum e_canfd_frame_option
{
    CANFD_FRAME_OPTION_ERROR = 0x01,   ///< Error state set (ESI).
    CANFD_FRAME_OPTION_BRS   = 0x02,   ///< Bit Rate Switching (BRS) enabled.
    CANFD_FRAME_OPTION_FD    = 0x04,   ///< Flexible Data frame (FDF).
    // CANFD_FRAME_OPTION_ONESHOT = 0x80, ///< One-shot mode (no retries).
} canfd_frame_options_t;

/* CAN Instance Control Block   */
typedef struct st_canfd_instance_ctrl
{
    R_CANFD_Type * p_reg;                       // Pointer to register base address

    /* Parameters to control CAN peripheral device */
    can_cfg_t const    * p_cfg;                 // Pointer to the configuration structure
    uint32_t             open;                  // Open status of channel.
    can_operation_mode_t operation_mode;        // Can operation mode.
    can_test_mode_t      test_mode;             // Can operation mode.
#if BSP_TZ_SECURE_BUILD
    bool callback_is_secure;                    // If the callback is in non-secure memory then a security state transition is required to call p_callback (BLXNS)
#endif
    void (* p_callback)(can_callback_args_t *); // Pointer to callback
    can_callback_args_t * p_callback_memory;    // Pointer to optional callback argument memory
    void                * p_context;            // Pointer to context to be passed into callback function
} canfd_instance_ctrl_t;

/** AFL Entry (based on R_CANFD_CFDGAFL_Type in renesas.h) */
typedef struct st_canfd_afl_entry_t
{
    union
    {
        uint32_t id_u32;

        struct
        {
            uint32_t id                 : 29; ///< ID to match against
            uint32_t                    : 1;
            can_frame_type_t frame_type : 1;  ///< Frame type (Data or Remote)
            can_id_mode_t    id_mode    : 1;  ///< ID mode (Standard or Extended)
        } id;
    };

    union
    {
        uint32_t mask_u32;

        struct
        {
            uint32_t mask_id         : 29; ///< ID Mask
            uint32_t                 : 1;
            uint32_t mask_frame_type : 1;  ///< Only accept frames with the configured frame type
            uint32_t mask_id_mode    : 1;  ///< Only accept frames with the configured ID mode
        } mask;
    };

    union
    {
        uint32_t destination_u32[2];

        struct
        {
            canfd_minimum_dlc_t minimum_dlc : 4; ///< Minimum DLC value to accept (valid when DLC Check is enabled)
            uint32_t                        : 4;
            canfd_rx_mb_t rx_buffer         : 8; ///< RX Message Buffer to receive messages accepted by this rule
            uint32_t                        : 16;
            canfd_rx_fifo_t fifo_select_flags;   ///< RX FIFO(s) to receive messages accepted by this rule
        } destination;
    };
} canfd_afl_entry_t;

/** CANFD Global Configuration */
typedef struct st_canfd_global_cfg
{
    uint32_t global_interrupts;                            ///< Global control options (CFDGCTR register setting)
    uint32_t global_config;                                ///< Global configuration options (CFDGCFG register setting)
#if !BSP_FEATURE_CANFD_LITE
    uint32_t rx_fifo_config[8];                            ///< RX FIFO configuration (CFDRFCCn register settings)
#else
    uint32_t rx_fifo_config[2];                            ///< RX FIFO configuration (CFDRFCCn register settings)
#endif
    uint32_t rx_mb_config;                                 ///< Number and size of RX Message Buffers (CFDRMNB register setting)
    uint8_t  global_err_ipl;                               ///< Global Error interrupt priority
    uint8_t  rx_fifo_ipl;                                  ///< RX FIFO interrupt priority
    uint32_t common_fifo_config[R_CANFD_NUM_COMMON_FIFOS]; ///< Common FIFO configurations
} canfd_global_cfg_t;

/** CANFD Extended Configuration */
typedef struct st_canfd_extended_cfg
{
    canfd_afl_entry_t const * p_afl;           ///< AFL rules list
    uint64_t               txmb_txi_enable;    ///< Array of TX Message Buffer enable bits
    uint32_t               error_interrupts;   ///< Error interrupt enable bits
    can_bit_timing_cfg_t * p_data_timing;      ///< FD Data Rate (when bitrate switching is used)
    uint8_t                delay_compensation; ///< FD Transceiver Delay Compensation (enable or disable)
    canfd_global_cfg_t   * p_global_cfg;       ///< Global configuration (global error callback channel only)
} canfd_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const can_api_t g_canfd_on_canfd;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_CANFD_Open(can_ctrl_t * const p_api_ctrl, can_cfg_t const * const p_cfg);
fsp_err_t R_CANFD_Close(can_ctrl_t * const p_api_ctrl);
fsp_err_t R_CANFD_Write(can_ctrl_t * const p_api_ctrl, uint32_t const buffer, can_frame_t * const p_frame);
fsp_err_t R_CANFD_Read(can_ctrl_t * const p_api_ctrl, uint32_t const buffer, can_frame_t * const p_frame);
fsp_err_t R_CANFD_ModeTransition(can_ctrl_t * const   p_api_ctrl,
                                 can_operation_mode_t operation_mode,
                                 can_test_mode_t      test_mode);
fsp_err_t R_CANFD_InfoGet(can_ctrl_t * const p_api_ctrl, can_info_t * const p_info);
fsp_err_t R_CANFD_CallbackSet(can_ctrl_t * const          p_api_ctrl,
                              void (                    * p_callback)(can_callback_args_t *),
                              void * const                p_context,
                              can_callback_args_t * const p_callback_memory);

/*******************************************************************************************************************//**
 * @} (end defgroup CAN)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
