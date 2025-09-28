/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_MONITORING_INTERFACES
 * @defgroup WDT_API WDT Interface
 * @brief Interface for watch dog timer functions.
 *
 * @section WDT_API_Summary Summary
 * The WDT interface for the Watchdog Timer (WDT) peripheral provides watchdog functionality including resetting the
 * device or generating an interrupt.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_WDT_API_H
#define R_WDT_API_H

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
#ifndef BSP_OVERRIDE_WDT_TIMEOUT_T

/** WDT time-out periods. */
typedef enum e_wdt_timeout
{
    WDT_TIMEOUT_128 = 0,               ///< 128 clock cycles
    WDT_TIMEOUT_512,                   ///< 512 clock cycles
    WDT_TIMEOUT_1024,                  ///< 1024 clock cycles
    WDT_TIMEOUT_2048,                  ///< 2048 clock cycles
    WDT_TIMEOUT_4096,                  ///< 4096 clock cycles
    WDT_TIMEOUT_8192,                  ///< 8192 clock cycles
    WDT_TIMEOUT_16384,                 ///< 16384 clock cycles
} wdt_timeout_t;
#endif

#ifndef BSP_OVERRIDE_WDT_CLOCK_DIVISION_T

/** WDT clock division ratio. */
typedef enum e_wdt_clock_division
{
    WDT_CLOCK_DIVISION_1    = 0,       ///< CLK/1
    WDT_CLOCK_DIVISION_4    = 1,       ///< CLK/4
    WDT_CLOCK_DIVISION_16   = 2,       ///< CLK/16
    WDT_CLOCK_DIVISION_32   = 3,       ///< CLK/32
    WDT_CLOCK_DIVISION_64   = 4,       ///< CLK/64
    WDT_CLOCK_DIVISION_128  = 15,      ///< CLK/128
    WDT_CLOCK_DIVISION_256  = 5,       ///< CLK/256
    WDT_CLOCK_DIVISION_512  = 6,       ///< CLK/512
    WDT_CLOCK_DIVISION_2048 = 7,       ///< CLK/2048
    WDT_CLOCK_DIVISION_8192 = 8,       ///< CLK/8192
} wdt_clock_division_t;
#endif

#ifndef BSP_OVERRIDE_WDT_WINDOW_START_END_T

/** WDT refresh permitted period window start position. */
typedef enum e_wdt_window_start
{
    WDT_WINDOW_START_25  = 0,          ///< Start position = 25%
    WDT_WINDOW_START_50  = 1,          ///< Start position = 50%
    WDT_WINDOW_START_75  = 2,          ///< Start position = 75%
    WDT_WINDOW_START_100 = 3,          ///< Start position = 100%
} wdt_window_start_t;

/** WDT refresh permitted period window end position. */
typedef enum e_wdt_window_end
{
    WDT_WINDOW_END_75 = 0,             ///< End position = 75%
    WDT_WINDOW_END_50 = 1,             ///< End position = 50%
    WDT_WINDOW_END_25 = 2,             ///< End position = 25%
    WDT_WINDOW_END_0  = 3,             ///< End position = 0%
} wdt_window_end_t;
#endif

/** WDT Counter underflow and refresh error control. */
typedef enum e_wdt_reset_control
{
    WDT_RESET_CONTROL_NMI   = 0,       ///< NMI/IRQ request when counter underflows.
    WDT_RESET_CONTROL_RESET = 1,       ///< Reset request when counter underflows.
} wdt_reset_control_t;

/** WDT Counter operation in sleep mode. */
typedef enum e_wdt_stop_control
{
    WDT_STOP_CONTROL_DISABLE = 0,      ///< Count will not stop when device enters sleep mode.
    WDT_STOP_CONTROL_ENABLE  = 1,      ///< Count will automatically stop when device enters sleep mode.
} wdt_stop_control_t;

