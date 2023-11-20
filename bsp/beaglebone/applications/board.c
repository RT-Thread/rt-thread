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
#include <finsh.h>

#include "board.h"
#include <mmu.h>
#include <interrupt.h>

#define TIMER_HW_BASE AM33XX_DMTIMER_7_REGS

#define DMTIMER_TCLR_AR                         (0x00000002u)
#define DMTIMER_TCLR_CE                         (0x00000040u)
#define DMTIMER_TCLR_PRE                        (0x00000020u)
#define DMTIMER_TCLR_ST                         (0x00000001u)
#define DMTIMER_IRQENABLE_SET_OVF_EN_FLAG       (0x00000002u)
#define DMTIMER_IRQSTATUS_RAW_OVF_IT_FLAG       (0x00000002u)

#define CM_DPLL_CLKSEL_CLK_CLKSEL               (0x00000003u)
#define CM_DPLL_CLKSEL_CLK_CLKSEL_SEL3          (0x2u)

#define CM_PER_CLKCTRL_MODULEMODE_ENABLE        (0x2u)
#define CM_PER_CLKCTRL_MODULEMODE               (0x00000003u)

#define CM_PER_CLKCTRL_IDLEST                   (0x00030000u)
#define CM_PER_CLKCTRL_IDLEST_FUNC              (0x0u)

#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_L4LS_GCLK     (0x00000100u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER2_GCLK   (0x00004000u)
#define CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER7_GCLK   (1<<13)

static void rt_hw_timer_isr(int vector, void* param)
{
    rt_tick_increase();

    DMTIMER_IRQSTATUS(TIMER_HW_BASE) = DMTIMER_IRQSTATUS_RAW_OVF_IT_FLAG;
}

static void timer_clk_init(void)
{
    unsigned long prcm_base;

    prcm_base = AM33XX_PRCM_REGS;

    /* software forced wakeup */
    CM_PER_L4LS_CLKSTCTRL_REG(prcm_base) |= 0x2;

    /* Waiting for the L4LS clock */
    while (!(CM_PER_L4LS_CLKSTCTRL_REG(prcm_base) & (1<<8)))
        ;

    /* Select the clock source for the Timer2 instance.  */
    CM_DPLL_CLKSEL_TIMER7_CLK(prcm_base) &= ~(CM_DPLL_CLKSEL_CLK_CLKSEL);
    /* 32k clock source */
    CM_DPLL_CLKSEL_TIMER7_CLK(prcm_base) |= CM_DPLL_CLKSEL_CLK_CLKSEL_SEL3;

    while ((CM_DPLL_CLKSEL_TIMER7_CLK(prcm_base) & CM_DPLL_CLKSEL_CLK_CLKSEL) !=
        CM_DPLL_CLKSEL_CLK_CLKSEL_SEL3);

    /* Writing to MODULEMODE field of CM_PER_TIMER7_CLKCTRL register. */
    CM_PER_TIMER7_CLKCTRL(prcm_base) |= CM_PER_CLKCTRL_MODULEMODE_ENABLE;

    /* Waiting for MODULEMODE field to reflect the written value. */
    while ((CM_PER_TIMER7_CLKCTRL(prcm_base) & CM_PER_CLKCTRL_MODULEMODE) !=
        CM_PER_CLKCTRL_MODULEMODE_ENABLE);

    /*
     * Waiting for IDLEST field in CM_PER_TIMER7_CLKCTRL register
     * for the module is fully functional.
     */
    while ((CM_PER_TIMER7_CLKCTRL(prcm_base) & CM_PER_CLKCTRL_IDLEST) !=
        CM_PER_CLKCTRL_IDLEST_FUNC);

    /* Waiting for the L4LS clock */
    while (!(CM_PER_L4LS_CLKSTCTRL_REG(prcm_base) & CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_L4LS_GCLK));
    /* Waiting for the TIMER7 clock */
    while (!(CM_PER_L4LS_CLKSTCTRL_REG(prcm_base) & CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER7_GCLK));
}

int rt_hw_timer_init(void)
{
    rt_uint32_t counter;

    timer_clk_init();

    /* soft reset the timer */
    DMTIMER_TIOCP_CFG(TIMER_HW_BASE) |= 1;
    while ((DMTIMER_TIOCP_CFG(TIMER_HW_BASE) & 0x1) == 1)
        ;

    /* calculate count */
    counter = 0xffffffff - (32768UL/RT_TICK_PER_SECOND);

    /* set initial count */
    DMTIMER_TCRR(TIMER_HW_BASE) = counter;
    /* set reload count */
    DMTIMER_TLDR(TIMER_HW_BASE) = counter;

    /* set mode: auto reload */
    DMTIMER_TCLR(TIMER_HW_BASE) |= DMTIMER_TCLR_AR;

    /* interrupt enable for match */
    DMTIMER_IRQENABLE_SET(TIMER_HW_BASE) = DMTIMER_IRQENABLE_SET_OVF_EN_FLAG;
    DMTIMER_IRQSTATUS(TIMER_HW_BASE) = DMTIMER_IRQSTATUS_RAW_OVF_IT_FLAG;

    rt_hw_interrupt_install(TINT7, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_control(TINT7, 0, 0);
    rt_hw_interrupt_umask(TINT7);

    while (DMTIMER_TWPS(TIMER_HW_BASE) != 0)
        ;

    /* start timer */
    DMTIMER_TCLR(TIMER_HW_BASE) |= DMTIMER_TCLR_ST;

    while (DMTIMER_TWPS(TIMER_HW_BASE) != 0)
        ;

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);

/**
 * This function will initialize beaglebone board
 */
void rt_hw_board_init(void)
{
    rt_hw_mmu_init();

    /* init hardware interrupt */
    rt_hw_interrupt_init();

    /* Heap initialization */
#if defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

    rt_components_board_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
}

void rt_hw_cpu_reset(void)
{
    unsigned long prcm_base = AM33XX_PRCM_REGS;

    REG32(PRM_DEVICE(prcm_base)) = 0x1;
    RT_ASSERT(0);
}
MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reboot, reboot the cpu);
