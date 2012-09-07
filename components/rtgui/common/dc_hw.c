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
#include <rtgui/widgets/title.h>

#define _int_swap(x, y)			do {x ^= y; y ^= x; x ^= y;} while (0)

static void rtgui_dc_hw_draw_point(struct rtgui_dc* dc, int x, int y);
static void rtgui_dc_hw_draw_color_point(struct rtgui_dc* dc, int x, int y, rtgui_color_t color);
static void rtgui_dc_hw_draw_hline(struct rtgui_dc* dc, int x1, int x2, int y);
static void rtgui_dc_hw_draw_vline(struct rtgui_dc* dc, int x, int y1, int y2);
static void rtgui_dc_hw_fill_rect (struct rtgui_dc* dc, rtgui_rect_t* rect);
static void rtgui_dc_hw_blit_line (struct rtgui_dc* self, int x1, int x2, int y, rt_uint8_t* line_data);
static void rtgui_dc_hw_blit	  (struct rtgui_dc* dc, struct rtgui_point* dc_point, struct rtgui_dc* dest, rtgui_rect_t* rect);
static void rtgui_dc_hw_set_gc (struct rtgui_dc* dc, rtgui_gc_t *gc);
static rtgui_gc_t *rtgui_dc_hw_get_gc (struct rtgui_dc* dc);
static rt_bool_t rtgui_dc_hw_fini(struct rtgui_dc* dc);
static rt_bool_t rtgui_dc_hw_get_visible(struct rtgui_dc* dc);
static void rtgui_dc_hw_get_rect(struct rtgui_dc* dc, rtgui_rect_t* rect);

struct rtgui_dc_hw
{
	struct rtgui_dc parent;
	rtgui_widget_t *owner;
	const struct rtgui_graphic_driver* hw_driver;
};

const struct rtgui_dc_engine dc_hw_engine = 
{
	rtgui_dc_hw_draw_point,
	rtgui_dc_hw_draw_color_point,
	rtgui_dc_hw_draw_vline,
	rtgui_dc_hw_draw_hline,
	rtgui_dc_hw_fill_rect,
	rtgui_dc_hw_blit_line,
	rtgui_dc_hw_blit,

	rtgui_dc_hw_set_gc,
	rtgui_dc_hw_get_gc,

	rtgui_dc_hw_get_visible,
	rtgui_dc_hw_get_rect,

	rtgui_dc_hw_fini,
};

extern struct rt_mutex cursor_mutex;
extern void rtgui_mouse_show_cursor(void);
extern void rtgui_mouse_hide_cursor(void);
struct rtgui_dc* rtgui_dc_hw_create(rtgui_widget_t* owner)
{
	struct rtgui_dc_hw* dc;
	rtgui_widget_t* widget;

	/* adjudge owner */
	if (owner == RT_NULL || owner->toplevel == RT_NULL) return RT_NULL;
	if (!RTGUI_IS_WIN(owner->toplevel)) return RT_NULL;

	/* set init visible as true */
	RTGUI_WIDGET_DC_SET_VISIBLE(owner);

	/* check widget visible */
	widget = owner;
	while (widget != RT_NULL)
	{
		if (RTGUI_WIDGET_IS_HIDE(widget))
		{
			RTGUI_WIDGET_DC_SET_UNVISIBLE(owner);
			return RT_NULL;
		}

		widget = widget->parent;
	}

	if (!RTGUI_WIDGET_IS_DC_VISIBLE(owner)) return RT_NULL;

	/* create DC */
	dc = (struct rtgui_dc_hw*) rtgui_malloc(sizeof(struct rtgui_dc_hw));
	dc->parent.type = RTGUI_DC_HW;
	dc->parent.engine = &dc_hw_engine;
	dc->owner = owner;
	dc->hw_driver = rtgui_graphic_driver_get_default();

