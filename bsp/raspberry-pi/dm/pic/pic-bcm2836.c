/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-24     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pic.bcm2836"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpuport.h>

#define LOCAL_CONTROL               0x00
#define LOCAL_PRESCALER             0x08

/*
 * The low 2 bits identify the CPU that the GPU IRQ goes to, and the next 2 bits
 * identify the CPU that the GPU FIQ goes to.
 */
#define LOCAL_GPU_ROUTING           0x0c
/* When setting bits 0-3, enables PMU interrupts on that CPU. */
#define LOCAL_PM_ROUTING_SET        0x10
/* When setting bits 0-3, disables PMU interrupts on that CPU. */
#define LOCAL_PM_ROUTING_CLR        0x14
/*
 * The low 4 bits of this are the CPU's timer IRQ enables, and the next 4 bits
 * are the CPU's timer FIQ enables (which override the IRQ bits).
 */
#define LOCAL_TIMER_INT_CONTROL0    0x40
/*
 * The low 4 bits of this are the CPU's per-mailbox IRQ enables, and the next 4
 * bits are the CPU's per-mailbox FIQ enables (which override the IRQ bits).
 */
#define LOCAL_MAILBOX_INT_CONTROL0  0x50
/*
 * The CPU's interrupt status register. Bits are defined by the LOCAL_IRQ_* bits
 * below.
 */
#define LOCAL_IRQ_PENDING0          0x60
/* Same status bits as above, but for FIQ. */
#define LOCAL_FIQ_PENDING0          0x70
/*
 * Mailbox write-to-set bits. There are 16 mailboxes, 4 per CPU, and these bits
 * are organized by mailbox number and then CPU number. We use mailbox 0 for
 * IPIs. The mailbox's interrupt is raised while any bit is set.
 */
#define LOCAL_MAILBOX0_SET0         0x80
#define LOCAL_MAILBOX3_SET0         0x8c
/* Mailbox write-to-clear bits. */
#define LOCAL_MAILBOX0_CLR0         0xc0
#define LOCAL_MAILBOX3_CLR0         0xcc

#define LOCAL_IRQ_CNTPSIRQ          0
#define LOCAL_IRQ_CNTPNSIRQ         1
#define LOCAL_IRQ_CNTHPIRQ          2
#define LOCAL_IRQ_CNTVIRQ           3
#define LOCAL_IRQ_MAILBOX0          4
#define LOCAL_IRQ_MAILBOX1          5
#define LOCAL_IRQ_MAILBOX2          6
#define LOCAL_IRQ_MAILBOX3          7
#define LOCAL_IRQ_GPU_FAST          8
#define LOCAL_IRQ_PMU_FAST          9
#define LAST_IRQ                    LOCAL_IRQ_PMU_FAST

struct bcm2836_arm_intc
{
    struct rt_pic parent;

    void *base;
};

static struct bcm2836_arm_intc intc;

static void bcm2836_arm_irqchip_mask_ipi(rt_uint32_t reg_offset, rt_uint32_t bit, int cpu)
{
    void *reg = intc.base + reg_offset + 4 * cpu;

    HWREG32(reg) &= ~RT_BIT(bit);
}

static void bcm2836_arm_irqchip_unmask_ipi(rt_uint32_t reg_offset, rt_uint32_t bit, int cpu)
{
    void *reg = intc.base + reg_offset + 4 * cpu;

    HWREG32(reg) |= RT_BIT(bit);
}

static void bcm2836_arm_irqchip_mask_timer_irq(int hwirq)
{
    bcm2836_arm_irqchip_mask_ipi(LOCAL_TIMER_INT_CONTROL0, hwirq - LOCAL_IRQ_CNTPSIRQ, rt_hw_cpu_id());
}

static void bcm2836_arm_irqchip_unmask_timer_irq(int hwirq)
{
    bcm2836_arm_irqchip_unmask_ipi(LOCAL_TIMER_INT_CONTROL0, hwirq - LOCAL_IRQ_CNTPSIRQ, rt_hw_cpu_id());
}

static void bcm2836_arm_irqchip_mask_gpu_irq(void)
{
}

static void bcm2836_arm_irqchip_unmask_gpu_irq(void)
{
}

