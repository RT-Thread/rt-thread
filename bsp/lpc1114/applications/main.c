/*
 * Copyright (c) 2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-05     jg1uaa       the first version
 */

#include <rtthread.h>
#include <rthw.h>

/* for Z111xP board (LED is connected to PIO3_5, low=ON) */
#define IOCON_PIO3_5    HWREG32(0x40044048)
#define GPIO3DIR        HWREG32(0x50038000)
#define GPIO3DATA_5     HWREG32(0x50030080)

static void led_off(void)
{
    GPIO3DATA_5 = 0x20;
}

static void led_on(void)
{
    GPIO3DATA_5 = 0x00;
}

static void led_setup(void)
{
    IOCON_PIO3_5 = 0xd0;        // (default)
    GPIO3DIR = 0x20;            // select output
    led_off();
}

static void led_demo(void)
{
    led_setup();

    while (1) {
        led_on();
        rt_thread_delay(50);    // 500msec, tick@100Hz
        led_off();
        rt_thread_delay(50);
    }
}

int main(int argc, char **argv)
{
    rt_kprintf("Hello, world!\n");

    led_demo();

    /* NOTREACHED */
    return 0;
}
