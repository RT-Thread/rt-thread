/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-29     tyustli      first version
 */

#include "MIMXRT1064.h"
#include <rtdevice.h>
#include "drv_gpio.h"
#include "core_cm7.h"

/* defined the LED pin: GPIO1_IO9 */
#define LED0_PIN               GET_PIN(1, 9)

int main(void)
{
#ifndef PHY_USING_KSZ8081
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
#endif
}

void reboot(void)
{
    NVIC_SystemReset();
}
MSH_CMD_EXPORT(reboot, reset system)
