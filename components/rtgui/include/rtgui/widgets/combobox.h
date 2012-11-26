#ifndef __RTGUI_COMBOBOX_H__
#define __RTGUI_COMBOBOX_H__

#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/listbox.h>

DECLARE_CLASS_TYPE(combobox);
/** Gets the type of a combobox */
#define RTGUI_COMBOBOX_TYPE       (RTGUI_TYPE(combobox))
/** Casts the object to a rtgui_combobox */
#define RTGUI_COMBOBOX(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_COMBOBOX_TYPE, rtgui_combobox_t))
/** Checks if the object is a rtgui_combobox */
#define RTGUI_IS_COMBOBOX(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_COMBOBOX_TYPE))

#define RTGUI_COMBOBOX_WIDTH        75
#define RTGUI_COMBOBOX_HEIGHT       20
#define RTGUI_COMBOBOX_BUTTON_WIDTH 18

struct rtgui_combobox
{
    struct rtgui_widget parent;

    /* widget private data */

    /* pull down window */
    struct rtgui_win *pd_win;
    rt_bool_t pd_pressed;

    /* combobox items */
    struct rtgui_listbox_item *items;
    rt_uint16_t items_count;
    rt_uint16_t current_item;

    /* call back */
    rtgui_event_handler_ptr on_selected;
};
typedef struct rtgui_combobox rtgui_combobox_t;

rtgui_combobox_t *rtgui_combobox_create(struct rtgui_listbox_item *items, rt_uint16_t counter, struct rtgui_rect *rect);
void rtgui_combobox_destroy(rtgui_combobox_t *box);

rt_bool_t rtgui_combobox_event_handler(struct rtgui_object *object, struct rtgui_event *event);
struct rtgui_listbox_item *rtgui_combox_get_select(struct rtgui_combobox *box);

void rtgui_combobox_set_onselected(struct rtgui_combobox *box, rtgui_event_handler_ptr func);

#endif
