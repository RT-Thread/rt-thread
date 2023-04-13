/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-18     Jesven       first version
 */

#ifndef  LWP_ARCH_H__
#define  LWP_ARCH_H__

#include <lwp.h>
#include <lwp_arch_comm.h>

#ifdef ARCH_MM_MMU

#define USER_VADDR_TOP    0x0001000000000000UL
#define USER_HEAP_VEND    0x0000ffffB0000000UL
#define USER_HEAP_VADDR   0x0000ffff80000000UL
#define USER_STACK_VSTART 0x0000ffff70000000UL
#define USER_STACK_VEND   USER_HEAP_VADDR
#define LDSO_LOAD_VADDR   0x60000000UL
#define USER_VADDR_START  0x00200000UL
#define USER_LOAD_VADDR   USER_VADDR_START

#ifdef __cplusplus
extern "C" {
#endif

unsigned long rt_hw_ffz(unsigned long x);

rt_inline void icache_invalid_all(void)
{
    asm volatile ("ic ialluis\n\tisb sy":::"memory");
}

#ifdef __cplusplus
}
#endif

#endif

#endif  /*LWP_ARCH_H__*/
