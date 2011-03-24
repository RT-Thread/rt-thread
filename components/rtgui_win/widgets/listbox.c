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

#define RTGUI_WIDGET_DEFAULT_MARGIN		3

static rt_bool_t rtgui_listbox_unfocus(PVOID wdt, rtgui_event_t* event);
static rt_bool_t rtgui_listbox_sbar_handle(PVOID wdt, rtgui_event_t* event);
static rt_uint32_t rtgui_listbox_get_item_count(rtgui_listbox_t* box);
static void rtgui_listbox_add_item(rtgui_listbox_t* box,rtgui_listbox_item_t* item);

static void _rtgui_listbox_constructor(rtgui_listbox_t *box)
{
	/* set default widget rect and set event handler */
	rtgui_widget_set_event_handler(box,rtgui_listbox_event_handler);
	rtgui_widget_set_onunfocus(box, rtgui_listbox_unfocus);
	RTGUI_WIDGET_FLAG(box) |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	box->frist_aloc = 0;	
	box->now_aloc = 0;
	box->old_aloc = 0;		
	box->item_count = 0;
	box->item_size	= SELECTED_HEIGHT;
	box->item_per_page = 0;	
	box->ispopup = RT_FALSE;
	box->widgetlnk = RT_NULL;		
	
	RTGUI_WIDGET_BACKGROUND(box) = white;
	RTGUI_WIDGET_TEXTALIGN(box) = RTGUI_ALIGN_LEFT|RTGUI_ALIGN_CENTER_VERTICAL;

	box->items = RT_NULL;
	box->sbar = RT_NULL;

	box->on_item = RT_NULL;

	box->get_count = rtgui_listbox_get_item_count;
	box->add_item = rtgui_listbox_add_item;
}
static void _rtgui_listbox_destructor(rtgui_listbox_t *box)
{

}

rtgui_type_t *rtgui_listbox_type_get(void)
{
	static rtgui_type_t *listbox_type = RT_NULL;

	if(!listbox_type)
	{
		listbox_type = rtgui_type_create("listbox", RTGUI_CONTAINER_TYPE,
			sizeof(rtgui_listbox_t),
			RTGUI_CONSTRUCTOR(_rtgui_listbox_constructor), 
			RTGUI_DESTRUCTOR(_rtgui_listbox_destructor));
	}

	return listbox_type;
}

rtgui_listbox_t* rtgui_listbox_create(PVOID parent, int left,int top,int w,int h,rt_uint32_t style)
{
	rtgui_listbox_t* box = RT_NULL;

	RT_ASSERT(parent != RT_NULL);

	box = rtgui_widget_create(RTGUI_LISTBOX_TYPE);
	if(box != RT_NULL)
	{
		rtgui_rect_t rect;    
		rtgui_widget_get_rect(parent,&rect);
		rtgui_widget_rect_to_device(parent, &rect);
		rect.x1 += left;
		rect.y1 += top;
		rect.x2 = rect.x1+w;
		rect.y2 = rect.y1+h;
		rtgui_widget_set_rect(box,&rect);
		rtgui_container_add_child(parent, box);

		rtgui_widget_set_style(box,style);

		if(box->sbar == RT_NULL)
		{//创建卷标控件
			rt_uint32_t sLeft,sTop,sWidth=RTGUI_DEFAULT_SB_WIDTH,sLen;
			sLeft = rtgui_rect_width(rect)-RTGUI_WIDGET_BORDER(box)-sWidth;
			sTop = RTGUI_WIDGET_BORDER(box);
			sLen = rtgui_rect_height(rect)-RTGUI_WIDGET_BORDER(box)*2;
	
			box->sbar = rtgui_scrollbar_create(box,sLeft,sTop,sWidth,sLen,RTGUI_VERTICAL);
			
			if(box->sbar != RT_NULL)
			{
				box->sbar->widgetlnk = (PVOID)box;
				box->sbar->on_scroll = rtgui_listbox_sbar_handle;
				RTGUI_WIDGET_HIDE(box->sbar);//默认隐藏滚动条		
			}
		}
	}

	return box;
}

