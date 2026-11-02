/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-12     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pic.bcm2835"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* Put the bank and irq (32 bits) into the hwirq */
#define MAKE_HWIRQ(b, n)        ((b << 5) | (n))
#define HWIRQ_BANK(i)           (i >> 5)
#define HWIRQ_BIT(i)            RT_BIT(i & 0x1f)

#define NR_IRQS_BANK0           8
#define BANK0_HWIRQ_MASK        0xff
/* Shortcuts can't be disabled so any unknown new ones need to be masked */
#define SHORTCUT1_MASK          0x00007c00
#define SHORTCUT2_MASK          0x001f8000
#define SHORTCUT_SHIFT          10
#define BANK1_HWIRQ             RT_BIT(8)
#define BANK2_HWIRQ             RT_BIT(9)
#define BANK0_VALID_MASK        (BANK0_HWIRQ_MASK | BANK1_HWIRQ | BANK2_HWIRQ | SHORTCUT1_MASK | SHORTCUT2_MASK)

#define REG_FIQ_CONTROL         0x0c
#define FIQ_CONTROL_ENABLE      RT_BIT(7)

#define NR_BANKS                3
#define IRQS_PER_BANK           32

struct bcm2835_arm_intc
{
    struct rt_pic parent;

    void *base;
    void *pending[NR_BANKS];
    void *enable[NR_BANKS];
    void *disable[NR_BANKS];
};

static struct bcm2835_arm_intc intc;

static const int shortcuts[] =
{
    7, 9, 10, 18, 19,       /* Bank 1 */
    21, 22, 23, 24, 25, 30  /* Bank 2 */
};

/*
 * Handle each interrupt across the entire interrupt controller.  This reads the
 * status register before handling each interrupt, which is necessary given that
 * handle_IRQ may briefly re-enable interrupts for soft IRQ handling.
 */

static rt_uint32_t bcm2835_arm_intc_translate_bank(int bank)
{
    rt_uint32_t status = HWREG32(intc.pending[bank]);

    return MAKE_HWIRQ(bank, __rt_ffs(status) - 1);
}

static rt_uint32_t bcm2835_arm_intc_translate_shortcut(int bank, rt_uint32_t status)
{
    return MAKE_HWIRQ(bank, shortcuts[__rt_ffs(status >> SHORTCUT_SHIFT) - 1]);
}

static rt_uint32_t bcm2835_arm_intc_get_next_armctrl_hwirq(void)
{
    rt_uint32_t ret;
    rt_uint32_t status = HWREG32(intc.pending[0]) & BANK0_VALID_MASK;

    if (status == 0)
    {
        ret = ~0;
    }
    else if (status & BANK0_HWIRQ_MASK)
    {
        ret = MAKE_HWIRQ(0, __rt_ffs(status & BANK0_HWIRQ_MASK) - 1);
    }
    else if (status & SHORTCUT1_MASK)
    {
        ret = bcm2835_arm_intc_translate_shortcut(1, status & SHORTCUT1_MASK);
    }
    else if (status & SHORTCUT2_MASK)
    {
        ret = bcm2835_arm_intc_translate_shortcut(2, status & SHORTCUT2_MASK);
    }
    else if (status & BANK1_HWIRQ)
    {
        ret = bcm2835_arm_intc_translate_bank(1);
    }
    else if (status & BANK2_HWIRQ)
    {
        ret = bcm2835_arm_intc_translate_bank(2);
    }
    else
    {
        LOG_E("IRQ status panic = %d", status);
        RT_ASSERT(0);
    }

    return ret;
}

static void bcm2835_arm_intc_mask_irq(struct rt_pic_irq *pirq)
{
    int hwirq = pirq->hwirq;

    HWREG32(intc.disable[HWIRQ_BANK(hwirq)]) = HWIRQ_BIT(hwirq);
}

static void bcm2835_arm_intc_unmask_irq(struct rt_pic_irq *pirq)
{
    int hwirq = pirq->hwirq;

    HWREG32(intc.enable[HWIRQ_BANK(hwirq)]) = HWIRQ_BIT(hwirq);
}

