#ifndef _DRM_DRM_CRTC_H_
#define _DRM_DRM_CRTC_H_

#include <stdint.h>
#include "drm_mode_object.h"
#include "drm_modes.h"

struct drm_device;
struct drm_plane;
struct drm_mode_set;
struct drm_crtc;

struct drm_crtc_state {
    struct drm_crtc* crtc;
    int enable;
    struct drm_display_mode mode;
};

struct __drm_planes_state {
    struct drm_plane* ptr;
    struct drm_plane_state *state, *old_state, *new_state;
};

struct __drm_crtcs_state {
    struct drm_crtc* ptr;
    struct drm_crtc_state *state, *old_state, *new_state;
};

struct drm_atomic_state {
    struct drm_device* dev;

    struct __drm_planes_state* planes;
    struct __drm_crtcs_state* crtcs;
};

struct drm_crtc {
    rt_list_t head;
    struct drm_mode_object base;
    struct drm_device* dev;

    unsigned index;

    struct drm_crtc_state* state;

    struct drm_plane* primary;
    struct drm_plane* cursor;
};

struct drm_mode_set {
    struct drm_framebuffer* fb;
    struct drm_crtc* crtc;
    struct drm_display_mode* mode;

    uint32_t x;
    uint32_t y;

    struct drm_connector** connectors;
    size_t num_connectors;
};

int drm_crtc_init_with_planes(struct drm_device* dev, struct drm_crtc* crtc,
                              struct drm_plane* primary,
                              struct drm_plane* cursor);

#define obj_to_crtc(x) rt_list_entry(x, struct drm_crtc, base)
static inline struct drm_crtc* drm_crtc_lookup(struct drm_device* dev,
                                               unsigned int id)
{
    struct drm_mode_object* mo;
    mo = drm_mode_object_find(dev, id, DRM_MODE_OBJECT_CRTC);
    return mo ? obj_to_crtc(mo) : NULL;
}

#define drm_for_each_crtc(crtc, dev) \
   rt_list_for_each_entry(crtc, &(dev)->mode_config.crtc_list, head)

#endif
