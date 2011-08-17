/*
 * File      : listbox.c
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
#include <rtgui/widgets/listbox.h>

#define LIST_MARGIN		5

static void _rtgui_listbox_constructor(struct rtgui_listbox *box)
{
	/* set default widget rect and set event handler */
	rtgui_widget_set_event_handler(RTGUI_WIDGET(box),rtgui_listbox_event_handler);

	RTGUI_WIDGET(box)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;

	box->current_item = -1;
	box->items_count = 0;
	box->page_items = 1;
	box->on_item = 0;

	RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(box)) = white;
	RTGUI_WIDGET_TEXTALIGN(RTGUI_WIDGET(box)) = RTGUI_ALIGN_CENTER_VERTICAL;
}

DEFINE_CLASS_TYPE(listbox, "listbox", 
	RTGUI_WIDGET_TYPE,
	_rtgui_listbox_constructor,
	RT_NULL,
	sizeof(struct rtgui_listbox));

void rtgui_listbox_ondraw(struct rtgui_listbox* box)
{
	struct rtgui_dc* dc;
	rt_uint16_t page_index, index;
	const struct rtgui_listbox_item* item;
	struct rtgui_rect rect, item_rect, image_rect;

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(box));
	if (dc == RT_NULL) return;

	rtgui_widget_get_rect(RTGUI_WIDGET(box), &rect);
	rtgui_dc_fill_rect(dc, &rect);

	rect.x2 -= 1; rect.y2 -= 1;
	/* draw focused border */
	if (RTGUI_WIDGET_IS_FOCUSED(RTGUI_WIDGET(box)))
		rtgui_dc_draw_focus_rect(dc, &rect);

	/* get item base rect */
	item_rect = rect;
	item_rect.x1 += 1; item_rect.x2 -= 1;
	item_rect.y1 += 2;
	item_rect.y2 = item_rect.y1 + (2 + rtgui_theme_get_selected_height());

	/* get current page */
	if (box->current_item == -1)
		page_index = 0;
	else
		page_index = (box->current_item / box->page_items) * box->page_items;

	for (index = 0; index < box->page_items; index ++)
	{
		if (page_index + index >= box->items_count) break;

		item = &(box->items[page_index + index]);

		if (page_index + index == box->current_item)
		{
			rtgui_theme_draw_selected(dc, &item_rect);
		}
		item_rect.x1 += LIST_MARGIN;

		if (item->image != RT_NULL)
		{
			rtgui_image_get_rect(item->image, &image_rect);
			rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);

			rtgui_image_blit(item->image, dc, &image_rect);
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

static void rtgui_listbox_update_current(struct rtgui_listbox* box, rt_int16_t old_item)
{
	struct rtgui_dc* dc;
	const struct rtgui_listbox_item* item;
	rtgui_rect_t rect, item_rect, image_rect;

	if ((old_item == -1) || (old_item/box->page_items != box->current_item/box->page_items))
	{
		/* it's not a same page, update all */
		rtgui_widget_update(RTGUI_WIDGET(box));
		return;
	}

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(box));
	if (dc == RT_NULL) return;

	rtgui_widget_get_rect(RTGUI_WIDGET(box), &rect);
	rect.x2 -= 1; rect.y2 -= 1;

	item_rect = rect;
	/* get old item's rect */
	item_rect.x1 += 1; item_rect.x2 -= 1;
	item_rect.y1 += 2;
	item_rect.y1 += (old_item % box->page_items) * (2 + rtgui_theme_get_selected_height());
	item_rect.y2 = item_rect.y1 + (2 + rtgui_theme_get_selected_height());

	/* draw old item */
	rtgui_dc_fill_rect(dc, &item_rect);

	item_rect.x1 += LIST_MARGIN;

	item = &(box->items[old_item]);
	if (item->image != RT_NULL)
	{
		rtgui_image_get_rect(item->image, &image_rect);
		rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);
		
		rtgui_image_blit(item->image, dc, &image_rect);
		item_rect.x1 += item->image->w + 2;
	}
	rtgui_dc_draw_text(dc, item->name, &item_rect);

	/* draw current item */
	item_rect = rect;
	/* get current item's rect */
	item_rect.x1 += 1; item_rect.x2 -= 1;
	item_rect.y1 += 2;
	item_rect.y1 += (box->current_item % box->page_items) * (2 + rtgui_theme_get_selected_height());
	item_rect.y2 = item_rect.y1 + (2 + rtgui_theme_get_selected_height());

	/* draw current item */
	rtgui_theme_draw_selected(dc, &item_rect);

	item_rect.x1 += LIST_MARGIN;

	item = &(box->items[box->current_item]);
	if (item->image != RT_NULL)
	{
		rtgui_image_get_rect(item->image, &image_rect);
		rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);

		rtgui_image_blit(item->image, dc, &image_rect);
        item_rect.x1 += (item->image->w + 2);
	}
	rtgui_dc_draw_text(dc, item->name, &item_rect);

	rtgui_dc_end_drawing(dc);
}

