/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 * 2018-11-19     flybreak     add stm32f407-atk-explorer bsp
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include <fal.h>

#include <sys/socket.h>
#include <netdev.h>


/* defined the LED0 pin: PF9 */
#define LED0_PIN    GET_PIN(F, 9)

int main(void)
{
    int count = 1;
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);

    if (fal_init() < 0)
    {
        rt_kprintf("fal init failed!\n");
    }

#ifdef RT_USING_NETDEV
    netdev_set_default(netdev_get_by_name(TC_NETDEV_LWIP_NAME));
#endif

    while (count++)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
