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
#include <rtatomic.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pic.riscv"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <csr.h>
#include <sbi.h>
#include <cpu.h>
#include <isa_ext.h>
#include <riscv_timer.h>

#include "pic-riscv-intc-andes.h"

#include "pic-riscv-clint.c"

struct riscv_intc
{
#ifndef PIC_DISABLE_DM
    struct rt_pic parent;
#endif /* !PIC_DISABLE_DM */

    rt_uint32_t irqs_base;
    rt_uint32_t irqs_count;
    rt_uint32_t irqs_def_count;

#ifdef RT_USING_SMP
    rt_uint32_t ipi_base;
    rt_atomic_t ipi_enable[RT_CPUS_NR];
    rt_atomic_t ipi_pending[RT_CPUS_NR];
#endif
};

static struct riscv_intc system_rv_intc;

rt_inline void riscv_intc_irq_mask_raw(struct riscv_intc *rv_intc, int hwirq)
{
#ifdef RT_USING_SMP
    if (hwirq >= rv_intc->ipi_base)
    {
        rt_atomic_t *ipi_enable = &rv_intc->ipi_enable[rt_hw_cpu_id()];

        rt_atomic_and(ipi_enable, ~BIT(hwirq - rv_intc->ipi_base));

        if (rt_atomic_load(ipi_enable) != 0)
        {
            return;
        }

        hwirq = RV_IRQ_SOFT;
    }
#endif /* RT_USING_SMP */

#if BITS_PER_LONG == 32
    if (hwirq >= BITS_PER_LONG)
    {
        csr_clear(CSR_IEH, BIT(hwirq - BITS_PER_LONG));
    }
    else
#endif /* BITS_PER_LONG == 32 */
    {
        csr_clear(CSR_IE, BIT(hwirq));
    }
}

rt_inline void riscv_intc_irq_unmask_raw(struct riscv_intc *rv_intc, int hwirq)
{
#ifdef RT_USING_SMP
    if (hwirq >= rv_intc->ipi_base)
    {
        rt_atomic_t *ipi_enable = &rv_intc->ipi_enable[rt_hw_cpu_id()];

        rt_atomic_or(ipi_enable, BIT(hwirq - rv_intc->ipi_base));
        hwirq = RV_IRQ_SOFT;
    }
#endif /* RT_USING_SMP */

#if BITS_PER_LONG == 32
    if (hwirq >= BITS_PER_LONG)
    {
        csr_set(CSR_IEH, BIT(hwirq - BITS_PER_LONG));
    }
    else
#endif /* BITS_PER_LONG == 32 */
    {
        csr_set(CSR_IE, BIT(hwirq));
    }
}

rt_inline void andes_intc_irq_mask_raw(struct riscv_intc *rv_intc, int hwirq)
{
    /*
     * Andes specific S-mode local interrupt causes (hwirq)
     * are defined as (256 + n) and controlled by n-th bit of SLIE.
     */
    rt_uint32_t mask;

#ifdef RT_USING_SMP
    if (hwirq >= rv_intc->ipi_base)
    {
        rt_atomic_t *ipi_enable = &rv_intc->ipi_enable[rt_hw_cpu_id()];

        rt_atomic_and(ipi_enable, ~BIT(hwirq - rv_intc->ipi_base));

        if (rt_atomic_load(ipi_enable) != 0)
        {
            return;
        }

        hwirq = RV_IRQ_SOFT;
    }
#endif /* RT_USING_SMP */

    mask = BIT(hwirq % BITS_PER_LONG);

    if (hwirq < ANDES_SLI_CAUSE_BASE)
    {
        csr_clear(CSR_IE, mask);
    }
    else
    {
        csr_clear(ANDES_CSR_SLIE, mask);
    }
}

