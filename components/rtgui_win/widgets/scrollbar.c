/*
 * File      : scrollbar.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-08-09     Bernard      first version
 */
#include <rtgui/dc.h>
#include <rtgui/widgets/scrollbar.h>
#include <rtgui/rtgui_theme.h>

static void _rtgui_scrollbar_constructor(rtgui_scrollbar_t *bar)
{
	/* set event handler */
	rtgui_widget_set_event_handler(bar, rtgui_scrollbar_event_handler);
	
	bar->status = 0;
	bar->value = 0;

	bar->thumb_w = 16;
	bar->thumb_len = 16;

	bar->widgetlnk = RT_NULL;
	bar->on_scroll = RT_NULL;

	bar->orient = RTGUI_HORIZONTAL;
	/* set gc */
	RTGUI_WIDGET_TEXTALIGN(bar) = RTGUI_ALIGN_CENTER_HORIZONTAL|RTGUI_ALIGN_CENTER_VERTICAL;
}

static void _rtgui_scrollbar_destructor(rtgui_scrollbar_t *bar)
{

}

rt_inline rt_uint32_t _rtgui_scrollbar_get_length(rtgui_scrollbar_t *bar)
{
	rtgui_rect_t rect;
	rt_uint32_t result;

	rtgui_widget_get_rect(bar, &rect);

	if(bar->orient & RTGUI_VERTICAL)
		result = rtgui_rect_height(rect) - 2*rtgui_rect_width(rect) - bar->thumb_len;
	else
		result = rtgui_rect_width(rect) - 2*rtgui_rect_height(rect) - bar->thumb_len;
	
	return result;
}

rt_inline rt_uint32_t get_scrollbar_pos(rtgui_scrollbar_t* bar)
{
	double pos,ftmp;
	rt_uint32_t result;
	
	/* calculate thumb position */
	pos = bar->value; 			 
	ftmp = _rtgui_scrollbar_get_length(bar); 
	pos *= ftmp; 
	ftmp = bar->count;				 
	pos /= ftmp; 

	result = pos;
	return result;
}

rtgui_type_t *rtgui_scrollbar_type_get(void)
{
	static rtgui_type_t *scrollbar_type = RT_NULL;

	if(!scrollbar_type)
	{
		scrollbar_type = rtgui_type_create("scrollbar", RTGUI_WIDGET_TYPE,
			sizeof(rtgui_scrollbar_t), 
			RTGUI_CONSTRUCTOR(_rtgui_scrollbar_constructor), 
			RTGUI_DESTRUCTOR(_rtgui_scrollbar_destructor));
	}

	return scrollbar_type;
}


rtgui_scrollbar_t* rtgui_scrollbar_create(PVOID parent,int left,int top,int w,int len,int orient)
{
    rtgui_scrollbar_t* bar;
	
	RT_ASSERT(parent != RT_NULL);

    bar = rtgui_widget_create (RTGUI_SCROLLBAR_TYPE);
    if(bar != RT_NULL)
    {
		rtgui_rect_t rect;

		rtgui_widget_get_rect(parent, &rect);
		rtgui_widget_rect_to_device(parent,&rect);
		rect.x1 += left;
		rect.y1 += top;
		
		bar->thumb_w = w;
		if(orient == RTGUI_VERTICAL)
		{
			rect.x2 = rect.x1+w;
			rect.y2 = rect.y1+len;
		}
		else
		{
			rect.x2 = rect.x1+len;
			rect.y2 = rect.y1+w;
		}
		
		rtgui_widget_set_rect(bar, &rect);

		bar->orient = orient;

		rtgui_container_add_child(parent, bar);
    }

    return bar;
}

void rtgui_scrollbar_destroy(rtgui_scrollbar_t* bar)
{
	rtgui_widget_destroy(bar);
}


void rtgui_scrollbar_get_thumb_rect(rtgui_scrollbar_t *bar, rtgui_rect_t *erect)
{
	rtgui_rect_t rect;

	rtgui_widget_get_rect(bar, &rect);
	if(bar->orient & RTGUI_VERTICAL)
	{
		/* vertical scroll bar */
		erect->x1 = rect.x1;
		erect->x2 = rect.x2;
		erect->y1 = rect.y1 + rtgui_rect_width(rect) + get_scrollbar_pos(bar);
		erect->y2 = erect->y1 + bar->thumb_len;
	}
	else
	{
		/* horizontal scroll bar */
		erect->x1 = rect.x1 + rtgui_rect_height(rect) + get_scrollbar_pos(bar);
		erect->x2 = erect->x1 + bar->thumb_len;
		erect->y1 = rect.y1;
		erect->y2 = rect.y2;
	}
}

