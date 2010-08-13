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
#include <rtgui/widgets/view.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/workbench.h>
#include <rtgui/widgets/title.h>

static void rtgui_dc_hw_draw_point(struct rtgui_dc* dc, int x, int y);
static void rtgui_dc_hw_draw_color_point(struct rtgui_dc* dc, int x, int y, rtgui_color_t color);
static void rtgui_dc_hw_draw_hline(struct rtgui_dc* dc, int x1, int x2, int y);
static void rtgui_dc_hw_draw_vline(struct rtgui_dc* dc, int x, int y1, int y2);
static void rtgui_dc_hw_fill_rect (struct rtgui_dc* dc, rtgui_rect_t* rect);
static void rtgui_dc_hw_blit	  (struct rtgui_dc* dc, struct rtgui_point* dc_point, struct rtgui_dc* dest, rtgui_rect_t* rect);
static void rtgui_dc_hw_set_gc (struct rtgui_dc* dc, rtgui_gc_t *gc);
static rtgui_gc_t *rtgui_dc_hw_get_gc (struct rtgui_dc* dc);
static rt_bool_t rtgui_dc_hw_fini(struct rtgui_dc* dc);
static rt_bool_t rtgui_dc_hw_get_visible(struct rtgui_dc* dc);
static void rtgui_dc_hw_get_rect(struct rtgui_dc* dc, rtgui_rect_t* rect);

#define hw_driver				(rtgui_graphic_driver_get_default())
#define dc_set_foreground(c) 	dc->gc.foreground = c
#define dc_set_background(c) 	dc->gc.background = c

const struct rtgui_dc_engine dc_hw_engine = 
{
	rtgui_dc_hw_draw_point,
	rtgui_dc_hw_draw_color_point,
	rtgui_dc_hw_draw_vline,
	rtgui_dc_hw_draw_hline,
	rtgui_dc_hw_fill_rect,
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
	struct rtgui_dc* dc;
	rtgui_widget_t* widget;

	/* adjudge owner */
	if (owner == RT_NULL || owner->toplevel == RT_NULL) return RT_NULL;
	if (!RTGUI_IS_TOPLEVEL(owner->toplevel)) return RT_NULL;

	dc = RTGUI_WIDGET_DC(owner);
	/* set init visible as true */
	RTGUI_WIDGET_DC_SET_VISIBLE(owner);

	/* check widget visible */
	widget = owner;
	while (widget != RT_NULL)
	{
		if (RTGUI_WIDGET_IS_HIDE(widget))
		{
			RTGUI_WIDGET_DC_SET_UNVISIBLE(owner);
			break;
		}

		widget = widget->parent;
	}

	if (RTGUI_IS_WINTITLE(owner->toplevel))
	{
		rtgui_toplevel_t* top = RTGUI_TOPLEVEL(owner->toplevel);
		top->drawing ++;

		if (top->drawing == 1)
		{
#ifdef RTGUI_USING_MOUSE_CURSOR
#ifdef __WIN32__
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
	else if (RTGUI_IS_WORKBENCH(owner->toplevel) ||
		RTGUI_IS_WIN(owner->toplevel))
	{
		rtgui_toplevel_t* top = RTGUI_TOPLEVEL(owner->toplevel);
		top->drawing ++;

		if (top->drawing == 1)
		{
#ifdef __WIN32__
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

			rtgui_thread_send(top->server, (struct rtgui_event*)&eupdate, sizeof(eupdate));
#endif
		}
	}

	return dc;
}

static rt_bool_t rtgui_dc_hw_fini(struct rtgui_dc* dc)
{
	rtgui_widget_t* owner;
	
	if (dc == RT_NULL || dc->type != RTGUI_DC_HW) return RT_FALSE;

	/* get owner */
	owner = RTGUI_CONTAINER_OF(dc, struct rtgui_widget, dc_type);

	if (RTGUI_IS_WINTITLE(owner->toplevel))
	{
		/* update title extent */
		rtgui_toplevel_t* top = RTGUI_TOPLEVEL(owner->toplevel);

		top->drawing --;
		if ((top->drawing == 0) && RTGUI_WIDGET_IS_DC_VISIBLE(owner))
		{
#ifdef __WIN32__
#ifdef RTGUI_USING_MOUSE_CURSOR
			rt_mutex_release(&cursor_mutex);
			/* show cursor */
			rtgui_mouse_show_cursor();
			rt_kprintf("show cursor\n");
#endif
			/* update screen */
			hw_driver->screen_update(&(owner->extent));
#else
#ifdef RTGUI_USING_MOUSE_CURSOR
			/* show cursor */
			rtgui_mouse_show_cursor();
#endif

			/* update screen */
			hw_driver->screen_update(&(owner->extent));
#endif
		}
	}
	else if (RTGUI_IS_WORKBENCH(owner->toplevel) ||
		RTGUI_IS_WIN(owner->toplevel))
	{
		rtgui_toplevel_t* top = RTGUI_TOPLEVEL(owner->toplevel);
		top->drawing --;

		if ((top->drawing == 0) && RTGUI_WIDGET_IS_DC_VISIBLE(owner))
		{
#ifdef __WIN32__
#ifdef RTGUI_USING_MOUSE_CURSOR
			rt_mutex_release(&cursor_mutex);
			/* show cursor */
			rtgui_mouse_show_cursor();
			rt_kprintf("show cursor\n");
#endif
			/* update screen */
			hw_driver->screen_update(&(owner->extent));
#else
			/* send to server to end drawing */
			struct rtgui_event_update_end eupdate;
			RTGUI_EVENT_UPDATE_END_INIT(&(eupdate));
			eupdate.rect = owner->extent;

			rtgui_thread_send(top->server, (struct rtgui_event*)&eupdate, sizeof(eupdate));
#endif
		}
	}

	return RT_TRUE;
}

/*
 * draw a logic point on device
 */
static void rtgui_dc_hw_draw_point(struct rtgui_dc* self, int x, int y)
{
	rtgui_rect_t rect;
	rtgui_widget_t *owner;

	if (self == RT_NULL) return;
	
	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);
	if (!RTGUI_WIDGET_IS_DC_VISIBLE(owner)) return;

	x = x + owner->extent.x1;
	y = y + owner->extent.y1;

	/* draw this point */
	hw_driver->set_pixel(&(owner->gc.foreground), x, y);
}

static void rtgui_dc_hw_draw_color_point(struct rtgui_dc* self, int x, int y, rtgui_color_t color)
{
	rtgui_rect_t rect;
	rtgui_widget_t *owner;

	if (self == RT_NULL) return;
	
	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);
	if (!RTGUI_WIDGET_IS_DC_VISIBLE(owner)) return;

	x = x + owner->extent.x1;
	y = y + owner->extent.y1;

	/* draw this point */
	hw_driver->set_pixel(&color, x, y);
}

