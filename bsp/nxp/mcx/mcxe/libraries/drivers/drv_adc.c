/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 * 2024-07-21     liujianhua   added mcxa153
 *
 */
#include <rtconfig.h>
#include <rtdevice.h>

#include "fsl_adc12.h"
#include "fsl_pmc.h"

#define DBG_TAG "drv.adc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_ADC

#define ADC_VBG_CH   27
#define ADC_VBG_VOLT 1000

struct mcx_adc
{
    struct rt_adc_device adc_device;
    ADC_Type            *adc_base;
    clock_ip_name_t      clock_ip_name;
    clock_ip_src_t       clock_ip_src;
    uint8_t              resolution_bits;
    uint8_t              max_channels;
    uint32_t             vref;
    char                *name;
};

static struct mcx_adc mcx_adc_obj[] =
    {
#ifdef BSP_USING_ADC0
        {
                             .adc_base        = ADC0,
                             .clock_ip_name   = kCLOCK_Adc0,
                             .clock_ip_src    = kCLOCK_IpSrcSysOscAsync,
                             .resolution_bits = 12,
                             .max_channels    = 32,
                             .name            = "adc0",
                             },
#endif
#ifdef BSP_USING_ADC1
        {
                             .adc_base        = ADC1,
                             .clock_ip_name   = kCLOCK_Adc1,
                             .clock_ip_src    = kCLOCK_IpSrcSysOscAsync,
                             .resolution_bits = 12,
                             .max_channels    = 32,
                             .name            = "adc1",
                             },
#endif
};

static uint16_t mcx_adc_get_raw(struct mcx_adc *adc, uint32_t channel)
{
    adc12_channel_config_t chnl_cfg = {0};

    chnl_cfg.channelNumber                        = channel;
    chnl_cfg.enableInterruptOnConversionCompleted = false;

    ADC12_SetChannelConfig(adc->adc_base, 0, &chnl_cfg);
    while ((ADC12_GetChannelStatusFlags(adc->adc_base, 0) & kADC12_ChannelConversionCompletedFlag) == 0U)
    {
    }

    return ADC12_GetChannelConversionValue(adc->adc_base, 0);
}

static rt_err_t mcx_adc_set_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    RT_ASSERT(device != RT_NULL);

    struct mcx_adc *adc = device->parent.user_data;
    /* ADC is enabled by global probe. */

    RT_UNUSED(adc);

    return RT_EOK;
}

static rt_int16_t mcx_get_vref(struct rt_adc_device *device)
{
    RT_ASSERT(device != RT_NULL);

    struct mcx_adc *adc = device->parent.user_data;

    return (int16_t)adc->vref;
}

static rt_err_t mcx_adc_get_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    RT_ASSERT(device != RT_NULL);

    struct mcx_adc *adc = device->parent.user_data;

    *value = mcx_adc_get_raw(adc, channel);

    return RT_EOK;
}

static rt_uint8_t mcx_adc_get_resolution(struct rt_adc_device *device)
{
    RT_ASSERT(device != RT_NULL);

    struct mcx_adc *adc = device->parent.user_data;

    return adc->resolution_bits;
}

static const struct rt_adc_ops mcx_adc_ops =
    {
        .get_resolution = mcx_adc_get_resolution,
        .enabled        = mcx_adc_set_enabled,
        .convert        = mcx_adc_get_value,
        .get_vref       = mcx_get_vref,
};

static int rt_hw_adc_init(void)
{
    int result = RT_EOK;
    int i      = 0;

    for (i = 0; i < sizeof(mcx_adc_obj) / sizeof(mcx_adc_obj[0]); i++)
    {
        struct mcx_adc *adc = &mcx_adc_obj[i];

        CLOCK_SetIpSrc(adc->clock_ip_name, adc->clock_ip_src);

        adc12_config_t cfg;
        ADC12_GetDefaultConfig(&cfg);

        cfg.clockSource      = kADC12_ClockSourceAlt0; /* Only available selection. */
        cfg.resolution       = kADC12_Resolution12Bit;
        cfg.sampleClockCount = 64;

        ADC12_Init(adc->adc_base, &cfg);
        ADC12_EnableHardwareTrigger(adc->adc_base, false);

        if (ADC12_DoAutoCalibration(adc->adc_base) != kStatus_Success)
        {
            return -RT_ERROR;
        }

        uint32_t vref_raw = mcx_adc_get_raw(adc, ADC_VBG_CH);
        adc->vref         = (1U << adc->resolution_bits) * ADC_VBG_VOLT / vref_raw;

        if (rt_hw_adc_register(&mcx_adc_obj[i].adc_device, mcx_adc_obj[i].name, &mcx_adc_ops, &mcx_adc_obj[i]) != RT_EOK)
        {
            return -RT_ERROR;
        }
    }

    return result;
}

INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */
