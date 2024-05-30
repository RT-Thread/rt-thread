/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-24     GuEe-GUI     the first version
 */

#include <rtdevice.h>

#define DBG_TAG "rtdm.power_domain"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/ofw.h>

void rt_dm_power_domain_proxy_default_name(struct rt_dm_power_domain_proxy *proxy)
{
#if RT_NAME_MAX > 0
    rt_strncpy(proxy->parent.name, RT_POWER_DOMAIN_OBJ_NAME, RT_NAME_MAX);
#else
    proxy->parent.name = RT_POWER_DOMAIN_OBJ_NAME;
#endif
}

void rt_dm_power_domain_proxy_ofw_bind(struct rt_dm_power_domain_proxy *proxy,
        struct rt_ofw_node *np)
{
    if (!proxy || !proxy->ofw_parse || !np)
    {
        return;
    }

    rt_dm_power_domain_proxy_default_name(proxy);
    rt_ofw_data(np) = proxy;
}

static void dm_power_domain_init(struct rt_dm_power_domain *domain)
{
#if RT_NAME_MAX > 0
    rt_strncpy(domain->parent.name, RT_POWER_DOMAIN_OBJ_NAME, RT_NAME_MAX);
#else
    domain->parent.name = RT_POWER_DOMAIN_OBJ_NAME;
#endif

    domain->parent_domain = RT_NULL;

    rt_list_init(&domain->list);
    rt_list_init(&domain->child_nodes);
    rt_list_init(&domain->unit_nodes);

    rt_ref_init(&domain->ref);
    rt_spin_lock_init(&domain->lock);
}

static rt_bool_t dm_power_domain_is_free(struct rt_dm_power_domain *domain)
{
    return rt_ref_read(&domain->ref) == 1 && !rt_list_isempty(&domain->child_nodes);
}

rt_err_t rt_dm_power_domain_register(struct rt_dm_power_domain *domain)
{
    if (!domain)
    {
        return -RT_EINVAL;
    }

    dm_power_domain_init(domain);

    return RT_EOK;
}

rt_err_t rt_dm_power_domain_unregister(struct rt_dm_power_domain *domain)
{
    rt_err_t err = RT_EOK;

    if (!domain)
    {
        return -RT_EINVAL;
    }

    if (!dm_power_domain_is_free(domain))
    {
        return -RT_EBUSY;
    }

    if (domain->parent_domain)
    {
        err = rt_dm_power_domain_unregister_child(domain->parent_domain, domain);
    }

    return err;
}

rt_err_t rt_dm_power_domain_register_child(struct rt_dm_power_domain *domain,
        struct rt_dm_power_domain *child_domain)
{
    if (!domain || !child_domain)
    {
        return -RT_EINVAL;
    }

    dm_power_domain_init(child_domain);
    child_domain->parent_domain = domain;

    return RT_EOK;
}

rt_err_t rt_dm_power_domain_unregister_child(struct rt_dm_power_domain *domain,
        struct rt_dm_power_domain *child_domain)
{
    rt_err_t err = RT_EOK;

    if (!domain || !child_domain)
    {
        return -RT_EINVAL;
    }

    rt_hw_spin_lock(&domain->lock.lock);

    if (dm_power_domain_is_free(domain))
    {
        rt_list_remove(&child_domain->list);
    }
    else
    {
        err = -RT_EBUSY;
    }

    rt_hw_spin_unlock(&domain->lock.lock);

    return err;
}

