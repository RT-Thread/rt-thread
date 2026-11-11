/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#ifndef __FB_VOPL_H__
#define __FB_VOPL_H__

#include "rockchip-display.h"

enum voplfb_hw_format
{
    VOPLFB_FMT_ARGB8888 = 0,
    VOPLFB_FMT_RGB888,
    VOPLFB_FMT_RGB565,
};

struct voplfb
{
    struct rt_graphic_device parent;

    void *regs;
    rt_uint32_t display_w;
    rt_uint32_t display_h;

    struct display_timing output_tim;
    rt_bool_t output_tim_valid;

    rt_bool_t clk_enabled;
    struct rt_clk_array *clks;

    int irq;
    rt_atomic_t vsync;
    struct rt_semaphore vsync_sem;

    struct rt_graphic_plane *primary;

    rt_bool_t powered;
};

rt_uint32_t voplfb_mode_to_hw(rt_uint32_t mode);
rt_uint32_t voplfb_hw_to_bpp(rt_uint32_t hw_fmt);

#endif /* __FB_VOPL_H__ */
