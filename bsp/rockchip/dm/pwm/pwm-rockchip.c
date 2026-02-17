/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "rockchip.h"

#define PWM_CTRL_TIMER_EN       (1 << 0)
#define PWM_CTRL_OUTPUT_EN      (1 << 3)

#define PWM_ENABLE              (1 << 0)
#define PWM_CONTINUOUS          (1 << 1)
#define PWM_DUTY_POSITIVE       (1 << 3)
#define PWM_DUTY_NEGATIVE       (0 << 3)
#define PWM_INACTIVE_NEGATIVE   (0 << 4)
#define PWM_INACTIVE_POSITIVE   (1 << 4)
#define PWM_POLARITY_MASK       (PWM_DUTY_POSITIVE | PWM_INACTIVE_POSITIVE)
#define PWM_OUTPUT_LEFT         (0 << 5)
#define PWM_LOCK_EN             (1 << 6)
#define PWM_LP_DISABLE          (0 << 8)

#define PWM_ENABLE_V4           (3 << 0)
#define PWM_CLK_EN(v)           HIWORD_UPDATE(v, 0, 0)
#define PWM_EN(v)               HIWORD_UPDATE(v, 1, 1)
#define PWM_CTRL_UPDATE_EN(v)   HIWORD_UPDATE(v, 2, 2)

#define OFFSET                  0x18
#define RPT                     0x1c
#define INT_EN                  0x74
#define CAP_LPR_INT_EN(v)       HIWORD_UPDATE(v, 0, 0)
#define CAP_HPR_INT_EN(v)       HIWORD_UPDATE(v, 1, 1)
#define ONESHOT_END_INT_EN(v)   HIWORD_UPDATE(v, 2, 2)
#define RELOAD_INT_EN(v)        HIWORD_UPDATE(v, 3, 3)
#define FREQ_INT_EN(v)          HIWORD_UPDATE(v, 4, 4)
#define PWR_INT_EN(v)           HIWORD_UPDATE(v, 5, 5)
#define IR_TRANS_END_INT_EN(v)  HIWORD_UPDATE(v, 6, 6)
#define WAVE_MAX_INT_EN(v)      HIWORD_UPDATE(v, 7, 7)
#define WAVE_MIDDLE_INT_EN(v)   HIWORD_UPDATE(v, 8, 8)
#define BIPHASIC_INT_EN(v)      HIWORD_UPDATE(v, 9, 9)

#define PWM_MODE(v)             HIWORD_UPDATE(v, 0, 1)
#define ONESHOT_MODE            0
#define CONTINUOUS_MODE         1
#define CAPTURE_MODE            2
#define PWM_POLARITY(v)         HIWORD_UPDATE(v, 2, 3)
#define DUTY_NEGATIVE           (0 << 0)
#define DUTY_POSITIVE           (1 << 0)
#define INACTIVE_NEGATIVE       (0 << 1)
#define INACTIVE_POSITIVE       (1 << 1)
#define PWM_ALIGNED_INVALID(v)  HIWORD_UPDATE(v, 5, 5)
#define PWM_IN_SEL(v)           HIWORD_UPDATE(v, 6, 8)

#define NSEC_PER_USEC           1000L
#define USEC_PER_SEC            1000000L
#define NSEC_PER_SEC            1000000000L

struct rockchip_pwm_regs
{
    rt_ubase_t duty;
    rt_ubase_t period;
    rt_ubase_t cntr;
    rt_ubase_t ctrl;
    rt_ubase_t enable;
};

struct rockchip_pwm_data
{
    struct rockchip_pwm_regs regs;

    rt_uint32_t main_version;
    rt_uint32_t prescaler;
    rt_bool_t supports_polarity;
    rt_bool_t supports_lock;
    rt_uint32_t enable_conf;
};

struct rockchip_pwm
{
    struct rt_device_pwm parent;
    void *base;

    struct rt_clk *clk;
    struct rt_clk *pclk;

    const struct rockchip_pwm_data *data;
};

#define raw_to_rockchip_pwm(raw) rt_container_of(raw, struct rockchip_pwm, parent)

