/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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

#include "mmu.h"
#include "board.h"

#define TIMER01_HW_BASE_PHY                 0x10011000
#define TIMER23_HW_BASE_PHY                 0x10012000

void* timer01_hw_base;
void* timer23_hw_base;

#define TIMER01_HW_BASE timer01_hw_base
#define TIMER23_HW_BASE timer23_hw_base

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

void* sys_ctrl;
#define SYS_CTRL                        __REG32(sys_ctrl)
void* timer_hw_base;
#define TIMER_HW_BASE                   timer_hw_base

static void rt_hw_timer_isr(int vector, void *param)
{
    rt_tick_increase();
    /* clear interrupt */
    TIMER_INTCLR(TIMER_HW_BASE) = 0x01;
}

int rt_hw_timer_init(void)
{
    rt_uint32_t val;

#ifdef RT_USING_SMART
    sys_ctrl = (void*)rt_ioremap((void*)REALVIEW_SCTL_BASE, 0x1000);
    timer_hw_base = (void*)rt_ioremap((void*)REALVIEW_TIMER2_3_BASE, 0x1000);
#else
    sys_ctrl = (void*)REALVIEW_SCTL_BASE;
    timer_hw_base = (void*)REALVIEW_TIMER2_3_BASE;
#endif

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
#ifdef RT_USING_SMART
        timer01_hw_base = (void*)rt_ioremap((void*)TIMER01_HW_BASE_PHY, 0x1000);
#else
        timer01_hw_base = (void*)TIMER01_HW_BASE_PHY;
#endif
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
#ifdef RT_USING_SMART
        timer23_hw_base = (void*)rt_ioremap((void*)TIMER23_HW_BASE_PHY, 0x1000);
#else
        timer01_hw_base = (void*)TIMER23_HW_BASE_PHY;
#endif
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
