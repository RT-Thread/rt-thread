/*
 * 程序清单：label控件演示
 *
 * 这个例子会在创建出的container上添加几个不同类型的label控件
 */
#include "demo_view.h"
#include <rtgui/widgets/label.h>

/* 创建用于演示label控件的视图 */
rtgui_container_t *demo_view_label(void)
{
    rtgui_rect_t rect;
    rtgui_container_t *container;
    rtgui_label_t *label;
    rtgui_font_t *font;

    /* 先创建一个演示用的视图 */
    container = demo_view("Label View");

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 -= 5;
    rect.y1 += 5;
    rect.y2 = rect.y1 + 20;
    /* 创建一个label控件 */
    label = rtgui_label_create("Red Left");
    /* 设置label控件上的文本对齐方式为：左对齐 */
    RTGUI_WIDGET_TEXTALIGN(label) = RTGUI_ALIGN_LEFT;
    /* 设置label控件的前景色为红色 */
    RTGUI_WIDGET_FOREGROUND(label) = red;
    /* 设置label的位置 */
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    /* container是一个container控件，调用add_child方法添加这个label控件 */
    rtgui_container_add_child(container, RTGUI_WIDGET(label));

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 -= 5;
    rect.y1 += 5 + 25;
    rect.y2 = rect.y1 + 20;
    /* 创建一个label控件 */
    label = rtgui_label_create("Blue Right");
    /* 设置label控件上的文本对齐方式为：右对齐 */
    RTGUI_WIDGET_TEXTALIGN(label) = RTGUI_ALIGN_RIGHT;
    /* 设置label控件的前景色为蓝色 */
    RTGUI_WIDGET_FOREGROUND(label) = blue;
    /* 设置label的位置 */
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    /* container是一个container控件，调用add_child方法添加这个label控件 */
    rtgui_container_add_child(container, RTGUI_WIDGET(label));

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 -= 5;
    rect.y1 += 5 + 25 + 25;
    rect.y2 = rect.y1 + 20;
    /* 创建一个label控件 */
    label = rtgui_label_create("Green Center");
    /* 设置label控件的前景色为绿色 */
    RTGUI_WIDGET_FOREGROUND(label) = green;
    /* 设置label控件上的文本对齐方式为：右对齐 */
    RTGUI_WIDGET_TEXTALIGN(label) = RTGUI_ALIGN_CENTER_HORIZONTAL;
    /* 设置label的位置 */
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    /* container是一个container控件，调用add_child方法添加这个label控件 */
    rtgui_container_add_child(container, RTGUI_WIDGET(label));

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.x2 -= 5;
    rect.y1 += 5 + 25 + 25 + 25;
    rect.y2 = rect.y1 + 20;
    /* 创建一个label控件 */
    label = rtgui_label_create("12 font");
    /* 设置字体为12点阵的asc字体 */
    font = rtgui_font_refer("asc", 12);
    RTGUI_WIDGET_FONT(label) = font;
    /* 设置label的位置 */
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    /* container是一个container控件，调用add_child方法添加这个label控件 */
    rtgui_container_add_child(container, RTGUI_WIDGET(label));

    /* 获得视图的位置信息 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 5;
    rect.y1 += 5 + 25 + 25 + 25 + 25;
    rect.y2 = rect.y1 + 20;
    /* 创建一个label控件 */
    label = rtgui_label_create("16 font");
    /* 设置字体为16点阵的asc字体 */
    font = rtgui_font_refer("asc", 16);
    RTGUI_WIDGET_FONT(label) = font;
    /* 设置label的位置 */
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    /* container是一个container控件，调用add_child方法添加这个label控件 */
    rtgui_container_add_child(container, RTGUI_WIDGET(label));

    return container;
}

