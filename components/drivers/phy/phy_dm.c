/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     GuEe-GUI     first version
 */

#include <rtdevice.h>

#ifdef RT_USING_OFW
static struct rt_phy_device *ofw_phy_get_by_index(struct rt_ofw_node *np, int index)
{
    struct rt_ofw_cell_args phy_args;
    struct rt_phy_device *phy_dev = RT_NULL;

    if (!rt_ofw_parse_phandle_cells(np, "phys", "#phy-cells", index, &phy_args))
    {
        phy_dev = rt_ofw_data(phy_args.data);

        rt_ofw_node_put(phy_args.data);

        if (phy_dev)
        {
            if (phy_dev->ops->ofw_parse)
            {
                phy_dev->ops->ofw_parse(phy_dev, &phy_args);
            }
        }
    }

    return phy_dev;
}
#else
static struct rt_phy_device *ofw_phy_get_by_index(struct rt_ofw_node *np, int index)
{
    return RT_NULL;
}
#endif /* RT_USING_OFW */

struct rt_phy_device *rt_phy_get_by_index(struct rt_device *dev, int index)
{
    struct rt_phy_device *phy_dev;

    if (!dev || index < 0)
    {
        return RT_NULL;
    }

    if (dev->ofw_node)
    {
        phy_dev = ofw_phy_get_by_index(dev->ofw_node, index);
    }

    return phy_dev;
}

struct rt_phy_device *rt_phy_get_by_name(struct rt_device *dev, const char *id)
{
    int index;

    if (!dev || !id)
    {
        return RT_NULL;
    }

    index = rt_dm_dev_prop_index_of_string(dev, "phy-names", id);

    return rt_phy_get_by_index(dev, index);
}
