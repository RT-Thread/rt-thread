#include <rtgui/rtgui.h>
#include <rtgui/rtgui_app.h>

#include <rtgui/widgets/container.h>
#include <rtgui/widgets/notebook.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/staticline.h>
#include <rtgui/widgets/box.h>

extern struct rtgui_notebook *the_notebook;

void demo_view_next(struct rtgui_object *object, struct rtgui_event *event)
{
    rtgui_notebook_set_current_by_index(the_notebook,
                                        (rtgui_notebook_get_current_index(the_notebook) + 1) %
                                        rtgui_notebook_get_count(the_notebook));
}

void demo_view_prev(struct rtgui_object *object, struct rtgui_event *event)
{
    rt_int16_t cur_idx = rtgui_notebook_get_current_index(the_notebook);

    if (cur_idx == 0)
        rtgui_notebook_set_current_by_index(the_notebook,
                                            rtgui_notebook_get_count(the_notebook) - 1);
    else
        rtgui_notebook_set_current_by_index(the_notebook,
                                            --cur_idx);
}

rtgui_container_t *demo_view(const char *title)
{
    struct rtgui_container  *container;
    struct rtgui_label      *label;
    struct rtgui_staticline *line;
    struct rtgui_button     *next_btn, *prev_btn;
    struct rtgui_rect       rect;

    container = rtgui_container_create();
    if (container == RT_NULL)
        return RT_NULL;

    rtgui_notebook_add(the_notebook, title, RTGUI_WIDGET(container));

    /* 获得视图的位置信息(在加入到 notebook 中时，notebook 会自动调整 container
     * 的大小) */
    rtgui_widget_get_rect(RTGUI_WIDGET(container), &rect);
    rtgui_widget_rect_to_device(RTGUI_WIDGET(container), &rect);
    rect.x1 += 5;
    rect.y1 += 5;
    rect.x2 = rect.x1 + rt_strlen(title)*8;
    rect.y2 = rect.y1 + 20;

    /* 创建标题用的标签 */
    label = rtgui_label_create(title);
    /* 设置标签位置信息 */
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    /* 添加标签到视图中 */
    rtgui_container_add_child(container, RTGUI_WIDGET(label));
	
	rtgui_widget_get_rect(RTGUI_WIDGET(container), &rect);
	rtgui_widget_rect_to_device(RTGUI_WIDGET(container), &rect);
    rect.y1 += 20 + 5;
    rect.y2 = rect.y1 + 2;
    /* 创建一个水平的 staticline 线 */
    line = rtgui_staticline_create(RTGUI_HORIZONTAL);
    /* 设置静态线的位置信息 */
    rtgui_widget_set_rect(RTGUI_WIDGET(line), &rect);
    /* 添加静态线到视图中 */
    rtgui_container_add_child(container, RTGUI_WIDGET(line));

    /* 获得视图的位置信息 */
    rtgui_widget_get_rect(RTGUI_WIDGET(container), &rect);
    rtgui_widget_rect_to_device(RTGUI_WIDGET(container), &rect);
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
    rtgui_container_add_child(container, RTGUI_WIDGET(next_btn));

    /* 获得视图的位置信息 */
    rtgui_widget_get_rect(RTGUI_WIDGET(container), &rect);
    rtgui_widget_rect_to_device(RTGUI_WIDGET(container), &rect);
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
    rtgui_container_add_child(container, RTGUI_WIDGET(prev_btn));

    /* 返回创建的视图 */
    return container;
}

/* 这个函数用于返回演示视图的对外可用区域 */
void demo_view_get_rect(rtgui_container_t *container, rtgui_rect_t *rect)
{
    RT_ASSERT(container != RT_NULL);
    RT_ASSERT(rect != RT_NULL);

    rtgui_widget_get_rect(RTGUI_WIDGET(container), rect);
    rtgui_widget_rect_to_device(RTGUI_WIDGET(container), rect);
    /* 去除演示标题和下方按钮的区域 */
    rect->y1 += 45;
    rect->y2 -= 35;
}

void demo_view_get_logic_rect(rtgui_container_t *container, rtgui_rect_t *rect)
{
    RT_ASSERT(container != RT_NULL);
    RT_ASSERT(rect != RT_NULL);

    rtgui_widget_get_rect(RTGUI_WIDGET(container), rect);
    /* 去除演示标题和下方按钮的区域 */
    rect->y1 += 45;
    rect->y2 -= 35;
}
