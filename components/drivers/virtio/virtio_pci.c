/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-07     GuEe-GUI     first version
 */

#include <rtthread.h>

#define DBG_TAG "virtio.pci"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mmu.h>

#include <drivers/pic.h>
#include <drivers/pci.h>
#include <drivers/pci_msi.h>
#include <drivers/virtio.h>
#include <drivers/core/bus.h>

#define VIRTIO_PCI_CAP_COMMON_CFG           1   /* Common configuration */
#define VIRTIO_PCI_CAP_NOTIFY_CFG           2   /* Notifications */
#define VIRTIO_PCI_CAP_ISR_CFG              3   /* ISR Status */
#define VIRTIO_PCI_CAP_DEVICE_CFG           4   /* Device specific configuration */
#define VIRTIO_PCI_CAP_PCI_CFG              5   /* PCI configuration access */
#define VIRTIO_PCI_CAP_SHARED_MEMORY_CFG    8   /* Shared memory region */
#define VIRTIO_PCI_CAP_VENDOR_CFG           9   /* Vendor-specific data */

struct virtio_pci_cap
{
    rt_uint8_t cap_vndr;                /* Generic PCI field: PCI_CAP_ID_VNDR */
    rt_uint8_t cap_next;                /* Generic PCI field: next ptr. */
    rt_uint8_t cap_len;                 /* Generic PCI field: capability length */
    rt_uint8_t cfg_type;                /* Identifies the structure. */
    rt_uint8_t bar;                     /* Where to find it. */
    rt_uint8_t id;                      /* Multiple capabilities of the same type */
    rt_uint8_t padding[2];              /* Pad to full dword. */
    rt_le32_t offset;                   /* Offset within bar. */
    rt_le32_t length;                   /* Length of the structure, in bytes. */
};

struct virtio_pci_cap64
{
    struct virtio_pci_cap cap;
    rt_le32_t offset_hi;                /* Most sig 32 bits of offset */
    rt_le32_t length_hi;                /* Most sig 32 bits of length */
};

struct virtio_pci_common_cfg
{
    /* About the whole device. */
    rt_le32_t device_feature_select;    /* Read-write */
    rt_le32_t device_feature;           /* Read-only for driver */
    rt_le32_t driver_feature_select;    /* Read-write */
    rt_le32_t driver_feature;           /* Read-write */
    rt_le16_t config_msix_vector;       /* Read-write */
    rt_le16_t num_queues;               /* Read-only for driver */
    rt_uint8_t device_status;           /* Read-write */
    rt_uint8_t config_generation;       /* Read-only for driver */

    /* About a specific virtqueue. */
    rt_le16_t queue_select;             /* Read-write */
    rt_le16_t queue_size;               /* Read-write */
    rt_le16_t queue_msix_vector;        /* Read-write */
    rt_le16_t queue_enable;             /* Read-write */
    rt_le16_t queue_notify_off;         /* Read-only for driver */
    rt_le32_t queue_desc_low;           /* read-write */
    rt_le32_t queue_desc_high;          /* read-write */
    rt_le32_t queue_avail_low;          /* read-write */
    rt_le32_t queue_avail_high;         /* read-write */
    rt_le32_t queue_used_low;           /* read-write */
    rt_le32_t queue_used_high;          /* read-write */
};

struct virtio_pci_notify_cap
{
    struct virtio_pci_cap cap;
    rt_le32_t notify_off_multiplier;    /* Multiplier for queue_notify_off. */
};

struct virtio_pci_cfg_cap
{
    struct virtio_pci_cap cap;
    rt_uint8_t pci_cfg_data[4];         /* Data for BAR access. */
};

#define VIRTIO_PCI_VIRTQ_ALIGN          4096
#define VIRTIO_PCI_ISR_QUEUE            RT_BIT(0)
#define VIRTIO_PCI_ISR_CONFIG           RT_BIT(1)
#define VIRTIO_MSI_NO_VECTOR            0xffff

