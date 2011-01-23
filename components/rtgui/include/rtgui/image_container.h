#ifndef __RTGUI_IMAGE_CONTAINER_H__
#define __RTGUI_IMAGE_CONTAINER_H__

#include <rtgui/rtgui.h>
#include <rtgui/image.h>

#ifdef RTGUI_IMAGE_CONTAINER
/* image item in image container */
struct rtgui_image_item
{
	rtgui_image_t *image;
	char *filename;

	rt_uint32_t refcount;
};
typedef struct rtgui_image_item rtgui_image_item_t;

void rtgui_system_image_container_init(rt_bool_t load);

rtgui_image_item_t* rtgui_image_container_get(const char* filename);
rtgui_image_item_t* rtgui_image_container_get_from_mem(const rt_uint8_t* mem, const char* type, rt_uint32_t len);

void rtgui_image_container_put(rtgui_image_item_t* item);
#endif

#endif
