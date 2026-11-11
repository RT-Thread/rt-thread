/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include "clk-rk.h"

int rockchip_gcd(int m, int n)
{
    while (m > 0)
    {
        if (n > m)
        {
            int t = m;
            m = n;
            n = t;
        }
        m -= n;
    }

    return n;
}

/*
 * rational_best_approximation(31415, 10000,
 *          (1 << 8) - 1, (1 << 5) - 1, &n, &d);
 *
 * you may look at given_numerator as a fixed point number,
 * with the fractional part size described in given_denominator.
 *
 * for theoretical background, see:
 * http://en.wikipedia.org/wiki/Continued_fraction
 */
void rational_best_approximation(rt_ubase_t given_numerator,
        rt_ubase_t given_denominator,
        rt_ubase_t max_numerator,
        rt_ubase_t max_denominator,
        rt_ubase_t *best_numerator,
        rt_ubase_t *best_denominator)
{
    rt_ubase_t n, d, n0, d0, n1, d1;

    n = given_numerator;
    d = given_denominator;
    n0 = 0;
    d1 = 0;
    n1 = 1;
    d0 = 1;

    for (;;)
    {
        rt_ubase_t t, a;

        if (n1 > max_numerator || d1 > max_denominator)
        {
            n1 = n0;
            d1 = d0;
            break;
        }
        if (d == 0)
        {
            break;
        }
        t = d;
        a = n / d;
        d = n % d;
        n = t;
        t = n0 + a * n1;
        n0 = n1;
        n1 = t;
        t = d0 + a * d1;
        d0 = d1;
        d1 = t;
    }
    *best_numerator = n1;
    *best_denominator = d1;
}

void rockchip_clk_init(struct rockchip_clk_provider *provider,
        struct rt_clk_cell **cells, rt_size_t cells_nr)
{
    for (rt_size_t i = 0; i < cells_nr; ++i)
    {
        struct rt_clk_cell *cell = cells[i];
        struct rockchip_clk_cell *rk_cell;

        if (!cell)
        {
            continue;
        }

        rk_cell = cell_to_rockchip_clk_cell(cell);
        rk_cell->provider = provider;

        if (rk_cell->init)
        {
            rk_cell->init(rk_cell);
        }
    }
}

void rockchip_clk_setup(struct rockchip_clk_provider *provider,
        struct rt_clk_cell **cells, rt_size_t cells_nr)
{
    for (rt_size_t i = 0; i < cells_nr; ++i)
    {
        struct rt_clk_cell *cell = cells[i];
        struct rockchip_clk_cell *rk_cell;

        if (!cell)
        {
            continue;
        }

        rk_cell = cell_to_rockchip_clk_cell(cell);

        if (rk_cell->setup)
        {
            rk_cell->setup(rk_cell);
        }
    }
}

struct rockchip_restart
{
    struct rt_device parent;

    rt_uint32_t reg;
    struct rockchip_clk_provider *provider;
    void (*callback)(struct rockchip_clk_provider *provider);
};

static rt_err_t rockchip_restart_handler(struct rt_device *dev)
{
    struct rockchip_restart *rdev = rt_container_of(dev, struct rockchip_restart, parent);

    if (rdev->callback)
    {
        rdev->callback(rdev->provider);
    }

    HWREG32(rdev->provider->reg_base + rdev->reg) = 0xfdb9;

    return RT_EOK;
}

void rockchip_register_restart_notifier(struct rockchip_clk_provider *provider,
        rt_uint32_t reg, void (*callback)(struct rockchip_clk_provider *provider))
{
    struct rockchip_restart *rdev = rt_calloc(1, sizeof(*rdev));

    if (!rdev)
    {
        return;
    }

    rdev->reg = reg;
    rdev->provider = provider;
    rdev->callback = callback;
    rt_dm_dev_set_name(&rdev->parent, "RK-CLK");

    rt_dm_power_off_handler(&rdev->parent, RT_DM_POWER_OFF_MODE_RESET,
            RT_DM_POWER_OFF_PRIO_PLATFORM, rockchip_restart_handler);
}
