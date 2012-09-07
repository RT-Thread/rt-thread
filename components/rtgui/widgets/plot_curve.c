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

#include <rtgui/color.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/plot_curve.h>

static void _rtgui_plot_curve_constructor(struct rtgui_plot_curve *curve)
{
    curve->length = 0;
    curve->x_data = curve->y_data = RT_NULL;
    curve->color = red;

    /* init widget and set event handler */
    rtgui_object_set_event_handler(RTGUI_OBJECT(curve), RT_NULL);
}

static void _rtgui_plot_curve_destructor(struct rtgui_plot_curve *curve)
{
    /* nothing to do so far. */
}

DEFINE_CLASS_TYPE(plot_curve, "plot_curve",
                  RTGUI_OBJECT_TYPE,
                  _rtgui_plot_curve_constructor,
                  _rtgui_plot_curve_destructor,
                  sizeof(struct rtgui_plot_curve));

struct rtgui_plot_curve *rtgui_plot_curve_create(void)
{
    return (struct rtgui_plot_curve*)rtgui_object_create(RTGUI_PLOT_CURVE_TYPE);
}
RTM_EXPORT(rtgui_plot_curve_create);

void rtgui_plot_curve_destroy(struct rtgui_plot_curve *curve)
{
    rtgui_object_destroy(RTGUI_OBJECT(curve));
}
RTM_EXPORT(rtgui_plot_curve_destroy);

