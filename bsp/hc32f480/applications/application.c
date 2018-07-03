/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2014-04-27     Bernard      make code cleanup.
 */

#include <board.h>
#include <rtthread.h>
#ifdef PKG_USING_EASYLOGGER
#include "elog.h"
#endif
#ifdef RT_USING_FINSH
#include <shell.h>
#include <finsh.h>
#endif

#define MAIN_TAG                "[MAIN]"

int main(void)
{
#ifdef PKG_USING_EASYLOGGER
    elog_output_lock_enabled(RT_TRUE);
#endif

#ifdef PKG_USING_EASYLOGGER
    elog_info(MAIN_TAG,"Start \n");
#endif

    while(1)
    {
        //rt_kprintf("main...\n");
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
    return 0;
}