#define VIRTIO_PCI_DEVICE_START         0x1040
#define VIRTIO_PCI_DEVICE_END           0x107f

struct virtio_pci
{
    struct rt_virtio_device parent;
    struct rt_pci_device *pdev;

    void *dev_regs;
    void *isr_regs;
    void *notify_regs;
    struct virtio_pci_common_cfg *common;

    rt_size_t dev_regs_offset;
    rt_size_t isr_regs_offset;
    rt_size_t notify_regs_offset;
    rt_size_t common_offset;

    rt_size_t notify_len;
    rt_uint32_t notify_offset_multiplier;

    int nvectors;
    struct rt_pci_msix_entry *msix_entries;
};

#define raw_to_virtio_pci(raw) rt_container_of(raw, struct virtio_pci, parent)

rt_inline rt_uint32_t virtio_pci_read32(void *addr)
{
    return rt_cpu_to_le32(HWREG32(addr));
}

rt_inline void virtio_pci_write32(void *addr, rt_uint32_t value)
{
    HWREG32(addr) = rt_le32_to_cpu(value);
}

rt_inline rt_uint16_t virtio_pci_read16(void *addr)
{
    return rt_cpu_to_le16(HWREG16(addr));
}

rt_inline void virtio_pci_write16(void *addr, rt_uint16_t value)
{
    HWREG16(addr) = rt_le16_to_cpu(value);
}

rt_inline rt_uint8_t virtio_pci_read8(void *addr)
{
    return HWREG8(addr);
}

rt_inline void virtio_pci_write8(void *addr, rt_uint8_t value)
{
    HWREG8(addr) = value;
}

static void virtio_pci_vq_isr(int irqno, void *param)
{
    struct rt_virtqueue *vq = param;

    rt_virtqueue_isr(irqno, vq);
}

static void virtio_pci_config_isr(int irqno, void *param)
{
    struct virtio_pci *vp = param;

    rt_virtio_device_config_changed(&vp->parent);
}

static void virtio_pci_isr(int irqno, void *param)
{
    rt_uint8_t isr;
    struct rt_virtqueue *vq;
    struct virtio_pci *vp = param;

    isr = virtio_pci_read8(vp->isr_regs);

    if (!isr)
    {
        return;
    }

    if (isr & VIRTIO_PCI_ISR_CONFIG)
    {
        virtio_pci_config_isr(irqno, param);
    }

    if (isr & VIRTIO_PCI_ISR_QUEUE)
    {
        rt_list_for_each_entry(vq, &vp->parent.vq_node, list)
        {
            virtio_pci_vq_isr(irqno, vq);
        }
    }
}

static rt_bool_t virtio_pci_notify(struct rt_virtqueue *vq)
{
    rt_uint16_t offset;
    struct virtio_pci *vp = raw_to_virtio_pci(vq->vdev);

    virtio_pci_write16(&vp->common->queue_select, vq->index);

    offset = virtio_pci_read16(&vp->common->queue_notify_off);
    offset *= vp->notify_offset_multiplier;

    /* We no config VIRTIO_F_NOTIFICATION_DATA, so it is only 16 bits */
    if (offset > vp->notify_len - sizeof(rt_uint16_t))
    {
        return RT_FALSE;
    }

    virtio_pci_write16(vp->notify_regs + offset, vq->index);

    return RT_TRUE;
}

static rt_uint16_t virtio_pci_queue_vector(struct virtio_pci *vp,
        rt_uint16_t index, rt_uint16_t vector)
{
    struct virtio_pci_common_cfg *cfg = vp->common;

    virtio_pci_write16(&cfg->queue_select, index);
    virtio_pci_write16(&cfg->queue_msix_vector, vector);

    /* Flush the write out to device */
    return virtio_pci_read16(&cfg->queue_msix_vector);
}