static rt_err_t rockchip_pwm_enable(struct rockchip_pwm *rk_pwm, rt_bool_t enable)
{
    rt_uint32_t enable_conf = rk_pwm->data->enable_conf, val;

    if (enable)
    {
        rt_err_t err = rt_clk_enable(rk_pwm->clk);

        if (err)
        {
            return err;
        }
    }

    val = HWREG32(rk_pwm->base + rk_pwm->data->regs.ctrl);

    if (enable)
    {
        val |= enable_conf;
    }
    else
    {
        val &= ~enable_conf;
    }

    HWREG32(rk_pwm->base + rk_pwm->data->regs.ctrl) = val;

    if (!enable)
    {
        rt_clk_disable(rk_pwm->clk);
    }
    else
    {
        rt_pin_ctrl_confs_apply_by_name(&rk_pwm->parent.parent, "active");
    }

    return RT_EOK;
}

static void rockchip_pwm_config(struct rockchip_pwm *rk_pwm, struct rt_pwm_configuration *pwm_cfg)
{
    rt_ubase_t period, duty;
    rt_uint64_t clk_rate, div;
    rt_uint32_t ctrl;

    clk_rate = rt_clk_get_rate(rk_pwm->clk);

    /*
     * Since period and duty cycle registers have a width of 32 bits, every
     * possible input period can be obtained using the default prescaler value
     * for all practical clock rate values.
     */
    div = clk_rate * pwm_cfg->period;
    period = RT_DIV_ROUND_CLOSEST_ULL(div, rk_pwm->data->prescaler * NSEC_PER_SEC);

    div = clk_rate * pwm_cfg->pulse;
    duty = RT_DIV_ROUND_CLOSEST_ULL(div, rk_pwm->data->prescaler * NSEC_PER_SEC);

    /*
     * Lock the period and duty of previous configuration, then change the duty
     * and period, that would not be effective.
     */
    ctrl = HWREG32(rk_pwm->base + rk_pwm->data->regs.ctrl);

    if (rk_pwm->data->supports_lock)
    {
        ctrl |= PWM_LOCK_EN;
        HWREG32(rk_pwm->base + rk_pwm->data->regs.ctrl) = ctrl;
    }

    HWREG32(rk_pwm->base + rk_pwm->data->regs.period) = period;
    HWREG32(rk_pwm->base + rk_pwm->data->regs.duty) = duty;

    if (rk_pwm->data->supports_polarity)
    {
        ctrl &= ~PWM_POLARITY_MASK;

        if (pwm_cfg->complementary)
        {
            ctrl |= PWM_DUTY_NEGATIVE | PWM_INACTIVE_POSITIVE;
        }
        else
        {
            ctrl |= PWM_DUTY_POSITIVE | PWM_INACTIVE_NEGATIVE;
        }
    }

    /*
     * Unlock and set polarity at the same time, the configuration of duty,
     * period and polarity would be effective together at next period.
     */
    if (rk_pwm->data->supports_lock)
    {
        ctrl &= ~PWM_LOCK_EN;
    }

    HWREG32(rk_pwm->base + rk_pwm->data->regs.ctrl) = ctrl;
}

static rt_err_t rockchip_pwm_get_state(struct rockchip_pwm *rk_pwm, struct rt_pwm_configuration *pwm_cfg)
{
    rt_uint32_t val;
    rt_uint64_t tmp;
    rt_ubase_t clk_rate;

    clk_rate = rt_clk_get_rate(rk_pwm->clk);

    tmp = HWREG32(rk_pwm->base + rk_pwm->data->regs.period);
    tmp *= rk_pwm->data->prescaler * NSEC_PER_SEC;
    pwm_cfg->period = RT_DIV_ROUND_CLOSEST_ULL(tmp, clk_rate);

    tmp = HWREG32(rk_pwm->base + rk_pwm->data->regs.duty);
    tmp *= rk_pwm->data->prescaler * NSEC_PER_SEC;
    pwm_cfg->pulse = RT_DIV_ROUND_CLOSEST_ULL(tmp, clk_rate);

    if (rk_pwm->data->main_version >= 4)
    {
        val = HWREG32(rk_pwm->base + rk_pwm->data->regs.enable);
    }
    else
    {
        val = HWREG32(rk_pwm->base + rk_pwm->data->regs.ctrl);
    }

    if (rk_pwm->data->supports_polarity && !(val & PWM_DUTY_POSITIVE))
    {
        pwm_cfg->complementary = RT_TRUE;
    }
    else
    {
        pwm_cfg->complementary = RT_FALSE;
    }

    return RT_EOK;
}

