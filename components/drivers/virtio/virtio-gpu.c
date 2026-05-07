/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 * 2023-02-25     GuEe-GUI     using virtio dm
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "virtio.dev.gpu"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mmu.h>
#include <cpuport.h>
#include "virtio_internal.h"
#include "virtio_config/virtio-gpu.h"

#define CTRL_QUEUE      0
#define CURSOR_QUEUE    1

struct virtio_gpu
{
    struct rt_graphic_device parent;
    struct rt_virtio_device *vdev;

    struct rt_virtqueue *vqs[2];

    rt_bool_t vsync;
    rt_uint32_t width;
    rt_uint32_t height;
    rt_uint32_t pmode_id;
    rt_uint32_t num_scanouts;
    rt_uint32_t resource_id;
#define PRIMARY_PLANE_RESOURCE_ID   1
#define CURSOR_PLANE_RESOURCE_ID    2

    struct rt_work event_work;
    struct rt_completion done;

#define CURSOR_WIDTH    64
#define CURSOR_HEIGHT   64
    rt_uint8_t *cursor;
};

#define raw_to_virtio_gpu(raw) rt_container_of(raw, struct virtio_gpu, parent)

static void virtio_gpu_ctrl_send_command(struct virtio_gpu *vgpu,
        const void *cmd, rt_size_t cmd_len, void *res, rt_size_t res_len)
{
    struct rt_virtqueue *vq;

    vq = vgpu->vqs[CTRL_QUEUE];

    rt_virtqueue_wait_prepare(vq, 2);

    rt_virtqueue_add_outbuf(vq, (void *)cmd, cmd_len);
    rt_virtqueue_add_inbuf(vq, res, res_len);

    rt_virtqueue_kick(vq);

    while (!rt_virtqueue_read_buf(vq, RT_NULL))
    {
        rt_hw_cpu_relax();
    }
}

static void virtio_gpu_cursor_send_command(struct virtio_gpu *vgpu,
        const void *cmd, rt_size_t cmd_len)
{
    struct rt_virtqueue *vq;

    vq = vgpu->vqs[CURSOR_QUEUE];

    rt_virtqueue_wait_prepare(vq, 1);

    rt_virtqueue_add_outbuf(vq, (void *)cmd, cmd_len);

    rt_virtqueue_kick(vq);

    while (!rt_virtqueue_read_buf(vq, RT_NULL))
    {
        rt_hw_cpu_relax();
    }
}

static rt_uint32_t virtio_gpu_next_resource_id(struct virtio_gpu *vgpu)
{
    rt_uint32_t last_resource_id = vgpu->resource_id++;

    while (last_resource_id != vgpu->resource_id)
    {
        if (vgpu->resource_id &&
            vgpu->resource_id == PRIMARY_PLANE_RESOURCE_ID &&
            vgpu->resource_id == CURSOR_PLANE_RESOURCE_ID)
        {
            return vgpu->resource_id;
        }

        ++vgpu->resource_id;
    }

    return 0;
}

static rt_err_t virtio_gpu_create_2d_resource(struct virtio_gpu *vgpu,
        enum virtio_gpu_formats format, rt_uint32_t resource_id,
        rt_uint32_t width, rt_uint32_t height)
{
    struct virtio_gpu_ctrl_hdr res;
    struct virtio_gpu_resource_create_2d req;

    req.hdr.type = rt_cpu_to_le32(VIRTIO_GPU_CMD_RESOURCE_CREATE_2D);
    req.resource_id = rt_cpu_to_le32(resource_id);
    req.format = rt_cpu_to_le32(format);
    req.width = rt_cpu_to_le32(width);
    req.height = rt_cpu_to_le32(height);

    virtio_gpu_ctrl_send_command(vgpu, &req, sizeof(req), &res, sizeof(res));

    return res.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_NODATA) ? RT_EOK : -RT_ERROR;
}

static rt_err_t virtio_gpu_unref_resource(struct virtio_gpu *vgpu,
        rt_uint32_t resource_id)
{
    struct virtio_gpu_ctrl_hdr res;
    struct virtio_gpu_resource_unref req;

    rt_memset(&req, 0, sizeof(req));

    req.hdr.type = rt_cpu_to_le32(VIRTIO_GPU_CMD_RESOURCE_UNREF);
    req.resource_id = rt_cpu_to_le32(resource_id);

    virtio_gpu_ctrl_send_command(vgpu, &req, sizeof(req), &res, sizeof(res));

    return res.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_NODATA) ? RT_EOK : -RT_ERROR;
}

