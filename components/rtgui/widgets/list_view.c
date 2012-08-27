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
	rtgui_object_set_event_handler(RTGUI_OBJECT(view),rtgui_list_view_event_handler);
	rtgui_widget_set_rect(RTGUI_WIDGET(view), &rect);

	RTGUI_WIDGET(view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;

	view->flag = RTGUI_LIST_VIEW_LIST;
	view->current_item = 0;
	view->items_count = 0;
	view->page_items = 0;

	RTGUI_WIDGET_BACKGROUND(view) = white;
	RTGUI_WIDGET_TEXTALIGN(view) = RTGUI_ALIGN_CENTER_VERTICAL;
}

DEFINE_CLASS_TYPE(listview, "listview", 
	RTGUI_CONTAINER_TYPE,
	_rtgui_list_view_constructor,
	RT_NULL,
	sizeof(struct rtgui_list_view));

static void rtgui_list_view_onicondraw(struct rtgui_list_view* view, struct rtgui_dc *dc)
{
	struct rtgui_rect rect, item_rect, drawing_rect;
	rt_ubase_t c, r, item_index; /* col and row index */
	rt_ubase_t item_width, item_height;
	rtgui_image_t* image;

	if (view->items_count == 0) return;

	rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);
	item_index = (view->current_item / view->page_items) * view->page_items;

	item_width = (rtgui_rect_width(rect) - 2 * LIST_MARGIN)/view->col_items;
	item_height = (rtgui_rect_height(rect) - 4)/view->row_items;
	image = view->items[0].image;

	for (r = 0; r < view->row_items; r ++)
	{
		for (c = 0; c < view->col_items; c ++)
		{
			if (item_index < view->items_count)
			{
				item_rect.y1 = rect.y1 + LIST_MARGIN + r * item_height;
				item_rect.x1 = rect.x1 + LIST_MARGIN + c * item_width;
				item_rect.x2 = item_rect.x1 + item_width;
				item_rect.y2 = item_rect.y1 + item_height;

				if (item_index == view->current_item)
				{
					rtgui_theme_draw_selected(dc, &item_rect);
				}

				drawing_rect.x1 = drawing_rect.y1 = 0;
				drawing_rect.x2 = image->w;
				drawing_rect.y2 = image->h;
				rtgui_rect_moveto_align(&item_rect, &drawing_rect, RTGUI_ALIGN_CENTER_HORIZONTAL);
				drawing_rect.y1 += 5; drawing_rect.y2 += 5;
				rtgui_image_blit(view->items[item_index].image, dc, &drawing_rect);

				item_rect.y1 = drawing_rect.y2 + LIST_MARGIN; 
				item_rect.x1 += 3; item_rect.x2 -=3;
				rtgui_font_get_metrics(RTGUI_WIDGET_FONT(view), view->items[item_index].name, 
					&drawing_rect);
				rtgui_rect_moveto_align(&item_rect, &drawing_rect, RTGUI_ALIGN_CENTER_HORIZONTAL);
				rtgui_dc_draw_text(dc, view->items[item_index].name, &drawing_rect);

				item_index ++;
			}
			else break;
		}
	}
}

