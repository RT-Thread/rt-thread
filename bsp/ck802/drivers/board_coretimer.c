/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
