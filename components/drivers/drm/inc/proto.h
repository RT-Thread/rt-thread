#ifndef _LIBDRMDRIVER_PROTO_H_
#define _LIBDRMDRIVER_PROTO_H_

#include "drm_device.h"
#include "drm_framebuffer.h"
#include "drm_crtc.h"
#include "drm_file.h"

void drm_select_retry(struct drm_device* dev);

/* connector.c */
int drm_mode_getconnector(struct drm_device* dev, void* data);

/* crtc.c */
int drm_mode_getcrtc(struct drm_device* dev,void* data);
int drm_mode_setcrtc(struct drm_device* dev,void* data);
int drm_atomic_page_flip(struct drm_crtc* crtc,  struct drm_framebuffer* fb, struct drm_pending_vblank_event* event);

/* dumb_buffer.c */
int drm_mode_create_dumb_ioctl(struct drm_device* dev, void* data) ;
int drm_mode_mmap_dumb_ioctl  (struct drm_device* dev, void* data) ;

/* encoder.c */
int drm_mode_getencoder(struct drm_device* dev,  void* data);

/* framebuffer.c */
int drm_mode_addfb_ioctl(struct drm_device* dev, void* data);
int drm_mode_addfb2_ioctl(struct drm_device* dev, void* data);

/* mode_config.c */
int drm_mode_getresources(struct drm_device* dev,  void* data);
                         

/* gem.c */
void drm_gem_open(struct drm_device* dev);

/* plane.c */
int drm_mode_page_flip_ioctl(struct drm_device* dev, void* data);
// int drm_mode_cursor_ioctl(struct drm_device* dev, endpoint_t endpoint,
//                           void* data);
// int drm_mode_cursor2_ioctl(struct drm_device* dev, endpoint_t endpoint,
//                            void* data);

/* file.c */
int drm_event_reserve(struct drm_device* dev, struct drm_pending_event* p,struct drm_event* e);
void drm_send_event(struct drm_device* dev, struct drm_pending_event* e);

/* mode_object.c */
int drm_mode_obj_get_properties_ioctl(struct drm_device* dev,  void* data);

#endif