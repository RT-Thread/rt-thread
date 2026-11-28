/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * AMP mailbox API on the proven ping/reply slots (same path as HETERO-OK).
 */

#include "amp_mbox.h"
#include "drv_amp_mailbox.h"

static int g_is_e907;
static uint32_t g_last_req;

static void busy_nop(volatile uint32_t n)
{
    while (n--)
    {
        __asm__ volatile("nop");
    }
}

uint32_t amp_mailbox_msgbox_probe(void)
{
    uint32_t ver = *(volatile uint32_t *)AMP_MSGBOX_VER;
    amp_write(AMP_MSGBOX_PROBE, ver);
    return ver;
}

int amp_mailbox_init(int is_e907)
{
    g_is_e907 = is_e907;
    g_last_req = amp_read(AMP_SLOT_PING_REQ);
    amp_coherent_begin();
    return 0;
}

int amp_mailbox_send(uint32_t data)
{
    uint32_t i;
    uint32_t expect;

    if (!g_is_e907)
    {
        return -1;
    }

    expect = data + 1U;
    amp_write(AMP_SLOT_C907_REPLY, 0);
    amp_write(AMP_SLOT_PING_REQ, data);
    g_last_req = data;

    for (i = 0; i < 8000000U; i++)
    {
        if (amp_read(AMP_SLOT_C907_REPLY) == expect)
        {
            return 0;
        }
        busy_nop(50U);
    }
    return -1;
}

int amp_mailbox_recv(uint32_t *data, uint32_t timeout_loops)
{
    uint32_t i;
    uint32_t req;

    if (!data)
    {
        return -1;
    }

    if (g_is_e907)
    {
        /* E907 recv = wait for C907 reply already handled in send. */
        *data = amp_read(AMP_SLOT_C907_REPLY);
        return 0;
    }

    for (i = 0; i < timeout_loops; i++)
    {
        req = amp_read(AMP_SLOT_PING_REQ);
        if (req != 0 && req != g_last_req)
        {
            *data = req;
            g_last_req = req;
            return 0;
        }
        busy_nop(50U);
    }
    return -1;
}

int amp_mailbox_ack(uint32_t data)
{
    if (g_is_e907)
    {
        return -1;
    }
    amp_write(AMP_SLOT_C907_REPLY, data);
    return 0;
}
