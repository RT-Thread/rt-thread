#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/view.h>
#include "demo_view.h"

rt_bool_t benchmark_event_handler(rtgui_widget_t* widget, rtgui_event_t *event)
{
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		rtgui_rect_t rect;

		/* 因为用的是demo view，上面本身有一部分控件，所以在绘图时先要让demo view先绘图 */
		rtgui_view_event_handler(widget, event);

		/* 获得控件所属的DC */
		dc = rtgui_dc_begin_drawing(widget);
		if (dc == RT_NULL) /* 如果不能正常获得DC，返回（如果控件或父控件是隐藏状态，DC是获取不成功的） */
			return RT_FALSE;

		/* 获得demo view允许绘图的区域 */
		demo_view_get_rect(RTGUI_VIEW(widget), &rect);

		/* 擦除所有 */
		rtgui_dc_fill_rect(dc, &rect);

		/* 绘图 */
		rtgui_dc_draw_text(dc, "飞线乱飞", &text_rect);

		/* 绘图完成 */
		rtgui_dc_end_drawing(dc);
	}
	else
	{
		/* 调用默认的事件处理函数 */
		return rtgui_view_event_handler(widget, event);
	}

	return RT_FALSE;
}

rtgui_view_t *demo_view_benchmark(rtgui_workbench_t* workbench)
{
	rtgui_view_t *view;

	view = demo_view(workbench, "绘图测试");
	if (view != RT_NULL)
		rtgui_widget_set_event_handler(RTGUI_WIDGET(view), benchmark_event_handler);

	return view;
}
