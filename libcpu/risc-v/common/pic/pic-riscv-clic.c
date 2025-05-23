/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-20     GuEe-GUI     The first version
 */

#include <rthw.h>
#include <rtatomic.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pic.clic"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <csr.h>
#include <bitmap.h>
#include <riscv_timer.h>

#define CLIC_CFG                            0x0000
#define CLIC_INFO                           0x0004
#define CLIC_VENDOR_MINTTHRESH              0x0008
#define CLIC_INT_TRIG                       0x0040
#define CLIC_INT_IP                         0x1000
#define CLIC_INT_IE                         0x1001
#define CLIC_INT_ATTR                       0x1002
#define CLIC_INT_CTL                        0x1003

#define CLIC_CFG_VECTORED_ENABLE            BIT(0)
#define CLIC_CFG_LEVEL_SHIFT                1
#define CLIC_CFG_LEVEL_MASK                 GENMASK(4, CLIC_CFG_LEVEL_SHIFT)
#define CLIC_CFG_MODE_SHIFT                 5
#define CLIC_CFG_MODE_MASK                  GENMASK(6, CLIC_CFG_MODE_SHIFT)

#define CLIC_INFO_NUM_INTERRUPT(val)        (val & GENMASK(12, 0))
#define CLIC_INFO_VERSION(val)              ((val & GENMASK(20, 13)) >> 13)
#define CLIC_INFO_VERSION_ARCH(val)         ((val & GENMASK(20, 17)) >> 17)
#define CLIC_INFO_VERSION_IMPL(val)         ((val & GENMASK(16, 13)) >> 13)
#define CLIC_INFO_INT_CTL_BITS(val)         ((val & GENMASK(24, 21)) >> 21)
#define CLIC_INFO_NUM_TRIGGER(val)          ((val & GENMASK(30, 25)) >> 25)

#define CLIC_INT_TRIG_ENABLE                BIT(31)
#define CLIC_INT_TRIG_IRQ_SHIFT             0
#define CLIC_INT_TRIG_IRQ_MASK              GENMASK(12, 0)

#define CLIC_INT_IP_PENDING                 1

#define CLIC_INT_IE_ENABLE                  1

#define CLIC_INT_ATTR_MODE_SHIFT            6
#define CLIC_INT_ATTR_MODE_MACHINE          (0x11 << CLIC_INT_ATTR_MODE_SHIFT)
#define CLIC_INT_ATTR_MODE_SUPERVISOR       (0x01 << CLIC_INT_ATTR_MODE_SHIFT)
#define CLIC_INT_ATTR_MODE_USER             (0x00 << CLIC_INT_ATTR_MODE_SHIFT)
#define CLIC_INT_ATTR_TRIGGERED_SHIFT       1
#define CLIC_INT_ATTR_TRIGGERED_MASK        GENMASK(2, CLIC_INT_ATTR_TRIGGERED_SHIFT)
#define CLIC_INT_ATTR_TRIGGERED_LEVEL       (0x0 << CLIC_INT_ATTR_TRIGGERED_SHIFT)
#define CLIC_INT_ATTR_TRIGGERED_EDGE        (0x1 << CLIC_INT_ATTR_TRIGGERED_SHIFT)
#define CLIC_INT_ATTR_SHV                   BIT(0)

#define CLIC_INT_CTL_LEVEL(nlbits, val)     ((val) << (nlbits))
#define CLIC_INT_CTL_LEVEL_MASK(nlbits)     GENMASK(8, nlbits)
#define CLIC_INT_CTL_PRIORITY(nlbits, val)  (val)
#define CLIC_INT_CTL_PRIORITY_MASK(nlbits)  GENMASK(nlbits, 0)

