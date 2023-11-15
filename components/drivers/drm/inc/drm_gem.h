#ifndef _DRM_DRM_GEM_H_
#define _DRM_DRM_GEM_H_

#include <sys/types.h>

struct drm_device;
struct drm_gem_object;

struct drm_gem_object_funcs {
    rt_base_t (*mmap)(struct drm_gem_object* obj,  size_t length );
};

struct drm_gem_object {
    size_t size;
    const struct drm_gem_object_funcs* funcs;
};

int drm_gem_object_init(struct drm_gem_object* obj, size_t size);
struct drm_gem_object* drm_gem_object_lookup(struct drm_device* dev,
                                                uint32_t handle);
int drm_gem_handle_create(struct drm_device* dev, struct drm_gem_object* obj,
                          unsigned int* handlep);
int drm_gem_dumb_map_offset(struct drm_device* dev, uint32_t handle, uint64_t* offset);

#endif
