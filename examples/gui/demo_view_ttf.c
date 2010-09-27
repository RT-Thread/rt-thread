/*
 * 程序清单：TTF字体显示演示
 *
 * 这个例子会在创建出的view上进行TTF字体显示的演示
 */

#include "demo_view.h"
#include <rtgui/dc.h>
#include <rtgui/font.h>
#include <rtgui/rtgui_system.h>

#ifdef RTGUI_USING_TTF
static 	rtgui_font_t *font_16, *font_24, *font_36, *font_48;

/*
 * view的事件处理函数
 */
rt_bool_t ttf_event_handler(rtgui_widget_t* widget, rtgui_event_t *event)
{
	/* 仅对PAINT事件进行处理 */
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		rtgui_rect_t rect;
		rtgui_font_t* saved;

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

		saved = RTGUI_WIDGET_FONT(widget);

		RTGUI_WIDGET_FONT(widget) = font_16;
		rtgui_dc_draw_text(dc, "ABCD中文", &rect);
		rect.y1 += 18; 

		RTGUI_WIDGET_FONT(widget) = font_24;
		rtgui_dc_draw_text(dc, "ABCD中文", &rect);
		rect.y1 += 26; 

		RTGUI_WIDGET_FONT(widget) = font_36;
		rtgui_dc_draw_text(dc, "ABCD中文", &rect);
		rect.y1 += 38; 

		RTGUI_WIDGET_FONT(widget) = font_48;
		rtgui_dc_draw_text(dc, "ABCD中文", &rect);

		RTGUI_WIDGET_FONT(widget) = saved;
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

/* 创建用于TTF字体显示演示用的视图 */
rtgui_view_t *demo_view_ttf(rtgui_workbench_t* workbench)
{
	rtgui_view_t *view;

	font_16 = rtgui_freetype_font_create("d:/simsun.ttf", 0, 0, 16);
	font_24 = rtgui_freetype_font_create("d:/simsun.ttf", 0, 0, 24);
	font_36 = rtgui_freetype_font_create("d:/simsun.ttf", 0, 0, 36);
	font_48 = rtgui_freetype_font_create("d:/simsun.TTF", 0, 0, 72);

	view = demo_view(workbench, "TTF 演示");
	if (view != RT_NULL)
	{
		RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(view)) = white;
		/* 设置成自己的事件处理函数 */
		rtgui_widget_set_event_handler(RTGUI_WIDGET(view), ttf_event_handler);
	}

	return view;
}
#endif
