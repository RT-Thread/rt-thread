/*
 * Copyright (c) 2015-2019, Leap Value IOT Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-08-15     flyu    change to new framework
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "drv_gpio.h"

#define LED_PIN GET_PIN(A, 2)

int main(void)
{
    int count = 1;
    rt_pin_mode(LED_PIN,PIN_MODE_OUTPUT);
    while (count++)
    {
        rt_pin_write(LED_PIN, !rt_pin_read(LED_PIN));
        rt_thread_mdelay(500);
    }
    return RT_EOK;
}
