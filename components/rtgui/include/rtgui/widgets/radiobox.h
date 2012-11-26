#ifndef __RTGUI_RADIOBOX_H__
#define __RTGUI_RADIOBOX_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/widget.h>

DECLARE_CLASS_TYPE(radiobox);
/** Gets the type of a radiobox */
#define RTGUI_RADIOBOX_TYPE       (RTGUI_TYPE(radiobox))
/** Casts the object to an rtgui_radiobox */
#define RTGUI_RADIOBOX(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_RADIOBOX_TYPE, rtgui_radiobox_t))
/** Checks if the object is an rtgui_radiobox */
#define RTGUI_IS_RADIOBOX(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_RADIOBOX_TYPE))

struct rtgui_radiobox
{
    struct rtgui_widget parent;

    /* widget private data */
    char *text; /* radio box label */

    /* box orient */
    rt_uint8_t orient;

    /* item size */
    rt_uint8_t item_size;

    char **items;
    rt_uint16_t item_count;
    rt_int16_t  item_selection;
};
typedef struct rtgui_radiobox rtgui_radiobox_t;

struct rtgui_radiobox *rtgui_radiobox_create(const char *label, int orient, char **radio_items, int number);
void rtgui_radiobox_destroy(struct rtgui_radiobox *radiobox);

void rtgui_radiobox_set_selection(struct rtgui_radiobox *radiobox, int selection);
int rtgui_radiobox_get_selection(struct rtgui_radiobox *radiobox);

rt_bool_t rtgui_radiobox_event_handler(struct rtgui_object *object, struct rtgui_event *event);

void rtgui_radiobox_set_orientation(struct rtgui_radiobox *radiobox, int orientation);

#endif

