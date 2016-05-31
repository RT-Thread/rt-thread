/*
 * File      : vfp.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
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
