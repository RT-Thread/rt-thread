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
#include <interrupt.h>
#ifdef ARCH_MM_MMU
#include <ioremap.h>
#else
static void *riscv_ioremap_identity(void *addr, rt_size_t size)
{
    RT_UNUSED(size);

    return addr;
}

static void riscv_iounmap_identity(void *addr)
{
    RT_UNUSED(addr);
}

#define rt_ioremap(addr, size)  riscv_ioremap_identity((addr), (size))
#define rt_iounmap(addr)        riscv_iounmap_identity(addr)
#endif

#define PIC_DISABLE_DM

/*
 * The DM and non-DM paths share the controller register logic. PIC_DISABLE_DM
 * keeps the included drivers free of OFW and rt_pic dependencies; this file
 * supplies the classic rt_hw_interrupt_* adapter around their raw helpers.
 */
#ifdef ARCH_RISCV_M_MODE
#include "pic/pic-riscv-clint.c"
#undef DBG_TAG
#undef DBG_LVL
#endif

#ifdef ARCH_RISCV_NON_DM_IRQ_PLIC
/* --------------------------- PLIC and Local INTC -------------------------- */

#ifdef ARCH_RISCV_INTC_ANDES
#define RISCV_INTC_IS_ANDES RT_TRUE
#else
#define RISCV_INTC_IS_ANDES RT_FALSE
#endif

#include "pic/pic-sifive-plic.c"
#undef DBG_TAG
#undef DBG_LVL
#include "pic/pic-riscv-intc.c"
#undef DBG_TAG
#undef DBG_LVL

#ifdef RT_USING_SMP
int ipi_intc_base;
#endif
int irq_plic_base;

static struct plic *system_plic;
size_t plic_base;

rt_weak rt_ubase_t platform_get_plic_base(void)
{
    return 0;
}

rt_weak rt_size_t platform_get_plic_size(void)
{
    return 0;
}

rt_weak rt_ubase_t platform_get_plic_quirks(void)
{
    return 0;
}

#else /* ARCH_RISCV_NON_DM_IRQ_CLIC */
/* ---------------------------------- CLIC ---------------------------------- */

/*
 * CLIC can be used alongside INTC and PLIC in a SoC.
 * However, we typically assume that NOT DM systems are MCUs,
 * and they only use CLIC for interrupt handling.
 */
#include "pic/pic-riscv-clic.c"
#undef DBG_TAG
#undef DBG_LVL

#ifdef RT_USING_SMP
int ipi_clic_base;
#endif
static struct riscv_clic *system_clic;

rt_weak rt_ubase_t platform_get_clic_base(void)
{
    return 0;
}

rt_weak rt_size_t platform_get_clic_size(void)
{
    return 0;
}

rt_weak rt_ubase_t platform_get_clic_quirks(void)
{
    return 0;
}

#endif /* ARCH_RISCV_NON_DM_IRQ_PLIC */

#ifdef ARCH_RISCV_M_MODE
rt_weak rt_ubase_t platform_get_clint_base(void)
{
    return 0;
}

rt_weak rt_size_t platform_get_clint_size(void)
{
    return 0;
}
#endif

#define DBG_TAG "hw.irq"
#define DBG_LVL DBG_INFO

static struct rt_irq_desc irq_desc[ARCH_RISCV_MAX_IRQS];

static rt_bool_t riscv_is_boot_cpu(void)
{
#ifdef RT_USING_SMP
    return rt_hw_cpu_id() == riscv_hartid_to_cpu_id(boot_cpu_hartid);
#else
    return RT_TRUE;
#endif
}

#ifdef ARCH_RISCV_M_MODE
static void riscv_clint_init(void)
{
    rt_ubase_t mmio_range[2] =
    {
        platform_get_clint_base(),
        platform_get_clint_size(),
    };

    if (!mmio_range[0] && !mmio_range[1])
    {
        return;
    }

    if (!mmio_range[0] || !mmio_range[1] ||
        riscv_clint_common_init(mmio_range, 1) != RT_EOK)
    {
        LOG_E("Failed to initialize CLINT at %p", (void *)mmio_range[0]);
    }
}
#endif

