/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 * 2023-10-12     fangjianzhou support SDL2
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

void virtio_interrupt_ack(struct virtio_device *dev)
{
    rt_uint32_t status;

    _virtio_dev_check(dev);

    status = dev->mmio_config->interrupt_status;

    if (status != 0)
    {
        dev->mmio_config->interrupt_ack = status;
    }
}

rt_bool_t virtio_has_feature(struct virtio_device *dev, rt_uint32_t feature_bit)
{
    _virtio_dev_check(dev);

    return !!(dev->mmio_config->device_features & (1UL << feature_bit));
}

rt_err_t virtio_queues_alloc(struct virtio_device *dev, rt_size_t queues_num)
{
    _virtio_dev_check(dev);

    dev->queues = rt_malloc(sizeof(struct virtq) * queues_num);

    if (dev->queues != RT_NULL)
    {
        dev->queues_num = queues_num;

        return RT_EOK;
    }

    return -RT_ENOMEM;
}

void virtio_queues_free(struct virtio_device *dev)
{
    if (dev->queues != RT_NULL)
    {
        dev->queues_num = 0;
        rt_free(dev->queues);
    }
}

rt_err_t virtio_queue_init(struct virtio_device *dev, rt_uint32_t queue_index, rt_size_t ring_size)
{
    int i;
    void *pages;
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
            VIRTQ_DESC_TOTAL_SIZE(ring_size) + VIRTQ_AVAIL_TOTAL_SIZE(ring_size)) + VIRTQ_USED_TOTAL_SIZE(ring_size);

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

    dev->mmio_config->guest_page_size = VIRTIO_PAGE_SIZE;
    dev->mmio_config->queue_sel = queue_index;
    dev->mmio_config->queue_num = ring_size;
    dev->mmio_config->queue_align = VIRTIO_PAGE_SIZE;
    dev->mmio_config->queue_pfn = VIRTIO_VA2PA(pages) >> VIRTIO_PAGE_SHIFT;

    queue->num = ring_size;
    queue->desc = (struct virtq_desc *)((rt_ubase_t)pages);
    queue->avail = (struct virtq_avail *)(((rt_ubase_t)pages) + VIRTQ_DESC_TOTAL_SIZE(ring_size));
    queue->used = (struct virtq_used *)VIRTIO_PAGE_ALIGN(
            (rt_ubase_t)&queue->avail->ring[ring_size] + VIRTQ_AVAIL_RES_SIZE);

    queue->used_idx = 0;

    /* All descriptors start out unused */
    for (i = 0; i < ring_size; ++i)
    {
        queue->free[i] = RT_TRUE;
    }

    queue->free_count = ring_size;

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
    struct virtq *queue;

    _virtio_dev_check(dev);

    RT_ASSERT(queue_index < dev->queues_num);

    queue = &dev->queues[queue_index];

    if (queue->free_count > 0)
    {
        rt_size_t ring_size = queue->num;

        for (i = 0; i < ring_size; ++i)
        {
            if (queue->free[i])
            {
                queue->free[i] = RT_FALSE;
                queue->free_count--;

                return (rt_uint16_t)i;
            }
        }
    }

    return VIRTQ_INVALID_DESC_ID;
}

void virtio_free_desc(struct virtio_device *dev, rt_uint32_t queue_index, rt_uint16_t desc_index)
{
    struct virtq *queue;

    _virtio_dev_check(dev);

    queue = &dev->queues[queue_index];

    RT_ASSERT(queue_index < dev->queues_num);
    RT_ASSERT(!queue->free[desc_index]);

    queue->desc[desc_index].addr = 0;
    queue->desc[desc_index].len = 0;
    queue->desc[desc_index].flags = 0;
    queue->desc[desc_index].next = 0;

    queue->free[desc_index] = RT_TRUE;

    queue->free_count++;
}

