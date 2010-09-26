/*
 * File      : font.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-09-15     Bernard      first version
 */
#include <rtgui/font.h>
#include <rtgui/dc.h>

/* bitmap font private data */

static void rtgui_bitmap_font_draw_text(struct rtgui_font* font, struct rtgui_dc* dc, const char* text, rt_ubase_t len, struct rtgui_rect* rect);
static void rtgui_bitmap_font_get_metrics(struct rtgui_font* font, const char* text, rtgui_rect_t* rect);
const struct rtgui_font_engine bmp_font_engine =
{
	RT_NULL,
	RT_NULL,
	rtgui_bitmap_font_draw_text,
	rtgui_bitmap_font_get_metrics
};

void rtgui_bitmap_font_draw_char(struct rtgui_font_bitmap* font, struct rtgui_dc* dc, const char ch,
	rtgui_rect_t* rect)
{
	const rt_uint8_t* font_ptr;
	rt_uint16_t x, y, h;
	register rt_base_t i, j, k, word_bytes;

	/* check first and last char */
	if (ch < font->first_char || ch > font->last_char) return;

	x = rect->x1;
	y = rect->y1;
	/* get width */
	if (font->char_width == RT_NULL)
	{
		word_bytes = (((font->width - 1) / 8) + 1);
		font_ptr = font->bmp + (ch - font->first_char) * word_bytes * font->height;
	}
	else
	{
		word_bytes = ((font->char_width[ch - font->first_char] - 1)/8) + 1;
		font_ptr = font->bmp + font->offset[ch - font->first_char];
	}

	h = (font->height + y > rect->y2) ? rect->y2 - rect->y1 : font->height;

	for (i = 0; i < h; i++)
	{
		for (j = 0; j < word_bytes; j++)
		{
			for (k = 0; k < 8; k++)
			{
				if (((font_ptr[i * word_bytes + j] >> (7 - k)) & 0x01) != 0)
				{
					/* draw a pixel */
					rtgui_dc_draw_point(dc, k + 8 * j + x, i + y);
				}
			}
		}
	}
}

static void rtgui_bitmap_font_draw_text(struct rtgui_font* font, struct rtgui_dc* dc, const char* text, rt_ubase_t len, struct rtgui_rect* rect)
{
	struct rtgui_font_bitmap* bmp_font = (struct rtgui_font_bitmap*)(font->data);

	RT_ASSERT(bmp_font != RT_NULL);

	while (len-- && rect->x1 < rect->x2)
	{
		rtgui_bitmap_font_draw_char(bmp_font, dc, *text, rect);

		/* move x to next character */
		if (bmp_font->char_width == RT_NULL)
			rect->x1 += bmp_font->width;
		else
			rect->x1 += bmp_font->char_width[*text - bmp_font->first_char];
		text ++;
	}
}

static void rtgui_bitmap_font_get_metrics(struct rtgui_font* font, const char* text, rtgui_rect_t* rect)
{
	struct rtgui_font_bitmap* bmp_font = (struct rtgui_font_bitmap*)(font->data);

	RT_ASSERT(bmp_font != RT_NULL);

	if (bmp_font->char_width != NULL)
	{
		rt_uint32_t index;

		/* set metrics rect */
		rect->x1 = rect->y1 = 0;rect->x2 = 0;
		rect->y2 = bmp_font->height;

		/* get width for each character */
		while (*text)
		{
			rect->x2 += bmp_font->char_width[*text - bmp_font->first_char];
			text ++;
		}
	}
	else
	{
		/* set metrics rect */
		rect->x1 = rect->y1 = 0;
		rect->x2 = bmp_font->width * (rt_int16_t)rt_strlen((const char*)text);
		rect->y2 = bmp_font->height;
	}
}
