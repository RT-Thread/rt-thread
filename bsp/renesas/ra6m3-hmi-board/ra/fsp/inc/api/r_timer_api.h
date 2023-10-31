/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#ifndef R_TIMER_API_H
#define R_TIMER_API_H

/*******************************************************************************************************************//**
 * @defgroup TIMER_API Timer Interface
 * @ingroup RENESAS_INTERFACES
 * @brief Interface for timer functions.
 *
 * @section TIMER_API_SUMMARY Summary
 * The general timer interface provides standard timer functionality including periodic mode, one-shot mode, PWM output,
 * and free-running timer mode.  After each timer cycle (overflow or underflow), an interrupt can be triggered.
 *
 * If an instance supports output compare mode, it is provided in the extension configuration
 * timer_on_<instance>_cfg_t defined in r_<instance>.h.
 *
 * Implemented by:
 * - @ref GPT
 * - @ref AGT
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Leading zeroes removed to avoid coding standard violation. */

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Events that can trigger a callback function */
typedef enum e_timer_event
{
    TIMER_EVENT_CYCLE_END,                     ///< Requested timer delay has expired or timer has wrapped around
    TIMER_EVENT_CREST = TIMER_EVENT_CYCLE_END, ///< Timer crest event (counter is at a maximum, triangle-wave PWM only)
    TIMER_EVENT_CAPTURE_A,                     ///< A capture has occurred on signal A
    TIMER_EVENT_CAPTURE_B,                     ///< A capture has occurred on signal B
    TIMER_EVENT_TROUGH,                        ///< Timer trough event (counter is 0, triangle-wave PWM only
} timer_event_t;

/** Timer variant types. */
typedef enum e_timer_variant
{
    TIMER_VARIANT_32_BIT,              ///< 32-bit timer
    TIMER_VARIANT_16_BIT               ///< 16-bit timer
} timer_variant_t;

/** Callback function parameter data */
typedef struct st_timer_callback_args
{
    /** Placeholder for user data.  Set in @ref timer_api_t::open function in @ref timer_cfg_t. */
    void const  * p_context;
    timer_event_t event;               ///< The event can be used to identify what caused the callback.

    /** Most recent capture, only valid if event is TIMER_EVENT_CAPTURE_A or TIMER_EVENT_CAPTURE_B. */
    uint32_t capture;
} timer_callback_args_t;

/** Timer control block.  Allocate an instance specific control block to pass into the timer API calls.
 * @par Implemented as
 * - gpt_instance_ctrl_t
 * - agt_instance_ctrl_t
 */
typedef void timer_ctrl_t;

/** Possible status values returned by @ref timer_api_t::statusGet. */
typedef enum e_timer_state
{
    TIMER_STATE_STOPPED  = 0,          ///< Timer is stopped
    TIMER_STATE_COUNTING = 1,          ///< Timer is running
} timer_state_t;

/** Timer operational modes */
typedef enum e_timer_mode
{
    TIMER_MODE_PERIODIC,                          ///< Timer restarts after period elapses.
    TIMER_MODE_ONE_SHOT,                          ///< Timer stops after period elapses.
    TIMER_MODE_PWM,                               ///< Timer generates saw-wave PWM output.
    TIMER_MODE_TRIANGLE_WAVE_SYMMETRIC_PWM  = 4U, ///< Timer generates symmetric triangle-wave PWM output.
    TIMER_MODE_TRIANGLE_WAVE_ASYMMETRIC_PWM = 5U, ///< Timer generates asymmetric triangle-wave PWM output.

    /**
     * Timer generates Asymmetric Triangle-wave PWM output. In PWM mode 3, the duty cycle does
     * not need to be updated at each tough/crest interrupt. Instead, the trough and crest duty cycle values can be
     * set once and only need to be updated when the application needs to change the duty cycle.
     */
    TIMER_MODE_TRIANGLE_WAVE_ASYMMETRIC_PWM_MODE3 = 6U,
} timer_mode_t;

/** Direction of timer count */
typedef enum e_timer_direction
{
    TIMER_DIRECTION_DOWN = 0,          ///< Timer count goes up
    TIMER_DIRECTION_UP   = 1           ///< Timer count goes down
} timer_direction_t;

