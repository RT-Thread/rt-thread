/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-29     rose_man     first version
 */
#include "board.h"
#include "drv_adc.h"

#if defined BSP_USING_ADC

#define DBG_TAG              "drv.adc"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

#if defined(BSP_USING_BL70X) || defined(BSP_USING_BL60X)
#define ADC_GPIP_BASE ((uint32_t)0x40002000)
#elif defined(BSP_USING_BL61X) || defined(BSP_USING_BL808)
#define ADC_GPIP_BASE ((uint32_t)0x20002000)
#endif

static struct bflb_adc_config_s adc_config =
{
    ADC_CLK_DIV_32,
    false,
    false,
    false,
    ADC_RESOLUTION_16B,
    ADC_VREF_2P0V
};

struct bl_adc
{
    struct rt_adc_device bl_adc_device;
    struct bflb_device_s *bflb_device;
};

static struct bl_adc bl_adc_obj;

static rt_err_t bl_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    struct bflb_device_s *bl_adc_handler;
    RT_ASSERT(device != RT_NULL);
    bl_adc_handler = device->parent.user_data;
    struct bflb_adc_channel_s chan;

    chan.pos_chan = channel;
    chan.neg_chan = ADC_CHANNEL_GND;

    bflb_adc_channel_config(bl_adc_handler, &chan, channel);

    bflb_adc_link_rxdma(bl_adc_handler, enabled);

    if (enabled)
    {
        bflb_adc_start_conversion(bl_adc_handler);
    }
    else
    {
        bflb_adc_stop_conversion(bl_adc_handler);
    }

    return RT_EOK;
}

static rt_err_t bl_adc_get_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    struct bflb_device_s *bl_adc_handler;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    bl_adc_handler = device->parent.user_data;

    /* get ADC value */
    *value = (rt_uint32_t)bflb_adc_read_raw(bl_adc_handler);

    return RT_EOK;
}

static const struct rt_adc_ops bl_adc_ops =
{
    .enabled = bl_adc_enabled,
    .convert = bl_adc_get_value,
};

int rt_hw_adc_init(void)
{
    int result = RT_EOK;
    /* ADC init */
    bl_adc_obj.bflb_device = bflb_device_get_by_name("adc");

    bflb_adc_init(bl_adc_obj.bflb_device, &adc_config);

    /* register ADC device */
    if (rt_hw_adc_register(&bl_adc_obj.bl_adc_device, "adc", &bl_adc_ops, &bl_adc_obj.bflb_device) == RT_EOK)
    {
        LOG_D("adc init success");
    }
    else
    {
        LOG_E("adc register failed");
        result = -RT_ERROR;
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */
