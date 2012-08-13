#include "demo_view.h"
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/scrollbar.h>

rtgui_container_t *demo_view_scrollbar(void)
{
    rtgui_container_t *container;
    rtgui_rect_t rect;
    rtgui_label_t *label;
    rtgui_scrollbar_t *hbar;
    rtgui_scrollbar_t *vbar;

    /* create a demo container */
    container = demo_view("ScrollBar View");

    /* get demo container rect */
    demo_view_get_rect(container, &rect);
    label = rtgui_label_create("horizontal bar:");
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
    rect.x1 += 5;
    rect.x2 -= 5;
    rect.y1 += 5;
    rect.y2 = rect.y1 + 18;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rect.y1 += 20;
    rect.y2 = rect.y1 + 18;
    hbar = rtgui_scrollbar_create(RTGUI_HORIZONTAL, &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(hbar));

    /* get demo container rect */
    demo_view_get_rect(container, &rect);
    label = rtgui_label_create("vertical bar:");
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
    rect.x1 += 5;
    rect.x2 -= 5;
    rect.y1 += 45;
    rect.y2 = rect.y1 + 18;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rect.x1 += 110;
    rect.x2 = rect.x1 + 20;
    rect.y1 += 18 + 5;
    rect.y2 = rect.y1 + 150;
    vbar = rtgui_scrollbar_create(RTGUI_VERTICAL, &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(vbar));
    rtgui_scrollbar_set_line_step(vbar, 1);
    // RTGUI_WIDGET_DISABLE(vbar);

    return container;
}
