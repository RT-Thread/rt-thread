/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rpmsg.ns"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_err_t rpmsg_ns_rx_callback(struct rt_rpmsg_device *rdev,
        rt_uint32_t src, void *data, rt_size_t len)
{
    rt_err_t err = RT_EOK;
    struct rt_rpmsg_ns_msg *msg = data;
    struct rt_rpmsg_endpoint *ept;
    struct rt_rpmsg_endpoint_info info;

    if (len != sizeof(*msg))
    {
        LOG_E("Invalid MSG size = %d", len);

        return -RT_EINVAL;
    }

    /* Fixup the name */
    msg->name[RT_RPMSG_NAME_SIZE - 1] = '\0';
    rt_strncpy(info.name, msg->name, RT_RPMSG_NAME_SIZE);
    info.src = RT_RPMSG_ADDR_ANY;
    info.dst = rt_le32_to_cpu(msg->addr);

    LOG_D("name: %s, src: %u, dst: %u", info.name, info.src, info.dst);

    if (rt_le32_to_cpu(msg->flags) & RT_RPMSG_NS_DESTROY)
    {
        ept = rt_rpmsg_find_endpoint(rdev, &info);

        if (ept)
        {
            err = rt_rpmsg_destroy_endpoint(rdev, ept);
        }
        else
        {
            err = -RT_EEMPTY;
        }
    }
    else if (rt_le32_to_cpu(msg->flags) == RT_RPMSG_NS_CREATE)
    {
        ept = rt_rpmsg_create_endpoint(rdev, &info, RT_NULL);

        if (rt_is_err(ept))
        {
            err = rt_ptr_err(ept);
        }
    }
    else
    {
        LOG_E("Unsupported flags = %x", rt_le32_to_cpu(msg->flags));
    }

    if (err)
    {
        LOG_E("%s: name = %s, addr = %x flags = %d error = %s",
                rt_dm_dev_get_name(&rdev->parent),
                msg->name, msg->addr, msg->flags, rt_strerror(err));
    }

    return err;
}

static rt_err_t rpmsg_ns_probe(struct rt_rpmsg_device *rdev)
{
    struct rt_rpmsg_endpoint_info info;

    rt_strncpy(info.name, "name-service", RT_RPMSG_NAME_SIZE);
    info.src = RT_RPMSG_NS_ADDR;
    info.dst = RT_RPMSG_NS_ADDR;

    return rt_rpmsg_create_endpoint(rdev, &info, &rpmsg_ns_rx_callback)
            ? RT_EOK : -RT_ENOSYS;
}

static struct rt_rpmsg_device_id rpmsg_ns_ids[] =
{
    { .name = "rpmsg-name-service" },
    { /* sentinel */ }
};

static struct rt_rpmsg_driver rpmsg_ns_driver =
{
    .parent.parent =
    {
        .name = "rpmsg-name-service",
    },
    .ids = rpmsg_ns_ids,

    .probe = rpmsg_ns_probe,
};
RT_RPMSG_DRIVER_EXPORT(rpmsg_ns_driver);
