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

#define DBG_TAG "display.rk"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct rockchip_display_entity
{
    struct rt_ofw_node *np;
    const struct rockchip_crtc_ops *crtc_ops;
    const struct rockchip_connector_ops *conn_ops;
    const struct rockchip_panel_ops *panel_ops;
    void *priv;
    struct rockchip_display_entity *next;
};

static struct rockchip_display_entity *crtc_list;
static struct rockchip_display_entity *conn_list;
static struct rockchip_display_entity *panel_list;

static const char *display_node_name(struct rt_ofw_node *np)
{
    return np ? rt_ofw_node_full_name(np) : "<no-node>";
}

static rt_bool_t display_is_legacy_hdmi(struct rt_ofw_node *np)
{
    if (!np)
    {
        return RT_FALSE;
    }

    return rt_ofw_node_is_compatible(np, "rockchip,rk3568-dw-hdmi") ||
           rt_ofw_node_is_compatible(np, "rockchip,rk3528-dw-hdmi");
}

static rt_bool_t display_try_fallback_timing(const struct display_route *route,
        struct display_timing *tim)
{
    if (!route || !tim || !display_is_legacy_hdmi(route->connector_np))
    {
        return RT_FALSE;
    }

    rt_memset(tim, 0, sizeof(*tim));
    tim->pixelclock = 74250000;
    tim->hactive = 1280;
    tim->hfront_porch = 110;
    tim->hsync_len = 40;
    tim->hback_porch = 220;
    tim->vactive = 720;
    tim->vfront_porch = 5;
    tim->vsync_len = 5;
    tim->vback_porch = 20;
    tim->flags = DISPLAY_TIMING_F_PHSYNC | DISPLAY_TIMING_F_PVSYNC;
    display_timing_derive(tim);

    return RT_TRUE;
}

static rt_bool_t display_enable_connector_after_crtc(const struct display_route *route)
{
    RT_UNUSED(route);

    /*
     * Keep the standard DRM/U-Boot order: let the CRTC start driving a
     * stable mode first, then enable the connector/PHY.
     */
    return RT_TRUE;
}

static struct rockchip_display_entity *display_entity_find(struct rockchip_display_entity *head,
        struct rt_ofw_node *np)
{
    while (head)
    {
        if (head->np == np)
        {
            return head;
        }

        head = head->next;
    }

    return RT_NULL;
}

static rt_err_t display_entity_add(struct rockchip_display_entity **head,
        struct rt_ofw_node *np, void *priv,
        const struct rockchip_crtc_ops *crtc_ops,
        const struct rockchip_connector_ops *conn_ops,
        const struct rockchip_panel_ops *panel_ops)
{
    struct rockchip_display_entity *ent;

    if (display_entity_find(*head, np))
    {
        LOG_D("display entity %s already registered", display_node_name(np));
        return RT_EOK;
    }

    ent = rt_calloc(1, sizeof(*ent));

    if (!ent)
    {
        return -RT_ENOMEM;
    }

    ent->np = np;
    ent->priv = priv;
    ent->crtc_ops = crtc_ops;
    ent->conn_ops = conn_ops;
    ent->panel_ops = panel_ops;
    ent->next = *head;
    *head = ent;

    return RT_EOK;
}

rt_err_t rockchip_display_register_crtc(struct rt_ofw_node *np,
        const struct rockchip_crtc_ops *ops, void *priv)
{
    LOG_D("register crtc %s", display_node_name(np));
    return display_entity_add(&crtc_list, np, priv, ops, RT_NULL, RT_NULL);
}

rt_err_t rockchip_display_register_connector(struct rt_ofw_node *np,
        const struct rockchip_connector_ops *ops, void *priv)
{
    LOG_D("register connector %s", display_node_name(np));
    return display_entity_add(&conn_list, np, priv, RT_NULL, ops, RT_NULL);
}

rt_err_t rockchip_display_register_panel(struct rt_ofw_node *np,
        const struct rockchip_panel_ops *ops, void *priv)
{
    LOG_D("register panel %s", display_node_name(np));
    return display_entity_add(&panel_list, np, priv, RT_NULL, RT_NULL, ops);
}

