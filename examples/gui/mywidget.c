#include <rtgui/dc.h>
#include "mywidget.h"

/* 控件绘图函数 */
static void rtgui_mywidget_ondraw(struct rtgui_mywidget* me)
{
	struct rtgui_dc* dc;
	struct rtgui_rect rect;
	rt_uint16_t x, y;

	/* 获得目标DC，开始绘图 */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(me));
	if (dc == RT_NULL) return;

	/* 获得窗口的尺寸 */
	rtgui_widget_get_rect(RTGUI_WIDGET(me), &rect);
	/* 绘制背景色 */
	rtgui_dc_set_color(dc, white);
	rtgui_dc_fill_rect(dc, &rect);

	/* 计算中心原点 */
	x = (rect.x2 + rect.x1)/2; y = (rect.y2 + rect.y1)/2;

	/* 绘制十字架 */
	rtgui_dc_set_color(dc, black);
	rtgui_dc_draw_hline(dc, rect.x1, rect.x2, y);
	rtgui_dc_draw_vline(dc, x, rect.y1, rect.y2);

	/* 根据状态绘制圆圈 */
	if (me->status == MYWIDGET_STATUS_ON)
		rtgui_dc_set_color(dc, green);
	else
		rtgui_dc_set_color(dc, red);
	rtgui_dc_fill_circle(dc, x, y, 5);

	/* 结束绘图 */
	rtgui_dc_end_drawing(dc);
	return;
}

/* 鼠标事件处理函数 */
static void rtgui_mywidget_onmouse(struct rtgui_mywidget* me, struct rtgui_event_mouse* mouse)
{
	struct rtgui_rect rect;
	rt_uint16_t x, y;

	/* 仅对鼠标抬起动作进行处理 */
	if (!(mouse->button & RTGUI_MOUSE_BUTTON_UP)) return;

	/* 获得控件的位置 */
	rtgui_widget_get_rect(RTGUI_WIDGET(me), &rect);
	/* get_rect函数获得是控件的相对位置，而鼠标事件给出的坐标是绝对坐标，需要做一个转换 */
	rtgui_widget_rect_to_device(RTGUI_WIDGET(me), &rect);

	/* 计算中心原点 */
	x = (rect.x2 + rect.x1)/2; y = (rect.y2 + rect.y1)/2;

	/* 比较鼠标坐标是否在圈内 */
	if ((mouse->x < x + 5 && mouse->x > x - 5) &&
		(mouse->y < y + 5 && mouse->y > y - 5))
	{
		/* 更改控件状态 */
		if (me->status & MYWIDGET_STATUS_ON) me->status = MYWIDGET_STATUS_OFF;
		else me->status = MYWIDGET_STATUS_ON;

		/* 刷新(重新绘制)控件 */
		rtgui_mywidget_ondraw(me);
	}
}

static rt_bool_t rtgui_mywidget_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_mywidget* me = (struct rtgui_mywidget*)widget;

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		/* 绘制事件，调用绘图函数绘制 */
		rtgui_mywidget_ondraw(me);
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		/* 鼠标事件 */
		rtgui_mywidget_onmouse(RTGUI_MYWIDGET(me), (struct rtgui_event_mouse*) event);
		break;

	/* 其他事件调用父类的事件处理函数 */
	default:
		rtgui_widget_event_handler(widget, event);
	}

	return RT_FALSE;
}

static void _rtgui_mywidget_constructor(rtgui_mywidget_t *mywidget)
{
	/* 初始化控件并设置事件处理函数 */
	RTGUI_WIDGET(mywidget)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	rtgui_widget_set_event_handler(RTGUI_WIDGET(mywidget), rtgui_mywidget_event_handler);

	mywidget->status = MYWIDGET_STATUS_OFF;
}

static void _rtgui_mywidget_destructor(rtgui_mywidget_t *mywidget)
{
}

rtgui_type_t *rtgui_mywidget_type_get(void)
{
	static rtgui_type_t *mywidget_type = RT_NULL;

	if (!mywidget_type)
	{
		mywidget_type = rtgui_type_create("mywidget", RTGUI_WIDGET_TYPE,
			sizeof(rtgui_mywidget_t),
			RTGUI_CONSTRUCTOR(_rtgui_mywidget_constructor),
			RTGUI_DESTRUCTOR(_rtgui_mywidget_destructor));
	}

	return mywidget_type;
}

struct rtgui_mywidget* rtgui_mywidget_create(rtgui_rect_t* r)
{
    struct rtgui_mywidget* me;

    me = (struct rtgui_mywidget*) rtgui_widget_create (RTGUI_MYWIDGET_TYPE);
    if (me != RT_NULL)
    {
		rtgui_widget_set_rect(RTGUI_WIDGET(me), r);
    }

	return me;
}

void rtgui_mywidget_destroy(struct rtgui_mywidget* me)
{
	rtgui_widget_destroy(RTGUI_WIDGET(me));
}
