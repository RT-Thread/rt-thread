/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-04     Rbb666       first version
 */
#include "drv_common.h"
#include "drv_adc.h"

#include "cyhal.h"
#include "cybsp.h"

#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2)

//#define DRV_DEBUG
#define LOG_TAG             "drv.adc"
#include <drv_log.h>

#define VPLUS_CHANNEL_0     (P10_0)

struct ifx_adc
{
    struct rt_adc_device ifx_adc_device;
    cyhal_adc_channel_t *adc_ch;
    char *name;
};

static struct ifx_adc ifx_adc_obj[] =
{
    #ifdef BSP_USING_ADC1
    ADC1_CONFIG,
    #endif
};

static rt_err_t ifx_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    cyhal_adc_channel_t *adc_ch;
    cy_rslt_t result;

    RT_ASSERT(device != RT_NULL);
    adc_ch = device->parent.user_data;

    const cyhal_adc_channel_config_t channel_config =
    {
        .enable_averaging = false,      // Disable averaging for channel
        .min_acquisition_ns = 1000,     // Minimum acquisition time set to 1us
        .enabled = enabled              // Sample this channel when ADC performs a scan
    };

    if (enabled)
    {
        /* Initialize ADC. The ADC block which can connect to pin 10[0] is selected */
        result = cyhal_adc_init(&adc_obj, VPLUS_CHANNEL_0, NULL);

        if (result != RT_EOK)
        {
            LOG_E("ADC initialization failed. Error: %u\n", result);
            return -RT_ENOSYS;
        }

        /* Initialize a channel 0 and configure it to scan P10_0 in single ended mode. */
        result  = cyhal_adc_channel_init_diff(adc_ch, &adc_obj, VPLUS_CHANNEL_0,
                                              CYHAL_ADC_VNEG, &channel_config);

        if (result != RT_EOK)
        {
            LOG_E("ADC single ended channel initialization failed. Error: %u\n", result);
            return -RT_ENOSYS;
        }

        /* Update ADC configuration */
        result = cyhal_adc_configure(&adc_obj, &adc_config);

        if (result != RT_EOK)
        {
            printf("ADC configuration update failed. Error: %u\n", result);
            return -RT_ENOSYS;
        }
    }
    else
    {
        cyhal_adc_free(&adc_obj);
        cyhal_adc_channel_free(adc_ch);
    }

    return RT_EOK;
}

static rt_err_t ifx_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    cyhal_adc_channel_t *adc_ch;

    RT_ASSERT(device != RT_NULL);
    adc_ch = device->parent.user_data;

    channel = adc_ch->channel_idx;

    *value = cyhal_adc_read(adc_ch);

    return RT_EOK;
}

static const struct rt_adc_ops at_adc_ops =
{
    .enabled = ifx_adc_enabled,
    .convert = ifx_get_adc_value,
};

static int rt_hw_adc_init(void)
{
    int result = RT_EOK;
    int i = 0;

    for (i = 0; i < sizeof(ifx_adc_obj) / sizeof(ifx_adc_obj[0]); i++)
    {
        /* register ADC device */
        if (rt_hw_adc_register(&ifx_adc_obj[i].ifx_adc_device, ifx_adc_obj[i].name, &at_adc_ops, ifx_adc_obj[i].adc_ch) == RT_EOK)
        {
            LOG_D("%s register success", at32_adc_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", ifx_adc_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */
