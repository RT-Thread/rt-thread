/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rtc_w.h"
#include "r_rtc_w_helper.h" 

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Divisors and Multipliers */
#define RTC_DIV_MUL_100                         (100)
#define RTC_DIV_400                             (400)

#define RTC_FIRST_DAY_OF_A_MONTH                (1)

/* Month : valid range between 0 to 11.*/
#define RTC_MONTHS_VALUE_MAX                    (11)
#define RTC_LAST_DAY_OF_LEAP_FEB_MONTH          (29)

/* Year : valid range between 0 to 1099.*/
#define RTC_YEAR_VALUE_MIN                      (0)
#define RTC_YEAR_VALUE_MAX                      (1099)

/* Seconds : valid range between 0 to 59.*/
#define RTC_SECONDS_VALUE_MAX                   (59)

/* Minute : valid range between 0 to 59. */
#define RTC_MINUTES_VALUE_MAX                   (59)

/* Hours : valid range between 0 to 23. */
#define RTC_HOURS_VALUE_MAX                     (23)

/* Macro definitions for February and March months */
#define RTC_FEBRUARY_MONTH                      (1U)
#define RTC_MARCH_MONTH                         (2U)

/* As per HW manual, value of Month is between 1 to 12.
 * But as per C standards, tm_month is between 0 to 11.*/
#define RTC_TIME_H_MONTH_WDAY_OFFSET            (1)

/* As per HW manual, value of Year is between 1900 to 2999.
 * But as per C standards, tm_year is years since 1900.*/
#define RTC_TIME_H_YEAR_OFFSET                  (1900)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * rtc_prv_ns_callback)(rtc_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile rtc_prv_ns_callback)(rtc_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

#if RTC_W_CFG_PARAM_CHECKING_ENABLE

static fsp_err_t r_rtc_time_and_date_validate(rtc_time_t * const p_time);
static fsp_err_t r_rtc_time_validate(rtc_time_t * const p_time);
static fsp_err_t r_rtc_date_validate(rtc_time_t * const p_time);
static fsp_err_t r_rtc_alarm_time_and_date_validate(rtc_alarm_time_t * const p_alarm);
static fsp_err_t r_rtc_alarm_time_validate(rtc_alarm_time_t * const p_alarm);
static fsp_err_t r_rtc_alarm_date_validate(rtc_alarm_time_t * const p_alarm);
static fsp_err_t r_rtc_month_and_year_validate(uint32_t year, uint32_t month);
static fsp_err_t r_rtc_monthday_validate(uint32_t day_of_month, uint32_t * num_days_month, uint32_t month,
                                         uint32_t year);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
rtc_w_instance_ctrl_t * g_p_rtc_w_ctrl = NULL;

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/** RTC Implementation of Real Time Clock  */
const rtc_api_t g_rtc_on_rtc_w =
{
    .open               = R_RTC_W_Open,
    .close              = R_RTC_W_Close,
    .clockSourceSet     = R_RTC_W_ClockSourceSet,
    .calendarTimeGet    = R_RTC_W_CalendarTimeGet,
    .calendarTimeSet    = R_RTC_W_CalendarTimeSet,
    .calendarAlarmGet   = R_RTC_W_CalendarAlarmGet,
    .calendarAlarmSet   = R_RTC_W_CalendarAlarmSet,
    .periodicIrqRateSet = R_RTC_W_PeriodicIrqRateSet,
    .infoGet            = R_RTC_W_InfoGet,
    .errorAdjustmentSet = R_RTC_W_ErrorAdjustmentSet,
    .callbackSet        = R_RTC_W_CallbackSet,
    .timeCaptureSet     = R_RTC_W_TimeCaptureSet,
    .timeCaptureGet     = R_RTC_W_TimeCaptureGet,
};

#if RTC_W_CFG_PARAM_CHECKING_ENABLE

/* Number of days in each months start from January to December */
static const uint8_t days_in_months[12] = {31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};
#endif

