#include "demo_view.h"
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/progressbar.h>

void hbar_timeout(struct rtgui_timer* timer, void* parameter)
{
	static rt_uint32_t value = 0;
	rtgui_progressbar_t *bar = (rtgui_progressbar_t*)parameter;

	value += 3;
	if (value >= 100) value = 0;

	rtgui_progressbar_set_value(bar, value);
}

void vbar_timeout(struct rtgui_timer* timer, void* parameter)
{
	static rt_uint32_t value = 0;
	rtgui_progressbar_t *bar = (rtgui_progressbar_t*)parameter;

	value += 5;
	if (value >= 100) value = 0;

	rtgui_progressbar_set_value(bar, value);
}

rtgui_view_t *demo_gui_progressbar(rtgui_view_t* parent_view)
{
	rtgui_view_t *view;
	rtgui_progressbar_t *hbar, *vbar;
	rtgui_timer_t *timer = RT_NULL;
	
	/* create a demo view */
	view = demo_view_create(parent_view, "ProgressBar View");
	
	rtgui_label_create(view, "水平进度条:", 5, 40, 100, 20);
	hbar = rtgui_progressbar_create(view, RTGUI_HORIZONTAL, 100, 10, 70, 150, 15);

	rtgui_label_create(view, "垂直进度条:", 5, 90, 100, 20);
	vbar = rtgui_progressbar_create(view, RTGUI_VERTICAL, 100, 10, 110, 15, 60);

	timer = rtgui_timer_create(20, RT_TIMER_FLAG_PERIODIC, hbar_timeout, hbar);
	rtgui_timer_start(timer);

	timer = rtgui_timer_create(20, RT_TIMER_FLAG_PERIODIC, vbar_timeout, vbar);
	rtgui_timer_start(timer);

	return view;
}

