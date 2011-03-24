#ifndef __RTGUI_SLIDER_H__
#define __RTGUI_SLIDER_H__

#include <rtgui/rtgui.h>
#include <rtgui/kbddef.h>

typedef struct rtgui_slider rtgui_slider_t;

/** Gets the type of a slider */
#define RTGUI_SLIDER_TYPE       (rtgui_slider_type_get())
/** Casts the object to an rtgui_slider */
#define RTGUI_SLIDER(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_SLIDER_TYPE, rtgui_slider_t))
/** Checks if the object is an rtgui_slider */
#define RTGUI_IS_SLIDER(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_SLIDER_TYPE))

struct rtgui_slider
{
	rtgui_widget_t parent;

	/* widget private data */
	rt_size_t min, max, value, ticks;
	rt_size_t thumb_width;

	int orient;
};

rtgui_type_t *rtgui_slider_type_get(void);

rtgui_slider_t* rtgui_slider_create(PVOID parent, rt_size_t min, rt_size_t max, int left, int top, int w, int h, int orient);
void rtgui_slider_destroy(rtgui_slider_t* slider);

rt_bool_t rtgui_slider_event_handler(PVOID wdt, rtgui_event_t* event);

void rtgui_slider_set_range(rtgui_slider_t* slider, rt_size_t min, rt_size_t max);
void rtgui_slider_set_value(rtgui_slider_t* slider, rt_size_t value);
void rtgui_slider_set_orientation(rtgui_slider_t* slider, int orient);

rt_size_t rtgui_slider_get_value(rtgui_slider_t* slider);

#endif
