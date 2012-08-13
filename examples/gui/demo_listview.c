/*
 * 程序清单：列表视图演示
 *
 * 这个例子会先创建出一个演示用的container，当点击上面的按钮时会按照模式显示的形式显示
 * 新的列表视图
 */
#include "demo_view.h"
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/list_view.h>

static struct rtgui_application *application = RT_NULL;
static rtgui_list_view_t *_view = RT_NULL;
// static rtgui_image_t* return_image = RT_NULL;

/* 列表项的动作函数 */
static void listitem_action(rtgui_widget_t *widget, void *parameter)
{
    char label_text[32];
    rtgui_win_t *win;
    rtgui_label_t *label;
    rtgui_rect_t rect = {0, 0, 150, 80};
    int no = (int)parameter;

    rtgui_rect_moveto(&rect, 20, 50);

    /* 显示消息窗口 */
    win = rtgui_win_create(RTGUI_TOPLEVEL(application),
                           "窗口", &rect, RTGUI_WIN_STYLE_DEFAULT);

    rect.x1 += 20;
    rect.x2 -= 5;
    rect.y1 += 5;
    rect.y2 = rect.y1 + 20;

    /* 添加相应的标签 */
    rt_sprintf(label_text, "动作 %d", no);
    label = rtgui_label_create(label_text);

    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(win, RTGUI_WIDGET(label));

    /* 非模态显示窗口 */
    rtgui_win_show(win, RT_FALSE);
}

/* 返回功能的动作函数 */
static void return_action(rtgui_widget_t *widget, void *parameter)
{
    rtgui_container_end_modal(RTGUI_CONTAINER(_view), RTGUI_MODAL_OK);
}

/* 各个列表项定义 */
static struct rtgui_list_item items[] =
{
    {"列表项1", RT_NULL, listitem_action, (void *)1},
    {"列表项2", RT_NULL, listitem_action, (void *)2},
    {"列表项3", RT_NULL, listitem_action, (void *)3},
    {"列表项4", RT_NULL, listitem_action, (void *)4},
    {"列表项5", RT_NULL, listitem_action, (void *)5},
    {"返回",    RT_NULL, return_action,    RT_NULL},
};

/* 打开列表视图用的按钮触发函数 */
static void open_btn_onbutton(rtgui_widget_t *widget, struct rtgui_event *event)
{
    rtgui_rect_t rect;

    /* 获得顶层的application */
    application = RTGUI_APPLICATION(rtgui_widget_get_toplevel(widget));
    rtgui_widget_get_rect(RTGUI_WIDGET(application), &rect);

    /* 创建一个列表视图， 项指定为items */
    _view = rtgui_list_view_create(items, sizeof(items) / sizeof(struct rtgui_list_item),
                                   &rect, RTGUI_LIST_VIEW_LIST);

    rtgui_application_add_container(application, RTGUI_CONTAINER(_view));

    /* 模式显示视图 */
    rtgui_container_show(RTGUI_CONTAINER(_view), RT_TRUE);
    rtgui_container_destroy(RTGUI_CONTAINER(_view));
    _view = RT_NULL;
}

/* 创建用于演示列表视图的视图 */
rtgui_container_t *demo_listview_view(void)
{
    rtgui_rect_t rect;
    rtgui_container_t *container;
    rtgui_button_t *open_btn;

    container = demo_view("列表视图演示");

    /* 添加动作按钮 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 80;
    rect.y1 += 30;
    rect.y2 = rect.y1 + 20;
    open_btn = rtgui_button_create("打开列表");
    rtgui_container_add_child(container, RTGUI_WIDGET(open_btn));
    rtgui_widget_set_rect(RTGUI_WIDGET(open_btn), &rect);
    rtgui_button_set_onbutton(open_btn, open_btn_onbutton);

    return container;
}
