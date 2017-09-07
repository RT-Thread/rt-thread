/*
 * File      : font.h
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
#ifndef __RTGUI_FONT_H__
#define __RTGUI_FONT_H__

#include <rtgui/rtgui.h>
#include <rtgui/list.h>

#ifdef __cplusplus
extern "C" {
#endif

struct rtgui_font;
struct rtgui_dc;
struct rtgui_rect;

struct rtgui_font_engine
{
    /* font engine function */
    void (*font_init)(struct rtgui_font *font);
    void (*font_load)(struct rtgui_font *font);

    void (*font_draw_text)(struct rtgui_font *font, struct rtgui_dc *dc, const char *text,
                           rt_ubase_t len, struct rtgui_rect *rect);
    void (*font_get_metrics)(struct rtgui_font *font, const char *text, struct rtgui_rect *rect);
};

/*
 * bitmap font engine
 */
struct rtgui_font_bitmap
{
    const rt_uint8_t  *bmp;         /* bitmap font data */
    const rt_uint8_t  *char_width;  /* each character width, NULL for fixed font */
    const rt_uint32_t *offset;      /* offset for each character */

    rt_uint16_t width;              /* font width  */
    rt_uint16_t height;             /* font height */

    rt_uint8_t first_char;
    rt_uint8_t last_char;
};
extern const struct rtgui_font_engine bmp_font_engine;

#include <rtgui/tree.h>
SPLAY_HEAD(cache_tree, hz_cache);
struct hz_cache
{
    SPLAY_ENTRY(hz_cache) hz_node;

    rt_uint16_t hz_id;
};

struct rtgui_hz_file_font
{
    struct cache_tree cache_root;
    rt_uint16_t cache_size;

    /* font size */
    rt_uint16_t font_size;
    rt_uint16_t font_data_size;

    /* file descriptor */
    int fd;

    /* font file name */
    const char *font_fn;
};
extern const struct rtgui_font_engine rtgui_hz_file_font_engine;

struct rtgui_font
{
    /* font name */
    char *family;

    /* font height */
    rt_uint16_t height;

    /* refer count */
    rt_uint32_t refer_count;

    /* font engine */
    const struct rtgui_font_engine *engine;

    /* font private data */
    void *data;

    /* the font list */
    rtgui_list_t list;
};
typedef struct rtgui_font rtgui_font_t;

void rtgui_font_system_init(void);
void rtgui_font_system_add_font(struct rtgui_font *font);
void rtgui_font_system_remove_font(struct rtgui_font *font);
struct rtgui_font *rtgui_font_default(void);
void rtgui_font_set_defaut(struct rtgui_font *font);

struct rtgui_font *rtgui_font_refer(const char *family, rt_uint16_t height);
void rtgui_font_derefer(struct rtgui_font *font);

/* draw a text */
void rtgui_font_draw(struct rtgui_font *font, struct rtgui_dc *dc, const char *text, rt_ubase_t len, struct rtgui_rect *rect);
int  rtgui_font_get_string_width(struct rtgui_font *font, const char *text);
void rtgui_font_get_metrics(struct rtgui_font *font, const char *text, struct rtgui_rect *rect);

/* used by stract font */
#define FONT_BMP_DATA_BEGIN
#define FONT_BMP_DATA_END

struct rtgui_char_position
{
    /* Keep the size of this struct within 4 bytes so it can be passed by
     * value. */
    /* How long this char is. */
    rt_uint16_t char_width;
    /* How many bytes remaining from current pointer. At least, it will be 1. */
    rt_uint16_t remain;
};

/*
 * @len the length of @str.
 * @offset the char offset on the string to check with.
 */
struct rtgui_char_position _string_char_width(char *str, rt_size_t len, rt_size_t offset);

#ifdef __cplusplus
}
#endif

#endif

