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
*
*/
#include <stdlib.h>
#include <rtgui/dc.h>
#include <rtgui/widgets/scrollbar.h>

static void _rtgui_scrollbar_constructor(rtgui_scrollbar_t *bar)
{
	/* set event handler */
	rtgui_object_set_event_handler(RTGUI_OBJECT(bar), rtgui_scrollbar_event_handler);

	bar->status = 0;
	bar->value = 0;

	bar->thumb_w = 16;
	bar->thumb_len = 16;

	bar->widget_link = RT_NULL;
	bar->on_scroll = RT_NULL;

	bar->orient = RTGUI_HORIZONTAL;
	/* set gc */
	RTGUI_WIDGET_TEXTALIGN(bar) = RTGUI_ALIGN_CENTER;
}

static void _rtgui_scrollbar_destructor(rtgui_scrollbar_t *bar)
{

}

rt_uint32_t _rtgui_scrollbar_get_length(rtgui_scrollbar_t *bar)
{
	rtgui_rect_t rect;
	rt_uint32_t result;

	rtgui_widget_get_rect(RTGUI_WIDGET(bar), &rect);

	if(bar->orient & RTGUI_VERTICAL)
		result = rtgui_rect_height(rect) - 2*rtgui_rect_width(rect) - bar->thumb_len;
	else
		result = rtgui_rect_width(rect) - 2*rtgui_rect_height(rect) - bar->thumb_len;

	return result;
}

rt_uint32_t get_scrollbar_pos(rtgui_scrollbar_t* bar)
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

DEFINE_CLASS_TYPE(scrollbar, "scrollbar",
				  RTGUI_WIDGET_TYPE,
				  _rtgui_scrollbar_constructor,
				  _rtgui_scrollbar_destructor,
				  sizeof(struct rtgui_scrollbar));

rtgui_scrollbar_t* rtgui_scrollbar_create(rtgui_container_t *container,int left,int top,int w,int len,int orient)
{
	rtgui_scrollbar_t* bar;

	RT_ASSERT(container != RT_NULL);

	bar = (rtgui_scrollbar_t *)rtgui_widget_create(RTGUI_SCROLLBAR_TYPE);
	if(bar != RT_NULL)
	{
		rtgui_rect_t rect;

		rtgui_widget_get_rect(RTGUI_WIDGET(container), &rect);
		rtgui_widget_rect_to_device(RTGUI_WIDGET(container),&rect);
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

		rtgui_widget_set_rect(RTGUI_WIDGET(bar), &rect);

		bar->orient = orient;

		rtgui_container_add_child(container, RTGUI_WIDGET(bar));
	}

	return bar;
}

void rtgui_scrollbar_destroy(rtgui_scrollbar_t* bar)
{
	rtgui_widget_destroy(RTGUI_WIDGET(bar));
}

const static rt_uint8_t _up_arrow[]    = {0x10, 0x38, 0x7C, 0xFE};
const static rt_uint8_t _down_arrow[]  = {0xFE,0x7C, 0x38, 0x10};
const static rt_uint8_t _left_arrow[]  = {0x10, 0x30, 0x70, 0xF0, 0x70, 0x30, 0x10};
const static rt_uint8_t _right_arrow[] = {0x80, 0xC0, 0xE0, 0xF0, 0xE0, 0xC0, 0x80};

