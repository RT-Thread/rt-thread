/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pwm.pxa"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define PWMCR       0x00
#define PWMDCR      0x04
#define PWMPCR      0x08

#define PWMCR_SD    RT_BIT(6)
#define PWMDCR_FD   RT_BIT(10)

struct pxa_pwm
{
    struct rt_device_pwm parent;

    void *regs;
    struct rt_clk *clk;
    struct rt_reset_control *rstc;

    int dcr_fd; /* Controller PWM_DCR FD feature */
    int rcpu_pwm; /* PWM in rcpu domain */
    rt_bool_t enabled;

#define QUIRK_HAS_SECONDARY_PWM 0
#define QUIRK_HAS_PWM_DCR_FD    1
    rt_bitmap_t quirks;
};

#define raw_to_pxa_pwm(raw) rt_container_of(raw, struct pxa_pwm, parent)

static rt_err_t pxa_pwm_toggle(struct pxa_pwm *pc, rt_bool_t enabled)
{
    rt_err_t err = RT_EOK;

    if (pc->enabled == enabled)
    {
        return err;
    }

    if (pc->enabled)
    {
        rt_clk_disable_unprepare(pc->clk);
    }
    else
    {
        err = rt_clk_prepare_enable(pc->clk);
    }

    pc->enabled = enabled;

    return err;
}

static rt_err_t pxa_pwm_apply(struct pxa_pwm *pc, struct rt_pwm_configuration *pwm_cfg)
{
    rt_err_t err;
    rt_bool_t enabled;
    rt_uint32_t offset;
    rt_uint64_t clk, duty_ns, period_ns;
    rt_ubase_t period_cycles, prescale, pv, dc;

    if (pwm_cfg->complementary)
    {
        return -RT_EINVAL;
    }

    enabled = pc->enabled;

    if ((err = pxa_pwm_toggle(pc, RT_FALSE)))
    {
        return err;
    }

    /*
     * period_ns = 10^9 * (PRESCALE + 1) * (PV + 1) / PWM_CLK_RATE
     * duty_ns   = 10^9 * (PRESCALE + 1) * DC / PWM_CLK_RATE
     */
    duty_ns = enabled ? pwm_cfg->pulse : 0;
    period_ns = pwm_cfg->period;
    offset = pwm_cfg->channel ? 0x10 : 0;

    clk = rt_clk_get_rate(pc->clk);
    clk *= period_ns;
    rt_do_div(clk, 1000000000);
    period_cycles = clk;

    if (period_cycles < 1)
    {
        period_cycles = 1;
    }
    prescale = (period_cycles - 1) / 1024;
    pv = period_cycles / (prescale + 1) - 1;

    if (prescale > 63)
    {
        err = -RT_EINVAL;
        goto _end;
    }

    if (duty_ns == period_ns)
    {
        if (pc->quirks & RT_BIT(QUIRK_HAS_PWM_DCR_FD))
        {
            if (pc->dcr_fd)
            {
                dc = PWMDCR_FD;
            }
            else
            {
                dc = (pv + 1) * duty_ns / period_ns;

                if (dc >= PWMDCR_FD)
                {
                    dc = PWMDCR_FD - 1;
                    pv = dc - 1;
                }
            }
        }
        else
        {
            dc = PWMDCR_FD;
        }
    }
    else
    {
        dc = ((rt_uint64_t)(pv + 1) * duty_ns) / period_ns;
    }

    if (pc->quirks & RT_BIT(QUIRK_HAS_PWM_DCR_FD))
    {
        prescale |= PWMCR_SD;
    }

    HWREG32(pc->regs + offset + PWMCR) = prescale | PWMCR_SD;
    HWREG32(pc->regs + offset + PWMDCR) = dc;
    HWREG32(pc->regs + offset + PWMPCR) = pv;

_end:
    if (pc->enabled != enabled)
    {
        err = pxa_pwm_toggle(pc, RT_TRUE);
    }

    return err;
}

