/*
 * File      : box.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 */
#include <rtgui/dc.h>
#include <rtgui/widgets/box.h>

static void _rtgui_box_constructor(rtgui_box_t *box)
{
    /* init widget and set event handler */
    rtgui_object_set_event_handler(RTGUI_OBJECT(box), RT_NULL);

    /* set proper of control */
    box->orient = RTGUI_HORIZONTAL;
    box->border_size = RTGUI_BORDER_DEFAULT_WIDTH;
    box->container = RT_NULL;
}

DEFINE_CLASS_TYPE(box, "box",
                  RTGUI_PARENT_TYPE(object),
                  _rtgui_box_constructor,
                  RT_NULL,
                  sizeof(struct rtgui_box));

struct rtgui_box *rtgui_box_create(int orientation, int border_size)
{
    struct rtgui_box *box;

    box = (struct rtgui_box *) rtgui_object_create(RTGUI_BOX_TYPE);
    if (box != RT_NULL)
    {
        box->orient = orientation;
        box->border_size = border_size;
    }

    return box;
}
RTM_EXPORT(rtgui_box_create);

void rtgui_box_destroy(struct rtgui_box *box)
{
    rtgui_object_destroy(RTGUI_OBJECT(box));
}
RTM_EXPORT(rtgui_box_destroy);

static void rtgui_box_layout_vertical(struct rtgui_box *box, struct rtgui_rect *extent)
{
    rtgui_list_t *node;
    rt_int32_t box_width;
    rt_int32_t space_count;
    rt_int32_t next_x, next_y;
    rt_int32_t total_height, space_height;
    struct rtgui_event_resize size_event;

    /* prepare the resize event */
    RTGUI_EVENT_RESIZE_INIT(&size_event);

    /* find spaces */
    space_count  = 0;
    total_height = box->border_size;
    space_height = 0;

    rtgui_list_foreach(node, &(box->container->children))
    {
        rtgui_widget_t *widget = rtgui_list_entry(node, struct rtgui_widget, sibling);
        if (widget->align & RTGUI_ALIGN_STRETCH)
        {
            space_count ++;
        }
        else
        {
            total_height += widget->min_height;
        }
        total_height += box->border_size;
    }

    /* calculate the height for each spaces */
    if (space_count != 0 && rtgui_rect_height(*extent) > total_height)
    {
        space_height = (rtgui_rect_height(*extent) - total_height) / space_count;
    }

    /* init (x, y) and box width */
    next_x = extent->x1 + box->border_size;
    next_y = extent->y1 + box->border_size;
    box_width = rtgui_rect_width(*extent) - box->border_size * 2;

    /* layout each widget */
    rtgui_list_foreach(node, &(box->container->children))
    {
        struct rtgui_rect *rect;
        rtgui_widget_t *widget = rtgui_list_entry(node, struct rtgui_widget, sibling);

        /* get extent of widget */
        rect = &(widget->extent);

        /* reset rect */
        rtgui_rect_init(rect, 0, 0, widget->min_width, widget->min_height);

        /* left in default */
        rtgui_rect_moveto(rect, next_x, next_y);

        if (widget->align & RTGUI_ALIGN_EXPAND)
        {
            /* expand on horizontal */
            rect->x2 = rect->x1 + (rt_int16_t)box_width;
        }
        if (widget->align & RTGUI_ALIGN_CENTER_VERTICAL)
        {
            /* center */
            rt_uint32_t mid;

            mid = box_width - rtgui_rect_width(*rect);
            mid = mid / 2;

            rect->x1 = next_x + mid;
            rect->x2 = next_x + box_width - mid;
        }
        else if (widget->align & RTGUI_ALIGN_RIGHT)
        {
            /* right */
            rect->x1 = next_x + box_width - rtgui_rect_width(*rect);
            rect->x2 = next_x + box_width;
        }

        if (widget->align & RTGUI_ALIGN_STRETCH)
        {
            rect->y2 = rect->y1 + space_height;
        }

        /* process resize event */
        size_event.x = rect->x1;
        size_event.y = rect->y1;
        size_event.w = rect->x2 - rect->x1;
        size_event.h = rect->y2 - rect->y1;
        RTGUI_OBJECT(widget)->event_handler(RTGUI_OBJECT(widget),
                                            &size_event.parent);

        /* point to next height */
        next_y = rect->y2 + box->border_size;
    }
}

