/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-01     Bernard      The first version
 * 2025-04-20     GuEe-GUI     Port for not DM
 */

#include <rthw.h>
#include <rtthread.h>

#include <cpu.h>
#include <mmu.h>
#include <board.h>
#include <interrupt.h>

#define INTC_TYPE_RISCV     0
#define INTC_TYPE_ANDESTECH 1
#define INTC_TYPE_CLIC      2

#ifndef INTC_TYPE
#define INTC_TYPE           INTC_TYPE_RISCV
#endif

#define PIC_DISABLE_DM

#if INTC_TYPE != INTC_TYPE_CLIC
/* --------------------------- PLIC and Local INTC -------------------------- */

#ifndef PLIC_QUICKS
#define PLIC_QUICKS         0
#endif

#include "pic/pic-sifive-plic.c"
#undef DBG_TAG
#undef DBG_LVL
#include "pic/pic-riscv-intc.c"
#undef DBG_TAG
#undef DBG_LVL

#ifdef RT_USING_SMP
rt_uint32_t ipi_intc_base;
#endif
rt_uint32_t irq_plic_base;

static struct plic *system_plic;

#else /* INTC_TYPE == INTC_TYPE_CLIC */
/* ---------------------------------- CLIC ---------------------------------- */

#ifndef CLIC_QUICKS
#define CLIC_QUICKS         0
#endif

/*
 * CLIC can be used alongside INTC and PLIC in a SoC.
 * However, we typically assume that NOT DM systems are MCUs,
 * and they only use CLIC for interrupt handling.
 */
#include "pic/pic-riscv-clic.c"
#undef DBG_TAG
#undef DBG_LVL

#ifdef RT_USING_SMP
rt_uint32_t ipi_clic_base;
#endif
static struct riscv_clic *system_clic;

#endif /* INTC_TYPE != INTC_TYPE_CLIC */

#define DBG_TAG "hw.irq"
#define DBG_LVL DBG_INFO

static struct rt_irq_desc irq_desc[MAX_HANDLERS];

rt_weak void rt_hw_interrupt_init(void)
{
    union
    {
        struct { rt_ubase_t base, size };
        rt_ubase_t range[2];
    } mmio;

#ifdef RT_USING_SMP
    if (rt_hw_cpu_id() != riscv_hartid_to_cpu_id(boot_cpu_hartid))
    {
        goto _percpu_init;
    }
#endif /* RT_USING_SMP */

#if INTC_TYPE != INTC_TYPE_CLIC
/* --------------------------- PLIC and Local INTC -------------------------- */

    riscv_intc_common_init(&system_rv_intc, INTC_TYPE == INTC_TYPE_ANDESTECH);

    irq_plic_base = rv_intc->irqs_def_count + rv_intc->irqs_count;
#ifdef RT_USING_SMP
    ipi_intc_base = irq_plic_base - RT_MAX_IPI;
#endif

#ifdef ARCH_RISCV_M_MODE
    mmio.range[0] = platform_get_clint_base();
    mmio.range[1] = platform_get_clint_size();
    riscv_clint_common_init(mmio.range, 1);
#endif

    RT_ASSERT(irq_plic_base < MAX_HANDLERS);

    mmio.base = platform_get_plic_base();
    mmio.size = platform_get_plic_size();

    system_plic = plic_common_init(mmio.base, mmio.size, MAX_HANDLERS - irq_plic_base, PLIC_QUICKS);

    RT_ASSERT(system_plic != RT_NULL);

#else /* INTC_TYPE == INTC_TYPE_CLIC */
/* ---------------------------------- CLIC ---------------------------------- */

    if (rt_hw_cpu_id() != riscv_hartid_to_cpu_id(boot_cpu_hartid))
    {
        return;
    }

#ifdef ARCH_RISCV_M_MODE
    mmio.range[0] = platform_get_clint_base();
    mmio.range[1] = platform_get_clint_size();
    riscv_clint_common_init(mmio.range, 1);
#endif

    mmio.base = platform_get_clic_base();
    mmio.size = platform_get_clic_size();

    system_clic = clic_common_init(mmio.base, mmio.size, CLIC_QUICKS);

    RT_ASSERT(system_clic != RT_NULL);

#ifdef RT_USING_SMP
    ipi_intc_base = system_clic->ipi_base;
#endif

#endif /* INTC_TYPE != INTC_TYPE_CLIC */

#ifdef RT_USING_SMP
_percpu_init:
#endif
#if INTC_TYPE != INTC_TYPE_CLIC

    plic_percpu_common_init(system_plic);

    rt_hw_interrupt_umask(IRQ_INTC(IRQ_S_EXT));

#else /* INTC_TYPE == INTC_TYPE_CLIC */

    riscv_clic_percpu_common_init(system_clic);

#endif /* INTC_TYPE != INTC_TYPE_CLIC */
}

