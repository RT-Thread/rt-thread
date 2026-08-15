/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pwm.brcmstb"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define PWM_CTRL                0x00
#define     CTRL_START          RT_BIT(0)
#define     CTRL_OEB            RT_BIT(1)
#define     CTRL_FORCE_HIGH     RT_BIT(2)
#define     CTRL_OPENDRAIN      RT_BIT(3)
#define     CTRL_CHAN_OFFS      4

#define PWM_CTRL2               0x04
#define     CTRL2_OUT_SELECT    RT_BIT(0)

#define PWM_CH_SIZE             0x8

#define PWM_CWORD_MSB(ch)       (0x08 + ((ch) * PWM_CH_SIZE))
#define PWM_CWORD_LSB(ch)       (0x0c + ((ch) * PWM_CH_SIZE))

/* Number of bits for the CWORD value */
#define CWORD_BIT_SIZE          16

/*
 * Maximum control word value allowed when variable-frequency PWM is used as a
 * clock for the constant-frequency PMW.
 */
#define CONST_VAR_F_MAX         32768
#define CONST_VAR_F_MIN         1

#define PWM_ON(ch)              (0x18 + ((ch) * PWM_CH_SIZE))
#define     PWM_ON_MIN          1
#define PWM_PERIOD(ch)          (0x1c + ((ch) * PWM_CH_SIZE))
#define     PWM_PERIOD_MIN      0

#define PWM_ON_PERIOD_MAX       0xff

#define PWM_NUMBER              2

#define NSEC_PER_SEC            1000000000L

struct brcmstb_pwm
{
    struct rt_device_pwm parent;

    void *base;
    struct rt_clk *clk;
};

#define raw_to_brcmstb_pwm(raw) rt_container_of(raw, struct brcmstb_pwm, parent)

#ifndef mul_u64_u64_div_u64
static rt_uint64_t mul_u64_u64_div_u64(rt_uint64_t a, rt_uint64_t b, rt_uint64_t c)
{
    /* overflow in rt-thread is unlikely */
    return a * b / c;
}
#endif /* mul_u64_u64_div_u64 */

static rt_err_t brcmstb_pwm_enable(struct brcmstb_pwm *bpwm, int channel, rt_bool_t enable)
{
    rt_uint32_t shift, value;

    if (channel >= PWM_NUMBER)
    {
        return -RT_EINVAL;
    }

    shift = channel * CTRL_CHAN_OFFS;
    value = HWREG32(bpwm->base + PWM_CTRL);

    if (enable)
    {
        value &= ~(CTRL_OEB << shift);
        value |= (CTRL_START | CTRL_OPENDRAIN) << shift;
    }
    else
    {
        value &= ~((CTRL_START | CTRL_OPENDRAIN) << shift);
        value |= CTRL_OEB << shift;
    }

    HWREG32(bpwm->base + PWM_CTRL) = value;

    return RT_EOK;
}

/*
 * Fv is derived from the variable frequency output. The variable frequency
 * output is configured using this formula:
 *
 * W = cword, if cword < 2 ^ 15 else 16-bit 2's complement of cword
 *
 * Fv = W x 2 ^ -16 x 27Mhz (reference clock)
 *
 * The period is: (period + 1) / Fv and "on" time is on / (period + 1)
 *
 * The PWM core framework specifies that the "duty_ns" parameter is in fact the
 * "on" time, so this translates directly into our HW programming here.
 */
static rt_err_t brcmstb_pwm_config(struct brcmstb_pwm *bpwm,
        struct rt_pwm_configuration *pwm_cfg)
{
    rt_ubase_t pc, dc, cword = CONST_VAR_F_MAX;
    rt_uint32_t value, channel, period_ns, duty_ns;

    channel = pwm_cfg->channel;
    period_ns = pwm_cfg->period;
    duty_ns = pwm_cfg->pulse;

    /*
     * If asking for a duty_ns equal to period_ns, we need to substract
     * the period value by 1 to make it shorter than the "on" time and
     * produce a flat 100% duty cycle signal, and max out the "on" time
     */
    if (duty_ns == period_ns)
    {
        dc = PWM_ON_PERIOD_MAX;
        pc = PWM_ON_PERIOD_MAX - 1;
        goto _done;
    }

