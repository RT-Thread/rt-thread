
#include <rtgui/dc.h>
#include <rtgui/font.h>

#ifdef RTGUI_USING_HZ_BMP

static void rtgui_hz_bitmap_font_draw_text(struct rtgui_font* font, struct rtgui_dc* dc, const char* text, rt_ubase_t len, struct rtgui_rect* rect);
static void rtgui_hz_bitmap_font_get_metrics(struct rtgui_font* font, const char* text, rtgui_rect_t* rect);
const struct rtgui_font_engine hz_bmp_font_engine =
{
	RT_NULL,
	RT_NULL,
	rtgui_hz_bitmap_font_draw_text,
	rtgui_hz_bitmap_font_get_metrics
};

static void _rtgui_hz_bitmap_font_draw_text(struct rtgui_font_bitmap* bmp_font, struct rtgui_dc* dc, const char* text, rt_ubase_t len, struct rtgui_rect* rect)
{
	rt_uint8_t* str;
	rtgui_color_t bc;
	rt_uint16_t style;
	register rt_base_t h, word_bytes, font_bytes;

	RT_ASSERT(bmp_font != RT_NULL);

	/* get text style */
	style = rtgui_dc_get_gc(dc)->textstyle;
	bc = rtgui_dc_get_gc(dc)->background;

	/* drawing height */
	h = (bmp_font->height + rect->y1 > rect->y2)? rect->y2 - rect->y1 : bmp_font->height;
	word_bytes = (bmp_font->width + 7)/8;
	font_bytes = word_bytes * bmp_font->height;

	str = (rt_uint8_t*)text;

	while (len > 0 && rect->x1 < rect->x2)
	{
		const rt_uint8_t* font_ptr;
		rt_ubase_t sect, index;
		register rt_base_t i, j, k;

		/* calculate section and index */
		sect  = *str - 0xA0;
		index = *(str+1) - 0xA0;

		/* get font pixel data */
		font_ptr = bmp_font->bmp + (94 * (sect - 1) + (index - 1)) * font_bytes;
		/* draw word */
		for (i=0; i < h; i ++)
		{
			for (j=0; j < word_bytes; j++)
				for (k=0; k < 8; k++)
				{
					if ( ((font_ptr[i*word_bytes + j] >> (7-k)) & 0x01) != 0 &&
						(rect->x1 + 8 * j + k < rect->x2))
					{
						rtgui_dc_draw_point(dc, rect->x1 + 8*j + k, rect->y1 + i);
					}
					else if (style & RTGUI_TEXTSTYLE_DRAW_BACKGROUND)
					{
						rtgui_dc_draw_color_point(dc, rect->x1 + 8*j + k, rect->y1 + i, bc);
					}
				}
		}

		/* move x to next character */
		rect->x1 += bmp_font->width;
		str += 2;
		len -= 2;
	}
}

static void rtgui_hz_bitmap_font_draw_text (struct rtgui_font* font, struct rtgui_dc* dc, const char* text, rt_ubase_t length, struct rtgui_rect* rect)
{
	rt_uint32_t len;
	struct rtgui_font *efont;
	struct rtgui_font_bitmap* bmp_font = (struct rtgui_font_bitmap*)(font->data);

	RT_ASSERT(dc != RT_NULL);

	/* get English font */
	efont = rtgui_font_refer("asc", bmp_font->height);
	if (efont == RT_NULL) efont = rtgui_font_default(); /* use system default font */

	while (length > 0)
	{
		len = 0;
		while (((rt_uint8_t)*(text + len)) < 0x80 && *(text + len)) len ++;
		/* draw text with English font */
		if (len > 0)
		{
			rtgui_font_draw(efont, dc, text, len, rect);

			text += len;
			length -= len;
		}

		len = 0;
		while (((rt_uint8_t)*(text + len)) >= 0x80) len ++;
		if (len > 0)
		{
			_rtgui_hz_bitmap_font_draw_text(bmp_font, dc, text, len, rect);

			text += len;
			length -= len;
		}
	}

	rtgui_font_derefer(efont);
}

static void rtgui_hz_bitmap_font_get_metrics(struct rtgui_font* font, const char* text, rtgui_rect_t* rect)
{
	struct rtgui_font_bitmap* bmp_font = (struct rtgui_font_bitmap*)(font->data);

	RT_ASSERT(bmp_font != RT_NULL);

	/* set metrics rect */
	rect->x1 = rect->y1 = 0;
	/* Chinese font is always fixed font */
	rect->x2 = (rt_int16_t)(bmp_font->width * rt_strlen((const char*)text));
	rect->y2 = bmp_font->height;
}

#endif