#define CLIC_INT_ID_USIP                    0   /* User software Interrupt */
#define CLIC_INT_ID_SSIP                    1   /* Supervisor software Interrupt */
#define CLIC_INT_ID_MSIP                    3   /* Machine software interrupt */
#define CLIC_INT_ID_UTIP                    4   /* User timer interrupt */
#define CLIC_INT_ID_STIP                    5   /* Supervisor timer interrupt */
#define CLIC_INT_ID_MTIP                    7   /* Machine timer interrupt */
#define CLIC_INT_ID_UEIP                    8   /* User external (PLIC) interrupt */
#define CLIC_INT_ID_SEIP                    9   /* Supervisor external (PLIC) interrupt */
#define CLIC_INT_ID_MEIP                    11  /* Machine external (PLIC) interrupt */
#define CLIC_INT_ID_CSIP                    12  /* CLIC software interrupt */
#define CLIC_INT_ID_EXT_BASE                16  /* CLIC external base */

#ifdef ARCH_RISCV_M_MODE
#define CLIC_INT_ID_xSIP                    CLIC_INT_ID_SSIP
#define CLIC_INT_ID_xTIP                    CLIC_INT_ID_MTIP
#define CLIC_INT_ID_xEIP                    CLIC_INT_ID_MEIP
#else
#define CLIC_INT_ID_xSIP                    CLIC_INT_ID_MSIP
#define CLIC_INT_ID_xTIP                    CLIC_INT_ID_STIP
#define CLIC_INT_ID_xEIP                    CLIC_INT_ID_SEIP
#endif

#define CLIC_QUIRK_MODE_FIXED               0
#define CLIC_QUIRK_MINTTHRESH               1

#ifdef ARCH_RISCV_M_MODE
#include "pic-riscv-clint.c"
#endif

struct riscv_clic
{
#ifndef PIC_DISABLE_DM
    struct rt_pic parent;
#endif

    void *regs;

    rt_bitmap_t quirks;
    rt_bool_t shv;
    rt_uint32_t irqs_count:16;
    rt_uint32_t int_ctl_bits:8;

#ifdef RT_USING_SMP
    rt_uint32_t ipi_base;
    rt_atomic_t ipi_enable[RT_CPUS_NR];
    rt_atomic_t ipi_pending[RT_CPUS_NR];
#endif
};

extern void fast_irq_vectors(void);

static void riscv_clic_set_mintthresh(struct riscv_clic *clic, rt_uint32_t mintthresh)
{
    if (rt_bitmap_test_bit(&clic->quirks, CLIC_QUIRK_MINTTHRESH))
    {
        HWREG32(clic->regs + CLIC_VENDOR_MINTTHRESH) = mintthresh;
    }
}

static void riscv_clic_irq_ack_raw(struct riscv_clic *clic, int hwirq)
{
    if (clic->shv)
    {
        return;
    }

    hwirq = csr_swap(CSR_MNXTI, 0UL);
}

static void riscv_clic_irq_mask_raw(struct riscv_clic *clic, int hwirq)
{
#ifdef RT_USING_SMP
    if (hwirq >= clic->ipi_base)
    {
        rt_atomic_t *ipi_enable = &clic->ipi_enable[rt_hw_cpu_id()];

        rt_atomic_and(ipi_enable, ~BIT(hwirq - clic->ipi_base));

        if (rt_atomic_load(ipi_enable) != 0)
        {
            return;
        }

        hwirq = CLIC_INT_ID_xSIP;
    }
#endif /* RT_USING_SMP */

    HWREG8(clic->regs + CLIC_INT_IE + 4 * hwirq) = CLIC_INT_IE_ENABLE;
}

static void riscv_clic_irq_unmask_raw(struct riscv_clic *clic, int hwirq)
{
#ifdef RT_USING_SMP
    if (hwirq >= clic->ipi_base)
    {
        rt_atomic_t *ipi_enable = &clic->ipi_enable[rt_hw_cpu_id()];

        rt_atomic_or(ipi_enable, BIT(hwirq - clic->ipi_base));
        hwirq = CLIC_INT_ID_xSIP;
    }
#endif /* RT_USING_SMP */

    HWREG8(clic->regs + CLIC_INT_IE + 4 * hwirq) = !CLIC_INT_IE_ENABLE;
}

