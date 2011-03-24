#ifndef __RTGUI_STATICLINE__H__
#define __RTGUI_STATICLINE__H__

#include <rtgui/rtgui.h>

/*
 * the static line widget
 */

/** Gets the type of a sline */
#define RTGUI_STATICLINE_TYPE       (rtgui_staticline_type_get())
/** Casts the object to an rtgui_staticline_t */
#define RTGUI_STATICLINE(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_STATICLINE_TYPE, rtgui_staticline_t))
/** Checks if the object is an rtgui_staticline_t */
#define RTGUI_IS_STATICLINE(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_STATICLINE_TYPE))

struct rtgui_staticline
{
	/* inherit from widget */
	rtgui_widget_t parent;

	int orient;
};
typedef struct rtgui_staticline rtgui_staticline_t;

rtgui_staticline_t *rtgui_staticline_create(PVOID wdt,int left,int top,int w,int len,int orient);
void rtgui_staticline_destroy(rtgui_staticline_t* sline);

rt_bool_t rtgui_staticline_event_handler(PVOID wdt, rtgui_event_t* event);

#endif

