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
#include <rtdevice.h>

#define DBG_TAG "drv.exti"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/pic.h>
#include <drivers/ofw_irq.h>

#include "drv_exti.h"

#define STM32_EXTI_LINE_NR  16
#define STM32_EXTI_GROUP_NR 16

#if defined(SOC_SERIES_STM32H7)
#define STM32_EXTI_IMR  (EXTI->IMR1)
#define STM32_EXTI_RTSR (EXTI->RTSR1)
#define STM32_EXTI_FTSR (EXTI->FTSR1)
#else
#define STM32_EXTI_IMR  (EXTI->IMR)
#define STM32_EXTI_RTSR (EXTI->RTSR)
#define STM32_EXTI_FTSR (EXTI->FTSR)
#endif

struct stm32_exti_group
{
    struct stm32_exti *exti;
    int parent_irq;
    rt_uint32_t line_mask;
    char name[RT_NAME_MAX];
};

struct stm32_exti
{
    struct rt_pic parent;
    struct rt_spinlock lock;
    GPIO_TypeDef *owners[STM32_EXTI_LINE_NR];
    struct stm32_exti_group groups[STM32_EXTI_GROUP_NR];
    rt_uint8_t group_nr;
};

static struct stm32_exti _exti;

static rt_uint32_t exti_line_mask(int line)
{
    return RT_BIT(line);
}

static void exti_irq_mask(struct rt_pic_irq *pirq)
{
    STM32_EXTI_IMR &= ~exti_line_mask(pirq->hwirq);
}

static void exti_irq_unmask(struct rt_pic_irq *pirq)
{
    STM32_EXTI_IMR |= exti_line_mask(pirq->hwirq);
}

static void exti_irq_ack(struct rt_pic_irq *pirq)
{
    __HAL_GPIO_EXTI_CLEAR_IT(exti_line_mask(pirq->hwirq));
}

static rt_err_t exti_irq_set_trigger(struct rt_pic_irq *pirq, rt_uint32_t mode)
{
    rt_uint32_t mask = exti_line_mask(pirq->hwirq);

    switch (mode)
    {
    case RT_IRQ_MODE_EDGE_RISING:
        STM32_EXTI_RTSR |= mask;
        STM32_EXTI_FTSR &= ~mask;
        break;

    case RT_IRQ_MODE_EDGE_FALLING:
        STM32_EXTI_RTSR &= ~mask;
        STM32_EXTI_FTSR |= mask;
        break;

    case RT_IRQ_MODE_EDGE_BOTH:
        STM32_EXTI_RTSR |= mask;
        STM32_EXTI_FTSR |= mask;
        break;

    default:
        return -RT_ENOSYS;
    }

    pirq->mode = mode;

    return RT_EOK;
}

static int exti_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
{
    int irq;
    struct rt_pic_irq *pirq;

    if (hwirq < 0 || hwirq >= STM32_EXTI_LINE_NR)
    {
        return -RT_EINVAL;
    }

    pirq = rt_pic_find_irq(pic, hwirq);
    irq = rt_pic_config_irq(pic, hwirq, hwirq);

    if (irq >= 0 && mode != RT_IRQ_MODE_NONE)
    {
        if (exti_irq_set_trigger(pirq, mode))
        {
            irq = -RT_EINVAL;
        }
    }

    return irq;
}

