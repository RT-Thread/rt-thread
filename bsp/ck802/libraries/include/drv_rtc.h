/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
 * @file     drv_rtc.h
 * @brief    header file for rtc driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef _CSI_RTC_H_
#define _CSI_RTC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <drv_common.h>
#include <time.h>

/// definition for rtc handle.
typedef void *rtc_handle_t;

/****** rtc specific error codes *****/
typedef enum {
    EDRV_RTC_TIME  = (EDRV_SPECIFIC + 1),      ///< timer data not supported
} drv_rtc_error_e;

/**
\brief RTC Status
*/
typedef struct {
    uint32_t active          : 1;        ///< rtc is running or not
} rtc_status_t;

/****** RTC Event *****/
typedef enum {
    RTC_EVENT_TIMER_INTRERRUPT  = 0   ///< generate interrupt
} rtc_event_e;

typedef void (*rtc_event_cb_t)(rtc_event_e event);  ///< Pointer to \ref rtc_event_cb_t : RTC Event call back.

/**
\brief RTC Device Driver Capabilities.
*/
typedef struct {
    uint32_t interrupt_mode          : 1;      ///< supports Interrupt mode
    uint32_t wrap_mode               : 1;      ///< supports wrap mode
} rtc_capabilities_t;

/**
  \brief       get rtc instance count.
  \return      rtc instance count
*/
int32_t csi_rtc_get_instance_count(void);

/**
  \brief       Initialize RTC Interface. 1. Initializes the resources needed for the RTC interface 2.registers event callback function
  \param[in]   idx  must not exceed return value of csi_rtc_get_instance_count()
  \param[in]   cb_event  Pointer to \ref rtc_event_cb_t
  \return      pointer to rtc instance
*/
rtc_handle_t csi_rtc_initialize(int32_t idx, rtc_event_cb_t cb_event);

/**
  \brief       De-initialize RTC Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle rtc handle to operate.
  \return      error code
*/
int32_t csi_rtc_uninitialize(rtc_handle_t handle);

/**
  \brief       Get driver capabilities.
  \param[in]   handle rtc handle to operate.
  \return      \ref rtc_capabilities_t
*/
rtc_capabilities_t csi_rtc_get_capabilities(rtc_handle_t handle);

/**
  \brief       Set RTC timer.
  \param[in]   handle rtc handle to operate.
  \param[in]   rtctime pointer to rtc time
  \return      error code
*/
int32_t csi_rtc_set_time(rtc_handle_t handle, const struct tm *rtctime);

/**
  \brief       Get RTC timer.
  \param[in]   handle rtc handle to operate.
  \param[in]   rtctime  pointer to rtc time
  \return      error code
*/
int32_t csi_rtc_get_time(rtc_handle_t handle, struct tm *rtctime);



/**
  \brief       Start RTC timer.
  \param[in]   handle rtc handle to operate.
  \return      error code
*/
int32_t csi_rtc_start(rtc_handle_t handle);

/**
  \brief       Stop RTC timer.
  \param[in]   handle rtc handle to operate.
  \return      error code
*/
int32_t csi_rtc_stop(rtc_handle_t handle);

/**
  \brief       config rtc mode.
  \param[in]   handle rtc handle to operate.
  \return      error code
*/
//int32_t drv_rtc_config (rtc_handle_t handle/*,rtc_mode_e mode*/);

/**
  \brief       Get RTC status.
  \param[in]   handle rtc handle to operate.
  \return      RTC status \ref rtc_status_t
*/
rtc_status_t csi_rtc_get_status(rtc_handle_t handle);

/**
  \brief       config RTC timer.
  \param[in]   handle rtc handle to operate.
  \param[in]   rtctime time to wake up
  \return      error code
*/
int32_t csi_rtc_timer_config(rtc_handle_t handle, const struct tm *rtctime);

/**
  \brief       disable or enable RTC timer.
  \param[in]   handle rtc handle to operate.
  \param[in]   en set 1 enable for rtc timer
  \return      error code
*/
int32_t csi_rtc_timer_enable(rtc_handle_t handle, uint8_t en);




#ifdef __cplusplus
}
#endif

#endif /* _CSI_RTC_H_ */
