/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-11-07     weety      first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "vfp.h"

#ifdef RT_USING_VFP

void vfp_init(void)
{
    int ret = 0;
    unsigned int value;
    asm  volatile ("mrc p15, 0, %0, c1, c0, 2"
            :"=r"(value)
            :);
    value |= 0xf00000;/*enable CP10, CP11 user access*/
    asm volatile("mcr p15, 0, %0, c1, c0, 2"
            :
            :"r"(value));

    asm volatile("fmrx %0, fpexc"
            :"=r"(value));
    value |=(1<<30);
    asm volatile("fmxr fpexc, %0"
            :
            :"r"(value));

}

#endif
