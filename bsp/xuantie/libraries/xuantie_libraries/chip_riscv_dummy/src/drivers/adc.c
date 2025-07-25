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
 * @file     wj_adc.c
 * @brief    CSI Source File for ADC Driver
 * @version  V1.0
 * @date     2020-03-05
 ******************************************************************************/

#include <string.h>

#include <drv/adc.h>
#include <drv/irq.h>
#include <drv/tick.h>

static void wj_adc_irqhandler(void *args)
{

    ///< TODO：获取ADC中断的状态
    ///< TODO：清除ADC中断
    ///< TODO：根据ADC的中断状态处理中断

}

void wj_adc_dma_event_cb(csi_dma_ch_t *dma, csi_dma_event_t event, void *arg)
{
    csi_adc_t      *adc;

    adc = (csi_adc_t *)dma->parent;

    if (event == DMA_EVENT_TRANSFER_DONE) {
        ///< 关闭DMA通道
        csi_dma_ch_stop(dma);
        adc->num = 0U;
        adc->state.readable = 1U;

        if (adc->callback) {
            soc_dcache_clean_invalid_range((unsigned long)adc->data, adc->num * 4U);
            ///< 执行ADC DMA传输完成的用户回调函数
            adc->callback(adc, ADC_EVENT_CONVERT_COMPLETE, adc->arg);
        }
    }
}

static csi_error_t wj_adc_start_intr(csi_adc_t *adc)
{

    ///< 使能ADC的中断控制器中对应的中断
    csi_irq_enable((uint32_t)adc->dev.irq_num);
    ///< TODO：使能ADC的中断

    ///< TODO：打开ADC控制器
    return CSI_OK;
}

static csi_error_t wj_adc_start_dma(csi_adc_t *adc)
{
    csi_dma_ch_config_t config;

    config.src_inc = DMA_ADDR_CONSTANT;
    config.dst_inc = DMA_ADDR_INC;
    config.src_tw  = DMA_DATA_WIDTH_32_BITS;
    config.dst_tw  = DMA_DATA_WIDTH_32_BITS;

    config.group_len = 4U;
    config.trans_dir = DMA_PERH2MEM;
    config.handshake = 81U;
    ///< 配置ADC的DMA通道
    csi_dma_ch_config(adc->dma, &config);
    ///< 禁止中断控制器对应的中断
    csi_irq_disable((uint32_t)adc->dev.irq_num);
    soc_dcache_clean_invalid_range((unsigned long)adc->data, adc->num * 4U);

    ///< TODO：调用csi_dma_ch_start接口打开ADC的DMA通道
    ///< TODO：打开ADC
    return CSI_OK;
}

static csi_error_t wj_adc_stop_intr(csi_adc_t *adc)
{
    csi_error_t   ret = CSI_OK;

    ///< TODO：关闭ADC的中断

    ///< TODO：关闭ADC

    return ret;
}

static csi_error_t wj_adc_stop_dma(csi_adc_t *adc)
{
    csi_error_t   ret = CSI_OK;

    ///< TODO：关闭ADC

    return ret;
}

