/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>

#define DBG_TAG "virtio.mmio"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mmu.h>

#include <drivers/ofw.h>
#include <drivers/pic.h>
#include <drivers/virtio.h>
#include <drivers/platform.h>
#include <drivers/core/bus.h>

#define VIRTIO_MMIO_MAGIC               0x000 /* <RO> Magic value */
#define VIRTIO_MMIO_VERSION             0x004 /* <RO> Device version number */
#define VIRTIO_MMIO_DEVICE_ID           0x008 /* <RO> Virtio Subsystem Device ID */
#define VIRTIO_MMIO_VENDOR_ID           0x00c /* <RO> Virtio Subsystem Vendor ID */
#define VIRTIO_MMIO_DEVICE_FEATURES     0x010 /* <RO> Flags representing features the device supports */
#define VIRTIO_MMIO_DEVICE_FEATURES_SEL 0x014 /* <WO> Device (host) features word selection. */
#define VIRTIO_MMIO_DRIVER_FEATURES     0x020 /* <WO> Device features understood and activated by the driver */
#define VIRTIO_MMIO_DRIVER_FEATURES_SEL 0x024 /* <WO> Activated (guest) features word selection */
#define VIRTIO_MMIO_GUEST_PAGE_SIZE     0x028 /* <WO> Guest page size, this value should be a power of 2 */
#define VIRTIO_MMIO_QUEUE_SEL           0x030 /* <WO> Virtual queue index */
#define VIRTIO_MMIO_QUEUE_NUM_MAX       0x034 /* <RO> Maximum virtual queue size */
#define VIRTIO_MMIO_QUEUE_NUM           0x038 /* <WO> Virtual queue size */
#define VIRTIO_MMIO_QUEUE_ALIGN         0x03c /* <WO> Used Ring alignment in the virtual queue */
#define VIRTIO_MMIO_QUEUE_PFN           0x040 /* <RW> Guest physical page number of the virtual queue */
#define VIRTIO_MMIO_QUEUE_READY         0x044 /* <RW> Virtual queue ready bit */
#define VIRTIO_MMIO_QUEUE_NOTIFY        0x050 /* <WO> Queue notifier */
#define VIRTIO_MMIO_INTERRUPT_STATUS    0x060 /* <RO> Interrupt status */
#define VIRTIO_MMIO_INTERRUPT_ACK       0x064 /* <WO> Interrupt acknowledge */
#define VIRTIO_MMIO_STATUS              0x070 /* <RW> Device status */
#define VIRTIO_MMIO_QUEUE_DESC_LOW      0x080 /* <WO> Virtual queue's descriptor Area 64 bit long physical address */
#define VIRTIO_MMIO_QUEUE_DESC_HIGH     0x084 /* <WO> */
#define VIRTIO_MMIO_QUEUE_AVAIL_LOW     0x090 /* <WO> Virtual queue's available Ring (Driver Area) 64 bit long physical address */
#define VIRTIO_MMIO_QUEUE_AVAIL_HIGH    0x094 /* <WO> */
#define VIRTIO_MMIO_QUEUE_USED_LOW      0x0a0 /* <WO> Virtual queue's used Ring (Device Area) 64 bit long physical address */
#define VIRTIO_MMIO_QUEUE_USED_HIGH     0x0a4 /* <WO> */
#define VIRTIO_MMIO_SHM_SEL             0x0ac /* <WO> Shared memory region id */
#define VIRTIO_MMIO_SHM_LEN_LOW         0x0b0 /* <RO> Shared memory region length, 64 bits in two halves */
#define VIRTIO_MMIO_SHM_LEN_HIGH        0x0b4 /* <RO> */
#define VIRTIO_MMIO_SHM_BASE_LOW        0x0b8 /* <RO> Shared memory region base address, 64 bits in two halves */
#define VIRTIO_MMIO_SHM_BASE_HIGH       0x0bc /* <RO> */
#define VIRTIO_MMIO_CONFIG_GENERATION   0x0fc /* <RO> Configuration atomicity value */
#define VIRTIO_MMIO_CONFIG              0x100 /* <RO> Configuration space */

