/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "virtio.dev.input"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "virtio_config/virtio-input.h"

#define QUEUE_EVENTS    0
#define QUEUE_STATUS    1

struct virtio_input
{
    struct rt_input_device parent;
    struct rt_virtio_device *vdev;

    struct rt_virtqueue *vqs[2];

    rt_size_t events_nr;
    struct rt_spinlock lock;
    struct virtio_input_event *events;
};

#define raw_to_virtio_input(raw) rt_container_of(raw, struct virtio_input, parent)

static rt_err_t virtio_input_trigger(struct rt_input_device *idev,
        rt_uint16_t type, rt_uint16_t code, rt_int32_t value)
{
    struct rt_virtqueue *vq;
    struct virtio_input_event status;
    struct virtio_input *vinput = raw_to_virtio_input(idev);

    vq = vinput->vqs[QUEUE_STATUS];

    rt_virtqueue_wait_prepare(vq, 1);

    rt_spin_lock(&vinput->lock);

    status.type = rt_cpu_to_le16(type);
    status.code = rt_cpu_to_le16(code);
    status.value = rt_cpu_to_le32(value);
    rt_virtqueue_add_outbuf(vq, &status, sizeof(status));

    rt_virtqueue_kick(vq);

    while (!rt_virtqueue_read_buf(vq, RT_NULL))
    {
        rt_hw_cpu_relax();
    }

    rt_spin_unlock(&vinput->lock);

    return RT_EOK;
}

static void virtio_input_events_done(struct rt_virtqueue *vq)
{
    rt_ubase_t level;
    struct virtio_input_event *event;
    struct virtio_input *vinput = vq->vdev->priv;

    level = rt_spin_lock_irqsave(&vinput->lock);

    while ((event = rt_virtqueue_read_buf(vq, RT_NULL)))
    {
        rt_input_event(&vinput->parent,
                rt_le16_to_cpu(event->type),
                rt_le16_to_cpu(event->code),
                rt_le32_to_cpu(event->value));

        LOG_D("%s: Event (type: %d, code: %d, value: %d)",
                rt_dm_dev_get_name(&vinput->parent),
                rt_le16_to_cpu(event->type),
                rt_le16_to_cpu(event->code),
                rt_le32_to_cpu(event->value));

        rt_virtqueue_add_inbuf(vq, event, sizeof(*event));

        rt_virtqueue_kick(vq);
    }

    rt_spin_unlock_irqrestore(&vinput->lock, level);
}

static void virtio_input_status_done(struct rt_virtqueue *vq)
{
}

static rt_uint8_t virtio_input_cfg_select(struct virtio_input *vinput,
        rt_uint8_t select, rt_uint8_t subsel)
{
    rt_uint8_t size = 0;
    struct rt_virtio_device *vdev = vinput->vdev;

    rt_virtio_write_config(vdev, struct virtio_input_config, select, select);
    rt_virtio_write_config(vdev, struct virtio_input_config, subsel, subsel);
    rt_virtio_read_config(vdev, struct virtio_input_config, size, &size);

    return size;
}

static void virtio_input_cfg_bits(struct virtio_input *vinput,
        rt_uint8_t select, rt_uint8_t subsel, rt_bitmap_t *map, rt_size_t bitcount)
{
    rt_uint8_t size = virtio_input_cfg_select(vinput, select, subsel);

    if (!size)
    {
        return;
    }

    bitcount = rt_min_t(rt_size_t, bitcount, size * RT_BITS_PER_BYTE);

    rt_virtio_read_bytes(vinput->vdev,
            rt_offsetof(struct virtio_input_config, bitmap), map, 1, size);

    rt_bitmap_set_bit(vinput->parent.cap, subsel);
}

static void virtio_input_cfg_abs(struct virtio_input *vinput, int abs)
{
    rt_uint32_t min, max, res, fuzz, flat;
    struct rt_virtio_device *vdev = vinput->vdev;

    virtio_input_cfg_select(vinput, VIRTIO_INPUT_CFG_ABS_INFO, abs);
    rt_virtio_read_config(vdev, struct virtio_input_config, abs.min, &min);
    rt_virtio_read_config(vdev, struct virtio_input_config, abs.max, &max);
    rt_virtio_read_config(vdev, struct virtio_input_config, abs.res, &res);
    rt_virtio_read_config(vdev, struct virtio_input_config, abs.fuzz, &fuzz);
    rt_virtio_read_config(vdev, struct virtio_input_config, abs.flat, &flat);

    rt_input_set_capability(&vinput->parent, EV_ABS, abs);
    rt_input_set_absinfo(&vinput->parent, abs, min, max, fuzz, flat);
    vinput->parent.absinfo->resolution = res;
}

