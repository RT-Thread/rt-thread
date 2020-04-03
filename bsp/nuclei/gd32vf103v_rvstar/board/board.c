/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-02     Huaqi Fang      first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#ifdef RT_USING_SERIAL
#include <drv_usart.h>
#endif


extern void *_end;
extern void *_heap_end;
#define HEAP_BEGIN  &_end
#define HEAP_END    &_heap_end

extern void _init(void);
extern void vPortSetupTimerInterrupt(void);

void rt_hw_board_init(void)
{
    /* OS Tick Configuration */
    vPortSetupTimerInterrupt();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *) HEAP_BEGIN, (void *) HEAP_END);
#endif

    _init(); // __libc_init_array is not used

    /* USART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif

    /* Set the shell console output device */
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    /* Board underlying hardware initialization */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

/******************** end of file *******************/

