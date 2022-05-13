/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-11     shelton      first version
 */

#include "board.h"
#include "drv_adc.h"

#if defined(BSP_USING_ADC1)

//#define DRV_DEBUG
#define LOG_TAG             "drv.adc"
#include <drv_log.h>

struct at32_adc
{
    struct rt_adc_device at32_adc_device;
    adc_type *adc_x;
    char *name;
};

static struct at32_adc at32_adc_obj[] =
{
#ifdef BSP_USING_ADC1
    ADC1_CONFIG,
#endif
};

static rt_err_t at32_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    adc_type *adc_x;
    adc_base_config_type adc_config_struct;

    RT_ASSERT(device != RT_NULL);
    adc_x = device->parent.user_data;

    at32_msp_adc_init(adc_x);

    /* adc_x configuration */
    adc_base_default_para_init(&adc_config_struct);
    adc_config_struct.data_align = ADC_RIGHT_ALIGNMENT;
    adc_config_struct.ordinary_channel_length = 1;
    adc_config_struct.repeat_mode = FALSE;
    adc_config_struct.sequence_mode = FALSE;
    adc_base_config(adc_x, &adc_config_struct);
    adc_ordinary_conversion_trigger_set(adc_x, ADC12_ORDINARY_TRIG_SOFTWARE, TRUE);

    if (!enabled)
    {
        /* disable adc_x */
        adc_enable(adc_x, FALSE);
    }
    else
    {
        /* enable adc_x */
        adc_enable(adc_x, TRUE);

        /* enable adc_x calibration */
        adc_calibration_init(adc_x);
        /* check the end of adc_x reset calibration register */
        while(adc_calibration_init_status_get(adc_x) == SET)
        {
        }
        /* start adc_x calibration */
         adc_calibration_start(adc_x);
        /* check the end of adc_x calibration */
        while(adc_calibration_status_get(adc_x) == SET)
        {
        }
    }

    return RT_EOK;
}

static rt_err_t at32_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    adc_type *adc_x;
    rt_uint32_t timeout = 0;

    RT_ASSERT(device != RT_NULL);
    adc_x = device->parent.user_data;

    /* adc_x regular channels configuration */
    adc_ordinary_channel_set(adc_x, (adc_channel_select_type)channel, 1, ADC_SAMPLETIME_239_5);

    /* start adc_x software conversion */
    adc_ordinary_software_trigger_enable(adc_x, TRUE);

    /* wait for the adc to convert */
    while((adc_flag_get(adc_x, ADC_CCE_FLAG) == RESET) && timeout < 0xFFFF)
    {
        timeout ++;
    }

    if(timeout >= 0xFFFF)
    {
        LOG_D("channel%d converts timeout, please confirm adc_x enabled or not", channel);
    }

    /* get adc value */
    *value = adc_ordinary_conversion_data_get(adc_x);

    return RT_EOK;
}

static const struct rt_adc_ops at_adc_ops =
{
    .enabled = at32_adc_enabled,
    .convert = at32_get_adc_value,
};

static int rt_hw_adc_init(void)
{
    int result = RT_EOK;
    int i = 0;

    for (i = 0; i < sizeof(at32_adc_obj) / sizeof(at32_adc_obj[0]); i++)
    {
        /* register ADC device */
        if (rt_hw_adc_register(&at32_adc_obj[i].at32_adc_device, at32_adc_obj[i].name, &at_adc_ops, at32_adc_obj[i].adc_x) == RT_EOK)
        {
            LOG_D("%s register success", at32_adc_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", at32_adc_obj[i].name);
            result = -RT_ERROR;
        }

    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */
