/*
 * File      : widget.c
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-04     Bernard      first version
 */
#include <rtgui/dc_client.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/combobox.h>
#include <rtgui/widgets/view.h> 
#include <rtgui/widgets/listbox.h>
#include <panel.h>
#include <rtgui/dc.h>
#include <topwin.h>


static void _rtgui_widget_constructor(PVOID wdt)
{
    rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
    if(!widget) return;

	/* set default flag */
	widget->flag = RTGUI_WIDGET_FLAG_DEFAULT;
	
	/* init list */
	rtgui_list_init(&(widget->sibling));

	/* init gc */
	widget->gc.foreground = default_foreground;
	widget->gc.background = default_background;
	widget->gc.font = rtgui_font_default();
	widget->gc.textstyle = RTGUI_TEXTSTYLE_NORMAL;
	widget->gc.textalign = RTGUI_ALIGN_CENTER_HORIZONTAL|RTGUI_ALIGN_CENTER_VERTICAL;
#ifndef RTGUI_USING_SMALL_SIZE
	widget->align = RTGUI_ALIGN_CENTER_VERTICAL;
#endif
	rtgui_widget_set_style(widget,RTGUI_BORDER_SUNKEN);

	widget->tab_index 		= 0;
	widget->tab_stop 		= RT_FALSE;
	/* set parent and toplevel */
	widget->parent			= RT_NULL;
	widget->toplevel		= RT_NULL;

	/* some common event handler */
	widget->on_focus_in		= RT_NULL;
	widget->on_focus_out	= RT_NULL;
	widget->on_draw 		= RT_NULL;
	widget->on_mouseclick 	= RT_NULL;
	widget->on_key 			= RT_NULL;
	widget->on_size 		= RT_NULL;
	widget->on_command 		= RT_NULL;

	/* set default event handler */
	rtgui_widget_set_event_handler(widget,rtgui_widget_event_handler);

	/* init user data private to 0 */
	widget->user_data = 0;

	/* init clip information */
	rtgui_region_init(&(widget->clip));

	/* init hardware dc */
	rtgui_dc_client_init(widget);
}

/* Destroys the widget */
static void _rtgui_widget_destructor(PVOID wdt)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	if(widget == RT_NULL) return;

	if(widget->parent != RT_NULL)
	{
		/* remove widget from parent's child list */
		rtgui_list_remove(&(RTGUI_CONTAINER(widget->parent)->children), &(widget->sibling));

		widget->parent = RT_NULL;
	}

	/* fini clip region */
	rtgui_region_fini(&(widget->clip));
}

rtgui_type_t *rtgui_widget_type_get(void)
{
	static rtgui_type_t *widget_type = RT_NULL;

	if(!widget_type)
	{
		widget_type = rtgui_type_create("rtgui_widget", RTGUI_OBJECT_TYPE,
			sizeof(rtgui_widget_t), 
			RTGUI_CONSTRUCTOR(_rtgui_widget_constructor),
			RTGUI_DESTRUCTOR(_rtgui_widget_destructor));
	}

	return widget_type;
}

PVOID rtgui_widget_create(rtgui_type_t *widget_type)
{
	PVOID widget;

	widget = rtgui_object_create(widget_type);

	return widget;
}

void rtgui_widget_destroy(PVOID wdt)
{
	rtgui_object_destroy(RTGUI_OBJECT(wdt));
}

void rtgui_widget_set_rect(PVOID wht, rtgui_rect_t* rect)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wht;
	if(widget == RT_NULL || rect == RT_NULL) return;

	widget->extent = *rect;

	/* it's not empty, fini it */
	if(rtgui_region_not_empty(&(widget->clip)))
	{
		rtgui_region_fini(&(widget->clip));
	}

	/* reset clip info */
	rtgui_region_init_with_extents(&(widget->clip), rect);
	if((widget->parent != RT_NULL) && (widget->toplevel != RT_NULL))
	{
		/* update widget clip */
		rtgui_widget_update_clip(widget->parent);
	}
}

//设置控件的外观样式
void rtgui_widget_set_style(PVOID wdt, rt_uint32_t style)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	RT_ASSERT(widget != RT_NULL);
	
	widget->border_style = style;
	switch(style)
	{
		case RTGUI_BORDER_NONE:
			widget->border = 0;
			break;

		case RTGUI_BORDER_STATIC:
		case RTGUI_BORDER_SIMPLE:
		case RTGUI_BORDER_UP:
		case RTGUI_BORDER_DOWN:
			widget->border = 1;
			break;

		case RTGUI_BORDER_RAISE:
		case RTGUI_BORDER_SUNKEN:
		case RTGUI_BORDER_BOX:
		case RTGUI_BORDER_EXTRA:
			widget->border = 2;
			break;

		default:
			widget->border = 2;
			break;	
	}	
}

/*
 * 这个函数移动控件和它的子控件到一个逻辑点
 */
void rtgui_widget_move_to_logic(PVOID wdt, int dx, int dy)
{
	rtgui_list_t* node;
	rtgui_widget_t* child;
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	
	if(widget == RT_NULL) return;

	rtgui_rect_moveto(&(widget->extent), dx, dy);

	/* move each child */
	if(RTGUI_IS_CONTAINER(widget))
	{
		rtgui_list_foreach(node, &(RTGUI_CONTAINER(widget)->children))
		{
			child = rtgui_list_entry(node, rtgui_widget_t, sibling);
			rtgui_widget_move_to_logic(child, dx, dy);
		}
	}
}

void rtgui_widget_set_event_handler(PVOID wdt, rtgui_event_handler_ptr handler)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	RT_ASSERT(widget != RT_NULL);

	RTGUI_WIDGET_EVENT_HANDLE(widget) = handler;
}
//返回绝对坐标的rect区域
void rtgui_widget_get_rect(PVOID wdt, rtgui_rect_t *rect)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	RT_ASSERT(widget != RT_NULL);

	if (rect != RT_NULL)
	{
		rect->x1 = rect->y1 = 0;
		rect->x2 = widget->extent.x2 - widget->extent.x1;
		rect->y2 = widget->extent.y2 - widget->extent.y1;
	}
}

void rtgui_widget_get_position(PVOID wdt, rtgui_point_t *p)
{
	rtgui_rect_t rect,parent_rect; 
	RT_ASSERT(wdt != RT_NULL && RTGUI_WIDGET_PARENT(wdt) != RT_NULL);

	rtgui_widget_get_rect(wdt, &rect);
	rtgui_widget_rect_to_device(wdt,&rect);
	rtgui_widget_get_rect(RTGUI_WIDGET_PARENT(wdt), &parent_rect);
	rtgui_widget_rect_to_device(RTGUI_WIDGET_PARENT(wdt),&parent_rect);

	p->x = rect.x1 - parent_rect.x1;
	p->y = rect.y1 - parent_rect.y1;
}

rt_uint16_t rtgui_widget_get_width(PVOID wdt)
{
	rtgui_rect_t rect={0};
	RT_ASSERT(wdt != RT_NULL);
	
	rtgui_widget_get_rect(wdt, &rect);
	return rtgui_rect_width(rect);	
}

rt_uint16_t rtgui_widget_get_height(PVOID wdt)
{
	rtgui_rect_t rect={0};
	RT_ASSERT(wdt != RT_NULL);
	
	rtgui_widget_get_rect(wdt, &rect);
	return rtgui_rect_height(rect);	
}

void rtgui_widget_set_onfocus(PVOID wdt, rtgui_event_handler_ptr handler)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	RT_ASSERT(widget != RT_NULL);

	widget->on_focus_in = handler;
}

void rtgui_widget_set_onunfocus(PVOID wdt, rtgui_event_handler_ptr handler)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	RT_ASSERT(widget != RT_NULL);

	widget->on_focus_out = handler;
}

void rtgui_widget_set_ondraw(PVOID wdt, rtgui_event_handler_ptr handler)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	RT_ASSERT(widget != RT_NULL);

	widget->on_draw = handler;
}

void rtgui_widget_set_onmouseclick(PVOID wdt, rtgui_event_handler_ptr handler)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	RT_ASSERT(widget != RT_NULL);

	widget->on_mouseclick = handler;
}

void rtgui_widget_set_onkey(PVOID wdt, rtgui_event_handler_ptr handler)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	RT_ASSERT(widget != RT_NULL);

	widget->on_key = handler;
}

void rtgui_widget_set_onsize(PVOID wdt, rtgui_event_handler_ptr handler)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	RT_ASSERT(widget != RT_NULL);

	widget->on_size = handler;
}

void rtgui_widget_set_oncommand(PVOID wdt, rtgui_event_handler_ptr handler)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	RT_ASSERT(widget != RT_NULL);

	widget->on_command = handler;
}

/**
 * find wdt's toplevel widget and return toplevel focused
 */
PVOID rtgui_widget_get_focus(PVOID wdt)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_widget_t *top;

	if(widget == RT_NULL)return RT_NULL;	

	top = rtgui_widget_get_toplevel(widget);

	if(RTGUI_IS_CONTAINER(top))
		return RTGUI_CONTAINER(top)->focused;

	return RT_NULL;
}

