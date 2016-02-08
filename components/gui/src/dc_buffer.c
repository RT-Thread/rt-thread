/*
 * File      : dc_buffer.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 */
#include <rtgui/rtgui.h>
#include <rtgui/dc.h>
#include <rtgui/blit.h>
#include <rtgui/dc_hw.h>
#include <rtgui/color.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/dc_draw.h>

#include <string.h>

static rt_bool_t rtgui_dc_buffer_fini(struct rtgui_dc *dc);
static void rtgui_dc_buffer_draw_point(struct rtgui_dc *dc, int x, int y);
static void rtgui_dc_buffer_draw_color_point(struct rtgui_dc *dc, int x, int y, rtgui_color_t color);
static void rtgui_dc_buffer_draw_vline(struct rtgui_dc *dc, int x, int y1, int y2);
static void rtgui_dc_buffer_draw_hline(struct rtgui_dc *dc, int x1, int x2, int y);
static void rtgui_dc_buffer_fill_rect(struct rtgui_dc *dc, struct rtgui_rect *rect);
static void rtgui_dc_buffer_blit_line(struct rtgui_dc *self, int x1, int x2, int y, rt_uint8_t *line_data);
static void rtgui_dc_buffer_blit(struct rtgui_dc *self, struct rtgui_point *dc_point,
                                 struct rtgui_dc *dest, rtgui_rect_t *rect);

const struct rtgui_dc_engine dc_buffer_engine =
{
    rtgui_dc_buffer_draw_point,
    rtgui_dc_buffer_draw_color_point,
    rtgui_dc_buffer_draw_vline,
    rtgui_dc_buffer_draw_hline,
    rtgui_dc_buffer_fill_rect,
    rtgui_dc_buffer_blit_line,
    rtgui_dc_buffer_blit,

    rtgui_dc_buffer_fini,
};

#define _dc_get_pitch(dc) 			\
	(dc->pitch)
#define _dc_get_pixel(dc, x, y)		\
	((dc)->pixel + (y) * (dc)->pitch + (x) * rtgui_color_get_bpp((dc)->pixel_format))
#define _dc_get_bits_per_pixel(dc)	\
	rtgui_color_get_bits(dc->pixel_format)

#define _hw_get_pixel(dst, x, y, type)  \
		(type *)((rt_uint8_t*)((dst)->framebuffer) + (y) * (dst)->pitch + (x) * _UI_BITBYTES((dst)->bits_per_pixel))

struct rtgui_dc *rtgui_dc_buffer_create(int w, int h)
{
	rt_uint8_t pixel_format;

	pixel_format = rtgui_graphic_driver_get_default()->pixel_format;

	/* create a dc_buffer with hardware driver pixel format */
	return rtgui_dc_buffer_create_pixformat(pixel_format, w, h);
}
RTM_EXPORT(rtgui_dc_buffer_create);

struct rtgui_dc *rtgui_dc_buffer_create_pixformat(rt_uint8_t pixel_format, int w, int h)
{
	struct rtgui_dc_buffer *dc;

	dc = (struct rtgui_dc_buffer *)rtgui_malloc(sizeof(struct rtgui_dc_buffer));
	if (dc)
	{
		dc->parent.type = RTGUI_DC_BUFFER;
		dc->parent.engine = &dc_buffer_engine;
		dc->gc.foreground = default_foreground;
		dc->gc.background = default_background;
		dc->gc.font = rtgui_font_default();
		dc->gc.textalign = RTGUI_ALIGN_LEFT | RTGUI_ALIGN_TOP;
		dc->pixel_format = pixel_format;

		dc->width = w;
		dc->height = h;
		dc->pitch = w * rtgui_color_get_bpp(pixel_format);

		dc->pixel = rtgui_malloc(h * dc->pitch);
		if (!dc->pixel)
		{
			rtgui_free(dc);
			return RT_NULL;
		}
		rt_memset(dc->pixel, 0, h * dc->pitch);

		return &(dc->parent);
	}

