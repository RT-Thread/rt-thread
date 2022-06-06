/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-08-10     Urey         first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "csi_core.h"
#include "pinmux.h"

extern int __bss_end__;
#define SYS_HEAP_BEGIN    (&__bss_end__)

#include "core_ck802.h"

/**
 * This function will initial CK802 board.
 */
void rt_hw_board_init(void)
{
    phobos_ioreuse_initial();

    /* NVIC Configuration */
    drv_nvic_init(2);

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)SYS_HEAP_BEGIN, (void *)CK802_IRAM_END);
#endif
}

/*@}*/
