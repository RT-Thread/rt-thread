/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-29     RTT          the first version
 */

#include <rtthread.h>
#include <cpuport.h>

#define DBG_TAG "pic.nvic"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/pic.h>
#include <drivers/ofw.h>
#include <drivers/ofw_io.h>

#define NVIC_ICTR_ADDR            0xe000e004UL
#define NVIC_ICSR_ADDR            0xe000ed04UL
#define NVIC_ICSR_VECTACTIVE_MASK 0x1ffUL
#define NVIC_ISER_OFFSET          0x000UL
#define NVIC_ICER_OFFSET          0x080UL
#define NVIC_ISPR_OFFSET          0x100UL
#define NVIC_ICPR_OFFSET          0x180UL
#define NVIC_IABR_OFFSET          0x200UL
#define NVIC_IPR_OFFSET           0x300UL
#define NVIC_REG_INDEX(irq)       ((rt_uint32_t)(irq) >> 5)
#define NVIC_REG_MASK(irq)        RT_BIT((rt_uint32_t)(irq) & 0x1f)

struct arm_nvic
{
    struct rt_pic parent;
    rt_ubase_t base;
    rt_uint32_t irq_nr;
    rt_uint8_t priority_bits;
};

rt_inline void nvic_sync(void)
{
    rt_hw_dsb();
    rt_hw_isb();
}

static struct arm_nvic _nvic;

static rt_ubase_t nvic_reg(struct arm_nvic *nvic,
                           rt_ubase_t offset, int hwirq)
{
    return nvic->base + offset + NVIC_REG_INDEX(hwirq) * sizeof(rt_uint32_t);
}

static void nvic_irq_mask(struct rt_pic_irq *pirq)
{
    struct arm_nvic *nvic = pirq->pic->priv_data;

    HWREG32(nvic_reg(nvic, NVIC_ICER_OFFSET, pirq->hwirq)) =
        NVIC_REG_MASK(pirq->hwirq);
    nvic_sync();
}

static void nvic_irq_unmask(struct rt_pic_irq *pirq)
{
    struct arm_nvic *nvic = pirq->pic->priv_data;

    HWREG32(nvic_reg(nvic, NVIC_ISER_OFFSET, pirq->hwirq)) =
        NVIC_REG_MASK(pirq->hwirq);
    nvic_sync();
}

static rt_err_t nvic_irq_set_priority(struct rt_pic_irq *pirq, rt_uint32_t priority)
{
    struct arm_nvic *nvic = pirq->pic->priv_data;
    rt_uint32_t priority_max = RT_BIT(nvic->priority_bits) - 1;

    if (priority > priority_max)
    {
        return -RT_EINVAL;
    }

    HWREG8(nvic->base + NVIC_IPR_OFFSET + pirq->hwirq) =
        priority << (8 - nvic->priority_bits);
    pirq->priority = priority;

    return RT_EOK;
}

static rt_err_t nvic_irq_set_state(struct rt_pic *pic, int hwirq,
                                   int type, rt_bool_t state)
{
    struct arm_nvic *nvic = pic->priv_data;
    rt_ubase_t reg;

    if (hwirq < 0 || hwirq >= nvic->irq_nr)
    {
        return -RT_EINVAL;
    }

    switch (type)
    {
    case RT_IRQ_STATE_PENDING:
        reg = nvic_reg(nvic, state ? NVIC_ISPR_OFFSET : NVIC_ICPR_OFFSET, hwirq);
        HWREG32(reg) = NVIC_REG_MASK(hwirq);
        break;

    case RT_IRQ_STATE_MASKED:
        reg = nvic_reg(nvic, state ? NVIC_ICER_OFFSET : NVIC_ISER_OFFSET, hwirq);
        HWREG32(reg) = NVIC_REG_MASK(hwirq);
        break;

    default:
        return -RT_ENOSYS;
    }

    nvic_sync();

    return RT_EOK;
}

static rt_err_t nvic_irq_get_state(struct rt_pic *pic, int hwirq,
                                   int type, rt_bool_t *out_state)
{
    rt_ubase_t offset;
    struct arm_nvic *nvic = pic->priv_data;

    if (!out_state || hwirq < 0 || hwirq >= nvic->irq_nr)
    {
        return -RT_EINVAL;
    }

    switch (type)
    {
    case RT_IRQ_STATE_PENDING:
        offset = NVIC_ISPR_OFFSET;
        break;

    case RT_IRQ_STATE_ACTIVE:
        offset = NVIC_IABR_OFFSET;
        break;

    case RT_IRQ_STATE_MASKED:
        offset = NVIC_ISER_OFFSET;
        break;

    default:
        return -RT_ENOSYS;
    }

    *out_state = !!(HWREG32(nvic_reg(nvic, offset, hwirq)) &
                    NVIC_REG_MASK(hwirq));
    if (type == RT_IRQ_STATE_MASKED)
    {
        *out_state = !*out_state;
    }

    return RT_EOK;
}

