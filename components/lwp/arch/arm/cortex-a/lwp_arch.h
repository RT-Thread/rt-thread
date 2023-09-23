/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef  LWP_ARCH_H__
#define  LWP_ARCH_H__

#include <lwp.h>
#include <lwp_arch_comm.h>

#ifdef ARCH_MM_MMU

#define USER_VADDR_TOP    0xC0000000UL
#define USER_HEAP_VEND    0xB0000000UL
#define USER_HEAP_VADDR   0x80000000UL
#define USER_STACK_VSTART 0x70000000UL
#define USER_STACK_VEND   USER_HEAP_VADDR
#define LDSO_LOAD_VADDR   0x60000000UL
#define USER_VADDR_START  0x00100000UL
#define USER_LOAD_VADDR   USER_VADDR_START

#ifdef __cplusplus
extern "C" {
#endif

rt_inline unsigned long rt_hw_ffz(unsigned long x)
{
    return __builtin_ffsl(~x) - 1;
}

rt_inline void icache_invalid_all(void)
{
    asm volatile ("mcr p15, 0, r0, c7, c5, 0\ndsb\nisb":::"memory");//iciallu
}

unsigned int arch_get_asid(struct rt_lwp *lwp);

struct signal_regs;
void *arch_signal_ucontext_restore(rt_base_t user_sp);
void *arch_signal_ucontext_save(rt_base_t lr, siginfo_t *psiginfo,
                                struct signal_regs *exp_frame, rt_base_t user_sp,
                                lwp_sigset_t *save_sig_mask);

#ifdef __cplusplus
}
#endif

#endif

#endif  /*LWP_ARCH_H__*/
