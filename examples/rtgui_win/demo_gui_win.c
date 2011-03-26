/*
 * 这个例子演示了如何在一个线程中创建一个win
 */

#include <rtthread.h>
#include <rtgui/rtgui.h>
#include <rtgui/event.h>
#include <rtgui/driver.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/radiobox.h>
#include <rtgui/widgets/window.h>

static rt_bool_t demo_win_inited = RT_FALSE;


static rt_bool_t demo_gui_win_event_handler(PVOID wdt, rtgui_event_t* event)
{

	if(event->type == RTGUI_EVENT_PAINT)
	{
		
	}
	
	/* 其他事件使用win默认的事件处理函数处理 */
	return rtgui_win_event_handler(wdt, event);
}

static void gui_win_entry(void* parameter)
{
	const struct rtgui_graphic_driver* gd = rtgui_graphic_driver_get_default();
	struct rt_messagequeue *mq;
	rtgui_win_t *win;
	rtgui_button_t *button;
	rtgui_point_t p;
	rtgui_rect_t rect = {0,0,200,180};
	rtgui_label_t *label;
	rtgui_font_t *font;
	
	/* 创建GUI应用需要的消息队列 */
	mq = rt_mq_create("demo_win", 256, 32, RT_IPC_FLAG_FIFO);
	/* 注册当前线程 */
	rtgui_thread_register(rt_thread_self(), mq);

	/* 窗口居中 */
	rtgui_rect_moveto(&rect, (gd->width - rtgui_rect_width(rect))/2, (gd->height - rtgui_rect_height(rect))/2);
	/* 创建窗口 */
	win = rtgui_win_create(RT_NULL,"demo_win",&rect,RTGUI_WIN_DEFAULT);
	if(win == RT_NULL) return;
 
	/* 取得客户区坐标零点 */
	p = rtgui_win_get_client_zero(win);
	label = rtgui_label_create(win, "hello world!", p.x+5, p.y+5, 100,25);
	font = rtgui_font_refer("asc", 12);	
	RTGUI_WIDGET_FONT(label) = font;

	button = rtgui_button_create(win, "Exit", (rtgui_rect_width(rect)-50)/2,
								rtgui_rect_height(rect)-40,50,25);
	rtgui_button_set_onbutton(button,rtgui_win_close);

	rtgui_widget_set_event_handler(win, demo_gui_win_event_handler);
	
	rtgui_win_show(win,RT_FALSE);
	
	/* 执行工作台事件循环 */
	rtgui_win_event_loop(win);

	demo_win_inited = RT_FALSE;
	
	/* 去注册GUI线程 */
	rtgui_thread_deregister(rt_thread_self());
	rt_mq_delete(mq);
}

void demo_gui_win(PVOID wdt, rtgui_event_t *event)
{
	if(demo_win_inited == RT_FALSE) /* 避免重复初始化而做的保护 */
	{
		struct rt_thread* tid;
		
		tid = rt_thread_create("demo_win", gui_win_entry, RT_NULL, 1024, 5, 10);

		if(tid != RT_NULL) rt_thread_startup(tid);

		demo_win_inited = RT_TRUE;
	}
}





