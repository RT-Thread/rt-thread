/*
 * 这个一个RTGUI的例子，演示了如何创建一个RTGUI程序
 */
#include <rtthread.h>
#include <rtgui/rtgui.h>
#include <panel.h>
#include <rtgui/event.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/textbox.h>
#include <rtgui/widgets/view.h>
#include <rtgui/widgets/listbox.h>
#include <rtgui/rtgui_theme.h>

rtgui_listbox_t *__lbox;

static rtgui_listbox_item_t _demo_list[] = 
{
	{"item1",  RT_NULL},
	{"item2",  RT_NULL},
};

/* 给列表添加一个项目 */
void user_add_one_item(PVOID wdt, rtgui_event_t *event)
{
	rtgui_listbox_item_t item={"new item", RT_NULL};
	if(__lbox != RT_NULL)
	{
		__lbox->add_item(__lbox, &item);
	}	 	
}

static void rtgui_panel_entry(void* parameter)
{
	const struct rtgui_graphic_driver* gd = rtgui_graphic_driver_get_default();
	struct rt_messagequeue* mq;
	rtgui_panel_t *panel;
	rtgui_view_t *view;
	rtgui_button_t *button;
	
	/* 创建GUI应用需要的消息队列 */
	mq = rt_mq_create("Panel", 256, 32, RT_IPC_FLAG_FIFO);
	/* 注册当前线程为GUI线程 */
	rtgui_thread_register(rt_thread_self(), mq);

	panel = rtgui_panel_create(0,0,gd->width,gd->height);

	//创建一个标题/信息栏
	view = rtgui_view_create(panel,"titlebar",0,0,gd->width,30);
	rtgui_widget_set_style(view, RTGUI_BORDER_SIMPLE);
	rtgui_label_create(view, "hello world!",5,2,150,24);	

	//创建一个列表
	__lbox = rtgui_listbox_create(panel,10,30,120,100,RTGUI_BORDER_SUNKEN);
	rtgui_listbox_set_items(__lbox,_demo_list,RT_COUNT(_demo_list));
	button = rtgui_button_create(panel,"add",140,60,50,25);
	rtgui_button_set_onbutton(button,user_add_one_item);

	//创建一个编辑框
	rtgui_textbox_create(panel,
		"this is a textbox,\n"
		"demo multi text.\n",
		10,150,180,50,
		RTGUI_TEXTBOX_MULTI);

	///////////////////////////////////////////////////////
	rtgui_panel_show(panel);	

	/* 执行工作台事件循环 */
	rtgui_panel_event_loop(panel);
	
	/* 去注册GUI线程 */
	rtgui_thread_deregister(rt_thread_self());
	rt_mq_delete(mq);
}

void rtgui_panel_init(void)
{
	static rt_bool_t main_inited = RT_FALSE;

	if(main_inited == RT_FALSE) /* 避免重复初始化而做的保护 */
	{
		struct rt_thread* tid;

		tid = rt_thread_create("Panel", rtgui_panel_entry, RT_NULL, 4096, 4, 5);

		if(tid != RT_NULL) rt_thread_startup(tid);

		main_inited = RT_TRUE;
	}
}

