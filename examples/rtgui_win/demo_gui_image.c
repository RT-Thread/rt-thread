/*
 * 程序清单：DC上显示图像演示
 *
 * 这个例子会在创建出的view上显示图像
 */

#include "demo_view.h"
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/filelist_view.h>
#include <string.h>

#if defined(RTGUI_USING_DFS_FILERW) || defined(RTGUI_USING_STDIO_FILERW)
/* 打开按钮的回调函数 */
static void open_btn_onbutton(PVOID wdt, rtgui_event_t* event)
{
	
}

/* 演示视图的事件处理函数 */
static rt_bool_t demo_view_event_handler(PVOID wdt, rtgui_event_t *event)
{
	rtgui_widget_t *widget = RTGUI_WIDGET(wdt);
	rt_bool_t result;

	/* 先调用默认的事件处理函数(这里只关心PAINT事件，但演示视图还有本身的一些控件) */
	result = rtgui_view_event_handler(widget, event);

	if (event->type == RTGUI_EVENT_PAINT)
	{
		rtgui_dc_t* dc;

		/* 获得控件所属的DC */
		dc = rtgui_dc_begin_drawing(widget);
		if (dc == RT_NULL) return RT_FALSE;

		/* 绘图完成 */
		rtgui_dc_end_drawing(dc);
	}

	return result;
}

/* 创建用于显示图像的演示视图 */
rtgui_view_t* demo_gui_image(rtgui_view_t* parent_view)
{
	rtgui_button_t* open_btn;
	rtgui_view_t *view;
	rtgui_filelist_view_t *fview;
	

	/* 先创建一个演示视图 */
	view = demo_view_create(parent_view, "图像演示");

#ifdef _WIN32
	fview = rtgui_filelist_view_create(view, "d:\\", "*.*", 5, 65, 200, 180);
#else
	fview = rtgui_filelist_view_create(view, "/", "*.*", 5, 65, 200, 180);
#endif

	if (view != RT_NULL)
		/* 设置默认的事件处理函数到demo_view_event_handler函数 */
		rtgui_widget_set_event_handler(view, demo_view_event_handler);

	/* 添加一个按钮 */
	open_btn = rtgui_button_create(view, "打开图像文件", 10, 40, 120, 22);
	rtgui_button_set_onbutton(open_btn, open_btn_onbutton);

	return view;
}
#endif
