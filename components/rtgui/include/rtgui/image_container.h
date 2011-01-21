#ifndef __RTGUI_IMAGE_CONTAINER_H__
#define __RTGUI_IMAGE_CONTAINER_H__

#include <rtgui/rtgui.h>
#include <rtgui/image.h>

void image_container_system_init(void);

rtgui_image_t* image_container_get(const char* filename);
void image_container_put(rtgui_image_t* image);

#endif
