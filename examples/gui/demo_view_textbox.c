#include "demo_view.h"
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/textbox.h>

rtgui_view_t* demo_view_textbox(rtgui_workbench_t* workbench)
{
	rtgui_rect_t rect, textbox_rect;
	rtgui_view_t* view;
	rtgui_label_t* label;
	rtgui_textbox_t* text;

	/* create a demo view */
	view = demo_view(workbench, "TextBox View");

	/* add label */
	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 = rect.x1 + 30;
	rect.y1 += 5; rect.y2 = rect.y1 + 20;
	label = rtgui_label_create("Ãû×Ö: ");
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));

	textbox_rect = rect;
	textbox_rect.x1 = textbox_rect.x2 + 5; textbox_rect.x2 = textbox_rect.x1 + 160;
	text = rtgui_textbox_create("bernard");
	rtgui_widget_set_rect(RTGUI_WIDGET(text), &textbox_rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(text));

	rect.y1 += 23; rect.y2 = rect.y1 + 20;
	label = rtgui_label_create("ÓÊ¼þ: ");
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));
	textbox_rect = rect;
	textbox_rect.x1 = textbox_rect.x2 + 5; textbox_rect.x2 = textbox_rect.x1 + 160;
	text = rtgui_textbox_create("bernard.xiong@gmail.com");
	rtgui_widget_set_rect(RTGUI_WIDGET(text), &textbox_rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(text));

	rect.y1 += 23; rect.y2 = rect.y1 + 20;
	label = rtgui_label_create("ÃÜÂë: ");
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));
	textbox_rect = rect;
	textbox_rect.x1 = textbox_rect.x2 + 5; textbox_rect.x2 = textbox_rect.x1 + 160;
	text = rtgui_textbox_create("rt-thread");
	text->flag |= RTGUI_TEXTBOX_MASK;
	rtgui_widget_set_rect(RTGUI_WIDGET(text), &textbox_rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(text));

	rect.y1 += 23; rect.y2 = rect.y1 + 20;
	label = rtgui_label_create("Ö÷Ò³: ");
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));
	textbox_rect = rect;
	textbox_rect.x1 = textbox_rect.x2 + 5; textbox_rect.x2 = textbox_rect.x1 + 160;
	text = rtgui_textbox_create("http://www.rt-thread.org");
	rtgui_widget_set_rect(RTGUI_WIDGET(text), &textbox_rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(text));

	return view;
}
