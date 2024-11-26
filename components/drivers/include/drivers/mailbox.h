/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#ifndef __MAILBOX_H__
#define __MAILBOX_H__

#include <rtdef.h>
#include <drivers/ofw.h>

struct rt_mbox_chan;
struct rt_mbox_client;
struct rt_mbox_controller_ops;

struct rt_mbox_controller
{
    rt_list_t list;

    struct rt_device *dev;

    const struct rt_mbox_controller_ops *ops;

    rt_size_t num_chans;
    struct rt_mbox_chan *chans;
};

struct rt_mbox_controller_ops
{
    rt_err_t (*request)(struct rt_mbox_chan *);
    void (*release)(struct rt_mbox_chan *);
    rt_err_t (*send)(struct rt_mbox_chan *, const void *data);
    rt_bool_t (*peek)(struct rt_mbox_chan *);
    int (*ofw_parse)(struct rt_mbox_controller *, struct rt_ofw_cell_args *);
};

struct rt_mbox_chan
{
    struct rt_mbox_controller *ctrl;
    struct rt_mbox_client *client;

    void *data;
    rt_bool_t complete;
    struct rt_timer timer;
    struct rt_spinlock lock;

    void *priv;
};

struct rt_mbox_client
{
    struct rt_device *dev;

    void (*rx_callback)(struct rt_mbox_client *, void *data);
    void (*tx_prepare)(struct rt_mbox_client *, const void *data);
    void (*tx_done)(struct rt_mbox_client *, const void *data, rt_err_t err);
};

rt_err_t rt_mbox_controller_register(struct rt_mbox_controller *ctrl);
rt_err_t rt_mbox_controller_unregister(struct rt_mbox_controller *ctrl);

rt_err_t rt_mbox_send(struct rt_mbox_chan *chan, const void *data,
        rt_uint32_t timeout_ms);
void rt_mbox_send_done(struct rt_mbox_chan *chan, rt_err_t err);
rt_bool_t rt_mbox_peek(struct rt_mbox_chan *chan);
rt_err_t rt_mbox_recv(struct rt_mbox_chan *chan, void *data);

struct rt_mbox_chan *rt_mbox_request_by_index(struct rt_mbox_client *client, int index);
struct rt_mbox_chan *rt_mbox_request_by_name(struct rt_mbox_client *client, char *name);
rt_err_t rt_mbox_release(struct rt_mbox_chan *chan);

#endif /* __MAILBOX_H__ */
