/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef DRV_HW_MSGBOX_H__
#define DRV_HW_MSGBOX_H__

#include <stdint.h>

#define MSGBOX_VIEW_E907    0x06020000U
#define MSGBOX_VIEW_C907    0x0800B000U
#define MSGBOX_MAGIC        0xA11C0B0CU

void rt_hw_msgbox_clk_enable(void);
void rt_hw_msgbox_kick(uint32_t peer_view, uint32_t token);
int rt_hw_msgbox_wait(uint32_t local_view, uint32_t *token_out, uint32_t spins);
int rt_hw_msgbox_c907_wait(uint32_t spins);

#endif
