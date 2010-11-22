#include <rtgui/rtgui.h>
#include <rtgui/widgets/view.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/workbench.h>
#include <rtgui/widgets/staticline.h>

/* 用于存放演示视图的数组，最多可创建32个演示视图 */
static rtgui_view_t* demo_view_list[32];
/* 当前演示视图索引 */
static rt_uint16_t demo_view_current = 0;
/* 总共包括的演示视图数目 */
static rt_uint16_t demo_view_number = 0;

/* 显示下一个演示视图 */
void demo_view_next(struct rtgui_widget* widget, rtgui_event_t *event)
{
	if (demo_view_current + 1< demo_view_number)
	{
		demo_view_current ++;
		rtgui_view_show(demo_view_list[demo_view_current], RT_FALSE);
	}
}

/* 显示前一个演示视图 */
void demo_view_prev(struct rtgui_widget* widget, rtgui_event_t *event)
{
	if (demo_view_current != 0)
	{
		demo_view_current --;
		rtgui_view_show(demo_view_list[demo_view_current], RT_FALSE);
	}
}

/* 创建一个演示视图，需提供父workbench和演示用的标题 */
rtgui_view_t* demo_view(rtgui_workbench_t* workbench, const char* title)
{
	struct rtgui_view* view;

	/* 设置视图的名称 */
	view = rtgui_view_create(title);
	if (view == RT_NULL) return RT_NULL;

	/* 创建成功后，添加到数组中 */
	demo_view_list[demo_view_number] = view;
	demo_view_number ++;

	/* 添加到父workbench中 */
	rtgui_workbench_add_view(workbench, view);

	/* 添加下一个视图和前一个视图按钮 */
	{
		struct rtgui_rect rect;
		struct rtgui_button *next_btn, *prev_btn;
		struct rtgui_label *label;
		struct rtgui_staticline *line;

		/* 获得视图的位置信息(在加入到workbench中时，workbench会自动调整视图的大小) */
		rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);
		rtgui_widget_rect_to_device(RTGUI_WIDGET(view), &rect);
		rect.x1 += 5;
		rect.y1 += 5;
		rect.x2 -= 5;
		rect.y2 = rect.y1 + 20;

		/* 创建标题用的标签 */
		label = rtgui_label_create(title);
		/* 设置标签位置信息 */
		rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
		/* 添加标签到视图中 */
		rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));

		rect.y1 += 20;
		rect.y2 += 20;
		/* 创建一个水平的staticline线 */
		line = rtgui_staticline_create(RTGUI_HORIZONTAL);
		/* 设置静态线的位置信息 */
		rtgui_widget_set_rect(RTGUI_WIDGET(line), &rect);
		/* 添加静态线到视图中 */
		rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(line));

		/* 获得视图的位置信息 */
		rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);
		rtgui_widget_rect_to_device(RTGUI_WIDGET(view), &rect);
		rect.x2 -= 5;
		rect.y2 -= 5;
		rect.x1 = rect.x2 - 100;
		rect.y1 = rect.y2 - 25;

		/* 创建"下一个"按钮 */
		next_btn = rtgui_button_create("下一个");
		/* 设置onbutton动作到demo_view_next函数 */
		rtgui_button_set_onbutton(next_btn, demo_view_next);
		/* 设置按钮的位置信息 */
		rtgui_widget_set_rect(RTGUI_WIDGET(next_btn), &rect);
		/* 添加按钮到视图中 */
		rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(next_btn));

		/* 获得视图的位置信息 */
		rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);
		rtgui_widget_rect_to_device(RTGUI_WIDGET(view), &rect);
		rect.x1 += 5;
		rect.y2 -= 5;
		rect.x2 = rect.x1 + 100;
		rect.y1 = rect.y2 - 25;

		/* 创建"上一个"按钮 */
		prev_btn = rtgui_button_create("上一个");
		/* 设置onbutton动作到demo_view_prev函数 */
		rtgui_button_set_onbutton(prev_btn, demo_view_prev);
		/* 设置按钮的位置信息 */
		rtgui_widget_set_rect(RTGUI_WIDGET(prev_btn), &rect);
		/* 添加按钮到视图中 */
		rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(prev_btn));
	}

	/* 返回创建的视图 */
	return view;
}

/* 这个函数用于返回演示视图的对外可用区域 */
void demo_view_get_rect(rtgui_view_t* view, rtgui_rect_t *rect)
{
	RT_ASSERT(view != RT_NULL);
	RT_ASSERT(rect != RT_NULL);

	rtgui_widget_get_rect(RTGUI_WIDGET(view), rect);
	rtgui_widget_rect_to_device(RTGUI_WIDGET(view), rect);
	/* 去除演示标题和下方按钮的区域 */
	rect->y1 += 45;
	rect->y2 -= 35;
}

void demo_view_get_logic_rect(rtgui_view_t* view, rtgui_rect_t *rect)
{
	RT_ASSERT(view != RT_NULL);
	RT_ASSERT(rect != RT_NULL);

	rtgui_widget_get_rect(RTGUI_WIDGET(view), rect);
	/* 去除演示标题和下方按钮的区域 */
	rect->y1 += 45;
	rect->y2 -= 35;
}

/* 当是标准版本时，这个函数用于返回自动布局引擎box控件 */
#ifndef RTGUI_USING_SMALL_SIZE
rtgui_box_t* demo_view_create_box(rtgui_view_t* view, int orient)
{
	rtgui_rect_t rect;
	rtgui_box_t* box;

	/* 获得视图的位置信息 */
	rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);
	rect.y1 += 45;
	rect.y2 -= 25;

	/* 创建一个自动布局引擎 */
	box = rtgui_box_create(orient, &rect);
	/* 添加box控件到视图中 */
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(box));

	return box;
}
#endif

/* 这个函数用于显示当前的视图 */
void demo_view_show()
{
	if (demo_view_number != 0)
	{
		rtgui_view_show(demo_view_list[demo_view_current], RT_FALSE);
	}
}