static void bcm2836_arm_irqchip_mask_pmu_irq(void)
{
    HWREG32(intc.base + LOCAL_PM_ROUTING_CLR) = 1 << rt_hw_cpu_id();
}

static void bcm2836_arm_irqchip_unmask_pmu_irq(void)
{
    HWREG32(intc.base + LOCAL_PM_ROUTING_SET) = 1 << rt_hw_cpu_id();
}

static void bcm2836_arm_irqchip_irq_ops(int hwirq, rt_bool_t mask)
{
#define CALL_OPS(name, ...)                                 \
    if (mask) {                                             \
        bcm2836_arm_irqchip_mask_##name(__VA_ARGS__);       \
    } else {                                                \
        bcm2836_arm_irqchip_unmask_##name(__VA_ARGS__);     \
    }

    switch (hwirq)
    {
    case LOCAL_IRQ_MAILBOX0:
    case LOCAL_IRQ_MAILBOX1:
    case LOCAL_IRQ_MAILBOX2:
    case LOCAL_IRQ_MAILBOX3:
        CALL_OPS(ipi, LOCAL_MAILBOX_INT_CONTROL0, 0, rt_hw_cpu_id());
        break;
    case LOCAL_IRQ_CNTPSIRQ:
    case LOCAL_IRQ_CNTPNSIRQ:
    case LOCAL_IRQ_CNTHPIRQ:
    case LOCAL_IRQ_CNTVIRQ:
        CALL_OPS(timer_irq, hwirq);
        break;
    case LOCAL_IRQ_GPU_FAST:
        CALL_OPS(gpu_irq);
        break;
    case LOCAL_IRQ_PMU_FAST:
        CALL_OPS(pmu_irq);
        break;
    default:
        LOG_W("Unexpected hwirq = %d", hwirq);
        break;
    }
#undef CALL_OPS
}

static void bcm2836_arm_l1_intc_irq_mask(struct rt_pic_irq *pirq)
{
    bcm2836_arm_irqchip_irq_ops(pirq->hwirq, RT_TRUE);
}

static void bcm2836_arm_l1_intc_irq_unmask(struct rt_pic_irq *pirq)
{
    bcm2836_arm_irqchip_irq_ops(pirq->hwirq, RT_FALSE);
}

static void bcm2836_arm_l1_intc_irq_send_ipi(struct rt_pic_irq *pirq, rt_bitmap_t *cpumask)
{
    int cpu, hwirq = pirq->hwirq;
    void *mailbox0_base = intc.base + LOCAL_MAILBOX0_SET0;

    /*
     * Ensure that stores to normal memory are visible to the other CPUs before
     * issuing the IPI.
     */
    rt_hw_wmb();

    rt_bitmap_for_each_set_bit(cpumask, cpu, RT_CPUS_NR)
    {
        HWREG32(mailbox0_base + 16 * cpu) = RT_BIT(hwirq);
    }
}

static int bcm2836_arm_l1_intc_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
{
    struct rt_pic_irq *pirq = rt_pic_find_irq(pic, hwirq);

    pirq->mode = mode;

    switch (hwirq)
    {
    case LOCAL_IRQ_CNTPSIRQ:
    case LOCAL_IRQ_CNTPNSIRQ:
    case LOCAL_IRQ_CNTHPIRQ:
    case LOCAL_IRQ_CNTVIRQ:
        for (int cpuid = 0; cpuid < RT_CPUS_NR; ++cpuid)
        {
            RT_IRQ_AFFINITY_SET(pirq->affinity, cpuid);
        }
        break;

    default:
        RT_IRQ_AFFINITY_SET(pirq->affinity, rt_hw_cpu_id());
        break;
    }

    return rt_pic_config_irq(pic, hwirq, hwirq);
}

