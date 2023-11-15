#ifndef _DRM_DRM_PLANE_H_
#define _DRM_DRM_PLANE_H_

#include <sys/types.h>

#include "drm_mode_object.h"

struct drm_crtc;
struct drm_framebuffer;
struct drm_plane;
struct drm_atomic_state;

enum drm_plane_type {
    DRM_PLANE_TYPE_OVERLAY,
    DRM_PLANE_TYPE_PRIMARY,
    DRM_PLANE_TYPE_CURSOR,
};

struct drm_plane_state {
    struct drm_crtc* crtc;
    struct drm_framebuffer* fb;

    int crtc_x, crtc_y, crtc_w, crtc_h;
    int src_x, src_y, src_w, src_h;
};

struct drm_plane_helper_funcs {
    void (*update)(struct drm_plane* plane, struct drm_plane_state* old_state, void *userdata);
};

struct drm_plane {
    rt_list_t  head;
    struct drm_mode_object base;
    unsigned index;

    struct drm_plane_state* state;
    struct drm_plane_helper_funcs* helper_funcs;

    enum drm_plane_type type;
    uint32_t possible_crtcs;
};

int drm_plane_init(struct drm_device* dev, struct drm_plane* plane,
                   uint32_t possible_crtcs, enum drm_plane_type type);

void drm_helper_commit_planes(struct drm_device* dev,
                              struct drm_atomic_state* old_state);

static inline void
drm_plane_add_helper_funcs(struct drm_plane* plane,
                           struct drm_plane_helper_funcs* funcs)
{
    plane->helper_funcs = funcs;
}

#define drm_for_each_plane(plane, dev) \
    rt_list_for_each_entry(plane, &(dev)->mode_config.plane_list, head)

#endif