	if (RTGUI_IS_WINTITLE(owner->toplevel))
	{
		struct rtgui_win* top = RTGUI_WIN(owner->toplevel);
		top->drawing ++;

		if (top->drawing == 1)
		{
#ifdef RTGUI_USING_MOUSE_CURSOR
#ifdef _WIN32
			rt_mutex_take(&cursor_mutex, RT_WAITING_FOREVER);
			rt_kprintf("hide cursor\n");
			rtgui_mouse_hide_cursor();
#else
			/* hide cursor */
			rtgui_mouse_hide_cursor();
#endif
#endif
		}
	}
	else if (RTGUI_IS_APP(owner->toplevel) ||
		RTGUI_IS_WIN(owner->toplevel))
	{
		struct rtgui_win* top = RTGUI_WIN(owner->toplevel);
		top->drawing ++;

		if (top->drawing == 1)
		{
#ifdef _WIN32
#ifdef RTGUI_USING_MOUSE_CURSOR
			rt_mutex_take(&cursor_mutex, RT_WAITING_FOREVER);
			rt_kprintf("hide cursor\n");
			rtgui_mouse_hide_cursor();
#endif
#else
			/* send draw begin to server */
			struct rtgui_event_update_begin eupdate;
			RTGUI_EVENT_UPDATE_BEGIN_INIT(&(eupdate));
			eupdate.rect = RTGUI_WIDGET(top)->extent;

			rtgui_server_post_event((struct rtgui_event*)&eupdate, sizeof(eupdate));
#endif
		}
	}

	return &(dc->parent);
}

static rt_bool_t rtgui_dc_hw_fini(struct rtgui_dc* dc)
{
	rtgui_widget_t* owner;
	struct rtgui_dc_hw* self;

	if (dc == RT_NULL || dc->type != RTGUI_DC_HW) return RT_FALSE;

	self = (struct rtgui_dc_hw*)dc;
	/* get owner */
	owner = self->owner;

	if (RTGUI_IS_WINTITLE(owner->toplevel))
	{
		/* update title extent */
		struct rtgui_win* top = RTGUI_WIN(owner->toplevel);

		top->drawing --;
		if ((top->drawing == 0) && RTGUI_WIDGET_IS_DC_VISIBLE(owner))
		{
#ifdef _WIN32
#ifdef RTGUI_USING_MOUSE_CURSOR
			rt_mutex_release(&cursor_mutex);
			/* show cursor */
			rtgui_mouse_show_cursor();
			rt_kprintf("show cursor\n");
#endif
			/* update screen */
			rtgui_graphic_driver_screen_update(self->hw_driver, &(owner->extent));
#else
#ifdef RTGUI_USING_MOUSE_CURSOR
			/* show cursor */
			rtgui_mouse_show_cursor();
#endif

			/* update screen */
			rtgui_graphic_driver_screen_update(self->hw_driver, &(owner->extent));
#endif
		}
	}
	else if (RTGUI_IS_APP(owner->toplevel) ||
		RTGUI_IS_WIN(owner->toplevel))
	{
		struct rtgui_win* top = RTGUI_WIN(owner->toplevel);
		top->drawing --;

		if ((top->drawing == 0) && RTGUI_WIDGET_IS_DC_VISIBLE(owner))
		{
#ifdef _WIN32
#ifdef RTGUI_USING_MOUSE_CURSOR
			rt_mutex_release(&cursor_mutex);
			/* show cursor */
			rtgui_mouse_show_cursor();
			rt_kprintf("show cursor\n");
#endif
			/* update screen */
			rtgui_graphic_driver_screen_update(self->hw_driver, &(owner->extent));
#else
			/* send to server to end drawing */
			struct rtgui_event_update_end eupdate;
			RTGUI_EVENT_UPDATE_END_INIT(&(eupdate));
			eupdate.rect = owner->extent;

			rtgui_server_post_event((struct rtgui_event*)&eupdate, sizeof(eupdate));
#endif
		}
	}

	/* release hardware dc */
	rtgui_free(self);

	return RT_TRUE;
}

/*
 * draw a logic point on device
 */
static void rtgui_dc_hw_draw_point(struct rtgui_dc* self, int x, int y)
{
	struct rtgui_dc_hw* dc;

	RT_ASSERT(self != RT_NULL);
	dc = (struct rtgui_dc_hw*) self;

	x = x + dc->owner->extent.x1;
#if (0) /* Please yourself to decide whether to use it*/
	if(x < dc->owner->extent.x1 || x >= dc->owner->extent.x2) return;
#endif
	y = y + dc->owner->extent.y1;
#if (0)
	if(y < dc->owner->extent.y1 || y >= dc->owner->extent.y2) return;
#endif
	/* draw this point */
	dc->hw_driver->ops->set_pixel(&(dc->owner->gc.foreground), x, y);
}

static void rtgui_dc_hw_draw_color_point(struct rtgui_dc* self, int x, int y, rtgui_color_t color)
{
	struct rtgui_dc_hw* dc;

	RT_ASSERT(self != RT_NULL);
	dc = (struct rtgui_dc_hw*) self;

	x = x + dc->owner->extent.x1;
	y = y + dc->owner->extent.y1;

	/* draw this point */
	dc->hw_driver->ops->set_pixel(&color, x, y);
}