static rt_err_t bcm2836_arm_l1_intc_irq_parse(struct rt_pic *pic,
        struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
{
    rt_err_t err = RT_EOK;

    if (args->args_count == 2)
    {
        out_pirq->hwirq = args->args[0];
        out_pirq->mode = args->args[1];
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

const static struct rt_pic_ops bcm2836_arm_l1_intc_ops =
{
    .name = "BCM2836-ARM-L1-INTC",
    .irq_mask = bcm2836_arm_l1_intc_irq_mask,
    .irq_unmask = bcm2836_arm_l1_intc_irq_unmask,
    .irq_send_ipi = bcm2836_arm_l1_intc_irq_send_ipi,
    .irq_map = bcm2836_arm_l1_intc_irq_map,
    .irq_parse = bcm2836_arm_l1_intc_irq_parse,
};

static rt_bool_t bcm2836_arm_l1_intc_handler(void *data)
{
    rt_uint32_t hwirq;
    rt_bool_t res = RT_FALSE;
    int cpu_id = rt_hw_cpu_id();
    rt_uint32_t status = HWREG32(intc.base + LOCAL_IRQ_PENDING0 + 4 * cpu_id);

    if (!status)
    {
        status = HWREG32(intc.base + LOCAL_MAILBOX0_CLR0 + 16 * cpu_id);
    }

    if (status)
    {
        struct rt_pic_irq *pirq;

        hwirq = __rt_ffs(status) - 1;

        if (hwirq > LOCAL_IRQ_MAILBOX3 || hwirq < LOCAL_IRQ_MAILBOX0)
        {
            pirq = rt_pic_find_irq(&intc.parent, hwirq);
        }
        else
        {
            HWREG32(intc.base + LOCAL_MAILBOX0_CLR0 + 16 * rt_hw_cpu_id()) = RT_BIT(hwirq);

            pirq = rt_pic_find_ipi(&intc.parent, hwirq - LOCAL_IRQ_MAILBOX0);
        }

        rt_pic_handle_isr(pirq);

        res = RT_TRUE;
    }

    return res;
}

/*
 * The LOCAL_IRQ_CNT* timer firings are based off of the external oscillator
 * with some scaling.  The firmware sets up CNTFRQ to report 19.2Mhz, but
 * doesn't set up the scaling registers.
 */
static void bcm2835_init_local_timer_frequency(void)
{
    /*
     * Set the timer to source from the 19.2Mhz crystal clock (bit 8 unset), and
     * only increment by 1 instead of 2 (bit 9 unset).
     */
    HWREG32(intc.base + LOCAL_CONTROL) = 0;

    /* Set the timer prescaler to 1:1 (timer freq = input freq * 2**31 / prescaler) */
    HWREG32(intc.base + LOCAL_PRESCALER) = 0x80000000;
}

static rt_err_t bcm2836_arm_l1_intc_init(struct rt_ofw_node *np, const struct rt_ofw_node_id *id)
{
    rt_err_t err = RT_EOK;

    intc.base = rt_ofw_iomap(np, 0);

    if (intc.base)
    {
        bcm2835_init_local_timer_frequency();

        intc.parent.priv_data = &intc;
        intc.parent.ops = &bcm2836_arm_l1_intc_ops;
        rt_ofw_data(np) = &intc.parent;

        rt_pic_linear_irq(&intc.parent, LAST_IRQ + 1);

        for (int ipi = 0; ipi < RT_MAX_IPI; ++ipi)
        {
            struct rt_pic_irq *pirq;

            if (LOCAL_IRQ_MAILBOX0 + ipi > LOCAL_IRQ_MAILBOX3)
            {
                RT_ASSERT(0);
                break;
            }

            rt_pic_config_ipi(&intc.parent, ipi, LOCAL_IRQ_MAILBOX0 + ipi);
            pirq = rt_pic_find_ipi(&intc.parent, ipi);
            pirq->mode = RT_IRQ_MODE_EDGE_RISING;
        }

        rt_pic_add_traps(bcm2836_arm_l1_intc_handler, &intc);
    }
    else
    {
        err = -RT_ERROR;
    }

    return err;
}

static const struct rt_ofw_node_id bcm2836_arm_l1_intc_ofw_ids[] =
{
    { .compatible = "brcm,bcm2836-l1-intc" },
    { /* sentinel */ }
};
RT_PIC_OFW_DECLARE(bcm2836_arm_l1_intc, bcm2836_arm_l1_intc_ofw_ids, bcm2836_arm_l1_intc_init);
