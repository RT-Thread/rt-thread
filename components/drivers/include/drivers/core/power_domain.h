/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#ifndef __RT_DM_POWER_DOMAIN_H__
#define __RT_DM_POWER_DOMAIN_H__

#include <rthw.h>
#include <rtthread.h>

#include <ref.h>

#define RT_POWER_DOMAIN_OBJ_NAME        "PMD"
#define RT_POWER_DOMAIN_PROXY_OBJ_NAME  "PMP"

struct rt_ofw_node;
struct rt_ofw_cell_args;

struct rt_dm_power_domain_unit
{
    rt_list_t list;

    int id;
    struct rt_dm_power_domain *domain;
};

struct rt_dm_power_domain_proxy
{
    struct rt_object parent;

    struct rt_dm_power_domain *(*ofw_parse)(struct rt_dm_power_domain_proxy *proxy,
            struct rt_ofw_cell_args *args);
};

struct rt_dm_power_domain
{
    struct rt_object parent;

    struct rt_device *dev;
    struct rt_dm_power_domain *parent_domain;

    rt_list_t list;
    rt_list_t child_nodes;
    rt_list_t unit_nodes;

    struct rt_ref ref;
    struct rt_spinlock lock;

    rt_err_t (*power_on)(struct rt_dm_power_domain *domain);
    rt_err_t (*power_off)(struct rt_dm_power_domain *domain);
    rt_err_t (*attach_dev)(struct rt_dm_power_domain *domain, struct rt_device *dev);
    rt_err_t (*detach_dev)(struct rt_dm_power_domain *domain, struct rt_device *dev);

    void *pirv;
};

void rt_dm_power_domain_proxy_default_name(struct rt_dm_power_domain_proxy *proxy);
void rt_dm_power_domain_proxy_ofw_bind(struct rt_dm_power_domain_proxy *proxy,
        struct rt_ofw_node *np);

rt_err_t rt_dm_power_domain_register(struct rt_dm_power_domain *domain);
rt_err_t rt_dm_power_domain_unregister(struct rt_dm_power_domain *domain);

rt_err_t rt_dm_power_domain_register_child(struct rt_dm_power_domain *domain,
        struct rt_dm_power_domain *child_domain);
rt_err_t rt_dm_power_domain_unregister_child(struct rt_dm_power_domain *domain,
        struct rt_dm_power_domain *child_domain);

rt_err_t rt_dm_power_domain_power_on(struct rt_dm_power_domain *domain);
rt_err_t rt_dm_power_domain_power_off(struct rt_dm_power_domain *domain);

struct rt_dm_power_domain *rt_dm_power_domain_get_by_index(struct rt_device *dev, int index);
struct rt_dm_power_domain *rt_dm_power_domain_get_by_name(struct rt_device *dev, const char *name);
rt_err_t rt_dm_power_domain_put(struct rt_dm_power_domain *domain);

rt_err_t rt_dm_power_domain_attach(struct rt_device *dev, rt_bool_t on);
rt_err_t rt_dm_power_domain_detach(struct rt_device *dev, rt_bool_t off);

#endif /* __RT_DM_POWER_DOMAIN_H__ */
