/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author               Notes
 * 2022-04-28     CDT                  first version
 * 2022-06-08     xiaoxiaolisunny      add hc32f460 series
 * 2022-06-14     CDT                  fix a bug of internal trigger
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

#if !defined(BSP_USING_ADC1) && !defined(BSP_USING_ADC2) && !defined(BSP_USING_ADC3)
    #error "Please define at least one BSP_USING_ADCx"
#endif

static adc_device g_adc_dev_array[] =
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

#if defined(HC32F4A0)
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
#endif

#if defined(HC32F460)
    switch ((rt_uint32_t)p_adc_dev->instance)
    {
    case (rt_uint32_t)CM_ADC1:
        u32TriggerSel = AOS_ADC1_0;
        break;
    case (rt_uint32_t)CM_ADC2:
        u32TriggerSel = AOS_ADC2_0;
        break;
    default:
        break;
    }
    AOS_CommonTriggerCmd(u32TriggerSel, AOS_COMM_TRIG1, (en_functional_state_t)p_adc_dev->init.internal_trig0_comtrg0_enable);
    AOS_CommonTriggerCmd(u32TriggerSel, AOS_COMM_TRIG2, (en_functional_state_t)p_adc_dev->init.internal_trig0_comtrg1_enable);
#endif
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

#if defined(HC32F4A0)
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
#endif

#if defined(HC32F460)
    switch ((rt_uint32_t)p_adc_dev->instance)
    {
    case (rt_uint32_t)CM_ADC1:
        u32TriggerSel = AOS_ADC1_1;
        break;
    case (rt_uint32_t)CM_ADC2:
        u32TriggerSel = AOS_ADC2_1;
        break;
    default:
        break;
    }
    AOS_CommonTriggerCmd(u32TriggerSel, AOS_COMM_TRIG1, (en_functional_state_t)p_adc_dev->init.internal_trig1_comtrg0_enable);
    AOS_CommonTriggerCmd(u32TriggerSel, AOS_COMM_TRIG2, (en_functional_state_t)p_adc_dev->init.internal_trig1_comtrg1_enable);
#endif
    AOS_SetTriggerEventSrc(u32TriggerSel, p_adc_dev->init.internal_trig1_sel);
}

static rt_err_t _adc_enable(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    adc_device *p_adc_dev = rt_container_of(device, adc_device, rt_adc);
    ADC_ChCmd(p_adc_dev->instance, ADC_SEQ_A, channel, (en_functional_state_t)enabled);
    return 0;
}

static rt_err_t _adc_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    rt_err_t rt_ret = RT_ERROR;

    if (!value)
    {
        return -RT_EINVAL;
    }

    adc_device *p_adc_dev = rt_container_of(device, adc_device, rt_adc);
    if (p_adc_dev->init.hard_trig_enable == RT_FALSE && p_adc_dev->instance->STR == 0)
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

    return rt_ret;
}

static struct rt_adc_ops g_adc_ops =
{
    _adc_enable,
    _adc_convert,
};

static void _adc_clock_enable(void)
{
#if defined(HC32F4A0)
#if defined(BSP_USING_ADC1)
    FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_ADC1, ENABLE);
#endif
#if defined(BSP_USING_ADC2)
    FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_ADC2, ENABLE);
#endif
#if defined(BSP_USING_ADC3)
    FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_ADC3, ENABLE);
#endif
#endif

#if defined(HC32F460)
#if defined(BSP_USING_ADC1)
    FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_ADC1, ENABLE);
#endif
#if defined(BSP_USING_ADC2)
    FCG_Fcg3PeriphClockCmd(FCG3_PERIPH_ADC2, ENABLE);
#endif
#endif
}

extern rt_err_t rt_hw_board_adc_init(CM_ADC_TypeDef *ADCx);
static int rt_hw_adc_init(void)
{
    int ret, i = 0;
    stc_adc_init_t stcAdcInit = {0};
    int32_t ll_ret = 0;

    _adc_clock_enable();
    uint32_t dev_cnt = sizeof(g_adc_dev_array) / sizeof(g_adc_dev_array[0]);
    for (; i < dev_cnt; i++)
    {
        ADC_DeInit(g_adc_dev_array[i].instance);
        /* Initializes ADC. */
        stcAdcInit.u16Resolution = g_adc_dev_array[i].init.resolution;
        stcAdcInit.u16DataAlign = g_adc_dev_array[i].init.data_align;
        stcAdcInit.u16ScanMode = (g_adc_dev_array[i].init.continue_conv_mode_enable) ? ADC_MD_SEQA_CONT : ADC_MD_SEQA_SINGLESHOT;
        ll_ret = ADC_Init((void *)g_adc_dev_array[i].instance, &stcAdcInit);
        if (ll_ret != LL_OK)
        {
            ret = -RT_ERROR;
            break;
        }

        ADC_TriggerCmd(g_adc_dev_array[i].instance, ADC_SEQ_A, (en_functional_state_t)g_adc_dev_array[i].init.hard_trig_enable);
        ADC_TriggerConfig(g_adc_dev_array[i].instance, ADC_SEQ_A, g_adc_dev_array[i].init.hard_trig_src);
        if (g_adc_dev_array[i].init.hard_trig_enable && g_adc_dev_array[i].init.hard_trig_src != ADC_HARDTRIG_ADTRG_PIN)
        {
            _adc_internal_trigger0_set(&g_adc_dev_array[i]);
            _adc_internal_trigger1_set(&g_adc_dev_array[i]);
        }

        rt_hw_board_adc_init((void *)g_adc_dev_array[i].instance);
        ret = rt_hw_adc_register(&g_adc_dev_array[i].rt_adc, \
                                 (const char *)g_adc_dev_array[i].init.name, \
                                 &g_adc_ops, (void *)g_adc_dev_array[i].instance);
        if (ret != RT_EOK)
        {
            /* TODO err handler */
            // LOG_E("failed register %s, err=%d", g_adc_dev_array[i].name, ret);
        }
    }
    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_adc_init);
#endif
