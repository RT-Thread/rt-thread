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
 * @file     ck_trng.c
 * @brief
 * @version
 * @date     27. April 2020
 ******************************************************************************/

#include <drv/rng.h>
#include <drv/irq.h>
#include <drv/tick.h>
#include <string.h>

/**
  \brief       Get data from the TRNG engine
  \param[out]  data  Pointer to buffer with data get from TRNG
  \param[in]   num   Number of data items,uinit in uint32
  \return      error code
*/
csi_error_t csi_rng_get_multi_word(uint32_t *data, uint32_t num)
{
    csi_error_t ret = CSI_OK;

    CSI_PARAM_CHK(data, CSI_ERROR);
    if (num == 0U) {
        ret = CSI_ERROR;
    }else{
        int i = 0;
        while (num) {
            ///< TODO：使能trng 模块

            ///< TODO：等待trng 模块有效  且未超时，超时设置ret并退出循环

            ///< TODO：获取trng值到data[i]
            i++;
            num--;
        }
    }
    return ret;
}

/**
  \brief       Get data from the TRNG engine
  \return      error code
*/
csi_error_t csi_rng_get_single_word(uint32_t* data)
{
    csi_error_t ret = CSI_OK;
    CSI_PARAM_CHK(data, CSI_ERROR);

    ///< TODO：使能trng 模块

    ///< TODO：等待trng 模块有效  且未超时，超时设置ret并退出循环

    ///< TODO：获取trng值到*data

    return  ret;
}
