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
 * @file     drv/clk.h
 * @brief    Header File for CLK Driver.
 * @version  V1.0
 * @date     18. Mar 2020
 ******************************************************************************/

#ifndef _DRV_CLK_H_
#define _DRV_CLK_H_

#include <stdint.h>
#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t module;
    uint16_t dev_tag;
    uint8_t  idx;
} csi_clkmap_t;

void csi_clk_enable(csi_dev_t *dev);
void csi_clk_disable(csi_dev_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_CLK_H_ */

