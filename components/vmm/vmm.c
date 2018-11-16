/*
 *  VMM startup file.
 *
 * COPYRIGHT (C) 2013-2014, Real-Thread Information Technology Ltd
 * All rights reserved
 * 
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-06-15     Bernard      the first verion
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

#include "vmm.h"
#include "vmm_context.h"

extern void rt_hw_interrupt_init(void);
extern void rt_application_init(void);

void vmm_entry(struct vmm_entry_param* param) SECTION(".vmm_init");

#ifdef RT_USING_LOGTRACE
#include <log_trace.h>
static struct log_trace_session _lgs = {
    .id  = {.name = "vmm"},
    .lvl = LOG_TRACE_LEVEL_VERBOSE,
};
#endif

struct rt_thread vmm_thread SECTION(".bss.share.vmm");
extern rt_uint8_t vmm_stack_start;
extern rt_uint8_t vmm_stack_end;

void vmm_thread_init(struct rt_thread *thread, const char *name)
{
    extern struct rt_thread *rt_current_thread;

    rt_thread_init(thread, name, RT_NULL, RT_NULL,
                   &vmm_stack_start, &vmm_stack_end - &vmm_stack_start,
                   RT_THREAD_PRIORITY_MAX - 1, 10);

    /* set thread to ready status but not switch to */
    rt_thread_startup(thread);

    /* set current thread as vmm thread */
    rt_current_thread = thread;
}

#ifdef VMM_VERIFY_GUEST
static void _verify_guest(void *p)
{
    while (1)
    {
        rt_thread_delay(RT_TICK_PER_SECOND/4);
        vmm_verify_guest_status(vmm_thread.sp);
    }
}

static void vmm_create_monitor(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("vmon",
                           _verify_guest, RT_NULL,
                           1024, 8, 20);
    if (tid)
        rt_thread_startup(tid);
}
#endif

#ifdef RT_VMM_USING_DOMAIN
extern unsigned long guest_domain_val;
extern unsigned long vmm_domain_val;
#endif

static void vmm_entry_glue(rt_uint32_t level,
                           unsigned int vmm_domain,
                           unsigned int kernel_domain)
    /* inline would make the section setting meaningless */
    __attribute__((noinline))
    SECTION(".vmm_glue");
static void vmm_entry_glue(rt_uint32_t level,
                           unsigned int vmm_domain,
                           unsigned int kernel_domain)
{
    rt_schedule();

#ifdef RT_VMM_USING_DOMAIN
    /* protect us from the guest code, but leave the shared region permission
     */
    guest_domain_val &= ~(0x3 << (vmm_domain * 2));

    /* don't touch the guest kernel space */
    vmm_domain_val &= ~(0x3 << (kernel_domain * 2));
#endif

    rt_hw_interrupt_enable(level);
}

void vmm_entry(struct vmm_entry_param *param)
{
    rt_uint32_t level;

    level = rt_hw_interrupt_disable();

    /* set iomap */
    vmm_iomap_init(param->iomap);

    /* set VMM context address */
    vmm_context_init(&RT_VMM_SHARE->ctx);

    /* init hardware interrupt */
    rt_hw_interrupt_init();

    vmm_vector_init();

    /* init board */
    rt_hw_board_init();

#ifdef RT_USING_LOGTRACE
    /* Some parts of VMM use log_trace, so we need to init it right after
     * board_init. */
    log_trace_init();
    log_trace_set_device(RT_CONSOLE_DEVICE_NAME);

    log_trace_register_session(&_lgs);
#endif

    /* show version */
    rt_show_version();
    rt_kprintf("share ctx: %p(%x)\n",
               &RT_VMM_SHARE->ctx, sizeof(RT_VMM_SHARE->ctx));

    /* init timer system */
    rt_system_timer_init();

    {
        rt_uint32_t ttbr;
        asm volatile ("mrc p15, 0, %0, c2, c0, 0\n"
                      : "=r"(ttbr));
        rt_kprintf("Linux TTBR: 0x%08x\n", ttbr);
        /*
         *rt_hw_cpu_dump_page_table((void*)((ttbr & (0xffffc000))
         *                                  - 0x80000000 + 0xC0000000));
         */
        /*rt_hw_cpu_dump_page_table((void*)(0xc0004000));*/
    }

#ifdef RT_VMM_USING_DOMAIN
    vmm_context_init_domain(param->domain);
#endif

    rt_kprintf("heap: 0x%p - 0x%p, %dKi bytes\n",
               (void*)HEAP_BEGIN, (void*)HEAP_END,
               ((int)HEAP_END - (int)HEAP_BEGIN) / 1024);
    /* init heap memory system */
    rt_system_heap_init((void*)HEAP_BEGIN, (void*)HEAP_END);

    /* init scheduler system */
    rt_system_scheduler_init();

    rt_kprintf("user application init.\n");
    /* init application */
    rt_application_init();

#ifdef VMM_VERIFY_GUEST
    vmm_create_monitor();
#endif

    rt_system_timer_thread_init();

    vmm_thread_init(&vmm_thread, "vmm");

#ifdef RT_VMM_USING_DOMAIN
    rt_kprintf("domain protect present\n");
#endif
    /* start scheduler */
    rt_kprintf("do the first scheduling...\n");

    vmm_entry_glue(level,
                   param->domain->vmm,
                   param->domain->kernel);
}

