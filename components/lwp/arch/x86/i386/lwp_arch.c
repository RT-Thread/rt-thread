/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-7-14      JasonHu      first version
 */

#include <rthw.h>
#include <stddef.h>
#include <rtconfig.h>
#include <rtdbg.h>

#ifdef ARCH_MM_MMU

#include <stackframe.h>
#include <interrupt.h>
#include <segment.h>

#include <mmu.h>
#include <page.h>
#include <lwp_mm_area.h>
#include <lwp_user_mm.h>
#include <lwp_arch.h>

#ifdef RT_USING_SIGNALS
#include <lwp_signal.h>
#endif /* RT_USING_SIGNALS */

extern size_t g_mmu_table[];

int arch_expand_user_stack(void *addr)
{
    int ret = 0;
    size_t stack_addr = (size_t)addr;

    stack_addr &= ~PAGE_OFFSET_MASK;
    if ((stack_addr >= (size_t)USER_STACK_VSTART) && (stack_addr < (size_t)USER_STACK_VEND))
    {
        void *map = lwp_map_user(lwp_self(), (void *)stack_addr, PAGE_SIZE, RT_FALSE);

        if (map || lwp_user_accessable(addr, 1))
        {
            ret = 1;    /* map success */
        }
        else /* map failed, send signal SIGSEGV */
        {
#ifdef RT_USING_SIGNALS
            dbg_log(DBG_ERROR, "[fault] thread %s mapped addr %p failed!\n", rt_thread_self()->parent.name, addr);
            lwp_thread_kill(rt_thread_self(), SIGSEGV);
            ret = 1;    /* return 1, will return back to intr, then check exit */
#endif
        }
    }
    else    /* not stack, send signal SIGSEGV */
    {
#ifdef RT_USING_SIGNALS
        dbg_log(DBG_ERROR, "[fault] thread %s access unmapped addr %p!\n", rt_thread_self()->parent.name, addr);
        lwp_thread_kill(rt_thread_self(), SIGSEGV);
        ret = 1;    /* return 1, will return back to intr, then check exit */
#endif
    }
    return ret;
}

void *get_thread_kernel_stack_top(rt_thread_t thread)
{
    return RT_NULL;
}

/**
 * don't support this in i386, it's ok!
 */
void *arch_get_user_sp()
{
    return RT_NULL;
}

int arch_user_space_init(struct rt_lwp *lwp)
{
    rt_size_t *mmu_table;

    mmu_table = (rt_size_t *)rt_pages_alloc(0);
    if (!mmu_table)
    {
        return -1;
    }
    rt_memset(mmu_table, 0, ARCH_PAGE_SIZE);

    lwp->end_heap = USER_HEAP_VADDR;
    memcpy(mmu_table, g_mmu_table, ARCH_PAGE_SIZE / 4);
    memset((rt_uint8_t *)mmu_table + ARCH_PAGE_SIZE / 4, 0, ARCH_PAGE_SIZE / 4 * 3);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, mmu_table, ARCH_PAGE_SIZE);
    if (rt_hw_mmu_map_init(&lwp->mmu_info, (void*)USER_VADDR_START, USER_VADDR_TOP - USER_VADDR_START, mmu_table, PV_OFFSET) < 0)
    {
        rt_pages_free(mmu_table, 0);
        return -1;
    }
    return 0;
}

void *arch_kernel_mmu_table_get(void)
{
    return (void *)((char *)g_mmu_table);
}

void arch_user_space_vtable_free(struct rt_lwp *lwp)
{
    if (lwp && lwp->mmu_info.vtable)
    {
        rt_pages_free(lwp->mmu_info.vtable, 0);
        lwp->mmu_info.vtable = NULL;
    }
}

void arch_set_thread_area(void *p)
{
    rt_hw_seg_tls_set((rt_ubase_t) p);
    rt_thread_t cur = rt_thread_self();
    cur->thread_idr = p; /* update thread idr after first set */
}

void *arch_get_tidr(void)
{
    rt_thread_t cur = rt_thread_self();
    if (!cur->lwp)  /* no lwp, don't get thread idr from tls seg */
        return NULL;
    return (void *)rt_hw_seg_tls_get();   /* get thread idr from tls seg */
}

void arch_set_tidr(void *p)
{
    rt_thread_t cur = rt_thread_self();
    if (!cur->lwp) /* no lwp, don't set thread idr to tls seg */
        return;
    rt_hw_seg_tls_set((rt_ubase_t) p); /* set tls seg addr as thread idr */
}

