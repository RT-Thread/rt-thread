#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <lwp_user_mm.h>



#include "inc/drm_device.h"
#include "inc/drm_modes.h"
#include "inc/drm_gem.h"

int drm_mode_create_dumb(struct drm_device* dev,
                         struct drm_mode_create_dumb* args)
{
    if (!dev->driver->dumb_create) {
        return ENOSYS;
    }

    return dev->driver->dumb_create(dev, args);
}

int drm_mode_create_dumb_ioctl(struct drm_device* dev, void* data)                 
{
    return drm_mode_create_dumb(dev, data);
}

int drm_mode_mmap_dumb_ioctl(struct drm_device* dev, void* data)
{
    struct drm_mode_map_dumb args;
    lwp_get_from_user(&args,data,sizeof(args));

    if (!dev->driver->dumb_create) {
        return RT_ENOSYS;
    }
    drm_gem_dumb_map_offset(dev, args.handle,&args.offset);
    lwp_put_to_user(data,&args,sizeof(args));
    return 0;    
} 
