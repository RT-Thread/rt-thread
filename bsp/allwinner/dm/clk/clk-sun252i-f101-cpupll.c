/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <dt-bindings/clock/sun252i-f101-cpupll.h>

#define SUN252I_F101_PLL_CPU_CTRL      0x0000
#define SUN252I_F101_PLL_CPU_SSC       0x0200
#define SUN252I_F101_RISCV_CLK         0x0d00

#define SUN252I_F101_PLL_CPU_N         RT_GENMASK(15, 8)
#define SUN252I_F101_PLL_CPU_P         RT_GENMASK(18, 16)
#define SUN252I_F101_PLL_CPU_M0        RT_GENMASK(21, 20)
#define SUN252I_F101_PLL_CPU_M1        RT_GENMASK(3, 0)
#define SUN252I_F101_PLL_CPU_UPDATE    RT_BIT(26)
#define SUN252I_F101_PLL_CPU_LOCK      RT_BIT(28)
#define SUN252I_F101_PLL_CPU_LOCK_EN   RT_BIT(29)

#define SUN252I_F101_RISCV_DIV         RT_GENMASK(4, 0)
#define SUN252I_F101_RISCV_AXI_DIV     RT_GENMASK(9, 8)
#define SUN252I_F101_RISCV_CLK_SEL     RT_GENMASK(26, 24)
#define SUN252I_F101_RISCV_CLK_CPU_PLL 5

#define SUN252I_F101_OSC24M_RATE       24000000UL
#define SUN252I_F101_PLL_CPU_MIN_RATE  480000000UL
/* The C907 is specified at 1 GHz; 24 MHz PLL steps make this 1008 MHz. */
#define SUN252I_F101_PLL_CPU_MAX_RATE  1008000000UL

struct sun252i_f101_cpupll
{
    struct rt_clk_node parent;
    struct rt_clk_cell clocks[CLK_CPUPLL_NUMBER];
    struct rt_clk_cell *cells[CLK_CPUPLL_NUMBER];
    struct rt_spinlock lock;
    void *base;
};

static const char * const sun252i_f101_cpupll_clock_names[] =
{
    [CLK_PLL_CPU] = "pll-cpu",
    [CLK_RISCV] = "riscv",
    [CLK_RISCV_AXI] = "riscv-axi",
};

static rt_ubase_t sun252i_f101_cpupll_rate(struct sun252i_f101_cpupll *ccu)
{
    rt_uint32_t value = HWREG32(ccu->base + SUN252I_F101_PLL_CPU_CTRL);
    rt_ubase_t rate = SUN252I_F101_OSC24M_RATE;
    rt_uint32_t n = (value & SUN252I_F101_PLL_CPU_N) >> 8;
    rt_uint32_t p = ((value & SUN252I_F101_PLL_CPU_P) >> 16) + 1;
    rt_uint32_t m0 = ((value & SUN252I_F101_PLL_CPU_M0) >> 20) + 1;
    rt_uint32_t m1 = (value & SUN252I_F101_PLL_CPU_M1) + 1;

    return rate * n / p / m0 / m1;
}

static rt_ubase_t sun252i_f101_riscv_rate(struct sun252i_f101_cpupll *ccu)
{
    rt_uint32_t value = HWREG32(ccu->base + SUN252I_F101_RISCV_CLK);
    rt_uint32_t source = (value & SUN252I_F101_RISCV_CLK_SEL) >> 24;
    rt_ubase_t parent_rate;

    if (source != SUN252I_F101_RISCV_CLK_CPU_PLL)
    {
        return 0;
    }

    parent_rate = sun252i_f101_cpupll_rate(ccu);
    return parent_rate / ((value & SUN252I_F101_RISCV_DIV) + 1);
}

static rt_ubase_t sun252i_f101_cpupll_recalc_rate(
        struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    struct sun252i_f101_cpupll *ccu = cell->priv;

    RT_UNUSED(parent_rate);

    if (cell == &ccu->clocks[CLK_PLL_CPU])
    {
        return sun252i_f101_cpupll_rate(ccu);
    }

    if (cell == &ccu->clocks[CLK_RISCV])
    {
        return sun252i_f101_riscv_rate(ccu);
    }

    return sun252i_f101_riscv_rate(ccu) /
            (((HWREG32(ccu->base + SUN252I_F101_RISCV_CLK) &
               SUN252I_F101_RISCV_AXI_DIV) >> 8) + 1);
}