static void lwp_user_stack_init(rt_hw_stack_frame_t *frame)
{
    frame->ds = frame->es = USER_DATA_SEL;
    frame->cs = USER_CODE_SEL;
    frame->ss = USER_STACK_SEL;
    frame->gs = USER_TLS_SEL;
    frame->fs = 0;  /* unused */

    frame->edi = frame->esi = \
    frame->ebp = frame->esp_dummy = 0;
    frame->eax = frame->ebx = \
    frame->ecx = frame->edx = 0;

    frame->error_code = 0;
    frame->vec_no = 0;

    frame->eflags = (EFLAGS_MBS | EFLAGS_IF_1 | EFLAGS_IOPL_3);
}

extern void lwp_switch_to_user(void *frame);
/**
 * user entry, set frame.
 * at the end of execute, we need enter user mode,
 * in x86, we can set stack, arg, text entry in a stack frame,
 * then pop then into register, final use iret to switch kernel mode to user mode.
 */
void arch_start_umode(void *args, const void *text, void *ustack, void *k_stack)
{
    rt_uint8_t *stk = k_stack;
    stk -= sizeof(struct rt_hw_stack_frame);
    struct rt_hw_stack_frame *frame = (struct rt_hw_stack_frame *)stk;

    lwp_user_stack_init(frame);
    frame->esp = (rt_uint32_t)ustack - 32;
    frame->ebx = (rt_uint32_t)args;
    frame->eip = (rt_uint32_t)text;
    lwp_switch_to_user(frame);
    /* should never return */
}

void lwp_exec_user(void *args, void *kernel_stack, void *user_entry)
{
    arch_start_umode(args, (const void *)user_entry, (void *)USER_STACK_VEND, kernel_stack);
}

extern void lwp_thread_return();
extern void lwp_thread_return_end();

static void *lwp_copy_return_code_to_user_stack(void *ustack)
{
    size_t size = (size_t)lwp_thread_return_end - (size_t)lwp_thread_return;
    void *retcode = (void *)((size_t)ustack - size);
    memcpy(retcode, (void *)lwp_thread_return, size);
    return retcode;
}

/**
 * when called sys_thread_create, need create a thread, after thread stared, will come here,
 * like arch_start_umode, will enter user mode, but we must set thread exit function. it looks like:
 * void func(void *arg)
 * {
 *      ...
 * }
 * when thread func return, we must call exit code to exit thread, or not the program runs away.
 * so we need copy exit code to user and call exit code when func return.
 */
void arch_crt_start_umode(void *args, const void *text, void *ustack, void *k_stack)
{
    RT_ASSERT(ustack != NULL);

    rt_uint8_t *stk;
    stk  = (rt_uint8_t *)((rt_uint8_t *)k_stack + sizeof(rt_ubase_t));
    stk  = (rt_uint8_t *)RT_ALIGN_DOWN(((rt_ubase_t)stk), sizeof(rt_ubase_t));
    stk -= sizeof(struct rt_hw_stack_frame);
    struct rt_hw_stack_frame *frame = (struct rt_hw_stack_frame *)stk;

    lwp_user_stack_init(frame);

    /* make user thread stack */
    unsigned long *retcode = lwp_copy_return_code_to_user_stack(ustack);    /* copy ret code */
    unsigned long *retstack = (unsigned long *)RT_ALIGN_DOWN(((rt_ubase_t)retcode), sizeof(rt_ubase_t));

    /**
     * x86 call stack
     *
     * retcode here
     *
     * arg n
     * arg n - 1
     * ...
     * arg 2
     * arg 1
     * arg 0
     * eip (caller return addr, point to retcode)
     * esp
     */
    *(--retstack) = (unsigned long) args;       /* arg */
    *(--retstack) = (unsigned long) retcode;    /* ret eip */

    frame->esp = (rt_uint32_t)retstack;
    frame->eip = (rt_uint32_t)text;
    lwp_switch_to_user(frame);
    /* should never return */
}

rt_thread_t rt_thread_sp_to_thread(void *spmember_addr)
{
    return (rt_thread_t)(((rt_ubase_t)spmember_addr) - (offsetof(struct rt_thread, sp)));
}

/**
 * set exec context for fork/clone.
 * user_stack(unused)
 */
