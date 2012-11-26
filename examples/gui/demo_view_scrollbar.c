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
	rect.x1 += 5;
	rect.x2 -= 5;
	rect.y1 += 5;
	rect.y2 = rect.y1 + 20;
    label = rtgui_label_create("horizontal bar:");
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));

    hbar = rtgui_scrollbar_create(container, 5, 70, 20, 200, RTGUI_HORIZONTAL);
	rtgui_scrollbar_set_line_step(hbar, 1);
	rtgui_scrollbar_set_page_step(hbar, 3);
	rtgui_scrollbar_set_range(hbar, 20);

    /* get demo container rect */
    demo_view_get_rect(container, &rect);
	rect.x1 += 5;
	rect.x2 -= 5;
	rect.y1 += 5+40;
	rect.y2 = rect.y1 + 20;
    label = rtgui_label_create("vertical bar:");
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
    
    vbar = rtgui_scrollbar_create(container, 10, 110, 20, 200, RTGUI_VERTICAL);
	rtgui_scrollbar_set_line_step(vbar, 1);
	rtgui_scrollbar_set_page_step(vbar, 5);
	rtgui_scrollbar_set_range(vbar, 20);

    return container;
}
