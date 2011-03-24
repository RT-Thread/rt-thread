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

static void _rtgui_list_view_constructor(rtgui_list_view_t *view)
{
	/* default rect */
	rtgui_rect_t rect = {0, 0, 200, 200};

	/* set default widget rect and set event handler */
	rtgui_widget_set_event_handler(view,rtgui_list_view_event_handler);
	rtgui_widget_set_rect(view, &rect);

	RTGUI_WIDGET_FLAG(view) |= RTGUI_WIDGET_FLAG_FOCUSABLE;

	view->flag = RTGUI_LIST_VIEW_LIST;
	view->item_current = 0;
	view->item_count = 0;
	view->page = 0;

	RTGUI_WIDGET_BACKGROUND(view) = white;
	RTGUI_WIDGET_TEXTALIGN(view) = RTGUI_ALIGN_CENTER_VERTICAL;
}

static void _rtgui_list_view_destructor(rtgui_list_view_t *view)
{

}

rtgui_type_t *rtgui_list_view_type_get(void)
{
	static rtgui_type_t *list_view_type = RT_NULL;

	if(!list_view_type)
	{
		list_view_type = rtgui_type_create("listview", RTGUI_VIEW_TYPE,
			sizeof(rtgui_list_view_t), 
			RTGUI_CONSTRUCTOR(_rtgui_list_view_constructor), 
			RTGUI_DESTRUCTOR(_rtgui_list_view_destructor));
	}

	return list_view_type;
}

static void rtgui_list_view_onicondraw(rtgui_list_view_t* view)
{
	rtgui_rect_t rect, item_rect, drawing_rect;
	rt_uint32_t c, r, i; /* col and row index */
	rt_uint32_t item_width, item_height;
	rtgui_image_t* image;
	rtgui_dc_t* dc;
	
	RT_ASSERT(view != RT_NULL);

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(view);
	if(dc == RT_NULL)return;

	if(view->item_count == 0) return;

	rtgui_widget_get_rect(view, &rect);
	i = (view->item_current / view->page) * view->page;

	item_width = (rtgui_rect_width(rect) - 2 * RTGUI_WIDGET_DEFAULT_MARGIN)/view->col_items;
	item_height = (rtgui_rect_height(rect) - 4)/view->row_items;
	image = view->items[0].image;

	for(r = 0; r < view->row_items; r ++)
	{
		for(c = 0; c < view->col_items; c ++)
		{
			if(i < view->item_count)
			{
				item_rect.y1 = rect.y1 + RTGUI_WIDGET_DEFAULT_MARGIN + r * item_height;
				item_rect.x1 = rect.x1 + RTGUI_WIDGET_DEFAULT_MARGIN + c * item_width;
				item_rect.x2 = item_rect.x1 + item_width;
				item_rect.y2 = item_rect.y1 + item_height;

				if(i == view->item_current)
				{
					RTGUI_DC_BC(dc) = selected_color;
					rtgui_dc_fill_rect(dc, &item_rect);
				}

				drawing_rect.x1 = drawing_rect.y1 = 0;
				drawing_rect.x2 = image->w;
				drawing_rect.y2 = image->h;
				rtgui_rect_moveto_align(&item_rect, &drawing_rect, RTGUI_ALIGN_CENTER_HORIZONTAL);
				drawing_rect.y1 += 3; drawing_rect.y2 += 3;
				rtgui_image_blit(view->items[i].image, dc, &drawing_rect);

				item_rect.y1 = drawing_rect.y2 + RTGUI_WIDGET_DEFAULT_MARGIN; 
				item_rect.x1 += 3; item_rect.x2 -=3;
				rtgui_font_get_string_rect(RTGUI_WIDGET_FONT(view), view->items[i].name, 
					&drawing_rect);
				rtgui_rect_moveto_align(&item_rect, &drawing_rect, RTGUI_ALIGN_CENTER_HORIZONTAL);
				rtgui_dc_draw_text(dc, view->items[i].name, &drawing_rect);

				i ++;
			}
			else break;
		}
	}
	rtgui_dc_end_drawing(dc);
}