static void riscv_clic_irq_send_ipi_raw(struct riscv_clic *clic, int ipi, rt_bitmap_t *cpumask)
{
    int cpu;

    rt_bitmap_for_each_set_bit(cpumask, cpu, RT_CPUS_NR)
    {
        rt_atomic_or(&clic->ipi_pending[cpu], BIT(ipi));

    #ifdef ARCH_RISCV_M_MODE
        clint_send_ipi(cpu);
    #endif
    }

#ifndef ARCH_RISCV_M_MODE
    sbi_send_ipi((const unsigned long *)cpumask);
#endif
}

static rt_bool_t riscv_clic_handler_isr_raw(struct riscv_clic *clic, int hwirq,
        rt_bool_t (*callback)(int hwirq, void *data), void *data)
{
    if (hwirq >= CLIC_INT_ID_EXT_BASE)
    {
        return callback(hwirq, data);
    }
    else if (hwirq == CLIC_INT_ID_xTIP)
    {
        riscv_timer_isr();
        return RT_TRUE;
    }
#ifdef RT_USING_SMP
    else if (hwirq == CLIC_INT_ID_xSIP)
    {
        int ipi;
        rt_bool_t res;
        rt_bitmap_t pending;

    #ifdef ARCH_RISCV_M_MODE
        clint_clear_ipi();
    #endif

        pending = rt_atomic_exchange(&clic->ipi_pending[rt_hw_cpu_id()], 0);

        rt_bitmap_for_each_set_bit(&pending, ipi, RT_MAX_IPI)
        {
            res = callback(clic->ipi_base + ipi, data);
        }

        return res;
    }
#endif /* RT_USING_SMP */
    else if (hwirq != CLIC_INT_ID_xEIP)
    {
        LOG_E("Unhandled IRQ: %d", hwirq);
    }

    return RT_FALSE;
}

static void riscv_clic_percpu_common_init(struct riscv_clic *clic)
{
    RT_UNUSED(clic);

    csr_set(CSR_MTVT, &fast_irq_vectors);
}

static struct riscv_clic *riscv_clic_common_init(rt_ubase_t clic_base, rt_size_t clic_size,
        rt_bitmap_t quirks)
{
    rt_uint32_t value;
    struct riscv_clic *clic = rt_calloc(1, sizeof(*clic));

    if (!clic)
    {
        rt_set_errno(-RT_ENOMEM);
        return RT_NULL;
    }

    clic->regs = rt_ioremap((void *)clic_base, clic_size);

    if (!clic->regs)
    {
        rt_set_errno(-RT_EIO);

        rt_free(clic);
        return RT_NULL;
    }

    clic->quirks = quirks;

    riscv_clic_set_mintthresh(clic, 0);

    value = HWREG32(clic->regs + CLIC_INFO);
    clic->int_ctl_bits = CLIC_INFO_INT_CTL_BITS(value);
    clic->irqs_count = CLIC_INFO_NUM_INTERRUPT(value);

    HWREG32(clic->regs + CLIC_CFG) |= CLIC_CFG_VECTORED_ENABLE;
    HWREG32(clic->regs + CLIC_CFG) |= 8 << CLIC_CFG_LEVEL_SHIFT;
    HWREG32(clic->regs + CLIC_CFG) |= CLIC_CFG_MODE_MASK << CLIC_CFG_MODE_SHIFT;

    clic->shv = !!(HWREG32(clic->regs + CLIC_CFG) & CLIC_CFG_VECTORED_ENABLE);

    LOG_D("Version %d.%d, %d IRQs implemented",
            CLIC_INFO_VERSION_ARCH(value), CLIC_INFO_VERSION_IMPL(value),
            clic->irqs_count);

#ifdef RT_USING_SMP
    clic->irqs_count += RT_MAX_IPI;
#endif

    value = clic->shv ? CLIC_INT_ATTR_SHV : 0;
#ifdef ARCH_RISCV_M_MODE
    value |= CLIC_INT_ATTR_MODE_MACHINE << CLIC_INT_ATTR_MODE_SHIFT;
#else
    value |= CLIC_INT_ATTR_MODE_SUPERVISOR << CLIC_INT_ATTR_MODE_SHIFT;
#endif

    for (int hwirq = 0; hwirq < clic->irqs_count; ++hwirq)
    {
        HWREG8(clic->regs + CLIC_INT_ATTR + 4 * hwirq) &= CLIC_INT_ATTR_TRIGGERED_MASK;
        HWREG8(clic->regs + CLIC_INT_ATTR + 4 * hwirq) |= value;
    }

    return clic;
}

