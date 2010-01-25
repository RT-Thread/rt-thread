#include "demo_view.h"
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/slider.h>

rt_bool_t dc_event_handler(rtgui_widget_t* widget, rtgui_event_t *event)
{
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		rtgui_rect_t rect;
		rt_uint32_t vx[] = {20, 50, 60, 45, 60, 20};
		rt_uint32_t vy[] = {150, 50, 90, 60, 45, 50};

		/* 因为用的是demo view，上面本身有一部分控件，所以在绘图时先要让它先绘图 */
		rtgui_view_event_handler(widget, event);

		/************************************************************************/
		/* 下面的是DC的处理                                                     */
		/************************************************************************/

		/* 获得控件所属的DC */
		dc = rtgui_dc_begin_drawing(widget);
		if (dc == RT_NULL) /* 如果不能正常获得DC，返回（如果控件或父控件是隐藏状态，DC是获取不成功的） */
			return RT_FALSE;

		/* 获得demo view允许绘图的区域 */
		demo_view_get_rect(RTGUI_VIEW(widget), &rect);

		/* 绘制一个圆形 */
		rtgui_dc_set_color(dc, red);
		rtgui_dc_draw_circle(dc, rect.x1 + 10, rect.y1 + 10, 10);

		/* 填充一个圆形 */
		rtgui_dc_set_color(dc, green);
		rtgui_dc_fill_circle(dc, rect.x1 + 30, rect.y1 + 10, 10);

		/* 多边形 */
		rtgui_dc_set_color(dc, blue);
		rtgui_dc_draw_polygon(dc, vx, vy, 6);

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

rtgui_view_t *demo_view_dc(rtgui_workbench_t* workbench)
{
	rtgui_view_t *view;

	view = demo_view(workbench, "DC Demo");
	rtgui_widget_set_event_handler(RTGUI_WIDGET(view), dc_event_handler);

	return view;
}
