/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rthw.h>

#include <drivers/mailbox.h>
#include <dt-bindings/size.h>

#define DBG_TAG "scmi.agent.mailbox"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "agent.h"

struct scmi_agent_mailbox
{
    struct rt_mbox_client mbox_client;

    struct rt_mbox_chan *chan;
    struct scmi_shared_mem *shmem;

    struct rt_spinlock lock;
};
#define raw_to_scmi_mailbox(raw)    rt_container_of(raw, struct scmi_agent_mailbox, mbox_client)

static void scmi_mailbox_rx_callback(struct rt_mbox_client *client, void *data)
{
    struct rt_scmi_msg *msg = data;

    if (msg->rx_callback)
    {
        msg->rx_callback(msg->sdev, msg->out_msg, msg->out_msg_size);
    }
}

static void scmi_mailbox_tx_prepare(struct rt_mbox_client *client, const void *data)
{
    struct rt_scmi_msg *msg = (void *)data;
    struct scmi_agent_mailbox *ambox = raw_to_scmi_mailbox(client);

    scmi_shmem_msg_write(ambox->shmem, msg);
}

static void scmi_mailbox_tx_done(struct rt_mbox_client *client, const void *data,
        rt_err_t err)
{
    struct scmi_agent_mailbox *ambox = raw_to_scmi_mailbox(client);

    if (!err)
    {
        scmi_shmem_clear_channel(ambox->shmem);
    }
}

static rt_err_t scmi_agent_mailbox_setup(struct scmi_agent *agent,
        struct rt_device *dev)
{
    rt_err_t err;
    rt_uint64_t shm_addr, shm_size;
    int mbox_chan, mbox_count, shmem_count;
    struct rt_ofw_node *np = dev->ofw_node, *shmem_np;
    struct scmi_agent_mailbox *ambox = rt_calloc(1, sizeof(*ambox));

    if (!ambox)
    {
        return -RT_ENOMEM;
    }

    mbox_count = rt_ofw_count_phandle_cells(np, "mboxes", "#mbox-cells");
    shmem_count = rt_ofw_count_phandle_cells(np, "shmem", RT_NULL);

    if (mbox_count < 0)
    {
        err = mbox_count;
        goto _fail;
    }

    if (shmem_count < 0)
    {
        err = shmem_count;
        goto _fail;
    }

    mbox_chan = 0;
    if (mbox_count == 2 && shmem_count == 2)
    {
        mbox_chan = 1;
    }
    else if (mbox_count == 3)
    {
        mbox_chan = 2;
    }

    ambox->mbox_client.dev = dev;
    ambox->mbox_client.rx_callback = scmi_mailbox_rx_callback;
    ambox->mbox_client.tx_prepare = scmi_mailbox_tx_prepare;
    ambox->mbox_client.tx_done = scmi_mailbox_tx_done;

    ambox->chan = rt_mbox_request_by_index(&ambox->mbox_client, mbox_chan);
    if (rt_is_err_or_null(ambox->chan))
    {
        err = -RT_EIO;
        goto _fail;
    }

    shmem_np = rt_ofw_parse_phandle(np, "shmem", 0);

    if (!rt_ofw_node_is_compatible(shmem_np, "arm,scmi-shmem"))
    {
        err = -RT_EINVAL;
        rt_ofw_node_put(shmem_np);

        goto _fail;
    }

    if ((err = rt_ofw_get_address(shmem_np, 0, &shm_addr, &shm_size)))
    {
        rt_ofw_node_put(shmem_np);
        goto _fail;
    }
    rt_ofw_node_put(shmem_np);

    ambox->shmem = rt_ioremap((void *)shm_addr, shm_size);

    if (!ambox->shmem)
    {
        err = -RT_EIO;
        goto _fail;
    }

    agent->priv = ambox;

    return RT_EOK;

_fail:
    if (!rt_is_err_or_null(ambox->chan))
    {
        rt_mbox_release(ambox->chan);
    }
    if (ambox->shmem)
    {
        rt_iounmap(ambox->shmem);
    }
    rt_free(ambox);

    return err;
}

static rt_err_t scmi_agent_mailbox_process_msg(struct scmi_agent *agent,
        struct rt_scmi_msg *msg)
{
    rt_err_t err;
    struct scmi_agent_mailbox *ambox = agent->priv;

    rt_hw_spin_lock(&ambox->lock.lock);

    err = rt_mbox_send(ambox->chan, (const void *)msg, 30);

    rt_hw_spin_unlock(&ambox->lock.lock);

    return err;
}

struct scmi_agent_ops scmi_agent_mailbox_ops =
{
    .name = "mailbox",
    .setup = scmi_agent_mailbox_setup,
    .process_msg = scmi_agent_mailbox_process_msg,
};
