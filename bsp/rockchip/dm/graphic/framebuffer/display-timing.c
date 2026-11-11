/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include "rockchip-display.h"

void display_timing_derive(struct display_timing *tim)
{
    rt_uint32_t hsync_start, hsync_end, vsync_start, vsync_end;

    hsync_start = tim->hactive + tim->hfront_porch;
    hsync_end = hsync_start + tim->hsync_len;
    tim->htotal = hsync_end + tim->hback_porch;

    vsync_start = tim->vactive + tim->vfront_porch;
    vsync_end = vsync_start + tim->vsync_len;
    tim->vtotal = vsync_end + tim->vback_porch;
}

static rt_err_t display_timing_read_u32(struct rt_ofw_node *np,
        const char *prop, rt_uint32_t *value)
{
    int count = rt_ofw_prop_count_of_u32(np, prop);

    if (count <= 0)
    {
        return count ? (rt_err_t)count : -RT_ENOENT;
    }

    /* Timing bindings may encode <min typical max>; use the typical value. */
    return rt_ofw_prop_read_u32_index(np, prop, count >= 3 ? 1 : 0, value);
}

static rt_err_t display_timing_parse_prop(struct rt_ofw_node *np, struct display_timing *tim)
{
    rt_uint32_t val, pixelclock;

    if (display_timing_read_u32(np, "hactive", &tim->hactive))
    {
        return -RT_EINVAL;
    }

    if (display_timing_read_u32(np, "vactive", &tim->vactive))
    {
        return -RT_EINVAL;
    }

    if (display_timing_read_u32(np, "clock-frequency", &pixelclock))
    {
        tim->pixelclock = 0;
    }
    else
    {
        tim->pixelclock = pixelclock;
    }

    if (display_timing_read_u32(np, "hsync-len", &tim->hsync_len))
    {
        tim->hsync_len = 10;
    }

    if (display_timing_read_u32(np, "hfront-porch", &tim->hfront_porch))
    {
        tim->hfront_porch = 40;
    }

    if (display_timing_read_u32(np, "hback-porch", &tim->hback_porch))
    {
        tim->hback_porch = 40;
    }

    if (display_timing_read_u32(np, "vsync-len", &tim->vsync_len))
    {
        tim->vsync_len = 4;
    }

    if (display_timing_read_u32(np, "vfront-porch", &tim->vfront_porch))
    {
        tim->vfront_porch = 20;
    }

    if (display_timing_read_u32(np, "vback-porch", &tim->vback_porch))
    {
        tim->vback_porch = 20;
    }

    tim->flags = 0;

    if (!rt_ofw_prop_read_u32(np, "hsync-active", &val) && val)
    {
        tim->flags |= DISPLAY_TIMING_F_PHSYNC;
    }

    if (!rt_ofw_prop_read_u32(np, "vsync-active", &val) && val)
    {
        tim->flags |= DISPLAY_TIMING_F_PVSYNC;
    }

    if (!rt_ofw_prop_read_u32(np, "pixelclk-active", &val) && !val)
    {
        tim->flags |= DISPLAY_TIMING_F_PIXDATA_NEGEDGE;
    }

    display_timing_derive(tim);

    return RT_EOK;
}

rt_err_t display_timing_parse(struct rt_ofw_node *np, struct display_timing *tim)
{
    struct rt_ofw_node *child, *timings;
    rt_err_t err = -RT_ENOSYS;

    if (!np || !tim)
    {
        return -RT_EINVAL;
    }

    rt_memset(tim, 0, sizeof(*tim));

    if (!display_timing_parse_prop(np, tim))
    {
        return RT_EOK;
    }

    child = rt_ofw_get_child_by_tag(np, "panel-timing");
    if (child)
    {
        err = display_timing_parse_prop(child, tim);
        rt_ofw_node_put(child);

        if (!err)
        {
            return RT_EOK;
        }
    }

    timings = rt_ofw_get_child_by_tag(np, "display-timings");
    if (!timings)
    {
        return err;
    }

    child = rt_ofw_parse_phandle(timings, "native-mode", 0);
    if (child)
    {
        err = display_timing_parse_prop(child, tim);
        rt_ofw_node_put(child);

        if (!err)
        {
            rt_ofw_node_put(timings);
            return RT_EOK;
        }
    }

    rt_ofw_foreach_available_child_node(timings, child)
    {
        err = display_timing_parse_prop(child, tim);

        if (!err)
        {
            rt_ofw_node_put(child);
            rt_ofw_node_put(timings);
            return RT_EOK;
        }
    }

    rt_ofw_node_put(timings);

    return err;
}