static rt_err_t virtio_gpu_attach_backing_resource(struct virtio_gpu *vgpu,
        rt_uint32_t resource_id, void *buffer, rt_size_t size)
{
    struct virtio_gpu_ctrl_hdr res;
    struct
    {
        struct virtio_gpu_resource_attach_backing req;
        struct virtio_gpu_mem_entry mem;
    } req;

    rt_memset(&req, 0, sizeof(req));

    req.req.hdr.type = rt_cpu_to_le32(VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING);
    req.req.resource_id = rt_cpu_to_le32(resource_id);
    req.req.nr_entries = rt_cpu_to_le32(1);

    req.mem.addr = rt_cpu_to_le64((rt_ubase_t)rt_kmem_v2p(buffer));
    req.mem.length = rt_cpu_to_le32(size);

    virtio_gpu_ctrl_send_command(vgpu, &req, sizeof(req), &res, sizeof(res));

    return res.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_NODATA) ? RT_EOK : -RT_ERROR;
}

static rt_err_t virtio_gpu_detach_backing_resource(struct virtio_gpu *vgpu,
        rt_uint32_t resource_id)
{
    struct virtio_gpu_ctrl_hdr res;
    struct virtio_gpu_resource_detach_backing req;

    rt_memset(&req, 0, sizeof(req));

    req.hdr.type = rt_cpu_to_le32(VIRTIO_GPU_CMD_RESOURCE_DETACH_BACKING);
    req.resource_id = rt_cpu_to_le32(resource_id);

    virtio_gpu_ctrl_send_command(vgpu, &req, sizeof(req), &res, sizeof(res));

    return res.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_NODATA) ? RT_EOK : -RT_ERROR;
}

static rt_err_t virtio_gpu_set_scanout(struct virtio_gpu *vgpu,
        rt_uint32_t scanout_id, rt_uint32_t resource_id,
        rt_uint32_t width, rt_uint32_t height)
{
    struct virtio_gpu_ctrl_hdr res;
    struct virtio_gpu_set_scanout req;

    rt_memset(&req, 0, sizeof(req));

    req.hdr.type = rt_cpu_to_le32(VIRTIO_GPU_CMD_SET_SCANOUT);
    req.r.width = rt_cpu_to_le32(width);
    req.r.height = rt_cpu_to_le32(height);
    req.scanout_id = rt_cpu_to_le32(scanout_id);
    req.resource_id = rt_cpu_to_le32(resource_id);

    virtio_gpu_ctrl_send_command(vgpu, &req, sizeof(req), &res, sizeof(res));

    return res.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_NODATA) ? RT_EOK : -RT_ERROR;
}

static rt_err_t virtio_gpu_flush_resource(struct virtio_gpu *vgpu,
        rt_uint32_t resource_id,
        rt_uint32_t x, rt_uint32_t y, rt_uint32_t width, rt_uint32_t height)
{
    struct virtio_gpu_ctrl_hdr res;
    struct virtio_gpu_resource_flush req;

    rt_memset(&req, 0, sizeof(req));

    req.hdr.type = rt_cpu_to_le32(VIRTIO_GPU_CMD_RESOURCE_FLUSH);
    req.r.x = rt_cpu_to_le32(x);
    req.r.y = rt_cpu_to_le32(y);
    req.r.width = rt_cpu_to_le32(width);
    req.r.height = rt_cpu_to_le32(height);
    req.resource_id = rt_cpu_to_le32(resource_id);

    virtio_gpu_ctrl_send_command(vgpu, &req, sizeof(req), &res, sizeof(res));

    return res.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_NODATA) ? RT_EOK : -RT_ERROR;
}

static rt_err_t virtio_gpu_transfer_to_host_2d(struct virtio_gpu *vgpu,
        rt_uint32_t resource_id,
        rt_uint32_t x, rt_uint32_t y, rt_uint32_t width, rt_uint32_t height,
        rt_uint64_t offset)
{
    struct virtio_gpu_ctrl_hdr res;
    struct virtio_gpu_transfer_to_host_2d req;

    rt_memset(&req, 0, sizeof(req));

    req.hdr.type = rt_cpu_to_le32(VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D);
    req.r.x = rt_cpu_to_le32(x);
    req.r.y = rt_cpu_to_le32(y);
    req.r.width = rt_cpu_to_le32(width);
    req.r.height = rt_cpu_to_le32(height);
    req.offset = rt_cpu_to_le64(offset);
    req.resource_id = rt_cpu_to_le32(resource_id);

    virtio_gpu_ctrl_send_command(vgpu, &req, sizeof(req), &res, sizeof(res));

    return res.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_NODATA) ? RT_EOK : -RT_ERROR;
}

