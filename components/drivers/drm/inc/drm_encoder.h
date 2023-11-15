#ifndef _DRM_DRM_ENCODER_H_
#define _DRM_DRM_ENCODER_H_

#include <stdint.h>

#include "drm_mode_object.h"

struct drm_device;
struct drm_crtc;

struct drm_encoder {
    rt_list_t head; 
    struct drm_mode_object base;
    unsigned index;

    int encoder_type;
    int encoder_type_id;

    uint32_t possible_crtcs;
    uint32_t possible_clones;

    struct drm_crtc* crtc;
};

int drm_encoder_init(struct drm_device* dev, struct drm_encoder* encoder,
                     int encoder_type);

#define obj_to_encoder(x) rt_list_entry(x, struct drm_encoder, base)

static inline struct drm_encoder* drm_encoder_find(struct drm_device* dev,
                                                   unsigned int id)
{
    struct drm_mode_object* mo;
    mo = drm_mode_object_find(dev, id, DRM_MODE_OBJECT_ENCODER);
    return mo ? obj_to_encoder(mo) : NULL;
}
#define drm_for_each_encoder(encoder, dev) \
    rt_list_for_each_entry(encoder, &(dev)->mode_config.encoder_list, head)

#endif
