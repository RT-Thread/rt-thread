#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>

#include <rtgui/widgets/view.h>
#include <rtgui/widgets/workbench.h>

#define POINT_LENGTH    320
static rt_uint8_t points[POINT_LENGTH];
static rt_uint8_t old_point, fudu = 1;
static rt_uint16_t current_point = 0;

static rtgui_view_t  *osc_view = RT_NULL;
static rtgui_timer_t *osc_timer;

#include <math.h>

void osc_timeout(struct rtgui_timer* timer, void* parameter)
{
    struct rtgui_dc* dc;
    rtgui_color_t saved;
	const double PI=3.141592653589793238462643383279;

    dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(osc_view));
    if (dc == RT_NULL) return ;

    saved = RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(osc_view));
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(osc_view)) =
        RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(osc_view));
	if (current_point != 0)
		rtgui_dc_draw_line(dc, current_point - 1, old_point, current_point, points[current_point]);
	else
		rtgui_dc_draw_point(dc, current_point, points[current_point]);

    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(osc_view)) = saved;

	old_point = points[current_point];
	points[current_point] = 100 * sin((current_point * 4 * fudu) * PI / POINT_LENGTH) + 100;
	if (current_point != 0)
		rtgui_dc_draw_line(dc, current_point - 1, points[current_point - 1], current_point, points[current_point]);
	else
		rtgui_dc_draw_point(dc, current_point, points[current_point]);

	current_point ++; 
	if (current_point == POINT_LENGTH)
	{
		current_point = 0;
		fudu ++;
		if (fudu == 4) fudu = 1;
	}

    rtgui_dc_end_drawing(dc);
}

static rt_bool_t osc_view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
    switch (event->type)
    {
    case RTGUI_EVENT_PAINT:
    {
		struct rtgui_dc* dc;
		struct rtgui_rect rect;
		int index;

		dc = rtgui_dc_begin_drawing(widget);
		if (dc == RT_NULL) return RT_FALSE;
		rtgui_widget_get_rect(widget, &rect);

		rtgui_dc_fill_rect(dc, &rect);
		for (index = 0; index < 320; index ++)
			rtgui_dc_draw_point(dc, index, points[index]);
		rtgui_dc_end_drawing(dc);

		return RT_FALSE;
    }

    case RTGUI_EVENT_KBD:
    {
		struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
		if ((ekbd->type == RTGUI_KEYDOWN) && (ekbd->key == RTGUIK_RETURN))
		{
            rtgui_workbench_t* workbench;

			/* stop timer */
			rtgui_timer_destory(osc_timer);
			/* clean points */
			rt_memset(points, 0xff, sizeof(points));
			current_point = 0;

            /* close this view */
            workbench = RTGUI_WORKBENCH(RTGUI_WIDGET(osc_view)->parent);
            rtgui_workbench_remove_view(workbench, osc_view);
            rtgui_view_destroy(osc_view);

            osc_view = RT_NULL;
			fudu = 0;
			return RT_FALSE;
		}
    }
    }

    return rtgui_view_event_handler(widget, event);
}

rtgui_view_t *osc_view_create(struct rtgui_workbench* workbench)
{
    if (osc_view != RT_NULL)
    {
        rtgui_view_show(osc_view, RT_FALSE);
    }
	else
	{
	    /* create picture view */
	    osc_view = rtgui_view_create("Oscilloscope");
		rtgui_widget_set_event_handler(RTGUI_WIDGET(osc_view),
	        osc_view_event_handler);

		rtgui_workbench_add_view(workbench, osc_view);
		/* this view can be focused */
		RTGUI_WIDGET(osc_view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;

		rt_memset(points, 0xff, sizeof(points));

		osc_timer = rtgui_timer_create(8,
            RT_TIMER_FLAG_PERIODIC,
            osc_timeout, RT_NULL);
        rtgui_timer_start(osc_timer);
	}

	return osc_view;
}
