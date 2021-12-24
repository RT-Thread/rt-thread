/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-9-16      GuEe-GUI     the first version
 */

#include <rtconfig.h>
#include <rtthread.h>
#include <rthw.h>
#include <cpuport.h>
#include <board.h>

#include "virtio.h"
#include "virtio_mmio.h"
#include "drv_virtio_blk.h"

#ifdef BSP_USING_VIRTIO_BLK

#ifdef RT_USING_VIRTIO_BLK0
static struct virtio_blk blk0;
static struct virtio_blk_device virtio_blk_dev0;
#endif /* RT_USING_VIRTIO_BLK0 */

static int alloc_desc(struct virtio_blk *blk)
{
    int i;
    for(i = 0; i < QUEUE_SIZE; i++)
    {
        if (blk->free[i])
        {
            blk->free[i] = 0;
            return i;
        }
    }
    return -RT_ERROR;
}

static void free_desc(struct virtio_blk *blk, int i)
{
    if (i >= QUEUE_SIZE)
    {
        rt_kprintf("Out of queue number");
        RT_ASSERT(0);
    }
    if (blk0.free[i])
    {
        rt_kprintf("Already freed");
        RT_ASSERT(0);
    }
    blk->desc[i].addr = 0;
    blk->desc[i].len = 0;
    blk->desc[i].flags = 0;
    blk->desc[i].next = 0;
    blk->free[i] = 1;
}

static void free_chain(struct virtio_blk *blk, int i)
{
    int flag, nxt;
    for (;;)
    {
        flag = blk->desc[i].flags;
        nxt = blk->desc[i].next;

        free_desc(blk, i);

        if (flag & VRING_DESC_F_NEXT)
        {
            i = nxt;
        }
        else
        {
            break;
        }
    }
}

static int alloc3_desc(struct virtio_blk *blk, int *idx)
{
    for (int i = 0; i < 3; ++i)
    {
        idx[i] = alloc_desc(blk);
        if (idx[i] < 0)
        {
            for (int j = 0; j < i; ++j)
            {
                free_desc(blk, idx[j]);
            }
            return -RT_ERROR;
        }
    }
    return 0;
}

static int virtio_blk_device_init(struct virtio_blk_device *virtio_blk_dev)
{
    uint32_t status = 0;
    uint32_t max;
    uint64_t features;
    int i;

#ifdef RT_USING_SMP
    rt_spin_lock_init(&virtio_blk_dev->spinlock);
#endif

    if (virtio_mmio_read32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_MAGIC_VALUE) != VIRTIO_MMIO_MAGIC ||
        virtio_mmio_read32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_VERSION) != 1 ||
        virtio_mmio_read32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_DEVICE_ID) != 2 ||
        virtio_mmio_read32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_VENDOR_ID) != VIRTIO_MMIO_VENDOR)
    {
        rt_kprintf("Could not find virtio disk");

        return -RT_ERROR;
    }

    status |= VIRTIO_STAT_ACKNOWLEDGE;
    virtio_mmio_write32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_STATUS, status);

    status |= VIRTIO_STAT_DRIVER;
    virtio_mmio_write32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_STATUS, status);

    /* negotiate features */
    features = virtio_mmio_read32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_DEVICE_FEATURES);
    features &= ~(1 << VIRTIO_BLK_F_RO);
    features &= ~(1 << VIRTIO_BLK_F_SCSI);
    features &= ~(1 << VIRTIO_BLK_F_CONFIG_WCE);
    features &= ~(1 << VIRTIO_BLK_F_MQ);
    features &= ~(1 << VIRTIO_F_ANY_LAYOUT);
    features &= ~(1 << VIRTIO_RING_F_EVENT_IDX);
    features &= ~(1 << VIRTIO_RING_F_INDIRECT_DESC);
    virtio_mmio_write32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_DRIVER_FEATURES, features);

    /* tell device that feature negotiation is complete */
    status |= VIRTIO_STAT_FEATURES_OK;
    virtio_mmio_write32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_STATUS, status);

    /* tell device we're completely ready */
    status |= VIRTIO_STAT_DRIVER_OK;
    virtio_mmio_write32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_STATUS, status);

    virtio_mmio_write32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_GUEST_PAGE_SIZE, PAGE_SIZE);

    /* initialize queue 0 */
    virtio_mmio_write32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_QUEUE_SEL, 0);

    max = virtio_mmio_read32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_QUEUE_NUM_MAX);
    if (max == 0)
    {
        rt_kprintf("Virtio disk has no queue 0");
        RT_ASSERT(0);
    }
    if (max < QUEUE_SIZE)
    {
        rt_kprintf("Virtio disk max queue too short");
        RT_ASSERT(0);
    }
    virtio_mmio_write32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_QUEUE_NUM, QUEUE_SIZE);

    rt_memset(virtio_blk_dev->blk->pages, 0, sizeof(virtio_blk_dev->blk->pages));
    virtio_mmio_write32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_QUEUE_PFN, ((uint64_t)blk0.pages) >> PAGE_SHIFT);

    virtio_blk_dev->blk->desc = (struct virtq_desc *)virtio_blk_dev->blk->pages;
    virtio_blk_dev->blk->avail = (struct virtq_avail *)(virtio_blk_dev->blk->pages + QUEUE_SIZE * sizeof(struct virtq_desc));
    virtio_blk_dev->blk->used = (struct virtq_used *)(virtio_blk_dev->blk->pages + PAGE_SIZE);

    /* all QUEUE_SIZE descriptors start out unused */
    for (i = 0; i < QUEUE_SIZE; ++i)
    {
        virtio_blk_dev->blk->free[i] = 1;
    }

    return RT_EOK;
}

