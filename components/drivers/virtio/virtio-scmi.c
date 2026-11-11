/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "virtio.dev.scmi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "virtio_internal.h"
#include "virtio_config/virtio-scmi.h"
#include "../firmware/arm_scmi/agent.h"

#define QUEUE_CMDQ      0
#define QUEUE_EVENTQ    1

struct virtio_scmi_event_msg_ext
{
    rt_list_t list;

    struct rt_scmi_device *sdev;
    rt_scmi_msg_callback rx_callback;

    rt_size_t msg_size;
    struct virtio_scmi_event_msg event_msg;
};

struct virtio_scmi
{
    struct rt_virtio_device *vdev;

    rt_list_t event_nodes;
    struct rt_work event_work;

    struct rt_virtqueue *vqs[2];
    struct rt_completion done;
    struct rt_spinlock lock;
};

static struct virtio_scmi *system_virtio_scmi = RT_NULL;

static rt_err_t scmi_agent_virtio_setup(struct scmi_agent *agent,
        struct rt_device *dev)
{
    RT_ASSERT(system_virtio_scmi != RT_NULL);

    agent->priv = system_virtio_scmi;

    return RT_EOK;
}

static rt_err_t scmi_agent_virtio_process_msg(struct scmi_agent *agent,
        struct rt_scmi_msg *msg)
{
    rt_base_t level;
    struct rt_virtqueue *vq;
    struct virtio_scmi *vscmi = agent->priv;

    if (!msg->rx_callback ||
        !rt_virtio_has_feature(vscmi->vdev, VIRTIO_SCMI_F_P2A_CHANNELS))
    {
        void *buffer;
        rt_size_t request_size, response_size;
        struct virtio_scmi_request *request;
        struct virtio_scmi_response *response;

        request_size = sizeof(*request) + msg->in_msg_size;
        response_size = sizeof(*response) + msg->out_msg_size;
        buffer = rt_malloc(request_size + response_size);

        if (!buffer)
        {
            return -RT_ENOMEM;
        }

        request = buffer;
        response = buffer + request_size;

        request->hdr = cpu_to_virtio32(vscmi->vdev, scmi_header(
                msg->message_id, 0, msg->sdev->protocol_id, 0));
        rt_memcpy(request->params, msg->in_msg, msg->in_msg_size);

        vq = vscmi->vqs[QUEUE_CMDQ];
        rt_virtqueue_wait_prepare(vq, 2);

        level = rt_spin_lock_irqsave(&vscmi->lock);

        rt_virtqueue_add_outbuf(vq, request, request_size);
        rt_virtqueue_add_inbuf(vq, response, response_size);
        rt_virtqueue_kick(vq);

        rt_spin_unlock_irqrestore(&vscmi->lock, level);

        rt_completion_wait(&vscmi->done, RT_WAITING_FOREVER);

        if (msg->out_msg)
        {
            if (request->hdr != response->hdr)
            {
                LOG_W("WTF? request header(%x) != response header(%x)",
                        rt_le32_to_cpu(request->hdr), rt_le32_to_cpu(response->hdr));
            }

            rt_memcpy(msg->out_msg, response->ret_values, msg->out_msg_size);
        }

        /* Fixup for device */
        if (msg->rx_callback)
        {
            msg->rx_callback(msg->sdev, response->ret_values, msg->out_msg_size);
        }

        rt_free(buffer);
    }
    else
    {
        struct virtio_scmi_event_msg_ext *msge = rt_malloc(sizeof(*msge) +
                rt_max(msg->in_msg_size, msg->out_msg_size));

        if (!msge)
        {
            return -RT_ENOMEM;
        }

        msge->sdev = msg->sdev;
        msge->rx_callback = msg->rx_callback;
        msge->msg_size = msg->out_msg_size;
        msge->event_msg.hdr = cpu_to_virtio32(vscmi->vdev, scmi_header(
                msg->message_id, 0, msg->sdev->protocol_id, 0));
        rt_memcpy(msge->event_msg.payload, msg->in_msg, msg->in_msg_size);

        vq = vscmi->vqs[QUEUE_EVENTQ];
        rt_virtqueue_wait_prepare(vq, 1);

        level = rt_spin_lock_irqsave(&vscmi->lock);

        rt_virtqueue_add_outbuf(vq, &msge->event_msg,
                sizeof(msge->event_msg) + msg->in_msg_size);
        rt_virtqueue_kick(vq);

        rt_spin_unlock_irqrestore(&vscmi->lock, level);
    }

    return RT_EOK;
}

