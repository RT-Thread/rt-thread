/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-3-15      GuEe-GUI     the first version
 */

#include <rtdevice.h>

#define DBG_TAG "phye.inno-hdmi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct inno_pll
{
    rt_ubase_t rate;
    rt_uint8_t prediv;
    rt_uint16_t fbdiv;
    rt_uint8_t tmds_a;
    rt_uint8_t tmds_b;
    rt_uint8_t tmds_c;
    rt_uint8_t pixel_a;
    rt_uint8_t pixel_b;
    rt_uint8_t pixel_c;
    rt_uint8_t pixel_d;
    rt_uint32_t frac;
};

/* 24 MHz reference, pixel clock == TMDS clock (RGB, 8 bpc). */
static const struct inno_pll inno_plls[] =
{
    {  27000000, 1,  90, 3, 2, 2, 10, 3, 3,  4, 0 },
    {  40000000, 1,  80, 2, 2, 2, 12, 2, 2,  2, 0 },
    {  59400000, 1,  99, 3, 1, 1,  1, 3, 3,  4, 0 },
    {  65000000, 1, 130, 2, 2, 2,  1, 0, 0, 12, 0 },
    {  71000000, 3, 284, 0, 3, 3,  1, 0, 0,  8, 0 },
    {  74176000, 1,  98, 1, 2, 2,  1, 2, 3,  4, 0xe6ae6b },
    {  74250000, 1,  99, 1, 2, 2,  1, 2, 3,  4, 0 },
    {  83500000, 2, 167, 2, 1, 1,  1, 0, 0,  6, 0 },
    {  85750000, 3, 343, 0, 3, 3,  1, 0, 0,  8, 0 },
    {  88750000, 3, 355, 0, 3, 3,  1, 0, 0,  8, 0 },
    { 108000000, 1,  90, 3, 0, 0,  1, 0, 0,  5, 0 },
    { 119000000, 1, 119, 2, 1, 1,  1, 0, 0,  6, 0 },
    { 148352000, 1,  98, 1, 1, 1,  1, 2, 2,  2, 0xe6ae6b },
    { 148500000, 1,  99, 1, 1, 1,  1, 2, 2,  2, 0 },
    { 162000000, 1, 108, 0, 2, 2,  1, 0, 0,  4, 0 },
    { 296703000, 1,  98, 0, 1, 1,  1, 0, 2,  2, 0xe6ae6b },
    { 297000000, 1,  99, 0, 1, 1,  1, 0, 2,  2, 0 },
};

struct inno_hdmi
{
    struct rt_phye phye;
    void *regs;
    struct rt_clk *sysclk;
    struct rt_clk *refclk;
    struct rt_clk *pixel;
    struct rt_clk_node clk_np;
    struct rt_clk_cell pixel_cell;
    struct rt_clk_cell *cells[1];
    struct rt_device clk_dev;
    const struct inno_pll *pll;
    rt_bool_t clock_on;
    rt_bool_t lanes_on;
};

static const struct inno_pll *inno_find_pll(rt_ubase_t rate)
{
    rt_size_t i;

    for (i = 0; i < RT_ARRAY_SIZE(inno_plls); ++i)
    {
        if (inno_plls[i].rate == rate)
        {
            return &inno_plls[i];
        }
    }
    return RT_NULL;
}

static void inno_write(struct inno_hdmi *inno, rt_uint32_t reg, rt_uint8_t val)
{
    HWREG32((rt_uint8_t *)inno->regs + reg * 4) = val;
}

static rt_uint8_t inno_read(struct inno_hdmi *inno, rt_uint32_t reg)
{
    return HWREG32((rt_uint8_t *)inno->regs + reg * 4);
}

static void inno_update(struct inno_hdmi *inno, rt_uint32_t reg,
        rt_uint8_t mask, rt_uint8_t val)
{
    inno_write(inno, reg, (inno_read(inno, reg) & ~mask) | (val & mask));
}

static rt_err_t inno_wait_lock(struct inno_hdmi *inno, rt_uint32_t reg)
{
    unsigned int i;

    for (i = 0; i < 500; ++i)
    {
        if (inno_read(inno, reg) & 1)
        {
            return RT_EOK;
        }
        rt_hw_us_delay(10);
    }
    LOG_E("PLL lock timeout at register 0x%02x", reg);
    return -RT_ETIMEOUT;
}

