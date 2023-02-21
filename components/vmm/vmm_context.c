/*
 * COPYRIGHT (C) 2011-2021, Real-Thread Information Technology Ltd
 * All rights reserved
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-11-04     Grissiom     add comment
 */

#include <rthw.h>
#include <rtthread.h>
#include <interrupt.h>

#include <log_trace.h>
#include <vmm.h>

#include "vmm_context.h"

struct rt_vmm_share_layout rt_vmm_share rt_section(".vmm.share");

volatile struct vmm_context *_vmm_context = RT_NULL;

void vmm_context_init(void *context_addr)
{
    _vmm_context = (struct vmm_context *)context_addr;
    rt_memset((void *)_vmm_context, 0x00, sizeof(struct vmm_context));
    /* When loading RT-Thread, the IRQ on the guest should be disabled. */
    _vmm_context->virq_status = 1;
}

#ifdef RT_VMM_USING_DOMAIN
unsigned long guest_domain_val rt_section(".bss.share");
unsigned long vmm_domain_val rt_section(".bss.share");
/* some RT-Thread code need to be called in the guest
 * context(rt_thread_idle_excute for example). To simplify the code, we need a
 * "super" domain mode to have access of both side. The code executed in super
 * domain mode is restricted and should be harmless. */
unsigned long super_domain_val rt_section(".bss.share");
void vmm_context_init_domain(struct vmm_domain *domain)
{
    asm volatile ("mrc p15, 0, %0, c3, c0\n" : "=r" (guest_domain_val));

    rt_kprintf("Linux domain: kernel: %d, user: %d, io: %d\n"
               "VMM domain: vmm: %d, share: %d\n",
               domain->kernel, domain->user, domain->io,
               domain->vmm, domain->vmm_share);

    if (domain->kernel == domain->vmm ||
        domain->io     == domain->vmm)
    {
        rt_kprintf("VMM and the guest share the same domain\n");
        super_domain_val = vmm_domain_val = guest_domain_val;
        return;
    }

    vmm_domain_val = guest_domain_val;

    /* become client to our own territory */
    vmm_domain_val |= (1 << (domain->vmm * 2)) | (1 << (domain->vmm_share * 2));

    super_domain_val = vmm_domain_val;
    /* super domain has access to both side */
    super_domain_val |= (1 << (domain->kernel * 2)) | (1 << (domain->user * 2));

    rt_kprintf("Original DAC: 0x%08x\n", guest_domain_val);
}

unsigned long vmm_context_enter_domain(unsigned long domain_val)
{
    unsigned long old_domain;

    asm volatile ("mrc p15, 0, %0, c3, c0\n" : "=r" (old_domain));
    asm volatile ("mcr p15, 0, %0, c3, c0\n" : :"r" (domain_val) : "memory");

    return old_domain;
}

void vmm_context_restore_domain(unsigned long domain_val)
{
    asm volatile ("mcr p15, 0, %0, c3, c0\n" : :"r" (domain_val) : "memory");
}
#endif

void vmm_virq_pending(int irq)
{
    /* when running this piece of code, the guest is already suspended. So it's
     * safe to set the bits without locks. */
    _vmm_context->virq_pending[irq / 32] |= (1 << (irq % 32));
    _vmm_context->virq_pended = 1;
    /* mask this IRQ in host */
    rt_hw_interrupt_mask(irq);
}

void vmm_virq_update(void)
{
    if ((!_vmm_context->virq_status) &&
        ( _vmm_context->virq_pended))
    {
        rt_hw_interrupt_trigger(RT_VMM_VIRQ_TRIGGER);
    }
}

/** check the guest IRQ status
 *
 * @return 0 on guest should handle IRQ, -1 on should restore the guest context
 * normally.
 */
int vmm_virq_check(void)
{
    if ((!_vmm_context->virq_status) &&
        ( _vmm_context->virq_pended))
    {
        return 0;
    }

    return -1;
}

/* 10 = len("%08x, ") */
static char _vmbuf[10*ARRAY_SIZE(_vmm_context->virq_pending)];
void vmm_dump_virq(void)
{
    int i, s;

    vmm_info("---- virtual IRQ ----\n");
    vmm_info("  status: %08x,   pended: %08x, pending:\n",
               _vmm_context->virq_status, _vmm_context->virq_pended);
    for (s = 0, i = 0; i < ARRAY_SIZE(_vmm_context->virq_pending); i++)
    {
        s += rt_snprintf(_vmbuf+s, sizeof(_vmbuf)-s,
                         "%08x, ", _vmm_context->virq_pending[i]);
    }
    vmm_info("%.*s\n", sizeof(_vmbuf), _vmbuf);
    vmm_info("---- virtual IRQ ----\n");
}

