/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-31     Bernard      first implementation
 * 2018-09-02     xuzhuoyi     modify for TMS320F28379D version
 * 2022-08-21     qiyu         modify the entry function
 */

#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>
#include "board.h"

int main(void)
{
    unsigned long x=10000;

    while(x)
    {
        x--;
    }
}

/*@}*/
