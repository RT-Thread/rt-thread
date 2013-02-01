/*
 * 程序清单：自定义控件演示
 *
 * 这个例子会在创建出的container上添加两个自定义控件
 */
#include "demo_view.h"
#include "mywidget.h"

/* 创建用于演示自定义控件的视图 */
rtgui_container_t *demo_view_mywidget(void)
{
    rtgui_container_t *container;
    rtgui_rect_t rect;
    rtgui_mywidget_t *mywidget;

    /* 先创建一个演示用的视图 */
    container = demo_view("MyWidget View");

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 = rect.y1 + 80;
    rect.y1 += 5;
    rect.y2 = rect.y1 + 80;
    /* 创建一个自定义控件 */
    mywidget = rtgui_mywidget_create(&rect);
    /* container是一个container控件，调用add_child方法添加这个自控件 */
    rtgui_container_add_child(container, RTGUI_WIDGET(mywidget));

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 25;
    rect.x2 = rect.y1 + 40;
    rect.y1 += 5 + 100;
    rect.y2 = rect.y1 + 40;
    /* 创建一个自定义控件 */
    mywidget = rtgui_mywidget_create(&rect);
    /* container是一个container控件，调用add_child方法添加这个自控件 */
    rtgui_container_add_child(container, RTGUI_WIDGET(mywidget));

    return container;
}
