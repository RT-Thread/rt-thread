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
#ifndef __RTGUI_PLOT_H__
#define __RTGUI_PLOT_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/mv_view.h>
#include <rtgui/widgets/plot_curve.h>

DECLARE_CLASS_TYPE(plot);

/** Gets the type of a plot */
#define RTGUI_PLOT_TYPE       (RTGUI_TYPE(plot))
/** Casts the object to an rtgui_plot */
#define RTGUI_PLOT(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_PLOT_TYPE, struct rtgui_plot))
/** Checks if the object is an rtgui_plot */
#define RTGUI_IS_PLOT(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_PLOT_TYPE))

enum rtgui_plot_type
{
    RTGUI_PLOT_TYPE_SCAN,
    RTGUI_PLOT_TYPE_INCREMENTAL,
};

/*
 * the plot widget
 */
struct rtgui_plot
{
    struct rtgui_mv_view parent;

    enum rtgui_plot_type ptype;
    rt_uint16_t          scale_x;
    rt_uint16_t          scale_y;

    rtgui_plot_curve_dtype base_x;
    rtgui_plot_curve_dtype base_y;
};

struct rtgui_plot *rtgui_plot_create(void);
void rtgui_plot_destroy(struct rtgui_plot *plot);

void rtgui_plot_set_base(struct rtgui_plot *plot,
                         rtgui_plot_curve_dtype x, rtgui_plot_curve_dtype y);

rt_bool_t rtgui_plot_event_handler(struct rtgui_object *object, struct rtgui_event *event);

#endif