static rt_err_t pxa_pwm_control(struct rt_device_pwm *pwm, int cmd, void *args)
{
    rt_err_t err;
    struct pxa_pwm *pc = raw_to_pxa_pwm(pwm);
    struct rt_pwm_configuration *pwm_cfg = args;

    if (pwm_cfg->channel > 0)
    {
        if (pwm_cfg->channel > 1 || !pc->quirks & RT_BIT(QUIRK_HAS_SECONDARY_PWM))
        {
            return -RT_EINVAL;
        }
    }

    /* RT_PWM framework have check args */
    switch (cmd)
    {
    case PWM_CMD_ENABLE:
    case PWM_CMD_DISABLE:
        err = pxa_pwm_toggle(pc, cmd == PWM_CMD_ENABLE);
        break;

    case PWM_CMD_SET:
    case PWM_CMD_SET_PERIOD:
    case PWM_CMD_SET_PULSE:
        err = pxa_pwm_apply(pc, pwm_cfg);
        break;

    case PWM_CMD_GET:
        err = -RT_ENOSYS;
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

const static struct rt_pwm_ops pxa_pwm_ops =
{
    .control = pxa_pwm_control,
};

static void pxa_pwm_free(struct pxa_pwm *pc)
{
    if (pc->regs)
    {
        rt_iounmap(pc->regs);
    }

    if (rt_is_err_or_null(pc->clk))
    {
        rt_clk_put(pc->clk);
    }

    if (rt_is_err_or_null(pc->rstc))
    {
        rt_reset_control_assert(pc->rstc);
        rt_reset_control_put(pc->rstc);
    }

    rt_free(pc);
}

static rt_err_t pxa_pwm_probe(struct rt_platform_device *pdev)
{
    int id;
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct pxa_pwm *pc = rt_calloc(1, sizeof(*pc));

    if (!pc)
    {
        return -RT_ENOMEM;
    }

    pc->quirks = pdev->id->data ? *(rt_ubase_t *)pdev->id->data : 0;

    if (pc->quirks & RT_BIT(QUIRK_HAS_PWM_DCR_FD))
    {
        pc->dcr_fd = rt_dm_dev_prop_read_bool(dev, "k1x,pwm-disable-fd") ? 0 : 1;
        pc->dcr_fd = rt_dm_dev_prop_read_bool(dev, "rcpu-pwm") ? 1 : 0;
    }

    pc->regs = rt_dm_dev_iomap(dev, 0);
    if (!pc->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    pc->clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(pc->clk))
    {
        err = rt_ptr_err(pc->clk);
        goto _fail;
    }

    pc->rstc = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(pc->rstc))
    {
        err = rt_ptr_err(pc->rstc);
        goto _fail;
    }
    rt_reset_control_deassert(pc->rstc);

    dev->user_data = pc;

    pc->parent.parent.ofw_node = dev->ofw_node;

    if ((id = pdev->dev_id) >= 0)
    {
        rt_dm_dev_set_name(&pc->parent.parent, "pwm%u", id);
    }
    else
    {
        rt_dm_dev_set_name_auto(&pc->parent.parent, "pwm");
    }

    rt_device_pwm_register(&pc->parent,
            rt_dm_dev_get_name(&pc->parent.parent), &pxa_pwm_ops, pc);

    rt_dm_dev_bind_fwdata(dev, RT_NULL, pc);

    return RT_EOK;

_fail:
    pxa_pwm_free(pc);

    return err;
}

static rt_err_t pxa_pwm_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct pxa_pwm *pc = dev->user_data;

    pxa_pwm_toggle(pc, RT_FALSE);

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);

    rt_device_unregister(&pc->parent.parent);

    pxa_pwm_free(pc);

    return RT_EOK;
}

static rt_bitmap_t has_secondary_pwm_quirk = RT_BIT(QUIRK_HAS_SECONDARY_PWM);
static rt_bitmap_t has_pwm_dcr_fd_quirk = RT_BIT(QUIRK_HAS_PWM_DCR_FD);

static const struct rt_ofw_node_id pxa_pwm_ofw_ids[] =
{
    { .compatible = "marvell,pxa250-pwm", },
    { .compatible = "marvell,pxa270-pwm", .data = &has_secondary_pwm_quirk },
    { .compatible = "marvell,pxa168-pwm", },
    { .compatible = "marvell,pxa910-pwm", },
    { .compatible = "spacemit,k1x-pwm", .data = &has_pwm_dcr_fd_quirk },
    { /* sentinel */ }
};

static struct rt_platform_driver pxa_pwm_driver =
{
    .name = "pxa-pwm",
    .ids = pxa_pwm_ofw_ids,

    .probe = pxa_pwm_probe,
    .remove = pxa_pwm_remove,
};
RT_PLATFORM_DRIVER_EXPORT(pxa_pwm_driver);