/**
 * @brief Focuses the widget. The focused widget is the widget which can receive the keyboard events
 * @param widget a widget
 * @note The widget has to be attached to a top widget, otherwise it will have no effect
 */
void rtgui_widget_focus(PVOID wdt)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_container_t *parent;

	if(widget == RT_NULL)return;

	if(!widget->parent || !widget->toplevel) return;
	if(!RTGUI_WIDGET_IS_FOCUSABLE(widget) || !RTGUI_WIDGET_IS_ENABLE(widget))
		return;
	
	/* set widget as focused */
	widget->flag |= RTGUI_WIDGET_FLAG_FOCUS;

	/* 取得旧的根控件和焦点控件 */
	parent = RTGUI_CONTAINER(widget->toplevel);	
	if(parent->focused == widget) return; /* it's the same focused widget */

	/* unfocused the old widget */
	if((parent->focused != RT_NULL) && !RTGUI_IS_WIN(parent->focused))	
		rtgui_widget_unfocus(parent->focused);

	/* set widget as focused widget in parent link */
	parent = RTGUI_CONTAINER(widget->parent);
	do 
	{
		parent->focused = widget;
		parent = RTGUI_CONTAINER(RTGUI_WIDGET_PARENT(parent));
	} while((parent != RT_NULL) && !RTGUI_WIDGET_IS_HIDE(parent));

	/* invoke on focus in call back */
	if(widget->on_focus_in != RT_NULL)
   		widget->on_focus_in(widget, RT_NULL);
}

/**
 * @brief Unfocused the widget
 * @param widget a widget
 */
void rtgui_widget_unfocus(PVOID wdt)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	if(widget == RT_NULL)return;

	if(!widget->toplevel || !RTGUI_WIDGET_IS_FOCUSED(widget))
		return;

	widget->flag &= ~RTGUI_WIDGET_FLAG_FOCUS;

	if(widget->on_focus_out != RT_NULL)
   		widget->on_focus_out(widget, RT_NULL);
		
	if(RTGUI_IS_CONTAINER(widget))
	{
		rtgui_list_t *node;
		rtgui_list_foreach(node,&(RTGUI_CONTAINER(widget)->children))
		{
			rtgui_widget_t *child = rtgui_list_entry(node, rtgui_widget_t, sibling);
			if(RTGUI_WIDGET_IS_HIDE(child))continue;
			rtgui_widget_unfocus(child);
		}
	}

	/* refresh widget 刷新控件 */
	//rtgui_widget_update(widget);//要除去该句,避免重复刷新
}

void rtgui_widget_point_to_device(PVOID wdt, rtgui_point_t* point)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	RT_ASSERT(widget != RT_NULL);

	if(point != RT_NULL)
	{
		point->x += widget->extent.x1;
		point->y += widget->extent.y1;
	}
}

void rtgui_widget_rect_to_device(PVOID wdt, rtgui_rect_t* rect)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	RT_ASSERT(widget != RT_NULL);

	if(rect != RT_NULL)
	{
		rect->x1 += widget->extent.x1;
		rect->x2 += widget->extent.x1;

		rect->y1 += widget->extent.y1;
		rect->y2 += widget->extent.y1;
	}
}

void rtgui_widget_point_to_logic(PVOID wdt, rtgui_point_t* point)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	RT_ASSERT(widget != RT_NULL);

	if(point != RT_NULL)
	{
		point->x -= widget->extent.x1;
		point->y -= widget->extent.y1;
	}
}

void rtgui_widget_rect_to_logic(PVOID wdt, rtgui_rect_t* rect)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	RT_ASSERT(widget != RT_NULL);

	if(rect != RT_NULL)
	{
		rect->x1 -= widget->extent.x1;
		rect->x2 -= widget->extent.x1;

		rect->y1 -= widget->extent.y1;
		rect->y2 -= widget->extent.y1;
	}
}

PVOID rtgui_widget_get_toplevel(PVOID wdt)
{
	rtgui_widget_t *top;
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	
	RT_ASSERT(widget != RT_NULL);

	if(widget->toplevel) 
		return (PVOID)(widget->toplevel);

	top = widget;
	/* get the top widget */
	while(top->parent != RT_NULL) top = top->parent;

	/* set top */
	widget->toplevel = top;

	return top;
}