	return RT_NULL;
}
RTM_EXPORT(rtgui_dc_buffer_create_pixformat);

struct rtgui_dc *rtgui_dc_buffer_create_from_dc(struct rtgui_dc* dc)
{
    struct rtgui_dc_buffer *buffer;

    if (dc == RT_NULL)
        return RT_NULL;

    if (dc->type == RTGUI_DC_BUFFER)
    {
        struct rtgui_dc_buffer *d = (struct rtgui_dc_buffer*) dc;

        /* buffer clone */
        buffer = (struct rtgui_dc_buffer*)rtgui_dc_buffer_create_pixformat(d->pixel_format,
                                                                           d->width,
                                                                           d->height);
        if (buffer != RT_NULL)
        {
            rt_memcpy(buffer->pixel, d->pixel, d->pitch * d->height);

            return RTGUI_DC(buffer);
        }
    }

    return RT_NULL;
}
RTM_EXPORT(rtgui_dc_buffer_create_from_dc);

rt_uint8_t *rtgui_dc_buffer_get_pixel(struct rtgui_dc *dc)
{
    struct rtgui_dc_buffer *dc_buffer;

    dc_buffer = (struct rtgui_dc_buffer *)dc;

    return dc_buffer->pixel;
}
RTM_EXPORT(rtgui_dc_buffer_get_pixel);

static rt_bool_t rtgui_dc_buffer_fini(struct rtgui_dc *dc)
{
    struct rtgui_dc_buffer *buffer = (struct rtgui_dc_buffer *)dc;

    if (dc->type != RTGUI_DC_BUFFER) return RT_FALSE;

    rtgui_free(buffer->pixel);
    buffer->pixel = RT_NULL;

    return RT_TRUE;
}

static void rtgui_dc_buffer_draw_point(struct rtgui_dc *self, int x, int y)
{
    struct rtgui_dc_buffer *dst;
    unsigned r, g, b, a;

    dst = (struct rtgui_dc_buffer *)self;

    /* does not draw point out of dc */
    if ((x >= dst->width) || (y >= dst->height)) return;
	if (x < 0 || y < 0) return;

	r = RTGUI_RGB_R(dst->gc.foreground);
	g = RTGUI_RGB_G(dst->gc.foreground);
	b = RTGUI_RGB_B(dst->gc.foreground);
	a = RTGUI_RGB_A(dst->gc.foreground);

	switch (dst->pixel_format)
	{
	case RTGRAPHIC_PIXEL_FORMAT_RGB565:
		DRAW_SETPIXELXY_RGB565(x, y);
		break;
	case RTGRAPHIC_PIXEL_FORMAT_BGR565:
		DRAW_SETPIXELXY_BGR565(x, y);
		break;
	case RTGRAPHIC_PIXEL_FORMAT_RGB888:
		DRAW_SETPIXELXY_RGB888(x, y);
		break;
	case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
		DRAW_SETPIXELXY_ARGB8888(x, y);
		break;
	}
}

static void rtgui_dc_buffer_draw_color_point(struct rtgui_dc *self, int x, int y, rtgui_color_t color)
{
	struct rtgui_dc_buffer *dst;
	unsigned r, g, b, a;

	dst = (struct rtgui_dc_buffer *)self;

	/* does not draw point out of dc */
	if ((x >= dst->width) || (y >= dst->height)) return;
	if (x < 0 || y < 0) return;

	r = RTGUI_RGB_R(color);
	g = RTGUI_RGB_G(color);
	b = RTGUI_RGB_B(color);
	a = RTGUI_RGB_A(color);

	switch (dst->pixel_format)
	{
	case RTGRAPHIC_PIXEL_FORMAT_RGB565:
		DRAW_SETPIXELXY_RGB565(x, y);
		break;
	case RTGRAPHIC_PIXEL_FORMAT_BGR565:
		DRAW_SETPIXELXY_BGR565(x, y);
		break;
	case RTGRAPHIC_PIXEL_FORMAT_RGB888:
		DRAW_SETPIXELXY_RGB888(x, y);
		break;
	case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
		DRAW_SETPIXELXY_ARGB8888(x, y);
		break;
	}
}

