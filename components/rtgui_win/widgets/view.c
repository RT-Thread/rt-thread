/*
 * File      : view.c
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
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/view.h>

static void _rtgui_view_constructor(rtgui_view_t *view)
{
	/* init view */
	rtgui_widget_set_event_handler(view,rtgui_view_event_handler);

	RTGUI_WIDGET_BORDER_STYLE(view) = RTGUI_BORDER_NONE;
	view->title = RT_NULL;
}

static void _rtgui_view_destructor(rtgui_view_t *view)
{
	rt_free(view->title);
}

rtgui_type_t *rtgui_view_type_get(void)
{
	static rtgui_type_t *view_type = RT_NULL;

	if(!view_type)
	{
		view_type = rtgui_type_create("view", RTGUI_CONTAINER_TYPE,
			sizeof(rtgui_view_t), 
			RTGUI_CONSTRUCTOR(_rtgui_view_constructor), 
			RTGUI_DESTRUCTOR(_rtgui_view_destructor));
	}

	return view_type;
}

rtgui_view_t* rtgui_view_create(PVOID parent,const char* title,int left,int top,int w,int h)
{
	rtgui_view_t* view;

	RT_ASSERT(parent != RT_NULL);

	/* allocate view */
	view = rtgui_widget_create (RTGUI_VIEW_TYPE);
	if(view != RT_NULL)
	{
		rtgui_rect_t rect;
		rtgui_widget_get_rect(parent,&rect);
		rtgui_widget_rect_to_device(parent, &rect);
		rect.x1 += left;
		rect.y1 += top;
		rect.x2 = rect.x1+w;
		rect.y2 = rect.y1+h;
		rtgui_widget_set_rect(view,&rect);

		if(title != RT_NULL)
			view->title = rt_strdup(title);

		rtgui_container_add_child(parent, view);
	}

	return view;
}

void rtgui_view_destroy(rtgui_view_t* view)
{
	rtgui_widget_destroy(view);
}

rt_bool_t rtgui_view_event_handler(PVOID wdt, rtgui_event_t* event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_view_t* view = (rtgui_view_t*) widget;
	
	RT_ASSERT(wdt != RT_NULL);

	switch (event->type)
	{
		case RTGUI_EVENT_PAINT:		
			if(widget->on_draw != RT_NULL) 
				widget->on_draw(widget, event);
			else
			{
				rtgui_rect_t rect;
				rtgui_dc_t* dc;
				
				/* begin drawing */
				dc = rtgui_dc_begin_drawing(view);
				if(dc == RT_NULL)return RT_FALSE;
				
				rtgui_widget_get_rect(view, &rect);
				/* fill view with background */
				rtgui_dc_fill_rect(dc, &rect);
				
				if(RTGUI_WIDGET_BORDER(view)>0)
					rtgui_dc_draw_border(dc,&rect,RTGUI_WIDGET_BORDER_STYLE(view));

				rtgui_dc_end_drawing(dc);

				/* paint on each child */
				rtgui_container_dispatch_event(RTGUI_CONTAINER(view), event);
			}
			break;
	
		default:
			return rtgui_container_event_handler(widget, event);
	}

	return RT_FALSE;
}

rt_bool_t rtgui_view_show(rtgui_view_t* view)
{
	/* parameter check */
	if(view == RT_NULL) return RT_FALSE;

	//该句放在后面
	rtgui_widget_show(view);

	/* no modal mode, always return modal_ok */
	return RT_TRUE;
}


void rtgui_view_hide(rtgui_view_t* view)
{
	if(view == RT_NULL) return;

	if(RTGUI_WIDGET_PARENT(view) == RT_NULL)
	{
		RTGUI_WIDGET_HIDE(view);
		return;
	}

	rtgui_widget_hide(view);
}

char* rtgui_view_get_title(rtgui_view_t* view)
{
	RT_ASSERT(view != RT_NULL);

	return view->title;
}

void rtgui_view_set_title(rtgui_view_t* view, const char *title)
{
	RT_ASSERT(view != RT_NULL);

	rt_free(view->title);
	
	if(title != RT_NULL) 
		view->title = rt_strdup(title);
	else 
		view->title = RT_NULL;
}

//显示一个视图下指定名称的子视图
void rtgui_view_show_child(PVOID wdt,const char* name)
{
	rtgui_list_t* node;
	rtgui_container_t *container = (rtgui_container_t*)wdt;

	rtgui_list_foreach(node, &(container->children))
	{
		rtgui_widget_t* child = rtgui_list_entry(node, rtgui_widget_t, sibling);
		if(RTGUI_IS_VIEW(child))
		{
			if(strcmp(RTGUI_VIEW(child)->title,name)==0)
			{	
				RTGUI_WIDGET_UNHIDE(child);
			}
			else
			{	
				RTGUI_WIDGET_HIDE(child);
			}	
		}
	}
	rtgui_widget_update_clip(wdt);
	rtgui_widget_update(wdt);
}



