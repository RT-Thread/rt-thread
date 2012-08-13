/*
 * 程序清单：menu控件演示
 *
 * 这个例子会在创建出的container上添加几个不同类型的label控件
 */
#include "demo_view.h"
#include <rtgui/widgets/menu.h>
#include <rtgui/widgets/button.h>

static rt_bool_t _onmenuitem(struct rtgui_object *object, struct rtgui_event *event)
{
    rt_kprintf("menu action!!\n");
    return RT_TRUE;
}

static const rtgui_menu_item_t sub_items[] =
{
    {RTGUI_ITEM_NORMAL, "item #1", RT_NULL, RT_NULL, 0, _onmenuitem},
    {RTGUI_ITEM_NORMAL, "item #2", RT_NULL, RT_NULL, 0, RT_NULL},
    {RTGUI_ITEM_SEPARATOR, RT_NULL, RT_NULL, RT_NULL, 0, RT_NULL},
    {RTGUI_ITEM_NORMAL, "item #3", RT_NULL, RT_NULL, 0, RT_NULL},
};
static const rtgui_menu_item_t items[] =
{
    {RTGUI_ITEM_NORMAL, "item #1", RT_NULL, RT_NULL, 0, RT_NULL},
    {RTGUI_ITEM_NORMAL, "item #2", RT_NULL, RT_NULL, 0, RT_NULL},
    {RTGUI_ITEM_SEPARATOR, RT_NULL, RT_NULL, RT_NULL, 0, RT_NULL},
    {
        RTGUI_ITEM_SUBMENU, "item #3", RT_NULL,
        (struct rtgui_menu_item_t *)sub_items,
        sizeof(sub_items) / sizeof(sub_items[0]), RT_NULL
    },
};
static rtgui_menu_t *menu;

static rt_bool_t _onmenu(struct rtgui_object *object, struct rtgui_event *event)
{
    rtgui_rect_t rect;

    rtgui_widget_get_rect(RTGUI_WIDGET(object), &rect);
    rtgui_widget_rect_to_device(RTGUI_WIDGET(object), &rect);

    if (menu != RT_NULL)
        rtgui_menu_pop(menu, rect.x1, rect.y2 + 5);

    return RT_TRUE;
}

/* 创建用于演示menu控件的视图 */
rtgui_container_t *demo_view_menu(void)
{
    rtgui_rect_t rect;
    rtgui_container_t *container;
    rtgui_button_t *button;

    /* 先创建一个演示用的视图 */
    container = demo_view("MENU View");

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 100;
    rect.y1 += 5;
    rect.y2 = rect.y1 + 20;
    /* 创建一个button控件 */
    button = rtgui_button_create("Pop Menu");
    /* 设置button的位置 */
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    /* container是一个container控件，调用add_child方法添加这个button控件 */
    rtgui_container_add_child(container, RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, _onmenu);

    menu = rtgui_menu_create("Menu Test", RT_NULL, items, sizeof(items) / sizeof(items[0]));

    return container;
}