rt_err_t rockchip_display_route_enable(struct rt_ofw_node *route_np)
{
    rt_err_t err;
    struct display_route route;
    struct display_timing tim;
    struct rockchip_display_entity *crtc, *conn, *panel;
    rt_bool_t conn_prepared = RT_FALSE;
    rt_bool_t panel_prepared = RT_FALSE;
    rt_bool_t panel_enabled = RT_FALSE;
    rt_bool_t conn_enabled = RT_FALSE;
    rt_bool_t crtc_configured = RT_FALSE;
    rt_bool_t crtc_enabled = RT_FALSE;

    if ((err = display_route_resolve(route_np, &route)))
    {
        LOG_W("route %s: resolve failed: %s", display_node_name(route_np), rt_strerror(err));
        return err;
    }

    crtc = display_entity_find(crtc_list, route.vop_np);
    conn = display_entity_find(conn_list, route.connector_np);
    panel = route.panel_np ? display_entity_find(panel_list, route.panel_np) : RT_NULL;

    LOG_D("route %s: crtc=%s connector=%s panel=%s",
            display_node_name(route_np),
            crtc ? "yes" : "no",
            conn ? "yes" : "no",
            panel ? "yes" : "no");

    if (!crtc || !crtc->crtc_ops)
    {
        LOG_W("route %s: no crtc driver for %s",
                display_node_name(route_np), display_node_name(route.vop_np));
        return -RT_ENOSYS;
    }

    if (!conn || !conn->conn_ops)
    {
        LOG_W("route %s: no connector driver for %s",
                display_node_name(route_np), display_node_name(route.connector_np));
        return -RT_ENOSYS;
    }

    if (route.panel_np && !panel)
    {
        LOG_W("route %s: panel node %s present but no panel driver",
                display_node_name(route_np), display_node_name(route.panel_np));
        return -RT_ENOSYS;
    }

    rt_memset(&tim, 0, sizeof(tim));

    if (panel && panel->panel_ops && panel->panel_ops->get_timing)
    {
        LOG_D("route %s: timing from panel driver %s",
                display_node_name(route_np), display_node_name(route.panel_np));
        panel->panel_ops->get_timing(panel->priv, &tim);
    }
    else if (route.panel_np)
    {
        LOG_D("route %s: timing from panel dt %s",
                display_node_name(route_np), display_node_name(route.panel_np));
        display_timing_parse(route.panel_np, &tim);
    }
    else
    {
        LOG_D("route %s: no panel timing source", display_node_name(route_np));
    }

    if (!tim.hactive || !tim.vactive)
    {
        if (display_try_fallback_timing(&route, &tim))
        {
            LOG_D("route %s: fallback timing 1280x720p60 for %s",
                    display_node_name(route_np),
                    display_node_name(route.connector_np));
        }
        else
        {
            LOG_W("route %s: invalid timing hactive=%u vactive=%u connector=%s panel=%s",
                    display_node_name(route_np), tim.hactive, tim.vactive,
                    display_node_name(route.connector_np),
                    display_node_name(route.panel_np));
            return -RT_EINVAL;
        }
    }

    if (conn && conn->conn_ops && conn->conn_ops->prepare)
    {
        if ((err = conn->conn_ops->prepare(conn->priv, route.vp_id, &tim)))
        {
            LOG_W("route %s: connector prepare failed: %s",
                    display_node_name(route_np), rt_strerror(err));
            return err;
        }
        conn_prepared = RT_TRUE;
    }

    if (panel && panel->panel_ops && panel->panel_ops->prepare)
    {
        if ((err = panel->panel_ops->prepare(panel->priv)))
        {
            LOG_W("route %s: panel prepare failed: %s",
                    display_node_name(route_np), rt_strerror(err));
            goto _fail_enable;
        }
        panel_prepared = RT_TRUE;
    }

    if (panel && panel->panel_ops && panel->panel_ops->run_init &&
            conn && conn->conn_ops && conn->conn_ops->transfer)
    {
        if ((err = panel->panel_ops->run_init(panel->priv, conn->conn_ops, conn->priv)))
        {
            LOG_W("route %s: panel init failed: %d", display_node_name(route_np), err);
            goto _fail_enable;
        }
    }

    if (conn && conn->conn_ops && conn->conn_ops->mode_set)
    {
        if ((err = conn->conn_ops->mode_set(conn->priv, &tim)))
        {
            LOG_W("route %s: connector mode_set failed: %s",
                    display_node_name(route_np), rt_strerror(err));
            goto _fail_enable;
        }
    }

    if (crtc->crtc_ops->mode_set)
    {
        LOG_D("route %s: crtc mode_set %ux%u on vp%u",
                display_node_name(route_np), tim.hactive, tim.vactive, route.vp_id);
        if ((err = crtc->crtc_ops->mode_set(crtc->priv, &route, &tim)))
        {
            LOG_W("route %s: crtc mode_set failed: %s",
                    display_node_name(route_np), rt_strerror(err));
            goto _fail_enable;
        }
        crtc_configured = RT_TRUE;
    }

    if (display_enable_connector_after_crtc(&route))
    {
        if (crtc->crtc_ops->enable)
        {
            err = crtc->crtc_ops->enable(crtc->priv, route.vp_id, RT_TRUE);
            if (err)
            {
                LOG_W("route %s: crtc enable failed: %s",
                        display_node_name(route_np), rt_strerror(err));
                goto _fail_enable;
            }
            crtc_enabled = RT_TRUE;
        }

        if (conn && conn->conn_ops && conn->conn_ops->enable)
        {
            err = conn->conn_ops->enable(conn->priv, RT_TRUE);
            if (err)
            {
                LOG_W("route %s: connector enable failed: %s",
                        display_node_name(route_np), rt_strerror(err));
                goto _fail_enable;
            }
            conn_enabled = RT_TRUE;
        }
    }
    else
    {
        if (conn && conn->conn_ops && conn->conn_ops->enable)
        {
            err = conn->conn_ops->enable(conn->priv, RT_TRUE);
            if (err)
            {
                LOG_W("route %s: connector enable failed: %s",
                        display_node_name(route_np), rt_strerror(err));
                goto _fail_enable;
            }
            conn_enabled = RT_TRUE;
        }

        if (crtc->crtc_ops->enable)
        {
            err = crtc->crtc_ops->enable(crtc->priv, route.vp_id, RT_TRUE);
            if (err)
            {
                LOG_W("route %s: crtc enable failed: %s",
                        display_node_name(route_np), rt_strerror(err));
                goto _fail_enable;
            }
            crtc_enabled = RT_TRUE;
        }
    }

    if (panel && panel->panel_ops && panel->panel_ops->enable)
    {
        err = panel->panel_ops->enable(panel->priv);
        if (err)
        {
            LOG_W("route %s: panel enable failed: %s",
                    display_node_name(route_np), rt_strerror(err));
            goto _fail_enable;
        }
        panel_enabled = RT_TRUE;
    }

    /*
     * Registering fb0 renders the boot logo and may commit several planes.
     * Keep those operations out of the hardware-enable phase: at this point
     * the complete VOP -> connector -> panel chain is already transmitting.
     */
    if (crtc->crtc_ops->complete)
    {
        err = crtc->crtc_ops->complete(crtc->priv, route.vp_id);
        if (err)
        {
            LOG_W("route %s: crtc completion failed: %s",
                    display_node_name(route_np), rt_strerror(err));
            goto _fail_enable;
        }
    }

    LOG_I("route %s: vp%u %ux%u via %s",
            display_node_name(route_np), route.vp_id, tim.hactive, tim.vactive,
            display_node_name(route.connector_np));

    return RT_EOK;

_fail_enable:
    if ((panel_prepared || panel_enabled) && panel && panel->panel_ops &&
            panel->panel_ops->disable)
    {
        panel->panel_ops->disable(panel->priv);
    }
    if ((conn_prepared || conn_enabled) && conn && conn->conn_ops &&
            conn->conn_ops->disable)
    {
        conn->conn_ops->disable(conn->priv);
    }
    if ((crtc_configured || crtc_enabled) && crtc->crtc_ops->enable)
    {
        crtc->crtc_ops->enable(crtc->priv, route.vp_id, RT_FALSE);
    }

    return err;
}