void arch_set_thread_context(void *exit_addr, void *new_thread_stack, void *user_stack, void **thread_sp)
{
    /**
     * thread kernel stack was set to tss.esp0, when intrrupt/syscall occur,
     * the stack frame will store in kernel stack top, so we can get the stack
     * frame by kernel stack top.
     */
    rt_hw_stack_frame_t *frame = (rt_hw_stack_frame_t *)((rt_ubase_t)new_thread_stack - sizeof(rt_hw_stack_frame_t));

    frame->eax = 0; /* child return 0 */

    rt_hw_context_t *context = (rt_hw_context_t *) (((rt_uint32_t *)frame) - HW_CONTEXT_MEMBER_NR);
    context->eip = (void *)exit_addr;    /* when thread started, jump to intr exit for enter user mode */
    context->ebp = context->ebx = context->esi = context->edi = 0;

    /**
     * set sp as the address of first member of rt_hw_context,
     * when scheduler call switch, pop stack from context stack.
     */
    *thread_sp = (void *)&context->ebp;

    /**
     * after set context, the stack like this:
     *
     * -----------
     * stack frame| eax = 0
     * -----------
     * context(only HW_CONTEXT_MEMBER_NR)| eip = rt_hw_intr_exit
     * -----------
     * thread sp  | to <- rt_hw_context_switch(from, to)
     * -----------
     */
}

#ifdef RT_USING_SIGNALS

#define SIGNAL_RET_CODE_SIZE    16

struct rt_signal_frame
{
    char *ret_addr; /* return addr when handler return */
    int signo;   /* signal for user handler arg  */
    rt_hw_stack_frame_t frame; /* save kernel signal stack */
    char ret_code[SIGNAL_RET_CODE_SIZE];    /* save return code  */
};
typedef struct rt_signal_frame rt_signal_frame_t;

extern void lwp_signal_return();
extern void lwp_signal_return_end();

void lwp_try_do_signal(rt_hw_stack_frame_t *frame)
{
    if (!lwp_signal_check())
        return;

    /* 1. backup signal mask */
    int signal = lwp_signal_backup((void *) frame->esp, (void *) frame->eip, (void *) frame->eflags);

    /* 2. get signal handler */
    lwp_sighandler_t handler = lwp_sighandler_get(signal);
    if (handler == RT_NULL) /* no handler, ignore  */
    {
        lwp_signal_restore();
        return;
    }

    rt_base_t level = rt_hw_interrupt_disable();
    /* 3. backup frame */
    rt_signal_frame_t *sig_frame = (rt_signal_frame_t *)((frame->esp - sizeof(rt_signal_frame_t)) & -8UL);
    memcpy(&sig_frame->frame, frame, sizeof(rt_hw_stack_frame_t));
    sig_frame->signo = signal;

    /**
     * 4. copy user return code into user stack
     *
     * save current frame on user stack. the user stack like:
     *
     * ----------
     * user code stack
     * ----------+ -> esp before enter kernel
     * signal frame
     * ----------+ -> esp when handle signal handler
     * signal handler stack
     * ----------
     */
    size_t ret_code_size = (size_t)lwp_signal_return_end - (size_t)lwp_signal_return;
    memcpy(sig_frame->ret_code, (void *)lwp_signal_return, ret_code_size);
    sig_frame->ret_addr = sig_frame->ret_code;

    /* 5. jmp to user execute handler, update frame register info */
    lwp_user_stack_init(frame);
    frame->eip = (rt_uint32_t) handler;
    frame->esp = (rt_uint32_t) sig_frame;

    rt_hw_interrupt_enable(level);
}

void lwp_signal_do_return(rt_hw_stack_frame_t *frame)
{
    /**
     * ASSUME: in x86, each stack push and pop element is 4 byte. so STACK_ELEM_SIZE = sizeof(int) => 4.
     * when signal handler return, the stack move to the buttom of signal frame.
     * but return will pop eip from esp, then {esp += STACK_ELEM_SIZE}, thus {esp = (signal frame) + STACK_ELEM_SIZE}.
     * so {(signal frame) = esp - STACK_ELEM_SIZE}
     */
    rt_signal_frame_t *sig_frame = (rt_signal_frame_t *)(frame->esp - sizeof(rt_uint32_t));
    memcpy(frame, &sig_frame->frame, sizeof(rt_hw_stack_frame_t));

    /**
     * restore signal info, but don't use rt_user_context,
     * we use sig_frame to restore stack frame
     */
    lwp_signal_restore();
}
#endif /* RT_USING_SIGNALS */

#endif  /* ARCH_MM_MMU */
