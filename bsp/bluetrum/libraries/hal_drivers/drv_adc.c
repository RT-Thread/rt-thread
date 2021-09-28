/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-02-01     greedyhao         first version
 */

#include "drv_gpio.h"

#ifdef BSP_USING_ADC0

#include "adc_config.h"

// #define DRV_DEBUG
#define LOG_TAG             "drv.adc"
#include <drv_log.h>

struct ab32_adc
{
    struct rt_adc_device ab32_adc_device;
    hal_sfr_t adc_dat_handle;
    char *name;
};

enum
{
#ifdef BSP_USING_ADC0
    ADC0_INDEX,
#endif

    ADC_INDEX_END
};

static struct ab32_adc ab32_adc_obj[] =
{
#ifdef BSP_USING_ADC0
    ADC0_CONFIG,
#endif
};

static rt_err_t ab32_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    RT_ASSERT(device != RT_NULL);

    hal_adc_enable(enabled);

    return RT_EOK;
}

static rt_uint32_t ab32_adc_get_channel(rt_uint32_t channel)
{
    rt_uint32_t ab32_channel = 0;

    switch (channel)
    {
    case  0:
        ab32_channel = ADC_CHANNEL_0;
        break;
    case  1:
        ab32_channel = ADC_CHANNEL_1;
        break;
    case  2:
        ab32_channel = ADC_CHANNEL_2;
        break;
    case  3:
        ab32_channel = ADC_CHANNEL_3;
        break;
    case  4:
        ab32_channel = ADC_CHANNEL_4;
        break;
    case  5:
        ab32_channel = ADC_CHANNEL_5;
        break;
    case  6:
        ab32_channel = ADC_CHANNEL_6;
        break;
    case  7:
        ab32_channel = ADC_CHANNEL_7;
        break;
    case  8:
        ab32_channel = ADC_CHANNEL_8;
        break;
    case  9:
        ab32_channel = ADC_CHANNEL_9;
        break;
    case 10:
        ab32_channel = ADC_CHANNEL_10;
        break;
    case 11:
        ab32_channel = ADC_CHANNEL_11;
        break;
    case 12:
        ab32_channel = ADC_CHANNEL_12;
        break;
    case 13:
        ab32_channel = ADC_CHANNEL_13;
        break;
    case 14:
        ab32_channel = ADC_CHANNEL_14;
        break;
    case 15:
        ab32_channel = ADC_CHANNEL_15;
        break;
    }

    return ab32_channel;
}

static rt_err_t ab32_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    hal_sfr_t ab32_adc_handler;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    ab32_adc_handler = device->parent.user_data;

    hal_adc_start(ab32_adc_get_channel(channel));
    hal_adc_poll_for_conversion(1000);

    *value = ab32_adc_handler[channel];

    return RT_EOK;
}

static const struct rt_adc_ops _adc_ops =
{
    .enabled = ab32_adc_enabled,
    .convert = ab32_get_adc_value,
};

static int ab32_adc_init(void)
{
    int result = RT_EOK;
    int i = 0;

    if (ADC_INDEX_END == 0) {
        return result;
    }

    CLKCON0 |= BIT(28); // enable adc clock

    for (i = 0; i < sizeof(ab32_adc_obj) / sizeof(ab32_adc_obj[0]); i++) {
        if (rt_hw_adc_register(&ab32_adc_obj[i].ab32_adc_device, ab32_adc_obj[i].name, &_adc_ops, (const void *)ab32_adc_obj[i].adc_dat_handle) == RT_EOK)
        {
            LOG_D("%s init success", ab32_adc_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", ab32_adc_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(ab32_adc_init);

#endif

