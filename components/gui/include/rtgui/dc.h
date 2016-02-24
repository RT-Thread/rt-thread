/*
 * File      : dc.h
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
#ifndef __RTGUI_DC_H__
#define __RTGUI_DC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtgui/rtgui.h>
#include <rtgui/font.h>
#include <rtgui/driver.h>
#include <rtgui/widgets/widget.h>

#define RTGUI_DC(dc)		((struct rtgui_dc*)(dc))

#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif

enum rtgui_dc_type
{
    RTGUI_DC_HW,
    RTGUI_DC_CLIENT,
    RTGUI_DC_BUFFER,
};

struct rtgui_dc_engine
{
    /* interface */
    void (*draw_point)(struct rtgui_dc *dc, int x, int y);
    void (*draw_color_point)(struct rtgui_dc *dc, int x, int y, rtgui_color_t color);
    void (*draw_vline)(struct rtgui_dc *dc, int x, int y1, int y2);
    void (*draw_hline)(struct rtgui_dc *dc, int x1, int x2, int y);
    void (*fill_rect)(struct rtgui_dc *dc, rtgui_rect_t *rect);
    void (*blit_line)(struct rtgui_dc *dc, int x1, int x2, int y, rt_uint8_t *line_data);
    void (*blit)(struct rtgui_dc *dc, struct rtgui_point *dc_point, struct rtgui_dc *dest, rtgui_rect_t *rect);

    rt_bool_t (*fini)(struct rtgui_dc *dc);
};

/*
 * The abstract device context 
 *
 * Normally, a DC is a drawable canvas, user can draw point/line/cycle etc
 * on the DC. 
 *
 * There are several kinds of DC:
 * - Hardware DC;
 * - Client DC;
 * - Buffer DC;
 */
struct rtgui_dc
{
    /* type of device context */
    rt_uint32_t type;

    /* dc engine */
    const struct rtgui_dc_engine *engine;
};

/* 
 * The hardware device context 
 *
 * The hardware DC is a context based on hardware device, for examle the 
 * LCD device. The operations on the hardware DC are reflected to the real
 * hardware. 
 * 
 */
struct rtgui_dc_hw
{
	struct rtgui_dc parent;
	rtgui_widget_t *owner;
	const struct rtgui_graphic_driver *hw_driver;
};

/**
 * The buffer dc is a device context with memory buffer. 
 *
 * All the operations on this device context is reflected to the memory buffer.
 */
struct rtgui_dc_buffer
{
	struct rtgui_dc parent;

	/* graphic context */
	rtgui_gc_t gc;

	/* pixel format */
	rt_uint8_t pixel_format;
	rt_uint8_t blend_mode;		/* RTGUI_BLENDMODE: None/Blend/Add/Mod */

	/* width and height */
	rt_uint16_t width, height;
	/* pitch */
	rt_uint16_t pitch;

	/* pixel data */
	rt_uint8_t *pixel;
};

#define RTGUI_DC_FC(dc)         (rtgui_dc_get_gc(RTGUI_DC(dc))->foreground)
#define RTGUI_DC_BC(dc)         (rtgui_dc_get_gc(RTGUI_DC(dc))->background)
#define RTGUI_DC_FONT(dc)       (rtgui_dc_get_gc(RTGUI_DC(dc))->font)
#define RTGUI_DC_TEXTALIGN(dc)  (rtgui_dc_get_gc(RTGUI_DC(dc))->textalign)

/* create a buffer dc */
struct rtgui_dc *rtgui_dc_buffer_create(int width, int height);
struct rtgui_dc *rtgui_dc_buffer_create_pixformat(rt_uint8_t pixel_format, int w, int h);
struct rtgui_dc *rtgui_dc_buffer_create_from_dc(struct rtgui_dc* dc);

/* create a widget dc */
struct rtgui_dc *rtgui_dc_widget_create(struct rtgui_widget * owner);

/* begin and end a drawing */
struct rtgui_dc *rtgui_dc_begin_drawing(rtgui_widget_t *owner);
void rtgui_dc_end_drawing(struct rtgui_dc *dc);

