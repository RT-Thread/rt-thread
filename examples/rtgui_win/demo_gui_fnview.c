/*
 * 程序清单：文件列表视图演示
 *
 * 这个例子会先创建出一个演示用的view，当点击上面的按钮时会按照模式显示的形式显示
 * 新的文件列表视图。
 */
#include "demo_view.h"
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/filelist_view.h>

#if defined(RTGUI_USING_DFS_FILERW) || defined(RTGUI_USING_STDIO_FILERW)

/* 文件处理函数 */
rt_bool_t demo_fview_on_item(PVOID wdt, struct rtgui_event *event)
{
	rt_kprintf("fview file on item.\n");
	return RT_TRUE;
}

/* 创建用于演示文件列表视图的视图 */
/* 方向键: 移动
 * 回车键: 进入下一级目录,或调用文件处理函数
 * 退格键: 返回上一级目录 
 */
rtgui_view_t* demo_gui_fnview(rtgui_view_t* parent_view)
{
	rtgui_view_t *view;
	rtgui_filelist_view_t *fview;

	/* 创建演示用的视图 */
	view = demo_view_create(parent_view, "FileList View");

#ifdef _WIN32
	fview = rtgui_filelist_view_create(view, "d:\\", "*.*", 5, 40, 200, 150);
#else
	fview = rtgui_filelist_view_create(view, "/", "*.*", 5, 40, 200, 150);
#endif

	fview->on_item = demo_fview_on_item;

	return view;
}
#endif
