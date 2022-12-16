/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-08     WangShun     the first version
 * 2022-12-13     WangShun     put the rt_system_heap_init in head
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include "udma_uart_driver.h"
#include "hal_udma_ctrl_reg_defs.h"
#include "hal_udma_uart_reg_defs.h"
#include "core-v-mcu-config.h"
#include "drv_usart.h"
#include "string.h"

extern void rt_systick_config(void);

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
#define RT_HEAP_SIZE (64*1024)
static rt_uint8_t rt_heap[RT_HEAP_SIZE];
void *rt_heap_begin_get(void)
{
    return rt_heap;
}
void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

void rt_hw_board_init()
{
    /*Initialize heap first, or system_ Semaphore in init cannot be created*/
#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
    /* System Clock Update */
    extern void system_init(void);
    system_init();
    /* System Tick Configuration */
    rt_systick_config();

    volatile uint32_t mtvec = 0;
    __asm volatile( "csrr %0, mtvec" : "=r"( mtvec ) );
    __asm volatile( "csrs mie, %0" :: "r"(0x880) );

    /* USART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}