void rtgui_scrollbar_ondraw(rtgui_scrollbar_t* bar)
{
	/* draw scroll bar */
	rtgui_rect_t rect, btn_rect, thum_rect, arrow_rect;
	struct rtgui_dc* dc;
	rtgui_color_t bc;

	RT_ASSERT(bar != RT_NULL);

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(bar));
	if(dc == RT_NULL)return;

	bc = RTGUI_DC_BC(dc);
	/* begin drawing */
	rtgui_widget_get_rect(RTGUI_WIDGET(bar), &rect);
	RTGUI_DC_BC(dc) = white;
	rtgui_dc_fill_rect(dc,&rect);
	RTGUI_DC_BC(dc) = bc;

	if(bar->orient == RTGUI_VERTICAL)
	{
		btn_rect = rect;
		btn_rect.y2 = btn_rect.y1 + (rect.x2 - rect.x1);
		rtgui_dc_fill_rect(dc,&btn_rect);
		/* draw up button */
		if(bar->status & SBS_UPARROW)
			rtgui_dc_draw_border(dc, &btn_rect, RTGUI_BORDER_SUNKEN);
		else
			rtgui_dc_draw_border(dc, &btn_rect, RTGUI_BORDER_RAISE);
		/* draw up arrow */
		arrow_rect.x1 = 0; arrow_rect.y1 = 0;
		arrow_rect.x2 = 7; arrow_rect.y2 = 4;
		rtgui_rect_moveto_align(&btn_rect, &arrow_rect, RTGUI_ALIGN_CENTER);
		rtgui_dc_draw_byte(dc, arrow_rect.x1, arrow_rect.y1, rtgui_rect_height(arrow_rect), _up_arrow);

		/* draw thumb */
		rtgui_scrollbar_get_thumb_rect(bar, &thum_rect);
		rtgui_dc_fill_rect(dc,&thum_rect);
		rtgui_dc_draw_border(dc, &thum_rect, RTGUI_BORDER_RAISE);
		
		/* draw down button */
		btn_rect.y1 = rect.y2 - (rect.x2 - rect.x1);
		btn_rect.y2 = rect.y2;
		rtgui_dc_fill_rect(dc,&btn_rect);
		if(bar->status & SBS_DOWNARROW)
			rtgui_dc_draw_border(dc, &btn_rect, RTGUI_BORDER_SUNKEN);
		else
			rtgui_dc_draw_border(dc, &btn_rect, RTGUI_BORDER_RAISE);
		/* draw down arrow */
		arrow_rect.x1 = 0;
		arrow_rect.y1 = 0;
		arrow_rect.x2 = 7;
		arrow_rect.y2 = 4;
		rtgui_rect_moveto_align(&btn_rect, &arrow_rect, RTGUI_ALIGN_CENTER);
		rtgui_dc_draw_byte(dc, arrow_rect.x1, arrow_rect.y1, rtgui_rect_height(arrow_rect), _down_arrow);
	}
	else
	{
		btn_rect = rect;
		btn_rect.x2 = btn_rect.x1 + (rect.y2 - rect.y1);
		rtgui_dc_fill_rect(dc,&btn_rect);
		/* draw left button */
		if(bar->status & SBS_LEFTARROW)
			rtgui_dc_draw_border(dc, &btn_rect, RTGUI_BORDER_SUNKEN);
		else
			rtgui_dc_draw_border(dc, &btn_rect, RTGUI_BORDER_RAISE);
		arrow_rect.x1 = 0;
		arrow_rect.y1 = 0;
		arrow_rect.x2 = 4;
		arrow_rect.y2 = 7;
		rtgui_rect_moveto_align(&btn_rect, &arrow_rect, RTGUI_ALIGN_CENTER);
		rtgui_dc_draw_byte(dc, arrow_rect.x1, arrow_rect.y1, rtgui_rect_height(arrow_rect), _left_arrow);

		/* draw thumb */
		if(RTGUI_WIDGET_IS_ENABLE(bar))
		{
			rtgui_scrollbar_get_thumb_rect(bar, &thum_rect);
			rtgui_dc_fill_rect(dc,&thum_rect);
			rtgui_dc_draw_border(dc, &thum_rect, RTGUI_BORDER_RAISE);
		}

		btn_rect.x1 = rect.x2 - (rect.y2-rect.y1);
		btn_rect.x2 = rect.x2;
		rtgui_dc_fill_rect(dc,&btn_rect);
		/* draw right button */
		if(bar->status & SBS_RIGHTARROW)
			rtgui_dc_draw_border(dc, &btn_rect, RTGUI_BORDER_SUNKEN);
		else
			rtgui_dc_draw_border(dc, &btn_rect, RTGUI_BORDER_RAISE);
		arrow_rect.x1 = 0;
		arrow_rect.y1 = 0;
		arrow_rect.x2 = 4;
		arrow_rect.y2 = 7;
		rtgui_rect_moveto_align(&btn_rect, &arrow_rect, RTGUI_ALIGN_CENTER);
		rtgui_dc_draw_byte(dc, arrow_rect.x1, arrow_rect.y1, rtgui_rect_height(arrow_rect), _right_arrow);

	}

	rtgui_dc_end_drawing(dc);
}

