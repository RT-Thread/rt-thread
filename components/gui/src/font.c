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
 * 2013-08-31     Bernard      remove the default font setting.
 *                             (which set by theme)
 */
#include <rtgui/font.h>
#include <rtgui/dc.h>

static rtgui_list_t _rtgui_font_list;
static struct rtgui_font *rtgui_default_font;

extern struct rtgui_font rtgui_font_asc16;
extern struct rtgui_font rtgui_font_arial16;
extern struct rtgui_font rtgui_font_asc12;
extern struct rtgui_font rtgui_font_arial12;
#ifdef RTGUI_USING_FONTHZ
extern struct rtgui_font rtgui_font_hz16;
extern struct rtgui_font rtgui_font_hz12;
#endif

void rtgui_font_system_init()
{
    rtgui_list_init(&(_rtgui_font_list));

    /* set default font to NULL */
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
}

void rtgui_font_system_add_font(struct rtgui_font *font)
{
    rtgui_list_init(&(font->list));
    rtgui_list_append(&_rtgui_font_list, &(font->list));

    /* init font */
    if (font->engine->font_init != RT_NULL)
        font->engine->font_init(font);

    /* first refer, load it */
    if (font->engine->font_load != RT_NULL)
        font->engine->font_load(font);
}
RTM_EXPORT(rtgui_font_system_add_font);

void rtgui_font_system_remove_font(struct rtgui_font *font)
{
    rtgui_list_remove(&_rtgui_font_list, &(font->list));
}
RTM_EXPORT(rtgui_font_system_remove_font);

struct rtgui_font *rtgui_font_default()
{
    return rtgui_default_font;
}

void rtgui_font_set_defaut(struct rtgui_font *font)
{
    // rt_kprintf("set font size to %d\n", font->height);
    rtgui_default_font = font;
}

struct rtgui_font *rtgui_font_refer(const char *family, rt_uint16_t height)
{
    /* search font */
    struct rtgui_list_node *node;
    struct rtgui_font *font;

    rtgui_list_foreach(node, &_rtgui_font_list)
    {
        font = rtgui_list_entry(node, struct rtgui_font, list);
        if ((rt_strncmp(font->family, family, RTGUI_NAME_MAX) == 0) &&
                font->height == height)
        {
            font->refer_count ++;
            return font;
        }
    }

    return RT_NULL;
}
RTM_EXPORT(rtgui_font_refer);

void rtgui_font_derefer(struct rtgui_font *font)
{
    RT_ASSERT(font != RT_NULL);

    font->refer_count --;

    /* no refer, remove font */
    if (font->refer_count == 0)
    {
        rtgui_font_system_remove_font(font);
    }
}
RTM_EXPORT(rtgui_font_derefer);

/* draw a text */
void rtgui_font_draw(struct rtgui_font *font, struct rtgui_dc *dc, const char *text, rt_ubase_t len, struct rtgui_rect *rect)
{
    RT_ASSERT(font != RT_NULL);

    if (font->engine != RT_NULL &&
            font->engine->font_draw_text != RT_NULL)
    {
        font->engine->font_draw_text(font, dc, text, len, rect);
    }
}

int rtgui_font_get_string_width(struct rtgui_font *font, const char *text)
{
    rtgui_rect_t rect;

    /* get metrics */
    rtgui_font_get_metrics(font, text, &rect);

    return rect.x2 - rect.x1;
}
RTM_EXPORT(rtgui_font_get_string_width);

void rtgui_font_get_metrics(struct rtgui_font *font, const char *text, rtgui_rect_t *rect)
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
RTM_EXPORT(rtgui_font_get_metrics);


/* GB18030 encoding:
 *          1st byte    2nd byte    3rd byte    4th byte
 *  1byte: 0x00~0x7F
 * 2bytes: 0x81~0xFE   0x40~0xFE
 * 4bytes: 0x81~0xFE   0x30~0x39   0x81~0xFE   0x30~0x39
 */
struct rtgui_char_position _string_char_width(char *str, rt_size_t len, rt_size_t offset)
{
    struct rtgui_char_position pos = {0, 0};
    unsigned char *pc;

    RT_ASSERT(offset < len);

    pc = (unsigned char*)str;

    while (pc <= (unsigned char*)str + offset)
    {
        if (pc[0] < 0x80)
        {
            pos.char_width = 1;
        }
        else if (0x81 <= pc[0] && pc[0] <= 0xFE)
        {
            if (0x40 <= pc[1] && pc[1] <= 0xFE)
            {
                /* GBK */
                pos.char_width = 2;
            }
            else if (0x30 <= pc[1] && pc[1] <= 0x39)
            {
                /* GB18030 */
                pos.char_width = 4;
            }
            else
            {
                /* FIXME: unknown encoding */
                RT_ASSERT(0);
                pos.char_width = 1;
            }
        }
        else
        {
            /* FIXME: unknown encoding */
            RT_ASSERT(0);
            pos.char_width = 1;
        }
        pc += pos.char_width;
    }
    pos.remain = pc - (unsigned char*)&str[offset];
    return pos;
}
