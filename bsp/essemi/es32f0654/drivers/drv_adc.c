/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-04-03     wangyq        the first version
 * 2019-11-01     wangyq        update libraries
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_adc.h"
#include <ald_gpio.h>
#include <ald_adc.h>

#ifdef RT_USING_ADC

/* define adc instance */
static struct rt_adc_device _device_adc0;

/* enable or disable adc */
static rt_err_t es32f0_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    adc_handle_t *_hadc = (adc_handle_t *)device->parent.user_data;

    RT_ASSERT(device != RT_NULL);

    if (enabled)
    {
        ADC_ENABLE(_hadc); ;
    }
    else
    {
        ADC_DISABLE(_hadc);
    }

    return RT_EOK;
}

static adc_channel_t es32f0_adc_get_channel(rt_uint32_t channel)
{
    adc_channel_t es32f0_channel;
    gpio_init_t gpio_initstruct;

    /* Initialize ADC pin */
    gpio_initstruct.mode = GPIO_MODE_INPUT;
    gpio_initstruct.pupd = GPIO_FLOATING;
    gpio_initstruct.odrv = GPIO_OUT_DRIVE_NORMAL;
    gpio_initstruct.flt  = GPIO_FILTER_DISABLE;
    gpio_initstruct.type = GPIO_TYPE_CMOS;
    gpio_initstruct.func = GPIO_FUNC_0;

    /* select gpio pin as adc function */
    switch (channel)
    {
    case  0:
        es32f0_channel = ADC_CHANNEL_0;
        ald_gpio_init(GPIOC, GPIO_PIN_0, &gpio_initstruct);
        break;
    case  1:
        es32f0_channel = ADC_CHANNEL_1;
        ald_gpio_init(GPIOC, GPIO_PIN_1, &gpio_initstruct);
        break;
    case  2:
        es32f0_channel = ADC_CHANNEL_2;
        ald_gpio_init(GPIOC, GPIO_PIN_2, &gpio_initstruct);
        break;
    case  3:
        es32f0_channel = ADC_CHANNEL_3;
        ald_gpio_init(GPIOC, GPIO_PIN_3, &gpio_initstruct);
        break;
    case  4:
        es32f0_channel = ADC_CHANNEL_4;
        ald_gpio_init(GPIOA, GPIO_PIN_0, &gpio_initstruct);
        break;
    case  5:
        es32f0_channel = ADC_CHANNEL_5;
        ald_gpio_init(GPIOA, GPIO_PIN_1, &gpio_initstruct);
        break;
    case  6:
        es32f0_channel = ADC_CHANNEL_6;
        ald_gpio_init(GPIOA, GPIO_PIN_2, &gpio_initstruct);
        break;
    case  7:
        es32f0_channel = ADC_CHANNEL_7;
        ald_gpio_init(GPIOA, GPIO_PIN_3, &gpio_initstruct);
        break;
    case  8:
        es32f0_channel = ADC_CHANNEL_8;
        ald_gpio_init(GPIOA, GPIO_PIN_4, &gpio_initstruct);
        break;
    case  9:
        es32f0_channel = ADC_CHANNEL_9;
        ald_gpio_init(GPIOA, GPIO_PIN_5, &gpio_initstruct);
        break;
    case 10:
        es32f0_channel = ADC_CHANNEL_10;
        ald_gpio_init(GPIOA, GPIO_PIN_6, &gpio_initstruct);
        break;
    case 11:
        es32f0_channel = ADC_CHANNEL_11;
        ald_gpio_init(GPIOA, GPIO_PIN_7, &gpio_initstruct);
        break;
    case 12:
        es32f0_channel = ADC_CHANNEL_12;
        ald_gpio_init(GPIOC, GPIO_PIN_4, &gpio_initstruct);
        break;
    case 13:
        es32f0_channel = ADC_CHANNEL_13;
        ald_gpio_init(GPIOC, GPIO_PIN_5, &gpio_initstruct);
        break;
    case 14:
        es32f0_channel = ADC_CHANNEL_14;
        ald_gpio_init(GPIOB, GPIO_PIN_0, &gpio_initstruct);
        break;
    case 15:
        es32f0_channel = ADC_CHANNEL_15;
        ald_gpio_init(GPIOB, GPIO_PIN_1, &gpio_initstruct);
        break;
    case 16:
        es32f0_channel = ADC_CHANNEL_16;
        break;
    case 17:
        es32f0_channel = ADC_CHANNEL_17;
        break;
    case 18:
        es32f0_channel = ADC_CHANNEL_18;
        break;
    default:
        break;
    }

    return es32f0_channel;
}

static rt_err_t es32f0_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    adc_handle_t *_hadc = (adc_handle_t *)device->parent.user_data;
    adc_nch_conf_t nm_config;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    /* config adc channel */
    nm_config.channel       = es32f0_adc_get_channel(channel);
    nm_config.rank          = ADC_NCH_RANK_1;
    nm_config.samp_time = ADC_SAMPLETIME_4;
    ald_adc_normal_channel_config(_hadc, &nm_config);

    ald_adc_normal_start(_hadc);

    if (ald_adc_normal_poll_for_conversion(_hadc, 5000) == OK)
        *value = ald_adc_normal_get_value(_hadc);

    return RT_EOK;
}

static const struct rt_adc_ops es32f0_adc_ops =
{
    es32f0_adc_enabled,
    es32f0_get_adc_value,
};

int rt_hw_adc_init(void)
{
    int result = RT_EOK;
    static adc_handle_t _h_adc0;

    /* adc function initialization */
    _h_adc0.perh = ADC0;
    _h_adc0.init.data_align = ADC_DATAALIGN_RIGHT;
    _h_adc0.init.scan_mode = DISABLE;
    _h_adc0.init.cont_mode = DISABLE;
    _h_adc0.init.disc_mode = ADC_ALL_DISABLE;
    _h_adc0.init.disc_nbr = ADC_DISC_NBR_1;
    _h_adc0.init.conv_res = ADC_CONV_RES_10;
    _h_adc0.init.clk_div = ADC_CKDIV_128;
    _h_adc0.init.nche_sel = ADC_NCHESEL_MODE_ALL;
    _h_adc0.init.neg_ref = ADC_NEG_REF_VSS;
    _h_adc0.init.pos_ref = ADC_POS_REF_VDD;
    ald_adc_init(&_h_adc0);

    rt_hw_adc_register(&_device_adc0, "adc0", &es32f0_adc_ops, &_h_adc0);

    return result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif
