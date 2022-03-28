/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <cpuport.h>

#include <virtio.h>

rt_inline void _virtio_dev_check(struct virtio_device *dev)
{
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(dev->mmio_config != RT_NULL);
}

void virtio_reset_device(struct virtio_device *dev)
{
    _virtio_dev_check(dev);

    dev->mmio_config->status = 0;
}

void virtio_status_acknowledge_driver(struct virtio_device *dev)
{
    _virtio_dev_check(dev);

    dev->mmio_config->status |= VIRTIO_STATUS_ACKNOWLEDGE | VIRTIO_STATUS_DRIVER;
}

void virtio_status_driver_ok(struct virtio_device *dev)
{
    _virtio_dev_check(dev);

    dev->mmio_config->status |= VIRTIO_STATUS_FEATURES_OK | VIRTIO_STATUS_DRIVER_OK;
}

void virtio_interrupt_ack(struct virtio_device *dev, rt_uint32_t ack)
{
    _virtio_dev_check(dev);

    dev->mmio_config->interrupt_ack = ack;
}

rt_err_t virtio_queue_init(struct virtio_device *dev, rt_uint32_t queue_index, rt_size_t ring_size)
{
    int i;
    void *pages;
    rt_ubase_t pages_paddr;
    rt_size_t pages_total_size;
    struct virtq *queue;

    _virtio_dev_check(dev);

    RT_ASSERT(dev->mmio_config->queue_num_max > 0);
    RT_ASSERT(dev->mmio_config->queue_num_max > queue_index);
    /* ring_size is power of 2 */
    RT_ASSERT(ring_size > 0);
    RT_ASSERT(((ring_size - 1) & ring_size) == 0);

    queue = &dev->queues[queue_index];
    pages_total_size = VIRTIO_PAGE_ALIGN(
            VIRTQ_DESC_TOTAL_SIZE(ring_size) + VIRTQ_AVAIL_TOTAL_SIZE(ring_size) + VIRTQ_USED_TOTAL_SIZE(ring_size));

    pages = rt_malloc_align(pages_total_size, VIRTIO_PAGE_SIZE);

    if (pages == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    queue->free = rt_malloc(sizeof(rt_bool_t) * ring_size);

    if (queue->free == RT_NULL)
    {
        rt_free_align(pages);
        return -RT_ENOMEM;
    }

    rt_memset(pages, 0, pages_total_size);
    pages_paddr = VIRTIO_VA2PA(pages);

    dev->mmio_config->guest_page_size = VIRTIO_PAGE_SIZE;
    dev->mmio_config->queue_sel = queue_index;
    dev->mmio_config->queue_num = ring_size;
    dev->mmio_config->queue_align = VIRTIO_PAGE_SIZE;
    dev->mmio_config->queue_pfn = pages_paddr >> VIRTIO_PAGE_SHIFT;

    queue->num = ring_size;
    queue->desc = (struct virtq_desc *)pages_paddr;
    queue->avail = (struct virtq_avail *)(pages_paddr + VIRTQ_DESC_TOTAL_SIZE(ring_size));
    queue->used = (struct virtq_used *)VIRTIO_PAGE_ALIGN(
            (rt_ubase_t)&queue->avail->ring[ring_size] + VIRTQ_AVAIL_RES_SIZE);

    queue->used_idx = 0;

    /* All descriptors start out unused */
    for (i = 0; i < ring_size; ++i)
    {
        queue->free[i] = RT_TRUE;
    }

    return RT_EOK;
}

void virtio_queue_destroy(struct virtio_device *dev, rt_uint32_t queue_index)
{
    struct virtq *queue;

    _virtio_dev_check(dev);

    RT_ASSERT(dev->mmio_config->queue_num_max > 0);
    RT_ASSERT(dev->mmio_config->queue_num_max > queue_index);

    queue = &dev->queues[queue_index];

    RT_ASSERT(queue->num > 0);

    rt_free(queue->free);
    rt_free_align((void *)queue->desc);

    dev->mmio_config->queue_sel = queue_index;
    dev->mmio_config->queue_pfn = RT_NULL;

    queue->num = 0;
    queue->desc = RT_NULL;
    queue->avail = RT_NULL;
    queue->used = RT_NULL;
}

void virtio_queue_notify(struct virtio_device *dev, rt_uint32_t queue_index)
{
    _virtio_dev_check(dev);

    dev->mmio_config->queue_notify = queue_index;
}

void virtio_submit_chain(struct virtio_device *dev, rt_uint32_t queue_index, rt_uint16_t desc_index)
{
    rt_size_t ring_size;
    struct virtq *queue;

    _virtio_dev_check(dev);

    queue = &dev->queues[queue_index];
    ring_size = queue->num;

    /* Tell the device the first index in our chain of descriptors */
    queue->avail->ring[queue->avail->idx % ring_size] = desc_index;
    rt_hw_dsb();

    /* Tell the device another avail ring entry is available */
    queue->avail->idx++;
    rt_hw_dsb();
}

rt_uint16_t virtio_alloc_desc(struct virtio_device *dev, rt_uint32_t queue_index)
{
    int i;
    rt_size_t ring_size;
    struct virtq *queue;

    _virtio_dev_check(dev);

    RT_ASSERT(queue_index < RT_USING_VIRTIO_QUEUE_MAX_NR);

    queue = &dev->queues[queue_index];
    ring_size = queue->num;

    for (i = 0; i < ring_size; ++i)
    {
        if (queue->free[i])
        {
            queue->free[i] = RT_FALSE;

            return (rt_uint16_t)i;
        }
    }

    return RT_UINT16_MAX;
}

void virtio_free_desc(struct virtio_device *dev, rt_uint32_t queue_index, rt_uint16_t desc_index)
{
    struct virtq *queue;

    _virtio_dev_check(dev);

    queue = &dev->queues[queue_index];

    RT_ASSERT(queue_index + 1 < RT_USING_VIRTIO_QUEUE_MAX_NR);
    RT_ASSERT(!queue->free[desc_index]);

    queue->desc[desc_index].addr = 0;
    queue->desc[desc_index].len = 0;
    queue->desc[desc_index].flags = 0;
    queue->desc[desc_index].next = 0;

    queue->free[desc_index] = RT_TRUE;
}

rt_err_t virtio_alloc_desc_chain(struct virtio_device *dev, rt_uint32_t queue_index, rt_size_t count,
        rt_uint16_t *indexs)
{
    int i, j;

    _virtio_dev_check(dev);

    RT_ASSERT(indexs != RT_NULL);

    for (i = 0; i < count; ++i)
    {
        indexs[i] = virtio_alloc_desc(dev, queue_index);

        if (indexs[i] == RT_UINT16_MAX)
        {
            for (j = 0; j < i; ++j)
            {
                virtio_free_desc(dev, queue_index, indexs[j]);
            }

            return -RT_ERROR;
        }
    }

    return RT_EOK;
}

void virtio_free_desc_chain(struct virtio_device *dev, rt_uint32_t queue_index, rt_uint16_t desc_index)
{
    rt_uint16_t flags, next;
    struct virtq_desc *desc;

    _virtio_dev_check(dev);

    desc = &dev->queues[queue_index].desc[0];

    for (;;)
    {
        flags = desc[desc_index].flags;
        next = desc[desc_index].next;

        virtio_free_desc(dev, queue_index, desc_index);

        if (flags & VIRTQ_DESC_F_NEXT)
        {
            desc_index = next;
        }
        else
        {
            break;
        }
    }
}

void virtio_fill_desc(struct virtio_device *dev, rt_uint32_t queue_index, rt_uint16_t desc_index,
        rt_uint64_t addr, rt_uint32_t len, rt_uint16_t flags, rt_uint16_t next)
{
    struct virtq_desc *desc;

    _virtio_dev_check(dev);

    desc = &dev->queues[queue_index].desc[desc_index];

    desc->addr = addr;
    desc->len = len;
    desc->flags = flags;
    desc->next = next;
}
