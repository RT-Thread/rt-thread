/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>

#define DBG_TAG "rtdm.mailbox"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/ofw.h>
#include <drivers/mailbox.h>
#include <drivers/platform.h>
#include <drivers/core/dm.h>

static struct rt_spinlock mbox_ops_lock = {};
static rt_list_t mbox_nodes = RT_LIST_OBJECT_INIT(mbox_nodes);

static void mbox_chan_timeout(void *param);

rt_err_t rt_mbox_controller_register(struct rt_mbox_controller *ctrl)
{
    int len;
    struct rt_mbox_chan *chan;
    char timer_name[RT_NAME_MAX];

    if (!ctrl || !ctrl->dev || !ctrl->ops || !ctrl->num_chans)
    {
        return -RT_EINVAL;
    }

    ctrl->chans = rt_calloc(ctrl->num_chans, sizeof(struct rt_mbox_chan));

    if (!ctrl->chans)
    {
        return -RT_ENOMEM;
    }

    len = rt_snprintf(timer_name, sizeof(timer_name), "%s-",
            rt_dm_dev_get_name(ctrl->dev));

    RT_ASSERT(len < sizeof(timer_name));

    chan = &ctrl->chans[0];

    for (int i = 0; i < ctrl->num_chans; ++i, ++chan)
    {
        chan->ctrl = ctrl;
        rt_spin_lock_init(&chan->lock);

        rt_snprintf(&timer_name[len], sizeof(timer_name) - len, "%d", i);
        rt_timer_init(&chan->timer, timer_name, mbox_chan_timeout, chan,
                0, RT_TIMER_FLAG_ONE_SHOT);
    }

    rt_list_init(&ctrl->list);
    rt_dm_dev_bind_fwdata(ctrl->dev, RT_NULL, ctrl);

    rt_spin_lock(&mbox_ops_lock);

    rt_list_insert_after(&mbox_nodes, &ctrl->list);

    rt_spin_unlock(&mbox_ops_lock);

    return RT_EOK;
}

rt_err_t rt_mbox_controller_unregister(struct rt_mbox_controller *ctrl)
{
    struct rt_mbox_chan *chan;

    if (!ctrl)
    {
        return -RT_EINVAL;
    }

    rt_spin_lock(&mbox_ops_lock);

    rt_dm_dev_unbind_fwdata(ctrl->dev, RT_NULL);
    rt_list_remove(&ctrl->list);

    rt_spin_unlock(&mbox_ops_lock);

    chan = &ctrl->chans[0];

    for (int i = ctrl->num_chans - 1; i >= 0; --i, ++chan)
    {
        rt_mbox_release(&ctrl->chans[i]);
    }

    rt_free(ctrl->chans);

    return RT_EOK;
}

rt_err_t rt_mbox_send(struct rt_mbox_chan *chan, const void *data,
        rt_uint32_t timeout_ms)
{
    rt_err_t err;
    rt_ubase_t level;
    rt_bool_t timer_go = RT_FALSE;
    struct rt_mbox_client *client;
    struct rt_mbox_controller *ctrl;

    if (!chan || !data)
    {
        return -RT_EINVAL;
    }

    ctrl = chan->ctrl;
    client = chan->client;

    level = rt_spin_lock_irqsave(&chan->lock);

    if (client->tx_prepare)
    {
        client->tx_prepare(client, data);
    }

    chan->complete = RT_FALSE;
    err = ctrl->ops->send(chan, data);

    if (!err)
    {
        chan->data = (void *)data;

        if (timeout_ms != RT_WAITING_FOREVER)
        {
            rt_tick_t tick = rt_tick_from_millisecond(timeout_ms);

            rt_timer_control(&chan->timer, RT_TIMER_CTRL_SET_TIME, &tick);

            timer_go = RT_TRUE;
        }
    }
    else
    {
        chan->complete = RT_TRUE;
    }

    rt_spin_unlock_irqrestore(&chan->lock, level);

    if (timer_go)
    {
        rt_timer_start(&chan->timer);
    }

    return err;
}

