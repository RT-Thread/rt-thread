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
#define USER_HEAP_VADDR   (0x0000ffff40000000UL)
#define USER_HEAP_VEND    USER_STACK_VSTART
#define USER_STACK_VSTART 0x0000ffff70000000UL
#define USER_STACK_VEND   (USER_STACK_VSTART + 0x10000000)
#define USER_ARG_VADDR    USER_STACK_VEND
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

/**
 * @brief Save signal-related context to user stack
 *
 * @param user_sp the current sp of user
 * @param exp_frame exception frame to resume former execution
 * @param psiginfo pointer to the siginfo
 * @param elr pc of former execution
 * @param spsr program status of former execution
 * @return void* the new user sp
 */
void *arch_signal_ucontext_save(rt_base_t user_sp, siginfo_t *psiginfo,
                                struct rt_hw_exp_stack *exp_frame,
                                lwp_sigset_t *save_sig_mask);

/**
 * @brief Restore the signal mask after return
 *
 * @param user_sp sp of user
 * @return void*
 */
void *arch_signal_ucontext_restore(rt_base_t user_sp);
#ifdef __cplusplus
}
#endif

#endif

#endif  /*LWP_ARCH_H__*/