rt_err_t rt_dm_power_domain_power_on(struct rt_dm_power_domain *domain)
{
    rt_err_t err = RT_EOK;
    struct rt_dm_power_domain *child_domain;

    if (!domain)
    {
        return -RT_EINVAL;
    }

    rt_hw_spin_lock(&domain->lock.lock);

    if (rt_ref_read(&domain->ref) == 1)
    {
        err = domain->power_on(domain);
    }

    if (!err)
    {
        struct rt_dm_power_domain *fail_domain = RT_NULL;

        rt_list_for_each_entry(child_domain, &domain->child_nodes, list)
        {
            err = rt_dm_power_domain_power_on(child_domain);

            if (err)
            {
                fail_domain = child_domain;
                break;
            }
        }

        if (fail_domain)
        {
            rt_list_for_each_entry(child_domain, &domain->child_nodes, list)
            {
                if (child_domain == fail_domain)
                {
                    break;
                }

                rt_dm_power_domain_power_off(child_domain);
            }
        }
    }

    rt_hw_spin_unlock(&domain->lock.lock);

    if (!err)
    {
        rt_ref_get(&domain->ref);
    }

    return err;
}

static void dm_power_domain_release(struct rt_ref *r)
{
    struct rt_dm_power_domain *domain = rt_container_of(r, struct rt_dm_power_domain, ref);

    if (domain->dev)
    {
        LOG_E("%s power domain is release", rt_dm_dev_get_name(domain->dev));
    }

    RT_ASSERT(0);
}

rt_err_t rt_dm_power_domain_power_off(struct rt_dm_power_domain *domain)
{
    rt_err_t err;
    struct rt_dm_power_domain *child_domain;

    if (!domain)
    {
        return -RT_EINVAL;
    }

    rt_ref_put(&domain->ref, dm_power_domain_release);

    rt_hw_spin_lock(&domain->lock.lock);

    if (rt_ref_read(&domain->ref) == 1)
    {
        err = domain->power_off(domain);
    }
    else
    {
        err = -RT_EBUSY;
    }

    if (!err)
    {
        struct rt_dm_power_domain *fail_domain = RT_NULL;

        rt_list_for_each_entry(child_domain, &domain->child_nodes, list)
        {
            err = rt_dm_power_domain_power_off(child_domain);

            if (err)
            {
                fail_domain = child_domain;
                break;
            }
        }

        if (fail_domain)
        {
            rt_list_for_each_entry(child_domain, &domain->child_nodes, list)
            {
                if (child_domain == fail_domain)
                {
                    break;
                }

                rt_dm_power_domain_power_on(child_domain);
            }
        }
    }

    rt_hw_spin_unlock(&domain->lock.lock);

    if (err)
    {
        rt_ref_get(&domain->ref);
    }

    return err;
}

#ifdef RT_USING_OFW
static struct rt_dm_power_domain *ofw_find_power_domain(struct rt_device *dev,
        int index, struct rt_ofw_cell_args *args)
{
    struct rt_object *obj;
    struct rt_dm_power_domain_proxy *proxy;
    struct rt_dm_power_domain *domain = RT_NULL;
    struct rt_ofw_node *np = dev->ofw_node, *power_domain_np;

    if (!rt_ofw_parse_phandle_cells(np, "power-domains", "#power-domain-cells",
            index, args))
    {
        power_domain_np = args->data;

        if (power_domain_np && (obj = rt_ofw_data(power_domain_np)))
        {
            if (!rt_strcmp(obj->name, RT_POWER_DOMAIN_OBJ_NAME))
            {
                proxy = rt_container_of(obj, struct rt_dm_power_domain_proxy, parent);
                domain = proxy->ofw_parse(proxy, args);
            }
            else if (!rt_strcmp(obj->name, RT_POWER_DOMAIN_OBJ_NAME))
            {
                domain = rt_container_of(obj, struct rt_dm_power_domain, parent);
            }
            else if ((obj = rt_ofw_parse_object(power_domain_np,
                    RT_POWER_DOMAIN_PROXY_OBJ_NAME, "#power-domain-cells")))
            {
                proxy = rt_container_of(obj, struct rt_dm_power_domain_proxy, parent);
                domain = proxy->ofw_parse(proxy, args);
            }
            else if ((obj = rt_ofw_parse_object(power_domain_np,
                    RT_POWER_DOMAIN_OBJ_NAME, "#power-domain-cells")))
            {
                domain = rt_container_of(obj, struct rt_dm_power_domain, parent);
            }

            rt_ofw_node_put(power_domain_np);
        }
    }

    return domain;
}
#else
rt_inline struct rt_dm_power_domain *ofw_find_power_domain(struct rt_device *dev,
        int index, struct rt_ofw_cell_args *args)
{
    return RT_NULL;
}
#endif /* RT_USING_OFW */

