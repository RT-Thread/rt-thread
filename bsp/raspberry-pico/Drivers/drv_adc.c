/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-04     Chushicheng  first version
 */

#include "board.h"
#include "drv_adc.h"
#include "hardware/adc.h"

#ifdef BSP_USING_ADC
#define DBG_TAG              "drv.adc"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

static struct pico_adc_config adc_config[] =
{
#ifdef BSP_USING_ADC0
    ADC0_CONFIG,
#endif

#ifdef BSP_USING_ADC1
    ADC1_CONFIG,
#endif

#ifdef BSP_USING_ADC2
    ADC2_CONFIG,
#endif
};

static struct pico_adc pico_adc_obj[sizeof(adc_config) / sizeof(adc_config[0])];

static rt_err_t pico_adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    struct pico_adc_config *pico_adc_handler;
    RT_ASSERT(device != RT_NULL);
    pico_adc_handler = device->parent.user_data;

    if (enabled)
    {
        adc_gpio_init(pico_adc_handler->pin);
        adc_select_input(pico_adc_handler->channel);
    }

    return RT_EOK;
}

static rt_err_t pico_adc_get_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    /* get ADC value */
    *value = (rt_uint32_t)adc_read();

    return RT_EOK;
}

static const struct rt_adc_ops pico_adc_ops =
{
    .enabled = pico_adc_enabled,
    .convert = pico_adc_get_value,
    .get_resolution = RT_NULL,
    .get_vref = RT_NULL,
};

int rt_hw_adc_init(void)
{
    int result = RT_EOK;

    adc_init();

    for (rt_size_t i = 0; i < sizeof(pico_adc_obj) / sizeof(struct pico_adc); i++)
    {
        /* register ADC device */
        if (rt_hw_adc_register(&pico_adc_obj[i].pico_adc_device, adc_config[i].device_name, &pico_adc_ops, &adc_config[i]) == RT_EOK)
        {
            LOG_D("%s init success", adc_config[i].device_name);
        }
        else
        {
            LOG_E("%s register failed", adc_config[i].device_name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */
