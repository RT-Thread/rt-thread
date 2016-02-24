#include <rtthread.h>

#ifdef RTGUI_USING_TTF
#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/dc.h>
#include <rtgui/font.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#define LOG_ERROR

#ifdef LOG_ERROR
#define PERROR       rt_kprintf
#else
#define PERROR(...)
#endif

//#define LOG_INFO

#ifdef LOG_INFO
#define PINFO       rt_kprintf
#else
#define PINFO(...)
#endif

static void ftf_draw_text(struct rtgui_font *font,
                          struct rtgui_dc *dc,
                          const char *text,
                          rt_ubase_t len,
                          struct rtgui_rect *rect);
static void ftf_get_metrics_kern(struct rtgui_font *font,
                                  const char *text,
                                  rtgui_rect_t *rect);

static const struct rtgui_font_engine ftf_engine =
{
    RT_NULL,
    RT_NULL,
    ftf_draw_text,
    ftf_get_metrics_kern
};

struct rtgui_freetype2_font
{
    int bold;
    int italic;

    FT_Face     face;
    FT_Library  library;
};

#if !defined(RT_USING_DFS) || !defined(RT_USING_DFS_ELMFAT) || (RT_DFS_ELM_CODE_PAGE != 936)
extern rt_uint32_t gb2312tounicode(const rt_uint16_t key);
#else
extern unsigned short ff_convert(unsigned short wch, int direction);
#define gb2312tounicode(code) ff_convert(code, 1)
#endif

static void gbk_to_unicode(rt_uint16_t *unicode, const char *text, int len)
{
    int i;
    const unsigned char *tp = (const unsigned char *)text;
    unsigned short wch;

    for (i = 0; i < len;)
    {
        if (*tp < 0x80)
        {
            wch = *tp;
            *unicode = gb2312tounicode(wch);
            tp ++;
            i ++;
        }
        else
        {
            wch = *(tp + 1) | (*tp << 8);
            *unicode = gb2312tounicode(wch);
            tp += 2;
            i += 2;
        }

        unicode ++;
    }

    *unicode = '\0';
}

static void _draw_bitmap(struct rtgui_dc *dc,
                         FT_GlyphSlot slot,
                         rt_int16_t ox, rt_int16_t btm_y,
                         rt_uint8_t r, rt_uint8_t g, rt_uint8_t b)
{
    int rows;
    rt_uint8_t *ptr;
    FT_Bitmap *bitmap;
    rt_int16_t xstart;

    bitmap = &slot->bitmap;
    ptr = (rt_uint8_t *)bitmap->buffer;
    xstart = ox + slot->bitmap_left;

    for (rows = 0; rows < bitmap->rows; rows++)
    {
        int x;
        int y = btm_y + rows - slot->bitmap_top;

        for (x = 0; x < bitmap->width; x++)
        {
            /* Use 5bit alpha. */
            rt_uint8_t c = *ptr;
            if (c >= 0xF8)
            {
                rtgui_dc_draw_point(dc, xstart + x, y);
            }
            else if (c >> 3)
            {
                rtgui_dc_blend_point(dc, xstart + x, y,
                                     RTGUI_BLENDMODE_BLEND,
                                     r, g, b, c);
            }
            ptr++;
        }
    }
}

static void _draw_text_nkern(struct rtgui_dc *dc,
                             struct rtgui_freetype2_font *fft,
                             rt_uint16_t *text_short,
                             rt_int16_t begin_x, rt_int16_t btm_y,
                             rt_uint8_t r, rt_uint8_t g, rt_uint8_t b)
{
    rt_uint16_t *text_ptr;
    FT_GlyphSlot  slot;

    slot = fft->face->glyph;

    for (text_ptr = text_short; *text_ptr; text_ptr++)
    {
        FT_Error err = 0;

        err = FT_Load_Char(fft->face, *text_ptr, FT_LOAD_RENDER | FT_LOAD_NO_HINTING);
        if (err)
            continue;  /* ignore errors */

        /* render font */
        _draw_bitmap(dc, slot, begin_x, btm_y, r, g, b);

        begin_x += slot->advance.x >> 6;
    }
}

static void _draw_text_kern(struct rtgui_dc *dc,
                            struct rtgui_freetype2_font *fft,
                            rt_uint16_t *text_short,
                            rt_int16_t begin_x, rt_int16_t btm_y,
                            rt_uint8_t r, rt_uint8_t g, rt_uint8_t b)
{
    rt_uint16_t *tp;
    FT_GlyphSlot  slot;
    FT_Face  face;
    rt_uint32_t prev_gidx;

    face = fft->face;
    slot = face->glyph;

    prev_gidx = 0;
    for (tp = text_short; *tp; tp++)
    {
        FT_Error err;
        rt_uint32_t cur_gidx;

        cur_gidx = FT_Get_Char_Index(face, *tp);
        if (prev_gidx && cur_gidx)
        {
            FT_Vector delta;

            FT_Get_Kerning(face, prev_gidx, cur_gidx,
                            FT_KERNING_DEFAULT, &delta );

            begin_x += delta.x >> 6;
        }
        prev_gidx = cur_gidx;

        err = FT_Load_Glyph(face, cur_gidx, FT_LOAD_RENDER | FT_LOAD_NO_HINTING);
        if (err)
            continue;

        /* render font */
        _draw_bitmap(dc, slot, begin_x, btm_y, r, g, b);

        begin_x += slot->advance.x >> 6;
    }
}

static void ftf_draw_text(struct rtgui_font *font,
                          struct rtgui_dc *dc,
                          const char *text,
                          rt_ubase_t len,
                          struct rtgui_rect *rect)
{
    rt_uint16_t *text_short;
    struct rtgui_freetype2_font *fft;
    rt_int16_t begin_x, btm_y;
    rt_int16_t topy;
    rt_uint8_t r, g, b;
    rtgui_color_t fgc;

    RT_ASSERT(font != RT_NULL);
    fft = (struct rtgui_freetype2_font *) font->data;
    RT_ASSERT(fft != RT_NULL);

    /* allocate unicode buffer */
    text_short = (rt_uint16_t *)rtgui_malloc((len + 1) * 2);
    if (text_short == RT_NULL)
        return; /* out of memory */

    RT_ASSERT(rect);

    /* convert gbk to unicode */
    gbk_to_unicode(text_short, text, len);

    fgc = RTGUI_DC_FC(dc);
    r = RTGUI_RGB_R(fgc);
    g = RTGUI_RGB_G(fgc);
    b = RTGUI_RGB_B(fgc);

    /* FIXME: RTGUI has no concept of "base line" right now. FreeType
     * coordinate(0, 0) start from base line. So we have to adjust the rect to
     * fit the glyphs within the rect. */
    /* FIXME: face->size->metrics.descender is format specific actually. But it
     * just works on TrueType. Varify this if you want to use with other fonts. */
    topy = rect->y1 + (fft->face->size->metrics.descender >> 6);
    btm_y = topy + rtgui_rect_height(*rect);
    if (btm_y <= 0)
        return;
    begin_x = rect->x1;

    if (dc->type == RTGUI_DC_BUFFER)
    {
		struct rtgui_dc_buffer *bdc = (struct rtgui_dc_buffer *) dc;

        if (begin_x >= bdc->width || topy >= bdc->height)
        {
            goto _out;
        }
    }
	else if (dc->type == RTGUI_DC_HW)
	{
        int x, y;
		struct rtgui_dc_hw *hdc = (struct rtgui_dc_hw *) dc;

		x = begin_x + hdc->owner->extent.x1;
		y = topy + hdc->owner->extent.y1;
		if (x >= hdc->owner->extent.x2)
            goto _out;
		if (y >= hdc->owner->extent.y2)
            goto _out;
	}

    if (FT_HAS_KERNING(fft->face))
    {
        _draw_text_kern(dc, fft, text_short, begin_x, btm_y, r, g, b);
    }
    else
    {
        _draw_text_nkern(dc, fft, text_short, begin_x, btm_y, r, g, b);
    }

_out:
    /* release unicode buffer */
    rtgui_free(text_short);
}

static void _get_metrics_nkern(FT_Face face, const rt_uint16_t *text_short, struct rtgui_rect *rect)
{
    rt_int16_t w;

    w = 0;
    while (*text_short)
    {
        FT_Error err = 0;
        rt_uint16_t index;

        index = FT_Get_Char_Index(face, *text_short);
        err = FT_Load_Glyph(face, index,
                            FT_LOAD_DEFAULT |
                            FT_LOAD_NO_HINTING |
                            FT_LOAD_IGNORE_TRANSFORM |
                            FT_LOAD_NO_AUTOHINT);

        if (err == 0)
            w += face->glyph->advance.x >> 6;

        text_short ++;
    }

    rect->x1 = 0;
    rect->y1 = 0;
    rect->x2 = w;
    rect->y2 = FT_MulFix(face->bbox.yMax - face->bbox.yMin,
                         face->size->metrics.y_scale) >> 6;
}

