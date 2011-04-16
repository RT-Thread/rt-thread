#include "demo_view.h"
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/scrollbar.h>

rtgui_view_t *demo_gui_scrollbar(rtgui_view_t* parent_view)
{
	rtgui_view_t *view;
	rtgui_scrollbar_t* hbar;
	rtgui_scrollbar_t* vbar;

	/* create a demo view */
	view = demo_view_create(parent_view, "ScrollBar View");
	
	rtgui_label_create(view, "horizontal bar:", 5, 40, 150, 20);
	hbar = rtgui_scrollbar_create(view, 5, 65, 20, 100, RTGUI_HORIZONTAL);
	rtgui_scrollbar_set_range(hbar, 10);
	rtgui_scrollbar_set_page_step(hbar, 5);
	rtgui_scrollbar_set_line_step(hbar, 1);

	rtgui_label_create(view, "vertical bar:", 5, 90, 150, 20);
	vbar = rtgui_scrollbar_create(view, 10, 115, 20, 80, RTGUI_VERTICAL);
	rtgui_scrollbar_set_range(vbar, 5);
	rtgui_scrollbar_set_page_step(vbar, 3);
	rtgui_scrollbar_set_line_step(vbar, 1);

	return view;
}
