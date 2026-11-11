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

#define DBG_TAG "display.route"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static const char *display_route_node_name(struct rt_ofw_node *np)
{
    return np ? rt_ofw_node_full_name(np) : "<no-node>";
}

static struct rt_ofw_node *display_graph_remote(struct rt_ofw_node *ep_np)
{
    return rt_ofw_parse_phandle(ep_np, "remote-endpoint", 0);
}

static struct rt_ofw_node *display_graph_device_from_ep(struct rt_ofw_node *ep_np,
        struct rt_ofw_node **out_port_np)
{
    struct rt_ofw_node *port_np, *dev_np;

    port_np = rt_ofw_get_parent(ep_np);

    if (out_port_np)
    {
        *out_port_np = port_np;
    }

    if (!port_np)
    {
        return RT_NULL;
    }

    dev_np = rt_ofw_get_parent(port_np);

    if (dev_np && rt_ofw_node_tag_equ(dev_np, "ports"))
    {
        dev_np = rt_ofw_get_parent(dev_np);
    }

    return dev_np;
}

static struct rt_ofw_node *display_graph_find_sink(struct rt_ofw_node *connector_np,
        struct rt_ofw_node *source_np)
{
    struct rt_ofw_node *child, *ports_np = RT_NULL;
    struct rt_ofw_node *port_np, *ep_np, *remote_ep, *sink_np;

    if (!connector_np)
    {
        return RT_NULL;
    }

    /* A DSI panel is commonly represented as a direct child of the host. */
    rt_ofw_foreach_available_child_node(connector_np, child)
    {
        if (rt_ofw_node_is_compatible(child, "simple-panel-dsi") ||
                rt_ofw_node_is_compatible(child, "simple-panel") ||
                rt_ofw_node_is_compatible(child, "rockchip,panel-simple"))
        {
            return child;
        }

        if (rt_ofw_node_tag_equ(child, "ports"))
        {
            ports_np = child;
        }
    }

    if (!ports_np)
    {
        return RT_NULL;
    }

    rt_ofw_foreach_available_child_node(ports_np, port_np)
    {
        rt_ofw_foreach_available_child_node(port_np, ep_np)
        {
            remote_ep = display_graph_remote(ep_np);

            if (!remote_ep)
            {
                continue;
            }

            sink_np = display_graph_device_from_ep(remote_ep, RT_NULL);

            if (sink_np && sink_np != source_np && sink_np != connector_np)
            {
                rt_ofw_node_put(remote_ep);
                return sink_np;
            }

            rt_ofw_node_put(remote_ep);
        }
    }

    return RT_NULL;
}

rt_err_t display_route_get_vp_id(struct rt_ofw_node *vp_port_np, rt_uint32_t *vp_id)
{
    rt_uint32_t reg;

    if (!vp_port_np || !vp_id)
    {
        return -RT_EINVAL;
    }

    if (!rt_ofw_prop_read_u32(vp_port_np, "reg", &reg))
    {
        *vp_id = reg;
        return RT_EOK;
    }

    *vp_id = 0;

    return RT_EOK;
}

rt_err_t display_route_resolve(struct rt_ofw_node *route_np, struct display_route *route)
{
    struct rt_ofw_node *ep_np, *port_np, *remote_ep, *remote_port;
    const char *route_name = display_route_node_name(route_np);

    if (!route_np || !route)
    {
        return -RT_EINVAL;
    }

    rt_memset(route, 0, sizeof(*route));
    route->route_np = route_np;

    ep_np = rt_ofw_parse_phandle(route_np, "connect", 0);

    if (!ep_np)
    {
        LOG_W("route %s: missing connect phandle", route_name);
        return -RT_EINVAL;
    }

    route->vop_np = display_graph_device_from_ep(ep_np, &port_np);

    if (!port_np)
    {
        LOG_W("route %s: endpoint %s has no port parent",
                route_name, display_route_node_name(ep_np));
        return -RT_ENOENT;
    }

    route->vp_port_np = port_np;

    if (!route->vop_np)
    {
        LOG_W("route %s: failed to resolve vop node", route_name);
        return -RT_ENOENT;
    }

    display_route_get_vp_id(route->vp_port_np, &route->vp_id);

    remote_ep = display_graph_remote(ep_np);

    if (!remote_ep)
    {
        LOG_W("route %s: endpoint %s missing remote-endpoint",
                route_name, display_route_node_name(ep_np));
        return -RT_ENOENT;
    }

    route->connector_np = display_graph_device_from_ep(remote_ep, &remote_port);

    if (!remote_port)
    {
        LOG_W("route %s: remote endpoint %s has no port parent",
                route_name, display_route_node_name(remote_ep));
        return -RT_ENOENT;
    }

    if (!route->connector_np)
    {
        LOG_W("route %s: remote port %s has no connector parent",
                route_name, display_route_node_name(remote_port));
        return -RT_ENOENT;
    }

    route->panel_np = display_graph_find_sink(route->connector_np, route->vop_np);

    LOG_D("route %s: resolved vop=%s vp%u connector=%s panel=%s",
            route_name, display_route_node_name(route->vop_np), route->vp_id,
            display_route_node_name(route->connector_np),
            display_route_node_name(route->panel_np));

    return RT_EOK;
}
