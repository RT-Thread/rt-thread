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
 * @file       drv/timer.h
 * @brief      Header File for TIMER Driver
 * @version    V1.0
 * @date       9. Oct 2020
 * @model      timer
 ******************************************************************************/

#ifndef _DRV_TIMER_H_
#define _DRV_TIMER_H_

#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct csi_timer csi_timer_t;

struct csi_timer {
    csi_dev_t        dev;
    void (*callback)(csi_timer_t *timer, void *arg);
    void            *arg;
    void            *priv;
};

/**
  \brief       Initialize TIMER interface. initializes the resources needed for the TIMER interface
  \param[in]   timer    Handle to operate
  \param[in]   idx      TIMER index
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_timer_init(csi_timer_t *timer, uint32_t idx);

/**
  \brief       De-initialize TIMER interface. stops operation and releases the software resources used by the interface
  \param[in]   timer    Handle to operate
  \return      None
*/
void csi_timer_uninit(csi_timer_t *timer);

/**
  \brief       Start TIMER
  \param[in]   timer         Handle to operate
  \param[in]   timeout_us    The timeout for TIMER
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_timer_start(csi_timer_t *timer, uint32_t timeout_us);

/**
  \brief       Stop TIMER
  \param[in]   timer    Handle to operate
  \return      None
*/
void csi_timer_stop(csi_timer_t *timer);

/**
  \brief       Get TIMER remaining value
  \param[in]   timer    Handle to operate
  \return      remaining value
*/
uint32_t csi_timer_get_remaining_value(csi_timer_t *timer);

/**
  \brief       Get TIMER load value
  \param[in]   timer    Handle to operate
  \return      Load value
*/
uint32_t csi_timer_get_load_value(csi_timer_t *timer);

/**
  \brief       Check TIMER is running
  \param[in]   timer    Handle to operate
  \return
               true  - TIMER is running
               false - TIMER is stopped
*/
bool csi_timer_is_running(csi_timer_t *timer);

/**
  \brief       Attach the callback handler to TIMER
  \param[in]   timer       Operate handle
  \param[in]   callback    Callback function
  \param[in]   arg         Callback's param
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_timer_attach_callback(csi_timer_t *timer, void *callback, void *arg);

/**
  \brief       Detach the callback handler
  \param[in]   timer    Operate handle
  \return      None
*/
void csi_timer_detach_callback(csi_timer_t *timer);

/**
  \brief       Enable TIMER power manage
  \param[in]   timer    Handle to operate
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_timer_enable_pm(csi_timer_t *timer);

/**
  \brief       Disable TIMER power manage
  \param[in]   timer    Handle to operate
  \return      None
*/
void csi_timer_disable_pm(csi_timer_t *timer);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_TIMER_H_ */
