/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include "drv_hw_msgbox.h"

#define CCU_BASE       0x02001000U
#define CCU_MSGBOX_BGR (CCU_BASE + 0x71cU)
#define MSGBOX_CHAN    0

/* Both MSGBOX bank gates (bit0/1) and their reset deassert bits (bit16/17). */
#define MSGBOX_BGR_CLK_BITS ((1U << 0) | (1U << 1))
#define MSGBOX_BGR_RST_BITS ((1U << 16) | (1U << 17))

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

/*
 * Re-entrant MSGBOX bring-up on the C907 side.
 *
 * Releasing the bank resets clears every pending token in both banks, so this
 * side never pulses them: E907 resets the block once before it releases C907,
 * and any reset after that would silently drop a doorbell token that E907 (or
 * this side) has already published, leaving the receiver with a timeout only.
 * Only the gate clocks and reset deassert bits are ensured, and only when they
 * are not already in the expected state.
 */
void rt_hw_msgbox_hw_init(void)
{
    uint32_t v = mmio_r(CCU_MSGBOX_BGR);
    uint32_t want = MSGBOX_BGR_CLK_BITS | MSGBOX_BGR_RST_BITS;

    if ((v & want) == want)
    {
        return;
    }

    mmio_w(CCU_MSGBOX_BGR, v | want);
    fence_io();
}

void rt_hw_msgbox_clk_enable(void)
{
    rt_hw_msgbox_hw_init();
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
    if (amp_sta(peer_view) >= 7U)
    {
        (void)amp_dat_r(peer_view);
    }
    amp_dat_w(peer_view, token);
}

int rt_hw_msgbox_wait(uint32_t local_view, uint32_t *token_out, uint32_t spins)
{
    uint32_t i;

    if (!token_out)
    {
        return -1;
    }

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

int rt_hw_msgbox_c907_wait(uint32_t spins)
{
    uint32_t tok;

    rt_hw_msgbox_clk_enable();
    rt_kprintf("[MSGBOX] c907 wait ver=0x%08x\n",
               mmio_r(MSGBOX_VIEW_C907 + 0x10U));
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
