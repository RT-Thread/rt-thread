/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2018-09-02     xuzhuoyi     modify for TMS320F28379D version
 * 2022-06-21     guyunjie     fix bugs in trap_rtosint and enable interrupt nesting
 * 2022-08-21     yuqi         adding onboard devices initialization code
 */
#include <rtthread.h>
#include "board.h"
#include "drv_sci.h"
#include "drv_gpio.h"
#include "F28x_Project.h"

#ifndef RT_USING_SMP
extern volatile rt_atomic_t rt_interrupt_nest;
#endif

extern rt_uint32_t rt_thread_switch_interrupt_flag;

extern interrupt void rtosint_handler();

/**
 * This is the timer interrupt service routine.
 *
 */
interrupt void cpu_timer2_isr(void)
{
    CpuTimer2Regs.TCR.all = 0xC000;

    rt_interrupt_enter();

    rt_tick_increase();

    rt_interrupt_leave();
}

extern interrupt void XINT1_Handler(void);
extern interrupt void XINT2_Handler(void);
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

#ifdef _FLASH
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32)&RamfuncsLoadSize);
    InitFlash();
#endif
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.TIMER2_INT = &cpu_timer2_isr;
    PieVectTable.RTOS_INT = &rtosint_handler;

#ifdef BSP_USING_XINT1
    PieVectTable.XINT1_INT = &XINT1_Handler;
#endif
#ifdef BSP_USING_XINT2
    PieVectTable.XINT2_INT = &XINT2_Handler;
#endif
#ifdef BSP_USING_XINT3
    PieVectTable.XINT3_INT = &XINT3_Handler;
#endif
#ifdef BSP_USING_XINT4
    PieVectTable.XINT4_INT = &XINT4_Handler;
#endif
#ifdef BSP_USING_XINT5
    PieVectTable.XINT5_INT = &XINT5_Handler;
#endif
    EDIS;

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer2, 200, 1000000 / RT_TICK_PER_SECOND);
    CpuTimer2Regs.TCR.all = 0x4000;
    IER |= M_INT14;
    IER |= M_INT1;

#ifdef RT_USING_HEAP
    rt_system_heap_init(&__ebss_end, &(__heap_end));
#endif

#ifdef RT_USING_SERIAL
    rt_hw_sci_init();
#endif

#ifdef RT_USING_PIN
    rt_hw_pin_init();
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}

int _args_main()
{
    /* _args_main is the entry point called by _c_int00. We define it
     * here to override the one defined by the compiler in args_main.c */

    extern int rtthread_startup();

    /* startup RT-Thread RTOS */
    rtthread_startup();
    /* never reach here*/
    return 0;
}
