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
#include <rtgui/color.h>
#include <rtgui/rtgui_system.h>

#ifndef RTGUI_USING_SMALL_SIZE
struct rtgui_dc_buffer
{
	struct rtgui_dc parent;

	/* color and font */
	rtgui_color_t color;
	struct rtgui_font* font;
	/* text align */
	rt_int32_t align;

	/* width and height */
	rt_uint16_t width, height;
	rt_uint16_t pitch;

	/* blit info */
	rt_uint32_t clip_sync;
	rtgui_region_t clip;

	/* pixel data */
	rt_uint8_t* pixel;
};

static rt_bool_t rtgui_dc_buffer_fini(struct rtgui_dc* dc);
static void rtgui_dc_buffer_draw_point(struct rtgui_dc* dc, int x, int y);
static void rtgui_dc_buffer_draw_vline(struct rtgui_dc* dc, int x, int y1, int y2);
static void rtgui_dc_buffer_draw_hline(struct rtgui_dc* dc, int x1, int x2, int y);
static void rtgui_dc_buffer_fill_rect (struct rtgui_dc* dc, struct rtgui_rect* rect);
static void rtgui_dc_buffer_blit(struct rtgui_dc* self, struct rtgui_point* dc_point,
	struct rtgui_dc* dest, rtgui_rect_t* rect);
static void rtgui_dc_buffer_set_color (struct rtgui_dc* dc, rtgui_color_t color);
static rtgui_color_t rtgui_dc_buffer_get_color(struct rtgui_dc* dc);
static void rtgui_dc_buffer_set_font(struct rtgui_dc* dc, rtgui_font_t* font);
static rtgui_font_t* rtgui_dc_buffer_get_font(struct rtgui_dc* dc);
static void rtgui_dc_buffer_set_textalign(struct rtgui_dc* dc, rt_int32_t textalign);
static rt_int32_t rtgui_dc_buffer_get_textalign(struct rtgui_dc* dc);
static rt_bool_t rtgui_dc_buffer_get_visible(struct rtgui_dc* dc);
static void rtgui_dc_buffer_get_rect(struct rtgui_dc* dc, rtgui_rect_t* rect);

static void rtgui_dc_buffer_init(struct rtgui_dc_buffer* dc)
{
	if (dc == RT_NULL) return;

	dc->parent.type = RTGUI_DC_BUFFER;
	dc->parent.draw_point = rtgui_dc_buffer_draw_point;
	dc->parent.draw_hline = rtgui_dc_buffer_draw_hline;
	dc->parent.draw_vline = rtgui_dc_buffer_draw_vline;
	dc->parent.fill_rect  = rtgui_dc_buffer_fill_rect;
	dc->parent.blit		  = rtgui_dc_buffer_blit;

	dc->parent.set_color  = rtgui_dc_buffer_set_color;
	dc->parent.get_color  = rtgui_dc_buffer_get_color;

	dc->parent.set_font	  = rtgui_dc_buffer_set_font;
	dc->parent.get_font	  = rtgui_dc_buffer_get_font;
	dc->parent.set_textalign  = rtgui_dc_buffer_set_textalign;
	dc->parent.get_textalign  = rtgui_dc_buffer_get_textalign;

	dc->parent.get_visible= rtgui_dc_buffer_get_visible;
	dc->parent.get_rect	  = rtgui_dc_buffer_get_rect;

	dc->parent.fini		  = rtgui_dc_buffer_fini;
}

struct rtgui_dc* rtgui_dc_buffer_create(int w, int h)
{
	struct rtgui_dc_buffer* dc;

	dc = (struct rtgui_dc_buffer*)rtgui_malloc(sizeof(struct rtgui_dc_buffer));
	rtgui_dc_buffer_init(dc);
	dc->color	= 0;
	dc->font	= RT_NULL;
	dc->align	= 0;

	dc->width	= w;
	dc->height	= h;
	dc->pitch	= w * sizeof(rtgui_color_t);

	dc->clip_sync = 0;
	rtgui_region_init(&(dc->clip));

	dc->pixel = rtgui_malloc(h * dc->pitch);
	rt_memset(dc->pixel, 0, h * dc->pitch);

	return &(dc->parent);
}

rt_uint8_t* rtgui_dc_buffer_get_pixel(struct rtgui_dc* dc)
{
	struct rtgui_dc_buffer* dc_buffer;

	dc_buffer = (struct rtgui_dc_buffer*)dc;

	return dc_buffer->pixel;
}

static rt_bool_t rtgui_dc_buffer_fini(struct rtgui_dc* dc)
{
	struct rtgui_dc_buffer* buffer = (struct rtgui_dc_buffer*)dc;

	if (dc->type != RTGUI_DC_BUFFER) return RT_FALSE;

	rtgui_free(buffer->pixel);
	buffer->pixel = RT_NULL;

	return RT_TRUE;
}

