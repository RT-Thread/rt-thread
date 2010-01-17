#include "demo_view.h"
#include <rtgui/widgets/radiobox.h>

static char* radio_item[5] =
{
    "one",
    "two",
    "three",
    "item 1",
    "item 2"
};

static char* radio_item_h[3] =
{
	"one", "two", "three"
};

rtgui_view_t* demo_view_radiobox(rtgui_workbench_t* workbench)
{
    rtgui_rect_t rect;
    rtgui_view_t* view;
    rtgui_radiobox_t* radiobox;

    view = demo_view(workbench);
    demo_view_get_rect(view, &rect);

    rect.x1 += 5; rect.x2 -= 5;
    rect.y1 += 5; rect.y2 = rect.y1 + 5 * 25;

    radiobox = rtgui_radiobox_create("Radio Box", RTGUI_VERTICAL, radio_item, 5);
	rtgui_radiobox_set_selection(radiobox, 0);

    rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(radiobox));
    rtgui_widget_set_rect(RTGUI_WIDGET(radiobox), &rect);

    demo_view_get_rect(view, &rect);
    rect.x1 += 5; rect.x2 -= 5;
    rect.y1 = 5 + 5 * 25; rect.y2 = rect.y1 + 60;

    radiobox = rtgui_radiobox_create("Radio Box", RTGUI_HORIZONTAL, radio_item_h, 3);
	rtgui_radiobox_set_selection(radiobox, 0);

    rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(radiobox));
    rtgui_widget_set_rect(RTGUI_WIDGET(radiobox), &rect);

    return view;
}

