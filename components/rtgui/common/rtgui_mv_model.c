/*
 * File      : rtgui_mv_model.c
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

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/rtgui_object.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_mv_model.h>
#include <rtgui/widgets/mv_view.h>
#include <rtgui/widgets/window.h>

static void _rtgui_mv_model_bare_remove(struct rtgui_mv_model *model, struct rtgui_mv_view *view);
static void _rtgui_mv_view_bare_remove(struct rtgui_mv_view *view, struct rtgui_mv_model *model);
static rt_bool_t _rtgui_mv_model_notify_view(struct rtgui_mv_model *model,
        struct rtgui_mv_view  *view,
        struct rtgui_event_mv_model *emodel);

static void _rtgui_mv_model_constructor(struct rtgui_mv_model *model)
{
    model->dimension   = 0;
    model->length      = 0;
    model->data        = RT_NULL;
    model->view_number = 0;
    model->view        = RT_NULL;

    /* currently not interested in any event */
    rtgui_object_set_event_handler(RTGUI_OBJECT(model), RT_NULL);
}

static void _rtgui_mv_model_destructor(struct rtgui_mv_model *model)
{
    if (model->view_number == 1)
    {
        rtgui_mv_model_remove_view(model, model->view);
    }
    else if (model->view_number > 1)
    {
        int i;
        struct rtgui_mv_view **view_arr = (struct rtgui_mv_view **)(model)->view;

        for (i = 0; i < model->view_number; i++)
        {
            rtgui_mv_model_remove_view(model, view_arr[i]);
        }
    }

    if (model->dimension > 1)
        rtgui_free(model->data);
}

DEFINE_CLASS_TYPE(mv_model, "mv_model",
                  RTGUI_OBJECT_TYPE,
                  _rtgui_mv_model_constructor,
                  _rtgui_mv_model_destructor,
                  sizeof(struct rtgui_mv_model));

struct rtgui_mv_model *rtgui_mv_model_create(rt_uint16_t dimension)
{
    struct rtgui_mv_model *model;

    RT_ASSERT(dimension);

    model = RTGUI_MV_MODEL(rtgui_object_create(RTGUI_MV_MODEL_TYPE));
    if (model == RT_NULL)
        return RT_NULL;

    if (rtgui_mv_model_set_dimension(model, dimension) != RT_EOK)
    {
        rtgui_object_destroy(RTGUI_OBJECT(model));
        return RT_NULL;
    }

    return model;
}
RTM_EXPORT(rtgui_mv_model_create);

rt_err_t rtgui_mv_model_set_dimension(struct rtgui_mv_model *model, rt_uint16_t dimension)
{
    if (dimension == 1)
    {
        if (model->dimension > 1)
            rtgui_free(model->data);
        model->data = RT_NULL;
    }
    else
    {
        void *data;

        if (model->dimension > 1)
            rtgui_free(model->data);

        data = rtgui_malloc(sizeof(void *)*dimension);

        if (data == RT_NULL)
        {
            return -RT_ENOMEM;
        }

        rt_memset(data, 0, sizeof(void *)*dimension);
        model->data = data;
    }
    model->dimension = dimension;

    return RT_EOK;
}
RTM_EXPORT(rtgui_mv_model_set_dimension);

void rtgui_mv_model_destroy(struct rtgui_mv_model *model)
{
    rtgui_object_destroy(RTGUI_OBJECT(model));
}
RTM_EXPORT(rtgui_mv_model_destroy);