static rt_err_t virtio_gpu_update_cursor(struct virtio_gpu *vgpu,
        rt_uint32_t scanout_id, rt_uint32_t resource_id,
        rt_uint32_t hot_x, rt_uint32_t hot_y)
{
    struct virtio_gpu_update_cursor req;

    rt_memset(&req, 0, sizeof(req));

    req.hdr.type = rt_cpu_to_le32(VIRTIO_GPU_CMD_UPDATE_CURSOR);
    req.pos.scanout_id = rt_cpu_to_le32(scanout_id);
    req.resource_id = rt_cpu_to_le32(resource_id);
    req.hot_x = rt_cpu_to_le32(hot_x);
    req.hot_y = rt_cpu_to_le32(hot_y);

    virtio_gpu_cursor_send_command(vgpu, &req, sizeof(req));

    return RT_EOK;
}

static rt_err_t virtio_gpu_cursor_move(struct virtio_gpu *vgpu,
        rt_uint32_t scanout_id, rt_uint32_t resource_id,
        rt_uint32_t x, rt_uint32_t y)
{
    struct virtio_gpu_update_cursor req;

    rt_memset(&req, 0, sizeof(req));

    req.hdr.type = rt_cpu_to_le32(VIRTIO_GPU_CMD_MOVE_CURSOR);
    req.pos.scanout_id = rt_cpu_to_le32(scanout_id);
    req.pos.x = rt_cpu_to_le32(x);
    req.pos.y = rt_cpu_to_le32(y);
    req.resource_id = rt_cpu_to_le32(resource_id);

    virtio_gpu_cursor_send_command(vgpu, &req, sizeof(req));

    return RT_EOK;
}

static rt_err_t virtio_gpu_get_edid(struct virtio_gpu *vgpu)
{
    rt_err_t err;
    struct virtio_gpu_cmd_get_edid req;
    struct virtio_gpu_resp_edid *res = rt_malloc(sizeof(*res));

    if (!res)
    {
        return -RT_ENOMEM;
    }

    rt_memset(&req, 0, sizeof(req));
    req.hdr.type = rt_cpu_to_le32(VIRTIO_GPU_CMD_GET_EDID);
    req.scanout = rt_cpu_to_le32(vgpu->pmode_id);

    virtio_gpu_ctrl_send_command(vgpu, &req, sizeof(req), res, sizeof(*res));

    if (res->hdr.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_EDID))
    {
        rt_memcpy(&vgpu->parent.edid, res->edid,
                rt_min_t(rt_size_t, sizeof(vgpu->parent.edid), res->size));
        err = RT_EOK;
    }
    else
    {
        err = -RT_EIO;
    }

    rt_free(res);

    return err;
}

static rt_err_t virtio_gpu_get_display_info(struct virtio_gpu *vgpu)
{
    struct virtio_gpu_ctrl_hdr req;
    struct virtio_gpu_resp_display_info info;

    rt_memset(&req, 0, sizeof(req));
    req.type = rt_cpu_to_le32(VIRTIO_GPU_CMD_GET_DISPLAY_INFO);

    virtio_gpu_ctrl_send_command(vgpu, &req, sizeof(req), &info, sizeof(info));

    if (info.hdr.type != rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_DISPLAY_INFO))
    {
        return -RT_EIO;
    }

    for (int i = 0; i < vgpu->num_scanouts; ++i)
    {
        if (info.pmodes[i].enabled)
        {
            struct virtio_gpu_display_one *pmode = &info.pmodes[i];

            vgpu->pmode_id = i;
            vgpu->width = pmode->r.width;
            vgpu->height = pmode->r.height;
            break;
        }
    }

    return RT_EOK;
}

