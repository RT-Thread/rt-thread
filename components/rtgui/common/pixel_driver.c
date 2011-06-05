#include <rtgui/rtgui_system.h>
#include <rtgui/driver.h>

static void _pixeldevice_set_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y)
{
	switch (rtgui_graphic_get_device()->pixel_format)
	{
	case PIXEL_FORMAT_RGB565:
		{		
		rt_uint16_t pixel;
		pixel = rtgui_color_to_565(*c);
		rt_device_write(rtgui_graphic_get_device()->device, PIXEL_POSITION(x, y), &pixel, 
			sizeof(pixel));
		}
		break;

	case PIXEL_FORMAT_RGB888:
		{
		rt_uint32_t pixel;
		pixel = rtgui_color_to_888(*c);
		rt_device_write(rtgui_graphic_get_device()->device, PIXEL_POSITION(x, y), &pixel, 
			3);
		}

		break;
	}
}

static void _pixeldevice_get_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y)
{
	switch (rtgui_graphic_get_device()->pixel_format)
	{
	case PIXEL_FORMAT_RGB565:
		{
		rt_uint16_t pixel;
		rt_device_read(rtgui_graphic_get_device()->device, PIXEL_POSITION(x, y), &pixel, 
			rtgui_graphic_get_device()->byte_per_pixel);
		/* get pixel from color */
		*c = rtgui_color_from_565(pixel);
		}
		break;

	case PIXEL_FORMAT_RGB888:
		{
			rt_uint32_t pixel;
			rt_device_read(rtgui_graphic_get_device()->device, PIXEL_POSITION(x, y), &pixel, 
				3);
			/* get pixel from color */
			*c = rtgui_color_from_888(pixel);
		}
		break;
	}
}

static void _pixeldevice_draw_hline(rtgui_color_t *c, rt_base_t x1, rt_base_t x2, rt_base_t y)
{
	rt_ubase_t index;

	for (index = x1; index < x2; index ++)
		_pixeldevice_set_pixel(c, index, y);
}

static void _pixeldevice_vline(rtgui_color_t *c, rt_base_t x , rt_base_t y1, rt_base_t y2)
{
	rt_ubase_t index;

	for (index = y1; index < y2; index ++)
		_pixeldevice_set_pixel(c, x, index);
}

/* draw raw hline */
static void _pixeldevice_draw_raw_hline(rt_uint8_t *pixels, rt_base_t x1, rt_base_t x2, rt_base_t y)
{
	rt_device_write(rtgui_graphic_get_device()->device, PIXEL_POSITION(x1, y), pixels, 
		(x2 - x1) * rtgui_graphic_get_device()->byte_per_pixel);
}

/* pixel device */
const struct rtgui_graphic_driver_ops _pixeldevice_ops = 
{
	_pixeldevice_set_pixel,
	_pixeldevice_get_pixel,
	_pixeldevice_draw_hline,
	_pixeldevice_vline,
	_pixeldevice_draw_raw_hline,
};

const struct rtgui_graphic_driver_ops *rtgui_pixel_device_get_ops(int pixel_format)
{
	return &_pixeldevice_ops;
}

