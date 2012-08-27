#include <rtgui/dc.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/staticline.h>

static void _rtgui_staticline_constructor(rtgui_staticline_t *staticline)
{
	/* init widget and set event handler */
	rtgui_rect_t rect = {0, 0, 100, 2};

	rtgui_widget_set_rect(RTGUI_WIDGET(staticline), &rect);
	staticline->orient= RTGUI_HORIZONTAL;

	rtgui_object_set_event_handler(RTGUI_OBJECT(staticline), rtgui_staticline_event_handler);
}


DEFINE_CLASS_TYPE(staticline, "staticline", 
	RTGUI_WIDGET_TYPE,
	_rtgui_staticline_constructor,
	RT_NULL,
	sizeof(struct rtgui_staticline));

rt_bool_t rtgui_staticline_event_handler(struct rtgui_object* object, struct rtgui_event* event)
{
	struct rtgui_staticline* staticline;
	RTGUI_WIDGET_EVENT_HANDLER_PREPARE

	staticline = RTGUI_STATICLINE(object);
	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_draw != RT_NULL)
			widget->on_draw(RTGUI_OBJECT(widget), event);
		else
#endif
			rtgui_theme_draw_staticline(staticline);
		break;
	default:
		return rtgui_widget_event_handler(object, event);
	}

	return RT_FALSE;
}
RTM_EXPORT(rtgui_staticline_event_handler);

rtgui_staticline_t * rtgui_staticline_create(int orientation)
{
	rtgui_staticline_t* staticline;

	staticline = (struct rtgui_staticline*) rtgui_widget_create(RTGUI_STATICLINE_TYPE);
	if (staticline!= RT_NULL)
	{
		rtgui_staticline_set_orientation(staticline, orientation);
	}

	return staticline;
}
RTM_EXPORT(rtgui_staticline_create);

void rtgui_staticline_destroy(rtgui_staticline_t* staticline)
{
	rtgui_widget_destroy(RTGUI_WIDGET(staticline));
}
RTM_EXPORT(rtgui_staticline_destroy);

void rtgui_staticline_set_orientation(rtgui_staticline_t* staticline, int orientation)
{
	RT_ASSERT(staticline != RT_NULL);

	staticline->orient = orientation;
#ifndef RTGUI_USING_SMALL_SIZE
	if (orientation == RTGUI_HORIZONTAL)
	{
		/* HORIZONTAL */
		rtgui_widget_set_miniheight(RTGUI_WIDGET(staticline), 2);
		rtgui_widget_set_miniwidth(RTGUI_WIDGET(staticline), 100);
	}
	else
	{
		/* VERTICAL */
		rtgui_widget_set_miniwidth(RTGUI_WIDGET(staticline), 2);
		rtgui_widget_set_miniheight(RTGUI_WIDGET(staticline), 100);
	}
#endif
}
RTM_EXPORT(rtgui_staticline_set_orientation);