void rtgui_scrollbar_get_thumb_rect(rtgui_scrollbar_t *bar, rtgui_rect_t *erect)
{
	rtgui_rect_t rect;

	rtgui_widget_get_rect(RTGUI_WIDGET(bar), &rect);
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

static void _rtgui_scrollbar_on_mouseclick(rtgui_scrollbar_t *bar, rtgui_event_t * event)
{
	rtgui_rect_t btn_rect, bar_rect,rect;
	rt_uint32_t pos;
	struct rtgui_event_mouse *mouse = (struct rtgui_event_mouse*)event;

	RT_ASSERT(bar != RT_NULL);

	/* get value */
	pos = get_scrollbar_pos(bar);

	rtgui_widget_get_rect(RTGUI_WIDGET(bar), &rect);
	rtgui_widget_rect_to_device(RTGUI_WIDGET(bar),&rect);

	if(bar->orient == RTGUI_VERTICAL)
	{
		/* arrange vertical */
		/* get up arrow button rect */
		btn_rect.x1 = rect.x1;
		btn_rect.x2 = rect.x2;
		btn_rect.y1 = rect.y1;
		btn_rect.y2 = rect.y1 + rtgui_rect_width(rect);

		if(rtgui_rect_contains_point(&btn_rect, mouse->x, mouse->y) == RT_EOK)
		{
			if((mouse->button & RTGUI_MOUSE_BUTTON_LEFT) && (mouse->button & RTGUI_MOUSE_BUTTON_DOWN))
			{
				bar->status |= SBS_UPARROW;
				if(bar->value==0)
				{
					rtgui_scrollbar_ondraw(bar);
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
		rtgui_widget_rect_to_device(RTGUI_WIDGET(bar),&bar_rect);
		if(rtgui_rect_contains_point(&bar_rect, mouse->x, mouse->y) == RT_EOK)
		{
			/* on thumb */
			if((mouse->button & RTGUI_MOUSE_BUTTON_LEFT) && (mouse->button & RTGUI_MOUSE_BUTTON_DOWN))
			{
				/* changed status into drag */
				bar->status |= SBS_VERTTHUMB;
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
			/* click on space without thumb */
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
						bar->status |= SBS_UPSPACE;
						bar->value -= bar->page_step;
						if(bar->value < 0) bar->value = 0;
					}
					else if(mouse->y > pos + bar->thumb_len)
					{
						bar->status |= SBS_DOWNSPACE;
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
				bar->status |= SBS_DOWNARROW;
				if(bar->value==bar->count)
				{
					rtgui_scrollbar_ondraw(bar);
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
				bar->status |= SBS_LEFTARROW;
				if(bar->value==0)
				{
					rtgui_scrollbar_ondraw(bar);
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
		rtgui_widget_rect_to_device(RTGUI_WIDGET(bar),&bar_rect);
		if(rtgui_rect_contains_point(&bar_rect, mouse->x, mouse->y) == RT_EOK)
		{
			/* on the thumb */
			if((mouse->button & RTGUI_MOUSE_BUTTON_LEFT) && (mouse->button & RTGUI_MOUSE_BUTTON_DOWN))
			{
				bar->status |= SBS_HORZTHUMB;
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
						bar->status |= SBS_LEFTSPACE;
						bar->value -= bar->page_step;
						if(bar->value < 0) bar->value = 0;
					}
					else if(mouse->x > pos + bar->thumb_len)
					{
						bar->status |= SBS_RIGHTSPACE;
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
				bar->status |= SBS_RIGHTARROW;
				if(bar->value==bar->count)
				{
					rtgui_scrollbar_ondraw(bar);
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
	rtgui_scrollbar_ondraw(bar);
	if((mouse->button & RTGUI_MOUSE_BUTTON_LEFT) && (mouse->button & RTGUI_MOUSE_BUTTON_DOWN))
	{
		if(bar->widget_link != RT_NULL && bar->on_scroll != RT_NULL)
		{
			rtgui_widget_focus(bar->widget_link);
			bar->on_scroll(RTGUI_OBJECT(bar->widget_link), event);
		}
	}
}

/* thumb chunk activity */
static void _rtgui_scrollbar_on_mousemotion(rtgui_scrollbar_t *bar, rtgui_event_t * event)
{
	float tmppos;
	rt_uint32_t pos;
	struct rtgui_event_mouse *mouse = (struct rtgui_event_mouse*)event;
rt_kprintf("sbar mouse motion.\n");
	tmppos = _rtgui_scrollbar_get_length(bar);
	tmppos /= bar->count;
	pos = (rt_uint32_t)tmppos;

	if(bar->orient == RTGUI_VERTICAL)
	{
		if(bar->status & SBS_VERTTHUMB)
		{
			/* from then on mouseclick */
			if((mouse->y-sbar_mouse_move_size.y) > 3)
			{
				bar->status |= SBS_DOWNTHUMB;
			}
			else if((mouse->y-sbar_mouse_move_size.y) < -3)
			{
				bar->status |= SBS_UPTHUMB;
			}
			else bar->status &= ~(SBS_UPTHUMB|SBS_DOWNTHUMB);

			if(abs(mouse->y-sbar_mouse_move_size.y) >= pos)
			{
				int step = abs(mouse->y-sbar_mouse_move_size.y)/pos;
				sbar_mouse_move_size.y = mouse->y;

				if(bar->status & SBS_UPTHUMB)
				{
					bar->value -= step;
					if(bar->value < 0) bar->value = 0;
				}
				else if(bar->status & SBS_DOWNTHUMB)
				{
					bar->value += step;
					if(bar->value > bar->count) bar->value = bar->count;
				}
				goto __exit;
			}
		}
		else if(bar->status & SBS_UPARROW)
		{
			/* on-going push down uparrow button */
			if(bar->value==0)return;
			bar->value -= bar->line_step;
			if(bar->value < 0) bar->value = 0;
			goto __exit;
		}
		else if(bar->status & SBS_DOWNARROW)
		{
			/* on-going push down downarrow button */
			if(bar->value==bar->count)return;
			bar->value += bar->line_step;
			if(bar->value > bar->count) bar->value = bar->count;
			goto __exit;
		}
		/*else if(bar->status & SBS_UPSPACE)
		{
		bar->value -= bar->page_step;
		if(bar->value < 0) bar->value = 0;
		goto __exit;
		}
		else if(bar->status & SBS_DOWNSPACE)
		{
		bar->value += bar->page_step;
		if(bar->value > bar->count) bar->value = bar->count;
		goto __exit;
		}*/
		return;
	}
	else
	{
		if(bar->status & SBS_HORZTHUMB)
		{rt_kprintf("HORZTHUMB, move event\n");
			if((mouse->x-sbar_mouse_move_size.x) > 5)
			{
				bar->status |= SBS_RIGHTTHUMB;
			}
			else if((mouse->x-sbar_mouse_move_size.x) < -5)
			{
				bar->status |= SBS_LEFTTHUMB;
			}
			if(abs(mouse->x-sbar_mouse_move_size.x) > pos)
			{
				int step = abs(mouse->x-sbar_mouse_move_size.x)/pos;
				sbar_mouse_move_size.x = mouse->x;
				if(bar->status & SBS_LEFTTHUMB)
				{
					bar->value -= step;
					if(bar->value < 0) bar->value = 0;
				}
				else if(bar->status & SBS_RIGHTTHUMB)
				{
					bar->value += step;
					if(bar->value > bar->count) bar->value = bar->count;
				}
				goto __exit;
			}
		}
		else if(bar->status & SBS_LEFTARROW)
		{
			if(bar->value==0)return;
			bar->value -= bar->line_step;
			if(bar->value < 0) bar->value = 0;
			goto __exit;
		}
		else if(bar->status & SBS_RIGHTARROW)
		{
			if(bar->value==bar->count)return;
			bar->value += bar->line_step;
			if(bar->value > bar->count) bar->value = bar->count;
			goto __exit;
		}
		/*else if(bar->status & SBS_LEFTSPACE)
		{
		bar->value -= bar->page_step;
		if(bar->value < bar->min) bar->value = bar->min;
		goto __exit;
		}
		else if(bar->status & SBS_RIGHTSPACE)
		{
		bar->value += bar->page_step;
		if(bar->value > bar->count-1) bar->value = bar->count-1;
		goto __exit;
		}*/
		return;
	}

__exit:
	rtgui_scrollbar_ondraw(bar);
	if(bar->widget_link != RT_NULL && bar->on_scroll != RT_NULL)
	{
		rtgui_widget_focus(bar->widget_link);
		bar->on_scroll(RTGUI_OBJECT(bar->widget_link), event);
	}
}


rt_bool_t rtgui_scrollbar_event_handler(rtgui_object_t *object, rtgui_event_t *event)
{
	rtgui_widget_t *widget = RTGUI_WIDGET(object);
	rtgui_scrollbar_t* bar = RTGUI_SCROLLBAR(object);

	switch(event->type)
	{
	case RTGUI_EVENT_PAINT:
#ifndef RTGUI_USING_SMALL_SIZE
		if(widget->on_draw != RT_NULL)
			widget->on_draw(object, event);
		else
#endif
		{
			if(!RTGUI_WIDGET_IS_HIDE(bar))
				rtgui_scrollbar_ondraw(bar);
		}
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		if(RTGUI_WIDGET_IS_ENABLE(widget))
		{
#ifndef RTGUI_USING_SMALL_SIZE
			if(widget->on_mouseclick != RT_NULL)
			{
				widget->on_mouseclick(object, event);
			}
			else
#endif
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
		return rtgui_widget_event_handler(object, event);
	}

	return RT_FALSE;
}

void rtgui_scrollbar_set_orientation(rtgui_scrollbar_t* bar, int orient)
{
	RT_ASSERT(bar != RT_NULL);

	bar->orient = orient;
}

/* get active area length */
rt_uint32_t get_sbar_active_len(rtgui_scrollbar_t *bar)
{
	rtgui_rect_t rect;

	rtgui_widget_get_rect(RTGUI_WIDGET(bar), &rect);

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

	/* Make sure called rtgui_scrollbar_set_range(),before you use under code. */
	size = bar->page_step;
	size /= bar->count+bar->page_step;
	size *= get_sbar_active_len(bar);
	len = (rt_uint32_t)size ;

	w = bar->thumb_w;

	if(len < w/2) len = w/2;

	bar->thumb_len = len;
}

/*
* please use them with below step:
* 1.SetLineStep();2.SetPageStep();3.SetRange();
*/

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
	{
		/* disable bar */
		RTGUI_WIDGET_DISABLE(bar);
	}
	else
	{
		/* enable bar */
		RTGUI_WIDGET_ENABLE(bar);
	}

	/* thumb step count = item_count-item_per_page */
	bar->count = (rt_int16_t)(count-bar->page_step);
	rtgui_scrollbar_set_thumbbar_len(bar);
}

/* use VALUE change be binding widget's frist item. */
void rtgui_scrollbar_set_value(rtgui_scrollbar_t* bar, rt_int16_t value)
{
	RT_ASSERT(bar != RT_NULL);

	bar->value = value;

	if(bar->value < 0) bar->value = 0;

	rtgui_widget_update(RTGUI_WIDGET(bar));
}

void rtgui_scrollbar_set_onscroll(rtgui_scrollbar_t* bar, rtgui_event_handler_ptr handler)
{
	if(bar == RT_NULL || handler == RT_NULL) return;

	bar->on_scroll = handler;
}

void rtgui_scrollbar_hide(rtgui_scrollbar_t* bar)
{
	rtgui_rect_t rect;
	struct rtgui_dc* dc;

	RT_ASSERT(bar != RT_NULL);

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(bar));
	if(dc == RT_NULL)return;

	RTGUI_WIDGET_HIDE(bar);

	/* begin drawing */
	rtgui_widget_get_rect(RTGUI_WIDGET(bar), &rect);
	if((RTGUI_WIDGET(bar))->parent != RT_NULL)
		RTGUI_DC_BC(dc) = RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(bar)->parent);
	else
		RTGUI_DC_BC(dc) = RTGUI_RGB(225, 228, 220);
	rtgui_dc_fill_rect(dc,&rect);

	rtgui_dc_end_drawing(dc);
}