#ifndef PIC_DISABLE_DM
static rt_err_t riscv_clic_irq_init(struct rt_pic *pic)
{
    struct riscv_clic *clic = pirq->pic->priv_data;

    riscv_clic_percpu_common_init(clic);

    return RT_EOK;
}

static void riscv_clic_irq_ack(struct rt_pic_irq *pirq)
{
    return riscv_clic_irq_ack_raw(pirq->hwirq);
}

static void riscv_clic_irq_mask(struct rt_pic_irq *pirq)
{
    struct riscv_clic *clic = pirq->pic->priv_data;

    return riscv_clic_irq_mask_raw(clic, pirq->hwirq);
}

static void riscv_clic_irq_unmask(struct rt_pic_irq *pirq)
{
    struct riscv_clic *clic = pirq->pic->priv_data;

    return riscv_clic_irq_unmask_raw(clic, pirq->hwirq);
}

static rt_err_t riscv_clic_irq_set_priority(struct rt_pic_irq *pirq, rt_uint32_t priority)
{
    struct riscv_clic *clic = pirq->pic->priv_data;

    priority = rt_min_t(rt_uint32_t, priority, GENMASK(8, 8 - clic->int_ctl_bits));

    HWREG8(clic->regs + CLIC_INT_CTL + pirq->hwirq * 4) =
            CLIC_INT_CTL_LEVEL_MASK(clic->int_ctl_bits) |
            CLIC_INT_CTL_PRIORITY(clic->int_ctl_bits, priority);

    return RT_EOK;
}

static rt_err_t riscv_clic_irq_set_triger_mode(struct rt_pic_irq *pirq, rt_uint32_t mode)
{
    int hwirq = pirq->hwirq;
    struct riscv_clic *clic = pirq->pic->priv_data;

    if (rt_bitmap_test_bit(&clic->quirks, PLIC_QUIRK_EDGE_INTERRUPT))
    {
        return -RT_ENOSYS;
    }

    if (mode == RT_IRQ_MODE_EDGE_RISING)
    {
        HWREG8(clic->regs + CLIC_INT_ATTR + 4 * hwirq) &= CLIC_INT_ATTR_TRIGGERED_MASK;
        HWREG8(clic->regs + CLIC_INT_ATTR + 4 * hwirq) |= CLIC_INT_ATTR_TRIGGERED_EDGE;

        return RT_EOK;
    }
    else if (mode == RT_IRQ_MODE_LEVEL_HIGH)
    {
        HWREG8(clic->regs + CLIC_INT_ATTR + 4 * hwirq) &= CLIC_INT_ATTR_TRIGGERED_MASK;
        HWREG8(clic->regs + CLIC_INT_ATTR + 4 * hwirq) |= CLIC_INT_ATTR_TRIGGERED_LEVEL;

        return RT_EOK;
    }

    return -RT_ENOSYS;
}

static void riscv_clic_irq_send_ipi(struct rt_pic_irq *pirq, rt_bitmap_t *cpumask)
{
    struct riscv_clic *clic = pirq->pic->priv_data;

    riscv_clic_irq_send_ipi_raw(clic, pirq->hwirq, cpumask);
}

static int riscv_clic_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
{
    return rt_pic_config_irq(pic, hwirq, hwirq);
}

