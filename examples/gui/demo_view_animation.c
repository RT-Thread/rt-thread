#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/container.h>
#include "demo_view.h"

/*
 * 直接在DC上绘图以实现动画效果
 *
 * 动画是依赖于定时器驱动的，会上下翻滚显示文字
 * "飞线乱飞"
 */
static rt_int8_t dx = 1, dy = 1;
static rtgui_rect_t text_rect;
static rtgui_timer_t *timer;

void timeout(struct rtgui_timer *timer, void *parameter)
{
    struct rtgui_dc *dc;
    struct rtgui_rect rect;
    struct rtgui_widget *widget;

    /* 控件(container)通过parameter参数传递给定时器 */
    widget = RTGUI_WIDGET(parameter);

    /* 获得控件所属的DC */
    dc = rtgui_dc_begin_drawing(widget);
    if (dc == RT_NULL) /* 如果不能正常获得DC，返回（如果控件或父控件是隐藏状态，DC是获取不成功的） */
        return ;

    /* 获得demo container允许绘图的区域，主要用于判断边界 */
    demo_view_get_rect(RTGUI_CONTAINER(widget), &rect);
    rect.y2 -= 5;

    /* 判断是否是第一次绘图 */
    if ((text_rect.x1 == 0) && (text_rect.y1 == 0))
    {
        rtgui_rect_moveto(&text_rect, rect.x1, rect.y1);
    }
    else
    {
        /* 擦除老的文字 */
        rtgui_dc_fill_rect(dc, &text_rect);
    }

    /* 设置dx和dy */
    if (text_rect.x2 >= rect.x2) dx = -1;
    if (text_rect.x1 < rect.x1)  dx = 1;
    if (text_rect.y2 >= rect.y2) dy = -1;
    if (text_rect.y1 < rect.y1) dy = 1;

    /* 移动文本框的位置 */
    text_rect.x1 += dx;
    text_rect.x2 += dx;
    text_rect.y1 += dy;
    text_rect.y2 += dy;

    /* 绘图 */
    rtgui_dc_draw_text(dc, "飞线乱飞", &text_rect);

    /* 绘图完成 */
    rtgui_dc_end_drawing(dc);
}

static rt_bool_t animation_on_show(struct rtgui_object *object, struct rtgui_event *event)
{
    rt_kprintf("animation on show\n");
    if (timer != RT_NULL)
        rtgui_timer_start(timer);
    return RT_TRUE;
}

static rt_bool_t animation_on_hide(struct rtgui_object *object, struct rtgui_event *event)
{
    rt_kprintf("animation on hide\n");
    if (timer != RT_NULL)
        rtgui_timer_stop(timer);
    return RT_TRUE;
}

rt_bool_t animation_event_handler(struct rtgui_object *object, rtgui_event_t *event)
{
    struct rtgui_widget *widget = RTGUI_WIDGET(object);

    if (event->type == RTGUI_EVENT_PAINT)
    {
        struct rtgui_dc *dc;
        rtgui_rect_t rect;

        /* 因为用的是demo container，上面本身有一部分控件，所以在绘图时先要让demo container先绘图 */
        rtgui_container_event_handler(object, event);

        /* 获得控件所属的DC */
        dc = rtgui_dc_begin_drawing(widget);
        if (dc == RT_NULL) /* 如果不能正常获得DC，返回（如果控件或父控件是隐藏状态，DC是获取不成功的） */
            return RT_FALSE;

        /* 获得demo container允许绘图的区域 */
        demo_view_get_rect(RTGUI_CONTAINER(widget), &rect);

        /* 擦除所有 */
        rtgui_dc_fill_rect(dc, &rect);

        /* 绘图 */
        rtgui_dc_draw_text(dc, "飞线乱飞", &text_rect);

        /* 绘图完成 */
        rtgui_dc_end_drawing(dc);
    }
    else if (event->type == RTGUI_EVENT_SHOW)
    {
        rtgui_container_event_handler(object, event);
        animation_on_show(object, event);
    }
    else if (event->type == RTGUI_EVENT_HIDE)
    {
        rtgui_container_event_handler(object, event);
        animation_on_hide(object, event);
    }
    else
    {
        /* 调用默认的事件处理函数 */
        return rtgui_container_event_handler(object, event);
    }

    return RT_FALSE;
}

rtgui_container_t *demo_view_animation()
{
    rtgui_container_t *container;

    container = demo_view("DC 动画");
    if (container != RT_NULL)
        rtgui_object_set_event_handler(RTGUI_OBJECT(container), animation_event_handler);

    rtgui_font_get_metrics(RTGUI_WIDGET_FONT(container), "飞线乱飞", &text_rect);
    rtgui_rect_moveto(&text_rect, 0, 45);
    timer = rtgui_timer_create(2, RT_TIMER_FLAG_PERIODIC, timeout, (void *)container);

    return container;
}
