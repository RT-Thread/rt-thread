/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#ifdef RT_USING_SMART
#include <lwp_arch.h>

#define TRANCE_LEVEL 20

extern rt_ubase_t __text_start[];
extern rt_ubase_t __text_end[];

static char *_get_elf_name(size_t sepc);

void rt_hw_backtrace(rt_uint32_t *ffp, rt_ubase_t sepc)
{
    rt_ubase_t *ra;
    rt_ubase_t *fp;
    rt_ubase_t vas, vae;
    int i, j;

    rt_kprintf("riscv64-unknown-linux-musl-addr2line -e %s -a -f", _get_elf_name(sepc));

    fp = (rt_ubase_t *)ffp;

    if (!fp)
    {
        asm volatile("mv %0, s0"
                     : "=r"(fp));
    }

    if (sepc)
    {
        rt_kprintf(" %p", sepc - 0x4);
    }

    if (fp > (rt_ubase_t *)USER_VADDR_START && fp < (rt_ubase_t *)USER_VADDR_TOP)
    {
        vas = USER_VADDR_START;
        vae = USER_VADDR_TOP;
    }
    else
    {
        vas = (rt_ubase_t)&__text_start;
        vae = (rt_ubase_t)&__text_end;
    }

    for (i = j = 0; i < TRANCE_LEVEL; i++)
    {
        if (RT_ALIGN((rt_ubase_t)fp, sizeof(void *)) != (rt_ubase_t)fp)
        {
            break;
        }

        ra = fp - 1;
        if (!rt_kmem_v2p(ra) || *ra < vas || *ra > vae)
            break;

        rt_kprintf(" %p", *ra - 0x04);

        fp = fp - 2;
        if (!rt_kmem_v2p(fp))
            break;
        fp = (rt_ubase_t *)(*fp);
        if (!fp)
            break;
    }

    rt_kputs("\r\n");
}

static void _assert_backtrace_cb(const char *ex, const char *func, rt_size_t line)
{
    rt_hw_interrupt_disable();
    rt_kprintf("(%s) assertion failed at function:%s, line number:%d \n", ex, func, line);

    rt_hw_backtrace(0, 0);
    rt_hw_cpu_shutdown();
}

static int rt_hw_backtrace_init(void)
{
    rt_assert_set_hook(_assert_backtrace_cb);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_backtrace_init);

static void backtrace_test(int args, char *argv[])
{
    int *p = (void *)-1;
    init_fn_t ft = 0;

    if (args < 2)
    {
        rt_kprintf("backtrace_test usage:backtrace_test a(assert)/m(invalid memory)/i(illegal instruction)\r\n");
        return;
    }

    if (!rt_strcmp(argv[1], "a"))
    {
        rt_kprintf("Assert test:\r\n", argv[1]);
        RT_ASSERT(0);
    }
    else if (!rt_strcmp(argv[1], "m"))
    {
        rt_kprintf("Access invalid memory:\r\n", argv[1]);
        *p = 0;
    }
    else if (!rt_strcmp(argv[1], "i"))
    {
        rt_kprintf("Illegal instruction:\r\n", argv[1]);
        ft();
    }
    else
    {
        rt_kprintf("Unknown cmd :%s.\r\n", argv[1]);
    }
}
MSH_CMD_EXPORT(backtrace_test, backtrace test case);

extern struct rt_thread *rt_current_thread;

#define IN_USERSPACE (sepc > USER_VADDR_START && sepc < USER_VADDR_TOP)

static char *_get_elf_name(size_t sepc)
{
    return IN_USERSPACE ? rt_current_thread->parent.name : "rtthread.elf";
}

#endif /* RT_USING_SMART */