/*
 * draw a logic vertical line on device
 */
static void rtgui_dc_hw_draw_vline(struct rtgui_dc* self, int x, int y1, int y2)
{
	struct rtgui_dc_hw* dc;

	RT_ASSERT(self != RT_NULL);
	dc = (struct rtgui_dc_hw*) self;

	x = x + dc->owner->extent.x1;
	y1 = y1 + dc->owner->extent.y1;
	y2 = y2 + dc->owner->extent.y1;
	if (y1 > y2) _int_swap(y1, y2);

	/* draw vline */
	dc->hw_driver->ops->draw_vline(&(dc->owner->gc.foreground), x, y1, y2);
}

/*
 * draw a logic horizontal line on device
 */
static void rtgui_dc_hw_draw_hline(struct rtgui_dc* self, int x1, int x2, int y)
{
	struct rtgui_dc_hw* dc;

	RT_ASSERT(self != RT_NULL);
	dc = (struct rtgui_dc_hw*) self;

	/* convert logic to device */
	x1 = x1 + dc->owner->extent.x1;
	x2 = x2 + dc->owner->extent.x1;
	if (x1 > x2) _int_swap(x1, x2);	
	y  = y + dc->owner->extent.y1;

	/* draw hline */
	dc->hw_driver->ops->draw_hline(&(dc->owner->gc.foreground), x1, x2, y);
}

static void rtgui_dc_hw_fill_rect (struct rtgui_dc* self, struct rtgui_rect* rect)
{
	rtgui_color_t color;
	register rt_base_t index, x1, x2;
	struct rtgui_dc_hw* dc;

	RT_ASSERT(self != RT_NULL);
	dc = (struct rtgui_dc_hw*) self;

	/* get background color */
	color = dc->owner->gc.background;
	/* convert logic to device */
	x1 = rect->x1 + dc->owner->extent.x1;
	x2 = rect->x2 + dc->owner->extent.x1;

	/* fill rect */
	for (index = dc->owner->extent.y1 + rect->y1; index < dc->owner->extent.y1 + rect->y2; index ++)
	{
		dc->hw_driver->ops->draw_hline(&color, x1, x2, index);
	}
}

static void rtgui_dc_hw_blit_line (struct rtgui_dc* self, int x1, int x2, int y, rt_uint8_t* line_data)
{
	struct rtgui_dc_hw* dc;

	RT_ASSERT(self != RT_NULL);
	dc = (struct rtgui_dc_hw*) self;

	/* convert logic to device */
	x1 = x1 + dc->owner->extent.x1;
	x2 = x2 + dc->owner->extent.x1;
	if (x1 > x2) _int_swap(x1, x2);	
	y  = y + dc->owner->extent.y1;

	dc->hw_driver->ops->draw_raw_hline(line_data, x1, x2, y);
}

static void rtgui_dc_hw_blit(struct rtgui_dc* dc, struct rtgui_point* dc_point, struct rtgui_dc* dest, rtgui_rect_t* rect)
{
	/* not blit in hardware dc */
	return ;
}

static void rtgui_dc_hw_set_gc(struct rtgui_dc* self, rtgui_gc_t *gc)
{
	struct rtgui_dc_hw* dc;

	RT_ASSERT(self != RT_NULL);
	dc = (struct rtgui_dc_hw*) self;

	/* set gc */
	dc->owner->gc = *gc;
}

static rtgui_gc_t* rtgui_dc_hw_get_gc(struct rtgui_dc* self)
{
	struct rtgui_dc_hw* dc;

	RT_ASSERT(self != RT_NULL);
	dc = (struct rtgui_dc_hw*) self;

	return &(dc->owner->gc);
}

static rt_bool_t rtgui_dc_hw_get_visible(struct rtgui_dc* self)
{
	struct rtgui_dc_hw* dc;

	RT_ASSERT(self != RT_NULL);
	dc = (struct rtgui_dc_hw*) self;

	if (!RTGUI_WIDGET_IS_DC_VISIBLE(dc->owner)) return RT_FALSE;

	return RT_TRUE;
}

static void rtgui_dc_hw_get_rect(struct rtgui_dc* self, rtgui_rect_t* rect)
{
	struct rtgui_dc_hw* dc;

	RT_ASSERT(self != RT_NULL);
	dc = (struct rtgui_dc_hw*) self;

	/* get owner */
	rtgui_widget_get_rect(dc->owner, rect);
}