static void virtio_blk_rw(struct virtio_blk_device *virtio_blk_dev, struct virtio_blk_buf *buf, int flag)
{
    struct virtio_blk *blk = virtio_blk_dev->blk;
    uint64_t sector = buf->block_no * (VIRTIO_BLK_BUF_DATA_SIZE / 512);
    int idx[3];
    struct virtio_blk_req *req;

#ifdef RT_USING_SMP
    rt_base_t level;

    level = rt_spin_lock_irqsave(&virtio_blk_dev->spinlock);
#endif

    /* allocate the three descriptors */
    for (;;)
    {
        if (alloc3_desc(blk, idx) == 0)
        {
            break;
        }
    }

    req = &(blk->ops[idx[0]]);
    req->type = flag;
    req->reserved = 0;
    req->sector = sector;

    blk->desc[idx[0]].addr = (uint64_t)req;
    blk->desc[idx[0]].len = sizeof(struct virtio_blk_req);
    blk->desc[idx[0]].flags = VRING_DESC_F_NEXT;
    blk->desc[idx[0]].next = idx[1];

    blk->desc[idx[1]].addr = (uint64_t)buf->data;
    blk->desc[idx[1]].len = VIRTIO_BLK_BUF_DATA_SIZE;

    blk->desc[idx[1]].flags = flag ? 0 : VRING_DESC_F_WRITE;

    blk->desc[idx[1]].flags |= VRING_DESC_F_NEXT;
    blk->desc[idx[1]].next = idx[2];

    /* device writes 0 on success */
    blk->info[idx[0]].status = 0xff;
    blk->desc[idx[2]].addr = (uint64_t)&(blk->info[idx[0]].status);
    blk->desc[idx[2]].len = 1;
    /* device writes the status */
    blk->desc[idx[2]].flags = VRING_DESC_F_WRITE;
    blk->desc[idx[2]].next = 0;

    /* record struct buf for virtio_blk_isr() */
    buf->valid = 1;
    blk->info[idx[0]].buf = buf;

    /* tell the device the first index in our chain of descriptors */
    blk->avail->ring[blk->avail->idx % QUEUE_SIZE] = idx[0];

    rt_hw_dsb();

    /* tell the device another avail ring entry is available */
    blk->avail->idx += 1;

    rt_hw_dsb();

    /* value is queue number */
    virtio_mmio_write32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_QUEUE_NOTIFY, 0);

    /* wait for virtio_blk_isr() to done */
    while (buf->valid == 1)
    {
#ifdef RT_USING_SMP
        rt_spin_unlock_irqrestore(&virtio_blk_dev->spinlock, level);
#endif
        rt_thread_yield();
#ifdef RT_USING_SMP
        level = rt_spin_lock_irqsave(&virtio_blk_dev->spinlock);
#endif
    }

    blk->info[idx[0]].buf = 0;
    free_chain(blk, idx[0]);

#ifdef RT_USING_SMP
    rt_spin_unlock_irqrestore(&virtio_blk_dev->spinlock, level);