static rt_base_t sun252i_f101_cpupll_round_rate(
        struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t *parent_rate)
{
    struct sun252i_f101_cpupll *ccu = cell->priv;
    rt_uint32_t cpu_div = 1;
    rt_ubase_t pll_rate;

    RT_UNUSED(parent_rate);

    if (cell == &ccu->clocks[CLK_RISCV])
    {
        cpu_div = (HWREG32(ccu->base + SUN252I_F101_RISCV_CLK) &
                SUN252I_F101_RISCV_DIV) + 1;
    }
    else if (cell == &ccu->clocks[CLK_RISCV_AXI])
    {
        return -RT_ENOSYS;
    }

    pll_rate = rt_clamp(rate * cpu_div,
            SUN252I_F101_PLL_CPU_MIN_RATE, SUN252I_F101_PLL_CPU_MAX_RATE);
    pll_rate = (pll_rate / SUN252I_F101_OSC24M_RATE) * SUN252I_F101_OSC24M_RATE;

    return (rt_base_t)(pll_rate / cpu_div);
}

static rt_err_t sun252i_f101_cpupll_wait_update(struct sun252i_f101_cpupll *ccu)
{
    for (rt_uint32_t timeout = 1000; timeout; --timeout)
    {
        if (!(HWREG32(ccu->base + SUN252I_F101_PLL_CPU_CTRL) &
                SUN252I_F101_PLL_CPU_UPDATE))
        {
            return RT_EOK;
        }

        rt_hw_us_delay(1);
    }

    return -RT_ETIMEOUT;
}

static rt_err_t sun252i_f101_cpupll_wait_lock(struct sun252i_f101_cpupll *ccu)
{
    rt_uint32_t locked = 0;

    for (rt_uint32_t timeout = 1000; timeout; --timeout)
    {
        if (HWREG32(ccu->base + SUN252I_F101_PLL_CPU_CTRL) &
                SUN252I_F101_PLL_CPU_LOCK)
        {
            if (++locked == 3)
            {
                return RT_EOK;
            }
        }
        else
        {
            locked = 0;
        }

        rt_hw_us_delay(3);
    }

    return -RT_ETIMEOUT;
}

static rt_err_t sun252i_f101_cpupll_set_rate(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_ubase_t parent_rate)
{
    struct sun252i_f101_cpupll *ccu = cell->priv;
    rt_uint32_t value;
    rt_uint32_t divider = 1;
    rt_ubase_t pll_rate;
    rt_uint32_t n;
    rt_base_t level;
    rt_err_t err;

    RT_UNUSED(parent_rate);

    if (cell == &ccu->clocks[CLK_RISCV_AXI])
    {
        return -RT_ENOSYS;
    }

    level = rt_spin_lock_irqsave(&ccu->lock);
    value = HWREG32(ccu->base + SUN252I_F101_RISCV_CLK);

    if (cell == &ccu->clocks[CLK_RISCV])
    {
        if (((value & SUN252I_F101_RISCV_CLK_SEL) >> 24) !=
                SUN252I_F101_RISCV_CLK_CPU_PLL)
        {
            rt_spin_unlock_irqrestore(&ccu->lock, level);
            return -RT_EBUSY;
        }

        divider = (value & SUN252I_F101_RISCV_DIV) + 1;
    }

    if (sun252i_f101_cpupll_recalc_rate(cell, 0) == rate)
    {
        rt_spin_unlock_irqrestore(&ccu->lock, level);
        return RT_EOK;
    }

    pll_rate = rate * divider;
    if (pll_rate < SUN252I_F101_PLL_CPU_MIN_RATE ||
            pll_rate > SUN252I_F101_PLL_CPU_MAX_RATE ||
            pll_rate % SUN252I_F101_OSC24M_RATE)
    {
        rt_spin_unlock_irqrestore(&ccu->lock, level);
        return -RT_EINVAL;
    }

    n = pll_rate / SUN252I_F101_OSC24M_RATE;
    value = HWREG32(ccu->base + SUN252I_F101_PLL_CPU_CTRL);
    value &= ~SUN252I_F101_PLL_CPU_N;
    value |= n << 8;
    HWREG32(ccu->base + SUN252I_F101_PLL_CPU_CTRL) = value;
    rt_hw_us_delay(10);

    /* Re-arm PLL lock detection before applying the new N factor. */
    value &= ~SUN252I_F101_PLL_CPU_LOCK_EN;
    HWREG32(ccu->base + SUN252I_F101_PLL_CPU_CTRL) = value;
    rt_hw_us_delay(10);
    value |= SUN252I_F101_PLL_CPU_LOCK_EN;
    HWREG32(ccu->base + SUN252I_F101_PLL_CPU_CTRL) = value |
            SUN252I_F101_PLL_CPU_UPDATE;

    err = sun252i_f101_cpupll_wait_update(ccu);
    if (!err)
    {
        err = sun252i_f101_cpupll_wait_lock(ccu);
        if (!err)
        {
            rt_hw_us_delay(20);
        }
    }

    rt_spin_unlock_irqrestore(&ccu->lock, level);
    return err;
}

