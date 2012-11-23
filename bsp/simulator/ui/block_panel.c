#include <rtgui/dc.h>
#include "block_panel.h"

static void dc_render_block(struct rtgui_dc* dc, struct rtgui_rect *rect, int angle_y)
{
#define BLOCK_BORDER_SZ	5
#define BLOCK_ANGLE_SZ	10
	int rect_y[12];
	int rect_x[12];
	int ri = 0;
	rtgui_color_t line_color = RTGUI_RGB(215, 215, 215);
	// rtgui_color_t external_color = RTGUI_RGB(241, 241, 241);
	// rtgui_color_t angle_color = RTGUI_RGB(229, 229, 229);
	rtgui_color_t fg, bg;
	struct rtgui_gc *gc;

	rect_x[ri] = rect->x1 + BLOCK_ANGLE_SZ + 3; rect_y[ri] = rect->y1 + BLOCK_BORDER_SZ; ri ++;
	rect_x[ri] = rect->x2 - BLOCK_BORDER_SZ - 3; rect_y[ri] = rect->y1 + BLOCK_BORDER_SZ; ri ++;
	rect_x[ri] = rect->x2 - BLOCK_BORDER_SZ; rect_y[ri] = rect->y1 + BLOCK_BORDER_SZ + 3; ri ++;
	rect_x[ri] = rect->x2 - BLOCK_BORDER_SZ; rect_y[ri] = rect->y2 - BLOCK_BORDER_SZ - 3; ri ++;
	rect_x[ri] = rect->x2 - BLOCK_BORDER_SZ - 3; rect_y[ri] = rect->y2 - BLOCK_BORDER_SZ; ri ++;
	rect_x[ri] = rect->x1 + BLOCK_ANGLE_SZ + 3; rect_y[ri] = rect->y2 - BLOCK_BORDER_SZ; ri ++;
	rect_x[ri] = rect->x1 + BLOCK_ANGLE_SZ ; rect_y[ri] = rect->y2 - BLOCK_BORDER_SZ - 3; ri ++;

	/* angle */
	rect_x[ri] = rect->x1 + BLOCK_ANGLE_SZ ; rect_y[ri] = angle_y + BLOCK_ANGLE_SZ; ri ++;
	rect_x[ri] = rect->x1; rect_y[ri] = angle_y; ri ++;
	rect_x[ri] = rect->x1 + BLOCK_ANGLE_SZ ; rect_y[ri] = angle_y - BLOCK_ANGLE_SZ; ri ++;

	rect_x[ri] = rect->x1 + BLOCK_ANGLE_SZ ; rect_y[ri] = rect->y1 + BLOCK_BORDER_SZ + 3; ri ++;
	rect_x[ri] = rect->x1 + BLOCK_ANGLE_SZ + 3; rect_y[ri] = rect->y1 + BLOCK_BORDER_SZ; ri ++;

	gc = rtgui_dc_get_gc(dc);
	fg = gc->foreground;
	bg = gc->background;
	gc->foreground = white;
	rtgui_dc_fill_polygon(dc, rect_x, rect_y, 12);
	gc->foreground = line_color;
	rtgui_dc_draw_polygon(dc, rect_x, rect_y, 12);
	gc->foreground = fg;
	gc->background = bg;
}

static void _block_panel_constructor(block_panel_t *panel)
{
	/* init widget and set event handler */
	rtgui_object_set_event_handler(RTGUI_OBJECT(panel), block_panel_event_handler);

	/* set field */
	panel->angle_y = 10;
}

DEFINE_CLASS_TYPE(block_panel, "block_panel", 
				  RTGUI_PANEL_TYPE,
				  _block_panel_constructor,
				  RT_NULL,
				  sizeof(struct block_panel));

struct block_panel *block_panel_create(int angle_y, struct rtgui_rect *rect)
{
	struct block_panel* panel;

	panel = (struct block_panel*) rtgui_widget_create(BLOCK_PANEL_TYPE);
	if (panel != RT_NULL)
	{
		panel->angle_y = angle_y;

		rtgui_widget_set_rect(RTGUI_WIDGET(panel), rect);
		rtgui_object_set_event_handler(RTGUI_OBJECT(panel), block_panel_event_handler);
	}

	return panel;
}

void block_panel_destroy(block_panel_t* panel)
{
	rtgui_object_destroy(RTGUI_OBJECT(panel));
}

rt_bool_t block_panel_event_handler(struct rtgui_object* object, struct rtgui_event* event)
{
	struct block_panel *panel;

	panel = BLOCK_PANEL(object);
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		struct rtgui_rect rect;

		rtgui_widget_get_rect(RTGUI_WIDGET(object), &rect);
		dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(object));

		rtgui_dc_fill_rect(dc, &rect);
		rtgui_rect_inflate(&rect, - 3);
		dc_render_block(dc, &rect, panel->angle_y);

		/* paint on each child */
		rtgui_container_dispatch_event(RTGUI_CONTAINER(panel), event);
		rtgui_dc_end_drawing(dc);
	}
	else
	{
		return rtgui_panel_event_handler(object, event);
	}

	return RT_FALSE;
}

void block_panel_get_client_extent(struct block_panel *panel, struct rtgui_rect *rect)
{
	RT_ASSERT(panel != RT_NULL);
	RT_ASSERT(rect  != RT_NULL);

	rtgui_widget_get_extent(RTGUI_WIDGET(panel), rect);
	rect->x1 += 20; rect->y1 += 10;
	rect->x2 -= 10;  rect->y2 -= 10;
}

