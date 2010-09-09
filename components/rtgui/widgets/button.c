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
#include <rtgui/rtgui_theme.h>

static void _rtgui_button_constructor(rtgui_button_t *button)
{
	/* init widget and set event handler */
	RTGUI_WIDGET(button)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	rtgui_widget_set_event_handler(RTGUI_WIDGET(button), rtgui_button_event_handler);

	/* un-press button */
	button->flag = 0;

	/* set flag and on_button event handler */
	button->pressed_image = RT_NULL;
	button->unpressed_image = RT_NULL;
	button->on_button = RT_NULL;

	/* set gc */
	RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(button)) = default_foreground;
	RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(button)) = RTGUI_RGB(212, 208, 200);
	RTGUI_WIDGET_TEXTALIGN(RTGUI_WIDGET(button)) = RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL;
}

static void _rtgui_button_destructor(rtgui_button_t *button)
{
	if (button->pressed_image != RT_NULL)
	{
		rtgui_image_destroy(button->pressed_image);
		button->pressed_image = RT_NULL;
	}

	if (button->unpressed_image != RT_NULL)
	{
		rtgui_image_destroy(button->unpressed_image);
		button->unpressed_image = RT_NULL;
	}
}

rtgui_type_t *rtgui_button_type_get(void)
{
	static rtgui_type_t *button_type = RT_NULL;

	if (!button_type)
	{
		button_type = rtgui_type_create("button", RTGUI_LABEL_TYPE,
			sizeof(rtgui_button_t), 
			RTGUI_CONSTRUCTOR(_rtgui_button_constructor), 
			RTGUI_DESTRUCTOR(_rtgui_button_destructor));
	}

	return button_type;
}

rt_bool_t rtgui_button_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_button* btn;

	RT_ASSERT(widget != RT_NULL);

	btn = (struct rtgui_button*) widget;
	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
#ifndef RTGUI_USING_SMALL_SIZE		
		if (widget->on_draw != RT_NULL ) widget->on_draw(widget, event);
		else
#endif			
			rtgui_theme_draw_button(btn);
		break;

	case RTGUI_EVENT_KBD:
		{
			struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*) event;

			if (RTGUI_WIDGET_IS_HIDE(widget)) return RT_FALSE;
			if ((ekbd->key == RTGUIK_RETURN) || (ekbd->key == RTGUIK_SPACE))
			{
				if (RTGUI_KBD_IS_DOWN(ekbd))
				{
					btn->flag |= RTGUI_BUTTON_FLAG_PRESS;
				}
				else
				{
					btn->flag &= ~RTGUI_BUTTON_FLAG_PRESS;
				}

				/* draw button */
				rtgui_theme_draw_button(btn);

				if ((btn->flag & RTGUI_BUTTON_FLAG_PRESS) && (btn->on_button != RT_NULL))
				{
					/* call on button handler */
					btn->on_button(widget, event);
				}
			}
		}
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		if (RTGUI_WIDGET_IS_HIDE(widget)) return RT_FALSE;
		{
			struct rtgui_event_mouse* emouse = (struct rtgui_event_mouse*)event;

			if (btn->flag & RTGUI_BUTTON_TYPE_PUSH)
			{
				/* it's a push button */
				if (emouse->button & RTGUI_MOUSE_BUTTON_UP)
				{
					if (btn->flag & RTGUI_BUTTON_FLAG_PRESS)
					{
						btn->flag &= ~RTGUI_BUTTON_FLAG_PRESS;
					}
					else
					{
						btn->flag |= RTGUI_BUTTON_FLAG_PRESS;
					}

					/* draw button */
#ifndef RTGUI_USING_SMALL_SIZE
					if (widget->on_draw != RT_NULL ) widget->on_draw(widget, event);
					else 
#endif
						rtgui_theme_draw_button(btn);

					if (btn->on_button != RT_NULL)
					{
						/* call on button handler */
						btn->on_button(widget, event);
					}

#ifndef RTGUI_USING_SMALL_SIZE
					/* invokes call back */
					if (widget->on_mouseclick != RT_NULL &&
						emouse->button & RTGUI_MOUSE_BUTTON_UP)
						return widget->on_mouseclick(widget, event);
#endif
				}
			}
			else
			{
				if (emouse->button & RTGUI_MOUSE_BUTTON_LEFT)
				{
					/* it's a normal button */
					if (emouse->button & RTGUI_MOUSE_BUTTON_DOWN)
					{
						btn->flag |= RTGUI_BUTTON_FLAG_PRESS;
					}
					else
					{
						btn->flag &= ~RTGUI_BUTTON_FLAG_PRESS;
					}

					/* draw button */
#ifndef RTGUI_USING_SMALL_SIZE					
					if (widget->on_draw != RT_NULL ) widget->on_draw(widget, event);
					else
#endif
						rtgui_theme_draw_button(btn);

#ifndef RTGUI_USING_SMALL_SIZE
					/* invokes call back */
					if (widget->on_mouseclick != RT_NULL &&
						emouse->button & RTGUI_MOUSE_BUTTON_UP)
						return widget->on_mouseclick(widget, event);
#endif

					if (!(btn->flag & RTGUI_BUTTON_FLAG_PRESS) && (btn->on_button != RT_NULL))
					{
						/* call on button handler */
						btn->on_button(widget, event);
					}
				}

			}

			return RT_TRUE;
		}
	}

	return RT_FALSE;
}

rtgui_button_t* rtgui_button_create(char* text)
{
    struct rtgui_button* btn;

    btn = (struct rtgui_button*) rtgui_widget_create (RTGUI_BUTTON_TYPE);
    if (btn != RT_NULL)
    {
		rtgui_rect_t rect;

		/* set default rect */
		rtgui_font_get_metrics(rtgui_font_default(), text, &rect);
		rect.x2 += (RTGUI_BORDER_DEFAULT_WIDTH << 1);
		rect.y2 += (RTGUI_BORDER_DEFAULT_WIDTH << 1);
		rtgui_widget_set_rect(RTGUI_WIDGET(btn), &rect);
		rtgui_label_set_text(RTGUI_LABEL(btn), text);
    }

    return btn;
}

rtgui_button_t* rtgui_pushbutton_create(char* text)
{
	rtgui_button_t* btn;

	btn = rtgui_button_create(text);
	if (btn != RT_NULL) btn->flag |= RTGUI_BUTTON_TYPE_PUSH;

	return btn;
}

void rtgui_button_destroy(rtgui_button_t* btn)
{
	rtgui_widget_destroy(RTGUI_WIDGET(btn));
}

void rtgui_button_set_pressed_image(rtgui_button_t* btn, rtgui_image_t* image)
{
	RT_ASSERT(btn != RT_NULL);

	btn->pressed_image = image;
}

void rtgui_button_set_unpressed_image(rtgui_button_t* btn, rtgui_image_t* image)
{
	RT_ASSERT(btn != RT_NULL);

	btn->unpressed_image = image;
}

void rtgui_button_set_onbutton(rtgui_button_t* btn, rtgui_onbutton_func_t func)
{
	RT_ASSERT(btn != RT_NULL);

	btn->on_button = func;
}