static void rtgui_list_view_update_icon(struct rtgui_list_view* view, rt_int16_t old_item)
{
	struct rtgui_rect rect, item_rect, drawing_rect;
	rt_ubase_t c, r; /* col and row index */
	rt_ubase_t item_width, item_height;
	rtgui_image_t* image;
	struct rtgui_dc* dc;

	if ((view->items_count == 0) ||
		(old_item == view->current_item))
		return;

	if (old_item/view->page_items != view->current_item/view->page_items)
	{
		/* it's not a same page, update all */
		rtgui_widget_update(RTGUI_WIDGET(view));
		return;
	}

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(view));
	if (dc == RT_NULL) return;

	rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);

	item_width = (rtgui_rect_width(rect) - 2 * LIST_MARGIN)/view->col_items;
	item_height = (rtgui_rect_height(rect) - 4)/view->row_items;
	image = view->items[0].image;

	/* update old item */
	r = (old_item % view->page_items)/ view->col_items;
	c = (old_item % view->page_items)% view->col_items;
	item_rect.y1 = rect.y1 + LIST_MARGIN + r * item_height;
	item_rect.x1 = rect.x1 + LIST_MARGIN + c * item_width;
	item_rect.x2 = item_rect.x1 + item_width;
	item_rect.y2 = item_rect.y1 + item_height;
	rtgui_dc_fill_rect(dc, &item_rect);

	/* draw image */
	drawing_rect.x1 = drawing_rect.y1 = 0;
	drawing_rect.x2 = image->w;
	drawing_rect.y2 = image->h;
	rtgui_rect_moveto_align(&item_rect, &drawing_rect, RTGUI_ALIGN_CENTER_HORIZONTAL);
	drawing_rect.y1 += 5; drawing_rect.y2 += 5;
	rtgui_image_blit(view->items[old_item].image, dc, &drawing_rect);

	/* draw text */
	item_rect.y1 = drawing_rect.y2 + LIST_MARGIN; 
	item_rect.x1 += 3; item_rect.x2 -=3;
	rtgui_font_get_metrics(RTGUI_WIDGET_FONT(view), view->items[old_item].name, 
		&drawing_rect);
	rtgui_rect_moveto_align(&item_rect, &drawing_rect, RTGUI_ALIGN_CENTER_HORIZONTAL);
	rtgui_dc_draw_text(dc, view->items[old_item].name, &drawing_rect);

	/* update new item as selected */
	r = (view->current_item % view->page_items) / view->col_items;
	c = (view->current_item % view->page_items) % view->col_items;
	item_rect.y1 = rect.y1 + LIST_MARGIN + r * item_height;
	item_rect.x1 = rect.x1 + LIST_MARGIN + c * item_width;
	item_rect.x2 = item_rect.x1 + item_width;
	item_rect.y2 = item_rect.y1 + item_height;
	rtgui_theme_draw_selected(dc, &item_rect);

	/* draw image */
	drawing_rect.x1 = 0;
	drawing_rect.y1 = 3;
	drawing_rect.x2 = image->w;
	drawing_rect.y2 = 3 + image->h;

	rtgui_rect_moveto_align(&item_rect, &drawing_rect, RTGUI_ALIGN_CENTER_HORIZONTAL);
	rtgui_image_blit(view->items[view->current_item].image, dc, &drawing_rect);

	/* draw text */
	item_rect.y1 = drawing_rect.y2 + LIST_MARGIN; 
	item_rect.x1 += 3; item_rect.x2 -=3;
	rtgui_font_get_metrics(RTGUI_WIDGET_FONT(view), 
		view->items[view->current_item].name, 
		&drawing_rect);
	rtgui_rect_moveto_align(&item_rect, &drawing_rect, RTGUI_ALIGN_CENTER_HORIZONTAL);
	rtgui_dc_draw_text(dc, view->items[view->current_item].name, &drawing_rect);

	rtgui_dc_end_drawing(dc);
}

static void rtgui_list_view_onlistdraw(struct rtgui_list_view* view, struct rtgui_dc *dc)
{
	rt_ubase_t index, page_index;
	rtgui_rect_t rect, item_rect, image_rect;
	const struct rtgui_list_item* item;

	rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);

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
			/* blit on center */
			image_rect.x1 = 0; image_rect.y1 = 0;
			image_rect.x2 = item->image->w;
			image_rect.y2 = item->image->h;

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
}

void rtgui_list_view_update_list(struct rtgui_list_view* view, rt_int16_t old_item)
{
	struct rtgui_dc* dc;
	const struct rtgui_list_item* item;
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

	/* get old item's rect and draw old item */
	item_rect.x1 = rect.x1; item_rect.x2 = rect.x2;
	item_rect.y1 = rect.y1 + 2;
	item_rect.y1 += (old_item % view->page_items) * (2 + rtgui_theme_get_selected_height());
	item_rect.y2 = item_rect.y1 + (2 + rtgui_theme_get_selected_height());
	rtgui_dc_fill_rect(dc, &item_rect);

	item_rect.x1 += LIST_MARGIN;

	item = &(view->items[old_item]);
	if (item->image != RT_NULL)
	{
		struct rtgui_rect image_rect;

		/* blit on center */
		image_rect.x1 = 0; image_rect.y1 = 0;
		image_rect.x2 = item->image->w;
		image_rect.y2 = item->image->h;

		rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);
		rtgui_image_blit(item->image, dc, &image_rect);
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
		struct rtgui_rect image_rect;

		/* blit on center */
		image_rect.x1 = 0; image_rect.y1 = 0;
		image_rect.x2 = item->image->w;
		image_rect.y2 = item->image->h;

		rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);
		rtgui_image_blit(item->image, dc, &image_rect);
		item_rect.x1 += (item->image->w + 2);
	}
	rtgui_dc_draw_text(dc, item->name, &item_rect);

	rtgui_dc_end_drawing(dc);
}
RTM_EXPORT(rtgui_list_view_update_list);

