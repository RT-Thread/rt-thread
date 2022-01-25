/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-02-25     iysheng           first version
 */

#include <board.h>
#include <drivers/adc.h>

#define DBG_TAG             "drv.adc"
#define DBG_LVL             DBG_INFO

#include <rtdbg.h>

#ifdef RT_USING_ADC

#define MAX_EXTERN_ADC_CHANNEL    16

typedef struct {
    struct rt_adc_device adc_dev;
    char name[8];
    rt_base_t adc_pins[16];
    void *private_data;
} gd32_adc_device;

static gd32_adc_device g_gd32_devs[] = {
#ifdef BSP_USING_ADC0
    {
        {},
        "adc0",
        {
            GET_PIN(A, 0), GET_PIN(A, 1), GET_PIN(A, 2), GET_PIN(A, 3),
            GET_PIN(A, 4), GET_PIN(A, 5), GET_PIN(A, 6), GET_PIN(A, 7),
            GET_PIN(B, 0), GET_PIN(B, 1), GET_PIN(C, 0), GET_PIN(C, 1),
            GET_PIN(C, 2), GET_PIN(C, 3), GET_PIN(C, 4), GET_PIN(C, 5),
        },
        (void *)ADC0,
    },
#endif

#ifdef BSP_USING_ADC1
    {
        {},
        "adc1",
        {
            GET_PIN(A, 0), GET_PIN(A, 1), GET_PIN(A, 2), GET_PIN(A, 3),
            GET_PIN(A, 4), GET_PIN(A, 5), GET_PIN(A, 6), GET_PIN(A, 7),
            GET_PIN(B, 0), GET_PIN(B, 1), GET_PIN(C, 0), GET_PIN(C, 1),
            GET_PIN(C, 2), GET_PIN(C, 3), GET_PIN(C, 4), GET_PIN(C, 5),
        },
        (void *)ADC1,
    },
#endif
};

/*
 * static void init_pin4adc
 *
 * @ rt_uint32_t pin: pin information
 * return: N/A
 */
static void init_pin4adc(rt_base_t pin)
{
    gpio_init(PIN_GDPORT(pin), GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, PIN_GDPIN(pin));
}

static rt_err_t gd32_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    uint32_t adc_periph;
    gd32_adc_device * gd32_adc = (gd32_adc_device *)device;

    if (channel >= MAX_EXTERN_ADC_CHANNEL)
    {
        LOG_E("invalid channel");
        return -RT_EINVAL;
    }

    adc_periph = (uint32_t )(device->parent.user_data);

    if (enabled == ENABLE)
    {
        init_pin4adc(gd32_adc->adc_pins[channel]);
        adc_deinit(adc_periph);
        adc_channel_length_config(adc_periph, ADC_REGULAR_CHANNEL, 1);
        adc_data_alignment_config(adc_periph, ADC_DATAALIGN_RIGHT);
        adc_external_trigger_source_config(adc_periph, ADC_REGULAR_CHANNEL, ADC0_1_2_EXTTRIG_INSERTED_NONE);
        adc_external_trigger_config(adc_periph, ADC_REGULAR_CHANNEL, ENABLE);
        adc_regular_channel_config(adc_periph, 0, channel, ADC_SAMPLETIME_13POINT5);
        adc_enable(adc_periph);
    }
    else
    {
        adc_disable(adc_periph);
    }

    return 0;
}

static rt_err_t gd32_adc_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    uint32_t adc_periph;

    if (!value)
    {
        LOG_E("invalid param");
        return -RT_EINVAL;
    }

    adc_periph = (uint32_t )(device->parent.user_data);
    adc_software_trigger_enable(adc_periph, ADC_REGULAR_CHANNEL);
    *value = adc_regular_data_read(adc_periph);

    return 0;
}

static struct rt_adc_ops g_gd32_adc_ops = {
    gd32_adc_enabled,
    gd32_adc_convert,
};



static int rt_hw_adc_init(void)
{
    int ret, i = 0;

#ifdef BSP_USING_ADC0
    rcu_periph_clock_enable(RCU_ADC0);
#endif

#ifdef BSP_USING_ADC1
    rcu_periph_clock_enable(RCU_ADC1);
#endif

    for (; i < sizeof(g_gd32_devs) / sizeof(g_gd32_devs[0]); i++)
    {
        ret = rt_hw_adc_register(&g_gd32_devs[i].adc_dev, \
            (const char *)g_gd32_devs[i].name, \
            &g_gd32_adc_ops, (void *)g_gd32_devs[i].private_data);
        if (ret != RT_EOK)
        {
            /* TODO err handler */
            LOG_E("failed register %s, err=%d", g_gd32_devs[i].name, ret);
        }
    }

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);
#endif
