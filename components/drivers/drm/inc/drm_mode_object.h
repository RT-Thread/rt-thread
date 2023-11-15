#ifndef _DRM_DRM_MODE_OBJECT_H_
#define _DRM_DRM_MODE_OBJECT_H_

struct drm_device;

#define DRM_MODE_OBJECT_CRTC      0xcccccccc
#define DRM_MODE_OBJECT_CONNECTOR 0xc0c0c0c0
#define DRM_MODE_OBJECT_ENCODER   0xe0e0e0e0
#define DRM_MODE_OBJECT_MODE      0xdededede
#define DRM_MODE_OBJECT_PROPERTY  0xb0b0b0b0
#define DRM_MODE_OBJECT_FB        0xfbfbfbfb
#define DRM_MODE_OBJECT_BLOB      0xbbbbbbbb
#define DRM_MODE_OBJECT_PLANE     0xeeeeeeee
#define DRM_MODE_OBJECT_ANY       0

struct drm_mode_object {
    
    unsigned int id;
    unsigned int type;
};


int drm_mode_object_add(struct drm_device* dev, struct drm_mode_object* obj,
                        unsigned int type);
struct drm_mode_object* drm_mode_object_find(struct drm_device* dev,
                                             unsigned int id, unsigned type);

#endif
