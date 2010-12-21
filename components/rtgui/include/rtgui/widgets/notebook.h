#ifndef __RTGUI_NOTEBOOK_H__
#define __RTGUI_NOTEBOOK_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/container.h>

/** Gets the type of a notebook */
#define RTGUI_NOTEBOOK_TYPE       (rtgui_notebook_type_get())
/** Casts the object to a notebook control */
#define RTGUI_NOTEBOOK(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_NOTEBOOK_TYPE, rtgui_notebook_t))
/** Checks if the object is a notebook control */
#define RTGUI_IS_NOTEBOOK(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_NOTEBOOK_TYPE))

struct rtgui_notebook
{
	struct rtgui_container parent;

	/* widget private data */
	struct rtgui_widget* childs;
	rt_uint16_t count;
	rt_int16_t current;
};
typedef struct rtgui_notebook rtgui_notebook_t;

rtgui_type_t *rtgui_notebook_type_get(void);

rtgui_notebook_t* rtgui_notebook_create(const rtgui_rect_t* rect);
void rtgui_notebook_destroy(rtgui_notebook_t* notebook);

void rtgui_notebook_add(rtgui_notebook_t* notebook, const char* label, rtgui_widget_t* child);
int rtgui_notebook_get_count(rtgui_notebootk_t* notebook);
rtgui_widget_t* rtgui_notebook_get_current(rtgui_notebook_t* notebook);
void rtgui_notebook_set_current(rtgui_notebook_t* notebook, rtgui_widget_t* widget);
void rtgui_notebook_set_current_by_index(rtgui_notebook_t* notebook, rt_uint16_t index);
rtgui_widget_t* rtgui_notebook_get_index(rtgui_notebook_t* notebook, rt_uint16_t index);

rt_bool_t rtgui_notebook_event_handler(struct rtgui_widget* widget, struct rtgui_event* event);

#endif
