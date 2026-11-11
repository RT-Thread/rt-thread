/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_RTC_API_H
#define R_RTC_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_TIMERS_INTERFACES
 * @defgroup RTC_API RTC Interface
 * @brief Interface for accessing the Realtime Clock.
 *
 *
 * @section RTC_API_Summary Summary
 * The RTC Interface is for configuring Real Time Clock (RTC) functionality including alarm, periodic notification and
 * error adjustment.
 *
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Use of time structure, tm */
#include <time.h>

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
#ifndef BSP_OVERRIDE_RTC_EVENT_T

/** Events that can trigger a callback function */
typedef enum e_rtc_event
{
    RTC_EVENT_ALARM_IRQ,               ///< Real Time Clock ALARM 0 IRQ
    RTC_EVENT_ALARM1_IRQ,              ///< Real Time Clock ALARM 1 IRQ
    RTC_EVENT_PERIODIC_IRQ,            ///< Real Time Clock PERIODIC IRQ
} rtc_event_t;
#endif

/** RTC alarm channel */
typedef enum e_rtc_alarm_channel
{
    RTC_ALARM_CHANNEL_0,
    RTC_ALARM_CHANNEL_1,
} rtc_alarm_channel_t;

/** Callback function parameter data */
typedef struct st_rtc_callback_args
{
    rtc_event_t event;                 ///< The event can be used to identify what caused the callback (compare match or error).
    void      * p_context;             ///< Placeholder for user data.
} rtc_callback_args_t;

/** Clock source for the RTC block */
typedef enum e_rtc_count_source
{
    RTC_CLOCK_SOURCE_SUBCLK  = 0,      ///< Sub-clock oscillator
    RTC_CLOCK_SOURCE_LOCO    = 1,      ///< Low power On Chip Oscillator
    RTC_CLOCK_SOURCE_MAINCLK = 2       ///< Main clock oscillator
} rtc_clock_source_t;

/** RTC run state */
typedef enum e_rtc_status
{
    RTC_STATUS_STOPPED = 0,            ///< RTC counter is stopped
    RTC_STATUS_RUNNING = 1             ///< RTC counter is running
} rtc_status_t;

/** Time error adjustment settings */
typedef enum e_rtc_error_adjustment
{
    RTC_ERROR_ADJUSTMENT_NONE               = 0, ///< Adjustment is not performed
    RTC_ERROR_ADJUSTMENT_ADD_PRESCALER      = 1, ///< Adjustment is performed by the addition to the prescaler
    RTC_ERROR_ADJUSTMENT_SUBTRACT_PRESCALER = 2, ///< Adjustment is performed by the subtraction from the prescaler
} rtc_error_adjustment_t;

/** Time error adjustment mode settings */
typedef enum e_rtc_error_adjustment_mode
{
    RTC_ERROR_ADJUSTMENT_MODE_MANUAL    = 0, ///< Adjustment mode is set to manual
    RTC_ERROR_ADJUSTMENT_MODE_AUTOMATIC = 1, ///< Adjustment mode is set to automatic
} rtc_error_adjustment_mode_t;

/** Time error adjustment period settings */
typedef enum e_rtc_error_adjustment_period
{
    RTC_ERROR_ADJUSTMENT_PERIOD_1_MINUTE  = 0, ///< Adjustment period is set to every one minute
    RTC_ERROR_ADJUSTMENT_PERIOD_10_SECOND = 1, ///< Adjustment period is set to every ten second
    RTC_ERROR_ADJUSTMENT_PERIOD_NONE      = 2, ///< Adjustment period not supported in manual mode
    RTC_ERROR_ADJUSTMENT_PERIOD_20_SECOND = 3, ///< Adjustment period is set to every twenty seconds
} rtc_error_adjustment_period_t;