rt_bool_t rtgui_widget_event_handler(PVOID wdt, rtgui_event_t* event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;

	switch (event->type)
	{
		case RTGUI_EVENT_PAINT:
			if(widget->on_draw != RT_NULL) return widget->on_draw(widget, event);
			break;
	
		case RTGUI_EVENT_KBD:
			if(widget->on_key != RT_NULL) return widget->on_key(widget, event);
			break;
	
		case RTGUI_EVENT_MOUSE_BUTTON:
			if(widget->on_mouseclick != RT_NULL) return widget->on_mouseclick(widget, event);
			break;
	
		case RTGUI_EVENT_COMMAND:
			if(widget->on_command != RT_NULL) return widget->on_command(widget, event);
			break;
	
		case RTGUI_EVENT_RESIZE:
			if(widget->on_size != RT_NULL) return widget->on_size(widget, event);
			break;
	}

	return RT_FALSE;
}

/*
 * This function updates the clip info of widget
 */
void rtgui_widget_update_clip(PVOID wdt)
{
	rtgui_list_t *node;
	rtgui_widget_t *parent;
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;

	/* no widget or widget is hide, no update clip */
	if(widget == RT_NULL || RTGUI_WIDGET_IS_HIDE(widget)) return;

	parent = widget->parent; 

	/* if there is no parent, do not update clip (please use toplevel widget API) */
	if(parent == RT_NULL) 
	{	
		rtgui_panel_t *panel = rtgui_panel_get();
		rtgui_panel_update_clip(panel);
		return;
	}

	/* reset clip to extent */
	rtgui_region_reset(&(widget->clip), &(widget->extent));
	
	/* limit widget extent in screen extent */
	//rtgui_region_intersect(&(widget->clip), &(widget->clip), &(parent->clip));
	{
		rtgui_rect_t screen_rect;
		rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(),&screen_rect);
		//rtgui_region_intersect_rect(&(widget->clip), &(widget->clip), &(parent->clip.extents));
		rtgui_region_intersect_rect(&(widget->clip), &(widget->clip), &screen_rect);
	}

	/* get the no transparent parent */
	while (parent != RT_NULL && parent->flag & RTGUI_WIDGET_FLAG_TRANSPARENT)
	{	
		parent = parent->parent;
	} 

	if (parent != RT_NULL)
	{
		/* subtract widget clip in parent clip */
		if (!(widget->flag & RTGUI_WIDGET_FLAG_TRANSPARENT))
		{	
			rtgui_region_subtract_rect(&(parent->clip), &(parent->clip),
				&(widget->extent));
		}
	}

	/*
	 * note: since the layout widget introduction, the sibling widget will not
	 * intersect.
	 */

	/* if it's a container object, update the clip info of children */
	if (RTGUI_IS_CONTAINER(widget))
	{
		rtgui_widget_t* child;	 
		rtgui_list_foreach(node, &(RTGUI_CONTAINER(widget)->children))
		{
			child = rtgui_list_entry(node, rtgui_widget_t, sibling);
			if (RTGUI_WIDGET_IS_HIDE(child)) continue;
			rtgui_widget_update_clip(child);
		}
	}
}

/*
 * 更新多个控件重叠时的clip剪切情况,将子控件topwdt作为最顶端控件,
 * 它的兄弟控件则相应的剪切掉topwdt区域,使它们从位置上被topwdt覆盖
 * 调用该函数时,应该保证topwdt控件是wdt控件下的一个子控件.
 */
void rtgui_widget_update_clip_pirate(PVOID wdt,PVOID topwdt)
{
	rtgui_list_t *node;
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_rect_t wdt_rect;
	
	if(widget == RT_NULL || RTGUI_WIDGET_IS_HIDE(widget)) return;
	
	wdt_rect = widget->extent;

	if(wdt == topwdt)
	{	/* the same as oneself */
		rtgui_widget_update_clip(widget);
		return;	
	}
	else
	{	/* different widget */
		if(rtgui_rect_is_intersect(&RTGUI_WIDGET_EXTENT(topwdt), &wdt_rect) == RT_EOK)
		{
			rtgui_rect_intersect(&RTGUI_WIDGET_EXTENT(topwdt), &wdt_rect);/* calculate overlap */
			rtgui_region_reset(&(widget->clip), &(widget->extent));
			rtgui_region_subtract_rect(&(widget->clip), &(widget->clip),&wdt_rect);/* subtract overlap area */
		}
		else
		{
			rtgui_region_reset(&(widget->clip), &(widget->extent));
		}
	}

	{
		rtgui_rect_t screen_rect;
		rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(),&screen_rect);
		rtgui_region_intersect_rect(&(widget->clip), &(widget->clip), &screen_rect);
	}

	if(RTGUI_IS_CONTAINER(widget))
	{   /* update all child widget */
		rtgui_list_foreach(node, &(RTGUI_CONTAINER(widget)->children))
		{	
			rtgui_widget_t *child = rtgui_list_entry(node, rtgui_widget_t, sibling);
			if(RTGUI_WIDGET_IS_HIDE(child))continue;
			if(RTGUI_IS_WIN(child))continue; /* no dispose windows */

			rtgui_region_subtract_rect(&(widget->clip), &(widget->clip),&(child->extent));
			rtgui_widget_update_clip_pirate(child,topwdt);
		}
	}
}

