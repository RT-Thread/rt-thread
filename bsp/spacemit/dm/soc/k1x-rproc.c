/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <elf.h>
#include <drivers/byteorder.h>
#include <drivers/core/bus.h>
#include <drivers/dma.h>
#include <drivers/rpmsg.h>
#include <drivers/virtq.h>
#include <drivers/virtio.h>

#define DBG_TAG "soc.k1x-rproc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <firmware-spacemit.h>
#include <k1x-rproc.h>

#define K1X_MBOX_VQ0_ID                 0
#define K1X_MBOX_VQ1_ID                 1

#define K1X_RPMSG_VRING0_REGION         2
#define K1X_RPMSG_VRING1_REGION         3
#define K1X_RPMSG_BUFFER_REGION         4
#define K1X_RPMSG_RSC_REGION            5

#define K1X_RPMSG_VRING0_NAME           "vdev0vring0"
#define K1X_RPMSG_VRING1_NAME           "vdev0vring1"
#define K1X_RPMSG_BUFFER_NAME           "vdev0buffer"
#define K1X_RPMSG_RSC_NAME              "rsc_table"

#define K1X_RPMSG_QUEUE_NUM             256
#define K1X_RPMSG_BUFFER_SIZE           512
#define K1X_RPMSG_MAX_MEMORY_REGIONS    16
#define K1X_RPMSG_VRING0_NOTIFY_ID      0
#define K1X_RPMSG_VRING1_NOTIFY_ID      1
#define K1X_RPMSG_VIRTIO_VENDOR         0x53504d54U

#define K1X_RSC_VDEV                    3
#define K1X_VIRTIO_ID_RPMSG             7
#define K1X_VIRTIO_RPMSG_F_NS           RT_BIT(0)

#define FW_BOOT_ENTRY_REG_OFFSET        0x88
#define FW_BOOTUP_REG_OFFSET            0x30
#define FW_AON_PER_CLK_RST_CTL_REG      0x2c

#define FW_DDR_REGMAP_BASE_REG_OFFSET   0xc0

static char *const mb_name[] =
{
    [K1X_MBOX_VQ0_ID] = "vq0",
    [K1X_MBOX_VQ1_ID] = "vq1",
};

struct spacemit_rproc;

struct spacemit_rproc_mbox
{
    struct rt_mbox_client parent;

    struct rt_mbox_chan *chan;

    int vq_id;
    struct spacemit_rproc *rproc;
};

struct spacemit_rpmsg_region
{
    void *va;
    rt_uint64_t pa;
    rt_uint64_t size;
    rt_uint32_t da;
};

struct spacemit_fw_rsc_vdev_vring
{
    rt_uint32_t da;
    rt_uint32_t align;
    rt_uint32_t num;
    rt_uint32_t notifyid;
    rt_uint32_t reserved;
};

struct spacemit_fw_rsc_vdev
{
    rt_uint32_t type;
    rt_uint32_t id;
    rt_uint32_t notifyid;
    rt_uint32_t dfeatures;
    rt_uint32_t gfeatures;
    rt_uint32_t config_len;
    rt_uint8_t status;
    rt_uint8_t num_of_vrings;
    rt_uint8_t reserved[2];
    struct spacemit_fw_rsc_vdev_vring vring[2];
};

struct spacemit_resource_table
{
    rt_uint32_t version;
    rt_uint32_t num;
    rt_uint32_t reserved[2];
    rt_uint32_t offset[1];
};

struct spacemit_rproc
{
    struct rt_device *dev;

    void *bootc_mem_base;
    void *sysctrl_mem_base;

    struct rt_clk *core_clk;
    struct rt_clk *apb_clk;
    struct rt_reset_control *core_rstc;

    rt_uint32_t apb_clk_rate;
    rt_uint32_t ddr_remap_base;
    rt_uint32_t fw_entry_point;
    char fw_name[32];
    struct spacemit_rproc_mbox mb[RT_ARRAY_SIZE(mb_name)];

    struct spacemit_rpmsg_region vring_region[2];
    struct spacemit_rpmsg_region buffer_region;
    struct spacemit_rpmsg_region rsc_region;
    struct rt_virtio_device vdev;
    struct rt_virtqueue *vqs[2];
    rt_uint8_t virtio_status;
    rt_uint64_t virtio_features;
    rt_uint32_t vring_notify[2];
    rt_uint32_t vring_align[2];
    rt_uint16_t vring_num[2];
    rt_bool_t virtio_registered;
    struct rt_spinlock dma_lock;
    rt_uint8_t *dma_slots;
    rt_size_t dma_slot_count;
    rt_uint32_t rsc_vdev_offset;
    rt_bool_t rpmsg_ready;
    rt_bool_t firmware_started;
    rt_bool_t boot_requested;
    rt_bool_t clocks_enabled;
    rt_bool_t worker_stop;
    rt_bool_t worker_started;
    rt_bool_t rpmsg_sem_inited;
    rt_bool_t rpmsg_mutex_inited;
    struct rt_semaphore rpmsg_sem;
    struct rt_mutex rpmsg_mutex;
    rt_thread_t rpmsg_thread;
    rt_uint32_t notify_count[RT_ARRAY_SIZE(mb_name)];
    rt_uint32_t mbox_count[RT_ARRAY_SIZE(mb_name)];
};

static struct spacemit_rproc *spacemit_rproc_global;
static RT_DEFINE_SPINLOCK(spacemit_rpmsg_lock);

static rt_err_t spacemit_rproc_boot(struct spacemit_rproc *rproc);
static rt_err_t spacemit_rproc_stop(struct spacemit_rproc *rproc);
static void spacemit_rpmsg_notify(struct spacemit_rproc *rproc, int vq_id);

static struct spacemit_rproc *spacemit_virtio_to_rproc(
        struct rt_virtio_device *vdev)
{
    return rt_container_of(vdev, struct spacemit_rproc, vdev);
}

static struct spacemit_fw_rsc_vdev *spacemit_rproc_rsc_vdev(
        struct spacemit_rproc *rproc)
{
    struct spacemit_resource_table *table;

    if (!rproc || !rproc->rsc_region.va ||
        rproc->rsc_vdev_offset + sizeof(struct spacemit_fw_rsc_vdev) >
                rproc->rsc_region.size)
    {
        return RT_NULL;
    }

    table = rproc->rsc_region.va;

    return (void *)((char *)table + rproc->rsc_vdev_offset);
}

