/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <rtthread.h>

#include "board.h"

int main() {
    const uint LED_PIN = 25;

    rt_kprintf("Hello, RT-Thread!\n");

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, 1);
        rt_thread_mdelay(1000);
        gpio_put(LED_PIN, 0);
        rt_thread_mdelay(1000);
    }
}

