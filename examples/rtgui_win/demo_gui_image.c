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

rtgui_filelist_view_t *demo_fview;
static rtgui_view_t *image_view = RT_NULL;
static rtgui_image_t *demo_image = RT_NULL;

/* 打开文件处理函数,这里只处理图像文件 */
rt_bool_t demo_image_fview_on_item(PVOID wdt, rtgui_event_t *event)
{
	rtgui_filelist_view_t *fview = wdt;
	if(fview == RT_NULL) return RT_FALSE;

	if(fview->pattern != RT_NULL && fview->items != RT_NULL)
	{
		char path[32], image_type[8];

		/* 设置文件路径的标签 */
		rtgui_filelist_view_get_fullpath(fview, path, sizeof(path));
		if (demo_image != RT_NULL) 
		{
			rtgui_image_destroy(demo_image);
			demo_image = RT_NULL;
		}

		rt_memset(image_type, 0, sizeof(image_type));

		/* 获得图像的类型 */
		if (rt_strstr(path, ".bmp") != RT_NULL ||
			rt_strstr(path, ".BMP") != RT_NULL)
			strcat(image_type, "bmp");
		if (rt_strstr(path, ".png") != RT_NULL ||
			rt_strstr(path, ".PNG") != RT_NULL)
			strcat(image_type, "png");
		if (rt_strstr(path, ".jpg") != RT_NULL ||
			rt_strstr(path, ".JPG") != RT_NULL)
			strcat(image_type, "jpeg");
		if (rt_strstr(path, ".hdc") != RT_NULL ||
			rt_strstr(path, ".HDC") != RT_NULL)
			strcat(image_type, "hdc");
		
		/* 如果图像文件有效，创建相应的rtgui_image对象 */
		if (image_type[0] != '\0')
			demo_image = rtgui_image_create_from_file(image_type, path, RT_TRUE);
	}

	rtgui_widget_update(image_view);
	return RT_TRUE;
}

/* 返回按钮的回调函数 */
static void back_btn_onbutton(PVOID wdt, rtgui_event_t* event)
{
	if(demo_fview != RT_NULL)
	{
		rtgui_filelist_view_goto_topfolder(demo_fview);
	}		
}

/* 打开按钮的回调函数 */
static void open_btn_onbutton(PVOID wdt, rtgui_event_t* event)
{
	if(demo_fview != RT_NULL)
	{
		rtgui_filelist_view_on_enter(demo_fview);
	}		
}

/* 演示视图的事件处理函数 */
static rt_bool_t demo_gui_image_handler(PVOID wdt, rtgui_event_t *event)
{
	rtgui_widget_t* widget = wdt;

	if(event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		rtgui_rect_t rect;

		/* 获得控件所属的DC */
		dc = rtgui_dc_begin_drawing(widget);
		if(dc == RT_NULL) return RT_FALSE;

		/* 获得demo view允许绘图的区域 */
		rtgui_widget_get_rect(widget, &rect);
		/* 清除背景 */
		rtgui_dc_fill_rect(dc, &rect);
		/* 绘制图片 */
		if(demo_image != RT_NULL) rtgui_image_blit(demo_image, dc, &rect);

		/* 绘图完成 */
		rtgui_dc_end_drawing(dc);
	}
	else
		return rtgui_view_event_handler(widget, event);
	
	return RT_TRUE;
}

/* 创建用于显示图像的演示视图 */
rtgui_view_t* demo_gui_image(rtgui_view_t* parent_view)
{
	rtgui_button_t* button;
	rtgui_view_t *view;
	
	/* 先创建一个演示视图 */
	view = demo_view_create(parent_view, "图像演示");

	/* 创建一个文件浏览列表 */
#ifdef _WIN32
	demo_fview = rtgui_filelist_view_create(view, "d:\\", "*.hdc", 5, 32, 200, 68);
#else
	demo_fview = rtgui_filelist_view_create(view, "/", "*.hdc", 5, 32, 200, 68);
#endif
	demo_fview->on_item = demo_image_fview_on_item;

	/* 添加一个返回按钮,浏览文件夹时,用于返回上一级目录 */
	button = rtgui_button_create(view, "back", 5, 102, 40, 24);
	rtgui_button_set_onbutton(button, back_btn_onbutton);
	/* 添加一个打开按钮,浏览文件夹是,用于进入下一级目录,或者打开文件 */
	button = rtgui_button_create(view, "open", 5, 130, 40, 24);
	rtgui_button_set_onbutton(button, open_btn_onbutton);
	
	/* 创建一个视图,用于显示图片 */
	image_view = rtgui_view_create(view, "image_view", 50, 102, 160, 120);
	if(image_view == RT_NULL) return RT_NULL;
	/* 给image_view设置一个事件处理句柄 */
	rtgui_widget_set_event_handler(image_view, demo_gui_image_handler);

	return view;
}
#endif
