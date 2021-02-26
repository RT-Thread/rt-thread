/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     zx.chen      timer driver header file
 */

/******************************************************************************
 * @file     drv_timer.h
 * @brief    header file for timer driver
 * @version  V1.0
 * @date     02. June 2017
 * @model    timer
 ******************************************************************************/

#ifndef _CSI_TIMER_H_
#define _CSI_TIMER_H_


#include <stdint.h>
#include <drv_common.h>

#ifdef __cplusplus
extern "C" {
#endif
/// definition for timer handle.
typedef void *timer_handle_t;

/*----- TIMER Control Codes: Mode -----*/
typedef enum
{
    TIMER_MODE_FREE_RUNNING                 = 0,   ///< free running mode
    TIMER_MODE_RELOAD                              ///< reload mode
} timer_mode_e;

/**
\brief TIMER Status
*/
typedef struct
{
    uint32_t active   : 1;                        ///< timer active flag
    uint32_t timeout  : 1;                        ///< timeout flag
} timer_status_t;

/**
\brief TIMER Event
*/
typedef enum
{
    TIMER_EVENT_TIMEOUT  = 0   ///< time out event
} timer_event_e;

typedef void (*timer_event_cb_t)(int32_t idx, timer_event_e event);   ///< Pointer to \ref timer_event_cb_t : TIMER Event call back.

/**
  \brief       Initialize TIMER Interface. 1. Initializes the resources needed for the TIMER interface 2.registers event callback function
  \param[in]   idx  timer index
  \param[in]   cb_event  event call back function \ref timer_event_cb_t
  \param[in]   cb_arg    arguments of cb_event
  \return      pointer to timer instance
*/
timer_handle_t csi_timer_initialize(int32_t idx, timer_event_cb_t cb_event);

/**
  \brief       De-initialize TIMER Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle timer handle to operate.
  \return      error code
*/
int32_t csi_timer_uninitialize(timer_handle_t handle);

/**
  \brief       control timer power.
  \param[in]   handle  timer handle to operate.
  \param[in]   state   power state.\ref csi_power_stat_e.
  \return      error code
*/
int32_t csi_timer_power_control(timer_handle_t handle, csi_power_stat_e state);

/**
  \brief       config timer mode.
  \param[in]   handle timer handle to operate.
  \param[in]   mode      \ref timer_mode_e
  \return      error code
*/
int32_t csi_timer_config(timer_handle_t handle, timer_mode_e mode);

/**
  \brief       Set timeout just for the reload mode.
  \param[in]   handle timer handle to operate.
  \param[in]   timeout the timeout value in microseconds(us).
  \return      error code
*/
int32_t csi_timer_set_timeout(timer_handle_t handle, uint32_t timeout);

/**
  \brief       Start timer.
  \param[in]   handle timer handle to operate.
  \return      error code
*/
int32_t csi_timer_start(timer_handle_t handle);

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
  \param[out]   value     timer current value
  \return      error code
*/
int32_t csi_timer_get_current_value(timer_handle_t handle, uint32_t *value);

/**
  \brief       Get TIMER status.
  \param[in]   handle timer handle to operate.
  \return      TIMER status \ref timer_status_t
*/
timer_status_t csi_timer_get_status(timer_handle_t handle);

/**
  \brief       get timer reload value
  \param[in]   handle timer handle to operate.
  \param[out]   value    timer reload value
  \return      error code
*/
int32_t csi_timer_get_load_value(timer_handle_t handle, uint32_t *value);

#ifdef __cplusplus
}
#endif

#endif /* _CSI_TIMER_H_ */

