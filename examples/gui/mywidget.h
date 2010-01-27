#ifndef __MY_WIDGET_H__
#define __MY_WIDGET_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/widget.h>

#define MYWIDGET_STATUS_ON	1
#define MYWIDGET_STATUS_OFF	0

/** Gets the type of a button */
#define RTGUI_MYWIDGET_TYPE       (rtgui_mywidget_type_get())
/** Casts the object to an rtgui_button */
#define RTGUI_MYWIDGET(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_MYWIDGET_TYPE, rtgui_mywidget_t))
/** Checks if the object is an rtgui_button */
#define RTGUI_IS_MYWIDGET(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_MYWIDGET_TYPE))

/* 个性化控件 */
struct rtgui_mywidget
{
	struct rtgui_widget parent;

	/* 状态：ON、OFF */
	rt_uint8_t status;
};
typedef struct rtgui_mywidget rtgui_mywidget_t;

struct rtgui_mywidget* rtgui_mywidget_create(rtgui_rect_t* r);
void rtgui_mywidget_destroy(struct rtgui_mywidget* me);

#endif