static rt_err_t spacemit_rproc_dma_sync_out_data(struct rt_device *dev,
        void *data, rt_size_t size, rt_ubase_t *dma_handle,
        rt_ubase_t flags)
{
    rt_ubase_t level;
    rt_size_t slot = 0;
    rt_bool_t found = RT_FALSE;
    struct rt_virtio_device *vdev =
            rt_container_of(dev, struct rt_virtio_device, parent);
    struct spacemit_rproc *rproc = spacemit_virtio_to_rproc(vdev);

    if (!data || !dma_handle || !rproc->dma_slots ||
        !rproc->dma_slot_count || size > K1X_RPMSG_BUFFER_SIZE)
    {
        return -RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(&rproc->dma_lock);
    for (slot = 0; slot < rproc->dma_slot_count; ++slot)
    {
        if (!rproc->dma_slots[slot])
        {
            rproc->dma_slots[slot] = 1;
            found = RT_TRUE;
            break;
        }
    }
    rt_spin_unlock_irqrestore(&rproc->dma_lock, level);

    if (!found)
    {
        return -RT_EFULL;
    }

    rt_memset((char *)rproc->buffer_region.va +
            slot * K1X_RPMSG_BUFFER_SIZE, 0, K1X_RPMSG_BUFFER_SIZE);
    rt_memcpy((char *)rproc->buffer_region.va +
            slot * K1X_RPMSG_BUFFER_SIZE, data, size);
    rt_hw_wmb();

    *dma_handle = rproc->buffer_region.da +
            slot * K1X_RPMSG_BUFFER_SIZE;

    return RT_EOK;
}

static rt_err_t spacemit_rproc_dma_sync_in_data(struct rt_device *dev,
        void *out_data, rt_size_t size, rt_ubase_t dma_handle,
        rt_ubase_t flags)
{
    rt_ubase_t level;
    rt_uint64_t offset;
    rt_size_t slot;
    struct rt_virtio_device *vdev =
            rt_container_of(dev, struct rt_virtio_device, parent);
    struct spacemit_rproc *rproc = spacemit_virtio_to_rproc(vdev);

    if (!out_data || !rproc->dma_slots ||
        dma_handle < rproc->buffer_region.da)
    {
        return -RT_EINVAL;
    }

    offset = dma_handle - rproc->buffer_region.da;
    if (offset >= rproc->buffer_region.size ||
        offset % K1X_RPMSG_BUFFER_SIZE)
    {
        return -RT_EINVAL;
    }

    slot = offset / K1X_RPMSG_BUFFER_SIZE;
    if (slot >= rproc->dma_slot_count)
    {
        return -RT_EINVAL;
    }

    rt_hw_rmb();
    rt_memcpy(out_data, (char *)rproc->buffer_region.va + offset,
            rt_min_t(rt_size_t, size, K1X_RPMSG_BUFFER_SIZE));

    level = rt_spin_lock_irqsave(&rproc->dma_lock);
    rproc->dma_slots[slot] = 0;
    rt_spin_unlock_irqrestore(&rproc->dma_lock, level);

    return RT_EOK;
}

static const struct rt_dma_map_ops spacemit_rproc_dma_ops =
{
    .sync_out_data = spacemit_rproc_dma_sync_out_data,
    .sync_in_data = spacemit_rproc_dma_sync_in_data,
};

static rt_err_t spacemit_rproc_virtio_get_status(
        struct rt_virtio_device *vdev, rt_uint8_t *out_status)
{
    struct spacemit_rproc *rproc = spacemit_virtio_to_rproc(vdev);

    *out_status = rproc->virtio_status;

    return RT_EOK;
}

static rt_err_t spacemit_rproc_virtio_set_status(
        struct rt_virtio_device *vdev, rt_uint8_t status)
{
    struct spacemit_fw_rsc_vdev *rsc_vdev;
    struct spacemit_rproc *rproc = spacemit_virtio_to_rproc(vdev);

    rproc->virtio_status = status;
    rsc_vdev = spacemit_rproc_rsc_vdev(rproc);
    if (rsc_vdev)
    {
        rsc_vdev->status = status;
        rt_hw_wmb();
    }

    return RT_EOK;
}

static rt_err_t spacemit_rproc_virtio_get_features(
        struct rt_virtio_device *vdev, rt_uint64_t *out_features)
{
    struct spacemit_rproc *rproc = spacemit_virtio_to_rproc(vdev);

    *out_features = rproc->virtio_features;

    return RT_EOK;
}

static rt_err_t spacemit_rproc_virtio_set_features(
        struct rt_virtio_device *vdev)
{
    struct spacemit_fw_rsc_vdev *rsc_vdev;
    struct spacemit_rproc *rproc = spacemit_virtio_to_rproc(vdev);

    rsc_vdev = spacemit_rproc_rsc_vdev(rproc);
    if (rsc_vdev)
    {
        rsc_vdev->gfeatures = rt_cpu_to_le32(
                (rt_uint32_t)vdev->features);
        rt_hw_wmb();
    }

    return RT_EOK;
}

static rt_err_t spacemit_rproc_virtio_get_config(
        struct rt_virtio_device *vdev, rt_uint32_t offset, void *dst,
        int length)
{
    rt_memset(dst, 0, length);

    return RT_EOK;
}

static rt_err_t spacemit_rproc_virtio_set_config(
        struct rt_virtio_device *vdev, rt_uint32_t offset,
        const void *src, int length)
{
    return RT_EOK;
}

static rt_bool_t spacemit_rproc_virtio_notify(struct rt_virtqueue *vq)
{
    static const char kick[] = "kick";
    rt_ubase_t level;
    struct spacemit_rproc *rproc = spacemit_virtio_to_rproc(vq->vdev);

    if (!rproc->firmware_started)
    {
        level = rt_spin_lock_irqsave(&spacemit_rpmsg_lock);
        rproc->boot_requested = RT_TRUE;
        rt_spin_unlock_irqrestore(&spacemit_rpmsg_lock, level);

        if (rproc->rpmsg_sem_inited)
        {
            rt_sem_release(&rproc->rpmsg_sem);
        }

        LOG_D("RCPU firmware boot requested by RPMsg vq%d", vq->index);

        return RT_TRUE;
    }

    if (rproc->rpmsg_ready && rproc->firmware_started &&
        vq->index < RT_ARRAY_SIZE(rproc->mb))
    {
        ++rproc->notify_count[vq->index];
        rt_mbox_send(rproc->mb[vq->index].chan, kick,
                RT_WAITING_FOREVER);
    }

    return RT_TRUE;
}

static rt_err_t spacemit_rproc_virtio_install_vqs(
        struct rt_virtio_device *vdev, int vqs_nr,
        struct rt_virtqueue *vqs[], const char *names[],
        rt_virtqueue_callback cbs[])
{
    struct spacemit_rproc *rproc = spacemit_virtio_to_rproc(vdev);

    if (vqs_nr != RT_ARRAY_SIZE(rproc->vqs))
    {
        return -RT_EINVAL;
    }

    for (int i = 0; i < vqs_nr; ++i)
    {
        rt_uint32_t align = rproc->vring_align[i] ? :
                ARCH_PAGE_SIZE;
        rt_uint16_t num = rproc->vring_num[i] ? :
                K1X_RPMSG_QUEUE_NUM;
        struct rt_virtqueue_formula formula =
        {
            .page = rproc->vring_region[i].va,
        };

        if (!names[i])
        {
            vqs[i] = RT_NULL;
            continue;
        }

        if (rproc->vring_region[i].size <
            virtq_size(RT_NULL, num, align))
        {
            rt_virtio_virtqueue_release(vdev);
            return -RT_EINVAL;
        }

        vqs[i] = rt_virtqueue_create(vdev, names[i], i, num, align,
                spacemit_rproc_virtio_notify, cbs[i], &formula);
        if (!vqs[i])
        {
            rt_virtio_virtqueue_release(vdev);
            return -RT_ENOMEM;
        }

        rproc->vqs[i] = vqs[i];
    }

    return RT_EOK;
}

static rt_err_t spacemit_rproc_virtio_release_vqs(
        struct rt_virtio_device *vdev)
{
    struct rt_virtqueue *vq, *next;
    struct spacemit_rproc *rproc = spacemit_virtio_to_rproc(vdev);

    rt_list_for_each_entry_safe(vq, next, &vdev->vq_node, list)
    {
        if (vq->index < RT_ARRAY_SIZE(rproc->vqs))
        {
            rproc->vqs[vq->index] = RT_NULL;
        }
        rt_virtqueue_delete(vdev, vq);
    }

    return RT_EOK;
}

static rt_err_t spacemit_rproc_virtio_control_vqs(
        struct rt_virtio_device *vdev, rt_uint32_t cfg, void *data)
{
    return -RT_ENOSYS;
}

static rt_err_t spacemit_rproc_virtio_generation(
        struct rt_virtio_device *vdev, rt_uint32_t *out_counter)
{
    *out_counter = 0;

    return RT_EOK;
}

static rt_err_t spacemit_rproc_virtio_reset(
        struct rt_virtio_device *vdev)
{
    struct spacemit_rproc *rproc = spacemit_virtio_to_rproc(vdev);

    rproc->virtio_status = 0;
    if (rproc->dma_slots)
    {
        rt_memset(rproc->dma_slots, 0,
                rproc->dma_slot_count * sizeof(rproc->dma_slots[0]));
    }
    spacemit_rproc_virtio_set_status(vdev, 0);

    return RT_EOK;
}

static const struct rt_virtio_transport spacemit_rproc_virtio_transport =
{
    .get_status = spacemit_rproc_virtio_get_status,
    .set_status = spacemit_rproc_virtio_set_status,
    .get_features = spacemit_rproc_virtio_get_features,
    .set_features = spacemit_rproc_virtio_set_features,
    .get_config = spacemit_rproc_virtio_get_config,
    .set_config = spacemit_rproc_virtio_set_config,
    .install_vqs = spacemit_rproc_virtio_install_vqs,
    .release_vqs = spacemit_rproc_virtio_release_vqs,
    .control_vqs = spacemit_rproc_virtio_control_vqs,
    .generation = spacemit_rproc_virtio_generation,
    .reset = spacemit_rproc_virtio_reset,
};

static void spacemit_rpmsg_notify(struct spacemit_rproc *rproc, int vq_id)
{
    static const char kick[] = "kick";

    if (rproc->rpmsg_ready && rproc->firmware_started &&
        vq_id < RT_ARRAY_SIZE(rproc->mb))
    {
        ++rproc->notify_count[vq_id];
        rt_mbox_send(rproc->mb[vq_id].chan, kick, RT_WAITING_FOREVER);
    }
}

static rt_err_t spacemit_rpmsg_worker_start(struct spacemit_rproc *rproc)
{
    rt_err_t err;
    rt_ubase_t level;

    if (!rproc || !rproc->rpmsg_thread)
    {
        return -RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(&spacemit_rpmsg_lock);
    if (rproc != spacemit_rproc_global || rproc->worker_started)
    {
        rt_spin_unlock_irqrestore(&spacemit_rpmsg_lock, level);
        return RT_EOK;
    }
    rt_spin_unlock_irqrestore(&spacemit_rpmsg_lock, level);

    err = rt_thread_startup(rproc->rpmsg_thread);
    if (err == RT_EOK)
    {
        level = rt_spin_lock_irqsave(&spacemit_rpmsg_lock);
        if (rproc == spacemit_rproc_global)
        {
            rproc->worker_started = RT_TRUE;
        }
        rt_spin_unlock_irqrestore(&spacemit_rpmsg_lock, level);

        rt_sem_release(&rproc->rpmsg_sem);
        LOG_D("RPMsg worker started");
    }

    return err;
}

static void spacemit_rpmsg_pump(struct spacemit_rproc *rproc)
{
    if (!rproc || !rproc->rpmsg_ready || !rproc->firmware_started ||
        !rproc->rpmsg_mutex_inited)
    {
        return;
    }

    if (rt_mutex_take(&rproc->rpmsg_mutex, RT_WAITING_NO) != RT_EOK)
    {
        return;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(rproc->vqs); ++i)
    {
        if (rproc->vqs[i])
        {
            rt_virtqueue_isr(i, rproc->vqs[i]);
        }
    }

    rt_mutex_release(&rproc->rpmsg_mutex);
}

static void spacemit_rpmsg_worker(void *parameter)
{
    struct spacemit_rproc *rproc = parameter;

    while (!rproc->worker_stop)
    {
        rt_bool_t boot_requested;

        rt_sem_take(&rproc->rpmsg_sem, rt_tick_from_millisecond(10));

        boot_requested = rproc->boot_requested;
        if (boot_requested && !rproc->firmware_started)
        {
            rt_err_t err;
            rt_ubase_t level;

            level = rt_spin_lock_irqsave(&spacemit_rpmsg_lock);
            rproc->boot_requested = RT_FALSE;
            rt_spin_unlock_irqrestore(&spacemit_rpmsg_lock, level);

            err = spacemit_rproc_boot(rproc);
            if (err)
            {
                LOG_E("Boot RCPU firmware failed: %s",
                        rt_strerror(err));
            }
            else
            {
                spacemit_rpmsg_notify(rproc, K1X_MBOX_VQ0_ID);
                spacemit_rpmsg_notify(rproc, K1X_MBOX_VQ1_ID);
            }
        }

        spacemit_rpmsg_pump(rproc);
    }
}

static void spacemit_rpmsg_worker_destroy(struct spacemit_rproc *rproc)
{
    rt_thread_t thread = rproc->rpmsg_thread;

    if (!thread)
    {
        return;
    }

    rproc->worker_stop = RT_TRUE;
    if (rproc->worker_started)
    {
        rt_sem_release(&rproc->rpmsg_sem);
        rt_thread_delete(thread);
    }
    else
    {
        rt_timer_detach(&thread->thread_timer);
#ifdef RT_USING_HW_STACK_GUARD
        RT_KERNEL_FREE(thread->stack_buf);
#else
        RT_KERNEL_FREE(thread->stack_addr);
#endif
        rt_object_delete((rt_object_t)thread);
    }

    rproc->rpmsg_thread = RT_NULL;
    rproc->worker_started = RT_FALSE;
}

static rt_err_t spacemit_rpmsg_map_region_node(struct rt_ofw_node *np,
        const char *label, int index, struct spacemit_rpmsg_region *region)
{
    rt_err_t err;

    if (!np)
    {
        return -RT_EINVAL;
    }

    err = rt_ofw_get_address(np, 0, &region->pa, &region->size);
    if (!err && rt_ofw_prop_read_u32(np, "da_base", &region->da))
    {
        region->da = (rt_uint32_t)region->pa;
    }
    if (err)
    {
        rt_ofw_node_put(np);
        return err;
    }

    region->va = rt_ioremap_nocache((void *)(rt_ubase_t)region->pa,
            region->size);
    if (!region->va)
    {
        rt_ofw_node_put(np);
        return -RT_ENOMEM;
    }

    LOG_D("RPMsg %s region: %s idx=%d pa=%p da=0x%08x size=%p va=%p",
            label, rt_ofw_node_full_name(np), index,
            (void *)(rt_ubase_t)region->pa, region->da,
            (void *)(rt_ubase_t)region->size, region->va);

    rt_ofw_node_put(np);

    return RT_EOK;
}

static rt_err_t spacemit_rpmsg_map_region(struct spacemit_rproc *rproc,
        const char *tag, int fallback_index,
        struct spacemit_rpmsg_region *region)
{
    struct rt_ofw_node *np;

    for (int i = 0; i < K1X_RPMSG_MAX_MEMORY_REGIONS; ++i)
    {
        np = rt_ofw_parse_phandle(rproc->dev->ofw_node,
                "memory-region", i);
        if (!np)
        {
            break;
        }

        if (rt_ofw_node_tag_equ(np, tag))
        {
            return spacemit_rpmsg_map_region_node(np, tag, i, region);
        }

        rt_ofw_node_put(np);
    }

    np = rt_ofw_parse_phandle(rproc->dev->ofw_node,
            "memory-region", fallback_index);
    if (!np)
    {
        return -RT_EINVAL;
    }

    LOG_W("RPMsg %s reserved memory not found by name, fallback to memory-region[%d]",
            tag, fallback_index);

    return spacemit_rpmsg_map_region_node(np, tag, fallback_index, region);
}

static rt_err_t spacemit_rpmsg_load_resource(const char *fw_name,
        struct spacemit_rpmsg_region *region)
{
    rt_ubase_t base;
    rt_size_t size;
    Elf32_Ehdr *ehdr;
    Elf32_Phdr *phdr;

    if (!spacemit_firmware_find(fw_name, &base, &size))
    {
        return -RT_EEMPTY;
    }

    ehdr = (Elf32_Ehdr *)base;
    if (size < sizeof(*ehdr) ||
        rt_memcmp(ehdr->e_ident, ELFMAG, SELFMAG) ||
        ehdr->e_ident[EI_CLASS] != ELFCLASS32 ||
        ehdr->e_phoff + ehdr->e_phnum * sizeof(*phdr) > size)
    {
        return -RT_EINVAL;
    }

    phdr = (Elf32_Phdr *)(base + ehdr->e_phoff);
    for (int i = 0; i < ehdr->e_phnum; ++i)
    {
        rt_ubase_t offset;
        rt_size_t copy;

        if (phdr[i].p_type != PT_LOAD || region->da < phdr[i].p_paddr ||
            region->da >= phdr[i].p_paddr + phdr[i].p_memsz)
        {
            continue;
        }

        offset = region->da - phdr[i].p_paddr;
        if (offset >= phdr[i].p_filesz ||
            phdr[i].p_offset + phdr[i].p_filesz > size)
        {
            return -RT_EINVAL;
        }

        copy = rt_min_t(rt_size_t, phdr[i].p_filesz - offset,
                region->size);
        rt_memset(region->va, 0, region->size);
        rt_memcpy(region->va, (void *)(base + phdr[i].p_offset + offset),
                copy);
        return RT_EOK;
    }

    return -RT_EEMPTY;
}

static rt_err_t spacemit_rproc_da_to_pa(struct spacemit_rproc *rproc,
        rt_uint32_t da, rt_uint64_t *out_pa)
{
    struct rt_ofw_node *np;

    for (int i = 0; i < K1X_RPMSG_MAX_MEMORY_REGIONS; ++i)
    {
        rt_uint32_t da_base;
        rt_uint64_t pa, size, offset;

        np = rt_ofw_parse_phandle(rproc->dev->ofw_node,
                "memory-region", i);
        if (!np)
        {
            break;
        }

        if (rt_ofw_get_address(np, 0, &pa, &size))
        {
            rt_ofw_node_put(np);
            continue;
        }

        if (rt_ofw_prop_read_u32(np, "da_base", &da_base))
        {
            da_base = (rt_uint32_t)pa;
        }

        if (da >= da_base)
        {
            offset = da - da_base;
            if (offset < size)
            {
                *out_pa = pa + offset;
                LOG_D("RCPU DA 0x%08x -> PA %p by %s idx=%d",
                        da, (void *)(rt_ubase_t)*out_pa,
                        rt_ofw_node_full_name(np), i);
                rt_ofw_node_put(np);

                return RT_EOK;
            }
        }

        rt_ofw_node_put(np);
    }

    return -RT_EINVAL;
}

static rt_err_t spacemit_rproc_clear_carveouts(struct spacemit_rproc *rproc)
{
    struct rt_ofw_node *np;

    for (int i = 0; i < K1X_RPMSG_MAX_MEMORY_REGIONS; ++i)
    {
        void *va;
        rt_uint64_t pa, size;

        np = rt_ofw_parse_phandle(rproc->dev->ofw_node,
                "memory-region", i);
        if (!np)
        {
            break;
        }

        if (rt_ofw_get_address(np, 0, &pa, &size))
        {
            rt_ofw_node_put(np);
            continue;
        }

        va = rt_ioremap_nocache((void *)(rt_ubase_t)pa, size);
        if (!va)
        {
            LOG_E("Map RCPU carveout %s failed",
                    rt_ofw_node_full_name(np));
            rt_ofw_node_put(np);
            return -RT_ENOMEM;
        }

        LOG_D("Clear RCPU carveout %s pa=%p size=%p",
                rt_ofw_node_full_name(np), (void *)(rt_ubase_t)pa,
                (void *)(rt_ubase_t)size);
        rt_memset(va, 0, size);
        rt_hw_wmb();
        rt_iounmap(va);
        rt_ofw_node_put(np);
    }

    return RT_EOK;
}

static rt_err_t spacemit_rpmsg_reset_transport(struct spacemit_rproc *rproc,
        const char *fw_name)
{
    rt_err_t err;
    struct spacemit_resource_table *table;
    struct spacemit_fw_rsc_vdev *vdev;

    if (rproc->vring_region[0].size <
            virtq_size(RT_NULL, K1X_RPMSG_QUEUE_NUM, ARCH_PAGE_SIZE) ||
        rproc->vring_region[1].size <
            virtq_size(RT_NULL, K1X_RPMSG_QUEUE_NUM, ARCH_PAGE_SIZE) ||
        rproc->buffer_region.size <
            K1X_RPMSG_QUEUE_NUM * K1X_RPMSG_BUFFER_SIZE * 2)
    {
        return -RT_EINVAL;
    }

    if ((err = spacemit_rpmsg_load_resource(fw_name,
            &rproc->rsc_region)))
    {
        return err;
    }

    table = rproc->rsc_region.va;
    if (rt_le32_to_cpu(table->num) != 1 ||
        rt_le32_to_cpu(table->offset[0]) + sizeof(*vdev) >
                rproc->rsc_region.size)
    {
        return -RT_EINVAL;
    }
    rproc->rsc_vdev_offset = rt_le32_to_cpu(table->offset[0]);
    vdev = (void *)((char *)table + rproc->rsc_vdev_offset);
    if (rt_le32_to_cpu(vdev->type) != K1X_RSC_VDEV ||
        rt_le32_to_cpu(vdev->id) != K1X_VIRTIO_ID_RPMSG ||
            vdev->num_of_vrings != 2)
    {
        return -RT_EINVAL;
    }

    rt_memset(rproc->vring_region[0].va, 0,
            rproc->vring_region[0].size);
    rt_memset(rproc->vring_region[1].va, 0,
            rproc->vring_region[1].size);
    rt_memset(rproc->buffer_region.va, 0, rproc->buffer_region.size);

    for (int i = 0; i < RT_ARRAY_SIZE(rproc->vring_region); ++i)
    {
        rproc->vring_num[i] = rt_le32_to_cpu(vdev->vring[i].num) ? :
                K1X_RPMSG_QUEUE_NUM;
        rproc->vring_align[i] = rt_le32_to_cpu(vdev->vring[i].align) ? :
                ARCH_PAGE_SIZE;
        rproc->vring_notify[i] = rt_le32_to_cpu(vdev->vring[i].notifyid);
    }
    rproc->vring_notify[0] = K1X_RPMSG_VRING0_NOTIFY_ID;
    rproc->vring_notify[1] = K1X_RPMSG_VRING1_NOTIFY_ID;

    vdev->vring[0].da = rt_cpu_to_le32(rproc->vring_region[0].da);
    vdev->vring[1].da = rt_cpu_to_le32(rproc->vring_region[1].da);
    vdev->vring[0].align = rt_cpu_to_le32(rproc->vring_align[0]);
    vdev->vring[1].align = rt_cpu_to_le32(rproc->vring_align[1]);
    vdev->vring[0].num = rt_cpu_to_le32(rproc->vring_num[0]);
    vdev->vring[1].num = rt_cpu_to_le32(rproc->vring_num[1]);
    vdev->vring[0].notifyid = rt_cpu_to_le32(rproc->vring_notify[0]);
    vdev->vring[1].notifyid = rt_cpu_to_le32(rproc->vring_notify[1]);
    rproc->virtio_features = rt_le32_to_cpu(vdev->dfeatures) |
            K1X_VIRTIO_RPMSG_F_NS;
    vdev->dfeatures = rt_cpu_to_le32(
            (rt_uint32_t)rproc->virtio_features);
    vdev->gfeatures = 0;
    vdev->status = 0;
    rt_hw_wmb();

    LOG_D("RPMsg resource ready: status=0x%02x notify=%u/%u vring0=0x%08x vring1=0x%08x buffer=0x%08x",
            vdev->status, rproc->vring_notify[0],
            rproc->vring_notify[1],
            rproc->vring_region[0].da,
            rproc->vring_region[1].da, rproc->buffer_region.da);

    return RT_EOK;
}

static rt_err_t spacemit_rpmsg_prepare(struct spacemit_rproc *rproc,
        const char *fw_name)
{
    rt_err_t err;

    if ((err = spacemit_rpmsg_map_region(rproc, K1X_RPMSG_VRING0_NAME,
            K1X_RPMSG_VRING0_REGION,
            &rproc->vring_region[0])) ||
        (err = spacemit_rpmsg_map_region(rproc, K1X_RPMSG_VRING1_NAME,
            K1X_RPMSG_VRING1_REGION,
            &rproc->vring_region[1])) ||
        (err = spacemit_rpmsg_map_region(rproc, K1X_RPMSG_BUFFER_NAME,
            K1X_RPMSG_BUFFER_REGION,
            &rproc->buffer_region)) ||
        (err = spacemit_rpmsg_map_region(rproc, K1X_RPMSG_RSC_NAME,
            K1X_RPMSG_RSC_REGION,
            &rproc->rsc_region)))
    {
        return err;
    }

    rproc->dma_slot_count = rproc->buffer_region.size /
            K1X_RPMSG_BUFFER_SIZE;
    if (!rproc->dma_slot_count)
    {
        return -RT_EINVAL;
    }

    rproc->dma_slots = rt_calloc(rproc->dma_slot_count,
            sizeof(rproc->dma_slots[0]));
    if (!rproc->dma_slots)
    {
        return -RT_ENOMEM;
    }
    rt_spin_lock_init(&rproc->dma_lock);

    return spacemit_rpmsg_reset_transport(rproc, fw_name);
}

static rt_err_t spacemit_rproc_prepare(struct spacemit_rproc *rproc)
{
    rt_err_t err;

    /* Keep the RCPU held until a client explicitly needs RPMsg. */
    HWREG32(rproc->bootc_mem_base + FW_BOOTUP_REG_OFFSET) = 0;
    rt_hw_wmb();

    /* De-assert the clk */
    rt_reset_control_assert(rproc->core_rstc);
    rt_reset_control_deassert(rproc->core_rstc);
    HWREG32(rproc->bootc_mem_base + FW_BOOTUP_REG_OFFSET) = 0;
    rt_hw_wmb();

    /* Enable clocks explicitly (RT-Thread may keep them gated by default) */
    if ((err = rt_clk_prepare_enable(rproc->core_clk)))
    {
        return err;
    }

    if ((err = rt_clk_prepare_enable(rproc->apb_clk)))
    {
        rt_clk_disable_unprepare(rproc->core_clk);
        return err;
    }
    rproc->clocks_enabled = RT_TRUE;

    /* Set apb clk rate */
    if ((err = rt_clk_set_rate(rproc->apb_clk, rproc->apb_clk_rate)))
    {
        rt_clk_disable_unprepare(rproc->apb_clk);
        rt_clk_disable_unprepare(rproc->core_clk);
        rproc->clocks_enabled = RT_FALSE;
        return err;
    }

    return RT_EOK;
}

static rt_err_t spacemit_rproc_start(struct spacemit_rproc *rproc)
{
    /* Enable ipc2ap clk & reset--> rcpu side */
    HWREG32(rproc->bootc_mem_base + FW_AON_PER_CLK_RST_CTL_REG) = 0xff;

    /* Set the boot-entry */
    HWREG32(rproc->sysctrl_mem_base + FW_BOOT_ENTRY_REG_OFFSET) = rproc->fw_entry_point;

    /* Set ddr map */
    HWREG32(rproc->sysctrl_mem_base + FW_DDR_REGMAP_BASE_REG_OFFSET) = rproc->ddr_remap_base;

    rt_hw_wmb();

    /* Lanching up firmware */
    HWREG32(rproc->bootc_mem_base + FW_BOOTUP_REG_OFFSET) = 1;
    rt_hw_wmb();

    return RT_EOK;
}

static rt_err_t spacemit_rproc_boot(struct spacemit_rproc *rproc)
{
    rt_err_t err;
    rt_ubase_t level;
    rt_bool_t started;

    if (!rproc || !rproc->rpmsg_ready || !rproc->rpmsg_mutex_inited)
    {
        return -RT_EINVAL;
    }

    err = rt_mutex_take(&rproc->rpmsg_mutex, RT_WAITING_FOREVER);
    if (err)
    {
        return err;
    }

    level = rt_spin_lock_irqsave(&spacemit_rpmsg_lock);
    if (rproc != spacemit_rproc_global)
    {
        rt_spin_unlock_irqrestore(&spacemit_rpmsg_lock, level);
        rt_mutex_release(&rproc->rpmsg_mutex);
        return -RT_EINVAL;
    }
    started = rproc->firmware_started;
    rt_spin_unlock_irqrestore(&spacemit_rpmsg_lock, level);

    if (!started)
    {
        if (rproc->clocks_enabled == RT_FALSE)
        {
            err = spacemit_rproc_prepare(rproc);
            if (err)
            {
                rt_mutex_release(&rproc->rpmsg_mutex);
                return err;
            }
        }

        err = spacemit_rproc_start(rproc);
        if (!err)
        {
            rt_hw_wmb();
            level = rt_spin_lock_irqsave(&spacemit_rpmsg_lock);
            if (rproc == spacemit_rproc_global)
            {
                rproc->firmware_started = RT_TRUE;
                rproc->boot_requested = RT_FALSE;
            }
            else
            {
                err = -RT_EINVAL;
            }
            rt_spin_unlock_irqrestore(&spacemit_rpmsg_lock, level);
        }
    }

    rt_mutex_release(&rproc->rpmsg_mutex);
    if (err)
    {
        return err;
    }

    err = spacemit_rpmsg_worker_start(rproc);
    if (err)
    {
        return err;
    }

    spacemit_rpmsg_notify(rproc, K1X_MBOX_VQ0_ID);
    spacemit_rpmsg_notify(rproc, K1X_MBOX_VQ1_ID);
    LOG_D("RCPU firmware booted on demand, entry=0x%08x remap=0x%08x",
            rproc->fw_entry_point, rproc->ddr_remap_base);

    return RT_EOK;
}

rt_err_t spacemit_k1x_rproc_boot(const char *fw_name)
{
    rt_err_t err;
    rt_ubase_t level;
    struct spacemit_rproc *rproc;

    level = rt_spin_lock_irqsave(&spacemit_rpmsg_lock);
    rproc = spacemit_rproc_global;
    rt_spin_unlock_irqrestore(&spacemit_rpmsg_lock, level);

    if (!rproc)
    {
        return -RT_ENOENT;
    }

    if (fw_name && fw_name[0] && rt_strcmp(fw_name, rproc->fw_name))
    {
        return -RT_ENOENT;
    }

    err = spacemit_rproc_boot(rproc);
    if (err)
    {
        LOG_E("Boot RCPU firmware %s failed: %s",
                rproc->fw_name, rt_strerror(err));
        return err;
    }

    return RT_EOK;
}

void spacemit_k1x_rproc_dump_status(void)
{
    rt_ubase_t level;
    struct spacemit_fw_rsc_vdev *rsc_vdev;
    struct spacemit_rproc *rproc;

    level = rt_spin_lock_irqsave(&spacemit_rpmsg_lock);
    rproc = spacemit_rproc_global;
    rt_spin_unlock_irqrestore(&spacemit_rpmsg_lock, level);
    if (!rproc)
    {
        LOG_W("RCPU state unavailable");
        return;
    }

    LOG_W("RCPU state: started=%u worker=%u boot=%08x entry=%08x remap=%08x aon=%08x",
            rproc->firmware_started, rproc->worker_started,
            HWREG32((char *)rproc->bootc_mem_base + FW_BOOTUP_REG_OFFSET),
            HWREG32((char *)rproc->sysctrl_mem_base +
                    FW_BOOT_ENTRY_REG_OFFSET),
            HWREG32((char *)rproc->sysctrl_mem_base +
                    FW_DDR_REGMAP_BASE_REG_OFFSET),
            HWREG32((char *)rproc->bootc_mem_base +
                    FW_AON_PER_CLK_RST_CTL_REG));

    rsc_vdev = spacemit_rproc_rsc_vdev(rproc);
    if (rsc_vdev)
    {
        rt_hw_rmb();
        LOG_W("RPMsg resource: status=%02x dfeatures=%08x gfeatures=%08x",
                rsc_vdev->status,
                rt_le32_to_cpu(rsc_vdev->dfeatures),
                rt_le32_to_cpu(rsc_vdev->gfeatures));
    }

    for (int i = 0; i < RT_ARRAY_SIZE(rproc->vqs); ++i)
    {
        struct virtq ring;
        struct rt_virtqueue *vq = rproc->vqs[i];

        if (!vq || !rproc->vring_region[i].va)
        {
            continue;
        }

        virtq_init(&ring, rproc->vring_num[i],
                rproc->vring_region[i].va,
                rproc->vring_align[i]);
        rt_hw_rmb();
        LOG_W("RPMsg vq%d: avail=%u used=%u last=%u notify=%u mailbox=%u",
                i, rt_le16_to_cpu(ring.avail->idx),
                rt_le16_to_cpu(ring.used->idx), vq->last_used_idx,
                rproc->notify_count[i], rproc->mbox_count[i]);
    }
}

static rt_err_t spacemit_rproc_stop(struct spacemit_rproc *rproc)
{
    rt_ubase_t level;

    /* Hold the rcpu */
    HWREG32(rproc->bootc_mem_base + FW_BOOTUP_REG_OFFSET) = 0;
    rt_hw_wmb();

    level = rt_spin_lock_irqsave(&spacemit_rpmsg_lock);
    rproc->firmware_started = RT_FALSE;
    rt_spin_unlock_irqrestore(&spacemit_rpmsg_lock, level);

    rt_reset_control_assert(rproc->core_rstc);

    if (rproc->clocks_enabled)
    {
        /* Gate clocks after reset asserted */
        rt_clk_disable_unprepare(rproc->apb_clk);
        rt_clk_disable_unprepare(rproc->core_clk);
        rproc->clocks_enabled = RT_FALSE;
    }

    return RT_EOK;
}

static void spacemit_rproc_mbox_rx_callback(struct rt_mbox_client *client, void *data)
{
    struct spacemit_rproc_mbox *mb = rt_container_of(client, struct spacemit_rproc_mbox, parent);
    struct spacemit_rproc *rproc = mb->rproc;

    if (mb->vq_id < RT_ARRAY_SIZE(rproc->mbox_count))
    {
        ++rproc->mbox_count[mb->vq_id];
    }

    if (rproc->rpmsg_sem_inited)
    {
        rt_sem_release(&rproc->rpmsg_sem);
    }
}

static rt_err_t spacemit_rproc_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint64_t fw_entry_pa;
    const char *fw_name, *name;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_rproc *rproc = rt_calloc(1, sizeof(*rproc));

    if (!rproc)
    {
        return -RT_ENOMEM;
    }
    rproc->dev = dev;

    rproc->bootc_mem_base = rt_dm_dev_iomap(dev, 0);
    if (!rproc->bootc_mem_base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rproc->sysctrl_mem_base = rt_dm_dev_iomap(dev, 1);
    if (!rproc->sysctrl_mem_base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rproc->core_rstc = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(rproc->core_rstc))
    {
        err = rt_ptr_err(rproc->core_rstc);
        goto _fail;
    }

    rproc->core_clk = rt_clk_get_by_name(dev, "core");
    if (rt_is_err(rproc->core_clk))
    {
        err = rt_ptr_err(rproc->core_clk);
        goto _fail;
    }

    rproc->apb_clk = rt_clk_get_by_name(dev, "apb");
    if (rt_is_err(rproc->apb_clk))
    {
        err = rt_ptr_err(rproc->apb_clk);
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "apb-clk-rate", &rproc->apb_clk_rate)))
    {
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "ddr-remap-base", &rproc->ddr_remap_base)))
    {
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_string(dev, "firmware-name", &fw_name)))
    {
        goto _fail;
    }
    rt_strncpy(rproc->fw_name, fw_name, sizeof(rproc->fw_name) - 1);

    if (!(name = rt_dm_dev_get_prop_fuzzy_name(dev, "-entry-point$")))
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, name, &rproc->fw_entry_point)))
    {
        goto _fail;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(rproc->mb); ++i)
    {
        struct spacemit_rproc_mbox *mb = &rproc->mb[i];

        mb->vq_id = i;
        mb->rproc = rproc;

        mb->parent.dev = dev;
        mb->parent.rx_callback = spacemit_rproc_mbox_rx_callback;

        mb->chan = rt_mbox_request_by_name(&mb->parent, mb_name[i]);

        if (rt_is_err_or_null(mb->chan))
        {
            err = -RT_EINVAL;
            LOG_E("Request mailbox fail");
            goto _fail;
        }
    }

    if ((err = spacemit_rproc_prepare(rproc)))
    {
        LOG_E("Prepare RCPU hardware failed: %s", rt_strerror(err));
        goto _fail;
    }

    if ((err = spacemit_rproc_clear_carveouts(rproc)))
    {
        goto _fail;
    }

    if ((err = spacemit_rproc_da_to_pa(rproc, rproc->fw_entry_point,
            &fw_entry_pa)))
    {
        LOG_E("Translate RCPU firmware entry 0x%08x failed: %s",
                rproc->fw_entry_point, rt_strerror(err));
        goto _fail;
    }
    if ((err = spacemit_firmware_load_elf(fw_name, fw_entry_pa)))
    {
        LOG_E("Run firmware %s fail", fw_name);
        goto _fail;
    }

    if ((err = spacemit_rpmsg_prepare(rproc, fw_name)))
    {
        LOG_E("Prepare RPMsg transport failed: %s", rt_strerror(err));
        goto _fail;
    }

    if ((err = rt_sem_init(&rproc->rpmsg_sem, "k1-rpmsg", 0,
            RT_IPC_FLAG_FIFO)))
    {
        goto _fail;
    }
    rproc->rpmsg_sem_inited = RT_TRUE;
    if ((err = rt_mutex_init(&rproc->rpmsg_mutex, "k1-rpmsg",
            RT_IPC_FLAG_FIFO)))
    {
        goto _fail;
    }
    rproc->rpmsg_mutex_inited = RT_TRUE;
    rproc->rpmsg_thread = rt_thread_create("k1-rpmsg", spacemit_rpmsg_worker,
            rproc, 4096, RT_THREAD_PRIORITY_MAX / 2, 10);
    if (!rproc->rpmsg_thread)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    rproc->rpmsg_ready = RT_TRUE;
    rt_spin_lock(&spacemit_rpmsg_lock);
    spacemit_rproc_global = rproc;
    rt_spin_unlock(&spacemit_rpmsg_lock);

    rproc->vdev.parent.ofw_node = dev->ofw_node;
    rproc->vdev.id.device = VIRTIO_DEVICE_ID_RPMSG;
    rproc->vdev.id.vendor = K1X_RPMSG_VIRTIO_VENDOR;
    rproc->vdev.trans = &spacemit_rproc_virtio_transport;
    rproc->vdev.dma_dispatch = RT_TRUE;
    rt_dma_device_set_ops(&rproc->vdev.parent, &spacemit_rproc_dma_ops);
    if ((err = rt_virtio_device_register(&rproc->vdev)))
    {
        LOG_E("Register RCPU virtio-rpmsg failed: %s",
                rt_strerror(err));
        goto _fail;
    }
    rproc->virtio_registered = RT_TRUE;

    LOG_D("RCPU firmware %s loaded, entry=0x%08x remap=0x%08x, boot deferred",
            fw_name, rproc->fw_entry_point, rproc->ddr_remap_base);

    dev->user_data = rproc;

    return RT_EOK;

