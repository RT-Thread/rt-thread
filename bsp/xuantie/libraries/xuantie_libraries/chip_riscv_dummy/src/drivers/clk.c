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
 * @file     clk.c
 * @brief    CSI Source File for clk Driver
 * @version  V1.0
 * @date     9. April 2020
 ******************************************************************************/

#include <stdint.h>
#include <soc.h>
#include <csi_core.h>
#include <csi_config.h>
#include <drv/common.h>

extern csi_clkmap_t clk_map[];

void csi_clk_enable(csi_dev_t *dev)
{
    csi_clkmap_t *map = clk_map;

    while (map->module != 0xFFFFFFFFU) {
        if ((map->dev_tag == dev->dev_tag) &&
            (map->idx == dev->idx)) {
            soc_clk_enable((clk_module_t)map->module); ///< TODO：打开时钟
            break;
        }

        map++;
    }
}

void csi_clk_disable(csi_dev_t *dev)
{
    csi_clkmap_t *map = clk_map;

    while (map->module != 0xFFFFFFFFU) {
        if ((map->dev_tag == dev->dev_tag) &&
            (map->idx == dev->idx)) {
            soc_clk_disable((clk_module_t)map->module); ///< TODO：关闭时钟
            break;
        }

        map++;
    }
}