rt_inline void andes_intc_irq_unmask_raw(struct riscv_intc *rv_intc, int hwirq)
{
    rt_uint32_t mask;

#ifdef RT_USING_SMP
    if (hwirq >= rv_intc->ipi_base)
    {
        rt_atomic_t *ipi_enable = &rv_intc->ipi_enable[rt_hw_cpu_id()];

        rt_atomic_or(ipi_enable, BIT(hwirq - rv_intc->ipi_base));
        hwirq = RV_IRQ_SOFT;
    }
#endif /* RT_USING_SMP */

    mask = BIT(hwirq % BITS_PER_LONG);

    if (hwirq < ANDES_SLI_CAUSE_BASE)
    {
        csr_set(CSR_IE, mask);
    }
    else
    {
        csr_set(ANDES_CSR_SLIE, mask);
    }
}

rt_inline void riscv_intc_irq_send_ipi_raw(struct riscv_intc *rv_intc, int ipi, rt_bitmap_t *cpumask)
{
#if defined(RT_USING_SMP) || defined(ARCH_RISCV_M_MODE)
    int cpu;

    rt_bitmap_for_each_set_bit(cpumask, cpu, RT_CPUS_NR)
    {
    #ifdef RT_USING_SMP
        rt_atomic_or(&rv_intc->ipi_pending[cpu], BIT(ipi));
    #endif

    #ifndef ARCH_RISCV_M_MODE
        if (riscv_aclint_ipi_base)
    #endif
        {
            clint_send_ipi(cpu);
        }
    }
#endif /* RT_USING_SMP || ARCH_RISCV_M_MODE */

#ifndef ARCH_RISCV_M_MODE
    if (!riscv_aclint_ipi_base)
    {
        sbi_send_ipi((const unsigned long *)cpumask);
    }
#endif /* !ARCH_RISCV_M_MODE */
}

rt_inline rt_bool_t riscv_intc_common_handler_raw(struct riscv_intc *rv_intc, int hwirq,
        rt_bool_t (*callback)(int hwirq, void *data), void *data)
{
#ifdef RT_USING_SMP
    if (hwirq != RV_IRQ_SOFT)
#endif
    {
        if (hwirq != RV_IRQ_TIMER)
        {
            return callback(hwirq, data);
        }
        else
        {
            riscv_timer_isr();
            return RT_TRUE;
        }
    }
#ifdef RT_USING_SMP
    else
    {
        int ipi;
        rt_bool_t res;
        rt_bitmap_t pending;

    #ifndef ARCH_RISCV_M_MODE
        if (riscv_aclint_ipi_base)
    #endif
        {
            clint_clear_ipi();
        }
    #ifndef ARCH_RISCV_M_MODE
        else
        {
            csr_clear(CSR_IP, IE_SIE);
        }
    #endif

        pending = rt_atomic_exchange(&rv_intc->ipi_pending[rt_hw_cpu_id()], 0);

        rt_bitmap_for_each_set_bit(&pending, ipi, RT_MAX_IPI)
        {
            res = callback(rv_intc->ipi_base + ipi, data);
        }

        return res;
    }
#endif /* RT_USING_SMP */
}

rt_inline rt_bool_t riscv_intc_handler_raw(struct riscv_intc *rv_intc, rt_ubase_t scause,
        rt_bool_t (*callback)(int hwirq, void *data), void *data)
{
    return riscv_intc_common_handler_raw(rv_intc, scause & ~CAUSE_IRQ_FLAG, callback, data);
}

rt_inline rt_bool_t riscv_intc_aia_handler_raw(struct riscv_intc *rv_intc,
        rt_bool_t (*callback)(int hwirq, void *data), void *data)
{
    rt_ubase_t topi;
    rt_bool_t res = RT_FALSE;

    while ((topi = csr_read(CSR_TOPI) >> TOPI_IID_SHIFT))
    {
        res = riscv_intc_common_handler_raw(rv_intc, topi, callback, data);
    }

    return res;
}

