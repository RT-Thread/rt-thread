/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * V861 sun252iw1 MSGBOX (Tina DTB: 0x06020000 + 0x0800b000).
 * OpenAMP-shaped transport: HW FIFO kick + DRAM payload (not libmetal).
 */

#ifndef DRV_HW_MSGBOX_H__
#define DRV_HW_MSGBOX_H__

#include <stdint.h>

#define MSGBOX_VIEW_E907    0x06020000U
#define MSGBOX_VIEW_C907    0x0800B000U
#define MSGBOX_MAGIC        0xA11C0B0CU

void rt_hw_msgbox_clk_enable(void);
int rt_hw_msgbox_phase1_probe(void);

/* Write token into peer view FIFO (kick). */
void rt_hw_msgbox_kick(uint32_t peer_view, uint32_t token);

/* Poll local view FIFO; return 0 and *token_out on message. */
int rt_hw_msgbox_wait(uint32_t local_view, uint32_t *token_out, uint32_t spins);

/* Phase1 helpers */
int rt_hw_msgbox_e907_doorbell(void);
int rt_hw_msgbox_c907_wait(uint32_t spins);

#endif
