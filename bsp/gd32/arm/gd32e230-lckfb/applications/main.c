/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-28     Yunkun Huang    Init Project
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


#define LED_PIN BSP_LED_PIN


static void led_blink_thread_entry(void *parameter)
{
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    rt_kprintf("LED blink thread started.\n");

    while (1)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);

        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}

#define UART_DEVICE_NAME "uart0"

static void uart_send_thread_entry(void *parameter)
{
    rt_device_t console_dev;
    char msg[] = "hello rt-thread\r\n";

    console_dev = rt_console_get_device();

    if (!console_dev)
    {
        rt_kprintf("Failed to get console device.\n");
        return;
    }

    rt_kprintf("UART send thread started. Will send message every 2 seconds.\n");

    while (1)
    {
        rt_device_write(console_dev, 0, msg, (sizeof(msg) - 1));
        rt_thread_mdelay(2000);
    }
}


int main(void)
{
    rt_thread_t led_tid = RT_NULL;
    rt_thread_t uart_tid = RT_NULL;

    led_tid = rt_thread_create("led_blink",
                               led_blink_thread_entry,
                               RT_NULL,
                               256,
                               20,
                               10);

    if (led_tid != RT_NULL)
    {
        rt_thread_startup(led_tid);
    }
    else
    {
        rt_kprintf("Failed to create led_blink thread.\n");
    }

    uart_tid = rt_thread_create("uart_send",
                                uart_send_thread_entry,
                                RT_NULL,
                                512,
                                21,
                                10);

    if (uart_tid != RT_NULL)
    {
        rt_kprintf("uart_send thread created successfully. Starting it up...\n");
        rt_thread_startup(uart_tid);
    }
    else
    {
        rt_kprintf("!!! FAILED to create uart_send thread. Not enough memory?\n");
    }

    return 0;
}