static void rtgui_box_layout_horizontal(struct rtgui_box *box, struct rtgui_rect *extent)
{
    rtgui_list_t *node;
    rt_int32_t box_height;
    rt_int32_t space_count;
    rt_int32_t next_x, next_y;
    rt_int32_t total_width, space_width;
    struct rtgui_event_resize size_event;

    /* prepare the resize event */
    RTGUI_EVENT_RESIZE_INIT(&size_event);

    /* find spaces */
    space_count = 0;
    total_width = 0;
    space_width = 0;

    rtgui_list_foreach(node, &(box->container->children))
    {
        rtgui_widget_t *widget = rtgui_list_entry(node, struct rtgui_widget, sibling);
        if (widget->align & RTGUI_ALIGN_STRETCH)
        {
            space_count ++;
        }
        else
        {
            total_width += widget->min_width;
        }
        total_width += box->border_size;
    }

    if (space_count != 0)
    {
        /* calculate the height for each spaces */
        space_width = (rtgui_rect_width(*extent) - total_width) / space_count;
    }

    /* init (x, y) and box height */
    next_x = extent->x1 + box->border_size;
    next_y = extent->y1 + box->border_size;
    box_height = rtgui_rect_height(*extent) - (box->border_size << 1);

    /* layout each widget */
    rtgui_list_foreach(node, &(box->container->children))
    {
        rtgui_rect_t *rect;
        rtgui_widget_t *widget = rtgui_list_entry(node, struct rtgui_widget, sibling);

        /* get extent of widget */
        rect = &(widget->extent);

        /* reset rect */
        rtgui_rect_moveto(rect, -rect->x1, -rect->y1);
        rect->x2 = widget->min_width;
        rect->y2 = widget->min_height;

        /* top in default */
        rtgui_rect_moveto(rect, next_x, next_y);

        if (widget->align & RTGUI_ALIGN_EXPAND)
        {
            /* expand on vertical */
            rect->y2 = rect->y1 + box_height;
        }
        if (widget->align & RTGUI_ALIGN_CENTER_HORIZONTAL)
        {
            /* center */
            rt_uint32_t mid;

            mid = box_height - rtgui_rect_height(*rect);
            mid = mid / 2;

            rect->y1 = next_y + mid;
            rect->y2 = next_y + box_height - mid;
        }
        else if (widget->align & RTGUI_ALIGN_RIGHT)
        {
            /* right */
            rect->y1 = next_y + box_height - rtgui_rect_height(*rect);
            rect->y2 = next_y + box_height;
        }

        if (widget->align & RTGUI_ALIGN_STRETCH)
        {
            rect->x2 = rect->x1 + space_width;
        }

        /* process resize event */
        size_event.x = rect->x1;
        size_event.y = rect->y1;
        size_event.w = rect->x2 - rect->x1;
        size_event.h = rect->y2 - rect->y1;
        RTGUI_OBJECT(widget)->event_handler(RTGUI_OBJECT(widget),
                                            &size_event.parent);

        /* point to next width */
        next_x = rect->x2 + box->border_size;
    }
}

void rtgui_box_layout(rtgui_box_t *box)
{
    struct rtgui_rect extent;
    RT_ASSERT(box != RT_NULL);

    if (box->container == RT_NULL) return;

    rtgui_widget_get_extent(RTGUI_WIDGET(box->container), &extent);
    if (box->orient & RTGUI_VERTICAL)
    {
        rtgui_box_layout_vertical(box, &extent);
    }
    else
    {
        rtgui_box_layout_horizontal(box, &extent);
    }

    /* update box and its children clip */
    if (!RTGUI_WIDGET_IS_HIDE(RTGUI_WIDGET(box->container)))
    {
        rtgui_widget_update_clip(RTGUI_WIDGET(box->container));
    }
}
RTM_EXPORT(rtgui_box_layout);

void rtgui_box_layout_rect(rtgui_box_t *box, struct rtgui_rect *rect)
{
    RT_ASSERT(box != RT_NULL);

    if (box->container == RT_NULL) return;

    if (box->orient & RTGUI_VERTICAL)
    {
        rtgui_box_layout_vertical(box, rect);
    }
    else
    {
        rtgui_box_layout_horizontal(box, rect);
    }

    /* update box and its children clip */
    if (!RTGUI_WIDGET_IS_HIDE(RTGUI_WIDGET(box->container)))
    {
        rtgui_widget_update_clip(RTGUI_WIDGET(box->container));
    }
}
RTM_EXPORT(rtgui_box_layout_rect);

