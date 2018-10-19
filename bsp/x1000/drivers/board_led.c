/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016/05/13     Urey         the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_gpio.h"

#if 0
#include "board_led.h"

#if defined(BOARD_CANNA)

#define MAX_LED_NBR     3

struct led_io_def led_io_tbl[MAX_LED_NBR] =
{
    //LED_POWER
    {
        GPIO_PORT_C,
        GPIO_Pin_24
    },

    //LED_WIFI
    {
        GPIO_PORT_D,
        GPIO_Pin_5
    },

    //LED_CHARGING
    {
        GPIO_PORT_A,
        GPIO_Pin_0
    },

};

#else
#define MAX_LED_NBR     0
struct led_io_def led_io_tbl[] =
{
    //LED_POWER
    {
        GPIO_PORT_B,
        GPIO_Pin_6
    },
};
#endif

void rt_hw_led_on(int led)
{
    if((led >= LED_LAST) || (led > MAX_LED_NBR))
        return;

    gpio_set_value(led_io_tbl[led].port,led_io_tbl[led].pin,0);
}

void rt_hw_led_off(int led)
{
    if((led >= LED_LAST) || (led > MAX_LED_NBR))
        return;

    gpio_set_value(led_io_tbl[led].port,led_io_tbl[led].pin,1);
}

int rt_hw_led_init(void)
{
    rt_uint8_t  i;

    /* Init all IO for keyboard */
    for (i = 0; i < MAX_LED_NBR; ++i)
    {
        gpio_set_func(led_io_tbl[i].port,led_io_tbl[i].pin,GPIO_OUTPUT1);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_led_init);


#endif
