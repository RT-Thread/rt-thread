/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>

#include "amp_mbox.h"
#include "board.h"
#include "board_c907_release.h"

static void busy_delay_loops(volatile uint32_t loops)
{
    while (loops--)
    {
        __asm__ volatile("nop");
    }
}

static int wait_reply(uint32_t expect, uint32_t spins)
{
    uint32_t i;

    for (i = 0; i < spins; i++)
    {
        if (amp_read(AMP_SLOT_C907_REPLY) == expect)
        {
            return 0;
        }
        busy_delay_loops(50U);
    }
    return -1;
}

int main(void)
{
    uint32_t i;
    uint32_t req;
    int ok = 0;

    rt_kprintf("[E907] avaota-f2 v861 e907 hetero\n");

    amp_coherent_begin();
    amp_write(AMP_SLOT_C907, 0);
    amp_write(AMP_SLOT_C907_REPLY, 0);
    amp_write(AMP_SLOT_PING_REQ, 0);
    amp_write(AMP_SLOT_E907, AMP_MAGIC_E907);
    amp_write(AMP_SLOT_E907_STEP, AMP_STEP_UP);

    /* First ping before release — same as proven HETERO path. */
    amp_write(AMP_SLOT_PING_REQ, AMP_PING_REQ);
    rt_kprintf("[E907] ping0=0x%08x before release\n", AMP_PING_REQ);

    rt_hw_c907_release(V861_C907_ENTRY);
    amp_write(AMP_SLOT_E907_STEP, AMP_STEP_RELEASED);

    /* Short spin first; print probe then one longer wait if needed. */
    if (wait_reply(AMP_PING_REQ + 1U, 2000000U) != 0)
    {
        rt_kprintf("[E907] wait1 c907=0x%08x reply=0x%08x ping=0x%08x\n",
                   amp_read(AMP_SLOT_C907), amp_read(AMP_SLOT_C907_REPLY),
                   amp_read(AMP_SLOT_PING_REQ));
        if (wait_reply(AMP_PING_REQ + 1U, 4000000U) != 0 ||
            amp_read(AMP_SLOT_C907) != AMP_MAGIC_C907)
        {
            rt_kprintf("[E907] HETERO-FAIL c907=0x%08x reply=0x%08x ping=0x%08x\n",
                       amp_read(AMP_SLOT_C907), amp_read(AMP_SLOT_C907_REPLY),
                       amp_read(AMP_SLOT_PING_REQ));
            return 0;
        }
    }
    else if (amp_read(AMP_SLOT_C907) != AMP_MAGIC_C907)
    {
        rt_kprintf("[E907] HETERO-FAIL c907=0x%08x reply=0x%08x ping=0x%08x\n",
                   amp_read(AMP_SLOT_C907), amp_read(AMP_SLOT_C907_REPLY),
                   amp_read(AMP_SLOT_PING_REQ));
        return 0;
    }
    rt_kprintf("[E907] HETERO-OK c907=0x%08x reply=0x%08x\n",
               AMP_MAGIC_C907, amp_read(AMP_SLOT_C907_REPLY));
    ok = 1;

    amp_write(AMP_SLOT_E907_STEP, AMP_STEP_RPMSG);

    /* Three more round-trips on the same proven slots. */
    for (i = 1; i <= 3; i++)
    {
        req = 0xB1000000U + i;
        amp_write(AMP_SLOT_C907_REPLY, 0);
        busy_delay_loops(10000U);
        amp_write(AMP_SLOT_PING_REQ, req);
        if (wait_reply(req + 1U, 4000000U) != 0)
        {
            rt_kprintf("[E907] RPMSG-FAIL #%u req=0x%08x reply=0x%08x\n",
                       i, req, amp_read(AMP_SLOT_C907_REPLY));
            ok = 0;
            break;
        }
        rt_kprintf("[E907] rpmsg #%u ack=0x%08x\n", i, req + 1U);
    }

    if (ok)
    {
        rt_kprintf("[E907] RPMSG-OK tx=3 rx=3\n");
    }

    amp_write(AMP_SLOT_E907_STEP, AMP_STEP_OK);
    return 0;
}
