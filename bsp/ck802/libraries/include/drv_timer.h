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
 * @file     drv_timer.h
 * @brief    header file for timer driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef _CSI_TIMER_H_
#define _CSI_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <drv_common.h>

/// definition for timer handle.
typedef void *timer_handle_t;

/*----- TIMER Control Codes: Mode -----*/
typedef enum {
    TIMER_MODE_FREE_RUNNING                 = 0,   ///< free running mode
    TIMER_MODE_RELOAD                              ///< reload mode
} timer_mode_e;

/**
\brief TIMER Status
*/
typedef struct {
    uint32_t active   : 1;                        ///< timer active flag
    uint32_t timeout  : 1;                        ///< timeout flag
} timer_status_t;

/**
\brief TIMER Event
*/
typedef enum {
    TIMER_EVENT_TIMEOUT  = 0   ///< time out event
} timer_event_e;

typedef void (*timer_event_cb_t)(timer_event_e event, void *arg);   ///< Pointer to \ref timer_event_cb_t : TIMER Event call back.

/**
\brief TIMER Device Driver Capabilities.
*/
typedef struct {
    uint32_t interrupt_mode          : 1;      ///< supports Interrupt mode
} timer_capabilities_t;

/**
  \brief       get timer instance count.
  \return      timer instance count
*/
int32_t csi_timer_get_instance_count(void);

/**
  \brief       Initialize TIMER Interface. 1. Initializes the resources needed for the TIMER interface 2.registers event callback function
  \param[in]   idx  instance timer index
  \param[in]   cb_event  Pointer to \ref timer_event_cb_t
  \param[in]   cb_arg    arguments of cb_event
  \return      pointer to timer instance
*/
timer_handle_t csi_timer_initialize(int32_t idx, timer_event_cb_t cb_event, void *cb_arg);

/**
  \brief       De-initialize TIMER Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle timer handle to operate.
  \return      error code
*/
int32_t csi_timer_uninitialize(timer_handle_t handle);

/**
  \brief       Get driver capabilities.
  \param[in]   handle timer handle to operate.
  \return      \ref timer_capabilities_t
*/
timer_capabilities_t csi_timer_get_capabilities(timer_handle_t handle);

/**
  \brief       config timer mode.
  \param[in]   handle timer handle to operate.
  \param[in]   mode      \ref timer_mode_e
  \return      error code
*/
int32_t csi_timer_config(timer_handle_t handle, timer_mode_e mode);

/**
  \brief       Set timer.
  \param[in]   handle timer handle to operate.
  \param[in]   timeout the timeout value in microseconds(us).
  \return      error code
*/
int32_t csi_timer_set_timeout(timer_handle_t handle, uint32_t timeout);

/**
  \brief       Start timer.
  \param[in]  handle timer handle to operate.
  \param[in]   apbfreq APB frequency
  \return      error code
*/
int32_t csi_timer_start(timer_handle_t handle, uint32_t apbfreq);

/**
  \brief       Stop timer.
  \param[in]   handle timer handle to operate.
  \return      error code
*/
int32_t csi_timer_stop(timer_handle_t handle);

/**
  \brief       suspend timer.
  \param[in]   handle timer handle to operate.
  \return      error code
*/
int32_t csi_timer_suspend(timer_handle_t handle);

/**
  \brief       resume timer.
  \param[in]   handle timer handle to operate.
  \return      error code
*/
int32_t csi_timer_resume(timer_handle_t handle);

/**
  \brief       get timer current value
  \param[in]   handle timer handle to operate.
  \param[in]   value     timer current value
  \return      error code
*/
int32_t csi_timer_get_current_value(timer_handle_t handle, uint32_t *value);

/**
  \brief       Get TIMER status.
  \param[in]   handle timer handle to operate.
  \return      TIMER status \ref timer_status_t
*/
timer_status_t csi_timer_get_status(timer_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* _CSI_TIMER_H_ */

