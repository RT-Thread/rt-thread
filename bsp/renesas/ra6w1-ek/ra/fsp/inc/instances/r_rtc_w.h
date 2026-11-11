/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_RTC_W_H
#define R_RTC_W_H

/*******************************************************************************************************************//**
 * @addtogroup RTC_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_rtc_w_cfg.h"
#include "r_rtc_api.h"
#include "r_rtc_w_helper.h"

#if (BSP_CFG_RTOS == 2)
#include "FreeRTOS.h"
#include "semphr.h"

#define RTC_W_LOCK_TYPE       SemaphoreHandle_t
#define RTC_W_LOCK_INIT(p_ctrl) \
    (((p_ctrl)->calendar_time_lock = xSemaphoreCreateMutex()) != NULL ? FSP_SUCCESS : FSP_ERR_OUT_OF_MEMORY)
#define RTC_W_LOCK_DEINIT(p_ctrl) \
    do { vSemaphoreDelete((p_ctrl)->calendar_time_lock); (p_ctrl)->calendar_time_lock = NULL; } while (0)
#define RTC_W_LOCK_TAKE(p_ctrl) \
    do { (void) xSemaphoreTake((p_ctrl)->calendar_time_lock, portMAX_DELAY); } while (0)
#define RTC_W_LOCK_GIVE(p_ctrl) \
    do { (void) xSemaphoreGive((p_ctrl)->calendar_time_lock); } while (0)
#elif (BSP_CFG_RTOS == 3)
#include <rtthread.h>

#define RTC_W_LOCK_TYPE       struct rt_mutex
#define RTC_W_LOCK_INIT(p_ctrl) \
    (rt_mutex_init(&(p_ctrl)->calendar_time_lock, "rtc", RT_IPC_FLAG_PRIO) == RT_EOK ? FSP_SUCCESS : FSP_ERR_OUT_OF_MEMORY)
#define RTC_W_LOCK_DEINIT(p_ctrl) \
    do { rt_mutex_detach(&(p_ctrl)->calendar_time_lock); } while (0)
#define RTC_W_LOCK_TAKE(p_ctrl) \
    do { (void) rt_mutex_take(&(p_ctrl)->calendar_time_lock, RT_WAITING_FOREVER); } while (0)
#define RTC_W_LOCK_GIVE(p_ctrl) \
    do { (void) rt_mutex_release(&(p_ctrl)->calendar_time_lock); } while (0)
#else
#define RTC_W_LOCK_TYPE       uint8_t
#define RTC_W_LOCK_INIT(p_ctrl) (FSP_ERR_UNSUPPORTED)
#define RTC_W_LOCK_DEINIT(p_ctrl) do { } while (0)
#define RTC_W_LOCK_TAKE(p_ctrl) do { } while (0)
#define RTC_W_LOCK_GIVE(p_ctrl) do { } while (0)
#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "RTC" in ASCII, used to determine if device is open. */
#define RTC_W_OPEN                                (0x00525444ULL)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** RTC extended configuration */
typedef struct st_rtc_extended_cfg
{
    uint32_t       reserved; ///< Reserved
} rtc_extended_cfg_t;

/** Channel control block. DO NOT INITIALIZE. Initialization occurs when @ref rtc_api_t::open is called */
typedef struct st_rtc_w_ctrl
{
    uint32_t          open;                     ///< Whether or not driver is open.
    const rtc_cfg_t * p_cfg;                    ///< Pointer to initial configurations.
    RTC_W_LOCK_TYPE      calendar_time_lock;    ///< Lock for shared Calendar time data.
} rtc_w_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rtc_api_t g_rtc_on_rtc_w;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_Open(rtc_ctrl_t * const p_ctrl, rtc_cfg_t const * const p_cfg);
fsp_err_t R_RTC_W_Close(rtc_ctrl_t * const p_ctrl);
fsp_err_t R_RTC_W_ClockSourceSet(rtc_ctrl_t * const p_ctrl);
fsp_err_t R_RTC_W_CalendarTimeSet(rtc_ctrl_t * const p_ctrl, rtc_time_t * const p_time);
fsp_err_t R_RTC_W_CalendarTimeGet(rtc_ctrl_t * const p_ctrl, rtc_time_t * const p_time);
fsp_err_t R_RTC_W_CalendarAlarmSet(rtc_ctrl_t * const p_ctrl, rtc_alarm_time_t * const p_alarm);
fsp_err_t R_RTC_W_CalendarAlarmGet(rtc_ctrl_t * const p_ctrl, rtc_alarm_time_t * const p_alarm);
fsp_err_t R_RTC_W_PeriodicIrqRateSet(rtc_ctrl_t * const p_ctrl, rtc_periodic_irq_select_t const rate);
fsp_err_t R_RTC_W_ErrorAdjustmentSet(rtc_ctrl_t * const p_ctrl, rtc_error_adjustment_cfg_t const * const err_adj_cfg);
fsp_err_t R_RTC_W_InfoGet(rtc_ctrl_t * const p_ctrl, rtc_info_t * const p_rtc_info);
fsp_err_t R_RTC_W_PDCEventConfig(rtc_ctrl_t * const p_ctrl, uint16_t pdc_evt_period);
fsp_err_t R_RTC_W_MotorEventConfig(rtc_ctrl_t * const p_ctrl, uint16_t motor_evt_period);
fsp_err_t R_RTC_W_CallbackSet(rtc_ctrl_t * const          p_ctrl,
                              void (                    * p_callback)(rtc_callback_args_t *),
                              void * const          p_context,
                              rtc_callback_args_t * const p_callback_memory);