static void riscv_intc_common_init(struct riscv_intc *rv_intc, rt_bool_t is_andes)
{
    rt_memset(rv_intc, 0, sizeof(*rv_intc));
    rv_intc->irqs_def_count = RT_BITS_PER_LONG;

    if (is_andes)
    {
        rv_intc->irqs_base = ANDES_SLI_CAUSE_BASE;
        rv_intc->irqs_count = ANDES_RV_IRQ_LAST;
    }
    else
    {
        rv_intc->irqs_base = BITS_PER_LONG;
        rv_intc->irqs_count = 0;
    }

    if (riscv_isa_ext_test(SxAIA))
    {
        rv_intc->irqs_def_count = 64;
    }
    else
    {
        rv_intc->irqs_def_count = IRQ_LOCAL_MAX;
    }

#ifdef RT_USING_SMP
    rv_intc->irqs_def_count += RT_MAX_IPI;
#endif
}

#ifndef PIC_DISABLE_DM
static void riscv_intc_irq_mask(struct rt_pic_irq *pirq)
{
    RT_IRQ_AFFINITY_CLEAR(pirq->affinity, rt_hw_cpu_id());
    riscv_intc_irq_mask_raw(pirq->pic->priv_data, pirq->hwirq);
}

static void riscv_intc_irq_unmask(struct rt_pic_irq *pirq)
{
    RT_IRQ_AFFINITY_SET(pirq->affinity, rt_hw_cpu_id());
    riscv_intc_irq_unmask_raw(pirq->pic->priv_data, pirq->hwirq);
}

static void andes_intc_irq_mask(struct rt_pic_irq *pirq)
{
    andes_intc_irq_mask_raw(pirq->pic->priv_data, pirq->hwirq);
    RT_IRQ_AFFINITY_CLEAR(pirq->affinity, rt_hw_cpu_id());
}

static void andes_intc_irq_unmask(struct rt_pic_irq *pirq)
{
    RT_IRQ_AFFINITY_SET(pirq->affinity, rt_hw_cpu_id());
    andes_intc_irq_unmask_raw(pirq->pic->priv_data, pirq->hwirq);
}

static void riscv_intc_irq_send_ipi(struct rt_pic_irq *pirq, rt_bitmap_t *cpumask)
{
    struct riscv_intc *rv_intc = pirq->pic->priv_data;

    riscv_intc_irq_send_ipi_raw(rv_intc, pirq->hwirq, cpumask);
}

static int riscv_intc_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
{
    int irq, irq_index = -1;
    struct riscv_intc *rv_intc = rt_container_of(pic, struct riscv_intc, parent);

    if (hwirq >= rv_intc->irqs_def_count &&
        (hwirq < rv_intc->irqs_base || hwirq >= rv_intc->irqs_base + rv_intc->irqs_count))
    {
        return -RT_EINVAL;
    }

    if (hwirq < rv_intc->irqs_def_count)
    {
        irq_index = hwirq;
    }
    else if (hwirq >= rv_intc->irqs_base &&
            hwirq < rv_intc->irqs_base + rv_intc->irqs_count)
    {
        irq_index = rv_intc->irqs_def_count + hwirq - rv_intc->irqs_base;
    }

    if (irq_index >= 0)
    {
        irq = rt_pic_config_irq(pic, hwirq, irq_index);
    }
    else
    {
        irq = -1;
    }

    return irq;
}

