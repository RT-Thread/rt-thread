/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-15     Emuzit            first version
 */
#include <rthw.h>
#include <drivers/dev_pin.h>
#include "board.h"
#include "ch56x_pfic.h"
#include "ch56x_uart.h"

extern rt_uint32_t rt_thread_switch_interrupt_flag;

/* FIXME: Use rt_interrupt_leave_hook to trigger SWI for context switch.
 * Hopefully there's a standard riscv way instead of this clumsy patch.
*/
static void irq_leave_hook(void)
{
    if (rt_thread_switch_interrupt_flag)
    {
        pfic_swi_pendset();
    }
}

/*
 * _start -> handle_reset
 * src/components.c/entry() -> rtthread_startup()
 * libcpu/risc-v/common/context_gcc.S/rt_hw_interrupt_disable
 */
void rt_hw_board_init()
{
    volatile struct pfic_registers *pfic = (void *)PFIC_REG_BASE;

    /* disable all pfic interrupts */
    pfic->IRER[0] = PFIC_IREG1_MASK;
    pfic->IRER[1] = PFIC_IREG2_MASK;

    /* disable hwstack push/pop & nested interrupt */
    pfic->CFGR = cfgr_nest_hwstk(CFGR_NESTCTRL_DISABLE | CFGR_HWSTKCTRL_DISABLE);

    /* disable clock input for all peripheral devices */
    sys_slp_clk_off0(0xff, SYS_SLP_CLK_OFF);
    sys_slp_clk_off1(0xff, SYS_SLP_CLK_OFF);
    sys_clk_off_by_irqn(ETH_IRQn, SYS_SLP_CLK_OFF);
    sys_clk_off_by_irqn(ECDC_IRQn, SYS_SLP_CLK_OFF);

    /* setup HCLK for systick & peripheral devices */
    sys_hclk_set(SYS_HCLK_FREQ);

    /* set SysTick to RT_TICK_PER_SECOND with current HCLK */
    systick_init(0);

    /* Note: keep MSTATUS_MIE disabled to prevent SysTick from processing
     * thread scheduling, which may not be ready upon 1st systick irq.
     * MSTATUS_MIE will be set when rt_system_scheduler_start() starts
     * the first thread and copies mstatus from stack_frame.
     */

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_hw_uart_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    rt_interrupt_leave_sethook(irq_leave_hook);
}