static void rtgui_dc_buffer_draw_vline(struct rtgui_dc *self, int x1, int y1, int y2)
{
    struct rtgui_dc_buffer *dst;
    unsigned r, g, b, a;

    dst = (struct rtgui_dc_buffer *)self;

    if (x1 < 0 || x1 >= dst->width) return;
    if (y1 >= dst->height) return;

	if (y1 < 0) y1 = 0;
    if (y2 > dst->height) y2 = dst->height;

	r = RTGUI_RGB_R(dst->gc.foreground);
	g = RTGUI_RGB_G(dst->gc.foreground);
	b = RTGUI_RGB_B(dst->gc.foreground);
	a = RTGUI_RGB_A(dst->gc.foreground);

	switch (dst->pixel_format)
	{
	case RTGRAPHIC_PIXEL_FORMAT_RGB565:
		VLINE(rt_uint16_t, DRAW_SETPIXEL_RGB565, 0);
		break;
	case RTGRAPHIC_PIXEL_FORMAT_BGR565:
		VLINE(rt_uint16_t, DRAW_SETPIXEL_BGR565, 0);
		break;
	case RTGRAPHIC_PIXEL_FORMAT_RGB888:
		VLINE(rt_uint16_t, DRAW_SETPIXEL_RGB888, 0);
		break;
	case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
		VLINE(rt_uint32_t, DRAW_SETPIXEL_ARGB8888, 0);
		break;
	}
}

static void rtgui_dc_buffer_draw_hline(struct rtgui_dc *self, int x1, int x2, int y1)
{
    struct rtgui_dc_buffer *dst;
    unsigned r, g, b, a;

    dst = (struct rtgui_dc_buffer *)self;

	/* parameter checking */
    if (y1 < 0 || y1 >= dst->height) return;
    if (x1 >= dst->width) return;

	if (x1 < 0) x1 = 0;
    if (x2 > dst->width) x2 = dst->width;

	r = RTGUI_RGB_R(dst->gc.foreground);
	g = RTGUI_RGB_G(dst->gc.foreground);
	b = RTGUI_RGB_B(dst->gc.foreground);
	a = RTGUI_RGB_A(dst->gc.foreground);

	switch (dst->pixel_format)
	{
	case RTGRAPHIC_PIXEL_FORMAT_RGB565:
		HLINE(rt_uint16_t, DRAW_SETPIXEL_RGB565, 0);
		break;
	case RTGRAPHIC_PIXEL_FORMAT_BGR565:
		HLINE(rt_uint16_t, DRAW_SETPIXEL_BGR565, 0);
		break;
	case RTGRAPHIC_PIXEL_FORMAT_RGB888:
		HLINE(rt_uint16_t, DRAW_SETPIXEL_RGB888, 0);
		break;
	case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
		HLINE(rt_uint32_t, DRAW_SETPIXEL_ARGB8888, 0);
		break;
	}
}

