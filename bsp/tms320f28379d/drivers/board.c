/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2018-09-02     xuzhuoyi     modify for TMS320F28379D version
 */
#include <rtthread.h>
#include "board.h"
#include "drv_sci.h"
#include "F28x_Project.h"

extern rt_uint32_t rt_thread_switch_interrupt_flag;

extern interrupt void RTOSINT_Handler();

void trap_rtosint()
{
    if(rt_thread_switch_interrupt_flag)
        asm(" trap #16");
}

/**
 * This is the timer interrupt service routine.
 *
 */
interrupt void cpu_timer2_isr(void)
{
    CpuTimer2Regs.TCR.all = 0xC000;
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();
    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * This function will initial TMS320F28379D board.
 */
void rt_hw_board_init()
{
    /* Configure the system clock @ 84 Mhz */
    InitSysCtrl();

    DINT;
    InitPieCtrl();

    IER = 0x0000;
    IFR = 0x0000;

    InitPieVectTable();

    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.TIMER2_INT = &cpu_timer2_isr;
    PieVectTable.RTOS_INT = &RTOSINT_Handler;
    EDIS;

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer2, 200, 1000000 / RT_TICK_PER_SECOND);
    CpuTimer2Regs.TCR.all = 0x4000;
    IER |= M_INT14;

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

    rt_hw_sci_init();

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
    rt_interrupt_leave_sethook((void (*)(void))trap_rtosint);
}
