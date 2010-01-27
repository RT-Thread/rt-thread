#include "demo_view.h"
#include "mywidget.h"

rtgui_view_t *demo_view_mywidget(rtgui_workbench_t* workbench)
{
	rtgui_view_t *view;
	rtgui_rect_t rect;
	rtgui_mywidget_t *mywidget;

	/* create a demo view */
	view = demo_view(workbench, "MyWidget View");

	/* get demo view rect */
	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 = rect.y1 + 80;
	rect.y1 += 5; rect.y2 = rect.y1 + 80;
	mywidget = rtgui_mywidget_create(&rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(mywidget));

	/* get demo view rect */
	demo_view_get_rect(view, &rect);
	rect.x1 += 25; rect.x2 = rect.y1 + 40;
	rect.y1 += 5 + 100; rect.y2 = rect.y1 + 40;
	mywidget = rtgui_mywidget_create(&rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(mywidget));

	return view;
}
