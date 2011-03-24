//组合框控件

#include <rtgui/dc.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/combobox.h>

static rt_uint32_t rtgui_combo_get_count(rtgui_combo_t* cbo);
static void rtgui_combo_add_string(rtgui_combo_t* cbo, char* string);

static void _rtgui_combobox_constructor(rtgui_combo_t *cbo)
{
	RTGUI_WIDGET_FLAG(cbo) |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	cbo->style = RTGUI_COMBO_STYLE_DOWNARROW_UP;
	cbo->lbox = RT_NULL;
	cbo->tbox = RT_NULL;

	rtgui_widget_set_event_handler(cbo, rtgui_combo_event_handler);

	RTGUI_WIDGET_BACKGROUND(cbo) = white;
	/* set default text align */
	RTGUI_WIDGET_TEXTALIGN(cbo) = RTGUI_ALIGN_CENTER_VERTICAL;
	rtgui_widget_set_style(cbo, RTGUI_BORDER_SUNKEN);
	cbo->on_selected = RT_NULL;
	cbo->get_count = rtgui_combo_get_count;
	cbo->add_string = rtgui_combo_add_string;
}

static void _rtgui_combobox_destructor(rtgui_combo_t *cbo)
{

}

rtgui_type_t *rtgui_combo_type_get(void)
{
	static rtgui_type_t *combo_type = RT_NULL;

	if(!combo_type)
	{
		combo_type = rtgui_type_create("combobox", RTGUI_CONTAINER_TYPE,
			sizeof(rtgui_combo_t),
			RTGUI_CONSTRUCTOR(_rtgui_combobox_constructor),
			RTGUI_DESTRUCTOR(_rtgui_combobox_destructor));
	}

	return combo_type;
}

rtgui_combo_t* rtgui_combo_create(PVOID parent,const char* text,int left,int top,int w,int h)
{
	rtgui_combo_t* cbo;
	
	RT_ASSERT(parent != RT_NULL);

    cbo = rtgui_widget_create(RTGUI_COMBOBOX_TYPE);
    if(cbo != RT_NULL)
    {
		rtgui_rect_t rect;

		rtgui_widget_get_rect(parent, &rect);
		rtgui_widget_rect_to_device(parent,&rect);
		rect.x1 += left;
		rect.y1 += top;
		rect.x2 = rect.x1+w;
		rect.y2 = rect.y1+RTGUI_COMBOBOX_HEIGHT;
		rtgui_widget_set_rect(cbo,&rect);

		rtgui_container_add_child(parent, cbo);

		if(cbo->tbox == RT_NULL)
		{
			cbo->tbox = rtgui_textbox_create(cbo,text,
					RTGUI_WIDGET_BORDER(cbo),
					RTGUI_WIDGET_BORDER(cbo),
					w-RTGUI_COMBOBOX_BUTTON_WIDTH-RTGUI_WIDGET_BORDER(cbo)*2,
					h-RTGUI_WIDGET_BORDER(cbo)*2,RTGUI_TEXTBOX_NONE);

			if(cbo->tbox == RT_NULL) return RT_NULL;
			rtgui_widget_set_style(cbo->tbox,RTGUI_BORDER_NONE);
			cbo->tbox->isedit = RT_FALSE;//缺省combo的编辑框不可编辑	
		}
		if(cbo->lbox == RT_NULL)
		{//创建弹出的下拉列表
			rtgui_point_t point;
			rt_uint32_t mleft,mtop,mwidth;
	
			rtgui_widget_get_position(cbo, &point);
			mleft = point.x;
			mtop = point.y+RTGUI_COMBOBOX_HEIGHT;
			mwidth = rtgui_widget_get_width(cbo);	
				
			//创建下拉列表
			cbo->lbox = rtgui_listbox_create(parent,mleft,mtop,mwidth,4,RTGUI_BORDER_SIMPLE);
			if(cbo->lbox == RT_NULL)return RT_NULL;
			cbo->lbox->ispopup = RT_TRUE;
			cbo->lbox->widgetlnk = cbo;
			rtgui_listbox_set_onitem(cbo->lbox,rtgui_combo_onitem);
			
			RTGUI_WIDGET_HIDE(cbo->lbox);
		}
	}

	return cbo;
}