csi_error_t csi_adc_init(csi_adc_t *adc, uint32_t idx)
{
    CSI_PARAM_CHK(adc, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    adc->priv = 0U;

    ///< 获取中断号、基地址等相关信息
    if (target_get(DEV_WJ_ADC_TAG, idx, &adc->dev) != CSI_OK) {
        ret = CSI_ERROR;
    } else {

        adc->state.writeable = 1U;
        adc->state.readable  = 1U;
        adc->state.error     = 0U;
        adc->callback        = NULL;
        adc->arg             = NULL;
        adc->data            = NULL;
        adc->dma             = NULL;
        adc->start           = NULL;
        adc->stop            = NULL;

        ///< TODO：关闭ADC控制器
        ///< TODO：打开ADC控制器

    }

    return ret;
}

void csi_adc_uninit(csi_adc_t *adc)
{
    CSI_PARAM_CHK_NORETVAL(adc);

    ///< TODO：关闭ADC所有的通道
    ///< TODO：关闭ADC控制器
}

csi_error_t csi_adc_set_buffer(csi_adc_t *adc, uint32_t *data, uint32_t num)
{
    csi_error_t ret = CSI_OK;
    CSI_PARAM_CHK(adc, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(num, CSI_ERROR);

    if (num == 0U) {
        ret = CSI_ERROR;
    } else {
        adc->data = data;
        adc->num = num;
        ret = CSI_OK;
    }

    return ret;
}

csi_error_t csi_adc_start(csi_adc_t *adc)
{
    CSI_PARAM_CHK(adc, CSI_ERROR);

    csi_error_t ret = CSI_OK;

    if (adc->state.readable == 0U) {
        ret = CSI_BUSY;
        return ret;
    }

    if (adc->state.writeable == 0U) {
        ret = CSI_BUSY;
        return ret;
    }

    ///< TODO：打开ADC控制器

    return ret;
}

csi_error_t csi_adc_stop(csi_adc_t *adc)
{
    CSI_PARAM_CHK(adc, CSI_ERROR);

    csi_error_t   ret = CSI_OK;

    ///< TODO：关闭ADC

    adc->state.readable  = 1U;
    adc->state.writeable = 1U;
    adc->data = NULL;
    adc->num = 0U;

    return ret;
}

csi_error_t csi_adc_channel_enable(csi_adc_t *adc, uint8_t ch_id, bool is_enable)
{
    CSI_PARAM_CHK(adc, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    if (is_enable) {
        ///< TODO：选择ADC的通道
    } else {
        ///< TODO：关闭指定的ADC通道
    }

    return ret;
}

csi_error_t csi_adc_channel_sampling_time(csi_adc_t *adc, uint8_t ch_id, uint16_t clock_num)
{
    CSI_PARAM_CHK(adc, CSI_ERROR);
    return CSI_UNSUPPORTED;
}

csi_error_t csi_adc_sampling_time(csi_adc_t *adc, uint16_t clock_num)
{
    CSI_PARAM_CHK(adc, CSI_ERROR);

    csi_error_t ret = CSI_OK;

    ///< TODO：设置ADC的采样时间

    return ret;
}


uint32_t csi_adc_freq_div(csi_adc_t *adc, uint32_t div)
{
    CSI_PARAM_CHK(adc, CSI_ERROR);
    uint32_t ret = 0;

    ///< TODO：设置ADC的分频
    ///< TODO：获取ADC分频后使用的频率ret,需要用户自己获取ret

    return ret;
}

int32_t csi_adc_read(csi_adc_t *adc)
{
    CSI_PARAM_CHK(adc, CSI_ERROR);

    int32_t  ret = CSI_OK;

    ///< TODO：在一定时间内ADC读数据的标志位不为0，否则超时退出
    ///< TODO：读数据寄存器获取ADC转换的数据到ret

    return ret;
}

csi_error_t csi_adc_get_state(csi_adc_t *adc, csi_state_t *state)
{
    CSI_PARAM_CHK(adc, CSI_ERROR);
    *state = adc->state;
    return CSI_OK;
}

uint32_t csi_adc_get_freq(csi_adc_t *adc)
{
    CSI_PARAM_CHK(adc, 0U);
    uint32_t freq = 0U;

    ///< TODO：获取ADC的分频div
    ///< TODO：获取ADC分频后使用的频率freq

    return freq;

}

csi_error_t csi_adc_attach_callback(csi_adc_t *adc, void *callback, void *arg)
{
    CSI_PARAM_CHK(adc, CSI_ERROR);
    CSI_PARAM_CHK(callback, CSI_ERROR);

    adc->callback = callback;
    adc->arg      = arg;
    adc->start    = wj_adc_start_intr;
    adc->stop     = wj_adc_stop_intr;

    ///< 注册ADC的中断服务函数，使能中断控制器对应的中断
    csi_irq_attach((uint32_t)adc->dev.irq_num, &wj_adc_irqhandler, &adc->dev);
    csi_irq_enable((uint32_t)adc->dev.irq_num);
    return CSI_OK;

}

void csi_adc_detach_callback(csi_adc_t *adc)
{
    CSI_PARAM_CHK_NORETVAL(adc);

    adc->callback  = NULL;
    adc->arg       = NULL;
    adc->start     = NULL;
    adc->stop      = NULL;

    ///< 禁止中断控制器对应的中断
    csi_irq_disable((uint32_t)adc->dev.irq_num);
}

csi_error_t csi_adc_start_async(csi_adc_t *adc)
{
    CSI_PARAM_CHK(adc, CSI_ERROR);

    csi_error_t   ret = CSI_OK;

    if ((adc->data == NULL) || (adc->num == 0U)) {
        ret = CSI_ERROR;
        return ret;
    }

    /* rx buffer not full */
    if (adc->state.readable == 0U) {
        ret = CSI_BUSY;
        return ret;
    }

    /* last conversion existed */
    if (adc->state.writeable == 0U) {
        ret = CSI_ERROR;
        return ret;
    }

    if (adc->start) {
        ///< 执行ADC中断或者DMA传输完成中断回调函数
        adc->start(adc);
    }
    return ret;
}

csi_error_t csi_adc_stop_async(csi_adc_t *adc)
{
    CSI_PARAM_CHK(adc, CSI_ERROR);

    csi_error_t ret = CSI_OK;

    if (adc->stop) {
        adc->stop(adc);
        adc->state.readable  = 1U;
        adc->state.writeable = 1U;
        adc->data = NULL;
        adc->num = 0U;
    } else {
        ret = CSI_ERROR;
    }

    return ret;
}

csi_error_t csi_adc_continue_mode(csi_adc_t *adc, bool is_enable)
{
    CSI_PARAM_CHK(adc, CSI_ERROR);

    if (is_enable) {
        ///< TODO：设置ADC为continue模式
    } else {
        ///< TODO：设置ADC为single模式
    }

    ///< TODO：打开ADC的等待模式
    return CSI_OK;
}

csi_error_t csi_adc_link_dma(csi_adc_t *adc, csi_dma_ch_t *dma)
{
    CSI_PARAM_CHK(adc, CSI_ERROR);

    csi_error_t ret = CSI_OK;

    if (dma != NULL) {
        dma->parent = adc;
        ///< 申请DMA通道
        ret = csi_dma_ch_alloc(dma, -1, -1);

        if (ret == CSI_OK) {
            ///< ADC DMA模式传输完成中断服务函数的注册
            csi_dma_ch_attach_callback(dma, wj_adc_dma_event_cb, NULL);
            adc->dma   = dma;
            adc->start = wj_adc_start_dma;
            adc->stop  = wj_adc_stop_dma;
        } else {
            dma->parent = NULL;
        }
    } else {
        if (adc->dma) {
            ///< 释放DMA通道，注销ADC DMA模式传输完成中断服务函数
            csi_dma_ch_free(adc->dma);
            csi_dma_ch_detach_callback(adc->dma);
            adc->dma = NULL;
        }

        if (adc->callback != NULL) {
            adc->start = wj_adc_start_intr;
            adc->stop  = wj_adc_stop_intr;
        } else {
            adc->start = NULL;
            adc->stop  = NULL;
        }
    }
    return ret;
}

#ifdef CONFIG_PM
csi_error_t dw_adc_pm_action(csi_dev_t *dev, csi_pm_dev_action_t action)
{
    CSI_PARAM_CHK(dev, CSI_ERROR);

    csi_error_t ret = CSI_OK;
    csi_pm_dev_t *pm_dev = &dev->pm_dev;
    wj_adc_regs_t *adc_base = (wj_adc_regs_t *)dev->reg_base;

    switch (action) {
        case PM_DEV_SUSPEND:
            ///< TODO：恢复ADC寄存器
            break;

        case PM_DEV_RESUME:
            ///< TODO：保存ADC寄存器
            break;

        default:
            ret = CSI_ERROR;
            break;
    }

    return ret;
}

csi_error_t csi_adc_enable_pm(csi_adc_t *adc)
{
    ///< TODO：注册ADC低功耗处理函数dw_adc_pm_action
}

void csi_adc_disable_pm(csi_adc_t *adc)
{
    csi_pm_dev_unregister(&adc->dev);
}
#endif