static rt_err_t inno_pre_pll(struct inno_hdmi *inno, const struct inno_pll *pll)
{
    inno_update(inno, 0xb0, 4, 4);
    inno_write(inno, 0xcc, 0x0f);
    inno_update(inno, 0xa0, 3, 0);
    inno_write(inno, 0xa1, pll->prediv);
    inno_write(inno, 0xa2, (pll->fbdiv >> 8) | (pll->frac ? 0xc0 : 0xf0));
    inno_write(inno, 0xa3, pll->fbdiv);
    inno_write(inno, 0xa5, pll->pixel_a | (pll->pixel_b << 5));
    inno_write(inno, 0xa6, pll->pixel_d | (pll->pixel_c << 5));
    inno_write(inno, 0xa4, (pll->tmds_a << 4) | (pll->tmds_b << 2) | pll->tmds_c);
    inno_write(inno, 0xd3, pll->frac);
    inno_write(inno, 0xd2, pll->frac >> 8);
    inno_write(inno, 0xd1, pll->frac >> 16);
    return inno_wait_lock(inno, 0xa9);
}

static void inno_lanes_off(struct inno_hdmi *inno)
{
    inno_write(inno, 0xb2, 0);
    inno_write(inno, 0xbe, 0);
    inno_update(inno, 0xaa, 1, 1);
    inno_write(inno, 0x05, 0);
    inno_write(inno, 0x07, 0);
    inno->lanes_on = RT_FALSE;
}

static struct inno_hdmi *inno_from_cell(struct rt_clk_cell *cell)
{
    return rt_container_of(cell->clk_np, struct inno_hdmi, clk_np);
}

static rt_err_t inno_pixel_enable(struct rt_clk_cell *cell)
{
    struct inno_hdmi *inno = inno_from_cell(cell);
    rt_err_t err;

    err = rt_clk_prepare_enable(inno->sysclk);
    if (err)
    {
        return err;
    }
    /* The clock framework enables our refclk parent before this callback. */
    inno_write(inno, 0x02, 0x81);
    inno_lanes_off(inno);
    err = inno_pre_pll(inno, inno->pll);
    if (err)
    {
        inno_update(inno, 0xa0, 1, 1);
        inno_write(inno, 0xcc, 0);
        inno_update(inno, 0xb0, 4, 0);
        rt_clk_disable_unprepare(inno->sysclk);
        return err;
    }
    inno->clock_on = RT_TRUE;
    return RT_EOK;
}

static void inno_pixel_disable(struct rt_clk_cell *cell)
{
    struct inno_hdmi *inno = inno_from_cell(cell);

    inno_lanes_off(inno);
    inno_update(inno, 0xa0, 1, 1);
    inno_write(inno, 0xcc, 0);
    inno_update(inno, 0xb0, 4, 0);
    inno->clock_on = RT_FALSE;
    rt_clk_disable_unprepare(inno->sysclk);
}

static rt_ubase_t inno_pixel_recalc(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    RT_UNUSED(parent_rate);
    return inno_from_cell(cell)->pll->rate;
}

static rt_base_t inno_pixel_round(struct rt_clk_cell *cell, rt_ubase_t rate,
        rt_ubase_t *parent_rate)
{
    RT_UNUSED(cell);
    return *parent_rate == 24000000 && inno_find_pll(rate) ? (rt_base_t)rate : -RT_EINVAL;
}

static rt_err_t inno_pixel_set_rate(struct rt_clk_cell *cell, rt_ubase_t rate,
        rt_ubase_t parent_rate)
{
    struct inno_hdmi *inno = inno_from_cell(cell);
    const struct inno_pll *pll = inno_find_pll(rate);
    rt_err_t err;

    if (!pll || parent_rate != 24000000)
    {
        return -RT_EINVAL;
    }
    if (inno->lanes_on && pll != inno->pll)
    {
        return -RT_EBUSY;
    }
    if (inno->clock_on && pll != inno->pll)
    {
        err = inno_pre_pll(inno, pll);
        if (err)
        {
            inno_pre_pll(inno, inno->pll);
            return err;
        }
    }
    inno->pll = pll;
    return RT_EOK;
}

