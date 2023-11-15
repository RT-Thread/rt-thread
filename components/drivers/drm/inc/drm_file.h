#ifndef _DRM_DRM_FILE_H_
#define _DRM_DRM_FILE_H_

#include "drm.h"

struct drm_device;

#define MAXEVENT 32

struct drm_pending_event {
    struct drm_event* event;
    struct drm_device* dev;

    rt_list_t  link;
    rt_list_t  pending_link;
};


struct drm_pending_vblank_event {
    struct drm_pending_event base;
    unsigned int pipe;
    union {
        struct drm_event base;
        struct drm_event_vblank vbl;
    } event;
};

#endif
