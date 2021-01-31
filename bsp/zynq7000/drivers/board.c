/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-03-30     Bernard      the first verion
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

typedef struct
{
    volatile rt_uint32_t LOAD;
    volatile rt_uint32_t COUNTER;
    volatile rt_uint32_t CONTROL;
    volatile rt_uint32_t ISR;
} ptimer_reg_t;

/* Values for control register */
#define PRIVATE_TIMER_CONTROL_PRESCALER_MASK     0x0000FF00
#define PRIVATE_TIMER_CONTROL_PRESCALER_SHIFT    8
#define PRIVATE_TIMER_CONTROL_IRQ_ENABLE_MASK    0x00000004
#define PRIVATE_TIMER_CONTROL_AUTO_RELOAD_MASK   0x00000002
#define PRIVATE_TIMER_CONTROL_ENABLE_MASK        0x00000001

/* Values for ISR register */
#define PRIVATE_TIMER_ISR_EVENT_FLAG_MASK        0x00000001


#define PRIVATE_TIMER_BASE            0xF8F00600
#define PRIVATE_TIMER                ((ptimer_reg_t*)PRIVATE_TIMER_BASE)

static void rt_hw_timer_isr(int vector, void *param)
{
    rt_tick_increase();
    /* clear interrupt */
    PRIVATE_TIMER->ISR = PRIVATE_TIMER_ISR_EVENT_FLAG_MASK;
}

int rt_hw_timer_init(void)
{
    PRIVATE_TIMER->CONTROL &= ~PRIVATE_TIMER_CONTROL_ENABLE_MASK;
    {
        /* Clear the prescaler. */
        rt_uint32_t ctrl = PRIVATE_TIMER->CONTROL;
        ctrl &= ~PRIVATE_TIMER_CONTROL_PRESCALER_MASK;
        PRIVATE_TIMER->CONTROL = ctrl;
    }
    /* The processor timer is always clocked at 1/2 CPU frequency(CPU_3x2x). */
    PRIVATE_TIMER->COUNTER = APU_FREQ/2/RT_TICK_PER_SECOND;
    /* Set reload value. */
    PRIVATE_TIMER->LOAD = APU_FREQ/2/RT_TICK_PER_SECOND;
    PRIVATE_TIMER->CONTROL |= PRIVATE_TIMER_CONTROL_AUTO_RELOAD_MASK;

    PRIVATE_TIMER->CONTROL |= PRIVATE_TIMER_CONTROL_IRQ_ENABLE_MASK;
    PRIVATE_TIMER->ISR = PRIVATE_TIMER_ISR_EVENT_FLAG_MASK;

    rt_hw_interrupt_install(IRQ_Zynq7000_PTIMER, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(IRQ_Zynq7000_PTIMER);

    PRIVATE_TIMER->CONTROL |= PRIVATE_TIMER_CONTROL_ENABLE_MASK;

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);

void rt_hw_board_init()
{
    rt_components_board_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
}