static const struct rt_clk_ops inno_pixel_ops =
{
    .enable = inno_pixel_enable,
    .disable = inno_pixel_disable,
    .recalc_rate = inno_pixel_recalc,
    .round_rate = inno_pixel_round,
    .set_rate = inno_pixel_set_rate,
};

static rt_err_t inno_configure(struct rt_phye *phye,
        union rt_phye_configure_opts *opts)
{
    struct inno_hdmi *inno = rt_container_of(phye, struct inno_hdmi, phye);

    if (!opts || opts->hdmi.pixel_clock != opts->hdmi.tmds_clock ||
            opts->hdmi.pixel_clock > 297000000)
    {
        return -RT_EINVAL;
    }
    return rt_clk_set_rate(inno->pixel, opts->hdmi.pixel_clock);
}

static rt_err_t inno_power_on(struct rt_phye *phye)
{
    struct inno_hdmi *inno = rt_container_of(phye, struct inno_hdmi, phye);
    static const rt_uint8_t analog[][9] =
    {
        { 2, 4, 15, 15, 0, 0x76, 0x83, 0x0a, 0x0a },
        { 2, 11, 15, 15, 0, 0x76, 0x83, 0x0a, 0x33 },
        { 3, 4, 12, 18, 0, 0x76, 0x83, 0, 0x0f },
    };
    const rt_uint8_t *cfg;
    rt_uint32_t rate;
    rt_uint32_t counter;
    rt_uint32_t i;
    rt_err_t err;

    rate = inno->pll->rate;
    err = rt_clk_prepare_enable(inno->pixel);

    if (err)
    {
        return err;
    }
    cfg = analog[rate <= 165000000 ? 0 : rate <= 185625000 ? 1 : 2];
    inno_update(inno, 0xaa, 1, 0);
    inno_write(inno, 0xab, rate <= 148500000 ? 1 : 2);
    inno_write(inno, 0xad, rate <= 74250000 ? 1 : 0);
    inno_write(inno, 0xaa, 0x0e);
    inno_write(inno, 0xac, rate > 74250000 && rate <= 148500000 ? 10 : 20);
    inno_update(inno, 0xad, 0x10, 0);
    inno_write(inno, 0xbf, (cfg[0] << 4) | cfg[1]);
    inno_write(inno, 0xc0, (cfg[1] << 4) | cfg[1]);
    inno_write(inno, 0xb5, cfg[2]);
    for (i = 0; i < 3; ++i)
    {
        inno_write(inno, 0xb6 + i, cfg[3]);
        inno_write(inno, 0xbb + i, cfg[4]);
    }
    inno_write(inno, 0xb4, 7);
    inno_write(inno, 0xbe, 0x70);
    inno_write(inno, 0xb2, 0x0f);
    err = inno_wait_lock(inno, 0xaf);
    if (err)
    {
        inno_lanes_off(inno);
        rt_clk_disable_unprepare(inno->pixel);
        return err;
    }
    inno_write(inno, 0xc7, cfg[5]);
    inno_write(inno, 0xc5, cfg[6]);
    inno_write(inno, 0xc8, cfg[7]);
    for (i = 0; i < 3; ++i)
    {
        inno_write(inno, 0xc9 + i, cfg[8]);
    }
    counter = 47520000000ULL / rate;
    inno_write(inno, 0xd8, counter >> 8);
    inno_write(inno, 0xd9, counter);
    inno_update(inno, 0xaa, 1, 0);
    inno_update(inno, 0xb0, 4, 4);
    inno_write(inno, 0xb2, 0x0f);
    inno_update(inno, 0x02, 1, 0);
    inno_update(inno, 0x02, 1, 1);
    /* No PHY interrupt handler: leave the interrupt sources masked. */
    inno_write(inno, 0x05, 0);
    inno_write(inno, 0x07, 0);
    inno_write(inno, 0xcc, 0x0f);
    inno->lanes_on = RT_TRUE;
    LOG_D("RK3528 TMDS locked at %u Hz", rate);
    return RT_EOK;
}