void rtgui_listbox_set_items(rtgui_listbox_t* box, rtgui_listbox_item_t* items, rt_uint32_t count)
{
	rtgui_rect_t rect;
	rt_uint32_t i,h;;

	RT_ASSERT(box != RT_NULL);

	if(box->items != RT_NULL)
	{
		rt_free(box->items);
		box->items = RT_NULL;
	}
	//支持增加/删除项目,动态空间
	box->items = (rtgui_listbox_item_t*) rt_malloc(sizeof(rtgui_listbox_item_t)*count);
	if(box->items == RT_NULL) return;

	for(i=0;i<count;i++)
	{
		box->items[i].name = rt_strdup(items[i].name);
		box->items[i].image = items[i].image;	
	}

	box->item_count = count;
	box->now_aloc = 0;
	box->old_aloc = 0;

	rtgui_widget_get_rect(box, &rect);

	box->item_per_page = rtgui_rect_height(rect) / (box->item_size+2);
	
	if(box->ispopup)//弹出式下拉列表,例如点击combo控件之后
	{
		if(box->item_count < 5)
			box->item_per_page = count;	
		else
			box->item_per_page = 5;

		h = 2+(box->item_size+2)*box->item_per_page;
		rect.y2 = rect.y1+h;
		rtgui_widget_rect_to_device(box,&rect);
		rtgui_widget_set_rect(box,&rect);//更新box的大小

		if(box->sbar != RT_NULL)    //更新sbar的extent
		{	
			rtgui_widget_get_rect(box->sbar,&rect);
			rect.y2 = rect.y1+h-RTGUI_WIDGET_BORDER(box)*2;
			rtgui_widget_rect_to_device(box->sbar,&rect);
			rtgui_widget_set_rect(box->sbar,&rect);		
		}	
	}
	
	if(box->sbar != RT_NULL)//更新sbar的参数
	{	
		if(box->item_count > box->item_per_page)
		{
			RTGUI_WIDGET_UNHIDE(box->sbar);
			rtgui_scrollbar_set_line_step(box->sbar, 1);
			rtgui_scrollbar_set_page_step(box->sbar, box->item_per_page);
			rtgui_scrollbar_set_range(box->sbar, box->item_count);
		}
		else
		{
			RTGUI_WIDGET_HIDE(box->sbar);
		}
		rtgui_widget_update_clip(box);		
	}
	
}

void rtgui_listbox_destroy(rtgui_listbox_t* box)
{
    /* destroy box */
	rtgui_widget_destroy(box);
}