static void rtgui_dc_buffer_draw_point(struct rtgui_dc* self, int x, int y)
{
	rtgui_color_t* ptr;
	struct rtgui_dc_buffer* dc;

	dc = (struct rtgui_dc_buffer*)self;

	/* note: there is no parameter check in this function */
	ptr = (rtgui_color_t*)(dc->pixel + y * dc->pitch + x * sizeof(rtgui_color_t));

	*ptr = dc->color;
}

static void rtgui_dc_buffer_draw_vline(struct rtgui_dc* self, int x, int y1, int y2)
{
	rtgui_color_t* ptr;
	register rt_base_t index;
	struct rtgui_dc_buffer* dc;

	dc = (struct rtgui_dc_buffer*)self;

	if (x  >= dc->width) return;
	if (y1 > dc->height) y1 = dc->height;
	if (y2 > dc->height) y2 = dc->height;

	ptr = (rtgui_color_t*)(dc->pixel + y1 * dc->pitch + x * sizeof(rtgui_color_t));
	for (index = y1; index < y2; index ++)
	{
		/* draw this point */
		*ptr = dc->color;
		ptr += dc->width;
	}
}

static void rtgui_dc_buffer_draw_hline(struct rtgui_dc* self, int x1, int x2, int y)
{
	rtgui_color_t* ptr;
	register rt_base_t index;
	struct rtgui_dc_buffer* dc;

	dc = (struct rtgui_dc_buffer*)self;
	if (y >= dc->height) return;
	if (x1 > dc->width) x1 = dc->width;
	if (x2 > dc->width) x2 = dc->width;

	ptr = (rtgui_color_t*)(dc->pixel + y * dc->pitch + x1 * sizeof(rtgui_color_t));
	for (index = x1; index < x2; index ++)
	{
		/* draw this point */
		*ptr++ = dc->color;
	}
}

static void rtgui_dc_buffer_fill_rect (struct rtgui_dc* self, struct rtgui_rect* rect)
{
	rtgui_rect_t r;
	struct rtgui_dc_buffer* dc;

	r = *rect;
	dc = (struct rtgui_dc_buffer*)self;
	if (r.x1 > dc->width) r.x1 = dc->width;
	if (r.x2 > dc->width) r.x2 = dc->width;
	if (r.y1 > dc->height) r.y1 = dc->height;
	if (r.y2 > dc->height) r.y2 = dc->height;

	/* fill first line */
	rtgui_dc_buffer_draw_hline(&(dc->parent), r.x1, r.x2, r.y1);

	/* memory copy other lines */
	if (r.y2 > r.y1)
	{
		register rt_base_t index;
		for (index = r.y1 + 1; index < r.y2; index ++)
		{
			rt_memcpy(dc->pixel + index * dc->pitch,
				dc->pixel + r.y1 * dc->pitch,
				(r.x2 - r.x1) * sizeof(rtgui_color_t));
		}
	}
}

/* rtgui_color to RGB323 */
rt_inline void rtgui_blit_line_1(rtgui_color_t* color, rt_uint8_t* dest, int line)
{
	struct _color {rt_uint8_t r, g, b, a;} *c;

	c = (struct _color*)color;
	while (line-- > 0)
	{
		*dest = (c->r & 0xe0) | (c->g & 0xc0) >> 3 | (c->b & 0xe0) >> 5 ;

		c ++;
		dest ++;
	}
}

/* rtgui_color to RGB565 */
rt_inline void rtgui_blit_line_2(rtgui_color_t* color, rt_uint8_t* dest, int line)
{
	struct _color {rt_uint8_t r, g, b, a;} *c;
	rt_uint16_t* ptr;

	c = (struct _color*)color;
	ptr = (rt_uint16_t*)dest;

	while (line-- > 0)
	{
		*ptr = ((c->r & 0xf8) << 8) | ((c->g & 0xfc) << 3) | (c->b >> 3);

		c ++;
		ptr ++;
	}
}

/* rtgui_color to RGB888 */
rt_inline void rtgui_blit_line_4(rtgui_color_t* color, rt_uint8_t* dest, int line)
{
	rt_memcpy(dest, color, line * 4);
}

