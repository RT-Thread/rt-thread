/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-27     seteiro      trigger and clear the QingKe V2 software interrupt
 */

#include "board.h"

void rt_trigger_software_interrupt(void)
{
    SysTick->CTLR |= (1 << 31);
}

void rt_hw_do_after_save_above(void)
{
    __asm volatile("li t0,0x20");
    __asm volatile("csrs 0x804, t0");
    SysTick->CTLR &= ~(1 << 31);
}
