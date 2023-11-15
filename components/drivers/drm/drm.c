/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 * 2023-11-11     zhangxianshun  add drm 
 */

#include <rtthread.h>
#include <rthw.h>
#include <cpuport.h>

#define RT_USING_DRM
#ifdef RT_USING_DRM

#include <sys/mman.h>
#include <lwp_user_mm.h>

#include "virtio_gpu.h"

#include "inc/drm_connector.h"
#include "inc/drm_encoder.h"
#include "inc/drm_fourcc.h"
#include "inc/drm_plane.h"
#include "inc/drm_modes.h"
#include "inc/drm_gem.h"
#include "inc/proto.h"
#include "inc/idr.h"

#define DRIVER_NAME "virtio_drm"
#define DRIVER_DESC "Virtio DRM"
#define DRIVER_DATE "0"

#define DRIVER_MAJOR      0
#define DRIVER_MINOR      1
#define DRIVER_PATCHLEVEL 0

struct virtio_gpu_output {
    int index;
    struct drm_crtc crtc;
    struct drm_connector connector;
    struct drm_encoder encoder;
    int enabled;
} outputs[VIRTIO_GPU_MAX_SCANOUTS];

struct virtio_gpu_object_params {
    uint32_t format;
    uint32_t width;
    uint32_t height;
    unsigned long size;
    int dumb;
};

struct virtio_gpu_object {
    struct drm_gem_object base;
    unsigned int hw_res_handle;
    rt_base_t *paddr;
    int dumb;
    int created;
};

#define gem_to_virtio_gpu_obj(gobj) \
    rt_list_entry((gobj), struct virtio_gpu_object, base)

#define drm_crtc_to_virtio_gpu_output(x) \
    rt_list_entry(x, struct virtio_gpu_output, crtc)

struct virtio_gpu_framebuffer {
    struct drm_framebuffer base;
};
#define to_virtio_gpu_framebuffer(x) \
    rt_list_entry(x, struct virtio_gpu_framebuffer, base)

static int virtio_gpu_mode_dumb_create(struct drm_device* dev,
                                       struct drm_mode_create_dumb* args);

static struct drm_driver virtio_drm_driver = {
    .name = DRIVER_NAME,
    .desc = DRIVER_DESC,
    .date = DRIVER_DATE,

    .major = DRIVER_MAJOR,
    .minor = DRIVER_MINOR,
    .patchlevel = DRIVER_PATCHLEVEL,

    .dumb_create = virtio_gpu_mode_dumb_create,
};


