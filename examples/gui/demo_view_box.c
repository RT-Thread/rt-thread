#include "demo_view.h"
#include <rtgui/widgets/box.h>
#include <rtgui/widgets/panel.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>

rtgui_container_t *demo_view_box(void)
{
    rtgui_rect_t  rect;
    rtgui_container_t *view;
    struct rtgui_panel *panel;
    struct rtgui_box *box;

    struct rtgui_label *label;
    struct rtgui_button *button;

    view = demo_view("Box View");
    demo_view_get_rect(view, &rect);

    panel = rtgui_panel_create(RTGUI_BORDER_NONE);
    rtgui_widget_set_rect(RTGUI_WIDGET(panel), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(panel));

    box = rtgui_box_create(RTGUI_VERTICAL, 5);
    rtgui_container_set_box(RTGUI_CONTAINER(panel), box);

    label = rtgui_label_create("label 1");
    rtgui_container_add_child(RTGUI_CONTAINER(panel), RTGUI_WIDGET(label));
    label = rtgui_label_create("label 2");
    rtgui_container_add_child(RTGUI_CONTAINER(panel), RTGUI_WIDGET(label));

    button = rtgui_button_create("button 1");
    rtgui_container_add_child(RTGUI_CONTAINER(panel), RTGUI_WIDGET(button));

    button = rtgui_button_create("button 2");
    rtgui_container_add_child(RTGUI_CONTAINER(panel), RTGUI_WIDGET(button));
    rtgui_widget_set_minheight(RTGUI_WIDGET(button), 25);
    RTGUI_WIDGET_ALIGN(button) = RTGUI_ALIGN_EXPAND;

    rtgui_container_layout(RTGUI_CONTAINER(panel));

    return view;
}

