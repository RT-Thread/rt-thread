/*
 * Copyright (c) 2023, lepustse@gmail.com
 *
 * License-Identifier: MIT
 *
 * Change Logs:
 * Date         Author		Notes
 * 2023-05-03   lepustse	the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>
#include "drv_timer.h"

#define TTC0_0_BASEADDR     ZYNQMP_TTC0_BASE
#define TTC0_0_CLK_FREQ_HZ  100000000UL

static void rt_hw_timer_isr(int vector, void *param)
{
    rt_tick_increase();
    /* clear interrupt */
    TTC_ISR(TTC0_0_BASEADDR);
}

int rt_hw_timer_init(void)
{
    /* Stop timer */
    TTC_CNT_CNTRL(TTC0_0_BASEADDR) |= TTC_CNT_CNTRL_DIS;

    /* Initialize TTC */
    TTC_CNT_CNTRL(TTC0_0_BASEADDR) = TTC_CNT_CNTRL_RESET_VALUE;
    TTC_CLK_CNTRL(TTC0_0_BASEADDR) = 0x00;
    TTC_INTERVAL_VAL(TTC0_0_BASEADDR) = 0x00;
    TTC_MATCH_0(TTC0_0_BASEADDR) = 0x00;
    TTC_MATCH_1(TTC0_0_BASEADDR) = 0x00;
    TTC_MATCH_2(TTC0_0_BASEADDR) = 0x00;
    TTC_IER(TTC0_0_BASEADDR) = 0x00;
    TTC_ISR(TTC0_0_BASEADDR) = 0x00;

    /* Reset counter */
    TTC_CNT_CNTRL(TTC0_0_BASEADDR) |= TTC_CNT_CNTRL_RST;

    /* Interval mode select */
    TTC_CNT_CNTRL(TTC0_0_BASEADDR) |= TTC_CNT_CNTRL_INT;
    /* Setup interval */
    TTC_INTERVAL_VAL(TTC0_0_BASEADDR) = TTC0_0_CLK_FREQ_HZ / RT_TICK_PER_SECOND;
    /* Clear all of the prescaler control bits in the register */
    TTC_CLK_CNTRL(TTC0_0_BASEADDR) &= ~(TTC_CLK_CNTRL_PS_VAL_MASK |
                                            TTC_CLK_CNTRL_PS_EN);
    /* We do not need a prescaler*/

    /* Register the ticker handler with the GIC */
    rt_hw_interrupt_install(IRQ_TTC0_0, rt_hw_timer_isr, RT_NULL, "tick");
    /* Enable TTC interrupts in the GIC */
    rt_hw_interrupt_umask(IRQ_TTC0_0);
    /* Enable interval interrupt */
    TTC_IER(TTC0_0_BASEADDR) |= TTC_IXR_INTERVAL;
    /* Start timer */
    TTC_CNT_CNTRL(TTC0_0_BASEADDR) &=~ TTC_CNT_CNTRL_DIS;

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);
