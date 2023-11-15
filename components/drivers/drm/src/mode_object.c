#include <rtthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <lwp_user_mm.h>

#include "inc/drm_device.h"
#include "inc/drm_mode.h"
#include "inc/drm_mode_object.h"


int drm_mode_object_add(struct drm_device* dev, struct drm_mode_object* obj,
                        unsigned int type)
{
    int retval;

    retval = idr_alloc_new(&dev->mode_config.object_idr, obj, 1, 0);
    if (retval >= 0) {
        obj->id = retval;
        obj->type = type;
    }

    return retval < 0 ? -retval : 0;
}

struct drm_mode_object* drm_mode_object_find(struct drm_device* dev,
                                             unsigned int id, unsigned type)
{
    struct drm_mode_object* obj = NULL;

    obj = idr_find_new(&dev->mode_config.object_idr, id);

    if (obj && type != DRM_MODE_OBJECT_ANY && obj->type != type) obj = NULL;
    if (obj && obj->id != id) obj = NULL;

    return obj;
}

int drm_mode_object_get_properties(struct drm_mode_object* obj, void* prop_ptr,
                                   void* prop_values, uint32_t* arg_count_props)
{
    *arg_count_props = 0;
    return 0;
}

int drm_mode_obj_get_properties_ioctl(struct drm_device* dev,  void* data)
{
    struct drm_mode_obj_get_properties arg;
    struct drm_mode_object* obj;
    int retval = 0;

    lwp_get_from_user(&arg,data,sizeof(arg));
    
    obj = drm_mode_object_find(dev, arg.obj_id, arg.obj_type);
    if (!obj) return ENOENT;
 
  
    retval = drm_mode_object_get_properties(
        obj, (void*)(unsigned long)arg.props_ptr,
        (void*)(unsigned long)arg.prop_values_ptr, &arg.count_props);
    
    
    lwp_put_to_user(data,&arg,sizeof(arg));
    return retval;
}