rt_err_t rtgui_mv_model_add_view(struct rtgui_mv_model *model, struct rtgui_mv_view *view)
{
    RT_ASSERT(model);

    if (view == RT_NULL)
        return RT_EOK;

    /* add view to model */
    if (model->view_number == 0)
    {
        model->view = view;
    }
    else if (model->view_number == 1)
    {
        /* create the array of view pointers */
        struct rtgui_mv_view **new_view;

        if (view == model->view)
            return RT_EOK;

        new_view = rtgui_malloc(2 * sizeof(struct rtgui_mv_view *));
        if (new_view == RT_NULL)
            return -RT_ENOMEM;

        new_view[0] = model->view;
        new_view[1] = view;
        model->view = new_view;
    }
    else
    {
        int i;
        struct rtgui_mv_view **new_view;
        struct rtgui_mv_view **view_arr = (struct rtgui_mv_view **)(model)->view;

        for (i = 0; i < model->view_number; i++)
        {
            if (view == view_arr[i])
                return RT_EOK;
        }

        new_view = rtgui_realloc(model->view,
                                 (model->view_number + 1) * sizeof(struct rtgui_mv_view *));

        if (new_view == RT_NULL)
            return -RT_ENOMEM;

        new_view[model->view_number] = view;
        model->view = new_view;
    }
    model->view_number++;

    /* add model to view. Roll back previous action on fail. */
    if (view->model_number == 0)
    {
        view->model = model;
    }
    else if (view->model_number == 1)
    {
        struct rtgui_mv_model **new_arr = rtgui_malloc(2 * sizeof(struct rtgui_mv_model *));

        if (new_arr == RT_NULL)
        {
            _rtgui_mv_model_bare_remove(model, view);
            return -RT_ENOMEM;
        }

        new_arr[0] = view->model;
        new_arr[1] = model;
        view->model = new_arr;
    }
    else
    {
        struct rtgui_mv_model **new_arr = rtgui_realloc(view->model,
                                          (view->model_number + 1) * sizeof(struct rtgui_mv_model *));

        if (new_arr == RT_NULL)
        {
            _rtgui_mv_model_bare_remove(model, view);
            return -RT_ENOMEM;
        }

        new_arr[view->model_number] = model;
        view->model = new_arr;
    }
    view->model_number++;

    return RT_EOK;
}
RTM_EXPORT(rtgui_mv_model_add_view);

static void _rtgui_mv_model_bare_remove(struct rtgui_mv_model *model, struct rtgui_mv_view *view)
{
    int i;

    if (model->view_number == 1)
    {
        if (model->view == view)
        {
            model->view_number--;
            model->view = RT_NULL;
        }
        return;
    }

    for (i = 0; i < model->view_number; i++)
    {
        struct rtgui_mv_view **view_arr = (struct rtgui_mv_view **)(model)->view;
        if (view == view_arr[i])
            break;
    }

    /* no match */
    if (i == model->view_number)
    {
        return;
    }
    else if (model->view_number == 2)
    {
        struct rtgui_mv_view **view_arr = (struct rtgui_mv_view **)(model)->view;
        struct rtgui_mv_view *the_view = view_arr[(i + 1) % 2];
        rtgui_free(model->view);
        model->view = the_view;
        model->view_number--;
        return;
    }
    else
    {
        struct rtgui_mv_view **view_arr = (struct rtgui_mv_view **)(model)->view;
        void *new_view;

        for (; i < model->view_number - 1; i++)
        {
            view_arr[i] = view_arr[i + 1];
        }

        new_view = rtgui_realloc(model->view,
                                 (model->view_number - 1) * sizeof(struct rtgui_mv_view *));

        /* no need to be panic on OOM error. The original array is still there
         * and we can operate it safely. So just ignore the NULL value returned
         * by realloc. */
        if (new_view != RT_NULL)
            model->view = new_view;

        model->view_number--;
        return;
    }
}

static void _rtgui_mv_view_bare_remove(struct rtgui_mv_view *view, struct rtgui_mv_model *model)
{
    int i;
    struct rtgui_mv_model **model_arr = (struct rtgui_mv_model **)(view)->model;

    if (view->model_number == 1)
    {
        if (view->model == model)
        {
            view->model_number--;
            view->model = RT_NULL;
        }
        return;
    }

    for (i = 0; i < view->model_number; i++)
    {
        if (model == model_arr[i])
            break;
    }

    /* no match */
    if (i == view->model_number)
    {
        return;
    }
    else if (view->model_number == 2)
    {
        struct rtgui_mv_model **model_arr = (struct rtgui_mv_model **)(view)->model;
        struct rtgui_mv_model *the_model = model_arr[(i + 1) % 2];
        rtgui_free(view->model);
        view->model = the_model;
        view->model_number--;
        return;
    }
    else
    {
        struct rtgui_mv_model **model_arr = (struct rtgui_mv_model **)(view)->model;
        void *new_model;

        for (; i < view->model_number - 1; i++)
        {
            model_arr[i] = model_arr[i + 1];
        }

        new_model = rtgui_realloc(view->model,
                                  (view->model_number - 1) * sizeof(struct rtgui_mv_model *));

        /* no need to be panic on OOM error. The original array is still there
         * and we can operate it safely. So just ignore the NULL value returned
         * by realloc. */
        if (new_model != RT_NULL)
            view->model = new_model;

        view->model_number--;
        return;
    }
}

