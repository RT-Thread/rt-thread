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
#include "inc/drm_mode_config.h"
#include "inc/drm_plane.h"
#include "inc/drm_crtc.h"
#include "inc/drm_encoder.h"


void drm_mode_config_init(struct drm_device* dev)
{
    struct drm_mode_config* config = &dev->mode_config;
    
    rt_list_init(&config->fb_list);
    rt_list_init(&config->crtc_list);
    rt_list_init(&config->connector_list);
    rt_list_init(&config->encoder_list);
    rt_list_init(&config->plane_list);
    idr_init_new(&config->object_idr);
    config->num_fb = 0;
    config->num_crtc = 0;
    config->num_encoder = 0;
    config->num_connector = 0;
    config->num_total_plane = 0;

}

void drm_mode_config_reset(struct drm_device* dev)
{
    struct drm_crtc* crtc;
    struct drm_plane* plane;

    drm_for_each_plane(plane, dev)
    {
        if (plane->state) {
            rt_free(plane->state);
        }
        plane->state = rt_malloc(sizeof(*plane->state));
        rt_memset(plane->state, 0, sizeof(*plane->state));
    }
    drm_for_each_crtc(crtc, dev)
    {
        if (crtc->state) {
            rt_free(crtc->state);
        }
        crtc->state = rt_malloc(sizeof(*crtc->state));
        rt_memset(crtc->state, 0, sizeof(*crtc->state));
        crtc->state->crtc = crtc;
    }
}

int drm_mode_getresources(struct drm_device* dev,  void* data)
{
    struct drm_mode_card_res  card_res;
    lwp_get_from_user(&card_res,data,sizeof(card_res));

    struct drm_mode_config* config = &dev->mode_config;
    struct drm_crtc* crtc;
    struct drm_encoder* encoder;
    struct drm_connector* connector;
#define ID_BUF_SIZE 32
    uint32_t id_buf[ID_BUF_SIZE], *crtc_id, *encoder_id, *connector_id;
    int count, copy_count;
    rt_uint32_t *device_id_ken ;

    count = copy_count = 0;
    card_res.count_fbs = count;

    card_res.max_width = config->max_width;
    card_res.max_height = config->max_height;
    card_res.min_width = config->min_width;
    card_res.max_width = config->max_width; 

    count = copy_count = 0;
    crtc_id = (void*)((uintptr_t)card_res.crtc_id_ptr);
   
    drm_for_each_crtc(crtc, dev)
    {
        if (count < card_res.count_crtcs) {
            id_buf[copy_count++] = crtc->base.id;
            
            if (copy_count == ID_BUF_SIZE) {
                device_id_ken = (void*)(uintptr_t)rt_malloc(copy_count * sizeof(id_buf[0]));
                lwp_get_from_user(device_id_ken,crtc_id, sizeof( device_id_ken ));
                rt_memcpy(device_id_ken,id_buf, copy_count * sizeof(id_buf[0]));
                lwp_put_to_user( crtc_id,device_id_ken , sizeof( device_id_ken ));
                rt_free(device_id_ken);
                crtc_id += copy_count;
                copy_count = 0;
            }
        }
        count++;
    }

    if (copy_count) {
        device_id_ken = (void*)(uintptr_t)rt_malloc(copy_count * sizeof(id_buf[0]));
        lwp_get_from_user(device_id_ken,crtc_id, sizeof( device_id_ken ));
        rt_memcpy(device_id_ken,id_buf, copy_count * sizeof(id_buf[0]));
        lwp_put_to_user( crtc_id,device_id_ken , sizeof( device_id_ken ));
        rt_free(device_id_ken);

    }
    card_res.count_crtcs = count;

    count = copy_count = 0;
    encoder_id = (void*)((uintptr_t)card_res.encoder_id_ptr);


    drm_for_each_encoder(encoder, dev)
    {
      
        if (count < card_res.count_encoders) {
            
            id_buf[copy_count++] = encoder->base.id;

            if (copy_count == ID_BUF_SIZE) {
                device_id_ken = (void*)(uintptr_t)rt_malloc(copy_count * sizeof(id_buf[0]));
                lwp_get_from_user(device_id_ken,encoder_id, sizeof( device_id_ken ));
                rt_memcpy(device_id_ken,id_buf, copy_count * sizeof(id_buf[0]));
                lwp_put_to_user( encoder_id,device_id_ken , sizeof( device_id_ken ));
                rt_free(device_id_ken);

                encoder_id += copy_count;
                copy_count = 0;
            }
        }

        count++;
    }

    if (copy_count) {
        device_id_ken = (void*)(uintptr_t)rt_malloc(copy_count * sizeof(id_buf[0]));
        lwp_get_from_user(device_id_ken,encoder_id, sizeof( device_id_ken ));
        rt_memcpy(device_id_ken,id_buf, copy_count * sizeof(id_buf[0]));
        lwp_put_to_user( encoder_id,device_id_ken , sizeof( device_id_ken ));
        rt_free(device_id_ken);
    }
    card_res.count_encoders = count;

    count = copy_count = 0;
    connector_id = (void*)((uintptr_t)card_res.connector_id_ptr);
    drm_for_each_connector(connector, dev)
    {
        if (count < card_res.count_connectors) {
           
            id_buf[copy_count++] = connector->base.id;
            if (copy_count == ID_BUF_SIZE) {
                device_id_ken = (void*)(uintptr_t)rt_malloc(copy_count * sizeof(id_buf[0]));
                lwp_get_from_user(device_id_ken,connector_id, sizeof( device_id_ken ));
                rt_memcpy(device_id_ken,id_buf, copy_count * sizeof(id_buf[0]));
                lwp_put_to_user( connector_id,device_id_ken , sizeof( device_id_ken ));
                rt_free(device_id_ken);
                connector_id += copy_count;
            }
        }
        count++;
    }
    if (copy_count) {

        device_id_ken = (void*)(uintptr_t)rt_malloc(copy_count * sizeof(id_buf[0]));
        lwp_get_from_user(device_id_ken,connector_id, sizeof( device_id_ken ));
        rt_memcpy(device_id_ken,id_buf, copy_count * sizeof(id_buf[0]));
        lwp_put_to_user( connector_id,device_id_ken , sizeof( device_id_ken ));
        rt_free(device_id_ken);
    }
    card_res.count_connectors = count;
    lwp_put_to_user(data,&card_res,sizeof(card_res));
    return 0;
}
