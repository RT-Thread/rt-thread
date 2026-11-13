/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

#include <stdarg.h>
#include <rthw.h>
#include <rtthread.h>
#include "rh850_cpu.h"

static rt_err_t (*rh850_exception_hook)(void *context);

void rt_hw_exception_install(rt_err_t (*exception_handle)(void *context))
{
    rh850_exception_hook = exception_handle;
}

static void fault_print(const char *fmt, ...)
{
    char buf[96];
    va_list args;

    va_start(args, fmt);
    rt_vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    rt_hw_console_output(buf);
}

/* While a switch from an interrupt is held back, "from" still runs */
static rt_thread_t running_thread(void)
{
    if (rt_thread_switch_interrupt_flag != 0)
    {
        return rt_container_of((rt_ubase_t *)rt_interrupt_from_thread,
                               struct rt_thread, sp);
    }

    return rt_thread_self();
}

static void __attribute__((noreturn)) fault_halt(void *context)
{
    if (rh850_exception_hook != RT_NULL)
    {
        rh850_exception_hook(context);
    }

    for (;;)
    {
        rh850_halt();
    }
}

void rh850_fault(rt_uint32_t fe, rt_uint32_t cause,
                 struct rt_hw_stack_frame *frame)
{
    rt_thread_t thread = running_thread();
    int n;

    fault_print("\n%s exception: cause 0x%08x, thread %s\n", fe ? "FE" : "EI",
                cause, thread ? thread->parent.name : "-");
    fault_print("pc  0x%08x psw   0x%08x sp 0x%08x\n", frame->eipc,
                frame->eipsw, (rt_ubase_t)(frame + 1));
    fault_print("fpsr 0x%08x fpepc 0x%08x\n", frame->fpsr, frame->fpepc);
    fault_print("r1  0x%08x r2  0x%08x\n", frame->r1, frame->r2);
    for (n = 4; n <= 31; n += 4)
    {
        fault_print("r%-2d 0x%08x r%-2d 0x%08x r%-2d 0x%08x r%-2d 0x%08x\n",
                    n, frame->FRAME_GPR(n), n + 1, frame->FRAME_GPR(n + 1),
                    n + 2, frame->FRAME_GPR(n + 2), n + 3,
                    frame->FRAME_GPR(n + 3));
    }

    fault_halt(frame);
}

void rh850_fpi_pending(rt_ubase_t from)
{
    rt_thread_t thread =
        rt_container_of((rt_ubase_t *)from, struct rt_thread, sp);

    fault_print("\nFPI pending at a thread switch: thread %s, fpepc 0x%08x\n",
                thread->parent.name, RH850_STSR(RH850_SR_FPEPC));

    fault_halt(RT_NULL);
}
