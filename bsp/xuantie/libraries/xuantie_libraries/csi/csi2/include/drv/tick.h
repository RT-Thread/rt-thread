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
 * @file     tick.h
 * @brief    Header File for TICK Driver
 * @version  V1.0
 * @date     28. Sep 2020
 ******************************************************************************/

#ifndef _DRV_TICK_H_
#define _DRV_TICK_H_

#include <stdint.h>
#include <stdint.h>
#include <drv/common.h>

#ifndef CONFIG_SYSTICK_HZ
#define CONFIG_SYSTICK_HZ  100U
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
  \brief       Initializes the resources needed for the TICK interface
  \return      error code \ref csi_error_t
*/
csi_error_t csi_tick_init(void);

/**
  \brief       De-initialize TICK Interface
*/
void csi_tick_uninit(void);

/**
  \brief       Get the sys-tick, one tick == (1000 / CONFIG_SYSTICK_HZ) ms
  \return      the sys-tick
*/
uint32_t csi_tick_get(void);

/**
  \brief       Get the time which start from csi_tick_init
  \return      The time which start from csi_tick_init (ms)
*/
uint32_t csi_tick_get_ms(void);

/**
  \brief       Get the time which start from csi_tick_init
  \return      The time which start from csi_tick_init (us)
*/
uint64_t csi_tick_get_us(void);

/**
  \brief       Increase the sys-tick
*/
void csi_tick_increase(void);

#ifdef __cplusplus
}
#endif

#endif /*_DRV_TICK_H_*/