/** WDT status */
typedef enum e_wdt_status
{
    WDT_STATUS_NO_ERROR                    = 0, ///< No status flags set.
    WDT_STATUS_UNDERFLOW                   = 1, ///< Underflow flag set.
    WDT_STATUS_REFRESH_ERROR               = 2, ///< Refresh error flag set. Refresh outside of permitted window.
    WDT_STATUS_UNDERFLOW_AND_REFRESH_ERROR = 3, ///< Underflow and refresh error flags set.
    WDT_STATUS_OVERFLOW                    = 4, ///< Overflow flag set.
} wdt_status_t;

/** Callback function parameter data */
typedef struct st_wdt_callback_args
{
    void * p_context;                  ///< Placeholder for user data.  Set in @ref wdt_api_t::open function in @ref wdt_cfg_t.
} wdt_callback_args_t;

/** WDT timeout data. Used to return frequency of WDT clock and timeout period */
typedef struct st_wdt_timeout_values
{
    uint32_t clock_frequency_hz;       ///< Frequency of watchdog clock after divider.
    uint32_t timeout_clocks;           ///< Timeout period in units of watchdog clock ticks.
} wdt_timeout_values_t;

/** WDT control block.  Allocate an instance specific control block to pass into the WDT API calls.
 */
typedef void wdt_ctrl_t;

/** WDT configuration parameters. */
typedef struct st_wdt_cfg
{
    wdt_timeout_t        timeout;                      ///< Timeout period.
    wdt_clock_division_t clock_division;               ///< Clock divider.
    wdt_window_start_t   window_start;                 ///< Refresh permitted window start position.
    wdt_window_end_t     window_end;                   ///< Refresh permitted window end position.
    wdt_reset_control_t  reset_control;                ///< Select NMI/IRQ or reset generated on underflow.
    wdt_stop_control_t   stop_control;                 ///< Select whether counter operates in sleep mode.
    void (* p_callback)(wdt_callback_args_t * p_args); ///< Callback provided when a WDT ISR occurs.

    /** Placeholder for user data.  Passed to the user callback in wdt_callback_args_t. */
    void       * p_context;
    void const * p_extend;                             ///< Placeholder for user extension.
} wdt_cfg_t;

/** WDT functions implemented at the HAL layer will follow this API. */
typedef struct st_wdt_api
{
    /** Initialize the WDT in register start mode. In auto-start mode (Supported devices only) with NMI output it
     * registers the NMI callback.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(wdt_ctrl_t * const p_ctrl, wdt_cfg_t const * const p_cfg);

    /** Refresh the watchdog timer.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* refresh)(wdt_ctrl_t * const p_ctrl);

    /** Read the status of the WDT.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_status     Pointer to variable to return status information through.
     */
    fsp_err_t (* statusGet)(wdt_ctrl_t * const p_ctrl, wdt_status_t * const p_status);

    /** Clear the status flags of the WDT.
     *
     * @param[in] p_ctrl        Pointer to control structure.
     * @param[in] status        Status condition(s) to clear.
     */
    fsp_err_t (* statusClear)(wdt_ctrl_t * const p_ctrl, const wdt_status_t status);

    /** Read the current WDT counter value.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[out] p_count      Pointer to variable to return current WDT counter value.
     */
    fsp_err_t (* counterGet)(wdt_ctrl_t * const p_ctrl, uint32_t * const p_count);

    /** Read the watchdog timeout values.
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[out] p_timeout        Pointer to structure to return timeout values.
     */
    fsp_err_t (* timeoutGet)(wdt_ctrl_t * const p_ctrl, wdt_timeout_values_t * const p_timeout);

    /** Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Pointer to the WDT control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_callback_memory        Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(wdt_ctrl_t * const p_ctrl, void (* p_callback)(wdt_callback_args_t *),
                              void * const p_context, wdt_callback_args_t * const p_callback_memory);
} wdt_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_wdt_instance
{
    wdt_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    wdt_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    wdt_api_t const * p_api;           ///< Pointer to the API structure for this instance
} wdt_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup WDT_API)
 **********************************************************************************************************************/
