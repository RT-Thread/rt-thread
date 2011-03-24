/*
 * File      : font.c
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
#include <rtgui/font.h>
#include <rtgui/dc.h>

static rtgui_list_t _rtgui_font_list;
static rtgui_font_t* rtgui_default_font;

extern rtgui_font_t rtgui_font_asc12;
extern rtgui_font_t rtgui_font_asc16;
/* extern rtgui_font_t rtgui_font_arial16; */
/* extern rtgui_font_t rtgui_font_arial12; */
#ifdef RTGUI_USING_FONTHZ
extern rtgui_font_t rtgui_font_hz16;
extern rtgui_font_t rtgui_font_hz12;
#endif

void rtgui_font_system_init()
{
	rtgui_list_init(&(_rtgui_font_list));

	/* set default font to RT_NULL */
	rtgui_default_font = RT_NULL;

#ifdef RTGUI_USING_FONT16
	rtgui_font_system_add_font(&rtgui_font_asc16);
#ifdef RTGUI_USING_FONTHZ
	rtgui_font_system_add_font(&rtgui_font_hz16);
#endif
#endif

#ifdef RTGUI_USING_FONT12
	rtgui_font_system_add_font(&rtgui_font_asc12);
#ifdef RTGUI_USING_FONTHZ
	rtgui_font_system_add_font(&rtgui_font_hz12);
#endif
#endif
	
#ifdef RTGUI_USING_FONT12
	if (rtgui_default_font == RT_NULL)
		rtgui_font_set_defaut(&rtgui_font_asc12);
#endif
#ifdef RTGUI_USING_FONT16
	if (rtgui_default_font == RT_NULL)
		rtgui_font_set_defaut(&rtgui_font_asc16);
#endif

}

void rtgui_font_system_add_font(rtgui_font_t* font)
{
	rtgui_list_init(&(font->list));
	rtgui_list_append(&_rtgui_font_list, &(font->list));

	/* init font */
	if(font->engine->font_init != RT_NULL)
		font->engine->font_init(font);

	/* first refer, load it */
	if(font->engine->font_load != RT_NULL)
		font->engine->font_load(font);
}

void rtgui_font_system_remove_font(rtgui_font_t* font)
{
	rtgui_list_remove(&_rtgui_font_list, &(font->list));
}

rtgui_font_t* rtgui_font_default(void)
{
	return rtgui_default_font;
}

void rtgui_font_set_defaut(rtgui_font_t* font)
{
	rtgui_default_font = font;
}

rtgui_font_t* rtgui_font_refer(const rt_uint8_t* family, rt_uint16_t height)
{
	/* search font */
	rtgui_list_t* node;
	rtgui_font_t* font;

	rtgui_list_foreach(node, &_rtgui_font_list)
	{
		font = rtgui_list_entry(node, rtgui_font_t, list);
		if((rt_strncmp((const char*)font->family, (const char*)family, RTGUI_NAME_MAX) == 0) &&
			font->height == height)
		{
			font->refer_count ++;
			return font;
		}
	}

	return RT_NULL;
}

void rtgui_font_derefer(rtgui_font_t* font)
{
	RT_ASSERT(font != RT_NULL);

	font->refer_count --;

	/* no refer, remove font */
	if(font->refer_count == 0)
	{
		rtgui_font_system_remove_font(font);
	}
}

/* draw a text */
void rtgui_font_draw(rtgui_font_t* font, rtgui_dc_t *dc, const char* text, rt_uint32_t len, rtgui_rect_t* rect)
{
	RT_ASSERT(font != RT_NULL);

	if(font->engine != RT_NULL && font->engine->font_draw_text != RT_NULL)
	{
		font->engine->font_draw_text(font, dc, text, len, rect);
	}
}

int rtgui_font_get_string_width(rtgui_font_t *font, const char* text)
{
	rtgui_rect_t rect;

	/* get metrics */
	rtgui_font_get_string_rect(font, text, &rect);

	return rect.x2 - rect.x1;
}

int rtgui_font_get_font_width(rtgui_font_t* font)
{
	rtgui_rect_t rect;
	char *text = "H";
	/* get metrics */
	rtgui_font_get_string_rect(font, text, &rect);

	return rect.x2 - rect.x1;
}

int rtgui_font_get_font_height(rtgui_font_t* font)
{
	rtgui_rect_t rect;
	char *text = "H";
	/* get metrics */
	rtgui_font_get_string_rect(font, text, &rect);

	return rect.y2 - rect.y1;
}

