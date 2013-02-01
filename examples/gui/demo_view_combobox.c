/*
 * 程序清单：label控件演示
 *
 * 这个例子会在创建出的container上添加几个不同类型的label控件
 */
#include "demo_view.h"
#include <rtgui/widgets/combobox.h>

struct rtgui_listbox_item items[] =
{
    {"item 1", RT_NULL},
    {"item 2", RT_NULL},
    {"item 3", RT_NULL},
    {"item 4", RT_NULL},
    {"item 5", RT_NULL},
};

/* 创建用于演示combobox控件的视图 */
rtgui_container_t *demo_view_combobox(void)
{
    rtgui_rect_t rect;
    rtgui_container_t *container;
    rtgui_combobox_t *box;

    /* 先创建一个演示用的视图 */
    container = demo_view("ComboBox View");

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 -= 5;
    rect.y1 += 5;
    rect.y2 = rect.y1 + 20;
    /* 创建一个label控件 */
    box = rtgui_combobox_create(items, sizeof(items) / sizeof(items[0]), &rect);
    /* container是一个container控件，调用add_child方法添加这个box控件 */
    rtgui_container_add_child(container, RTGUI_WIDGET(box));

    return container;
}