static rtgui_point_t sbar_mouse_move_size;

static void _rtgui_scrollbar_on_mouseclick(PVOID wdt, rtgui_event_t * event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_rect_t btn_rect, bar_rect,rect;
	rt_uint32_t pos;
    rtgui_scrollbar_t *bar = (rtgui_scrollbar_t*)widget;
    rtgui_event_mouse_t *mouse = (rtgui_event_mouse_t*)event;

	RT_ASSERT(bar != RT_NULL);

	/* get value */
	pos = get_scrollbar_pos(bar);

	rtgui_widget_get_rect(bar, &rect);
	rtgui_widget_rect_to_device(bar,&rect);

    if(bar->orient == RTGUI_VERTICAL)
    {	/* arrange vertical */
		/* get up arrow button rect */
		btn_rect.x1 = rect.x1;
		btn_rect.x2 = rect.x2;
		btn_rect.y1 = rect.y1;
		btn_rect.y2 = rect.y1 + rtgui_rect_width(rect);
		
        if(rtgui_rect_contains_point(&btn_rect, mouse->x, mouse->y) == RT_EOK)
        {	
            if((mouse->button & RTGUI_MOUSE_BUTTON_LEFT) && (mouse->button & RTGUI_MOUSE_BUTTON_DOWN))
            {	
				bar->status |= SBAR_UPARROW;
                if(bar->value==0)
				{
					rtgui_theme_draw_scrollbar(bar);
					return;
				}
				/* line step */
				bar->value -= bar->line_step;
				if(bar->value < 0) bar->value = 0; 
            }
            else if(mouse->button & RTGUI_MOUSE_BUTTON_UP)
			{
                bar->status = 0;
			}
			goto __exit;
        }
		/* click on the thumb chunk, be going to dragging */
		rtgui_scrollbar_get_thumb_rect(bar, &bar_rect);
		rtgui_widget_rect_to_device(bar,&bar_rect);
		if(rtgui_rect_contains_point(&bar_rect, mouse->x, mouse->y) == RT_EOK)
		{	/* on thumb */  
			if((mouse->button & RTGUI_MOUSE_BUTTON_LEFT) && (mouse->button & RTGUI_MOUSE_BUTTON_DOWN))
			{	/* changed status into drag */
				bar->status |= SBAR_VERTTHUMB;
				sbar_mouse_move_size.x = mouse->x;
				sbar_mouse_move_size.y = mouse->y;
			}
			else if(mouse->button & RTGUI_MOUSE_BUTTON_UP)
			{
                bar->status = 0;
			}
			goto __exit;
		}
		else
		{	/* click on space without thumb */
			/* get bar rect */
			bar_rect.y1 = rect.y1 + rtgui_rect_width(rect);
			bar_rect.y2 = rect.y2 - rtgui_rect_width(rect);
	        if(rtgui_rect_contains_point(&bar_rect, mouse->x, mouse->y) == RT_EOK)
	        {
				if((mouse->button & RTGUI_MOUSE_BUTTON_LEFT) && (mouse->button & RTGUI_MOUSE_BUTTON_DOWN))
	            {
					/* page step */
					if(mouse->y < bar_rect.y1 + pos)
					{
						bar->status |= SBAR_UPSPACE;
						bar->value -= bar->page_step;
						if(bar->value < 0) bar->value = 0;
					}
					else if(mouse->y > pos + bar->thumb_len)
					{
						bar->status |= SBAR_DOWNSPACE;
						bar->value += bar->page_step;
						if(bar->value > bar->count) bar->value = bar->count;
					}
	            }
				goto __exit;
	        }
		}
		/* likewise foregoing */
		/* get down arrow button rect */
		bar_rect.x1 = rect.x1;
		bar_rect.x2 = rect.x2;
        btn_rect.y1 = rect.y2 - rtgui_rect_width(rect);
        btn_rect.y2 = rect.y2;
        if(rtgui_rect_contains_point(&btn_rect, mouse->x, mouse->y) == RT_EOK)
        {	
            if((mouse->button & RTGUI_MOUSE_BUTTON_LEFT) && (mouse->button & RTGUI_MOUSE_BUTTON_DOWN))
            {
                bar->status |= SBAR_DOWNARROW;
				if(bar->value==bar->count)
				{
					rtgui_theme_draw_scrollbar(bar);
					return;
				}
				/* line step */
				bar->value += bar->line_step;
				if(bar->value > bar->count) bar->value = bar->count;
            }
            else if(mouse->button & RTGUI_MOUSE_BUTTON_UP)
                bar->status = 0;
			goto __exit;
        }
    }
    else
    {
		/* get left arrow button rect */
		btn_rect.x1 = rect.x1;
		btn_rect.x2 = rect.x1 + rtgui_rect_height(rect);
		btn_rect.y1 = rect.y1;
		btn_rect.y2 = rect.y2;
        if(rtgui_rect_contains_point(&btn_rect, mouse->x, mouse->y) == RT_EOK)
        {
            if((mouse->button & RTGUI_MOUSE_BUTTON_LEFT) && (mouse->button & RTGUI_MOUSE_BUTTON_DOWN))
            {
				bar->status |= SBAR_LEFTARROW;
				if(bar->value==0)
				{
					rtgui_theme_draw_scrollbar(bar);
					return;
				}
				/* line step */
				bar->value -= bar->line_step;
				if(bar->value < 0) bar->value = 0;
            }
            else if(mouse->button & RTGUI_MOUSE_BUTTON_UP)
                bar->status = 0;
			goto __exit;
        }

		rtgui_scrollbar_get_thumb_rect(bar, &bar_rect);
		rtgui_widget_rect_to_device(bar,&bar_rect);
		if(rtgui_rect_contains_point(&bar_rect, mouse->x, mouse->y) == RT_EOK)
		{/* on the thumb */
			if((mouse->button & RTGUI_MOUSE_BUTTON_LEFT) && (mouse->button & RTGUI_MOUSE_BUTTON_DOWN))
			{
				bar->status |= SBAR_HORZTHUMB;
				sbar_mouse_move_size.x = mouse->x;
				sbar_mouse_move_size.y = mouse->y;
			}
			else if(mouse->button & RTGUI_MOUSE_BUTTON_UP)
			{
                bar->status = 0;
			}
			goto __exit;
		}
		else
		{
			/* get bar rect */
			bar_rect.x1 = rect.x1 + rtgui_rect_height(rect);
			bar_rect.x2 = rect.x2 - rtgui_rect_height(rect);
			bar_rect.y1 = rect.y1;
			bar_rect.y2 = rect.y2;
	        if(rtgui_rect_contains_point(&bar_rect, mouse->x, mouse->y) == RT_EOK)
	        {
	            if((mouse->button & RTGUI_MOUSE_BUTTON_LEFT) && (mouse->button & RTGUI_MOUSE_BUTTON_DOWN))
	            {
					/* page step */
					if(mouse->x <  bar_rect.x1 + pos)
					{	
						bar->status |= SBAR_LEFTSPACE;
						bar->value -= bar->page_step;
						if(bar->value < 0) bar->value = 0;
					}
					else if(mouse->x > pos + bar->thumb_len)
					{	
						bar->status |= SBAR_RIGHTSPACE;
						bar->value += bar->page_step;
						if(bar->value > bar->count) bar->value = bar->count;
					}
	            }
				else if(mouse->button & RTGUI_MOUSE_BUTTON_UP)
				{
					bar->status = 0;	
				}
				goto __exit;
	        }
		}
		/* get right arrow button rect */
        btn_rect.x1 = rect.x2 - rtgui_rect_height(rect);
        btn_rect.x2 = rect.x2;
        bar_rect.y1 = rect.y1;
		bar_rect.y2 = rect.y2;
        if(rtgui_rect_contains_point(&btn_rect, mouse->x, mouse->y) == RT_EOK)
        {	
            if((mouse->button & RTGUI_MOUSE_BUTTON_LEFT) && (mouse->button & RTGUI_MOUSE_BUTTON_DOWN))
            {
				bar->status |= SBAR_RIGHTARROW;
				if(bar->value==bar->count)
				{
					rtgui_theme_draw_scrollbar(bar);
					return;
				}
				/* line step */
				bar->value += bar->line_step;
				if(bar->value > bar->count) bar->value = bar->count;
            }
			else if(mouse->button & RTGUI_MOUSE_BUTTON_UP)
                bar->status = 0;
			goto __exit;
        }
    }

__exit:
    rtgui_theme_draw_scrollbar(bar); 
	if((mouse->button & RTGUI_MOUSE_BUTTON_LEFT) && (mouse->button & RTGUI_MOUSE_BUTTON_DOWN))
	{
		if(bar->widgetlnk != RT_NULL && bar->on_scroll != RT_NULL) 
		{
			rtgui_widget_focus(bar->widgetlnk);
			bar->on_scroll(bar->widgetlnk, RT_NULL);
		}
	}

}

