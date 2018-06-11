/*
 * File      : board_coretimer.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-01-01     Urey      first version
 */
#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "board_coretimer.h"

#include <stdint.h>

static inline unsigned int readreg32(volatile unsigned int *addr)
{
    return *(volatile unsigned int *)addr;
}

static inline void writereg32(unsigned int b, volatile unsigned int *addr)
{
    *(volatile unsigned int *)addr = b;
}

void CKTimerInit(uint32_t timer_id, uint32_t freq)
{
    uint32_t reg;

    writereg32(APB_DEFAULT_FREQ / freq, CORET_RVR);
    writereg32(0, CORET_CVR);

    reg = readreg32(CORET_CSR);
    reg |= CORETIM_TXCONTROL_ENABLE;
    reg |= CORETIM_TXCONTROL_INTMASK;
    writereg32(reg, CORET_CSR);

    return;
}

void CKTimerClear(uint32_t timer_id)
{
    uint32_t reg;

    reg = readreg32(CORET_CSR);
    reg |= ~CORETIM_TXCONTROL_MODE;
    writereg32(reg, CORET_CSR);
}

uint32_t CKTimer_CurrentValue(void)
{
    return readreg32(CORET_CVR);
}

void __attribute__((isr)) SysTick_Handler(void)
{
    CKTimerClear(0x1);
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}