#define VIRTIO_MMIO_INT_VIRTQ           (1 << 0) /* The device has used a buffer in at least one of the active virtual queues */
#define VIRTIO_MMIO_INT_CONFIG          (1 << 1) /* The configuration of the device has changed */

#define VIRTIO_MMIO_VIRTQ_PAGE_SHIFT    ARCH_PAGE_SHIFT
#define VIRTIO_MMIO_VIRTQ_PAGE_SZIE     (1 << VIRTIO_MMIO_VIRTQ_PAGE_SHIFT)
#define VIRTIO_MMIO_VIRTQ_ALIGN_SHIFT   VIRTIO_MMIO_VIRTQ_PAGE_SHIFT
#define VIRTIO_MMIO_VIRTQ_ALIGN         (1 << VIRTIO_MMIO_VIRTQ_ALIGN_SHIFT)

struct virtio_mmio
{
    struct rt_virtio_device parent;

    void *base;
    int irq;
    rt_ubase_t version;

    struct rt_spinlock spinlock;
};

#define raw_to_virtio_mmio(raw) rt_container_of(raw, struct virtio_mmio, parent)

rt_inline rt_uint64_t virtio_mmio_read64(struct virtio_mmio *vio, int offset)
{
    return rt_cpu_to_le64(HWREG64(vio->base + offset));
}

rt_inline void virtio_mmio_write64(struct virtio_mmio *vio, int offset, rt_uint64_t value)
{
    HWREG64(vio->base + offset) = rt_le64_to_cpu(value);
}

rt_inline rt_uint32_t virtio_mmio_read32(struct virtio_mmio *vio, int offset)
{
    return rt_cpu_to_le32(HWREG32(vio->base + offset));
}

rt_inline void virtio_mmio_write32(struct virtio_mmio *vio, int offset, rt_uint32_t value)
{
    HWREG32(vio->base + offset) = rt_le32_to_cpu(value);
}

rt_inline rt_uint16_t virtio_mmio_read16(struct virtio_mmio *vio, int offset)
{
    return rt_cpu_to_le16(HWREG16(vio->base + offset));
}

rt_inline void virtio_mmio_write16(struct virtio_mmio *vio, int offset, rt_uint16_t value)
{
    HWREG16(vio->base + offset) = rt_le16_to_cpu(value);
}

rt_inline rt_uint8_t virtio_mmio_read8(struct virtio_mmio *vio, int offset)
{
    return HWREG8(vio->base + offset);
}

rt_inline void virtio_mmio_write8(struct virtio_mmio *vio, int offset, rt_uint8_t value)
{
    HWREG8(vio->base + offset) = value;
}

static void virtio_mmio_isr(int irqno, void *param)
{
    rt_uint32_t status;
    struct virtio_mmio *vio = param;

    /* Read interrupts */
    status = virtio_mmio_read32(vio, VIRTIO_MMIO_INTERRUPT_STATUS);

    /* Acknowledge interrupts */
    virtio_mmio_write32(vio, VIRTIO_MMIO_INTERRUPT_ACK, status);

    if (status & VIRTIO_MMIO_INT_CONFIG)
    {
        rt_virtio_device_config_changed(&vio->parent);
    }

    if (status & VIRTIO_MMIO_INT_VIRTQ)
    {
        struct rt_virtqueue *vq;
        rt_ubase_t level = rt_spin_lock_irqsave(&vio->spinlock);

        rt_list_for_each_entry(vq, &vio->parent.vq_node, list)
        {
            rt_virtqueue_isr(irqno, vq);
        }

        rt_spin_unlock_irqrestore(&vio->spinlock, level);
    }
}

static rt_bool_t virtio_mmio_notify(struct rt_virtqueue *vq)
{
    struct virtio_mmio *vio = raw_to_virtio_mmio(vq->vdev);

    virtio_mmio_write32(vio, VIRTIO_MMIO_QUEUE_NOTIFY, vq->index);

    return RT_TRUE;
}

static rt_err_t virtio_mmio_read_shm_region(struct virtio_mmio *vio,
        struct rt_virtio_shm_region *shm)
{
    virtio_mmio_write32(vio, VIRTIO_MMIO_SHM_SEL, shm->id);

