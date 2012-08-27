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
#include <rtthread.h>
#include <rtgui/driver.h>

struct rtgui_graphic_driver _driver;

extern const struct rtgui_graphic_driver_ops *rtgui_pixel_device_get_ops(int pixel_format);
extern const struct rtgui_graphic_driver_ops *rtgui_framebuffer_get_ops(int pixel_format);

/* get default driver */
struct rtgui_graphic_driver* rtgui_graphic_driver_get_default()
{
	return &_driver;
}
RTM_EXPORT(rtgui_graphic_driver_get_default);

void rtgui_graphic_driver_get_rect(const struct rtgui_graphic_driver *driver, rtgui_rect_t *rect)
{
	RT_ASSERT(rect != RT_NULL);
	RT_ASSERT(driver != RT_NULL);

	rect->x1 = rect->y1 = 0;
	rect->x2 = driver->width;
	rect->y2 = driver->height;
}
RTM_EXPORT(rtgui_graphic_driver_get_rect);

rt_err_t rtgui_graphic_set_device(rt_device_t device)
{
	rt_err_t result;
	struct rt_device_graphic_info info;

	/* get framebuffer address */
	result = rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &info);
	if (result != RT_EOK)
	{
		/* get device information failed */
		return -RT_ERROR;
	}

	/* initialize framebuffer driver */
	_driver.device = device;
	_driver.pixel_format = info.pixel_format;
	_driver.bits_per_pixel = info.bits_per_pixel;
	_driver.width = info.width;
	_driver.height = info.height;
	_driver.pitch = _driver.width * _driver.bits_per_pixel/8;
	_driver.framebuffer = info.framebuffer;

	if (info.framebuffer != RT_NULL)
	{
		/* is a frame buffer device */
		_driver.ops = rtgui_framebuffer_get_ops(_driver.pixel_format);
	}
	else
	{
		/* is a pixel device */
		_driver.ops = rtgui_pixel_device_get_ops(_driver.pixel_format);
	}
	
	return RT_EOK;
}
RTM_EXPORT(rtgui_graphic_set_device);

/* screen update */
void rtgui_graphic_driver_screen_update(const struct rtgui_graphic_driver* driver, rtgui_rect_t *rect)
{
	struct rt_device_rect_info rect_info;

	rect_info.x = rect->x1; rect_info.y = rect->y1;
	rect_info.width = rect->x2 - rect->x1; 
	rect_info.height = rect->y2 - rect->y1;
	rt_device_control(driver->device, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);
}
RTM_EXPORT(rtgui_graphic_driver_screen_update);

/* get video frame buffer */
rt_uint8_t* rtgui_graphic_driver_get_framebuffer(const struct rtgui_graphic_driver* driver)
{
	return (rt_uint8_t*)driver->framebuffer;
}
RTM_EXPORT(rtgui_graphic_driver_get_framebuffer);

rt_uint8_t* rtgui_graphic_driver_get_default_framebuffer(void)
{
	return rtgui_graphic_driver_get_framebuffer(&_driver);
}
RTM_EXPORT(rtgui_graphic_driver_get_default_framebuffer);

