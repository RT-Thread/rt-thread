/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#ifndef __PHYE_MIPI_DPHY_H__
#define __PHYE_MIPI_DPHY_H__

#include <rtthread.h>

struct rt_phye_configure_opts_mipi_dphy
{
    rt_uint64_t hs_clk_rate;    /* lane HS bit rate, Hz */
    rt_uint32_t lanes;

    rt_uint32_t lpx;
    rt_uint32_t hs_prepare;
    rt_uint32_t hs_zero;
    rt_uint32_t hs_trail;
    rt_uint32_t hs_exit;
    rt_uint32_t clk_prepare;
    rt_uint32_t clk_zero;
    rt_uint32_t clk_pre;
    rt_uint32_t clk_post;
    rt_uint32_t clk_trail;
};

rt_err_t rt_phye_mipi_dphy_get_default_config(rt_uint64_t pixel_clock,
                                              rt_uint32_t bpp, rt_uint32_t lanes,
                                              struct rt_phye_configure_opts_mipi_dphy *cfg);
rt_err_t rt_phye_mipi_dphy_get_default_config_for_hsclk(rt_uint64_t hs_clk_rate,
                                                        rt_uint32_t lanes, struct rt_phye_configure_opts_mipi_dphy *cfg);

#endif /* __PHYE_MIPI_DPHY_H__ */