void rtgui_mv_model_remove_view(struct rtgui_mv_model *model, struct rtgui_mv_view *view)
{
    RT_ASSERT(model);

    if (view == RT_NULL)
        return;

    if (model->length > 0)
    {
        struct rtgui_event_mv_model emodel;

        RTGUI_EVENT_MV_MODEL_DELETED_INIT(&emodel);
        emodel.first_data_changed_idx = 0;
        emodel.last_data_changed_idx = model->length;

        /* rtgui_mv_model_remove_view is to be called in thread context.
         * Besides, it is called by _rtgui_mv_view_destructor which means the
         * view will be invalid in the future. So we should call the event
         * handler immediately. */
        RTGUI_OBJECT(view)->event_handler(RTGUI_OBJECT(view), (struct rtgui_event *)&emodel);
    }

    _rtgui_mv_model_bare_remove(model, view);
    _rtgui_mv_view_bare_remove(view, model);
}
RTM_EXPORT(rtgui_mv_model_remove_view);

rt_bool_t rtgui_mv_model_has_view(struct rtgui_mv_model *model, struct rtgui_mv_view *view)
{
    RT_ASSERT(model);

    if (view == RT_NULL || model->view_number == 0)
        return RT_FALSE;

    if (model->view_number == 1)
    {
        return model->view == view;
    }
    else
    {
        int i;
        struct rtgui_mv_view **view_arr = (struct rtgui_mv_view **)(model)->view;

        for (i = 0; i < model->view_number; i++)
        {
            if (view == view_arr[i])
                return RT_TRUE;
        }
        return RT_FALSE;
    }
}
RTM_EXPORT(rtgui_mv_model_has_view);

void rtgui_mv_model_set_data(struct rtgui_mv_model *model, rt_uint16_t dim, void *p)
{
    RT_ASSERT(model);
    RT_ASSERT(dim < model->dimension);

    if (model->dimension == 1)
    {
        model->data = p;
        return;
    }
    else
    {
        void **d_arr = (void **)model->data;
        d_arr[dim] = p;
    }
}
RTM_EXPORT(rtgui_mv_model_set_data);

void *rtgui_mv_model_get_data(struct rtgui_mv_model *model, rt_uint16_t dim)
{
    RT_ASSERT(model);
    RT_ASSERT(dim < model->dimension);

    if (model->dimension == 1)
    {
        return model->data;
    }
    else
    {
        void **d_arr = (void **)model->data;
        return d_arr[dim];
    }
}
RTM_EXPORT(rtgui_mv_model_get_data);

static rt_bool_t _rtgui_mv_model_notify_view(struct rtgui_mv_model *model,
        struct rtgui_mv_view  *view,
        struct rtgui_event_mv_model *emodel)
{
    struct rtgui_app *target = RTGUI_WIDGET(view)->toplevel->app;
    emodel->model = model;
    emodel->view = view;
    return rtgui_send(target, (struct rtgui_event *)emodel, sizeof(*emodel));
}

void rtgui_mv_model_notify(struct rtgui_mv_model *model,
                           struct rtgui_event_mv_model *em)
{
    /* model and view may not be in the same thread. Actually, model may not
     * belong to any RTGUI thread. So we have to notify the views by sending
     * events to the thread directly. */

    if (model->view_number == 1)
    {
        struct rtgui_mv_view *view = (struct rtgui_mv_view *)model->view;
        _rtgui_mv_model_notify_view(model, view, em);
    }
    else
    {
        int i;
        struct rtgui_mv_view **view_arr = (struct rtgui_mv_view **)(model)->view;
        for (i = 0; i < model->view_number; i++)
        {
            _rtgui_mv_model_notify_view(model, view_arr[i], em);
        }
    }
}
RTM_EXPORT(rtgui_mv_model_notify);