static rt_err_t riscv_clic_irq_parse(struct rt_pic *pic, struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
{
    struct riscv_clic *clic = pic->priv_data;

    out_pirq->hwirq = args->args[0];

    if (rt_bitmap_test_bit(&clic->quirks, CLIC_QUIRK_MODE_FIXED))
    {
        out_pirq->mode = args->args[1];
        out_pirq->priority = args->args[2];
    }
    else
    {
        out_pirq->mode = RT_IRQ_MODE_LEVEL_HIGH;
        out_pirq->priority = args->args[1];
    }

    return RT_EOK;
}

const static struct rt_pic_ops riscv_clic_ops =
{
    .name = "CLIC",
    .irq_init = riscv_clic_irq_init,
    .irq_ack = riscv_clic_irq_ack,
    .irq_mask = riscv_clic_irq_mask,
    .irq_unmask = riscv_clic_irq_unmask,
    .irq_set_priority = riscv_clic_irq_set_priority,
    .irq_set_triger_mode = riscv_clic_irq_set_triger_mode,
    .irq_send_ipi = riscv_clic_irq_send_ipi,
    .irq_map = riscv_clic_irq_map,
    .irq_parse = riscv_clic_irq_parse,
};

static rt_bool_t clic_common_handler_isr(int hwirq, void *data)
{
    struct rt_pic_irq *pirq;
    struct riscv_clic *clic = data;

    if (hwirq < clic->ipi_base)
    {
        pirq = rt_pic_find_irq(&clic->parent, hwirq);
    }
    else
    {
        pirq = rt_pic_find_ipi(&clic->parent, hwirq - clic->ipi_base);
    }

    riscv_clic_irq_ack(pirq);

    return rt_pic_handle_isr(pirq);
}

static rt_bool_t clic_handler(void *data)
{
    rt_ubase_t cause;
    struct riscv_clic *clic = data;

    cause = csr_read(CSR_CAUSE) & ~CAUSE_IRQ_FLAG;

    return riscv_clic_handler_isr_raw(clic, cause, clic_common_handler_isr, clic);
}

static rt_err_t riscv_clic_ofw_init(struct rt_ofw_node *np, const struct rt_ofw_node_id *id)
{
    rt_err_t err;
    rt_uint64_t clic_base, clic_size;
    rt_bitmap_t quirks;
    struct riscv_clic *clic;

    if ((err = rt_ofw_get_address(np, 0, &clic_base, &clic_size)))
    {
        return err;
    }

    quirks = id->data ? *(rt_ubase_t *)id->data : 0;

    if (!(clic = clic_common_init(clic_base, clic_size, quirks)))
    {
        return rt_get_errno();
    }

#ifdef ARCH_RISCV_M_MODE
    riscv_clint_ofw_init();
#endif

    clic->parent.priv_data = clic;
    clic->parent.ops = &riscv_clic_ops;
    rt_ofw_data(np) = &clic->parent;

    rt_pic_linear_irq(&clic->parent, clic->irqs_count);

    rt_pic_add_traps(clic_handler, clic);

#ifdef RT_USING_SMP
    clic->ipi_base = clic->irqs_count - RT_MAX_IPI;

    for (int ipi = 0; ipi < RT_MAX_IPI; ++ipi)
    {
        rt_pic_config_ipi(&clic->parent, ipi, clic->ipi_base + ipi);
    }
#endif /* RT_USING_SMP */

    rt_pic_user_extends(&clic->parent);

    return RT_EOK;
}

static rt_bitmap_t xtensa_clic_quirk = RT_BIT(CLIC_QUIRK_MODE_FIXED) | RT_BIT(CLIC_QUIRK_MINTTHRESH);

static const struct rt_ofw_node_id clic_ofw_ids[] =
{
    { .compatible = "cdns,xtensa-core-intc", .data = &xtensa_clic_quirk },
    { .compatible = "nuclei,eclic" },
    { .compatible = "nordic,nrf-clic" },
    { /* sentinel */ }
};
RT_PIC_OFW_DECLARE(riscv_clic, riscv_clic_ofw_ids, riscv_clic_ofw_init);
#endif /* PIC_DISABLE_DM */
