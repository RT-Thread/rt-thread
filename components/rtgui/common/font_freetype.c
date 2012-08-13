#include <rtgui/font_freetype.h>

#ifdef RTGUI_USING_TTF
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>

static void rtgui_freetype_font_draw_text(struct rtgui_font* font, struct rtgui_dc* dc, const char* text, rt_ubase_t len, struct rtgui_rect* rect);
static void rtgui_freetype_font_get_metrics(struct rtgui_font* font, const char* text, rtgui_rect_t* rect);

struct rtgui_font_engine freetype_font_engine =
{
	RT_NULL,
	RT_NULL,
	rtgui_freetype_font_draw_text,
	rtgui_freetype_font_get_metrics
};

struct rtgui_freetype_font
{
	int bold;
	int italic;

	FT_Face     face;
	FT_Library  library;
};

static void gbk_to_unicode(rt_uint16_t *unicode, const unsigned char *text, int len)
{
	int i;
	unsigned short wch;
	extern unsigned short ff_convert(unsigned short wch, int direction);

	for (i = 0; i < len; )
	{
		if (*text < 0x80)
		{
			wch = *text;
			*unicode = ff_convert(wch, 1);
			text ++;
			i ++;
		}
		else
		{
			wch = wch = *(text + 1) | (*text << 8);
			*unicode = ff_convert(wch, 1);
			text += 2;
			i += 2;
		}

		unicode ++;
	}

	*unicode = '\0';
}

static void rtgui_freetype_font_draw_text(struct rtgui_font* font, struct rtgui_dc* dc, const char* text, rt_ubase_t len, struct rtgui_rect* rect)
{
	int index = 0;
	FT_Error err = 0;
	rt_uint16_t *text_short, *text_ptr;
	struct rtgui_freetype_font* freetype;

	RT_ASSERT(font != RT_NULL);
	freetype = (struct rtgui_freetype_font*) font->data;
	RT_ASSERT(freetype != RT_NULL);

	/* allocate unicode buffer */
	text_short = (rt_uint16_t*)rtgui_malloc((len + 1)* 2);
	if (text_short == RT_NULL) return ; /* out of memory */

	/* convert gbk to unicode */
	gbk_to_unicode(text_short, text, len);
	text_ptr = text_short;

	while (*text_ptr)
	{
		index = FT_Get_Char_Index(freetype->face, *text_ptr);
		err = FT_Load_Glyph(freetype->face, index, FT_LOAD_DEFAULT|FT_LOAD_RENDER);
		if (err == 0)
		{
			int rows, x;
			rt_uint8_t* ptr;

			/* render font */
			ptr = (rt_uint8_t*)freetype->face->glyph->bitmap.buffer;
			
			for (rows = 0; rows < freetype->face->glyph->bitmap.rows; rows ++)
				for (x = 0; x < freetype->face->glyph->bitmap.width; x++)
				{
					if (*ptr > 0)
						rtgui_dc_draw_color_point(dc, rect->x1 + x, rect->y1 + rows, RTGUI_RGB(0xff - *ptr, 0xff - *ptr, 0xff - *ptr));
					ptr ++;
				}
		}

		text_ptr ++;
		rect->x1 += freetype->face->glyph->bitmap.width;
	}

	/* release unicode buffer */
	rtgui_free(text_short);
}

static void rtgui_freetype_font_get_metrics(struct rtgui_font* font, const char* text, rtgui_rect_t* rect)
{
	int index = 0, len;
	FT_Error err = 0;
	rt_uint16_t w = 0, h = 0;
	rt_uint16_t *text_short, *text_ptr;
	struct rtgui_freetype_font* freetype;
	
	RT_ASSERT(font != RT_NULL);
	RT_ASSERT(rect != RT_NULL);
	freetype = (struct rtgui_freetype_font*) font->data;
	RT_ASSERT(freetype != RT_NULL);

	len = strlen(text);
	memset(rect, 0, sizeof(struct rtgui_rect));

	/* allocate unicode buffer */
	text_short = (rt_uint16_t*)rtgui_malloc((len + 1)* 2);
	if (text_short == RT_NULL) return ; /* out of memory */

	/* convert gbk to unicode */
	gbk_to_unicode(text_short, text, len);
	text_ptr = text_short;

	while (*text_ptr)
	{
		index = FT_Get_Char_Index(freetype->face, *text_ptr);
		err = FT_Load_Glyph(freetype->face, index, FT_LOAD_DEFAULT);

		if (err == 0)
		{
			w += freetype->face->glyph->bitmap.width;
			if (freetype->face->glyph->bitmap.rows > h)
			{
				h = freetype->face->glyph->bitmap.rows;
			}
		}

		text_ptr ++;
	}

	rect->x1 = 0; rect->y1 = 0;
	rect->x2 = w; rect->y2 = h;

	/* release unicode buffer */
	rtgui_free(text_short);
}

rtgui_font_t* rtgui_freetype_font_create(const char* filename, int bold, int italic, rt_size_t size)
{
	FT_Error err = 0;
	struct rtgui_font* font;

	font = (struct rtgui_font*) rtgui_malloc (sizeof(struct rtgui_font));
	if (font != RT_NULL)
	{
		struct rtgui_freetype_font* freetype;

		freetype = (struct rtgui_freetype_font*) rtgui_malloc (sizeof(struct rtgui_freetype_font));
		if (freetype == RT_NULL)
		{
			rtgui_free(font);
			font = RT_NULL;
		}
		else
		{
			err = FT_Init_FreeType(&freetype->library);
			if((err = FT_New_Face(freetype->library, filename, 0, &freetype->face)))
			{
				FT_Done_FreeType(freetype->library);

				rtgui_free(font);
				font = RT_NULL;
			}
			else
			{
				err = FT_Select_Charmap(freetype->face, ft_encoding_unicode);
				if(err)
				{
					err = FT_Select_Charmap(freetype->face, ft_encoding_latin_1 );
				}

				err = FT_Set_Pixel_Sizes(freetype->face, 0, size);
				if (err != 0)
				{
					rtgui_free(font);
					font = RT_NULL;

					FT_Done_FreeType(freetype->library);
					rtgui_free(freetype);

					return RT_NULL;
				}

				freetype->bold = bold;
				freetype->italic = italic;

				rt_kprintf("fonfile:%s\n", filename);
				rt_kprintf("font family_name:%s\n", freetype->face->family_name);
				rt_kprintf("font style_name:%s\n", freetype->face->style_name);

				/* set user data */
				font->data = freetype;
				font->family = rt_strdup(freetype->face->family_name);
				font->height = (rt_uint16_t)size;
				font->refer_count = 0;
				font->engine = &freetype_font_engine;

				/* add to system */
				rtgui_font_system_add_font(font);
			}
		}
	}

	return font;
}

void rtgui_freetype_font_destroy(rtgui_font_t* font)
{
	struct rtgui_freetype_font* freetype;
	
	RT_ASSERT(font != RT_NULL);
	freetype = (struct rtgui_freetype_font*) font->data;
	RT_ASSERT(freetype != RT_NULL);

	rtgui_font_system_remove_font(font);

	FT_Done_Face    (freetype->face);
	FT_Done_FreeType(freetype->library);
	rtgui_free(freetype);
	rtgui_free(font);
}
#endif
