/*
 * File      : list_view.c
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-01-06     Bernard      first version
 */

#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/list_view.h>

#define LIST_MARGIN		5

static void _rtgui_list_view_constructor(struct rtgui_list_view *view)
{
	/* default rect */
	struct rtgui_rect rect = {0, 0, 200, 200};

	/* set default widget rect and set event handler */
	rtgui_widget_set_event_handler(RTGUI_WIDGET(view),rtgui_list_view_event_handler);
	rtgui_widget_set_rect(RTGUI_WIDGET(view), &rect);

	RTGUI_WIDGET(view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;

	view->current_item = 0;
	view->items_count = 0;
	view->page_items = 0;

	RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(view)) = white;
	RTGUI_WIDGET_TEXTALIGN(RTGUI_WIDGET(view)) = RTGUI_ALIGN_CENTER_VERTICAL;
}

rtgui_type_t *rtgui_list_view_type_get(void)
{
	static rtgui_type_t *list_view_type = RT_NULL;

	if (!list_view_type)
	{
		list_view_type = rtgui_type_create("listview", RTGUI_VIEW_TYPE,
			sizeof(rtgui_list_view_t), RTGUI_CONSTRUCTOR(_rtgui_list_view_constructor), RT_NULL);
	}

	return list_view_type;
}

void rtgui_list_view_ondraw(struct rtgui_list_view* view)
{
	struct rtgui_rect rect, item_rect;
	struct rtgui_dc* dc;
	rt_uint16_t page_index, index;
	struct rtgui_list_item* item;

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(view));
	if (dc == RT_NULL) return;

	rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);
	rtgui_dc_fill_rect(dc, &rect);

	/* get item base rect */
	item_rect = rect;
	item_rect.y1 += 2;
	item_rect.y2 = item_rect.y1 + (2 + rtgui_theme_get_selected_height());

	/* get current page */
	page_index = (view->current_item / view->page_items) * view->page_items;
	for (index = 0; index < view->page_items; index ++)
	{
		if (page_index + index >= view->items_count) break;

		item = &(view->items[page_index + index]);

		if (page_index + index == view->current_item)
		{
			rtgui_theme_draw_selected(dc, &item_rect);
		}
		item_rect.x1 += LIST_MARGIN;

		if (item->image != RT_NULL)
		{
			rtgui_image_blit(item->image, dc, &item_rect);
			item_rect.x1 += item->image->w + 2;
		}
        /* draw text */
		rtgui_dc_draw_text(dc, item->name, &item_rect);

        if (item->image != RT_NULL)
            item_rect.x1 -= (item->image->w + 2);
		item_rect.x1 -= LIST_MARGIN;

        /* move to next item position */
		item_rect.y1 += (rtgui_theme_get_selected_height() + 2);
		item_rect.y2 += (rtgui_theme_get_selected_height() + 2);
	}
	rtgui_dc_end_drawing(dc);
}

void rtgui_list_view_update_current(struct rtgui_list_view* view, rt_uint16_t old_item)
{
	struct rtgui_dc* dc;
	struct rtgui_list_item* item;
	rtgui_rect_t rect, item_rect;

	if (old_item/view->page_items != view->current_item/view->page_items)
	{
		/* it's not a same page, update all */
		rtgui_widget_update(RTGUI_WIDGET(view));
		return;
	}

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(view));
	if (dc == RT_NULL) return;

	rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);

	item_rect = rect;
	/* get old item's rect */
	item_rect.y1 += 2;
	item_rect.y1 += (old_item % view->page_items) * (2 + rtgui_theme_get_selected_height());
	item_rect.y2 = item_rect.y1 + (2 + rtgui_theme_get_selected_height());

	/* draw old item */
	rtgui_dc_fill_rect(dc, &item_rect);

	item_rect.x1 += LIST_MARGIN;

	item = &(view->items[old_item]);
	if (item->image != RT_NULL)
	{
		rtgui_image_blit(item->image, dc, &item_rect);
		item_rect.x1 += item->image->w + 2;
	}
	rtgui_dc_draw_text(dc, item->name, &item_rect);

	/* draw current item */
	item_rect = rect;
	/* get current item's rect */
	item_rect.y1 += 2;
	item_rect.y1 += (view->current_item % view->page_items) * (2 + rtgui_theme_get_selected_height());
	item_rect.y2 = item_rect.y1 + (2 + rtgui_theme_get_selected_height());

	/* draw current item */
	rtgui_theme_draw_selected(dc, &item_rect);

	item_rect.x1 += LIST_MARGIN;

	item = &(view->items[view->current_item]);
	if (item->image != RT_NULL)
	{
		rtgui_image_blit(item->image, dc, &item_rect);
        item_rect.x1 += (item->image->w + 2);
	}
	rtgui_dc_draw_text(dc, item->name, &item_rect);

	rtgui_dc_end_drawing(dc);
}

