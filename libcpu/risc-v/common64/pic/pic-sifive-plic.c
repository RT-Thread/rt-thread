/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-30     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pic.plic"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <csr.h>
#include <cpu.h>
#include <mmu.h>
#include <cache.h>
#include <bitmap.h>

/*
 * This driver implements a version of the RISC-V PLIC with the actual layout
 * specified in chapter 8 of the SiFive U5 Coreplex Series Manual:
 *
 *     https://static.dev.sifive.com/U54-MC-RVCoreIP.pdf
 */

#define MAX_DEVICES                     1024
#define MAX_CONTEXTS                    15872

/*
 * Each interrupt source has a priority register associated with it.
 * We always hardwire it to one in Linux.
 */
#define PRIORITY_BASE                   0
#define   PRIORITY_PER_ID               4

#ifdef ARCH_RISCV_M_MODE
#define CONTEXT_ENABLE_MODE_OFFSET      0
#define CONTEXT_BASE_MODE_OFFSET        0
#else
#define CONTEXT_ENABLE_MODE_OFFSET      0x80
#define CONTEXT_BASE_MODE_OFFSET        0x1000
#endif

/*
 * Each hart context has a vector of interrupt enable bits associated with it.
 * There's one bit for each interrupt source.
 */
#define CONTEXT_ENABLE_BASE             (0x2000 + CONTEXT_ENABLE_MODE_OFFSET)
#define   CONTEXT_ENABLE_SIZE(hartid)   ((2 * hartid) * 0x80)

/*
 * Each hart context has a set of control registers associated with it.  Right
 * now there's only two: a source priority threshold over which the hart will
 * take an interrupt, and a register to claim interrupts.
 */
#define CONTEXT_BASE                    (0x200000 + CONTEXT_BASE_MODE_OFFSET)
#define   CONTEXT_SIZE(hartid)          ((2 * hartid) * 0x1000)
#define   CONTEXT_THRESHOLD             0x00
#define   CONTEXT_CLAIM                 0x04

#define PLIC_DISABLE_THRESHOLD          0x7
#define PLIC_ENABLE_THRESHOLD           0

#define PLIC_HWIRQ_START                1

#define PLIC_QUIRK_EDGE_INTERRUPT       0

struct plic
{
#ifndef PIC_DISABLE_DM
    struct rt_pic parent;
    struct rt_ofw_node *np;

    int parent_irq;
#endif

    void *regs;

    rt_bitmap_t quirks;

    rt_uint32_t irqs_count;
};

struct plic_percpu
{
    void *hart_base;
    void *enable_base;

    struct rt_spinlock enable_lock;
};

static struct plic_percpu plic_percpu[RT_CPUS_NR] rt_align(L1_CACHE_BYTES);

static void plic_set_threshold(struct plic_percpu *percpu, rt_uint32_t threshold)
{
    /* Priority must be > threshold to trigger an interrupt */
    HWREG32(percpu->hart_base + CONTEXT_THRESHOLD) = threshold;
}

static void plic_toggle(struct plic_percpu *percpu, int hwirq, rt_bool_t enable)
{
    rt_ubase_t level;
    rt_uint32_t *reg, hwirq_mask;

    level = rt_spin_lock_irqsave(&percpu->enable_lock);

    reg = percpu->enable_base + (hwirq / 32) * sizeof(rt_uint32_t);
    hwirq_mask = 1 << (hwirq % 32);

    if (enable)
    {
        HWREG32(reg) |= hwirq_mask;
    }
    else
    {
        HWREG32(reg) &= ~hwirq_mask;
    }

    rt_spin_unlock_irqrestore(&percpu->enable_lock, level);
}

static void plic_irq_unmask_raw(int cpu, int hwirq)
{
    struct plic_percpu *percpu = &plic_percpu[cpu];

    plic_toggle(percpu, hwirq, RT_TRUE);
}

static void plic_irq_mask_raw(int cpu, int hwirq)
{
    struct plic_percpu *percpu = &plic_percpu[cpu];

    plic_toggle(percpu, hwirq, RT_FALSE);
}

static void plic_irq_ack_or_eoi(int cpu, int hwirq)
{
    struct plic_percpu *percpu = &plic_percpu[cpu];

    HWREG32(percpu->hart_base + CONTEXT_CLAIM) = hwirq;
}

static rt_bool_t plic_handler_isr_raw(struct plic *plic,
        rt_bool_t (*callback)(int hwirq, void *data), void *data)
{
    int hwirq;
    void *claim;
    rt_bool_t res = RT_FALSE;
    struct plic_percpu *percpu = &plic_percpu[rt_hw_cpu_id()];

    claim = percpu->hart_base + CONTEXT_CLAIM;

    while ((hwirq = HWREG32(claim)))
    {
        res = callback(hwirq, data);
    }

    return res;
}

