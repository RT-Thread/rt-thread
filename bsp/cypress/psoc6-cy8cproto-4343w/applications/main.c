/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-29     Rbb666       first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "drv_gpio.h"

#define LED_PIN		GET_PIN(13, 7)

int main(void)
{
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    for (;;)
    {
        rt_pin_write(CYBSP_USER_LED, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(CYBSP_USER_LED, PIN_LOW);
        rt_thread_mdelay(1000);
    }
}

#define KEY0_PIN_NUM		GET_PIN(0, 4)

void btn_test(void *args)
{
    rt_kprintf("down button!\n");
}

static void pin_btn_sample(void)
{
    rt_pin_mode(KEY0_PIN_NUM, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(KEY0_PIN_NUM, PIN_IRQ_MODE_FALLING, btn_test, RT_NULL);
    rt_pin_irq_enable(KEY0_PIN_NUM, PIN_IRQ_ENABLE);

}
MSH_CMD_EXPORT(pin_btn_sample, pin button sample);

#if defined(BSP_USING_ADC1)
static int adc_vol_sample(int argc, char *argv[])
{
    rt_adc_device_t adc_dev;
    rt_uint32_t value, vol;
    rt_err_t ret = RT_EOK;

    adc_dev = (rt_adc_device_t)rt_device_find("adc1");
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", "adc1");
        return RT_ERROR;
    }

    ret = rt_adc_enable(adc_dev, 10);

    while (1)
    {
        value = rt_adc_read(adc_dev, 10);
        rt_kprintf("the value is :%d \n", value);

        vol = value * 330 / (1 << 12);
        rt_kprintf("the voltage is :%d.%02d \n", vol / 100, vol % 100);

        rt_thread_mdelay(500);
    }

    return ret;
}
MSH_CMD_EXPORT(adc_vol_sample, adc voltage convert sample);

#endif