void rtgui_combo_destroy(rtgui_combo_t* cbo)
{
	rtgui_widget_destroy(cbo);
}

void rtgui_combo_set_onitem(rtgui_combo_t* cbo, rtgui_event_handler_ptr func)
{
	if(cbo == RT_NULL) return;

	if(cbo->lbox != RT_NULL)
	{
		rtgui_listbox_set_onitem(cbo->lbox,func);
	}
}

rt_uint32_t rtgui_combo_get_select(rtgui_combo_t* cbo)
{
	return cbo->lbox->now_aloc;
}

char* rtgui_combo_get_string(rtgui_combo_t* cbo)
{
	if(cbo->lbox->items != RT_NULL)
	{
		return cbo->lbox->items[cbo->lbox->now_aloc].name;
	}

	return RT_NULL;
}

//返回项目的编号
rt_bool_t rtgui_combo_onitem(PVOID wdt, rtgui_event_t* event)
{
	rtgui_listbox_t* box = (rtgui_listbox_t*)wdt;

	if(box != RT_NULL && box->ispopup)
	{
		char *str;
		rtgui_combo_t* cbo=box->widgetlnk;
		if(cbo==RT_NULL)return RT_FALSE;

		str = rtgui_combo_get_string(cbo);
		
		rtgui_textbox_set_value(cbo->tbox,str);
	}
	
	return RT_TRUE;	
}

void rtgui_combo_get_downarrow_rect(rtgui_combo_t* cbo, rtgui_rect_t* rect)
{
	rtgui_widget_get_rect(cbo, rect);
	rect->x1 = rect->x2 - RTGUI_COMBOBOX_BUTTON_WIDTH;
}

static rt_uint32_t rtgui_combo_get_count(rtgui_combo_t* cbo)
{
	if(cbo->lbox)
	{
		return cbo->lbox->get_count(cbo->lbox);
	}
	return 0;
}

static void rtgui_combo_add_string(rtgui_combo_t* cbo,char* string)
{
	if(cbo->lbox != RT_NULL)
	{
		rtgui_listbox_item_t item;
		rtgui_rect_t rect;
		rt_uint32_t h,count;

		item.name = string;
		item.image = RT_NULL;	
		cbo->lbox->add_item(cbo->lbox,&item);
		
		rtgui_widget_get_rect(cbo->lbox, &rect);
		count = cbo->get_count(cbo);

		h = 2+(SELECTED_HEIGHT + 2)*count;

		if(h>rtgui_rect_height(rect))//可能需要更改控件的extent			
		{
			if(cbo->lbox->item_per_page<5)//每页显示条数小于5条才会更改
			{
				rect.y2 = rect.y1+h;
				rtgui_widget_rect_to_device(cbo->lbox,&rect);
				rtgui_widget_set_rect(cbo->lbox,&rect);//更新lbox的大小
				cbo->lbox->item_per_page = rtgui_rect_height(rect) / (SELECTED_HEIGHT+2);

				if(cbo->lbox->sbar != RT_NULL)//同时更新sbar的extent
				{
					rtgui_widget_get_rect(cbo->lbox->sbar, &rect);
					rect.y2 = rect.y1+h-RTGUI_WIDGET_BORDER(cbo->lbox)*2;
					rtgui_widget_rect_to_device(cbo->lbox->sbar,&rect);
					rtgui_widget_set_rect(cbo->lbox->sbar,&rect);

					if(cbo->lbox->item_count > cbo->lbox->item_per_page)
					{
						RTGUI_WIDGET_UNHIDE(cbo->lbox->sbar);
						rtgui_scrollbar_set_line_step(cbo->lbox->sbar, 1);
						rtgui_scrollbar_set_page_step(cbo->lbox->sbar, cbo->lbox->item_per_page);
						rtgui_scrollbar_set_range(cbo->lbox->sbar, cbo->lbox->item_count);
					}
					else
					{
						RTGUI_WIDGET_HIDE(cbo->lbox->sbar);
					}
					rtgui_widget_update_clip(cbo->lbox);		
				}
			}
		}
	}
}

