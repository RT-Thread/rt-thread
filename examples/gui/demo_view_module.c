/*
 * 程序清单：DC上显示图像演示
 *
 * 这个例子会在创建出的view上显示图像
 */

#include "demo_view.h"
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/filelist_view.h>
#include <string.h>

#ifdef RT_USING_MODULE
#if defined(RTGUI_USING_DFS_FILERW) || defined(RTGUI_USING_STDIO_FILERW)
static rtgui_view_t* _view = RT_NULL;

/* 打开按钮的回调函数 */
static void open_btn_onbutton(rtgui_widget_t* widget, struct rtgui_event* event)
{
	rtgui_filelist_view_t *view;
	rtgui_workbench_t *workbench;
	rtgui_rect_t rect;

	/* 获得顶层的workbench */
	workbench = RTGUI_WORKBENCH(rtgui_widget_get_toplevel(widget));
	rtgui_widget_get_rect(RTGUI_WIDGET(workbench), &rect);

	/* WIN32平台上和真实设备上的初始路径处理 */
#ifdef _WIN32
	view = rtgui_filelist_view_create(workbench, "d:\\", "*.*", &rect);
#else
	view = rtgui_filelist_view_create(workbench, "/", "*.*", &rect);
#endif
	/* 模态显示一个文件列表视图，以提供给用户选择图像文件 */
	if (rtgui_view_show(RTGUI_VIEW(view), RT_TRUE) == RTGUI_MODAL_OK)
	{
		char path[32], name[8];

		/* 设置文件路径的标签 */
		rtgui_filelist_view_get_fullpath(view, path, sizeof(path));

		rt_memset(name, 0, sizeof(name));

		/* 获得应用模块的类型 */
		if (rt_strstr(path, ".mo") != RT_NULL || rt_strstr(path, ".so") != RT_NULL)
		{
			rt_module_open(path);
		}	
	}

	/* 删除 文件列表 视图 */
	rtgui_view_destroy(RTGUI_VIEW(view));
	rtgui_view_show(_view, RT_FALSE);
}

/* 创建用于显示应用模块的演示视图 */
rtgui_view_t* demo_view_module(rtgui_workbench_t* workbench)
{
	rtgui_rect_t rect;
	rtgui_button_t* open_btn;

	/* 先创建一个演示视图 */
	_view = demo_view(workbench, "应用模块演示");

	/* 添加一个按钮 */
	demo_view_get_rect(_view, &rect);
	rect.x1 += 5; rect.x2 = rect.x1 + 120;
	rect.y2 = rect.y1 + 20;
	open_btn = rtgui_button_create("打开应用模块");
	rtgui_container_add_child(RTGUI_CONTAINER(_view), RTGUI_WIDGET(open_btn));
	rtgui_widget_set_rect(RTGUI_WIDGET(open_btn), &rect);
	rtgui_button_set_onbutton(open_btn, open_btn_onbutton);

	return _view;
}
#endif
#endif

