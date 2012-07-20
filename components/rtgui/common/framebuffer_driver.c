#include <rtgui/rtgui_system.h>
#include <rtgui/driver.h>

#define GET_PIXEL(dst, x, y, type)	\
	(type *)((rt_uint8_t*)((dst)->framebuffer) + (y) * (dst)->pitch + (x) * ((dst)->bits_per_pixel/8))

static void _rgb565_set_pixel(rtgui_color_t *c, int x, int y)
{
	*GET_PIXEL(rtgui_graphic_get_device(), x, y, rt_uint16_t) = rtgui_color_to_565(*c);
}

static void _rgb565_get_pixel(rtgui_color_t *c, int x, int y)
{
	rt_uint16_t pixel;

	pixel = *GET_PIXEL(rtgui_graphic_get_device(), x, y, rt_uint16_t);

	/* get pixel from color */
	*c = rtgui_color_from_565(pixel);
}

static void _rgb565_draw_hline(rtgui_color_t *c, int x1, int x2, int y)
{
	rt_ubase_t index;
	rt_uint16_t pixel;
	rt_uint16_t *pixel_ptr;

	/* get pixel from color */
	pixel = rtgui_color_to_565(*c);

	/* get pixel pointer in framebuffer */
	pixel_ptr = GET_PIXEL(rtgui_graphic_get_device(), x1, y, rt_uint16_t);
	
	for (index = x1; index < x2; index ++)
	{
		*pixel_ptr = pixel;
		pixel_ptr ++;
	}
}

static void _rgb565_draw_vline(rtgui_color_t *c, int x , int y1, int y2)
{
	rt_uint8_t *dst;
	rt_uint16_t pixel;
	rt_ubase_t index;

	pixel = rtgui_color_to_565(*c);
	dst = GET_PIXEL(rtgui_graphic_get_device(), x, y1, rt_uint8_t);
	for (index = y1; index < y2; index ++)
	{
		*(rt_uint16_t*)dst = pixel;
		dst += rtgui_graphic_get_device()->pitch;
	}
}

static void _rgb565p_set_pixel(rtgui_color_t *c, int x, int y)
{
	*GET_PIXEL(rtgui_graphic_get_device(), x, y, rt_uint16_t) = rtgui_color_to_565p(*c);
}

static void _rgb565p_get_pixel(rtgui_color_t *c, int x, int y)
{
	rt_uint16_t pixel;

	pixel = *GET_PIXEL(rtgui_graphic_get_device(), x, y, rt_uint16_t);

	/* get pixel from color */
	*c = rtgui_color_from_565p(pixel);
}

static void _rgb565p_draw_hline(rtgui_color_t *c, int x1, int x2, int y)
{
	rt_ubase_t index;
	rt_uint16_t pixel;
	rt_uint16_t *pixel_ptr;

	/* get pixel from color */
	pixel = rtgui_color_to_565p(*c);

	/* get pixel pointer in framebuffer */
	pixel_ptr = GET_PIXEL(rtgui_graphic_get_device(), x1, y, rt_uint16_t);
	
	for (index = x1; index < x2; index ++)
	{
		*pixel_ptr = pixel;
		pixel_ptr ++;
	}
}

static void _rgb565p_draw_vline(rtgui_color_t *c, int x , int y1, int y2)
{
	rt_uint8_t *dst;
	rt_uint16_t pixel;
	rt_ubase_t index;

	pixel = rtgui_color_to_565p(*c);
	dst = GET_PIXEL(rtgui_graphic_get_device(), x, y1, rt_uint8_t);
	for (index = y1; index < y2; index ++)
	{
		*(rt_uint16_t*)dst = pixel;
		dst += rtgui_graphic_get_device()->pitch;
	}
}

/* draw raw hline */
static void framebuffer_draw_raw_hline(rt_uint8_t *pixels, int x1, int x2, int y)
{
	rt_uint8_t *dst;

	dst = GET_PIXEL(rtgui_graphic_get_device(), x1, y, rt_uint8_t);
	rt_memcpy(dst, pixels, (x2 - x1) * (rtgui_graphic_get_device()->bits_per_pixel/8));
}

