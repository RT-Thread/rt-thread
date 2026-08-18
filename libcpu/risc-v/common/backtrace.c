/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-10-18     Shell        Add backtrace support
 */

#define DBG_TAG "hw.backtrace"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <stack.h>
#include <rtthread.h>
#ifdef ARCH_MM_MMU
#include <mmu.h>
#include <mm_aspace.h>
#endif

#define WORD                            sizeof(rt_base_t)
#define ARCH_CONTEXT_FETCH(pctx, id)    (*(((unsigned long *)pctx) + (id)))

rt_inline rt_err_t _bt_kaddr(rt_ubase_t *fp, struct rt_hw_backtrace_frame *frame)
{
    rt_err_t rc;
    frame->fp = *(fp - 2);
    frame->pc = *(fp - 1);

    if ((rt_ubase_t)fp == frame->fp)
    {
        rc = -RT_ERROR;
    }
    else
    {
        rc = RT_EOK;
    }
    return rc;
}

#ifndef ARCH_MM_MMU
static rt_bool_t _bt_thread_stack_contains(rt_thread_t thread, rt_ubase_t *fp)
{
    rt_ubase_t frame_start;
    rt_ubase_t stack_start;
    rt_ubase_t stack_end;

    if (!thread)
    {
        thread = rt_thread_self();
    }
    if (!thread || (rt_ubase_t)fp < 2 * WORD)
    {
        return RT_FALSE;
    }

    frame_start = (rt_ubase_t)(fp - 2);
    stack_start = (rt_ubase_t)thread->stack_addr;
    stack_end = stack_start + thread->stack_size;

    return frame_start >= stack_start &&
            frame_start + 2 * WORD <= stack_end;
}
#endif

#ifdef RT_USING_SMART
#include <lwp_arch.h>
#include <lwp_user_mm.h>

rt_inline rt_err_t _bt_uaddr(rt_lwp_t lwp, rt_ubase_t *fp, struct rt_hw_backtrace_frame *frame)
{
    rt_err_t rc;
    if (lwp_data_get(lwp, &frame->fp, fp - 2, WORD) != WORD)
    {
        rc = -RT_EFAULT;
    }
    else if (lwp_data_get(lwp, &frame->pc, fp - 1, WORD) != WORD)
    {
        rc = -RT_EFAULT;
    }
    else if ((rt_ubase_t)fp == frame->fp)
    {
        rc = -RT_ERROR;
    }
    else
    {
        frame->pc -= 0;
        rc = RT_EOK;
    }
    return rc;
}
#endif /* RT_USING_SMART */

rt_err_t rt_hw_backtrace_frame_unwind(rt_thread_t thread, struct rt_hw_backtrace_frame *frame)
{
    rt_err_t rc = -RT_ERROR;
    rt_ubase_t *fp = (rt_ubase_t *)frame->fp;

    if (fp && !((long)fp & 0x7))
    {
    #ifdef RT_USING_SMART
        if (thread && thread->lwp)
        {
            void *lwp = thread->lwp;
            void *this_lwp = lwp_self();
            if (this_lwp == lwp && rt_hw_mmu_v2p(((rt_lwp_t)lwp)->aspace, fp) != ARCH_MAP_FAILED)
            {
                rc = _bt_kaddr(fp, frame);
            }
            else if (lwp_user_accessible_ext(lwp, (void *)fp, WORD))
            {
                rc = _bt_uaddr(lwp, fp, frame);
            }
            else
            {
                rc = -RT_EFAULT;
            }
        }
        else
    #endif /* RT_USING_SMART */
    #ifdef ARCH_MM_MMU
        if (rt_kmem_v2p(fp) != ARCH_MAP_FAILED)
    #else
        if (_bt_thread_stack_contains(thread, fp))
    #endif
        {
            rc = _bt_kaddr(fp, frame);
        }
        else
        {
            rc = -RT_EINVAL;
        }
    }
    else
    {
        rc = -RT_EFAULT;
    }
    return rc;
}

rt_err_t rt_hw_backtrace_frame_get(rt_thread_t thread, struct rt_hw_backtrace_frame *frame)
{
    rt_err_t rc;

    if (!thread || !frame)
    {
        rc = -RT_EINVAL;
    }
    else
    {
        rt_hw_switch_frame_t sframe = thread->sp;
        frame->pc = sframe->regs[RT_HW_SWITCH_CONTEXT_RA];
        frame->fp = sframe->regs[RT_HW_SWITCH_CONTEXT_S0];
        rc = RT_EOK;
    }
    return rc;
}
