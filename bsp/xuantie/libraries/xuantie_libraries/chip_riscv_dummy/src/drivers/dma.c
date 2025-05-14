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
 * @file     dw_dma.c
 * @brief    CSI Source File for uart Driver
 * @version  V1.0
 * @date     16. Mar 2020
 * @vendor   csky
 * @name     dw_dma
 * @ip_id    0x111000010
 * @model    dma
 * @tag      DEV_DW_DMA_TAG
 ******************************************************************************/

#include <drv/dma.h>
#include <drv/irq.h>
#include <csi_core.h>

#define CONFIG_DMA_CHANNEL_NUM  8

extern uint8_t g_dma_chnum[];
csi_dma_t *dma_array[2] = {0};
static uint32_t inited_ctrl_num = 0U;

void dw_dma_irq_handler(void *arg)
{

    ///< TODO：获取中断状态
    ///< TODO：清除中断
    ///< TODO：处理中断
}

csi_error_t csi_dma_init(csi_dma_t *dma, int8_t ctrl_id)
{
    CSI_PARAM_CHK(dma, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    ///< 获取中断号、基地址等相关信息
    ret = target_get(DEV_DW_DMA_TAG, (uint32_t) ctrl_id, &dma->dev);

    if (ret == CSI_OK) {

        slist_init(&dma->head);
        dma->alloc_status = 0U;
        dma_array[ctrl_id] = dma;
        dma_array[ctrl_id]->ch_num = g_dma_chnum[ctrl_id];

        if (ctrl_id == 0) {

            ///< TODO：清除DMA0搬运中断
            ///< TODO：清除DMA0块搬运中断
            ///< TODO：清除DMA0错误中断
            ///< TODO：清除DMA0源搬运中断
            ///< TODO：清除DMA0目的搬运中断

        } else if (ctrl_id == 1) {

            ///< TODO：清除DMA1搬运中断
            ///< TODO：清除DMA1块搬运中断
            ///< TODO：清除DMA1错误中断
            ///< TODO：清除DMA1源搬运中断
            ///< TODO：清除DMA1目的搬运中断

        }

        ///< 注册DMA中断服务函数，使能中断控制器中对应的中断
        csi_irq_attach((uint32_t)dma->dev.irq_num, &dw_dma_irq_handler, &dma->dev);
        csi_irq_enable((uint32_t)dma->dev.irq_num);

        if (ctrl_id == 0) {
            ///< TODO：关闭DMA0所有通道的使能
        } else if (ctrl_id == 1) {
            ///< TODO：关闭DMA1所有通道的使能
        }

        ///< TODO：使能DMA控制器

        uint32_t result = csi_irq_save();
        inited_ctrl_num++;
        csi_irq_restore(result);
    }

    return ret;
}

void csi_dma_uninit(csi_dma_t *dma)
{
    CSI_PARAM_CHK_NORETVAL(dma);
    slist_init(&dma->head);
    dma->alloc_status = 0U;
    dma_array[dma->dev.idx] = NULL;
    ///< 禁止中断控制器对应的中断，注销DMA中断服务函数
    csi_irq_disable((uint32_t)dma->dev.irq_num);
    csi_irq_detach((uint32_t)dma->dev.irq_num);

    ///< TODO：关闭DMA控制器

    uint32_t result = csi_irq_save();
    inited_ctrl_num--;
    csi_irq_restore(result);
}

csi_error_t csi_dma_ch_alloc(csi_dma_ch_t *dma_ch, int8_t ch_id, int8_t ctrl_id)
{
    CSI_PARAM_CHK(dma_ch, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    csi_dma_ch_desc_t ch_info = {0};
    csi_dev_t *dev_info;
    dev_info = (csi_dev_t *)(dma_ch->parent);
    uint32_t result = csi_irq_save();

    if ((ctrl_id == -1) && (ch_id == -1)) {
        ret = target_get_optimal_dma_channel(dma_array, inited_ctrl_num, dev_info, &ch_info);

        if (ret == CSI_OK) {
            dma_array[ch_info.ctrl_idx]->alloc_status |= (uint32_t)((uint32_t)1U << (uint32_t)ch_info.ch_idx);

            dma_ch->ch_id = ch_info.ch_idx;
            dma_ch->ctrl_id = ch_info.ctrl_idx;
        }
    } else if ((ctrl_id >= 0) && (ch_id >= 0)) {
        if (dma_array[ctrl_id]->alloc_status & (uint32_t)((uint32_t)1U << (uint32_t)ch_id)) {
            ret = CSI_ERROR;
        } else {
            dma_array[ctrl_id]->alloc_status |= (uint32_t)((uint32_t)1U << (uint32_t)ch_id);
            dma_ch->ch_id = ch_id;
            dma_ch->ctrl_id = ctrl_id;

            ///< TODO：清除DMA指定通道的搬运中断
            ///< TODO：清除DMA指定通道的块搬运中断
            ///< TODO：清除DMA指定通道的错误中断
            ///< TODO：清除DMA指定通道的源搬运中断
            ///< TODO：清除DMA指定通道的目的搬运中断

            ///< TODO：配置DMA指定通道的搬运中断屏蔽
            ///< TODO：配置DMA指定通道的块搬运中断屏蔽
            ///< TODO：配置DMA指定通道的错误中断屏蔽

            ///< TODO：关闭指定的DMA通道
        }
    } else {
        ret = CSI_ERROR;
    }

    if (ret == CSI_ERROR) {
        csi_irq_restore(result);

    } else {
        slist_add(&dma_ch->next, &dma_array[dma_ch->ctrl_id]->head);
        csi_irq_restore(result);
    }

    dma_ch->etb_ch_id = -1;

    return ret;
}

void csi_dma_ch_free(csi_dma_ch_t *dma_ch)
{
    CSI_PARAM_CHK_NORETVAL(dma_ch);
    uint32_t result = csi_irq_save();

    uint32_t temp_u32;
    temp_u32 = 1U << (uint8_t)(dma_ch->ch_id);

    if (dma_array[dma_ch->ctrl_id]->alloc_status & temp_u32) {
        dma_array[dma_ch->ctrl_id]->alloc_status &= ~((uint32_t)1 << (uint32_t)dma_ch->ch_id);

        ///< TODO：清除DMA指定通道的搬运中断
        ///< TODO：清除DMA指定通道的块搬运中断
        ///< TODO：清除DMA指定通道的错误中断
        ///< TODO：清除DMA指定通道的源搬运中断
        ///< TODO：清除DMA指定通道的目的搬运中断

        ///< TODO：对DMA的搬运中断掩码进行允许掩码位写入的操作
        ///< TODO：对DMA的错误中断掩码进行允许掩码位写入的操作

        ///< TODO：关闭指定的DMA通道

        slist_del(&dma_ch->next, &dma_array[dma_ch->ctrl_id]->head);
    }

    csi_irq_restore(result);
}

csi_error_t csi_dma_ch_config(csi_dma_ch_t *dma_ch, csi_dma_ch_config_t *config)
{
    CSI_PARAM_CHK(dma_ch, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    ///< TODO：关闭DMA指定通道的所有中断

    /* Initializes corresponding channel registers */

    switch (config->dst_tw) {
        case DMA_DATA_WIDTH_8_BITS:
            ///< TODO：配置正在使用的DMA通道的目地端传输数据的位宽为8
            break;

        case DMA_DATA_WIDTH_16_BITS:
            ///< TODO：配置正在使用的DMA通道的目地端传输数据的位宽为16
            break;

        case DMA_DATA_WIDTH_32_BITS:
            ///< TODO：配置正在使用的DMA通道的目地端传输数据的位宽为32
            break;

        default:
            break;
    }

    switch (config->src_tw) {
        case DMA_DATA_WIDTH_8_BITS:
            ///< TODO：配置正在使用的DMA通道的源端传输数据的位宽为8
            break;

        case DMA_DATA_WIDTH_16_BITS:
            ///< TODO：配置正在使用的DMA通道的源端传输数据的位宽为16
            break;

        case DMA_DATA_WIDTH_32_BITS:
            ///< TODO：配置正在使用的DMA通道的源端传输数据的位宽为32
            break;

        default:
            break;
    }

    switch (config->src_inc) {
        case  DMA_ADDR_INC  :
            ///< TODO：配置正在使用的DMA通道的源端的地址是增加的
            break;

        case  DMA_ADDR_DEC:
            ///< TODO：配置正在使用的DMA通道的源端的地址是减少的
            break;

        case  DMA_ADDR_CONSTANT:
            ///< TODO：配置正在使用的DMA通道的源端的地址是不变的
            break;

        default:
            break;
    }

    switch (config->dst_inc) {
        case  DMA_ADDR_INC  :
            ///< TODO：配置正在使用的DMA通道的目地端的地址是增加的
            break;

        case  DMA_ADDR_DEC:
            ///< TODO：配置正在使用的DMA通道的目地端的地址是减少的
            break;

        case  DMA_ADDR_CONSTANT:
            ///< TODO：配置正在使用的DMA通道的目地端的地址是不变的
            break;

        default:
            break;
    }

    ///< TODO：配置正在使用的DMA通道的突发传输长度

    switch (config->trans_dir) {
        case DMA_MEM2MEM:
            ///< TODO：配置正在使用的DMA通道的传输方向为内存到内存
            ///< TODO：配置正在使用的DMA通道的目地端的握手方式为软件握手
            ///< TODO：配置正在使用的DMA通道的源端的握手方式为软件握手
            break;

        case DMA_MEM2PERH:
            ///< TODO：配置正在使用的DMA通道的传输方向为内存到外设
            ///< TODO：配置正在使用的DMA通道的目地端的握手方式为硬件握手
            ///< TODO：配置正在使用的DMA通道的源端的握手方式为软件握手
            ///< TODO：配置正在使用的DMA通道的目地端的握手号
            break;

        case DMA_PERH2MEM:
            ///< TODO：配置正在使用的DMA通道的传输方向为外设到内存
            ///< TODO：配置正在使用的DMA通道的目地端的握手方式为软件握手
            ///< TODO：配置正在使用的DMA通道的源端的握手方式为硬件握手
            ///< TODO：配置正在使用的DMA通道的源端的握手号
            break;

        default:
            break;
    }

    if (config->src_reload_en == 1) {
        ///< TODO：配置正在使用的DMA通道的源地址自动重载
    } else {
        ///< TODO：配置正在使用的DMA通道的源地址不是自动重载
    }

    if (config->dst_reload_en == 1) {
        ///< TODO：配置正在使用的DMA通道的目地地址自动重载
    } else {
        ///< TODO：配置正在使用的DMA通道的目地地址不是自动重载
    }

    return ret;
}

csi_error_t csi_dma_ch_attach_callback(csi_dma_ch_t *dma_ch, void *callback, void *arg)
{
    csi_error_t ret = CSI_OK;
    CSI_PARAM_CHK(dma_ch, CSI_ERROR);

    dma_ch->callback = callback;
    dma_ch->arg = arg;

    ///< TODO：配置DMA0/DMA1的搬运中断、块搬运中断、错误中断屏蔽寄存器的写使能位和屏蔽位

    ///< TODO：配置DMA0/DMA1的搬运中断、块搬运中断、源搬运中断、目地搬运中断、错误中断清除寄存器

    return ret;
}

void csi_dma_ch_detach_callback(csi_dma_ch_t *dma_ch)
{
    CSI_PARAM_CHK_NORETVAL(dma_ch);

    dma_ch->callback = NULL;
    dma_ch->arg = NULL;

    ///< TODO：配置DMA0/DMA1的搬运中断、块搬运中断、源搬运中断、目地搬运中断、错误中断屏蔽寄存器的写使能位
    ///< TODO：配置DMA0/DMA1的搬运中断、块搬运中断、源搬运中断、目地搬运中断、错误中断清除寄存器

    ///< TODO：关闭DMA中断

}

void csi_dma_ch_start(csi_dma_ch_t *dma_ch, void *srcaddr, void *dstaddr, uint32_t length)
{
    CSI_PARAM_CHK_NORETVAL(dma_ch);

    ///< TODO：关闭正在使用的DMA通道

    if (srcaddr != NULL) {
        ///< TODO：配置正在使用的DMA通道的源地址
    }

    if (dstaddr != NULL) {
        ///< TODO：配置正在使用的DMA通道的目地地址
    }

    ///< TODO：配置DMA0/DMA1的搬运中断、块搬运中断、源搬运中断、目地搬运中断、错误中断清除寄存器

    ///< TODO：使能正在使用的DMA通道的中断
    ///< TODO：打开申请到的DMA通道

}

void csi_dma_ch_stop(csi_dma_ch_t *dma_ch)
{
    int8_t ch = dma_ch->ch_id;

    if (ch >= CONFIG_DMA_CHANNEL_NUM || ch < 0) {
        return;
    }

    ///< TODO：关闭DMA通道
    ///< TODO：关闭DMA中断

}
