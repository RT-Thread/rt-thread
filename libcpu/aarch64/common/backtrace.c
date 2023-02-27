/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-02     Jesven       the first version
 */

#include <rtthread.h>
#include <backtrace.h>

#define BT_NESTING_MAX 100

static int unwind_frame(struct bt_frame *frame)
{
    unsigned long fp = frame->fp;

    if ((fp & 0x7)
#ifdef RT_USING_LWP
         || fp < KERNEL_VADDR_START
#endif
            )
    {
        return 1;
    }
    frame->fp = *(unsigned long *)fp;
    frame->pc = *(unsigned long *)(fp + 8);
    return 0;
}

static void walk_unwind(unsigned long pc, unsigned long fp)
{
    struct bt_frame frame;
    unsigned long lr = pc;
    int nesting = 0;

    frame.fp = fp;
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
    rt_kprintf("please use: addr2line -e rtthread.elf -a -f %p", (void *)pc);
    walk_unwind(lr, fp);
    rt_kprintf("\n");
}

int rt_backtrace(void)
{
    unsigned long pc = (unsigned long)backtrace;
    unsigned long ra = (unsigned long)__builtin_return_address(0U);
    unsigned long fr = (unsigned long)__builtin_frame_address(0U);

    backtrace(pc, ra, fr);
    return 0;
}
MSH_CMD_EXPORT_ALIAS(rt_backtrace, bt_test, backtrace test);