/** PCLK divisors */
typedef enum e_timer_source_div
{
    TIMER_SOURCE_DIV_1    = 0,         ///< Timer clock source divided by 1
    TIMER_SOURCE_DIV_2    = 1,         ///< Timer clock source divided by 2
    TIMER_SOURCE_DIV_4    = 2,         ///< Timer clock source divided by 4
    TIMER_SOURCE_DIV_8    = 3,         ///< Timer clock source divided by 8
    TIMER_SOURCE_DIV_16   = 4,         ///< Timer clock source divided by 16
    TIMER_SOURCE_DIV_32   = 5,         ///< Timer clock source divided by 32
    TIMER_SOURCE_DIV_64   = 6,         ///< Timer clock source divided by 64
    TIMER_SOURCE_DIV_128  = 7,         ///< Timer clock source divided by 128
    TIMER_SOURCE_DIV_256  = 8,         ///< Timer clock source divided by 256
    TIMER_SOURCE_DIV_512  = 9,         ///< Timer clock source divided by 512
    TIMER_SOURCE_DIV_1024 = 10,        ///< Timer clock source divided by 1024
} timer_source_div_t;

/** Timer information structure to store various information for a timer resource */
typedef struct st_timer_info
{
    timer_direction_t count_direction; ///< Clock counting direction of the timer.
    uint32_t          clock_frequency; ///< Clock frequency of the timer counter.

    /** Period in raw timer counts.
     * @note For triangle wave PWM modes, the full period is double this value.
     */
    uint32_t period_counts;
} timer_info_t;

/** Current timer status. */
typedef struct st_timer_status
{
    uint32_t      counter;             ///< Current counter value
    timer_state_t state;               ///< Current timer state (running or stopped)
} timer_status_t;

/** User configuration structure, used in open function */
typedef struct st_timer_cfg
{
    timer_mode_t mode;                    ///< Select enumerated value from @ref timer_mode_t

    /* Period in raw timer counts.
     * @note For triangle wave PWM modes, enter the period of half the triangle wave, or half the desired period.
     */
    uint32_t           period_counts;     ///< Period in raw timer counts
    timer_source_div_t source_div;        ///< Source clock divider
    uint32_t           duty_cycle_counts; ///< Duty cycle in counts

    /** Select a channel corresponding to the channel number of the hardware. */
    uint8_t   channel;
    uint8_t   cycle_end_ipl;              ///< Cycle end interrupt priority
    IRQn_Type cycle_end_irq;              ///< Cycle end interrupt

    /** Callback provided when a timer ISR occurs.  Set to NULL for no CPU interrupt. */
    void (* p_callback)(timer_callback_args_t * p_args);

    /** Placeholder for user data.  Passed to the user callback in @ref timer_callback_args_t. */
    void const * p_context;
    void const * p_extend;             ///< Extension parameter for hardware specific settings.
} timer_cfg_t;

