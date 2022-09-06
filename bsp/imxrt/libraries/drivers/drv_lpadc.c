/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-20     tyustli      the first version.
 *
 */
#include <rtthread.h>

#ifdef BSP_USING_LPADC

#if !defined(BSP_USING_LPADC1) && !defined(BSP_USING_LPADC2)
#error "Please define at least one BSP_USING_LPADCx"
#endif

#if (defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#error "Please don't define 'FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL'!"
#endif

#define LOG_TAG             "drv.lpadc"
#include <drv_log.h>
#include "drv_lpadc.h"
#include "fsl_lpadc.h"
#include <rtdevice.h>

lpadc_config_t mLpadcConfigStruct;

#if defined(BSP_USING_LPADC1)
static struct rt_adc_device lpadc1_device;
#endif

#if defined(BSP_USING_LPADC2)
static struct rt_adc_device lpadc2_device;
#endif

#if (defined(DEMO_LPADC_USE_HIGH_RESOLUTION) && DEMO_LPADC_USE_HIGH_RESOLUTION)
uint32_t g_LpadcResultShift = 0U;
#else
uint32_t g_LpadcResultShift = 3U;
#endif /* DEMO_LPADC_USE_HIGH_RESOLUTION */

static rt_err_t imxrt_hp_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    return RT_EOK;
}

static rt_err_t imxrt_hp_adc_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    LPADC1_BASE *base;
    lpadc_conv_command_config_t mLpadcCommandConfigStruct;
    lpadc_conv_trigger_config_t mLpadcTriggerConfigStruct;
    lpadc_conv_result_t mLpadcResultConfigStruct;
    base = (LPADC1_BASE *)(device->parent.user_data);

    //ADC_SetChannelConfig(base, 0, &adc_channel);
    LPADC_GetDefaultConvCommandConfig(&mLpadcCommandConfigStruct);
    mLpadcCommandConfigStruct.channelNumber = channel;
#if defined(DEMO_LPADC_USE_HIGH_RESOLUTION) && DEMO_LPADC_USE_HIGH_RESOLUTION
    mLpadcCommandConfigStruct.conversionResolutionMode = kLPADC_ConversionResolutionHigh;
#endif /* DEMO_LPADC_USE_HIGH_RESOLUTION */
    LPADC_SetConvCommandConfig(base, 1U, &mLpadcCommandConfigStruct);

    /* Set trigger configuration. */
    LPADC_GetDefaultConvTriggerConfig(&mLpadcTriggerConfigStruct);
    mLpadcTriggerConfigStruct.targetCommandId       = 1U;
    mLpadcTriggerConfigStruct.enableHardwareTrigger = false;
    LPADC_SetConvTriggerConfig(base, 0U, &mLpadcTriggerConfigStruct); /* Configurate the trigger0. */

    LPADC_DoSoftwareTrigger(base, 1U);

#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
    while (!LPADC_GetConvResult(base, &mLpadcResultConfigStruct, 0U))
#else
    while (!LPADC_GetConvResult(base, &mLpadcResultConfigStruct))
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */
    {
    }
    *value = (mLpadcResultConfigStruct.convValue) >> g_LpadcResultShift;

    return RT_EOK;
}

static struct rt_adc_ops imxrt_lpadc_ops =
{
    .enabled = imxrt_hp_adc_enabled,
    .convert = imxrt_hp_adc_convert,
};

int rt_hw_adc_init(void)
{
    int result = RT_EOK;

    LPADC_GetDefaultConfig(&mLpadcConfigStruct);
    mLpadcConfigStruct.enableAnalogPreliminary = true;
#if defined(kLPADC_ReferenceVoltageAlt1)
    mLpadcConfigStruct.referenceVoltageSource = kLPADC_ReferenceVoltageAlt1;
#endif /* DEMO_LPADC_VREF_SOURCE */
#if defined(BSP_USING_LPADC1)
    LPADC_Init(LPADC1, &mLpadcConfigStruct);
    result = rt_hw_adc_register(&lpadc1_device, "lpadc1", &imxrt_lpadc_ops, LPADC1);
    if (result != RT_EOK)
    {
        LOG_E("register lpadc1 device failed error code = %d\n", result);
    }
#endif
#if defined(BSP_USING_LPADC2)
    LPADC_Init(LPADC1, &mLpadcConfigStruct);
    result = rt_hw_adc_register(&lpadc2_device, "lpadc2", &imxrt_lpadc_ops, LPADC2);
    if (result != RT_EOK)
    {
        LOG_E("register lpadc2 device failed error code = %d\n", result);
    }
#endif
    return result;
}

INIT_DEVICE_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_LPADC */

