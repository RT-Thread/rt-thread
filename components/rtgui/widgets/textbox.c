/*
 * File      : textbox.c
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
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/textbox.h>

#ifndef _WIN32
#include <ctype.h>
#endif

#define RTGUI_TEXTBOX_LINE_MAX		64
#define RTGUI_TEXTBOX_MARGIN		3

static void rtgui_textbox_onkey(struct rtgui_textbox* box, struct rtgui_event_kbd* event);
static rt_bool_t rtgui_textbox_onfocus(struct rtgui_widget* widget, struct rtgui_event* event);
static rt_bool_t rtgui_textbox_onunfocus(struct rtgui_widget* widget, struct rtgui_event* event);

static void _rtgui_textbox_caret_timeout(struct rtgui_timer* timer, void* parameter)
{
	rtgui_textbox_t* box;
	
	box = (rtgui_textbox_t*)parameter;
	/* set caret flag */
	if (box->flag & RTGUI_TEXTBOX_CARET_SHOW)
		box->flag &= ~RTGUI_TEXTBOX_CARET_SHOW;
	else
		box->flag |= RTGUI_TEXTBOX_CARET_SHOW;

	/* re-darw textbox */
	rtgui_theme_draw_textbox(box);

	return ;
}

static void _rtgui_textbox_constructor(rtgui_textbox_t *box)
{
	rtgui_rect_t rect = {0, 0, RTGUI_TEXTBOX_DEFAULT_WIDTH, RTGUI_TEXTBOX_DEFAULT_HEIGHT};
	rtgui_widget_set_rect(RTGUI_WIDGET(box), &rect);

	RTGUI_WIDGET(box)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	rtgui_widget_set_event_handler(RTGUI_WIDGET(box), rtgui_textbox_event_handler);
	rtgui_widget_set_onfocus(RTGUI_WIDGET(box), rtgui_textbox_onfocus);
	rtgui_widget_set_onunfocus(RTGUI_WIDGET(box), rtgui_textbox_onunfocus);

	/* set default text align */
	RTGUI_WIDGET_TEXTALIGN(RTGUI_WIDGET(box)) = RTGUI_ALIGN_CENTER_VERTICAL;

	/* set proper of control */
	box->caret_timer = rtgui_timer_create(RT_TICK_PER_SECOND, RT_TIMER_FLAG_PERIODIC, 
		_rtgui_textbox_caret_timeout, box);

	box->line = box->line_begin = box->position = 0;
	box->flag = RTGUI_TEXTBOX_SINGLE;

	/* allocate default line buffer */
	box->text = RT_NULL;

	rtgui_font_get_metrics(RTGUI_WIDGET(box)->gc.font, "h", &rect);
	box->font_width = rtgui_rect_width(rect);
}

static void _rtgui_textbox_deconstructor(rtgui_textbox_t *box)
{
	if (box->text != RT_NULL)
	{
		rt_free(box->text);
		box->text = RT_NULL;
	}

	rtgui_timer_destory(box->caret_timer);
	box->caret_timer = RT_NULL;
}

rtgui_type_t *rtgui_textbox_type_get(void)
{
	static rtgui_type_t *textbox_type = RT_NULL;

	if (!textbox_type)
	{
		textbox_type = rtgui_type_create("textbox", RTGUI_WIDGET_TYPE,
			sizeof(rtgui_textbox_t),
			RTGUI_CONSTRUCTOR(_rtgui_textbox_constructor),
			RTGUI_DESTRUCTOR(_rtgui_textbox_deconstructor));
	}

	return textbox_type;
}

static void rtgui_textbox_onmouse(struct rtgui_textbox* box, struct rtgui_event_mouse* event)
{
	rt_size_t length;

	RT_ASSERT(box != RT_NULL);
	RT_ASSERT(event != RT_NULL);

	length = rt_strlen((const char*)box->text);

	if (event->button & RTGUI_MOUSE_BUTTON_LEFT &&
		event->button & RTGUI_MOUSE_BUTTON_DOWN)
	{
		rt_int32_t x;

		/* set caret position */
		x = event->x - RTGUI_WIDGET(box)->extent.x1;
		if (x < 0)
		{
			box->position = 0;
		}
		else if (x > length * box->font_width)
		{
			box->position = length;
		}
		else
		{
			box->position = x / box->font_width;
		}

		/* set caret to show */
		box->flag |= RTGUI_TEXTBOX_CARET_SHOW;

		/* set widget focus */
		rtgui_widget_focus(RTGUI_WIDGET(box));
		/* re-draw text box */
		rtgui_theme_draw_textbox(box);
	}
}

