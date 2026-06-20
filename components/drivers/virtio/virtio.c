/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 * 2023-04-13     ErikChan     add virtio bus
 */

#include <rtatomic.h>
#include <rtthread.h>

#define DBG_TAG "rtdm.virtio"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpuport.h>

#include <drivers/virtio.h>
#include <drivers/core/bus.h>

void rt_virtio_device_ready(struct rt_virtio_device *vdev)
{
    rt_uint8_t status;

    RT_ASSERT(vdev != RT_NULL);
    RT_ASSERT(vdev->trans != RT_NULL);

    if (!vdev->trans->get_status(vdev, &status))
    {
        if (status & VIRTIO_STATUS_DRIVER_OK)
        {
            LOG_W("%s device driver is OK yet");
        }

        vdev->trans->set_status(vdev, status | VIRTIO_STATUS_DRIVER_OK);
    }
}

void rt_virtio_device_reset(struct rt_virtio_device *vdev)
{
    RT_ASSERT(vdev != RT_NULL);
    RT_ASSERT(vdev->trans != RT_NULL);

    vdev->trans->reset(vdev);
}

void rt_virtio_device_config_changed(struct rt_virtio_device *vdev)
{
    struct rt_virtio_driver *vdrv;

    RT_ASSERT(vdev != RT_NULL);
    RT_ASSERT(vdev->parent.drv != RT_NULL);

    vdrv = rt_container_of(vdev->parent.drv, struct rt_virtio_driver, parent);

    if (vdrv->config_changed)
    {
        vdrv->config_changed(vdev);
    }
}

void rt_virtio_add_status(struct rt_virtio_device *vdev, rt_uint32_t status)
{
    rt_uint8_t cur_status;

    RT_ASSERT(vdev != RT_NULL);
    RT_ASSERT(vdev->trans != RT_NULL);

    if (!vdev->trans->get_status(vdev, &cur_status))
    {
        vdev->trans->set_status(vdev, cur_status | status);
    }
}

rt_bool_t rt_virtio_has_status(struct rt_virtio_device *vdev, rt_uint8_t status_bit)
{
    rt_uint8_t status;

    RT_ASSERT(vdev != RT_NULL);
    RT_ASSERT(vdev->trans != RT_NULL);

    if (!vdev->trans->get_status(vdev, &status))
    {
        return (status & RT_BIT(status_bit)) != 0;
    }

    return RT_FALSE;
}

rt_bool_t rt_virtio_has_feature(struct rt_virtio_device *vdev, rt_uint32_t feature_bit)
{
    RT_ASSERT(vdev != RT_NULL);

    return (vdev->features & RT_BIT(feature_bit)) != 0;
}

rt_err_t rt_virtio_get_config(struct rt_virtio_device *vdev, rt_uint32_t offset, void *dst, int length)
{
    RT_ASSERT(vdev != RT_NULL);
    RT_ASSERT(vdev->trans != RT_NULL);

    return vdev->trans->get_config(vdev, offset, dst, length);
}

rt_err_t rt_virtio_set_config(struct rt_virtio_device *vdev, rt_uint32_t offset, const void *src, int length)
{
    RT_ASSERT(vdev != RT_NULL);
    RT_ASSERT(vdev->trans != RT_NULL);

    return vdev->trans->set_config(vdev, offset, src, length);
}

rt_err_t rt_virtio_virtqueue_install(struct rt_virtio_device *vdev, int vqs_nr,
        struct rt_virtqueue *vqs[], const char *names[], rt_virtqueue_callback cbs[])
{
    RT_ASSERT(vdev != RT_NULL);
    RT_ASSERT(vdev->trans != RT_NULL);
    RT_ASSERT(vqs_nr >= 0);
    RT_ASSERT(vqs != RT_NULL);
    RT_ASSERT(names != RT_NULL);
    RT_ASSERT(cbs != RT_NULL);

    return vdev->trans->install_vqs(vdev, vqs_nr, vqs, names, cbs);
}

rt_err_t rt_virtio_virtqueue_release(struct rt_virtio_device *vdev)
{
    RT_ASSERT(vdev != RT_NULL);
    RT_ASSERT(vdev->trans != RT_NULL);

    return vdev->trans->release_vqs(vdev);
}

rt_err_t rt_virtio_virtqueue_control(struct rt_virtio_device *vdev, rt_uint32_t cfg, void *data)
{
    RT_ASSERT(vdev != RT_NULL);
    RT_ASSERT(vdev->trans != RT_NULL);

    return vdev->trans->control_vqs(vdev, cfg, data);
}

static const char *const virtio_device_id_name[] =
{
    [VIRTIO_DEVICE_ID_INVALID]          = "invalid",
    [VIRTIO_DEVICE_ID_NET]              = "net",
    [VIRTIO_DEVICE_ID_BLOCK]            = "blk",
    [VIRTIO_DEVICE_ID_CONSOLE]          = "console",
    [VIRTIO_DEVICE_ID_RNG]              = "rng",
    [VIRTIO_DEVICE_ID_RPMSG]            = "rpmsg",
    [VIRTIO_DEVICE_ID_SCSI]             = "scsi",
    [VIRTIO_DEVICE_ID_9P]               = "9p",
    [VIRTIO_DEVICE_ID_RPROC_SERIAL]     = "rproc-serial",
    [VIRTIO_DEVICE_ID_GPU]              = "gpu",
    [VIRTIO_DEVICE_ID_INPUT]            = "input",
    [VIRTIO_DEVICE_ID_CRYPTO]           = "crypto",
    [VIRTIO_DEVICE_ID_IOMMU]            = "iommu",
    [VIRTIO_DEVICE_ID_AUDIO]            = "sound",
    [VIRTIO_DEVICE_ID_SCMI]             = "scmi",

    [VIRTIO_DEVICE_ID_MAX]              = RT_NULL,
};

