/*
 * 程序清单：button控件演示
 *
 * 这个例子会在创建出的container上添加几个不同类型的button控件
 */

#include "demo_view.h"
#include <rtgui/widgets/button.h>

/* 创建用于演示button控件的视图 */
rtgui_container_t *demo_view_button(void)
{
    rtgui_rect_t rect;
    rtgui_container_t *container;
    rtgui_button_t *button;
    rtgui_font_t *font;

    /* 先创建一个演示用的视图 */
    container = demo_view("Button View");

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 100;
    rect.y1 += 5;
    rect.y2 = rect.y1 + 20;
    /* 创建一个button控件 */
    button = rtgui_button_create("Red");
    /* 设置label控件的前景色为红色 */
    RTGUI_WIDGET_FOREGROUND(button) = red;
    /* 设置button的位置 */
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(button));

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 100;
    rect.y1 += 5 + 25;
    rect.y2 = rect.y1 + 20;
    /* 创建一个button控件 */
    button = rtgui_button_create("Blue");
    /* 设置label控件的前景色为蓝色 */
    RTGUI_WIDGET_FOREGROUND(button) = blue;
    /* 设置button的位置 */
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(button));

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 100;
    rect.y1 += 5 + 25 + 25;
    rect.y2 = rect.y1 + 20;
    /* 创建一个button控件 */
    button = rtgui_button_create("12 font");
    /* 设置字体为12点阵的asc字体 */
    font = rtgui_font_refer("asc", 12);
    RTGUI_WIDGET_FONT(button) = font;
    /* 设置button的位置 */
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(button));

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 100;
    rect.y1 += 5 + 25 + 25 + 25;
    rect.y2 = rect.y1 + 20;
    /* 创建一个button控件 */
    button = rtgui_button_create("16 font");
    /* 设置字体为16点阵的asc字体 */
    font = rtgui_font_refer("asc", 16);
    RTGUI_WIDGET_FONT(button) = font;
    /* 设置button的位置 */
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(button));

    return container;
}
