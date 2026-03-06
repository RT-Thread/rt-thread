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
#include <cpuport.h>
#include <rtdevice.h>

#ifdef RT_USING_VIRTIO_GPU

#include <virtio_gpu.h>

static struct virtio_gpu_device *_primary_virtio_gpu_dev = RT_NULL;

static rt_ubase_t _pixel_format_convert(rt_ubase_t format, rt_bool_t to_virtio_gpu_format)
{
    rt_ubase_t ret = 0;

    if (to_virtio_gpu_format)
    {
        switch (format)
        {
        case RTGRAPHIC_PIXEL_FORMAT_RGB888:
            ret = VIRTIO_GPU_FORMAT_R8G8B8X8_UNORM;
            break;
        case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
            ret = VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM;
            break;
        case RTGRAPHIC_PIXEL_FORMAT_ABGR888:
            ret = VIRTIO_GPU_FORMAT_A8B8G8R8_UNORM;
            break;
        default:
            break;
        }
    }
    else
    {
        switch (format)
        {
        case VIRTIO_GPU_FORMAT_R8G8B8X8_UNORM:
            ret = RTGRAPHIC_PIXEL_FORMAT_RGB888;
            break;
        case VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM:
            ret = RTGRAPHIC_PIXEL_FORMAT_ARGB888;
            break;
        case VIRTIO_GPU_FORMAT_A8B8G8R8_UNORM:
            ret = RTGRAPHIC_PIXEL_FORMAT_ABGR888;
            break;
        default:
            break;
        }
    }

    return ret;
}

static void virtio_gpu_ctrl_send_command(struct virtio_gpu_device *virtio_gpu_dev,
        const void *cmd, rt_size_t cmd_len, void *res, rt_size_t res_len)
{
    rt_uint16_t idx[2];
    void *addr = &virtio_gpu_dev->gpu_request;
    void *ret_res = ((rt_uint8_t *)addr + cmd_len);
    struct virtio_device *virtio_dev = &virtio_gpu_dev->virtio_dev;

#ifdef RT_USING_SMP
    rt_base_t level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
#endif

    while (virtio_alloc_desc_chain(virtio_dev, VIRTIO_GPU_QUEUE_CTRL, 2, idx))
    {
#ifdef RT_USING_SMP
        rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
#endif
        rt_thread_yield();

#ifdef RT_USING_SMP
        level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
#endif
    }

    rt_memcpy(&virtio_gpu_dev->gpu_request, cmd, cmd_len);

    virtio_fill_desc(virtio_dev, VIRTIO_GPU_QUEUE_CTRL, idx[0],
            VIRTIO_VA2PA(addr), cmd_len, VIRTQ_DESC_F_NEXT, idx[1]);

    virtio_fill_desc(virtio_dev, VIRTIO_GPU_QUEUE_CTRL, idx[1],
            VIRTIO_VA2PA(addr) + cmd_len, res_len, VIRTQ_DESC_F_WRITE, 0);

    rt_memset(ret_res, 0, res_len);

    virtio_gpu_dev->info[idx[0]].ctrl_valid = RT_TRUE;

    virtio_submit_chain(virtio_dev, VIRTIO_GPU_QUEUE_CTRL, idx[0]);

    virtio_queue_notify(virtio_dev, VIRTIO_GPU_QUEUE_CTRL);

    while (virtio_gpu_dev->info[idx[0]].ctrl_valid)
    {
#ifdef RT_USING_SMP
        rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
#endif
        rt_thread_yield();

#ifdef RT_USING_SMP
        level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
#endif
    }

    virtio_free_desc_chain(virtio_dev, VIRTIO_GPU_QUEUE_CTRL, idx[0]);

    rt_memcpy(res, ret_res, res_len);

#ifdef RT_USING_SMP
    rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
#endif
}

