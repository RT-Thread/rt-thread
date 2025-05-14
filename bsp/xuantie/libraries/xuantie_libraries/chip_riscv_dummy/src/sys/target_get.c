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
 * @file     target_get.c
 * @brief    CSI Source File for target API
 * @version  V1.0
 * @date     9. April 2020
 ******************************************************************************/

#include <stdint.h>
#include <soc.h>
#include <csi_core.h>
#include <csi_config.h>
#include <drv/common.h>
#include <drv/pin.h>
#include <drv/dma.h>

extern csi_perip_info_t g_soc_info[];
extern const csi_dma_ch_spt_list_t dma_spt_list[];

csi_error_t target_get(csi_dev_tag_t dev_tag, uint32_t idx, csi_dev_t *dev)
{
    csi_error_t ret = CSI_OK;
    csi_perip_info_t *info;

    if (dev == NULL) {
        ret = CSI_ERROR;
    }

    ///< 使用包含外设基地址，外设中断号，外设设备号，外设设备类型成员的结构体数组变量初始化info
    info = (csi_perip_info_t *)&g_soc_info;

    ///< 获取相应的设备类型和设备号
    while (info->reg_base) {
        if ((info->dev_tag == (uint16_t)dev_tag) && (info->idx == (uint8_t)idx)) {
            break;
        }

        info++;
    }

    ///< 初始化设备的统一句柄：基地址，中断号，设备号，设备类型
    if (info->reg_base == 0U) {
        ret = CSI_ERROR;
    }

    if (ret != CSI_ERROR) {
        dev->reg_base = info->reg_base;
        dev->irq_num  = info->irq_num;
        dev->idx      = info->idx;
        dev->dev_tag  = (uint16_t)dev_tag;
    }

    return ret;
}

uint32_t target_pin_to_devidx(pin_name_t pin_name, const  csi_pinmap_t *pinmap)
{
    const csi_pinmap_t *map = pinmap;
    uint32_t ret = 0xFFFFFFFFU;

    while ((uint32_t)map->pin_name != 0xFFFFFFFFU) {
        if ((map->pin_name == pin_name) && (csi_pin_get_mux(pin_name) == map->pin_func)) {
            ret = map->idx;
            break;
        }

        map++;
    }

    return ret;
}

uint32_t target_pin_to_channel(pin_name_t pin_name, const csi_pinmap_t *pinmap)
{
    const csi_pinmap_t *map = pinmap;
    uint32_t ret = 0xFFFFFFFFU;

    while ((uint32_t)map->pin_name != 0xFFFFFFFFU) {
        if (map->pin_name == pin_name) {
            ret = (uint32_t)map->channel;
            break;
        }

        map++;
    }

    return ret;
}

pin_name_t target_gpio_to_pin(uint8_t gpio_idx, uint8_t channel, const csi_pinmap_t *pinmap)
{
    const csi_pinmap_t *map = pinmap;
    pin_name_t ret = (pin_name_t)0xFFU;

    while ((uint32_t)map->pin_name != 0xFFFFFFFFU) {
        if ((map->idx == gpio_idx) && (map->channel == channel)) {
            ret = map->pin_name;
            break;
        }

        map++;
    }

    return ret;
}

csi_error_t target_get_optimal_dma_channel(void *dma_list, uint32_t ctrl_num, csi_dev_t *parent_dev, void *ch_info)
{
    uint32_t spt_id, ch_info_id, ctrl_id, ch_id;
    int32_t is_find = 0;
    csi_error_t csi_ret = CSI_OK;
    csi_dma_t **list = (csi_dma_t **)dma_list;
    csi_dma_ch_desc_t *dma_ch_info = (csi_dma_ch_desc_t *)ch_info;

    if (parent_dev == NULL) {
        /* the MEM2MEM mode */
        for (ctrl_id = 0U; ctrl_id < ctrl_num; ctrl_id++) {
            for (ch_id = 0U; ch_id < list[ctrl_id]->ch_num; ch_id++) {
                if (!(list[ctrl_id]->alloc_status & ((uint32_t)1 << ch_id))) {
                    dma_ch_info->ch_idx = (uint8_t)ch_id;
                    dma_ch_info->ctrl_idx = (uint8_t)ctrl_id;
                    /* find the channel */
                    is_find = 1;
                    break;
                }
            }

            if (is_find) {
                break;
            }
        }

        if (is_find == 0) {
            csi_ret = CSI_ERROR;
        }
    } else {
        /* the MEM2PERH mode or PERH2MEM mode */
        for (spt_id = 0U; dma_spt_list[spt_id].dev_tag != 0xFFFFU; spt_id++) {
            if ((dma_spt_list[spt_id].dev_tag == parent_dev->dev_tag) && ((uint8_t)dma_spt_list[spt_id].ctrl_idx == parent_dev->idx)) {
                break;
            }
        }

        if (dma_spt_list[spt_id].dev_tag == 0xFFFFU) {
            csi_ret = CSI_ERROR;
        }

        for (ch_info_id = 0U;; ch_info_id++) {
            if (dma_spt_list[spt_id].ch_list[ch_info_id].ctrl_idx == 0xFFU) {
                csi_ret = CSI_ERROR;
                break;
            }

            for (ctrl_id = 0U; ctrl_id < ctrl_num; ctrl_id++) {
                if ((ctrl_id == dma_spt_list[spt_id].ch_list[ch_info_id].ctrl_idx) &&
                    !(list[ctrl_id]->alloc_status & ((uint32_t)1 << dma_spt_list[spt_id].ch_list[ch_info_id].ch_idx))) {
                    dma_ch_info->ch_idx = dma_spt_list[spt_id].ch_list[ch_info_id].ch_idx;
                    dma_ch_info->ctrl_idx = dma_spt_list[spt_id].ch_list[ch_info_id].ctrl_idx;
                    /* find the channel */
                    is_find = 1;
                    break;
                }
            }

            if (is_find) {
                break;
            }
        }
    }

    return csi_ret;
}