//绘制ListBox界面,绘制所有行
void rtgui_listbox_ondraw(rtgui_listbox_t* box)
{
	rtgui_rect_t rect, item_rect, image_rect;
	rt_uint16_t frist, i;
	const rtgui_listbox_item_t* item;
	rtgui_dc_t* dc;
	
	RT_ASSERT(box != RT_NULL);

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(box);
	if(dc == RT_NULL)return;

	rtgui_widget_get_rect(box, &rect);

	//绘制边框
	rtgui_dc_draw_border(dc, &rect,RTGUI_WIDGET_BORDER_STYLE(box));
	rtgui_rect_inflate(&rect,-RTGUI_WIDGET_BORDER(box));
	RTGUI_DC_BC(dc) = white;
	rtgui_dc_fill_rect(dc, &rect); 
	rtgui_rect_inflate(&rect,RTGUI_WIDGET_BORDER(box));
	
	if(box->items==RT_NULL)return;//没有项目,则不再绘制内容

	if(box->sbar && !RTGUI_WIDGET_IS_HIDE(box->sbar))
	{	
		rect.x2 -= rtgui_rect_width(box->sbar->parent.extent);
	}

	/* get item base rect */
	item_rect = rect;
	item_rect.x1 += RTGUI_WIDGET_BORDER(box); 
	item_rect.x2 -= RTGUI_WIDGET_BORDER(box);
	item_rect.y1 += RTGUI_WIDGET_BORDER(box);
	item_rect.y2 = item_rect.y1 + (2+box->item_size);

	/* get frist aloc */
	frist = box->frist_aloc;
	for(i = 0; i < box->item_per_page; i ++)
	{
		if(frist + i >= box->item_count) break;

		item = &(box->items[frist + i]);

		if(frist + i == box->now_aloc)
		{//draw current item
			if(RTGUI_WIDGET_IS_FOCUSED(box))
			{	
				RTGUI_DC_BC(dc) = selected_color;
				RTGUI_DC_FC(dc) = white;
				rtgui_dc_fill_rect(dc, &item_rect);
				rtgui_dc_draw_focus_rect(dc, &item_rect); //绘制焦点框
			}
			else
			{
				RTGUI_DC_BC(dc) = dark_grey;
				RTGUI_DC_FC(dc) = black;
				rtgui_dc_fill_rect(dc, &item_rect);
			}
		}
		item_rect.x1 += RTGUI_WIDGET_DEFAULT_MARGIN;

		if(item->image != RT_NULL)
		{
			/* get image base rect */
			image_rect.x1 = 0; 
			image_rect.y1 = 0;
			image_rect.x2 = item->image->w; 
			image_rect.y2 = item->image->h;
			rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);
			rtgui_image_paste(item->image, dc, &image_rect, white);
			item_rect.x1 += item->image->w + 2;
		}
        /* draw text */
		if(frist + i == box->now_aloc && RTGUI_WIDGET_IS_FOCUSED(box))
		{
			RTGUI_DC_FC(dc) = white;
			rtgui_dc_draw_text(dc, item->name, &item_rect);
		}
		else
		{
			RTGUI_DC_FC(dc) = black;
			rtgui_dc_draw_text(dc, item->name, &item_rect);
		}

        if(item->image != RT_NULL)
            item_rect.x1 -= (item->image->w + 2);
		item_rect.x1 -= RTGUI_WIDGET_DEFAULT_MARGIN;

        /* move to next item position */
		item_rect.y1 += (box->item_size + 2);
		item_rect.y2 += (box->item_size + 2);
	}

	if(box->sbar && !RTGUI_WIDGET_IS_HIDE(box->sbar))
	{
		rtgui_theme_draw_scrollbar(box->sbar);
	}

	rtgui_dc_end_drawing(dc);
}

//更新ListBox界面,只处理新旧焦点行
void rtgui_listbox_update(rtgui_listbox_t* box)
{
	const rtgui_listbox_item_t* item;
	rtgui_rect_t rect, item_rect, image_rect;
	rtgui_dc_t* dc;
	
	RT_ASSERT(box != RT_NULL);
	
	if(RTGUI_WIDGET_IS_HIDE(box))return;
	if(box->items==RT_NULL)return;

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(box);
	if(dc == RT_NULL)return;

	rtgui_widget_get_rect(box, &rect);
	if(box->sbar && !RTGUI_WIDGET_IS_HIDE(box->sbar))
	{
		rect.x2 -= rtgui_rect_width(box->sbar->parent.extent);
	}

	if((box->old_aloc >= box->frist_aloc) && /* 在之后某页中 */
	   (box->old_aloc < box->frist_aloc+box->item_per_page) && /* 在之前某页中 */
	   (box->old_aloc != box->now_aloc)) /* 位置没有变化,不需要刷旧行 */
	{//这些条件,可以最大限度的减少绘图闪烁现象
		item_rect = rect;
		/* get old item's rect */
		item_rect.x1 += RTGUI_WIDGET_BORDER(box); 
		item_rect.x2 -= RTGUI_WIDGET_BORDER(box);
		item_rect.y1 += RTGUI_WIDGET_BORDER(box);
		item_rect.y1 += ((box->old_aloc-box->frist_aloc) % box->item_per_page) * (2 + box->item_size);
		item_rect.y2 = item_rect.y1 + (2+box->item_size);
	
		/* draw old item */
		RTGUI_DC_BC(dc) = white;
		RTGUI_DC_FC(dc) = black;
		rtgui_dc_fill_rect(dc,&item_rect);
	
		item_rect.x1 += RTGUI_WIDGET_DEFAULT_MARGIN;
	
		item = &(box->items[box->old_aloc]);
		if(item->image != RT_NULL)
		{
			image_rect.x1 = 0; 
			image_rect.y1 = 0;
			image_rect.x2 = item->image->w; 
			image_rect.y2 = item->image->h;
			rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);
			rtgui_image_paste(item->image, dc, &image_rect, white);
			item_rect.x1 += item->image->w + 2;
		}
		rtgui_dc_draw_text(dc, item->name, &item_rect);
	}

	/* draw now item */
	item_rect = rect;
	/* get now item's rect */
	item_rect.x1 += RTGUI_WIDGET_BORDER(box); 
	item_rect.x2 -= RTGUI_WIDGET_BORDER(box);
	item_rect.y1 += RTGUI_WIDGET_BORDER(box);
	item_rect.y1 += ((box->now_aloc-box->frist_aloc) % box->item_per_page) * (2 + box->item_size);
	item_rect.y2 = item_rect.y1 + (2 + box->item_size);

	/* draw current item */
	if(RTGUI_WIDGET_IS_FOCUSED(box))
	{	
		RTGUI_DC_BC(dc) = selected_color;
		RTGUI_DC_FC(dc) = white;
		rtgui_dc_fill_rect(dc, &item_rect);
		rtgui_dc_draw_focus_rect(dc, &item_rect); //绘制焦点框
	}
	else
	{
		RTGUI_DC_BC(dc) = dark_grey;
		RTGUI_DC_FC(dc) = black;
		rtgui_dc_fill_rect(dc, &item_rect);
	}

	item_rect.x1 += RTGUI_WIDGET_DEFAULT_MARGIN;

	item = &(box->items[box->now_aloc]);
	if(item->image != RT_NULL)
	{
		image_rect.x1 = 0; 
		image_rect.y1 = 0;
		image_rect.x2 = item->image->w; 
		image_rect.y2 = item->image->h;
		rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);
		rtgui_image_paste(item->image, dc, &image_rect, white);
        item_rect.x1 += (item->image->w + 2);
	}
	if(RTGUI_WIDGET_IS_FOCUSED(box))
	{
		RTGUI_DC_FC(dc) = white;
		rtgui_dc_draw_text(dc, item->name, &item_rect);
	}
	else
	{
		RTGUI_DC_FC(dc) = black;
		rtgui_dc_draw_text(dc, item->name, &item_rect);
	}
	box->old_aloc = box->now_aloc;

	rtgui_dc_end_drawing(dc);
}

