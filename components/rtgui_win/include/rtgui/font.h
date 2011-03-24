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

extern rtgui_font_t rtgui_font_asc12,rtgui_font_asc16,font_dotum;

struct rtgui_font_engine
{
	/* font engine function */
	void (*font_init)(rtgui_font_t* font);
	void (*font_load)(rtgui_font_t* font);

	void (*font_draw_text)(rtgui_font_t* font, rtgui_dc_t *dc, const char* text, rt_uint32_t len, rtgui_rect_t* rect);
	void (*font_get_metrics)(rtgui_font_t* font, const char* text, rtgui_rect_t* rect);
};

/*
 * bitmap font engine
 */
/* bitmap font private data */
struct rtgui_font_bitmap
{
	/* bitmap data */
	const rt_uint8_t* bmp;
	const rt_uint8_t*  char_width;	/* each character width, NULL for fixed font */
	const rt_uint32_t* offset;		/* offset for each character */

	rt_uint16_t width;
	rt_uint16_t height;

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
    const char* font_fn;
};
extern struct rtgui_font_engine rtgui_hz_file_font_engine;

struct rtgui_font
{
	/* font name */
	char* family;

	/* font height */
	rt_uint16_t height;

	/* refer count */
	rt_uint32_t refer_count;

	/* font engine */
	const struct rtgui_font_engine* engine;

	/* font private data */
	void* data;

	/* the font list */
	rtgui_list_t list;
};
typedef struct rtgui_font rtgui_font_t;

void rtgui_font_system_init(void);
void rtgui_font_system_add_font(rtgui_font_t* font);
void rtgui_font_system_remove_font(rtgui_font_t* font);
rtgui_font_t* rtgui_font_default(void);
void rtgui_font_set_defaut(rtgui_font_t* font);

rtgui_font_t* rtgui_font_refer(const rt_uint8_t* family, rt_uint16_t height);
void rtgui_font_derefer(rtgui_font_t* font);

/* draw a text */
void rtgui_font_draw(rtgui_font_t* font, rtgui_dc_t *dc, const char* text, rt_uint32_t len, rtgui_rect_t* rect);
int  rtgui_font_get_string_width(rtgui_font_t* font, const char* text);//取得字符串的宽度
int rtgui_font_get_font_width(rtgui_font_t* font); //取得字体的宽度
int rtgui_font_get_font_height(rtgui_font_t* font);//取得字体的高度
void rtgui_font_get_string_rect(rtgui_font_t* font, const char* text, rtgui_rect_t* rect);//取得字符串的矩形区域
void rtgui_font_get_metrics(struct rtgui_font* font, const char* text, rtgui_rect_t* rect);

#endif