static rt_err_t virtio_gpu_resize(struct virtio_gpu *vgpu)
{
    rt_err_t err = RT_EOK;

    if (rt_virtio_has_feature(vgpu->vdev, VIRTIO_GPU_F_EDID))
    {
        err = virtio_gpu_get_edid(vgpu);
    }

    if (!err)
    {
        err = virtio_gpu_get_display_info(vgpu);
    }

    return err;
}

static enum virtio_gpu_formats virtio_gpu_raw_modes[] =
{
    VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM,
    VIRTIO_GPU_FORMAT_R8G8B8A8_UNORM,
};

static rt_uint32_t virtio_gpu_modes[] =
{
    RTGRAPHIC_PIXEL_FORMAT_ARGB888,
    RTGRAPHIC_PIXEL_FORMAT_ABGR888,
};

typedef char __assert_virtio_gpu_modes[-(RT_ARRAY_SIZE(virtio_gpu_raw_modes) % RT_ARRAY_SIZE(virtio_gpu_modes))];

static enum virtio_gpu_formats virtio_gpu_mode(rt_uint32_t mode)
{
    for (int i = 0; i < RT_ARRAY_SIZE(virtio_gpu_modes); ++i)
    {
        if (virtio_gpu_modes[i] == mode)
        {
            return virtio_gpu_raw_modes[i];
        }
    }

    LOG_E("BUG of the graphic framework");
    RT_ASSERT(0);
    return -1;
}

static rt_err_t virtio_gpu_cursor_plane_fb_update(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    rt_err_t err;
    rt_uint32_t resource_id;
    struct virtio_gpu *vgpu = raw_to_virtio_gpu(plane->graphic);

    if (!rect->width && !rect->height)
    {
        return RT_EOK;
    }

    if (rect->width > CURSOR_WIDTH || rect->height > CURSOR_HEIGHT)
    {
        return -RT_EINVAL;
    }

    resource_id = CURSOR_PLANE_RESOURCE_ID;

    err = virtio_gpu_transfer_to_host_2d(vgpu, resource_id,
            rect->x, rect->y, rect->width, rect->height, 0);

    if (!err)
    {
        err = virtio_gpu_flush_resource(vgpu, resource_id,
                rect->x, rect->y, rect->width, rect->height);
    }

    virtio_gpu_update_cursor(vgpu, vgpu->pmode_id, resource_id, rect->x, rect->y);
    virtio_gpu_cursor_move(vgpu, vgpu->pmode_id, resource_id, rect->x, rect->y);

    return err;
}

static rt_err_t virtio_gpu_cursor_plane_fb_remap(struct rt_graphic_plane *plane,
        rt_uint32_t mode, struct rt_device_rect_info *rect)
{
    rt_err_t err;
    rt_uint32_t framebuffer_len, bits_per_pixel, line_length, resource_id;
    struct virtio_gpu *vgpu = raw_to_virtio_gpu(plane->graphic);

    if (rect->width > CURSOR_WIDTH || rect->height > CURSOR_HEIGHT)
    {
        return -RT_EINVAL;
    }

    resource_id = CURSOR_PLANE_RESOURCE_ID;

    err = virtio_gpu_create_2d_resource(vgpu, virtio_gpu_mode(mode),
            resource_id, rect->width, rect->height);

    if (err)
    {
        return err;
    }

    bits_per_pixel = rt_graphic_mode_bpp(mode);
    line_length = rect->width * (bits_per_pixel / 8);

    framebuffer_len = line_length * rect->height;

    err = virtio_gpu_attach_backing_resource(vgpu, resource_id, vgpu->cursor, framebuffer_len);

    if (err)
    {
        goto _unref_resource;
    }

    plane->line_length = line_length;
    plane->bits_per_pixel = bits_per_pixel;

    plane->framebuffer = vgpu->cursor;
    plane->screen_len = framebuffer_len;
    plane->framebuffer_len = framebuffer_len;

    return RT_EOK;

_unref_resource:
    virtio_gpu_unref_resource(vgpu, resource_id);

    return err;
}

static rt_err_t virtio_gpu_cursor_plane_fb_cleanup(struct rt_graphic_plane *plane)
{
    rt_uint32_t resource_id;
    struct virtio_gpu *vgpu = raw_to_virtio_gpu(plane->graphic);

    if (!plane->framebuffer)
    {
        return RT_EOK;
    }

    resource_id = CURSOR_PLANE_RESOURCE_ID;

    virtio_gpu_detach_backing_resource(vgpu, resource_id);
    virtio_gpu_unref_resource(vgpu, resource_id);

    plane->framebuffer = RT_NULL;

    return RT_EOK;
}

