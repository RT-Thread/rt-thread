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
 * @file     drv_pmu.h
 * @brief    header file for pmu driver
 * @version  V1.0
 * @date     02. June 2017
 * @model    pmu
 ******************************************************************************/

#ifndef _DRV_PMU_H_
#define _DRV_PMU_H_


#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif
/// definition for pmu handle.
typedef void *pmu_handle_t;

/****** PMU specific error codes *****/
typedef enum {
    EDRV_PMU_MODE  = (1),      ///< Specified Mode not supported
} pmu_error_e;

/*----- PMU Control Codes: Mode -----*/
typedef enum {
    PMU_MODE_RUN                  = 0,   ///< Running mode
    PMU_MODE_SLEEP,                      ///< Sleep mode
    PMU_MODE_DOZE,                       ///< Doze mode
    PMU_MODE_DORMANT,                    ///< Dormant mode
    PMU_MODE_STANDBY,                    ///< Standby mode
    PMU_MODE_SHUTDOWN                    ///< Shutdown mode
} pmu_mode_e;

/*----- PMU Control Codes: Wakeup type -----*/
typedef enum {
    PMU_WAKEUP_TYPE_PULSE   = 0,    ///< Pulse interrupt
    PMU_WAKEUP_TYPE_LEVEL           ///< Level interrupt
} pmu_wakeup_type_e;

/*----- PMU Control Codes: Wakeup polarity -----*/
typedef enum {
    PMU_WAKEUP_POL_LOW      = 0,       ///< Low or negedge
    PMU_WAKEUP_POL_HIGH                ///< High or posedge
} pmu_wakeup_pol_e;

/****** PMU Event *****/
typedef enum {
    PMU_EVENT_SLEEP_DONE        = 0,  ///< Send completed; however PMU may still transmit data
    PMU_EVENT_PREPARE_SLEEP     = 1
} pmu_event_e;

typedef void (*pmu_event_cb_t)(int32_t idx, pmu_event_e event, pmu_mode_e mode);   ///< Pointer to \ref pmu_event_cb_t : PMU Event call back.

/**
  \brief       Initialize PMU Interface. 1. Initializes the resources needed for the PMU interface 2.registers event callback function
  \param[in]   idx the id of the pmu
  \param[in]   cb_event  Pointer to \ref pmu_event_cb_t
  \return      return pmu handle if success
*/
pmu_handle_t csi_pmu_initialize(int32_t idx, pmu_event_cb_t cb_event);

/**
  \brief       De-initialize PMU Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle  pmu handle to operate.
  \return      error code
*/
int32_t csi_pmu_uninitialize(pmu_handle_t handle);

/**
  \brief       choose the pmu mode to enter
  \param[in]   handle  pmu handle to operate.
  \param[in]   mode    \ref pmu_mode_e
  \return      error code
*/
int32_t csi_pmu_enter_sleep(pmu_handle_t handle, pmu_mode_e mode);

/**
  \brief       control pmu power.
  \param[in]   handle  pmu handle to operate.
  \param[in]   state   power state.\ref csi_power_stat_e.
  \return      error code
*/
/**
  \brief       Config the wakeup source.
  \param[in]   handle  pmu handle to operate
  \param[in]   wakeup_num wakeup source num
  \param[in]   type    \ref pmu_wakeup_type
  \param[in]   pol     \ref pmu_wakeup_pol
  \param[in]   enable  flag control the wakeup source is enable or not
  \return      error code
*/
int32_t csi_pmu_config_wakeup_source(pmu_handle_t handle, uint32_t wakeup_num, pmu_wakeup_type_e type, pmu_wakeup_pol_e pol, uint8_t enable);

#ifdef __cplusplus
}
#endif

#endif /* _CSI_PMU_H_ */