static void plic_percpu_common_init(struct plic *plic)
{
    struct plic_percpu *percpu = &plic_percpu[rt_hw_cpu_id()];

    plic_set_threshold(percpu, PLIC_ENABLE_THRESHOLD);
}

static struct plic *plic_common_init(rt_ubase_t plic_base, rt_size_t plic_size,
        rt_size_t ndev, rt_bitmap_t quirks)
{
    struct plic *plic = rt_calloc(1, sizeof(*plic));

    if (!plic)
    {
        rt_set_errno(-RT_ENOMEM);
        return RT_NULL;
    }

    plic->regs = rt_ioremap((void *)plic_base, plic_size);

    if (!plic->regs)
    {
        rt_set_errno(-RT_EIO);

        rt_free(plic);
        return RT_NULL;
    }

    plic->quirks = quirks;
    plic->irqs_count = ndev;

    for (int cpu = 0, hartid; cpu < RT_CPUS_NR; ++cpu)
    {
        struct plic_percpu *percpu = &plic_percpu[cpu];

    #ifndef RT_USING_SMP
        hartid = boot_cpu_hartid;
    #else
        hartid = riscv_cpu_id_to_hartid(cpu);
    #endif

        percpu->hart_base = plic->regs + CONTEXT_BASE + CONTEXT_SIZE(hartid);
        percpu->enable_base = plic->regs + CONTEXT_ENABLE_BASE + CONTEXT_ENABLE_SIZE(hartid);

        rt_spin_lock_init(&percpu->enable_lock);
    }

    /* Set default priority */
    for (int hwirq = PLIC_HWIRQ_START; hwirq <= plic->irqs_count; ++hwirq)
    {
        HWREG32(plic->regs + PRIORITY_BASE + hwirq * PRIORITY_PER_ID) = PLIC_ENABLE_THRESHOLD + 1;
    }

    return plic;
}

#ifndef PIC_DISABLE_DM
static void plic_handler(int hwirq, void *data);

static rt_err_t plic_irq_init(struct rt_pic *pic)
{
    struct plic *plic = pic->priv_data;

    if (plic->parent_irq < 0)
    {
        struct rt_ofw_cell_args irq_args;

        if (rt_ofw_parse_irq_cells(plic->np, 0, &irq_args))
        {
            LOG_E("%s: Parent IRQ is not available", rt_ofw_node_full_name(plic->np));
            goto _percpu_init;
        }

        /* Create mapping */
        irq_args.args[0] = RV_IRQ_EXT;

        plic->parent_irq = rt_ofw_map_irq(&irq_args);
        rt_hw_interrupt_install(plic->parent_irq, plic_handler, plic, "PLIC");
    }

    rt_hw_interrupt_umask(plic->parent_irq);

_percpu_init:
    plic_percpu_common_init(plic);

    return RT_EOK;
}

static void plic_irq_ack(struct rt_pic_irq *pirq)
{
    if (pirq->mode == RT_IRQ_MODE_EDGE_RISING)
    {
        plic_irq_ack_or_eoi(rt_hw_cpu_id(), pirq->hwirq);
    }
}

static void plic_irq_unmask(struct rt_pic_irq *pirq)
{
    int cpu, count = 0;

    rt_bitmap_for_each_set_bit(pirq->affinity, cpu, RT_CPUS_NR)
    {
        plic_irq_unmask_raw(cpu, pirq->hwirq);
        ++count;
    }

    if (!count)
    {
        int boot_cpu_id = riscv_hartid_to_cpu_id(boot_cpu_hartid);

        RT_IRQ_AFFINITY_SET(pirq->affinity, boot_cpu_id);
        plic_irq_unmask_raw(boot_cpu_id, pirq->hwirq);
    }
}

static void plic_irq_mask(struct rt_pic_irq *pirq)
{
    int cpu;

    rt_bitmap_for_each_set_bit(pirq->affinity, cpu, RT_CPUS_NR)
    {
        plic_irq_mask_raw(cpu, pirq->hwirq);
    }
}

static void plic_irq_eoi(struct rt_pic_irq *pirq)
{
    if (pirq->mode == RT_IRQ_MODE_LEVEL_HIGH)
    {
        plic_irq_ack_or_eoi(rt_hw_cpu_id(), pirq->hwirq);
    }
}

static rt_err_t plic_irq_set_priority(struct rt_pic_irq *pirq, rt_uint32_t priority)
{
    struct plic *plic = pirq->pic->priv_data;

    priority = rt_min_t(rt_uint32_t, priority, PLIC_DISABLE_THRESHOLD);

    HWREG32(plic->regs + PRIORITY_BASE + pirq->hwirq * PRIORITY_PER_ID) = priority;

    return RT_EOK;
}

