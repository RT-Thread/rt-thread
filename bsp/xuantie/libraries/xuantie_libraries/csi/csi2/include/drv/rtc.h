 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file       drv/rtc.h
 * @brief      Header File for RTC Driver
 * @version    V1.0
 * @date       9. Oct 2020
 * @model      rtc
 ******************************************************************************/

#ifndef _DRV_RTC_H_
#define _DRV_RTC_H_

#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/****** RTC time ******/
typedef struct {
    int tm_sec;             ///< Second.      [0-59]
    int tm_min;             ///< Minute.      [0-59]
    int tm_hour;            ///< Hour.        [0-23]
    int tm_mday;            ///< Day.         [1-31]
    int tm_mon;             ///< Month.       [0-11]
    int tm_year;            ///< Year-1900.   [70- ]      !NOTE:Set 100 mean 2000
    int tm_wday;            ///< Day of week. [0-6 ]      !NOTE:Set 0 mean Sunday
    int tm_yday;            ///< Days in year.[0-365]     !NOTE:Set 0 mean January 1st
} csi_rtc_time_t;

/****** definition for RTC ******/
typedef struct csi_rtc csi_rtc_t;

struct csi_rtc {
    csi_dev_t           dev;
    void (*callback)(csi_rtc_t *rtc, void *arg);
    void               *arg;
    void               *priv;
};

/**
  \brief       Initialize RTC interface. Initializes the resources needed for the RTC interface
  \param[in]   rtc    Handle to operate
  \param[in]   idx    RTC index
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_rtc_init(csi_rtc_t *rtc, uint32_t idx);

/**
  \brief       De-initialize RTC interface. Stops operation and releases the software resources used by the interface
  \param[in]   rtc    Handle to operate
  \return      None
*/
void csi_rtc_uninit(csi_rtc_t *rtc);

/**
  \brief       Set system date and wait for synchro
  \param[in]   rtc        Handle to operate
  \param[in]   rtctime    Pointer to RTC time
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_rtc_set_time(csi_rtc_t *rtc, const csi_rtc_time_t *rtctime);

/**
  \brief       Set system date but no wait
  \param[in]   rtc        Handle to operate
  \param[in]   rtctime    Pointer to RTC time
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_rtc_set_time_no_wait(csi_rtc_t *rtc, const csi_rtc_time_t *rtctime);

/**
  \brief       Get system date
  \param[in]   rtc        Handle to operate
  \param[out]  rtctime    Pointer to RTC time
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_rtc_get_time(csi_rtc_t *rtc, csi_rtc_time_t *rtctime);

/**
  \brief       Get alarm remaining time
  \param[in]   rtc    Handle to operate
  \return      The remaining time(s)
*/
uint32_t csi_rtc_get_alarm_remaining_time(csi_rtc_t *rtc);

/**
  \brief       Config RTC alarm timer
  \param[in]   rtc         Handle to operate
  \param[in]   rtctime     Time to wake up
  \param[in]   callback    Callback function
  \param[in]   arg         Callback's param
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_rtc_set_alarm(csi_rtc_t *rtc, const csi_rtc_time_t *rtctime, void *callback, void *arg);

/**
  \brief       Cancel the RTC alarm
  \param[in]   rtc    Handle to operate
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_rtc_cancel_alarm(csi_rtc_t *rtc);

/**
  \brief       Judge RTC is running
  \param[in]   rtc    Handle to operate
  \return
               true  - RTC is running
               false - RTC is not running
*/
bool csi_rtc_is_running(csi_rtc_t *rtc);

/**
  \brief       Enable RTC power manage
  \param[in]   rtc    Handle to operate
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_rtc_enable_pm(csi_rtc_t *rtc);

/**
  \brief       Disable RTC power manage
  \param[in]   rtc    Handle to operate
  \return      None
*/
void csi_rtc_disable_pm(csi_rtc_t *rtc);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_RTC_H_ */
