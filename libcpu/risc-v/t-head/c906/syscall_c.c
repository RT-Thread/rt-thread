/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-03     lizhirui     first version
 * 2022-11-10     WangXiaoyao  Add readable syscall tracing
 */

#include <rthw.h>
#include <rtthread.h>

#ifdef RT_USING_SMART

#define DBG_TAG "syscall"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#include <stdint.h>
#include <mmu.h>
#include <page.h>
#include <lwp_user_mm.h>

#include "riscv_mmu.h"
#include "stack.h"

typedef rt_size_t (*syscallfunc_t)(rt_size_t, rt_size_t, rt_size_t, rt_size_t, rt_size_t, rt_size_t, rt_size_t);

void syscall_handler(struct rt_hw_stack_frame *regs)
{
    const char *syscall_name;
    int syscallid = regs->a7;

    if (syscallid == 0)
    {
        LOG_E("syscall id = 0!\n");
        while (1)
            ;
    }

    syscallfunc_t syscallfunc = (syscallfunc_t)lwp_get_sys_api(syscallid);

    if (syscallfunc == RT_NULL)
    {
        LOG_E("unsupported syscall!\n");
        sys_exit_group(-1);
    }

#if DBG_LVL >= DBG_INFO
    syscall_name = lwp_get_syscall_name(syscallid);
#endif

    LOG_I("[0x%lx] %s(0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%lx)", rt_thread_self(), syscall_name,
        regs->a0, regs->a1, regs->a2, regs->a3, regs->a4, regs->a5, regs->a6);
    regs->a0 = syscallfunc(regs->a0, regs->a1, regs->a2, regs->a3, regs->a4, regs->a5, regs->a6);
    regs->a7 = 0;
    regs->epc += 4; // skip ecall instruction
    LOG_I("[0x%lx] %s ret: 0x%lx", rt_thread_self(), syscall_name, regs->a0);
}
#endif /* RT_USING_SMART */
