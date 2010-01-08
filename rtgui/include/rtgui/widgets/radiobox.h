#ifndef __RTGUI_RADIOBOX_H__
#define __RTGUI_RADIOBOX_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/widget.h>

/** Gets the type of a radiobox */
#define RTGUI_RADIOBOX_TYPE       (rtgui_radiobox_type_get())
/** Casts the object to an rtgui_radiobox */
#define RTGUI_SLIDER(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_RADIOBOX_TYPE, rtgui_radiobox_t))
/** Checks if the object is an rtgui_radiobox */
#define RTGUI_IS_SLIDER(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_RADIOBOX_TYPE))

struct rtgui_radiobox
{
	struct rtgui_widget parent;

	/* widget private data */
	int orient;

	char* items;
	int item_count, item_selection;
};
typedef struct rtgui_radiobox rtgui_radiobox_t;

rtgui_type_t *rtgui_radiobox_type_get(void);

struct rtgui_radiobox* rtgui_radiobox_create(int orient, char** radio_items, int number);
void rtgui_radiobox_destroy(struct rtgui_radiobox* radiobox);

void rtgui_radiobox_set_selection(struct rtgui_radiobox* radiobox, int selection);
int rtgui_radiobox_get_selection(struct rtgui_radiobox* radiobox);

rt_bool_t rtgui_radiobox_event_handler(struct rtgui_widget* widget, struct rtgui_event* event);

#endif
