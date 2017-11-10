/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-20     Bernard    the first version
 */

#include <stdlib.h>
#include <rtthread.h>

#ifdef RT_USING_GDB
#include <gdb_stub.h>
#endif

int rt_application_init()
{
    /* do component initialization */
    rt_components_init();

#ifdef RT_USING_GDB
    gdb_set_device("uart4");
    gdb_start();
#endif

    return 0;
}
