#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <lwp_user_mm.h>



#include "inc/drm_connector.h"
#include "inc/drm_modes.h"
#include "inc/drm_mode_config.h"
#include "inc/drm_plane.h"
#include "inc/drm_encoder.h"
#include "inc/proto.h"



static int drm_crtc_set_config(struct drm_mode_set* set);
static int drm_atomic_set_config(struct drm_mode_set* set,
                                 struct drm_atomic_state* state);
static int drm_atomic_commit(struct drm_atomic_state* state);

int drm_crtc_init_with_planes(struct drm_device* dev, struct drm_crtc* crtc,
                              struct drm_plane* primary,
                              struct drm_plane* cursor)
{
    struct drm_mode_config* config = &dev->mode_config;
    int retval;

    if (config->num_crtc >= 32) {
        return RT_EINVAL;
    }

    crtc->dev = dev;

    retval = drm_mode_object_add(dev, &crtc->base, DRM_MODE_OBJECT_CRTC);
    if (retval) return retval;

    rt_list_insert_after(&dev->mode_config.crtc_list,&crtc->head);
    crtc->index = dev->mode_config.num_crtc++;

    crtc->primary = primary;
    if (primary && !primary->possible_crtcs) {
        primary->possible_crtcs = 1U << crtc->index;
    }

    crtc->cursor = cursor;
    if (cursor && !cursor->possible_crtcs) {
        cursor->possible_crtcs = 1U << crtc->index;
    }

    return 0;
}

int drm_mode_getcrtc(struct drm_device* dev,void* data)
{
    struct drm_mode_crtc crtc_resp;
    struct drm_crtc* crtc;
    struct drm_plane* plane;

    lwp_get_from_user(&crtc_resp,data,sizeof(crtc_resp));
    crtc = drm_crtc_lookup(dev, crtc_resp.crtc_id);
    if (!crtc) return ENOENT;

    plane = crtc->primary;

    if (plane->state && plane->state->fb)
        crtc_resp.fb_id = plane->state->fb->base.id;
    else
        crtc_resp.fb_id = 0;

    if (plane->state) {
        crtc_resp.x = plane->state->src_x >> 16;
        crtc_resp.y = plane->state->src_y >> 16;
    }

    if (crtc->state) {
        if (crtc->state->enable) {
            drm_mode_convert_to_umode(&crtc_resp.mode, &crtc->state->mode);
            crtc_resp.mode_valid = 1;
        } else {
            crtc_resp.mode_valid = 0;
        }
    } else {
        crtc_resp.x = 0;
        crtc_resp.y = 0;
        crtc_resp.mode_valid = 0;
    }

    lwp_put_to_user(data,&crtc_resp,sizeof(crtc_resp));
    return 0;
}

int drm_mode_setcrtc(struct drm_device* dev, void* data)
{
    struct drm_mode_crtc crtc_req ;
    struct drm_mode_config* config = &dev->mode_config;
    struct drm_crtc* crtc;
    struct drm_framebuffer* fb = NULL;
    struct drm_connector* connector;
    struct drm_display_mode* mode = NULL;
    struct drm_connector** connectors = NULL;
    struct drm_mode_set set;
    uint32_t* user_conn_ptr;
    uint32_t* conn_ids = NULL;
    int i, retval;
    uint32_t *device_id_ken = NULL;

    lwp_get_from_user(&crtc_req,data,sizeof(crtc_req));

    crtc = drm_crtc_lookup(dev, crtc_req.crtc_id);
    if (!crtc) return RT_ENOENT;

    if (crtc_req.mode_valid) {
        if (crtc_req.fb_id == -1) {
            retval = RT_EINVAL;
            goto out;
        } else {
            fb = drm_framebuffer_lookup(dev, crtc_req.fb_id);
            if (!fb) {
                retval = RT_EINVAL;
                goto out;
            }
        }

        mode = rt_malloc(sizeof(*mode));
        if (!mode) {
            retval = RT_ENOMEM;
            goto out;
        }

        retval = drm_mode_convert_umode(mode, &crtc_req.mode);
        if (retval) goto out;
    }

    if (crtc_req.count_connectors == 0 && mode) {
        retval = RT_EINVAL;
        goto out;
    }

    if (crtc_req.count_connectors > 0 && (!mode || !fb)) {
        retval = RT_EINVAL;
        goto out;
    }

    if (crtc_req.count_connectors > 0) {
        if (crtc_req.count_connectors > config->num_connector) {
            retval = RT_EINVAL;
            goto out;
        }

        connectors = rt_calloc(sizeof(connectors[0]), crtc_req.count_connectors);
        if (!connectors) {
            retval = RT_ENOMEM;
            goto out;
        }

        conn_ids = rt_calloc(sizeof(conn_ids[0]), crtc_req.count_connectors);
        if (!conn_ids) {
            retval = RT_ENOMEM;
            goto out;
        }
 
        user_conn_ptr = (uint32_t *)(uintptr_t)crtc_req.set_connectors_ptr;
        device_id_ken = (uint32_t *)(uintptr_t)rt_malloc( sizeof(conn_ids[0]) * crtc_req.count_connectors);
        lwp_get_from_user(device_id_ken, user_conn_ptr, sizeof( device_id_ken ));
        rt_memcpy( conn_ids, device_id_ken, sizeof(conn_ids[0]) * crtc_req.count_connectors);
        rt_free(device_id_ken);

        for (i = 0; i < crtc_req.count_connectors; i++) {
            connectors[i] = RT_NULL;
            connector = drm_connector_lookup(dev, conn_ids[i]);
            if (!connector) {
                retval = ENOENT;
                rt_free(conn_ids);
                goto out;
            }

            connectors[i] = connector;
        }
    }

    set.crtc = crtc;
    set.x = crtc_req.x;
    set.y = crtc_req.y;
    set.mode = mode;
    set.connectors = connectors;
    set.num_connectors = crtc_req.count_connectors;
    set.fb = fb;


    retval = drm_crtc_set_config(&set);
    lwp_put_to_user( data,&crtc_req , sizeof( crtc_req ));

out:
    if (connectors) rt_free(connectors);

    if (mode) rt_free(mode);
    return retval;
}