static void virtio_gpu_cursor_send_command(struct virtio_gpu_device *virtio_gpu_dev,
        const void *cmd, rt_size_t cmd_len)
{
    rt_uint16_t id;
    void *addr;
    struct virtio_device *virtio_dev = &virtio_gpu_dev->virtio_dev;

#ifdef RT_USING_SMP
    rt_base_t level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
#endif

    while ((id = virtio_alloc_desc(virtio_dev, VIRTIO_GPU_QUEUE_CURSOR)) == VIRTQ_INVALID_DESC_ID)
    {
#ifdef RT_USING_SMP
        rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
#endif
        rt_thread_yield();

#ifdef RT_USING_SMP
        level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
#endif
    }

    addr = &virtio_gpu_dev->info[id].cursor_cmd;
    virtio_gpu_dev->info[id].cursor_valid = RT_TRUE;

    rt_memcpy(addr, cmd, cmd_len);

    virtio_fill_desc(virtio_dev, VIRTIO_GPU_QUEUE_CURSOR, id, VIRTIO_VA2PA(addr), cmd_len, 0, 0);

    virtio_submit_chain(virtio_dev, VIRTIO_GPU_QUEUE_CURSOR, id);

    virtio_queue_notify(virtio_dev, VIRTIO_GPU_QUEUE_CURSOR);

    while (virtio_gpu_dev->info[id].cursor_valid)
    {
#ifdef RT_USING_SMP
        rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
#endif
        rt_thread_yield();

#ifdef RT_USING_SMP
        level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
#endif
    }

    virtio_free_desc(virtio_dev, VIRTIO_GPU_QUEUE_CURSOR, id);

#ifdef RT_USING_SMP
    rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
#endif
}

static rt_err_t virtio_gpu_create_2d_resource(struct virtio_gpu_device *virtio_gpu_dev, enum virtio_gpu_formats format,
        rt_uint32_t *resource_id, rt_uint32_t width, rt_uint32_t height)
{
    struct virtio_gpu_ctrl_hdr res;
    struct virtio_gpu_resource_create_2d req;

    *resource_id = ++virtio_gpu_dev->next_resource_id;

    req.hdr.type = VIRTIO_GPU_CMD_RESOURCE_CREATE_2D;
    req.resource_id = *resource_id;
    req.format = format;
    req.width = width;
    req.height = height;

    virtio_gpu_ctrl_send_command(virtio_gpu_dev, &req, sizeof(req), &res, sizeof(res));

    if (res.type == VIRTIO_GPU_RESP_OK_NODATA)
    {
        return RT_EOK;
    }

    return -RT_ERROR;
}

static rt_err_t virtio_gpu_unref_resource(struct virtio_gpu_device *virtio_gpu_dev, rt_uint32_t resource_id)
{
    struct virtio_gpu_ctrl_hdr res;
    struct virtio_gpu_resource_unref req;

    rt_memset(&req, 0, sizeof(req));

    req.hdr.type = VIRTIO_GPU_CMD_RESOURCE_UNREF;
    req.resource_id = resource_id;

    virtio_gpu_ctrl_send_command(virtio_gpu_dev, &req, sizeof(req), &res, sizeof(res));

    if (res.type == VIRTIO_GPU_RESP_OK_NODATA)
    {
        return RT_EOK;
    }

    return -RT_ERROR;
}

static rt_err_t virtio_gpu_attach_backing_resource(struct virtio_gpu_device *virtio_gpu_dev, rt_uint32_t resource_id,
        void *buffer, rt_size_t size)
{
    struct virtio_gpu_ctrl_hdr res;
    struct
    {
        struct virtio_gpu_resource_attach_backing req;
        struct virtio_gpu_mem_entry mem;
    } req;

    rt_memset(&req, 0, sizeof(req));

    req.req.hdr.type = VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING;
    req.req.resource_id = resource_id;
    req.req.nr_entries = 1;

    req.mem.addr = VIRTIO_VA2PA(buffer);
    req.mem.length = size;

    virtio_gpu_ctrl_send_command(virtio_gpu_dev, &req, sizeof(req), &res, sizeof(res));

    if (res.type == VIRTIO_GPU_RESP_OK_NODATA)
    {
        return RT_EOK;
    }

    return -RT_ERROR;
}

static rt_err_t virtio_gpu_set_scanout(struct virtio_gpu_device *virtio_gpu_dev, rt_uint32_t scanout_id,
        rt_uint32_t resource_id, rt_uint32_t width, rt_uint32_t height)
{
    struct virtio_gpu_ctrl_hdr res;
    struct virtio_gpu_set_scanout req;

    rt_memset(&req, 0, sizeof(req));

    req.hdr.type = VIRTIO_GPU_CMD_SET_SCANOUT;
    req.r.x = 0;
    req.r.y = 0;
    req.r.width = width;
    req.r.height = height;
    req.scanout_id = scanout_id;
    req.resource_id = resource_id;

    virtio_gpu_ctrl_send_command(virtio_gpu_dev, &req, sizeof(req), &res, sizeof(res));

    if (res.type == VIRTIO_GPU_RESP_OK_NODATA)
    {
        return RT_EOK;
    }

    return -RT_ERROR;
}

