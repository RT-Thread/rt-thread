/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-07-13     xiaonong     port for lpc43xx
 */

#include <rtthread.h>
#include <board.h>
#include <rtdevice.h>
#include "drv_led.h"

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <shell.h>
#endif

#ifdef RT_USING_VBUS
#include <vbus.h>
#endif

static const unsigned char _M0_CODE[] rt_section("M0_CODE") = {
#include "M0_CODE.h"
};

static void _boot_M0(void)
{
    volatile uint32_t u32REG,  u32Val;

    LPC_CREG->M0APPMEMMAP = (uint32_t)&_M0_CODE[0];

    // Release Slave from reset,  first read status
    u32REG = LPC_RGU->RESET_ACTIVE_STATUS1;

    // If the M0 is being held in reset,  release it...
    // 1 = no reset,  0 = reset
    while(!(u32REG & (1u << 24)))
    {
        u32Val = (~(u32REG) & (~(1 << 24)));
        LPC_RGU->RESET_CTRL1 = u32Val;
        u32REG = LPC_RGU->RESET_ACTIVE_STATUS1;
    }

    rt_kprintf("M0 boot to %p\n", &_M0_CODE[0]);
}

/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
    /*
     *register unsigned int _msp __asm("msp");
     *register unsigned int _psp __asm("psp");
     *rt_kprintf("msp@ %p, psp@ %p\n", _msp, _psp);
     */

#ifdef RT_USING_FINSH
    /* initialize finsh */
    finsh_system_init();
#if !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE)
    finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
#endif

#ifdef RT_USING_VBUS
    rt_vbus_do_init();
#endif

    _boot_M0();
}

/*the led thread*/
rt_align(RT_ALIGN_SIZE)
static rt_uint8_t led_stack[ 512 ];
static struct rt_thread led_thread;
static void led_thread_entry(void *parameter)
{
    rt_uint8_t led_value;
    rt_device_t led_dev;
    rt_device_t vbus_dev;
    rt_err_t err;

    rt_led_hw_init();

    led_dev = rt_device_find("led");
    if (led_dev == RT_NULL)
    {
        rt_kprintf("can not find the led device\n");
        return;
    }

    vbus_dev = rt_device_find("vecho");
    if (vbus_dev == RT_NULL)
    {
        rt_kprintf("can not find the vbus device\n");
        return;
    }

    err = rt_device_open(vbus_dev, RT_DEVICE_OFLAG_RDWR);
    if (err != RT_EOK)
    {
        rt_kprintf("open vbus failed: %d\n", err);
        return;
    }

    led_value = 0;
    while (1)
    {
        int len;

        led_dev->write(led_dev, 0, &led_value, sizeof(led_value));

        led_value = !led_value;
        len = rt_device_write(vbus_dev, 0, &led_value, sizeof(led_value));
        if (len <= 0)
        {
            rt_kprintf("vbus write err: %d, %d\n", len, rt_get_errno());
        }

        rt_thread_delay(1000);
    }
}

int rt_application_init(void)
{
    rt_thread_t tid;
    rt_err_t result;
    tid = rt_thread_create("init",
                           rt_init_thread_entry, RT_NULL,
                           2048, 3, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    /* init led thread */
    result = rt_thread_init(&led_thread, "led",
                            led_thread_entry, RT_NULL,
                            (rt_uint8_t *)&led_stack[0], sizeof(led_stack),
                            20, 5);
    if (result == RT_EOK)
    {
        rt_thread_startup(&led_thread);
    }
    return 0;
}
