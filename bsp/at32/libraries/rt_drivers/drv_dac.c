/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-18     shelton      first version
 * 2024-08-30     shelton      add support m412/416
 */

#include "drv_common.h"

#if defined(BSP_USING_DAC1)
#include "drv_config.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.dac"
#include <drv_log.h>

struct at32_dac {
    char *name;
    dac_type *dac_x;
    struct rt_dac_device dac_device;
};

enum {
#ifdef BSP_USING_DAC1
    DAC1_INDEX,
#endif
};

static struct at32_dac dac_config[] =
{
#ifdef BSP_USING_DAC1
    DAC1_CONFIG,
#endif
};

static dac_select_type at32_dac_get_channel(rt_uint32_t channel)
{
    dac_select_type at32_channel = DAC1_SELECT;

    switch (channel)
    {
    case 1:
        at32_channel = DAC1_SELECT;
        break;
    case 2:
        at32_channel = DAC2_SELECT;
        break;
    default:
        RT_ASSERT(0);
        break;
    }

    return at32_channel;
}

static rt_err_t at32_dac_enabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    dac_select_type dac_channel;
    dac_type *instance;

    RT_ASSERT(device != RT_NULL);
    instance = device->parent.user_data;
    /* prepare for mult dac instance */
    (void)instance;

    if ((channel <= 2) && (channel > 0))
    {
        /* set at32 dac channel */
        dac_channel =  at32_dac_get_channel(channel);
    }
    else
    {
      LOG_E("dac channel must be 1 or 2.");
      return -RT_ERROR;
    }
#if defined (SOC_SERIES_AT32M412) || defined (SOC_SERIES_AT32M416)
    dac_output_enable(dac_channel, TRUE);
#endif
    dac_enable(dac_channel, TRUE);

    return RT_EOK;
}

static rt_err_t at32_dac_disabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    dac_select_type dac_channel;
    dac_type *instance;

    RT_ASSERT(device != RT_NULL);
    instance = device->parent.user_data;
    /* prepare for mult dac instance */
    (void)instance;

    if ((channel <= 2) && (channel > 0))
    {
        /* set at32 dac channel */
        dac_channel =  at32_dac_get_channel(channel);
    }
    else
    {
      LOG_E("dac channel must be 1 or 2.");
      return -RT_ERROR;
    }
#if defined (SOC_SERIES_AT32M412) || defined (SOC_SERIES_AT32M416)
    dac_output_enable(dac_channel, FALSE);
#endif
    dac_enable(dac_channel, FALSE);

    return RT_EOK;
}

static rt_uint8_t at32_dac_get_resolution(struct rt_dac_device *device)
{
    dac_type *instance;

    RT_ASSERT(device != RT_NULL);
    instance = device->parent.user_data;
    /* prepare for mult dac instance */
    (void)instance;

    /* Only has supported DAC_ALIGN_12B_R, so it will return 12 bits */
    return 12;
}

static rt_err_t at32_set_dac_value(struct rt_dac_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    dac_select_type dac_channel;
    dac_type *instance;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    instance = device->parent.user_data;
    /* prepare for mult dac instance */
    (void)instance;

    if ((channel <= 2) && (channel > 0))
    {
        /* set at32 dac channel */
        dac_channel =  at32_dac_get_channel(channel);
    }
    else
    {
        LOG_E("dac channel must be 1 or 2.");
        return -RT_ERROR;
    }
#if !defined (SOC_SERIES_AT32M412) && !defined (SOC_SERIES_AT32M416)
    dac_output_buffer_enable(dac_channel, FALSE);
#endif
    dac_trigger_enable(dac_channel, FALSE);

    /* set dac channel out value*/
    if(dac_channel == DAC1_SELECT)
    {
#if !defined (SOC_SERIES_AT32M412) && !defined (SOC_SERIES_AT32M416)
        dac_1_data_set(DAC1_12BIT_RIGHT, *value);
#else
        /* 6-bit */
        *value = *value >> 6;
        dac_1_data_set(*value);
#endif
    }
    else
    {
#if !defined (SOC_SERIES_AT32M412) && !defined (SOC_SERIES_AT32M416)
        dac_2_data_set(DAC2_12BIT_RIGHT, *value);
#else
        /* 6-bit */
        *value = *value >> 6;
        dac_2_data_set(*value);
#endif
    }

    /* start dac */
    dac_enable(dac_channel, TRUE);

    return RT_EOK;
}

static const struct rt_dac_ops at32_dac_ops =
{
    .disabled = at32_dac_disabled,
    .enabled  = at32_dac_enabled,
    .convert  = at32_set_dac_value,
    .get_resolution = at32_dac_get_resolution,
};

static int at32_dac_init(void)
{
    rt_size_t obj_num;
    int index;

    obj_num = sizeof(dac_config) / sizeof(struct at32_dac);
    rt_err_t result = 0;

    for (index = 0; index < obj_num; index++) {
        at32_msp_dac_init((void *)(dac_config[index].dac_x));
        /* reset dac */
        dac_reset();

        /* register dac device */
        if (rt_hw_dac_register(&dac_config[index].dac_device, dac_config[index].name, &at32_dac_ops, \
            &dac_config[index].dac_x) == RT_EOK)
        {
            LOG_D("%s init success", dac_config[index].name);
        }
        else
        {
            LOG_E("%s register failed", dac_config[index].name);
            result = -RT_ERROR;
        }
    }

    return result;
}

INIT_DEVICE_EXPORT(at32_dac_init);

#endif /* BSP_USING_DAC */
