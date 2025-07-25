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
 * @file     wj_etb.c
 * @brief    CSI Source File for etb Driver
 * @version  V1.0
 * @date     19. December 2024
 * @vendor   csky
 * @name     wj_etb
 * @ip_id    0x111000010
 * @model    etb
 * @tag      DEV_WJ_ETB_TAG
 ******************************************************************************/
#include <soc.h>
#include <drv/etb.h>
#include <drv/common.h>

static uint8_t csi_etb_alloc_status[4];

static int32_t check_is_alloced(int32_t ch_id)
{
    uint32_t ch_offset, ch_group;
    int32_t ret = 0;
    uint8_t status = 0U;

    ch_group = (uint32_t)((uint32_t)ch_id / 8U);
    ch_offset = (uint32_t)((uint32_t)ch_id % 8U);

    status = csi_etb_alloc_status[ch_group];

    status &= (uint8_t)(1U << (uint8_t)ch_offset);

    if (status != 0U) {
        ret = -1;
    }

    return ret;
}

static void set_ch_alloc_status(int32_t ch_id, uint32_t status)
{
    uint32_t ch_offset, ch_group;

    ch_group = (uint32_t)((uint32_t)ch_id / 8U);
    ch_offset = (uint32_t)((uint32_t)ch_id % 8U);

    if (status == 1U) {
        csi_etb_alloc_status[ch_group] |= (uint8_t)(1U << (uint8_t)ch_offset);
    } else if (status == 0U) {
        csi_etb_alloc_status[ch_group] &= ~(uint8_t)(1U << (uint8_t)ch_offset);
    }
}

csi_error_t csi_etb_init(void)
{
    ///< TODO：使能ETB

    return CSI_OK;
}

void csi_etb_uninit(void)
{
    ///< TODO：禁止ETB
}

int32_t csi_etb_ch_alloc(csi_etb_ch_type_t ch_type)
{
    int32_t ret, ret_ch;
    uint32_t result = csi_irq_save();

    switch (ch_type) {
        case ETB_CH_MORE_TRIGGER_ONE:
            ret_ch = 0;

            if (check_is_alloced(ret_ch) < 0) {
                ret = CSI_ERROR;
            } else {
                ret = ret_ch;
            }

            break;

        case ETB_CH_ONE_TRIGGER_MORE:
            for (ret_ch = 1; ret_ch < 3; ret_ch++) {
                if (check_is_alloced(ret_ch) != -1) {
                    break;
                }
            }

            if (ret_ch == 3) {
                ret = CSI_ERROR;
            } else {
                ret = ret_ch;
            }

            break;

        case ETB_CH_ONE_TRIGGER_ONE:
            for (ret_ch = 3; ret_ch < 32; ret_ch++) {
                if (check_is_alloced(ret_ch) != -1) {
                    break;
                }
            }

            if (ret_ch == 32) {
                ret = CSI_ERROR;
            } else {
                ret = ret_ch;
            }

            break;

        default:
            ret = CSI_ERROR;
    }

    if (ret != CSI_ERROR) {
        set_ch_alloc_status(ret_ch, 1U);
    }

    csi_irq_restore(result);
    return ret;
}

void csi_etb_ch_free(int32_t ch_id)
{
    uint32_t result = csi_irq_save();
    set_ch_alloc_status(ch_id, 0U);
    csi_irq_restore(result);
}

csi_error_t csi_etb_ch_config(int32_t ch_id, csi_etb_config_t *config)
{
    CSI_PARAM_CHK(config, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    if (config->ch_type == ETB_CH_ONE_TRIGGER_ONE) {
        if (ch_id < 3) {
            ret = CSI_ERROR;
        } else {
            ///< TODO：配置ETB的通道
        }
    } else {
        ret = CSI_UNSUPPORTED;
    }

    if (ret == CSI_OK) {
        ///< TODO：配置ETB通道的触发
    }

    return ret;
}

void csi_etb_ch_start(int32_t ch_id)
{
    ///< TODO：使能ETB通道
}

void csi_etb_ch_stop(int32_t ch_id)
{
    ///< TODO：禁止ETB通道
}
