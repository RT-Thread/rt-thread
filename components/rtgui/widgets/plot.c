/*
 * File      : plot.c
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
#include <rtgui/widgets/plot_curve.h>

static void _rtgui_plot_constructor(struct rtgui_plot *plot)
{
    plot->base_x = plot->base_y = 0;
    plot->ptype = RTGUI_PLOT_TYPE_SCAN;
    plot->scale_x = plot->scale_y = 1;

    rtgui_object_set_event_handler(RTGUI_OBJECT(plot), rtgui_plot_event_handler);
}

static void _rtgui_plot_destructor(struct rtgui_plot *plot)
{
}

DEFINE_CLASS_TYPE(plot, "plot",
                  RTGUI_MV_VIEW_TYPE,
                  _rtgui_plot_constructor,
                  _rtgui_plot_destructor,
                  sizeof(struct rtgui_plot));

struct rtgui_plot *rtgui_plot_create(void)
{
    struct rtgui_plot *plot;

    plot = RTGUI_PLOT(rtgui_widget_create(RTGUI_PLOT_TYPE));

    return plot;
}
RTM_EXPORT(rtgui_plot_create);

void rtgui_plot_destroy(struct rtgui_plot *plot)
{
    rtgui_mv_view_destroy(RTGUI_MV_VIEW(plot));
}
RTM_EXPORT(rtgui_plot_destroy);

void rtgui_plot_set_base(struct rtgui_plot *plot,
                         rtgui_plot_curve_dtype x, rtgui_plot_curve_dtype y)
{
    plot->base_x = x;
    plot->base_y = y;
}
RTM_EXPORT(rtgui_plot_set_base);

rt_inline int _rtgui_plot_curve_calc_x(struct rtgui_plot *plot, rtgui_plot_curve_dtype x)
{
    return (x - plot->base_x) / plot->scale_x;
}

rt_inline int _rtgui_plot_curve_calc_y(struct rtgui_plot *plot, rtgui_plot_curve_dtype y, rt_uint16_t height)
{
    return height - (y - plot->base_y) / plot->scale_y;
}

static void _rtgui_plot_curve_onpaint(
    struct rtgui_dc *dc,
    struct rtgui_plot *plot,
    struct rtgui_plot_curve *curve,
    rt_uint16_t start_idx,
    rt_uint16_t stop_idx)
{
    struct rtgui_rect rect;
    rt_uint16_t height;
    int last_x, last_y;
    rtgui_color_t old_color;
    rtgui_plot_curve_dtype *x_data, *y_data;

    rtgui_dc_get_rect(dc, &rect);
    height = rtgui_rect_height(rect);

    old_color = RTGUI_DC_FC(dc);
    RTGUI_DC_FC(dc) = curve->color;

    x_data = rtgui_plot_curve_get_x(curve);
    y_data = rtgui_plot_curve_get_y(curve);
    if (x_data)
    {
        rt_size_t i;

        last_x = _rtgui_plot_curve_calc_x(plot, x_data[start_idx]);
        last_y = _rtgui_plot_curve_calc_y(plot, y_data[start_idx], height);
        for (i = start_idx + 1; i < stop_idx; i++)
        {
            int cur_x = _rtgui_plot_curve_calc_x(plot, x_data[i]);
            int cur_y = _rtgui_plot_curve_calc_y(plot, y_data[i], height);
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

        last_x = _rtgui_plot_curve_calc_x(plot, start_idx);
        last_y = _rtgui_plot_curve_calc_y(plot, y_data[start_idx], height);
        for (i = start_idx + 1; i < stop_idx; i++)
        {
            int cur_x = _rtgui_plot_curve_calc_x(plot, i);
            int cur_y = _rtgui_plot_curve_calc_y(plot, y_data[i], height);
            rtgui_dc_draw_line(dc,
                               last_x, last_y,
                               cur_x, cur_y);
            last_x = cur_x;
            last_y = cur_y;
        }
    }
    RTGUI_DC_FC(dc) = old_color;
}

static void _rtgui_plot_draw_curve(struct rtgui_plot *plot, struct rtgui_event *event)
{
    int i;
    struct rtgui_dc *dc;

    dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(plot));
    if (dc == RT_NULL)
        return;

    if (RTGUI_MV_VIEW(plot)->model_number == 1)
    {
        _rtgui_plot_curve_onpaint(dc, plot,
                                  RTGUI_PLOT_CURVE(RTGUI_MV_VIEW(plot)->model),
                                  0, RTGUI_MV_MODEL(RTGUI_MV_VIEW(plot)->model)->length);
    }
    else
    {
        void **curve_array = (void **)RTGUI_MV_VIEW(plot)->model;
        for (i = 0; i < RTGUI_MV_VIEW(plot)->model_number; i++)
        {
            _rtgui_plot_curve_onpaint(dc, plot,
                                      RTGUI_PLOT_CURVE(curve_array[i]),
                                      0, RTGUI_MV_MODEL(curve_array[i])->length);
        }
    }

    rtgui_dc_end_drawing(dc);
}

static void _rtgui_plot_update_scale(struct rtgui_plot *plot)
{
    struct rtgui_plot_curve *curve;
    struct rtgui_rect rect;
    rtgui_plot_curve_dtype max_x = 0;
    rtgui_plot_curve_dtype min_x = 0;
    rtgui_plot_curve_dtype max_y = 0;
    rtgui_plot_curve_dtype min_y = 0;
    rt_uint32_t iter = 0;

    rtgui_widget_get_rect(RTGUI_WIDGET(plot), &rect);

    curve = RTGUI_PLOT_CURVE(
                rtgui_mv_view_foreach_in_model(RTGUI_MV_VIEW(plot), &iter));
    max_x = curve->max_x;
    min_x = curve->min_x;
    max_y = curve->max_y;
    min_y = curve->min_y;

    while (curve)
    {
        if (curve->max_x > max_x)
            max_x = curve->max_x;
        if (curve->min_x < min_x)
            min_x = curve->min_x;
        if (curve->max_y > max_y)
            max_y = curve->max_y;
        if (curve->min_y < min_y)
            min_y = curve->min_y;

        curve = RTGUI_PLOT_CURVE(
                    rtgui_mv_view_foreach_in_model(RTGUI_MV_VIEW(plot), &iter));
    }

    plot->scale_x = (max_x - min_x + rtgui_rect_width(rect)) / rtgui_rect_width(rect);
    plot->scale_y = (max_y - min_y + rtgui_rect_height(rect)) / rtgui_rect_height(rect);
}

rt_bool_t rtgui_plot_ondraw(struct rtgui_plot *plot, struct rtgui_event *event)
{
    struct rtgui_dc *dc;
    struct rtgui_rect rect;

    dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(plot));
    if (dc == RT_NULL)
        return RT_FALSE;

    rtgui_widget_get_rect(RTGUI_WIDGET(plot), &rect);

    rtgui_dc_fill_rect(dc, &rect);

    _rtgui_plot_draw_curve(plot, event);

    rtgui_dc_end_drawing(dc);

    return RT_FALSE;
}

rt_bool_t rtgui_plot_onmvmodel(struct rtgui_plot *plot, struct rtgui_event *event)
{
    struct rtgui_event_mv_model *emodel = (struct rtgui_event_mv_model *)event;

    RT_ASSERT(plot);
    RT_ASSERT(event);

    switch (plot->ptype)
    {
    case RTGUI_PLOT_TYPE_SCAN:
        _rtgui_plot_update_scale(plot);
        rtgui_plot_ondraw(plot, event);
    case RTGUI_PLOT_TYPE_INCREMENTAL:
    {
        rt_uint16_t old_sc_x = plot->scale_x;
        rt_uint16_t old_sc_y = plot->scale_y;

        _rtgui_plot_update_scale(plot);

        if (old_sc_x != plot->scale_x || old_sc_y != plot->scale_y)
        {
            /* we need to repaint the whole widget as the scale changed. */
            rtgui_plot_ondraw(plot, event);
        }
        else
        {
            /* get dc for _rtgui_plot_curve_onpaint */
            struct rtgui_dc *dc;
            dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(plot));
            if (dc == RT_NULL)
                return RT_FALSE;

            /* only draw the newly recieved data */
            _rtgui_plot_curve_onpaint(dc, plot,
                                      RTGUI_PLOT_CURVE(emodel->model),
                                      emodel->first_data_changed_idx,
                                      emodel->last_data_changed_idx + 1);

            rtgui_dc_end_drawing(dc);
        }
    }
    return RT_TRUE;
    default:
        RT_ASSERT(0);
    }

    return RT_TRUE;
}

rt_bool_t rtgui_plot_event_handler(struct rtgui_object *object, struct rtgui_event *event)
{
    struct rtgui_plot *plot;

    RTGUI_WIDGET_EVENT_HANDLER_PREPARE;

    plot = RTGUI_PLOT(object);

    switch (event->type)
    {
    case RTGUI_EVENT_PAINT:
        _rtgui_plot_update_scale(RTGUI_PLOT(object));
        return rtgui_plot_ondraw(plot, event);
    case RTGUI_EVENT_MV_MODEL:
        return rtgui_plot_onmvmodel(plot, event);
    default:
        return rtgui_widget_event_handler(object, event);
    }
}
RTM_EXPORT(rtgui_plot_event_handler);

