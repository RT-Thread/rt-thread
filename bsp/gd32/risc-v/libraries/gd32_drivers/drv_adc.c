/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-05-03     BruceOu           optimization adc
 */

#include "drv_adc.h"

#define DBG_TAG             "drv.adc"
#define DBG_LVL             DBG_INFO

#include <rtdbg.h>

#ifdef RT_USING_ADC

#if defined(BSP_USING_ADC0)
struct rt_adc_device adc0;
#endif

#if defined(BSP_USING_ADC1)
struct rt_adc_device adc1;
#endif

#if defined(BSP_USING_ADC2)
struct rt_adc_device adc2;
#endif

#define MAX_EXTERN_ADC_CHANNEL    16

static const struct gd32_adc adc_obj[] = {
#ifdef BSP_USING_ADC0
    {
        ADC0,
        RCU_ADC0,
        {
            GET_PIN(A, 0), GET_PIN(A, 1), GET_PIN(A, 2), GET_PIN(A, 3),
            GET_PIN(A, 4), GET_PIN(A, 5), GET_PIN(A, 6), GET_PIN(A, 7),
            GET_PIN(B, 0), GET_PIN(B, 1), GET_PIN(C, 0), GET_PIN(C, 1),
            GET_PIN(C, 2), GET_PIN(C, 3), GET_PIN(C, 4), GET_PIN(C, 5),
        },
        &adc0,
        "adc0",
    },
#endif

#ifdef BSP_USING_ADC1
    {
        ADC1,
        RCU_ADC1,
        {
            GET_PIN(A, 0), GET_PIN(A, 1), GET_PIN(A, 2), GET_PIN(A, 3),
            GET_PIN(A, 4), GET_PIN(A, 5), GET_PIN(A, 6), GET_PIN(A, 7),
            GET_PIN(B, 0), GET_PIN(B, 1), GET_PIN(C, 0), GET_PIN(C, 1),
            GET_PIN(C, 2), GET_PIN(C, 3), GET_PIN(C, 4), GET_PIN(C, 5),
        },
        &adc1,
        "adc1",
    },
#endif
#ifdef BSP_USING_ADC2
    {
        ADC2,
        RCU_ADC2,
        {
            GET_PIN(A, 0), GET_PIN(A, 1), GET_PIN(A, 2), GET_PIN(A, 3),
            GET_PIN(A, 4), GET_PIN(A, 5), GET_PIN(A, 6), GET_PIN(A, 7),
            GET_PIN(B, 0), GET_PIN(B, 1), GET_PIN(C, 0), GET_PIN(C, 1),
            GET_PIN(C, 2), GET_PIN(C, 3), GET_PIN(C, 4), GET_PIN(C, 5),
        },
        &adc2,
        "adc2",
    },
#endif
};

/**
* @brief ADC MSP Initialization
*        This function configures the hardware resources.
* @param adc_clk, pin
* @retval None
*/
static void gd32_adc_gpio_init(rcu_periph_enum adc_clk, rt_base_t pin)
{
    /* enable ADC clock */
    rcu_periph_clock_enable(adc_clk);

    /* configure adc pin */
    gpio_init(PIN_GDPORT(pin), GPIO_MODE_AIN, GPIO_OSPEED_50MHZ, PIN_GDPIN(pin));

}

/**
* @brief ADC enable
*        This function enable adc.
* @param device, channel, enabled
* @retval None
*/
static rt_err_t gd32_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    uint32_t adc_periph;
    struct gd32_adc * adc = (struct gd32_adc *)device->parent.user_data;

    if (channel >= MAX_EXTERN_ADC_CHANNEL)
    {
        LOG_E("invalid channel");
        return -RT_EINVAL;
    }

    adc_periph = (uint32_t )(adc->adc_periph);

    if (enabled == ENABLE)
    {
        gd32_adc_gpio_init(adc->adc_clk, adc->adc_pins[channel]);

        adc_channel_length_config(adc_periph, ADC_REGULAR_CHANNEL, 1);
        adc_data_alignment_config(adc_periph, ADC_DATAALIGN_RIGHT);

        adc_external_trigger_source_config(adc_periph, ADC_REGULAR_CHANNEL, ADC0_1_2_EXTTRIG_REGULAR_NONE);
        adc_external_trigger_config(adc_periph, ADC_REGULAR_CHANNEL, ENABLE);

        adc_regular_channel_config(adc_periph, 0, channel, ADC_SAMPLETIME_13POINT5);

        adc_enable(adc_periph);

        /* ADC calibration and reset calibration */
        adc_calibration_enable(adc_periph);
    }
    else
    {
        adc_disable(adc_periph);
    }
    return 0;
}

/**
* @brief convert adc.
*        This function get adc value.
* @param device, channel, value
* @retval None
*/
static rt_err_t gd32_adc_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    uint32_t adc_periph;
    struct gd32_adc * adc = (struct gd32_adc *)(device->parent.user_data);

    if (!value)
    {
        LOG_E("invalid param");
        return -RT_EINVAL;
    }

    adc_periph = (uint32_t )(adc->adc_periph);
    adc_software_trigger_enable(adc_periph, ADC_REGULAR_CHANNEL);

    while(!adc_flag_get(adc_periph, ADC_FLAG_EOC)){};
    // clear flag
    adc_flag_clear(adc_periph, ADC_FLAG_EOC);

    *value = adc_regular_data_read(adc_periph);

    return 0;
}

static struct rt_adc_ops gd32_adc_ops = {
    .enabled = gd32_adc_enabled,
    .convert = gd32_adc_convert,
};

static int rt_hw_adc_init(void)
{
    int ret, i = 0;

    for (; i < sizeof(adc_obj) / sizeof(adc_obj[0]); i++)
    {
        ret = rt_hw_adc_register(adc_obj[i].adc, \
            (const char *)adc_obj[i].device_name, \
            &gd32_adc_ops, &adc_obj[i]);
        if (ret != RT_EOK)
        {
            /* TODO err handler */
            LOG_E("failed register %s, err=%d", adc_obj[i].device_name, ret);
        }
    }

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);
#endif