#endif
}

static void virtio_blk_isr(int irqno, void *param)
{
    int id;
    struct virtio_blk_device *virtio_blk_dev = (struct virtio_blk_device *)param;
    struct virtio_blk *blk = virtio_blk_dev->blk;
    struct virtio_blk_buf *buf_tmp;

#ifdef RT_USING_SMP
    rt_base_t level;

    level = rt_spin_lock_irqsave(&virtio_blk_dev->spinlock);
#endif

    virtio_mmio_write32(
        virtio_blk_dev->mmio_base,
        VIRTIO_MMIO_INTERRUPT_ACK,
        virtio_mmio_read32(virtio_blk_dev->mmio_base, VIRTIO_MMIO_INTERRUPT_STATUS) & 0x3);

    rt_hw_dsb();

    /*
     * the device increments disk.used->idx
     * when it adds an entry to the used ring
     */
    while (blk->used_idx != blk->used->idx)
    {
        rt_hw_dsb();
        id = blk->used->ring[blk->used_idx % QUEUE_SIZE].id;

        if (blk->info[id].status != 0)
        {
            rt_kprintf("Virtio BLK Status");
            RT_ASSERT(0);
        }

        buf_tmp = blk->info[id].buf;

        /* done with buf */
        buf_tmp->valid = 0;
        rt_thread_yield();

        blk->used_idx += 1;
    }

#ifdef RT_USING_SMP
    rt_spin_unlock_irqrestore(&virtio_blk_dev->spinlock, level);
#endif
}

static rt_err_t virtio_blk_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t virtio_blk_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t virtio_blk_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t virtio_blk_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct virtio_blk_device *virtio_blk_dev = (struct virtio_blk_device *)dev;
    struct virtio_blk_buf buf =
    {
        .block_no = (uint32_t)pos,
        .data = (uint8_t *)buffer
    };

    virtio_blk_rw(virtio_blk_dev, &buf, VIRTIO_BLK_T_IN);

    return size;
}

static rt_size_t virtio_blk_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    struct virtio_blk_device *virtio_blk_dev = (struct virtio_blk_device *)dev;
    struct virtio_blk_buf buf =
    {
        .block_no = (uint32_t)pos,
        .data = (uint8_t *)buffer
    };

    virtio_blk_rw(virtio_blk_dev, &buf, VIRTIO_BLK_T_OUT);

    return size;
}

static rt_err_t virtio_blk_control(rt_device_t dev, int cmd, void *args)
{
    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry;

        geometry = (struct rt_device_blk_geometry *)args;
        if (geometry == RT_NULL)
        {
            return -RT_ERROR;
        }

        geometry->bytes_per_sector = VIRTIO_BLK_BYTES_PER_SECTOR;
        geometry->block_size = VIRTIO_BLK_BLOCK_SIZE;
        geometry->sector_count = VIRTIO_BLK_SECTOR_COUNT;
    }

    return RT_EOK;
}

const static struct rt_device_ops virtio_blk_ops =
{
    virtio_blk_init,
    virtio_blk_open,
    virtio_blk_close,
    virtio_blk_read,
    virtio_blk_write,
    virtio_blk_control
};

int rt_virtio_blk_init(void)
{
    rt_err_t status = RT_EOK;

#ifdef RT_USING_VIRTIO_BLK0
    virtio_blk_dev0.parent.type = RT_Device_Class_Block;
    virtio_blk_dev0.parent.ops  = &virtio_blk_ops;
    virtio_blk_dev0.blk = &blk0;
    virtio_blk_dev0.mmio_base = (uint32_t *)VIRTIO_MMIO_BLK0_BASE;

    status = virtio_blk_device_init(&virtio_blk_dev0);
    rt_device_register((rt_device_t)&virtio_blk_dev0, "virtio-blk0", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE);
    rt_hw_interrupt_install(VIRTIO_MMIO_BLK0_IRQ, virtio_blk_isr, &virtio_blk_dev0, "virtio-blk0");
    rt_hw_interrupt_umask(VIRTIO_MMIO_BLK0_IRQ);
#endif /* RT_USING_VIRTIO_BLK0 */

    return status;
}
INIT_DEVICE_EXPORT(rt_virtio_blk_init);
#endif /* BSP_USING_VIRTIO_BLK */