/** Timer API structure. General timer functions implemented at the HAL layer follow this API. */
typedef struct st_timer_api
{
    /** Initial configuration.
     * @par Implemented as
     * - @ref R_GPT_Open()
     * - @ref R_AGT_Open()
     *
     * @param[in]   p_ctrl     Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg      Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(timer_ctrl_t * const p_ctrl, timer_cfg_t const * const p_cfg);

    /** Start the counter.
     * @par Implemented as
     * - @ref R_GPT_Start()
     * - @ref R_AGT_Start()
     *
     * @param[in]   p_ctrl     Control block set in @ref timer_api_t::open call for this timer.
     */
    fsp_err_t (* start)(timer_ctrl_t * const p_ctrl);

    /** Stop the counter.
     * @par Implemented as
     * - @ref R_GPT_Stop()
     * - @ref R_AGT_Stop()
     *
     * @param[in]   p_ctrl     Control block set in @ref timer_api_t::open call for this timer.
     */
    fsp_err_t (* stop)(timer_ctrl_t * const p_ctrl);

    /** Reset the counter to the initial value.
     * @par Implemented as
     * - @ref R_GPT_Reset()
     * - @ref R_AGT_Reset()
     *
     * @param[in]   p_ctrl     Control block set in @ref timer_api_t::open call for this timer.
     */
    fsp_err_t (* reset)(timer_ctrl_t * const p_ctrl);

    /** Enables input capture.
     * @par Implemented as
     * - @ref R_GPT_Enable()
     * - @ref R_AGT_Enable()
     *
     * @param[in]   p_ctrl     Control block set in @ref timer_api_t::open call for this timer.
     */
    fsp_err_t (* enable)(timer_ctrl_t * const p_ctrl);

    /** Disables input capture.
     * @par Implemented as
     * - @ref R_GPT_Disable()
     * - @ref R_AGT_Disable()
     *
     * @param[in]   p_ctrl     Control block set in @ref timer_api_t::open call for this timer.
     */
    fsp_err_t (* disable)(timer_ctrl_t * const p_ctrl);

    /** Set the time until the timer expires.  See implementation for details of period update timing.
     *
     * @par Implemented as
     * - @ref R_GPT_PeriodSet()
     * - @ref R_AGT_PeriodSet()
     *
     * @note Timer expiration may or may not generate a CPU interrupt based on how the timer is configured in
     * @ref timer_api_t::open.
     * @param[in]   p_ctrl     Control block set in @ref timer_api_t::open call for this timer.
     * @param[in]   p_period   Time until timer should expire.
     */
    fsp_err_t (* periodSet)(timer_ctrl_t * const p_ctrl, uint32_t const period);

    /** Sets the number of counts for the pin level to be high.  If the timer is counting, the updated duty cycle is
     * reflected after the next timer expiration.
     *
     * @par Implemented as
     * - @ref R_GPT_DutyCycleSet()
     * - @ref R_AGT_DutyCycleSet()
     *
     * @param[in]   p_ctrl             Control block set in @ref timer_api_t::open call for this timer.
     * @param[in]   duty_cycle_counts  Time until duty cycle should expire.
     * @param[in]   pin                Which output pin to update.  See implementation for details.
     */
    fsp_err_t (* dutyCycleSet)(timer_ctrl_t * const p_ctrl, uint32_t const duty_cycle_counts, uint32_t const pin);

    /** Stores timer information in p_info.
     * @par Implemented as
     * - @ref R_GPT_InfoGet()
     * - @ref R_AGT_InfoGet()
     *
     * @param[in]   p_ctrl     Control block set in @ref timer_api_t::open call for this timer.
     * @param[out]  p_info     Collection of information for this timer.
     */
    fsp_err_t (* infoGet)(timer_ctrl_t * const p_ctrl, timer_info_t * const p_info);

    /** Get the current counter value and timer state and store it in p_status.
     * @par Implemented as
     * - @ref R_GPT_StatusGet()
     * - @ref R_AGT_StatusGet()
     *
     * @param[in]   p_ctrl     Control block set in @ref timer_api_t::open call for this timer.
     * @param[out]  p_status   Current status of this timer.
     */
    fsp_err_t (* statusGet)(timer_ctrl_t * const p_ctrl, timer_status_t * const p_status);

    /** Specify callback function and optional context pointer and working memory pointer.
     * @par Implemented as
     * - @ref R_GPT_CallbackSet()
     * - @ref R_AGT_CallbackSet()
     *
     * @param[in]   p_ctrl                   Control block set in @ref timer_api_t::open call for this timer.
     * @param[in]   p_callback               Callback function to register
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(timer_ctrl_t * const p_api_ctrl, void (* p_callback)(timer_callback_args_t *),
                              void const * const p_context, timer_callback_args_t * const p_callback_memory);

    /** Allows driver to be reconfigured and may reduce power consumption.
     * @par Implemented as
     * - @ref R_GPT_Close()
     * - @ref R_AGT_Close()
     *
     * @param[in]   p_ctrl     Control block set in @ref timer_api_t::open call for this timer.
     */
    fsp_err_t (* close)(timer_ctrl_t * const p_ctrl);
} timer_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_timer_instance
{
    timer_ctrl_t      * p_ctrl;        ///< Pointer to the control structure for this instance
    timer_cfg_t const * p_cfg;         ///< Pointer to the configuration structure for this instance
    timer_api_t const * p_api;         ///< Pointer to the API structure for this instance
} timer_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup TIMER_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
