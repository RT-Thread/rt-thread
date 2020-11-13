/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-10-23     yuzrain       the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_adc.h"
#include "md_gpio.h"
#include "md_adc.h"
#include "md_rcu.h"
#include "md_syscfg.h"

#ifdef RT_USING_ADC

#define BSP_ADC_CHANNEL_NUM 8

/* define adc instance */
static struct rt_adc_device _device_adc0;

/* enable or disable adc */
static rt_err_t es32f0_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    RT_ASSERT(device != RT_NULL);

    if (enabled)
    {
        md_adc_enable_ssen_ss0en(ADC);
    }
    else
    {
        md_adc_disable_ssen_ss0en(ADC);
    }

    return RT_EOK;
}

static void _adc_channel_config(rt_uint32_t channel)
{
    /* select gpio pin as adc function */
    switch (channel)
    {
    case  0:
        md_gpio_set_mode(GPIOA, MD_GPIO_PIN_0, MD_GPIO_MODE_ANALOG);
        break;
    case  1:
        md_gpio_set_mode(GPIOA, MD_GPIO_PIN_1, MD_GPIO_MODE_ANALOG);
        break;
    case  2:
        md_gpio_set_mode(GPIOA, MD_GPIO_PIN_2, MD_GPIO_MODE_ANALOG);
        break;
    case  3:
        md_gpio_set_mode(GPIOA, MD_GPIO_PIN_3, MD_GPIO_MODE_ANALOG);
        break;
    case  4:
        md_gpio_set_mode(GPIOA, MD_GPIO_PIN_4, MD_GPIO_MODE_ANALOG);
        break;
    case  5:
        md_gpio_set_mode(GPIOA, MD_GPIO_PIN_5, MD_GPIO_MODE_ANALOG);
        break;
    case  6:
        md_gpio_set_mode(GPIOA, MD_GPIO_PIN_6, MD_GPIO_MODE_ANALOG);
        break;
    case  7:
        md_gpio_set_mode(GPIOA, MD_GPIO_PIN_7, MD_GPIO_MODE_ANALOG);
        break;
    default:
        break;
    }
}

static rt_err_t es32f0_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    rt_uint32_t chn_data[BSP_ADC_CHANNEL_NUM];
    rt_uint32_t i;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    /* config adc channel */
    _adc_channel_config(channel);

    md_adc_set_swtri_ss0(ADC);

    while ((ADC->RIF & ADC_RIF_SS0RIF_MSK) == 0);

    for (i=0; i<BSP_ADC_CHANNEL_NUM; i++)
        chn_data[i] = md_adc_get_ss0_data(ADC);

    *value = chn_data[channel];

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

    md_rcu_enable_apb2en_adcen(RCU);

    md_syscfg_enable_cfg_currgen(SYSCFG);
    md_syscfg_enable_cfg_vrefen(SYSCFG);
    md_syscfg_set_cfg_vlrs(SYSCFG, 7);

    md_adc_set_ss0_con_sel(ADC, MD_ADC_SS_CON_SEL_SW);
    md_adc_set_ss0_con_type(ADC, MD_ADC_SS_CON_TYPE_EDGE);
    md_adc_set_frf_ffrst(ADC);
    md_adc_set_ss0_mux0_mux7(ADC, MD_ADC_SS_MUX_ADIN7);
    md_adc_set_ss0_mux0_mux6(ADC, MD_ADC_SS_MUX_ADIN6);
    md_adc_set_ss0_mux0_mux5(ADC, MD_ADC_SS_MUX_ADIN5);
    md_adc_set_ss0_mux0_mux4(ADC, MD_ADC_SS_MUX_ADIN4);
    md_adc_set_ss0_mux0_mux3(ADC, MD_ADC_SS_MUX_ADIN3);
    md_adc_set_ss0_mux0_mux2(ADC, MD_ADC_SS_MUX_ADIN2);
    md_adc_set_ss0_mux0_mux1(ADC, MD_ADC_SS_MUX_ADIN1);
    md_adc_set_ss0_mux0_mux0(ADC, MD_ADC_SS_MUX_ADIN0);
    md_adc_enable_ier_ss0ie(ADC);
    md_adc_set_ss0_end_end(ADC, 7);
    md_adc_enable_ss0_end_ie7(ADC);
    md_adc_set_gainl_ch7pga(ADC, MD_ADC_GAIN_CHPGA_X2);
    md_adc_set_gainl_ch6pga(ADC, MD_ADC_GAIN_CHPGA_X2);
    md_adc_set_gainl_ch5pga(ADC, MD_ADC_GAIN_CHPGA_X2);
    md_adc_set_gainl_ch4pga(ADC, MD_ADC_GAIN_CHPGA_X2);
    md_adc_set_gainl_ch3pga(ADC, MD_ADC_GAIN_CHPGA_X2);
    md_adc_set_gainl_ch2pga(ADC, MD_ADC_GAIN_CHPGA_X2);
    md_adc_set_gainl_ch1pga(ADC, MD_ADC_GAIN_CHPGA_X2);
    md_adc_set_gainl_ch0pga(ADC, MD_ADC_GAIN_CHPGA_X2);
    md_adc_set_srate(ADC, MD_ADC_SRATE_CLKDIV1 | ADC_SRATE_CKEN_MSK);

    rt_hw_adc_register(&_device_adc0, "adc0", &es32f0_adc_ops, ADC);

    return result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif
