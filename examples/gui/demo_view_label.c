#include "demo_view.h"
#include <rtgui/widgets/label.h>

rtgui_view_t* demo_view_label(rtgui_workbench_t* workbench)
{
	rtgui_rect_t rect;
	rtgui_view_t* view;
	rtgui_label_t* label;
	rtgui_font_t* font;

	/* create a demo view */
	view = demo_view(workbench);

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 -= 5;
	rect.y1 += 5; rect.y2 = rect.y1 + 20;
	label = rtgui_label_create("Red Left");
	RTGUI_WIDGET_TEXTALIGN(RTGUI_WIDGET(label)) = RTGUI_ALIGN_LEFT;
	RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(label)) = red;
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 -= 5;
	rect.y1 += 5 + 25; rect.y2 = rect.y1 + 20;
	label = rtgui_label_create("Blue Right");
	RTGUI_WIDGET_TEXTALIGN(RTGUI_WIDGET(label)) = RTGUI_ALIGN_RIGHT;
	RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(label)) = blue;
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 -= 5;
	rect.y1 += 5 + 25 + 25; rect.y2 = rect.y1 + 20;
	label = rtgui_label_create("Green Center");
	RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(label)) = green;
	RTGUI_WIDGET_TEXTALIGN(RTGUI_WIDGET(label)) = RTGUI_ALIGN_CENTER_HORIZONTAL;
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 -= 5;
	rect.y1 += 5 + 25 + 25 + 25; rect.y2 = rect.y1 + 20;
	label = rtgui_label_create("12 font");
	font = rtgui_font_refer("asc", 12);
	RTGUI_WIDGET_FONT(RTGUI_WIDGET(label)) = font;
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; 
	rect.y1 += 5 + 25 + 25 + 25 + 25; rect.y2 = rect.y1 + 20;
	label = rtgui_label_create("16 font");
	font = rtgui_font_refer("asc", 16);
	RTGUI_WIDGET_FONT(RTGUI_WIDGET(label)) = font;
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));

	return view;
}