    while (RT_TRUE)
    {
        rt_uint64_t rate;

        /* Calculate the base rate from base frequency and current cword */
        rate = (rt_uint64_t)rt_clk_get_rate(bpwm->clk) * (rt_uint64_t)cword;
        rate >>= CWORD_BIT_SIZE;

        pc = mul_u64_u64_div_u64(period_ns, rate, NSEC_PER_SEC);
        dc = mul_u64_u64_div_u64(duty_ns + 1, rate, NSEC_PER_SEC);

        /*
         * We can be called with separate duty and period updates,
         * so do not reject dc == 0 right away
         */
        if (pc == PWM_PERIOD_MIN || (dc < PWM_ON_MIN && duty_ns))
        {
            return -RT_EINVAL;
        }

        /* We converged on a calculation */
        if (pc <= PWM_ON_PERIOD_MAX && dc <= PWM_ON_PERIOD_MAX)
        {
            break;
        }

        /*
         * The cword needs to be a power of 2 for the variable
         * frequency generator to output a 50% duty cycle variable
         * frequency which is used as input clock to the fixed
         * frequency generator.
         */
        cword >>= 1;

        /* Desired periods are too large, we do not have a divider for them */
        if (cword < CONST_VAR_F_MIN)
        {
            return -RT_EINVAL;
        }
    }

_done:
    /*
     * Configure the defined "cword" value to have the variable frequency
     * generator output a base frequency for the constant frequency
     * generator to derive from.
     */
    HWREG32(bpwm->base + PWM_CWORD_MSB(channel)) = cword >> 8;
    HWREG32(bpwm->base + PWM_CWORD_LSB(channel)) = cword & 0xff;

    /* Select constant frequency signal output */
    value = HWREG32(bpwm->base + PWM_CTRL2);
    value |= CTRL2_OUT_SELECT << (channel * CTRL_CHAN_OFFS);
    HWREG32(bpwm->base + PWM_CTRL2) = value;

    /* Configure on and period value */
    HWREG32(bpwm->base + PWM_PERIOD(channel)) = pc;
    HWREG32(bpwm->base + PWM_ON(channel)) = dc;

    return 0;
}

static rt_err_t brcmstb_pwm_control(struct rt_device_pwm *pwm, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct brcmstb_pwm *bpwm = raw_to_brcmstb_pwm(pwm);
    struct rt_pwm_configuration *pwm_cfg = args;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        err = brcmstb_pwm_enable(bpwm, pwm_cfg->channel, RT_TRUE);
        break;

    case PWM_CMD_DISABLE:
        err = brcmstb_pwm_enable(bpwm, pwm_cfg->channel, RT_FALSE);
        break;

    case PWM_CMD_SET:
    case PWM_CMD_SET_PERIOD:
    case PWM_CMD_SET_PULSE:
        err = brcmstb_pwm_config(bpwm, pwm_cfg);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

const static struct rt_pwm_ops brcmstb_pwm_ops =
{
    .control = brcmstb_pwm_control,
};

static rt_err_t brcmstb_pwm_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct brcmstb_pwm *bpwm = rt_calloc(1, sizeof(*bpwm));

    if (!bpwm)
    {
        return -RT_ENOMEM;
    }

    bpwm->base = rt_dm_dev_iomap(dev, 0);

    if (!bpwm->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    bpwm->clk = rt_clk_get_by_index(dev, 0);

    if (rt_is_err(bpwm->clk))
    {
        err = rt_ptr_err(bpwm->clk);
        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(bpwm->clk)))
    {
        goto _fail;
    }

    dev->user_data = bpwm;

    bpwm->parent.parent.ofw_node = dev->ofw_node;

    rt_dm_dev_set_name_auto(&bpwm->parent.parent, "pwm");
    rt_device_pwm_register(&bpwm->parent, rt_dm_dev_get_name(&bpwm->parent.parent), &brcmstb_pwm_ops, bpwm);

    rt_dm_dev_bind_fwdata(dev, RT_NULL, bpwm);

    return RT_EOK;

_fail:
    if (bpwm->base)
    {
        rt_iounmap(bpwm->base);
    }

    if (!rt_is_err_or_null(bpwm->clk))
    {
        rt_clk_disable_unprepare(bpwm->clk);
        rt_clk_put(bpwm->clk);
    }

    rt_free(bpwm);

    return err;
}

static rt_err_t brcmstb_pwm_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct brcmstb_pwm *bpwm = dev->user_data;

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);

    for (int channel = 0; channel < PWM_NUMBER; ++channel)
    {
        brcmstb_pwm_enable(bpwm, channel, RT_FALSE);
    }

    rt_device_unregister(&bpwm->parent.parent);

    rt_clk_disable_unprepare(bpwm->clk);
    rt_clk_put(bpwm->clk);

    rt_free(bpwm);

    return RT_EOK;
}

static const struct rt_ofw_node_id brcmstb_pwm_ofw_ids[] =
{
    { .compatible = "brcm,bcm7038-pwm", },
    { /* sentinel */ }
};

static struct rt_platform_driver brcmstb_pwm_driver =
{
    .name = "brcmstb-pwm",
    .ids = brcmstb_pwm_ofw_ids,

    .probe = brcmstb_pwm_probe,
    .remove = brcmstb_pwm_remove,
};
RT_PLATFORM_DRIVER_EXPORT(brcmstb_pwm_driver);
