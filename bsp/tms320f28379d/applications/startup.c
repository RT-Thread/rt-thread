/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-31     Bernard      first implementation
 * 2018-09-02     xuzhuoyi     modify for TMS320F28379D version
 * 2022-08-21     yuqi         modify the entry function
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include "board.h"


int main(void)
{
    extern int rtthread_startup();

    /* startup RT-Thread RTOS */
    rtthread_startup();
    /* never reach here*/
    return 0;
}

int rt_main(void)
{
    while(1)
    {

    }
}

/*@}*/