fsp_err_t R_RTC_W_TimeCaptureSet(rtc_ctrl_t * const p_ctrl, rtc_time_capture_t * const p_time_capture);
fsp_err_t R_RTC_W_TimeCaptureGet(rtc_ctrl_t * const p_ctrl, rtc_time_capture_t * const p_time_capture);


/*******************************************************************************************************************//**
 * Get the system boot time.
 *
 * @param[in]  p_ctrl      Pointer to RTC device handle
 * @param[out] p_time      Pointer to a time structure that contains the boot time.
 *
 * @retval FSP_SUCCESS              Calendar Boot time get operation was successful.
 * @retval FSP_ERR_ASSERTION        Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN         Driver not open already for operation.
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_CalendarBootTimeGet (rtc_ctrl_t * const p_ctrl, rtc_time_t * const p_time);

/*******************************************************************************************************************//**
 * Set the timezone offset from GMT.
 *
 * @param[in]  p_ctrl          Pointer to RTC device handle
 * @param[in]  p_timezone      Pointer to a timezone to set (in seconds)
 *
 * @retval FSP_SUCCESS              Calendar TimeZone set operation was successful.
 * @retval FSP_ERR_ASSERTION        Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN         Driver not open already for operation.
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_CalendarTimeZoneSet (rtc_ctrl_t * const p_ctrl, long * p_timezone);

/*******************************************************************************************************************//**
 * Get the timezone offset from GMT.
 *
 * @param[in]  p_ctrl           Pointer to RTC device handle
 * @param[out]  p_timezone      Pointer to the current timezone (in seconds)
 *
 * @retval FSP_SUCCESS              Calendar TimeZone get operation was successful.
 * @retval FSP_ERR_ASSERTION        Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN         Driver not open already for operation.
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_CalendarTimeZoneGet (rtc_ctrl_t * const p_ctrl, long * p_timezone);

/*******************************************************************************************************************//**
 * Get the GMT calendar time.
 *
 * @param[in]   p_ctrl      Pointer to RTC device handle
 * @param[out]  p_time      Pointer to GMT time
 *
 * @retval FSP_SUCCESS              Calendar GMT time get operation was successful.
 * @retval FSP_ERR_ASSERTION        Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN         Driver not open already for operation.
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_CalendarGMTTimeGet (rtc_ctrl_t * const p_ctrl, rtc_time_t * const p_time);

/*******************************************************************************************************************//**
 * Compare a given time to the current time.
 *
 * @param[in]   p_ctrl      Pointer to RTC device handle
 * @param[in]   p_time      Pointer to the given time
 * @param[out]  p_comp      Set to 'true' if the given time already passed (in compare to current time) 
 *                          and to 'false' otherwise.
 *
 * @retval FSP_SUCCESS              Calendar Time Passed operation was successful.
 * @retval FSP_ERR_ASSERTION        Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN         Driver not open already for operation.
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_CalendarTimePassed (rtc_ctrl_t * const p_ctrl, rtc_time_t * const p_time, bool * p_comp);

/*******************************************************************************************************************//**
 * Convert rtc_time struct to a human readable string according to a given format (format example: "%Y.%m.%d %H:%M:%S")
 *
 * @param[in]   p_ctrl         Pointer to RTC device handle
 * @param[in]   p_time         Pointer to the time to convert to a string
 * @param[out]  str_buff_ptr   Buffer to contain a string converted from p_time
 * @param[out]  maxsize        Max size of str_buff_ptr
 * @param[in]   format         Format string
 *
 * @retval FSP_SUCCESS              Time to Str operation was successful.
 * @retval FSP_ERR_ASSERTION        Invalid input argument.
 * @retval FSP_ERR_NOT_OPEN         Driver not open already for operation.
 **********************************************************************************************************************/
fsp_err_t R_RTC_W_Time2Str (rtc_ctrl_t * const p_ctrl, rtc_time_t * const p_time, char * const str_buff_ptr, 
                                             size_t maxsize,      char const * format);

/*******************************************************************************************************************//**
 * Get RTC_W control block.
 * 
 * @retval   p_ctrl               Pointer to the RTC_W control block.
**********************************************************************************************************************/
rtc_ctrl_t * R_RTC_W_GetCtrl(void);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_RTC_W_H

/*******************************************************************************************************************//**
 * @} (end addtogroup RTC_W)
 **********************************************************************************************************************/