static rt_err_t inno_power_off(struct rt_phye *phye)
{
    struct inno_hdmi *inno = rt_container_of(phye, struct inno_hdmi, phye);

    inno_lanes_off(inno);
    rt_clk_disable_unprepare(inno->pixel);
    return RT_EOK;
}

static rt_err_t inno_set_mode(struct rt_phye *phye,
        enum rt_phye_mode mode, int submode)
{
    RT_UNUSED(phye);
    RT_UNUSED(submode);
    return mode == RT_PHYE_MODE_HDMI ? RT_EOK : -RT_EINVAL;
}

static const struct rt_phye_ops inno_ops =
{
    .configure = inno_configure,
    .set_mode = inno_set_mode,
    .power_on = inno_power_on,
    .power_off = inno_power_off,
};

static rt_err_t inno_hdmi_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct inno_hdmi *inno;
    struct rt_ofw_node *port;
    rt_err_t err;

    inno = rt_calloc(1, sizeof(*inno));
    port = RT_NULL;
    err = -RT_EIO;

    if (!inno)
    {
        return -RT_ENOMEM;
    }
    inno->regs = rt_ofw_iomap(dev->ofw_node, 0);
    inno->sysclk = rt_clk_get_by_name(dev, "sysclk");
    inno->refclk = rt_clk_get_by_name(dev, "refclk");
    if (!inno->regs || rt_is_err_or_null(inno->sysclk) ||
            rt_is_err_or_null(inno->refclk))
    {
        goto fail;
    }
    if (rt_clk_get_rate(inno->refclk) != 24000000)
    {
        err = -RT_EINVAL;
        goto fail;
    }
    port = rt_ofw_get_child_by_tag(dev->ofw_node, "clk-port");
    if (!port)
    {
        goto fail;
    }
    inno->pll = inno_find_pll(74250000);
    inno->cells[0] = &inno->pixel_cell;
    inno->pixel_cell.name = "clk_hdmiphy_pixel_io";
    inno->pixel_cell.ops = &inno_pixel_ops;
    inno->pixel_cell.parents_nr = 1;
    inno->pixel_cell.parent = inno->refclk;
    inno->pixel_cell.parent_name = inno->refclk->cell->name;
    inno->pixel_cell.flags = RT_CLK_F_GET_RATE_NOCACHE;
    inno->clk_dev.ofw_node = port;
    inno->clk_np.dev = &inno->clk_dev;
    inno->clk_np.cells = inno->cells;
    inno->clk_np.cells_nr = 1;
    rt_list_init(&inno->clk_np.parent.list);
    err = rt_clk_register(&inno->clk_np);
    if (err)
    {
        goto fail;
    }
    inno->pixel = rt_clk_cell_get_clk(&inno->pixel_cell, RT_NULL);
    if (rt_is_err_or_null(inno->pixel))
    {
        err = -RT_ENOMEM;
        goto fail_clock;
    }
    inno->phye.dev = dev;
    inno->phye.ops = &inno_ops;
    err = rt_phye_register(&inno->phye);
    if (err)
    {
        rt_clk_put(inno->pixel);
        goto fail_clock;
    }
    dev->user_data = inno;

    return RT_EOK;

fail_clock:
    rt_clk_unregister(&inno->clk_np);
    if (rt_ofw_data(port) == &inno->clk_np.parent)
    {
        rt_ofw_data(port) = RT_NULL;
    }
fail:
    rt_ofw_node_put(port);
    if (!rt_is_err_or_null(inno->sysclk))
    {
        rt_clk_put(inno->sysclk);
    }
    if (!rt_is_err_or_null(inno->refclk))
    {
        rt_clk_put(inno->refclk);
    }
    if (inno->regs)
    {
        rt_iounmap(inno->regs);
    }
    rt_free(inno);
    return err;
}

static const struct rt_ofw_node_id inno_hdmi_ids[] =
{
    { .compatible = "rockchip,rk3528-hdmi-phy" },
    { /* sentinel */ }
};

static struct rt_platform_driver inno_hdmi_driver =
{
    .name = "phy-rockchip-inno-hdmi",
    .ids = inno_hdmi_ids,
    .probe = inno_hdmi_probe,
};
RT_PLATFORM_DRIVER_EXPORT(inno_hdmi_driver);
