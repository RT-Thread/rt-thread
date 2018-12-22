/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-11-19     Urey         the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <string.h>

#include "board.h"
#include "drv_clock.h"
#include "drv_uart.h"
#include "drv_ost.h"

extern void rt_hw_cache_init(void);

extern unsigned char _iramcopy;
extern unsigned char _iramstart;
extern unsigned char _iramend;

#ifdef RT_USING_CPLUSPLUS
int cplusplus_system_init(void)
{
    typedef void (*pfunc) ();
    extern pfunc __ctors_start__[];
    extern pfunc __ctors_end__[];
    pfunc *p;
    for (p = __ctors_end__ - 2; p > __ctors_start__; )
    {
        (*p)();
        p--;
    }
    return 0;
}
#endif

#ifdef PKG_USING_GUIENGINE
#include <rtgui/driver.h>
int lcd_hw_init(void)
{
    rt_device_t device;
    rt_err_t  err;
    
    device = rt_device_find("lcd");
    if (device == RT_NULL)
    {
        rt_kprintf("Not found LCD driver\n");
        return RT_ERROR;
    }
    
    err = rt_device_open(device, RT_DEVICE_OFLAG_RDWR);
    if (err != RT_EOK)
    {
        rt_kprintf("Open LCD driver fail\n");
        return RT_ERROR;
    }
    
    /* set graphic device */
    rtgui_graphic_set_device(device);
}
INIT_ENV_EXPORT(lcd_hw_init);
#endif

void rt_hw_board_init(void)
{
    memcpy((void*)&_iramstart, (void*)&_iramcopy, (rt_uint32_t)&_iramend - (rt_uint32_t)&_iramstart);
    memset((void*)&__bss_start, 0x0, (rt_uint32_t)&__bss_end - (rt_uint32_t)&__bss_start);

    rt_hw_cache_init();
    rt_hw_exception_init();

    /* init hardware interrupt */
    rt_hw_interrupt_init();
    rt_hw_uart_init();

#ifdef RT_USING_CONSOLE
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif /* RT_USING_CONSOLE */

#ifdef RT_USING_HEAP
    /* init memory system */
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

    rt_hw_ost_init();
}
