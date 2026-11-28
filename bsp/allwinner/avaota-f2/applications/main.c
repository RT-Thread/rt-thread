/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rthw.h>

#include "amp_mbox.h"
#include "drv_hw_msgbox.h"
#include "drv_mmc.h"
#include "drv_openamp.h"

static uint32_t g_last_req;

static void busy_nop(volatile uint32_t n)
{
    while (n--)
    {
        __asm__ volatile("nop");
    }
}

static int ping_looks_valid(uint32_t req)
{
    if (req == AMP_PING_REQ)
    {
        return 1;
    }
    /* RPMsg-lite / OpenAMP lab used 0xB1000001..3 */
    if ((req & 0xFFFFFF00U) == 0xB1000000U && (req & 0xFFU) >= 1U && (req & 0xFFU) <= 3U)
    {
        return 1;
    }
    return 0;
}

static int wait_new_req(uint32_t *req_out, uint32_t spins)
{
    uint32_t i;
    uint32_t req;

    for (i = 0; i < spins; i++)
    {
        req = amp_read(AMP_SLOT_PING_REQ);
        if (ping_looks_valid(req) && req != g_last_req)
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
    uint32_t tok;

    rt_kprintf("[C907] avaota-f2 v861 c907 hetero\n");

    /* Bring MSGBOX up before the peer can publish a doorbell token. This path
     * only ensures the block (clock gates + reset deassert); it never pulses
     * the bank resets, so a token already sent by E907 is never dropped. */
    rt_hw_msgbox_hw_init();

    /* Publish magic early so E907 can sync before doorbell. */
    amp_coherent_begin();
    g_last_req = 0;
    amp_write(AMP_SLOT_C907, AMP_MAGIC_C907);
    rt_kprintf("[C907] magic=0xc907a11c\n");

    /* Optional Phase1 MAGIC (may arrive after magic). Non-fatal. */
    if (rt_hw_msgbox_wait(MSGBOX_VIEW_C907, &tok, 2000000U) == 0 &&
        tok == MSGBOX_MAGIC)
    {
        rt_kprintf("[MSGBOX] MSGBOX-OK\n");
    }

    if (wait_new_req(&req, 4000000U) != 0)
    {
        rt_kprintf("[C907] no ping (solo) — mmc then msh\n");
        (void)rt_hw_mmc0_probe_from_fdt();
        return 0;
    }
    amp_write(AMP_SLOT_C907_REPLY, req + 1U);
    rt_kprintf("[C907] ping_req=0x%08x reply=0x%08x\n", req, req + 1U);

    if (openamp_slave_start(8000000U) != 0)
    {
        rt_kprintf("[C907] OPENAMP-EPT-FAIL link\n");
        return 0;
    }

    for (i = 1; i <= 3; i++)
    {
        if (openamp_echo_once(16000000U) != 0)
        {
            rt_kprintf("[C907] OPENAMP-EPT-FAIL echo #%u\n", i);
            break;
        }
    }

    return 0;
}