rt_bool_t rtgui_listbox_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_listbox* box = RT_NULL;

	box = RTGUI_LISTBOX(widget);
	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		rtgui_listbox_ondraw(box);
		return RT_FALSE;

    case RTGUI_EVENT_RESIZE:
        {
			struct rtgui_event_resize* resize;

			resize = (struct rtgui_event_resize*)event;

            /* recalculate page items */
			box->page_items = resize->h  / (2 + rtgui_theme_get_selected_height());
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

			if ((rtgui_rect_contains_point(&rect, emouse->x, emouse->y) == RT_EOK) && (box->items_count > 0))
			{
				rt_uint16_t index;
				index = (emouse->y - rect.y1) / (2 + rtgui_theme_get_selected_height());

				/* set focus */
				rtgui_widget_focus(widget);
				{
					struct rtgui_rect rect;
					struct rtgui_dc* dc;

					dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(box));
					if (dc != RT_NULL)
					{
						/* get widget rect */
						rtgui_widget_get_rect(RTGUI_WIDGET(box), &rect);
						/* update focus border */
						rect.x2 -= 1; rect.y2 -= 1;
						/* draw focused border */
						if (RTGUI_WIDGET_IS_FOCUSED(RTGUI_WIDGET(box)))
							rtgui_dc_draw_focus_rect(dc, &rect);
						rtgui_dc_end_drawing(dc);
					}
				}

				if ((index < box->items_count) && (index < box->page_items))
				{
					rt_uint16_t old_item;

					old_item = box->current_item;

					/* set selected item */
					box->current_item = (box->current_item/box->page_items) * box->page_items + index;
					if (emouse->button & RTGUI_MOUSE_BUTTON_DOWN)
					{
						/* down event */
						rtgui_listbox_update_current(box, old_item);
					}
					else
					{
						/* up event */
						if (box->on_item != RT_NULL)
						{
							box->on_item(RTGUI_WIDGET(box), RT_NULL);
						}
					}
				}
			}

			return RT_TRUE;
		}

    case RTGUI_EVENT_KBD:
        {
            struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
            if ((ekbd->type == RTGUI_KEYDOWN) && (box->items_count > 0))
            {
				rt_int16_t old_item;

				if (box->current_item == -1) 
				{
					/* set a initial item */
					if ((box->items_count > 0) && 
						(ekbd->key == RTGUIK_UP || ekbd->key == RTGUIK_DOWN))
					{
						box->current_item = 0;
						rtgui_listbox_update_current(box, -1);
						break;
					}
					else return RT_FALSE;
				}
				old_item = box->current_item;

                switch (ekbd->key)
                {
				case RTGUIK_LEFT:
					if (box->current_item - box->page_items >= 0)
						box->current_item -= box->page_items;
					rtgui_listbox_update_current(box, old_item);
					return RT_FALSE;

                case RTGUIK_UP:
					if (box->current_item > 0)
						box->current_item --;
					rtgui_listbox_update_current(box, old_item);
					return RT_FALSE;

				case RTGUIK_RIGHT:
					if (box->current_item + box->page_items < box->items_count - 1)
						box->current_item += box->page_items;
					rtgui_listbox_update_current(box, old_item);
					return RT_FALSE;

                case RTGUIK_DOWN:
					if (box->current_item < box->items_count - 1)
						box->current_item ++;
					rtgui_listbox_update_current(box, old_item);
					return RT_FALSE;

				case RTGUIK_RETURN:
                    if (box->on_item != RT_NULL)
					{
						box->on_item(RTGUI_WIDGET(box), RT_NULL);
					}
					return RT_FALSE;

                default:
                    break;
                }
            }
        }
		return RT_FALSE;
	}

    /* use box event handler */
    return rtgui_widget_event_handler(widget, event);
}

rtgui_listbox_t* rtgui_listbox_create(const struct rtgui_listbox_item* items, rt_uint16_t count, rtgui_rect_t *rect)
{
	struct rtgui_listbox* box = RT_NULL;

	box = (struct rtgui_listbox*) rtgui_widget_create(RTGUI_LISTBOX_TYPE);
	if (box != RT_NULL)
	{
	    box->items = items;
	    box->items_count = count;

		box->page_items = rtgui_rect_height(*rect) / (2 + rtgui_theme_get_selected_height());
		if (box->page_items == 0) box->page_items = 1;
		rtgui_widget_set_rect(RTGUI_WIDGET(box), rect);
	}

	return box;
}

void rtgui_listbox_destroy(rtgui_listbox_t* box)
{
    /* destroy box */
	rtgui_widget_destroy(RTGUI_WIDGET(box));
}

void rtgui_listbox_set_onitem(rtgui_listbox_t* box, rtgui_onitem_func_t func)
{
	RT_ASSERT(box != RT_NULL);

	box->on_item = func;
}

void rtgui_listbox_set_items(rtgui_listbox_t* box, struct rtgui_listbox_item* items, rt_uint16_t count)
{
	rtgui_rect_t rect;
	
	box->items = items;
	box->items_count = count;
	box->current_item = -1;

	rtgui_widget_get_rect(RTGUI_WIDGET(box), &rect);
	box->page_items = rtgui_rect_height(rect) / (2 + rtgui_theme_get_selected_height());

	rtgui_widget_update(RTGUI_WIDGET(box));
}

void rtgui_listbox_set_current_item(rtgui_listbox_t* box, int index)
{
	RT_ASSERT(box != RT_NULL);

	if (index != box->current_item)
	{
		int old_item; 

		old_item = box->current_item;
		box->current_item = index;

		rtgui_listbox_update_current(box, old_item);
	}
}