/*
 * draw a logic vertical line on device
 */
static void rtgui_dc_hw_draw_vline(struct rtgui_dc* self, int x, int y1, int y2)
{
	register rt_base_t index;
	rtgui_widget_t *owner;

	if (self == RT_NULL) return;
	
	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);
	if (!RTGUI_WIDGET_IS_DC_VISIBLE(owner)) return;

	x  = x + owner->extent.x1;
	y1 = y1 + owner->extent.y1;
	y2 = y2 + owner->extent.y1;

	/* draw vline */
	hw_driver->draw_vline(&(owner->gc.foreground), x, y1, y2);
}

/*
 * draw a logic horizontal line on device
 */
static void rtgui_dc_hw_draw_hline(struct rtgui_dc* self, int x1, int x2, int y)
{
	register rt_base_t index;
	rtgui_widget_t *owner;

	if (self == RT_NULL) return;
	
	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);
	if (!RTGUI_WIDGET_IS_DC_VISIBLE(owner)) return;

	/* convert logic to device */
	x1 = x1 + owner->extent.x1;
	x2 = x2 + owner->extent.x1;
	y  = y + owner->extent.y1;

	/* draw hline */
	hw_driver->draw_hline(&(owner->gc.foreground), x1, x2, y);
}

static void rtgui_dc_hw_fill_rect (struct rtgui_dc* self, struct rtgui_rect* rect)
{
	rtgui_color_t color;
	register rt_base_t index, x1, x2;
	rtgui_widget_t *owner;

	if (self == RT_NULL) return;

	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);
	if (!RTGUI_WIDGET_IS_DC_VISIBLE(owner)) return;

	/* get background color */
	color = owner->gc.background;
	/* convert logic to device */
	x1 = rect->x1 + owner->extent.x1;
	x2 = rect->x2 + owner->extent.x1;

	/* fill rect */
	for (index = owner->extent.y1 + rect->y1; index < owner->extent.y1 + rect->y2; index ++)
	{
		hw_driver->draw_hline(&color, x1, x2, index);
	}
}

static void rtgui_dc_hw_blit(struct rtgui_dc* dc, struct rtgui_point* dc_point, struct rtgui_dc* dest, rtgui_rect_t* rect)
{
	/* not blit in hardware dc */
	return ;
}

static void rtgui_dc_hw_set_gc(struct rtgui_dc* self, rtgui_gc_t *gc)
{
	rtgui_widget_t *owner;

	if (self == RT_NULL) return;
	
	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);
	owner->gc = *gc;
}

static rtgui_gc_t* rtgui_dc_hw_get_gc(struct rtgui_dc* self)
{
	rtgui_widget_t *owner;

	if (self == RT_NULL) 
	{
	rt_kprintf("why!!\n");
	return RT_NULL;
	}
	
	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);

	return &(owner->gc);
}

static rt_bool_t rtgui_dc_hw_get_visible(struct rtgui_dc* self)
{
	rtgui_widget_t *owner;

	if (self == RT_NULL) return RT_FALSE;
	
	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);
	if (!RTGUI_WIDGET_IS_DC_VISIBLE(owner)) return RT_FALSE;

	return RT_TRUE;
}

static void rtgui_dc_hw_get_rect(struct rtgui_dc* self, rtgui_rect_t* rect)
{
	rtgui_widget_t *owner;

	if (self == RT_NULL) return;
	
	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);
	rtgui_widget_get_rect(owner, rect);
}

void rtgui_dc_hw_draw_raw_hline(struct rtgui_dc* self, rt_uint8_t* raw_ptr, int x1, int x2, int y)
{
	register rt_base_t index;
	rtgui_widget_t *owner;

	if (self == RT_NULL) return;
	
	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);
	if (!RTGUI_WIDGET_IS_DC_VISIBLE(owner)) return;

	/* convert logic to device */
	x1 = x1 + owner->extent.x1;
	x2 = x2 + owner->extent.x1;
	y  = y + owner->extent.y1;

	/* draw raw hline */
	hw_driver->draw_raw_hline(raw_ptr, x1, x2, y);
}

