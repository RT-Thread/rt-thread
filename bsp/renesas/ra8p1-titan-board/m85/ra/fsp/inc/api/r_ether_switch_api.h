/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_NETWORKING_INTERFACES
 * @defgroup ETHER_SWITCH_API Ethernet Switch Interface
 * @brief Interface for Ethernet Switch functions.
 *
 * @section ETHER_SWITCH_API_Summary Summary
 * The Ether Switch module provides an API for ethernet switch peripheral.
 * And the general ethernet switch peripheral have forwarding functionality.
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_ETHER_SWITCH_API_H
#define R_ETHER_SWITCH_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#ifndef BSP_OVERRIDE_ETHER_SWITCH_EVENT_T

/** Events that can trigger a callback function */
typedef enum e_ether_switch_event
{
    ETHER_SWITCH_EVENT_RX_COMPLETE,     ///< A descriptor complete to receive a flame.
    ETHER_SWITCH_EVENT_TX_COMPLETE,     ///< A descriptor complete to transmit a flame.
    ETHER_SWITCH_EVENT_RX_QUEUE_FULL,   ///< A RX descriptor queue is full.
    ETHER_SWITCH_EVENT_RX_MESSAGE_LOST, ///< Receive a frame when a RX descriptor queue is full.
    ETHER_SWITCH_EVENT_TAS_ERROR,       ///< TAS gate error.
} ether_switch_event_t;
#endif

#ifndef BSP_OVERRIDE_ETHER_SWITCH_CALLBACK_ARGS_T

/** Callback function parameter data */
typedef struct st_ether_switch_callback_args
{
    uint32_t             channel;      ///< Device channel number
    uint32_t             ports;        ///< Bitmap of ports on which the interrupt occurred.
    uint32_t             queue_index;  ///< Queue index where a interrupt occurs.
    ether_switch_event_t event;        ///< The event can be used to identify what caused the callback.

    void * p_context;                  ///< Placeholder for user data.  Set in @ref ether_switch_api_t::open function in @ref ether_switch_cfg_t.
} ether_switch_callback_args_t;
#endif

/** Control block.  Allocate an instance specific control block to pass into the API calls.
 */
typedef void ether_switch_ctrl_t;

/** Configuration parameters. */
typedef struct st_ether_switch_cfg
{
    uint8_t channel;                                            ///< Channel

    IRQn_Type irq;                                              ///< MCU interrupt number
    uint8_t   ipl;                                              ///< MCU interrupt priority

    void (* p_callback)(ether_switch_callback_args_t * p_args); ///< Callback provided when an ISR occurs.

    /** Placeholder for user data.  Passed to the user callback in ether_switch_callback_args_t. */
    void       * p_context;
    void const * p_extend;                                      ///< Placeholder for user extension.
} ether_switch_cfg_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_ether_switch_api
{
    /** Open driver.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(ether_switch_ctrl_t * const p_ctrl, ether_switch_cfg_t const * const p_cfg);

    /** Close driver.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(ether_switch_ctrl_t * const p_ctrl);
} ether_switch_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_ether_switch_instance
{
    ether_switch_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    ether_switch_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    ether_switch_api_t const * p_api;  ///< Pointer to the API structure for this instance
} ether_switch_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup ETHER_SWITCH_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_ETHER_SWITCH_API_H */