static int nvic_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t priority)
{
    int irq;
    struct arm_nvic *nvic = pic->priv_data;
    struct rt_pic_irq *pirq;

    if (hwirq < 0 || hwirq >= nvic->irq_nr)
    {
        return -RT_EINVAL;
    }

    pirq = rt_pic_find_irq(pic, hwirq);
    irq = rt_pic_config_irq(pic, hwirq, hwirq);

    if (irq >= 0 && nvic_irq_set_priority(pirq, priority))
    {
        irq = -RT_EINVAL;
    }

    return irq;
}

static rt_err_t nvic_irq_parse(struct rt_pic *pic,
                               struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
{
    if (args->args_count != 2 || args->args[0] >= pic->irq_nr)
    {
        return -RT_EINVAL;
    }

    out_pirq->hwirq = args->args[0];
    out_pirq->mode = args->args[1];

    return RT_EOK;
}

static const struct rt_pic_ops nvic_ops = {
    .name = "NVIC",
    .irq_enable = nvic_irq_unmask,
    .irq_disable = nvic_irq_mask,
    .irq_mask = nvic_irq_mask,
    .irq_unmask = nvic_irq_unmask,
    .irq_set_priority = nvic_irq_set_priority,
    .irq_set_state = nvic_irq_set_state,
    .irq_get_state = nvic_irq_get_state,
    .irq_map = nvic_irq_map,
    .irq_parse = nvic_irq_parse,
};

static rt_bool_t nvic_handler(void *data)
{
    int hwirq;
    struct rt_pic_irq *pirq;
    struct arm_nvic *nvic = data;
    rt_uint32_t exception = HWREG32(NVIC_ICSR_ADDR) &
                            NVIC_ICSR_VECTACTIVE_MASK;

    if (exception < 16)
    {
        return RT_FALSE;
    }

    hwirq = exception - 16;
    if (hwirq >= nvic->irq_nr)
    {
        return RT_FALSE;
    }

    pirq = rt_pic_find_irq(&nvic->parent, hwirq);
    if (pirq->irq < 0)
    {
        return RT_FALSE;
    }

    rt_pic_handle_isr(pirq);

    return RT_TRUE;
}

static rt_err_t nvic_ofw_init(struct rt_ofw_node *np,
                              const struct rt_ofw_node_id *id)
{
    rt_err_t err;
    rt_uint32_t value;
    rt_uint64_t reg, reg_size;
    rt_uint32_t hw_irq_nr;

    RT_UNUSED(id);

    if (_nvic.parent.ops)
    {
        return -RT_EBUSY;
    }

    if ((err = rt_ofw_get_address(np, 0, &reg, &reg_size)))
    {
        return err;
    }

    if (reg_size < NVIC_IPR_OFFSET + 1)
    {
        return -RT_EINVAL;
    }

    hw_irq_nr = ((HWREG32(NVIC_ICTR_ADDR) & 0xf) + 1) * 32;
    if (!rt_ofw_prop_read_u32(np, "arm,num-irqs", &value))
    {
        if (!value || value > hw_irq_nr)
        {
            return -RT_EINVAL;
        }
        hw_irq_nr = value;
    }

    _nvic.priority_bits = 4;
    if (!rt_ofw_prop_read_u32(np, "arm,num-irq-priority-bits", &value))
    {
        if (!value || value > 8)
        {
            return -RT_EINVAL;
        }
        _nvic.priority_bits = value;
    }

    _nvic.base = (rt_ubase_t)reg;
    _nvic.irq_nr = hw_irq_nr;
    _nvic.parent.priv_data = &_nvic;
    _nvic.parent.ops = &nvic_ops;

    if ((err = rt_pic_linear_irq(&_nvic.parent, _nvic.irq_nr)))
    {
        _nvic.parent.ops = RT_NULL;
        return err;
    }

    rt_pic_add_traps(nvic_handler, &_nvic);

    rt_ofw_data(np) = &_nvic.parent;
    rt_pic_user_extends(&_nvic.parent);

    return RT_EOK;
}

static const struct rt_ofw_node_id nvic_ofw_ids[] = {
    { .compatible = "arm,v7m-nvic" },
    { .compatible = "arm,v8m-nvic" },
    { /* sentinel */ }
};
RT_PIC_OFW_DECLARE(arm_nvic, nvic_ofw_ids, nvic_ofw_init);
