/*
 * File      : driver.c
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-04     Bernard      first version
 */
#include <rtgui/driver.h>

#ifdef RTGUI_USING_GRAPHIC_DRIVER_LIST
struct rtgui_list_node _rtgui_graphic_driver_list = {RT_NULL};

void rtgui_graphic_driver_add(struct rtgui_graphic_driver* driver)
{
	rtgui_list_insert(&_rtgui_graphic_driver_list, &(driver->list));
}

void rtgui_graphic_driver_remove(struct rtgui_graphic_driver* driver)
{
	rtgui_list_remove(&_rtgui_graphic_driver_list, &(driver->list));
}

struct rtgui_graphic_driver* rtgui_graphic_driver_find(char* name)
{
	struct rtgui_list_node* node;
	struct rtgui_graphic_driver* driver;

	/* search in list */
	rtgui_list_foreach(node, &(_rtgui_graphic_driver_list))
	{
		driver = rtgui_list_entry(node, struct rtgui_graphic_driver, list);

		/* find it */
		if (rt_strncmp(driver->name, name, RTGUI_NAME_MAX) == 0)
		{
			return driver;
		}
	}

	return RT_NULL;
}

struct rtgui_graphic_driver* rtgui_graphic_driver_get_default()
{
	return rtgui_list_entry(_rtgui_graphic_driver_list.next,
		struct rtgui_graphic_driver, list);
}
#else
static const struct rtgui_graphic_driver* _default_graphic_driver = RT_NULL;

void rtgui_graphic_driver_add(const struct rtgui_graphic_driver* driver)
{
	_default_graphic_driver = driver;
}

const struct rtgui_graphic_driver* rtgui_graphic_driver_get_default()
{
	return _default_graphic_driver;
}
#endif


void rtgui_graphic_driver_get_rect(const struct rtgui_graphic_driver *driver, rtgui_rect_t *rect)
{
	RT_ASSERT(rect != RT_NULL);
	RT_ASSERT(driver != RT_NULL);

	rect->x1 = rect->y1 = 0;
	rect->x2 = driver->width;
	rect->y2 = driver->height;
}

void rtgui_graphic_driver_get_default_rect(rtgui_rect_t *rect)
{
	/* return default the extent of default driver */
	rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(), rect);
}

