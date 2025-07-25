/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-08     zhujiale    the first version
 */
#include "mdio.h"

static struct rt_list_node mdio_list;

struct mii_bus *rt_mdio_get_bus_by_name(const char *busname)
{
    struct rt_list_node *entry;
    struct mii_bus *bus;

    if (!busname)
    {
        rt_kprintf("NULL bus name!\n");
        return RT_NULL;
    }

    rt_list_for_each(entry, &mdio_list)
    {
        bus = rt_container_of(entry, struct mii_bus, node);
        if (!strcmp(bus->name, busname))
            return bus;
    }

    return RT_NULL;
}

struct mii_bus *rt_mdio_alloc(void)
{
    struct mii_bus *mii;
    mii = rt_malloc(sizeof(struct mii_bus));
    if (!mii)
        return RT_NULL;

    rt_list_init(&mii->node);
    return mii;
}

rt_err_t rt_mdio_register(struct mii_bus *bus)
{
    if (!bus)
        return -RT_ERROR;

    if(rt_mdio_get_bus_by_name(bus->name))
    {
        rt_kprintf("mdio bus %s already exist!\n", bus->name);
        return -RT_ERROR;
    }

    rt_list_insert_before(&mdio_list, &bus->node);
    return RT_EOK;
}

rt_err_t rt_mdio_unregister(struct mii_bus *bus)
{
    if (!bus)
        return -RT_ERROR;

    rt_list_remove(&bus->node);
    return RT_EOK;
}

static int mdio_init(void)
{
    rt_list_init(&mdio_list);
    return 0;
}
INIT_CORE_EXPORT(mdio_init);