static const struct rt_graphic_plane_ops virtio_gpu_cursor_plane_ops =
{
    .update = virtio_gpu_cursor_plane_fb_update,
    .fb_remap = virtio_gpu_cursor_plane_fb_remap,
    .fb_cleanup = virtio_gpu_cursor_plane_fb_cleanup,
};

static rt_err_t virtio_gpu_primary_plane_fb_update(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    rt_err_t err;
    rt_uint32_t resource_id;
    struct virtio_gpu *vgpu = raw_to_virtio_gpu(plane->graphic);

    vgpu->vsync = RT_FALSE;
    resource_id = PRIMARY_PLANE_RESOURCE_ID;

    err = virtio_gpu_transfer_to_host_2d(vgpu, resource_id,
            rect->x, rect->y, rect->width, rect->height, 0);

    if (!err)
    {
        err = virtio_gpu_flush_resource(vgpu, resource_id,
                rect->x, rect->y, rect->width, rect->height);
    }
    vgpu->vsync = RT_TRUE;

    return err;
}

static rt_err_t virtio_gpu_primary_plane_fb_remap(struct rt_graphic_plane *plane,
        rt_uint32_t mode, struct rt_device_rect_info *rect)
{
    rt_err_t err;
    void *framebuffer;
    rt_uint32_t framebuffer_len, bits_per_pixel, line_length, resource_id;
    struct virtio_gpu *vgpu = raw_to_virtio_gpu(plane->graphic);

    resource_id = PRIMARY_PLANE_RESOURCE_ID;
    err = virtio_gpu_create_2d_resource(vgpu, virtio_gpu_mode(mode),
            resource_id, rect->width, rect->height);

    if (err)
    {
        return err;
    }

    bits_per_pixel = rt_graphic_mode_bpp(mode);
    line_length = rect->width * (bits_per_pixel / 8);

    framebuffer_len = line_length * rect->height;
    framebuffer = rt_malloc_align(framebuffer_len, ARCH_PAGE_SIZE);

    if (!framebuffer)
    {
        err = -RT_ENOMEM;
        goto _unref_resource;
    }

    err = virtio_gpu_attach_backing_resource(vgpu, resource_id, framebuffer, framebuffer_len);

    if (err)
    {
        goto _free_framebuffer;
    }

    err = virtio_gpu_set_scanout(vgpu, vgpu->pmode_id, resource_id,
            rect->width, rect->height);

    if (err)
    {
        goto _detach_backing;
    }

    plane->line_length = line_length;
    plane->bits_per_pixel = bits_per_pixel;

    plane->framebuffer = framebuffer;
    plane->screen_len = framebuffer_len;
    plane->framebuffer_len = framebuffer_len;

    return RT_EOK;

_detach_backing:
    virtio_gpu_detach_backing_resource(vgpu, resource_id);

_free_framebuffer:
    rt_free_align(framebuffer);

_unref_resource:
    virtio_gpu_unref_resource(vgpu, resource_id);

    return err;
}

static rt_err_t virtio_gpu_primary_plane_fb_cleanup(struct rt_graphic_plane *plane)
{
    rt_uint32_t resource_id;
    struct virtio_gpu *vgpu = raw_to_virtio_gpu(plane->graphic);

    if (!plane->framebuffer)
    {
        return RT_EOK;
    }

    resource_id = PRIMARY_PLANE_RESOURCE_ID;

    virtio_gpu_detach_backing_resource(vgpu, resource_id);
    virtio_gpu_unref_resource(vgpu, resource_id);
    rt_free_align(plane->framebuffer);

    plane->framebuffer = RT_NULL;

    return RT_EOK;
}

static const struct rt_graphic_plane_ops virtio_gpu_primary_plane_ops =
{
    .update = virtio_gpu_primary_plane_fb_update,
    .fb_remap = virtio_gpu_primary_plane_fb_remap,
    .fb_cleanup = virtio_gpu_primary_plane_fb_cleanup,
};

static rt_err_t virtio_gpu_dpms_switch(struct rt_graphic_device *gdev, rt_uint32_t dpms)
{
    rt_uint32_t update_ms = 0;
    struct virtio_gpu *vgpu = raw_to_virtio_gpu(gdev);

    if (dpms == RT_GRAPHIC_DPMS_ON)
    {
        update_ms = RT_GRAPHIC_UPDATE_MS;
    }

    rt_graphic_device_update_auto(&vgpu->parent, update_ms);

    return RT_EOK;
}

