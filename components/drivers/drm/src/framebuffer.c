#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include <lwp_user_mm.h>

#include "inc/drm_mode.h"
#include "inc/drm_fourcc.h"
#include "inc/drm_device.h"
#include "inc/drm_mode_object.h"
#include "inc/drm_mode_config.h"
#include "inc/drm_framebuffer.h"

static uint32_t drm_mode_legacy_fb_format(uint32_t bpp, uint32_t depth)
{
    uint32_t fmt = DRM_FORMAT_INVALID;

    switch (bpp) {
    case 8:
        if (depth == 8) fmt = DRM_FORMAT_C8;
        break;

    case 16:
        switch (depth) {
        case 15:
            fmt = DRM_FORMAT_XRGB1555;
            break;
        case 16:
            fmt = DRM_FORMAT_RGB565;
            break;
        default:
            break;
        }
        break;

    case 24:
        if (depth == 24) fmt = DRM_FORMAT_RGB888;
        break;

    case 32:
        switch (depth) {
        case 24:
            fmt = DRM_FORMAT_XRGB8888;
            break;
        case 30:
            fmt = DRM_FORMAT_XRGB2101010;
            break;
        case 32:
            fmt = DRM_FORMAT_ARGB8888;
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }

    return fmt;
}

int drm_framebuffer_init(struct drm_device* dev, struct drm_framebuffer* fb)
{

    struct drm_mode_config* config = &dev->mode_config;
    int retval;

    retval = drm_mode_object_add(dev, &fb->base, DRM_MODE_OBJECT_FB);
    if (retval) return retval;

    rt_list_insert_after( &config->fb_list,&fb->head);

    config->num_fb++;

    return 0;
}

static int drm_framebuffer_create(struct drm_device* dev,
                                  const struct drm_mode_fb_cmd2* r,
                                  struct drm_framebuffer** fbp)
{
    struct drm_mode_config* config = &dev->mode_config;

    if (r->flags & ~(DRM_MODE_FB_INTERLACED | DRM_MODE_FB_MODIFIERS)) {
        return RT_EINVAL;
    }

    if ((config->min_width > r->width) || (r->width > config->max_width)) {
        return RT_EINVAL;
    }
    if ((config->min_height > r->height) || (r->height > config->max_height)) {
        return RT_EINVAL;
    }

    return config->funcs->fb_create(dev, r, fbp);
}

static int drm_mode_addfb2(struct drm_device* dev,  void* data)
{
    struct drm_mode_fb_cmd2* r = data;
    struct drm_framebuffer* fb;

    int retval;
    retval = drm_framebuffer_create(dev, r, &fb);
    if (retval) return retval;
    
    r->fb_id = fb->base.id;
    return 0;
}

int drm_mode_addfb_ioctl(struct drm_device* dev, void* data)
{
    struct drm_mode_fb_cmd or;
    struct drm_mode_fb_cmd2 r = {};
    int retval;
    
    lwp_get_from_user(&or,data,sizeof(or));

    r.pixel_format = drm_mode_legacy_fb_format(or.bpp, or.depth);
    if (r.pixel_format == DRM_FORMAT_INVALID) return RT_EINVAL;

    r.fb_id = or.fb_id;
    r.width = or.width;
    r.height = or.height;
    r.pitches[0] = or.pitch;
    r.handles[0] = or.handle;

    retval = drm_mode_addfb2(dev, &r);
    if (retval) return retval;

    or.fb_id = r.fb_id;

    lwp_put_to_user(data,&or,sizeof(or));
    return 0;
}

int drm_mode_addfb2_ioctl(struct drm_device* dev, void* data)
{
    return drm_mode_addfb2(dev, data);
}