static struct rt_platform_device *display_pdev;

enum display_route_scan_pass
{
    DISPLAY_ROUTE_CONNECTED,
    DISPLAY_ROUTE_FIXED,
    DISPLAY_ROUTE_FALLBACK,
};

enum display_route_policy
{
    DISPLAY_POLICY_AUTO,
    DISPLAY_POLICY_HDMI,
    DISPLAY_POLICY_DSI0,
    DISPLAY_POLICY_DSI1,
    DISPLAY_POLICY_EXTEND,
    DISPLAY_POLICY_MIRROR,
};

static struct rockchip_display_entity *display_route_find_connector(
        struct rt_ofw_node *route_np)
{
    struct rt_ofw_node *ep_np = RT_NULL;
    struct rt_ofw_node *remote_np = RT_NULL;
    struct rt_ofw_node *port_np = RT_NULL;
    struct rt_ofw_node *parent_np = RT_NULL;
    struct rt_ofw_node *connector_np = RT_NULL;
    struct rockchip_display_entity *conn = RT_NULL;

    ep_np = rt_ofw_parse_phandle(route_np, "connect", 0);
    if (!ep_np)
    {
        goto out;
    }

    remote_np = rt_ofw_parse_phandle(ep_np, "remote-endpoint", 0);
    if (!remote_np)
    {
        goto out;
    }

