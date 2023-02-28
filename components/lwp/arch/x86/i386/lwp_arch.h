/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-18     JasonHu      first version
 */

#ifndef  LWP_ARCH_H__
#define  LWP_ARCH_H__

#include <lwp.h>
#include <lwp_arch_comm.h>
#include <stackframe.h>

#ifdef ARCH_MM_MMU
#define USER_VADDR_TOP    0xFFFFF000UL
#define USER_HEAP_VEND    0xE0000000UL
#define USER_HEAP_VADDR   0x90000000UL
#define USER_STACK_VSTART 0x80000000UL
#define USER_STACK_VEND   USER_HEAP_VADDR
#define LDSO_LOAD_VADDR   0x70000000UL
#define USER_VADDR_START  0x40000000UL
#define USER_LOAD_VADDR   USER_VADDR_START

#define SIGNAL_RETURN_SYSCAL_ID    0xe000

#ifdef __cplusplus
extern "C" {
#endif

rt_thread_t rt_thread_sp_to_thread(void *spmember_addr);

void lwp_signal_do_return(rt_hw_stack_frame_t *frame);

rt_inline unsigned long rt_hw_ffz(unsigned long x)
{
    return __builtin_ffsl(~x) - 1;
}

#ifdef __cplusplus
}
#endif

#endif  /* ARCH_MM_MMU */

#endif  /*LWP_ARCH_H__*/