static int bcm2835_arm_intc_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
{
    struct rt_pic_irq *pirq = rt_pic_find_irq(pic, hwirq);

    pirq->mode = mode;
    RT_IRQ_AFFINITY_SET(pirq->affinity, rt_hw_cpu_id());

    return rt_pic_config_irq(pic, hwirq, hwirq);
}

static rt_err_t bcm2835_arm_intc_irq_parse(struct rt_pic *pic,
        struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
{
    rt_err_t err = RT_EOK;

    if (args->args_count == 2 &&
        args->args[0] < NR_BANKS &&
        args->args[1] < IRQS_PER_BANK &&
        (args->args[0] != 0 || args->args[1]))
    {
        out_pirq->hwirq = MAKE_HWIRQ(args->args[0], args->args[1]);
        out_pirq->mode = RT_IRQ_MODE_EDGE_RISING;
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

const static struct rt_pic_ops bcm2835_arm_intc_ops =
{
    .name = "BCM2835-ARMCTRL-level",
    .irq_mask = bcm2835_arm_intc_mask_irq,
    .irq_unmask = bcm2835_arm_intc_unmask_irq,
    .irq_map = bcm2835_arm_intc_irq_map,
    .irq_parse = bcm2835_arm_intc_irq_parse,
};

static rt_bool_t bcm2835_arm_intc_handler(void *data)
{
    rt_uint32_t hwirq;
    rt_bool_t res = RT_FALSE;

    while ((hwirq = bcm2835_arm_intc_get_next_armctrl_hwirq()) != ~0)
    {
        struct rt_pic_irq *pirq = rt_pic_find_irq(&intc.parent, hwirq);

        rt_pic_handle_isr(pirq);

        res = RT_TRUE;
    }

    return res;
}

static rt_err_t bcm2835_arm_ofw_intc(struct rt_ofw_node *np, const struct rt_ofw_node_id *id)
{
    rt_err_t err = RT_EOK;

    intc.base = rt_ofw_iomap(np, 0);

    if (intc.base)
    {
        rt_uint32_t reg;

        int reg_pending[] = { 0x00, 0x04, 0x08 };
        int reg_enable[] = { 0x18, 0x10, 0x14 };
        int reg_disable[] = { 0x24, 0x1c, 0x20 };

        for (int i = 0; i < NR_BANKS; ++i)
        {
            intc.pending[i] = intc.base + reg_pending[i];
            intc.enable[i] = intc.base + reg_enable[i];
            intc.disable[i] = intc.base + reg_disable[i];

            reg = HWREG32(intc.enable[i]);

            if (reg)
            {
                HWREG32(intc.disable[i]) = reg;

                LOG_E("Bootloader left irq enabled: bank = %d irq-bitmask = %08x", i, reg);
            }
        }

        reg = HWREG32(intc.base + REG_FIQ_CONTROL);

        if (reg & FIQ_CONTROL_ENABLE)
        {
            HWREG32(intc.base + REG_FIQ_CONTROL) = 0;

            LOG_E("Bootloader left fiq enabled");
        }

        intc.parent.priv_data = &intc;
        intc.parent.ops = &bcm2835_arm_intc_ops;

        rt_ofw_data(np) = &intc.parent;

        rt_pic_linear_irq(&intc.parent, MAKE_HWIRQ(NR_BANKS, 0));

        rt_pic_add_traps(bcm2835_arm_intc_handler, &intc);
    }
    else
    {
        err = -RT_ERROR;
    }

    return err;
}

static const struct rt_ofw_node_id bcm2835_arm_intc_ofw_ids[] =
{
    { .compatible = "brcm,bcm2835-armctrl-ic", },
    { .compatible = "brcm,bcm2836-armctrl-ic", },
    { /* sentinel */ }
};
RT_PIC_OFW_DECLARE(bcm2835_arm_intc, bcm2835_arm_intc_ofw_ids, bcm2835_arm_ofw_intc);
