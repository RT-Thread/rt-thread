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

struct rtgui_dc* rtgui_dc_begin_drawing(rtgui_widget_t* owner)
{
	return rtgui_dc_hw_create(owner);
}

void rtgui_dc_end_drawing(struct rtgui_dc* dc)
{
	if (rtgui_dc_hw_fini(dc) == RT_TRUE)
	{
		rtgui_free(dc);
	}
}

void rtgui_dc_hw_init(struct rtgui_dc_hw* dc)
{
	if (dc == RT_NULL) return;

	dc->parent.type		  = RTGUI_DC_HW;
	dc->parent.draw_point = rtgui_dc_hw_draw_point;
	dc->parent.draw_color_point = rtgui_dc_hw_draw_color_point;
	dc->parent.draw_hline = rtgui_dc_hw_draw_hline;
	dc->parent.draw_vline = rtgui_dc_hw_draw_vline;
	dc->parent.fill_rect  = rtgui_dc_hw_fill_rect ;
	dc->parent.blit		  = rtgui_dc_hw_blit;

	dc->parent.set_gc     = rtgui_dc_hw_set_gc;
	dc->parent.get_gc     = rtgui_dc_hw_get_gc;

	dc->parent.get_visible= rtgui_dc_hw_get_visible;
	dc->parent.get_rect	  = rtgui_dc_hw_get_rect;

	dc->parent.fini		  = rtgui_dc_hw_fini;
}

extern struct rt_mutex cursor_mutex;
#define dc_set_foreground(c) dc->owner->gc.foreground = c
#define dc_set_background(c) dc->owner->gc.background = c
extern void rtgui_mouse_show_cursor(void);
extern void rtgui_mouse_hide_cursor(void);
struct rtgui_dc* rtgui_dc_hw_create(rtgui_widget_t* owner)
{
	struct rtgui_dc_hw* dc;
	rtgui_widget_t* widget;

	/* adjudge owner */
	if (owner == RT_NULL || owner->toplevel == RT_NULL) return RT_NULL;
	if (!RTGUI_IS_TOPLEVEL(owner->toplevel)) return RT_NULL;

	/* malloc a dc object */
	dc = (struct rtgui_dc_hw*) rtgui_malloc(sizeof(struct rtgui_dc_hw));
	rtgui_dc_hw_init(dc);
	dc->owner	= owner;
	dc->visible = RT_TRUE;
	dc->device  = rtgui_graphic_driver_get_default();

	/* set visible */
	widget = owner;
	while (widget != RT_NULL)
	{
		if (RTGUI_WIDGET_IS_HIDE(widget))
		{
			dc->visible = RT_FALSE;
			break;
		}

		widget = widget->parent;
	}

