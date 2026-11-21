/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * C907 uses slave path; shared source with E907. SHM @ 0x41001000 + HW MSGBOX kicks.
 */

#include <rtthread.h>
#include <string.h>

#include "amp_mbox.h"
#include "drv_hw_msgbox.h"
#include "drv_openamp.h"

#define OA_MAGIC            0x0A11C0DEU
#define OA_LINK_IDLE        0U
#define OA_LINK_MASTER      1U
#define OA_LINK_UP          2U

/* Word offsets from OA_SHM_BASE */
#define OFF_MAGIC           0x00U
#define OFF_LINK            0x04U
#define OFF_NAME            0x08U   /* 16 bytes */
#define OFF_M2S_SEQ         0x18U
#define OFF_M2S_LEN         0x1cU
#define OFF_M2S_PAY         0x20U   /* 64 bytes */
#define OFF_S2M_SEQ         0x60U
#define OFF_S2M_LEN         0x64U
#define OFF_S2M_PAY         0x68U   /* 64 bytes */
#define OFF_M2S_ACK         0xa8U
#define OFF_S2M_ACK         0xacU

static int g_is_master;
static uint32_t g_tx_seq;

static void oa_w32(uint32_t off, uint32_t v)
{
    amp_write(OA_SHM_BASE + off, v);
}

static uint32_t oa_r32(uint32_t off)
{
    return amp_read(OA_SHM_BASE + off);
}

static void oa_write_bytes(uint32_t off, const uint8_t *src, uint32_t len)
{
    uint32_t i;
    uint32_t addr = OA_SHM_BASE + off;

    for (i = 0; i < len; i += 4U)
    {
        uint32_t w = 0;
        uint32_t n = len - i;
        uint32_t b;

        if (n > 4U)
            n = 4U;
        for (b = 0; b < n; b++)
            w |= ((uint32_t)src[i + b]) << (8U * b);
        amp_write(addr + i, w);
    }
}

static void oa_read_bytes(uint32_t off, uint8_t *dst, uint32_t len)
{
    uint32_t i;
    uint32_t addr = OA_SHM_BASE + off;

    for (i = 0; i < len; i += 4U)
    {
        uint32_t w = amp_read(addr + i);
        uint32_t n = len - i;
        uint32_t b;

        if (n > 4U)
            n = 4U;
        for (b = 0; b < n; b++)
            dst[i + b] = (uint8_t)((w >> (8U * b)) & 0xffU);
    }
}

static void oa_clear_name(void)
{
    uint32_t i;

    for (i = 0; i < 16U; i += 4U)
        oa_w32(OFF_NAME + i, 0);
}

static void oa_set_name(const char *name)
{
    uint8_t buf[16];
    uint32_t i;

    for (i = 0; i < 16U; i++)
        buf[i] = 0;
    for (i = 0; name[i] && i < 15U; i++)
        buf[i] = (uint8_t)name[i];
    oa_write_bytes(OFF_NAME, buf, 16U);
}

static int oa_wait_evt(uint32_t local_view, uint32_t want, uint32_t spins)
{
    uint32_t tok;

    while (spins--)
    {
        if (rt_hw_msgbox_wait(local_view, &tok, 1000U) == 0)
        {
            if ((tok & 0xffU) == (want & 0xffU))
                return 0;
            /* Drain unrelated tokens (e.g. Phase1 MAGIC). */
        }
    }
    return -1;
}

int openamp_master_start(uint32_t spins)
{
    g_is_master = 1;
    g_tx_seq = 0;

    rt_hw_msgbox_clk_enable();

    oa_w32(OFF_LINK, OA_LINK_IDLE);
    oa_w32(OFF_M2S_SEQ, 0);
    oa_w32(OFF_S2M_SEQ, 0);
    oa_w32(OFF_M2S_ACK, 0);
    oa_w32(OFF_S2M_ACK, 0);
    oa_w32(OFF_M2S_LEN, 0);
    oa_w32(OFF_S2M_LEN, 0);
    oa_clear_name();
    oa_set_name(OA_EPT_NAME);
    oa_w32(OFF_MAGIC, OA_MAGIC);
    oa_w32(OFF_LINK, OA_LINK_MASTER);

    rt_hw_msgbox_kick(MSGBOX_VIEW_C907, OA_EVT_LINK);

    if (oa_wait_evt(MSGBOX_VIEW_E907, OA_EVT_LINK_ACK, spins) != 0)
    {
        /* Fallback: peer may have set link without matching kick token. */
        if (oa_r32(OFF_LINK) != OA_LINK_UP)
            return -1;
    }

    if (oa_r32(OFF_MAGIC) != OA_MAGIC)
        return -2;

    oa_w32(OFF_LINK, OA_LINK_UP);
    return 0;
}

int openamp_slave_start(uint32_t spins)
{
    uint32_t tok;
    uint8_t name[16];
    uint32_t i;

    g_is_master = 0;
    g_tx_seq = 0;

    rt_hw_msgbox_clk_enable();

    /* Drain stale Phase1 doorbell tokens. */
    for (i = 0; i < 8U; i++)
    {
        if (rt_hw_msgbox_wait(MSGBOX_VIEW_C907, &tok, 100U) != 0)
            break;
    }

    if (oa_wait_evt(MSGBOX_VIEW_C907, OA_EVT_LINK, spins) != 0)
    {
        /* Also accept if master already wrote SHM. */
        if (oa_r32(OFF_MAGIC) != OA_MAGIC || oa_r32(OFF_LINK) < OA_LINK_MASTER)
            return -1;
    }

    if (oa_r32(OFF_MAGIC) != OA_MAGIC)
        return -2;

    oa_read_bytes(OFF_NAME, name, 16U);
    if (name[0] == 0)
        return -3;

    oa_w32(OFF_LINK, OA_LINK_UP);
    rt_hw_msgbox_kick(MSGBOX_VIEW_E907, OA_EVT_LINK_ACK);
    return 0;
}

