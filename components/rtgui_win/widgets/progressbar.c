#include <rtgui/dc.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/progressbar.h>

#define RTGUI_PROGRESSBAR_DEFAULT_RANGE	100

static void _rtgui_progressbar_constructor(rtgui_progressbar_t *bar)
{
	rtgui_rect_t rect = {0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT};

	rtgui_widget_set_event_handler(bar, rtgui_progressbar_event_handler);
	rtgui_widget_set_rect(bar, &rect);

	bar->orient = RTGUI_HORIZONTAL;
	bar->range = RTGUI_PROGRESSBAR_DEFAULT_RANGE;
	bar->position = 0;

	/* set gc */
	RTGUI_WIDGET_TEXTALIGN(bar) = RTGUI_ALIGN_CENTER_HORIZONTAL|RTGUI_ALIGN_CENTER_VERTICAL;
}

static void _rtgui_progressbar_destructor(rtgui_progressbar_t *bar)
{

}

rtgui_type_t *rtgui_progressbar_type_get(void)
{
	static rtgui_type_t *progressbar_type = RT_NULL;

	if(!progressbar_type)
	{
		progressbar_type = rtgui_type_create("progressbar", RTGUI_WIDGET_TYPE,
			sizeof(rtgui_progressbar_t), 
			RTGUI_CONSTRUCTOR(_rtgui_progressbar_constructor), 
			RTGUI_DESTRUCTOR(_rtgui_progressbar_destructor));
	}

	return progressbar_type;
}

rt_bool_t rtgui_progressbar_event_handler(PVOID wdt, rtgui_event_t* event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_progressbar_t* bar = (rtgui_progressbar_t*)widget;

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		if(widget->on_draw != RT_NULL) 
			widget->on_draw(widget, event);
		else
		{
			rtgui_theme_draw_progressbar(bar);
		}

		break;
	}

	return RT_FALSE;
}

rtgui_progressbar_t* rtgui_progressbar_create(PVOID parent, int orient, int range, int left, int top, int w, int h)
{
    rtgui_progressbar_t* bar;

	RT_ASSERT(parent != RT_NULL);

    bar = rtgui_widget_create (RTGUI_PROGRESSBAR_TYPE);
    if(bar != RT_NULL)
    {
		rtgui_rect_t rect;
		rtgui_widget_get_rect(bar, &rect);
		rtgui_widget_rect_to_device(parent,&rect);
		rect.x1 += left;
		rect.y1 += top;
		rect.x2 = rect.x1+w;
		rect.y2 = rect.y1+h;
		rtgui_widget_set_rect(bar, &rect);

		bar->orient = orient;
        bar->range = range;

		rtgui_container_add_child(parent, bar);
    }

    return bar;
}

void rtgui_progressbar_destroy(rtgui_progressbar_t* bar)
{
	rtgui_widget_destroy(bar);
}

void rtgui_progressbar_set_value(rtgui_progressbar_t *bar, int value)
{
    RT_ASSERT(bar != RT_NULL);

    bar->position = value;

    rtgui_theme_draw_progressbar(bar);
    return;
}

int rtgui_progressbar_get_value(rtgui_progressbar_t *bar)
{
    RT_ASSERT(bar != RT_NULL);

    return bar->position;
}

void rtgui_progressbar_set_range(rtgui_progressbar_t *bar, int range)
{
    RT_ASSERT(bar != RT_NULL);

    bar->range = range;

    rtgui_theme_draw_progressbar(bar);
    return;
}

int rtgui_progressbar_get_range(rtgui_progressbar_t *bar)
{
    RT_ASSERT(bar != RT_NULL);

    return bar->range;
}

