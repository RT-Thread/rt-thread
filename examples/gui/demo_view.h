/*
 * 程序清单：view演示
 *
 * 这是一个视图的演示，也是为了配合整个GUI演示而制作的视图，或者说，其他大多数控件的演示
 * 都是采用，先创建一个demo_view（演示视图），然后再在这个演示视图上添加相应的控件。
 *
 * 这个演示视图默认上方带一个演示标题，下方带两个按钮，点击它切换到前一个视图或后一个视图。
 * 针对控件演示而言，这个演示视图最重要的是提供了一个可显示的区域，只需要在这块区域上添加
 * 控件即可达到演示的目的。
 *
 * 获得这个显示区域的函数是：
 * demo_view_get_rect函数。
 */
#ifndef __DEMO_VIEW_H__
#define __DEMO_VIEW_H__

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/widgets/container.h>

/* 如果是标准版本，可以启用box自动布局引擎 */
#ifndef RTGUI_USING_SMALL_SIZE
#include <rtgui/widgets/box.h>
#endif

/* 创建一个演示视图，需要给出这个视图的演示标题 */
rtgui_container_t *demo_view(const char *title);
/* 获得演示视图提供给演示控件用的区域信息 */
void demo_view_get_rect(rtgui_container_t *view, rtgui_rect_t *rect);
void demo_view_get_logic_rect(rtgui_container_t *view, rtgui_rect_t *rect);
void demo_view_show(void);

#endif