void rtgui_list_view_ondraw(struct rtgui_list_view* view)
{
	struct rtgui_rect rect;
	struct rtgui_dc* dc;

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(view));
	if (dc == RT_NULL) return;

	rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);
	rtgui_dc_fill_rect(dc, &rect);

	switch (view->flag)
	{
	case RTGUI_LIST_VIEW_LIST:
		rtgui_list_view_onlistdraw(view, dc);
		break;

	case RTGUI_LIST_VIEW_ICON:
		rtgui_list_view_onicondraw(view, dc);
		break;
	}

	rtgui_dc_end_drawing(dc);
}
RTM_EXPORT(rtgui_list_view_ondraw);

static rt_bool_t rtgui_list_view_onmouse(struct rtgui_list_view* view, struct rtgui_event_mouse* emouse)
{
	rtgui_rect_t rect;

	/* calculate selected item */

	/* get physical extent information */
	rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);
	rtgui_widget_rect_to_device(RTGUI_WIDGET(view), &rect);

	if (rtgui_rect_contains_point(&rect, emouse->x, emouse->y) == RT_EOK)
	{
		rt_uint16_t index;
		rt_uint16_t old_item;

		/* get old item */
		old_item = view->current_item;

		switch (view->flag)
		{
		case RTGUI_LIST_VIEW_LIST:
			index = (emouse->y - rect.y1) / (2 + rtgui_theme_get_selected_height());

			if ((index < view->items_count) && (index < view->page_items))
			{
				/* set selected item */
				view->current_item = (view->current_item/view->page_items) * view->page_items + index;
				if (emouse->button & RTGUI_MOUSE_BUTTON_DOWN)
				{
					/* down event */
					rtgui_list_view_update_list(view, old_item);
				}
				else
				{
					/* up event */
					if (view->items[view->current_item].action != RT_NULL)
					{
						view->items[view->current_item].action(RTGUI_WIDGET(view), 
							view->items[view->current_item].parameter);
					}
				}
			}
			break;

		case RTGUI_LIST_VIEW_ICON:
			{
				rt_uint16_t x, y;
				rt_uint16_t item_height, item_width;
				rt_ubase_t current_page;

				item_width = (rtgui_rect_width(rect) - 2 * LIST_MARGIN)/view->col_items;
				item_height = (rtgui_rect_height(rect) - 4)/view->row_items;
				x = emouse->x - rect.x1;
				y = emouse->y - rect.y1;

				index = (y / item_height * view->col_items) + x / item_width;
				current_page = view->current_item / view->page_items;

				if ((index + (current_page * view->page_items) < view->items_count))
				{
					if (emouse->button & RTGUI_MOUSE_BUTTON_DOWN)
					{
						view->current_item = index + (current_page * view->page_items);

						/* down event */
						rtgui_list_view_update_icon(view, old_item);
					}
					else
					{
						/* up event */
						if (view->items[view->current_item].action != RT_NULL)
						{
							view->items[view->current_item].action(RTGUI_WIDGET(view),
								view->items[view->current_item].parameter);
						}
					}
				}
			}
			break;

		case RTGUI_LIST_VIEW_REPORT:
			break;
		}

		return RT_TRUE;
	}

	return RT_FALSE;
}