static void rtgui_list_view_update_icon(rtgui_list_view_t* view, rt_uint16_t old_item)
{
	rtgui_rect_t rect, item_rect, drawing_rect;
	rt_uint32_t c, r; /* col and row index */
	rt_uint32_t item_width, item_height;
	rtgui_image_t* image;
	rtgui_dc_t* dc;
	
	RT_ASSERT(view != RT_NULL);

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(view);
	if(dc == RT_NULL)return;

	if((view->item_count == 0) ||
		(old_item == view->item_current))
		return;

	if(old_item/view->page != view->item_current/view->page)
	{
		/* it's not a same page, update all */
		rtgui_widget_update(view);
		return;
	}

	rtgui_widget_get_rect(view, &rect);

	item_width = (rtgui_rect_width(rect) - 2 * RTGUI_WIDGET_DEFAULT_MARGIN)/view->col_items;
	item_height = (rtgui_rect_height(rect) - 4)/view->row_items;
	image = view->items[0].image;

	/* update old item */
	r = (old_item % view->page)/ view->col_items;
	c = (old_item % view->page)% view->col_items;
	item_rect.y1 = rect.y1 + RTGUI_WIDGET_DEFAULT_MARGIN + r * item_height;
	item_rect.x1 = rect.x1 + RTGUI_WIDGET_DEFAULT_MARGIN + c * item_width;
	item_rect.x2 = item_rect.x1 + item_width;
	item_rect.y2 = item_rect.y1 + item_height;
	rtgui_dc_fill_rect(dc,&item_rect);

	/* draw image */
	drawing_rect.x1 = drawing_rect.y1 = 0;
	drawing_rect.x2 = image->w;
	drawing_rect.y2 = image->h;
	rtgui_rect_moveto_align(&item_rect, &drawing_rect, RTGUI_ALIGN_CENTER_HORIZONTAL);
	drawing_rect.y1 += 3; drawing_rect.y2 += 3;
	rtgui_image_blit(view->items[old_item].image, dc,&drawing_rect);

	/* draw text */
	item_rect.y1 = drawing_rect.y2 + RTGUI_WIDGET_DEFAULT_MARGIN; 
	item_rect.x1 += 3; item_rect.x2 -=3;
	rtgui_font_get_string_rect(RTGUI_WIDGET_FONT(view), view->items[old_item].name, 
		&drawing_rect);
	rtgui_rect_moveto_align(&item_rect, &drawing_rect, RTGUI_ALIGN_CENTER_HORIZONTAL);
	rtgui_dc_draw_text(dc, view->items[old_item].name, &drawing_rect);

	/* update new item as selected */
	r = (view->item_current % view->page) / view->col_items;
	c = (view->item_current % view->page) % view->col_items;
	item_rect.y1 = rect.y1 + RTGUI_WIDGET_DEFAULT_MARGIN + r * item_height;
	item_rect.x1 = rect.x1 + RTGUI_WIDGET_DEFAULT_MARGIN + c * item_width;
	item_rect.x2 = item_rect.x1 + item_width;
	item_rect.y2 = item_rect.y1 + item_height;
	RTGUI_DC_BC(dc) = selected_color;
	rtgui_dc_fill_rect(dc, &item_rect);

	/* draw image */
	drawing_rect.x1 = 0;
	drawing_rect.y1 = 3;
	drawing_rect.x2 = image->w;
	drawing_rect.y2 = 3 + image->h;

	rtgui_rect_moveto_align(&item_rect, &drawing_rect, RTGUI_ALIGN_CENTER_HORIZONTAL);
	rtgui_image_blit(view->items[view->item_current].image, dc, &drawing_rect);

	/* draw text */
	item_rect.y1 = drawing_rect.y2 + RTGUI_WIDGET_DEFAULT_MARGIN; 
	item_rect.x1 += 3; item_rect.x2 -=3;
	rtgui_font_get_string_rect(RTGUI_WIDGET_FONT(view), 
		view->items[view->item_current].name, 
		&drawing_rect);
	rtgui_rect_moveto_align(&item_rect, &drawing_rect, RTGUI_ALIGN_CENTER_HORIZONTAL);
	rtgui_dc_draw_text(dc, view->items[view->item_current].name, &drawing_rect);

	rtgui_dc_end_drawing(dc);
}

