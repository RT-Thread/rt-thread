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
 * @file     drv/pm.h
 * @brief    Header File for PM Driver
 * @version  V1.0
 * @date     10. Oct 2020
 * @model    pm
 ******************************************************************************/

#ifndef _DRV_PM_H_
#define _DRV_PM_H_

#include <stdint.h>
#include <drv/common.h>
#include <soc.h>
#include <csi_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  \brief       Initialize PM module
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_pm_init(void);

/**
  \brief       De-initialize PM module
  \return      None
*/
void csi_pm_uninit(void);

/**
  \brief       Set the retention memory used to save registers
  \param[in]   mem    Retention memory(word align)
  \param[in]   num    Number of memory(1: 1 word)
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_pm_set_reten_mem(uint32_t *mem, uint32_t num);

/**
  \brief       Config the wakeup source
  \param[in]   wakeup_num    Wakeup source num
  \param[in]   enable        Flag control the wakeup source is enable or not
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_pm_config_wakeup_source(uint32_t wakeup_num, bool enable);

/**
  \brief       System enter low-power mode
  \param[in]   mode    Low-power mode, \ref csi_pm_mode_t
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_pm_enter_sleep(csi_pm_mode_t mode);

/**
  \brief       Register device to the PM list
  \param[in]   dev          Csi dev
  \param[in]   pm_action    PM action function
  \param[in]   mem_size     Size of memory for saving registers
  \param[in]   priority     PM dev priority(0-3), The smaller the value,
                            the last execution before entering low power consumption,
                            the first execution after exiting low power consumption
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_pm_dev_register(csi_dev_t *dev, void *pm_action, uint32_t mem_size, uint8_t priority);

/**
  \brief       Deregister device to the PM list
  \param[in]   dev    Csi dev
  \return      None
*/
void csi_pm_dev_unregister(csi_dev_t *dev);

/**
  \brief       Save registers to memory
  \param[in]   mem     Mem to store registers
  \param[in]   addr    Registers address
  \param[in]   num     Number of memory(1: 1 word)
  \return      None
*/
void csi_pm_dev_save_regs(uint32_t *mem, uint32_t *addr, uint32_t num);

/**
  \brief       Save registers to memory
  \param[in]   mem     Mem to store registers
  \param[in]   addr    Registers address
  \param[in]   num     Number of memory(1: 1 word)
  \return      None
*/
void csi_pm_dev_restore_regs(uint32_t *mem, uint32_t *addr, uint32_t num);

/**
  \brief       Notify devices enter low-power states
  \param[in]   action    Device low-power action
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_pm_dev_notify(csi_pm_dev_action_t action);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_PM_H_ */
