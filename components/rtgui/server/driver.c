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

struct rtgui_graphic_driver _driver;

extern const struct rtgui_graphic_driver_ops *rtgui_pixel_device_get_ops(int pixel_format);
extern const struct rtgui_graphic_driver_ops *rtgui_framebuffer_get_ops(int pixel_format);

/* get default driver */
struct rtgui_graphic_driver* rtgui_graphic_driver_get_default()
{
	return &_driver;
}

void rtgui_graphic_driver_get_rect(const struct rtgui_graphic_driver *driver, rtgui_rect_t *rect)
{
	RT_ASSERT(rect != RT_NULL);
	RT_ASSERT(driver != RT_NULL);

	rect->x1 = rect->y1 = 0;
	rect->x2 = driver->width;
	rect->y2 = driver->height;
}

rt_err_t rtgui_graphic_set_device(rt_device_t device)
{
	rt_err_t result;
	struct rt_lcd_info info;

	/* get framebuffer address */
	result = rt_device_control(device, LCD_GET_INFO, &info);
	if (result != RT_EOK)
	{
		/* get device information failed */
		return -RT_ERROR;
	}

	/* initialize framebuffer driver */
	_driver.device = device;
	_driver.pixel_format = info.pixel_format;
	_driver.byte_per_pixel = info.byte_per_pixel;
	_driver.width = info.width;
	_driver.height = info.height;
	_driver.pitch = _driver.width * _driver.byte_per_pixel;
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

/* screen update */
void rtgui_graphic_driver_screen_update(struct rtgui_graphic_driver* driver, rtgui_rect_t *rect)
{
	rt_device_control(driver->device, LCD_RECT_UPDATE, rect);
}

/* get video frame buffer */
rt_uint8_t* rtgui_graphic_driver_get_framebuffer(struct rtgui_graphic_driver* driver)
{
	return (rt_uint8_t*)driver->framebuffer;
}