_fail:
    rproc->rpmsg_ready = RT_FALSE;
    rt_spin_lock(&spacemit_rpmsg_lock);
    if (spacemit_rproc_global == rproc)
    {
        spacemit_rproc_global = RT_NULL;
    }
    rt_spin_unlock(&spacemit_rpmsg_lock);
    if (rproc->firmware_started)
    {
        spacemit_rproc_stop(rproc);
    }
    else if (rproc->clocks_enabled)
    {
        spacemit_rproc_stop(rproc);
    }
    if (rproc->virtio_registered)
    {
        rt_bus_remove_device(&rproc->vdev.parent);
        rproc->virtio_registered = RT_FALSE;
    }
    if (rproc->rpmsg_thread)
    {
        spacemit_rpmsg_worker_destroy(rproc);
    }
    if (rproc->rpmsg_sem_inited)
    {
        rt_sem_detach(&rproc->rpmsg_sem);
    }
    if (rproc->rpmsg_mutex_inited)
    {
        rt_mutex_detach(&rproc->rpmsg_mutex);
    }
    for (int i = 0; i < RT_ARRAY_SIZE(rproc->vring_region); ++i)
    {
        if (rproc->vring_region[i].va)
        {
            rt_iounmap(rproc->vring_region[i].va);
        }
    }
    if (rproc->buffer_region.va)
    {
        rt_iounmap(rproc->buffer_region.va);
    }
    if (rproc->rsc_region.va)
    {
        rt_iounmap(rproc->rsc_region.va);
    }
    if (rproc->dma_slots)
    {
        rt_free(rproc->dma_slots);
    }
    if (rproc->bootc_mem_base)
    {
        rt_iounmap(rproc->bootc_mem_base);
    }
    if (rproc->sysctrl_mem_base)
    {
        rt_iounmap(rproc->sysctrl_mem_base);
    }

    if (!rt_is_err_or_null(rproc->core_rstc))
    {
        rt_reset_control_put(rproc->core_rstc);
    }
    if (!rt_is_err_or_null(rproc->core_clk))
    {
        rt_clk_put(rproc->core_clk);
    }
    if (!rt_is_err_or_null(rproc->apb_clk))
    {
        rt_clk_put(rproc->apb_clk);
    }

    for (int i = 0; i < RT_ARRAY_SIZE(rproc->mb); ++i)
    {
        struct spacemit_rproc_mbox *mb = &rproc->mb[i];

        if (!rt_is_err_or_null(mb->chan))
        {
            rt_mbox_release(mb->chan);
        }
    }

    rt_free(rproc);

    return err;
}

