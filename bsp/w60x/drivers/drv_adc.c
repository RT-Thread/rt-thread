/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-23     fanwenl      1st version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "wm_io.h"
#include "wm_adc.h"
#include "wm_gpio_afsel.h"
#include "drv_adc.h"

#ifdef BSP_USING_ADC
#if defined(USING_ADC_CH1) || defined(USING_ADC_CH2) || defined(USING_ADC_CH3) || defined(USING_ADC_CH4) || \
    defined(USING_ADC_CH5) || defined(USING_ADC_CH6) || defined(USING_ADC_CH7) || defined(USING_ADC_CH8)

static rt_err_t wm_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    if (channel < 1 || channel > 8)
        return -RT_ERROR;

    if (enabled == RT_TRUE)
    {
        tls_adc_start_with_cpu(channel - 1);
    }
    else
    {
        tls_adc_stop(0);
    }
    return RT_EOK;
}

static rt_err_t wm_adc_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    if (channel < 1 || channel > 8)
        return -RT_ERROR;

    *value = adc_get_inputVolt(channel - 1) ;

    return RT_EOK;
}

static struct rt_adc_ops wm_adc_ops =
{
    wm_adc_enabled,
    wm_adc_convert,
};
static struct rt_adc_device wm_adc;
#endif

#ifdef USING_CPU_TEMP
static rt_err_t wm_cpu_temp_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    if (enabled == RT_FALSE)
    {
        tls_adc_stop(0);
    }
    return RT_EOK;

}

static rt_err_t wm_cpu_temp_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    *value = (rt_uint32_t)adc_temp();

    /**
    sprintf(temperature, "%d.%d", *value/1000, (*value%1000)/100);
    printf("tem: %s", temperature);
    */

    return RT_EOK;
}

static struct rt_adc_ops wm_cpu_temp_ops =
{
    wm_cpu_temp_enabled,
    wm_cpu_temp_convert,
};
static struct rt_adc_device wm_cpu_temp;
#endif

int wm_hw_adc_init(void)
{
    /*adc io config*/
#ifdef USING_ADC_CH1
    wm_adc_config(0);
#endif
#ifdef USING_ADC_CH2
    wm_adc_config(1);
#endif
#ifdef USING_ADC_CH3
    wm_adc_config(2);
#endif
#ifdef USING_ADC_CH4
    wm_adc_config(3);
#endif
#ifdef USING_ADC_CH5
    wm_adc_config(4);
#endif
#ifdef USING_ADC_CH6
    wm_adc_config(5);
#endif
#ifdef USING_ADC_CH7
    wm_adc_config(6);
#endif
#ifdef USING_ADC_CH8
    wm_adc_config(7);
#endif

#if defined(USING_ADC_CH1) || defined(USING_ADC_CH2) || defined(USING_ADC_CH3) || defined(USING_ADC_CH4) || \
    defined(USING_ADC_CH5) || defined(USING_ADC_CH6) || defined(USING_ADC_CH7) || defined(USING_ADC_CH8)

    rt_hw_adc_register(&wm_adc, "adc", &wm_adc_ops, 0);
#endif

#ifdef USING_CPU_TEMP
    rt_hw_adc_register(&wm_cpu_temp, "cputemp", &wm_cpu_temp_ops, 0);
#endif

    return RT_EOK;
}
INIT_DEVICE_EXPORT(wm_hw_adc_init);

#endif /* BSP_USING_ADC */
