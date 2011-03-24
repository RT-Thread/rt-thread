/*
 * File      : button.c
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
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/container.h>
#include <rtgui/rtgui_theme.h>

static rt_bool_t rtgui_button_onunfocus(PVOID wdt, rtgui_event_t* event);

static void _rtgui_button_constructor(rtgui_button_t *button)
{
	/* init widget and set event handler */
	RTGUI_WIDGET_FLAG(button) |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	
	rtgui_widget_set_event_handler(button, rtgui_button_event_handler);
	rtgui_widget_set_onunfocus(button, rtgui_button_onunfocus);
	/* un-press button */
	button->flag = 0;
	rtgui_widget_set_style(button,RTGUI_BORDER_UP);

	/* set flag and on_button event handler */
	button->image = RT_NULL;
	button->on_button = RT_NULL;

	/* set gc */
	RTGUI_WIDGET_FOREGROUND(button) = default_foreground;
	RTGUI_WIDGET_BACKGROUND(button) = default_background;
	RTGUI_WIDGET_TEXTALIGN(button) = RTGUI_ALIGN_CENTER_HORIZONTAL|RTGUI_ALIGN_CENTER_VERTICAL;
}

static void _rtgui_button_destructor(rtgui_button_t *button)
{
	if(button->image != RT_NULL)
	{
		rtgui_image_destroy(button->image);
		button->image = RT_NULL;
	}
}

rtgui_type_t *rtgui_button_type_get(void)
{
	static rtgui_type_t *button_type = RT_NULL;

	if(!button_type)
	{
		button_type = rtgui_type_create("button", RTGUI_LABEL_TYPE,
			sizeof(rtgui_button_t), 
			RTGUI_CONSTRUCTOR(_rtgui_button_constructor), 
			RTGUI_DESTRUCTOR(_rtgui_button_destructor));
	}

	return button_type;
}

rtgui_button_t* rtgui_button_create(PVOID parent, char* text,int left, int top, int w, int h)
{
    rtgui_button_t* btn;

	RT_ASSERT(parent != RT_NULL);

    btn = rtgui_widget_create(RTGUI_BUTTON_TYPE);
    if(btn != RT_NULL)
    {
		rtgui_rect_t rect;
		/* set default rect */
		rtgui_font_get_string_rect(RTGUI_WIDGET_FONT(btn), text, &rect);
		
		rtgui_label_set_text(RTGUI_LABEL(btn), text);

		rtgui_widget_get_rect(parent, &rect);
		rtgui_widget_rect_to_device(parent,&rect);
		rect.x1 += left;
		rect.y1 += top;
		rect.x2 = rect.x1+w;
		rect.y2 = rect.y1+h;
		rtgui_widget_set_rect(btn, &rect);
		
		rtgui_container_add_child(parent, btn);
    }
	
    return btn;
}

void rtgui_button_destroy(rtgui_button_t* btn)
{
	rtgui_widget_destroy(btn);
}

rt_bool_t rtgui_button_event_handler(PVOID wdt, rtgui_event_t* event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_button_t* btn = (rtgui_button_t*) widget;
	
	if(btn == RT_NULL)return RT_FALSE;

	switch (event->type)
	{
		case RTGUI_EVENT_PAINT:		
			if(widget->on_draw != RT_NULL ) 
				widget->on_draw(widget, event);
			else			
				rtgui_theme_draw_button(btn);
			break;
	
		case RTGUI_EVENT_KBD:
			{
				rtgui_event_kbd_t* ekbd = (rtgui_event_kbd_t*) event;
	
				if((ekbd->key == RTGUIK_RETURN) || (ekbd->key == RTGUIK_SPACE))
				{
					if(RTGUI_KBD_IS_DOWN(ekbd))
					{
						btn->flag |= RTGUI_BUTTON_FLAG_PRESS;
					}
					else
					{
						btn->flag &= ~RTGUI_BUTTON_FLAG_PRESS;
					}
	
					/* draw button */
					rtgui_theme_draw_button(btn);
	
					if((btn->flag & RTGUI_BUTTON_FLAG_PRESS) && (btn->on_button != RT_NULL))
					{
						/* call on button handler */
						btn->on_button(widget, event);
					}
				}
			}
			break;
	
		case RTGUI_EVENT_MOUSE_BUTTON:
			{
				rtgui_event_mouse_t* emouse = (rtgui_event_mouse_t*)event;
				
				if(emouse->button & RTGUI_MOUSE_BUTTON_LEFT)
				{	
					rtgui_widget_focus(widget);
					/* it's a normal button */
					if(emouse->button & RTGUI_MOUSE_BUTTON_DOWN)
					{
						btn->flag |= RTGUI_BUTTON_FLAG_PRESS;	
					}
					else
					{
						btn->flag &= ~RTGUI_BUTTON_FLAG_PRESS;
					}
					
					/* draw button */					
					if(widget->on_draw != RT_NULL ) 
						widget->on_draw(widget, event);
					else
					{	
						rtgui_theme_draw_button(btn);
					}
	
					/* invokes call back */
					if(widget->on_mouseclick != RT_NULL && emouse->button & RTGUI_MOUSE_BUTTON_UP)
						return widget->on_mouseclick(widget, event);
	
					if(!(btn->flag & RTGUI_BUTTON_FLAG_PRESS) && (btn->on_button != RT_NULL))
					{
						/* call on button handler */
						btn->on_button(widget, event);
					}
				}
	
				return RT_TRUE;
			}
		default:
			break;
	}

	return RT_FALSE;
}

void rtgui_button_set_image(rtgui_button_t* btn, rtgui_image_t* image)
{
	if(btn == RT_NULL)return;

	btn->image = image;
}

void rtgui_button_set_onbutton(rtgui_button_t* btn, rtgui_onbutton_func_t func)
{
	RT_ASSERT(btn != RT_NULL);

	btn->on_button = func;
}

static rt_bool_t rtgui_button_onunfocus(PVOID wdt, rtgui_event_t* event)
{
	rtgui_rect_t rect;
	rtgui_button_t *btn = (rtgui_button_t*)wdt;
	rtgui_dc_t *dc;

	RT_ASSERT(wdt != RT_NULL);

	dc = rtgui_dc_begin_drawing(wdt);
	if(dc == RT_NULL)return RT_FALSE;

	rtgui_widget_get_rect(btn, &rect);

	if(!RTGUI_WIDGET_IS_FOCUSED(btn))
	{//Çå³ý½¹µã¿ò
		rtgui_color_t color;
		rtgui_rect_inflate(&rect, -2);
		color = RTGUI_DC_FC(dc);
		RTGUI_DC_FC(dc) = RTGUI_DC_BC(dc);
		rtgui_dc_draw_focus_rect(dc,&rect);
		RTGUI_DC_FC(dc) = color;
	}

	rtgui_dc_end_drawing(dc);

	return RT_TRUE;
}

void rtgui_button_set_text(rtgui_button_t* btn, const char* text)
{
	if(btn == RT_NULL)return;

	rtgui_label_set_text(RTGUI_LABEL(btn), text);

	/* update widget */
	rtgui_theme_draw_button(btn);
}