/*******************************************************************************************************************//**
 * @addtogroup RTC_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Opens and configures the RTC driver module. Implements @ref rtc_api_t::open.
 * @note To start the RTC @ref R_RTC_W_CalendarTimeZoneSet and @ref R_RTC_W_CalendarTimeSet must be called at least once.
 *       R_RTC_W_Open should be called once globally.
 *
 * Example:
 * @snippet r_rtc_w_example.c R_RTC_W_Open
 *
 * @retval FSP_SUCCESS                   Initialization was successful and RTC has started.
 * @retval FSP_ERR_ASSERTION             Invalid p_ctrl or p_cfg pointer.
 * @retval FSP_ERR_ALREADY_OPEN          Module is already open.
 * @retval FSP_ERR_INVALID_HW_CONDITION  Invalid Low-Power clock selected.
 *********************************`*************************************************************************************/
fsp_err_t R_RTC_W_Open (rtc_ctrl_t * const p_ctrl, rtc_cfg_t const * const p_cfg)
{
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;
    fsp_err_t               err             = FSP_SUCCESS;

    /* Parameter checking */
#if RTC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ERROR_RETURN(RTC_W_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    if (g_p_rtc_w_ctrl)
    {
        return FSP_ERR_ALREADY_OPEN;
    }

    /* Save the module's configuration. */
    p_instance_ctrl->p_cfg = p_cfg;
    rtc_extended_cfg_t const * p_extend = p_instance_ctrl->p_cfg->p_extend;

    /* init lock for shared Calendar time data */
    err = RTC_W_LOCK_INIT(p_instance_ctrl);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    /** Mark driver as open by initializing it to "RTC" in its ASCII equivalent. */
    p_instance_ctrl->open = RTC_W_OPEN;

    g_p_rtc_w_ctrl = p_instance_ctrl;

    FSP_PARAMETER_NOT_USED(p_extend);

    return err;
}

/*******************************************************************************************************************//**
 * Close the RTC driver.
 * Implements @ref rtc_api_t::close
 *
 * @retval FSP_SUCCESS          De-Initialization was successful and RTC driver closed.
 * @retval FSP_ERR_ASSERTION    Invalid p_ctrl.
 * @retval FSP_ERR_NOT_OPEN     Driver not open already for close.
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_Close (rtc_ctrl_t * const p_ctrl)
{
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;

    /* Parameter checking */
