
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <lwp_user_mm.h>

#include "inc/drm_device.h"
#include "inc/drm_connector.h"
#include "inc/drm_mode.h"

#include "inc/drm_encoder.h"
#include "inc/drm_modes.h"



int drm_connector_init(struct drm_device* dev, struct drm_connector* connector,
                       int connector_type)
{
    int retval;

    connector->possible_encoders = 0;

    connector->connector_type = connector_type;
    connector->connector_type_id = 0;

    retval =
        drm_mode_object_add(dev, &connector->base, DRM_MODE_OBJECT_CONNECTOR);
    if (retval) return retval;

    rt_list_init(&connector->modes);

    rt_list_insert_after(&dev->mode_config.connector_list, &connector->head);
    connector->index = dev->mode_config.num_connector++;

    return 0;
}

int drm_connector_attach_encoder(struct drm_connector* connector,
                                 struct drm_encoder* encoder)
{
    connector->possible_encoders |= 1U << encoder->index;

    return 0;
}


int drm_mode_getconnector(struct drm_device* dev, void* data)
{
    struct drm_mode_get_connector out_resp ;
    lwp_get_from_user(&out_resp,data,sizeof(out_resp));


    /* struct drm_mode_config* config = &dev->mode_config; */
    struct drm_connector* connector;
    struct drm_encoder* encoder;
    struct drm_display_mode* mode;
#define MODE_BUF_SIZE 64
    struct drm_mode_modeinfo modes[MODE_BUF_SIZE], *mode_ptr;
    void* encoder_ptr;
    int encoders_count, modes_count, copy_count;
    uint32_t encoder_ids[32];
    int i;
    void* device_id_ken ;



    connector = drm_connector_lookup(dev, out_resp.connector_id);
    if (!connector) {
        return RT_ENOENT;
    }

    encoders_count = 0;
    for (i = 0; i < 32; i++) {
        if (connector->possible_encoders & (1U << i)) {
            encoders_count++;
        }
    }

    copy_count = 0;
    if ((out_resp.count_encoders >= encoders_count) && encoders_count) {
        drm_for_each_encoder(encoder, dev)
        {
            if (connector->possible_encoders & (1U << encoder->index)) {
                
                encoder_ids[copy_count++] = encoder->base.id;
            }
        }
    }

    if (copy_count) {
        encoder_ptr = (void*)(uintptr_t)out_resp.encoders_ptr;
        device_id_ken = (void*)(uintptr_t)rt_malloc(copy_count * sizeof( uint32_t ));

        lwp_get_from_user(device_id_ken, encoder_ptr, copy_count * sizeof( uint32_t ));
        rt_memcpy(device_id_ken,encoder_ids, copy_count *sizeof(encoder_ids[0]));
        lwp_put_to_user( encoder_ptr, device_id_ken , copy_count * sizeof( uint32_t ));
        rt_free(device_id_ken);
     
    }

    out_resp.count_encoders = encoders_count;
    out_resp.connector_id = connector->base.id;
    out_resp.connector_type = connector->connector_type;
    out_resp.connector_type_id = connector->connector_type_id;

    if (out_resp.count_modes == 0) {
        connector->helper_funcs->get_modes(dev,connector);
    }

    /* out_resp->mm_width = connector->display_info.width_mm; */
    /* out_resp->mm_height = connector->display_info.height_mm; */
    /* out_resp->subpixel = connector->display_info.subpixel_order; */
    out_resp.connection = 1;

    modes_count = 0;
    rt_list_for_each_entry(mode, &connector->modes, head) { modes_count++; }

    if ((out_resp.count_modes >= modes_count) && modes_count) {
        mode_ptr = (struct drm_mode_modeinfo*)(uintptr_t)out_resp.modes_ptr;
        copy_count = 0;
        
        rt_list_for_each_entry(mode, &connector->modes, head)
        {   
            drm_mode_convert_to_umode(&modes[copy_count++], mode);
            if (copy_count == MODE_BUF_SIZE) {

                device_id_ken = (struct drm_mode_modeinfo*)(uintptr_t)rt_malloc( copy_count * sizeof(struct drm_mode_modeinfo));
                lwp_get_from_user(device_id_ken, mode_ptr,copy_count * sizeof( struct drm_mode_modeinfo ));
                rt_memcpy(device_id_ken, modes, copy_count * sizeof(modes[0]));
                lwp_put_to_user( mode_ptr,device_id_ken , copy_count * sizeof( struct drm_mode_modeinfo ));
                rt_free(device_id_ken);

                mode_ptr += copy_count;
                copy_count = 0;

            }
        }

        if (copy_count) {

            device_id_ken = (struct drm_mode_modeinfo*)(uintptr_t)rt_malloc( copy_count * sizeof(struct drm_mode_modeinfo));
            lwp_get_from_user(device_id_ken, mode_ptr,copy_count * sizeof( struct drm_mode_modeinfo ));
            rt_memcpy(device_id_ken, &modes, copy_count * sizeof(modes[0]));
            lwp_put_to_user( mode_ptr,device_id_ken , copy_count * sizeof( struct drm_mode_modeinfo ));
            rt_free(device_id_ken);
        }
    }

    out_resp.count_modes = modes_count;
    if (connector->encoder) {
        out_resp.encoder_id = connector->encoder->base.id;
    } else {
        out_resp.encoder_id = 0;
    }
    
    lwp_put_to_user(data,&out_resp,sizeof(out_resp));
    return 0;
}