static rt_uint16_t virtio_pci_config_vector(struct virtio_pci *vp,
        rt_uint16_t vector)
{
    struct virtio_pci_common_cfg *cfg = vp->common;

    virtio_pci_write16(&cfg->config_msix_vector, vector);

    /* Flush the write out to device */
    return virtio_pci_read16(&cfg->config_msix_vector);
}

static rt_err_t virtio_pci_read_shm_region(struct virtio_pci *vp,
        struct rt_virtio_shm_region *shm)
{
    int pos;
    rt_uint8_t bar;
    rt_uint64_t offset, len;
    struct rt_pci_device *pdev = vp->pdev;

    for (pos = rt_pci_find_capability(pdev, PCIY_VENDOR); pos > 0;
         pos = rt_pci_find_next_capability(pdev, pos, PCIY_VENDOR))
    {
        rt_uint32_t value32;
        rt_uint8_t type, cap_len, id;

        rt_pci_read_config_u8(pdev,
                pos + rt_offsetof(struct virtio_pci_cap, cfg_type), &type);

        if (type != VIRTIO_PCI_CAP_SHARED_MEMORY_CFG)
        {
            continue;
        }

        rt_pci_read_config_u8(pdev,
                pos + rt_offsetof(struct virtio_pci_cap, cap_len), &cap_len);

        if (cap_len != sizeof(struct virtio_pci_cap64))
        {
            LOG_E("%s: shm cap with bad size offset: %d size: %d",
                    rt_dm_dev_get_name(&pdev->parent), pos, cap_len);

            continue;
        }

        rt_pci_read_config_u8(pdev,
                pos + rt_offsetof(struct virtio_pci_cap, id), &id);

        if (id != shm->id)
        {
            continue;
        }

        rt_pci_read_config_u8(pdev,
                pos + rt_offsetof(struct virtio_pci_cap, bar), &bar);

        if (bar >= PCI_STD_NUM_BARS)
        {
            continue;
        }

        rt_pci_read_config_u32(pdev,
                pos + rt_offsetof(struct virtio_pci_cap, offset), &value32);
        offset = value32;

        rt_pci_read_config_u32(pdev,
                pos + rt_offsetof(struct virtio_pci_cap, length), &value32);
        len = value32;

        rt_pci_read_config_u32(pdev,
                pos + rt_offsetof(struct virtio_pci_cap64, offset_hi), &value32);
        offset |= ((rt_uint64_t)value32) << 32;

        rt_pci_read_config_u32(pdev,
                pos + rt_offsetof(struct virtio_pci_cap64, length_hi), &value32);
        len |= ((rt_uint64_t)value32) << 32;

        break;
    }

    if (!pos)
    {
        return -RT_EEMPTY;
    }

    if (offset + len < offset)
    {
        LOG_E("%s: cap offset + len overflow detected",
                rt_dm_dev_get_name(&pdev->parent));

        return -RT_EIO;
    }

    if (offset + len > pdev->resource[bar].size)
    {
        LOG_E("%s: bar shorter than cap offset + len",
                rt_dm_dev_get_name(&pdev->parent));

        return -RT_EIO;
    }

    shm->base = pdev->resource[bar].base + offset;
    shm->size = len;

    return RT_EOK;
}

static rt_err_t virtio_pci_get_status(struct rt_virtio_device *vdev,
        rt_uint8_t *out_status)
{
    struct virtio_pci *vp = raw_to_virtio_pci(vdev);

    *out_status = virtio_pci_read32(&vp->common->device_status);

    return RT_EOK;
}

static rt_err_t virtio_pci_set_status(struct rt_virtio_device *vdev,
        rt_uint8_t status)
{
    struct virtio_pci *vp = raw_to_virtio_pci(vdev);

    virtio_pci_write32(&vp->common->device_status, status);

    return RT_EOK;
}

