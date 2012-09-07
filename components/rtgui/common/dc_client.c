/*
 * File      : dc_client.c
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
 * 2010-08-09     Bernard      rename hardware dc to client dc
 * 2010-09-13     Bernard      fix rtgui_dc_client_blit_line issue, which found 
 *                             by appele 
 * 2010-09-14     Bernard      fix vline and hline coordinate issue
 */
#include <rtgui/dc.h>
#include <rtgui/dc_hw.h>
#include <rtgui/dc_client.h>

#include <rtgui/driver.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/widgets/container.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/title.h>

static void rtgui_dc_client_draw_point(struct rtgui_dc* dc, int x, int y);
static void rtgui_dc_client_draw_color_point(struct rtgui_dc* dc, int x, int y, rtgui_color_t color);
static void rtgui_dc_client_draw_hline(struct rtgui_dc* dc, int x1, int x2, int y);
static void rtgui_dc_client_draw_vline(struct rtgui_dc* dc, int x, int y1, int y2);
static void rtgui_dc_client_fill_rect (struct rtgui_dc* dc, rtgui_rect_t* rect);
static void rtgui_dc_client_blit_line (struct rtgui_dc* self, int x1, int x2, int y, rt_uint8_t* line_data);
static void rtgui_dc_client_blit	  (struct rtgui_dc* dc, struct rtgui_point* dc_point, struct rtgui_dc* dest, rtgui_rect_t* rect);
static void rtgui_dc_client_set_gc (struct rtgui_dc* dc, rtgui_gc_t *gc);
static rtgui_gc_t *rtgui_dc_client_get_gc (struct rtgui_dc* dc);
static rt_bool_t rtgui_dc_client_fini(struct rtgui_dc* dc);
static rt_bool_t rtgui_dc_client_get_visible(struct rtgui_dc* dc);
static void rtgui_dc_client_get_rect(struct rtgui_dc* dc, rtgui_rect_t* rect);

#define hw_driver				(rtgui_graphic_driver_get_default())
#define dc_set_foreground(c) 	dc->gc.foreground = c
#define dc_set_background(c) 	dc->gc.background = c
#define _int_swap(x, y)			do {x ^= y; y ^= x; x ^= y;} while (0)

struct rtgui_dc* rtgui_dc_begin_drawing(rtgui_widget_t* owner)
{
	struct rtgui_dc* dc;
	RT_ASSERT(owner != RT_NULL);

	rtgui_screen_lock(RT_WAITING_FOREVER);

	if ((rtgui_region_is_flat(&owner->clip) == RT_EOK) &&
		rtgui_rect_is_equal(&(owner->extent), &(owner->clip.extents)) == RT_EOK)
		dc = rtgui_dc_hw_create(owner);
	else
		dc = rtgui_dc_client_create(owner);

	if (dc == RT_NULL) rtgui_screen_unlock();

	return dc;
}
RTM_EXPORT(rtgui_dc_begin_drawing);

void rtgui_dc_end_drawing(struct rtgui_dc* dc)
{
	dc->engine->fini(dc);
	rtgui_screen_unlock();
}
RTM_EXPORT(rtgui_dc_end_drawing);

const struct rtgui_dc_engine dc_client_engine =
{
	rtgui_dc_client_draw_point,
	rtgui_dc_client_draw_color_point,
	rtgui_dc_client_draw_vline,
	rtgui_dc_client_draw_hline,
	rtgui_dc_client_fill_rect,
	rtgui_dc_client_blit_line,
	rtgui_dc_client_blit,

	rtgui_dc_client_set_gc,
	rtgui_dc_client_get_gc,

	rtgui_dc_client_get_visible,
	rtgui_dc_client_get_rect,

	rtgui_dc_client_fini,
};

void rtgui_dc_client_init(rtgui_widget_t* owner)
{
	struct rtgui_dc* dc;

	RT_ASSERT(owner != RT_NULL);

	dc = RTGUI_WIDGET_DC(owner);
	dc->type = RTGUI_DC_CLIENT;
	dc->engine = &dc_client_engine;
}

extern struct rt_mutex cursor_mutex;
extern void rtgui_mouse_show_cursor(void);
extern void rtgui_mouse_hide_cursor(void);
struct rtgui_dc* rtgui_dc_client_create(rtgui_widget_t* owner)
{
	struct rtgui_dc* dc;
	rtgui_widget_t* widget;

	/* adjudge owner */
	if (owner == RT_NULL || owner->toplevel == RT_NULL) return RT_NULL;
	if (!RTGUI_IS_WIN(owner->toplevel)) return RT_NULL;

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
			return RT_NULL;
		}

		widget = widget->parent;
	}

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
	else if (RTGUI_IS_APP(owner->toplevel))
	{
		RT_ASSERT(0);
	}
	else if (RTGUI_IS_WIN(owner->toplevel))
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

	return dc;
}

