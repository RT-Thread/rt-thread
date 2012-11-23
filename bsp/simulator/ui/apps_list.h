#ifndef __APPS_LIST_H__
#define __APPS_LIST_H__

#include <rtgui/event.h>
#include <rtgui/rtgui_object.h>
#include <rtgui/widgets/panel.h>

rt_bool_t apps_list_event_handler(struct rtgui_object* object, struct rtgui_event* event);
struct rtgui_panel* apps_list_create(struct rtgui_panel* panel);

#endif
