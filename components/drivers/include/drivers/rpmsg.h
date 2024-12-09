/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __RPMSG_H__
#define __RPMSG_H__

#include <rthw.h>
#include <rtthread.h>

#include <drivers/core/dm.h>
#include <drivers/core/driver.h>
#include <drivers/byteorder.h>

#define RT_DEVICE_CTRL_RPMSG_CREATE_EPT     (RT_DEVICE_CTRL_BASE(Char) + 'R' + 1)
#define RT_DEVICE_CTRL_RPMSG_DESTROY_EPT    (RT_DEVICE_CTRL_BASE(Char) + 'R' + 2)
#define RT_DEVICE_CTRL_RPMSG_DATA_OVERWRITE (RT_DEVICE_CTRL_BASE(Char) + 'R' + 3)

struct rt_rpmsg_device_id
{
#define RT_RPMSG_NAME_SIZE 32
    char name[RT_RPMSG_NAME_SIZE];

    const void *data;
};

struct rt_rpmsg_ops;
struct rt_rpmsg_endpoint;
struct rt_rpmsg_endpoint_info;

struct rt_rpmsg_device
{
    struct rt_device parent;

    struct rt_rpmsg_device_id id;
    rt_list_t ept_nodes;
    struct rt_spinlock lock;

    const struct rt_rpmsg_ops *ops;
    void *priv;
};

struct rt_rpmsg_driver
{
    struct rt_driver parent;

    const struct rt_rpmsg_device_id *ids;

    rt_err_t (*probe)(struct rt_rpmsg_device *rdev);
    rt_err_t (*remove)(struct rt_rpmsg_device *rdev);
    rt_err_t (*rx_callback)(struct rt_rpmsg_device *rdev,
            rt_uint32_t src, void *data, rt_size_t len);
};

typedef rt_err_t (*rt_rpmsg_rx_callback)(struct rt_rpmsg_device *rdev,
        rt_uint32_t src, void *data, rt_size_t len);

struct rt_rpmsg_ops
{
    rt_err_t (*create_endpoint)(struct rt_rpmsg_device *, struct rt_rpmsg_endpoint *,
            struct rt_rpmsg_endpoint_info *info);
    rt_err_t (*destroy_endpoint)(struct rt_rpmsg_device *, struct rt_rpmsg_endpoint *);
    rt_err_t (*send)(struct rt_rpmsg_device *, rt_uint32_t src, rt_uint32_t dst,
            const void *data, rt_size_t len, rt_int32_t timeout);
};

struct rt_rpmsg_endpoint_info
{
    char name[RT_RPMSG_NAME_SIZE];

#define RT_RPMSG_ADDR_ANY   0xffffffff
    rt_uint32_t src;
    rt_uint32_t dst;
};

struct rt_rpmsg_endpoint
{
    rt_list_t list;
    struct rt_rpmsg_device *rdev;

    struct rt_rpmsg_endpoint_info info;
    rt_rpmsg_rx_callback rx_callback;

    struct rt_spinlock lock;
    void *sysdata;
    void *priv;
};

enum rt_rpmsg_ns_flags
{
    RT_RPMSG_NS_CREATE = 0,
    RT_RPMSG_NS_DESTROY = 1,
};

struct rt_rpmsg_ns_msg
{
    char name[RT_RPMSG_NAME_SIZE];

#define RT_RPMSG_NS_ADDR    0x35        /* 0x35 -> 53 */
    rt_uint32_t addr;
    rt_uint32_t flags;
} rt_packed;

enum
{
    RT_RPMSG_MODE_MASTER,
    RT_RPMSG_MODE_SLAVE,

    RT_RPMSG_MODE_MAX,
};

rt_uint32_t rt_rpmsg_mode(void);

struct rt_rpmsg_endpoint *rt_rpmsg_create_endpoint(struct rt_rpmsg_device *,
        struct rt_rpmsg_endpoint_info *info, rt_rpmsg_rx_callback rx_cb);
rt_err_t rt_rpmsg_destroy_endpoint(struct rt_rpmsg_device *,
        struct rt_rpmsg_endpoint *);
struct rt_rpmsg_endpoint *rt_rpmsg_find_endpoint(struct rt_rpmsg_device *,
        struct rt_rpmsg_endpoint_info *info);

rt_err_t rt_rpmsg_send(struct rt_rpmsg_endpoint *,
        const void *data, rt_size_t len);
rt_err_t rt_rpmsg_sendto(struct rt_rpmsg_endpoint *, rt_uint32_t dst,
        const void *data, rt_size_t len);

rt_err_t rt_rpmsg_send_wait(struct rt_rpmsg_endpoint *,
        const void *data, rt_size_t len, rt_int32_t timeout);
rt_err_t rt_rpmsg_sendto_wait(struct rt_rpmsg_endpoint *, rt_uint32_t dst,
        const void *data, rt_size_t len, rt_int32_t timeout);

rt_err_t rt_rpmsg_driver_register(struct rt_rpmsg_driver *rdrv);
rt_err_t rt_rpmsg_device_register(struct rt_rpmsg_device *rdev);

#define RT_RPMSG_DRIVER_EXPORT(driver)  RT_DRIVER_EXPORT(driver, rpmsg, BUILIN)

#endif /* __RPMSG_H__ */