/** Time error adjustment value configuration */
typedef struct st_rtc_error_adjustment_cfg
{
    rtc_error_adjustment_mode_t   adjustment_mode;   ///< Automatic Adjustment Enable/Disable
    rtc_error_adjustment_period_t adjustment_period; ///< Error Adjustment period
    rtc_error_adjustment_t        adjustment_type;   ///< Time error adjustment setting
    uint32_t adjustment_value;                       ///< Value of the prescaler for error adjustment
} rtc_error_adjustment_cfg_t;

#ifndef BSP_OVERRIDE_RTC_PERIODIC_IRQ_SELECT_T

/** Periodic Interrupt select */
typedef enum e_rtc_periodic_irq_select
{
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_256_SECOND = 6,  ///< A periodic irq is generated every 1/256 second
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_128_SECOND = 7,  ///< A periodic irq is generated every 1/128 second
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_64_SECOND  = 8,  ///< A periodic irq is generated every 1/64 second
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_32_SECOND  = 9,  ///< A periodic irq is generated every 1/32 second
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_16_SECOND  = 10, ///< A periodic irq is generated every 1/16 second
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_8_SECOND   = 11, ///< A periodic irq is generated every 1/8 second
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_4_SECOND   = 12, ///< A periodic irq is generated every 1/4 second
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_2_SECOND   = 13, ///< A periodic irq is generated every 1/2 second
    RTC_PERIODIC_IRQ_SELECT_1_SECOND            = 14, ///< A periodic irq is generated every 1 second
    RTC_PERIODIC_IRQ_SELECT_2_SECOND            = 15, ///< A periodic irq is generated every 2 seconds
    RTC_PERIODIC_IRQ_SELECT_1_MINUTE            = 16, ///< A periodic irq is generated every 1 minute
    RTC_PERIODIC_IRQ_SELECT_1_HOUR              = 17, ///< A periodic irq is generated every 1 hour
    RTC_PERIODIC_IRQ_SELECT_1_DAY               = 18, ///< A periodic irq is generated every 1 day
    RTC_PERIODIC_IRQ_SELECT_1_MONTH             = 19, ///< A periodic irq is generated every 1 month
} rtc_periodic_irq_select_t;
#endif

#ifndef BSP_OVERRIDE_RTC_TIME_CAPTURE_SOURCE_T

/** Time capture trigger source */
typedef enum e_rtc_time_capture_source
{
    RTC_TIME_CAPTURE_SOURCE_DISABLED    = 0, ///< Disable trigger
    RTC_TIME_CAPTURE_SOURCE_PIN_RISING  = 1, ///< Rising edge pin trigger
    RTC_TIME_CAPTURE_SOURCE_PIN_FALLING = 2, ///< Falling edge pin trigger
    RTC_TIME_CAPTURE_SOURCE_PIN_BOTH    = 3, ///< Both edges pin trigger
    RTC_TIME_CAPTURE_SOURCE_SOFTWARE    = 4, ///< Software trigger
    RTC_TIME_CAPTURE_SOURCE_ELC_EVENT   = 5, ///< ELC event trigger
} rtc_time_capture_source_t;
#endif

/** Time capture trigger mode */
typedef enum e_rtc_time_capture_mode
{
    RTC_TIME_CAPTURE_MODE_CONTINUOUS = 0, ///< Continuous capturing to all capturing channels
    RTC_TIME_CAPTURE_MODE_ONE_SHOT   = 1, ///< Single capture to a particular channel
} rtc_time_capture_mode_t;

/** Time capture noise filter control */
typedef enum e_rtc_time_capture_noise_filter
{
    RTC_TIME_CAPTURE_NOISE_FILTER_OFF             = 0, ///< Turn noise filter off
    RTC_TIME_CAPTURE_NOISE_FILTER_ON              = 2, ///< Turn noise filter on (count source)
    RTC_TIME_CAPTURE_NOISE_FILTER_ON_DIVIDER_32   = 3, ///< Turn noise filter on (count source by divided by 32)
    RTC_TIME_CAPTURE_NOISE_FILTER_ON_DIVIDER_4096 = 4, ///< Turn noise filter on (count source by divided by 4096)
    RTC_TIME_CAPTURE_NOISE_FILTER_ON_DIVIDER_8192 = 5, ///< Turn noise filter on (count source by divided by 8192)
} rtc_time_capture_noise_filter_t;