int vmm_virq_coherence_ok(void)
{
    int i, res;
    int should_pend = 0;

    for (i = 0; i < ARRAY_SIZE(_vmm_context->virq_pending); i++)
    {
        should_pend |= _vmm_context->virq_pending[i];
    }

    res = (_vmm_context->virq_pended == !!should_pend);

    if (!res)
    {
        vmm_info("--- %x %x, %x\n",
                 _vmm_context->virq_pended, should_pend, !!should_pend);
    }

    return res;
}

extern struct rt_thread vmm_thread;

void vmm_show_guest_reg(void)
{
    struct rt_hw_stack *sp = vmm_thread.sp;
#ifdef RT_VMM_USING_DOMAIN
    unsigned long old_domain;

    old_domain = vmm_context_enter_domain(super_domain_val);
#endif

    vmm_info("CPSR: %08x, PC: %08x, LR: %08x, SP: %08x\n",
             sp->cpsr, sp->pc, sp->lr, sp+1);

#ifdef RT_VMM_USING_DOMAIN
    vmm_context_restore_domain(old_domain);
#endif
}

void vmm_dump_domain(void)
{
    unsigned long dac;

    asm volatile ("mrc p15, 0, %0, c3, c0\n" : "=r" (dac));
    vmm_info("current DAC: %08x\n", dac);
#ifdef RT_VMM_USING_DOMAIN
    vmm_info("guest DAC: %08x, RTT DAC: %08x, super DAC: %08x\n",
             guest_domain_val, vmm_domain_val, super_domain_val);
#endif
}

void vmm_show_guest(void)
{
    vmm_show_guest_reg();
    vmm_dump_virq();
    vmm_dump_domain();
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT_ALIAS(vmm_show_guest, vmm, show vmm status);
#endif

static int _bad_cpsr(unsigned long cpsr)
{
    int bad = 1;

    switch (cpsr & MODEMASK)
    {
    case USERMODE:
    case FIQMODE:
    case IRQMODE:
    case SVCMODE:
#ifdef CPU_HAS_MONITOR_MODE
    case MONITORMODE:
#endif
    case ABORTMODE:
#ifdef CPU_HAS_HYP_MODE
    case HYPMODE:
#endif
    case UNDEFMODE:
    case MODEMASK:
        bad = 0;
        break;
    };
    return bad;
}

void vmm_verify_guest_status(struct rt_hw_stack *sp)
{
    int dump_vmm = 0;
    unsigned long cpsr;
#ifdef RT_VMM_USING_DOMAIN
    unsigned long old_domain;

    old_domain = vmm_context_enter_domain(super_domain_val);
#endif

    cpsr = sp->cpsr;
    if (_bad_cpsr(cpsr))
    {
            vmm_info("=================================\n");
            vmm_info("VMM WARING: bad CPSR in guest\n");
            dump_vmm = 1;
    }
    else
    {
        if (cpsr & A_Bit && 0)
        {
            vmm_info("=================================\n");
            vmm_info("VMM WARING: A bit is set in guest\n");
            dump_vmm = 1;
        }
        if ((cpsr & I_Bit) && (sp->pc <= VMM_BEGIN))
        {
            vmm_info("=================================\n");
            vmm_info("VMM WARING: IRQ disabled in guest\n");
            dump_vmm = 1;
        }
        if (cpsr & F_Bit)
        {
            vmm_info("=================================\n");
            vmm_info("VMM WARING: FIQ disabled in guest\n");
            dump_vmm = 1;
        }
        if ((cpsr & MODEMASK) == USERMODE)
        {
            if (_vmm_context->virq_status & 1)
            {
                vmm_info("=================================\n");
                vmm_info("VMM WARING: VIRQ disabled in user mode\n");
                dump_vmm = 1;
            }
            if ((sp->pc > 0xbf000000) && (sp->pc < 0xffff0000))
            {
                vmm_info("=================================\n");
                vmm_info("VMM WARING: executing kernel code in usr mode\n");
                dump_vmm = 1;
            }
            /* FIXME: when the guest is suspended in user mode and its
             * interrupts come, this can be misleading. */
#if 0
            if (_vmm_context->virq_pended)
            {
                vmm_info("=================================\n");
                vmm_info("VMM WARING: VIRQ pended in user mode\n");
                dump_vmm = 1;
            }
#endif
        }
        else if ((cpsr & MODEMASK) == SVCMODE && sp->pc < 0xbf000000)
        {
            vmm_info("=================================\n");
            vmm_info("VMM WARING: executing usr code in svc mode\n");
            dump_vmm = 1;
        }
    }

#if 0
    if (!vmm_virq_coherence_ok())
    {
        vmm_info("=================================\n");
        vmm_info("VMM WARING: bad VIRQ status\n");
        dump_vmm = 1;
    }
#endif

    if (dump_vmm)
    {
        vmm_show_guest();
        vmm_info("=================================\n");
    }

#ifdef RT_VMM_USING_DOMAIN
    vmm_context_restore_domain(old_domain);
#endif
}