const struct rtgui_graphic_driver_ops _framebuffer_rgb565_ops = 
{
	_rgb565_set_pixel,
	_rgb565_get_pixel,
	_rgb565_draw_hline,
	_rgb565_draw_vline,
	framebuffer_draw_raw_hline,
};

const struct rtgui_graphic_driver_ops _framebuffer_rgb565p_ops = 
{
	_rgb565p_set_pixel,
	_rgb565p_get_pixel,
	_rgb565p_draw_hline,
	_rgb565p_draw_vline,
	framebuffer_draw_raw_hline,
};

#define FRAMEBUFFER	(rtgui_graphic_get_device()->framebuffer)
#define MONO_PIXEL(framebuffer, x, y) \
	((rt_uint8_t**)(framebuffer))[y/8][x]

static void _mono_set_pixel(rtgui_color_t *c, int x, int y)
{
	if (*c == white)
		MONO_PIXEL(FRAMEBUFFER, x, y) &= ~(1 << (y%8));
	else
		MONO_PIXEL(FRAMEBUFFER, x, y) |= (1 << (y%8));
}

static void _mono_get_pixel(rtgui_color_t *c, int x, int y)
{
	if (MONO_PIXEL(FRAMEBUFFER, x, y) & (1 << (y%8)))
		*c = black;
	else
		*c = white;
}

static void _mono_draw_hline(rtgui_color_t *c, int x1, int x2, int y)
{
	rt_ubase_t index;
	
	if (*c == white)
		for (index = x1; index < x2; index ++)
		{
			MONO_PIXEL(FRAMEBUFFER, index, y) &= ~(1 << (y%8));
		}
	else
		for (index = x1; index < x2; index ++)
		{
			MONO_PIXEL(FRAMEBUFFER, index, y) |= (1 << (y%8));
		}
}

static void _mono_draw_vline(rtgui_color_t *c, int x , int y1, int y2)
{
	rt_ubase_t index;
	
	if (*c == white)
		for (index = y1; index < y2; index ++)
		{
			MONO_PIXEL(FRAMEBUFFER, x, index) &= ~(1 << (index%8));
		}
	else
		for (index = y1; index < y2; index ++)
		{
			MONO_PIXEL(FRAMEBUFFER, x, index) |=  (1 << (index%8));
		}
}

/* draw raw hline */
static void _mono_draw_raw_hline(rt_uint8_t *pixels, int x1, int x2, int y)
{
	rt_ubase_t index;

	for (index = x1; index < x2; index ++)
	{
		if (pixels[index/8] && (1 << (index % 8)))
			MONO_PIXEL(FRAMEBUFFER, index, y) |=  (1 << (y%8));
		else
			MONO_PIXEL(FRAMEBUFFER, index, y) &= ~(1 << (y%8));
	}
}

const struct rtgui_graphic_driver_ops _framebuffer_mono_ops = 
{
	_mono_set_pixel,
	_mono_get_pixel,
	_mono_draw_hline,
	_mono_draw_vline,
	_mono_draw_raw_hline,
};

const struct rtgui_graphic_driver_ops *rtgui_framebuffer_get_ops(int pixel_format)
{
	switch (pixel_format)
	{
	case RTGRAPHIC_PIXEL_FORMAT_MONO:
		return &_framebuffer_mono_ops;
	case RTGRAPHIC_PIXEL_FORMAT_GRAY4:
		break;
	case RTGRAPHIC_PIXEL_FORMAT_GRAY16:
		break;
	case RTGRAPHIC_PIXEL_FORMAT_RGB565:
		return &_framebuffer_rgb565_ops;
	case RTGRAPHIC_PIXEL_FORMAT_RGB565P:
		return &_framebuffer_rgb565p_ops;
	}

	return RT_NULL;
}

