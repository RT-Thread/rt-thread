/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-02     Jesven       the first version
 * 2023-06-24     WangXiaoyao  Support backtrace for non-active thread
 */

#include "mm_aspace.h"
#include "mmu.h"

#include <rtthread.h>
#include <backtrace.h>
#include <stdlib.h>

#define BT_NESTING_MAX 100

static int unwind_frame(struct bt_frame *frame)
{
    unsigned long fp = frame->fp;

    if ((fp & 0x7)
#ifdef RT_USING_LWP
        || (rt_kmem_v2p((void *)fp) == ARCH_MAP_FAILED)
#endif
            )
    {
        return 1;
    }
    frame->fp = *(unsigned long *)fp;
    frame->pc = *(unsigned long *)(fp + 8);

    if ((rt_kmem_v2p((void *)frame->pc) == ARCH_MAP_FAILED))
        return 1;
    return 0;
}

static void walk_unwind(unsigned long pc, unsigned long fp)
{
    struct bt_frame frame = {fp, 1};
    unsigned long lr = pc;
    int nesting = 0;

    while (nesting < BT_NESTING_MAX)
    {
        rt_kprintf(" %p", (void *)lr);
        if (unwind_frame(&frame))
        {
            break;
        }
        lr = frame.pc;
        nesting++;
    }
}

void backtrace(unsigned long pc, unsigned long lr, unsigned long fp)
{
    rt_kprintf("please use: addr2line -e rtthread.elf -a -f");
    if (pc)
        rt_kprintf(" %p", (void *)pc);

    if (lr && fp)
        walk_unwind(lr, fp);
    rt_kprintf("\n");
}

int rt_backtrace(void)
{
    unsigned long ra = (unsigned long)__builtin_return_address(0U);
    unsigned long fr = (unsigned long)__builtin_frame_address(0U);

    backtrace(0, ra, fr);
    return 0;
}
MSH_CMD_EXPORT_ALIAS(rt_backtrace, bt_test, backtrace test);

#define ARCH_CONTEXT_FETCH(pctx, id) (*(((unsigned long *)pctx) + (id)))

int rt_backtrace_thread(rt_thread_t thread)
{
    unsigned long lr;
    unsigned long fp;

    if (thread == rt_thread_self())
    {
        return -RT_EINVAL;
    }
    else
    {
        lr = ARCH_CONTEXT_FETCH(thread->sp, 3);
        fp = ARCH_CONTEXT_FETCH(thread->sp, 7);
        backtrace(0, lr, fp);
        return 0;
    }
}

#ifdef RT_USING_SMART

int rt_backtrace_user_thread(rt_thread_t thread)
{
    unsigned long pc;
    unsigned long lr;
    unsigned long fp;
    unsigned long ctx = (unsigned long)thread->user_ctx.ctx;

    if (ctx > (unsigned long)thread->stack_addr
        && ctx < (unsigned long)thread->stack_addr + thread->stack_size)
    {
        pc = ARCH_CONTEXT_FETCH(thread->user_ctx.ctx, 0);
        lr = ARCH_CONTEXT_FETCH(thread->user_ctx.ctx, 3);
        fp = ARCH_CONTEXT_FETCH(thread->user_ctx.ctx, 7);
        backtrace(pc, lr, fp);
        return 0;
    }
    else
        return -1;
}

#endif /* RT_USING_SMART */

static long custom_hex_to_long(const char* hex)
{
    long result = 0;
    int i = 0;

    // Skip the "0x" prefix
    if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
    {
        i = 2;
    }

    // Convert each hex digit to its decimal value
    for (; hex[i] != '\0'; i++)
    {
        char digit = hex[i];
        if (digit >= '0' && digit <= '9')
        {
            result = result * 16 + (digit - '0');
        }
        else if (digit >= 'a' && digit <= 'f')
        {
            result = result * 16 + (digit - 'a' + 10);
        }
        else if (digit >= 'A' && digit <= 'F')
        {
            result = result * 16 + (digit - 'A' + 10);
        }
        else
        {
            // Invalid hex digit
            return 0;
        }
    }

    return result;
}

static void cmd_backtrace(int argc, char** argv)
{
    long pid;

    if (argc < 2)
    {
        rt_kprintf("please use: backtrace pid\n");
        return;
    }

    if (strncmp(argv[1], "0x", 2) == 0)
    {
        pid = custom_hex_to_long(argv[1]);
    }
    else
    {
        pid = atol(argv[1]);
    }
    if (pid)
    {
        rt_kprintf("backtrace %s(0x%lx), from %s\n", ((rt_thread_t)pid)->parent.name, pid, argv[1]);
        rt_backtrace_thread((rt_thread_t)pid);
    }
}
MSH_CMD_EXPORT_ALIAS(cmd_backtrace, backtrace, print backtrace of a thread);
