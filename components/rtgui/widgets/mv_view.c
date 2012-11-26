/*
 * File      : mv_view.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-09-17     Grissiom     first version
 */

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_mv_model.h>
#include <rtgui/widgets/mv_view.h>

static void _rtgui_mv_view_constructor(struct rtgui_mv_view *view)
{
    view->model_number = 0;
    view->model = RT_NULL;
}

static void _rtgui_mv_view_destructor(struct rtgui_mv_view *view)
{
    if (view->model_number == 1)
    {
        rtgui_mv_model_remove_view(view->model, view);
    }
    else if (view->model_number > 1)
    {
        void **model_arr = *(void ** *)view->model;
        int i;

        for (i = 0; i < view->model_number; i++)
        {
            rtgui_mv_model_remove_view(model_arr[i], view);
        }
    }
}

DEFINE_CLASS_TYPE(mv_view, "mv_view",
                  RTGUI_WIDGET_TYPE,
                  _rtgui_mv_view_constructor,
                  _rtgui_mv_view_destructor,
                  sizeof(struct rtgui_mv_view));

struct rtgui_mv_view *rtgui_mv_view_create(void)
{
    return RTGUI_MV_VIEW(rtgui_widget_create(RTGUI_MV_VIEW_TYPE));
}

void rtgui_mv_view_destroy(struct rtgui_mv_view *view)
{
    rtgui_widget_destroy(RTGUI_WIDGET(view));
}

struct rtgui_mv_model *rtgui_mv_view_foreach_in_model(struct rtgui_mv_view *view, rt_uint32_t *iter)
{
    struct rtgui_mv_model *model;

    RT_ASSERT(view);

    if (*iter >= view->model_number)
        return RT_NULL;

    if (view->model_number == 1)
    {
        model = view->model;
    }
    else
    {
        struct rtgui_mv_model **model_array = view->model;
        model = model_array[*iter];
    }

    (*iter)++;
    return model;
}

