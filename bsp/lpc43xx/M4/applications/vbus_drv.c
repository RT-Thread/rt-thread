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
#include <vbus.h>
#include <board.h>

struct rt_vbus_ring rt_vbus_rings[2] RT_SECTION("vbus_ring");

int rt_vbus_do_init(void)
{
    return rt_vbus_init(&rt_vbus_rings[0], &rt_vbus_rings[1]);
}
INIT_COMPONENT_EXPORT(rt_vbus_do_init);

int rt_vbus_hw_init(void)
{
    NVIC_ClearPendingIRQ(M0CORE_IRQn);
    NVIC_EnableIRQ(M0CORE_IRQn);
    return 0;
}

void M0CORE_IRQHandler(void)
{
    LPC_CREG->M0TXEVENT = 0;
    rt_vbus_isr(M0CORE_IRQn, RT_NULL);
}

int rt_vbus_hw_eoi(int irqnr, void *param)
{
    /* Nothing to do here as we cleared the interrupt in IRQHandler. */
    return 0;
}

struct rt_vbus_dev rt_vbus_chn_devx[] = {
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

