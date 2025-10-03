/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_CAN_H
#define R_CAN_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_can_cfg.h"
#include "r_can_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup CAN
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** CAN Status */
typedef enum e_can_status
{
    CAN_STATUS_NEW_DATA                 = 1,  ///< New Data status flag
    CAN_STATUS_SENT_DATA                = 2,  ///< Sent Data status flag
    CAN_STATUS_RECEIVE_FIFO             = 4,  ///< Receive FIFO status flag
    CAN_STATUS_TRANSMIT_FIFO            = 8,  ///< Transmit FIFO status flag
    CAN_STATUS_NORMAL_MBOX_MESSAGE_LOST = 16, ///< Normal mailbox message lost status flag
    CAN_STATUS_FIFO_MBOX_MESSAGE_LOST   = 32, ///< FIFO mailbox message lost status flag
    CAN_STATUS_TRANSMISSION_ABORT       = 64, ///< Transmission abort status flag
    CAN_STATUS_ERROR         = 128,           ///< Error status flag
    CAN_STATUS_RESET_MODE    = 256,           ///< Reset mode status flag
    CAN_STATUS_HALT_MODE     = 512,           ///< Halt mode status flag
    CAN_STATUS_SLEEP_MODE    = 1024,          ///< Sleep mode status flag
    CAN_STATUS_ERROR_PASSIVE = 2048,          ///< Error-passive status flag
    CAN_STATUS_BUS_OFF       = 4096,          ///< Bus-off status flag
} can_status_t;

/** CAN Error Code */
typedef enum e_can_error
{
    CAN_ERROR_STUFF         = 1,       ///< Stuff Error
    CAN_ERROR_FORM          = 2,       ///< Form Error
    CAN_ERROR_ACK           = 4,       ///< ACK Error
    CAN_ERROR_CRC           = 8,       ///< CRC Error
    CAN_ERROR_BIT_RECESSIVE = 16,      ///< Bit Error (recessive) Error
    CAN_ERROR_BIT_DOMINANT  = 32,      ///< Bit Error (dominant) Error
    CAN_ERROR_ACK_DELIMITER = 64,      ///< ACK Delimiter Error
} can_error_t;

/** CAN Mailbox IDs (MB + FIFO) */
typedef enum e_can_mailbox_id
{
    CAN_MAILBOX_ID_0  = 0,
    CAN_MAILBOX_ID_1  = 1,
    CAN_MAILBOX_ID_2  = 2,
    CAN_MAILBOX_ID_3  = 3,
    CAN_MAILBOX_ID_4  = 4,
    CAN_MAILBOX_ID_5  = 5,
    CAN_MAILBOX_ID_6  = 6,
    CAN_MAILBOX_ID_7  = 7,
    CAN_MAILBOX_ID_8  = 8,
    CAN_MAILBOX_ID_9  = 9,
    CAN_MAILBOX_ID_10 = 10,
    CAN_MAILBOX_ID_11 = 11,
    CAN_MAILBOX_ID_12 = 12,
    CAN_MAILBOX_ID_13 = 13,
    CAN_MAILBOX_ID_14 = 14,
    CAN_MAILBOX_ID_15 = 15,
    CAN_MAILBOX_ID_16 = 16,
    CAN_MAILBOX_ID_17 = 17,
    CAN_MAILBOX_ID_18 = 18,
    CAN_MAILBOX_ID_19 = 19,
    CAN_MAILBOX_ID_20 = 20,
    CAN_MAILBOX_ID_21 = 21,
    CAN_MAILBOX_ID_22 = 22,
    CAN_MAILBOX_ID_23 = 23,
    CAN_MAILBOX_ID_24 = 24,
    CAN_MAILBOX_ID_25 = 25,
    CAN_MAILBOX_ID_26 = 26,
    CAN_MAILBOX_ID_27 = 27,
    CAN_MAILBOX_ID_28 = 28,
    CAN_MAILBOX_ID_29 = 29,
    CAN_MAILBOX_ID_30 = 30,
    CAN_MAILBOX_ID_31 = 31,

    CAN_MAILBOX_ID_TX_FIFO = 24,
    CAN_MAILBOX_ID_RX_FIFO = 28,
} can_mailbox_number_t;

/** CAN  Mailbox type */
typedef enum e_can_mailbox_send_receive
{
    CAN_MAILBOX_RECEIVE,               ///< Mailbox is for receiving.
    CAN_MAILBOX_TRANSMIT,              ///< Mailbox is for sending.
} can_mailbox_send_receive_t;

/** Global CAN ID mode settings */
typedef enum e_can_global_id_mode
{
    CAN_GLOBAL_ID_MODE_STANDARD,       ///< Standard IDs of 11 bits used.
    CAN_GLOBAL_ID_MODE_EXTENDED,       ///< Extended IDs of 29 bits used.
    CAN_GLOBAL_ID_MODE_MIXED,          ///< Both Standard and Extended IDs used.
} can_global_id_mode_t;

/** CAN Message Modes */
typedef enum e_can_message_mode
{
    CAN_MESSAGE_MODE_OVERWRITE = 0,    ///< Receive data will be overwritten if not read before the next frame.
    CAN_MESSAGE_MODE_OVERRUN,          ///< Receive data will be retained until it is read.
} can_message_mode_t;