/* thumb chunk activity */
static void _rtgui_scrollbar_on_mousemotion(PVOID wdt, rtgui_event_t * event)
{
	#include <stdlib.h>
	float tmppos;
	rt_uint32_t pos;
	rtgui_scrollbar_t *bar = (rtgui_scrollbar_t*)wdt;
	rtgui_event_mouse_t *mouse = (rtgui_event_mouse_t*)event;
	
	tmppos = _rtgui_scrollbar_get_length(bar);
	tmppos /= bar->count;
	pos = (rt_uint32_t)tmppos;

	if(bar->orient == RTGUI_VERTICAL)
	{
		if(bar->status & SBAR_VERTTHUMB)
		{	/* from then on mouseclick */
			if((mouse->y-sbar_mouse_move_size.y) > 3)
			{
				bar->status |= SBAR_DOWNTHUMB;
			}
			else if((mouse->y-sbar_mouse_move_size.y) < -3)
			{
				bar->status |= SBAR_UPTHUMB;
			}
			else bar->status &= ~(SBAR_UPTHUMB|SBAR_DOWNTHUMB);

			if(abs(mouse->y-sbar_mouse_move_size.y) >= pos)	
			{
				int step = abs(mouse->y-sbar_mouse_move_size.y)/pos;
				sbar_mouse_move_size.y = mouse->y;

				if(bar->status & SBAR_UPTHUMB)
				{
					bar->value -= step;
					if(bar->value < 0) bar->value = 0;
				}
				else if(bar->status & SBAR_DOWNTHUMB)
				{
					bar->value += step;
					if(bar->value > bar->count) bar->value = bar->count;
				}
				goto __exit;
			}
		}
		else if(bar->status & SBAR_UPARROW)
		{	/* on-going push down uparrow button */
			if(bar->value==0)return;
			bar->value -= bar->line_step;
			if(bar->value < 0) bar->value = 0;
			goto __exit;	
		}
		else if(bar->status & SBAR_DOWNARROW)
		{	/* on-going push down downarrow button */
			if(bar->value==bar->count)return;
			bar->value += bar->line_step;
			if(bar->value > bar->count) bar->value = bar->count;
			goto __exit;
		}
		/*else if(bar->status & SBAR_UPSPACE)
		{
			bar->value -= bar->page_step;
			if(bar->value < 0) bar->value = 0;
			goto __exit;
		}
		else if(bar->status & SBAR_DOWNSPACE)
		{
			bar->value += bar->page_step;
			if(bar->value > bar->count) bar->value = bar->count;
			goto __exit;
		}*/
		return;
	}
	else
	{	/* 水平排列 */
		if(bar->status & SBAR_HORZTHUMB)
		{
			if((mouse->x-sbar_mouse_move_size.x) > 5)
			{
				bar->status |= SBAR_RIGHTTHUMB;
			}
			else if((mouse->x-sbar_mouse_move_size.x) < -5)
			{
				bar->status |= SBAR_LEFTTHUMB;
			}
			if(abs(mouse->x-sbar_mouse_move_size.x) > pos)	
			{
				int step = abs(mouse->x-sbar_mouse_move_size.x)/pos;
				sbar_mouse_move_size.x = mouse->x;
				if(bar->status & SBAR_LEFTTHUMB)
				{
					bar->value -= step;
					if(bar->value < 0) bar->value = 0;
				}
				else if(bar->status & SBAR_RIGHTTHUMB)
				{
					bar->value += step;
					if(bar->value > bar->count) bar->value = bar->count;
				}
				goto __exit;
			}	
		}
		else if(bar->status & SBAR_LEFTARROW)
		{
			if(bar->value==0)return;
			bar->value -= bar->line_step;
			if(bar->value < 0) bar->value = 0;
			goto __exit;	
		}
		else if(bar->status & SBAR_RIGHTARROW)
		{
			if(bar->value==bar->count)return;
			bar->value += bar->line_step;
			if(bar->value > bar->count) bar->value = bar->count;
			goto __exit;
		}
		/*else if(bar->status & SBAR_LEFTSPACE)
		{
			bar->value -= bar->page_step;
			if(bar->value < bar->min) bar->value = bar->min;
			goto __exit;
		}
		else if(bar->status & SBAR_RIGHTSPACE)
		{
			bar->value += bar->page_step;
			if(bar->value > bar->count-1) bar->value = bar->count-1;
			goto __exit;
		}*/
		return;
	}
	
__exit:
	rtgui_theme_draw_scrollbar(bar);
	if(bar->widgetlnk != RT_NULL && bar->on_scroll != RT_NULL) 
	{
		rtgui_widget_focus(bar->widgetlnk);
		bar->on_scroll(bar->widgetlnk, RT_NULL);
	}
}


