/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-18     Jesven       first version
 * 2023-07-16     Shell        Move part of the codes to C from asm in signal handling
 */

#include <armv8.h>
#include <rthw.h>
#include <rtthread.h>
#include <stdlib.h>
#include <string.h>
#include <lwp_signal.h>

#ifdef ARCH_MM_MMU

#define DBG_TAG "lwp.arch"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <lwp_arch.h>
#include <lwp_user_mm.h>

extern size_t MMUTable[];

int arch_user_space_init(struct rt_lwp *lwp)
{
    size_t *mmu_table;

    mmu_table = (size_t *)rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE);
    if (!mmu_table)
    {
        return -RT_ENOMEM;
    }

    lwp->end_heap = USER_HEAP_VADDR;

    memset(mmu_table, 0, ARCH_PAGE_SIZE);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, mmu_table, ARCH_PAGE_SIZE);

    lwp->aspace = rt_aspace_create(
        (void *)USER_VADDR_START, USER_VADDR_TOP - USER_VADDR_START, mmu_table);
    if (!lwp->aspace)
    {
        return -RT_ERROR;
    }

    return 0;
}

void *arch_kernel_mmu_table_get(void)
{
    return (void *)NULL;
}

void arch_user_space_free(struct rt_lwp *lwp)
{
    if (lwp)
    {
        RT_ASSERT(lwp->aspace);
        void *pgtbl = lwp->aspace->page_table;
        rt_aspace_delete(lwp->aspace);

        /* must be freed after aspace delete, pgtbl is required for unmap */
        rt_pages_free(pgtbl, 0);
        lwp->aspace = NULL;
    }
    else
    {
        LOG_W("%s: NULL lwp as parameter", __func__);
        RT_ASSERT(0);
    }
}

int arch_expand_user_stack(void *addr)
{
    int ret = 0;
    size_t stack_addr = (size_t)addr;

    stack_addr &= ~ARCH_PAGE_MASK;
    if ((stack_addr >= (size_t)USER_STACK_VSTART) &&
        (stack_addr < (size_t)USER_STACK_VEND))
    {
        void *map =
            lwp_map_user(lwp_self(), (void *)stack_addr, ARCH_PAGE_SIZE, 0);

        if (map || lwp_user_accessable(addr, 1))
        {
            ret = 1;
        }
    }
    return ret;
}

#endif
#define ALGIN_BYTES (16)

struct signal_ucontext
{
    rt_int64_t sigreturn;
    lwp_sigset_t save_sigmask;

    siginfo_t si;

    rt_align(16)
    struct rt_hw_exp_stack frame;
};

void *arch_signal_ucontext_restore(rt_base_t user_sp)
{
    struct signal_ucontext *new_sp;
    new_sp = (void *)user_sp;

    if (lwp_user_accessable(new_sp, sizeof(*new_sp)))
    {
        lwp_thread_signal_mask(rt_thread_self(), LWP_SIG_MASK_CMD_SET_MASK, &new_sp->save_sigmask, RT_NULL);
    }
    else
    {
        LOG_I("User frame corrupted during signal handling\nexiting...");
        sys_exit_group(EXIT_FAILURE);
    }

    return (char *)&new_sp->frame + sizeof(struct rt_hw_exp_stack);
}

void *arch_signal_ucontext_save(rt_base_t user_sp, siginfo_t *psiginfo,
                                struct rt_hw_exp_stack *exp_frame,
                                lwp_sigset_t *save_sig_mask)
{
    struct signal_ucontext *new_sp;
    new_sp = (void *)(user_sp - sizeof(struct signal_ucontext));

    if (lwp_user_accessable(new_sp, sizeof(*new_sp)))
    {
        /* push psiginfo */
        if (psiginfo)
        {
            lwp_memcpy(&new_sp->si, psiginfo, sizeof(*psiginfo));
        }

        /* exp frame is already aligned as AAPCS64 required */
        lwp_memcpy(&new_sp->frame, exp_frame, sizeof(*exp_frame));

        /* copy the save_sig_mask */
        lwp_memcpy(&new_sp->save_sigmask, save_sig_mask, sizeof(lwp_sigset_t));

        /* copy lwp_sigreturn */
        const size_t lwp_sigreturn_bytes = 8;
        extern void lwp_sigreturn(void);
        /* -> ensure that the sigreturn start at the outer most boundary */
        lwp_memcpy(&new_sp->sigreturn,  &lwp_sigreturn, lwp_sigreturn_bytes);
    }
    else
    {
        LOG_I("%s: User stack overflow", __func__);
        sys_exit_group(EXIT_FAILURE);
    }

    return new_sp;
}
