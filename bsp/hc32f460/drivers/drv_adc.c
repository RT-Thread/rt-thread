/*
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author             Notes
 * 2022-05-10     xiaoxiaolisunny    first version
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
    M4_ADC_TypeDef *hc32_adc_instance;
    struct hc32_adc_init_type init;
} hc32_adc_device;

#if !defined(BSP_USING_ADC1) && !defined(BSP_USING_ADC2)
    #error "Please define at least one BSP_USING_ADCx"
#endif

static hc32_adc_device g_hc32_devs[] =
{
#ifdef BSP_USING_ADC1
    {
        {0},
        M4_ADC1,
        ADC1_CONFIG,
    },
#endif
#ifdef BSP_USING_ADC2
    {
        {0},
        M4_ADC2,
        ADC2_CONFIG,
    },
#endif
};

static rt_err_t hc32_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    hc32_adc_device *adc;

    stc_adc_ch_cfg_t stcChCfg;
    rt_uint8_t adcSampleTime[] = {0x50};

    adc = rt_container_of(device, hc32_adc_device, adc_dev);

    MEM_ZERO_STRUCT(stcChCfg);

    stcChCfg.u32Channel  = 1u << channel;
    stcChCfg.u8Sequence  = ADC_SEQ_A;
    stcChCfg.pu8SampTime = adcSampleTime;
    ADC_AddAdcChannel(adc->hc32_adc_instance, &stcChCfg);

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
        ADC_StartConvert(adc->hc32_adc_instance);
    }

    uint32_t start_time = rt_tick_get();
    do
    {
        if (ADC_GetEocFlag(adc->hc32_adc_instance, ADC_SEQ_A ) == Set)
        {
            ADC_ClrEocFlag(adc->hc32_adc_instance, ADC_SEQ_A );
            rt_ret = Ok;
            break;
        }
    }
    while ((rt_tick_get() - start_time) < adc->init.eoc_poll_time_max);

    if (rt_ret == Ok)
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

extern rt_err_t rt_hw_board_adc_init(M4_ADC_TypeDef *ADCx);
extern void rt_hw_board_adc_clock_init(void);
static int rt_hw_adc_init(void)
{
    int ret, i = 0;
    stc_adc_init_t stcAdcInit;
    int32_t ll_ret = 0;

    rt_hw_board_adc_clock_init();
    uint32_t dev_cnt = sizeof(g_hc32_devs) / sizeof(g_hc32_devs[0]);
    for (; i < dev_cnt; i++)
    {
        ADC_DeInit(g_hc32_devs[i].hc32_adc_instance);
        /* Initializes ADC. */
        stcAdcInit.enResolution = g_hc32_devs[i].init.resolution;
        stcAdcInit.enDataAlign = g_hc32_devs[i].init.data_align;
              stcAdcInit.enAutoClear = g_hc32_devs[i].init.auto_clear;
        stcAdcInit.enScanMode = (g_hc32_devs[i].init.continue_conv_mode_enable) ? AdcMode_SAContinuous : AdcMode_SAOnce;
        ll_ret = ADC_Init((void *)g_hc32_devs[i].hc32_adc_instance, &stcAdcInit);
        if (ll_ret != Ok)
        {
            ret = -RT_ERROR;
            break;
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