#ifdef ARCH_RISCV_NON_DM_IRQ_PLIC
static rt_err_t riscv_irq_controller_init(void)
{
    rt_ubase_t base;
    rt_size_t size;

    riscv_intc_common_init(&system_rv_intc, RISCV_INTC_IS_ANDES);

    irq_plic_base = system_rv_intc.irqs_def_count + system_rv_intc.irqs_count;
#ifdef RT_USING_SMP
    ipi_intc_base = irq_plic_base - RT_MAX_IPI;
#endif

#ifdef ARCH_RISCV_M_MODE
    riscv_clint_init();
#endif

    RT_ASSERT(irq_plic_base < ARCH_RISCV_MAX_IRQS);
    if (irq_plic_base >= ARCH_RISCV_MAX_IRQS)
    {
        LOG_E("ARCH_RISCV_MAX_IRQS is too small for local interrupts");
        return -RT_EINVAL;
    }

    base = platform_get_plic_base();
    size = platform_get_plic_size();
    if (!base || !size)
    {
        LOG_E("PLIC MMIO range is not configured");
        return -RT_EINVAL;
    }

    system_plic = plic_common_init(base, size,
            ARCH_RISCV_MAX_IRQS - irq_plic_base,
            platform_get_plic_quirks());

    RT_ASSERT(system_plic != RT_NULL);
    return system_plic ? RT_EOK : -RT_EIO;
}

static void riscv_irq_controller_percpu_init(void)
{
    if (!system_plic)
    {
        return;
    }

    plic_percpu_common_init(system_plic);
    rt_hw_interrupt_umask(IRQ_INTC(RV_IRQ_EXT));
}

#else /* ARCH_RISCV_NON_DM_IRQ_CLIC */
static rt_err_t riscv_irq_controller_init(void)
{
    rt_ubase_t base;
    rt_size_t size;

#ifdef ARCH_RISCV_M_MODE
    riscv_clint_init();
#endif

    base = platform_get_clic_base();
    size = platform_get_clic_size();
    if (!base || !size)
    {
        LOG_E("CLIC MMIO range is not configured");
        return -RT_EINVAL;
    }

    system_clic = riscv_clic_common_init(base, size,
            platform_get_clic_quirks());

    RT_ASSERT(system_clic != RT_NULL);
    if (!system_clic)
    {
        return -RT_EIO;
    }

#ifdef RT_USING_SMP
    ipi_clic_base = system_clic->ipi_base;
#endif

    return RT_EOK;
}

static void riscv_irq_controller_percpu_init(void)
{
    if (system_clic)
    {
        riscv_clic_percpu_common_init(system_clic);
    }
}
#endif /* ARCH_RISCV_NON_DM_IRQ_PLIC */

rt_weak void rt_hw_interrupt_init(void)
{
    if (riscv_is_boot_cpu() && riscv_irq_controller_init() != RT_EOK)
    {
        return;
    }

    riscv_irq_controller_percpu_init();
}

rt_weak void rt_hw_interrupt_mask(int vector)
{
    if (vector < 0 || vector >= ARCH_RISCV_MAX_IRQS)
    {
        return;
    }

#ifdef ARCH_RISCV_NON_DM_IRQ_PLIC
/* --------------------------- PLIC and Local INTC -------------------------- */

    if (vector >= irq_plic_base)
    {
        if (!system_plic)
        {
            return;
        }

        vector -= irq_plic_base;

        LOG_D("PLIC IRQ %d %s on CPU#%d", vector, "disabled", rt_hw_cpu_id());
        plic_irq_mask_raw(rt_hw_cpu_id(), vector);
    }
    else
    {
    #ifdef ARCH_RISCV_INTC_ANDES
        andes_intc_irq_mask_raw(&system_rv_intc, vector);
    #else
        riscv_intc_irq_mask_raw(&system_rv_intc, vector);
    #endif
    }

#else /* ARCH_RISCV_NON_DM_IRQ_CLIC */
/* ---------------------------------- CLIC ---------------------------------- */

    if (system_clic)
    {
        riscv_clic_irq_mask_raw(system_clic, vector);
    }

#endif /* ARCH_RISCV_NON_DM_IRQ_PLIC */
}

rt_weak void rt_hw_interrupt_umask(int vector)
{
    if (vector < 0 || vector >= ARCH_RISCV_MAX_IRQS)
    {
        return;
    }

#ifdef ARCH_RISCV_NON_DM_IRQ_PLIC
/* --------------------------- PLIC and Local INTC -------------------------- */

    if (vector >= irq_plic_base)
    {
        if (!system_plic)
        {
            return;
        }

        vector -= irq_plic_base;

        LOG_D("PLIC IRQ %d %s on CPU#%d", vector, "enabled", rt_hw_cpu_id());
        plic_irq_unmask_raw(rt_hw_cpu_id(), vector);
    }
    else
    {
    #ifdef ARCH_RISCV_INTC_ANDES
        andes_intc_irq_unmask_raw(&system_rv_intc, vector);
    #else
        riscv_intc_irq_unmask_raw(&system_rv_intc, vector);
    #endif
    }

#else /* ARCH_RISCV_NON_DM_IRQ_CLIC */
/* ---------------------------------- CLIC ---------------------------------- */

    if (system_clic)
    {
        riscv_clic_irq_unmask_raw(system_clic, vector);
    }

#endif /* ARCH_RISCV_NON_DM_IRQ_PLIC */
}