/** Date and time structure defined in C standard library <time.h> */
typedef struct tm rtc_time_t;

#ifndef BSP_OVERRIDE_RTC_ALARM_TIME_T

/** Alarm time setting structure */
typedef struct st_rtc_alarm_time
{
    rtc_time_t          time;            ///< Time structure
    bool                sec_match;       ///< Enable the alarm based on a match of the seconds field
    bool                min_match;       ///< Enable the alarm based on a match of the minutes field
    bool                hour_match;      ///< Enable the alarm based on a match of the hours field
    bool                mday_match;      ///< Enable the alarm based on a match of the days field
    bool                mon_match;       ///< Enable the alarm based on a match of the months field
    bool                year_match;      ///< Enable the alarm based on a match of the years field
    bool                dayofweek_match; ///< Enable the alarm based on a match of the dayofweek field
    bool                sunday_match;    ///< Enable the alarm on Sunday
    bool                monday_match;    ///< Enable the alarm on Monday
    bool                tuesday_match;   ///< Enable the alarm on Tuesday
    bool                wednesday_match; ///< Enable the alarm on Wednesday
    bool                thursday_match;  ///< Enable the alarm on Thursday
    bool                friday_match;    ///< Enable the alarm on Friday
    bool                saturday_match;  ///< Enable the alarm on Saturday
    rtc_alarm_channel_t channel;         ///< Select alarm 0 or alarm 1
} rtc_alarm_time_t;
#endif

/** Time capture configuration structure */
typedef struct st_rtc_time_capture
{
    rtc_time_t                      time;         ///< Time structure
    uint8_t                         channel;      ///< Capture channel
    rtc_time_capture_source_t       source;       ///< Trigger source
    rtc_time_capture_noise_filter_t noise_filter; ///< Noise filter
    rtc_time_capture_mode_t         mode;         ///< Capture mode
} rtc_time_capture_t;

/** RTC Information Structure for information returned by  infoGet() */
typedef struct st_rtc_info
{
    rtc_clock_source_t clock_source;   ///< Clock source for the RTC block
    rtc_status_t       status;         ///< RTC run status
} rtc_info_t;

/** User configuration structure, used in open function */
typedef struct st_rtc_cfg
{
    rtc_clock_source_t clock_source;                    ///< Clock source for the RTC block
    uint32_t           freq_compare_value;              ///< The frequency comparison value
    rtc_error_adjustment_cfg_t const * const p_err_cfg; ///< Pointer to Error Adjustment configuration
    uint8_t   alarm_ipl;                                ///< Alarm interrupt priority
    IRQn_Type alarm_irq;                                ///< Alarm interrupt vector
    uint8_t   periodic_ipl;                             ///< Periodic interrupt priority
    IRQn_Type periodic_irq;                             ///< Periodic interrupt vector
    uint8_t   carry_ipl;                                ///< Carry interrupt priority
    IRQn_Type carry_irq;                                ///< Carry interrupt vector
    void (* p_callback)(rtc_callback_args_t * p_args);  ///< Called from the ISR.
    void       * p_context;                             ///< User defined context passed into callback function.
    void const * p_extend;                              ///< RTC hardware dependant configuration.
} rtc_cfg_t;

/** RTC control block.  Allocate an instance specific control block to pass into the RTC API calls.
 */
typedef void rtc_ctrl_t;

