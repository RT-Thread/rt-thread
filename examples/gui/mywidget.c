#include <rtgui/dc.h>
#include "mywidget.h"

static void rtgui_mywidget_ondraw(struct rtgui_mywidget *me)
{
    struct rtgui_dc *dc;
    struct rtgui_rect rect;
    rt_uint16_t x, y;

    dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(me));
    if (dc == RT_NULL) return;

    rtgui_widget_get_rect(RTGUI_WIDGET(me), &rect);
    RTGUI_DC_BC(dc) = white;
    rtgui_dc_fill_rect(dc, &rect);

    x = (rect.x2 + rect.x1) / 2;
    y = (rect.y2 + rect.y1) / 2;

    RTGUI_DC_FC(dc) = black;
    rtgui_dc_draw_hline(dc, rect.x1, rect.x2, y);
    rtgui_dc_draw_vline(dc, x, rect.y1, rect.y2);

    if (me->status == MYWIDGET_STATUS_ON)
        RTGUI_DC_FC(dc) = green;
    else
        RTGUI_DC_FC(dc) = red;
    rtgui_dc_fill_circle(dc, x, y, 5);

    rtgui_dc_end_drawing(dc);
    return;
}

static void rtgui_mywidget_onmouse(struct rtgui_mywidget *me, struct rtgui_event_mouse *mouse)
{
    struct rtgui_rect rect;
    rt_uint16_t x, y;

    if (!(mouse->button & RTGUI_MOUSE_BUTTON_UP)) return;

    rtgui_widget_get_rect(RTGUI_WIDGET(me), &rect);
    rtgui_widget_rect_to_device(RTGUI_WIDGET(me), &rect);

    x = (rect.x2 + rect.x1) / 2;
    y = (rect.y2 + rect.y1) / 2;

    if ((mouse->x < x + 5 && mouse->x > x - 5) &&
            (mouse->y < y + 5 && mouse->y > y - 5))
    {
        if (me->status & MYWIDGET_STATUS_ON) me->status = MYWIDGET_STATUS_OFF;
        else me->status = MYWIDGET_STATUS_ON;

        rtgui_mywidget_ondraw(me);
    }
}

rt_bool_t rtgui_mywidget_event_handler(struct rtgui_object *object, struct rtgui_event *event)
{
    struct rtgui_mywidget *me = RTGUI_MYWIDGET(object);

    switch (event->type)
    {
    case RTGUI_EVENT_PAINT:
        rtgui_mywidget_ondraw(me);
        break;

    case RTGUI_EVENT_MOUSE_BUTTON:
        rtgui_mywidget_onmouse(RTGUI_MYWIDGET(me), (struct rtgui_event_mouse *) event);
        break;

    default:
        return rtgui_widget_event_handler(object, event);
    }

    return RT_FALSE;
}

static void _rtgui_mywidget_constructor(rtgui_mywidget_t *mywidget)
{
    RTGUI_WIDGET(mywidget)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
    rtgui_object_set_event_handler(RTGUI_OBJECT(mywidget), rtgui_mywidget_event_handler);

    mywidget->status = MYWIDGET_STATUS_OFF;
}

DEFINE_CLASS_TYPE(mywidget, "mywidget",
                  RTGUI_WIDGET_TYPE,
                  _rtgui_mywidget_constructor,
                  RT_NULL,
                  sizeof(struct rtgui_mywidget));

struct rtgui_mywidget *rtgui_mywidget_create(rtgui_rect_t *r)
{
    struct rtgui_mywidget *me;

    me = (struct rtgui_mywidget *) rtgui_widget_create(RTGUI_MYWIDGET_TYPE);
    if (me != RT_NULL)
    {
        rtgui_widget_set_rect(RTGUI_WIDGET(me), r);
    }

    return me;
}

void rtgui_mywidget_destroy(struct rtgui_mywidget *me)
{
    rtgui_widget_destroy(RTGUI_WIDGET(me));
}