static rt_err_t exti_irq_parse(struct rt_pic *pic,
                               struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
{
    if (args->args_count != 1 || args->args[0] >= pic->irq_nr)
    {
        return -RT_EINVAL;
    }

    out_pirq->hwirq = args->args[0];
    out_pirq->mode = RT_IRQ_MODE_NONE;

    return RT_EOK;
}

static const struct rt_pic_ops exti_ops = {
    .name = "STM32-EXTI",
    .irq_enable = exti_irq_unmask,
    .irq_disable = exti_irq_mask,
    .irq_ack = exti_irq_ack,
    .irq_mask = exti_irq_mask,
    .irq_unmask = exti_irq_unmask,
    .irq_set_triger_mode = exti_irq_set_trigger,
    .irq_map = exti_irq_map,
    .irq_parse = exti_irq_parse,
};

static void exti_parent_isr(int vector, void *param)
{
    struct stm32_exti_group *group = param;
    struct stm32_exti *exti = group->exti;
    rt_uint32_t pending = STM32_EXTI_IMR &
                          __HAL_GPIO_EXTI_GET_IT(group->line_mask);

    RT_UNUSED(vector);

    while (pending)
    {
        int line = __rt_ffs(pending) - 1;
        rt_uint32_t mask = exti_line_mask(line);
        struct rt_pic_irq *pirq = rt_pic_find_irq(&exti->parent, line);

        pending &= ~mask;
        __HAL_GPIO_EXTI_CLEAR_IT(mask);
        if (pirq->irq >= 0)
        {
            rt_pic_handle_isr(pirq);
        }
    }
}

struct stm32_exti *stm32_exti_get(struct rt_ofw_node *np)
{
    struct rt_pic *pic;

    if (!np || !(pic = rt_pic_dynamic_cast(rt_ofw_data(np))) || pic != &_exti.parent)
    {
        return RT_NULL;
    }

    return &_exti;
}

int stm32_exti_acquire(struct stm32_exti *exti, GPIO_TypeDef *gpio,
                       rt_base_t pin, rt_uint32_t irq_mode)
{
    int irq;
    rt_ubase_t level;

    if (!exti || !gpio || pin < 0 || pin >= STM32_EXTI_LINE_NR)
    {
        return -RT_EINVAL;
    }

    if (irq_mode != RT_IRQ_MODE_EDGE_RISING &&
        irq_mode != RT_IRQ_MODE_EDGE_FALLING &&
        irq_mode != RT_IRQ_MODE_EDGE_BOTH)
    {
        return -RT_ENOSYS;
    }

    level = rt_spin_lock_irqsave(&exti->lock);
    if (exti->owners[pin] && exti->owners[pin] != gpio)
    {
        rt_spin_unlock_irqrestore(&exti->lock, level);
        return -RT_EBUSY;
    }
    exti->owners[pin] = gpio;
    rt_spin_unlock_irqrestore(&exti->lock, level);

    __HAL_RCC_SYSCFG_CLK_ENABLE();
    irq = exti_irq_map(&exti->parent, pin, irq_mode);
    if (irq < 0)
    {
        level = rt_spin_lock_irqsave(&exti->lock);
        exti->owners[pin] = RT_NULL;
        rt_spin_unlock_irqrestore(&exti->lock, level);
    }

    return irq;
}

rt_err_t stm32_exti_release(struct stm32_exti *exti, GPIO_TypeDef *gpio,
                            rt_base_t pin)
{
    rt_ubase_t level;

    if (!exti || !gpio || pin < 0 || pin >= STM32_EXTI_LINE_NR)
    {
        return -RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(&exti->lock);
    if (exti->owners[pin] != gpio)
    {
        rt_spin_unlock_irqrestore(&exti->lock, level);
        return -RT_EINVAL;
    }
    exti->owners[pin] = RT_NULL;
    rt_spin_unlock_irqrestore(&exti->lock, level);

    exti_irq_mask(rt_pic_find_irq(&exti->parent, pin));

    return RT_EOK;
}

static void exti_init_fail(struct stm32_exti *exti)
{
    for (int i = 0; i < exti->group_nr; ++i)
    {
        struct stm32_exti_group *group = &exti->groups[i];

        if (group->parent_irq >= 0)
        {
            rt_pic_irq_mask(group->parent_irq);
            rt_pic_detach_irq(group->parent_irq, group);
        }
    }

    if (exti->parent.pirqs)
    {
        rt_pic_cancel_irq(&exti->parent);
    }
}

static rt_err_t exti_ofw_init(struct rt_ofw_node *np,
                              const struct rt_ofw_node_id *id)
{
    int irq_count, range_cells;
    rt_err_t err = RT_EOK;
    rt_uint32_t covered = 0;
    struct stm32_exti *exti = &_exti;

    RT_UNUSED(id);

    if (exti->parent.ops)
    {
        return -RT_EBUSY;
    }

    irq_count = rt_ofw_get_irq_count(np);
    range_cells = rt_ofw_prop_count_of_u32(np, "line-ranges");
    if (irq_count <= 0 || irq_count > STM32_EXTI_GROUP_NR ||
        range_cells != irq_count * 2)
    {
        return -RT_EINVAL;
    }

    exti->parent.priv_data = exti;
    exti->parent.ops = &exti_ops;
    rt_spin_lock_init(&exti->lock);

    if ((err = rt_pic_linear_irq(&exti->parent, STM32_EXTI_LINE_NR)))
    {
        exti->parent.ops = RT_NULL;
        return err;
    }

    for (int i = 0; i < irq_count; ++i)
    {
        rt_uint32_t start, count, range_mask;
        struct stm32_exti_group *group = &exti->groups[i];

        if (rt_ofw_prop_read_u32_index(np, "line-ranges", i * 2, &start) ||
            rt_ofw_prop_read_u32_index(np, "line-ranges", i * 2 + 1, &count) ||
            !count || start >= STM32_EXTI_LINE_NR ||
            count > STM32_EXTI_LINE_NR - start)
        {
            err = -RT_EINVAL;
            break;
        }

        range_mask = ((RT_BIT(count) - 1) << start);
        if (covered & range_mask)
        {
            err = -RT_EINVAL;
            break;
        }
        covered |= range_mask;

        group->exti = exti;
        group->line_mask = range_mask;
        group->parent_irq = rt_ofw_get_irq(np, i);
        rt_snprintf(group->name, sizeof(group->name), "exti%d", i);

        if (group->parent_irq < 0 ||
            (err = rt_pic_attach_irq(group->parent_irq, exti_parent_isr,
                                     group, group->name, RT_IRQ_F_NONE)))
        {
            if (group->parent_irq < 0)
            {
                err = group->parent_irq;
            }
            break;
        }
        ++exti->group_nr;

        for (int line = start; line < start + count; ++line)
        {
            int child_irq = rt_pic_config_irq(&exti->parent, line, line);

            /* Shared EXTI vectors must dispatch only lines with pending bits. */
            if (child_irq < 0)
            {
                err = child_irq;
                break;
            }
        }

        if (err)
        {
            break;
        }
    }

    if (!err && covered != (RT_BIT(STM32_EXTI_LINE_NR) - 1))
    {
        err = -RT_EINVAL;
    }

    if (err)
    {
        exti_init_fail(exti);
        exti->parent.ops = RT_NULL;
        return err;
    }

    rt_ofw_data(np) = &exti->parent;
    rt_pic_user_extends(&exti->parent);

    for (int i = 0; i < exti->group_nr; ++i)
    {
        rt_pic_irq_unmask(exti->groups[i].parent_irq);
    }

    return RT_EOK;
}

static const struct rt_ofw_node_id exti_ofw_ids[] = {
    { .compatible = "st,stm32-exti" },
    { /* sentinel */ }
};
RT_PIC_OFW_DECLARE(stm32_exti, exti_ofw_ids, exti_ofw_init);

void EXTI0_IRQHandler(void)
{
    rt_pic_do_traps();
}

void EXTI1_IRQHandler(void)
{
    rt_pic_do_traps();
}

void EXTI2_IRQHandler(void)
{
    rt_pic_do_traps();
}

void EXTI3_IRQHandler(void)
{
    rt_pic_do_traps();
}

void EXTI4_IRQHandler(void)
{
    rt_pic_do_traps();
}

void EXTI9_5_IRQHandler(void)
{
    rt_pic_do_traps();
}

void EXTI15_10_IRQHandler(void)
{
    rt_pic_do_traps();
}
