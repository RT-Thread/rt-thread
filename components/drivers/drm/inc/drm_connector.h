#ifndef _DRM_DRM_CONNECTOR_H_
#define _DRM_DRM_CONNECTOR_H_

#include <stdint.h>
#include "drm_mode_object.h"


struct drm_device;
struct drm_encoder;
struct drm_connector;

struct drm_connector_helper_funcs {
    int (*get_modes)(struct drm_device*,struct drm_connector*);
};

struct drm_connector {
    rt_list_t head;
    struct drm_mode_object base;
    unsigned index;

    int connector_type;
    int connector_type_id;

    uint32_t possible_encoders;
    struct drm_encoder* encoder;

    rt_list_t modes;

    const struct drm_connector_helper_funcs* helper_funcs;
};

int drm_connector_init(struct drm_device* dev, struct drm_connector* connector,
                       int connector_type);
int drm_connector_attach_encoder(struct drm_connector* connector,
                                 struct drm_encoder* encoder);

#define obj_to_connector(x)  \
    rt_list_entry(x, struct drm_connector, base)



#define drm_for_each_connector(connector, dev) \
    rt_list_for_each_entry(connector, &(dev)->mode_config.connector_list, head)



static inline struct drm_connector* 
drm_connector_lookup(struct drm_device* dev, unsigned int id)
{
    struct drm_mode_object* mo;
    mo = drm_mode_object_find(dev, id, DRM_MODE_OBJECT_CONNECTOR);
    return mo ? obj_to_connector(mo) : NULL;
}


static inline void
drm_connector_set_helper_funcs(struct drm_connector* connector,
                               const struct drm_connector_helper_funcs* helper)
{
    connector->helper_funcs = helper;
}
#endif