/** CAN Source Clock */
typedef enum e_can_clock_source
{
    CAN_CLOCK_SOURCE_PCLKB = 0,        ///< PCLKB is the source of the CAN Clock
    CAN_CLOCK_SOURCE_CANMCLK,          ///< CANMCLK is the source of the CAN Clock
} can_clock_source_t;

/** CAN FIFO Interrupt Modes */
typedef enum e_can_fifo_interrupt_mode
{
    CAN_FIFO_INTERRUPT_MODE_TX_EVERY_FRAME = R_CAN0_MIER_FIFO_MB24_Msk,
    CAN_FIFO_INTERRUPT_MODE_RX_EVERY_FRAME = R_CAN0_MIER_FIFO_MB28_Msk,
    CAN_FIFO_INTERRUPT_MODE_TX_EMPTY       = R_CAN0_MIER_FIFO_MB25_Msk | R_CAN0_MIER_FIFO_MB24_Msk,
} can_fifo_interrupt_mode_t;

/** CAN Mailbox */
typedef struct st_can_mailbox
{
    /* The first three elements are the same as can_frame_t for optimization purposes. */
    uint32_t                   mailbox_id;   ///< Mailbox ID.
    can_id_mode_t              id_mode;      ///< Standard or Extended ID. Only used in Mixed ID mode.
    can_frame_type_t           frame_type;   ///< Frame type for receive mailbox.
    can_mailbox_send_receive_t mailbox_type; ///< Receive or Transmit mailbox type.
} can_mailbox_t;

/** CAN FIFO interrupt configuration */
typedef struct st_can_fifo_interrupt_cfg
{
    can_fifo_interrupt_mode_t fifo_int_mode; ///< FIFO interrupts mode (RX and TX combined).

    IRQn_Type tx_fifo_irq;                   ///< TX FIFO IRQ.
    IRQn_Type rx_fifo_irq;                   ///< RX FIFO IRQ.
} can_fifo_interrupt_cfg_t;

/** CAN RX FIFO configuration */
typedef struct st_can_rx_fifo_cfg
{
    uint32_t      rx_fifo_mask1;       ///< RX FIFO acceptance filter mask 1.
    uint32_t      rx_fifo_mask2;       ///< RX FIFO acceptance filter mask 1.
    can_mailbox_t rx_fifo_id1;         ///< RX FIFO acceptance filter ID 1.
    can_mailbox_t rx_fifo_id2;         ///< RX FIFO acceptance filter ID 2.
} can_rx_fifo_cfg_t;

/** CAN extended configuration */
typedef struct st_can_extended_cfg
{
    can_clock_source_t               clock_source;   ///< Source of the CAN clock.
    uint32_t                       * p_mailbox_mask; ///< Mailbox mask, one for every 4 mailboxes.
    can_mailbox_t                  * p_mailbox;      ///< Pointer to mailboxes.
    can_global_id_mode_t             global_id_mode; ///< Standard or Extended ID mode.
    uint32_t                         mailbox_count;  ///< Number of mailboxes.
    can_message_mode_t               message_mode;   ///< Overwrite message or overrun.
    can_fifo_interrupt_cfg_t const * p_fifo_int_cfg; ///< Pointer to FIFO interrupt configuration.
    can_rx_fifo_cfg_t              * p_rx_fifo_cfg;  ///< Pointer to RX FIFO configuration.
} can_extended_cfg_t;

/* CAN Instance Control Block   */
typedef struct st_can_instance_ctrl
{
    /* Parameters to control CAN peripheral device */
    can_cfg_t const    * p_cfg;                 // Pointer to the configuration structure
    R_CAN0_Type        * p_reg;                 // Pointer to register base address
    uint32_t             open;                  // Open status of channel.
    can_operation_mode_t operation_mode;        // Can operation mode.
    can_test_mode_t      test_mode;             // Can operation mode.
    can_id_mode_t        id_mode;               // Standard or Extended ID mode.
    uint32_t             mailbox_count;         // Number of mailboxes.
    can_mailbox_t      * p_mailbox;             // Pointer to mailboxes.
    can_clock_source_t   clock_source;          // Clock source. CANMCLK or PCLKB.

    void (* p_callback)(can_callback_args_t *); // Pointer to callback
    can_callback_args_t * p_callback_memory;    // Pointer to optional callback argument memory
    void                * p_context;            // Pointer to context to be passed into callback function
} can_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const can_api_t g_can_on_can;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_CAN_Open(can_ctrl_t * const p_api_ctrl, can_cfg_t const * const p_cfg);
fsp_err_t R_CAN_Close(can_ctrl_t * const p_api_ctrl);
fsp_err_t R_CAN_Write(can_ctrl_t * const p_api_ctrl, uint32_t const mailbox, can_frame_t * const p_frame);
fsp_err_t R_CAN_Read(can_ctrl_t * const p_api_ctrl, uint32_t mailbox, can_frame_t * const p_frame);
fsp_err_t R_CAN_ModeTransition(can_ctrl_t * const   p_api_ctrl,
                               can_operation_mode_t operation_mode,
                               can_test_mode_t      test_mode);
fsp_err_t R_CAN_InfoGet(can_ctrl_t * const p_api_ctrl, can_info_t * const p_info);
fsp_err_t R_CAN_CallbackSet(can_ctrl_t * const          p_api_ctrl,
                            void (                    * p_callback)(can_callback_args_t *),
                            void * const                p_context,
                            can_callback_args_t * const p_callback_memory);

/*******************************************************************************************************************//**
 * @} (end defgroup CAN)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
