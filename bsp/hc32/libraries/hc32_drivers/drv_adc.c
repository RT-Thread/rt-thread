/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author               Notes
 * 2022-04-28     CDT                  first version
 * 2022-06-08     xiaoxiaolisunny      add hc32f460 series
 * 2022-06-14     CDT                  fix a bug of internal trigger
 * 2024-02-20     CDT                  support HC32F448
 *                                     add function for associating with the dma
 */

#include <board.h>
#include <drivers/adc.h>
#include <drv_adc.h>
#include <drv_config.h>

#define DBG_TAG             "drv.adc"
#define DBG_LVL             DBG_INFO

#include <rtdbg.h>
#ifdef RT_USING_ADC
typedef struct
{
    struct rt_adc_device rt_adc;
    CM_ADC_TypeDef *instance;
    struct adc_dev_init_params init;
} adc_device;

#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3)

enum
{
#ifdef BSP_USING_ADC1
    ADC1_INDEX,
#endif
#ifdef BSP_USING_ADC2
    ADC2_INDEX,
#endif
#ifdef BSP_USING_ADC3
    ADC3_INDEX,
#endif
};

static adc_device _g_adc_dev_array[] =
{
#ifdef BSP_USING_ADC1
    {
        {0},
        CM_ADC1,
        ADC1_INIT_PARAMS,
    },
#endif
#ifdef BSP_USING_ADC2
    {
        {0},
        CM_ADC2,
        ADC2_INIT_PARAMS,
    },
#endif
#ifdef BSP_USING_ADC3
    {
        {0},
        CM_ADC3,
        ADC3_INIT_PARAMS,
    },
#endif
};

static void _adc_internal_trigger0_set(adc_device *p_adc_dev)
{
    uint32_t u32TriggerSel;
    rt_bool_t is_internal_trig0_enabled = (p_adc_dev->init.hard_trig_src == ADC_HARDTRIG_EVT0 || p_adc_dev->init.hard_trig_src == ADC_HARDTRIG_EVT0_EVT1);

    if (is_internal_trig0_enabled == RT_FALSE)
    {
        return;
    }

    switch ((rt_uint32_t)p_adc_dev->instance)
    {
    case (rt_uint32_t)CM_ADC1:
        u32TriggerSel = AOS_ADC1_0;
        break;
    case (rt_uint32_t)CM_ADC2:
        u32TriggerSel = AOS_ADC2_0;
        break;
    case (rt_uint32_t)CM_ADC3:
        u32TriggerSel = AOS_ADC3_0;
        break;
    default:
        break;
    }
    AOS_CommonTriggerCmd(u32TriggerSel, AOS_COMM_TRIG1, (en_functional_state_t)p_adc_dev->init.internal_trig0_comtrg0_enable);
    AOS_CommonTriggerCmd(u32TriggerSel, AOS_COMM_TRIG2, (en_functional_state_t)p_adc_dev->init.internal_trig0_comtrg1_enable);
    AOS_SetTriggerEventSrc(u32TriggerSel, p_adc_dev->init.internal_trig0_sel);
}

static void _adc_internal_trigger1_set(adc_device *p_adc_dev)
{
    uint32_t u32TriggerSel;
    rt_bool_t is_internal_trig1_enabled = (p_adc_dev->init.hard_trig_src == ADC_HARDTRIG_EVT1 || p_adc_dev->init.hard_trig_src == ADC_HARDTRIG_EVT0_EVT1);

    if (is_internal_trig1_enabled == RT_FALSE)
    {
        return;
    }

    switch ((rt_uint32_t)p_adc_dev->instance)
    {
    case (rt_uint32_t)CM_ADC1:
        u32TriggerSel = AOS_ADC1_1;
        break;
    case (rt_uint32_t)CM_ADC2:
        u32TriggerSel = AOS_ADC2_1;
        break;
    case (rt_uint32_t)CM_ADC3:
        u32TriggerSel = AOS_ADC3_1;
        break;
    default:
        break;
    }
    AOS_CommonTriggerCmd(u32TriggerSel, AOS_COMM_TRIG1, (en_functional_state_t)p_adc_dev->init.internal_trig1_comtrg0_enable);
    AOS_CommonTriggerCmd(u32TriggerSel, AOS_COMM_TRIG2, (en_functional_state_t)p_adc_dev->init.internal_trig1_comtrg1_enable);
    AOS_SetTriggerEventSrc(u32TriggerSel, p_adc_dev->init.internal_trig1_sel);
}

static rt_err_t _adc_enable(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    adc_device *p_adc_dev = rt_container_of(device, adc_device, rt_adc);
    ADC_ChCmd(p_adc_dev->instance, ADC_SEQ_A, channel, (en_functional_state_t)enabled);

    /* user_data != NULL */
    if (device->parent.user_data != RT_NULL)
    {
        struct adc_dev_priv_params *adc_dev_priv = device->parent.user_data;
        if ((ADC_USING_EOCA_DMA_FLAG == adc_dev_priv->flag) && (adc_dev_priv->ops->dma_trig_config != RT_NULL))
        {
            adc_dev_priv->ops->dma_trig_config();
        }
    }

    return 0;
}

