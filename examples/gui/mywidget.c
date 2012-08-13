#include <rtgui/dc.h>
#include "mywidget.h"

/* 控件绘图函数 */
static void rtgui_mywidget_ondraw(struct rtgui_mywidget *me)
{
    struct rtgui_dc *dc;
    struct rtgui_rect rect;
    rt_uint16_t x, y;

    /* 获得目标DC，开始绘�?*/
    dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(me));
    if (dc == RT_NULL) return;

    /* 获得窗口的尺�?*/
    rtgui_widget_get_rect(RTGUI_WIDGET(me), &rect);
    /* 绘制背景�?*/
    RTGUI_DC_BC(dc) = white;
    rtgui_dc_fill_rect(dc, &rect);

    /* 计算中心原点 */
    x = (rect.x2 + rect.x1) / 2;
    y = (rect.y2 + rect.y1) / 2;

    /* 绘制十字�?*/
    RTGUI_DC_FC(dc) = black;
    rtgui_dc_draw_hline(dc, rect.x1, rect.x2, y);
    rtgui_dc_draw_vline(dc, x, rect.y1, rect.y2);

    /* 根据状态绘制圆�?*/
    if (me->status == MYWIDGET_STATUS_ON)
        RTGUI_DC_FC(dc) = green;
    else
        RTGUI_DC_FC(dc) = red;
    rtgui_dc_fill_circle(dc, x, y, 5);

    /* 结束绘图 */
    rtgui_dc_end_drawing(dc);
    return;
}

/* 鼠标事件处理函数 */
static void rtgui_mywidget_onmouse(struct rtgui_mywidget *me, struct rtgui_event_mouse *mouse)
{
    struct rtgui_rect rect;
    rt_uint16_t x, y;

    /* 仅对鼠标抬起动作进行处理 */
    if (!(mouse->button & RTGUI_MOUSE_BUTTON_UP)) return;

    /* 获得控件的位�?*/
    rtgui_widget_get_rect(RTGUI_WIDGET(me), &rect);
    /* get_rect函数获得是控件的相对位置，而鼠标事件给出的坐标是绝对坐标，需要做一个转�?*/
    rtgui_widget_rect_to_device(RTGUI_WIDGET(me), &rect);

    /* 计算中心原点 */
    x = (rect.x2 + rect.x1) / 2;
    y = (rect.y2 + rect.y1) / 2;

    /* 比较鼠标坐标是否在圈�?*/
    if ((mouse->x < x + 5 && mouse->x > x - 5) &&
            (mouse->y < y + 5 && mouse->y > y - 5))
    {
        /* 更改控件状�?*/
        if (me->status & MYWIDGET_STATUS_ON) me->status = MYWIDGET_STATUS_OFF;
        else me->status = MYWIDGET_STATUS_ON;

        /* 刷新(重新绘制)控件 */
        rtgui_mywidget_ondraw(me);
    }
}

/* mywidget控件的事件处理函�?*/
rt_bool_t rtgui_mywidget_event_handler(struct rtgui_object *object, struct rtgui_event *event)
{
    /* 调用事件处理函数时，widget指针指向控件本身，所以先获得相应控件对象的指�?*/
    struct rtgui_mywidget *me = RTGUI_MYWIDGET(object);

    switch (event->type)
    {
    case RTGUI_EVENT_PAINT:
        /* 绘制事件，调用绘图函数绘�?*/
        rtgui_mywidget_ondraw(me);
        break;

    case RTGUI_EVENT_MOUSE_BUTTON:
        /* 鼠标事件 */
        rtgui_mywidget_onmouse(RTGUI_MYWIDGET(me), (struct rtgui_event_mouse *) event);
        break;

        /* 其他事件调用父类的事件处理函�?*/
    default:
        return rtgui_widget_event_handler(object, event);
    }

    return RT_FALSE;
}

/* 自定义控件的构造函�?*/
static void _rtgui_mywidget_constructor(rtgui_mywidget_t *mywidget)
{
    /* 默认这个控件接收聚焦 */
    RTGUI_WIDGET(mywidget)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
    /* 初始化控件并设置事件处理函数 */
    rtgui_object_set_event_handler(RTGUI_OBJECT(mywidget), rtgui_mywidget_event_handler);

    /* 初始状态时OFF */
    mywidget->status = MYWIDGET_STATUS_OFF;
}

DEFINE_CLASS_TYPE(mywidget, "mywidget",
                  RTGUI_WIDGET_TYPE,
                  _rtgui_mywidget_constructor,
                  RT_NULL,
                  sizeof(struct rtgui_mywidget));

/* 创建一个自定义控件 */
struct rtgui_mywidget *rtgui_mywidget_create(rtgui_rect_t *r)
{
    struct rtgui_mywidget *me;

    /* 让rtgui_widget创建出一个指定类型：RTGUI_MYWIDGET_TYPE类型的控�?*/
    me = (struct rtgui_mywidget *) rtgui_widget_create(RTGUI_MYWIDGET_TYPE);
    if (me != RT_NULL)
    {
        rtgui_widget_set_rect(RTGUI_WIDGET(me), r);
    }

    return me;
}

/* 删除一个自定义控件 */
void rtgui_mywidget_destroy(struct rtgui_mywidget *me)
{
    rtgui_widget_destroy(RTGUI_WIDGET(me));
}
