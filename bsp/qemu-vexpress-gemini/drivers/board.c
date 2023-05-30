/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-20     Bernard    the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

#define TIMER_LOAD(hw_base)     __REG32(hw_base + 0x00)
#define TIMER_VALUE(hw_base)    __REG32(hw_base + 0x04)
#define TIMER_CTRL(hw_base)     __REG32(hw_base + 0x08)
#define TIMER_CTRL_ONESHOT      (1 << 0)
#define TIMER_CTRL_32BIT        (1 << 1)
#define TIMER_CTRL_DIV1         (0 << 2)
#define TIMER_CTRL_DIV16        (1 << 2)
#define TIMER_CTRL_DIV256       (2 << 2)
#define TIMER_CTRL_IE           (1 << 5)        /* Interrupt Enable (versatile only) */
#define TIMER_CTRL_PERIODIC     (1 << 6)
#define TIMER_CTRL_ENABLE       (1 << 7)

#define TIMER_INTCLR(hw_base)   __REG32(hw_base + 0x0c)
#define TIMER_RIS(hw_base)      __REG32(hw_base + 0x10)
#define TIMER_MIS(hw_base)      __REG32(hw_base + 0x14)
#define TIMER_BGLOAD(hw_base)   __REG32(hw_base + 0x18)

#define SYS_CTRL                __REG32(REALVIEW_SCTL_BASE)

#define TIMER_HW_BASE           REALVIEW_TIMER2_3_BASE

void rt_hw_timer_ack(void)
{
    /* clear interrupt */
    TIMER_INTCLR(TIMER_HW_BASE) = 0x01;
}

static void rt_hw_timer_isr(int vector, void *param)
{
    rt_tick_increase();

    rt_hw_timer_ack();
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

    TIMER_LOAD(TIMER_HW_BASE) = 1000;

    /* enable timer */
    TIMER_CTRL(TIMER_HW_BASE) |= TIMER_CTRL_ENABLE;

    rt_hw_interrupt_install(IRQ_PBA8_TIMER2_3, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(IRQ_PBA8_TIMER2_3);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);

/**
 * This function will initialize beaglebone board
 */
void rt_hw_board_init(void)
{
    rt_components_board_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
}

/*@}*/
