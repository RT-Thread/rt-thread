#include "demo_view.h"
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/slider.h>

rtgui_container_t *demo_view_slider(void)
{
    rtgui_container_t *container;
    rtgui_rect_t rect;
    rtgui_label_t *label;
    rtgui_slider_t *slider;

    /* create a demo container */
    container = demo_view("Slider View");

    /* get demo container rect */
    demo_view_get_rect(container, &rect);
    label = rtgui_label_create("horizontal slider:");
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
    rect.x1 += 5;
    rect.x2 -= 5;
    rect.y1 += 5;
    rect.y2 = rect.y1 + 18;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rect.y1 += 20;
    rect.y2 = rect.y1 + 18;
    slider = rtgui_slider_create(0, 100, RTGUI_HORIZONTAL);
    rtgui_container_add_child(container, RTGUI_WIDGET(slider));
    rtgui_widget_set_rect(RTGUI_WIDGET(slider), &rect);

    /* get demo container rect */
    demo_view_get_rect(container, &rect);
    label = rtgui_label_create("vertical slider:");
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
    rect.x1 += 5;
    rect.x2 -= 5;
    rect.y1 += 50;
    rect.y2 = rect.y1 + 18;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rect.x1 += 110;
    rect.x2 = rect.x1 + 20;
    rect.y1 += 18 + 5;
    rect.y2 = rect.y1 + 150;
    slider = rtgui_slider_create(0, 100, RTGUI_VERTICAL);
    rtgui_container_add_child(container, RTGUI_WIDGET(slider));
    rtgui_widget_set_rect(RTGUI_WIDGET(slider), &rect);

    return container;
}