/** RTC driver structure. General RTC functions implemented at the HAL layer follow this API. */
typedef struct st_rtc_api
{
    /** Open the RTC driver.
     *
     * @param[in] p_ctrl     Pointer to RTC device handle
     * @param[in] p_cfg      Pointer to the configuration structure
     */
    fsp_err_t (* open)(rtc_ctrl_t * const p_ctrl, rtc_cfg_t const * const p_cfg);

    /** Close the RTC driver.
     *
     * @param[in] p_ctrl     Pointer to RTC device handle.
     */
    fsp_err_t (* close)(rtc_ctrl_t * const p_ctrl);

    /** Sets the RTC clock source.
     *
     * @param[in] p_ctrl     Pointer to RTC device handle
     */
    fsp_err_t (* clockSourceSet)(rtc_ctrl_t * const p_ctrl);

    /** Set the calendar time and start the calendar counter
     *
     * @param[in] p_ctrl      Pointer to RTC device handle
     * @param[in] p_time      Pointer to a time structure that contains the time to set
     */
    fsp_err_t (* calendarTimeSet)(rtc_ctrl_t * const p_ctrl, rtc_time_t * const p_time);

    /** Get the calendar time.
     *
     * @param[in] p_ctrl      Pointer to RTC device handle
     * @param[out] p_time     Pointer to a time structure that contains the time to get
     */
    fsp_err_t (* calendarTimeGet)(rtc_ctrl_t * const p_ctrl, rtc_time_t * const p_time);

    /** Set the calendar alarm time and enable the alarm interrupt.
     *
     * @param[in] p_ctrl                 Pointer to RTC device handle
     * @param[in] p_alarm                Pointer to an alarm structure that contains the alarm time to set
     */
    fsp_err_t (* calendarAlarmSet)(rtc_ctrl_t * const p_ctrl, rtc_alarm_time_t * const p_alarm);

    /** Get the calendar alarm time.
     *
     * @param[in] p_ctrl       Pointer to RTC device handle
     * @param[out] p_alarm     Pointer to an alarm structure to fill up with the alarm time
     */
    fsp_err_t (* calendarAlarmGet)(rtc_ctrl_t * const p_ctrl, rtc_alarm_time_t * const p_alarm);

    /** Set the periodic irq rate
     *
     * @param[in] p_ctrl       Pointer to RTC device handle
     * @param[in] rate         Rate of periodic interrupts
     */
    fsp_err_t (* periodicIrqRateSet)(rtc_ctrl_t * const p_ctrl, rtc_periodic_irq_select_t const rate);

    /** Set time error adjustment.
     *
     *
     * @param[in]  p_ctrl        Pointer to control handle structure
     * @param[in]  err_adj_cfg   Pointer to the Error Adjustment Config
     */
    fsp_err_t (* errorAdjustmentSet)(rtc_ctrl_t * const p_ctrl, rtc_error_adjustment_cfg_t const * const err_adj_cfg);

    /**
     * Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Pointer to the RTC control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated
     */
    fsp_err_t (* callbackSet)(rtc_ctrl_t * const p_ctrl, void (* p_callback)(rtc_callback_args_t *),
                              void * const p_context, rtc_callback_args_t * const p_callback_memory);

    /** Return the currently configure clock source for the RTC
     *
     *
     * @param[in]   p_ctrl       Pointer to control handle structure
     * @param[out]  p_rtc_info   Pointer to RTC information structure
     */
    fsp_err_t (* infoGet)(rtc_ctrl_t * const p_ctrl, rtc_info_t * const p_rtc_info);

    /** Config Time capture
     *
     * @param[in] p_ctrl             Pointer to RTC device handle
     * @param[in] p_time_capture     Pointer to a time capture structure that contains the configuration
     */
    fsp_err_t (* timeCaptureSet)(rtc_ctrl_t * const p_ctrl, rtc_time_capture_t * const p_time_capture);

    /** Get the capture time and clear bit status.
     *
     * @param[in]  p_ctrl             Pointer to RTC device handle
     * @param[out] p_time_capture     Pointer to a time capture structure to fill up with the time capture
     */
    fsp_err_t (* timeCaptureGet)(rtc_ctrl_t * const p_ctrl, rtc_time_capture_t * const p_time_capture);
} rtc_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rtc_instance
{
    rtc_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    rtc_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    rtc_api_t const * p_api;           ///< Pointer to the API structure for this instance
} rtc_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup RTC_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
