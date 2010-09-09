#include <rtgui/dc.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/progressbar.h>

#define RTGUI_PROGRESSBAR_DEFAULT_RANGE	100

static void _rtgui_progressbar_constructor(rtgui_progressbar_t *bar)
{
	rtgui_rect_t rect = {0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT};

	rtgui_widget_set_event_handler(RTGUI_WIDGET(bar), rtgui_progressbar_event_handler);
	rtgui_widget_set_rect(RTGUI_WIDGET(bar), &rect);

	bar->orient = RTGUI_HORIZONTAL;
	bar->range = RTGUI_PROGRESSBAR_DEFAULT_RANGE;
	bar->position = 0;

	/* set gc */
	RTGUI_WIDGET_TEXTALIGN(RTGUI_WIDGET(bar)) = RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL;
}

rtgui_type_t *rtgui_progressbar_type_get(void)
{
	static rtgui_type_t *progressbar_type = RT_NULL;

	if (!progressbar_type)
	{
		progressbar_type = rtgui_type_create("progressbar", RTGUI_WIDGET_TYPE,
			sizeof(rtgui_progressbar_t), RTGUI_CONSTRUCTOR(_rtgui_progressbar_constructor), RT_NULL);
	}

	return progressbar_type;
}

rt_bool_t rtgui_progressbar_event_handler(struct rtgui_widget* widget,
                                            struct rtgui_event* event)
{
	struct rtgui_progressbar* bar = (struct rtgui_progressbar*)widget;

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_draw != RT_NULL) widget->on_draw(widget, event);
		else
#endif
		{
			rtgui_theme_draw_progressbar(bar);
		}

		break;
	}

	return RT_FALSE;
}

struct rtgui_progressbar* rtgui_progressbar_create(int orientation, int range,
	rtgui_rect_t* r)
{
    struct rtgui_progressbar* bar;

    bar = (struct rtgui_progressbar*) rtgui_widget_create (RTGUI_PROGRESSBAR_TYPE);
    if (bar != RT_NULL)
    {
		if (r != RT_NULL)
			rtgui_widget_set_rect(RTGUI_WIDGET(bar), r);

		bar->orient = orientation;
        bar->range = range;
    }

    return bar;
}

void rtgui_progressbar_destroy(struct rtgui_progressbar* bar)
{
	rtgui_widget_destroy(RTGUI_WIDGET(bar));
}

void rtgui_progressbar_set_value(struct rtgui_progressbar *bar, int value)
{
    RT_ASSERT(bar != RT_NULL);

	if (!RTGUI_WIDGET_IS_ENABLE(RTGUI_WIDGET(bar))) return;

    bar->position = value;

    rtgui_theme_draw_progressbar(bar);
    return;
}

int rtgui_progressbar_get_value(struct rtgui_progressbar *bar)
{
    RT_ASSERT(bar != RT_NULL);

    return bar->position;
}

void rtgui_progressbar_set_range(struct rtgui_progressbar *bar, int range)
{
    RT_ASSERT(bar != RT_NULL);

    bar->range = range;

    rtgui_theme_draw_progressbar(bar);
    return;
}

int rtgui_progressbar_get_range(struct rtgui_progressbar *bar)
{
    RT_ASSERT(bar != RT_NULL);

    return bar->range;
}