static rt_err_t spacemit_rproc_shutdown(struct rt_platform_device *pdev)
{
    struct spacemit_rproc *rproc = pdev->parent.user_data;

    rproc->rpmsg_ready = RT_FALSE;
    spacemit_rpmsg_worker_destroy(rproc);
    if (rproc->rpmsg_mutex_inited)
    {
        rt_mutex_detach(&rproc->rpmsg_mutex);
        rproc->rpmsg_mutex_inited = RT_FALSE;
    }
    if (rproc->rpmsg_sem_inited)
    {
        rt_sem_detach(&rproc->rpmsg_sem);
        rproc->rpmsg_sem_inited = RT_FALSE;
    }
    rt_spin_lock(&spacemit_rpmsg_lock);
    if (spacemit_rproc_global == rproc)
    {
        spacemit_rproc_global = RT_NULL;
    }
    rt_spin_unlock(&spacemit_rpmsg_lock);
    if (rproc->virtio_registered)
    {
        rt_bus_remove_device(&rproc->vdev.parent);
        rproc->virtio_registered = RT_FALSE;
    }
    spacemit_rproc_stop(rproc);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_rproc_ofw_ids[] =
{
    { .compatible = "spacemit,k1-x-rproc" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_rproc_driver =
{
    .name = "spacemit-rproc",
    .ids = spacemit_rproc_ofw_ids,

    .probe = spacemit_rproc_probe,
    .shutdown = spacemit_rproc_shutdown,
};

static int spacemit_rproc_drv_register(void)
{
    rt_platform_driver_register(&spacemit_rproc_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(spacemit_rproc_drv_register);