static rt_err_t virtio_input_vq_init(struct virtio_input *vinput)
{
    rt_err_t err;
    const char *names[] =
    {
        "events",
        "status"
    };
    rt_virtqueue_callback cbs[] =
    {
        &virtio_input_events_done,
        &virtio_input_status_done,
    };
    struct rt_virtqueue *vq;

    err = rt_virtio_virtqueue_install(vinput->vdev,
            RT_ARRAY_SIZE(names), vinput->vqs, names, cbs);

    if (err)
    {
        return err;
    }

    vinput->events_nr = rt_virtqueue_get_virtq_size(vinput->vqs[QUEUE_EVENTS]);

    vinput->events = rt_malloc(sizeof(*vinput->events) * vinput->events_nr);

    if (!vinput->events)
    {
        return -RT_ENOMEM;
    }

    vq = vinput->vqs[QUEUE_EVENTS];

    for (int i = 0; i < vinput->events_nr; ++i)
    {
        rt_virtqueue_add_inbuf(vq, &vinput->events[i], sizeof(*vinput->events));

        rt_virtqueue_submit(vq);
    }

    rt_virtqueue_notify(vq);

    return RT_EOK;
}

static void virtio_input_vq_finit(struct virtio_input *vinput)
{
    if (vinput->vqs[0])
    {
        rt_virtio_virtqueue_release(vinput->vdev);
    }

    if (vinput->events)
    {
        rt_free(vinput->events);
    }
}

static rt_err_t virtio_input_probe(struct rt_virtio_device *vdev)
{
    rt_err_t err;
    struct virtio_input *vinput = rt_calloc(1, sizeof(*vinput));

    if (!vinput)
    {
        return -RT_ENOMEM;
    }

    vdev->priv = vinput;
    vinput->vdev = vdev;
    vdev->parent.user_data = vinput;

    if ((err = virtio_input_vq_init(vinput)) < 0)
    {
        goto _fail;
    }

    rt_spin_lock_init(&vinput->lock);

    virtio_input_cfg_bits(vinput, VIRTIO_INPUT_CFG_EV_BITS, EV_KEY,
            vinput->parent.key_map, KEY_CNT);
    virtio_input_cfg_bits(vinput, VIRTIO_INPUT_CFG_EV_BITS, EV_REL,
            vinput->parent.rel_map, REL_CNT);
    virtio_input_cfg_bits(vinput, VIRTIO_INPUT_CFG_EV_BITS, EV_ABS,
            vinput->parent.abs_map, ABS_CNT);

    if (rt_bitmap_test_bit(vinput->parent.cap, EV_ABS))
    {
        for (int abs = 0; abs < ABS_CNT; ++abs)
        {
            if (!rt_bitmap_test_bit(vinput->parent.abs_map, abs))
            {
                continue;
            }

            virtio_input_cfg_abs(vinput, abs);
        }

        if (rt_bitmap_test_bit(vinput->parent.abs_map, ABS_MT_SLOT))
        {
            int nslots = vinput->parent.absinfo[ABS_MT_SLOT].maximum + 1;

            if ((err = rt_input_setup_touch(&vinput->parent, nslots, RT_NULL)))
            {
                goto _fail;
            }
        }
    }

    vinput->parent.trigger = &virtio_input_trigger;

    if ((err = rt_input_device_register(&vinput->parent)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    virtio_input_vq_finit(vinput);
    rt_input_remove_config(&vinput->parent);
    rt_free(vinput);

    return err;
}

static rt_err_t virtio_input_remove(struct rt_virtio_device *vdev)
{
    struct virtio_input *vinput = vdev->parent.user_data;

    rt_input_device_unregister(&vinput->parent);

    virtio_input_vq_finit(vinput);
    rt_free(vinput);

    return RT_EOK;
}

static const struct rt_virtio_device_id virtio_input_ids[] =
{
    { VIRTIO_DEVICE_ID_INPUT, VIRTIO_DEVICE_ANY_ID },
    { /* sentinel */ }
};

static struct rt_virtio_driver virtio_input_driver =
{
    .ids = virtio_input_ids,
    .probe = virtio_input_probe,
    .remove = virtio_input_remove,
};
RT_VIRTIO_DRIVER_EXPORT(virtio_input_driver);
