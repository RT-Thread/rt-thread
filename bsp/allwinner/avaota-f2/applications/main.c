/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>

#include "amp_mbox.h"

static uint32_t g_last_ping;

static void c907_handle_ping(uint32_t req)
{
    if (amp_read(AMP_SLOT_C907) != AMP_MAGIC_C907)
    {
        amp_write(AMP_SLOT_C907, AMP_MAGIC_C907);
    }
    amp_write(AMP_SLOT_C907_REPLY, req + 1U);
    g_last_ping = req;
    rt_kprintf("[C907] hetero ack req=0x%08x reply=0x%08x\n", req, req + 1U);
}

int main(void)
{
    uint32_t req;

    rt_kprintf("[C907] avaota-f2 v861 c907 hetero\n");

    amp_coherent_begin();
    g_last_ping = amp_read(AMP_SLOT_PING_REQ);

    while (1)
    {
        req = amp_read(AMP_SLOT_PING_REQ);
        if (req != 0 && req != g_last_ping)
        {
            c907_handle_ping(req);
        }
        rt_thread_mdelay(1);
    }

    return 0;
}