/* destroy a dc */
void rtgui_dc_destory(struct rtgui_dc *dc);

rt_uint8_t *rtgui_dc_buffer_get_pixel(struct rtgui_dc *dc);

void rtgui_dc_draw_line(struct rtgui_dc *dc, int x1, int y1, int x2, int y2);
void rtgui_dc_draw_rect(struct rtgui_dc *dc, struct rtgui_rect *rect);
void rtgui_dc_fill_rect_forecolor(struct rtgui_dc *dc, struct rtgui_rect *rect);
void rtgui_dc_draw_round_rect(struct rtgui_dc *dc, struct rtgui_rect *rect, int r);
void rtgui_dc_fill_round_rect(struct rtgui_dc *dc, struct rtgui_rect *rect, int r);
/** Fill a vertical gradient rect from @c1 to @c2 */
void rtgui_dc_fill_gradient_rectv(struct rtgui_dc *dc, rtgui_rect_t *rect,
                                  rtgui_color_t c1, rtgui_color_t c2);
void rtgui_dc_draw_annulus(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t r1, rt_int16_t r2, rt_int16_t start, rt_int16_t end);
void rtgui_dc_draw_pie(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t r, rt_int16_t start, rt_int16_t end);
void rtgui_dc_fill_pie(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t r, rt_int16_t start, rt_int16_t end);

void rtgui_dc_draw_text(struct rtgui_dc *dc, const char *text, struct rtgui_rect *rect);
void rtgui_dc_draw_text_stroke(struct rtgui_dc *dc, const char *text, struct rtgui_rect *rect,
                               rtgui_color_t color_stroke, rtgui_color_t color_core);

void rtgui_dc_draw_mono_bmp(struct rtgui_dc *dc, int x, int y, int w, int h, const rt_uint8_t *data);
void rtgui_dc_draw_byte(struct rtgui_dc *dc, int x, int y, int h, const rt_uint8_t *data);
void rtgui_dc_draw_word(struct rtgui_dc *dc, int x, int y, int h, const rt_uint8_t *data);

void rtgui_dc_draw_border(struct rtgui_dc *dc, rtgui_rect_t *rect, int flag);
void rtgui_dc_draw_horizontal_line(struct rtgui_dc *dc, int x1, int x2, int y);
void rtgui_dc_draw_vertical_line(struct rtgui_dc *dc, int x, int y1, int y2);
void rtgui_dc_draw_focus_rect(struct rtgui_dc *dc, rtgui_rect_t *rect);

void rtgui_dc_draw_polygon(struct rtgui_dc *dc, const int *vx, const int *vy, int count);
void rtgui_dc_fill_polygon(struct rtgui_dc *dc, const int *vx, const int *vy, int count);

void rtgui_dc_draw_circle(struct rtgui_dc *dc, int x, int y, int r);
void rtgui_dc_fill_circle(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t r);
void rtgui_dc_draw_arc(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t r, rt_int16_t start, rt_int16_t end);

void rtgui_dc_draw_ellipse(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t rx, rt_int16_t ry);
void rtgui_dc_fill_ellipse(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t rx, rt_int16_t ry);

/* alpha blending functions */
void rtgui_dc_draw_aa_line(struct rtgui_dc * dst,int x1,int y1,int x2,int y2);
void rtgui_dc_draw_aa_lines(struct rtgui_dc * dst,const struct rtgui_point * points,int count);

void rtgui_dc_blend_point(struct rtgui_dc * dst,int x,int y,enum RTGUI_BLENDMODE blendMode,rt_uint8_t r,rt_uint8_t g,rt_uint8_t b,rt_uint8_t a);
void rtgui_dc_blend_points(struct rtgui_dc * dst,const rtgui_point_t * points,int count,enum RTGUI_BLENDMODE blendMode,rt_uint8_t r,rt_uint8_t g,rt_uint8_t b,rt_uint8_t a);