static rt_err_t _adc_convert(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    rt_err_t rt_ret = -RT_ERROR;
    rt_uint32_t timeCnt;

    if (!value)
    {
        return -RT_EINVAL;
    }

    adc_device *p_adc_dev = rt_container_of(device, adc_device, rt_adc);
    if (p_adc_dev->init.hard_trig_enable == RT_FALSE)
    {
        if (p_adc_dev->instance->STR == 0)
        {
            ADC_Start(p_adc_dev->instance);
        }

        uint32_t start_time = rt_tick_get();
        do
        {
            if (ADC_GetStatus(p_adc_dev->instance, ADC_FLAG_EOCA) == SET)
            {
                ADC_ClearStatus(p_adc_dev->instance, ADC_FLAG_EOCA);
                rt_ret = LL_OK;
                break;
            }
        }
        while ((rt_tick_get() - start_time) < p_adc_dev->init.eoc_poll_time_max);

        if (rt_ret == LL_OK)
        {
            /* Get any ADC value of sequence A channel that needed. */
            *value = ADC_GetValue(p_adc_dev->instance, channel);
        }
    }
    else if (p_adc_dev->init.hard_trig_enable == RT_TRUE)
    {
        /* DMA src/dest/tc... config; start/stop trigger */
        if (p_adc_dev->init.adc_eoca_dma != RT_NULL)
        {
            if (p_adc_dev->rt_adc.parent.user_data != RT_NULL)
            {
                struct adc_dev_priv_params *adc_dev_priv = device->parent.user_data;
                struct dma_config *adc_eoca_dma;
                adc_eoca_dma = p_adc_dev->init.adc_eoca_dma;
                if ((ADC_USING_EOCA_DMA_FLAG == adc_dev_priv->flag) && (adc_dev_priv->ops->dma_trig_start != RT_NULL))
                {
                    DMA_ClearTransCompleteStatus(adc_eoca_dma->Instance, adc_eoca_dma->flag);
                    (void)DMA_SetTransCount(adc_eoca_dma->Instance, adc_eoca_dma->channel, 1U);
                    (void)DMA_SetSrcAddr(adc_eoca_dma->Instance, adc_eoca_dma->channel, (uint32_t)(&p_adc_dev->instance->DR0) + channel * 2);
                    (void)DMA_SetDestAddr(adc_eoca_dma->Instance, adc_eoca_dma->channel, (uint32_t)(value));
                    (void)DMA_ChCmd(adc_eoca_dma->Instance, adc_eoca_dma->channel, ENABLE);
                    adc_dev_priv->ops->dma_trig_start();
                    timeCnt = 0;
                    /* wait DMA transfer completed */
                    while (RESET == DMA_GetTransCompleteStatus(adc_eoca_dma->Instance, adc_eoca_dma->flag) && (timeCnt < p_adc_dev->init.eoc_poll_time_max))
                    {
                        rt_thread_mdelay(1);
                        timeCnt++;
                    }
                    if (timeCnt >= p_adc_dev->init.eoc_poll_time_max)
                    {
                        (void)DMA_ChCmd(adc_eoca_dma->Instance, adc_eoca_dma->channel, DISABLE);
                        rt_ret = -RT_ETIMEOUT;
                    }
                    if (adc_dev_priv->ops->dma_trig_stop != RT_NULL)
                    {
                        adc_dev_priv->ops->dma_trig_stop();
                    }
                }
            }
        }
    }

    return rt_ret;
}

static rt_uint8_t _adc_get_resolution(struct rt_adc_device *device)
{
    rt_uint8_t resolution = 0;
    rt_uint16_t accsel;

    adc_device *p_adc_dev = rt_container_of(device, adc_device, rt_adc);
    accsel = ADC_GetResolution(p_adc_dev->instance);

    switch (accsel)
    {
    case ADC_RESOLUTION_12BIT:
        resolution = 12;
        break;
    case ADC_RESOLUTION_10BIT:
        resolution = 10;
        break;
    case ADC_RESOLUTION_8BIT:
        resolution = 8;
        break;
    default:
        break;
    }

    return resolution;
}

static rt_int16_t _adc_get_vref(struct rt_adc_device *device)
{
    rt_int16_t vref = 0;

    adc_device *p_adc_dev = rt_container_of(device, adc_device, rt_adc);
    vref = p_adc_dev->init.vref;

    return vref;
}

static struct rt_adc_ops _g_adc_ops =
{
    _adc_enable,
    _adc_convert,
    _adc_get_resolution,
    _adc_get_vref
};

static void _adc_clock_enable(void)
{
#if defined(BSP_USING_ADC1)
    FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_ADC1, ENABLE);
#endif
#if defined(BSP_USING_ADC2)
    FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_ADC2, ENABLE);
#endif
#if defined(BSP_USING_ADC3)
    FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_ADC3, ENABLE);
#endif
}