void rtgui_combo_set_items(rtgui_combo_t* cbo, rtgui_listbox_item_t* items, rt_uint32_t count)
{
	if(cbo != RT_NULL && cbo->lbox != RT_NULL)
	{
		rtgui_listbox_set_items(cbo->lbox,items,count);
	}
}

rt_bool_t rtgui_combo_event_handler(PVOID wdt, rtgui_event_t* event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_combo_t* cbo = (rtgui_combo_t*) widget;
	
	
	RT_ASSERT(widget != RT_NULL);

	switch(event->type)
	{
		case RTGUI_EVENT_PAINT:		
			if(widget->on_draw != RT_NULL ) 
				widget->on_draw(widget, event);
			else			
				rtgui_theme_draw_combo(cbo);
			break;

		case RTGUI_EVENT_KBD:
			if(widget->on_key != RT_NULL) 
				widget->on_key(widget, event);

			return RT_TRUE;

		case RTGUI_EVENT_MOUSE_BUTTON:
		{
			rtgui_rect_t rect;
			rtgui_event_mouse_t* emouse = (rtgui_event_mouse_t*)event;
			rt_bool_t inclip=RT_EOK;

			if(cbo->tbox->isedit == RT_TRUE)
			{//编辑框可编辑时,只检测下拉按钮区域
				inclip = rtgui_region_contains_point(&RTGUI_WIDGET_CLIP(cbo),emouse->x,emouse->y,&rect);
			}
			else 
			{//检查全部区域
				inclip = (rtgui_region_contains_point(&RTGUI_WIDGET_CLIP(cbo),emouse->x,emouse->y,&rect) &&
						  rtgui_region_contains_point(&RTGUI_WIDGET_CLIP(cbo->tbox),emouse->x,emouse->y,&rect));
			}

			if(inclip == RT_EOK)
			{	
				rtgui_combo_get_downarrow_rect(cbo,&rect);
				if(emouse->button & RTGUI_MOUSE_BUTTON_DOWN)
				{
					if(rtgui_rect_contains_point(&rect,emouse->x,emouse->y) == RT_EOK)
					{//在下拉按钮上
						cbo->style = RTGUI_COMBO_STYLE_DOWNARROW_DOWN;
						rtgui_theme_draw_combo_downarrow(cbo);	
					}
					
					if(cbo->lbox != RT_NULL)
					{
						if(RTGUI_WIDGET_IS_HIDE(cbo->lbox))
						{//显示弹出列表
							RTGUI_WIDGET_UNHIDE(cbo->lbox);
							rtgui_widget_focus(cbo->lbox);
							rtgui_widget_update_clip_pirate(RTGUI_WIDGET_PARENT(cbo->lbox),cbo->lbox);
							//列表的位置置为0
							cbo->lbox->frist_aloc=0;
							cbo->lbox->now_aloc = 0;
							if(cbo->lbox->sbar != RT_NULL)
							{
								if(!RTGUI_WIDGET_IS_HIDE(cbo->lbox->sbar))
								{//滚动条的位置置为0
									rtgui_scrollbar_set_value(cbo->lbox->sbar,cbo->lbox->frist_aloc);
								}
							}
							rtgui_widget_update(RTGUI_WIDGET_PARENT(cbo->lbox));
						}
						else
						{//隐藏弹出列表
							RTGUI_WIDGET_HIDE(cbo->lbox);
							rtgui_widget_unfocus(cbo->lbox);
						}
					}
				}
				else if(emouse->button & RTGUI_MOUSE_BUTTON_UP)
				{	
					if(rtgui_region_contains_point(&RTGUI_WIDGET_CLIP(cbo),emouse->x,emouse->y,&rect) == RT_EOK)
					{//在下拉按钮上
						cbo->style = RTGUI_COMBO_STYLE_DOWNARROW_UP;
						rtgui_theme_draw_combo_downarrow(cbo);
					}
				}
			}
			else
				rtgui_view_event_handler(widget,event);
			
			break;
		}

		default:
			return rtgui_view_event_handler(widget,event);
	}

	return RT_FALSE;
}


