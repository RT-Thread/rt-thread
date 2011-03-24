#ifndef __RTGUI_RADIOBOX_H__
#define __RTGUI_RADIOBOX_H__

#include <rtgui/rtgui.h>
#include <rtgui/kbddef.h>
#include <rtgui/widgets/container.h>

/** Gets the type of a rbox */
#define RTGUI_RADIOBOX_TYPE       (rtgui_radiobox_type_get())
/** Casts the object to an rtgui_radiobox_t */
#define RTGUI_RADIOBOX(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_RADIOBOX_TYPE, rtgui_radiobox_t))
/** Checks if the object is an rtgui_radiobox_t */
#define RTGUI_IS_RADIOBOX(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_RADIOBOX_TYPE))

struct rtgui_radiobox
{
	rtgui_container_t parent;

	char* name;

	rt_uint32_t orient;
	rt_uint32_t	item_count;
	rt_bool_t item_sel;

	char **items;
};

typedef struct rtgui_radiobox rtgui_radiobox_t;

rtgui_type_t *rtgui_radiobox_type_get(void);

rtgui_radiobox_t* rtgui_radiobox_create(PVOID parent, const char* name, int orient, char **items, int count,
						int left, int top, int w, int h);
void rtgui_radiobox_destroy(rtgui_radiobox_t* rbox);

void rtgui_radiobox_set_selection(rtgui_radiobox_t* rbox, int selection);
int rtgui_radiobox_get_selection(rtgui_radiobox_t* rbox);

rt_bool_t rtgui_radiobox_event_handler(PVOID wdt, rtgui_event_t* event);

#endif