static void rtgui_textbox_onkey(struct rtgui_textbox* box, struct rtgui_event_kbd* event)
{
	rt_size_t length;

	RT_ASSERT(box != RT_NULL);
	RT_ASSERT(event != RT_NULL);

	if (event->type != RTGUI_KEYUP)
		return ;

	length = rt_strlen((const char*)box->text);
	if (event->key == RTGUIK_DELETE)
	{
		if (box->position == length - 1)
		{
			box->text[box->position] = '\0';
		}
		else
		{
			char *c;

			/* remove character */
			for (c = &box->text[box->position]; c[1] != '\0'; c++)
				*c = c[1];
			*c = '\0';
		}
	}
	else if (event->key == RTGUIK_BACKSPACE)
	{
		if (box->position == length - 1)
		{
			box->text[box->position] = '\0';
			box->position --;
		}
		else if (box->position != 0)
		{
			/* remove current character */
			char *c;

			/* remove character */
			for (c = &box->text[box->position - 1]; c[1] != '\0'; c++)
				*c = c[1];
			*c = '\0';
			box->position --;
		}
	}
	else if (event->key == RTGUIK_LEFT)
	{
		if (box->position > 0) box->position --;
	}
	else if (event->key == RTGUIK_RIGHT)
	{
		if (box->position < length) box->position ++;
	}
	else if (event->key == RTGUIK_HOME)
	{
		box->position = 0;
	}
	else if (event->key == RTGUIK_END)
	{
		box->position = length;
	}
	else if (event->key == RTGUIK_RETURN)
	{
		if (box->on_enter != RT_NULL)
		{
			box->on_enter(RTGUI_WIDGET(box), RT_NULL);
		}
	}
	else
	{
		if (isprint(event->key) || isdigit(event->key))
		{
			/* no buffer on this line */
			if (length + 1 > box->line_length) return;

			if (box->position < length - 1)
			{
				char* c;

				for (c = &box->text[length]; c != &box->text[box->position]; c--)
					*c = *(c-1);
				box->text[length + 1] = '\0';
			}

			box->text[box->position] = event->key;
			box->position ++;
		}
	}

	/* set caret to show */
	box->flag |= RTGUI_TEXTBOX_CARET_SHOW;

	/* re-draw text box */
	rtgui_theme_draw_textbox(box);
}

static rt_bool_t rtgui_textbox_onfocus(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_textbox* box = (struct rtgui_textbox*)widget;

	/* set caret to show */
	box->flag |= RTGUI_TEXTBOX_CARET_SHOW;
	/* start caret timer */
	rtgui_timer_start(box->caret_timer);

	return RT_TRUE;
}

static rt_bool_t rtgui_textbox_onunfocus(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_textbox* box = (struct rtgui_textbox*)widget;

	/* stop caret timer */
	rtgui_timer_stop(box->caret_timer);
	/* set caret to hide */
	box->flag &= ~RTGUI_TEXTBOX_CARET_SHOW;

	return RT_TRUE;
}

rt_bool_t rtgui_textbox_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_textbox* box = (struct rtgui_textbox*)widget;

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_draw != RT_NULL) widget->on_draw(widget, event);
		else 
#endif
			rtgui_theme_draw_textbox(box);
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		if (!RTGUI_WIDGET_IS_ENABLE(widget) || RTGUI_WIDGET_IS_HIDE(widget)) return RT_FALSE;

#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_mouseclick != RT_NULL) widget->on_mouseclick(widget, event);
		else 
#endif
			rtgui_textbox_onmouse(box, (struct rtgui_event_mouse*)event);
		return RT_TRUE;

	case RTGUI_EVENT_KBD:
		if (!RTGUI_WIDGET_IS_ENABLE(widget) || RTGUI_WIDGET_IS_HIDE(widget)) return RT_FALSE;

#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_key != RT_NULL) widget->on_key(widget, event);
		else 
#endif
			rtgui_textbox_onkey(box, (struct rtgui_event_kbd*)event);
		return RT_TRUE;
	}

	return RT_FALSE;
}

struct rtgui_textbox* rtgui_textbox_create(const char* text, rt_uint8_t flag)
{
    struct rtgui_textbox* box;

    box = (struct rtgui_textbox*) rtgui_widget_create (RTGUI_TEXTBOX_TYPE);
    if (box != RT_NULL)
    {
		rtgui_rect_t rect = {0, 0, RTGUI_TEXTBOX_DEFAULT_WIDTH, RTGUI_TEXTBOX_DEFAULT_HEIGHT};

		/* allocate default line buffer */
		rtgui_textbox_set_value(box, text);
		box->flag = flag;

		rtgui_font_get_metrics(RTGUI_WIDGET(box)->gc.font, "h", &rect);
	}

	return box;
}

void rtgui_textbox_destroy(struct rtgui_textbox* box)
{
	rtgui_widget_destroy(RTGUI_WIDGET(box));
}

void rtgui_textbox_set_value(struct rtgui_textbox* box, const char* text)
{
	if (box->text != RT_NULL)
	{
		if (box->line_length > rt_strlen(text) + 1)
		{
			rt_memcpy(box->text, text, rt_strlen(text) + 1);
			/* set current position */
			box->position = 0;
			return;
		}
		else
		{
			/* free the old text */
			rtgui_free(box->text);
			box->text = RT_NULL;
		}
	}

	box->line_length = RTGUI_TEXTBOX_LINE_MAX > rt_strlen(text) + 1 ?
		RTGUI_TEXTBOX_LINE_MAX : rt_strlen(text) + 1;

	/* allocate line buffer */
	box->text = rtgui_malloc(box->line_length);
	rt_memset(box->text, 0, box->line_length);

	/* copy text */
	rt_memcpy(box->text, text, rt_strlen(text) + 1);

	/* set current position */
	box->position = 0;
}

const char* rtgui_textbox_get_value(struct rtgui_textbox* box)
{
	return (const char*)box->text;
}

void rtgui_textbox_set_line_length(struct rtgui_textbox* box, rt_size_t length)
{
	rt_uint8_t* new_line;

	RT_ASSERT(box != RT_NULL);

	/* invalid length */
	if (length <= 0) return;

	new_line = rtgui_malloc(length);
	if (length < box->line_length)
	{
		rt_memcpy(new_line, box->text, length - 1);
		new_line[length] = '\0';
	}
	else
	{
		rt_memcpy(new_line, (const char*)box->text, rt_strlen((const char*)box->text));
	}

	/* set line length */
	box->line_length = length;
}