static rt_err_t riscv_intc_irq_parse(struct rt_pic *pic,
        struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
{
    rt_err_t err = RT_EOK;

    if (args->args_count == 1)
    {
        out_pirq->hwirq = args->args[0];
        out_pirq->mode = RT_IRQ_MODE_EDGE_RISING;
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

const static struct rt_pic_ops riscv_intc_ops =
{
    .name = "RISC-V-INTC",
    .irq_mask = riscv_intc_irq_mask,
    .irq_unmask = riscv_intc_irq_unmask,
    .irq_send_ipi = riscv_intc_irq_send_ipi,
    .irq_map = riscv_intc_irq_map,
    .irq_parse = riscv_intc_irq_parse,
};

const static struct rt_pic_ops andes_intc_ops =
{
    .name = "ANDES-INTC",
    .irq_mask = andes_intc_irq_mask,
    .irq_unmask = andes_intc_irq_unmask,
    .irq_send_ipi = riscv_intc_irq_send_ipi,
    .irq_map = riscv_intc_irq_map,
    .irq_parse = riscv_intc_irq_parse,
};

static rt_bool_t riscv_intc_common_handler_isr(int hwirq, void *data)
{
    struct rt_pic_irq *pirq;
    struct riscv_intc *rv_intc = data;

#ifdef RT_USING_SMP
    if (hwirq < rv_intc->ipi_base)
#endif
    {
        pirq = rt_pic_find_irq(&rv_intc->parent, hwirq);
    }
#ifdef RT_USING_SMP
    else
    {
        pirq = rt_pic_find_ipi(&rv_intc->parent, hwirq - rv_intc->ipi_base);
    }
#endif

    return rt_pic_handle_isr(pirq) == RT_EOK;
}

static rt_bool_t riscv_intc_handler(void *data)
{
    rt_ubase_t cause;
    struct riscv_intc *rv_intc = data;

    cause = csr_read(CSR_CAUSE);

    return riscv_intc_handler_raw(rv_intc, cause, riscv_intc_common_handler_isr, data);
}

static rt_bool_t riscv_intc_aia_handler(void *data)
{
    struct riscv_intc *rv_intc = data;

    return riscv_intc_aia_handler_raw(rv_intc, riscv_intc_common_handler_isr, data);
}

static rt_err_t riscv_intc_ofw_init(struct rt_ofw_node *np, const struct rt_ofw_node_id *id)
{
    const struct rt_pic_ops *ops;
    struct riscv_intc *rv_intc = &system_rv_intc;
    struct rt_ofw_node *pnp = rt_ofw_get_parent(np);

    /* Only boot CPU to init */
    if (rt_ofw_get_cpu_hwid(pnp, 0) != boot_cpu_hartid)
    {
        rt_ofw_node_put(pnp);
        rt_ofw_data(np) = &rv_intc->parent;

        return RT_EOK;
    }
    rt_ofw_node_put(pnp);

    ops = id->data;
    riscv_intc_common_init(rv_intc, ops == &andes_intc_ops);

    riscv_clint_ofw_init();

    if (riscv_isa_ext_test(SxAIA))
    {
        rt_pic_add_traps(riscv_intc_aia_handler, rv_intc);
    }
    else
    {
        rt_pic_add_traps(riscv_intc_handler, rv_intc);
    }

    rv_intc->parent.priv_data = rv_intc;
    rv_intc->parent.ops = ops;
    rt_ofw_data(np) = &rv_intc->parent;

    rt_pic_linear_irq(&rv_intc->parent, rv_intc->irqs_def_count + rv_intc->irqs_count);

#ifdef RT_USING_SMP
    rv_intc->ipi_base = rv_intc->parent.irq_nr - RT_MAX_IPI;

    for (int ipi = 0; ipi < RT_MAX_IPI; ++ipi)
    {
        rt_pic_config_ipi(&rv_intc->parent, ipi, rv_intc->ipi_base + ipi);
    }
#endif /* RT_USING_SMP */

    rt_pic_user_extends(&rv_intc->parent);

    return RT_EOK;
}

static const struct rt_ofw_node_id riscv_intc_ofw_ids[] =
{
    { .compatible = "riscv,cpu-intc", (void *)&riscv_intc_ops },
    { .compatible = "andestech,cpu-intc", (void *)&andes_intc_ops },
    { /* sentinel */ }
};
RT_PIC_OFW_DECLARE(riscv_intc, riscv_intc_ofw_ids, riscv_intc_ofw_init);
#endif /* !PIC_DISABLE_DM */
