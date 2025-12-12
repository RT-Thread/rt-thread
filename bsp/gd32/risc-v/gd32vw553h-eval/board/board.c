/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-04     BruceOu      first implementation
 */

#include <stddef.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#ifdef RT_USING_SERIAL
#include <drv_usart.h>
#endif

/*  System Tick Configuration */
void systick_config(void)
{
    SysTimer_SetControlValue(SysTimer_MTIMECTL_CMPCLREN_Msk);
    SysTimer_SetCompareValue(((uint32_t) SystemCoreClock / 4) / RT_TICK_PER_SECOND);
    __ECLIC_SetTrigIRQ(CLIC_INT_TMR, ECLIC_POSTIVE_EDGE_TRIGGER);
    eclic_irq_enable(CLIC_INT_TMR, 0, 0);
}

void rt_hw_board_init(void)
{
extern void _init(void);
    _init();
    systick_config();

    /* USART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif

    /* Set the shell console output device */
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    /* Board underlying hardware initialization */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *) HEAP_BEGIN, (void *) HEAP_END);
#endif

}

 void eclic_mtip_handler(void)
 {
     /* clear value */
     ECLIC_ClearPendingIRQ(CLIC_INT_TMR);
     SysTimer_SetLoadValue(0);

     /* enter interrupt */
     rt_interrupt_enter();
     /* tick increase */
     rt_tick_increase();

     /* leave interrupt */
     rt_interrupt_leave();
 }

/******************** end of file *******************/