static rt_err_t virtio_gpu_flush_resource(struct virtio_gpu_device *virtio_gpu_dev, rt_uint32_t resource_id,
        rt_uint32_t x, rt_uint32_t y, rt_uint32_t width, rt_uint32_t height)
{
    struct virtio_gpu_ctrl_hdr res;
    struct virtio_gpu_resource_flush req;

    rt_memset(&req, 0, sizeof(req));

    req.hdr.type = VIRTIO_GPU_CMD_RESOURCE_FLUSH;
    req.r.x = x;
    req.r.y = y;
    req.r.width = width;
    req.r.height = height;
    req.resource_id = resource_id;

    virtio_gpu_ctrl_send_command(virtio_gpu_dev, &req, sizeof(req), &res, sizeof(res));

    if (res.type == VIRTIO_GPU_RESP_OK_NODATA)
    {
        return RT_EOK;
    }

    return -RT_ERROR;
}

static rt_err_t virtio_gpu_transfer_to_host_2d(struct virtio_gpu_device *virtio_gpu_dev, rt_uint32_t resource_id,
        rt_uint32_t x, rt_uint32_t y, rt_uint32_t width, rt_uint32_t height, rt_uint32_t offset)
{
    struct virtio_gpu_ctrl_hdr res;
    struct virtio_gpu_transfer_to_host_2d req;

    rt_memset(&req, 0, sizeof(req));

    req.hdr.type = VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D;
    req.r.x = x;
    req.r.y = y;
    req.r.width = width;
    req.r.height = height;
    req.offset = offset;
    req.resource_id = resource_id;

    virtio_gpu_ctrl_send_command(virtio_gpu_dev, &req, sizeof(req), &res, sizeof(res));

    if (res.type == VIRTIO_GPU_RESP_OK_NODATA)
    {
        return RT_EOK;
    }

    return -RT_ERROR;
}

static rt_err_t virtio_gpu_gfx_flush_2d(struct virtio_gpu_device *virtio_gpu_dev, rt_uint32_t resource_id,
        rt_uint32_t x, rt_uint32_t y, rt_uint32_t width, rt_uint32_t height)
{
    rt_err_t status = virtio_gpu_transfer_to_host_2d(virtio_gpu_dev, resource_id, x, y, width, height, 0);

    if (status == RT_EOK)
    {
        status = virtio_gpu_flush_resource(virtio_gpu_dev, resource_id, x, y, width, height);
    }

    return status;
}

static rt_err_t virtio_gpu_update_cursor(struct virtio_gpu_device *virtio_gpu_dev, rt_uint32_t scanout_id,
        rt_uint32_t resource_id, rt_uint32_t hot_x, rt_uint32_t hot_y)
{
    struct virtio_gpu_update_cursor req;

    rt_memset(&req, 0, sizeof(req));

    req.hdr.type = VIRTIO_GPU_CMD_UPDATE_CURSOR;
    req.pos.scanout_id = scanout_id;
    req.resource_id = resource_id;
    req.hot_x = hot_x;
    req.hot_y = hot_y;

    virtio_gpu_cursor_send_command(virtio_gpu_dev, &req, sizeof(req));

    return RT_EOK;
}

static rt_err_t virtio_gpu_cursor_move(struct virtio_gpu_device *virtio_gpu_dev, rt_uint32_t scanout_id,
        rt_uint32_t resource_id, rt_uint32_t x, rt_uint32_t y)
{
    struct virtio_gpu_update_cursor req;

    rt_memset(&req, 0, sizeof(req));

    req.hdr.type = VIRTIO_GPU_CMD_MOVE_CURSOR;
    req.pos.scanout_id = scanout_id;
    req.pos.x = x;
    req.pos.y = y;
    req.resource_id = resource_id;

    virtio_gpu_cursor_send_command(virtio_gpu_dev, &req, sizeof(req));

    return RT_EOK;
}