static rt_err_t rockchip_pwm_enable_v4(struct rockchip_pwm *rk_pwm, rt_bool_t enable)
{
    rt_uint32_t delay_us;
    struct rt_pwm_configuration pwm_cfg;

    if (enable)
    {
        rt_err_t err = rt_clk_enable(rk_pwm->clk);

        if (err)
        {
            return err;
        }
    }

    HWREG32(rk_pwm->base + rk_pwm->data->regs.enable) = PWM_EN(enable) | PWM_CLK_EN(enable);

    if (!enable)
    {
        rockchip_pwm_get_state(rk_pwm, &pwm_cfg);
        delay_us = RT_DIV_ROUND_UP_ULL(pwm_cfg.period, NSEC_PER_USEC);
        rt_hw_us_delay(delay_us);
        rt_clk_disable(rk_pwm->clk);
    }
    else
    {
        rt_pin_ctrl_confs_apply_by_name(&rk_pwm->parent.parent, "active");
    }

    return RT_EOK;
}

static void rockchip_pwm_config_v4(struct rockchip_pwm *rk_pwm, struct rt_pwm_configuration *pwm_cfg)
{
    unsigned long period, duty;
    rt_uint64_t clk_rate_kHz = rt_clk_get_rate(rk_pwm->clk) / 1000;
    rt_uint64_t div = 0;
    rt_uint64_t tmp = 0;

    tmp = (rt_uint64_t)rk_pwm->data->prescaler * USEC_PER_SEC;
    /*
     * Since period and duty cycle registers have a width of 32
     * bits, every possible input period can be obtained using the
     * default prescaler value for all practical clock rate values.
     */
    div = (rt_uint64_t)clk_rate_kHz * pwm_cfg->period;
    period = RT_DIV_ROUND_CLOSEST_ULL(div, tmp);

    div = (rt_uint64_t)clk_rate_kHz * pwm_cfg->pulse;
    duty = RT_DIV_ROUND_CLOSEST_ULL(div, tmp);

    HWREG32(rk_pwm->base + rk_pwm->data->regs.period) = period;
    HWREG32(rk_pwm->base + rk_pwm->data->regs.duty) = duty;

    if (rk_pwm->data->supports_polarity)
    {
        if (pwm_cfg->complementary)
        {
            HWREG32(rk_pwm->base + rk_pwm->data->regs.ctrl) = PWM_POLARITY(DUTY_NEGATIVE | INACTIVE_POSITIVE);
        }
        else
        {
            HWREG32(rk_pwm->base + rk_pwm->data->regs.ctrl) = PWM_POLARITY(DUTY_POSITIVE | INACTIVE_NEGATIVE);
        }
    }

    HWREG32(rk_pwm->base + rk_pwm->data->regs.ctrl) = PWM_MODE(CONTINUOUS_MODE) | PWM_ALIGNED_INVALID(RT_FALSE);
    HWREG32(rk_pwm->base + OFFSET) = 0;

    HWREG32(rk_pwm->base + RPT) = 0;
    HWREG32(rk_pwm->base + INT_EN) = ONESHOT_END_INT_EN(RT_FALSE);

    HWREG32(rk_pwm->base + rk_pwm->data->regs.enable) = PWM_CTRL_UPDATE_EN(RT_TRUE);
}