    shm->size = virtio_mmio_read32(vio, VIRTIO_MMIO_SHM_LEN_HIGH);
    shm->size <<= 32;
    shm->size |= virtio_mmio_read32(vio, VIRTIO_MMIO_SHM_LEN_LOW);

    if (shm->size == ~(rt_uint64_t)0UL)
    {
        return -RT_EEMPTY;
    }

    shm->base = virtio_mmio_read32(vio, VIRTIO_MMIO_SHM_BASE_HIGH);
    shm->base <<= 32;
    shm->base |= virtio_mmio_read32(vio, VIRTIO_MMIO_SHM_BASE_LOW);

    return RT_EOK;
}

static rt_err_t virtio_mmio_get_status(struct rt_virtio_device *vdev,
        rt_uint8_t *out_status)
{
    struct virtio_mmio *vio = raw_to_virtio_mmio(vdev);

    *out_status = virtio_mmio_read32(vio, VIRTIO_MMIO_STATUS);

    return RT_EOK;
}

static rt_err_t virtio_mmio_set_status(struct rt_virtio_device *vdev,
        rt_uint8_t status)
{
    struct virtio_mmio *vio = raw_to_virtio_mmio(vdev);

    RT_ASSERT(status != 0);

    virtio_mmio_write32(vio, VIRTIO_MMIO_STATUS, status);

    return RT_EOK;
}

static rt_err_t virtio_mmio_get_features(struct rt_virtio_device *vdev,
        rt_uint64_t *out_features)
{
    rt_uint64_t features;
    struct virtio_mmio *vio = raw_to_virtio_mmio(vdev);

    virtio_mmio_write32(vio, VIRTIO_MMIO_DEVICE_FEATURES_SEL, 1);
    features = virtio_mmio_read32(vio, VIRTIO_MMIO_DEVICE_FEATURES);
    features <<= 32;

    virtio_mmio_write32(vio, VIRTIO_MMIO_DEVICE_FEATURES_SEL, 0);
    features |= virtio_mmio_read32(vio, VIRTIO_MMIO_DEVICE_FEATURES);

    *out_features = features;

    return RT_EOK;
}

static rt_err_t virtio_mmio_set_features(struct rt_virtio_device *vdev)
{
    struct virtio_mmio *vio = raw_to_virtio_mmio(vdev);

    /* Make sure there are no mixed devices */
    if (vio->version == 2 && !(vdev->features & RT_BIT(VIRTIO_F_VERSION_1)))
    {
        LOG_E("%s devices (version 2) must provide VIRTIO_F_VERSION_1 feature",
                rt_dm_dev_get_name(&vdev->parent));

        return -RT_EINVAL;
    }

    virtio_mmio_write32(vio, VIRTIO_MMIO_DRIVER_FEATURES_SEL, 1);
    virtio_mmio_write32(vio, VIRTIO_MMIO_DRIVER_FEATURES,
            (rt_uint32_t)(vdev->features >> 32));

    virtio_mmio_write32(vio, VIRTIO_MMIO_DRIVER_FEATURES_SEL, 0);
    virtio_mmio_write32(vio, VIRTIO_MMIO_DRIVER_FEATURES,
            (rt_uint32_t)vdev->features);

    return RT_EOK;
}