static rt_err_t virtio_gpu_cursor_set_img(struct virtio_gpu_device *virtio_gpu_dev, void *img)
{
    rt_err_t status;

    rt_memcpy(virtio_gpu_dev->cursor_img, img, VIRTIO_GPU_CURSOR_IMG_SIZE);

    status = virtio_gpu_attach_backing_resource(virtio_gpu_dev,
            virtio_gpu_dev->cursor_resource_id, virtio_gpu_dev->cursor_img, VIRTIO_GPU_CURSOR_IMG_SIZE);

    if (status != RT_EOK)
    {
        return status;
    }

    status = virtio_gpu_transfer_to_host_2d(virtio_gpu_dev, virtio_gpu_dev->cursor_resource_id,
            0, 0, VIRTIO_GPU_CURSOR_WIDTH, VIRTIO_GPU_CURSOR_HEIGHT, 0);

    return status;
}

static rt_err_t virtio_gpu_get_display_info(struct virtio_gpu_device *virtio_gpu_dev)
{
    int i;
    struct virtio_gpu_ctrl_hdr req;
    struct virtio_gpu_resp_display_info info;

    rt_memset(&req, 0, sizeof(req));
    req.type = VIRTIO_GPU_CMD_GET_DISPLAY_INFO;

    virtio_gpu_ctrl_send_command(virtio_gpu_dev, &req, sizeof(req), &info, sizeof(info));

    if (info.hdr.type != VIRTIO_GPU_RESP_OK_DISPLAY_INFO)
    {
        return -RT_ERROR;
    }

    for (i = 0; i < VIRTIO_GPU_MAX_SCANOUTS; ++i)
    {
        if (info.pmodes[i].enabled)
        {
            if (virtio_gpu_dev->pmode_id == VIRTIO_GPU_INVALID_PMODE_ID)
            {
                rt_memcpy(&virtio_gpu_dev->pmode, &info.pmodes[i], sizeof(virtio_gpu_dev->pmode));
                virtio_gpu_dev->pmode_id = i;
            }
        }
    }

    return RT_EOK;
}

static rt_err_t virtio_gpu_init(rt_device_t dev)
{
    rt_err_t status;
    struct virtio_gpu_device *virtio_gpu_dev = (struct virtio_gpu_device *)dev;
    struct virtio_device *virtio_dev = &virtio_gpu_dev->virtio_dev;
    struct virtq *queue_ctrl, *queue_cursor;

    queue_ctrl = &virtio_dev->queues[VIRTIO_GPU_QUEUE_CTRL];
    queue_cursor = &virtio_dev->queues[VIRTIO_GPU_QUEUE_CURSOR];

    queue_ctrl->avail->flags = 0;
    queue_cursor->avail->flags = 0;

    status = virtio_gpu_get_display_info(virtio_gpu_dev);

    if (virtio_gpu_dev->pmode_id != VIRTIO_GPU_INVALID_PMODE_ID && _primary_virtio_gpu_dev == RT_NULL)
    {
        /* This device is ready */
        _primary_virtio_gpu_dev = virtio_gpu_dev;
    }

    return status;
}

static rt_ssize_t virtio_gpu_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct virtio_gpu_device *virtio_gpu_dev = (struct virtio_gpu_device *)dev;

    if (virtio_gpu_dev->framebuffer == RT_NULL || pos + size >= virtio_gpu_dev->smem_len)
    {
        return 0;
    }

    rt_mutex_take(&virtio_gpu_dev->rw_mutex, RT_WAITING_FOREVER);

    rt_memcpy(buffer, (rt_uint8_t *)virtio_gpu_dev->framebuffer + pos, size);

    rt_mutex_release(&virtio_gpu_dev->rw_mutex);

    return size;
}

static rt_ssize_t virtio_gpu_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    struct virtio_gpu_device *virtio_gpu_dev = (struct virtio_gpu_device *)dev;

    if (virtio_gpu_dev->framebuffer == RT_NULL || pos + size >= virtio_gpu_dev->smem_len)
    {
        return 0;
    }

    rt_mutex_take(&virtio_gpu_dev->rw_mutex, RT_WAITING_FOREVER);

    rt_memcpy((rt_uint8_t *)virtio_gpu_dev->framebuffer + pos, buffer, size);

    rt_mutex_release(&virtio_gpu_dev->rw_mutex);

    return size;
}

