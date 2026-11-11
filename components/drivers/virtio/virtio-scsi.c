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

#define DBG_TAG "virtio.dev.scsi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "virtio_config/virtio-scsi.h"
#include "virtio_internal.h"

#define QUEUE_CONTROL   0
#define QUEUE_EVENT     1
#define QUEUE_REQUEST   2

struct virtio_scsi
{
    struct rt_scsi_host parent;
    struct rt_virtio_device *vdev;

    struct rt_virtqueue *vqs[3];
    struct rt_completion done;
    struct rt_spinlock lock;

    rt_uint16_t max_target;
    rt_uint32_t max_lun;
    struct rt_work hotplug_work;
};

static void virtio_scsi_init_cmd_req(struct virtio_scsi *vscsi,
        struct rt_scsi_device *sdev, struct rt_scsi_cmd *cmd,
        struct virtio_scsi_cmd_req *req)
{
    req->lun[0] = 1;
    req->lun[1] = sdev->id;
    req->lun[2] = (sdev->lun >> 8) | 0x40;
    req->lun[3] = sdev->lun & 0xff;
    req->tag = cpu_to_virtio64(vscsi->vdev, (rt_ubase_t)cmd);
    req->task_attr = VIRTIO_SCSI_S_SIMPLE;
    req->prio = 0;
    req->crn = 0;
}

static rt_err_t virtio_scsi_transfer(struct rt_scsi_device *sdev,
        struct rt_scsi_cmd *cmd)
{
    rt_ubase_t level;
    struct rt_virtqueue *vq;
    struct virtio_scsi_cmd_req req;
    struct virtio_scsi_cmd_resp resp;
    struct virtio_scsi *vscsi = rt_container_of(sdev->host, struct virtio_scsi, parent);

    virtio_scsi_init_cmd_req(vscsi, sdev, cmd, &req);

    RT_ASSERT(cmd->op_size < sizeof(req.cdb));
    rt_memcpy(&req.cdb, &cmd->op, cmd->op_size);

    vq = vscsi->vqs[QUEUE_REQUEST];
    if (!cmd->data.ptr || !cmd->data.size)
    {
        rt_virtqueue_wait_prepare(vq, 2);
    }
    else
    {
        rt_virtqueue_wait_prepare(vq, 3);
    }

    level = rt_spin_lock_irqsave(&vscsi->lock);

    rt_virtqueue_add_outbuf(vq, &req, sizeof(req));

    if (!cmd->data.ptr || !cmd->data.size)
    {
        rt_virtqueue_add_inbuf(vq, &resp, sizeof(resp));
    }
    else if (!rt_scsi_cmd_is_write(cmd))
    {
        rt_virtqueue_add_inbuf(vq, &resp, sizeof(resp));
        rt_virtqueue_add_inbuf(vq, cmd->data.ptr, cmd->data.size);
    }
    else
    {
        rt_virtqueue_add_outbuf(vq, cmd->data.ptr, cmd->data.size);
        rt_virtqueue_add_inbuf(vq, &resp, sizeof(resp));
    }

    rt_virtqueue_kick(vq);

    rt_spin_unlock_irqrestore(&vscsi->lock, level);

    rt_completion_wait(&vscsi->done, RT_WAITING_FOREVER);

    switch (resp.response)
    {
    case VIRTIO_SCSI_S_OK:
        if (resp.sense_len)
        {
            rt_memcpy(&cmd->data.request_sense, &resp.sense,
                    rt_min_t(rt_uint32_t,
                            virtio32_to_cpu(vscsi->vdev, resp.sense_len),
                            VIRTIO_SCSI_SENSE_SIZE));
        }
        return RT_EOK;

    case VIRTIO_SCSI_S_OVERRUN:
        LOG_E("%s resp = %s", rt_dm_dev_get_name(sdev->host->dev), "OVERRUN");
        return -RT_ERROR;

    case VIRTIO_SCSI_S_ABORTED:
        LOG_E("%s resp = %s", rt_dm_dev_get_name(sdev->host->dev), "ABORTED");
        return -RT_EIO;

    case VIRTIO_SCSI_S_BAD_TARGET:
        LOG_E("%s resp = %s", rt_dm_dev_get_name(sdev->host->dev), "BAD_TARGET");
        return -RT_EINVAL;

    case VIRTIO_SCSI_S_RESET:
        LOG_E("%s resp = %s", rt_dm_dev_get_name(sdev->host->dev), "RESET");
        return -RT_EIO;

    case VIRTIO_SCSI_S_BUSY:
        LOG_E("%s resp = %s", rt_dm_dev_get_name(sdev->host->dev), "BUSY");
        return -RT_EBUSY;

    case VIRTIO_SCSI_S_TRANSPORT_FAILURE:
        LOG_E("%s resp = %s", rt_dm_dev_get_name(sdev->host->dev), "TRANSPORT_FAILURE");
        return -RT_EIO;

    case VIRTIO_SCSI_S_TARGET_FAILURE:
        LOG_E("%s resp = %s", rt_dm_dev_get_name(sdev->host->dev), "TARGET_FAILURE");
        return -RT_EIO;

    case VIRTIO_SCSI_S_NEXUS_FAILURE:
        LOG_E("%s resp = %s", rt_dm_dev_get_name(sdev->host->dev), "NEXUS_FAILURE");
        return -RT_EIO;

    case VIRTIO_SCSI_S_FAILURE:
        LOG_E("%s resp = %s", rt_dm_dev_get_name(sdev->host->dev), "FAILURE");
        return -RT_EIO;

    case VIRTIO_SCSI_S_FUNCTION_SUCCEEDED:
        return RT_EOK;

    case VIRTIO_SCSI_S_FUNCTION_REJECTED:
        LOG_E("%s resp = %s", rt_dm_dev_get_name(sdev->host->dev), "FUNCTION_REJECTED");
        return -RT_EINVAL;

    case VIRTIO_SCSI_S_INCORRECT_LUN:
        LOG_E("%s resp = %s", rt_dm_dev_get_name(sdev->host->dev), "INCORRECT_LUN");
        return -RT_EINVAL;

    default:
        LOG_E("%s resp = UNKNOWN(%d)", rt_dm_dev_get_name(sdev->host->dev), resp.response);
        return -RT_EIO;
    }
}