static void rtgui_list_view_onlistdraw(rtgui_list_view_t* view)
{
	rt_uint32_t i, page;
	rtgui_rect_t rect, item_rect, image_rect;
	const rtgui_list_view_item_t* item;
	rtgui_dc_t* dc;
	
	RT_ASSERT(view != RT_NULL);

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(view);
	if(dc == RT_NULL)return;

	rtgui_widget_get_rect(view, &rect);

	/* get item base rect */
	item_rect = rect;
	item_rect.x1 += 2;
	item_rect.x2 -= 2;
	item_rect.y1 += 2;
	item_rect.y2 = item_rect.y1 + (2 + SELECTED_HEIGHT);

	/* get current page */
	page = (view->item_current / view->page) * view->page;
	for(i = 0; i < view->page; i ++)
	{
		if(page + i >= view->item_count) break;

		item = &(view->items[page + i]);

		if(page + i == view->item_current)
		{
			RTGUI_DC_BC(dc) = selected_color;
			rtgui_dc_fill_rect(dc, &item_rect);
		}
		item_rect.x1 += RTGUI_WIDGET_DEFAULT_MARGIN;

		if(item->image != RT_NULL)
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

		if(item->image != RT_NULL)
			item_rect.x1 -= (item->image->w + 2);
		item_rect.x1 -= RTGUI_WIDGET_DEFAULT_MARGIN;

		/* move to next item position */
		item_rect.y1 += (SELECTED_HEIGHT + 2);
		item_rect.y2 += (SELECTED_HEIGHT + 2);
	}

	rtgui_dc_end_drawing(dc);
}

void rtgui_list_view_update_list(rtgui_list_view_t* view, rt_uint16_t old_item)
{
	const rtgui_list_view_item_t* item;
	rtgui_rect_t rect, item_rect;
	rtgui_dc_t* dc;
	
	RT_ASSERT(view != RT_NULL);

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(view);
	if(dc == RT_NULL)return;

	if(old_item/view->page != view->item_current/view->page)
	{
		/* it's not a same page, update all */
		rtgui_widget_update(view);
		return;
	}

	//绘制上一个项目
	rtgui_widget_get_rect(view, &rect);
	item_rect = rect;
	item_rect.x1 += 2;
	item_rect.x2 -= 2;
	item_rect.y1 += 2;
	item_rect.y1 += (old_item % view->page) * (2 + SELECTED_HEIGHT);
	item_rect.y2 = item_rect.y1 + (2 + SELECTED_HEIGHT);

	rtgui_dc_fill_rect(dc,&item_rect);

	item_rect.x1 += RTGUI_WIDGET_DEFAULT_MARGIN;

	item = &(view->items[old_item]);
	if(item->image != RT_NULL)
	{
		rtgui_rect_t image_rect;

		/* blit on center */
		image_rect.x1 = 0; image_rect.y1 = 0;
		image_rect.x2 = item->image->w;
		image_rect.y2 = item->image->h;

		rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);
		rtgui_image_blit(item->image, dc, &image_rect);
		item_rect.x1 += item->image->w + 2;
	}
	rtgui_dc_draw_text(dc, item->name, &item_rect);

	//绘制当前项
	item_rect = rect;
	/* get current item's rect */
	item_rect.x1 += 2;
	item_rect.x2 -= 2;
	item_rect.y1 += 2;
	item_rect.y1 += (view->item_current % view->page) * (2 + SELECTED_HEIGHT);
	item_rect.y2 = item_rect.y1 + (2 + SELECTED_HEIGHT);

	/* draw current item */
	RTGUI_DC_BC(dc) = selected_color;
	rtgui_dc_fill_rect(dc, &item_rect);

	item_rect.x1 += RTGUI_WIDGET_DEFAULT_MARGIN;

	item = &(view->items[view->item_current]);
	if(item->image != RT_NULL)
	{
		rtgui_rect_t image_rect;

		/* blit on center */
		image_rect.x1 = 0; image_rect.y1 = 0;
		image_rect.x2 = item->image->w;
		image_rect.y2 = item->image->h;

		rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);
		rtgui_image_blit(item->image, dc, &image_rect);
		item_rect.x1 += (item->image->w + 2);
	}

	RTGUI_DC_FC(dc) = white;
	rtgui_dc_draw_text(dc, item->name, &item_rect);
	
	rtgui_dc_end_drawing(dc);
}

void rtgui_list_view_ondraw(rtgui_list_view_t* view)
{
	rtgui_rect_t rect;
	rtgui_dc_t* dc;
	
	RT_ASSERT(view != RT_NULL);

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(view);
	if(dc == RT_NULL)return;

	rtgui_widget_get_rect(view, &rect);
	rtgui_dc_fill_rect(dc,&rect);

	switch (view->flag)
	{
		case RTGUI_LIST_VIEW_LIST:
			rtgui_list_view_onlistdraw(view);
			break;
	
		case RTGUI_LIST_VIEW_ICON:
			rtgui_list_view_onicondraw(view);
			break;
	}

	rtgui_dc_end_drawing(dc);
}