static rt_bool_t rtgui_dc_client_fini(struct rtgui_dc* dc)
{
	rtgui_widget_t* owner;
	
	if (dc == RT_NULL || dc->type != RTGUI_DC_CLIENT) return RT_FALSE;

	/* get owner */
	owner = RTGUI_CONTAINER_OF(dc, struct rtgui_widget, dc_type);

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
			rtgui_graphic_driver_screen_update(hw_driver, &(owner->extent));
#else
#ifdef RTGUI_USING_MOUSE_CURSOR
			/* show cursor */
			rtgui_mouse_show_cursor();
#endif

			/* update screen */
			rtgui_graphic_driver_screen_update(hw_driver, &(owner->extent));
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
			rtgui_graphic_driver_screen_update(hw_driver, &(owner->extent));
#else
			/* send to server to end drawing */
			struct rtgui_event_update_end eupdate;
			RTGUI_EVENT_UPDATE_END_INIT(&(eupdate));
			eupdate.rect = owner->extent;

			rtgui_server_post_event((struct rtgui_event*)&eupdate, sizeof(eupdate));
#endif
		}
	}

	return RT_TRUE;
}

/*
 * draw a logic point on device
 */
static void rtgui_dc_client_draw_point(struct rtgui_dc* self, int x, int y)
{
	rtgui_rect_t rect;
	rtgui_widget_t *owner;

	if (self == RT_NULL) return;
	
	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);
	if (!RTGUI_WIDGET_IS_DC_VISIBLE(owner)) return;

	x = x + owner->extent.x1;
	y = y + owner->extent.y1;

	if (rtgui_region_contains_point(&(owner->clip), x, y, &rect) == RT_EOK)
	{
		/* draw this point */
		hw_driver->ops->set_pixel(&(owner->gc.foreground), x, y);
	}
}

static void rtgui_dc_client_draw_color_point(struct rtgui_dc* self, int x, int y, rtgui_color_t color)
{
	rtgui_rect_t rect;
	rtgui_widget_t *owner;

	if (self == RT_NULL) return;
	
	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);
	if (!RTGUI_WIDGET_IS_DC_VISIBLE(owner)) return;

	x = x + owner->extent.x1;
	y = y + owner->extent.y1;

	if (rtgui_region_contains_point(&(owner->clip), x, y, &rect) == RT_EOK)
	{
		/* draw this point */
		hw_driver->ops->set_pixel(&color, x, y);
	}
}

/*
 * draw a logic vertical line on device
 */
static void rtgui_dc_client_draw_vline(struct rtgui_dc* self, int x, int y1, int y2)
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
	if (y1 > y2) _int_swap(y1, y2);

	if (owner->clip.data == RT_NULL)
	{
		rtgui_rect_t* prect;

		prect = &(owner->clip.extents);

		/* calculate vline intersect */
		if (prect->x1 > x   || prect->x2 <= x) return;
		if (prect->y2 <= y1 || prect->y1 > y2) return;

		if (prect->y1 > y1) y1 = prect->y1;
		if (prect->y2 < y2) y2 = prect->y2;

		/* draw vline */
		hw_driver->ops->draw_vline(&(owner->gc.foreground), x, y1, y2);
	}
	else for (index = 0; index < rtgui_region_num_rects(&(owner->clip)); index ++)
	{
		rtgui_rect_t* prect;
		register rt_base_t draw_y1, draw_y2;

		prect = ((rtgui_rect_t *)(owner->clip.data + index + 1));
		draw_y1 = y1;
		draw_y2 = y2;

		/* calculate vline clip */
		if (prect->x1 > x   || prect->x2 <= x) continue;
		if (prect->y2 <= y1 || prect->y1 > y2) continue;

		if (prect->y1 > y1) draw_y1 = prect->y1;
		if (prect->y2 < y2) draw_y2 = prect->y2;

		/* draw vline */
		hw_driver->ops->draw_vline(&(owner->gc.foreground), x, draw_y1, draw_y2);
	}
}

/*
 * draw a logic horizontal line on device
 */
static void rtgui_dc_client_draw_hline(struct rtgui_dc* self, int x1, int x2, int y)
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
	if (x1 > x2) _int_swap(x1, x2);
	y  = y + owner->extent.y1;

	if (owner->clip.data == RT_NULL)
	{
		rtgui_rect_t* prect;

		prect = &(owner->clip.extents);

		/* calculate vline intersect */
		if (prect->y1 > y  || prect->y2 <= y ) return;
		if (prect->x2 <= x1 || prect->x1 > x2) return;

		if (prect->x1 > x1) x1 = prect->x1;
		if (prect->x2 < x2) x2 = prect->x2;

		/* draw hline */
		hw_driver->ops->draw_hline(&(owner->gc.foreground), x1, x2, y);
	}
	else for (index = 0; index < rtgui_region_num_rects(&(owner->clip)); index ++)
	{
		rtgui_rect_t* prect;
		register rt_base_t draw_x1, draw_x2;

		prect = ((rtgui_rect_t *)(owner->clip.data + index + 1));
		draw_x1 = x1;
		draw_x2 = x2;

		/* calculate hline clip */
		if (prect->y1 > y  || prect->y2 <= y ) continue;
		if (prect->x2 <= x1 || prect->x1 > x2) continue;

		if (prect->x1 > x1) draw_x1 = prect->x1;
		if (prect->x2 < x2) draw_x2 = prect->x2;

		/* draw hline */
		hw_driver->ops->draw_hline(&(owner->gc.foreground), draw_x1, draw_x2, y);
	}
}