rt_err_t virtio_alloc_desc_chain(struct virtio_device *dev, rt_uint32_t queue_index, rt_size_t count,
        rt_uint16_t *indexs)
{
    int i, j;

    _virtio_dev_check(dev);

    RT_ASSERT(indexs != RT_NULL);

    if (dev->queues[queue_index].free_count < count)
    {
        return -RT_ERROR;
    }

    for (i = 0; i < count; ++i)
    {
        indexs[i] = virtio_alloc_desc(dev, queue_index);

        if (indexs[i] == VIRTQ_INVALID_DESC_ID)
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

#ifdef RT_USING_SMART
#ifdef RT_USING_VIRTIO_GPU

#include <virtio_gpu.h>
#include "drivers/lcd.h"
#include <dfs_file.h>
#include <lwp_user_mm.h>

static struct rt_device_graphic_info _graphic_info;
static struct rt_device_rect_info    _rect_info;
static struct rt_device              _fb        = {};
static rt_device_t                   _gpu_dev   = RT_NULL;

static rt_err_t fb_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t fb_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t fb_control(rt_device_t dev, int cmd, void *args)
{
    switch(cmd)
    {
        case FBIOPAN_DISPLAY:
        {
            rt_hw_cpu_dcache_clean(_graphic_info.framebuffer, _graphic_info.smem_len);
            rt_device_control(_gpu_dev, RTGRAPHIC_CTRL_RECT_UPDATE, &_rect_info);
            break;
        }
        case FBIOGET_FSCREENINFO:
        {
            struct fb_fix_screeninfo *info = (struct fb_fix_screeninfo *)args;
            strncpy(info->id, "lcd", sizeof(info->id));
            info->smem_len = _graphic_info.smem_len;
            break;
        }
        case FBIOGET_VSCREENINFO:
        {
            struct fb_var_screeninfo *info = (struct fb_var_screeninfo *)args;
            info->bits_per_pixel           = _graphic_info.bits_per_pixel;
            info->xres                     = _graphic_info.width;
            info->yres                     = _graphic_info.height;
            info->yres_virtual             = _graphic_info.height;
            info->xres_virtual             = _graphic_info.width;
            info->transp.offset            = 24;
            info->transp.length            = 8;
            info->red.offset               = 0;
            info->red.length               = 8;
            info->green.offset             = 8;
            info->green.length             = 8;
            info->blue.offset              = 16;
            info->blue.length              = 8;
            break;
        }
        case RT_FIOMMAP2:
        {
            struct dfs_mmap2_args *mmap2 = (struct dfs_mmap2_args *)args;

            if(mmap2)
            {
                mmap2->ret = lwp_map_user_phy(lwp_self(), RT_NULL, rt_kmem_v2p(_graphic_info.framebuffer), mmap2->length, 1);
            }
            else
            {
                return -EIO;
            }

            break;
        }
        default:
            break;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops fb_ops =
{
    RT_NULL,
    fb_open,
    fb_close,
    RT_NULL,
    RT_NULL,
    fb_control
};
#endif

static int fb_init()
{
    _gpu_dev = rt_device_find("virtio-gpu0");

    if(_gpu_dev == RT_NULL)
    {
        return -RT_ERROR;
    }

    if(_gpu_dev != RT_NULL && rt_device_open(_gpu_dev, 0) == RT_EOK)
    {
        rt_memset(&_graphic_info, 0, sizeof(_graphic_info));
        rt_memset(&_rect_info, 0, sizeof(_rect_info));
        rt_device_control(_gpu_dev, VIRTIO_DEVICE_CTRL_GPU_SET_PRIMARY, RT_NULL);
        rt_device_control(_gpu_dev, VIRTIO_DEVICE_CTRL_GPU_CREATE_2D, (void *)RTGRAPHIC_PIXEL_FORMAT_RGB888);
        rt_device_control(_gpu_dev, RTGRAPHIC_CTRL_GET_INFO, &_graphic_info);
        _rect_info.x      = 0;
        _rect_info.y      = 0;
        _rect_info.width  = _graphic_info.width;
        _rect_info.height = _graphic_info.height;
        memset(_graphic_info.framebuffer, 0xff, _graphic_info.smem_len);
        rt_device_control(_gpu_dev, RTGRAPHIC_CTRL_RECT_UPDATE, &_rect_info);
    }

    if(rt_device_find("fb0") != RT_NULL)
    {
        rt_kprintf("a device named fb0 already exists\n");
        return -RT_ERROR;
    }

    _fb.type = RT_Device_Class_Miscellaneous;

#ifdef RT_USING_DEVICE_OPS
    _fb.ops        = &fb_ops;
#else
    _fb.init       = RT_NULL;
    _fb.open       = fb_open;
    _fb.close      = fb_close;
    _fb.read       = RT_NULL;
    _fb.write      = RT_NULL;
    _fb.control    = fb_control;
    _fb.user_data  = RT_NULL;
#endif

    rt_device_register(&_fb, "fb0", RT_DEVICE_FLAG_RDWR);
    return RT_EOK;
}
INIT_COMPONENT_EXPORT(fb_init);
#endif
#endif
