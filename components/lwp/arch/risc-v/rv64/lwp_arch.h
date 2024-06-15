/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef  LWP_ARCH_H__
#define  LWP_ARCH_H__

#include <rthw.h>
#include <lwp.h>
#include <lwp_arch_comm.h>

#ifdef ARCH_MM_MMU

#ifdef ARCH_MM_MMU_32BIT_LIMIT
#define USER_HEAP_VADDR     0xF0000000UL
#define USER_HEAP_VEND      0xFE000000UL
#define USER_STACK_VSTART   0xE0000000UL
#define USER_STACK_VEND     USER_HEAP_VADDR
#define USER_VADDR_START    0xC0000000UL
#define USER_VADDR_TOP      0xFF000000UL
#define USER_LOAD_VADDR     0xD0000000UL
#define LDSO_LOAD_VADDR     USER_LOAD_VADDR
#else
#define USER_HEAP_VADDR     0x300000000UL
#define USER_HEAP_VEND      USER_STACK_VSTART
#define USER_STACK_VSTART   0x370000000UL
#define USER_STACK_VEND     0x400000000UL
#define USER_VADDR_START    0x200000000UL
#define USER_VADDR_TOP      0xfffffffffffff000UL
#define USER_LOAD_VADDR     0x200000000UL
#define LDSO_LOAD_VADDR     0x200000000UL
#endif

/* this attribution is cpu specified, and it should be defined in riscv_mmu.h */
#ifndef MMU_MAP_U_RWCB
#define MMU_MAP_U_RWCB 0
#endif

#ifndef MMU_MAP_U_RW
#define MMU_MAP_U_RW 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

rt_inline unsigned long rt_hw_ffz(unsigned long x)
{
    return __builtin_ffsl(~x) - 1;
}

rt_inline void icache_invalid_all(void)
{
    rt_hw_cpu_icache_invalidate_all();
}

struct rt_hw_stack_frame;
void *arch_signal_ucontext_restore(rt_base_t user_sp);
void *arch_signal_ucontext_save(int signo, siginfo_t *psiginfo,
                                struct rt_hw_stack_frame *exp_frame, rt_base_t user_sp,
                                lwp_sigset_t *save_sig_mask);
#ifdef __cplusplus
}
#endif

#endif

#endif  /*LWP_ARCH_H__*/