rt_bool_t rtgui_list_view_event_handler(struct rtgui_object* widget, struct rtgui_event* event)
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
			struct rtgui_event_mouse* emouse;

			emouse = (struct rtgui_event_mouse*)event;
			return rtgui_list_view_onmouse(view, emouse);
		}

    case RTGUI_EVENT_KBD:
        {
            struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
            if (ekbd->type == RTGUI_KEYDOWN)
            {
				rt_uint16_t old_item;

				if (view->current_item == -1) 
				{
					/* set a initial item */
					if ((view->items_count > 0) && 
						(ekbd->key == RTGUIK_UP || ekbd->key == RTGUIK_DOWN))
					{
						view->current_item = 0;
						if (view->flag == RTGUI_LIST_VIEW_LIST)
							rtgui_list_view_update_list(view, -1);
						else
							rtgui_list_view_update_icon(view, -1);
						break;
					}
					else return RT_FALSE;
				}

				old_item = view->current_item;
                switch (ekbd->key)
                {
				case RTGUIK_LEFT:
					if (view->flag == RTGUI_LIST_VIEW_LIST)
					{
						if (view->current_item - view->page_items >= 0)
							view->current_item -= view->page_items;
						
						rtgui_list_view_update_list(view, old_item);
					}
					else if (view->flag == RTGUI_LIST_VIEW_ICON)
					{
						if (view->current_item > 0)
							view->current_item --;
						rtgui_list_view_update_icon(view, old_item);
					}
					return RT_FALSE;

                case RTGUIK_UP:
					if (view->flag == RTGUI_LIST_VIEW_LIST)
					{
						if (view->current_item > 0)
							view->current_item --;
						rtgui_list_view_update_list(view, old_item);
					}
					else if (view->flag == RTGUI_LIST_VIEW_ICON)
					{
						if (view->current_item >= view->col_items)
							view->current_item -= view->col_items;
						else 
							view->current_item = 0;
						
						rtgui_list_view_update_icon(view, old_item);
					}
					return RT_FALSE;

				case RTGUIK_RIGHT:
					if (view->flag == RTGUI_LIST_VIEW_LIST)
					{
						if (view->current_item + view->page_items < view->items_count - 1)
							view->current_item += view->page_items;
						
						rtgui_list_view_update_list(view, old_item);
					}
					else if (view->flag == RTGUI_LIST_VIEW_ICON)
					{
						if (view->current_item < view->items_count - 1)
							view->current_item ++;
						
						rtgui_list_view_update_icon(view, old_item);
					}
					return RT_FALSE;

                case RTGUIK_DOWN:
					if (view->flag == RTGUI_LIST_VIEW_LIST)
					{
						if (view->current_item < view->items_count - 1)
							view->current_item ++;
						
						rtgui_list_view_update_list(view, old_item);
					}
					else if (view->flag == RTGUI_LIST_VIEW_ICON)
					{
						if (view->current_item + view->col_items <= (view->items_count - 1))
							view->current_item += view->col_items;
						else 
							view->current_item = view->items_count - 1;

						rtgui_list_view_update_icon(view, old_item);
					}
					return RT_FALSE;

				case RTGUIK_RETURN:
                    if (view->items[view->current_item].action != RT_NULL)
					{
					    view->items[view->current_item].action(RTGUI_WIDGET(view),
							view->items[view->current_item].parameter);
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
    return rtgui_container_event_handler(widget, event);
}
RTM_EXPORT(rtgui_list_view_event_handler);

static void rtgui_list_view_calc(struct rtgui_list_view* view)
{
	rtgui_rect_t rect;
	rt_uint32_t image_width, image_height;
	rt_ubase_t text_width, text_height;
	rt_ubase_t item_width, item_height;

	if (view->items_count == 0) return;

	/* get image width and height */
	if (view->items[0].image != RT_NULL)
	{
		image_width  = view->items[0].image->w;
		image_height = view->items[0].image->h;
	}
	else
	{
		image_width  = 0;
		image_height = 0;
	}

	rtgui_font_get_metrics(RTGUI_WIDGET_FONT(view), "HHHHHH", &rect);

	text_height = rtgui_rect_height(rect);
	text_width = rtgui_rect_width(rect);

	rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);

	item_width = (image_width + LIST_MARGIN);
	if (item_width < (text_width + LIST_MARGIN)) item_width = text_width + LIST_MARGIN;
	item_height = image_height + 8 + text_height + LIST_MARGIN; 
	if (item_width > item_height) item_height = item_width;
	else item_width = item_height;
	
	view->row_items = (rtgui_rect_height(rect) - 2 * LIST_MARGIN) / item_height;
	view->col_items = (rtgui_rect_width(rect) - 2 * LIST_MARGIN) / item_width;
	view->page_items = view->row_items * view->col_items;
}

rtgui_list_view_t* rtgui_list_view_create(const struct rtgui_list_item* items, rt_uint16_t count, 
	rtgui_rect_t *rect, rt_uint16_t flag)
{
	struct rtgui_list_view* view = RT_NULL;

	view = (struct rtgui_list_view*) rtgui_widget_create(RTGUI_LIST_VIEW_TYPE);
	if (view != RT_NULL)
	{
	    view->items = items;
	    view->items_count = count;

		view->flag = flag;
		rtgui_widget_set_rect(RTGUI_WIDGET(view), rect);

		if (flag == RTGUI_LIST_VIEW_LIST)
			view->page_items = rtgui_rect_height(*rect) / (2 + rtgui_theme_get_selected_height());
		else if ((flag == RTGUI_LIST_VIEW_ICON) && (count > 0))
		{
			rtgui_list_view_calc(view);
		}
	}

	return view;
}
RTM_EXPORT(rtgui_list_view_create);

void rtgui_list_view_destroy(rtgui_list_view_t* view)
{
    /* destroy view */
	rtgui_widget_destroy(RTGUI_WIDGET(view));
}
RTM_EXPORT(rtgui_list_view_destroy);

