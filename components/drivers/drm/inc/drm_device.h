#ifndef _DRM_DRM_DEVICE_H_
#define _DRM_DRM_DEVICE_H_

#include "drm.h"
#include "drm_mode_config.h"
#include "idr.h"

struct drm_driver {
    const char* name;
    const char* desc;
    const char* date;

    int major;
    int minor;
    int patchlevel;

    int (*dumb_create)(struct drm_device* dev,
                       struct drm_mode_create_dumb* args);
};   

struct drm_minor {
    int index;
    rt_uint8_t device_id;
};

struct drm_device {
    
    struct drm_driver* driver;
    struct drm_minor primary;
    struct drm_mode_config mode_config;

    struct idr gem_object_idr;

    rt_list_t  pending_event_list;
    rt_list_t  event_list;
    
    int tick;
    struct rt_mutex lock;
    rt_wqueue_t drm_queue;
    
    void      *user_data;                /**< device private data */
};

rt_err_t rt_virtio_gpu_drm_init(rt_ubase_t *mmio_base, rt_uint32_t irq);
#endif
