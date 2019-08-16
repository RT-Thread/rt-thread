/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-22     Jesven       first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>

#include "board.h"

#define TIMER01_HW_BASE                 0x10011000
#define TIMER23_HW_BASE                 0x10012000

#define TIMER_LOAD(hw_base)             __REG32(hw_base + 0x00)
#define TIMER_VALUE(hw_base)            __REG32(hw_base + 0x04)
#define TIMER_CTRL(hw_base)             __REG32(hw_base + 0x08)
#define TIMER_CTRL_ONESHOT              (1 << 0)
#define TIMER_CTRL_32BIT                (1 << 1)
#define TIMER_CTRL_DIV1                 (0 << 2)
#define TIMER_CTRL_DIV16                (1 << 2)
#define TIMER_CTRL_DIV256               (2 << 2)
#define TIMER_CTRL_IE                   (1 << 5)        /* Interrupt Enable (versatile only) */
#define TIMER_CTRL_PERIODIC             (1 << 6)
#define TIMER_CTRL_ENABLE               (1 << 7)

#define TIMER_INTCLR(hw_base)           __REG32(hw_base + 0x0c)
#define TIMER_RIS(hw_base)              __REG32(hw_base + 0x10)
#define TIMER_MIS(hw_base)              __REG32(hw_base + 0x14)
#define TIMER_BGLOAD(hw_base)           __REG32(hw_base + 0x18)

#define TIMER_LOAD(hw_base)             __REG32(hw_base + 0x00)
#define TIMER_VALUE(hw_base)            __REG32(hw_base + 0x04)
#define TIMER_CTRL(hw_base)             __REG32(hw_base + 0x08)
#define TIMER_CTRL_ONESHOT              (1 << 0)
#define TIMER_CTRL_32BIT                (1 << 1)
#define TIMER_CTRL_DIV1                 (0 << 2)
#define TIMER_CTRL_DIV16                (1 << 2)
#define TIMER_CTRL_DIV256               (2 << 2)
#define TIMER_CTRL_IE                   (1 << 5)        /* Interrupt Enable (versatile only) */
#define TIMER_CTRL_PERIODIC             (1 << 6)
#define TIMER_CTRL_ENABLE               (1 << 7)

#define TIMER_INTCLR(hw_base)           __REG32(hw_base + 0x0c)
#define TIMER_RIS(hw_base)              __REG32(hw_base + 0x10)
#define TIMER_MIS(hw_base)              __REG32(hw_base + 0x14)
#define TIMER_BGLOAD(hw_base)           __REG32(hw_base + 0x18)

#define SYS_CTRL                        __REG32(REALVIEW_SCTL_BASE)
#define TIMER_HW_BASE                   REALVIEW_TIMER2_3_BASE

static void rt_hw_timer_isr(int vector, void *param)
{
    rt_tick_increase();
    /* clear interrupt */
    TIMER_INTCLR(TIMER_HW_BASE) = 0x01;
}

int rt_hw_timer_init(void)
{
    rt_uint32_t val;

    SYS_CTRL |= REALVIEW_REFCLK;

    /* Setup Timer0 for generating irq */
    val = TIMER_CTRL(TIMER_HW_BASE);
    val &= ~TIMER_CTRL_ENABLE;
    val |= (TIMER_CTRL_32BIT | TIMER_CTRL_PERIODIC | TIMER_CTRL_IE);
    TIMER_CTRL(TIMER_HW_BASE) = val;

    TIMER_LOAD(TIMER_HW_BASE) = 1000000/RT_TICK_PER_SECOND;

    /* enable timer */
    TIMER_CTRL(TIMER_HW_BASE) |= TIMER_CTRL_ENABLE;

    rt_hw_interrupt_install(IRQ_PBA8_TIMER2_3, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(IRQ_PBA8_TIMER2_3);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);

void timer_init(int timer, unsigned int preload)
{
    uint32_t val;

    if (timer == 0) 
    {
        /* Setup Timer0 for generating irq */
        val = TIMER_CTRL(TIMER01_HW_BASE);
        val &= ~TIMER_CTRL_ENABLE;
        val |= (TIMER_CTRL_32BIT | TIMER_CTRL_PERIODIC | TIMER_CTRL_IE);
        TIMER_CTRL(TIMER01_HW_BASE) = val;

        TIMER_LOAD(TIMER01_HW_BASE) = preload;

        /* enable timer */
        TIMER_CTRL(TIMER01_HW_BASE) |= TIMER_CTRL_ENABLE;
    } 
    else 
    {
        /* Setup Timer1 for generating irq */
        val = TIMER_CTRL(TIMER23_HW_BASE);
        val &= ~TIMER_CTRL_ENABLE;
        val |= (TIMER_CTRL_32BIT | TIMER_CTRL_PERIODIC | TIMER_CTRL_IE);
        TIMER_CTRL(TIMER23_HW_BASE) = val;

        TIMER_LOAD(TIMER23_HW_BASE) = preload;

        /* enable timer */
        TIMER_CTRL(TIMER23_HW_BASE) |= TIMER_CTRL_ENABLE;
    }
}

void timer_clear_pending(int timer)
{
    if (timer == 0)
    {
        TIMER_INTCLR(TIMER01_HW_BASE) = 0x01;
    } 
    else
    {
        TIMER_INTCLR(TIMER23_HW_BASE) = 0x01;
    }
}