struct scmi_agent_ops scmi_agent_virtio_ops =
{
    .name = "virtio",
    .setup = scmi_agent_virtio_setup,
    .process_msg = scmi_agent_virtio_process_msg,
};

static void virtio_scmi_work(struct rt_work *work, void *work_data)
{
    rt_ubase_t level;
    struct virtio_scmi *vscmi = work_data;
    struct virtio_scmi_event_msg_ext *msge, *msge_next;

    level = rt_spin_lock_irqsave(&vscmi->lock);

    rt_list_for_each_entry_safe(msge, msge_next, &vscmi->event_nodes, list)
    {
        rt_list_remove(&msge->list);

        rt_spin_unlock_irqrestore(&vscmi->lock, level);

        msge->rx_callback(msge->sdev, msge->event_msg.payload, msge->msg_size);
        rt_free(msge);

        level = rt_spin_lock_irqsave(&vscmi->lock);
    }

    rt_spin_unlock_irqrestore(&vscmi->lock, level);
}

static void virtio_scmi_cmd_done(struct rt_virtqueue *vq)
{
    rt_ubase_t level;
    struct virtio_scmi *vscmi = vq->vdev->priv;

    level = rt_spin_lock_irqsave(&vscmi->lock);

    rt_virtqueue_read_buf(vq, RT_NULL);
    rt_completion_done(&vscmi->done);

    rt_spin_unlock_irqrestore(&vscmi->lock, level);
}

static void virtio_scmi_event_done(struct rt_virtqueue *vq)
{
    rt_ubase_t level;
    void *raw_buffer;
    struct virtio_scmi *vscmi = vq->vdev->priv;

    level = rt_spin_lock_irqsave(&vscmi->lock);

    if ((raw_buffer = rt_virtqueue_read_buf(vq, RT_NULL)))
    {
        struct virtio_scmi_event_msg_ext *msge;

        msge = rt_container_of(raw_buffer, struct virtio_scmi_event_msg_ext, event_msg);

        rt_list_init(&msge->list);
        rt_list_insert_before(&vscmi->event_nodes, &msge->list);

        rt_work_submit(&vscmi->event_work, 0);
    }

    rt_spin_unlock_irqrestore(&vscmi->lock, level);
}

static rt_err_t virtio_scmi_vq_init(struct virtio_scmi *vscmi)
{
    rt_size_t vqs_nr;
    const char *names[] =
    {
        "cmd",
        "event"
    };
    rt_virtqueue_callback cbs[] =
    {
        &virtio_scmi_cmd_done,
        &virtio_scmi_event_done,
    };

    vqs_nr = rt_virtio_has_feature(vscmi->vdev, VIRTIO_SCMI_F_P2A_CHANNELS) ?
            RT_ARRAY_SIZE(names) : 1;

    return rt_virtio_virtqueue_install(vscmi->vdev, vqs_nr, vscmi->vqs, names, cbs);
}

static rt_err_t virtio_scmi_probe(struct rt_virtio_device *vdev)
{
    rt_err_t err;
    struct virtio_scmi *vscmi = rt_calloc(1, sizeof(*vscmi));

    if (!vscmi)
    {
        return -RT_ENOMEM;
    }

    vdev->priv = vscmi;
    vscmi->vdev = vdev;
    vdev->parent.user_data = vscmi;

    if ((err = virtio_scmi_vq_init(vscmi)) < 0)
    {
        rt_free(vscmi);

        return err;
    }

    if (rt_virtio_has_feature(vscmi->vdev, VIRTIO_SCMI_F_P2A_CHANNELS))
    {
        rt_list_init(&vscmi->event_nodes);
        rt_work_init(&vscmi->event_work, virtio_scmi_work, vscmi);
    }

    rt_spin_lock_init(&vscmi->lock);
    rt_completion_init(&vscmi->done);

    system_virtio_scmi = vscmi;

    return RT_EOK;
}

static const struct rt_virtio_device_id virtio_scmi_ids[] =
{
    { VIRTIO_DEVICE_ID_SCMI, VIRTIO_DEVICE_ANY_ID },
    { /* sentinel */ }
};

static struct rt_virtio_driver virtio_scmi_driver =
{
    .ids = virtio_scmi_ids,
    .features =
        RT_BIT(VIRTIO_SCMI_F_P2A_CHANNELS)
      | RT_BIT(VIRTIO_SCMI_F_SHARED_MEMORY)
      | RT_BIT(VIRTIO_F_ANY_LAYOUT),

    .probe = virtio_scmi_probe,
};
RT_VIRTIO_DRIVER_EXPORT(virtio_scmi_driver);