rt_bool_t rtgui_scrollbar_event_handler(PVOID wdt, rtgui_event_t *event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_scrollbar_t* bar = (rtgui_scrollbar_t*)widget;
	
	if(RTGUI_WIDGET_IS_HIDE(bar))return RT_FALSE;

	switch (event->type)
	{
		case RTGUI_EVENT_PAINT:
			if(widget->on_draw != RT_NULL) 
				widget->on_draw(widget, event);
			else
			{
				if(!RTGUI_WIDGET_IS_HIDE(bar))
					rtgui_theme_draw_scrollbar(bar);
			}
	
			break;
	
		case RTGUI_EVENT_MOUSE_BUTTON:
			if(RTGUI_WIDGET_IS_ENABLE(widget))
			{
				if(widget->on_mouseclick != RT_NULL)
				{
					widget->on_mouseclick(widget, event);
				}
				else
				{	
					_rtgui_scrollbar_on_mouseclick(bar, event);
				}
			}
			break;
		case RTGUI_EVENT_MOUSE_MOTION:
			if(RTGUI_WIDGET_IS_ENABLE(widget))
			{
				_rtgui_scrollbar_on_mousemotion(bar, event);
			}
	
		default:
			break;
	}

	return RT_FALSE;
}

void rtgui_scrollbar_set_orientation(rtgui_scrollbar_t* bar, int orient)
{
	RT_ASSERT(bar != RT_NULL);

	bar->orient = orient;
}

