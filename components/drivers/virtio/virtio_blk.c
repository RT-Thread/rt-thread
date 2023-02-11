/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-9-16      GuEe-GUI     the first version
 * 2021-11-11     GuEe-GUI     using virtio common interface
 */

#include <rthw.h>
#include <rtthread.h>
#include <cpuport.h>

#ifdef RT_USING_VIRTIO_BLK

#include <virtio_blk.h>

static void virtio_blk_rw(struct virtio_blk_device *virtio_blk_dev, rt_off_t pos, void *buffer, rt_size_t count,
    int flags)
{
    rt_uint16_t idx[3];
    rt_size_t size = count * virtio_blk_dev->config->blk_size;
    struct virtio_device *virtio_dev = &virtio_blk_dev->virtio_dev;

#ifdef RT_USING_SMP
    rt_base_t level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
#endif

    /* Allocate 3 descriptors */
    while (virtio_alloc_desc_chain(virtio_dev, 0, 3, idx))
    {
#ifdef RT_USING_SMP
        rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
#endif
        rt_thread_yield();

#ifdef RT_USING_SMP
        level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
#endif
    }

    virtio_blk_dev->info[idx[0]].status = 0xff;
    virtio_blk_dev->info[idx[0]].valid = RT_TRUE;
    virtio_blk_dev->info[idx[0]].req.type = flags;
    virtio_blk_dev->info[idx[0]].req.ioprio = 0;
    virtio_blk_dev->info[idx[0]].req.sector = pos * (virtio_blk_dev->config->blk_size / 512);

    flags = flags == VIRTIO_BLK_T_OUT ? 0 : VIRTQ_DESC_F_WRITE;

    virtio_fill_desc(virtio_dev, VIRTIO_BLK_QUEUE, idx[0],
            VIRTIO_VA2PA(&virtio_blk_dev->info[idx[0]].req), sizeof(struct virtio_blk_req), VIRTQ_DESC_F_NEXT, idx[1]);

    virtio_fill_desc(virtio_dev, VIRTIO_BLK_QUEUE, idx[1],
            VIRTIO_VA2PA(buffer), size, flags | VIRTQ_DESC_F_NEXT, idx[2]);

    virtio_fill_desc(virtio_dev, VIRTIO_BLK_QUEUE, idx[2],
            VIRTIO_VA2PA(&virtio_blk_dev->info[idx[0]].status), sizeof(rt_uint8_t), VIRTQ_DESC_F_WRITE, 0);

    virtio_submit_chain(virtio_dev, VIRTIO_BLK_QUEUE, idx[0]);

    virtio_queue_notify(virtio_dev, VIRTIO_BLK_QUEUE);

    /* Wait for virtio_blk_isr() to done */
    while (virtio_blk_dev->info[idx[0]].valid)
    {
#ifdef RT_USING_SMP
        rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
#endif
        rt_thread_yield();

#ifdef RT_USING_SMP
        level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
#endif
    }

    virtio_free_desc_chain(virtio_dev, VIRTIO_BLK_QUEUE, idx[0]);

#ifdef RT_USING_SMP
    rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
#endif
}

static rt_ssize_t virtio_blk_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t count)
{
    virtio_blk_rw((struct virtio_blk_device *)dev, pos, buffer, count, VIRTIO_BLK_T_IN);

    return count;
}

static rt_ssize_t virtio_blk_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t count)
{
    virtio_blk_rw((struct virtio_blk_device *)dev, pos, (void *)buffer, count, VIRTIO_BLK_T_OUT);

    return count;
}

static rt_err_t virtio_blk_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t status = RT_EOK;
    struct virtio_blk_device *virtio_blk_dev = (struct virtio_blk_device *)dev;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_BLK_GETGEOME:
        {
            struct rt_device_blk_geometry *geometry = (struct rt_device_blk_geometry *)args;

            if (geometry == RT_NULL)
            {
                status = -RT_ERROR;
                break;
            }

            geometry->bytes_per_sector = VIRTIO_BLK_BYTES_PER_SECTOR;
            geometry->block_size = virtio_blk_dev->config->blk_size;
            geometry->sector_count = virtio_blk_dev->config->capacity;
        }
        break;
    default:
        status = -RT_EINVAL;
        break;
    }

    return status;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops virtio_blk_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    virtio_blk_read,
    virtio_blk_write,
    virtio_blk_control
};
#endif

