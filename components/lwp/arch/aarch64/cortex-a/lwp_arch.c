/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-18     Jesven       first version
 * 2023-07-16     Shell        Move part of the codes to C from asm in signal handling
 * 2023-10-16     Shell        Support a new backtrace framework
 * 2023-08-03     Shell        Support of syscall restart (SA_RESTART)
 */

#include <armv8.h>
#include <rthw.h>
#include <rtthread.h>
#include <stdlib.h>
#include <string.h>
#include <lwp_internal.h>

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

    mmu_table = rt_hw_mmu_pgtbl_create();
    if (mmu_table)
    {
        lwp->end_heap = USER_HEAP_VADDR;
        lwp->aspace = rt_aspace_create(
            (void *)USER_VADDR_START, USER_VADDR_TOP - USER_VADDR_START, mmu_table);
        if (!lwp->aspace)
        {
            return -RT_ERROR;
        }
    }
    else
    {
        return -RT_ENOMEM;
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

int arch_set_thread_context(void (*exit)(void), void *new_thread_stack,
                            void *user_stack, void **thread_sp)
{
    struct rt_hw_exp_stack *syscall_frame;
    struct rt_hw_exp_stack *thread_frame;
    struct rt_hw_exp_stack *ori_syscall = rt_thread_self()->user_ctx.ctx;
    RT_ASSERT(ori_syscall != RT_NULL);

    new_thread_stack = (rt_ubase_t*)RT_ALIGN_DOWN((rt_ubase_t)new_thread_stack, 16);

    syscall_frame = (void *)((long)new_thread_stack - sizeof(struct rt_hw_exp_stack));
    memcpy(syscall_frame, ori_syscall, sizeof(*syscall_frame));
    syscall_frame->sp_el0 = (long)user_stack;
    syscall_frame->x0 = 0;

    thread_frame = (void *)rt_hw_stack_init(exit, RT_NULL, (void *)syscall_frame, RT_NULL);

    *thread_sp = thread_frame;

    return 0;
}

#define ALGIN_BYTES (16)

/* the layout is part of ABI, dont change it */
struct signal_ucontext
{
    rt_int64_t sigreturn;
    lwp_sigset_t save_sigmask;

    siginfo_t si;

    rt_align(ALGIN_BYTES)
    struct rt_hw_exp_stack frame;
};

RT_STATIC_ASSERT(abi_offset_compatible, offsetof(struct signal_ucontext, si) == UCTX_ABI_OFFSET_TO_SI);

void *arch_signal_ucontext_get_frame(struct signal_ucontext *uctx)
{
    return &uctx->frame;
}

/* internal used only */
void arch_syscall_prepare_signal(rt_base_t rc, struct rt_hw_exp_stack *exp_frame)
{
    long x0 = exp_frame->x0;
    exp_frame->x0 = rc;
    exp_frame->x7 = x0;
    return ;
}

void arch_syscall_restart(void *sp, void *ksp);

void arch_syscall_set_errno(void *eframe, int expected, int code)
{
    struct rt_hw_exp_stack *exp_frame = eframe;
    if (exp_frame->x0 == -expected)
        exp_frame->x0 = -code;
    return ;
}

void arch_signal_check_erestart(void *eframe, void *ksp)
{
    struct rt_hw_exp_stack *exp_frame = eframe;
    long rc = exp_frame->x0;
    long sys_id = exp_frame->x8;
    (void)sys_id;

    if (rc == -ERESTART)
    {
        LOG_D("%s(rc=%ld,sys_id=%ld,pid=%d)", __func__, rc, sys_id, lwp_self()->pid);
        LOG_D("%s: restart rc = %ld", lwp_get_syscall_name(sys_id), rc);
        exp_frame->x0 = exp_frame->x7;
        arch_syscall_restart(eframe, ksp);
    }

    return ;
}

static void arch_signal_post_action(struct signal_ucontext *new_sp, rt_base_t kernel_sp)
{
    arch_signal_check_erestart(&new_sp->frame, (void *)kernel_sp);

    return ;
}

void *arch_signal_ucontext_restore(rt_base_t user_sp, rt_base_t kernel_sp)
{
    struct signal_ucontext *new_sp;
    new_sp = (void *)user_sp;

    if (lwp_user_accessable(new_sp, sizeof(*new_sp)))
    {
        lwp_thread_signal_mask(rt_thread_self(), LWP_SIG_MASK_CMD_SET_MASK, &new_sp->save_sigmask, RT_NULL);
        arch_signal_post_action(new_sp, kernel_sp);
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
    new_sp = (void *)((user_sp - sizeof(struct signal_ucontext)) & ~0xf);

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

int arch_backtrace_uthread(rt_thread_t thread)
{
    struct rt_hw_backtrace_frame frame;
    struct rt_hw_exp_stack *stack;

    if (thread && thread->lwp)
    {
        stack = thread->user_ctx.ctx;
        if ((long)stack > (unsigned long)thread->stack_addr
            && (long)stack < (unsigned long)thread->stack_addr + thread->stack_size)
        {
            frame.pc = stack->pc;
            frame.fp = stack->x29;
            lwp_backtrace_frame(thread, &frame);
            return 0;
        }
        else
            return -1;
    }
    return -1;
}
