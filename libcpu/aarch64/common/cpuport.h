/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-10     GuEe-GUI     first version
 */

#ifndef __CPUPORT_H__
#define __CPUPORT_H__

#include <rtdef.h>

#define __WFI() __asm__ volatile ("wfi":::"memory")
#define __WFE() __asm__ volatile ("wfe":::"memory")
#define __SEV() __asm__ volatile ("sev")
#define __ISB() __asm__ volatile ("isb 0xf":::"memory")
#define __DSB() __asm__ volatile ("dsb 0xf":::"memory")
#define __DMB() __asm__ volatile ("dmb 0xf":::"memory")

rt_inline void rt_hw_isb(void)
{
    __asm__ volatile ("isb":::"memory");
}

rt_inline void rt_hw_dmb(void)
{
    __asm__ volatile ("dmb sy":::"memory");
}

rt_inline void rt_hw_dsb(void)
{
    __asm__ volatile ("dsb sy":::"memory");
}

#endif /* __CPUPORT_H__ */
