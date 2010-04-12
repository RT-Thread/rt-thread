/*
 * 程序清单：DC操作演示
 *
 * 这个例子会在创建出的view上进行DC操作的演示
 */

#include "demo_view.h"
#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/slider.h>

/*
 * view的事件处理函数
 */
rt_bool_t dc_event_handler(rtgui_widget_t* widget, rtgui_event_t *event)
{
	/* 仅对PAINT事件进行处理 */
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		rtgui_rect_t rect;
		rt_uint32_t vx[] = {20, 50, 60, 45, 60, 20};
		rt_uint32_t vy[] = {150, 50, 90, 60, 45, 50};

		/*
		 * 因为用的是demo view，上面本身有一部分控件，所以在绘图时先要让demo view
		 * 先绘图
		 */
		rtgui_view_event_handler(widget, event);

		/************************************************************************/
		/* 下面的是DC的操作                                                     */
		/************************************************************************/

		/* 获得控件所属的DC */
		dc = rtgui_dc_begin_drawing(widget);
		/* 如果不能正常获得DC，返回（如果控件或父控件是隐藏状态，DC是获取不成功的） */
		if (dc == RT_NULL)
			return RT_FALSE;

		/* 获得demo view允许绘图的区域 */
		demo_view_get_rect(RTGUI_VIEW(widget), &rect);

		RTGUI_DC_TEXTALIGN(dc) = RTGUI_ALIGN_BOTTOM | RTGUI_ALIGN_CENTER_HORIZONTAL;
		/* 显示GUI的版本信息 */
#ifdef RTGUI_USING_SMALL_SIZE
		rtgui_dc_draw_text(dc, "RT-Thread/GUI小型版本", &rect);
#else
		rtgui_dc_draw_text(dc, "RT-Thread/GUI标准版本", &rect);
#endif

		/* 绘制一个圆形 */
		RTGUI_DC_FC(dc) = red;
		rtgui_dc_draw_circle(dc, rect.x1 + 10, rect.y1 + 10, 10);

		/* 填充一个圆形 */
		RTGUI_DC_FC(dc) = green;
		rtgui_dc_fill_circle(dc, rect.x1 + 30, rect.y1 + 10, 10);

		/* 画一个圆弧 */
		RTGUI_DC_FC(dc) = RTGUI_RGB(250, 120, 120);
		rtgui_dc_draw_arc(dc, rect.x1 + 120, rect.y1 + 60, 30, 0, 120);

		/* 多边形 */
		RTGUI_DC_FC(dc) = blue;
		rtgui_dc_draw_polygon(dc, vx, vy, 6);

		/* 绘制不同的边框 */
		{
			rtgui_rect_t rect = {0, 0, 16, 16};
			rtgui_rect_moveto(&rect, 30, 120);

			rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_RAISE);
			rect.x1 += 20;
			rect.x2 += 20 + 50;
			rtgui_dc_draw_text(dc, "raise", &rect);
			rect.x1 -= 20;
			rect.x2 -= 20 + 50;
			rect.y1 += 20;
			rect.y2 += 20;

			rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_SIMPLE);
			rect.x1 += 20;
			rect.x2 += 20 + 50;
			rtgui_dc_draw_text(dc, "simple", &rect);
			rect.x1 -= 20;
			rect.x2 -= 20 + 50;
			rect.y1 += 20;
			rect.y2 += 20;

			rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_SUNKEN);
			rect.x1 += 20;
			rect.x2 += 20 + 50;
			rtgui_dc_draw_text(dc, "sunken", &rect);
			rect.x1 -= 20;
			rect.x2 -= 20 + 50;
			rect.y1 += 20;
			rect.y2 += 20;

			rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_BOX);
			rect.x1 += 20;
			rect.x2 += 20 + 50;
			rtgui_dc_draw_text(dc, "box", &rect);
			rect.x1 -= 20;
			rect.x2 -= 20 + 50;
			rect.y1 += 20;
			rect.y2 += 20;

			rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_STATIC);
			rect.x1 += 20;
			rect.x2 += 20 + 50;
			rtgui_dc_draw_text(dc, "static", &rect);
			rect.x1 -= 20;
			rect.x2 -= 20 + 50;
			rect.y1 += 20;
			rect.y2 += 20;

			rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_EXTRA);
			rect.x1 += 20;
			rect.x2 += 20 + 50;
			rtgui_dc_draw_text(dc, "extra", &rect);
			rect.x1 -= 20;
			rect.x2 -= 20 + 50;
			rect.y1 += 20;
			rect.y2 += 20;
		}

		/* 绘图完成 */
		rtgui_dc_end_drawing(dc);
	}
	else
	{
		/* 其他事件，调用默认的事件处理函数 */
		return rtgui_view_event_handler(widget, event);
	}

	return RT_FALSE;
}

/* 创建用于DC操作演示用的视图 */
rtgui_view_t *demo_view_dc(rtgui_workbench_t* workbench)
{
	rtgui_view_t *view;

	view = demo_view(workbench, "DC Demo");
	if (view != RT_NULL)
		/* 设置成自己的事件处理函数 */
		rtgui_widget_set_event_handler(RTGUI_WIDGET(view), dc_event_handler);

	return view;
}
