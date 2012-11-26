/*
 * File      : plot_curve.h
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
#ifndef __RTGUI_PLOT_CURVE_H__
#define __RTGUI_PLOT_CURVE_H__

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_mv_model.h>

DECLARE_CLASS_TYPE(plot_curve);

/** Gets the type of a plot_curve */
#define RTGUI_PLOT_CURVE_TYPE       (RTGUI_TYPE(plot_curve))
/** Casts the object to an rtgui_plot */
#define RTGUI_PLOT_CURVE(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_PLOT_CURVE_TYPE, struct rtgui_plot_curve))
/** Checks if the object is an rtgui_plot */
#define RTGUI_IS_PLOT_CURVE(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_PLOT_CURVE_TYPE))

/* change this if you want to use other type of data.
 * For example, rt_uint8_t or rt_uint32_t. */
#define rtgui_plot_curve_dtype rt_int16_t

struct rtgui_plot_curve
{
    struct rtgui_mv_model parent;

    rtgui_color_t color;

    rtgui_plot_curve_dtype min_x, max_x;
    rtgui_plot_curve_dtype min_y, max_y;
};

struct rtgui_plot_curve *rtgui_plot_curve_create(void);
void rtgui_plot_curve_destroy(struct rtgui_plot_curve *curve);

void rtgui_plot_curve_set_x(struct rtgui_plot_curve *curve, void *p);
void *rtgui_plot_curve_get_x(struct rtgui_plot_curve *curve);
void rtgui_plot_curve_set_y(struct rtgui_plot_curve *curve, void *p);
void *rtgui_plot_curve_get_y(struct rtgui_plot_curve *curve);

#endif