static rt_err_t rockchip_pwm_control(struct rt_device_pwm *pwm, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct rockchip_pwm *rk_pwm = raw_to_rockchip_pwm(pwm);
    struct rt_pwm_configuration *pwm_cfg = args;

    rt_clk_enable(rk_pwm->pclk);
    rt_clk_enable(rk_pwm->clk);

    /* RT_PWM framework have check args */
    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        if (rk_pwm->data->main_version >= 4)
        {
            err = rockchip_pwm_enable_v4(rk_pwm, RT_TRUE);
        }
        else
        {
            err = rockchip_pwm_enable(rk_pwm, RT_TRUE);
        }
        break;

    case PWM_CMD_DISABLE:
        if (rk_pwm->data->main_version >= 4)
        {
            err = rockchip_pwm_enable_v4(rk_pwm, RT_FALSE);
        }
        else
        {
            err = rockchip_pwm_enable(rk_pwm, RT_FALSE);
        }
        break;

    case PWM_CMD_SET:
    case PWM_CMD_SET_PERIOD:
    case PWM_CMD_SET_PULSE:
        if (rk_pwm->data->main_version >= 4)
        {
            rockchip_pwm_config_v4(rk_pwm, RT_FALSE);
        }
        else
        {
            rockchip_pwm_config(rk_pwm, pwm_cfg);
        }
        break;

    case PWM_CMD_GET:
        err = rockchip_pwm_get_state(rk_pwm, pwm_cfg);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    rt_clk_disable(rk_pwm->clk);
    rt_clk_disable(rk_pwm->pclk);

    return err;
}

const static struct rt_pwm_ops rockchip_pwm_ops =
{
    .control = rockchip_pwm_control,
};

static void rockchip_pwm_free(struct rockchip_pwm *rk_pwm)
{
    if (rk_pwm->base)
    {
        rt_iounmap(rk_pwm->base);
    }

    if (!rt_is_err_or_null(rk_pwm->clk))
    {
        rt_clk_disable_unprepare(rk_pwm->clk);
        rt_clk_put(rk_pwm->clk);
    }

    if (!rt_is_err_or_null(rk_pwm->pclk))
    {
        rt_clk_disable_unprepare(rk_pwm->pclk);
        rt_clk_put(rk_pwm->pclk);
    }

    rt_free(rk_pwm);
}

static rt_err_t rockchip_pwm_probe(struct rt_platform_device *pdev)
{
    int id;
    rt_bool_t enabled;
    rt_err_t err = RT_EOK;
    rt_uint32_t enable_conf, ctrl;
    struct rt_device *dev = &pdev->parent;
    struct rockchip_pwm *rk_pwm = rt_calloc(1, sizeof(*rk_pwm));
    const struct rockchip_pwm_data *pdata = pdev->id->data;

    if (!rk_pwm)
    {
        return -RT_ENOMEM;
    }

    rk_pwm->data = pdata;
    rk_pwm->base = rt_dm_dev_iomap(dev, 0);

    if (!rk_pwm->base)
    {
        err = -RT_EIO;
        goto _free_res;
    }

    rk_pwm->clk = rt_clk_get_by_name(dev, "pwm");

    if (rt_is_err(rk_pwm->clk))
    {
        err = rt_ptr_err(rk_pwm->clk);
        goto _free_res;
    }

    rk_pwm->pclk = rt_clk_get_by_name(dev, "pclk");

    if (rt_is_err(rk_pwm->pclk))
    {
        err = rt_ptr_err(rk_pwm->pclk);
        goto _free_res;
    }

    if ((err = rt_clk_prepare_enable(rk_pwm->clk)))
    {
        goto _free_res;
    }

    if ((err = rt_clk_prepare_enable(rk_pwm->pclk)))
    {
        goto _free_res;
    }

    enable_conf = rk_pwm->data->enable_conf;
    if (rk_pwm->data->main_version >= 4)
    {
        ctrl = HWREG32(rk_pwm->base + rk_pwm->data->regs.enable);
    }
    else
    {
        ctrl = HWREG32(rk_pwm->base + rk_pwm->data->regs.ctrl);
    }
    enabled = (ctrl & enable_conf) == enable_conf;

    /* Keep the PWM clk enabled if the PWM appears to be up and running. */
    if (!enabled)
    {
        rt_clk_enable(rk_pwm->clk);
        rt_clk_disable(rk_pwm->clk);
    }

    rt_clk_disable(rk_pwm->pclk);

    dev->user_data = rk_pwm;

    rk_pwm->parent.parent.ofw_node = dev->ofw_node;

    if ((id = pdev->dev_id) >= 0)
    {
        rt_dm_dev_set_name(&rk_pwm->parent.parent, "pwm%u", id);
    }
    else
    {
        rt_dm_dev_set_name_auto(&rk_pwm->parent.parent, "pwm");
    }

    rt_device_pwm_register(&rk_pwm->parent,
            rt_dm_dev_get_name(&rk_pwm->parent.parent), &rockchip_pwm_ops, rk_pwm);

    rt_dm_dev_bind_fwdata(dev, RT_NULL, rk_pwm);

    /* Sync config */
    rt_pwm_enable(&rk_pwm->parent, 0);

    if (!enabled)
    {
        rt_pwm_disable(&rk_pwm->parent, 0);
    }

    return RT_EOK;

_free_res:
    rockchip_pwm_free(rk_pwm);

    return err;
}