static void _get_metrics_kern(FT_Face face, const rt_uint16_t *text_short, struct rtgui_rect *rect)
{
    rt_uint16_t prev_gidx;
    rt_int16_t w;

    prev_gidx = 0;
    w = 0;
    while (*text_short)
    {
        FT_Error err = 0;
        rt_uint16_t index;

        index = FT_Get_Char_Index(face, *text_short);
        if (prev_gidx && index)
        {
            FT_Vector delta;

            FT_Get_Kerning(face, prev_gidx, index,
                            FT_KERNING_DEFAULT, &delta);

            w += delta.x >> 6;
        }
        prev_gidx = index;
        err = FT_Load_Glyph(face, index,
                            FT_LOAD_DEFAULT |
                            FT_LOAD_NO_HINTING |
                            FT_LOAD_IGNORE_TRANSFORM |
                            FT_LOAD_NO_AUTOHINT);

        if (err == 0)
            w += face->glyph->advance.x >> 6;

        text_short ++;
    }

    rect->x1 = 0;
    rect->y1 = 0;
    rect->x2 = w;
    rect->y2 = FT_MulFix(face->bbox.yMax - face->bbox.yMin,
                         face->size->metrics.y_scale) >> 6;
}

static void ftf_get_metrics_kern(struct rtgui_font *font, const char *text, rtgui_rect_t *rect)
{
    int len;
    rt_uint16_t *text_short;
    struct rtgui_freetype2_font *fft;

    RT_ASSERT(font != RT_NULL);
    RT_ASSERT(rect != RT_NULL);
    fft = (struct rtgui_freetype2_font *) font->data;
    RT_ASSERT(fft != RT_NULL);

    len = strlen(text);
    memset(rect, 0, sizeof(struct rtgui_rect));

    /* allocate unicode buffer */
    text_short = (rt_uint16_t *)rtgui_malloc((len + 1) * 2);
    if (text_short == RT_NULL)
        return; /* out of memory */

    /* convert gbk to unicode */
    gbk_to_unicode(text_short, text, len);

    if (FT_HAS_KERNING(fft->face))
        _get_metrics_kern(fft->face, text_short, rect);
    else
        _get_metrics_nkern(fft->face, text_short, rect);

    /* release unicode buffer */
    rtgui_free(text_short);
}

rtgui_font_t *rtgui_freetype_font_create(const char *filename, int bold, int italic, rt_size_t size)
{
    FT_Error err = 0;
    struct rtgui_font *font;
    struct rtgui_freetype2_font *fft;

    font = (struct rtgui_font *)rtgui_malloc(sizeof(struct rtgui_font)
                                             + sizeof(struct rtgui_freetype2_font));
    rt_memset(font, 0, sizeof(struct rtgui_font) + sizeof(struct rtgui_freetype2_font));
    if (!font)
    {
        PERROR("failed to allocate structs\n");
        return RT_NULL;
    }

    fft = (struct rtgui_freetype2_font *)(font + 1);
    font->data = fft;

    err = FT_Init_FreeType(&fft->library);
    if (err)
    {
        PERROR("failed to Init FreeType: %d\n", err);
        goto _err_done_malloc;
    }

    err = FT_New_Face(fft->library, filename, 0, &fft->face);
    if (err)
    {
        PERROR("failed to New Face: %d\n", err);
        goto _err_done_init;
    }

    err = FT_Select_Charmap(fft->face, FT_ENCODING_UNICODE);
    if (err)
    {
        err = FT_Select_Charmap(fft->face, FT_ENCODING_ADOBE_LATIN_1);
    }

    err = FT_Set_Pixel_Sizes(fft->face, 0, size);
    if (err != 0)
    {
        PERROR("failed to set Pixel Size: %d\n", err);
        goto _err_done_face;
    }

    fft->bold = bold;
    fft->italic = italic;

    PINFO("fonfile:%s\n", filename);
    PINFO("font family_name:%s\n", fft->face->family_name);
    PINFO("font style_name:%s\n", fft->face->style_name);
    PINFO("%s kerneling\n", FT_HAS_KERNING(fft->face) ? "has" : "not has");

    /* set user data */
    font->family = rt_strdup(fft->face->family_name);
    font->height = (rt_uint16_t)size;
    font->refer_count = 1;
    font->engine = &ftf_engine;

    /* add to system */
    rtgui_font_system_add_font(font);

    return font;

_err_done_face:
    FT_Done_Face(fft->face);
_err_done_init:
    FT_Done_FreeType(fft->library);
_err_done_malloc:
    rtgui_free(font);

    return RT_NULL;
}
RTM_EXPORT(rtgui_freetype_font_create);

void rtgui_freetype_font_destroy(rtgui_font_t *font)
{
    struct rtgui_freetype2_font *fft;

    RT_ASSERT(font != RT_NULL);
    fft = (struct rtgui_freetype2_font *) font->data;
    RT_ASSERT(fft != RT_NULL);

    rtgui_font_system_remove_font(font);

    FT_Done_Face(fft->face);
    FT_Done_FreeType(fft->library);
    rt_free(font->family);
    rtgui_free(font);
}
RTM_EXPORT(rtgui_freetype_font_destroy);

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT_ALIAS(rtgui_freetype_font_create, ftc, "create freetype font: name, bold, italic, size")
FINSH_FUNCTION_EXPORT_ALIAS(rtgui_freetype_font_destroy, ftd, "destroy freetype font")
#endif

#endif
