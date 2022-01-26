/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-04-14     ArdaFu      first version
 */

#include <rtthread.h>
#include <board.h>
#include "led.h"
#include "gpio.h"

//ASM9260T EVK pin 16-7 LED0, 0: ON, 1 : OFF
void led_init(void)
{
     // enable IOCONFIG GPIO
    outl(((1UL<<25) | (1UL<<4)) , REG_SET(HW_AHBCLKCTRL0));
    HW_SetPinMux(16,7,0);
    HW_GpioSetDir(16,7,1);
}

void led_on(int num)
{
    HW_GpioClrVal(16, 7 );
}

void led_off(int num)
{
    HW_GpioSetVal(16, 7 );
}
