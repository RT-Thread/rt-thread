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
 * @file       drv/wdt.h
 * @brief      Header File for WDT Driver
 * @version    V1.0
 * @date       9. Oct 2020
 * @model      wdt
 ******************************************************************************/

#ifndef _DRV_WDT_H_
#define _DRV_WDT_H_

#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct csi_wdt csi_wdt_t;

struct csi_wdt {
    csi_dev_t       dev;
    void (*callback)(csi_wdt_t *wdt,  void *arg);
    void            *arg;
    void            *priv;
};

/**
  \brief       Initialize WDT interface. Initializes the resources needed for the WDT interface
  \param[in]   wdt    Handle to operate
  \param[in]   idx    WDT index
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_wdt_init(csi_wdt_t *wdt, uint32_t idx);

/**
  \brief       De-initialize WDT interface. Stops operation and releases the software resources used by the interface
  \param[in]   wdt    Handle to operate
  \return      None
*/
void csi_wdt_uninit(csi_wdt_t *wdt);

/**
  \brief       Set the WDT value
  \param[in]   wdt    Handle to operate
  \param[in]   ms     The timeout value(ms)
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_wdt_set_timeout(csi_wdt_t *wdt, uint32_t ms);

/**
  \brief       Start the WDT
  \param[in]   wdt    Handle to operate
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_wdt_start(csi_wdt_t *wdt);

/**
  \brief       Stop the WDT
  \param[in]   wdt    Handle to operate
  \return      None
*/
void csi_wdt_stop(csi_wdt_t *wdt);

/**
  \brief       Feed the WDT
  \param[in]   wdt    Handle to operate
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_wdt_feed(csi_wdt_t *wdt);

/**
  \brief       Get the remaining time to timeout
  \param[in]   wdt    Handle to operate
  \return      The remaining time of WDT(ms)
*/
uint32_t csi_wdt_get_remaining_time(csi_wdt_t *wdt);

/**
  \brief       Check WDT is running
  \param[in]   wdt    Handle to operate
  \return
               true  - WDT is running
               false - WDT is stopped
*/
bool csi_wdt_is_running(csi_wdt_t *wdt);

/**
  \brief       Attach the callback handler to WDT
  \param[in]   wdt         Handle to operate
  \param[in]   callback    Callback function
  \param[in]   arg         Callback's param
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_wdt_attach_callback(csi_wdt_t *wdt, void *callback, void *arg);

/**
  \brief       Detach the callback handler
  \param[in]   wdt    Handle to operate
  \return      None
*/
void csi_wdt_detach_callback(csi_wdt_t *wdt);

/**
  \brief       Enable WDT power manage
  \param[in]   wdt    Handle to operate
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_wdt_enable_pm(csi_wdt_t *wdt);

/**
  \brief       Disable WDT power manage
  \param[in]   wdt    Handle to operate
  \return      None
*/
void csi_wdt_disable_pm(csi_wdt_t *wdt);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_WDT_H_ */
