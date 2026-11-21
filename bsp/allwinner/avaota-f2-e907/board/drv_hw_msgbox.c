/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include "drv_hw_msgbox.h"

#define CCU_BASE            0x02001000U
#define CCU_MSGBOX_BGR      (CCU_BASE + 0x71cU)
#define MSGBOX_CHAN         0

static uint32_t mmio_r(uint32_t a)
{
    return *(volatile uint32_t *)a;
}

static void mmio_w(uint32_t a, uint32_t v)
{
    *(volatile uint32_t *)a = v;
}

static void fence_io(void)
{
    __asm__ volatile("fence iorw, iorw" ::: "memory");
}

void rt_hw_msgbox_clk_enable(void)
{
    uint32_t v = mmio_r(CCU_MSGBOX_BGR);

    v &= ~((1U << 16) | (1U << 17));
    mmio_w(CCU_MSGBOX_BGR, v);
    v |= (1U << 0) | (1U << 1);
    mmio_w(CCU_MSGBOX_BGR, v);
    v |= (1U << 16) | (1U << 17);
    mmio_w(CCU_MSGBOX_BGR, v);
    fence_io();
}

static uint32_t amp_sta(uint32_t base)
{
    return mmio_r(base + 0x60U + MSGBOX_CHAN * 4U) & 0xfu;
}

static uint32_t amp_dat_r(uint32_t base)
{
    return mmio_r(base + 0x70U + MSGBOX_CHAN * 4U);
}

static void amp_dat_w(uint32_t base, uint32_t v)
{
    mmio_w(base + 0x70U + MSGBOX_CHAN * 4U, v);
    fence_io();
}

void rt_hw_msgbox_kick(uint32_t peer_view, uint32_t token)
{
    /* Drain only if nearly full so we do not drop an unread peer msg. */
    if (amp_sta(peer_view) >= 7U)
        (void)amp_dat_r(peer_view);
    amp_dat_w(peer_view, token);
}

int rt_hw_msgbox_wait(uint32_t local_view, uint32_t *token_out, uint32_t spins)
{
    uint32_t i;

    if (!token_out)
        return -1;

    for (i = 0; i < spins; i++)
    {
        if (amp_sta(local_view) != 0)
        {
            *token_out = amp_dat_r(local_view);
            return 0;
        }
    }
    return -1;
}

int rt_hw_msgbox_phase1_probe(void)
{
    uint32_t ver0;
    uint32_t ver1;

    rt_kprintf("[MSGBOX] phase1 probe start\n");
    rt_hw_msgbox_clk_enable();
    rt_kprintf("[MSGBOX] CCU+0x71c=0x%08x\n", mmio_r(CCU_MSGBOX_BGR));

    ver0 = mmio_r(MSGBOX_VIEW_E907 + 0x10U);
    ver1 = mmio_r(MSGBOX_VIEW_C907 + 0x10U);
    rt_kprintf("[MSGBOX] e907@0x%08x ver=0x%08x c907@0x%08x ver=0x%08x\n",
               MSGBOX_VIEW_E907, ver0, MSGBOX_VIEW_C907, ver1);

    if (ver0 == 0 && ver1 == 0)
    {
        rt_kprintf("[MSGBOX] MSGBOX-FAIL VER zero\n");
        return -1;
    }

    rt_kprintf("[MSGBOX] MSGBOX-LIVE\n");
    return 0;
}

int rt_hw_msgbox_e907_doorbell(void)
{
    rt_hw_msgbox_clk_enable();
    rt_hw_msgbox_kick(MSGBOX_VIEW_C907, MSGBOX_MAGIC);
    rt_kprintf("[MSGBOX] e907 doorbell ->c907 token=0x%08x\n", MSGBOX_MAGIC);
    return 0;
}

int rt_hw_msgbox_c907_wait(uint32_t spins)
{
    uint32_t tok;

    rt_hw_msgbox_clk_enable();
    if (rt_hw_msgbox_wait(MSGBOX_VIEW_C907, &tok, spins) != 0)
    {
        rt_kprintf("[MSGBOX] c907 wait timeout\n");
        return -1;
    }
    rt_kprintf("[MSGBOX] c907 got=0x%08x\n", tok);
    if (tok == MSGBOX_MAGIC)
    {
        rt_kprintf("[MSGBOX] MSGBOX-OK\n");
        return 0;
    }
    return -2;
}