static struct rt_scsi_ops virtio_scsi_ops =
{
    .transfer = virtio_scsi_transfer,
};

static void virtio_scsi_hotplug_work(struct rt_work *work, void *work_data)
{
    struct virtio_scsi *vscsi = work_data;

    if (!rt_scsi_host_unregister(&vscsi->parent))
    {
        vscsi->parent.max_id = vscsi->max_target;
        vscsi->parent.max_lun = vscsi->max_lun;

        rt_scsi_host_register(&vscsi->parent);
    }
}

static void virtio_scsi_request_done(struct rt_virtqueue *vq)
{
    rt_ubase_t level;
    struct virtio_scsi *vscsi = vq->vdev->priv;

    level = rt_spin_lock_irqsave(&vscsi->lock);

    rt_virtqueue_read_buf(vq, RT_NULL);
    rt_completion_done(&vscsi->done);

    rt_spin_unlock_irqrestore(&vscsi->lock, level);
}

static void virtio_scsi_config_changed(struct rt_virtio_device *vdev)
{
    struct virtio_scsi *vscsi = vdev->priv;

    rt_virtio_read_config(vdev, struct virtio_scsi_config,
            max_target, &vscsi->max_target);
    rt_virtio_read_config(vdev, struct virtio_scsi_config,
            max_lun, &vscsi->max_lun);

    if (vscsi->parent.max_id != vscsi->max_target ||
        vscsi->parent.max_lun != vscsi->max_lun)
    {
        rt_work_submit(&vscsi->hotplug_work, 0);
    }
}

static rt_err_t virtio_scsi_vq_init(struct virtio_scsi *vscsi)
{
    const char *names[] =
    {
        RT_NULL, /* ctrl */
        RT_NULL, /* event */
        "req",
    };
    rt_virtqueue_callback cbs[] =
    {
        RT_NULL,
        RT_NULL,
        &virtio_scsi_request_done,
    };

    return rt_virtio_virtqueue_install(vscsi->vdev, RT_ARRAY_SIZE(vscsi->vqs),
            vscsi->vqs, names, cbs);
}

static void virtio_scsi_vq_finit(struct virtio_scsi *vscsi)
{
    if (vscsi->vqs[0])
    {
        rt_virtio_virtqueue_release(vscsi->vdev);
    }
}

static rt_err_t virtio_scsi_probe(struct rt_virtio_device *vdev)
{
    rt_err_t err;
    rt_uint32_t cdb_size;
    struct virtio_scsi *vscsi = rt_calloc(1, sizeof(*vscsi));

    if (!vscsi)
    {
        return -RT_ENOMEM;
    }

    vdev->priv = vscsi;
    vscsi->vdev = vdev;
    vdev->parent.user_data = vscsi;
    vscsi->parent.dev = &vdev->parent;
    vscsi->parent.ops = &virtio_scsi_ops;

    rt_virtio_read_config(vdev, struct virtio_scsi_config,
            max_target, &vscsi->max_target);
    rt_virtio_read_config(vdev, struct virtio_scsi_config,
            max_lun, &vscsi->max_lun);

    vscsi->parent.max_id = vscsi->max_target;
    vscsi->parent.max_lun = vscsi->max_lun;

    if ((err = virtio_scsi_vq_init(vscsi)))
    {
        goto _fail;
    }

    cdb_size = RT_ALIGN(sizeof(((struct rt_scsi_cmd *)RT_NULL)->op), 32);
    rt_virtio_write_config(vdev, struct virtio_scsi_config, cdb_size, cdb_size);

    rt_completion_init(&vscsi->done);
    rt_spin_lock_init(&vscsi->lock);

    rt_work_init(&vscsi->hotplug_work, virtio_scsi_hotplug_work, vscsi);

    if ((err = rt_scsi_host_register(&vscsi->parent)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    virtio_scsi_vq_finit(vscsi);
    rt_free(vscsi);

    return err;
}

static rt_err_t virtio_scsi_remove(struct rt_virtio_device *vdev)
{
    struct virtio_scsi *vscsi = vdev->parent.user_data;

    rt_scsi_host_unregister(&vscsi->parent);

    virtio_scsi_vq_finit(vscsi);
    rt_free(vscsi);

    return RT_EOK;
}

static const struct rt_virtio_device_id virtio_scsi_ids[] =
{
    { VIRTIO_DEVICE_ID_SCSI, VIRTIO_DEVICE_ANY_ID },
    { /* sentinel */ }
};

static struct rt_virtio_driver virtio_scsi_driver =
{
    .ids = virtio_scsi_ids,
    .features =
        RT_BIT(VIRTIO_F_ANY_LAYOUT),

    .probe = virtio_scsi_probe,
    .remove = virtio_scsi_remove,
    .config_changed = virtio_scsi_config_changed,
};
RT_VIRTIO_DRIVER_EXPORT(virtio_scsi_driver);
