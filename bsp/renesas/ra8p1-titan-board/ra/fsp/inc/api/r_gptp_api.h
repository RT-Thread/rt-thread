/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_NETWORKING_INTERFACES
 * @defgroup GPTP_API GPTP Interface
 * @brief Interface for gPTP timing.
 *
 * @section GPTP_API_Summary Summary
 * The gPTP API provides a generic interface for gPTP timer operation.
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_GPTP_API_H
#define R_GPTP_API_H

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

/** Timer value. */
typedef struct st_gptp_timer_value
{
    uint16_t time_sec_upper;           ///< Second(Upper 16 bit).
    uint32_t time_sec_lower;           ///< Second(Lower 32 bit).
    uint32_t time_nsec;                ///< Nanosecond.
} gptp_timer_value_t;

/** Configuration of gPTP timer. */
typedef struct st_gptp_timer_cfg
{
    uint8_t clock_period;              ///< Timer increment value.
} gptp_timer_cfg_t;

/** Control block.  Allocate an instance specific control block to pass into the API calls.
 */
typedef void gptp_ctrl_t;

/** GPTP callback arguments definitions. */
typedef struct st_gptp_callback_args
{
    void * p_context;                  ///< Placeholder for user data.   Set in @ref gptp_api_t::open function in @ref gptp_cfg_t.
} gptp_callback_args_t;

/** Configuration parameters. */
typedef struct st_gptp_cfg
{
    void (* p_callback)(gptp_callback_args_t * p_args); ///< Pointer to callback function.
    void       * p_context;                             ///< Placeholder for user data. Passed to the user callback in @ref gptp_callback_args_t.
    void const * p_extend;                              ///< Placeholder for user extension.
} gptp_cfg_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_gptp_api
{
    /** Open driver.
     *
     * @param[in]  p_ctrl             Pointer to control structure.
     * @param[in]  p_cfg              Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(gptp_ctrl_t * const p_ctrl, gptp_cfg_t const * const p_cfg);

    /** Close driver.
     *
     * @param[in]  p_ctrl             Pointer to control structure.
     */
    fsp_err_t (* close)(gptp_ctrl_t * const p_ctrl);

    /** Configure gptp timer parameters.
     *
     * @param[in]  p_ctrl             Pointer to control structure.
     * @param[in]  timer              Timer index.
     * @param[in]  p_timer_cfg        Configuration of the timer.
     */
    fsp_err_t (* timerCfg)(gptp_ctrl_t * const p_ctrl, uint8_t timer, gptp_timer_cfg_t const * const p_timer_cfg);

    /** Start gptp timer.
     *
     * @param[in]  p_ctrl             Pointer to control structure.
     * @param[in]  timer              Timer index.
     */
    fsp_err_t (* start)(gptp_ctrl_t * const p_ctrl, uint8_t timer);

    /** Stop gptp timer.
     *
     * @param[in]  p_ctrl             Pointer to control structure.
     * @param[in]  timer              Timer index.
     */
    fsp_err_t (* stop)(gptp_ctrl_t * const p_ctrl, uint8_t timer);

    /** Get the current time value to gptp timer.
     *
     * @param[in]  p_ctrl             Pointer to control structure.
     * @param[in]  timer              Timer index.
     * @param[out] p_timer_value      Pointer to timer value structure.
     */
    fsp_err_t (* timerValueGet)(gptp_ctrl_t * const p_ctrl, uint8_t timer, gptp_timer_value_t * const p_timer_value);

    /** Set time offset correction to gptp timer.
     *
     * @param[in]  p_ctrl             Pointer to control structure.
     * @param[in]  timer              Timer index.
     * @param[in]  offset             Time offset value.
     */
    fsp_err_t (* timerOffsetSet)(gptp_ctrl_t * const p_ctrl, uint8_t timer, int64_t offset);

    /** Set clock rate correction to gptp timer.
     *
     * @param[in]  p_ctrl             Pointer to control structure.
     * @param[in]  timer              Timer index.
     * @param[in]  rate               Clock rate value.
     */
    fsp_err_t (* timerRateSet)(gptp_ctrl_t * const p_ctrl, uint8_t timer, uint32_t rate);

    /**
     * Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl             Pointer to control structure.
     * @param[in]   p_callback         Callback function.
     * @param[in]   p_context          Pointer to send to callback function.
     * @param[in]   p_callback_memory  Pointer to volatile memory where callback structure can be allocated.
     *                                 Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(gptp_ctrl_t * const p_ctrl, void (* p_callback)(gptp_callback_args_t *),
                              void * const p_context, gptp_callback_args_t * const p_callback_memory);
} gptp_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_gptp_instance
{
    gptp_ctrl_t      * p_ctrl;         ///< Pointer to the control structure for this instance
    gptp_cfg_t const * p_cfg;          ///< Pointer to the configuration structure for this instance
    gptp_api_t const * p_api;          ///< Pointer to the API structure for this instance
} gptp_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup GPTP_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_GPTP_API_H */
