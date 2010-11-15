#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/view.h>
#include "demo_view.h"

/*
 * 直接在DC上绘图以实现动画效果
 *
 * 动画是依赖于定时器驱动的，会上下翻滚显示文字
 * "飞线乱飞"
 */
static rt_int8_t dx = 1, dy = 1;
static rtgui_rect_t text_rect;
static rtgui_timer_t *timer;
static struct rtgui_dc *dc_buffer;
static void timeout(struct rtgui_timer* timer, void* parameter)
{
	struct rtgui_dc* dc;
	rtgui_rect_t rect;
	rtgui_widget_t *widget;

	/* 控件(view)通过parameter参数传递给定时器 */
	widget = (rtgui_widget_t*)parameter;

	/* 获得控件所属的DC */
	dc = rtgui_dc_begin_drawing(widget);
	if (dc == RT_NULL) /* 如果不能正常获得DC，返回（如果控件或父控件是隐藏状态，DC是获取不成功的） */
		return ;

	/* 获得demo view允许绘图的区域，主要用于判断边界 */
	demo_view_get_logic_rect(RTGUI_VIEW(widget), &rect);
	rect.y2 -= 5;

	/* 判断是否是第一次绘图 */
	if ((text_rect.x1 == 0) && (text_rect.y1 == 0))
	{
		rtgui_rect_moveto(&text_rect, rect.x1, rect.y1);
	}

    /* 设置dx和dy */
	if (text_rect.x2 >= rect.x2) dx = -1;
	if (text_rect.x1 < rect.x1)  dx = 1;
	if (text_rect.y2 >= rect.y2) dy = -1;
	if (text_rect.y1 < rect.y1) dy = 1;

    /* 移动文本框的位置 */
	text_rect.x1 += dx; text_rect.x2 += dx;
	text_rect.y1 += dy; text_rect.y2 += dy;

    /* 绘图 */
	rect = text_rect;
	rect.x2 += 2; rect.y2 += 2;
	rtgui_dc_blit(dc_buffer, NULL, dc, &rect);

	/* 绘图完成 */
	rtgui_dc_end_drawing(dc);
}

static rt_bool_t animation_event_handler(rtgui_widget_t* widget, rtgui_event_t *event)
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
        demo_view_get_logic_rect(RTGUI_VIEW(widget), &rect);

		/* 绘图 */
		rect = text_rect;
		rtgui_rect_inflate(&rect, +1);
		rtgui_dc_blit(dc_buffer, NULL, dc, &rect);

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

rtgui_view_t *demo_view_buffer_animation(rtgui_workbench_t* workbench)
{
	rtgui_view_t *view;

	view = demo_view(workbench, "DC 缓冲区动画");
	if (view != RT_NULL)
		rtgui_widget_set_event_handler(RTGUI_WIDGET(view), animation_event_handler);

	rtgui_font_get_metrics(RTGUI_WIDGET_FONT(RTGUI_WIDGET(view)), "缓冲动画", &text_rect);
	if (dc_buffer == RT_NULL)
	{
		rtgui_rect_t rect;

		rect.x1 = 0; rect.x2 = rtgui_rect_width(text_rect) + 2;
		rect.y1 = 0; rect.y2 = rtgui_rect_height(text_rect) + 2;

		/* 创建 DC Buffer，长 50，宽 50 */
		dc_buffer = rtgui_dc_buffer_create(rtgui_rect_width(rect), rtgui_rect_height(rect));
		RTGUI_DC_FC(dc_buffer) = RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(view));
		rtgui_dc_fill_rect(dc_buffer, &rect);
		RTGUI_DC_FC(dc_buffer) = black;
		rect.x1 = 1; rect.y1 = 1;
		rtgui_dc_draw_text(dc_buffer, "缓冲动画", &rect);
	}

	/* 启动定时器以触发动画 */
	timer = rtgui_timer_create(1, RT_TIMER_FLAG_PERIODIC, timeout, (void*)view);
	rtgui_timer_start(timer);

	return view;
}
