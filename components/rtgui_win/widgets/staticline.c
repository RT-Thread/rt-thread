#include <rtgui/dc.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/staticline.h>

static void _rtgui_static_constructor(rtgui_staticline_t *sline)
{
	/* init widget and set event handler */
	rtgui_rect_t rect = {0, 0, 100, 2};

	rtgui_widget_set_rect(sline, &rect);
	sline->orient= RTGUI_HORIZONTAL;

	rtgui_widget_set_event_handler(sline, rtgui_staticline_event_handler);
}

static void _rtgui_static_destructor(rtgui_staticline_t *sline)
{

}

rtgui_type_t *rtgui_staticline_type_get(void)
{
	static rtgui_type_t *staticline_type = RT_NULL;

	if(!staticline_type)
	{
		staticline_type = rtgui_type_create("staticline", RTGUI_WIDGET_TYPE,
			sizeof(rtgui_staticline_t), 
			RTGUI_CONSTRUCTOR(_rtgui_static_constructor), 
			RTGUI_DESTRUCTOR(_rtgui_static_destructor));
	}

	return staticline_type;
}

rt_bool_t rtgui_staticline_event_handler(PVOID wdt, rtgui_event_t* event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_staticline_t* sline;
	RT_ASSERT(widget != RT_NULL);

	sline = (rtgui_staticline_t*) widget;
	switch (event->type)
	{
		case RTGUI_EVENT_PAINT:
			if(widget->on_draw != RT_NULL) widget->on_draw(widget, event);
			else
				rtgui_theme_draw_staticline(sline);
			break;
	}

	return RT_FALSE;
}

rtgui_staticline_t * rtgui_staticline_create(PVOID parent,int left,int top,int w,int len,int orient)
{
	rtgui_staticline_t* sline;
	
	RT_ASSERT(parent != RT_NULL);

	sline = rtgui_widget_create(RTGUI_STATICLINE_TYPE);
	if(sline!= RT_NULL)
	{
		rtgui_rect_t rect;

		rtgui_widget_get_rect(parent, &rect);
		rtgui_widget_rect_to_device(parent,&rect);
		rect.x1 += left;
		rect.y1 += top;

		sline->orient = orient;

		if(orient == RTGUI_HORIZONTAL)
		{
			rect.x2 = rect.x1+len;
			rect.y2 = rect.y1+w;
		}
		else
		{
			rect.x2 = rect.x1+w;
			rect.y2 = rect.y1+len;
		}

		rtgui_widget_set_rect(sline,&rect);

		rtgui_container_add_child(parent, sline);
	}

	return sline;
}

void rtgui_staticline_destroy(rtgui_staticline_t* sline)
{
	rtgui_widget_destroy(sline);
}