static rt_err_t virtio_gpu_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t status = RT_EOK;
    struct virtio_gpu_device *virtio_gpu_dev = (struct virtio_gpu_device *)dev;

    switch (cmd)
    {
    case VIRTIO_DEVICE_CTRL_GPU_SET_PRIMARY:

        _primary_virtio_gpu_dev = virtio_gpu_dev;

        return status;
    }

    if (args == RT_NULL)
    {
        return -RT_ERROR;
    }

    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        {
            struct rt_device_rect_info *info = (struct rt_device_rect_info *)args;

            if (virtio_gpu_dev->pmode_id == VIRTIO_GPU_INVALID_PMODE_ID)
            {
                status = -RT_ERROR;
                break;
            }

            status = virtio_gpu_gfx_flush_2d(virtio_gpu_dev, virtio_gpu_dev->display_resource_id,
                    info->x, info->y, info->width, info->height);
        }
        break;
    case RTGRAPHIC_CTRL_GET_INFO:
        {
            struct rt_device_graphic_info *info = (struct rt_device_graphic_info *)args;

            info->pixel_format      = _pixel_format_convert((rt_ubase_t)args, RT_FALSE);
            info->bits_per_pixel    = VIRTIO_GPU_FORMAT_BPP;
            info->pitch             = virtio_gpu_dev->pmode.r.width * VIRTIO_GPU_FORMAT_PIXEL;
            info->width             = virtio_gpu_dev->pmode.r.width;
            info->height            = virtio_gpu_dev->pmode.r.height;
            info->framebuffer       = virtio_gpu_dev->framebuffer;
            info->smem_len          = virtio_gpu_dev->smem_len;
        }
        break;
    case VIRTIO_DEVICE_CTRL_GPU_CREATE_2D:

        virtio_gpu_dev->format = _pixel_format_convert((rt_ubase_t)args, RT_TRUE);

        if (virtio_gpu_dev->format == 0 || virtio_gpu_dev->pmode_id == VIRTIO_GPU_INVALID_PMODE_ID)
        {
            status = -RT_ERROR;
            break;
        }

        status = virtio_gpu_create_2d_resource(virtio_gpu_dev, virtio_gpu_dev->format,
                &virtio_gpu_dev->display_resource_id, virtio_gpu_dev->pmode.r.width, virtio_gpu_dev->pmode.r.height);

        if (status != RT_EOK)
        {
            break;
        }

        virtio_gpu_dev->smem_len =
                virtio_gpu_dev->pmode.r.width * virtio_gpu_dev->pmode.r.height * VIRTIO_GPU_FORMAT_PIXEL;
        virtio_gpu_dev->smem_len = RT_ALIGN(virtio_gpu_dev->smem_len, VIRTIO_PAGE_SIZE);
        virtio_gpu_dev->framebuffer = rt_malloc_align(virtio_gpu_dev->smem_len, VIRTIO_PAGE_SIZE);

        if (virtio_gpu_dev->framebuffer == RT_NULL)
        {
            virtio_gpu_unref_resource(virtio_gpu_dev, virtio_gpu_dev->display_resource_id);

            status = -RT_ENOMEM;
            break;
        }

        status = virtio_gpu_attach_backing_resource(virtio_gpu_dev,
                virtio_gpu_dev->display_resource_id, virtio_gpu_dev->framebuffer, virtio_gpu_dev->smem_len);

        if (status != RT_EOK)
        {
            break;
        }

        status = virtio_gpu_set_scanout(virtio_gpu_dev, virtio_gpu_dev->pmode_id, virtio_gpu_dev->display_resource_id,
                virtio_gpu_dev->pmode.r.width, virtio_gpu_dev->pmode.r.height);

        break;
    case VIRTIO_DEVICE_CTRL_CURSOR_SETUP:

        if (virtio_gpu_dev->pmode_id == VIRTIO_GPU_INVALID_PMODE_ID)
        {
            status = -RT_ERROR;
            break;
        }

        rt_mutex_take(&virtio_gpu_dev->ops_mutex, RT_WAITING_FOREVER);

        status = virtio_gpu_create_2d_resource(virtio_gpu_dev, virtio_gpu_dev->format,
                &virtio_gpu_dev->cursor_resource_id, VIRTIO_GPU_CURSOR_WIDTH, VIRTIO_GPU_CURSOR_HEIGHT);

        if (status != RT_EOK)
        {
            goto _cursor_setup_end;
        }

        status = virtio_gpu_cursor_set_img(virtio_gpu_dev, args);

        if (status != RT_EOK)
        {
            goto _cursor_setup_end;
        }

        virtio_gpu_dev->cursor_x = 0;
        virtio_gpu_dev->cursor_y = 0;

        status = virtio_gpu_update_cursor(virtio_gpu_dev, virtio_gpu_dev->pmode_id, virtio_gpu_dev->cursor_resource_id,
            virtio_gpu_dev->cursor_x, virtio_gpu_dev->cursor_y);

        if (status == RT_EOK)
        {
            virtio_gpu_dev->cursor_enable = RT_TRUE;
        }

