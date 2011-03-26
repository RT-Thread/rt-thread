/*
 * 程序清单：DC Buffer演示
 *
 * 这个例子会在创建出的view上进行DC Buffer的演示
 */
#include <rtgui/event.h>
#include <rtgui/widgets/view.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/slider.h>
#include <rtgui/image.h>
#include "demo_view.h"

static struct rtgui_dc *dc_buffer;

/*
 * view的事件处理函数
 */
static rt_bool_t dc_buffer_event_handler(PVOID wdt, rtgui_event_t *event)
{

	/* 仅对PAINT事件进行处理 */
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		rtgui_rect_t rect;

		/*
		 * 因为用的是demo view，上面本身有一部分控件，所以在绘图时先要让demo view
		 * 先绘图
		 */
		rtgui_view_event_handler(wdt, event);

		/* 获得控件所属的DC */
		dc = rtgui_dc_begin_drawing(wdt);
		/* 如果不能正常获得DC，返回（如果控件或父控件是隐藏状态，DC是获取不成功的） */
		if (dc == RT_NULL)
			return RT_FALSE;
		rtgui_widget_get_rect(wdt, &rect);
		rect.x1 += 10;
		rect.y1 += 40;
		rtgui_dc_blit(dc_buffer, NULL, dc, &rect);

		/* 绘图完成 */
		rtgui_dc_end_drawing(dc);
	}
	else
	{
		/* 其他事件，调用默认的事件处理函数 */
		return rtgui_view_event_handler(wdt, event);
	}

	return RT_FALSE;
}

/* 创建用于DC Buffer操作演示用的视图 */
rtgui_view_t *demo_gui_dc_buffer(rtgui_view_t* parent_view)
{
	rtgui_view_t *view;

	if (dc_buffer == RT_NULL)
	{
		rtgui_rect_t rect = {0, 0, 50, 50};

		/* 创建 DC Buffer，长 50，宽 50 */
		dc_buffer = rtgui_dc_buffer_create(50, 50);
		RTGUI_DC_FC(dc_buffer) = blue;
		rtgui_dc_fill_rect(dc_buffer, &rect);

		RTGUI_DC_FC(dc_buffer) = red;
		rtgui_dc_draw_circle(dc_buffer, 25, 25, 10);
	}

	view = demo_view_create(parent_view, "缓冲DC演示");
	if (view == RT_NULL) return RT_NULL;
	/* 设置成自己的事件处理函数 */
	rtgui_widget_set_event_handler(view, dc_buffer_event_handler);

	return view;
}