static uint32_t virtio_gpu_translate_format(uint32_t drm_fourcc)
{
    uint32_t format;

    switch (drm_fourcc) {
    case DRM_FORMAT_XRGB8888:
        format = VIRTIO_GPU_FORMAT_B8G8R8X8_UNORM;
        break;
    case DRM_FORMAT_ARGB8888:
        format = VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM;
        break;
    case DRM_FORMAT_BGRX8888:
        format = VIRTIO_GPU_FORMAT_X8R8G8B8_UNORM;
        break;
    case DRM_FORMAT_BGRA8888:
        format = VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM;
        break;
    default:
        format = 0;
        break;
    }

    return format;
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

static rt_err_t virtio_gpu_create_2d_resource( struct virtio_gpu_device *virtio_gpu_dev ,enum virtio_gpu_formats format,
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


static rt_err_t virtio_gpu_attach_backing_resource(struct virtio_gpu_device *virtio_gpu_dev, struct virtio_gpu_object* bo)
{

    struct virtio_gpu_ctrl_hdr res;
    struct
    {
        struct virtio_gpu_resource_attach_backing req;
        struct virtio_gpu_mem_entry mem;
    } req;

    rt_memset(&req, 0, sizeof(req));

    req.req.hdr.type = VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING;
    req.req.resource_id = bo->hw_res_handle;
    req.req.nr_entries = 1;

    req.mem.addr =  (rt_uint64_t)bo->paddr;

    req.mem.length = bo->base.size ;

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

static rt_base_t virtio_gpu_mmap(struct drm_gem_object* obj,   size_t length )
{
    struct virtio_gpu_object* bo = gem_to_virtio_gpu_obj(obj);
    rt_base_t vaddr;
    if (length == bo->base.size)
    {  
        vaddr = (rt_base_t)lwp_map_user_phy(lwp_self(), RT_NULL,  bo->paddr  , bo->base.size , 0);
        return vaddr;
    }
    return -RT_ERROR;
}  

static const struct drm_gem_object_funcs virtio_gpu_gem_obj_funcs = {
    .mmap = virtio_gpu_mmap,
};

static int virtio_gpu_object_create(struct virtio_gpu_object_params* params,
                                    struct virtio_gpu_object** bo_p, void *userdata)
{   
    struct virtio_gpu_device *virtio_gpu_dev = userdata;
    struct virtio_gpu_object* bo;
    int retval;

    bo = rt_malloc(sizeof(*bo));
    if (!bo) return RT_ENOMEM;
    rt_memset(bo, 0, sizeof(*bo));

    retval = drm_gem_object_init(&bo->base, params->size);
    if (retval) goto err_free_obj;
    
    bo->base.funcs = &virtio_gpu_gem_obj_funcs;
    bo->paddr = (rt_base_t*)rt_kmem_v2p(rt_malloc_align( bo->base.size , VIRTIO_PAGE_SIZE));

     bo->hw_res_handle = virtio_gpu_dev->display_resource_id;
    bo->dumb = params->dumb;

    virtio_gpu_create_2d_resource( virtio_gpu_dev, params->format,
             &bo->hw_res_handle, params->width,  params->height);

    if (retval) goto err_free_mem;

    virtio_gpu_attach_backing_resource(virtio_gpu_dev, bo);
    if (retval) goto err_free_mem;

    virtio_gpu_set_scanout(virtio_gpu_dev,
                0, bo->hw_res_handle,params->width,  params->height);
    *bo_p = bo;
    return 0;

err_free_mem:
 
err_free_obj:
    rt_free(bo);
    return retval;

}

static int virtio_gpu_gem_create(struct drm_device* dev,
                                 struct virtio_gpu_object_params* params,
                                 struct drm_gem_object** obj_p,
                                 unsigned int* handle_p)
{
    struct virtio_gpu_object* obj;
    unsigned int handle;
    int retval;
    retval = virtio_gpu_object_create(params, &obj, dev->user_data);
    if (retval) return retval;

    retval = drm_gem_handle_create(dev, &obj->base, &handle);
    if (retval) return retval;

    *obj_p = &obj->base;
    *handle_p = handle;
    return 0;
}

static int virtio_gpu_mode_dumb_create(struct drm_device* dev,
                                       struct drm_mode_create_dumb* args)
{
    struct virtio_gpu_object_params params = {0};
    struct drm_mode_create_dumb dum_res;
    struct drm_gem_object* gobj;
    int retval;
    uint32_t pitch;

    lwp_get_from_user( &dum_res , args, sizeof(dum_res) );
    if (dum_res.bpp != 32) return RT_EINVAL;

    pitch = dum_res.width * 4;
    dum_res.size = pitch * dum_res.height;
    dum_res.size = RT_ALIGN(dum_res.size , VIRTIO_PAGE_SIZE);

    params.format = virtio_gpu_translate_format(DRM_FORMAT_XRGB8888);
    params.width = dum_res.width;
    params.height = dum_res.height;
    params.size =  dum_res.size;
    params.dumb = RT_TRUE;
    retval = virtio_gpu_gem_create(dev, &params, &gobj, &dum_res.handle);
    if (retval) return retval;
    dum_res.pitch = pitch;

    lwp_put_to_user( args, &dum_res, sizeof(dum_res) );
    return retval;
}



static void virtio_gpu_primary_plane_update(struct drm_plane* plane,
                                            struct drm_plane_state* old_state ,void *userdata)
{   
    struct virtio_gpu_device* virtio_gpu_dev = userdata;
    struct virtio_gpu_output* output = RT_NULL;
    struct virtio_gpu_object* bo = RT_NULL;
    if (plane->state->crtc) {
        output = drm_crtc_to_virtio_gpu_output(plane->state->crtc);
    }
    if (old_state->crtc) {
        output = drm_crtc_to_virtio_gpu_output(old_state->crtc);
    }
    if (!output) return;

    bo = gem_to_virtio_gpu_obj(plane->state->fb->obj[0]);

    if (!plane->state->fb || !bo->dumb) {
        return;
    }

    if (plane->state->fb != old_state->fb ||
        plane->state->src_w != old_state->src_w ||
        plane->state->src_h != old_state->src_h ||
        plane->state->src_x != old_state->src_x ||
        plane->state->src_y != old_state->src_y) {
        virtio_gpu_set_scanout(virtio_gpu_dev,
                    output->index, bo->hw_res_handle, plane->state->src_w >> 16, plane->state->src_h >> 16);
    }
    virtio_gpu_gfx_flush_2d(virtio_gpu_dev, bo->hw_res_handle, 
                    plane->state->src_x >> 16, plane->state->src_y >> 16, 
                    plane->state->src_w >> 16, plane->state->src_h >> 16);
}

static struct drm_plane_helper_funcs virtio_gpu_primary_helper_funcs = {
    .update = virtio_gpu_primary_plane_update,
};

static int virtio_gpu_plane_init( struct drm_device  *dev, enum drm_plane_type type, int index,
                                 struct drm_plane** pplane)
{
    struct drm_plane* plane;
    struct drm_plane_helper_funcs* funcs;
    int retval;

    if (type == DRM_PLANE_TYPE_PRIMARY) {
        funcs = &virtio_gpu_primary_helper_funcs;
    }

    plane = rt_malloc(sizeof(*plane));
    if (!plane) {
        return RT_ENOMEM;
    }

    rt_memset(plane, 0, sizeof(*plane));

    retval = drm_plane_init(dev, plane, 1U << index, type);
    if (retval) goto err_free_plane;

    drm_plane_add_helper_funcs(plane, funcs);
    
    *pplane = plane;

    return 0;
err_free_plane:
    rt_free(plane);
    return retval;
}

static int virtio_gpu_conn_get_modes(struct drm_device  *dev, struct drm_connector* conn)
{
    int count;
    count = drm_add_dmt_modes(conn, dev->mode_config.max_width ,dev->mode_config.max_height);
    drm_set_preferred_mode(conn,  dev->mode_config.max_width ,dev->mode_config.max_height);
    return count;
}

static const struct drm_connector_helper_funcs virtio_gpu_conn_helper_funcs = {
    .get_modes = virtio_gpu_conn_get_modes,
};
static int virtio_output_init( struct drm_device  *dev, int index )
{
    struct virtio_gpu_output* output = &outputs[index];
    struct drm_plane* primary;
    int retval;

    retval = virtio_gpu_plane_init( dev,DRM_PLANE_TYPE_PRIMARY, index, &primary);
    if (retval) return retval;

    drm_crtc_init_with_planes(dev, &output->crtc, primary, RT_NULL);

    drm_connector_init(dev, &output->connector,
                       DRM_MODE_CONNECTOR_VIRTUAL);

    drm_connector_set_helper_funcs(&output->connector,
                                   &virtio_gpu_conn_helper_funcs);

    drm_encoder_init(dev, &output->encoder, DRM_MODE_ENCODER_VIRTUAL);
    output->encoder.possible_crtcs = 1U << index;
    output->encoder.crtc = &output->crtc;

    drm_connector_attach_encoder(&output->connector, &output->encoder);
    output->connector.encoder = &output->encoder;

    return 0;
}

static int virtio_gpu_fb_create(struct drm_device* dev,
                                const struct drm_mode_fb_cmd2* cmd,
                                struct drm_framebuffer** fbp)
{
    struct drm_gem_object* obj = RT_NULL;
    struct virtio_gpu_framebuffer* fb;
    int retval;

    if (cmd->pixel_format != DRM_FORMAT_XRGB8888 &&
        cmd->pixel_format != DRM_FORMAT_ARGB8888)
        return RT_ENOENT;

    obj = drm_gem_object_lookup(dev, cmd->handles[0]);
    if (!obj) return RT_EINVAL;

    fb = rt_malloc(sizeof(*fb));
    if (!fb) return RT_ENOMEM;

    rt_memset(fb, 0, sizeof(*fb));

    fb->base.obj[0] = obj;

    retval = drm_framebuffer_init(dev, &fb->base);
    if (retval) {
        fb->base.obj[0] = RT_NULL;
        goto err_free_fb;
    }

    *fbp = &fb->base;

    return 0;

err_free_fb:
    rt_free(fb);
    return retval;
}

static void virtio_gpu_mode_commit(struct drm_atomic_state* state)
{
    struct drm_device* dev = state->dev;
    drm_helper_commit_planes(dev, state);
}

struct drm_mode_config_funcs virtio_gpu_mode_funcs = {
   .fb_create = virtio_gpu_fb_create, .commit = virtio_gpu_mode_commit
};

int drm_device_init(struct virtio_gpu_device *virtio_gpu_dev, struct drm_driver* drv, const char *name,
                    rt_uint8_t parent)
{
    struct drm_device  *dev = &virtio_gpu_dev->drm_dev;
    dev->user_data = virtio_gpu_dev;
    dev->driver = drv;
    dev->primary.device_id = parent;
    dev->primary.index = 0;
    dev->tick = RT_FALSE;
    rt_mutex_init(&dev->lock,name, RT_IPC_FLAG_PRIO);
    rt_wqueue_init(&dev->drm_queue);
    rt_list_init(&dev->pending_event_list);
    rt_list_init(&dev->event_list);

    return 0;
}

static void virtio_gpu_mode_init(struct drm_device  *dev,rt_uint32_t width, rt_uint32_t height , rt_uint8_t dev_id )
{   
    struct drm_mode_config* config =  &dev->mode_config;
    drm_mode_config_init(dev);
    config->max_width = width;
    config->min_width = 0;
    config->max_height = height;
    config->min_height = 0;
    config->funcs = &virtio_gpu_mode_funcs;
    virtio_output_init( dev, dev_id );
    drm_mode_config_reset(dev); 
}

static rt_err_t virtio_gpu_init( struct virtio_gpu_device *virtio_gpu_dev )
{
    rt_err_t status;
    
    struct virtio_device *virtio_dev = &virtio_gpu_dev->virtio_dev;   
    struct virtq *queue_ctrl, *queue_cursor;

    queue_ctrl = &virtio_dev->queues[VIRTIO_GPU_QUEUE_CTRL];
    queue_cursor = &virtio_dev->queues[VIRTIO_GPU_QUEUE_CURSOR];

    queue_ctrl->avail->flags = 0;
    queue_cursor->avail->flags = 0;

    status = virtio_gpu_get_display_info(virtio_gpu_dev);

    return status;
}

static void virtio_gpu_isr(int irqno, void *param)
{
    rt_uint16_t id;
    struct virtio_gpu_device *virtio_gpu_dev = param;
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

static int drm_fops_ioctl(struct dfs_file *file, int cmd, void *args)
{
    struct virtio_gpu_device *virtio_gpu_dev = (struct virtio_gpu_device *)file->vnode->data;
    struct drm_device *drm_dev = &virtio_gpu_dev->drm_dev;
    int status = RT_EOK;
    switch (cmd)
    {
    case RT_FIOMMAP2:
        {   
            struct dfs_mmap2_args *mmap2 = (struct dfs_mmap2_args *)args;
            struct drm_gem_object* obj;
            if( !mmap2 )  return RT_EINVAL;
        
            obj = drm_gem_object_lookup(drm_dev, mmap2->pgoffset);
            if (!obj) return RT_EINVAL;
            if (obj->size < mmap2->length) {
                return RT_EINVAL;
            }
            if (obj->funcs && obj->funcs->mmap) {
               mmap2->ret = (void *)(uintptr_t)obj->funcs->mmap(obj, mmap2->length); 
            }
        }
        break;
    case DRM_IOCTL_VERSION:
        {
            struct drm_version version;
            lwp_get_from_user(&version,args,sizeof(version));

            version.version_major = drm_dev->driver->major;
            version.version_minor = drm_dev->driver->minor;
            version.version_patchlevel = drm_dev->driver->patchlevel;

            version.name_len =  rt_strlen( drm_dev->driver->name);
            rt_memcpy(version.name,drm_dev->driver->name,version.name_len);

            version.desc_len = rt_strlen( drm_dev->driver->desc);
            rt_memcpy(version.desc,drm_dev->driver->desc, version.desc_len);
          
            version.date_len = rt_strlen( drm_dev->driver->date);
            rt_memcpy(version.date, drm_dev->driver->date,version.date_len);

            lwp_put_to_user(args,&version,sizeof(version));
        }
        break;
    case DRM_IOCTL_GET_CAP:
        {
            struct drm_get_cap req ;
            lwp_get_from_user(&req,args,sizeof(req));
           
             req.value = 0;
                switch (req.capability) {
            case DRM_CAP_TIMESTAMP_MONOTONIC:
                req.value = 1;
                break;
            case DRM_CAP_PRIME:
                req.value = 0;
                break;
            case DRM_CAP_DUMB_BUFFER:
                if (drm_dev->driver->dumb_create) {
                     req.value = 1;
                }
                break;
            default:
                return RT_EINVAL;
            }
            lwp_put_to_user(args,&req,sizeof(req));
        }
        break;

    case DRM_IOCTL_SET_MASTER:
        {
            return 0;
        }
        break;

    case DRM_IOCTL_MODE_GETRESOURCES:
        {   
            drm_mode_getresources(drm_dev,args);
        }
        break;

    case DRM_IOCTL_MODE_GETCONNECTOR:
        {  
            drm_mode_getconnector(drm_dev,args);
        }
        break;
    case DRM_IOCTL_MODE_GETENCODER:
        {   
            drm_mode_getencoder(drm_dev,args);
        }
        break;

    case DRM_IOCTL_MODE_CREATE_DUMB:
        {   
            drm_mode_create_dumb_ioctl(drm_dev,args);
        }
        break;

    case DRM_IOCTL_MODE_MAP_DUMB:
        {   
            drm_mode_mmap_dumb_ioctl(drm_dev,args);
        }
        break;

    case DRM_IOCTL_MODE_OBJ_GETPROPERTIES:
        {    
            drm_mode_obj_get_properties_ioctl(drm_dev,args);
        }
        break;
    
    case DRM_IOCTL_MODE_PAGE_FLIP:
        {
            drm_mode_page_flip_ioctl(drm_dev,args);
        }
        break;
    
    case DRM_IOCTL_MODE_GETCRTC:
        {   
            drm_mode_getcrtc(drm_dev,args);
        }
        break;

    case DRM_IOCTL_MODE_SETCRTC:
        {   
            drm_mode_setcrtc(drm_dev,args);
         
        }
        break;

    case DRM_IOCTL_MODE_ADDFB:
        {    
            drm_mode_addfb_ioctl(drm_dev,args);
        }
        break;

    case DRM_IOCTL_MODE_ADDFB2:
        {       
            struct drm_mode_fb_cmd2 req ;
            lwp_get_from_user(&req,args,sizeof(req));
            drm_mode_addfb2_ioctl(drm_dev,&req);
            lwp_put_to_user(args,&req,sizeof(req));
        }
        break;
    case F_DUPFD_CLOEXEC:
    case F_DUPFD:
        status = -1;
        break;
    }

    return status;
}


int drm_fops_open(struct dfs_file *file)
{    
    struct virtio_gpu_device *virtio_gpu_dev = (struct virtio_gpu_device *)file->vnode->data;
    drm_gem_open(&virtio_gpu_dev->drm_dev);

    return 0;
}
int drm_fops_close(struct dfs_file *file)
{
    return 0;
}
static int drm_fops_poll(struct dfs_file *file, struct rt_pollreq *req)
{   
    struct virtio_gpu_device *virtio_gpu_dev = (struct virtio_gpu_device *)file->vnode->data;    
    struct drm_device *dev = &virtio_gpu_dev->drm_dev;
    int events = 0;
    rt_poll_add(&dev->drm_queue, req);
     rt_mutex_take(&dev->lock, RT_WAITING_FOREVER);
    if (dev->tick)
        events |= POLLIN;
    dev->tick = 0;
    rt_mutex_release(&dev->lock);
    return events;
}
ssize_t drm_fops_read(struct dfs_file *file, void *buf, size_t len, off_t *pos)
{   
    struct virtio_gpu_device *virtio_gpu_dev = (struct virtio_gpu_device *)file->vnode->data; 
    struct drm_device *dev = &virtio_gpu_dev->drm_dev;
    struct drm_pending_event *e = RT_NULL;
    ssize_t retval = 0;
    size_t length = 0;

    rt_wqueue_wait(&dev->drm_queue, 0, RT_WAITING_FOREVER);
    rt_mutex_take(&dev->lock, RT_WAITING_FOREVER);

    if (!rt_list_isempty(&dev->event_list))
    {
        e = rt_list_first_entry(&dev->event_list, struct drm_pending_event,
            link);

        length = e->event->length;
        rt_memcpy(buf, e->event, length);

        rt_list_remove(&e->link);
        retval += length;
        rt_free(e);
    }

    rt_mutex_release(&dev->lock);
    return retval;
}


static const struct dfs_file_ops drm_fops =
{
    .open       = drm_fops_open,
    .close      = drm_fops_close,
    .poll       = drm_fops_poll,
    .read       = drm_fops_read,
    .ioctl      = drm_fops_ioctl
};

rt_err_t rt_virtio_gpu_drm_init(rt_ubase_t *mmio_base, rt_uint32_t irq)
{   
    int ret = 0;
    static int dev_no = 0;
    char dev_name[RT_NAME_MAX];
    struct virtio_gpu_device *virtio_gpu_dev;
    struct virtio_device *virtio_dev;
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

    rt_snprintf(dev_name, RT_NAME_MAX, "card%d", dev_no++);
    
    rt_mutex_init(&virtio_gpu_dev->rw_mutex, dev_name, RT_IPC_FLAG_PRIO);
    rt_mutex_init(&virtio_gpu_dev->ops_mutex, dev_name, RT_IPC_FLAG_PRIO);

    rt_hw_interrupt_install(irq, virtio_gpu_isr, virtio_gpu_dev, dev_name);
    rt_hw_interrupt_umask(irq);

    if (virtio_gpu_init( virtio_gpu_dev ) != RT_EOK)
    {
         goto _alloc_fail;
    }
    if (virtio_gpu_dev->pmode_id == VIRTIO_GPU_INVALID_PMODE_ID)
    {
         goto _alloc_fail;
    }
    
 /**************************************************************************/
    drm_device_init(virtio_gpu_dev, &virtio_drm_driver, dev_name,
                    virtio_gpu_dev->pmode_id);

    virtio_gpu_mode_init(&virtio_gpu_dev->drm_dev,
            virtio_gpu_dev->pmode.r.width, virtio_gpu_dev->pmode.r.height,  
            virtio_gpu_dev->pmode_id);

    ret =  rt_device_register((rt_device_t)virtio_gpu_dev, dev_name, RT_DEVICE_FLAG_RDWR);
    if (ret != RT_EOK)
    {
        goto _alloc_fail;
    }
    else
    {
        virtio_gpu_dev->parent.fops = &drm_fops;
    }
    return ret;

_alloc_fail:

    if (virtio_gpu_dev != RT_NULL)
    {
        virtio_queues_free(virtio_dev);
        rt_free(virtio_gpu_dev);
    }
    return -RT_ENOMEM;
}
#endif /* RT_USING_VIRTIO_DRM */
