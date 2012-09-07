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
#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/window.h>

static rt_bool_t rtgui_button_onunfocus(struct rtgui_object* object, rtgui_event_t* event);

static void _rtgui_button_constructor(rtgui_button_t *button)
{
	/* init widget and set event handler */
	RTGUI_WIDGET(button)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	rtgui_object_set_event_handler(RTGUI_OBJECT(button), rtgui_button_event_handler);
	rtgui_widget_set_onunfocus(RTGUI_WIDGET(button), rtgui_button_onunfocus);
	/* un-press button */
	button->flag = 0;

	/* set flag and on_button event handler */
	button->pressed_image = RT_NULL;
	button->unpressed_image = RT_NULL;
	button->on_button = RT_NULL;

	/* set gc */
	RTGUI_WIDGET_FOREGROUND(button) = default_foreground;
	RTGUI_WIDGET_BACKGROUND(button) = RTGUI_RGB(212, 208, 200);
	RTGUI_WIDGET_TEXTALIGN(button) = RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL;
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

DEFINE_CLASS_TYPE(button, "button", 
	RTGUI_LABEL_TYPE,
	_rtgui_button_constructor,
	_rtgui_button_destructor,
	sizeof(struct rtgui_button));

rt_bool_t rtgui_button_event_handler(struct rtgui_object* object, struct rtgui_event* event)
{
	struct rtgui_widget *widget;
	struct rtgui_button *btn;

	RT_ASSERT(object != RT_NULL);
	RT_ASSERT(event != RT_NULL);

	widget = RTGUI_WIDGET(object);
	btn = RTGUI_BUTTON(widget);
	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
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
					btn->on_button(RTGUI_OBJECT(widget), event);
				}
			}
		}
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		if (RTGUI_WIDGET_IS_HIDE(widget)) return RT_FALSE;
		{
			struct rtgui_event_mouse* emouse = (struct rtgui_event_mouse*)event;

			/* it's not this widget event, clean status */
			if (rtgui_rect_contains_point(&(RTGUI_WIDGET(btn)->extent), 
				emouse->x, emouse->y) != RT_EOK)
			{
				btn->flag &= ~RTGUI_BUTTON_FLAG_PRESS;
				/* draw button */
				rtgui_theme_draw_button(btn);

				break;
			}

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
					rtgui_theme_draw_button(btn);

					if (btn->on_button != RT_NULL)
					{
						/* call on button handler */
						btn->on_button(RTGUI_OBJECT(widget), event);
					}

#ifndef RTGUI_USING_SMALL_SIZE
					/* invokes call back */
					if (widget->on_mouseclick != RT_NULL &&
						emouse->button & RTGUI_MOUSE_BUTTON_UP)
						return widget->on_mouseclick(RTGUI_OBJECT(widget), event);
#endif
				}
			}
			else
			{
				if (emouse->button & RTGUI_MOUSE_BUTTON_LEFT)
				{
					/* set the last mouse event handled widget */
					struct rtgui_win* win;

					win = RTGUI_WIN(RTGUI_WIDGET(btn)->toplevel);
					win->last_mevent_widget = RTGUI_WIDGET(btn);

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
					rtgui_theme_draw_button(btn);

#ifndef RTGUI_USING_SMALL_SIZE
					/* invokes call back */
					if (widget->on_mouseclick != RT_NULL &&
						emouse->button & RTGUI_MOUSE_BUTTON_UP)
						return widget->on_mouseclick(RTGUI_OBJECT(widget), event);
#endif

					if (!(btn->flag & RTGUI_BUTTON_FLAG_PRESS) && (btn->on_button != RT_NULL))
					{
						/* call on button handler */
						btn->on_button(RTGUI_OBJECT(widget), event);
					}
				}

			}

			return RT_TRUE;
		}
	default:
		return rtgui_widget_event_handler(object, event);
	}

	return RT_FALSE;
}
RTM_EXPORT(rtgui_button_event_handler);

rtgui_button_t* rtgui_button_create(const char* text)
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
RTM_EXPORT(rtgui_button_create);

rtgui_button_t* rtgui_pushbutton_create(const char* text)
{
	rtgui_button_t* btn;

	btn = rtgui_button_create(text);
	if (btn != RT_NULL) btn->flag |= RTGUI_BUTTON_TYPE_PUSH;

	return btn;
}
RTM_EXPORT(rtgui_pushbutton_create);

void rtgui_button_destroy(rtgui_button_t* btn)
{
	rtgui_widget_destroy(RTGUI_WIDGET(btn));
}
RTM_EXPORT(rtgui_button_destroy);

void rtgui_button_set_pressed_image(rtgui_button_t* btn, rtgui_image_t* image)
{
	RT_ASSERT(btn != RT_NULL);

	btn->pressed_image = image;
}
RTM_EXPORT(rtgui_button_set_pressed_image);

void rtgui_button_set_unpressed_image(rtgui_button_t* btn, rtgui_image_t* image)
{
	RT_ASSERT(btn != RT_NULL);

	btn->unpressed_image = image;
}
RTM_EXPORT(rtgui_button_set_unpressed_image);

void rtgui_button_set_onbutton(rtgui_button_t* btn, rtgui_onbutton_func_t func)
{
	RT_ASSERT(btn != RT_NULL);

	btn->on_button = func;
}
RTM_EXPORT(rtgui_button_set_onbutton);

static rt_bool_t rtgui_button_onunfocus(struct rtgui_object* object, rtgui_event_t* event)
{
	rtgui_rect_t rect;
	rtgui_widget_t *widget;
	struct rtgui_dc *dc;

	RT_ASSERT(object);
	widget = RTGUI_WIDGET(object);

	dc = rtgui_dc_begin_drawing(widget);
	if(dc == RT_NULL) return RT_FALSE;
	
	rtgui_widget_get_rect(widget, &rect);

	if(!RTGUI_WIDGET_IS_FOCUSED(widget))
	{
		/* only clear focus rect */
		rtgui_color_t color;
		rtgui_rect_inflate(&rect, -2);
		color = RTGUI_DC_FC(dc);
		RTGUI_DC_FC(dc) = RTGUI_DC_BC(dc);
		rtgui_dc_draw_focus_rect(dc, &rect);
		RTGUI_DC_FC(dc) = color;
	}

	rtgui_dc_end_drawing(dc);
	return RT_TRUE;
}
