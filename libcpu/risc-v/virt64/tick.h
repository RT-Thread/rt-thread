/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/28     Bernard      The unify RISC-V porting code.
 */

#ifndef TICK_H__
#define TICK_H__

//ask the CLINT for a timer interrupt.
#define CLINT                   (0x2000000L)
#define CLINT_MTIMECMP(hartid)  (CLINT + 0x4000 + 4*(hartid))
#define CLINT_MTIME             (CLINT + 0xBFF8)            // cycles since boot.

int tick_isr(void);
int rt_hw_tick_init(void);

#endif