static void rtgui_dc_buffer_blit(struct rtgui_dc* self, struct rtgui_point* dc_point, struct rtgui_dc* dest, rtgui_rect_t* rect)
{
	struct rtgui_dc_buffer* dc = (struct rtgui_dc_buffer*)self;
	struct rtgui_dc_hw* hw = (struct rtgui_dc_hw*)dest;

	if (dest->type == RTGUI_DC_HW)
	{
		register int index;
		int fb_pitch;
		rtgui_rect_t abs_rect;
		void (*blit_line)(rtgui_color_t* color, rt_uint8_t* dest, int line);

		abs_rect.x1 = hw->owner->extent.x1 + rect->x1;
		abs_rect.y1 = hw->owner->extent.y1 + rect->y1;
		abs_rect.x2 = abs_rect.x1 + rtgui_rect_width(*rect);
		abs_rect.y2 = abs_rect.y1 + rtgui_rect_height(*rect);

		/* hw fb pitch */
		fb_pitch = hw->device->byte_per_pixel * hw->device->width;

		/* hardware dc blit */
		if (!rtgui_region_not_empty(&dc->clip) ||
			dc->clip_sync != hw->owner->clip_sync)
		{
			/* should re-calculate clip */
			rtgui_region_intersect_rect(&(dc->clip),
				&(hw->owner->clip), &abs_rect);
		}

		switch (hw->device->byte_per_pixel)
		{
		case 1:
			blit_line = rtgui_blit_line_1;
			break;
		case 2:
			blit_line = rtgui_blit_line_2;
			break;
		case 3:
			blit_line = rtgui_blit_line_4;
			break;

		default:
			/* can not blit */
			return;
		}

		/* blit each clip rect */
		if (dc->clip.data == RT_NULL)
		{
			int y;
			rtgui_color_t* pixel;
			rt_uint8_t* fb;

			pixel = (rtgui_color_t*)(dc->pixel + (dc_point->y + dc->clip.extents.y1 - abs_rect.y1) * dc->pitch +
				(dc_point->x + dc->clip.extents.x1 - abs_rect.x1) * sizeof(rtgui_color_t));
			fb = hw->device->get_framebuffer() + dc->clip.extents.y1 * fb_pitch +
				dc->clip.extents.x1 * hw->device->byte_per_pixel;

			for (y = dc->clip.extents.y1; y < dc->clip.extents.y2; y ++)
			{
				blit_line(pixel, fb, dc->clip.extents.x2 - dc->clip.extents.x1);

				fb += fb_pitch;
				pixel += dc->width;
			}
		}
		else for (index = 0; index < rtgui_region_num_rects(&(dc->clip)); index ++)
		{
			int y;
			rtgui_rect_t* prect;
			rtgui_color_t* pixel;
			rt_uint8_t* fb;

			prect = ((rtgui_rect_t *)(dc->clip.data + index + 1));

			pixel = (rtgui_color_t*)(dc->pixel + (dc_point->y + prect->y1 - abs_rect.y1) * dc->pitch +
				(dc_point->x + prect->x1 - abs_rect.x1) * sizeof(rtgui_color_t));
			fb = hw->device->get_framebuffer() + prect->y1 * fb_pitch +
				prect->x1 * hw->device->byte_per_pixel;

			for (y = prect->y1; y < prect->y2; y ++)
			{
				blit_line(pixel, fb, prect->x2 - prect->x1);

				fb += fb_pitch;
				pixel += dc->width;
			}
		}
	}
}

static void rtgui_dc_buffer_set_color (struct rtgui_dc* self, rtgui_color_t color)
{
	struct rtgui_dc_buffer* dc = (struct rtgui_dc_buffer*)self;

	dc->color = color;
}

static rtgui_color_t rtgui_dc_buffer_get_color(struct rtgui_dc* self)
{
	struct rtgui_dc_buffer* dc = (struct rtgui_dc_buffer*)self;

	return dc->color;
}

static void rtgui_dc_buffer_set_font(struct rtgui_dc* self, rtgui_font_t* font)
{
	struct rtgui_dc_buffer* dc = (struct rtgui_dc_buffer*)self;

	dc->font = font;
}

static rtgui_font_t* rtgui_dc_buffer_get_font(struct rtgui_dc* self)
{
	struct rtgui_dc_buffer* dc = (struct rtgui_dc_buffer*)self;

	return dc->font;
}

static void rtgui_dc_buffer_set_textalign(struct rtgui_dc* self, rt_int32_t textalign)
{
	struct rtgui_dc_buffer* dc = (struct rtgui_dc_buffer*)self;

	dc->align = textalign;
}

static rt_int32_t rtgui_dc_buffer_get_textalign(struct rtgui_dc* self)
{
	struct rtgui_dc_buffer* dc = (struct rtgui_dc_buffer*)self;

	return dc->align;
}

static rt_bool_t rtgui_dc_buffer_get_visible(struct rtgui_dc* dc)
{
	return RT_TRUE;
}

static void rtgui_dc_buffer_get_rect(struct rtgui_dc* self, rtgui_rect_t* rect)
{
	struct rtgui_dc_buffer* dc = (struct rtgui_dc_buffer*)self;

	rect->x1 = rect->y1 = 0;

	rect->x2 = dc->width;
	rect->y2 = dc->height;
}
#endif