static void drm_atomic_state_clear(struct drm_atomic_state* state)
{
    struct drm_device* dev = state->dev;
    struct drm_mode_config* config = &dev->mode_config;
    int i;

    for (i = 0; i < config->num_crtc; i++) {
        if (!state->crtcs[i].ptr) {
            continue;
        }

        rt_free(state->crtcs[i].state);
        rt_memset(&state->crtcs[i], 0, sizeof(state->crtcs[i]));
    }

    for (i = 0; i < config->num_total_plane; i++) {
        if (!state->planes[i].ptr) {
            continue;
        }

        rt_free(state->planes[i].state);
        rt_memset(&state->planes[i], 0, sizeof(state->planes[i]));
    }
}

static void drm_atomic_state_release(struct drm_atomic_state* state)
{
    if (state->crtcs) rt_free(state->crtcs);
    if (state->planes) rt_free(state->planes);
}

static int drm_atomic_state_init(struct drm_device* dev,
                                 struct drm_atomic_state* state)
{
    state->crtcs = rt_calloc(sizeof(*state->crtcs), dev->mode_config.num_crtc);
    if (!state->crtcs) goto err;

    state->planes =
        rt_calloc(sizeof(*state->planes), dev->mode_config.num_total_plane);
    if (!state->planes) goto err;

    state->dev = dev;

    return 0;
err:
    drm_atomic_state_release(state);
    return RT_ENOMEM;
}

static int drm_crtc_set_config(struct drm_mode_set* set)
{
    struct drm_atomic_state state;
    struct drm_crtc* crtc = set->crtc;
    int retval;

    retval = drm_atomic_state_init(crtc->dev, &state);
    if (retval) return retval;

    retval = drm_atomic_set_config(set, &state);
    if (retval) goto out;

    retval = drm_atomic_commit(&state);

out:
    drm_atomic_state_clear(&state);
    drm_atomic_state_release(&state);

    return retval;
}

static int drm_atomic_get_crtc_state(struct drm_atomic_state* state,
                                     struct drm_crtc* crtc,
                                     struct drm_crtc_state** crtc_statep)
{
    struct drm_crtc_state* crtc_state;
    int index = crtc->index;

    crtc_state = state->crtcs[index].state;
    if (crtc_state) {
        *crtc_statep = crtc_state;
        return 0;
    }

    crtc_state = rt_malloc(sizeof(*crtc_state));
    if (!crtc_state) return ENOMEM;

    assert(crtc->state);
    rt_memcpy(crtc_state, crtc->state, sizeof(*crtc_state));

    state->crtcs[index].ptr = crtc;
    state->crtcs[index].state = crtc_state;
    state->crtcs[index].old_state = crtc->state;
    state->crtcs[index].new_state = crtc_state;

    *crtc_statep = crtc_state;
    return 0;
}

static int drm_atomic_get_plane_state(struct drm_atomic_state* state,
                                      struct drm_plane* plane,
                                      struct drm_plane_state** plane_statep)
{
    struct drm_plane_state* plane_state;
    int index = plane->index;

    plane_state = state->planes[index].state;
    if (plane_state) {
        *plane_statep = plane_state;
        return 0;
    }

    plane_state =rt_malloc(sizeof(*plane_state));
    if (!plane_state) return RT_ENOMEM;

    assert(plane->state);
    rt_memcpy(plane_state, plane->state, sizeof(*plane_state));

