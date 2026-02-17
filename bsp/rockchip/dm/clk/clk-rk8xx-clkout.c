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

#define DBG_TAG "clk.rk8xx"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rk8xx.h"

struct rk8xx_clkout
{
    struct rt_clk_node parent;

    struct rk8xx *rk8xx;
};

#define raw_to_rk8xx_clkout(raw) rt_container_of(raw, struct rk8xx_clkout, parent)

static rt_ubase_t rk808_clkout_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    return 32768;
}

static const struct rt_clk_ops rk808_clkout1_ops =
{
    .recalc_rate = rk808_clkout_recalc_rate,
};

static rt_err_t rk808_clkout2_enable(struct rt_clk_cell *cell, rt_bool_t enable)
{
    struct rk8xx_clkout *clkout = raw_to_rk8xx_clkout(cell->clk_np);

    return rk8xx_update_bits(clkout->rk8xx, RK808_CLK32OUT_REG,
            CLK32KOUT2_EN, enable ? CLK32KOUT2_EN : 0);
}

static rt_err_t rk808_clkout2_prepare(struct rt_clk_cell *cell)
{
    return rk808_clkout2_enable(cell, RT_TRUE);
}

static void rk808_clkout2_unprepare(struct rt_clk_cell *cell)
{
    rk808_clkout2_enable(cell, RT_FALSE);
}

static rt_bool_t rk808_clkout2_is_prepared(struct rt_clk_cell *cell)
{
    rt_uint32_t val;
    struct rk8xx_clkout *clkout = raw_to_rk8xx_clkout(cell->clk_np);

    val = rk8xx_read(clkout->rk8xx, RK808_CLK32OUT_REG);

    if ((rt_err_t)val < 0)
    {
        return RT_FALSE;
    }

    return !!(val & CLK32KOUT2_EN);
}

static const struct rt_clk_ops rk808_clkout2_ops =
{
    .prepare = rk808_clkout2_prepare,
    .unprepare = rk808_clkout2_unprepare,
    .is_prepared = rk808_clkout2_is_prepared,
    .recalc_rate = rk808_clkout_recalc_rate,
};

static rt_err_t rk817_clkout2_enable(struct rt_clk_cell *cell, rt_bool_t enable)
{
    struct rk8xx_clkout *clkout = raw_to_rk8xx_clkout(cell->clk_np);

    return rk8xx_update_bits(clkout->rk8xx, RK817_SYS_CFG(1),
            RK817_CLK32KOUT2_EN, enable ? RK817_CLK32KOUT2_EN : 0);
}

static rt_err_t rk817_clkout2_prepare(struct rt_clk_cell *cell)
{
    return rk817_clkout2_enable(cell, RT_TRUE);
}

static void rk817_clkout2_unprepare(struct rt_clk_cell *cell)
{
    rk817_clkout2_enable(cell, RT_FALSE);
}

static rt_bool_t rk817_clkout2_is_prepared(struct rt_clk_cell *cell)
{
    rt_uint32_t val;
    struct rk8xx_clkout *clkout = raw_to_rk8xx_clkout(cell->clk_np);

    val = rk8xx_read(clkout->rk8xx, RK817_SYS_CFG(1));

    if ((rt_err_t)val < 0)
    {
        return RT_FALSE;
    }

    return !!(val & RK817_CLK32KOUT2_EN);
}

static const struct rt_clk_ops rk817_clkout2_ops =
{
    .prepare = rk817_clkout2_prepare,
    .unprepare = rk817_clkout2_unprepare,
    .is_prepared = rk817_clkout2_is_prepared,
    .recalc_rate = rk808_clkout_recalc_rate,
};

static struct rt_clk_cell *rk8xx_clkout_cell[] =
{
    &(struct rt_clk_cell) { .name = "rk808-clkout1" },
    &(struct rt_clk_cell) { .name = "rk808-clkout2" },
};

static rt_err_t rk8xx_clkout_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_clk_cell *cell;
    struct rt_device *dev = &pdev->parent;
    struct rk8xx *rk8xx = pdev->priv;
    struct rk8xx_clkout *clkout = rt_calloc(1, sizeof(*clkout));

    if (!clkout)
    {
        return -RT_ENOMEM;
    }

    clkout->rk8xx = rk8xx;

    /* clkout1 */
    cell = rk8xx_clkout_cell[0];
    cell->ops = &rk808_clkout1_ops;
    rt_dm_dev_prop_read_string_index(dev, "clock-output-names", 0, &cell->name);

    /* clkout2 */
    cell = rk8xx_clkout_cell[1];
    switch (rk8xx->variant)
    {
    case RK809_ID:
    case RK817_ID:
        cell->ops = &rk817_clkout2_ops;
        break;

    /*
     * For the default case, it match the following PMIC type.
     * RK805_ID
     * RK808_ID
     * RK818_ID
     */
    default:
        cell->ops = &rk808_clkout2_ops;
        break;
    }
    rt_dm_dev_prop_read_string_index(dev, "clock-output-names", 1, &cell->name);

    if (rt_dm_dev_prop_read_bool(dev, "rockchip,clk-32k-always-on"))
    {
        cell->flags |= RT_CLK_F_IS_CRITICAL;
    }

    clkout->parent.dev = dev;
    clkout->parent.cells = rk8xx_clkout_cell;
    clkout->parent.cells_nr = RT_ARRAY_SIZE(rk8xx_clkout_cell);

    if ((err = rt_clk_register(&clkout->parent)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    rt_free(clkout);

    return err;
}

static struct rt_platform_driver rk8xx_clkout_driver =
{
    .name = "rk8xx-clkout",
    .probe = rk8xx_clkout_probe,
};

static int rk8xx_clkout_register(void)
{
    rt_platform_driver_register(&rk8xx_clkout_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(rk8xx_clkout_register);
