/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     zx.chen      add T-HEAD header file csi_core.h
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "csi_core.h"
#include "drv_usart.h"

extern int __bss_end__;
#define SYS_HEAP_BEGIN    (&__bss_end__)

#include "core_rv32.h"


extern usart_handle_t console_handle;
extern void ioreuse_initial(void);


/**
 * This function will initial smartl-evb(e906) board.
 */
void rt_hw_board_init(void)
{
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
    /* initialize hardware usart */
    rt_hw_usart_init();

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)SYS_HEAP_BEGIN, (void *)E906FD_IRAM_END);
#endif
}

/*@}*/
