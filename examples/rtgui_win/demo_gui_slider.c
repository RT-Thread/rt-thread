#include "demo_view.h"
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/slider.h>

rtgui_view_t *demo_gui_slider(rtgui_view_t* parent_view)
{
	rtgui_view_t *view;

	/* create a demo view */
	view = demo_view_create(parent_view, "Slider View");

	rtgui_label_create(view, "horizontal slider:", 5, 40, 150, 20);
	rtgui_slider_create(view, 0, 100, 5, 60, 100, 16, RTGUI_HORIZONTAL);

	rtgui_label_create(view, "vertical slider:", 5, 80, 150, 20);
	rtgui_slider_create(view, 0, 100, 10, 100, 16, 80, RTGUI_VERTICAL);

	return view;
}
