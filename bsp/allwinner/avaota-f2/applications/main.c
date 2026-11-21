/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rthw.h>

#include "amp_mbox.h"

static uint32_t g_last_req;

static void busy_nop(volatile uint32_t n)
{
    while (n--)
        __asm__ volatile("nop");
}

static int wait_new_req(uint32_t *req_out, uint32_t spins)
{
    uint32_t i;
    uint32_t req;

    for (i = 0; i < spins; i++)
    {
        req = amp_read(AMP_SLOT_PING_REQ);
        if (req != 0 && req != g_last_req)
        {
            *req_out = req;
            g_last_req = req;
            return 0;
        }
        busy_nop(50U);
    }
    return -1;
}

int main(void)
{
    uint32_t i;
    uint32_t req;
    uint32_t ver;
    int tx = 0;
    int rx = 0;

    rt_kprintf("[C907] avaota-f2 v861 c907 hetero\n");

    amp_coherent_begin();
    g_last_req = 0;
    amp_write(AMP_SLOT_C907, AMP_MAGIC_C907);
    rt_kprintf("[C907] magic=0xc907a11c\n");

    /* Hetero: E907 wrote ping before release. Solo C907-boot: timeout → msh. */
    if (wait_new_req(&req, 4000000U) != 0)
    {
        rt_kprintf("[C907] no ping (solo) — skip hetero\n");
        return 0;
    }
    amp_write(AMP_SLOT_C907_REPLY, req + 1U);
    rx++;
    tx++;
    rt_kprintf("[C907] ping_req=0x%08x reply=0x%08x\n", req, req + 1U);

    ver = *(volatile uint32_t *)AMP_MSGBOX_VER;
    rt_kprintf("[C907] MSGBOX ver@0x03003010=0x%08x\n", ver);

    /* Three more round-trips on the same slots (RPMsg-lite shape). */
    for (i = 1; i <= 3; i++)
    {
        if (wait_new_req(&req, 16000000U) != 0)
        {
            rt_kprintf("[C907] RPMSG-FAIL wait #%u last=0x%08x\n", i, g_last_req);
            break;
        }
        amp_write(AMP_SLOT_C907_REPLY, req + 1U);
        rx++;
        tx++;
        /* Stay quiet — shared UART with E907; E907 prints RPMSG-OK. */
    }

    (void)tx;
    (void)rx;

    return 0;
}
