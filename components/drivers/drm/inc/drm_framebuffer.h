#ifndef _DRM_DRM_FRAMEBUFFER_H_
#define _DRM_DRM_FRAMEBUFFER_H_

#include "drm_mode_object.h"


struct drm_gem_object;

struct drm_framebuffer {
    rt_list_t head;
    struct drm_mode_object base;

    struct drm_gem_object* obj[4];
};



int drm_framebuffer_init(struct drm_device* dev, struct drm_framebuffer* fb);

#define obj_to_fb(x)  \
    rt_list_entry(x, struct drm_framebuffer, base)


static inline struct drm_framebuffer*
drm_framebuffer_lookup(struct drm_device* dev, unsigned int id)
{
    struct drm_mode_object* mo;
    mo = drm_mode_object_find(dev, id, DRM_MODE_OBJECT_FB);
    return mo ? obj_to_fb(mo) : NULL;
}

#endif
