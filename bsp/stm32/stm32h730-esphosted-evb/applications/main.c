/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-2-2       yekai        first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define LED_PIN    GET_PIN(E, 2)

int main(void) {
    /* set GPIO pin mode to output */
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    while (1) {
        rt_pin_write(LED_PIN, !rt_pin_read(LED_PIN));
        rt_thread_mdelay(1000);
    }
}
