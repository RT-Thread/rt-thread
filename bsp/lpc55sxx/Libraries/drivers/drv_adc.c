/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-20     tyustli      the first version.
 * 2019-07-15     Magicoe      The first version for LPC55S6x
 *
 */
#include <rtthread.h>

#ifdef BSP_USING_ADC

#if !defined(BSP_USING_ADC0_CH0)
#error "Please define at least one BSP_USING_ADCx_CH0"
#endif

#define LOG_TAG             "drv.adc"
#include <drv_log.h>
#include "drv_adc.h"
#include "fsl_power.h"
#include "fsl_lpadc.h"
#include <rtdevice.h>

static rt_err_t lpc_lpadc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    return RT_EOK;
}

static rt_err_t lpc_lpadc_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    lpadc_conv_trigger_config_t mLpadcTriggerConfigStruct;
    lpadc_conv_command_config_t mLpadcCommandConfigStruct;
    lpadc_conv_result_t mLpadcResultConfigStruct;

    ADC_Type *base;
    base = (ADC_Type *)(device->parent.user_data);

    /* Set conversion CMD configuration. */
    LPADC_GetDefaultConvCommandConfig(&mLpadcCommandConfigStruct);
    mLpadcCommandConfigStruct.channelNumber = channel;
    LPADC_SetConvCommandConfig(base, 1U, &mLpadcCommandConfigStruct);

    /* Set trigger configuration. */
    LPADC_GetDefaultConvTriggerConfig(&mLpadcTriggerConfigStruct);
    mLpadcTriggerConfigStruct.targetCommandId       = 1U;
    mLpadcTriggerConfigStruct.enableHardwareTrigger = false;
    LPADC_SetConvTriggerConfig(base, 0U, &mLpadcTriggerConfigStruct); /* Configurate the trigger0. */

    LPADC_DoSoftwareTrigger(base, 1U); /* 1U is trigger0 mask. */
    while (!LPADC_GetConvResult(base, &mLpadcResultConfigStruct, 0U));

    *value =  ((mLpadcResultConfigStruct.convValue) >> 3U);

    return RT_EOK;
}

static struct rt_adc_ops lpc_adc_ops =
{
    .enabled = lpc_lpadc_enabled,
    .convert = lpc_lpadc_convert,
};

#if defined(BSP_USING_ADC0_CH0)
static struct rt_adc_device adc0_device;
#endif  /* BSP_USING_ADC0_CH0 */


int rt_hw_adc_init(void)
{
    int result = RT_EOK;

#if defined(BSP_USING_ADC0_CH0)
    lpadc_config_t mLpadcConfigStruct;

    CLOCK_SetClkDiv(kCLOCK_DivAdcAsyncClk, 16U, true);
    CLOCK_AttachClk(kMAIN_CLK_to_ADC_CLK);
    /* Disable LDOGPADC power down */
    POWER_DisablePD(kPDRUNCFG_PD_LDOGPADC);

    LPADC_GetDefaultConfig(&mLpadcConfigStruct);
    mLpadcConfigStruct.enableAnalogPreliminary = true;
    mLpadcConfigStruct.referenceVoltageSource = kLPADC_ReferenceVoltageAlt2;
    mLpadcConfigStruct.conversionAverageMode = kLPADC_ConversionAverage128;
    LPADC_Init(ADC0, &mLpadcConfigStruct);

    /* Request offset calibration. */
    //LPADC_DoOffsetCalibration(ADC0);
    LPADC_SetOffsetValue(ADC0, 10U, 10U);
    /* Request gain calibration. */
    LPADC_DoAutoCalibration(ADC0);

    result = rt_hw_adc_register(&adc0_device, "adc0", &lpc_adc_ops, ADC0);

    if (result != RT_EOK)
    {
        LOG_E("register adc0 device failed error code = %d\n", result);
    }

#endif /* BSP_USING_ADC0_CH0 */

    return result;
}

INIT_DEVICE_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */

