/*
 * File      : plot.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-09-03     Grissiom     first version
 */

#include <rtgui/rtgui_system.h>
#include <rtgui/dc.h>
#include <rtgui/widgets/plot.h>

static void _rtgui_plot_constructor(struct rtgui_plot *plot)
{
    plot->base_point.x = plot->base_point.y = 0;
    plot->curve_container.curve = RT_NULL;
    plot->curve_container.next = RT_NULL;

    /* init widget and set event handler */
    rtgui_object_set_event_handler(RTGUI_OBJECT(plot), rtgui_plot_event_handler);
}

static void _free_curve_container_recursive(struct rtgui_plot_curve_container *cnt)
{
    if (!cnt)
        return;
    _free_curve_container_recursive(cnt->next);
    rtgui_free(cnt);
}

static void _rtgui_plot_destructor(struct rtgui_plot *plot)
{
    _free_curve_container_recursive(plot->curve_container.next);
}

DEFINE_CLASS_TYPE(plot, "plot",
                  RTGUI_WIDGET_TYPE,
                  _rtgui_plot_constructor,
                  _rtgui_plot_destructor,
                  sizeof(struct rtgui_plot));

struct rtgui_plot *rtgui_plot_create(struct rtgui_plot_curve *curve)
{
    struct rtgui_plot *plot;

    plot = (struct rtgui_plot *)rtgui_widget_create(RTGUI_PLOT_TYPE);
    plot->curve_container.curve = curve;

    return plot;
}
RTM_EXPORT(rtgui_plot_create);

void rtgui_plot_destroy(struct rtgui_plot *plot)
{
    rtgui_widget_destroy(RTGUI_WIDGET(plot));
}
RTM_EXPORT(rtgui_plot_destroy);

void rtgui_plot_set_base_point(struct rtgui_plot *plot, rt_uint16_t x, rt_uint16_t y)
{
    plot->base_point.x = x;
    plot->base_point.y = y;
}
RTM_EXPORT(rtgui_plot_set_base_point);

void rtgui_plot_append_curve(struct rtgui_plot *plot, struct rtgui_plot_curve *curve)
{
    struct rtgui_plot_curve_container *cur_cnt, *next_cnt;

    RT_ASSERT(plot);

    next_cnt = rtgui_malloc(sizeof(*next_cnt));
    next_cnt->curve = curve;
    next_cnt->next  = RT_NULL;

    cur_cnt = &plot->curve_container;
    while (cur_cnt->next)
    {
        cur_cnt = cur_cnt->next;
    }
    cur_cnt->next = next_cnt;
}
RTM_EXPORT(rtgui_plot_append_curve);

static void _rtgui_plot_curve_onpaint(
        struct rtgui_dc *dc,
        struct rtgui_plot_curve *curve,
        struct rtgui_point base)
{
    struct rtgui_rect rect;
    rt_uint16_t height;
    int last_x, last_y;
    rtgui_color_t old_color;

    rtgui_dc_get_rect(dc, &rect);
    height = rtgui_rect_height(rect);

    old_color = RTGUI_DC_FC(dc);
    RTGUI_DC_FC(dc) = curve->color;

    if (curve->x_data)
    {
        rt_size_t i;

        last_x = curve->x_data[0] + base.x;
        last_y = height - curve->y_data[0] - base.y;
        for (i = 1; i < curve->length; i++)
        {
            int cur_x = curve->x_data[i] + base.x;
            int cur_y = height - curve->y_data[i] - base.y;
            rtgui_dc_draw_line(dc,
                               last_x, last_y,
                               cur_x, cur_y);
            last_x = cur_x;
            last_y = cur_y;
        }
    }
    else
    {
        rt_size_t i;

        last_x = 0 + base.x;
        last_y = height - curve->y_data[0] - base.y;
        for (i = 1; i < curve->length; i++)
        {
            int cur_x = i + base.x;
            int cur_y = height - curve->y_data[i] - base.y;
            rtgui_dc_draw_line(dc,
                               last_x, last_y,
                               cur_x, cur_y);
            last_x = cur_x;
            last_y = cur_y;
        }
    }
    RTGUI_DC_FC(dc) = old_color;
}

static void _rtgui_plot_onpaint(struct rtgui_object *object, struct rtgui_event *event)
{
    struct rtgui_dc *dc;
    struct rtgui_rect rect;
    struct rtgui_plot *plot = RTGUI_PLOT(object);
    struct rtgui_plot_curve_container *cnt;

    dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(plot));
    if (dc == RT_NULL)
        return;
    rtgui_widget_get_rect(RTGUI_WIDGET(object), &rect);

    rtgui_dc_fill_rect(dc, &rect);

    for (cnt = &plot->curve_container; cnt; cnt = cnt->next)
    {
        _rtgui_plot_curve_onpaint(dc, cnt->curve, plot->base_point);
    }

    rtgui_dc_end_drawing(dc);
}

rt_bool_t rtgui_plot_event_handler(struct rtgui_object *object, struct rtgui_event *event)
{
    struct rtgui_plot *plot;
    RTGUI_WIDGET_EVENT_HANDLER_PREPARE;

    plot = RTGUI_PLOT(object);
    switch (event->type)
    {
    case RTGUI_EVENT_PAINT:
        _rtgui_plot_onpaint(object, event);
        break;
    default:
        return rtgui_widget_event_handler(object, event);
    }

    return RT_FALSE;
}
RTM_EXPORT(rtgui_plot_event_handler);