static void hc32_adc_get_dma_info(void)
{
#ifdef  BSP_ADC1_USING_DMA
    static struct dma_config adc1_eoca_dma = ADC1_EOCA_DMA_CONFIG;
    _g_adc_dev_array[ADC1_INDEX].init.adc_eoca_dma = &adc1_eoca_dma;
#endif

#ifdef  BSP_ADC2_USING_DMA
    static struct dma_config adc2_eoca_dma = ADC2_EOCA_DMA_CONFIG;
    _g_adc_dev_array[ADC2_INDEX].init.adc_eoca_dma = &adc2_eoca_dma;
#endif

#ifdef  BSP_ADC3_USING_DMA
    static struct dma_config adc3_eoca_dma = ADC3_EOCA_DMA_CONFIG;
    _g_adc_dev_array[ADC3_INDEX].init.adc_eoca_dma = &adc3_eoca_dma;
#endif
}

static void hc32_adc_dma_config(adc_device *p_adc_dev)
{
    stc_dma_init_t stcDmaInit;

    /* DMA/AOS FCG enable */
    FCG_Fcg0PeriphClockCmd(p_adc_dev->init.adc_eoca_dma->clock, ENABLE);

    (void)DMA_StructInit(&stcDmaInit);
    stcDmaInit.u32BlockSize  = 1UL;
    stcDmaInit.u32TransCount = 1UL;
    stcDmaInit.u32DataWidth  = DMA_DATAWIDTH_16BIT;
    stcDmaInit.u32SrcAddrInc  = DMA_SRC_ADDR_FIX;
    stcDmaInit.u32DestAddrInc = DMA_DEST_ADDR_FIX;
    stcDmaInit.u32SrcAddr     = (uint32_t)RT_NULL;
    stcDmaInit.u32DestAddr    = (uint32_t)RT_NULL;
    if (LL_OK != DMA_Init(p_adc_dev->init.adc_eoca_dma->Instance, p_adc_dev->init.adc_eoca_dma->channel, &stcDmaInit))
    {
        rt_kprintf("[%s:%d]ADC DMA init error!\n", __func__, __LINE__);
    }
    AOS_SetTriggerEventSrc(p_adc_dev->init.adc_eoca_dma->trigger_select, p_adc_dev->init.adc_eoca_dma->trigger_event);

    /* Clear DMA TC flag */
    DMA_ClearTransCompleteStatus(p_adc_dev->init.adc_eoca_dma->Instance, p_adc_dev->init.adc_eoca_dma->flag);
    /* Enable DMA unit */
    DMA_Cmd(p_adc_dev->init.adc_eoca_dma->Instance, ENABLE);
}

extern rt_err_t rt_hw_board_adc_init(CM_ADC_TypeDef *ADCx);
int rt_hw_adc_init(void)
{
    int ret = RT_EOK, i = 0;
    stc_adc_init_t stcAdcInit = {0};
    int32_t ll_ret = 0;

    _adc_clock_enable();
    hc32_adc_get_dma_info();
    uint32_t dev_cnt = sizeof(_g_adc_dev_array) / sizeof(_g_adc_dev_array[0]);
    for (; i < dev_cnt; i++)
    {
        ADC_DeInit(_g_adc_dev_array[i].instance);
        /* Initializes ADC. */
        stcAdcInit.u16Resolution = _g_adc_dev_array[i].init.resolution;
        stcAdcInit.u16DataAlign = _g_adc_dev_array[i].init.data_align;
        stcAdcInit.u16ScanMode = (_g_adc_dev_array[i].init.continue_conv_mode_enable) ? ADC_MD_SEQA_CONT : ADC_MD_SEQA_SINGLESHOT;
        ll_ret = ADC_Init((void *)_g_adc_dev_array[i].instance, &stcAdcInit);
        if (ll_ret != LL_OK)
        {
            ret = -RT_ERROR;
            break;
        }

        ADC_TriggerCmd(_g_adc_dev_array[i].instance, ADC_SEQ_A, (en_functional_state_t)_g_adc_dev_array[i].init.hard_trig_enable);
        ADC_TriggerConfig(_g_adc_dev_array[i].instance, ADC_SEQ_A, _g_adc_dev_array[i].init.hard_trig_src);
        if (_g_adc_dev_array[i].init.hard_trig_enable && _g_adc_dev_array[i].init.hard_trig_src != ADC_HARDTRIG_ADTRG_PIN)
        {
            _adc_internal_trigger0_set(&_g_adc_dev_array[i]);
            _adc_internal_trigger1_set(&_g_adc_dev_array[i]);
        }

        if (_g_adc_dev_array[i].init.adc_eoca_dma != RT_NULL)
        {
            hc32_adc_dma_config(&_g_adc_dev_array[i]);
        }

        rt_hw_board_adc_init((void *)_g_adc_dev_array[i].instance);
        ret = rt_hw_adc_register(&_g_adc_dev_array[i].rt_adc, \
                                 (const char *)_g_adc_dev_array[i].init.name, \
                                 &_g_adc_ops, (void *)_g_adc_dev_array[i].instance);
        if (ret != RT_EOK)
        {
            LOG_E("failed register %s, err=%d", _g_adc_dev_array[i].init.name, ret);
        }
    }
    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_adc_init);
#endif

#endif  /* RT_USING_ADC */
