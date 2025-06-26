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
 * @file       drv/baud_calc.h
 * @brief      Header File for the PWM capture uart bandrate Driver
 * @version    V1.0
 * @date       9. Oct 2020
 * @model      baud_calc
 ******************************************************************************/

#ifndef _DRV_BAUD_CALC_H_
#define _DRV_BAUD_CALC_H_

#include <stdint.h>
#include <drv/common.h>
#include <soc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  \brief       Baud rate calculation(Algorithm level)
  \param[in]   idx        PWM idx
  \param[in]   channel    Channel num
  \return      Error code(-1) or Baudare value
*/
int drv_calc_baud_adjust(uint32_t idx, uint32_t channel);

/**
  \brief       Baud rate calculation(Capture level)
  \param[in]   idx        PWM idx
  \param[in]   channel    Channel num
  \return      Error code(-1) or Baudare value
*/
int drv_calc_baud_original(uint32_t idx, uint32_t channel);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_BAUD_CALC_H_ */
