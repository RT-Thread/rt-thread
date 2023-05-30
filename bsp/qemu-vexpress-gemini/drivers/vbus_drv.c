/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-07     Grissiom     add comment
 */

#include <rtthread.h>

#ifdef RT_USING_VBUS
#include <rtdevice.h>
#include <rthw.h>
#include <interrupt.h>
#include <vbus.h>
#include <board.h>

int rt_vbus_do_init(void)
{
    return rt_vbus_init((void*)_RT_VBUS_RING_BASE,
                        (void*)(_RT_VBUS_RING_BASE + _RT_VBUS_RING_SZ));
}
INIT_COMPONENT_EXPORT(rt_vbus_do_init);

static void _bus_resume_in_thread(int irqnr, void *param)
{
    rt_vbus_isr(irqnr, RT_NULL);
}

int rt_vbus_hw_init(void)
{
    rt_kprintf("install irq: %d\n", RT_VBUS_HOST_VIRQ);
    rt_hw_interrupt_install(RT_VBUS_HOST_VIRQ,
                            _bus_resume_in_thread, RT_NULL,
                            "vbusin");
    rt_hw_interrupt_umask(RT_VBUS_HOST_VIRQ);

    return 0;
}

int rt_vbus_hw_eoi(int irqnr, void *param)
{
    rt_hw_interrupt_clear(irqnr);

    return 0;
}

#define RT_VBUS_SER_PRIO  20
#define RT_VBUS_RFS_PRIO  19
#define RT_VBUS_TASK2_PRIO 6
#define RT_VBUS_INT_PRIO   4

struct rt_vbus_dev rt_vbus_chn_devx[] = {
    {
        .req =
        {
            .prio = RT_VBUS_SER_PRIO,
            .name = RT_VBUS_SHELL_DEV_NAME,
            .is_server = 1,
            .recv_wm.low = RT_VMM_RB_BLK_NR / 3,
            .recv_wm.high = RT_VMM_RB_BLK_NR * 2 / 3,
            .post_wm.low = RT_VMM_RB_BLK_NR / 3,
            .post_wm.high = RT_VMM_RB_BLK_NR * 2 / 3,
        }
    },
    {
        .req =
        {
            .prio = 23,
            .name = RT_VBUS_RFS_DEV_NAME,
            .is_server = 0,
            .recv_wm.low = RT_VMM_RB_BLK_NR / 3,
            .recv_wm.high = RT_VMM_RB_BLK_NR * 2 / 3,
            .post_wm.low = RT_VMM_RB_BLK_NR / 3,
            .post_wm.high = RT_VMM_RB_BLK_NR * 2 / 3,
        }
    },
    {
        .req =
        {
            .prio = 30,
            .name = "vecho",
            .is_server = 1,
            .recv_wm.low = RT_VMM_RB_BLK_NR / 3,
            .recv_wm.high = RT_VMM_RB_BLK_NR * 2 / 3,
            .post_wm.low = RT_VMM_RB_BLK_NR / 3,
            .post_wm.high = RT_VMM_RB_BLK_NR * 2 / 3,
        }
    },
    {
        .req =
        {
            .name = RT_NULL,
        }
    },
};

#endif /* RT_USING_VBUS */