static rt_err_t virtio_gpu_wait_vsync(struct rt_graphic_device *gdev)
{
    struct virtio_gpu *vgpu = raw_to_virtio_gpu(gdev);

    while (!vgpu->vsync)
    {
        rt_hw_cpu_relax();
    }

    return RT_EOK;
}

static rt_err_t virtio_gpu_virgl_control(struct rt_graphic_device *gdev, int cmd, void *args)
{
    rt_err_t err;
    struct virtio_gpu *vgpu = raw_to_virtio_gpu(gdev);

    switch (cmd)
    {
    case VIRTIO_GPU_CMD_GET_CAPSET_INFO:
    {
        struct virtio_gpu_get_capset_info req;
        struct virtio_gpu_resp_capset_info *res = args;

        rt_memcpy(&req, args, sizeof(req));

        virtio_gpu_ctrl_send_command(vgpu, &req, sizeof(req), res, sizeof(*res));

        err = res->hdr.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_CAPSET_INFO) ? RT_EOK : -RT_ERROR;
        break;
    }

    case VIRTIO_GPU_CMD_GET_CAPSET:
    {
        struct virtio_gpu_get_capset req;
        struct virtio_gpu_resp_capset *res = args;

        rt_memcpy(&req, args, sizeof(req));

        virtio_gpu_ctrl_send_command(vgpu, &req, sizeof(req), res, sizeof(*res));

        err = res->hdr.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_CAPSET) ? RT_EOK : -RT_ERROR;
        break;
    }

    case VIRTIO_GPU_CMD_CTX_CREATE:
    {
        struct virtio_gpu_ctrl_hdr res;
        struct virtio_gpu_ctx_create *req = args;

        virtio_gpu_ctrl_send_command(vgpu, req, sizeof(*req), &res, sizeof(res));

        rt_memcpy(args, &res, sizeof(res));
        err = res.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_NODATA) ? RT_EOK : -RT_ERROR;
        break;
    }

    case VIRTIO_GPU_CMD_CTX_DESTROY:
    {
        struct virtio_gpu_ctrl_hdr res;
        struct virtio_gpu_ctx_destroy *req = args;

        virtio_gpu_ctrl_send_command(vgpu, req, sizeof(*req), &res, sizeof(res));

        rt_memcpy(args, &res, sizeof(res));
        err = res.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_NODATA) ? RT_EOK : -RT_ERROR;
        break;
    }

    case VIRTIO_GPU_CMD_CTX_ATTACH_RESOURCE:
    {
        struct virtio_gpu_ctrl_hdr res;
        struct virtio_gpu_ctx_resource *req = args;

        virtio_gpu_ctrl_send_command(vgpu, req, sizeof(*req), &res, sizeof(res));

        rt_memcpy(args, &res, sizeof(res));
        err = res.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_NODATA) ? RT_EOK : -RT_ERROR;
        break;
    }

    case VIRTIO_GPU_CMD_CTX_DETACH_RESOURCE:
    {
        struct virtio_gpu_ctrl_hdr res;
        struct virtio_gpu_ctx_resource *req = args;

        virtio_gpu_ctrl_send_command(vgpu, req, sizeof(*req), &res, sizeof(res));

        rt_memcpy(args, &res, sizeof(res));
        err = res.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_NODATA) ? RT_EOK : -RT_ERROR;
        break;
    }

    case VIRTIO_GPU_CMD_RESOURCE_CREATE_3D:
    {
        struct virtio_gpu_ctrl_hdr res;
        struct virtio_gpu_resource_create_3d *req = args;

        /*
         * Create a new resource id instead of user's. Because the
         * `virtio_gpu_resource_create_3d` is base on the `virtio_gpu_ctrl_hdr`,
         * user should pick the resource_id by res after request.
         */
        req->resource_id = virtio_gpu_next_resource_id(vgpu);

        virtio_gpu_ctrl_send_command(vgpu, req, sizeof(*req), &res, sizeof(res));

        rt_memcpy(args, &res, sizeof(res));
        err = res.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_NODATA) ? RT_EOK : -RT_ERROR;
        break;
    }

    case VIRTIO_GPU_CMD_TRANSFER_TO_HOST_3D:
    {
        struct virtio_gpu_ctrl_hdr res;
        struct virtio_gpu_transfer_host_3d *req = args;

        virtio_gpu_ctrl_send_command(vgpu, req, sizeof(*req), &res, sizeof(res));

        rt_memcpy(args, &res, sizeof(res));
        err = res.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_NODATA) ? RT_EOK : -RT_ERROR;
        break;
    }

    case VIRTIO_GPU_CMD_TRANSFER_FROM_HOST_3D:
    {
        struct virtio_gpu_ctrl_hdr res;
        struct virtio_gpu_transfer_host_3d *req = args;

        virtio_gpu_ctrl_send_command(vgpu, req, sizeof(*req), &res, sizeof(res));

        rt_memcpy(args, &res, sizeof(res));
        err = res.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_NODATA) ? RT_EOK : -RT_ERROR;
        break;
    }

    case VIRTIO_GPU_CMD_SUBMIT_3D:
    {
        struct virtio_gpu_ctrl_hdr res;
        struct virtio_gpu_cmd_submit *req = args;

        virtio_gpu_ctrl_send_command(vgpu, req, req->size, &res, sizeof(res));

        rt_memcpy(args, &res, sizeof(res));
        err = res.type == rt_cpu_to_le32(VIRTIO_GPU_RESP_OK_NODATA) ? RT_EOK : -RT_ERROR;
        break;
    }

    default:
        err = -RT_ENOSYS;
        break;
    }

    return err;
}

