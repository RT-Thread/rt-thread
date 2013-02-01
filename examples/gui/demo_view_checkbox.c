/*
 * 程序清单：checkbox控件演示
 *
 * 这个例子会在创建出的container上添加几个checkbox控件
 */

#include "demo_view.h"
#include <rtgui/widgets/checkbox.h>

/* 创建用于演示checkbox控件的视图 */
rtgui_container_t *demo_view_checkbox(void)
{
    rtgui_rect_t rect;
    rtgui_container_t *container;
    rtgui_checkbox_t *checkbox;
    rtgui_font_t *font;

    /* 先创建一个演示用的视图 */
    container = demo_view("CheckBox View");

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 100;
    rect.y1 += 5;
    rect.y2 = rect.y1 + 20;
    /* 创建一个checkbox控件 */
    checkbox = rtgui_checkbox_create("Red", RT_TRUE);
    /* 设置前景色为红色 */
    RTGUI_WIDGET_FOREGROUND(checkbox) = red;
    /* 设置checkbox的位置 */
    rtgui_widget_set_rect(RTGUI_WIDGET(checkbox), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(checkbox));

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 100;
    rect.y1 += 5 + 25;
    rect.y2 = rect.y1 + 20;
    /* 创建一个checkbox控件 */
    checkbox = rtgui_checkbox_create("Blue", RT_TRUE);
    /* 设置前景色为蓝色 */
    RTGUI_WIDGET_FOREGROUND(checkbox) = blue;
    /* 设置checkbox的位置 */
    rtgui_widget_set_rect(RTGUI_WIDGET(checkbox), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(checkbox));

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 100;
    rect.y1 += 5 + 25 + 25;
    rect.y2 = rect.y1 + 20;
    /* 创建一个checkbox控件 */
    checkbox = rtgui_checkbox_create("12 font", RT_TRUE);
    /* 设置字体为12点阵 */
    font = rtgui_font_refer("asc", 12);
    RTGUI_WIDGET_FONT(checkbox) = font;
    /* 设置checkbox的位置 */
    rtgui_widget_set_rect(RTGUI_WIDGET(checkbox), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(checkbox));

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 100;
    rect.y1 += 5 + 25 + 25 + 25;
    rect.y2 = rect.y1 + 20;
    /* 创建一个checkbox控件 */
    checkbox = rtgui_checkbox_create("16 font", RT_TRUE);
    /* 设置字体为16点阵 */
    font = rtgui_font_refer("asc", 16);
    RTGUI_WIDGET_FONT(checkbox) = font;
    /* 设置checkbox的位置 */
    rtgui_widget_set_rect(RTGUI_WIDGET(checkbox), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(checkbox));

    return container;
}
