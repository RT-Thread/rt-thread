/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-31     RTT          the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "drv.ra.extirq"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/core/dm.h>
#include <drivers/ofw.h>
#include <drivers/ofw_irq.h>
#include <drivers/pic.h>
#include <drivers/platform.h>

#include <hal_data.h>

#include "drv_external_irq.h"

#ifdef R_ICU_H
#define RA_EXTERNAL_IRQ_MAX_CHANNELS 32

struct ra_external_irq
{
    struct rt_pic parent;
    const external_irq_instance_t *fsp;
    external_irq_cfg_t cfg;
    int irq;
    rt_uint8_t channel;
    rt_uint8_t owner_port;
    rt_uint8_t owner_pin;
    rt_bool_t acquired;
    rt_bool_t opened;
    rt_bool_t enabled;
};

static struct ra_external_irq *ra_external_irqs[RA_EXTERNAL_IRQ_MAX_CHANNELS];

#define RA_EXTERNAL_IRQ_INSTANCE(_channel) \
    [_channel] = &g_external_irq##_channel

static const external_irq_instance_t * const
    ra_external_irq_instances[RA_EXTERNAL_IRQ_MAX_CHANNELS] = {
#if defined(VECTOR_NUMBER_ICU_IRQ0) || defined(VECTOR_NUMBER_IRQ0)
        RA_EXTERNAL_IRQ_INSTANCE(0),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ1) || defined(VECTOR_NUMBER_IRQ1)
        RA_EXTERNAL_IRQ_INSTANCE(1),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ2) || defined(VECTOR_NUMBER_IRQ2)
        RA_EXTERNAL_IRQ_INSTANCE(2),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ3) || defined(VECTOR_NUMBER_IRQ3)
        RA_EXTERNAL_IRQ_INSTANCE(3),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ4) || defined(VECTOR_NUMBER_IRQ4)
        RA_EXTERNAL_IRQ_INSTANCE(4),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ5) || defined(VECTOR_NUMBER_IRQ5)
        RA_EXTERNAL_IRQ_INSTANCE(5),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ6) || defined(VECTOR_NUMBER_IRQ6)
        RA_EXTERNAL_IRQ_INSTANCE(6),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ7) || defined(VECTOR_NUMBER_IRQ7)
        RA_EXTERNAL_IRQ_INSTANCE(7),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ8) || defined(VECTOR_NUMBER_IRQ8)
        RA_EXTERNAL_IRQ_INSTANCE(8),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ9) || defined(VECTOR_NUMBER_IRQ9)
        RA_EXTERNAL_IRQ_INSTANCE(9),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ10) || defined(VECTOR_NUMBER_IRQ10)
        RA_EXTERNAL_IRQ_INSTANCE(10),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ11) || defined(VECTOR_NUMBER_IRQ11)
        RA_EXTERNAL_IRQ_INSTANCE(11),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ12) || defined(VECTOR_NUMBER_IRQ12)
        RA_EXTERNAL_IRQ_INSTANCE(12),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ13) || defined(VECTOR_NUMBER_IRQ13)
        RA_EXTERNAL_IRQ_INSTANCE(13),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ14) || defined(VECTOR_NUMBER_IRQ14)
        RA_EXTERNAL_IRQ_INSTANCE(14),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ15) || defined(VECTOR_NUMBER_IRQ15)
        RA_EXTERNAL_IRQ_INSTANCE(15),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ16) || defined(VECTOR_NUMBER_IRQ16)
        RA_EXTERNAL_IRQ_INSTANCE(16),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ17) || defined(VECTOR_NUMBER_IRQ17)
        RA_EXTERNAL_IRQ_INSTANCE(17),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ18) || defined(VECTOR_NUMBER_IRQ18)
        RA_EXTERNAL_IRQ_INSTANCE(18),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ19) || defined(VECTOR_NUMBER_IRQ19)
        RA_EXTERNAL_IRQ_INSTANCE(19),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ20) || defined(VECTOR_NUMBER_IRQ20)
        RA_EXTERNAL_IRQ_INSTANCE(20),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ21) || defined(VECTOR_NUMBER_IRQ21)
        RA_EXTERNAL_IRQ_INSTANCE(21),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ22) || defined(VECTOR_NUMBER_IRQ22)
        RA_EXTERNAL_IRQ_INSTANCE(22),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ23) || defined(VECTOR_NUMBER_IRQ23)
        RA_EXTERNAL_IRQ_INSTANCE(23),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ24) || defined(VECTOR_NUMBER_IRQ24)
        RA_EXTERNAL_IRQ_INSTANCE(24),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ25) || defined(VECTOR_NUMBER_IRQ25)
        RA_EXTERNAL_IRQ_INSTANCE(25),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ26) || defined(VECTOR_NUMBER_IRQ26)
        RA_EXTERNAL_IRQ_INSTANCE(26),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ27) || defined(VECTOR_NUMBER_IRQ27)
        RA_EXTERNAL_IRQ_INSTANCE(27),
