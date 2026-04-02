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

#define DBG_TAG "virtio.dev.rng"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpuport.h>

struct virtio_rng
{
    struct rt_hwcrypto_device parent;
    struct rt_virtio_device *vdev;

    struct rt_virtqueue *vqs[1];
    struct rt_spinlock lock;
};

static rt_uint32_t virtio_rng_rand(struct hwcrypto_rng *ctx)
{
    rt_uint32_t rand;
    struct rt_virtqueue *vq;
    struct virtio_rng *vrng = rt_container_of(ctx->parent.device, struct virtio_rng, parent);

    vq = vrng->vqs[0];
    rt_virtqueue_wait_prepare(vq, 1);

    rt_spin_lock(&vrng->lock);

    rt_virtqueue_add_inbuf(vq, &rand, sizeof(rand));
    rt_virtqueue_kick(vq);

    while (!rt_virtqueue_read_buf(vq, RT_NULL))
    {
        rt_hw_cpu_relax();
    }

    rt_spin_unlock(&vrng->lock);

    return rand;
}

static const struct hwcrypto_rng_ops rng_ops =
{
    .update = virtio_rng_rand,
};

static rt_err_t virtio_rng_create(struct rt_hwcrypto_ctx *ctx)
{
    if ((ctx->type & HWCRYPTO_MAIN_TYPE_MASK) == HWCRYPTO_TYPE_RNG)
    {
        struct hwcrypto_rng *rng;

        ctx->contex = RT_NULL;

        rng = rt_container_of(ctx, struct hwcrypto_rng, parent);
        rng->ops = &rng_ops;

        return RT_EOK;
    }

    return -RT_ENOSYS;
}

static void virtio_rng_destroy(struct rt_hwcrypto_ctx *ctx)
{
}

static rt_err_t virtio_rng_copy(struct rt_hwcrypto_ctx *des,
        const struct rt_hwcrypto_ctx *src)
{
    if ((src->type & HWCRYPTO_MAIN_TYPE_MASK) == HWCRYPTO_TYPE_RNG)
    {
        return RT_EOK;
    }

    return -RT_ENOSYS;
}

static void virtio_rng_reset(struct rt_hwcrypto_ctx *ctx)
{
}

static const struct rt_hwcrypto_ops virtio_rng_ops =
{
    .create = virtio_rng_create,
    .destroy = virtio_rng_destroy,
    .copy = virtio_rng_copy,
    .reset = virtio_rng_reset,
};

static void virtio_rng_done(struct rt_virtqueue *vq)
{
}

static rt_err_t virtio_rng_vq_init(struct virtio_rng *vrng)
{
    const char *names[] =
    {
        "req",
    };
    rt_virtqueue_callback cbs[] =
    {
        &virtio_rng_done,
    };

    return rt_virtio_virtqueue_install(vrng->vdev, RT_ARRAY_SIZE(vrng->vqs),
            vrng->vqs, names, cbs);
}

static void virtio_rng_vq_finit(struct virtio_rng *vrng)
{
    if (vrng->vqs[0])
    {
        rt_virtio_virtqueue_release(vrng->vdev);
    }
}

static rt_err_t virtio_rng_probe(struct rt_virtio_device *vdev)
{
    rt_err_t err;
    struct virtio_rng *vrng = rt_calloc(1, sizeof(*vrng));

    if (!vrng)
    {
        return -RT_ENOMEM;
    }

    vdev->priv = vrng;
    vrng->vdev = vdev;
    vdev->parent.user_data = vrng;

    if ((err = virtio_rng_vq_init(vrng)))
    {
        goto _fail;
    }

    rt_spin_lock_init(&vrng->lock);
    vrng->parent.ops = &virtio_rng_ops;
    vrng->parent.id = vdev->id.vendor;

    if ((err = rt_hwcrypto_register(&vrng->parent, "hwrng")))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    virtio_rng_vq_finit(vrng);
    rt_free(vrng);

    return err;
}

static rt_err_t virtio_rng_remove(struct rt_virtio_device *vdev)
{
    struct virtio_rng *vrng = vdev->parent.user_data;

    rt_device_unregister(&vrng->parent.parent);

    virtio_rng_vq_finit(vrng);
    rt_free(vrng);

    return RT_EOK;
}

static const struct rt_virtio_device_id virtio_rng_ids[] =
{
    { VIRTIO_DEVICE_ID_RNG, VIRTIO_DEVICE_ANY_ID },
    { /* sentinel */ }
};

static struct rt_virtio_driver virtio_rng_driver =
{
    .ids = virtio_rng_ids,
    .probe = virtio_rng_probe,
    .remove = virtio_rng_remove,
};
RT_VIRTIO_DRIVER_EXPORT(virtio_rng_driver);