void rtgui_font_get_string_rect(rtgui_font_t* font, const char* text, rtgui_rect_t* rect)
{
	RT_ASSERT(font != RT_NULL);

	if(font->engine != RT_NULL && font->engine->font_get_metrics != RT_NULL)
	{
		font->engine->font_get_metrics(font, text, rect);
	}
	else
	{
		/* no font engine found, set rect to zero */
		rt_memset(rect, 0, sizeof(rtgui_rect_t));
	}
}

void rtgui_font_get_metrics(struct rtgui_font* font, const char* text, rtgui_rect_t* rect)
{
	RT_ASSERT(font != RT_NULL);

	if (font->engine != RT_NULL &&
		font->engine->font_get_metrics != RT_NULL)
	{
		font->engine->font_get_metrics(font, text, rect);
	}
	else
	{
		/* no font engine found, set rect to zero */
		rt_memset(rect, 0, sizeof(rtgui_rect_t));
	}
}

static void rtgui_bitmap_font_draw_text(rtgui_font_t* font, rtgui_dc_t *dc, const char* text, rt_uint32_t len, rtgui_rect_t* rect);
static void rtgui_bitmap_font_get_metrics(rtgui_font_t* font, const char* text, rtgui_rect_t* rect);
const struct rtgui_font_engine bmp_font_engine =
{
	RT_NULL,
	RT_NULL,
	rtgui_bitmap_font_draw_text,
	rtgui_bitmap_font_get_metrics
};

void rtgui_bitmap_font_draw_char(struct rtgui_font_bitmap* font, rtgui_dc_t *dc, const char ch, rtgui_rect_t* rect)
{
	const rt_uint8_t* font_ptr;
	rt_uint16_t x, y, h;
	register rt_int32_t i, j, k, word_bytes;

	/* check first and last char */
	if(ch < font->first_char || ch > font->last_char) return;

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

	for(i = 0; i < h; i++)
	{
		for(j = 0; j < word_bytes; j++)
		{
			for(k = 0; k < 8; k++)
			{
				
				if(((font_ptr[i * word_bytes + j] >> (7 - k)) & 0x01) != 0)
				{
					/* draw a pixel */
					rtgui_dc_draw_point(dc,k + 8 * j + x, i + y);
				}
			}
		}
	}
}

static void rtgui_bitmap_font_draw_text(rtgui_font_t* font, rtgui_dc_t *dc, const char* text, rt_uint32_t len, rtgui_rect_t* rect)
{
	rt_uint32_t length;
	struct rtgui_font_bitmap* bmp_font = (struct rtgui_font_bitmap*)(font->data);
#ifdef RTGUI_USING_FONTHZ
	struct rtgui_font* hz_font;

	RT_ASSERT(bmp_font != RT_NULL);

	hz_font = rtgui_font_refer("hz", font->height);
	while ((rect->x1 < rect->x2) && len)
	{
		length = 0;
		while ((rt_uint8_t)*(text + length) >= 0x80) length ++; /* it's not a ascii character */
		if (length > 0)
		{
			if (hz_font != RT_NULL)
				rtgui_font_draw(hz_font, dc, text, length, rect);
			text += length;
			len -= length;
		}

		length = 0;
		while (((rt_uint8_t)*(text + length) < 0x80) && *(text + length)) length ++;
		if (length > 0)
		{
			len -= length;
			while (length-- && rect->x1 < rect->x2)
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
	}

	rtgui_font_derefer(hz_font);
#else
	while ((rect->x1 < rect->x2) && len)
	{
		while (((rt_uint8_t)*(text + length) < 0x80) && *(text + length)) length ++;
		if (length > 0)
		{
			len -= length;
			while (length-- && rect->x1 < rect->x2)
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
	}
#endif
}

static void rtgui_bitmap_font_get_metrics(rtgui_font_t* font, const char* text, rtgui_rect_t* rect)
{
	rt_uint32_t length;
	struct rtgui_font_bitmap* bmp_font = (struct rtgui_font_bitmap*)(font->data);

	RT_ASSERT(bmp_font != RT_NULL);

		/* set init metrics rect */
	rect->x1 = rect->y1 = 0;rect->x2 = 0;
	rect->y2 = bmp_font->height;

	while (*text)
	{
		length = 0;
		while (*(text + length) >= 0x80) length ++; /* it's not a ascii character */
		rect->x2 += (font->height/2) * length;
		text += length;

		length = 0;
		while ((*(text + length) < 0x80) && *(text + length)) length ++;
		if (bmp_font->char_width != RT_NULL)
		{
			/* get width for each character */
			while (*text && (*text < 0x80))
			{
				rect->x2 += bmp_font->char_width[*text - bmp_font->first_char];
				text ++;
			}
		}
		else
		{
			/* set metrics rect */
			rect->x2 += bmp_font->width * length;
			text += length;
		}
	}
}