int openamp_send(const void *data, uint32_t len, uint32_t spins)
{
    uint32_t seq;
    uint32_t peer;
    uint32_t local;
    uint32_t tok;

    if (!data || len == 0 || len > OA_PAYLOAD_MAX)
        return -1;

    seq = ++g_tx_seq;

    if (g_is_master)
    {
        oa_w32(OFF_M2S_LEN, len);
        oa_write_bytes(OFF_M2S_PAY, (const uint8_t *)data, len);
        oa_w32(OFF_M2S_SEQ, seq);
        peer = MSGBOX_VIEW_C907;
        local = MSGBOX_VIEW_E907;
        rt_hw_msgbox_kick(peer, OA_EVT_QUEUE | (seq << 8));

        while (spins--)
        {
            if (rt_hw_msgbox_wait(local, &tok, 1000U) == 0)
            {
                if ((tok & 0xffU) == (OA_EVT_QUEUE_ACK & 0xffU) &&
                    ((tok >> 8) & 0xffU) == (seq & 0xffU))
                    return 0;
            }
            if (oa_r32(OFF_M2S_ACK) == seq)
                return 0;
        }
        return -2;
    }

    /* Slave send path (echo uses s2m). */
    oa_w32(OFF_S2M_LEN, len);
    oa_write_bytes(OFF_S2M_PAY, (const uint8_t *)data, len);
    oa_w32(OFF_S2M_SEQ, seq);
    rt_hw_msgbox_kick(MSGBOX_VIEW_E907, OA_EVT_QUEUE | (seq << 8));
    return 0;
}

int openamp_recv(void *data, uint32_t *len, uint32_t spins)
{
    uint32_t tok;
    uint32_t seq;
    uint32_t n;
    uint32_t local;
    uint32_t peer;

    if (!data || !len)
        return -1;

    if (g_is_master)
    {
        local = MSGBOX_VIEW_E907;
        peer = MSGBOX_VIEW_C907;
        while (spins--)
        {
            if (rt_hw_msgbox_wait(local, &tok, 1000U) == 0)
            {
                if ((tok & 0xffU) != (OA_EVT_QUEUE & 0xffU))
                    continue;
                seq = oa_r32(OFF_S2M_SEQ);
                n = oa_r32(OFF_S2M_LEN);
                if (n == 0 || n > OA_PAYLOAD_MAX)
                    return -2;
                oa_read_bytes(OFF_S2M_PAY, (uint8_t *)data, n);
                *len = n;
                oa_w32(OFF_S2M_ACK, seq);
                rt_hw_msgbox_kick(peer, OA_EVT_QUEUE_ACK | (seq << 8));
                return 0;
            }
        }
        return -3;
    }

    /* Slave recv from m2s */
    local = MSGBOX_VIEW_C907;
    peer = MSGBOX_VIEW_E907;
    while (spins--)
    {
        if (rt_hw_msgbox_wait(local, &tok, 1000U) == 0)
        {
            if ((tok & 0xffU) != (OA_EVT_QUEUE & 0xffU))
                continue;
            seq = oa_r32(OFF_M2S_SEQ);
            n = oa_r32(OFF_M2S_LEN);
            if (n == 0 || n > OA_PAYLOAD_MAX)
                return -2;
            oa_read_bytes(OFF_M2S_PAY, (uint8_t *)data, n);
            *len = n;
            oa_w32(OFF_M2S_ACK, seq);
            /* Echo payload back then ack kick with seq. */
            oa_w32(OFF_S2M_LEN, n);
            oa_write_bytes(OFF_S2M_PAY, (const uint8_t *)data, n);
            oa_w32(OFF_S2M_SEQ, seq);
            rt_hw_msgbox_kick(peer, OA_EVT_QUEUE_ACK | (seq << 8));
            return 0;
        }
        /* DRAM-only fallback if kick missed */
        seq = oa_r32(OFF_M2S_SEQ);
        if (seq != 0 && oa_r32(OFF_M2S_ACK) != seq)
        {
            n = oa_r32(OFF_M2S_LEN);
            if (n && n <= OA_PAYLOAD_MAX)
            {
                oa_read_bytes(OFF_M2S_PAY, (uint8_t *)data, n);
                *len = n;
                oa_w32(OFF_M2S_ACK, seq);
                oa_w32(OFF_S2M_LEN, n);
                oa_write_bytes(OFF_S2M_PAY, (const uint8_t *)data, n);
                oa_w32(OFF_S2M_SEQ, seq);
                rt_hw_msgbox_kick(peer, OA_EVT_QUEUE_ACK | (seq << 8));
                return 0;
            }
        }
    }
    return -3;
}

int openamp_echo_once(uint32_t spins)
{
    uint8_t buf[OA_PAYLOAD_MAX];
    uint32_t len = 0;

    if (openamp_recv(buf, &len, spins) != 0)
        return -1;
    return 0;
}
