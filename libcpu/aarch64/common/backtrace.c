/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-02     Jesven       the first version
 * 2023-06-24     WangXiaoyao  Support backtrace for non-active thread
 * 2023-10-16     Shell        Support a new backtrace framework
 */


#include <rtthread.h>
#include <rthw.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mm_aspace.h"
#include "mmu.h"

#define INST_WORD_BYTES                 4
#define WORD                            sizeof(rt_base_t)
#define ARCH_CONTEXT_FETCH(pctx, id)    (*(((unsigned long *)pctx) + (id)))
#define PTR_NORMALIZE(ptr)              (ptr = rt_backtrace_ptr_normalize(ptr))

rt_weak void *rt_backtrace_ptr_normalize(void *ptr)
{
    return ptr;
}

rt_inline rt_err_t _bt_kaddr(rt_ubase_t *fp, struct rt_hw_backtrace_frame *frame)
{
    rt_err_t rc;

    PTR_NORMALIZE(fp);

    frame->fp = *fp;
    frame->pc = *(fp + 1) - INST_WORD_BYTES;

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

#ifdef RT_USING_SMART
#include <lwp_user_mm.h>
rt_inline rt_err_t _bt_uaddr(rt_lwp_t lwp, rt_ubase_t *fp, struct rt_hw_backtrace_frame *frame)
{
    rt_err_t rc;
    if (lwp_data_get(lwp, &frame->fp, fp, WORD) != WORD)
    {
        rc = -RT_EFAULT;
    }
    else if (lwp_data_get(lwp, &frame->pc, fp + 1, WORD) != WORD)
    {
        rc = -RT_EFAULT;
    }
    else if ((rt_base_t)fp == frame->fp)
    {
        rc = -RT_ERROR;
    }
    else
    {
        frame->pc -= INST_WORD_BYTES;
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
        if (thread && thread->lwp && rt_scheduler_is_available())
        {
            rt_lwp_t lwp = thread->lwp;
            void *this_lwp = lwp_self();
            if (this_lwp == lwp && rt_kmem_v2p(fp) != ARCH_MAP_FAILED)
            {
                rc = _bt_kaddr(fp, frame);
            }
            else if (lwp_user_accessible_ext(lwp, fp, sizeof(rt_base_t)))
            {
                rc = _bt_uaddr(lwp, fp, frame);
            }
            else
            {
                rc = -RT_EFAULT;
            }
        }
        else
#endif
        if (rt_kmem_v2p(fp) != ARCH_MAP_FAILED)
        {
            rc = _bt_kaddr(fp, frame);
        }
        else
        {
            rc = -RT_EFAULT;
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
        frame->pc = ARCH_CONTEXT_FETCH(thread->sp, 3);
        frame->fp = ARCH_CONTEXT_FETCH(thread->sp, 7);
        rc = RT_EOK;
    }
    return rc;
}
