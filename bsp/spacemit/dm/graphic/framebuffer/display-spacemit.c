/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include "display-spacemit.h"

static rt_list_t spacemit_connectors = RT_LIST_OBJECT_INIT(spacemit_connectors);

rt_err_t spacemit_display_connector_register(
        struct spacemit_display_connector *connector,
        struct rt_ofw_node *np,
        const struct spacemit_display_connector_ops *ops,
        void *priv)
{
    struct spacemit_display_connector *entry;

    if (!connector || !np || !ops || !ops->get_timing || !ops->enable)
    {
        return -RT_EINVAL;
    }

    rt_list_for_each_entry(entry, &spacemit_connectors, list)
    {
        if (entry->ofw_node == np)
        {
            return -RT_EBUSY;
        }
    }

    rt_list_init(&connector->list);
    connector->ofw_node = rt_ofw_node_get(np);
    connector->ops = ops;
    connector->priv = priv;
    rt_list_insert_before(&spacemit_connectors, &connector->list);

    return RT_EOK;
}

void spacemit_display_connector_unregister(
        struct spacemit_display_connector *connector)
{
    if (!connector || !connector->ofw_node)
    {
        return;
    }

    rt_list_remove(&connector->list);
    rt_ofw_node_put(connector->ofw_node);
    connector->ofw_node = RT_NULL;
    connector->ops = RT_NULL;
    connector->priv = RT_NULL;
}

struct spacemit_display_connector *spacemit_display_connector_find(
        const char *compatible)
{
    struct spacemit_display_connector *connector;

    if (!compatible)
    {
        return RT_NULL;
    }

    rt_list_for_each_entry(connector, &spacemit_connectors, list)
    {
        if (rt_ofw_node_is_compatible(connector->ofw_node, compatible))
        {
            return connector;
        }
    }

    return RT_NULL;
}

static int spacemit_display_drivers_init(void)
{
    rt_err_t err;

    err = spacemit_hdmi_driver_register();
    if (err)
    {
        return err;
    }

    return spacemit_fb_driver_register();
}
INIT_DEVICE_EXPORT(spacemit_display_drivers_init);