static rt_bool_t rtgui_list_view_onmouse(rtgui_list_view_t* view, rtgui_event_mouse_t* emouse)
{
	rtgui_rect_t rect;

	/* calculate selected item */

	/* get physical extent information */
	rtgui_widget_get_rect(view, &rect);

	if(rtgui_rect_contains_point(&rect, emouse->x, emouse->y) == RT_EOK)
	{
		rt_uint16_t index;
		rt_uint16_t old_item;

		/* get old item */
		old_item = view->item_current;

		switch (view->flag)
		{
			case RTGUI_LIST_VIEW_LIST:
				index = (emouse->y - rect.y1) / (2 + SELECTED_HEIGHT);
	
				if((index < view->item_count) && (index < view->page))
				{
					/* set selected item */
					view->item_current = (view->item_current/view->page) * view->page + index;
					if(emouse->button & RTGUI_MOUSE_BUTTON_DOWN)
					{
						/* down event */
						rtgui_list_view_update_list(view, old_item);
					}
					else
					{
						/* up event */
						if(view->items[view->item_current].action != RT_NULL)
						{
							view->items[view->item_current].action(view->items[view->item_current].parameter);
						}
					}
				}
				break;
	
			case RTGUI_LIST_VIEW_ICON:
				{
					rt_uint16_t x, y;
					rt_uint16_t item_height, item_width;
					rt_uint32_t current_page;
	
					item_width = (rtgui_rect_width(rect) - 2 * RTGUI_WIDGET_DEFAULT_MARGIN)/view->col_items;
					item_height = (rtgui_rect_height(rect) - 4)/view->row_items;
					x = emouse->x - rect.x1;
					y = emouse->y - rect.y1;
	
					index = (y / item_height * view->col_items) + x / item_width;
					current_page = view->item_current / view->page;
	
					if((index + (current_page * view->page) < view->item_count))
					{
						if(emouse->button & RTGUI_MOUSE_BUTTON_DOWN)
						{
							view->item_current = index + (current_page * view->page);
	
							/* down event */
							rtgui_list_view_update_icon(view, old_item);
						}
						else
						{
							/* up event */
							if(view->items[view->item_current].action != RT_NULL)
							{
								view->items[view->item_current].action(view->items[view->item_current].parameter);
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

rt_bool_t rtgui_list_view_event_handler(PVOID wdt, rtgui_event_t* event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_list_view_t* view = RT_NULL;

	view = RTGUI_LIST_VIEW(widget);
	switch (event->type)
	{
		case RTGUI_EVENT_PAINT:
			rtgui_list_view_ondraw(view);
			return RT_FALSE;
	
	    case RTGUI_EVENT_RESIZE:
	        {
				rtgui_event_resize_t* resize;
	
				resize = (rtgui_event_resize_t*)event;
	
	            /* recalculate page items */
				view->page = resize->h  / (2 + SELECTED_HEIGHT);
	        }
	        break;
	
		case RTGUI_EVENT_MOUSE_BUTTON:
			{
				rtgui_event_mouse_t* emouse;
	
				emouse = (rtgui_event_mouse_t*)event;
				return rtgui_list_view_onmouse(view, emouse);
			}
	
	    case RTGUI_EVENT_KBD:
	        {
	            rtgui_event_kbd_t* ekbd = (rtgui_event_kbd_t*)event;
	            if(RTGUI_KBD_IS_DOWN(ekbd))
	            {
					rt_uint16_t old_item;
	
					old_item = view->item_current;
	                switch (ekbd->key)
	                {
						case RTGUIK_LEFT:
							if(view->flag == RTGUI_LIST_VIEW_LIST)
							{
								if(view->item_current - view->page >= 0)
									view->item_current -= view->page;
								
								rtgui_list_view_update_list(view, old_item);
							}
							else if(view->flag == RTGUI_LIST_VIEW_ICON)
							{
								if(view->item_current > 0)
									view->item_current --;
								rtgui_list_view_update_icon(view, old_item);
							}
							return RT_FALSE;
		
		                case RTGUIK_UP:
							if(view->flag == RTGUI_LIST_VIEW_LIST)
							{
								if(view->item_current > 0)
									view->item_current --;
								rtgui_list_view_update_list(view, old_item);
							}
							else if(view->flag == RTGUI_LIST_VIEW_ICON)
							{
								if(view->item_current >= view->col_items)
									view->item_current -= view->col_items;
								else 
									view->item_current = 0;
								
								rtgui_list_view_update_icon(view, old_item);
							}
							return RT_FALSE;
		
						case RTGUIK_RIGHT:
							if(view->flag == RTGUI_LIST_VIEW_LIST)
							{
								if(view->item_current + view->page < view->item_count - 1)
									view->item_current += view->page;
								
								rtgui_list_view_update_list(view, old_item);
							}
							else if(view->flag == RTGUI_LIST_VIEW_ICON)
							{
								if(view->item_current < view->item_count - 1)
									view->item_current ++;
								
								rtgui_list_view_update_icon(view, old_item);
							}
							return RT_FALSE;
		
		                case RTGUIK_DOWN:
							if(view->flag == RTGUI_LIST_VIEW_LIST)
							{
								if(view->item_current < view->item_count - 1)
									view->item_current ++;
								
								rtgui_list_view_update_list(view, old_item);
							}
							else if(view->flag == RTGUI_LIST_VIEW_ICON)
							{
								if(view->item_current + view->col_items <= (view->item_count - 1))
									view->item_current += view->col_items;
								else 
									view->item_current = view->item_count - 1;
		
								rtgui_list_view_update_icon(view, old_item);
							}
							return RT_FALSE;
		
						case RTGUIK_RETURN:
		                    if(view->items[view->item_current].action != RT_NULL)
							{
							    view->items[view->item_current].action(view->items[view->item_current].parameter);
							}
							return RT_FALSE;
		
		                default:
		                    break;
	                }
	            }
	        }
			return RT_FALSE;

		default: 
			break;
	}

    /* use view event handler */
    return rtgui_view_event_handler(widget, event);
}

static void rtgui_list_view_calc(rtgui_list_view_t* view)
{
	/* get image of first item*/
	rtgui_image_t *image;
	rtgui_rect_t rect;
	rt_uint32_t text_width, text_height;
	rt_uint32_t item_width, item_height;

	if(view->item_count == 0) return;

	image = view->items[0].image;
	rtgui_font_get_string_rect(RTGUI_WIDGET_FONT(view), "HHHHHH", &rect);

	text_height = rtgui_rect_height(rect);
	text_width = rtgui_rect_width(rect);

	rtgui_widget_get_rect(view, &rect);

	item_width = image->w + RTGUI_WIDGET_DEFAULT_MARGIN;
	if(item_width < (text_width + RTGUI_WIDGET_DEFAULT_MARGIN)) item_width = text_width + RTGUI_WIDGET_DEFAULT_MARGIN;
	item_height = image->h + 3 + text_height + RTGUI_WIDGET_DEFAULT_MARGIN; 

	view->row_items = (rtgui_rect_height(rect) - 2 * RTGUI_WIDGET_DEFAULT_MARGIN) / item_height;
	view->col_items = (rtgui_rect_width(rect) - 2 * RTGUI_WIDGET_DEFAULT_MARGIN) / item_width;
	view->page = view->row_items * view->col_items;
}

rtgui_list_view_t* rtgui_list_view_create(PVOID parent,const rtgui_list_view_item_t* items, rt_uint16_t count, int left,int top,int w,int h, rt_uint16_t flag)
{
	rtgui_list_view_t* view = RT_NULL;

	RT_ASSERT(parent != RT_NULL);

	view = rtgui_widget_create(RTGUI_LIST_VIEW_TYPE);
	if(view != RT_NULL)
	{
	    rtgui_rect_t rect;
		view->items = items;
	    view->item_count = count;

		view->flag = flag;
		rtgui_widget_get_rect(view, &rect);
		rtgui_widget_rect_to_device(parent,&rect);
		rect.x1 += left;
		rect.y1 += top;
		rect.x2 = rect.x1+w;
		rect.y2 = rect.y1+h;
		rtgui_widget_set_rect(view, &rect);

		if(flag == RTGUI_LIST_VIEW_LIST)
			view->page = rtgui_rect_height(rect) / (2 + SELECTED_HEIGHT);
		else if((flag == RTGUI_LIST_VIEW_ICON) && (count > 0))
		{	
			rtgui_list_view_calc(view);
		}
		rtgui_container_add_child(parent, view);
	}

	return view;
}

void rtgui_list_view_destroy(rtgui_list_view_t* view)
{
    /* destroy view */
	rtgui_widget_destroy(view);
}