void rtgui_dc_blend_line(struct rtgui_dc * dst,int x1,int y1,int x2,int y2,enum RTGUI_BLENDMODE blendMode,rtgui_color_t color);
void rtgui_dc_blend_lines(struct rtgui_dc * dst,const rtgui_point_t * points,int count,enum RTGUI_BLENDMODE blendMode,rtgui_color_t color);

void rtgui_dc_blend_fill_rect(struct rtgui_dc * dst,const rtgui_rect_t * rect,enum RTGUI_BLENDMODE blendMode,rtgui_color_t color);
void rtgui_dc_blend_fill_rects(struct rtgui_dc * dst,const rtgui_rect_t * rects,int count,enum RTGUI_BLENDMODE blendMode,rtgui_color_t color);

void rtgui_dc_draw_aa_circle(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t r);
void rtgui_dc_draw_aa_ellipse(struct rtgui_dc *dc, rt_int16_t  x, rt_int16_t y, rt_int16_t rx, rt_int16_t ry);

int rtgui_dc_draw_thick_line(struct rtgui_dc * dst, rt_int16_t x1, rt_int16_t y1, rt_int16_t x2, rt_int16_t y2, rt_uint8_t width);

/*
 * dc inline function
 *
 * Note:
 * In order to improve drawing speed, put most of common function of dc to inline
 */

/*
 * draw a point on dc
 */
rt_inline void rtgui_dc_draw_point(struct rtgui_dc *dc, int x, int y)
{
    dc->engine->draw_point(dc, x, y);
}

/*
 * draw a color point on dc
 */
rt_inline void rtgui_dc_draw_color_point(struct rtgui_dc *dc, int x, int y, rtgui_color_t color)
{
    dc->engine->draw_color_point(dc, x, y, color);
}

/*
 * draw a vertical line on dc
 */
rt_inline void rtgui_dc_draw_vline(struct rtgui_dc *dc, int x, int y1, int y2)
{
    dc->engine->draw_vline(dc, x, y1, y2);
}

/*
 * draw a horizontal line on dc
 */
rt_inline void rtgui_dc_draw_hline(struct rtgui_dc *dc, int x1, int x2, int y)
{
    dc->engine->draw_hline(dc, x1, x2, y);
}

/*
 * fill a rect with background color
 */
rt_inline void rtgui_dc_fill_rect(struct rtgui_dc *dc, struct rtgui_rect *rect)
{
    dc->engine->fill_rect(dc, rect);
}

/*
 * blit a dc (x, y) on another dc(rect)
 */
rt_inline void rtgui_dc_blit(struct rtgui_dc *dc, struct rtgui_point *dc_point, struct rtgui_dc *dest, rtgui_rect_t *rect)
{
    dc->engine->blit(dc, dc_point, dest, rect);
}

/* set gc of dc */
void rtgui_dc_set_gc(struct rtgui_dc *dc, rtgui_gc_t *gc);
/* get gc of dc */
rtgui_gc_t *rtgui_dc_get_gc(struct rtgui_dc *dc);
/* get visible status of dc */
rt_bool_t rtgui_dc_get_visible(struct rtgui_dc *dc);
/* get rect of dc */
void rtgui_dc_get_rect(struct rtgui_dc *dc, rtgui_rect_t *rect);
/* get pixel format */
rt_uint8_t rtgui_dc_get_pixel_format(struct rtgui_dc *dc);
/* coordinate conversion */
void rtgui_dc_logic_to_device(struct rtgui_dc* dc, struct rtgui_point *point);
void rtgui_dc_rect_to_device(struct rtgui_dc* dc, struct rtgui_rect* rect);

/* dc rotation and zoom operations */
struct rtgui_dc *rtgui_dc_shrink(struct rtgui_dc *dc, int factorx, int factory);
struct rtgui_dc *rtgui_dc_zoom(struct rtgui_dc *dc, double zoomx, double zoomy, int smooth);
struct rtgui_dc *rtgui_dc_rotozoom(struct rtgui_dc *dc, double angle, double zoomx, double zoomy, int smooth);

#ifdef __cplusplus
}
#endif

#endif

