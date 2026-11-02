/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#ifndef __ROCKCHIP_DISPLAY_H__
#define __ROCKCHIP_DISPLAY_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <dt-bindings/display/rockchip_vop.h>

#define DISPLAY_TIMING_F_PHSYNC     RT_BIT(0)
#define DISPLAY_TIMING_F_PVSYNC     RT_BIT(1)
#define DISPLAY_TIMING_F_PIXDATA_NEGEDGE RT_BIT(2)

struct display_timing
{
    rt_uint32_t hactive;
    rt_uint32_t vactive;
    rt_uint32_t hfront_porch;
    rt_uint32_t hback_porch;
    rt_uint32_t hsync_len;
    rt_uint32_t vfront_porch;
    rt_uint32_t vback_porch;
    rt_uint32_t vsync_len;
    rt_uint64_t pixelclock;
    rt_uint32_t flags;
    rt_uint32_t htotal;
    rt_uint32_t vtotal;
};

struct display_route
{
    struct rt_ofw_node *route_np;
    struct rt_ofw_node *vop_np;
    struct rt_ofw_node *vp_port_np;
    struct rt_ofw_node *connector_np;
    struct rt_ofw_node *panel_np;
    rt_uint32_t vp_id;
};

struct rockchip_crtc_ops
{
    rt_err_t (*mode_set)(void *priv, const struct display_route *route,
            const struct display_timing *tim);
    rt_err_t (*enable)(void *priv, rt_uint32_t vp_id, rt_bool_t enable);
    rt_err_t (*complete)(void *priv, rt_uint32_t vp_id);
};

struct rockchip_connector_ops
{
    rt_err_t (*detect)(void *priv, rt_bool_t *connected);
    rt_err_t (*prepare)(void *priv, rt_uint32_t vp_id, const struct display_timing *tim);
    rt_err_t (*mode_set)(void *priv, const struct display_timing *tim);
    rt_err_t (*transfer)(void *priv, rt_uint8_t data_type, rt_uint8_t delay_ms,
            const rt_uint8_t *payload, rt_size_t len);
    rt_err_t (*enable)(void *priv, rt_bool_t enable);
    rt_err_t (*disable)(void *priv);
};

struct rockchip_panel_ops
{
    rt_err_t (*get_timing)(void *priv, struct display_timing *tim);
    rt_err_t (*prepare)(void *priv);
    rt_err_t (*run_init)(void *priv, const struct rockchip_connector_ops *conn_ops, void *conn_priv);
    rt_err_t (*enable)(void *priv);
    rt_err_t (*disable)(void *priv);
};

rt_err_t display_timing_parse(struct rt_ofw_node *np, struct display_timing *tim);
void display_timing_derive(struct display_timing *tim);

rt_err_t display_route_resolve(struct rt_ofw_node *route_np, struct display_route *route);
rt_err_t display_route_get_vp_id(struct rt_ofw_node *vp_port_np, rt_uint32_t *vp_id);

rt_err_t rockchip_display_register_crtc(struct rt_ofw_node *np,
        const struct rockchip_crtc_ops *ops, void *priv);
rt_err_t rockchip_display_register_connector(struct rt_ofw_node *np,
        const struct rockchip_connector_ops *ops, void *priv);
rt_err_t rockchip_display_register_panel(struct rt_ofw_node *np,
        const struct rockchip_panel_ops *ops, void *priv);

rt_err_t rockchip_display_route_enable(struct rt_ofw_node *route_np);

#endif /* __ROCKCHIP_DISPLAY_H__ */