rt_bool_t rtgui_listbox_event_handler(PVOID wdt, rtgui_event_t* event)
{
	rtgui_listbox_t* box = (rtgui_listbox_t*)wdt;
	
	RT_ASSERT(box != RT_NULL);

	switch (event->type)
	{
		case RTGUI_EVENT_PAINT:
		{
			rtgui_dc_t *dc;

			dc = rtgui_dc_begin_drawing(box);
			if(dc == RT_NULL)return RT_FALSE;

			if(!RTGUI_WIDGET_IS_FOCUSED(box))
			{
				rtgui_rect_t rect;
				rtgui_widget_get_rect(box, &rect);
				rtgui_dc_fill_rect(dc,&rect);
			}	

			rtgui_dc_end_drawing(dc);

			rtgui_listbox_ondraw(box);
			return RT_FALSE;
		}
	    case RTGUI_EVENT_RESIZE:
	        {
				rtgui_event_resize_t* resize;
	
				resize = (rtgui_event_resize_t*)event;
	
	            /* recalculate page items */
				box->item_per_page = resize->h  / (2 + box->item_size);
	        }
	        break;
	
		case RTGUI_EVENT_MOUSE_BUTTON: 
			{
				rtgui_rect_t rect;
				rtgui_event_mouse_t* emouse;
	
				emouse = (rtgui_event_mouse_t*)event;
	
				/* get physical extent information */
				rtgui_widget_get_rect(box, &rect);
				if(box->sbar && !RTGUI_WIDGET_IS_HIDE(box->sbar))
					rect.x2 -= rtgui_rect_width(box->sbar->parent.extent);
	
				if((rtgui_region_contains_point(&RTGUI_WIDGET_CLIP(box), emouse->x, emouse->y,&rect) == RT_EOK) && (box->item_count > 0))
				{
					rt_uint16_t i;
					i = (emouse->y - rect.y1) / (2 + box->item_size);
	
					/* set focus */
					rtgui_widget_focus(box);
	
					if((i < box->item_count) && (i < box->item_per_page))
					{
						if(emouse->button & RTGUI_MOUSE_BUTTON_DOWN)
						{
							box->old_aloc = box->now_aloc;
							/* set selected item */
							box->now_aloc = box->frist_aloc + i;

							if(box->on_item != RT_NULL)
							{	
								box->on_item(box, RT_NULL);
							}

							/* down event */
							rtgui_listbox_update(box);
						}
						else if(emouse->button & RTGUI_MOUSE_BUTTON_UP)
						{
							rtgui_listbox_update(box);

							if(box->ispopup && !RTGUI_WIDGET_IS_HIDE(box))
							{
								RTGUI_WIDGET_HIDE(box);
								box->frist_aloc=0;
								box->now_aloc = 0;

								rtgui_widget_update_clip(RTGUI_WIDGET_PARENT(box));
								rtgui_widget_update(RTGUI_WIDGET_PARENT(box));
								return RT_TRUE;	
							}
						}
						if(box->sbar && !RTGUI_WIDGET_IS_HIDE(box))
						{
							if(!RTGUI_WIDGET_IS_HIDE(box->sbar))
								rtgui_scrollbar_set_value(box->sbar,box->frist_aloc);
						}
					}
				}
				
			}
			break;

	    case RTGUI_EVENT_KBD:
        {
            rtgui_event_kbd_t* ekbd = (rtgui_event_kbd_t*)event;
            if((RTGUI_KBD_IS_DOWN(ekbd)) && (box->item_count > 0))
            {
				switch (ekbd->key)
                {
	                case RTGUIK_UP:
						if(box->now_aloc > 0)
						{
							box->old_aloc = box->now_aloc;
							box->now_aloc --;
							if(box->now_aloc < box->frist_aloc)
							{
								if(box->frist_aloc)box->frist_aloc--;
								rtgui_listbox_ondraw(box);
							}
							else
							{
								rtgui_listbox_update(box);
							}

							if(box->sbar && !RTGUI_WIDGET_IS_HIDE(box))
							{
								if(!RTGUI_WIDGET_IS_HIDE(box->sbar))
									rtgui_scrollbar_set_value(box->sbar,box->frist_aloc);
							}

							if(box->on_item != RT_NULL)
							{
								box->on_item(box, RT_NULL);
							}
						}
						break;

	                case RTGUIK_DOWN:
						if(box->now_aloc < box->item_count - 1)
						{
							box->old_aloc = box->now_aloc;
							box->now_aloc ++;
							if(box->now_aloc >= box->frist_aloc+box->item_per_page)
							{
								box->frist_aloc++;
								rtgui_listbox_ondraw(box);
							}
							else
							{
								rtgui_listbox_update(box);
							}
							if(box->sbar && !RTGUI_WIDGET_IS_HIDE(box))
							{
								if(!RTGUI_WIDGET_IS_HIDE(box->sbar))
									rtgui_scrollbar_set_value(box->sbar,box->frist_aloc);
							}

							if(box->on_item != RT_NULL)
							{
								box->on_item(box, RT_NULL);
							}
						}
						break;
	
					case RTGUIK_RETURN:
	                    if(box->on_item != RT_NULL)
						{
							box->on_item(box, RT_NULL);
						}
						
						if(box->ispopup && !RTGUI_WIDGET_IS_HIDE(box))
						{
							RTGUI_WIDGET_HIDE(box);
							box->frist_aloc=0;
							box->now_aloc = 0;
							rtgui_widget_update_clip(RTGUI_WIDGET_PARENT(box));
							rtgui_widget_update(RTGUI_WIDGET_PARENT(box));
						}
						break;
	
	                default:
	                    break;
                }
            }
			return RT_FALSE;
        }
		default:  
			return rtgui_container_event_handler(box, event);
	}

    /* use box event handler */
    return rtgui_container_event_handler(box, event);
}