    state->planes[index].ptr = plane;
    state->planes[index].state = plane_state;
    state->planes[index].old_state = plane->state;
    state->planes[index].new_state = plane_state;

    *plane_statep = plane_state;
    return 0;
}

static int drm_atomic_set_mode_for_crtc(struct drm_crtc_state* state,
                                        const struct drm_display_mode* mode)
{
    if (mode) {
        drm_mode_copy(&state->mode, mode);
        state->enable = RT_TRUE;
    } else {
        rt_memset(&state->mode, 0, sizeof(state->mode));
        state->enable = RT_FALSE;
    }

    return 0;
}

static int drm_atomic_set_config(struct drm_mode_set* set,
                                 struct drm_atomic_state* state)
{
    struct drm_crtc_state* crtc_state;
    struct drm_plane_state* primary_state;
    struct drm_crtc* crtc = set->crtc;
    int retval;

    retval = drm_atomic_get_crtc_state(state, crtc, &crtc_state);
    if (retval) return retval;

    retval = drm_atomic_get_plane_state(state, crtc->primary, &primary_state);
    if (retval) return retval;

    retval = drm_atomic_set_mode_for_crtc(crtc_state, set->mode);
    if (retval) return retval;

    primary_state->crtc = crtc;
    primary_state->fb = set->fb;

    primary_state->crtc_x = 0;
    primary_state->crtc_y = 0;
    primary_state->crtc_w = set->mode->hdisplay;
    primary_state->crtc_h = set->mode->vdisplay;
    primary_state->src_x = set->x << 16;
    primary_state->src_y = set->y << 16;
    primary_state->src_w = set->mode->hdisplay << 16;
    primary_state->src_h = set->mode->vdisplay << 16;

    return 0;
}

static int drm_atomic_swap_state(struct drm_atomic_state* state)
{
    struct drm_device* dev = state->dev;
    int i;

    for (i = 0; i < dev->mode_config.num_crtc; i++) {
        state->crtcs[i].state = state->crtcs[i].old_state;
        state->crtcs[i].ptr->state = state->crtcs[i].new_state;
    }

    for (i = 0; i < dev->mode_config.num_total_plane; i++) {
        state->planes[i].state = state->planes[i].old_state;
        state->planes[i].ptr->state = state->planes[i].new_state;
    }

    return 0;
}

static int drm_atomic_commit(struct drm_atomic_state* state)
{
    struct drm_mode_config* config = &state->dev->mode_config;
    int retval;

    retval = drm_atomic_swap_state(state);
    if (retval) return retval;

    config->funcs->commit(state);

    return 0;
}

static int drm_atomic_page_flip_set(struct drm_atomic_state* state,
                                    struct drm_crtc* crtc,
                                    struct drm_framebuffer* fb)
{
    struct drm_crtc_state* crtc_state;
    struct drm_plane_state* primary_state;
    int retval;

    retval = drm_atomic_get_crtc_state(state, crtc, &crtc_state);
    if (retval) return retval;

    retval = drm_atomic_get_plane_state(state, crtc->primary, &primary_state);
    if (retval) return retval;

    primary_state->crtc = crtc;
    primary_state->fb = fb;

    return 0;
}

static void send_vblank_event(struct drm_device* dev,
                              struct drm_pending_vblank_event* e, rt_uint64_t seq,
                              struct timeval* now)
{
    switch (e->event.base.type) {
    case DRM_EVENT_FLIP_COMPLETE:
        e->event.vbl.sequence = seq;
        e->event.vbl.tv_sec = now->tv_sec;
        e->event.vbl.tv_usec = now->tv_usec;
        break;
    }

    drm_send_event(dev, &e->base);
}

void drm_crtc_send_vblank_event(struct drm_crtc* crtc,
                                struct drm_pending_vblank_event* e)
{
    struct drm_device* dev = crtc->dev;
    rt_uint64_t seq;
    unsigned int pipe;
    struct timeval tv;

    pipe = crtc->index;

    seq = 0;
    gettimeofday(&tv, NULL);

    e->pipe = pipe;
    send_vblank_event(dev, e, seq, &tv);
}

int drm_atomic_page_flip(struct drm_crtc* crtc, struct drm_framebuffer* fb,
                         struct drm_pending_vblank_event* event)
{
    struct drm_atomic_state state;
    int retval;

    retval = drm_atomic_state_init(crtc->dev, &state);
    if (retval) return retval;

    retval = drm_atomic_page_flip_set(&state, crtc, fb);
    if (retval) goto out;

    retval = drm_atomic_commit(&state);
        
    if (event) drm_crtc_send_vblank_event(crtc, event);
   
out:
    drm_atomic_state_clear(&state);
    drm_atomic_state_release(&state);

    return retval;
}