static void rtgui_dc_buffer_fill_rect(struct rtgui_dc *self, struct rtgui_rect *dst_rect)
{
    struct rtgui_dc_buffer *dst;
	unsigned r, g, b, a;
	rtgui_rect_t _r, *rect;

    RT_ASSERT(self);
	if (dst_rect == RT_NULL) rtgui_dc_get_rect(self, &_r);
	else _r = *dst_rect;

    dst = (struct rtgui_dc_buffer *)self;

	if (_r.x2 < 0 || _r.y2 < 0) return; /* out of rect */

	/* parameter checking */
    if (_r.x1 >= dst->width)
        return;
    else if (_r.x1 < 0)
        _r.x1 = 0;
    if (_r.x2 > dst->width)
        _r.x2 = dst->width;

    if (_r.y1 >= dst->height)
        return;
    else if (_r.y1 < 0)
        _r.y1 = 0;
    if (_r.y2 > dst->height)
        _r.y2 = dst->height;
	rect = &_r;

	r = RTGUI_RGB_R(dst->gc.background);
	g = RTGUI_RGB_G(dst->gc.background);
	b = RTGUI_RGB_B(dst->gc.background);
	a = RTGUI_RGB_A(dst->gc.background);

	switch (dst->pixel_format)
	{
		case RTGRAPHIC_PIXEL_FORMAT_RGB565:
			FILLRECT(rt_uint16_t, DRAW_SETPIXEL_RGB565);
			break;
		case RTGRAPHIC_PIXEL_FORMAT_BGR565:
			FILLRECT(rt_uint16_t, DRAW_SETPIXEL_BGR565);
			break;
		case RTGRAPHIC_PIXEL_FORMAT_RGB888:
			FILLRECT(rt_uint32_t, DRAW_SETPIXEL_RGB888);
			break;
		case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
			FILLRECT(rt_uint32_t, DRAW_SETPIXEL_ARGB8888);
			break;
	}
}