rt_weak void rt_hw_interrupt_mask(int vector)
{
#if INTC_TYPE != INTC_TYPE_CLIC
/* --------------------------- PLIC and Local INTC -------------------------- */

    if (vector >= irq_plic_base)
    {
        vector -= irq_plic_base;

        LOG_D("PLIC IRQ %d %s on CPU#%d", vector, "enabled", rt_hw_cpu_id());
        plic_irq_mask_raw(rt_hw_cpu_id(), vector);
    }
    else
    {
    #if INTC_TYPE == INTC_TYPE_RISCV
        riscv_intc_irq_mask_raw(&system_rv_intc, vector);
    #else
        andes_intc_irq_mask_raw(&system_rv_intc, vector);
    #endif
    }

#else /* INTC_TYPE == INTC_TYPE_CLIC */
/* ---------------------------------- CLIC ---------------------------------- */

    riscv_clic_irq_mask_raw(system_clic, vector);

#endif /* INTC_TYPE != INTC_TYPE_CLIC */
}

rt_weak void rt_hw_interrupt_umask(int vector)
{
#if INTC_TYPE != INTC_TYPE_CLIC
/* --------------------------- PLIC and Local INTC -------------------------- */

    if (vector >= irq_plic_base)
    {
        vector -= irq_plic_base;

        LOG_D("PLIC IRQ %d %s on CPU#%d", vector, "disabled", rt_hw_cpu_id());
        plic_irq_unmask_raw(rt_hw_cpu_id(), vector);
    }
    else
    {
    #if INTC_TYPE == INTC_TYPE_RISCV
        riscv_intc_irq_unmask_raw(&system_rv_intc, vector);
    #else
        andes_intc_irq_unmask_raw(&system_rv_intc, vector);
    #endif
    }

#else /* INTC_TYPE == INTC_TYPE_CLIC */
/* ---------------------------------- CLIC ---------------------------------- */

    riscv_clic_irq_unmask_raw(system_clic, vector);

#endif /* INTC_TYPE != INTC_TYPE_CLIC */
}

rt_weak rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if (vector < MAX_HANDLERS)
    {
        old_handler = irq_desc[vector].handler;

        if (handler != RT_NULL)
        {
            irq_desc[vector].handler = (rt_isr_handler_t)handler;
            irq_desc[vector].param = param;
        #ifdef RT_USING_INTERRUPT_INFO
            rt_snprintf(irq_desc[vector].name, RT_NAME_MAX - 1, "%s", name);
            irq_desc[vector].counter = 0;
        #endif
        }
    }

    return old_handler;
}

#ifdef RT_USING_SMP
rt_weak void rt_hw_ipi_handler_install(int ipi_hwirq, rt_isr_handler_t ipi_isr_handler)
{
    rt_hw_interrupt_install(ipi_hwirq, ipi_isr_handler, RT_NULL, "IPI_HANDLER");
}

rt_weak void rt_hw_ipi_send(int ipi_vector, unsigned int cpu_mask)
{
    RT_BITMAP_DECLARE(cpu_masks, RT_CPUS_NR) = { cpu_mask };

#if INTC_TYPE != INTC_TYPE_CLIC
    riscv_intc_irq_send_ipi_raw(&system_rv_intc, ipi_intc_base + ipi_vector, cpu_masks);
#else
    riscv_clic_irq_send_ipi_raw(system_clic, ipi_clic_base + ipi_vector, cpu_masks);
#endif
}
#endif /* RT_USING_SMP */

static rt_bool_t handler_irq(int hwirq, void *data)
{
    struct rt_irq_desc *irq_desc = &irq_desc[hwirq + (rt_ubase_t)data];

    if (irq_desc->handler)
    {
        irq_desc->handler(hwirq, irq_desc->param);

        return RT_TRUE;
    }

    return RT_FALSE;
}

static rt_bool_t handler_plic_irq(int hwirq, void *data)
{
    plic_irq_ack_or_eoi(rt_hw_cpu_id(), hwirq);

    return handler_irq(hwirq, data)
}

rt_weak void rt_hw_interrupt_handle(rt_uint32_t vector, void *param)
{
    /* vector is equal to scause from trap */

#if INTC_TYPE != INTC_TYPE_CLIC
/* --------------------------- PLIC and Local INTC -------------------------- */

    if (vector == IRQ_S_EXT)
    {
        plic_handler_isr_raw(system_plic, handler_plic_irq, irq_plic_base);
    }
    else
    {
    #if INTC_TYPE == INTC_TYPE_RISCV
        riscv_intc_handler_raw(&system_rv_intc, vector, handler_irq, RT_NULL);
    #else
        riscv_intc_aia_handler_raw(&system_rv_intc, handler_irq, RT_NULL);
    #endif
    }

#else /* INTC_TYPE == INTC_TYPE_CLIC */
/* ---------------------------------- CLIC ---------------------------------- */

    riscv_clic_handler_isr_raw(system_clic, vector, handler_irq, RT_NULL);

#endif /* INTC_TYPE != INTC_TYPE_CLIC */
}