rt_bool_t rtgui_list_view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_list_view* view = RT_NULL;

	view = RTGUI_LIST_VIEW(widget);
	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		rtgui_list_view_ondraw(view);
		return RT_FALSE;

    case RTGUI_EVENT_RESIZE:
        {
			struct rtgui_event_resize* resize;

			resize = (struct rtgui_event_resize*)event;

            /* recalculate page items */
			view->page_items = resize->h  / (2 + rtgui_theme_get_selected_height());
        }
        break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		{
			rtgui_rect_t rect;
			struct rtgui_event_mouse* emouse;

			emouse = (struct rtgui_event_mouse*)event;

			/* calculate selected item */

			/* get physical extent information */
			rtgui_widget_get_rect(widget, &rect);
			rtgui_widget_rect_to_device(widget, &rect);

			if (rtgui_rect_contains_point(&rect, emouse->x, emouse->y) == RT_EOK)
			{
				rt_uint16_t index;
				index = (emouse->y - rect.y1) / (2 + rtgui_theme_get_selected_height());

				if ((index < view->items_count) && (index < view->page_items))
				{
					rt_uint16_t old_item;

					old_item = view->current_item;

					/* set selected item */
					view->current_item = view->current_item/view->page_items + index;
					rtgui_list_view_update_current(view, old_item);
				}
			}
		}
		break;

    case RTGUI_EVENT_KBD:
        {
            struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
            if (ekbd->type == RTGUI_KEYDOWN)
            {
				rt_uint16_t old_item;

				old_item = view->current_item;
                switch (ekbd->key)
                {
				case RTGUIK_LEFT:
					if (view->current_item - view->page_items >= 0)
						view->current_item -= view->page_items;
					rtgui_list_view_update_current(view, old_item);
					return RT_FALSE;

                case RTGUIK_UP:
					if (view->current_item > 0)
						view->current_item --;
					rtgui_list_view_update_current(view, old_item);
					return RT_FALSE;

				case RTGUIK_RIGHT:
					if (view->current_item + view->page_items < view->items_count - 1)
						view->current_item += view->page_items;
					rtgui_list_view_update_current(view, old_item);
					return RT_FALSE;

                case RTGUIK_DOWN:
					if (view->current_item < view->items_count - 1)
						view->current_item ++;
					rtgui_list_view_update_current(view, old_item);
					return RT_FALSE;

				case RTGUIK_RETURN:
                    if (view->items[view->current_item].action != RT_NULL)
					{
					    view->items[view->current_item].action(view->items[view->current_item].parameter);
					}
					return RT_FALSE;

                default:
                    break;
                }
            }
        }
		return RT_FALSE;
	}

    /* use view event handler */
    return rtgui_view_event_handler(widget, event);
}

rtgui_list_view_t* rtgui_list_view_create(struct rtgui_list_item* items, rt_uint16_t count, rtgui_rect_t *rect)
{
	struct rtgui_list_view* view = RT_NULL;

	view = (struct rtgui_list_view*) rtgui_widget_create(RTGUI_LIST_VIEW_TYPE);
	if (view != RT_NULL)
	{
	    view->items = items;
	    view->items_count = count;

		view->page_items = rtgui_rect_height(*rect) / (2 + rtgui_theme_get_selected_height());
	}

	return view;
}

void rtgui_list_view_destroy(rtgui_list_view_t* view)
{
    /* destroy view */
	rtgui_widget_destroy(RTGUI_WIDGET(view));
}