	if (RTGUI_IS_WINTITLE(dc->owner->toplevel))
	{
		rtgui_toplevel_t* top = RTGUI_TOPLEVEL(dc->owner->toplevel);
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
	else if (RTGUI_IS_WORKBENCH(dc->owner->toplevel) ||
		RTGUI_IS_WIN(dc->owner->toplevel))
	{
		rtgui_toplevel_t* top = RTGUI_TOPLEVEL(dc->owner->toplevel);
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

	return &(dc->parent);
}

static rt_bool_t rtgui_dc_hw_fini(struct rtgui_dc* dc)
{
	struct rtgui_dc_hw* hw = (struct rtgui_dc_hw*)dc;
	if (dc == RT_NULL || hw->parent.type != RTGUI_DC_HW) return RT_FALSE;

	if (RTGUI_IS_WINTITLE(hw->owner->toplevel))
	{
		/* update title extent */
		rtgui_toplevel_t* top = RTGUI_TOPLEVEL(hw->owner->toplevel);

		top->drawing --;
		if ((top->drawing == 0) && (hw->visible == RT_TRUE))
		{
#ifdef __WIN32__
#ifdef RTGUI_USING_MOUSE_CURSOR
			rt_mutex_release(&cursor_mutex);
			/* show cursor */
			rtgui_mouse_show_cursor();
			rt_kprintf("show cursor\n");
#endif
			/* update screen */
			hw->device->screen_update(&(hw->owner->extent));
#else
#ifdef RTGUI_USING_MOUSE_CURSOR
			/* show cursor */
			rtgui_mouse_show_cursor();
#endif

			/* update screen */
			hw->device->screen_update(&(hw->owner->extent));
#endif
		}
	}
	else if (RTGUI_IS_WORKBENCH(hw->owner->toplevel) ||
		RTGUI_IS_WIN(hw->owner->toplevel))
	{
		rtgui_toplevel_t* top = RTGUI_TOPLEVEL(hw->owner->toplevel);
		top->drawing --;

		if ((top->drawing == 0) && (hw->visible == RT_TRUE))
		{
#ifdef __WIN32__
#ifdef RTGUI_USING_MOUSE_CURSOR
			rt_mutex_release(&cursor_mutex);
			/* show cursor */
			rtgui_mouse_show_cursor();
			rt_kprintf("show cursor\n");
#endif
			/* update screen */
			hw->device->screen_update(&(hw->owner->extent));
#else
			/* send to server to end drawing */
			struct rtgui_event_update_end eupdate;
			RTGUI_EVENT_UPDATE_END_INIT(&(eupdate));
			eupdate.rect = hw->owner->extent;

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
	struct rtgui_dc_hw* dc;
	rtgui_rect_t rect;

	dc = (struct rtgui_dc_hw*)self;
	if (dc == RT_NULL || dc->visible != RT_TRUE) return;

	x = x + dc->owner->extent.x1;
	y = y + dc->owner->extent.y1;

	if (rtgui_region_contains_point(&(dc->owner->clip), x, y, &rect) == RT_EOK)
	{
		/* draw this point */
		dc->device->set_pixel(&(dc->owner->gc.foreground), x, y);
	}
}

static void rtgui_dc_hw_draw_color_point(struct rtgui_dc* self, int x, int y, rtgui_color_t color)
{
	struct rtgui_dc_hw* dc;
	rtgui_rect_t rect;

	dc = (struct rtgui_dc_hw*)self;
	if (dc == RT_NULL || dc->visible != RT_TRUE) return;

	x = x + dc->owner->extent.x1;
	y = y + dc->owner->extent.y1;

	if (rtgui_region_contains_point(&(dc->owner->clip), x, y, &rect) == RT_EOK)
	{
		/* draw this point */
		dc->device->set_pixel(&color, x, y);
	}
}

/*
 * draw a logic vertical line on device
 */
static void rtgui_dc_hw_draw_vline(struct rtgui_dc* self, int x, int y1, int y2)
{
	register rt_base_t index;
	struct rtgui_dc_hw* dc;

	dc = (struct rtgui_dc_hw*)self;
	if (dc == RT_NULL || dc->visible != RT_TRUE) return;

	x  = x + dc->owner->extent.x1;
	y1 = y1 + dc->owner->extent.y1;
	y2 = y2 + dc->owner->extent.y1;

	if (dc->owner->clip.data == RT_NULL)
	{
		rtgui_rect_t* prect;

		prect = &(dc->owner->clip.extents);

		/* calculate vline intersect */
		if (prect->x1 > x   || prect->x2 <= x) return;
		if (prect->y2 <= y1 || prect->y1 > y2) return;

		if (prect->y1 > y1) y1 = prect->y1;
		if (prect->y2 < y2) y2 = prect->y2;

		/* draw vline */
		dc->device->draw_vline(&(dc->owner->gc.foreground), x, y1, y2);
	}
	else for (index = 0; index < rtgui_region_num_rects(&(dc->owner->clip)); index ++)
	{
		rtgui_rect_t* prect;
		register rt_base_t draw_y1, draw_y2;

		prect = ((rtgui_rect_t *)(dc->owner->clip.data + index + 1));
		draw_y1 = y1;
		draw_y2 = y2;

		/* calculate vline clip */
		if (prect->x1 > x   || prect->x2 <= x) continue;
		if (prect->y2 <= y1 || prect->y1 > y2) continue;

		if (prect->y1 > y1) draw_y1 = prect->y1;
		if (prect->y2 < y2) draw_y2 = prect->y2;

		/* draw vline */
		dc->device->draw_vline(&(dc->owner->gc.foreground), x, draw_y1, draw_y2);
	}
}

/*
 * draw a logic horizontal line on device
 */
static void rtgui_dc_hw_draw_hline(struct rtgui_dc* self, int x1, int x2, int y)
{
	register rt_base_t index;
	struct rtgui_dc_hw* dc;

	dc = (struct rtgui_dc_hw*)self;
	if (dc == RT_NULL || dc->visible != RT_TRUE) return;

	/* convert logic to device */
	x1 = x1 + dc->owner->extent.x1;
	x2 = x2 + dc->owner->extent.x1;
	y  = y + dc->owner->extent.y1;

	if (dc->owner->clip.data == RT_NULL)
	{
		rtgui_rect_t* prect;

		prect = &(dc->owner->clip.extents);

		/* calculate vline intersect */
		if (prect->y1 > y  || prect->y2 <= y ) return;
		if (prect->x2 <= x1 || prect->x1 > x2) return;

		if (prect->x1 > x1) x1 = prect->x1;
		if (prect->x2 < x2) x2 = prect->x2;

		/* draw hline */
		dc->device->draw_hline(&(dc->owner->gc.foreground), x1, x2, y);
	}
	else for (index = 0; index < rtgui_region_num_rects(&(dc->owner->clip)); index ++)
	{
		rtgui_rect_t* prect;
		register rt_base_t draw_x1, draw_x2;

		prect = ((rtgui_rect_t *)(dc->owner->clip.data + index + 1));
		draw_x1 = x1;
		draw_x2 = x2;

		/* calculate hline clip */
		if (prect->y1 > y  || prect->y2 <= y ) continue;
		if (prect->x2 <= x1 || prect->x1 > x2) continue;

		if (prect->x1 > x1) draw_x1 = prect->x1;
		if (prect->x2 < x2) draw_x2 = prect->x2;

		/* draw hline */
		dc->device->draw_hline(&(dc->owner->gc.foreground), draw_x1, draw_x2, y);
	}
}

static void rtgui_dc_hw_fill_rect (struct rtgui_dc* self, struct rtgui_rect* rect)
{
	rtgui_color_t foreground;
	register rt_base_t index;
	struct rtgui_dc_hw* dc;

	dc = (struct rtgui_dc_hw*)self;
	if (dc == RT_NULL || dc->visible != RT_TRUE) return;

	/* save foreground color */
	foreground = dc->owner->gc.foreground;

	/* set background color as foreground color */
	dc->owner->gc.foreground = dc->owner->gc.background;

	/* fill rect */
	for (index = rect->y1; index < rect->y2; index ++)
	{
		rtgui_dc_hw_draw_hline(self, rect->x1, rect->x2, index);
	}

	/* restore foreground color */
	dc->owner->gc.foreground = foreground;
}

static void rtgui_dc_hw_blit(struct rtgui_dc* dc, struct rtgui_point* dc_point, struct rtgui_dc* dest, rtgui_rect_t* rect)
{
	/* not blit in hardware dc */
	return ;
}

static void rtgui_dc_hw_set_gc(struct rtgui_dc* self, rtgui_gc_t *gc)
{
	struct rtgui_dc_hw* dc = (struct rtgui_dc_hw*)self;

	if (self != RT_NULL)
	{
		dc->owner->gc = *gc;
	}
}

static rtgui_gc_t* rtgui_dc_hw_get_gc(struct rtgui_dc* self)
{
	struct rtgui_dc_hw* dc = (struct rtgui_dc_hw*)self;

	return self != RT_NULL? &(dc->owner->gc) : RT_NULL;
}

static rt_bool_t rtgui_dc_hw_get_visible(struct rtgui_dc* self)
{
	struct rtgui_dc_hw* dc = (struct rtgui_dc_hw*)self;

	return dc->visible;
}

static void rtgui_dc_hw_get_rect(struct rtgui_dc* self, rtgui_rect_t* rect)
{
	struct rtgui_dc_hw* dc = (struct rtgui_dc_hw*)self;

	rtgui_widget_get_rect(dc->owner, rect);
}

void rtgui_dc_hw_draw_raw_hline(struct rtgui_dc_hw* dc, rt_uint8_t* raw_ptr, int x1, int x2, int y)
{
	register rt_base_t index;

	if (dc == RT_NULL || dc->visible != RT_TRUE) return;

	/* convert logic to device */
	x1 = x1 + dc->owner->extent.x1;
	x2 = x2 + dc->owner->extent.x1;
	y  = y + dc->owner->extent.y1;

	if (dc->owner->clip.data == RT_NULL)
	{
		rtgui_rect_t* prect;

		prect = &(dc->owner->clip.extents);

		/* calculate hline intersect */
		if (prect->y1 > y  || prect->y2 <= y ) return;
		if (prect->x2 <= x1 || prect->x1 > x2) return;

		if (prect->x1 > x1) x1 = prect->x1;
		if (prect->x2 < x2) x2 = prect->x2;

		/* draw raw hline */
		dc->device->draw_raw_hline(raw_ptr, x1, x2, y);
	}
	else for (index = 0; index < rtgui_region_num_rects(&(dc->owner->clip)); index ++)
	{
		rtgui_rect_t* prect;
		register rt_base_t draw_x1, draw_x2;

		prect = ((rtgui_rect_t *)(dc->owner->clip.data + index + 1));
		draw_x1 = x1;
		draw_x2 = x2;

		/* calculate hline clip */
		if (prect->y1 > y  || prect->y2 <= y ) continue;
		if (prect->x2 <= x1 || prect->x1 > x2) continue;

		if (prect->x1 > x1) draw_x1 = prect->x1;
		if (prect->x2 < x2) draw_x2 = prect->x2;

		/* draw raw hline */
		dc->device->draw_raw_hline(raw_ptr + (draw_x1 - x1) * dc->device->byte_per_pixel, draw_x1, draw_x2, y);
	}
}
