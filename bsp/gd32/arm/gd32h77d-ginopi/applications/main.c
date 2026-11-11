 /*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 * 2023-03-05     yuanzihao    change the LED pins
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED1 pin: PC4 */
#define LED1_PIN GET_PIN(C, 4)
#define VCOM_DEVICE_NAME "vcom"


int main(void)
{
#ifdef BSP_USING_USB_CDC_EXAMPLE
    rt_device_t vcom;
    rt_uint32_t cdc_count = 0;
    char cdc_message[64];
    int cdc_length;
#endif

    /* set LED1 pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);

#ifdef BSP_USING_USB_CDC_EXAMPLE
    vcom = rt_device_find(VCOM_DEVICE_NAME);
    if (vcom == RT_NULL)
    {
        rt_kprintf("cannot find %s device\n", VCOM_DEVICE_NAME);
    }
    else if (rt_device_open(vcom, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX) != RT_EOK)
    {
        rt_kprintf("cannot open %s device\n", VCOM_DEVICE_NAME);
        vcom = RT_NULL;
    }
#endif

    while (1)
    {
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(500);

#ifdef BSP_USING_USB_CDC_EXAMPLE
        if (vcom != RT_NULL)
        {
            cdc_length = rt_snprintf(cdc_message, sizeof(cdc_message),
                                     "GD32H77D USB CDC alive: %u\r\n",
                                     cdc_count++);
            if (cdc_length > 0)
            {
                rt_device_write(vcom, 0, cdc_message, (rt_size_t)cdc_length);
            }
        }
#endif
    }

    return RT_EOK;
}
