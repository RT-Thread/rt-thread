#include <mmu.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include "inc/drm_device.h"
#include "inc/drm_gem.h"

struct drm_gem_object* drm_gem_object_lookup(struct drm_device* dev, uint32_t handle)
{
    return idr_find_new(&dev->gem_object_idr, handle);
}

void drm_gem_open(struct drm_device* dev)
{
    idr_init_base(&dev->gem_object_idr, 1);
}

int drm_gem_handle_create(struct drm_device* dev, struct drm_gem_object* obj,
                          unsigned int* handlep)
{
    unsigned int handle;
    int retval;

    retval = idr_alloc_new(&dev->gem_object_idr, obj, 1, 0);

    if (retval < 0) return -retval;

    handle = retval;
    *handlep = handle;

    return 0;
}

int drm_gem_object_init(struct drm_gem_object* obj, size_t size)
{
    obj->size = size;

    return 0;
}

int drm_gem_dumb_map_offset(struct drm_device* dev, rt_uint32_t handle, uint64_t* offset)
{
    struct drm_gem_object* obj;

    obj = drm_gem_object_lookup(dev, handle);
    if (!obj) return ENOENT;

    *offset = handle << ARCH_PAGE_SHIFT;

    return 0;
}



