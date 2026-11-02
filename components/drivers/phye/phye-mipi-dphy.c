/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include <drivers/phye-mipi-dphy.h>

#define PSEC_PER_SEC 1000000000000ULL

static rt_err_t phye_mipi_dphy_calc_config(rt_uint64_t pixel_clock,
                                           rt_uint32_t bpp, rt_uint32_t lanes, rt_uint64_t hs_clk_rate,
                                           struct rt_phye_configure_opts_mipi_dphy *cfg)
{
    rt_uint64_t ui;

    if (!cfg)
    {
        return -RT_EINVAL;
    }

    if (!hs_clk_rate)
    {
        if (!pixel_clock || !bpp || !lanes)
        {
            return -RT_EINVAL;
        }

        hs_clk_rate = pixel_clock * bpp / lanes;
    }

    ui = (PSEC_PER_SEC + hs_clk_rate - 1) / hs_clk_rate;

    cfg->clk_pre     = 8;
    cfg->clk_prepare = 38000;
    cfg->clk_zero    = 262000;
    cfg->clk_post    = 60000 + 52 * (rt_uint32_t)ui;
    cfg->clk_trail   = 60000;
    cfg->lpx         = 50000;
    cfg->hs_prepare  = 40000 + 4 * (rt_uint32_t)ui;
    cfg->hs_zero     = 105000 + 6 * (rt_uint32_t)ui;
    cfg->hs_trail    = (4 * 8 * ui > 60000 + 4 * 4 * ui) ? 4 * 8 * (rt_uint32_t)ui : 60000 + 4 * 4 * (rt_uint32_t)ui;
    cfg->hs_exit     = 100000;
    cfg->hs_clk_rate = hs_clk_rate;
    cfg->lanes       = lanes;

    return RT_EOK;
}

rt_err_t rt_phye_mipi_dphy_get_default_config(rt_uint64_t pixel_clock,
                                              rt_uint32_t bpp, rt_uint32_t lanes,
                                              struct rt_phye_configure_opts_mipi_dphy *cfg)
{
    return phye_mipi_dphy_calc_config(pixel_clock, bpp, lanes, 0, cfg);
}

rt_err_t rt_phye_mipi_dphy_get_default_config_for_hsclk(rt_uint64_t hs_clk_rate,
                                                        rt_uint32_t lanes, struct rt_phye_configure_opts_mipi_dphy *cfg)
{
    if (!hs_clk_rate)
    {
        return -RT_EINVAL;
    }

    return phye_mipi_dphy_calc_config(0, 0, lanes, hs_clk_rate, cfg);
}