#endif
#if defined(VECTOR_NUMBER_ICU_IRQ28) || defined(VECTOR_NUMBER_IRQ28)
        RA_EXTERNAL_IRQ_INSTANCE(28),
#endif
    };

#undef RA_EXTERNAL_IRQ_INSTANCE

static const external_irq_instance_t *ra_external_irq_instance_get(
    rt_uint32_t channel)
{
    if (channel < RT_ARRAY_SIZE(ra_external_irq_instances))
    {
        return ra_external_irq_instances[channel];
    }

    return RT_NULL;
}

static rt_err_t ra_external_irq_mode_to_fsp(rt_uint8_t mode,
                                            external_irq_trigger_t *trigger)
{
    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
        *trigger = EXTERNAL_IRQ_TRIG_RISING;
        break;

    case PIN_IRQ_MODE_FALLING:
        *trigger = EXTERNAL_IRQ_TRIG_FALLING;
        break;

    case PIN_IRQ_MODE_RISING_FALLING:
        *trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE;
        break;

    case PIN_IRQ_MODE_LOW_LEVEL:
        *trigger = EXTERNAL_IRQ_TRIG_LEVEL_LOW;
        break;

    case PIN_IRQ_MODE_HIGH_LEVEL:
        *trigger = EXTERNAL_IRQ_TRIG_LEVEL_HIGH;
        break;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t ra_external_irq_trigger_from_ofw(const char *name,
                                                 external_irq_trigger_t *trigger)
{
    if (!rt_strcmp(name, "falling"))
    {
        *trigger = EXTERNAL_IRQ_TRIG_FALLING;
    }
    else if (!rt_strcmp(name, "rising"))
    {
        *trigger = EXTERNAL_IRQ_TRIG_RISING;
    }
    else if (!rt_strcmp(name, "both-edges"))
    {
        *trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE;
    }
    else if (!rt_strcmp(name, "low-level"))
    {
        *trigger = EXTERNAL_IRQ_TRIG_LEVEL_LOW;
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t ra_external_irq_clock_div_from_ofw(rt_uint32_t value,
                                                   external_irq_clock_source_div_t *clock_div)
{
    switch (value)
    {
    case 1:
        *clock_div = EXTERNAL_IRQ_CLOCK_SOURCE_DIV_1;
        break;

    case 8:
        *clock_div = EXTERNAL_IRQ_CLOCK_SOURCE_DIV_8;
        break;

    case 32:
        *clock_div = EXTERNAL_IRQ_CLOCK_SOURCE_DIV_32;
        break;

    case 64:
        *clock_div = EXTERNAL_IRQ_CLOCK_SOURCE_DIV_64;
        break;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_bool_t ra_external_irq_owner_is(struct ra_external_irq *external_irq,
                                          rt_uint8_t port, rt_uint8_t pin)
{
    return external_irq->acquired && external_irq->owner_port == port &&
           external_irq->owner_pin == pin;
}

struct ra_external_irq *ra_external_irq_get(struct rt_ofw_node *np)
{
    if (!np)
    {
        return RT_NULL;
    }

    if (!rt_ofw_data(np))
    {
        rt_platform_ofw_request(np);
    }

    return rt_ofw_data(np);
}

int ra_external_irq_acquire(struct ra_external_irq *external_irq,
                            rt_uint8_t port, rt_uint8_t pin, rt_uint8_t mode)
{
    rt_err_t err;
    fsp_err_t fsp_err;
    external_irq_trigger_t trigger;

    if (!external_irq ||
        (err = ra_external_irq_mode_to_fsp(mode, &trigger)))
    {
        return external_irq ? err : -RT_EINVAL;
    }

    if (external_irq->acquired)
    {
        if (!ra_external_irq_owner_is(external_irq, port, pin) ||
            external_irq->cfg.trigger != trigger)
        {
            return -RT_EBUSY;
        }

        return external_irq->irq;
    }

    external_irq->cfg = *external_irq->fsp->p_cfg;
    external_irq->cfg.trigger = trigger;
    external_irq->cfg.p_callback = irq_callback;
    external_irq->cfg.p_context = external_irq;

    fsp_err = external_irq->fsp->p_api->open(external_irq->fsp->p_ctrl,
                                             &external_irq->cfg);
    if (fsp_err != FSP_SUCCESS)
    {
        LOG_E("IRQ%u open failed: %d", external_irq->channel, fsp_err);
        return -RT_EIO;
    }

    external_irq->owner_port = port;
    external_irq->owner_pin = pin;
    external_irq->opened = RT_TRUE;
    external_irq->acquired = RT_TRUE;

    return external_irq->irq;
}

rt_err_t ra_external_irq_enable(struct ra_external_irq *external_irq,
                                rt_uint8_t port, rt_uint8_t pin)
{
    fsp_err_t fsp_err;

    if (!external_irq || !ra_external_irq_owner_is(external_irq, port, pin) ||
        !external_irq->opened)
    {
        return -RT_EINVAL;
    }

    if (external_irq->enabled)
    {
        return RT_EOK;
    }

    fsp_err = external_irq->fsp->p_api->enable(external_irq->fsp->p_ctrl);
    if (fsp_err != FSP_SUCCESS)
    {
        LOG_E("IRQ%u enable failed: %d", external_irq->channel, fsp_err);
        return -RT_EIO;
    }

    external_irq->enabled = RT_TRUE;

    return RT_EOK;
}

rt_err_t ra_external_irq_disable(struct ra_external_irq *external_irq,
                                 rt_uint8_t port, rt_uint8_t pin)
{
    fsp_err_t fsp_err;

    if (!external_irq || !ra_external_irq_owner_is(external_irq, port, pin))
    {
        return -RT_EINVAL;
    }

    if (!external_irq->enabled)
    {
        return RT_EOK;
    }

    fsp_err = external_irq->fsp->p_api->disable(external_irq->fsp->p_ctrl);
    if (fsp_err != FSP_SUCCESS)
    {
        LOG_E("IRQ%u disable failed: %d", external_irq->channel, fsp_err);
        return -RT_EIO;
    }

    external_irq->enabled = RT_FALSE;

    return RT_EOK;
}

rt_err_t ra_external_irq_release(struct ra_external_irq *external_irq,
                                 rt_uint8_t port, rt_uint8_t pin)
{
    rt_err_t err;
    fsp_err_t fsp_err;

    if (!external_irq || !ra_external_irq_owner_is(external_irq, port, pin))
    {
        return -RT_EINVAL;
    }

    if ((err = ra_external_irq_disable(external_irq, port, pin)))
    {
        return err;
    }

    if (external_irq->opened)
    {
        fsp_err = external_irq->fsp->p_api->close(external_irq->fsp->p_ctrl);
        if (fsp_err != FSP_SUCCESS)
        {
            LOG_E("IRQ%u close failed: %d", external_irq->channel, fsp_err);
            return -RT_EIO;
        }
    }

    external_irq->opened = RT_FALSE;
    external_irq->acquired = RT_FALSE;
    external_irq->owner_port = 0;
    external_irq->owner_pin = 0;

    return RT_EOK;
}

void irq_callback(external_irq_callback_args_t *args)
{
    struct ra_external_irq *external_irq;
    struct rt_pic_irq *pirq;

    if (!args || args->channel >= RA_EXTERNAL_IRQ_MAX_CHANNELS ||
        !(external_irq = ra_external_irqs[args->channel]) ||
        !external_irq->enabled)
    {
        return;
    }

    pirq = rt_pic_find_irq(&external_irq->parent, 0);
    if (pirq->irq >= 0)
    {
        rt_interrupt_enter();
        rt_pic_handle_isr(pirq);
        rt_interrupt_leave();
    }
}

static const struct rt_pic_ops ra_external_irq_pic_ops = {
    .name = "RA-External-IRQ",
};

static rt_err_t ra_external_irq_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *trigger_name;
    rt_uint32_t channel, clock_div;
    struct rt_ofw_cell_args irq_args = { 0 };
    struct rt_device *dev = &pdev->parent;
    struct ra_external_irq *external_irq;
    external_irq_trigger_t trigger;
    external_irq_clock_source_div_t clock_source_div;

    if ((err = rt_ofw_prop_read_u32(dev->ofw_node, "channel", &channel)))
    {
        return err;
    }
    if (channel >= RA_EXTERNAL_IRQ_MAX_CHANNELS)
    {
        return -RT_EINVAL;
    }

    external_irq = rt_calloc(1, sizeof(*external_irq));
    if (!external_irq)
    {
        return -RT_ENOMEM;
    }

    external_irq->fsp = ra_external_irq_instance_get(channel);
    if (!external_irq->fsp || external_irq->fsp->p_cfg->channel != channel ||
        external_irq->fsp->p_cfg->p_callback != irq_callback)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if ((err = rt_ofw_prop_read_string(dev->ofw_node, "renesas,trigger",
                                       &trigger_name)) ||
        (err = ra_external_irq_trigger_from_ofw(trigger_name, &trigger)) ||
        trigger != external_irq->fsp->p_cfg->trigger)
    {
        err = err ? err : -RT_EINVAL;
        goto _fail;
    }

    clock_div = 1;
    rt_ofw_prop_read_u32(dev->ofw_node, "renesas,sample-clock-div",
                         &clock_div);
    if ((err = ra_external_irq_clock_div_from_ofw(clock_div,
                                                  &clock_source_div)) ||
        clock_source_div != external_irq->fsp->p_cfg->clock_source_div ||
        rt_ofw_prop_read_bool(dev->ofw_node, "renesas,digital-filtering") !=
            external_irq->fsp->p_cfg->filter_enable)
    {
        err = err ? err : -RT_EINVAL;
        goto _fail;
    }

    if ((err = rt_ofw_parse_irq_cells(dev->ofw_node, 0, &irq_args)))
    {
        goto _fail;
    }
    if (irq_args.args_count != 2 ||
        irq_args.args[0] != (rt_uint32_t)external_irq->fsp->p_cfg->irq ||
        irq_args.args[1] != external_irq->fsp->p_cfg->ipl)
    {
        err = -RT_EINVAL;
        goto _put_irq_node;
    }

    external_irq->channel = channel;
    external_irq->parent.ops = &ra_external_irq_pic_ops;
    external_irq->parent.priv_data = external_irq;
    if ((err = rt_pic_linear_irq(&external_irq->parent, 1)))
    {
        goto _put_irq_node;
    }

    external_irq->irq = rt_pic_config_irq(&external_irq->parent, 0, channel);
    if (external_irq->irq < 0)
    {
        err = external_irq->irq;
        rt_pic_cancel_irq(&external_irq->parent);
        goto _put_irq_node;
    }

    rt_pic_user_extends(&external_irq->parent);
    ra_external_irqs[channel] = external_irq;
    rt_dm_dev_bind_fwdata(dev, RT_NULL, external_irq);
    pdev->priv = external_irq;
    rt_ofw_node_put(irq_args.data);

    return RT_EOK;

_put_irq_node:
    rt_ofw_node_put(irq_args.data);
_fail:
    rt_free(external_irq);

    return err;
}

static const struct rt_ofw_node_id ra_external_irq_ofw_ids[] = {
    { .compatible = "renesas,ra-external-interrupt" },
    { /* sentinel */ }
};

static struct rt_platform_driver ra_external_irq_driver = {
    .name = "ra-external-interrupt",
    .ids = ra_external_irq_ofw_ids,
    .probe = ra_external_irq_probe,
};
RT_PLATFORM_DRIVER_EXPORT(ra_external_irq_driver);
#else
struct ra_external_irq *ra_external_irq_get(struct rt_ofw_node *np)
{
    RT_UNUSED(np);

    return RT_NULL;
}

int ra_external_irq_acquire(struct ra_external_irq *external_irq,
                            rt_uint8_t port, rt_uint8_t pin, rt_uint8_t mode)
{
    RT_UNUSED(external_irq);
    RT_UNUSED(port);
    RT_UNUSED(pin);
    RT_UNUSED(mode);

    return -RT_ENOSYS;
}

rt_err_t ra_external_irq_enable(struct ra_external_irq *external_irq,
                                rt_uint8_t port, rt_uint8_t pin)
{
    RT_UNUSED(external_irq);
    RT_UNUSED(port);
    RT_UNUSED(pin);

    return -RT_ENOSYS;
}

rt_err_t ra_external_irq_disable(struct ra_external_irq *external_irq,
                                 rt_uint8_t port, rt_uint8_t pin)
{
    RT_UNUSED(external_irq);
    RT_UNUSED(port);
    RT_UNUSED(pin);

    return -RT_ENOSYS;
}

rt_err_t ra_external_irq_release(struct ra_external_irq *external_irq,
                                 rt_uint8_t port, rt_uint8_t pin)
{
    RT_UNUSED(external_irq);
    RT_UNUSED(port);
    RT_UNUSED(pin);

    return -RT_ENOSYS;
}
#endif /* R_ICU_H */
