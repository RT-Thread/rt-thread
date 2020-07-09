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
 * @file     drv_wdt.h
 * @brief    header file for wdt driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef _CSI_WDT_H_
#define _CSI_WDT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <drv_common.h>

/// definition for wdt handle.
typedef void *wdt_handle_t;

/****** WDT Event *****/
typedef enum {
    WDT_EVENT_TIMEOUT       = 0  ///< generate the interrupt
} wdt_event_e;

typedef void (*wdt_event_cb_t)(wdt_event_e event);   ///< Pointer to \ref wdt_event_cb_t : WDT Event call back.

/**
\brief WDT Device Driver Capabilities.
*/
typedef struct {
    uint32_t interrupt          : 1;      ///< supports interrupt
} wdt_capabilities_t;

/**
  \brief       get wdt instance count.
  \return      wdt instance count
*/
int32_t csi_wdt_get_instance_count(void);

/**
  \brief       Initialize WDT Interface. 1. Initializes the resources needed for the WDT interface 2.registers event callback function
  \param[in]   idx   must not exceed return value of csi_wdt_get_instance_count()
  \param[in]   cb_event  Pointer to \ref wdt_event_cb_t
  \return      pointer to wdt instance
*/
wdt_handle_t csi_wdt_initialize(int32_t idx, wdt_event_cb_t cb_event);

/**
  \brief       De-initialize WDT Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle wdt handle to operate.
  \return      error code
*/
int32_t csi_wdt_uninitialize(wdt_handle_t handle);

/**
  \brief       Get driver capabilities.
  \param[in]   handle wdt handle to operate.
  \return      \ref wdt_capabilities_t
*/
wdt_capabilities_t csi_wdt_get_capabilities(wdt_handle_t handle);

/**
  \brief       Set the WDT value.
  \param[in]   handle wdt handle to operate.
  \param[in]   value     the timeout value(ms).
  \return      error code
*/
int32_t csi_wdt_set_timeout(wdt_handle_t handle, uint32_t value);

/**
  \brief       Start the WDT.
  \param[in]   handle wdt handle to operate.
  \return      error code
*/
int32_t csi_wdt_start(wdt_handle_t handle);

/**
  \brief       Stop the WDT.
  \param[in]   handle wdt handle to operate.
  \return      error code
*/
int32_t csi_wdt_stop(wdt_handle_t handle);

/**
  \brief       Restart the WDT.
  \param[in]   handle wdt handle to operate.
  \return      error code
*/
int32_t csi_wdt_restart(wdt_handle_t handle);

/**
  \brief       Read the WDT Current value.
  \param[in]   handle wdt handle to operate.
  \param[in]   value     Pointer to the Value.
  \return      error code
*/
int32_t csi_wdt_read_current_value(wdt_handle_t handle, uint32_t *value);

#ifdef __cplusplus
}
#endif

#endif /* _CSI_WDT_H_ */