#if RTC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    rtc_extended_cfg_t  * p_extend        = (rtc_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    FSP_PARAMETER_NOT_USED(p_extend);

    if (g_p_rtc_w_ctrl)
    {
        p_instance_ctrl->p_cfg = NULL;
    }
    else
    {
        return FSP_ERR_NOT_OPEN;
    }

    g_p_rtc_w_ctrl = NULL;

    p_instance_ctrl->open = 0U;

    RTC_W_LOCK_DEINIT(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Sets the RTC clock source. Implements @ref rtc_api_t::clockSourceSet.
 *
 * @retval FSP_ERR_UNSUPPORTED       Clock source is the LP clock and which is selected during System Init.
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_ClockSourceSet (rtc_ctrl_t * const p_ctrl)
{
#if RTC_W_CFG_PARAM_CHECKING_ENABLE
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Set the calendar time.
 *
 * Implements @ref rtc_api_t::calendarTimeSet.
 *
 * @retval FSP_SUCCESS              Calendar time set operation was successful.
 * @retval FSP_ERR_ASSERTION        Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN         Driver not open already for operation.
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_CalendarTimeSet (rtc_ctrl_t * const p_ctrl, rtc_time_t * const p_time)
{
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;

#if RTC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_time);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Verify the seconds, minutes, hours, year ,day of the week, day of the month, month and year are valid values */
    FSP_ERROR_RETURN(FSP_SUCCESS == r_rtc_time_and_date_validate(p_time), FSP_ERR_INVALID_ARGUMENT);
#endif
    
	__time64_t  corrtime, now;
    RTC_W_LOCK_TAKE(p_instance_ctrl);
	ra6w1_mktime64(p_time, &corrtime); /* convert local time struct tm to GMT time64 */
	ra6w1_time64(&corrtime, &now);	    /* set GMT time */
    RTC_W_LOCK_GIVE(p_instance_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Get the calendar time.
 *
 * Implements @ref rtc_api_t::calendarTimeGet
 *
 * @retval FSP_SUCCESS              Calendar time get operation was successful.
 * @retval FSP_ERR_ASSERTION        Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN         Driver not open already for operation.
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_CalendarTimeGet (rtc_ctrl_t * const p_ctrl, rtc_time_t * const p_time)
{
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;

#if RTC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_time);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

	__time64_t  now;

    RTC_W_LOCK_TAKE(p_instance_ctrl);
	ra6w1_time64(NULL, &now);
	*p_time = *(struct tm *) ra6w1_localtime64(&now);
    RTC_W_LOCK_GIVE(p_instance_ctrl);
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set the calendar alarm time.
 *
 * Implements @ref rtc_api_t::calendarAlarmSet.
 *
 * @retval FSP_ERR_UNSUPPORTED
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_CalendarAlarmSet (rtc_ctrl_t * const p_ctrl, rtc_alarm_time_t * const p_alarm)
{
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;

#if RTC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_alarm);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Verify the seconds, minutes, hours, year ,day of the week, day of the month and month are valid values */
    FSP_ERROR_RETURN(FSP_SUCCESS == r_rtc_alarm_time_and_date_validate(p_alarm), FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(p_alarm);
#endif

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Get the calendar alarm time.
 *
 * Implements @ref rtc_api_t::calendarAlarmGet
 *
 * @retval FSP_ERR_UNSUPPORTED
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_CalendarAlarmGet (rtc_ctrl_t * const p_ctrl, rtc_alarm_time_t * const p_alarm)
{
#if RTC_W_CFG_PARAM_CHECKING_ENABLE
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_alarm);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_alarm);
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Set the periodic interrupt rate and enable periodic interrupt. Periodic interrupts refer to the recurring
 * interrupts when a unit of time rolls over.
 *
 * Implements @ref rtc_api_t::periodicIrqRateSet
 *
 * @retval FSP_ERR_UNSUPPORTED
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_PeriodicIrqRateSet (rtc_ctrl_t * const p_ctrl, rtc_periodic_irq_select_t const rate)
{
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;

#if RTC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(rate);
#endif

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Get RTC clock source and running status information and store it in provided pointer p_rtc_info
 *
 * Implements @ref rtc_api_t::infoGet
 *
 * @retval FSP_ERR_UNSUPPORTED
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_InfoGet (rtc_ctrl_t * const p_ctrl, rtc_info_t * const p_rtc_info)
{
#if RTC_W_CFG_PARAM_CHECKING_ENABLE
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_rtc_info);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_rtc_info);
#endif

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * This function sets time error adjustment
 *
 * @retval FSP_ERR_UNSUPPORTED          Time error adjustment functionality is not supported.
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_ErrorAdjustmentSet (rtc_ctrl_t * const p_ctrl, rtc_error_adjustment_cfg_t const * const err_adj_cfg)
{
#if RTC_W_CFG_PARAM_CHECKING_ENABLE
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != err_adj_cfg);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(err_adj_cfg);
#endif

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Updates the user callback and has option of providing memory for callback structure.
 *
 * Implements rtc_api_t::callbackSet
 *
 * @retval FSP_ERR_UNSUPPORTED
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_CallbackSet (rtc_ctrl_t * const          p_ctrl,
                             void (                    * p_callback)(rtc_callback_args_t *),
                             void * const          p_context,
                             rtc_callback_args_t * const p_callback_memory)
{
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;

#if (RTC_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_callback);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(p_callback);
    FSP_PARAMETER_NOT_USED(p_context);
    FSP_PARAMETER_NOT_USED(p_callback_memory);
#endif

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Set time capture configuration for the provided channel.
 *
 * Implements @ref rtc_api_t::timeCaptureSet
 *
 * @retval FSP_ERR_UNSUPPORTED
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_TimeCaptureSet (rtc_ctrl_t * const p_ctrl, rtc_time_capture_t * const p_time_capture)
{
#if BSP_FEATURE_RTC_CAPTURE_CHANNELS
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;
#if (RTC_W_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_time_capture);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(BSP_FEATURE_RTC_CAPTURE_CHANNELS > p_time_capture->channel, FSP_ERR_INVALID_CHANNEL);
#endif
    rtc_extended_cfg_t const * p_extend = p_instance_ctrl->p_cfg->p_extend;

    FSP_PARAMETER_NOT_USED(p_extend);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_time_capture);
#endif
    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * Get time capture value of the provided channel.
 *
 * Implements @ref rtc_api_t::timeCaptureGet
 *
 * @retval FSP_ERR_UNSUPPORTED
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_TimeCaptureGet (rtc_ctrl_t * const p_ctrl, rtc_time_capture_t * const p_time_capture)
{
#if BSP_FEATURE_RTC_CAPTURE_CHANNELS
#if (RTC_W_CFG_PARAM_CHECKING_ENABLE)
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_time_capture);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(BSP_FEATURE_RTC_CAPTURE_CHANNELS > p_time_capture->channel, FSP_ERR_INVALID_CHANNEL);
#endif
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_time_capture);
#endif
    return FSP_ERR_UNSUPPORTED;
}

fsp_err_t R_RTC_W_CalendarBootTimeGet (rtc_ctrl_t * const p_ctrl, rtc_time_t * const p_time)
{
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;
#if RTC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_time);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

	__time64_t boottime;
    RTC_W_LOCK_TAKE(p_instance_ctrl);
    __boottime(&boottime);
	*p_time = *(struct tm *) ra6w1_localtime64(&boottime);
    RTC_W_LOCK_GIVE(p_instance_ctrl);
    return FSP_SUCCESS;
}

fsp_err_t R_RTC_W_CalendarTimeZoneSet (rtc_ctrl_t * const p_ctrl, long * p_timezone)
{
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;
#if RTC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_timezone);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    RTC_W_LOCK_TAKE(p_instance_ctrl);
    ra6w1_SetTzoff(*p_timezone);
    RTC_W_LOCK_GIVE(p_instance_ctrl);

    return FSP_SUCCESS;
}

fsp_err_t R_RTC_W_CalendarTimeZoneGet (rtc_ctrl_t * const p_ctrl, long * p_timezone)
{
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;
#if RTC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_timezone);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    RTC_W_LOCK_TAKE(p_instance_ctrl);
    *p_timezone = ra6w1_Tzoff();
    RTC_W_LOCK_GIVE(p_instance_ctrl);

    return FSP_SUCCESS;
}

fsp_err_t R_RTC_W_CalendarGMTTimeGet (rtc_ctrl_t * const p_ctrl, rtc_time_t * const p_time)
{
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;
#if RTC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_time);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

	__time64_t  now;
    RTC_W_LOCK_TAKE(p_instance_ctrl);
    ra6w1_time64(NULL, &now);
    *p_time = *(struct tm *) ra6w1_gmtime64(&now);
    RTC_W_LOCK_GIVE(p_instance_ctrl);

    return FSP_SUCCESS;
}

fsp_err_t R_RTC_W_CalendarTimePassed (rtc_ctrl_t * const p_ctrl, rtc_time_t * const p_time, bool * p_comp)
{
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;
#if RTC_W_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_time);
    FSP_ASSERT(NULL != p_comp);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    __time64_t now, diff;

    RTC_W_LOCK_TAKE(p_instance_ctrl);
    ra6w1_time64(NULL, &now); /* current time */
    now += (__time64_t) ra6w1_Tzoff();
    ra6w1_mktime64(p_time, &diff); /* given time */
    RTC_W_LOCK_GIVE(p_instance_ctrl);

    if (now < diff) {
        *p_comp = 0;
    } else {
        *p_comp = 1;
    }

    return FSP_SUCCESS;
}

fsp_err_t R_RTC_W_Time2Str (rtc_ctrl_t * const p_ctrl, rtc_time_t * const p_time, char * const str_buff_ptr,
                                             size_t maxsize,      char const * format)
{
#if RTC_W_CFG_PARAM_CHECKING_ENABLE
    rtc_w_instance_ctrl_t * p_instance_ctrl = (rtc_w_instance_ctrl_t *) p_ctrl;
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_time);
    FSP_ASSERT(NULL != str_buff_ptr);
    FSP_ASSERT(0 != maxsize);
    FSP_ASSERT(NULL != format);
    FSP_ERROR_RETURN(RTC_W_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif
    size_t p_size;
    p_size = ra6w1_strftime(str_buff_ptr, maxsize, format, p_time);

    FSP_ASSERT(0 != p_size);

    return FSP_SUCCESS;
}

rtc_ctrl_t * R_RTC_W_GetCtrl(void)
{
    return g_p_rtc_w_ctrl;
}

/*******************************************************************************************************************//**
 * @} (end addtpgroup RTC_W)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if RTC_W_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Validate time and date fields of time parameter fields.
 * Checking if seconds, minutes, hours are valid values by calling sub-function time validate.
 * Checking if year, month, day of the week and day of a month are valid values by calling sub-function
 * date validate.
 *
 * @param[in]  p_time                     Pointer to rtc_time_t
 * @retval FSP_SUCCESS                    Validation successful
 * @retval FSP_ERR_INVALID_ARGUMENT       Invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static fsp_err_t r_rtc_time_and_date_validate (rtc_time_t * const p_time)
{
    fsp_err_t err = FSP_SUCCESS;
    err = r_rtc_time_validate(p_time);
    FSP_ERROR_RETURN(err == FSP_SUCCESS, err);
    err = r_rtc_date_validate(p_time);
    FSP_ERROR_RETURN(err == FSP_SUCCESS, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Validate time fields of time type parameter
 * Checking for the seconds, minutes, hours values for valid specified range.
 * Seconds 0 to 59.
 * Minutes 0 to 59.
 * Hours   0 to 23.
 *
 * @param[in]  p_time                     Pointer to rtc_time_t
 * @retval FSP_SUCCESS                    Validation successful
 * @retval FSP_ERR_INVALID_ARGUMENT       Invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static fsp_err_t r_rtc_time_validate (rtc_time_t * p_time)
{
    fsp_err_t err;
    err = FSP_SUCCESS;
    if ((p_time->tm_sec < 0) || (p_time->tm_sec > RTC_SECONDS_VALUE_MAX) ||
        (p_time->tm_min < 0) || (p_time->tm_min > RTC_MINUTES_VALUE_MAX) ||
        (p_time->tm_hour < 0) || (p_time->tm_hour > RTC_HOURS_VALUE_MAX))
    {
        err = FSP_ERR_INVALID_ARGUMENT;
    }

    return err;
}

/*******************************************************************************************************************//**
 * Validate date fields of time parameter and set day of a Week using Zeller's congruence.
 *
 * Day of week between 0 to 6. There's a mismatch between hardware configuration,
 * as we have a value from 1 through 7 (in BCD) for Day of week register in the RTC.
 * This difference will be taken care in the Set and Get functions.
 *
 * Day of month between 1 to 31.
 *
 * Month between 0 to 11 as per standard time.h. There's a mismatch between hardware configuration,
 * as we have a value from 01 through 12 (in BCD) for Month Counter register in the RTC.
 * This difference will be taken care in the Set and Get functions.
 *
 * As per HW manual, value of Year is between 1900 to 2999, the RTC has a 1099 year calendar from 1900 to 2999.
 * But as per C standards, tm_year is years since 1900.
 * A sample year set in an application would be like time.tm_year = 2019-1900; (to set year 2019)
 * Since RTC API follows the Date and Time structure defined in C standard library <time.h>, the valid value of year is
 * between 0 and 1099, which will be internally converted to HW required value.
 *
 * @param[in]  p_time                     Pointer to rtc_time_t
 * @retval FSP_SUCCESS                    Validation successful
 * @retval FSP_ERR_INVALID_ARGUMENT       Invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static fsp_err_t r_rtc_date_validate (rtc_time_t * const p_time)
{
    uint32_t day_of_week;
    uint32_t num_days_month;
    uint32_t day_of_month;
    uint32_t month;
    uint32_t year;
    uint32_t k_year;
    uint32_t j_year;

    day_of_month = (uint32_t) p_time->tm_mday;
    month        = (uint32_t) p_time->tm_mon;
    year         = (uint32_t) p_time->tm_year;

    /* Checking the error condition for year and months values
     * Here valid value of year is between 0 to 1099 and for month 0 to 11 */
    fsp_err_t err = FSP_SUCCESS;
    err = r_rtc_month_and_year_validate(year, month);
    FSP_ERROR_RETURN(err == FSP_SUCCESS, err);

    /*For particular valid month, number of days in a month is updated */
    num_days_month = days_in_months[month];

    /* Checking for February month and Conditions for Leap year.
     * Year needs to be translated from time.h format */
    year += RTC_TIME_H_YEAR_OFFSET;
    err   = r_rtc_monthday_validate(day_of_month, &num_days_month, month, year);
    FSP_ERROR_RETURN(err == FSP_SUCCESS, err);

    /* Month parameter valid values are 0 to 11 for January to December.
     * For Zeller's congruence formula below, adjust month to run from 3 to 14 for March to February */
    if (month < RTC_MARCH_MONTH)
    {
        month = (month + 12U);

        /* Adjust year if January or February*/
        --year;
    }

    month = month + RTC_TIME_H_MONTH_WDAY_OFFSET;

    /*For the Gregorian calendar, Zeller's congruence formulas is
     * h = ( q + [13(m+1)/5] + K + [K/4] + [J/4] + [5J])mod 7 (mod : modulo)
     * h is the day of the week , q is the day of the month,
     * m is the month (3 = March, 4 = April,..., 14 = February)
     * K is the year of the century (year % 100), J is the zero-based century (⌊ year/100 ⌋)
     * Day of week between 0 to 6 :- Saturday - Friday */
    k_year      = year % RTC_DIV_MUL_100;
    j_year      = year / RTC_DIV_MUL_100;
    day_of_week = day_of_month + ((13 * (month + 1)) / 5) + k_year + (k_year / 4) + (j_year / 4) + (5 * j_year);
    day_of_week = day_of_week % 7;

    /* We want day of week between 0 to 6 :- Sunday to Saturday */
    /* d = (h + 6)mod 7 (mod : modulo) */
    p_time->tm_wday = (int16_t) (day_of_week + 6U) % 7U;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Validate alarm time and date of alarm time type parameter
 * Checking if the seconds, minutes, hours are valid values, based on alarm enable bits.
 * Checking if year, month, day of the week and day of a month are valid values, based on alarm enable bits.
 * If alarm enable bit is set for year, month, and day of a month for valid range, Week of the day is
 * calculated and updated in alarm time.
 *
 * @param[in]  p_alarm_time               Pointer to rtc_alarm_time_t
 * @retval FSP_SUCCESS                    Validation successful
 * @retval FSP_ERR_INVALID_ARGUMENT       Invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static fsp_err_t r_rtc_alarm_time_and_date_validate (rtc_alarm_time_t * const p_alarm_time)
{
    fsp_err_t err = FSP_SUCCESS;
    err = r_rtc_alarm_time_validate(p_alarm_time);
    FSP_ERROR_RETURN(err == FSP_SUCCESS, err);
    err = r_rtc_alarm_date_validate(p_alarm_time);
    FSP_ERROR_RETURN(err == FSP_SUCCESS, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Validate alarm time fields of Alarm time type parameter
 * Checking if the seconds, minutes, hours value is in the valid specified range, based on alarm enable bits.
 * Seconds 0 to 59.
 * Minutes 0 to 59.
 * Hours   0 to 23.
 *
 * @param[in]  p_alarm_time               Pointer to rtc_alarm_time_t
 * @retval FSP_SUCCESS                    Validation successful
 * @retval FSP_ERR_INVALID_ARGUMENT       Invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static fsp_err_t r_rtc_alarm_time_validate (rtc_alarm_time_t * const p_alarm_time)
{
    fsp_err_t err;
    err = FSP_SUCCESS;
    if (((p_alarm_time->sec_match) &&
         ((p_alarm_time->time.tm_sec < 0) || (p_alarm_time->time.tm_sec > RTC_SECONDS_VALUE_MAX))) ||
        ((p_alarm_time->min_match) &&
         ((p_alarm_time->time.tm_min < 0) || (p_alarm_time->time.tm_min > RTC_MINUTES_VALUE_MAX))) ||
        ((p_alarm_time->hour_match) &&
         ((p_alarm_time->time.tm_hour < 0) || (p_alarm_time->time.tm_hour > RTC_HOURS_VALUE_MAX))))
    {
        err = FSP_ERR_INVALID_ARGUMENT;
    }

    return err;
}

/*******************************************************************************************************************//**
 * Validate alarm month and day of month of time type parameter
 * Checking if month and day of month value is in the valid specified range, based on alarm enable bits.
 * Month : 0 to 11.
 * Day of month  : 1 to 28/29/30/31.
 *
 * @param[in]  p_alarm                    Pointer to rtc_alarm_time_t
 * @retval FSP_SUCCESS                    Validation successful
 * @retval FSP_ERR_INVALID_ARGUMENT       Invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static fsp_err_t r_rtc_alarm_date_validate (rtc_alarm_time_t * const p_alarm)
{
    fsp_err_t err;
    err = FSP_SUCCESS;

    uint32_t num_days_month;
    uint32_t day_of_month;
    uint32_t month;
    uint32_t year;

    day_of_month = (uint32_t) p_alarm->time.tm_mday;
    month        = (uint32_t) p_alarm->time.tm_mon;

    /* Alarm on year time unit is not supported */
    year = (uint32_t) p_alarm->time.tm_year;

    err = r_rtc_month_and_year_validate(year, month);
    FSP_ERROR_RETURN(err == FSP_SUCCESS, err);

    if (p_alarm->mday_match)
    {
        /*For particular valid month, number of days in a month is updated */
        num_days_month = days_in_months[month];

        /* Checking for February month and Conditions for Leap year.
         * Year needs to be translated from time.h format */
        year += RTC_TIME_H_YEAR_OFFSET;
        err   = r_rtc_monthday_validate(day_of_month, &num_days_month, month, year);
        FSP_ERROR_RETURN(err == FSP_SUCCESS, err);
    }

    return err;
}

/*******************************************************************************************************************//**
 * Validates the year and month paremeters.
 *
 * @param[in]  year         Year parameter.
 * @param[in]  month        Month parameter.
 **********************************************************************************************************************/
static fsp_err_t r_rtc_month_and_year_validate (uint32_t year, uint32_t month)
{
    if ((year < RTC_YEAR_VALUE_MIN) || (year > RTC_YEAR_VALUE_MAX) ||
        (month < 0) || (month > RTC_MONTHS_VALUE_MAX))
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Validates the day of month paremeter and the number of total days in a month.
 *
 * @param[in]  day_of_month        Day of month parameter.
 * @param[in]  num_days_month      Total number of days in the month parameter.
 * @param[in]  month               Month parameter.
 * @param[in]  year                Year parameter.
 **********************************************************************************************************************/
static fsp_err_t r_rtc_monthday_validate (uint32_t   day_of_month,
                                          uint32_t * num_days_month,
                                          uint32_t   month,
                                          uint32_t   year)
{
    /* Checking for February month and Conditions for Leap year : Every fourth year is a leap year,
     * except for century-years (divisible by 100) which must be also divisible by 400. */
    if (RTC_FEBRUARY_MONTH == month)
    {
        if ((0 == (year % 4U)) && (((year % RTC_DIV_MUL_100) != 0) || (0 == (year % RTC_DIV_400))))
        {
            *num_days_month = RTC_LAST_DAY_OF_LEAP_FEB_MONTH;
        }
    }

    /* Checking for day of a month values for valid range */
    if ((day_of_month < RTC_FIRST_DAY_OF_A_MONTH) || (day_of_month > *num_days_month))
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    return FSP_SUCCESS;
}

#endif
