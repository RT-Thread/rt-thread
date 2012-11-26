/*
 * File      : rtgui_mv_model.h
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
#ifndef __RTGUI_MV_MODEL_H__
#define __RTGUI_MV_MODEL_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/mv_view.h>

DECLARE_CLASS_TYPE(mv_model);

/** Gets the type of a mv_model */
#define RTGUI_MV_MODEL_TYPE       (RTGUI_TYPE(mv_model))
/** Casts the object to an mv_model */
#define RTGUI_MV_MODEL(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_MV_MODEL_TYPE, struct rtgui_mv_model))
/** Checks if the object is an mv_model */
#define RTGUI_IS_MV_MODEL(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_MV_MODEL_TYPE))

struct rtgui_mv_model
{
    struct rtgui_object parent;

    rt_uint16_t dimension;
    rt_uint16_t view_number;
    /* the length of data */
    rt_uint16_t length;
    /* if the dimension is 1, the data is the pointer to the data. If the
     * dimension is more than 1, data is a pointer to a array of pointers to
     * data. */
    void *data;
    /* the content of view is like the content of data. If a model has more
     * then one view, view is pointed to an array of pointers to views. */
    void *view;
};

struct rtgui_mv_model *rtgui_mv_model_create(rt_uint16_t dimension);
void rtgui_mv_model_destroy(struct rtgui_mv_model *model);

rt_err_t rtgui_mv_model_set_dimension(struct rtgui_mv_model *model, rt_uint16_t dimension);
rt_err_t rtgui_mv_model_add_view(struct rtgui_mv_model *, struct rtgui_mv_view *);
void rtgui_mv_model_remove_view(struct rtgui_mv_model *, struct rtgui_mv_view *);

rt_bool_t rtgui_mv_model_has_view(struct rtgui_mv_model *model, struct rtgui_mv_view *view);
void rtgui_mv_model_set_data(struct rtgui_mv_model *model, rt_uint16_t dim, void *p);
void *rtgui_mv_model_get_data(struct rtgui_mv_model *model, rt_uint16_t dim);
void rtgui_mv_model_notify(struct rtgui_mv_model *model, struct rtgui_event_mv_model *em);

#endif /* end of include guard: __RTGUI_MV_MODEL_H__ */
