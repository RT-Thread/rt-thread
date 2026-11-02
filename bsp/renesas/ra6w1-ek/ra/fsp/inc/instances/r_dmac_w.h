/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup DMAC_W
 * @{
 **********************************************************************************************************************/

#ifndef R_DMAC_W_H
#define R_DMAC_W_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_transfer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** Max configurable number of transfers in TRANSFER_MODE_NORMAL. */
#define DMAC_MAX_NORMAL_TRANSFER_LENGTH    (0xFFFF)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Callback function parameter data. */
typedef transfer_callback_args_t dmac_callback_args_t;

/* Control block used by driver. DO NOT INITIALIZE - this structure will be initialized in @ref transfer_api_t::open. */
typedef struct st_dmac_instance_ctrl
{
    uint32_t open;                     // Driver ID

    transfer_cfg_t const * p_cfg;

    /* Pointer to base register. */
    DMA_Type * p_reg;

    void (* p_callback)(dmac_callback_args_t *); // Pointer to callback.
    dmac_callback_args_t * p_callback_memory;    // Pointer to optional callback argument memory.
    void                 * p_context;            // Pointer to context to be passed into callback function.
} dmac_instance_ctrl_t;

/** DMAC channel start mode */
typedef enum e_dmac_start_mode
{
    /** DMAC channel starts immediately. */
    DMAC_START_IMMEDIATELY = 0,

    /** DMAC channel must be triggered by a peripheral DMA request. */
    DMAC_START_ON_PERIPHERAL_REQUEST = 1,
} dmac_start_mode_t;

/** DMAC channel burst mode */
typedef enum e_dmac_burst_mode
{
    /** DMAC burst mode is disabled */
    DMAC_BURST_MODE_DISABLED = 0,

    /** DMAC burst mode enabled, burst size of 4 data units is used */
    DMAC_BURST_MODE_4x = 1,

    /** DMAC burst mode enabled, burst size of 8 data units is used */
    DMAC_BURST_MODE_8x = 2,
} dmac_burst_mode_t;

/** DMA idle mode
 *
 * In blocking mode the DMA performs a fast back-to-back
 * copy, disabling bus access for any bus master with lower priority.
 * In interrupting mode the DMAC inserts a wait cycle after each
 * store allowing other bus masters to perform a
 * burst read. */
typedef enum e_dmac_idle_mode
{
    /** Blocking mode. */
    DMAC_IDLE_BLOCKING_MODE = 0,

    /** Interrupting mode. */
    DMAC_IDLE_INTERRUPTING_MODE = 1,
} dmac_idle_mode_t;

typedef enum e_dmac_init_mode
{
    /** DMA performs copy A1 to B1, A2 to B2 */
    DMAC_INIT_AX_BX_AY_BY = 0,

    /** DMA performs copy A1 to B1, B2 */
    DMAC_INIT_AX_BX_BY = 1,
} dmac_init_mode_t;

/** DMAC transfer configuration extension. This extension is required. */
typedef struct st_dmac_extended_cfg
{
    uint8_t   channel;                 ///< Channel number, does not apply to all HAL drivers.
    IRQn_Type irq;                     ///< DMAC interrupt number
    uint8_t   ipl;                     ///< DMAC interrupt priority

    dmac_start_mode_t start_mode;      ///< Start DMA immediately or have it triggered by peripheral.
    dmac_idle_mode_t  idle_mode;       ///< Idle mode: blocking or interrupting.
    dmac_init_mode_t  init_mode;       ///< Copy mode: block copy or mem init.
    dmac_burst_mode_t burst_mode;      ///< Enable/Disable burst mode.
    uint8_t           channel_prio;    ///< DMAC channel priority.
    bsp_dmac_trig_t   periph_trigger;  ///< Trigger source, if DMAC starts on a peripheral request.

    /** Number of transfers before IRQ generation. Set to 0 to fire IRQ after transfer ends. */
    uint16_t irq_num_of_trans;

    /** Callback for transfer end interrupt. */
    void (* p_callback)(dmac_callback_args_t * cb_data);
    dmac_callback_args_t * p_callback_memory;

    /** Placeholder for user data.  Passed to the user p_callback in ::dmac_callback_args_t. */
    void * p_context;
} dmac_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const transfer_api_t g_transfer_on_dmac_w;

/** @endcond */

/***********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_DMAC_W_Open(transfer_ctrl_t * const p_api_ctrl, transfer_cfg_t const * const p_cfg);
fsp_err_t R_DMAC_W_Reconfigure(transfer_ctrl_t * const p_api_ctrl, transfer_info_t * p_info);
fsp_err_t R_DMAC_W_Reset(transfer_ctrl_t * const p_api_ctrl,
                         void const * volatile   p_src,
                         void * volatile         p_dest,
                         uint16_t const          num_transfers);
fsp_err_t R_DMAC_W_SoftwareStart(transfer_ctrl_t * const p_api_ctrl, transfer_start_mode_t mode);
fsp_err_t R_DMAC_W_SoftwareStop(transfer_ctrl_t * const p_api_ctrl);
fsp_err_t R_DMAC_W_Enable(transfer_ctrl_t * const p_api_ctrl);
fsp_err_t R_DMAC_W_Disable(transfer_ctrl_t * const p_api_ctrl);
fsp_err_t R_DMAC_W_InfoGet(transfer_ctrl_t * const p_api_ctrl, transfer_properties_t * const p_info);
fsp_err_t R_DMAC_W_Reload(transfer_ctrl_t * const p_api_ctrl,
                          void const            * p_src,
                          void                  * p_dest,
                          uint32_t const          num_transfers);
fsp_err_t R_DMAC_W_CallbackSet(transfer_ctrl_t * const      p_api_ctrl,
                               void (                     * p_callback)(dmac_callback_args_t *),
                               void * const                 p_context,
                               dmac_callback_args_t * const p_callback_memory);
fsp_err_t R_DMAC_W_Close(transfer_ctrl_t * const p_api_ctrl);
fsp_err_t R_DMAC_W_Freeze(bool freeze);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup DMAC_W)
 **********************************************************************************************************************/
