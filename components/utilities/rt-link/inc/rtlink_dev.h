/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-15     Sherman      the first version
 */

#include <rtthread.h>
#include <rtlink.h>

#define RT_LINK_RX_NONBLOCKING       0x1000
#define RT_LINK_RX_BLOCKING          0x2000
#define RT_LINK_TX_NONBLOCKING       0x4000
#define RT_LINK_TX_BLOCKING          0x8000
#define RT_LINK_DEVICE_MASK          0xf000

struct rtlink_recv_list
{
    void *data;
    rt_size_t size;
    rt_size_t index;
    struct rt_slist_node list;
};

struct rt_link_device
{
    struct rt_device parent;
    struct rt_link_service service;
    struct rt_slist_node recv_head; /* recv data list, struct rtlink_recv_list  */
};

/*
 * rtlink device register
 */
rt_err_t rt_link_dev_register(struct rt_link_device *rtlink,
                              const char              *name,
                              rt_uint32_t              flag,
                              void                    *data);