_cursor_setup_end:
        rt_mutex_release(&virtio_gpu_dev->ops_mutex);

        break;
    case VIRTIO_DEVICE_CTRL_CURSOR_SET_IMG:

        if (virtio_gpu_dev->pmode_id == VIRTIO_GPU_INVALID_PMODE_ID || !virtio_gpu_dev->cursor_enable)
        {
            status = -RT_ERROR;
            break;
        }

        rt_mutex_take(&virtio_gpu_dev->ops_mutex, RT_WAITING_FOREVER);

        status = virtio_gpu_cursor_set_img(virtio_gpu_dev, args);

        if (status != RT_EOK)
        {
            goto _cursor_set_img_end;
        }

        status = virtio_gpu_update_cursor(virtio_gpu_dev, virtio_gpu_dev->pmode_id, virtio_gpu_dev->cursor_resource_id,
            virtio_gpu_dev->cursor_x, virtio_gpu_dev->cursor_y);

_cursor_set_img_end:
        rt_mutex_release(&virtio_gpu_dev->ops_mutex);

        break;
    case VIRTIO_DEVICE_CTRL_CURSOR_MOVE:

        if (virtio_gpu_dev->pmode_id == VIRTIO_GPU_INVALID_PMODE_ID || !virtio_gpu_dev->cursor_enable)
        {
            status = -RT_ERROR;
            break;
        }

        rt_mutex_take(&virtio_gpu_dev->ops_mutex, RT_WAITING_FOREVER);

        virtio_gpu_dev->cursor_x = ((rt_uint32_t *)args)[0];
        virtio_gpu_dev->cursor_y = ((rt_uint32_t *)args)[1];

        status = virtio_gpu_cursor_move(virtio_gpu_dev, virtio_gpu_dev->pmode_id, virtio_gpu_dev->cursor_resource_id,
            virtio_gpu_dev->cursor_x, virtio_gpu_dev->cursor_y);

        rt_mutex_release(&virtio_gpu_dev->ops_mutex);

        break;
    default:
        status = -RT_EINVAL;
        break;
    }

    return status;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops virtio_gpu_ops =
{
    virtio_gpu_init,
    RT_NULL,
    RT_NULL,
    virtio_gpu_read,
    virtio_gpu_write,
    virtio_gpu_control
};
#endif

static void virtio_gpu_set_pixel(const char *pixel, int x, int y)
{
    rt_uint8_t *fb;
    struct virtio_gpu_device *virtio_gpu_dev = _primary_virtio_gpu_dev;

    if (virtio_gpu_dev == RT_NULL || virtio_gpu_dev->pmode_id == VIRTIO_GPU_INVALID_PMODE_ID)
    {
        return;
    }

    fb = (rt_uint8_t *)virtio_gpu_dev->framebuffer;
    fb += (y * virtio_gpu_dev->pmode.r.width + x) * VIRTIO_GPU_FORMAT_PIXEL;
    *((rt_uint32_t *)fb) = *((rt_uint32_t *)pixel);
}

static void virtio_gpu_get_pixel(char *pixel, int x, int y)
{
    rt_uint8_t *fb;
    struct virtio_gpu_device *virtio_gpu_dev = _primary_virtio_gpu_dev;

    if (virtio_gpu_dev == RT_NULL || virtio_gpu_dev->pmode_id == VIRTIO_GPU_INVALID_PMODE_ID)
    {
        return;
    }

    fb = (rt_uint8_t *)virtio_gpu_dev->framebuffer;
    *((rt_uint32_t *)pixel) = *(fb + (y * virtio_gpu_dev->pmode.r.width + x) * VIRTIO_GPU_FORMAT_PIXEL);
}