rt_weak rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if (vector >= 0 && vector < ARCH_RISCV_MAX_IRQS)
    {
        old_handler = irq_desc[vector].handler;

        if (handler != RT_NULL)
        {
            irq_desc[vector].handler = (rt_isr_handler_t)handler;
            irq_desc[vector].param = param;
        #ifdef RT_USING_INTERRUPT_INFO
            rt_snprintf(irq_desc[vector].name, RT_NAME_MAX - 1, "%s",
                    name ? name : "irq");
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

#ifdef ARCH_RISCV_NON_DM_IRQ_PLIC
    riscv_intc_irq_send_ipi_raw(&system_rv_intc,
            ipi_intc_base + ipi_vector, cpu_masks);
#else
    if (system_clic)
    {
        riscv_clic_irq_send_ipi_raw(system_clic,
                ipi_clic_base + ipi_vector, cpu_masks);
    }
#endif
}
#endif /* RT_USING_SMP */

static rt_bool_t handler_irq(int hwirq, void *data)
{
    rt_ubase_t irq = hwirq + (rt_ubase_t)data;
    struct rt_irq_desc *desc;

    if (irq >= ARCH_RISCV_MAX_IRQS)
    {
        return RT_FALSE;
    }

    desc = &irq_desc[irq];

    if (desc->handler)
    {
        desc->handler(hwirq, desc->param);

        return RT_TRUE;
    }

    return RT_FALSE;
}

#ifdef ARCH_RISCV_NON_DM_IRQ_PLIC
static rt_bool_t handler_plic_irq(int hwirq, void *data)
{
    plic_irq_ack_or_eoi(rt_hw_cpu_id(), hwirq);

    return handler_irq(hwirq, data);
}

void plic_init(void)
{
    plic_base = platform_get_plic_base();
}

void plic_set_priority(int irq, int priority)
{
    if (system_plic)
    {
        HWREG32(system_plic->regs + PRIORITY_BASE + irq * PRIORITY_PER_ID) = priority;
    }
}

void plic_irq_enable(int irq)
{
    if (system_plic)
    {
        plic_irq_unmask_raw(rt_hw_cpu_id(), irq);
    }

    csr_set(CSR_IE, BIT(RV_IRQ_EXT));
}

void plic_irq_disable(int irq)
{
    if (system_plic)
    {
        plic_irq_mask_raw(rt_hw_cpu_id(), irq);
    }
}

void plic_set_thresh(rt_uint32_t val)
{
    if (system_plic)
    {
        plic_set_threshold_raw(&plic_percpu[rt_hw_cpu_id()], val);
    }
}

void plic_set_threshold(int threshold)
{
    plic_set_thresh(threshold);
}

int plic_claim(void)
{
    if (!system_plic)
    {
        return 0;
    }

    return HWREG32(plic_percpu[rt_hw_cpu_id()].hart_base + CONTEXT_CLAIM);
}

void plic_complete(int irq)
{
    if (system_plic)
    {
        plic_irq_ack_or_eoi(rt_hw_cpu_id(), irq);
    }
}

void plic_set_ie(rt_uint32_t word_index, rt_uint32_t val)
{
    if (system_plic)
    {
        HWREG32(plic_percpu[rt_hw_cpu_id()].enable_base + word_index * sizeof(rt_uint32_t)) = val;
    }
}

void plic_handle_irq(void)
{
    if (system_plic)
    {
        plic_handler_isr_raw(system_plic, handler_plic_irq, (void *)(rt_ubase_t)irq_plic_base);
    }
}
#endif /* ARCH_RISCV_NON_DM_IRQ_PLIC */

rt_weak void rt_hw_interrupt_handle(rt_uint32_t vector, void *param)
{
    /* vector is equal to scause from trap */
    RT_UNUSED(param);

#ifdef ARCH_RISCV_NON_DM_IRQ_PLIC
/* --------------------------- PLIC and Local INTC -------------------------- */

    if (vector == RV_IRQ_EXT)
    {
        if (system_plic)
        {
            plic_handler_isr_raw(system_plic, handler_plic_irq,
                    (void *)(rt_ubase_t)irq_plic_base);
        }
    }
    else
    {
    #ifdef ARCH_RISCV_INTC_ANDES
        riscv_intc_aia_handler_raw(&system_rv_intc, handler_irq, RT_NULL);
    #else
        riscv_intc_handler_raw(&system_rv_intc, vector, handler_irq, RT_NULL);
    #endif
    }

#else /* ARCH_RISCV_NON_DM_IRQ_CLIC */
/* ---------------------------------- CLIC ---------------------------------- */

    if (system_clic)
    {
        riscv_clic_handler_isr_raw(system_clic, vector, handler_irq, RT_NULL);
    }

#endif /* ARCH_RISCV_NON_DM_IRQ_PLIC */
}
