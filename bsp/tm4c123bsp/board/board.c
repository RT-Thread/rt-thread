/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-07-24     Tanek        the first version
 * 2018-11-12     Ernest Chen  modify copyright
 */
 
#include <stdint.h>
#include <stdbool.h>
#include "hw_ints.h"
#include "hw_sysctl.h"
#include "hw_memmap.h"
#include "hw_types.h"
#include "fpu.h"
#include "debug.h"
#include "pin_map.h"
#include "rom.h"
#include "sysctl.h"
#include "systick.h"
#include "hw_ints.h"
#include "board.h"

// Holds the system core clock, which is the system clock 
// frequency supplied to the SysTick timer and the processor 
// core clock.
uint32_t SystemCoreClock;



void SystemCoreClockUpdate(void)
{
	
	   FPULazyStackingEnable();

    //
    // Set the clocking to run directly from the crystal.
    //
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);
	
	  SystemCoreClock = SysCtlClockGet();

}

void SysTickConfig()
{
	  SysTickDisable();
    SysTickPeriodSet(SystemCoreClock/RT_TICK_PER_SECOND);
    SysTickIntEnable();
    SysTickEnable();	
}

/**
 * This function will initial your board.
 */
void rt_hw_board_init()
{
    /* System Clock Update */
    SystemCoreClockUpdate();
    /* System Tick Configuration */
    SysTickConfig();

#ifdef RT_USING_SERIAL
		rt_hw_usart_init();
#endif
#ifdef RT_USING_PIN
	  rt_hw_pin_init();
#endif

#ifdef RT_USING_PWM
	  rt_hw_pwm_init();
#endif
    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
	
	  rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
	  
#endif


}


void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}






