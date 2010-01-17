#include "demo_view.h"
#include <rtgui/widgets/button.h>

rtgui_view_t* demo_view_button(rtgui_workbench_t* workbench)
{
	rtgui_rect_t rect;
	rtgui_view_t* view;
	rtgui_button_t* button;
	rtgui_font_t* font;

	/* create a demo view */
	view = demo_view(workbench);

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 = rect.x1 + 100;
	rect.y1 += 5; rect.y2 = rect.y1 + 20;
	button = rtgui_button_create("Red");
	RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(button)) = red;
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(button));

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 = rect.x1 + 100;
	rect.y1 += 5 + 25; rect.y2 = rect.y1 + 20;
	button = rtgui_button_create("Blue");
	RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(button)) = blue;
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(button));

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 = rect.x1 + 100;
	rect.y1 += 5 + 25 + 25; rect.y2 = rect.y1 + 20;
	button = rtgui_button_create("12 font");
	font = rtgui_font_refer("asc", 12);
	RTGUI_WIDGET_FONT(RTGUI_WIDGET(button)) = font;
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(button));

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 = rect.x1 + 100;
	rect.y1 += 5 + 25 + 25 + 25; rect.y2 = rect.y1 + 20;
	button = rtgui_button_create("16 font");
	font = rtgui_font_refer("asc", 16);
	RTGUI_WIDGET_FONT(RTGUI_WIDGET(button)) = font;
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(button));

	return view;
}