static rt_err_t plic_irq_set_affinity(struct rt_pic_irq *pirq, rt_bitmap_t *affinity)
{
    int cpu;

    rt_bitmap_for_each_clear_bit(affinity, cpu, RT_CPUS_NR)
    {
        plic_toggle(&plic_percpu[cpu], pirq->hwirq, RT_FALSE);
    }

    rt_bitmap_for_each_set_bit(affinity, cpu, RT_CPUS_NR)
    {
        plic_toggle(&plic_percpu[cpu], pirq->hwirq, RT_TRUE);
    }

    return RT_EOK;
}

static rt_err_t plic_irq_set_triger_mode(struct rt_pic_irq *pirq, rt_uint32_t mode)
{
    struct plic *plic = pirq->pic->priv_data;

    if (rt_bitmap_test_bit(&plic->quirks, PLIC_QUIRK_EDGE_INTERRUPT))
    {
        return -RT_ENOSYS;
    }

    if (mode == RT_IRQ_MODE_EDGE_RISING || mode == RT_IRQ_MODE_LEVEL_HIGH)
    {
        return RT_EOK;
    }

    return -RT_ENOSYS;
}

static int plic_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
{
    struct rt_pic_irq *pirq = rt_pic_find_irq(pic, hwirq - PLIC_HWIRQ_START);

    pirq->mode = mode;

    return rt_pic_config_irq(pic, hwirq - PLIC_HWIRQ_START, hwirq);
}

static rt_err_t plic_irq_parse(struct rt_pic *pic, struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
{
    struct plic *plic = pic->priv_data;

    out_pirq->hwirq = args->args[0];

    if (rt_bitmap_test_bit(&plic->quirks, PLIC_QUIRK_EDGE_INTERRUPT))
    {
        out_pirq->mode = args->args[1];
    }
    else
    {
        out_pirq->mode = RT_IRQ_MODE_LEVEL_HIGH;
    }

    return RT_EOK;
}

const static struct rt_pic_ops plic_ops =
{
    .name = "SiFive-PLIC",
    .irq_init = plic_irq_init,
    .irq_ack = plic_irq_ack,
    .irq_mask = plic_irq_mask,
    .irq_unmask = plic_irq_unmask,
    .irq_eoi = plic_irq_eoi,
    .irq_set_priority = plic_irq_set_priority,
    .irq_set_affinity = plic_irq_set_affinity,
    .irq_set_triger_mode = plic_irq_set_triger_mode,
    .irq_map = plic_irq_map,
    .irq_parse = plic_irq_parse,
};

static rt_bool_t plic_common_handler_isr(int hwirq, void *data)
{
    rt_bool_t res;
    struct plic *plic = data;
    struct rt_pic_irq *pirq = rt_pic_find_irq(&plic->parent, hwirq - PLIC_HWIRQ_START);

    plic_irq_ack(pirq);

    res = rt_pic_handle_isr(pirq);

    plic_irq_eoi(pirq);

    return res;
}

static void plic_handler(int hwirq, void *data)
{
    struct plic *plic = data;

    plic_handler_isr_raw(plic, plic_common_handler_isr, plic);
}

static rt_err_t plic_ofw_init(struct rt_ofw_node *np, const struct rt_ofw_node_id *id)
{
    rt_err_t err;
    rt_uint32_t irqs_count;
    rt_uint64_t plic_base, plic_size;
    rt_bitmap_t quirks;
    struct plic *plic;

    if ((err = rt_ofw_get_address(np, 0, &plic_base, &plic_size)))
    {
        return err;
    }

    if ((err = rt_ofw_prop_read_u32(np, "riscv,ndev", &irqs_count)))
    {
        return err;
    }

    quirks = id->data ? *(rt_ubase_t *)id->data : 0;

    if (!(plic = plic_common_init(plic_base, plic_size, irqs_count, quirks)))
    {
        return rt_get_errno();
    }

    plic->np = np;
    plic->parent_irq = -1;

    plic->parent.priv_data = plic;
    plic->parent.ops = &plic_ops;
    rt_ofw_data(np) = &plic->parent;

    rt_pic_linear_irq(&plic->parent, plic->irqs_count);

    rt_pic_user_extends(&plic->parent);

    return RT_EOK;
}

static rt_bitmap_t andestech_nceplic100_quirk_edge = RT_BIT(PLIC_QUIRK_EDGE_INTERRUPT);
static rt_bitmap_t thead_c900_quirk_edge = RT_BIT(PLIC_QUIRK_EDGE_INTERRUPT);

static const struct rt_ofw_node_id plic_ofw_ids[] =
{
    { .compatible = "sifive,plic-1.0.0" },
    { .compatible = "riscv,plic0" },
    { .compatible = "andestech,nceplic100", .data = &andestech_nceplic100_quirk_edge },
    { .compatible = "thead,c900-plic", .data = &thead_c900_quirk_edge },
    { /* sentinel */ }
};
RT_PIC_OFW_DECLARE(plic, plic_ofw_ids, plic_ofw_init);
#endif /* PIC_DISABLE_DM */