static rt_err_t virtio_pci_get_features(struct rt_virtio_device *vdev,
        rt_uint64_t *out_features)
{
    rt_uint64_t features;
    struct virtio_pci *vp = raw_to_virtio_pci(vdev);

    virtio_pci_write32(&vp->common->device_feature_select, 1);
    features = virtio_pci_read32(&vp->common->device_feature);
    features <<= 32;

    virtio_pci_write32(&vp->common->device_feature_select, 0);
    features |= virtio_pci_read32(&vp->common->device_feature);

    *out_features = features;

    return RT_EOK;
}

static rt_err_t virtio_pci_set_features(struct rt_virtio_device *vdev)
{
    struct virtio_pci *vp = raw_to_virtio_pci(vdev);

    virtio_pci_write32(&vp->common->driver_feature_select, 1);
    virtio_pci_write32(&vp->common->driver_feature, (rt_uint32_t)(vdev->features >> 32));

    virtio_pci_write32(&vp->common->driver_feature_select, 0);
    virtio_pci_write32(&vp->common->driver_feature, (rt_uint32_t)vdev->features);

    return RT_EOK;
}

static rt_err_t virtio_pci_get_config(struct rt_virtio_device *vdev,
        rt_uint32_t offset, void *dst, int length)
{
    rt_uint8_t byte;
    rt_le16_t word;
    rt_le32_t dword;
    struct virtio_pci *vp = raw_to_virtio_pci(vdev);

    switch (length)
    {
    case 4:
        dword = virtio_pci_read32(vp->dev_regs + offset);
        rt_memcpy(dst, &dword, sizeof(dword));
        break;
    case 1:
        byte = virtio_pci_read8(vp->dev_regs + offset);
        rt_memcpy(dst, &byte, sizeof(byte));
        break;
    case 2:
        word = virtio_pci_read16(vp->dev_regs + offset);
        rt_memcpy(dst, &word, sizeof(word));
        break;
    case 8:
        dword = virtio_pci_read32(vp->dev_regs + offset);
        rt_memcpy(dst, &dword, sizeof(dword));
        dword = virtio_pci_read32(vp->dev_regs + offset + sizeof(dword));
        rt_memcpy(dst + sizeof(dword), &dword, sizeof(dword));
        break;
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t virtio_pci_set_config(struct rt_virtio_device *vdev,
        rt_uint32_t offset, const void *src, int length)
{
    rt_uint8_t byte;
    rt_le16_t word;
    rt_le32_t dword;
    struct virtio_pci *vp = raw_to_virtio_pci(vdev);

    switch (length)
    {
    case 4:
        rt_memcpy(&dword, src, sizeof(dword));
        virtio_pci_write32(vp->dev_regs + offset, dword);
        break;
    case 1:
        rt_memcpy(&byte, src, sizeof(byte));
        virtio_pci_write8(vp->dev_regs + offset, byte);
        break;
    case 2:
        rt_memcpy(&word, src, sizeof(word));
        virtio_pci_write16(vp->dev_regs + offset, word);
        break;
    case 8:
        rt_memcpy(&dword, src, sizeof(dword));
        virtio_pci_write32(vp->dev_regs + offset, dword);
        rt_memcpy(&dword, src + sizeof(dword), sizeof(dword));
        virtio_pci_write32(vp->dev_regs + offset + sizeof(dword), dword);
        break;
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static struct rt_virtqueue *virtio_pci_install_vq(struct rt_virtio_device *vdev,
        int index, const char *name, rt_virtqueue_callback cb,
        struct rt_virtqueue_formula *formula)
{
    rt_uint64_t page;
    rt_uint32_t num_max;
    struct rt_virtqueue *vq;
    struct virtio_pci *vp = raw_to_virtio_pci(vdev);
    struct virtio_pci_common_cfg *cfg = vp->common;

    if (index >= virtio_pci_read16(&cfg->num_queues))
    {
        return RT_NULL;
    }

    virtio_pci_write16(&cfg->queue_select, index);

    num_max = virtio_pci_read16(&cfg->queue_size);

    if (!num_max || virtio_pci_read16(&cfg->queue_enable))
    {
        return RT_NULL;
    }

    vq = rt_virtqueue_create(vdev, name, index, num_max, VIRTIO_PCI_VIRTQ_ALIGN,
            virtio_pci_notify, cb, formula);

    if (!vq)
    {
        return vq;
    }

    vq->num_max = num_max;

    virtio_pci_write16(&cfg->queue_size, rt_virtqueue_get_virtq_size(vq));

    page = (rt_ubase_t)rt_kmem_v2p((void *)rt_virtqueue_get_desc_addr(vq));
    virtio_pci_write32(&cfg->queue_desc_low, (rt_uint32_t)page);
    virtio_pci_write32(&cfg->queue_desc_high, (rt_uint32_t)(page >> 32));

    page = (rt_ubase_t)rt_kmem_v2p((void *)rt_virtqueue_get_avail_addr(vq));
    virtio_pci_write32(&cfg->queue_avail_low, (rt_uint32_t)page);
    virtio_pci_write32(&cfg->queue_avail_high, (rt_uint32_t)(page >> 32));

    page = (rt_ubase_t)rt_kmem_v2p((void *)rt_virtqueue_get_used_addr(vq));
    virtio_pci_write32(&cfg->queue_used_low, (rt_uint32_t)page);
    virtio_pci_write32(&cfg->queue_used_high, (rt_uint32_t)(page >> 32));

    virtio_pci_write16(&cfg->queue_enable, 1);

    return vq;
}

static rt_err_t virtio_pci_install_vqs(struct rt_virtio_device *vdev, int vqs_nr,
        struct rt_virtqueue *vqs[], const char *names[], rt_virtqueue_callback cbs[])
{
    void *isr;
    rt_err_t err;
    char name[RT_NAME_MAX];
    int nvectors = vqs_nr + 1, irq, cpuid = 0;
    RT_IRQ_AFFINITY_DECLARE(affinity) = { 0 };
    struct virtio_pci *vp = raw_to_virtio_pci(vdev);

    vp->msix_entries = rt_malloc(nvectors * sizeof(*vp->msix_entries));

    if (!vp->msix_entries)
    {
        return -RT_ENOMEM;
    }

    rt_pci_msix_entry_index_linear(vp->msix_entries, nvectors);

    /* Try MSI-X with one vector per queue */
    if (rt_pci_msix_enable(vp->pdev, vp->msix_entries, nvectors) < 0)
    {
        nvectors = 2;

        /* Try MSI-X with one shared for queues, one vector for config */
        if (rt_pci_msix_enable(vp->pdev, vp->msix_entries, nvectors) < 0)
        {
            /* Only supported INTx */
            nvectors = 1;

            rt_free(vp->msix_entries);
            vp->msix_entries = RT_NULL;
        }
    }

    for (int i = 0, vq_idx = 0; i < vqs_nr; ++i, ++vq_idx)
    {
        if (!names[i])
        {
            vqs[i] = RT_NULL;

            continue;
        }

        vqs[i] = virtio_pci_install_vq(vdev, vq_idx, names[i], cbs[i], RT_NULL);

        if (!vqs[i])
        {
            err = -RT_ERROR;
            goto _fail;
        }

        if (nvectors >= 2 || (nvectors == 2 && vqs_nr == 1))
        {
            int vec_idx = nvectors != 2 ? vq_idx : 0;
            int msi_idx = nvectors != 2 ? i : 0;

            if (!cbs[i])
            {
                virtio_pci_queue_vector(vp, vq_idx, VIRTIO_MSI_NO_VECTOR);

                continue;
            }

            if (virtio_pci_queue_vector(vp, vq_idx, vec_idx) == VIRTIO_MSI_NO_VECTOR)
            {
                err = -RT_EBUSY;
                goto _fail;
            }

            irq = vp->msix_entries[msi_idx].irq;

            rt_snprintf(name, RT_NAME_MAX, "%s-%s-%d",
                    rt_dm_dev_get_name(&vdev->parent), names[i], vq_idx);

            RT_IRQ_AFFINITY_SET(affinity, cpuid % RT_CPUS_NR);
            rt_pic_irq_set_affinity(irq, affinity);
            RT_IRQ_AFFINITY_CLEAR(affinity, cpuid++ % RT_CPUS_NR);

            rt_hw_interrupt_install(irq, virtio_pci_vq_isr, vqs[i], name);
            rt_hw_interrupt_umask(irq);
        }
    }

    if (nvectors >= 2)
    {
        rt_snprintf(name, RT_NAME_MAX, "%s-config",
                    rt_dm_dev_get_name(&vdev->parent));

        isr = virtio_pci_config_isr;
        irq = vp->msix_entries[nvectors - 1].irq;

        if (virtio_pci_config_vector(vp, nvectors - 1) == VIRTIO_MSI_NO_VECTOR)
        {
            err = -RT_EBUSY;
            goto _fail;
        }

        RT_IRQ_AFFINITY_SET(affinity, cpuid % RT_CPUS_NR);
        rt_pic_irq_set_affinity(irq, affinity);
        RT_IRQ_AFFINITY_CLEAR(affinity, cpuid++ % RT_CPUS_NR);
    }
    else
    {
        rt_snprintf(name, RT_NAME_MAX, "%s", rt_dm_dev_get_name(&vdev->parent));

        isr = virtio_pci_isr;
        irq = vp->pdev->irq;

        virtio_pci_config_vector(vp, VIRTIO_MSI_NO_VECTOR);
    }

    rt_hw_interrupt_install(irq, isr, vp, name);
    rt_hw_interrupt_umask(irq);

    vp->nvectors = nvectors;

    return RT_EOK;

_fail:
    rt_virtio_virtqueue_release(vdev);

    return err;
}

static rt_err_t virtio_pci_release_vqs(struct rt_virtio_device *vdev)
{
    int irq;
    struct rt_virtqueue *vq, *vq_next;
    struct virtio_pci *vp = raw_to_virtio_pci(vdev);

    rt_list_for_each_entry_safe(vq, vq_next, &vp->parent.vq_node, list)
    {
        virtio_pci_write16(&vp->common->queue_select, vq->index);

        if (vp->nvectors >= 2)
        {
            virtio_pci_queue_vector(vp, vq->index, VIRTIO_MSI_NO_VECTOR);

            irq = vp->msix_entries[vq->index].irq;

            rt_hw_interrupt_mask(irq);
            rt_pic_detach_irq(irq, vq);
        }

        /* Select and deactivate the queue */
        virtio_pci_write16(&vp->common->queue_enable, 0);

        rt_virtqueue_delete(&vp->parent, vq);
    }

    if (vp->nvectors >= 2)
    {
        irq = vp->msix_entries[vp->nvectors - 1].irq;
    }
    else
    {
        irq = vp->pdev->irq;
    }

    rt_hw_interrupt_mask(irq);
    rt_pic_detach_irq(irq, vp);

    return RT_EOK;
}

static rt_err_t virtio_pci_control_vqs(struct rt_virtio_device *vdev,
        rt_uint32_t cfg, void *data)
{
    rt_err_t err = RT_EOK;
    struct virtio_pci *vp = raw_to_virtio_pci(vdev);

    switch (cfg)
    {
    case RT_VIRTQUEUE_CTL_IRQ_AFFINITY:
        if (vp->nvectors == 1)
        {
            err = rt_pic_irq_set_affinity(vp->pdev->irq, (rt_bitmap_t *)data);
        }
        else
        {
            err = -RT_ENOSYS;
        }
        break;

    case RT_VIRTQUEUE_CTL_READ_SHM_REGION:
        if (!data)
        {
            err = -RT_EINVAL;
            break;
        }

        err = virtio_pci_read_shm_region(vp, data);
        break;

    default:
        err = -RT_ENOSYS;
        break;
    }

    return err;
}

static rt_err_t virtio_pci_generation(struct rt_virtio_device *vdev,
        rt_uint32_t *out_counter)
{
    struct virtio_pci *vp = raw_to_virtio_pci(vdev);

    *out_counter = virtio_pci_read8(&vp->common->config_generation);

    return RT_EOK;
}

static rt_err_t virtio_pci_reset(struct rt_virtio_device *vdev)
{
    struct virtio_pci *vp = raw_to_virtio_pci(vdev);

    virtio_pci_write8(&vp->common->device_status, 0);

    while (virtio_pci_read8(&vp->common->device_status))
    {
        rt_thread_mdelay(1);
    }

    return RT_EOK;
}

static const struct rt_virtio_transport virtio_pci_trans =
{
    .get_status = virtio_pci_get_status,
    .set_status = virtio_pci_set_status,
    .get_features = virtio_pci_get_features,
    .set_features = virtio_pci_set_features,
    .get_config = virtio_pci_get_config,
    .set_config = virtio_pci_set_config,
    .install_vqs = virtio_pci_install_vqs,
    .release_vqs = virtio_pci_release_vqs,
    .control_vqs = virtio_pci_control_vqs,
    .generation = virtio_pci_generation,
    .reset = virtio_pci_reset,
};

static rt_uint32_t virtio_pci_find_capability(struct rt_pci_device *pdev,
        rt_uint8_t cfg_type, rt_size_t cap_size, struct virtio_pci_cap *out_cap)
{
    int offset;

    for (rt_uint8_t pos = rt_pci_find_capability(pdev, PCIY_VENDOR);
        pos > 0 && (PCI_REGMAX + 1) - cap_size >= pos;
        pos = rt_pci_find_next_capability(pdev, pos, PCIY_VENDOR))
    {
        offset = pos + rt_offsetof(struct virtio_pci_cap, cap_vndr);
        rt_pci_read_config_u8(pdev, offset, &out_cap->cap_vndr);
        offset = pos + rt_offsetof(struct virtio_pci_cap, cap_next);
        rt_pci_read_config_u8(pdev, offset, &out_cap->cap_next);
        offset = pos + rt_offsetof(struct virtio_pci_cap, cap_len);
        rt_pci_read_config_u8(pdev, offset, &out_cap->cap_len);
        offset = pos + rt_offsetof(struct virtio_pci_cap, cfg_type);
        rt_pci_read_config_u8(pdev, offset, &out_cap->cfg_type);
        offset = pos + rt_offsetof(struct virtio_pci_cap, bar);
        rt_pci_read_config_u8(pdev, offset, &out_cap->bar);
        offset = pos + rt_offsetof(struct virtio_pci_cap, offset);
        rt_pci_read_config_u32(pdev, offset, &out_cap->offset);
        offset = pos + rt_offsetof(struct virtio_pci_cap, length);
        rt_pci_read_config_u32(pdev, offset, &out_cap->length);

        /* Ignore structures with reserved BAR values */
        if (out_cap->bar >= RT_PCI_BAR_NR_MAX)
        {
            continue;
        }

        if (out_cap->cfg_type == cfg_type)
        {
            return pos;
        }
    }

    return 0;
}

static void virtio_pci_free(struct virtio_pci *vp)
{
    if (vp->common)
    {
        rt_iounmap(vp->common - vp->common_offset);
    }
    if (vp->dev_regs)
    {
        rt_iounmap(vp->dev_regs - vp->dev_regs_offset);
    }
    if (vp->notify_regs)
    {
        rt_iounmap(vp->notify_regs - vp->notify_regs_offset);
    }
    if (vp->isr_regs)
    {
        rt_iounmap(vp->isr_regs - vp->isr_regs_offset);
    }

    rt_free(vp);
}

static rt_err_t virtio_pci_probe(struct rt_pci_device *pdev)
{
    rt_err_t err = RT_EOK;
    rt_uint8_t common, notify, device, isr;
    struct virtio_pci_cap common_cap, notify_cap, device_cap, isr_cap;
    struct rt_virtio_device *vdev;
    struct virtio_pci *vp;

    if (pdev->device < VIRTIO_PCI_DEVICE_START ||
        pdev->device > VIRTIO_PCI_DEVICE_END)
    {
        return -RT_EINVAL;
    }

    if (!(vp = rt_calloc(1, sizeof(*vp))))
    {
        return -RT_ENOMEM;
    }
    vp->pdev = pdev;

    if (!(common = virtio_pci_find_capability(pdev, VIRTIO_PCI_CAP_COMMON_CFG,
            sizeof(struct virtio_pci_cap), &common_cap)))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if (!(device = virtio_pci_find_capability(pdev, VIRTIO_PCI_CAP_DEVICE_CFG,
            sizeof(struct virtio_pci_cap), &device_cap)))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if (!(notify = virtio_pci_find_capability(pdev, VIRTIO_PCI_CAP_NOTIFY_CFG,
            sizeof(struct virtio_pci_notify_cap), &notify_cap)))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if (!(isr = virtio_pci_find_capability(pdev, VIRTIO_PCI_CAP_ISR_CFG,
            sizeof(struct virtio_pci_cap), &isr_cap)))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if (!(vp->common = rt_pci_iomap(pdev, common_cap.bar)))
    {
        err = -RT_EIO;
        goto _fail;
    }
    vp->common_offset = common_cap.offset;
    vp->common += vp->common_offset;

    if (!(vp->dev_regs = rt_pci_iomap(pdev, device_cap.bar)))
    {
        err = -RT_EIO;
        goto _fail;
    }
    vp->dev_regs_offset = device_cap.offset;
    vp->dev_regs += vp->dev_regs_offset;

    if (!(vp->notify_regs = rt_pci_iomap(pdev, notify_cap.bar)))
    {
        err = -RT_EIO;
        goto _fail;
    }
    vp->notify_regs_offset = notify_cap.offset;
    vp->notify_regs += vp->notify_regs_offset;
    vp->notify_len = notify_cap.length;

    if (!(vp->isr_regs = rt_pci_iomap(pdev, isr_cap.bar)))
    {
        err = -RT_EIO;
        goto _fail;
    }
    vp->isr_regs_offset = isr_cap.offset;
    vp->isr_regs += vp->isr_regs_offset;

    rt_pci_read_config_u32(pdev,
            notify + rt_offsetof(struct virtio_pci_notify_cap, notify_off_multiplier),
            &vp->notify_offset_multiplier);

    vdev = &vp->parent;
    vdev->id.device = pdev->device - VIRTIO_PCI_DEVICE_START;
    rt_pci_read_config_u16(pdev, PCIR_SUBVEND_0, (rt_uint16_t *)&vdev->id.vendor);

    vdev->trans = &virtio_pci_trans;
    vdev->parent.ofw_node = pdev->parent.ofw_node;

    if ((err = rt_virtio_device_register(vdev)))
    {
        goto _fail;
    }

    pdev->parent.user_data = vp;

    return err;

_fail:
    virtio_pci_free(vp);

    return err;
}

static rt_err_t virtio_pci_remove(struct rt_pci_device *pdev)
{
    struct virtio_pci *vp = pdev->parent.user_data;

    rt_bus_remove_device(&vp->parent.parent);

    virtio_pci_free(vp);

    return RT_EOK;
}

static struct rt_pci_device_id virtio_pci_ids[] =
{
    { RT_PCI_DEVICE_ID(PCI_VENDOR_ID_REDHAT_QUMRANET, PCI_ANY_ID), },
    { /* sentinel */ }
};

static struct rt_pci_driver virtio_pci_driver =
{
    .name = "virtio-pci",

    .ids = virtio_pci_ids,
    .probe = virtio_pci_probe,
    .remove = virtio_pci_remove,
};
RT_PCI_DRIVER_EXPORT(virtio_pci_driver);
