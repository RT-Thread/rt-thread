/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <dt-bindings/clock/sun252i-f101-rtc.h>

#define SUN252I_F101_LOSC_CTRL             0x000
#define SUN252I_F101_32K_FOUT_CTRL         0x060
#define SUN252I_F101_XO_CTRL               0x160
#define SUN252I_F101_RTC_SPI_CLK_CTRL      0x310
#define SUN252I_F101_RTC_SPI_DIV_MASK      RT_GENMASK(4, 0)
#define SUN252I_F101_RTC_KEY               0x16aa0000

struct sun252i_f101_rtc_ccu
{
    struct rt_clk_node parent;
    struct rt_clk_fixed_rate clocks[CLK_RTC_NUMBER];
    struct rt_clk_cell *cells[CLK_RTC_NUMBER];
    void *base;
};

static const char * const sun252i_f101_rtc_clock_names[] =
{
    [CLK_RTC_IOSC] = "iosc",
    [CLK_RTC_IOSC_DIV32K] = "iosc-div32k",
    [CLK_RTC_DCXO24M_DIV32K] = "dcxo24m-div32k",
    [CLK_RTC_32K] = "rtc32k",
    [CLK_RTC_1K] = "rtc-1k",
    [CLK_RTC_32K_FANOUT] = "rtc-32k-fanout",
    [CLK_RTC_SPI] = "rtc-spi",
    [CLK_RTC_CLK1M_RC] = "clk1m-rc",
};

/* These outputs are fixed after RTC clock source setup. */
static const rt_ubase_t sun252i_f101_rtc_clock_rates[] =
{
    [CLK_RTC_IOSC] = 16000000,
    [CLK_RTC_IOSC_DIV32K] = 32000,
    [CLK_RTC_DCXO24M_DIV32K] = 32768,
    [CLK_RTC_32K] = 32768,
    [CLK_RTC_1K] = 1024,
    [CLK_RTC_32K_FANOUT] = 32768,
    [CLK_RTC_SPI] = 100000000,
    [CLK_RTC_CLK1M_RC] = 1000000,
};

static rt_ubase_t sun252i_f101_rtc_clk_recalc_rate(
        struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    struct rt_clk_fixed_rate *clock = rt_container_of(cell,
            struct rt_clk_fixed_rate, cell);
    struct sun252i_f101_rtc_ccu *ccu = cell->priv;

    RT_UNUSED(parent_rate);

    if (cell == &ccu->clocks[CLK_RTC_SPI].cell)
    {
        rt_uint32_t divider = HWREG32(ccu->base + SUN252I_F101_RTC_SPI_CLK_CTRL) &
                SUN252I_F101_RTC_SPI_DIV_MASK;

        return clock->fixed_rate / (divider + 1);
    }

    return clock->fixed_rate;
}

static const struct rt_clk_ops sun252i_f101_rtc_clk_ops =
{
    .recalc_rate = sun252i_f101_rtc_clk_recalc_rate,
};

static void sun252i_f101_rtc_ccu_init(void *base)
{
    rt_uint32_t value;

    value = HWREG32(base + SUN252I_F101_XO_CTRL);
    HWREG32(base + SUN252I_F101_XO_CTRL) = value | RT_BIT(1);

    value = HWREG32(base + SUN252I_F101_32K_FOUT_CTRL);
    value |= RT_BIT(16);
    value &= ~RT_GENMASK(2, 1);
    HWREG32(base + SUN252I_F101_32K_FOUT_CTRL) = value;

    value = HWREG32(base + SUN252I_F101_LOSC_CTRL);
    value &= ~RT_BIT(0);
    HWREG32(base + SUN252I_F101_LOSC_CTRL) = value | SUN252I_F101_RTC_KEY |
            RT_BIT(0);
}

static void sun252i_f101_rtc_ccu_release(struct sun252i_f101_rtc_ccu *ccu)
{
    if (ccu->base)
    {
        rt_iounmap(ccu->base);
    }
    rt_free(ccu);
}

static rt_err_t sun252i_f101_rtc_ccu_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_size_t index;
    struct rt_device *dev = &pdev->parent;
    struct sun252i_f101_rtc_ccu *ccu = rt_calloc(1, sizeof(*ccu));

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

    sun252i_f101_rtc_ccu_init(ccu->base);

    ccu->parent.dev = dev;
    ccu->parent.cells_nr = CLK_RTC_NUMBER;
    ccu->parent.cells = ccu->cells;
    for (index = 0; index < CLK_RTC_NUMBER; ++index)
    {
        ccu->clocks[index].fixed_rate = sun252i_f101_rtc_clock_rates[index];
        ccu->clocks[index].cell.name = sun252i_f101_rtc_clock_names[index];
        ccu->clocks[index].cell.ops = &sun252i_f101_rtc_clk_ops;
        ccu->clocks[index].cell.priv = ccu;
        ccu->cells[index] = &ccu->clocks[index].cell;
    }

    if ((err = rt_clk_register(&ccu->parent)))
    {
        goto _fail;
    }

    dev->user_data = ccu;

    rt_platform_ofw_device_probe_child(rt_ofw_get_next_child(dev->ofw_node, RT_NULL));

    return RT_EOK;

_fail:
    sun252i_f101_rtc_ccu_release(ccu);
    return err;
}

static rt_err_t sun252i_f101_rtc_ccu_remove(struct rt_platform_device *pdev)
{
    struct sun252i_f101_rtc_ccu *ccu = pdev->parent.user_data;

    if (rt_clk_unregister(&ccu->parent))
    {
        return -RT_EBUSY;
    }
    sun252i_f101_rtc_ccu_release(ccu);
    return RT_EOK;
}

static const struct rt_ofw_node_id sun252i_f101_rtc_ccu_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-rtc-ccu" },
    { /* sentinel */ }
};

static struct rt_platform_driver sun252i_f101_rtc_ccu_driver =
{
    .name = "sun252i-f101-rtc-ccu",
    .ids = sun252i_f101_rtc_ccu_ofw_ids,
    .probe = sun252i_f101_rtc_ccu_probe,
    .remove = sun252i_f101_rtc_ccu_remove,
};

static int sun252i_f101_rtc_ccu_register(void)
{
    rt_platform_driver_register(&sun252i_f101_rtc_ccu_driver);
    return 0;
}
INIT_SUBSYS_EXPORT(sun252i_f101_rtc_ccu_register);
