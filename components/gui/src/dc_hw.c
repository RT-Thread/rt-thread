/*
 * File      : dc_hw.c
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
#include <rtgui/dc.h>
#include <rtgui/dc_hw.h>
#include <rtgui/driver.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/rtgui_server.h>

#include <rtgui/widgets/container.h>
#include <rtgui/widgets/window.h>

#define _int_swap(x, y)         do {x ^= y; y ^= x; x ^= y;} while (0)

static void rtgui_dc_hw_draw_point(struct rtgui_dc *dc, int x, int y);
static void rtgui_dc_hw_draw_color_point(struct rtgui_dc *dc, int x, int y, rtgui_color_t color);
static void rtgui_dc_hw_draw_hline(struct rtgui_dc *dc, int x1, int x2, int y);
static void rtgui_dc_hw_draw_vline(struct rtgui_dc *dc, int x, int y1, int y2);
static void rtgui_dc_hw_fill_rect(struct rtgui_dc *dc, rtgui_rect_t *rect);
static void rtgui_dc_hw_blit_line(struct rtgui_dc *self, int x1, int x2, int y, rt_uint8_t *line_data);
static void rtgui_dc_hw_blit(struct rtgui_dc *dc, struct rtgui_point *dc_point, struct rtgui_dc *dest, rtgui_rect_t *rect);
static rt_bool_t rtgui_dc_hw_fini(struct rtgui_dc *dc);

const struct rtgui_dc_engine dc_hw_engine =
{
    rtgui_dc_hw_draw_point,
    rtgui_dc_hw_draw_color_point,
    rtgui_dc_hw_draw_vline,
    rtgui_dc_hw_draw_hline,
    rtgui_dc_hw_fill_rect,
    rtgui_dc_hw_blit_line,
    rtgui_dc_hw_blit,

    rtgui_dc_hw_fini,
};

struct rtgui_dc *rtgui_dc_hw_create(rtgui_widget_t *owner)
{
    struct rtgui_dc_hw *dc;

    /* adjudge owner */
    if (owner == RT_NULL || owner->toplevel == RT_NULL) return RT_NULL;

    /* create DC */
    dc = (struct rtgui_dc_hw *) rtgui_malloc(sizeof(struct rtgui_dc_hw));
	if (dc)
	{
		dc->parent.type = RTGUI_DC_HW;
		dc->parent.engine = &dc_hw_engine;
		dc->owner = owner;
		dc->hw_driver = rtgui_graphic_driver_get_default();

		return &(dc->parent);
	}

	return RT_NULL;
}

static rt_bool_t rtgui_dc_hw_fini(struct rtgui_dc *dc)
{
    if (dc == RT_NULL || dc->type != RTGUI_DC_HW) return RT_FALSE;

    /* release hardware dc */
    rtgui_free(dc);

    return RT_TRUE;
}

/*
 * draw a logic point on device
 */
static void rtgui_dc_hw_draw_point(struct rtgui_dc *self, int x, int y)
{
    struct rtgui_dc_hw *dc;

    RT_ASSERT(self != RT_NULL);
    dc = (struct rtgui_dc_hw *) self;

    if (x < 0 || y < 0)
        return;

    x = x + dc->owner->extent.x1;
    if (x >= dc->owner->extent.x2)
        return;
    y = y + dc->owner->extent.y1;
    if (y >= dc->owner->extent.y2)
        return;

    /* draw this point */
    dc->hw_driver->ops->set_pixel(&(dc->owner->gc.foreground), x, y);
}

static void rtgui_dc_hw_draw_color_point(struct rtgui_dc *self, int x, int y, rtgui_color_t color)
{
    struct rtgui_dc_hw *dc;

    RT_ASSERT(self != RT_NULL);
    dc = (struct rtgui_dc_hw *) self;

    if (x < 0 || y < 0)
        return;

    x = x + dc->owner->extent.x1;
    if (x >= dc->owner->extent.x2)
        return;
    y = y + dc->owner->extent.y1;
    if (y >= dc->owner->extent.y2)
        return;

    /* draw this point */
    dc->hw_driver->ops->set_pixel(&color, x, y);
}

/*
 * draw a logic vertical line on device
 */
