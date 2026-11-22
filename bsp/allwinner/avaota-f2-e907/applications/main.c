/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <string.h>

#include "amp_mbox.h"
#include "board.h"
#include "board_c907_release.h"
#include "drv_hw_msgbox.h"
#include "drv_openamp.h"
#include "drv_uart.h"

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
    int ok = 0;
    uint8_t payload[OA_PAYLOAD_MAX];
    uint8_t echo[OA_PAYLOAD_MAX];
    uint32_t echo_len;
    int ept_ok = 1;

    rt_kprintf("[E907] avaota-f2 v861 e907 hetero\n");

    /* One-time MSGBOX bring-up: E907 boots first, so this is the only reset
     * pulse of both banks, and it happens before C907 is released. Every later
     * path (doorbell, openamp_*_start, send/recv) only ensures the block. */
    rt_hw_msgbox_hw_init();

    (void)rt_hw_msgbox_phase1_probe();

    amp_coherent_begin();
    amp_write(AMP_SLOT_C907, 0);
    amp_write(AMP_SLOT_C907_REPLY, 0);
    amp_write(AMP_SLOT_PING_REQ, 0);
    amp_write(AMP_SLOT_E907, AMP_MAGIC_E907);
    amp_write(AMP_SLOT_E907_STEP, AMP_STEP_UP);

    amp_write(AMP_SLOT_PING_REQ, AMP_PING_REQ);
    rt_kprintf("[E907] ping0=0x%08x before release\n", AMP_PING_REQ);

    rt_hw_c907_release(V861_C907_ENTRY);
    amp_write(AMP_SLOT_E907_STEP, AMP_STEP_RELEASED);

    /* Wait until C907 published magic (avoids Phase1 doorbell race). */
    for (i = 0; i < 4000000U; i++)
    {
        if (amp_read(AMP_SLOT_C907) == AMP_MAGIC_C907)
        {
            break;
        }
        busy_delay_loops(50U);
    }
    (void)rt_hw_msgbox_e907_doorbell();

    busy_delay_loops(200000U);
    rt_hw_uart_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
    amp_coherent_begin();
    rt_kprintf("\n[E907] after C907 release, uart reinit\n");

    if (wait_reply(AMP_PING_REQ + 1U, 4000000U) != 0 ||
        amp_read(AMP_SLOT_C907) != AMP_MAGIC_C907)
    {
        rt_kprintf("[E907] HETERO-FAIL c907=0x%08x reply=0x%08x\n",
                   amp_read(AMP_SLOT_C907), amp_read(AMP_SLOT_C907_REPLY));
        return 0;
    }
    rt_kprintf("[E907] HETERO-OK c907=0x%08x reply=0x%08x\n",
               AMP_MAGIC_C907, amp_read(AMP_SLOT_C907_REPLY));
    ok = 1;

    amp_write(AMP_SLOT_E907_STEP, AMP_STEP_RPMSG);

    if (openamp_master_start(8000000U) != 0)
    {
        rt_kprintf("[E907] OPENAMP-EPT-FAIL link\n");
        ept_ok = 0;
    }
    else
    {
        for (i = 1; i <= 3; i++)
        {
            rt_sprintf((char *)payload, "ept-msg-%u", (unsigned)i);
            echo_len = 0;
            memset(echo, 0, sizeof(echo));
            if (openamp_send(payload, (uint32_t)strlen((char *)payload) + 1U,
                             8000000U) != 0)
            {
                rt_kprintf("[E907] OPENAMP-EPT-FAIL send #%u\n", i);
                ept_ok = 0;
                break;
            }
            /* Slave already echoed via QUEUE_ACK path; verify SHM echo. */
            echo_len = amp_read(OA_SHM_BASE + 0x64U); /* OFF_S2M_LEN */
            if (echo_len == 0 || echo_len > OA_PAYLOAD_MAX)
            {
                rt_kprintf("[E907] OPENAMP-EPT-FAIL echo len #%u\n", i);
                ept_ok = 0;
                break;
            }
            {
                uint32_t off = 0x68U;
                uint32_t b;
                for (b = 0; b < echo_len; b += 4U)
                {
                    uint32_t w = amp_read(OA_SHM_BASE + off + b);
                    uint32_t n = echo_len - b;
                    uint32_t k;
                    if (n > 4U)
                    {
                        n = 4U;
                    }
                    for (k = 0; k < n; k++)
                    {
                        echo[b + k] = (uint8_t)((w >> (8U * k)) & 0xffU);
                    }
                }
            }
            if (memcmp(payload, echo, echo_len) != 0)
            {
                rt_kprintf("[E907] OPENAMP-EPT-FAIL mismatch #%u\n", i);
                ept_ok = 0;
                break;
            }
            rt_kprintf("[E907] ept #%u ok len=%u\n", i, echo_len);
        }
    }

    if (ok && ept_ok)
    {
        rt_kprintf("[E907] OPENAMP-EPT-OK name=%s tx=3 rx=3\n", OA_EPT_NAME);
    }

    amp_write(AMP_SLOT_E907_STEP, AMP_STEP_OK);
    return 0;
}
