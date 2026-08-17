/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup WDOG_W
 * @{
 **********************************************************************************************************************/

#ifndef R_WDOG_W_H
#define R_WDOG_W_H

#include "r_wdog_w_cfg.h"
#include "r_wdt_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define WDOG_W_TIMEOUT_MIN     (1U)
#if defined(WDTSYS_WDTSYS_REG_WDTSYS_VAL_Msk)
 #define WDOG_W_TIMEOUT_MAX    WDTSYS_WDTSYS_REG_WDTSYS_VAL_Msk
#elif defined(SYS_WDOG_WATCHDOG_REG_WDOG_VAL_Msk)
 #define WDOG_W_TIMEOUT_MAX    SYS_WDOG_WATCHDOG_REG_WDOG_VAL_Msk
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** WDOG_W private control block. DO NOT MODIFY. Initialization occurs when @ref wdt_api_t::open is called. */
typedef struct st_wdog_w_instance_ctrl
{
    uint32_t          wdt_open;                        // Indicates whether the open() API has been successfully called.
    const wdt_cfg_t * p_cfg;                           // Pointer to initial configuration.

    uint32_t timeout;                                  // Timeout value (may be modified after initial open).
    void   * p_context;                                // Placeholder for user data.  Passed to the user callback in
    // wdt_callback_args_t.
    void (* p_callback)(wdt_callback_args_t * p_args); // Callback provided when a WDOG_W NMI ISR occurs.
    wdt_callback_args_t * p_callback_memory;           // Pointer to non-secure memory that can be used to pass
                                                       // arguments to a callback in non-secure memory.
} wdog_w_instance_ctrl_t;

/** WDOG_W clock source options. */
typedef enum e_wdog_w_clk_src
{
    WDOG_W_CLK_SRC_RCLP = 0,           ///< Use RCLP as clock source.
    WDOG_W_CLK_SRC_RCX  = 1,           ///< Use RCX as clock source.
} wdog_w_clk_src_t;

/** WATCHDOG extended Configuration */
typedef struct st_wdog_w_extended_cfg
{
    wdog_w_clk_src_t wdt_clk_src;      ///< CLock source setting for WDT.
} wdog_w_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const wdt_api_t g_wdt_on_wdog_w;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_WDOG_W_Refresh(wdt_ctrl_t * const p_ctrl);

fsp_err_t R_WDOG_W_Open(wdt_ctrl_t * const p_ctrl, wdt_cfg_t const * const p_cfg);

fsp_err_t R_WDOG_W_StatusClear(wdt_ctrl_t * const p_ctrl, const wdt_status_t status);

fsp_err_t R_WDOG_W_StatusGet(wdt_ctrl_t * const p_ctrl, wdt_status_t * const p_status);

fsp_err_t R_WDOG_W_CounterGet(wdt_ctrl_t * const p_ctrl, uint32_t * const p_count);

fsp_err_t R_WDOG_W_TimeoutGet(wdt_ctrl_t * const p_ctrl, wdt_timeout_values_t * const p_timeout);

fsp_err_t R_WDOG_W_TimeoutSet(wdt_ctrl_t * const p_ctrl, uint32_t timeout);

fsp_err_t R_WDOG_W_CallbackSet(wdt_ctrl_t * const          p_ctrl,
                               void (                    * p_callback)(wdt_callback_args_t *),
                               void * const                p_context,
                               wdt_callback_args_t * const p_callback_memory);

fsp_err_t R_WDOG_W_Freeze(wdt_ctrl_t * const p_ctrl, bool freeze);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_WDOG_W_H

/*******************************************************************************************************************//**
 * @} (end addtogroup WDOG_W)
 **********************************************************************************************************************/
