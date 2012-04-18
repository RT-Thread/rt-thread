#ifndef __RTGUI_STATICLINE__H__
#define __RTGUI_STATICLINE__H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/widget.h>

/*
 * the static line widget
 */

DECLARE_CLASS_TYPE(staticline);
/** Gets the type of a staticline */
#define RTGUI_STATICLINE_TYPE       (RTGUI_TYPE(staticline))
/** Casts the object to an rtgui_staticline */
#define RTGUI_STATICLINE(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_STATICLINE_TYPE, rtgui_staticline_t))
/** Checks if the object is an rtgui_staticline */
#define RTGUI_IS_STATICLINE(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_STATICLINE_TYPE))

struct rtgui_staticline
{
	/* inherit from widget */
	struct rtgui_widget parent;

	int orient;
};
typedef struct rtgui_staticline rtgui_staticline_t;

rtgui_staticline_t *rtgui_staticline_create(int orientation);
void rtgui_staticline_destroy(rtgui_staticline_t* staticline);

rt_bool_t rtgui_staticline_event_handler(struct rtgui_object* object, struct rtgui_event* event);
void rtgui_staticline_set_orientation(rtgui_staticline_t* staticline, int orientation);

#endif