/* blit a dc to another dc */
static void rtgui_dc_buffer_blit(struct rtgui_dc *self,
                                 struct rtgui_point *dc_pt,
                                 struct rtgui_dc *dest,
                                 rtgui_rect_t *rect)
{
	int pitch;
	rt_uint16_t rect_width, rect_height;
	struct rtgui_rect _rect, *dest_rect;
    struct rtgui_point dc_point;
    struct rtgui_dc_buffer *dc = (struct rtgui_dc_buffer *)self;

    if (rtgui_dc_get_visible(dest) == RT_FALSE)
        return;

	/* use the (0,0) origin point */
    if (dc_pt == RT_NULL)
        dc_point = rtgui_empty_point;
    else
    {
        dc_point = *dc_pt;
    }

    rtgui_dc_get_rect(dest, &_rect);
	/* use the rect of dest dc */
	if (rect == RT_NULL)
	{
		dest_rect = &_rect;
	}
	else
    {
        dest_rect = rect;
        if (dest_rect->x1 >= _rect.x2 || dest_rect->y1 >= _rect.y2)
            return;
        if (dest_rect->x1 < 0)
        {
            if (-dest_rect->x1 >= dc->width)
                return;
            dc_point.x += -dest_rect->x1;
            dest_rect->x1 = 0;
        }
        if (dest_rect->y1 < 0)
        {
            if (-dest_rect->y1 >= dc->height)
                return;
            dc_point.y += -dest_rect->y1;
            dest_rect->y1 = 0;
        }
        if (dest_rect->x2 > _rect.x2)
            dest_rect->x2 = _rect.x2;
        if (dest_rect->y2 > _rect.y2)
            dest_rect->y2 = _rect.y2;
    }

	if (dest_rect->x2 < dest_rect->x1 || dest_rect->y2 < dest_rect->y1) return;
    if (dc_point.x >= dc->width || dc_point.y >= dc->height) return;

	/* get the minimal width and height */
	rect_width  = _UI_MIN(rtgui_rect_width(*dest_rect), dc->width - dc_point.x);
	rect_height = _UI_MIN(rtgui_rect_height(*dest_rect), dc->height - dc_point.y);

    if ((dest->type == RTGUI_DC_HW) || (dest->type == RTGUI_DC_CLIENT))
    {
		int index;
        rt_uint8_t *line_ptr, *pixels;
        rtgui_blit_line_func blit_line;
		struct rtgui_graphic_driver *hw_driver;

		hw_driver = rtgui_graphic_driver_get_default();
        /* prepare pixel line */
		pixels = _dc_get_pixel(dc, dc_point.x, dc_point.y);

        if (hw_driver->bits_per_pixel == _dc_get_bits_per_pixel(dc))
        {
			if (dest->type == RTGUI_DC_HW && hw_driver->framebuffer != RT_NULL)
			{
				rt_uint8_t *hw_pixels;
				struct rtgui_dc_hw *hw;

				hw = (struct rtgui_dc_hw*)dest;

				/* NOTES: the rect of DC is the logic coordination.
				 * It should be converted to client
				 */
				if (dest_rect != &_rect)
				{
					/* use local rect */
					_rect = *dest_rect;
					dest_rect = &_rect;
				}
				rtgui_rect_moveto(dest_rect, hw->owner->extent.x1, hw->owner->extent.y1);

				pitch = rtgui_color_get_bpp(hw_driver->pixel_format) * rect_width;
				hw_pixels = (rt_uint8_t*)(hw_driver->framebuffer + dest_rect->y1 * hw_driver->pitch +
					dest_rect->x1 * rtgui_color_get_bpp(hw_driver->pixel_format));

				/* do the blit with memory copy */
				for (index = 0; index < rect_height; index ++)
				{
					rt_memcpy(hw_pixels, pixels, pitch);
					pixels += dc->pitch;
					hw_pixels += hw_driver->pitch;
				}
			}
			else
			{
	            /* it's the same bits per pixel, draw it directly */
	            for (index = dest_rect->y1; index < dest_rect->y1 + rect_height; index++)
	            {
	                dest->engine->blit_line(dest, dest_rect->x1, dest_rect->x1 + rect_width, index, pixels);
					pixels += dc->pitch;
	            }
			}
        }
        else
        {
			struct rtgui_graphic_driver *hw_driver;

			hw_driver = rtgui_graphic_driver_get_default();

			if ((dc->pixel_format == RTGRAPHIC_PIXEL_FORMAT_ARGB888) &&
                (dest->type == RTGUI_DC_HW) &&
				(hw_driver->framebuffer != RT_NULL) &&
				(hw_driver->pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB565))
			{
				/* do the fast ARGB to RGB565 blit */
				struct rtgui_blit_info info;
				struct rtgui_widget *owner;

				/* blit source */
				info.src = _dc_get_pixel(dc, dc_point.x, dc_point.y);
				info.src_fmt = dc->pixel_format;
				info.src_h = rect_height;
				info.src_w = rect_width;
				info.src_pitch = dc->pitch;
				info.src_skip = info.src_pitch - info.src_w * rtgui_color_get_bpp(dc->pixel_format);

				owner = ((struct rtgui_dc_hw*)dest)->owner;

				/* blit destination */
				info.dst = (rt_uint8_t*)hw_driver->framebuffer;
				info.dst = info.dst + (owner->extent.y1 + dest_rect->y1) * hw_driver->pitch +
                    (owner->extent.x1 + dest_rect->x1) * rtgui_color_get_bpp(hw_driver->pixel_format);
				info.dst_fmt = hw_driver->pixel_format;
				info.dst_h = rect_height;
				info.dst_w = rect_width;
				info.dst_pitch = hw_driver->pitch;
				info.dst_skip = info.dst_pitch - info.dst_w * rtgui_color_get_bpp(hw_driver->pixel_format);

				rtgui_blit(&info);
			}
			else
			{
				/* calculate pitch */
				pitch = rect_width * rtgui_color_get_bpp(dc->pixel_format);

	            /* get blit line function */
	            blit_line = rtgui_blit_line_get(_UI_BITBYTES(hw_driver->bits_per_pixel),
                                                rtgui_color_get_bpp(dc->pixel_format));
				if (hw_driver->framebuffer != RT_NULL)
				{
					struct rtgui_widget* owner;
					if (dest->type == RTGUI_DC_HW) owner = ((struct rtgui_dc_hw*) dest)->owner;
					else if (dest->type == RTGUI_DC_CLIENT) owner = RTGUI_CONTAINER_OF(dest, struct rtgui_widget, dc_type);
					else RT_ASSERT(0);

					/* change the logic coordinate to the device coordinate */
					rtgui_rect_moveto(dest_rect, owner->extent.x1, owner->extent.y1);

					for (index = dest_rect->y1; index < dest_rect->y1 + rect_height; index ++)
					{
						line_ptr = _hw_get_pixel(hw_driver, dest_rect->x1, index, rt_uint8_t);
						blit_line(line_ptr, (rt_uint8_t*)pixels, pitch);
						pixels += dc->pitch;
					}
				}
				else
				{
		            /* calculate pitch */
		            pitch = rect_width * rtgui_color_get_bpp(dc->pixel_format);
		            /* create line buffer */
		            line_ptr = (rt_uint8_t *) rtgui_malloc(rect_width * _UI_BITBYTES(hw_driver->bits_per_pixel));

		            /* draw each line */
		            for (index = dest_rect->y1; index < dest_rect->y1 + rect_height; index ++)
		            {
		                /* blit on line buffer */
		                blit_line(line_ptr, (rt_uint8_t *)pixels, pitch);
		                pixels += dc->pitch;

		                /* draw on hardware dc */
		                dest->engine->blit_line(dest, dest_rect->x1, dest_rect->x1 + rect_width,
	                                            index, line_ptr);
		            }

		            /* release line buffer */
		            rtgui_free(line_ptr);
				}
			}
        }
    }
	else if (dest->type == RTGUI_DC_BUFFER)
	{
		struct rtgui_dc_buffer *dest_dc = (struct rtgui_dc_buffer*)dest;

		if (dest_dc->pixel_format == dc->pixel_format && dest_dc->pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB565)
		{
			int index;
			rt_uint8_t *pixels, *dest_pixels;

			/* get pitch */
			pitch = rect_width * rtgui_color_get_bpp(dc->pixel_format);

			pixels = _dc_get_pixel(dc, dc_point.x, dc_point.y);
			dest_pixels = _dc_get_pixel(dest_dc, dest_rect->x1, dest_rect->y1);

			for (index = 0; index < rect_height; index ++)
			{
				rt_memcpy(dest_pixels, pixels, pitch);
				pixels += dc->pitch;
				dest_pixels += dest_dc->pitch;
			}
		}
		else /* use rtgui_blit to handle buffer blit */
		{
			/* do the fast ARGB to RGB565 blit */
			struct rtgui_blit_info info;

			/* blit source */
			info.src = _dc_get_pixel(dc, dc_point.x, dc_point.y);
			info.src_fmt = dc->pixel_format;
			info.src_h = rect_height;
			info.src_w = rect_width;
			info.src_pitch = dc->pitch;
			info.src_skip = info.src_pitch - info.src_w * rtgui_color_get_bpp(dc->pixel_format);

			/* blit destination */
			info.dst = _dc_get_pixel(dest_dc, dest_rect->x1, dest_rect->y1);
			info.dst_fmt = dest_dc->pixel_format;
			info.dst_h = rect_height;
			info.dst_w = rect_width;
			info.dst_pitch = dest_dc->pitch;
			info.dst_skip = info.dst_pitch - info.dst_w * rtgui_color_get_bpp(dest_dc->pixel_format);

			rtgui_blit(&info);
		}
	}
}

static void rtgui_dc_buffer_blit_line(struct rtgui_dc *self, int x1, int x2, int y, rt_uint8_t *line_data)
{
	rt_uint8_t *pixel;
    struct rtgui_dc_buffer *dc = (struct rtgui_dc_buffer *)self;

    RT_ASSERT(dc != RT_NULL);
    RT_ASSERT(line_data != RT_NULL);

    /* out of range */
    if ((x1 >= dc->width) || (y >= dc->height) || y < 0 || x1 == x2)
        return;

    /* check range */
    if (x1 < 0)
        x1 = 0;
    if (x2 >= dc->width)
        x2 = dc->width-1;

	pixel = _dc_get_pixel(dc,x1,y);
    rt_memcpy(pixel, line_data, (x2 - x1) * rtgui_color_get_bpp(dc->pixel_format));
}

