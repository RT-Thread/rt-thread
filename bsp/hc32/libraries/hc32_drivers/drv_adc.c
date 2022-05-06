/*
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
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
    struct rt_adc_device adc_dev;
    CM_ADC_TypeDef *hc32_adc_instance;
    struct hc32_adc_init_type init;
} hc32_adc_device;

#if !defined(BSP_USING_ADC1) && !defined(BSP_USING_ADC2) && !defined(BSP_USING_ADC3)
    #error "Please define at least one BSP_USING_ADCx"
#endif

static hc32_adc_device g_hc32_devs[] =
{
#ifdef BSP_USING_ADC1
    {
        {0},
        CM_ADC1,
        ADC1_CONFIG,
    },
#endif
#ifdef BSP_USING_ADC2
    {
        {0},
        CM_ADC2,
        ADC2_CONFIG,
    },
#endif
#ifdef BSP_USING_ADC3
    {
        {0},
        CM_ADC3,
        ADC3_CONFIG,
    },
#endif
};

static void internal_trigger0_set(hc32_adc_device *dev)
{
    uint32_t u32TriggerSel;
    rt_bool_t is_internal_trig0_enabled = (dev->init.hard_trig_src == ADC_HARDTRIG_EVT0 || dev->init.hard_trig_src == ADC_HARDTRIG_EVT0_EVT1);

    if (is_internal_trig0_enabled == RT_FALSE)
    {
        return;
    }

#if defined(HC32F4A0)
    switch ((rt_uint32_t)dev->hc32_adc_instance)
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
    AOS_CommonTriggerCmd(u32TriggerSel, AOS_COMM_TRIG1, (en_functional_state_t)dev->init.internal_trig0_comtrg0_enable);
    AOS_CommonTriggerCmd(u32TriggerSel, AOS_COMM_TRIG2, (en_functional_state_t)dev->init.internal_trig0_comtrg1_enable);
#endif
    AOS_SetTriggerEventSrc(u32TriggerSel, dev->init.internal_trig0_sel);
}

static void internal_trigger1_set(hc32_adc_device *dev)
{
    uint32_t u32TriggerSel;
    rt_bool_t is_internal_trig1_enabled = (dev->init.hard_trig_src == ADC_HARDTRIG_EVT1 || dev->init.hard_trig_src == ADC_HARDTRIG_EVT0_EVT1);

    if (is_internal_trig1_enabled == RT_FALSE)
    {
        return;
    }

#if defined(HC32F4A0)
    switch ((rt_uint32_t)dev->hc32_adc_instance)
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
    AOS_CommonTriggerCmd(u32TriggerSel, AOS_COMM_TRIG1, (en_functional_state_t)dev->init.internal_trig0_comtrg0_enable);
    AOS_CommonTriggerCmd(u32TriggerSel, AOS_COMM_TRIG2, (en_functional_state_t)dev->init.internal_trig0_comtrg1_enable);
#endif
    AOS_SetTriggerEventSrc(u32TriggerSel, dev->init.internal_trig1_sel);
}

static rt_err_t hc32_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    hc32_adc_device *adc;

    adc = rt_container_of(device, hc32_adc_device, adc_dev);
    ADC_ChCmd(adc->hc32_adc_instance, ADC_SEQ_A, channel, (en_functional_state_t)enabled);
    return 0;
}

static rt_err_t hc32_adc_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    rt_err_t rt_ret = RT_ERROR;

    if (!value)
    {
        return -RT_EINVAL;
    }

    hc32_adc_device *adc;
    adc = rt_container_of(device, hc32_adc_device, adc_dev);

    if (adc->init.hard_trig_enable == RT_FALSE && adc->hc32_adc_instance->STR == 0)
    {
        ADC_Start(adc->hc32_adc_instance);
    }

    uint32_t start_time = rt_tick_get();
    do
    {
        if (ADC_GetStatus(adc->hc32_adc_instance, ADC_FLAG_EOCA) == SET)
        {
            ADC_ClearStatus(adc->hc32_adc_instance, ADC_FLAG_EOCA);
            rt_ret = LL_OK;
            break;
        }
    }
    while ((rt_tick_get() - start_time) < adc->init.eoc_poll_time_max);

    if (rt_ret == LL_OK)
    {
        /* Get any ADC value of sequence A channel that needed. */
        *value = ADC_GetValue(adc->hc32_adc_instance, channel);
    }

    return rt_ret;
}

static struct rt_adc_ops g_hc32_adc_ops =
{
    hc32_adc_enabled,
    hc32_adc_convert,
};

extern rt_err_t rt_hw_board_adc_init(CM_ADC_TypeDef *ADCx);
extern void rt_hw_board_adc_clock_init(void);
static int rt_hw_adc_init(void)
{
    int ret, i = 0;
    stc_adc_init_t stcAdcInit = {0};
    int32_t ll_ret = 0;

    rt_hw_board_adc_clock_init();
    uint32_t dev_cnt = sizeof(g_hc32_devs) / sizeof(g_hc32_devs[0]);
    for (; i < dev_cnt; i++)
    {
        ADC_DeInit(g_hc32_devs[i].hc32_adc_instance);
        /* Initializes ADC. */
        stcAdcInit.u16Resolution = g_hc32_devs[i].init.resolution;
        stcAdcInit.u16DataAlign = g_hc32_devs[i].init.data_align;
        stcAdcInit.u16ScanMode = (g_hc32_devs[i].init.continue_conv_mode_enable) ? ADC_MD_SEQA_CONT : ADC_MD_SEQA_SINGLESHOT;
        ll_ret = ADC_Init((void *)g_hc32_devs[i].hc32_adc_instance, &stcAdcInit);
        if (ll_ret != LL_OK)
        {
            ret = -RT_ERROR;
            break;
        }

        ADC_TriggerCmd(g_hc32_devs[i].hc32_adc_instance, ADC_SEQ_A, (en_functional_state_t)g_hc32_devs[i].init.hard_trig_enable);
        ADC_TriggerConfig(g_hc32_devs[i].hc32_adc_instance, ADC_SEQ_A, g_hc32_devs[i].init.hard_trig_src);
        if (g_hc32_devs[i].init.hard_trig_enable && g_hc32_devs[i].init.hard_trig_src != ADC_HARDTRIG_ADTRG_PIN)
        {
            internal_trigger0_set(&g_hc32_devs[i]);
            internal_trigger1_set(&g_hc32_devs[i]);
        }

        rt_hw_board_adc_init((void *)g_hc32_devs[i].hc32_adc_instance);
        ret = rt_hw_adc_register(&g_hc32_devs[i].adc_dev, \
                                 (const char *)g_hc32_devs[i].init.name, \
                                 &g_hc32_adc_ops, (void *)g_hc32_devs[i].hc32_adc_instance);
        if (ret != RT_EOK)
        {
            /* TODO err handler */
            // LOG_E("failed register %s, err=%d", g_hc32_devs[i].name, ret);
        }
    }
    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_adc_init);
#endif