void rtgui_widget_show(PVOID wdt)
{
	/* there is no parent or the parent is hide, no show at all */
	if(RTGUI_WIDGET_PARENT(wdt) == RT_NULL ||RTGUI_WIDGET_IS_HIDE(RTGUI_WIDGET_PARENT(wdt))) return;

	/* update the clip info of widget */
	RTGUI_WIDGET_UNHIDE(wdt);
	rtgui_widget_update_clip(wdt);
}

void rtgui_widget_hide(PVOID wdt)
{
	rtgui_rect_t rect;
	rtgui_widget_t  *widget = (rtgui_widget_t*)wdt;

	/* hide this widget */
	RTGUI_WIDGET_HIDE(widget);

	if (widget->parent != RT_NULL)
	{
		int index;
		rtgui_widget_t *parent;

		rect = widget->extent;
		parent = widget->parent;
		/* get the no transparent parent */
		while (parent != RT_NULL && parent->flag & RTGUI_WIDGET_FLAG_TRANSPARENT)
		{
			parent = parent->parent;
		}

		/* union widget rect */
		rtgui_region_union_rect(&(widget->parent->clip), &(widget->parent->clip), &rect);

		/* subtract the external rect */
		for (index = 0; index < external_clip_size; index ++)
		{
			rtgui_region_subtract_rect(&(widget->parent->clip), &(widget->parent->clip),
				&(external_clip_rect[index]));
		}
	}
}

rtgui_color_t rtgui_widget_get_parent_foreground(PVOID wdt)
{
	rtgui_widget_t* parent;
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	
	/* get parent widget */
	parent = widget->parent;
	while (parent->parent != RT_NULL && (RTGUI_WIDGET_FLAG(parent) & RTGUI_WIDGET_FLAG_TRANSPARENT))
		parent = parent->parent;

	/* get parent's color */
	if (parent != RT_NULL)
		return RTGUI_WIDGET_FOREGROUND(parent);

	return RTGUI_WIDGET_FOREGROUND(widget);
}

rtgui_color_t rtgui_widget_get_parent_background(PVOID wdt)
{
	rtgui_widget_t* parent;
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	
	/* get parent widget */
	parent = widget->parent;
	while (parent->parent != RT_NULL && (RTGUI_WIDGET_FLAG(parent) & RTGUI_WIDGET_FLAG_TRANSPARENT))
		parent = parent->parent;

	/* get parent's color */
	if (parent != RT_NULL)
		return RTGUI_WIDGET_BACKGROUND(parent);

	return RTGUI_WIDGET_BACKGROUND(widget);
}

void rtgui_widget_update(PVOID wdt)
{
	rtgui_event_paint_t paint;

	if(RTGUI_WIDGET_IS_HIDE(wdt)) return;

	RTGUI_EVENT_PAINT_INIT(&paint);
	paint.wid = RT_NULL;

	RT_ASSERT(wdt != RT_NULL);

	if(RTGUI_WIDGET_EVENT_HANDLE(wdt) != RT_NULL)
	{
		RTGUI_WIDGET_EVENT_CALL(wdt, &paint.parent);
	}
}

//获得下一个兄弟控件
rtgui_widget_t* rtgui_widget_get_next_sibling(PVOID wdt)
{
	rtgui_widget_t* sibling = RT_NULL;
	rtgui_widget_t* widget = wdt;
	
	if(widget->sibling.next != RT_NULL)
	{
		sibling = rtgui_list_entry(widget->sibling.next, rtgui_widget_t, sibling);
	}

	return sibling;
}

//获得上一个兄弟控件
rtgui_widget_t* rtgui_widget_get_prev_sibling(PVOID wdt)
{
	rtgui_list_t* node;
	rtgui_widget_t *sibling, *parent;
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	
	node = RT_NULL; sibling = RT_NULL;
	parent = widget->parent;
	if(parent != RT_NULL)
	{
		rtgui_list_foreach(node, &(RTGUI_CONTAINER(parent)->children))
		{
			if(node->next == &(widget->sibling))
				break;
		}
	}

	if(node != RT_NULL)
		sibling = rtgui_list_entry(node, rtgui_widget_t, sibling);

	return sibling;
}