void rtgui_listbox_set_onitem(rtgui_listbox_t* box, rtgui_event_handler_ptr func)
{
	if(box == RT_NULL) return;

	box->on_item = func;
}

void rtgui_listbox_delete_item(rtgui_listbox_t* box, rt_uint32_t item_num)
{
	rtgui_listbox_item_t* _items;
	rt_base_t i;

	if(box == RT_NULL) return;

	for(i=item_num;i<box->item_count-1;i++)
	{
		if(box->items[i].name != RT_NULL)	
		{
			rt_free(box->items[i].name);
			box->items[i].name = RT_NULL;
		}
		box->items[i].name = box->items[i+1].name;
		box->items[i].image = box->items[i+1].image;
	}

	box->item_count -= 1;
	_items = rt_realloc(box->items,sizeof(rtgui_listbox_item_t)*(box->item_count));
	if(_items != RT_NULL)	
	{
		box->items = _items;
	}

	rtgui_listbox_ondraw(box);
}

static void rtgui_listbox_add_item(rtgui_listbox_t* box,rtgui_listbox_item_t* item)
{
	rtgui_listbox_item_t* _items;
	RT_ASSERT(box != RT_NULL);

	if(box->item_count==0)
	{
		_items = rt_malloc(sizeof(rtgui_listbox_item_t)*(box->item_count+1));
	}
	else
	{
		_items = rt_realloc(box->items,sizeof(rtgui_listbox_item_t)*(box->item_count+1));
	}
	
	if(_items != RT_NULL)	
	{
		box->items = _items;
		box->items[box->item_count].name = rt_strdup(item->name);
		box->items[box->item_count].image= item->image;
		box->item_count += 1;
		
		if(box->sbar != RT_NULL)		
		{
			if(RTGUI_WIDGET_IS_HIDE(box->sbar))
			{
				if(box->item_count > box->item_per_page)
				{
					RTGUI_WIDGET_UNHIDE(box->sbar);
					rtgui_scrollbar_set_line_step(box->sbar, 1);
					rtgui_scrollbar_set_page_step(box->sbar, box->item_per_page);
					rtgui_scrollbar_set_range(box->sbar, box->item_count);
				}
				else
				{
					RTGUI_WIDGET_HIDE(box->sbar);
				}
				rtgui_widget_update_clip(box);
			}
			else
			{
				rtgui_scrollbar_set_range(box->sbar, box->item_count);	
			}
		}
		
		if(!RTGUI_WIDGET_IS_HIDE(box))
			rtgui_listbox_ondraw(box);
	}
}

