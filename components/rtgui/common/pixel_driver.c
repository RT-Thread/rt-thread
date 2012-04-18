#include <rtgui/rtgui_system.h>
#include <rtgui/driver.h>

#define gfx_device		(rtgui_graphic_get_device()->device)
#define gfx_device_ops 	rt_graphix_ops(gfx_device)

static void _pixel_rgb565p_set_pixel(rtgui_color_t *c, int x, int y)
{
	rt_uint16_t pixel;

	pixel = rtgui_color_to_565p(*c);
	gfx_device_ops->set_pixel((char*)&pixel, x, y);
}

static void _pixel_rgb565_set_pixel(rtgui_color_t *c, int x, int y)
{
	rt_uint16_t pixel;

	pixel = rtgui_color_to_565(*c);
	gfx_device_ops->set_pixel((char*)&pixel, x, y);
}

static void _pixel_rgb888_set_pixel(rtgui_color_t *c, int x, int y)
{
	rt_uint32_t pixel;

	pixel = rtgui_color_to_888(*c);
	gfx_device_ops->set_pixel((char*)&pixel, x, y);
}

static void _pixel_rgb565p_get_pixel(rtgui_color_t *c, int x, int y)
{
	rt_uint16_t pixel;

	gfx_device_ops->get_pixel((char*)&pixel, x, y);
	*c = rtgui_color_from_565p(pixel);
}

static void _pixel_rgb565_get_pixel(rtgui_color_t *c, int x, int y)
{
	rt_uint16_t pixel;

	gfx_device_ops->get_pixel((char*)&pixel, x, y);
	*c = rtgui_color_from_565(pixel);
}

static void _pixel_rgb888_get_pixel(rtgui_color_t *c, int x, int y)
{
	rt_uint32_t pixel;

	gfx_device_ops->get_pixel((char*)&pixel, x, y);
	*c = rtgui_color_from_888(pixel);
}

static void _pixel_rgb565p_draw_hline(rtgui_color_t *c, int x1, int x2, int y)
{
	rt_uint16_t pixel;

	pixel = rtgui_color_to_565p(*c);
	gfx_device_ops->draw_hline((char*)&pixel, x1, x2, y);
}

static void _pixel_rgb565_draw_hline(rtgui_color_t *c, int x1, int x2, int y)
{
	rt_uint16_t pixel;

	pixel = rtgui_color_to_565(*c);
	gfx_device_ops->draw_hline((char*)&pixel, x1, x2, y);
}

static void _pixel_rgb888_draw_hline(rtgui_color_t *c, int x1, int x2, int y)
{
	rt_uint32_t pixel;

	pixel = rtgui_color_to_888(*c);
	gfx_device_ops->draw_hline((char*)&pixel, x1, x2, y);
}

static void _pixel_rgb565p_draw_vline(rtgui_color_t *c, int x, int y1, int y2)
{
	rt_uint16_t pixel;

	pixel = rtgui_color_to_565p(*c);
	gfx_device_ops->draw_vline((char*)&pixel, x, y1, y2);
}

static void _pixel_rgb565_draw_vline(rtgui_color_t *c, int x, int y1, int y2)
{
	rt_uint16_t pixel;

	pixel = rtgui_color_to_565(*c);
	gfx_device_ops->draw_vline((char*)&pixel, x, y1, y2);
}

static void _pixel_rgb888_draw_vline(rtgui_color_t *c, int x, int y1, int y2)
{
	rt_uint32_t pixel;

	pixel = rtgui_color_to_888(*c);
	gfx_device_ops->draw_vline((char*)&pixel, x, y1, y2);
}

static void _pixel_draw_raw_hline(rt_uint8_t *pixels, int x1, int x2, int y)
{
	if (x2 > x1)
		gfx_device_ops->blit_line((char*)pixels, x1, y, (x2 - x1));
	else
		gfx_device_ops->blit_line((char*)pixels, x2, y, (x1 - x2));	
}

/* pixel device */
const struct rtgui_graphic_driver_ops _pixel_rgb565p_ops = 
{
	_pixel_rgb565p_set_pixel,
	_pixel_rgb565p_get_pixel,
	_pixel_rgb565p_draw_hline,
	_pixel_rgb565p_draw_vline,
	_pixel_draw_raw_hline,
};

const struct rtgui_graphic_driver_ops _pixel_rgb565_ops = 
{
	_pixel_rgb565_set_pixel,
	_pixel_rgb565_get_pixel,
	_pixel_rgb565_draw_hline,
	_pixel_rgb565_draw_vline,
	_pixel_draw_raw_hline,
};

const struct rtgui_graphic_driver_ops _pixel_rgb888_ops = 
{
	_pixel_rgb888_set_pixel,
	_pixel_rgb888_get_pixel,
	_pixel_rgb888_draw_hline,
	_pixel_rgb888_draw_vline,
	_pixel_draw_raw_hline,
};

const struct rtgui_graphic_driver_ops *rtgui_pixel_device_get_ops(int pixel_format)
{
	switch (pixel_format)
	{
	case RTGRAPHIC_PIXEL_FORMAT_RGB565:
		return &_pixel_rgb565_ops;
		
	case RTGRAPHIC_PIXEL_FORMAT_RGB565P:
		return &_pixel_rgb565p_ops;
		
	case RTGRAPHIC_PIXEL_FORMAT_RGB888:
		return &_pixel_rgb888_ops;
	}

	return RT_NULL;
}