    port_np = rt_ofw_get_parent(remote_np);
    parent_np = rt_ofw_get_parent(port_np);
    if (parent_np && rt_ofw_node_tag_equ(parent_np, "ports"))
    {
        connector_np = rt_ofw_get_parent(parent_np);
    }
    else
    {
        connector_np = parent_np;
        parent_np = RT_NULL;
    }

    conn = display_entity_find(conn_list, connector_np);

out:
    rt_ofw_node_put(connector_np);
    rt_ofw_node_put(parent_np);
    rt_ofw_node_put(port_np);
    rt_ofw_node_put(remote_np);
    rt_ofw_node_put(ep_np);

    return conn;
}

static rt_err_t display_route_scan_vp_id(struct rt_ofw_node *route_np,
        rt_uint32_t *vp_id)
{
    rt_err_t err = -RT_ENOENT;
    struct rt_ofw_node *ep_np;
    struct rt_ofw_node *port_np;

    ep_np = rt_ofw_parse_phandle(route_np, "connect", 0);
    if (!ep_np)
    {
        return err;
    }

    port_np = rt_ofw_get_parent(ep_np);
    if (port_np)
    {
        err = display_route_get_vp_id(port_np, vp_id);
    }

    rt_ofw_node_put(port_np);
    rt_ofw_node_put(ep_np);

    return err;
}

static rt_bool_t display_route_is_legacy_hdmi(struct rt_ofw_node *route_np)
{
    struct rockchip_display_entity *conn;

    conn = display_route_find_connector(route_np);

    return conn && display_is_legacy_hdmi(conn->np);
}

static int display_route_dsi_id(struct rt_ofw_node *route_np)
{
    struct rockchip_display_entity *conn;

    conn = display_route_find_connector(route_np);
    if (!conn || !conn->np ||
            (!rt_ofw_node_is_compatible(conn->np, "rockchip,rk3568-mipi-dsi") &&
             !rt_ofw_node_is_compatible(conn->np, "rockchip,rk3588-mipi-dsi")))
    {
        return -1;
    }

    return rt_ofw_get_alias_id(conn->np, "dsi");
}

static enum display_route_policy display_route_get_policy(void)
{
    const char *value = rt_ofw_bootargs_select("rockchip.display=", 0);

    if (!value || !value[0] || !rt_strcmp(value, "auto"))
    {
        return DISPLAY_POLICY_AUTO;
    }
    if (!rt_strcmp(value, "hdmi"))
    {
        return DISPLAY_POLICY_HDMI;
    }
    if (!rt_strcmp(value, "dsi0"))
    {
        return DISPLAY_POLICY_DSI0;
    }
    if (!rt_strcmp(value, "dsi1"))
    {
        return DISPLAY_POLICY_DSI1;
    }
    if (!rt_strcmp(value, "extend"))
    {
        return DISPLAY_POLICY_EXTEND;
    }
    if (!rt_strcmp(value, "mirror"))
    {
        return DISPLAY_POLICY_MIRROR;
    }

    LOG_W("unknown rockchip.display=%s, use auto", value);

    return DISPLAY_POLICY_AUTO;
}

static const char *display_route_policy_name(enum display_route_policy policy)
{
    switch (policy)
    {
    case DISPLAY_POLICY_HDMI:
        return "hdmi";
    case DISPLAY_POLICY_DSI0:
        return "dsi0";
    case DISPLAY_POLICY_DSI1:
        return "dsi1";
    case DISPLAY_POLICY_EXTEND:
        return "extend";
    case DISPLAY_POLICY_MIRROR:
        return "mirror";
    case DISPLAY_POLICY_AUTO:
    default:
        return "auto";
    }
}

static rt_bool_t display_route_policy_allows(struct rt_ofw_node *route_np,
        enum display_route_policy policy)
{
    switch (policy)
    {
    case DISPLAY_POLICY_HDMI:
        return display_route_is_legacy_hdmi(route_np);
    case DISPLAY_POLICY_DSI0:
        return display_route_dsi_id(route_np) == 0;
    case DISPLAY_POLICY_DSI1:
        return display_route_dsi_id(route_np) == 1;
    case DISPLAY_POLICY_AUTO:
    case DISPLAY_POLICY_EXTEND:
    case DISPLAY_POLICY_MIRROR:
    default:
        return RT_TRUE;
    }
}

