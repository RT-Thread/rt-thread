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
 * @file     drv/tng.h
 * @brief    Header File for RNG Driver
 * @version  V1.0
 * @date     22. Apr 2020
 * @model    tng
 ******************************************************************************/
#ifndef _DRV_TNG_H_
#define _DRV_TNG_H_

#include "drv/common.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  \brief       Get data from the TNG engine
  \param[out]  Data  Pointer to buffer with data get from TNG
  \param[in]   Num   Number of data items,uinit in uint32
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_rng_get_multi_word(uint32_t *data, uint32_t num);

/**
  \brief       Get data from the TNG engine
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_rng_get_single_word(uint32_t* data);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_TNG_H_ */