static void rtgui_dc_hw_draw_vline(struct rtgui_dc *self, int x, int y1, int y2)
{
    struct rtgui_dc_hw *dc;

    RT_ASSERT(self != RT_NULL);
    dc = (struct rtgui_dc_hw *) self;

    if (x < 0)
        return;
    x = x + dc->owner->extent.x1;
    if (x >= dc->owner->extent.x2)
        return;
    y1 = y1 + dc->owner->extent.y1;
    y2 = y2 + dc->owner->extent.y1;

    if (y1 > y2)
        _int_swap(y1, y2);
    if (y1 > dc->owner->extent.y2 || y2 < dc->owner->extent.y1)
        return;

    if (y1 < dc->owner->extent.y1)
        y1 = dc->owner->extent.y1;
    if (y2 > dc->owner->extent.y2)
        y2 = dc->owner->extent.y2;


    /* draw vline */
    dc->hw_driver->ops->draw_vline(&(dc->owner->gc.foreground), x, y1, y2);
}

/*
 * draw a logic horizontal line on device
 */
static void rtgui_dc_hw_draw_hline(struct rtgui_dc *self, int x1, int x2, int y)
{
    struct rtgui_dc_hw *dc;

    RT_ASSERT(self != RT_NULL);
    dc = (struct rtgui_dc_hw *) self;

    if (y < 0)
        return;
    y = y + dc->owner->extent.y1;
    if (y >= dc->owner->extent.y2)
        return;

    /* convert logic to device */
    x1 = x1 + dc->owner->extent.x1;
    x2 = x2 + dc->owner->extent.x1;
    if (x1 > x2)
        _int_swap(x1, x2);
    if (x1 > dc->owner->extent.x2 || x2 < dc->owner->extent.x1)
        return;

    if (x1 < dc->owner->extent.x1)
        x1 = dc->owner->extent.x1;
    if (x2 > dc->owner->extent.x2)
        x2 = dc->owner->extent.x2;

    /* draw hline */
    dc->hw_driver->ops->draw_hline(&(dc->owner->gc.foreground), x1, x2, y);
}

static void rtgui_dc_hw_fill_rect(struct rtgui_dc *self, struct rtgui_rect *rect)
{
    rtgui_color_t color;
    register rt_base_t y1, y2, x1, x2;
    struct rtgui_dc_hw *dc;

    RT_ASSERT(self != RT_NULL);
    RT_ASSERT(rect);
    dc = (struct rtgui_dc_hw *) self;

    /* get background color */
    color = dc->owner->gc.background;

    /* convert logic to device */
    x1 = rect->x1 + dc->owner->extent.x1;
    if (x1 > dc->owner->extent.x2)
        return;
    if (x1 < dc->owner->extent.x1)
        x1 = dc->owner->extent.x1;
    x2 = rect->x2 + dc->owner->extent.x1;
    if (x2 < dc->owner->extent.x1)
        return;
    if (x2 > dc->owner->extent.x2)
        x2 = dc->owner->extent.x2;

    y1 = rect->y1 + dc->owner->extent.y1;
    if (y1 > dc->owner->extent.y2)
        return;
    if (y1 < dc->owner->extent.y1)
        y1 = dc->owner->extent.y1;
    y2 = rect->y2 + dc->owner->extent.y1;
    if (y2 < dc->owner->extent.y1)
        return;
    if (y2 > dc->owner->extent.y2)
        y2 = dc->owner->extent.y2;

    /* fill rect */
    for (; y1 < y2; y1++)
    {
        dc->hw_driver->ops->draw_hline(&color, x1, x2, y1);
    }
}

static void rtgui_dc_hw_blit_line(struct rtgui_dc *self, int x1, int x2, int y, rt_uint8_t *line_data)
{
    struct rtgui_dc_hw *dc;

    RT_ASSERT(self != RT_NULL);
    dc = (struct rtgui_dc_hw *) self;

    /* convert logic to device */
    if (y < 0)
        return;
    y = y + dc->owner->extent.y1;
    if (y > dc->owner->extent.y2)
        return;

    x1 = x1 + dc->owner->extent.x1;
    x2 = x2 + dc->owner->extent.x1;
    if (x1 > x2)
        _int_swap(x1, x2);

    if (x1 > dc->owner->extent.x2 || x2 < dc->owner->extent.x1)
        return;
    if (x1 < dc->owner->extent.x1)
        x1 = dc->owner->extent.x1;
    if (x2 > dc->owner->extent.x2)
        x2 = dc->owner->extent.x2;

    dc->hw_driver->ops->draw_raw_hline(line_data, x1, x2, y);
}

static void rtgui_dc_hw_blit(struct rtgui_dc *dc,
                             struct rtgui_point *dc_point,
                             struct rtgui_dc *dest,
                             rtgui_rect_t *rect)
{
    /* not blit in hardware dc */
    return ;
}

