/*
 * File      : mv_view.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-09-15     Grissiom     first version
 */
#ifndef __MV_VIEW_H__
#define __MV_VIEW_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/widget.h>

DECLARE_CLASS_TYPE(mv_view);

/** Gets the type of a mv_view */
#define RTGUI_MV_VIEW_TYPE       (RTGUI_TYPE(mv_view))
/** Casts the object to an mv_view */
#define RTGUI_MV_VIEW(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_MV_VIEW_TYPE, struct rtgui_mv_view))
/** Checks if the object is an mv_view */
#define RTGUI_IS_MV_VIEW(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_MV_VIEW_TYPE))

struct rtgui_mv_view
{
    struct rtgui_widget parent;
    rt_uint16_t model_number;
    /* if the model_number is 1, the model is the pointer to the model. If the
     * model_number is more than 1, model is a pointer to a array of pointers
     * to model. */
    void *model;
};

struct rtgui_mv_view *rtgui_mv_view_create(void);
void rtgui_mv_view_destroy(struct rtgui_mv_view *view);

struct rtgui_mv_model *rtgui_mv_view_foreach_in_model(struct rtgui_mv_view *view, rt_uint32_t *iter);

#endif /* end of include guard: __MV_VIEW_H__ */