static const struct rt_graphic_device_ops virtio_gpu_virgl_ops =
{
    .dpms_switch = virtio_gpu_dpms_switch,
    .wait_vsync = virtio_gpu_wait_vsync,
    .control = virtio_gpu_virgl_control,
};

static const struct rt_graphic_device_ops virtio_gpu_ops =
{
    .dpms_switch = virtio_gpu_dpms_switch,
    .wait_vsync = virtio_gpu_wait_vsync,
};

static void virtio_gpu_event_work(struct rt_work *work, void *work_data)
{
    rt_uint32_t events_read, events_clear = 0;
    struct virtio_gpu *vgpu = work_data;
    struct rt_virtio_device *vdev = vgpu->vdev;

    rt_virtio_read_config(vdev, struct virtio_gpu_config, events_read, &events_read);

    if (events_read & VIRTIO_GPU_EVENT_DISPLAY)
    {
        rt_graphic_device_enter(&vgpu->parent);
        virtio_gpu_resize(vgpu);
        rt_graphic_device_leave(&vgpu->parent);

        rt_graphic_device_hotplug_event(&vgpu->parent);

        events_clear |= VIRTIO_GPU_EVENT_DISPLAY;
    }

    rt_virtio_write_config(vdev, struct virtio_gpu_config, events_clear, events_clear);
}

static void virtio_gpu_config_changed(struct rt_virtio_device *vdev)
{
    struct virtio_gpu *vgpu = vdev->priv;

    rt_work_submit(&vgpu->event_work, 0);
}

static rt_err_t virtio_gpu_vq_init(struct virtio_gpu *vgpu)
{
    const char *names[] =
    {
        "ctrl",
        "cursor"
    };
    rt_virtqueue_callback cbs[] =
    {
        RT_NULL,    /* Just poll */
        RT_NULL,    /* Just poll */
    };

    return rt_virtio_virtqueue_install(vgpu->vdev,
            RT_ARRAY_SIZE(names), vgpu->vqs, names, cbs);
}

static void virtio_gpu_vq_finit(struct virtio_gpu *vgpu)
{
    if (vgpu->vqs[0])
    {
        rt_virtio_virtqueue_release(vgpu->vdev);
    }
}

static void virtio_gpu_unregister(struct virtio_gpu *vgpu)
{
    if (rt_virtio_has_feature(vgpu->vdev, VIRTIO_GPU_F_EDID))
    {
        rt_graphic_device_unregister(&vgpu->parent);
    }
    else
    {
        rt_graphic_device_simple_unregister(&vgpu->parent);
    }
}