static const struct rt_clk_ops sun252i_f101_cpupll_clk_ops =
{
    .recalc_rate = sun252i_f101_cpupll_recalc_rate,
    .round_rate = sun252i_f101_cpupll_round_rate,
    .set_rate = sun252i_f101_cpupll_set_rate,
};

static void sun252i_f101_cpupll_release(struct sun252i_f101_cpupll *ccu)
{
    if (ccu->base)
    {
        rt_iounmap(ccu->base);
    }
    rt_free(ccu);
}

static rt_err_t sun252i_f101_cpupll_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_size_t index;
    struct rt_device *dev = &pdev->parent;
    struct sun252i_f101_cpupll *ccu = rt_calloc(1, sizeof(*ccu));

    if (!ccu)
    {
        return -RT_ENOMEM;
    }

    ccu->base = rt_dm_dev_iomap(dev, 0);
    if (!ccu->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    ccu->parent.dev = dev;
    ccu->parent.cells_nr = CLK_CPUPLL_NUMBER;
    ccu->parent.cells = ccu->cells;
    rt_spin_lock_init(&ccu->lock);

    for (index = 0; index < CLK_CPUPLL_NUMBER; ++index)
    {
        ccu->clocks[index].name = sun252i_f101_cpupll_clock_names[index];
        ccu->clocks[index].ops = &sun252i_f101_cpupll_clk_ops;
        ccu->clocks[index].priv = ccu;
        ccu->clocks[index].flags = RT_CLK_F_GET_RATE_NOCACHE |
                RT_CLK_F_IS_CRITICAL;
        ccu->cells[index] = &ccu->clocks[index];
    }

    if ((err = rt_clk_register(&ccu->parent)))
    {
        goto _fail;
    }

    dev->user_data = ccu;
    return RT_EOK;

_fail:
    sun252i_f101_cpupll_release(ccu);
    return err;
}

static rt_err_t sun252i_f101_cpupll_remove(struct rt_platform_device *pdev)
{
    struct sun252i_f101_cpupll *ccu = pdev->parent.user_data;

    if (rt_clk_unregister(&ccu->parent))
    {
        return -RT_EBUSY;
    }

    sun252i_f101_cpupll_release(ccu);
    return RT_EOK;
}

static const struct rt_ofw_node_id sun252i_f101_cpupll_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-cpupll" },
    { /* sentinel */ }
};

static struct rt_platform_driver sun252i_f101_cpupll_driver =
{
    .name = "sun252i-f101-cpupll",
    .ids = sun252i_f101_cpupll_ofw_ids,
    .probe = sun252i_f101_cpupll_probe,
    .remove = sun252i_f101_cpupll_remove,
};

static int sun252i_f101_cpupll_register(void)
{
    rt_platform_driver_register(&sun252i_f101_cpupll_driver);
    return 0;
}
INIT_SUBSYS_EXPORT(sun252i_f101_cpupll_register);