static rt_err_t rockchip_pwm_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rockchip_pwm *rk_pwm = dev->user_data;

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);

    rockchip_pwm_enable(rk_pwm, RT_FALSE);

    rt_device_unregister(&rk_pwm->parent.parent);

    rockchip_pwm_free(rk_pwm);

    return RT_EOK;
}

static const struct rockchip_pwm_data pwm_data_v1 =
{
    .regs =
    {
        .duty = 0x04,
        .period = 0x08,
        .cntr = 0x00,
        .ctrl = 0x0c,
    },
    .prescaler = 2,
    .supports_polarity = RT_FALSE,
    .supports_lock = RT_FALSE,
    .enable_conf = PWM_CTRL_OUTPUT_EN | PWM_CTRL_TIMER_EN,
};

static const struct rockchip_pwm_data pwm_data_v2 =
{
    .regs =
    {
        .duty = 0x08,
        .period = 0x04,
        .cntr = 0x00,
        .ctrl = 0x0c,
    },
    .prescaler = 1,
    .supports_polarity = RT_TRUE,
    .supports_lock = RT_FALSE,
    .enable_conf = PWM_OUTPUT_LEFT | PWM_LP_DISABLE | PWM_ENABLE | PWM_CONTINUOUS,
};

static const struct rockchip_pwm_data pwm_data_vop =
{
    .regs =
    {
        .duty = 0x08,
        .period = 0x04,
        .cntr = 0x0c,
        .ctrl = 0x00,
    },
    .prescaler = 1,
    .supports_polarity = RT_TRUE,
    .supports_lock = RT_FALSE,
    .enable_conf = PWM_OUTPUT_LEFT | PWM_LP_DISABLE | PWM_ENABLE | PWM_CONTINUOUS,
};

static const struct rockchip_pwm_data pwm_data_v3 =
{
    .regs =
    {
        .duty = 0x08,
        .period = 0x04,
        .cntr = 0x00,
        .ctrl = 0x0c,
    },
    .prescaler = 1,
    .supports_polarity = RT_TRUE,
    .supports_lock = RT_TRUE,
    .enable_conf = PWM_OUTPUT_LEFT | PWM_LP_DISABLE | PWM_ENABLE | PWM_CONTINUOUS,
};

static const struct rockchip_pwm_data pwm_data_v4 =
{
    .regs =
    {
        .duty = 0x14,
        .period = 0x10,
        .enable = 0x4,
        .ctrl = 0xc,
    },
    .main_version = 0x04,
    .prescaler = 1,
    .supports_polarity = true,
    .supports_lock = true,
    .enable_conf = PWM_ENABLE_V4,
};

static const struct rt_ofw_node_id rockchip_pwm_ofw_ids[] =
{
    { .compatible = "rockchip,rk2928-pwm", .data = &pwm_data_v1 },
    { .compatible = "rockchip,rk3288-pwm", .data = &pwm_data_v2 },
    { .compatible = "rockchip,vop-pwm", .data = &pwm_data_vop },
    { .compatible = "rockchip,rk3328-pwm", .data = &pwm_data_v3 },
    { .compatible = "rockchip,rk3576-pwm", .data = &pwm_data_v4 },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_pwm_driver =
{
    .name = "rockchip-pwm",
    .ids = rockchip_pwm_ofw_ids,

    .probe = rockchip_pwm_probe,
    .remove = rockchip_pwm_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_pwm_driver);