static rt_err_t virtio_mmio_get_config(struct rt_virtio_device *vdev,
        rt_uint32_t offset, void *dst, int length)
{
    struct virtio_mmio *vio = raw_to_virtio_mmio(vdev);

    offset += VIRTIO_MMIO_CONFIG;

    if (vio->version == 1)
    {
        for (int i = 0; i < length; ++i)
        {
            ((rt_uint8_t *)dst)[i] = virtio_mmio_read8(vio, offset + i);
        }

        return RT_EOK;
    }

    switch (length)
    {
    case 4:
        *(rt_uint32_t *)dst = virtio_mmio_read32(vio, offset);
        break;
    case 1:
        *(rt_uint8_t *)dst = virtio_mmio_read8(vio, offset);
        break;
    case 2:
        *(rt_uint16_t *)dst = virtio_mmio_read16(vio, offset);
        break;
    case 8:
        *(rt_uint64_t *)dst = virtio_mmio_read64(vio, offset);
        break;
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t virtio_mmio_set_config(struct rt_virtio_device *vdev,
        rt_uint32_t offset, const void *src, int length)
{
    struct virtio_mmio *vio = raw_to_virtio_mmio(vdev);

    offset += VIRTIO_MMIO_CONFIG;

    if (vio->version == 1)
    {
        for (int i = 0; i < length; ++i)
        {
            virtio_mmio_write8(vio, offset + i, ((rt_uint8_t *)src)[i]);
        }

        return RT_EOK;
    }

    switch (length)
    {
    case 4:
        virtio_mmio_write32(vio, offset, *(rt_uint32_t *)src);
        break;
    case 1:
        virtio_mmio_write8(vio, offset, *(rt_uint8_t *)src);
        break;
    case 2:
        virtio_mmio_write16(vio, offset, *(rt_uint16_t *)src);
        break;
    case 8:
        virtio_mmio_write64(vio, offset, *(rt_uint64_t *)src);
        break;
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static struct rt_virtqueue *virtio_mmio_install_vq(struct rt_virtio_device *vdev,
        int index, const char *name, rt_virtqueue_callback cb,
        struct rt_virtqueue_formula *formula)
{
    rt_uint32_t num_max;
    struct rt_virtqueue *vq;
    struct virtio_mmio *vio = raw_to_virtio_mmio(vdev);

    virtio_mmio_write32(vio, VIRTIO_MMIO_QUEUE_SEL, index);

    if (virtio_mmio_read32(vio, vio->version == 1 ?
            VIRTIO_MMIO_QUEUE_PFN : VIRTIO_MMIO_QUEUE_READY))
    {
        return RT_NULL;
    }

    num_max = virtio_mmio_read32(vio, VIRTIO_MMIO_QUEUE_NUM_MAX);

    if (num_max == 0)
    {
        LOG_E("%s.virtqueue[%d](%s) num_max is zero",
                rt_dm_dev_get_name(&vdev->parent), index, name);

        return RT_NULL;
    }

    vq = rt_virtqueue_create(vdev, name, index, num_max, VIRTIO_MMIO_VIRTQ_ALIGN,
            virtio_mmio_notify, cb, formula);

    if (!vq)
    {
        return vq;
    }

    vq->num_max = num_max;

    /* Activate the queue */
    virtio_mmio_write32(vio, VIRTIO_MMIO_QUEUE_NUM, rt_virtqueue_get_virtq_size(vq));

    if (vio->version == 1)
    {
        rt_uint32_t pfn = (rt_ubase_t)rt_kmem_v2p((void *)rt_virtqueue_get_desc_addr(vq));

        pfn >>= VIRTIO_MMIO_VIRTQ_ALIGN_SHIFT;

        virtio_mmio_write32(vio, VIRTIO_MMIO_QUEUE_ALIGN, VIRTIO_MMIO_VIRTQ_ALIGN);
        virtio_mmio_write32(vio, VIRTIO_MMIO_QUEUE_PFN, pfn);
    }
    else
    {
        rt_uint64_t page;

        page = (rt_ubase_t)rt_kmem_v2p((void *)rt_virtqueue_get_desc_addr(vq));
        virtio_mmio_write32(vio, VIRTIO_MMIO_QUEUE_DESC_LOW, (rt_uint32_t)page);
        virtio_mmio_write32(vio, VIRTIO_MMIO_QUEUE_DESC_HIGH, (rt_uint32_t)(page >> 32));

        page = (rt_ubase_t)rt_kmem_v2p((void *)rt_virtqueue_get_avail_addr(vq));
        virtio_mmio_write32(vio, VIRTIO_MMIO_QUEUE_AVAIL_LOW, (rt_uint32_t)page);
        virtio_mmio_write32(vio, VIRTIO_MMIO_QUEUE_AVAIL_HIGH, (rt_uint32_t)(page >> 32));

        page = (rt_ubase_t)rt_kmem_v2p((void *)rt_virtqueue_get_used_addr(vq));
        virtio_mmio_write32(vio, VIRTIO_MMIO_QUEUE_USED_LOW, (rt_uint32_t)page);
        virtio_mmio_write32(vio, VIRTIO_MMIO_QUEUE_USED_HIGH, (rt_uint32_t)(page >> 32));

        virtio_mmio_write32(vio, VIRTIO_MMIO_QUEUE_READY, 1);
    }

    return vq;
}

static rt_err_t virtio_mmio_install_vqs(struct rt_virtio_device *vdev, int vqs_nr,
        struct rt_virtqueue *vqs[], const char *names[], rt_virtqueue_callback cbs[])
{
    struct virtio_mmio *vio = raw_to_virtio_mmio(vdev);

    for (int i = 0, vq_idx = 0; i < vqs_nr; ++i)
    {
        if (!names[i])
        {
            vqs[i] = RT_NULL;

            continue;
        }

        vqs[i] = virtio_mmio_install_vq(vdev, vq_idx++, names[i], cbs[i], RT_NULL);

        if (!vqs[i])
        {
            rt_virtio_virtqueue_release(vdev);

            return -RT_ERROR;
        }
    }

    rt_hw_interrupt_install(vio->irq, virtio_mmio_isr, vio,
            rt_dm_dev_get_name(&vdev->parent));
    rt_hw_interrupt_umask(vio->irq);

    return RT_EOK;
}

static rt_err_t virtio_mmio_release_vqs(struct rt_virtio_device *vdev)
{
    struct rt_virtqueue *vq, *vq_next;
    struct virtio_mmio *vio = raw_to_virtio_mmio(vdev);

    rt_hw_interrupt_mask(vio->irq);
    rt_pic_detach_irq(vio->irq, vio);

    rt_list_for_each_entry_safe(vq, vq_next, &vio->parent.vq_node, list)
    {
        virtio_mmio_write32(vio, VIRTIO_MMIO_QUEUE_SEL, vq->index);

        if (vio->version == 1)
        {
            virtio_mmio_write32(vio, VIRTIO_MMIO_QUEUE_PFN, RT_NULL);
        }
        else
        {
            rt_uint32_t status;

            virtio_mmio_write32(vio, VIRTIO_MMIO_QUEUE_READY, RT_NULL);
            status = virtio_mmio_read32(vio, VIRTIO_MMIO_QUEUE_READY);

            if (!status)
            {
                LOG_W("%s.virtqueue[%s] VIRTIO_MMIO_QUEUE_READY = %d",
                        rt_dm_dev_get_name(&vq->vdev->parent), vq->name, status);
            }
        }

        rt_virtqueue_delete(&vio->parent, vq);
    }

    return RT_EOK;
}

static rt_err_t virtio_mmio_control_vqs(struct rt_virtio_device *vdev,
        rt_uint32_t cfg, void *data)
{
    rt_err_t err = RT_EOK;
    struct virtio_mmio *vio = raw_to_virtio_mmio(vdev);

    switch (cfg)
    {
    case RT_VIRTQUEUE_CTL_IRQ_AFFINITY:
        err = rt_pic_irq_set_affinity(vio->irq, (rt_bitmap_t *)data);
        break;

    case RT_VIRTQUEUE_CTL_READ_SHM_REGION:
        if (!data)
        {
            err = -RT_EINVAL;
            break;
        }

        err = virtio_mmio_read_shm_region(vio, data);
        break;

    default:
        err = -RT_ENOSYS;
        break;
    }

    return err;
}

static rt_err_t virtio_mmio_generation(struct rt_virtio_device *vdev,
        rt_uint32_t *out_counter)
{
    struct virtio_mmio *vio = raw_to_virtio_mmio(vdev);

    if (vio->version == 1)
    {
        *out_counter = 0;
    }
    else
    {
        *out_counter = virtio_mmio_read32(vio, VIRTIO_MMIO_CONFIG_GENERATION);
    }

    return RT_EOK;
}

static rt_err_t virtio_mmio_reset(struct rt_virtio_device *vdev)
{
    struct virtio_mmio *vio = raw_to_virtio_mmio(vdev);

    virtio_mmio_write32(vio, VIRTIO_MMIO_STATUS, 0);

    return RT_EOK;
}

static const struct rt_virtio_transport virtio_mmio_trans =
{
    .get_status = virtio_mmio_get_status,
    .set_status = virtio_mmio_set_status,
    .get_features = virtio_mmio_get_features,
    .set_features = virtio_mmio_set_features,
    .get_config = virtio_mmio_get_config,
    .set_config = virtio_mmio_set_config,
    .install_vqs = virtio_mmio_install_vqs,
    .release_vqs = virtio_mmio_release_vqs,
    .control_vqs = virtio_mmio_control_vqs,
    .generation = virtio_mmio_generation,
    .reset = virtio_mmio_reset,
};

static rt_err_t virtio_mmio_probe(struct rt_platform_device *pdev)
{
    rt_err_t err = RT_EOK;
    rt_uint32_t magic;
    struct rt_virtio_device *vdev;
    struct rt_device *dev = &pdev->parent;
    struct virtio_mmio *vio = rt_calloc(1, sizeof(*vio));

    if (!vio)
    {
        return -RT_ENOMEM;
    }

    vio->base = rt_dm_dev_iomap(dev, 0);

    if (!vio->base)
    {
        err = -RT_EIO;

        goto _fail;
    }

    vio->irq = rt_dm_dev_get_irq(dev, 0);

    if (vio->irq < 0)
    {
        err = vio->irq;

        goto _fail;
    }

    magic = virtio_mmio_read32(vio, VIRTIO_MMIO_MAGIC);

    /* 0x74726976 (a Little Endian equivalent of the "virt" string). */
    if (magic != ('v' | 'i' << 8 | 'r' << 16 | 't' << 24))
    {
        err = -RT_EINVAL;

        LOG_E("Invalid magic: %x", magic);

        goto _fail;
    }

    vio->version = virtio_mmio_read32(vio, VIRTIO_MMIO_VERSION);

    /* Only support version 1~2 */
    if (vio->version < 1 || vio->version > 2)
    {
        err = -RT_ENOSYS;

        LOG_E("Not support version: %d", vio->version);

        goto _fail;
    }

    vdev = &vio->parent;

    vdev->id.device = virtio_mmio_read32(vio, VIRTIO_MMIO_DEVICE_ID);

    if (vdev->id.device == VIRTIO_DEVICE_ID_INVALID)
    {
        err = -RT_EEMPTY;
        goto _fail;
    }

    vdev->id.vendor = virtio_mmio_read32(vio, VIRTIO_MMIO_VENDOR_ID);

    if (vio->version == 1)
    {
        virtio_mmio_write32(vio, VIRTIO_MMIO_GUEST_PAGE_SIZE, VIRTIO_MMIO_VIRTQ_PAGE_SZIE);
    }

    rt_spin_lock_init(&vio->spinlock);

    vdev->trans = &virtio_mmio_trans;
    vdev->parent.ofw_node = dev->ofw_node;

    if ((err = rt_virtio_device_register(vdev)))
    {
        goto _fail;
    }

    dev->user_data = vio;

    return RT_EOK;

_fail:
    if (vio->base)
    {
        rt_iounmap(vio->base);
    }
    rt_free(vio);

    return err;
}

static rt_err_t virtio_mmio_remove(struct rt_platform_device *pdev)
{
    struct virtio_mmio *vio = pdev->parent.user_data;

    rt_hw_interrupt_mask(vio->irq);
    rt_pic_detach_irq(vio->irq, vio);

    rt_bus_remove_device(&vio->parent.parent);

    rt_iounmap(vio->base);
    rt_free(vio);

    return RT_EOK;
}

static const struct rt_ofw_node_id virtio_mmio_ofw_ids[] =
{
    { .compatible = "virtio,mmio" },
    { /* sentinel */ }
};

static struct rt_platform_driver virtio_mmio_driver =
{
    .name = "virtio-mmio",
    .ids = virtio_mmio_ofw_ids,

    .probe = virtio_mmio_probe,
    .remove = virtio_mmio_remove,
};
RT_PLATFORM_DRIVER_EXPORT(virtio_mmio_driver);
