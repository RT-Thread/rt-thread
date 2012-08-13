#include <rtgui/dc.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/progressbar.h>

#define RTGUI_PROGRESSBAR_DEFAULT_RANGE	100

static void _rtgui_progressbar_constructor(rtgui_progressbar_t *bar)
{
	rtgui_rect_t rect = {0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT};

	rtgui_object_set_event_handler(RTGUI_OBJECT(bar), rtgui_progressbar_event_handler);
	rtgui_widget_set_rect(RTGUI_WIDGET(bar), &rect);

	bar->orient = RTGUI_HORIZONTAL;
	bar->range = RTGUI_PROGRESSBAR_DEFAULT_RANGE;
	bar->position = 0;

	/* set gc */
	RTGUI_WIDGET_TEXTALIGN(bar) = RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL;
}

DEFINE_CLASS_TYPE(progressbar, "progressbar", 
	RTGUI_WIDGET_TYPE,
	_rtgui_progressbar_constructor,
	RT_NULL,
	sizeof(struct rtgui_progressbar));

rt_bool_t rtgui_progressbar_event_handler(struct rtgui_object* object,
                                            struct rtgui_event* event)
{
	struct rtgui_progressbar* bar;
	RTGUI_WIDGET_EVENT_HANDLER_PREPARE

	bar = RTGUI_PROGRESSBAR(object);

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		rtgui_theme_draw_progressbar(bar);
		break;
	default:
		return rtgui_widget_event_handler(object, event);
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

	if (!RTGUI_WIDGET_IS_ENABLE(bar)) return;

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