static rt_uint32_t rtgui_listbox_get_item_count(rtgui_listbox_t* box)
{
	return box->item_count;
}

static rt_bool_t rtgui_listbox_unfocus(PVOID wdt, rtgui_event_t* event)
{
	rtgui_listbox_t *box = (rtgui_listbox_t*)wdt;
	if(box == RT_NULL)return RT_FALSE;

	if(!RTGUI_WIDGET_IS_FOCUSED(box))
	{//清除焦点框
		rtgui_listbox_update(RTGUI_LISTBOX(wdt));
	}

	if(box->ispopup)
	{//是弹出列表,说明是挂在一些控件(例如combo)下的
		rtgui_win_t *win;

		RTGUI_WIDGET_HIDE(box);
		box->frist_aloc=0;
		box->now_aloc = 0;
		
		//rtgui_widget_update_clip(RTGUI_WIDGET_PARENT(box));
		//rtgui_widget_update_clip_pirate(RTGUI_WIDGET_PARENT(box),box);
		win = rtgui_win_get_win_by_widget(box);
		if(win != RT_NULL)
		{//在一个窗口中
			if(rtgui_rect_is_intersect(&(RTGUI_WIDGET_EXTENT(win)), 
				&(RTGUI_WIDGET_EXTENT(box))) == RT_EOK)
			{
				rtgui_topwin_move(win,RTGUI_WIDGET_EXTENT(win).x1,
					RTGUI_WIDGET_EXTENT(win).y1);
			}
			rtgui_widget_focus(win);
			rtgui_widget_update_clip(win);
		}
		rtgui_panel_redraw(&(RTGUI_WIDGET_EXTENT(box)));	
	}

	return RT_TRUE;
}

static rt_bool_t rtgui_listbox_sbar_handle(PVOID wdt, rtgui_event_t* event)
{
	rtgui_listbox_t *box = (rtgui_listbox_t*)wdt;

	//拖动时，改变第一行
	box->frist_aloc = box->sbar->value;	

	rtgui_listbox_ondraw(box);	

	return RT_TRUE;
}