static rt_bool_t display_route_matches(struct rt_ofw_node *route_np,
        enum display_route_scan_pass pass)
{
    rt_err_t err;
    rt_bool_t connected;
    struct rockchip_display_entity *conn;

    conn = display_route_find_connector(route_np);
    if (!conn || !conn->conn_ops || !conn->conn_ops->detect)
    {
        return pass == DISPLAY_ROUTE_FIXED;
    }

    if (pass == DISPLAY_ROUTE_FIXED)
    {
        return RT_FALSE;
    }

    err = conn->conn_ops->detect(conn->priv, &connected);
    if (err)
    {
        LOG_D("route %s: connector detect failed: %s",
                display_node_name(route_np), rt_strerror(err));
        return pass == DISPLAY_ROUTE_FALLBACK;
    }

    LOG_D("route %s: connector is %s",
            display_node_name(route_np), connected ? "connected" : "disconnected");

    return connected ? pass == DISPLAY_ROUTE_CONNECTED :
            pass == DISPLAY_ROUTE_FALLBACK;
}

static rt_uint32_t display_enable_routes(void)
{
    rt_err_t err;
    rt_uint32_t vp_id;
    rt_uint32_t enabled_vps = 0;
    rt_uint32_t enabled_count = 0;
    enum display_route_policy policy;
    enum display_route_scan_pass pass;
    struct rt_ofw_node *route_np, *child;
    struct rt_device *dev;

    if (!display_pdev)
    {
        LOG_W("display-subsystem route init: device not ready");
        return 0;
    }

    dev = &display_pdev->parent;
    route_np = rt_ofw_get_child_by_tag(dev->ofw_node, "route");

    if (!route_np)
    {
        LOG_W("display-subsystem route init: no route node");
        return 0;
    }

    LOG_D("display-subsystem route init: scan routes");
    policy = display_route_get_policy();
    LOG_I("display policy: %s", display_route_policy_name(policy));

    /*
     * Connected hot-plug outputs are enabled first so they receive fb0.
     * Fixed panels are then enabled on any remaining VP and receive fb1+.
     * Explicit single-output policies still filter the route list above.
     */
    for (pass = DISPLAY_ROUTE_CONNECTED; pass <= DISPLAY_ROUTE_FALLBACK; ++pass)
    {
        if (pass == DISPLAY_ROUTE_FALLBACK && enabled_count)
        {
            break;
        }
        rt_ofw_foreach_child_node(route_np, child)
        {
            if (!rt_ofw_node_is_available(child))
            {
                LOG_D("route %s: disabled, skip", display_node_name(child));
                continue;
            }

            if (!display_route_policy_allows(child, policy))
            {
                continue;
            }

            if (!display_route_matches(child, pass))
            {
                continue;
            }

            if (display_route_scan_vp_id(child, &vp_id))
            {
                LOG_D("route %s: cannot resolve VP, skip", display_node_name(child));
                continue;
            }

            if (vp_id >= 32 || (enabled_vps & RT_BIT(vp_id)))
            {
                LOG_D("route %s: vp%u already active, skip",
                        display_node_name(child), vp_id);
                continue;
            }

            LOG_D("route %s: enabling", display_node_name(child));
            err = rockchip_display_route_enable(child);

            if (err)
            {
                LOG_W("route %s: enable failed: %s",
                        display_node_name(child), rt_strerror(err));
            }
            else
            {
                enabled_vps |= RT_BIT(vp_id);
                enabled_count++;
            }
        }
    }

    return enabled_count;
}

static rt_err_t display_subsys_probe(struct rt_platform_device *pdev)
{
    display_pdev = pdev;
    LOG_D("display-subsystem probed");
    return RT_EOK;
}

static int rockchip_display_routes_init(void)
{
    /*
     * DSI retries deferred probing at component level 4. Enable every display
     * policy afterwards, but before environment level 5 can wait for rootfs.
     */
    display_enable_routes();

    return 0;
}
INIT_EXPORT(rockchip_display_routes_init, "4.1");

static const struct rt_ofw_node_id display_subsys_ids[] =
{
    { .compatible = "rockchip,display-subsystem" },
    { /* sentinel */ }
};

static struct rt_platform_driver display_subsys_driver =
{
    .name = "rockchip-display",
    .ids = display_subsys_ids,
    .probe = display_subsys_probe,
};
RT_PLATFORM_DRIVER_EXPORT(display_subsys_driver);