void rt_mbox_send_done(struct rt_mbox_chan *chan, rt_err_t err)
{
    void *data;
    rt_ubase_t level;

    level = rt_spin_lock_irqsave(&chan->lock);

    data = chan->data;
    chan->data = RT_NULL;

    rt_spin_unlock_irqrestore(&chan->lock, level);

    if (chan->client->tx_done)
    {
        chan->client->tx_done(chan->client, data, err);
    }

    chan->complete = RT_TRUE;
}

static void mbox_chan_timeout(void *param)
{
    rt_err_t err = RT_EOK;
    struct rt_mbox_chan *chan = param;

    if (!chan->complete)
    {
        err = -RT_ETIMEOUT;
    }

    rt_mbox_send_done(chan, err);
}

rt_bool_t rt_mbox_peek(struct rt_mbox_chan *chan)
{
    if (chan && chan->ctrl->ops->peek)
    {
        return chan->ctrl->ops->peek(chan);
    }

    return RT_FALSE;
}

rt_err_t rt_mbox_recv(struct rt_mbox_chan *chan, void *data)
{
    if (!chan || !data)
    {
        return -RT_EINVAL;
    }

    if (chan->client->rx_callback)
    {
        chan->client->rx_callback(chan->client, data);
    }

    return RT_EOK;
}

static int mbox_controller_ofw_parse_default(struct rt_mbox_controller *ctrl,
        struct rt_ofw_cell_args *args)
{
    if (args->args_count != 1)
    {
        return -RT_EINVAL;
    }

    return args->args[0];
}

struct rt_mbox_chan *rt_mbox_request_by_index(struct rt_mbox_client *client, int index)
{
    rt_err_t err;
    struct rt_ofw_cell_args args;
    struct rt_ofw_node *np, *ctrl_np;
    struct rt_mbox_controller *ctrl;
    struct rt_mbox_chan *chan = RT_NULL;

    if (!client && index < 0)
    {
        return rt_err_ptr(-RT_EINVAL);
    }

    np = client->dev->ofw_node;

    rt_spin_lock(&mbox_ops_lock);

    err = rt_ofw_parse_phandle_cells(np, "mboxes", "#mbox-cells", index, &args);

    if (err)
    {
        chan = rt_err_ptr(err);
        goto _out_lock;
    }

    ctrl_np = args.data;

    if (!rt_ofw_data(ctrl_np))
    {
        rt_spin_unlock(&mbox_ops_lock);

        rt_platform_ofw_request(ctrl_np);

        rt_spin_lock(&mbox_ops_lock);
    }

    ctrl = rt_ofw_data(ctrl_np);
    rt_ofw_node_put(ctrl_np);

    if (ctrl)
    {
        int index;

        if (ctrl->ops->ofw_parse)
        {
            index = ctrl->ops->ofw_parse(ctrl, &args);
        }
        else
        {
            index = mbox_controller_ofw_parse_default(ctrl, &args);
        }

        if (index >= 0)
        {
            chan = &ctrl->chans[index];
        }
        else
        {
            LOG_E("Parse chan from %s error = %s",
                    rt_dm_dev_get_name(ctrl->dev), rt_strerror(index));

            chan = rt_err_ptr(index);
            goto _out_lock;
        }

        if (ctrl->ops->request)
        {
            rt_err_t err = ctrl->ops->request(chan);

            if (err)
            {
                LOG_E("Request chan[%d] from %s error = %s",
                        index, rt_dm_dev_get_name(ctrl->dev), rt_strerror(err));

                rt_mbox_release(chan);
                chan = rt_err_ptr(err);
            }
        }

        chan->client = client;
    }
    else
    {
        chan = rt_err_ptr(-RT_ENOSYS);
    }

_out_lock:
    rt_spin_unlock(&mbox_ops_lock);

    return chan;
}

struct rt_mbox_chan *rt_mbox_request_by_name(struct rt_mbox_client *client, char *name)
{
    int index;
    struct rt_ofw_node *np;

    if (!client || !name)
    {
        return rt_err_ptr(-RT_EINVAL);
    }

    np = client->dev->ofw_node;
    index = rt_ofw_prop_index_of_string(np, "mbox-names", name);

    if (index < 0)
    {
        return RT_NULL;
    }

    return rt_mbox_request_by_index(client, index);
}

rt_err_t rt_mbox_release(struct rt_mbox_chan *chan)
{
    if (chan)
    {
        chan->ctrl->ops->release(chan);
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}
