/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-29     supperthomas first version
 *
 */
#include <rtthread.h>
#include <rthw.h>
#include <stdio.h>
#include "board.h"
#include "mxc_sys.h"
#ifdef RT_USING_SERIAL
#include "drv_usart.h"
#endif

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

void SysTick_Configuration(void)
{
    uint32_t error;
    error = SYS_SysTick_Config(SYS_SysTick_GetFreq()/RT_TICK_PER_SECOND, 1, MXC_TMR0);

    if (error != E_NO_ERROR) {
        printf("ERROR: Ticks is not valid");
    }
}

mxc_uart_regs_t *ConsoleUART = MXC_UART_GET_UART(1);

const sys_cfg_uart_t console_uart_sys_cfg = {
    MAP_A,
    UART_FLOW_DISABLE,
};


void rt_hw_board_init(void)
{
   // rt_hw_interrupt_enable(0);
    // sd_power_dcdc_mode_set(NRF_POWER_DCDC_ENABLE);
    /* Activate deep sleep mode */

    SysTick_Configuration();

#if defined(RT_USING_HEAP)
    rt_system_heap_init((void *)(0x20000000+16*1024), (void *)(0x20000000+64*1024));
#endif
   
#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif
    
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
    
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
    


}

