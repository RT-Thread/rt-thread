/*
 * 程序清单：自定义控件
 *
 * 这个例子是要实现一个自定义控件，外观大致如
 *   |
 * --o--
 *   |
 * 的形状，中间的o色彩表示了当前的状态，ON状态时是绿色，OFF状态时是红色�?
 * 并且，这个o位置接受鼠标点击，点击下切换下相应的状态�?
 */
#ifndef __MY_WIDGET_H__
#define __MY_WIDGET_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/widget.h>

/* 自定义控件的状态值定�?*/
#define MYWIDGET_STATUS_ON	1
#define MYWIDGET_STATUS_OFF	0

DECLARE_CLASS_TYPE(mywidget);
/** 每个控件会有一个类型，通过如下的宏获得控件相应的类型信�?*/
#define RTGUI_MYWIDGET_TYPE       (RTGUI_TYPE(mywidget))
/** 对一个对象实例，可以通过下面的宏实现类型转换 */
#define RTGUI_MYWIDGET(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_MYWIDGET_TYPE, rtgui_mywidget_t))
/** 可以通过下面的宏以决定一个具体实例是否是自定义控件类�?*/
#define RTGUI_IS_MYWIDGET(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_MYWIDGET_TYPE))

/* 个性化控件类定�?*/
struct rtgui_mywidget
{
	/* 这个控件是继承自rtgui_widget控件 */
	struct rtgui_widget parent;

	/* 状态：ON、OFF */
	rt_uint8_t status;
};
typedef struct rtgui_mywidget rtgui_mywidget_t;

/* 控件的创建和删除 */
struct rtgui_mywidget* rtgui_mywidget_create(rtgui_rect_t* r);
void rtgui_mywidget_destroy(struct rtgui_mywidget* me);

/* 控件的默认事件处理函数�?
 * 对一个控件而言，如果派生自它的子控件很可能会调用父控件的事件处理函数，
 * 所以这里采用公开声明的方式�?
 */
rt_bool_t rtgui_mywidget_event_handler(struct rtgui_widget* widget, struct rtgui_event* event);

#endif
