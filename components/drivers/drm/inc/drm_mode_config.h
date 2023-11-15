#ifndef _DRM_DRM_MODE_CONFIG_H_
#define _DRM_DRM_MODE_CONFIG_H_

#include <sys/types.h>
#include "idr.h"

struct drm_device;
struct drm_mode_fb_cmd2;
struct drm_framebuffer;
struct drm_atomic_state;

struct drm_mode_config_funcs {
    int (*fb_create)(struct drm_device* dev, const struct drm_mode_fb_cmd2* cmd,
                     struct drm_framebuffer** fbp);

    void (*commit)(struct drm_atomic_state* state);
};

struct drm_mode_config {
    int min_width, min_height;
    int max_width, max_height;
    const struct drm_mode_config_funcs* funcs;

    size_t num_fb;
    rt_list_t fb_list;

    size_t num_crtc;
    rt_list_t crtc_list;

    size_t num_connector;
    rt_list_t connector_list;

    size_t num_encoder;
    rt_list_t encoder_list;

    size_t num_total_plane;
    rt_list_t plane_list;

    struct idr object_idr;

};

void drm_mode_config_init(struct drm_device* dev);
void drm_mode_config_reset(struct drm_device* dev);

#endif
