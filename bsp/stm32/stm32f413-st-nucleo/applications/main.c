/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED1 pin: PB0 */
#define LED1_PIN    GET_PIN(B, 0)
/* defined the LED2 pin: PB7 */
#define LED2_PIN    GET_PIN(B, 7)
/* defined the LED3 pin: PB14 */
#define LED3_PIN    GET_PIN(B, 14)
/* defined the USER KEY pin: PC13 */
#define KEY_PIN    GET_PIN(C, 13)

int main(void)
{
    /* set LED1 pin mode to output */
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