const char *rt_virtio_device_id_name(struct rt_virtio_device *vdev)
{
    int device;
    const char *name = RT_NULL;

    RT_ASSERT(vdev != RT_NULL);

    device = vdev->id.device;

    if (device < RT_ARRAY_SIZE(virtio_device_id_name))
    {
        name = virtio_device_id_name[device];

        if (!name)
        {
            name = "nosys";
        }

        return name;
    }

    return name;
}

static struct rt_bus virtio_bus;

rt_err_t rt_virtio_driver_register(struct rt_virtio_driver *vdrv)
{
    const struct rt_virtio_device_id *id;

    RT_ASSERT(vdrv != RT_NULL);

    id = vdrv->ids;
    while (id->device && (id + 1)->device)
    {
        ++id;
    }

    vdrv->parent.bus = &virtio_bus;
#if RT_NAME_MAX > 0
    rt_strcpy(vdrv->parent.parent.name, virtio_device_id_name[id->device]);
#else
    vdrv->parent.parent.name = virtio_device_id_name[id->device];
#endif

    return rt_driver_register(&vdrv->parent);
}

static struct rt_dm_ida virtio_ida = RT_DM_IDA_INIT(CUSTOM);

rt_err_t rt_virtio_device_register(struct rt_virtio_device *vdev)
{
    RT_ASSERT(vdev != RT_NULL);
    RT_ASSERT(vdev->trans != RT_NULL);

    if ((vdev->idx = rt_dm_ida_alloc(&virtio_ida)) < 0)
    {
        return -RT_EFULL;
    }

    rt_dm_dev_set_name(&vdev->parent, "virtio%u-%s", vdev->idx,
            virtio_device_id_name[vdev->id.device]);

    rt_list_init(&vdev->vq_node);

    rt_spin_lock_init(&vdev->vq_lock);

    rt_virtio_device_reset(vdev);
    rt_virtio_add_status(vdev, VIRTIO_STATUS_ACKNOWLEDGE);

    return rt_bus_add_device(&virtio_bus, &vdev->parent);
}

static rt_bool_t virtio_match(rt_driver_t drv, rt_device_t dev)
{
    const struct rt_virtio_device_id *id;
    struct rt_virtio_driver *vdrv = rt_container_of(drv, struct rt_virtio_driver, parent);
    struct rt_virtio_device *vdev = rt_container_of(dev, struct rt_virtio_device, parent);

    for (id = vdrv->ids; id->device; ++id)
    {
        if (id->device != vdev->id.device && id->device != VIRTIO_DEVICE_ANY_ID)
        {
            continue;
        }

        if (id->vendor == VIRTIO_DEVICE_ANY_ID || id->vendor == vdev->id.vendor)
        {
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

static rt_err_t virtio_probe(rt_device_t dev)
{
    rt_err_t err;
    rt_uint8_t status;
    rt_uint64_t device_features, driver_features;
    struct rt_virtio_driver *vdrv = rt_container_of(dev->drv, struct rt_virtio_driver, parent);
    struct rt_virtio_device *vdev = rt_container_of(dev, struct rt_virtio_device, parent);

    rt_virtio_add_status(vdev, VIRTIO_STATUS_DRIVER);

    vdev->trans->get_features(vdev, &device_features);

    driver_features = vdrv->features;

    for (int i = VIRTIO_TRANSPORT_F_START; i <= VIRTIO_TRANSPORT_F_END; ++i)
    {
        rt_uint64_t flag = RT_BIT_ULL(i);

        if (device_features & flag)
        {
            driver_features |= flag;
        }
    }

    vdev->features = driver_features & device_features;

    err = vdev->trans->set_features(vdev);

    if (err)
    {
        goto _err;
    }

    if (rt_virtio_has_feature(vdev, VIRTIO_F_VERSION_1))
    {
        rt_virtio_add_status(vdev, VIRTIO_STATUS_FEATURES_OK);
        vdev->trans->get_status(vdev, &status);

        if (!(status & VIRTIO_STATUS_FEATURES_OK))
        {
            LOG_E("%s device refuses features: %x", rt_dm_dev_get_name(dev), status);

            err = -RT_EIO;
            goto _err;
        }
    }

    err = vdrv->probe(vdev);

    if (err)
    {
        goto _err;
    }

    vdev->trans->get_status(vdev, &status);

    if (!(status & VIRTIO_STATUS_DRIVER_OK))
    {
        rt_virtio_device_ready(vdev);
    }

    return RT_EOK;

_err:
    rt_virtio_add_status(vdev, VIRTIO_STATUS_FAILED);

    return err;
}

static rt_err_t virtio_remove(rt_device_t dev)
{
    struct rt_virtio_driver *vdrv = rt_container_of(dev->drv, struct rt_virtio_driver, parent);
    struct rt_virtio_device *vdev = rt_container_of(dev, struct rt_virtio_device, parent);

    if (vdrv && vdrv->remove)
    {
        vdrv->remove(vdev);
    }

    rt_virtio_add_status(vdev, VIRTIO_STATUS_ACKNOWLEDGE);

    rt_dm_ida_free(&virtio_ida, vdev->idx);

    return RT_EOK;
}

static struct rt_bus virtio_bus =
{
    .name = "virtio",
    .match = virtio_match,
    .probe = virtio_probe,
    .remove = virtio_remove,
};

static int virtio_bus_init(void)
{
    rt_bus_register(&virtio_bus);

    return 0;
}
INIT_CORE_EXPORT(virtio_bus_init);