static rt_err_t virtio_gpu_probe(struct rt_virtio_device *vdev)
{
    rt_err_t err;
    struct rt_graphic_plane *primary_plane, *cursor_plane;
    struct virtio_gpu *vgpu = rt_calloc(1, sizeof(*vgpu));

    if (!vgpu)
    {
        return -RT_ENOMEM;
    }

    vdev->priv = vgpu;
    vgpu->vdev = vdev;

    vgpu->cursor = rt_malloc_align(
            CURSOR_WIDTH * CURSOR_HEIGHT * sizeof(rt_uint32_t), ARCH_PAGE_SIZE);

    if (!vgpu->cursor)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    if ((err = virtio_gpu_vq_init(vgpu)))
    {
        goto _fail;
    }

    vgpu->vsync = RT_TRUE;

    rt_virtio_read_config(vdev, struct virtio_gpu_config, num_scanouts, &vgpu->num_scanouts);

    rt_work_init(&vgpu->event_work, virtio_gpu_event_work, vgpu);

    virtio_gpu_resize(vgpu);

    if (rt_virtio_has_feature(vdev, VIRTIO_GPU_F_VIRGL))
    {
        vgpu->parent.ops = &virtio_gpu_virgl_ops;
    }
    else
    {
        vgpu->parent.ops = &virtio_gpu_ops;
    }

    if (rt_virtio_has_feature(vdev, VIRTIO_GPU_F_EDID))
    {
        primary_plane = rt_graphic_device_alloc_plane(&vgpu->parent, 0,
                &virtio_gpu_primary_plane_ops,
                virtio_gpu_modes, RT_ARRAY_SIZE(virtio_gpu_modes),
                RT_GRAPHIC_PLANE_TYPE_PRIMARY);

        if (!primary_plane)
        {
            err = -RT_EIO;
            goto _fail;
        }

        if ((err = rt_graphic_device_add_plane(&vgpu->parent, primary_plane)))
        {
            goto _free_primary_plane;
        }

        err = rt_graphic_device_register(&vgpu->parent);
    }
    else
    {
        err = rt_graphic_device_simple_register(&vgpu->parent,
                vgpu->width, vgpu->height, 0, &virtio_gpu_primary_plane_ops,
                virtio_gpu_modes, RT_ARRAY_SIZE(virtio_gpu_modes));
    }

    if (err)
    {
        goto _fail;
    }

    cursor_plane = rt_graphic_device_alloc_plane(&vgpu->parent, 0,
            &virtio_gpu_cursor_plane_ops,
            virtio_gpu_modes, RT_ARRAY_SIZE(virtio_gpu_modes),
            RT_GRAPHIC_PLANE_TYPE_CURSOR);

    if (!cursor_plane)
    {
        err = -RT_EIO;
        goto _fail;
    }

    if ((err = rt_graphic_device_add_plane(&vgpu->parent, cursor_plane)))
    {
        goto _free_cursor_plane;
    }

    cursor_plane->width = CURSOR_WIDTH;
    cursor_plane->height = CURSOR_HEIGHT;

    return RT_EOK;

_free_cursor_plane:
    virtio_gpu_unregister(vgpu);
    rt_graphic_device_free_plane(cursor_plane);

_free_primary_plane:
    rt_graphic_device_free_plane(primary_plane);

_fail:
    virtio_gpu_vq_finit(vgpu);

    if (vgpu->cursor)
    {
        rt_free_align(vgpu->cursor);
    }
    rt_free(vgpu);

    return err;
}

static rt_err_t virtio_gpu_remove(struct rt_virtio_device *vdev)
{
    struct virtio_gpu *vgpu = vdev->parent.user_data;

    virtio_gpu_unregister(vgpu);
    virtio_gpu_vq_finit(vgpu);
    rt_free_align(vgpu->cursor);
    rt_free(vgpu);

    return RT_EOK;
}

static const struct rt_virtio_device_id virtio_gpu_ids[] =
{
    { VIRTIO_DEVICE_ID_GPU, VIRTIO_DEVICE_ANY_ID },
    { /* sentinel */ }
};

static struct rt_virtio_driver virtio_gpu_driver =
{
    .ids = virtio_gpu_ids,
    .features =
        RT_BIT(VIRTIO_GPU_F_VIRGL)
      | RT_BIT(VIRTIO_GPU_F_EDID)
      | RT_BIT(VIRTIO_F_ANY_LAYOUT),

    .probe = virtio_gpu_probe,
    .remove = virtio_gpu_remove,
    .config_changed = virtio_gpu_config_changed,
};
RT_VIRTIO_DRIVER_EXPORT(virtio_gpu_driver);