static void virtio_gpu_draw_hline(const char *pixel, int x1, int x2, int y)
{
    int i;
    rt_uint8_t *fb;
    rt_uint32_t color = *((rt_uint32_t *)pixel);
    struct virtio_gpu_device *virtio_gpu_dev = _primary_virtio_gpu_dev;

    if (virtio_gpu_dev == RT_NULL || virtio_gpu_dev->pmode_id == VIRTIO_GPU_INVALID_PMODE_ID ||
        x1 < 0 || x2 < 0 || y < 0)
    {
        return;
    }

    if (x1 > x2)
    {
        x1 ^= x2;
        x2 ^= x1;
        x1 ^= x2;
    }

    fb = (rt_uint8_t *)virtio_gpu_dev->framebuffer;
    fb += (y * virtio_gpu_dev->pmode.r.width + x1) * VIRTIO_GPU_FORMAT_PIXEL;

    for (i = x1; i < x2; ++i)
    {
        *((rt_uint32_t *)fb) = color;

        fb += VIRTIO_GPU_FORMAT_PIXEL;
    }
}

static void virtio_gpu_draw_vline(const char *pixel, int x, int y1, int y2)
{
    int i;
    rt_uint8_t *fb;
    rt_uint16_t pitch;
    rt_uint32_t color = *((rt_uint32_t *)pixel);
    struct virtio_gpu_device *virtio_gpu_dev = _primary_virtio_gpu_dev;

    if (virtio_gpu_dev == RT_NULL || virtio_gpu_dev->pmode_id == VIRTIO_GPU_INVALID_PMODE_ID ||
        x < 0 || y1 < 0 || y2 < 0)
    {
        return;
    }

    if (y1 > y2)
    {
        y1 ^= y2;
        y2 ^= y1;
        y1 ^= y2;
    }

    fb = (rt_uint8_t *)virtio_gpu_dev->framebuffer;
    fb += (y1 * virtio_gpu_dev->pmode.r.width + x) * VIRTIO_GPU_FORMAT_PIXEL;

    pitch = virtio_gpu_dev->pmode.r.width * VIRTIO_GPU_FORMAT_PIXEL;

    for (i = y1; i < y2; ++i)
    {
        *((rt_uint32_t *)fb) = color;

        fb += pitch;
    }
}

static void virtio_gpu_blit_line(const char *pixel, int x, int y, rt_size_t size)
{
    int i;
    rt_uint8_t *fb;
    rt_uint32_t *colors = (rt_uint32_t *)pixel;
    struct virtio_gpu_device *virtio_gpu_dev = _primary_virtio_gpu_dev;

    if (virtio_gpu_dev == RT_NULL || virtio_gpu_dev->pmode_id == VIRTIO_GPU_INVALID_PMODE_ID || x < 0 || y < 0)
    {
        return;
    }

    fb = (rt_uint8_t *)virtio_gpu_dev->framebuffer;
    fb += (y * virtio_gpu_dev->pmode.r.width + x) * VIRTIO_GPU_FORMAT_PIXEL;

    for (i = 0; i < size; ++i)
    {
        *((rt_uint32_t *)fb) = *colors++;
        fb += VIRTIO_GPU_FORMAT_PIXEL;
    }
}

static struct rt_device_graphic_ops virtio_gpu_graphic_ops =
{
    virtio_gpu_set_pixel,
    virtio_gpu_get_pixel,
    virtio_gpu_draw_hline,
    virtio_gpu_draw_vline,
    virtio_gpu_blit_line
};

static void virtio_gpu_isr(int irqno, void *param)
{
    rt_uint16_t id;
    struct virtio_gpu_device *virtio_gpu_dev = (struct virtio_gpu_device *)param;
    struct virtio_device *virtio_dev = &virtio_gpu_dev->virtio_dev;
    struct virtq *queue_ctrl = &virtio_dev->queues[VIRTIO_GPU_QUEUE_CTRL];
    struct virtq *queue_cursor = &virtio_dev->queues[VIRTIO_GPU_QUEUE_CURSOR];

#ifdef RT_USING_SMP
    rt_base_t level = rt_spin_lock_irqsave(&virtio_dev->spinlock);
#endif

    virtio_interrupt_ack(virtio_dev);
    rt_hw_dsb();

    while (queue_ctrl->used_idx != queue_ctrl->used->idx)
    {
        rt_hw_dsb();
        id = queue_ctrl->used->ring[queue_ctrl->used_idx % queue_ctrl->num].id;

        virtio_gpu_dev->info[id].ctrl_valid = RT_FALSE;

        queue_ctrl->used_idx++;
    }

    while (queue_cursor->used_idx != queue_cursor->used->idx)
    {
        rt_hw_dsb();
        id = queue_cursor->used->ring[queue_cursor->used_idx % queue_cursor->num].id;

        virtio_gpu_dev->info[id].cursor_valid = RT_FALSE;

        queue_cursor->used_idx++;
    }

#ifdef RT_USING_SMP
    rt_spin_unlock_irqrestore(&virtio_dev->spinlock, level);
#endif
}

