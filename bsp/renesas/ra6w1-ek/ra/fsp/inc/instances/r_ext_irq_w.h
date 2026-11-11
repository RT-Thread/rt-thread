/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup EXT_IRQ_W
 * @{
 **********************************************************************************************************************/

#ifndef R_EXT_IRQ_W_H
#define R_EXT_IRQ_W_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_external_irq_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/*********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/** Extended EXT_IRQ interface configuration */
typedef struct st_ext_irq_w_extended_cfg
{
    bsp_io_port_pin_t irq_pin;                                  ///< IRQ pin
} ext_irq_w_extended_cfg_t;

/** EXT_IRQ private control block. DO NOT MODIFY.  Initialization occurs when @ref R_EXT_IRQ_W_ExternalIrqOpen is called. */
typedef struct st_ext_irq_w_instance_ctrl
{
    uint32_t  open;                                             ///< Used to determine if channel control block is in use
    IRQn_Type irq;                                              ///< NVIC interrupt number
    uint8_t   channel;                                          ///< Channel

    bsp_io_port_pin_t irq_pin;                                  ///< IRQ pin

    void (* p_callback)(external_irq_callback_args_t * p_args); // Pointer to callback that is called when an edge is detected on the external irq pin.

    /** Placeholder for user data.  Passed to the user callback in ::external_irq_callback_args_t. */
    void * p_context;
} ext_irq_w_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const external_irq_api_t g_external_irq_on_ext_irq_w;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_EXT_IRQ_W_ExternalIrqOpen(external_irq_ctrl_t * const p_api_ctrl, external_irq_cfg_t const * const p_cfg);

fsp_err_t R_EXT_IRQ_W_ExternalIrqEnable(external_irq_ctrl_t * const p_api_ctrl);

fsp_err_t R_EXT_IRQ_W_ExternalIrqDisable(external_irq_ctrl_t * const p_api_ctrl);

fsp_err_t R_EXT_IRQ_W_ExternalIrqCallbackSet(external_irq_ctrl_t * const          p_api_ctrl,
                                         void (                             * p_callback)(external_irq_callback_args_t *),
                                         void * const                   p_context,
                                         external_irq_callback_args_t * const p_callback_memory);

fsp_err_t R_EXT_IRQ_W_ExternalIrqClose(external_irq_ctrl_t * const p_api_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup EXT_IRQ_W)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_EXT_IRQ_W_H
