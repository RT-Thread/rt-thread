#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>

#include <rtgui/widgets/view.h>
#include <rtgui/widgets/workbench.h>

static rt_bool_t view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	/* 我们目前只对绘制事件感兴趣 */
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		struct rtgui_rect rect;

		/* 获得一个设备上下文 */
		dc = rtgui_dc_begin_drawing(widget);
		if (dc == RT_NULL) return RT_FALSE; /* 如果获取失败代表什么？这个控件是隐藏的或... */
		rtgui_widget_get_rect(widget, &rect); /* 获得控件的可视区域 */

		/* 先对所在可视区域全部填充为背景色 */
		rtgui_dc_fill_rect(dc, &rect);

		/* 绘制一个hello! */
		rtgui_dc_draw_text(dc, "hello world", &rect);

		/* 通知RTGUI，绘制结束 */
		rtgui_dc_end_drawing(dc);

		return RT_FALSE;
	}

	/* 如果不是绘制事件，使用view原来的事件处理函数处理 */
	return rtgui_view_event_handler(widget, event);
}

static void workbench_entry(void* parameter)
{
	rt_mq_t mq;
	struct rtgui_view* view;
	struct rtgui_workbench* workbench;

	/* 创建GUI应用需要的消息队列 */
	mq = rt_mq_create("workbench", 256, 4, RT_IPC_FLAG_FIFO);
	/* 注册当前线程为GUI线程 */
	rtgui_thread_register(rt_thread_self(), mq);

	/* 创建一个工作台 */
	workbench = rtgui_workbench_create("main", "workbench");
	if (workbench == RT_NULL) return;

	/* 创建一个工作台上的一个视图 */
	view = rtgui_view_create("view");
	rtgui_widget_set_event_handler(RTGUI_WIDGET(view), view_event_handler);

	/* 在工作台上添加一个视图 */
	rtgui_workbench_add_view(workbench, view);

	/* 显示这个视图 */
	rtgui_view_show(view);

	/* 执行工作台事件循环 */
	rtgui_workbench_event_loop(workbench);

	/* 去注册GUI线程 */
	rtgui_thread_deregister(rt_thread_self());
	rt_mq_delete(mq);
}

void workbench_init()
{
	static rt_bool_t inited = RT_FALSE;

	if (inited == RT_FALSE) /* 避免重复初始化而做的保护 */
	{
		rt_thread_t tid;

		tid = rt_thread_create("wb",
			workbench_entry, RT_NULL,
			2048, 25, 10);

		if (tid != RT_NULL) rt_thread_startup(tid);

		inited = RT_TRUE;
	}
}

#ifdef RT_USING_RTGUI
#include <finsh.h>
void workbench()
{
	workbench_init();
}
/* finsh的命令输出，可以直接执行workbench()函数以执行上面的函数 */
FINSH_FUNCTION_EXPORT(workbench, workbench demo)
#endif