rt_err_t rt_virtio_gpu_init(rt_ubase_t *mmio_base, rt_uint32_t irq)
{
    static int dev_no = 0;
    char dev_name[RT_NAME_MAX];
    struct virtio_device *virtio_dev;
    struct virtio_gpu_device *virtio_gpu_dev;

    virtio_gpu_dev = rt_malloc(sizeof(struct virtio_gpu_device));

    if (virtio_gpu_dev == RT_NULL)
    {
        goto _alloc_fail;
    }

    virtio_dev = &virtio_gpu_dev->virtio_dev;
    virtio_dev->irq = irq;
    virtio_dev->mmio_base = mmio_base;

    virtio_gpu_dev->pmode_id = VIRTIO_GPU_INVALID_PMODE_ID;
    virtio_gpu_dev->display_resource_id = 0;
    virtio_gpu_dev->cursor_resource_id = 0;
    virtio_gpu_dev->next_resource_id = 0;
    virtio_gpu_dev->framebuffer = RT_NULL;
    virtio_gpu_dev->smem_len = 0;
    virtio_gpu_dev->cursor_enable = RT_FALSE;

#ifdef RT_USING_SMP
    rt_spin_lock_init(&virtio_dev->spinlock);
#endif

    virtio_reset_device(virtio_dev);
    virtio_status_acknowledge_driver(virtio_dev);

    virtio_dev->mmio_config->driver_features = virtio_dev->mmio_config->device_features & ~(
            (1 << VIRTIO_F_RING_EVENT_IDX) |
            (1 << VIRTIO_F_RING_INDIRECT_DESC));

    virtio_status_driver_ok(virtio_dev);

    if (virtio_queues_alloc(virtio_dev, 2) != RT_EOK)
    {
        goto _alloc_fail;
    }

    if (virtio_queue_init(virtio_dev, VIRTIO_GPU_QUEUE_CTRL, VIRTIO_GPU_QUEUE_SIZE) != RT_EOK)
    {
        goto _alloc_fail;
    }

    if (virtio_queue_init(virtio_dev, VIRTIO_GPU_QUEUE_CURSOR, VIRTIO_GPU_QUEUE_SIZE) != RT_EOK)
    {
        virtio_queue_destroy(virtio_dev, VIRTIO_GPU_QUEUE_CTRL);

        goto _alloc_fail;
    }

    virtio_gpu_dev->parent.type = RT_Device_Class_Graphic;
#ifdef RT_USING_DEVICE_OPS
    virtio_gpu_dev->parent.ops = &virtio_gpu_ops;
#else
    virtio_gpu_dev->parent.init     = virtio_gpu_init;
    virtio_gpu_dev->parent.open     = RT_NULL;
    virtio_gpu_dev->parent.close    = RT_NULL;
    virtio_gpu_dev->parent.read     = virtio_gpu_read;
    virtio_gpu_dev->parent.write    = virtio_gpu_write;
    virtio_gpu_dev->parent.control  = virtio_gpu_control;
#endif
    virtio_gpu_dev->parent.user_data = &virtio_gpu_graphic_ops;

    rt_snprintf(dev_name, RT_NAME_MAX, "virtio-gpu%d", dev_no++);

    rt_mutex_init(&virtio_gpu_dev->rw_mutex, dev_name, RT_IPC_FLAG_PRIO);
    rt_mutex_init(&virtio_gpu_dev->ops_mutex, dev_name, RT_IPC_FLAG_PRIO);

    rt_hw_interrupt_install(irq, virtio_gpu_isr, virtio_gpu_dev, dev_name);
    rt_hw_interrupt_umask(irq);

    return rt_device_register((rt_device_t)virtio_gpu_dev, dev_name, RT_DEVICE_FLAG_RDWR);

_alloc_fail:

    if (virtio_gpu_dev != RT_NULL)
    {
        virtio_queues_free(virtio_dev);
        rt_free(virtio_gpu_dev);
    }
    return -RT_ENOMEM;
}
#endif /* RT_USING_VIRTIO_GPU */