struct rt_dm_power_domain *rt_dm_power_domain_get_by_index(struct rt_device *dev,
        int index)
{
    struct rt_ofw_cell_args args;
    struct rt_dm_power_domain *domain;

    if (!dev || index < 0)
    {
        return RT_NULL;
    }

    if ((domain = ofw_find_power_domain(dev, index, &args)))
    {
        goto _end;
    }

_end:
    return domain;
}

struct rt_dm_power_domain *rt_dm_power_domain_get_by_name(struct rt_device *dev,
        const char *name)
{
    int index;

    if (!dev || !name)
    {
        return RT_NULL;
    }

    if ((index = rt_dm_dev_prop_index_of_string(dev, "power-domain-names", name)) < 0)
    {
        LOG_E("%s find power domain %s not found", rt_dm_dev_get_name(dev));

        return RT_NULL;
    }

    return rt_dm_power_domain_get_by_index(dev, index);
}

rt_err_t rt_dm_power_domain_put(struct rt_dm_power_domain *domain)
{
    if (!domain)
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

rt_err_t rt_dm_power_domain_attach(struct rt_device *dev, rt_bool_t on)
{
    int id = -1;
    rt_err_t err = RT_EOK;
    struct rt_ofw_cell_args args;
    struct rt_dm_power_domain *domain;
    struct rt_dm_power_domain_unit *unit;

    if (!dev)
    {
        return -RT_EINVAL;
    }

    /* We only attach the first one, get domains self if there are multiple domains */
    if ((domain = ofw_find_power_domain(dev, 0, &args)))
    {
        id = args.args[0];
    }

    if (!domain)
    {
        return -RT_EEMPTY;
    }

    unit = rt_malloc(sizeof(*unit));

    if (!unit)
    {
        return -RT_ENOMEM;
    }

    rt_list_init(&unit->list);
    unit->id = id;
    unit->domain = domain;

    dev->power_domain_unit = unit;

    rt_hw_spin_lock(&domain->lock.lock);

    if (domain->attach_dev)
    {
        err = domain->attach_dev(domain, dev);
    }

    if (!err)
    {
        rt_list_insert_before(&domain->unit_nodes, &unit->list);
    }

    rt_hw_spin_unlock(&domain->lock.lock);

    if (err)
    {
        dev->power_domain_unit = RT_NULL;
        rt_free(unit);

        return err;
    }

    if (on)
    {
        err = rt_dm_power_domain_power_on(domain);
    }

    return err;
}

rt_err_t rt_dm_power_domain_detach(struct rt_device *dev, rt_bool_t off)
{
    rt_err_t err = RT_EOK;
    struct rt_dm_power_domain *domain;
    struct rt_dm_power_domain_unit *unit;

    if (!dev || !dev->power_domain_unit)
    {
        return -RT_EINVAL;
    }

    unit = dev->power_domain_unit;
    domain = unit->domain;

    rt_hw_spin_lock(&domain->lock.lock);

    if (domain->detach_dev)
    {
        err = domain->detach_dev(domain, dev);
    }

    if (!err)
    {
        rt_list_remove(&unit->list);
    }

    rt_hw_spin_unlock(&domain->lock.lock);

    if (err)
    {
        return err;
    }

    rt_free(unit);
    dev->power_domain_unit = RT_NULL;

    if (off)
    {
        err = rt_dm_power_domain_power_off(domain);
    }

    return err;
}