//取得活动条的可活动区域的长度
rt_uint32_t get_sbar_active_len(rtgui_scrollbar_t *bar)
{
	rtgui_rect_t rect;

	rtgui_widget_get_rect(bar, &rect);

	if(bar->orient & RTGUI_VERTICAL)
		return rtgui_rect_height(rect) - 2*rtgui_rect_width(rect);
	else
		return rtgui_rect_width(rect) - 2*rtgui_rect_height(rect);
}

void rtgui_scrollbar_set_thumbbar_len(rtgui_scrollbar_t* bar)
{
	double size=0;
	rt_uint32_t len,w;

	RT_ASSERT(bar != RT_NULL);

	//Make sure called rtgui_scrollbar_set_range(),before you use under code.
	//计算活动块尺寸的方法:
	//用一页项目条数/总计数条数的比值,来确定活动块在可活动区域中的比例,
	//当函数很多是,使用活动块宽的的一半作为最小尺寸.

	size = bar->page_step;
	size /= bar->count+bar->page_step;
	size *= get_sbar_active_len(bar);
	len = (rt_uint32_t)size ;

	w = bar->thumb_w;

	if(len < w/2) len = w/2;

	bar->thumb_len = len;
}

//下面三个函数的调用顺序:
//1.SetLineStep();2.SetPageStep();3.SetRange();

void rtgui_scrollbar_set_line_step(rtgui_scrollbar_t* bar, int step)
{
	RT_ASSERT(bar != RT_NULL);

	bar->line_step = step;
}

void rtgui_scrollbar_set_page_step(rtgui_scrollbar_t* bar, int step)
{
	RT_ASSERT(bar != RT_NULL);

	bar->page_step = step;	
}

void rtgui_scrollbar_set_range(rtgui_scrollbar_t* bar, int count)
{
	RT_ASSERT(bar != RT_NULL);

	/* disable or enable scrollbar */
	if(bar->page_step >= count)
	{	/* disable bar */
		RTGUI_WIDGET_DISABLE(bar);
	}
	else
	{	/* enable bar */
		RTGUI_WIDGET_ENABLE(bar);
	}

	//活动块计数个数 = 总个数 - 一屏个数
	bar->count = (rt_int16_t)(count-bar->page_step);
	rtgui_scrollbar_set_thumbbar_len(bar);
}

//value的值是被绑定控件的首行值frist_aloc
void rtgui_scrollbar_set_value(rtgui_scrollbar_t* bar, rt_int16_t value)
{
	RT_ASSERT(bar != RT_NULL);

	bar->value = value;

	if(bar->value < 0) bar->value = 0;

	rtgui_widget_update(bar);
}

void rtgui_scrollbar_set_onscroll(rtgui_scrollbar_t* bar, rtgui_event_handler_ptr handler)
{
	if(bar == RT_NULL || handler == RT_NULL) return;

	bar->on_scroll = handler;
}
