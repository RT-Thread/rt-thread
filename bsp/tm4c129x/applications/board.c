/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2014-07-18     ArdaFu       Port to TM4C129X
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"


#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/fpu.h"
#include "driverlib/rom_map.h"

#define SYS_CLOCK_DEFAULT 120000000
uint32_t SystemCoreClock;
#define FAULT_NMI               2           // NMI fault
#define FAULT_HARD              3           // Hard fault
#define FAULT_MPU               4           // MPU fault
#define FAULT_BUS               5           // Bus fault
#define FAULT_USAGE             6           // Usage fault
#define FAULT_SVCALL            11          // SVCall
#define FAULT_DEBUG             12          // Debug monitor
#define FAULT_PENDSV            14          // PendSV
#define FAULT_SYSTICK           15          // System Tick

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

extern void PendSV_Handler(void);
extern void HardFault_Handler(void);

/**
 * This function will initial TM4C129X board.
 */
void rt_hw_board_init()
{
    //init low level drivers. e.g. cpu uart etc.
    rt_components_board_init();
    //init HEAP.
    #ifdef RT_USING_HEAP
        rt_system_heap_init(HEAP_BEGIN, HEAP_END);
    #endif
    //redirect RTT stdio to CONSOLE device
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
}

int rt_hw_cpu_init(void)
{
    MAP_IntMasterDisable();
    IntRegister(FAULT_HARD, HardFault_Handler);	
    IntRegister(FAULT_PENDSV, PendSV_Handler);
    IntRegister(FAULT_SYSTICK, SysTick_Handler);
    
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    MAP_FPULazyStackingEnable();

    // Set the clocking to run directly from the external crystal/oscillator.
    // TODO: The SYSCTL_XTAL_ value must be changed to match the value of the
    // crystal on your board.
    SystemCoreClock = MAP_SysCtlClockFreqSet(
                (SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                SYS_CLOCK_DEFAULT);

    MAP_SysTickDisable();
    MAP_SysTickPeriodSet(SystemCoreClock/ RT_TICK_PER_SECOND - 1);
    MAP_SysTickIntEnable();
    MAP_SysTickEnable();	

    return 0;
}
// rt_hw_cpu_init should be run before any other INIT_BOARD_EXPORT
// We use INIT_EXPORT here and set the sequence index to "0.xxxx"
INIT_EXPORT(rt_hw_cpu_init, "0.post");