static void virtio_blk_isr(int irqno, void *param)
{
    rt_uint32_t id;
    struct virtio_blk_device *virtio_blk_dev = (struct virtio_blk_device *)param;
    struct virtio_device *virtio_dev = &virtio_blk_dev->virtio_dev;
    struct virtq *queue = &virtio_dev->queues[VIRTIO_BLK_QUEUE];

#ifdef RT_USING_SMP
    rt_base_t level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
#endif

    virtio_interrupt_ack(virtio_dev);
    rt_hw_dsb();

    /* The device increments disk.used->idx when it adds an entry to the used ring */
    while (queue->used_idx != queue->used->idx)
    {
        rt_hw_dsb();
        id = queue->used->ring[queue->used_idx % queue->num].id;

        RT_ASSERT(virtio_blk_dev->info[id].status == 0);

        /* Done with buffer */
        virtio_blk_dev->info[id].valid = RT_FALSE;

        queue->used_idx++;
    }

#ifdef RT_USING_SMP
    rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
#endif
}

rt_err_t rt_virtio_blk_init(rt_ubase_t *mmio_base, rt_uint32_t irq)
{
    static int dev_no = 0;
    char dev_name[RT_NAME_MAX];
    struct virtio_device *virtio_dev;
    struct virtio_blk_device *virtio_blk_dev;

    virtio_blk_dev = rt_malloc(sizeof(struct virtio_blk_device));

    if (virtio_blk_dev == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    virtio_dev = &virtio_blk_dev->virtio_dev;
    virtio_dev->irq = irq;
    virtio_dev->mmio_base = mmio_base;

    virtio_blk_dev->config = (struct virtio_blk_config *)virtio_dev->mmio_config->config;

#ifdef RT_USING_SMP
    rt_spin_lock_init(&virtio_dev->spinlock);
#endif

    virtio_reset_device(virtio_dev);
    virtio_status_acknowledge_driver(virtio_dev);

    /* Negotiate features */
    virtio_dev->mmio_config->driver_features = virtio_dev->mmio_config->device_features & ~(
            (1 << VIRTIO_BLK_F_RO) |
            (1 << VIRTIO_BLK_F_MQ) |
            (1 << VIRTIO_BLK_F_SCSI) |
            (1 << VIRTIO_BLK_F_CONFIG_WCE) |
            (1 << VIRTIO_F_ANY_LAYOUT) |
            (1 << VIRTIO_F_RING_EVENT_IDX) |
            (1 << VIRTIO_F_RING_INDIRECT_DESC));

    /* Tell device that feature negotiation is complete and we're completely ready */
    virtio_status_driver_ok(virtio_dev);

    if (virtio_queues_alloc(virtio_dev, 1) != RT_EOK)
    {
        goto _alloc_fail;
    }

    /* Initialize queue 0 */
    if (virtio_queue_init(virtio_dev, 0, VIRTIO_BLK_QUEUE_RING_SIZE) != RT_EOK)
    {
        goto _alloc_fail;
    }

    virtio_blk_dev->parent.type = RT_Device_Class_Block;
#ifdef RT_USING_DEVICE_OPS
    virtio_blk_dev->parent.ops  = &virtio_blk_ops;
#else
    virtio_blk_dev->parent.init     = RT_NULL;
    virtio_blk_dev->parent.open     = RT_NULL;
    virtio_blk_dev->parent.close    = RT_NULL;
    virtio_blk_dev->parent.read     = virtio_blk_read;
    virtio_blk_dev->parent.write    = virtio_blk_write;
    virtio_blk_dev->parent.control  = virtio_blk_control;
#endif

    rt_snprintf(dev_name, RT_NAME_MAX, "virtio-blk%d", dev_no++);

    rt_hw_interrupt_install(irq, virtio_blk_isr, virtio_blk_dev, dev_name);
    rt_hw_interrupt_umask(irq);

    return rt_device_register((rt_device_t)virtio_blk_dev, dev_name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_REMOVABLE);

_alloc_fail:

    if (virtio_blk_dev != RT_NULL)
    {
        virtio_queues_free(virtio_dev);
        rt_free(virtio_blk_dev);
    }
    return -RT_ENOMEM;
}
#endif /* RT_USING_VIRTIO_BLK */