static void rtgui_dc_client_fill_rect (struct rtgui_dc* self, struct rtgui_rect* rect)
{
	rtgui_color_t foreground;
	register rt_base_t index;
	rtgui_widget_t *owner;

	if (self == RT_NULL) return;
	
	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);
	if (!RTGUI_WIDGET_IS_DC_VISIBLE(owner)) return;

	/* save foreground color */
	foreground = owner->gc.foreground;

	/* set background color as foreground color */
	owner->gc.foreground = owner->gc.background;

	/* fill rect */
	for (index = rect->y1; index < rect->y2; index ++)
	{
		rtgui_dc_client_draw_hline(self, rect->x1, rect->x2, index);
	}

	/* restore foreground color */
	owner->gc.foreground = foreground;
}

static void rtgui_dc_client_blit_line (struct rtgui_dc* self, int x1, int x2, int y, rt_uint8_t* line_data)
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
	if (x1 > x2) _int_swap(x1, x2);
	y  = y + owner->extent.y1;

	if (rtgui_region_is_flat(&(owner->clip)) == RT_EOK)
	{
		rtgui_rect_t* prect;
		int offset = 0;
		prect = &(owner->clip.extents);

		/* calculate vline intersect */
		if (prect->y1 > y  || prect->y2 <= y ) return;
		if (prect->x2 <= x1 || prect->x1 > x2) return;

		if (prect->x1 > x1) x1 = prect->x1;
		if (prect->x2 < x2) x2 = prect->x2;

		/* patch note: 
		 * We need to adjust the offset when update widget clip!
		 * Of course at ordinary times for 0. General */
		offset = owner->clip.extents.x1 - owner->extent.x1;
		offset = offset * hw_driver->bits_per_pixel/8;
		/* draw hline */
		hw_driver->ops->draw_raw_hline(line_data+offset, x1, x2, y);
	}
	else for (index = 0; index < rtgui_region_num_rects(&(owner->clip)); index ++)
	{
		rtgui_rect_t* prect;
		register rt_base_t draw_x1, draw_x2;

		prect = ((rtgui_rect_t *)(owner->clip.data + index + 1));
		draw_x1 = x1;
		draw_x2 = x2;

		/* calculate hline clip */
		if (prect->y1 > y  || prect->y2 <= y ) continue;
		if (prect->x2 <= x1 || prect->x1 > x2) continue;

		if (prect->x1 > x1) draw_x1 = prect->x1;
		if (prect->x2 < x2) draw_x2 = prect->x2;

		/* draw hline */
		hw_driver->ops->draw_raw_hline(line_data + (draw_x1 - x1) * hw_driver->bits_per_pixel/8, draw_x1, draw_x2, y);
	}
}

static void rtgui_dc_client_blit(struct rtgui_dc* dc, struct rtgui_point* dc_point, struct rtgui_dc* dest, rtgui_rect_t* rect)
{
	/* not blit in hardware dc */
	return ;
}

static void rtgui_dc_client_set_gc(struct rtgui_dc* self, rtgui_gc_t *gc)
{
	rtgui_widget_t *owner;

	if (self == RT_NULL) return;
	
	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);
	owner->gc = *gc;
}

static rtgui_gc_t* rtgui_dc_client_get_gc(struct rtgui_dc* self)
{
	rtgui_widget_t *owner;

	RT_ASSERT(self != RT_NULL);
	
	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);
	
	return &(owner->gc);
}

static rt_bool_t rtgui_dc_client_get_visible(struct rtgui_dc* self)
{
	rtgui_widget_t *owner;

	if (self == RT_NULL) return RT_FALSE;
	
	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);
	if (!RTGUI_WIDGET_IS_DC_VISIBLE(owner)) return RT_FALSE;

	return RT_TRUE;
}

static void rtgui_dc_client_get_rect(struct rtgui_dc* self, rtgui_rect_t* rect)
{
	rtgui_widget_t *owner;

	if (self == RT_NULL) return;
	
	/* get owner */
	owner = RTGUI_CONTAINER_OF(self, struct rtgui_widget, dc_type);
	rtgui_widget_get_rect(owner, rect);
}

