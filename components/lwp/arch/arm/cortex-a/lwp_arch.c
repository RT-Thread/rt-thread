/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-28     Jesven       first version
 * 2023-07-16     Shell        Move part of the codes to C from asm in signal handling
 */

#include <rthw.h>
#include <rtthread.h>
#include <stddef.h>
#include <stdlib.h>

#ifdef ARCH_MM_MMU

#define DBG_TAG "lwp.arch"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <lwp_arch.h>
#include <lwp_user_mm.h>

int arch_user_space_init(struct rt_lwp *lwp)
{
    size_t *mmu_table;

    mmu_table = rt_hw_mmu_pgtbl_create();
    if (!mmu_table)
    {
        return -RT_ENOMEM;
    }

    lwp->end_heap = USER_HEAP_VADDR;


    lwp->aspace = rt_aspace_create((void *)USER_VADDR_START, USER_VADDR_TOP - USER_VADDR_START, mmu_table);
    if (!lwp->aspace)
    {
        return -RT_ERROR;
    }

    return 0;
}

static struct rt_varea kuser_varea;

void arch_kuser_init(rt_aspace_t aspace, void *vectors)
{
    int err;
    const size_t kuser_size = 0x1000;
    extern char __kuser_helper_start[];
    extern char __kuser_helper_end[];
    rt_base_t start = (rt_base_t)__kuser_helper_start;
    rt_base_t end = (rt_base_t)__kuser_helper_end;
    int kuser_sz = end - start;

    err = rt_aspace_map_static(aspace, &kuser_varea, &vectors, kuser_size,
                               MMU_MAP_U_RO, MMF_MAP_FIXED | MMF_PREFETCH,
                               &rt_mm_dummy_mapper, 0);
    if (err != 0)
        while (1)
            ; // early failed

    lwp_memcpy((void *)((char *)vectors + 0x1000 - kuser_sz), __kuser_helper_start, kuser_sz);
    /*
     * vectors + 0xfe0 = __kuser_get_tls
     * vectors + 0xfe8 = hardware TLS instruction at 0xffff0fe8
     */
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)((char *)vectors + 0x1000 - kuser_sz), kuser_sz);
    rt_hw_cpu_icache_ops(RT_HW_CACHE_INVALIDATE, (void *)((char *)vectors + 0x1000 - kuser_sz), kuser_sz);
}

void arch_user_space_free(struct rt_lwp *lwp)
{
    if (lwp)
    {
        RT_ASSERT(lwp->aspace);
        void *pgtbl = lwp->aspace->page_table;
        rt_aspace_delete(lwp->aspace);

        /* must be freed after aspace delete, pgtbl is required for unmap */
        rt_hw_mmu_pgtbl_delete(pgtbl);
        lwp->aspace = RT_NULL;
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
    if ((stack_addr >= (size_t)USER_STACK_VSTART) && (stack_addr < (size_t)USER_STACK_VEND))
    {
        void *map = lwp_map_user(lwp_self(), (void *)stack_addr, ARCH_PAGE_SIZE, 0);

        if (map || lwp_user_accessable(addr, 1))
        {
            ret = 1;
        }
    }
    return ret;
}
#define ALGIN_BYTES 8
#define lwp_sigreturn_bytes 8
struct signal_regs {
    rt_base_t lr;
    rt_base_t spsr;
    rt_base_t r0_to_r12[13];
    rt_base_t ip;
};

struct signal_ucontext
{
    rt_base_t sigreturn[lwp_sigreturn_bytes / sizeof(rt_base_t)];
    lwp_sigset_t save_sigmask;

    siginfo_t si;

    rt_align(8)
    struct signal_regs frame;
};

void *arch_signal_ucontext_restore(rt_base_t user_sp)
{
    struct signal_ucontext *new_sp;
    rt_base_t ip;
    new_sp = (void *)user_sp;

    if (lwp_user_accessable(new_sp, sizeof(*new_sp)))
    {
        lwp_thread_signal_mask(rt_thread_self(), LWP_SIG_MASK_CMD_SET_MASK, &new_sp->save_sigmask, RT_NULL);
        ip = new_sp->frame.ip;
        /* let user restore its lr from frame.ip */
        new_sp->frame.ip = new_sp->frame.lr;
        /* kernel will pick eip from frame.lr */
        new_sp->frame.lr = ip;
    }
    else
    {
        LOG_I("User frame corrupted during signal handling\nexiting...");
        sys_exit_group(EXIT_FAILURE);
    }

    return (void *)&new_sp->frame;
}

void *arch_signal_ucontext_save(rt_base_t lr, siginfo_t *psiginfo,
                                struct signal_regs *exp_frame, rt_base_t user_sp,
                                lwp_sigset_t *save_sig_mask)
{
    rt_base_t spsr;
    struct signal_ucontext *new_sp;
    new_sp = (void *)(user_sp - sizeof(struct signal_ucontext));

    if (lwp_user_accessable(new_sp, sizeof(*new_sp)))
    {
        /* push psiginfo */
        if (psiginfo)
        {
            lwp_memcpy(&new_sp->si, psiginfo, sizeof(*psiginfo));
        }

        lwp_memcpy(&new_sp->frame.r0_to_r12, exp_frame, sizeof(new_sp->frame.r0_to_r12) + sizeof(rt_base_t));
        new_sp->frame.lr = lr;

        __asm__ volatile("mrs %0, spsr":"=r"(spsr));
        new_sp->frame.spsr = spsr;

        /* copy the save_sig_mask */
        lwp_memcpy(&new_sp->save_sigmask, save_sig_mask, sizeof(lwp_sigset_t));

        /* copy lwp_sigreturn */
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

void arch_syscall_set_errno(void *eframe, int expected, int code)
{
    /* NO support */
    return ;
}

#ifdef LWP_ENABLE_ASID
#define MAX_ASID_BITS 8
#define MAX_ASID (1 << MAX_ASID_BITS)
static uint64_t global_generation = 1;
static char asid_valid_bitmap[MAX_ASID];
unsigned int arch_get_asid(struct rt_lwp *lwp)
{
    if (lwp == RT_NULL)
    {
        // kernel
        return 0;
    }

    if (lwp->generation == global_generation)
    {
        return lwp->asid;
    }

    if (lwp->asid && !asid_valid_bitmap[lwp->asid])
    {
        asid_valid_bitmap[lwp->asid] = 1;
        return lwp->asid;
    }

    for (unsigned i = 1; i < MAX_ASID; i++)
    {
        if (asid_valid_bitmap[i] == 0)
        {
            asid_valid_bitmap[i] = 1;
            lwp->generation = global_generation;
            lwp->asid = i;
            return lwp->asid;
        }
    }

    global_generation++;
    memset(asid_valid_bitmap, 0, MAX_ASID * sizeof(char));

    asid_valid_bitmap[1] = 1;
    lwp->generation = global_generation;
    lwp->asid = 1;

    asm volatile ("mcr p15, 0, r0, c8, c7, 0\ndsb\nisb" ::: "memory");

    return lwp->asid;
}
#endif

#endif
