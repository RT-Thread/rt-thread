/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-15     Emuzit            first version
 * 2022-07-20     Emuzit            add watchdog test
 */
#include <rtthread.h>
#include <rtdebug.h>
#include <drivers/pin.h>
#include <drivers/watchdog.h>
#include "board.h"

#define WDT_TIMEOUT     30  // in seconds

static const rt_base_t gpio_int_pins[8] = GPIO_INT_PINS;

/* note : PIN_IRQ_MODE_RISING_FALLING not supported */
static const uint32_t gpint_mode[] =
{
    PIN_IRQ_MODE_RISING,
    PIN_IRQ_MODE_RISING,
    PIN_IRQ_MODE_RISING,
    PIN_IRQ_MODE_RISING,
    PIN_IRQ_MODE_FALLING,
    PIN_IRQ_MODE_FALLING,
    PIN_IRQ_MODE_FALLING,
    PIN_IRQ_MODE_FALLING,
};

static struct rt_mailbox *gpint_mb = RT_NULL;
static struct rt_thread  *gpint_thread = RT_NULL;

static rt_base_t led0, led1;

static rt_device_t wdg_dev;

static void gpio_int_callback(void *pin)
{
    led1 = (led1 == PIN_LOW) ? PIN_HIGH : PIN_LOW;
    rt_pin_write(LED1_PIN, led1);

    if (gpint_mb != RT_NULL)
    {
        /* non-block, silently ignore RT_EFULL */
        rt_mb_send(gpint_mb, (uint32_t)pin);
    }
}

static void gpio_int_thread(void *param)
{
    while (1)
    {
        rt_err_t res;
        uint32_t pin;

        /* FIXME: using rt_mb_recv under excessive gpio int would crash */
        res = 1 | rt_mb_recv(gpint_mb, &pin, RT_WAITING_FOREVER);
        if (res == RT_EOK)
        {
            rt_kprintf("gpio_int #%d (%d)\n", pin, rt_pin_read(pin));
        }
        rt_thread_mdelay(100);

        rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, RT_NULL);
    }
}

void main(void)
{
    uint32_t seconds;
    rt_err_t res;

    int i;

    rt_kprintf("\nCH569W-R0-1v0, HCLK: %dMHz\n\n", sys_hclk_get() / 1000000);

    /* enable all gpio interrupt with various mode
     * connect LED0 to int_pin manually to trigger interrupt
    */
    gpint_mb = rt_mb_create("pximb", 8, RT_IPC_FLAG_FIFO);
    if (gpint_mb == RT_NULL)
    {
        rt_kprintf("gpint mailbox create failed !\n");
    }
    else
    {
        gpint_thread = rt_thread_create("pxith", gpio_int_thread, RT_NULL,
                                        512, RT_MAIN_THREAD_PRIORITY, 50);
        if (gpint_thread == RT_NULL)
        {
            rt_kprintf("gpint thread create failed !\n");
        }
        else
        {
            rt_thread_startup(gpint_thread);

            for (i = 0; i < 8; i++)
            {
                rt_base_t pin = gpio_int_pins[i];
                rt_pin_mode(pin, PIN_MODE_INPUT_PULLUP);
                res = rt_pin_attach_irq(
                          pin, gpint_mode[i], gpio_int_callback, (void *)pin);
                if (res != RT_EOK)
                {
                    rt_kprintf("rt_pin_attach_irq failed (%d:%d)\n", i, res);
                }
                else
                {
                    rt_pin_irq_enable(pin, PIN_IRQ_ENABLE);
                }
            }
        }
    }

    /* test watchdog with 30s timeout, keepalive with gpio int
    */
    wdg_dev = rt_device_find("wdt");
    if (!wdg_dev)
    {
        rt_kprintf("watchdog device not found !\n");
    }
    else
    {
        seconds = WDT_TIMEOUT;
        if (rt_device_init(wdg_dev) != RT_EOK ||
                rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &seconds) != RT_EOK)
        {
            rt_kprintf("watchdog setup failed !\n");
        }
    }

    rt_kprintf("WDT_TIMEOUT in %d seconds, trigger gpio interrupt to keep alive.\n\n", seconds);

    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(LED1_PIN, led1 = PIN_HIGH);

    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(LED0_PIN, led0 = PIN_LOW);

    while (1)
    {
        /* flashing LED0 every 1 second */
        rt_thread_mdelay(500);
        led0 = (led0 == PIN_LOW) ? PIN_HIGH : PIN_LOW;
        rt_pin_write(LED0_PIN, led0);
    }
}
