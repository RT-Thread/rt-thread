/*
 * File      : textview.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-05     Bernard      first version
 */
#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/textview.h>

rt_inline char* _get_line_text(rtgui_textview_t *textview, rt_uint16_t index)
{
	char* line;
	if (index < textview->line_count)
	{
		line = textview->lines + (index * textview->line_width);
		return line;
	}

	return RT_NULL;
}

static void _calc_line(rtgui_textview_t *textview, const char* text)
{
	char* line;
	const unsigned char* ptr;
	rt_ubase_t line_index, line_position;

	if (textview->lines != RT_NULL)
	{
		rt_free(textview->lines);
		textview->lines = RT_NULL;
		textview->line_count = 0;
	}

	/* get line count */
	line_index = 0; line_position = 0;
	ptr = (const unsigned char*)text;
	if (*ptr == 0) return;

	while (*ptr != '\0')
	{
		if (*ptr == '\n') 
		{
			line_index ++;
			line_position = 0;
		}
		else if (*ptr == '\r')
		{
			ptr ++;
			continue;
		}
		else if (*ptr == '\t')
		{
			line_position += 4;
			if (line_position >= textview->line_width - 1)
			{
				line_index ++;
				line_position = 0;
			}
		}
		else 
		{
			if ((*ptr) >= 0x80)
			{
				/* fill cjk character */
				if (line_position + 1 >= (textview->line_width - 1))
				{
					/* split to next line */
					line_index ++;
					line_position = 0;
				}

				line_position ++;
				line_position ++;
			}
			else 
			{
				line_position ++;
			}

			if (line_position >= textview->line_width - 1)
			{
				line_index ++;
				line_position = 0;
			}
		}

		ptr ++;
	}

	/* set line count */
	textview->line_count = line_index + 1;

	/* allocate lines */
	textview->lines = rt_malloc(textview->line_count * textview->line_width);
	rt_memset(textview->lines, 0, (textview->line_count * textview->line_width));

	/* fill lines */
	line_index = 0; line_position = 0;
	ptr = (const unsigned char*)text;
	line = _get_line_text(textview, line_index);
	while (*ptr)
	{
		if (*ptr == '\n') 
		{
			line_index ++;
			line_position = 0;
			line = _get_line_text(textview, line_index);
		}
		else if (*ptr == '\r')
		{
			/* ignore '\r' */
			ptr ++;
			continue;
		}
		else if (*ptr == '\t')
		{
			line[line_position++] = ' ';
			line[line_position++] = ' ';
			line[line_position++] = ' ';
			line[line_position++] = ' ';
			if (line_position >= textview->line_width - 1)
			{
				line_index ++;
				line_position = 0;
				line = _get_line_text(textview, line_index);
			}
		}
		else 
		{
			if ((*ptr) >= 0x80)
			{
				/* fill cjk character */
				if (line_position + 1 >= (textview->line_width - 1))
				{
					/* split to next line */
					line_index ++;
					line_position = 0;
					line = _get_line_text(textview, line_index);
				}

				line[line_position ++] = *ptr ++;
				line[line_position ++] = *ptr;
			}
			else 
			{
				line[line_position ++] = *ptr;
			}

			if (line_position >= textview->line_width - 1)
			{
				line_index ++;
				line_position = 0;
				line = _get_line_text(textview, line_index);
			}
		}

		ptr ++;
	}

	textview->line_current = 0;
}

static void _calc_width(rtgui_textview_t *textview)
{
	rtgui_rect_t rect;
	rt_uint16_t width, height;

	width = rtgui_rect_width(RTGUI_WIDGET(textview)->extent) - 6;
	height = rtgui_rect_height(RTGUI_WIDGET(textview)->extent);

	rtgui_font_get_metrics(RTGUI_WIDGET_FONT(RTGUI_WIDGET(textview)), "W", &rect);
	textview->line_width = width / rtgui_rect_width(rect) + 1;
	textview->line_page_count = height / (rtgui_rect_height(rect) + 3);

	/* set minimal value */
	if (textview->line_page_count == 0) textview->line_page_count = 1;
}

static void _draw_textview(rtgui_textview_t *textview)
{
	struct rtgui_dc* dc;
	struct rtgui_rect rect, font_rect;
	char* line;
	rt_ubase_t line_index, item_height;

	rtgui_font_get_metrics(RTGUI_WIDGET_FONT(RTGUI_WIDGET(textview)), "W", &font_rect);
	item_height = rtgui_rect_height(font_rect) + 3;

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(textview));
	if (dc == RT_NULL) return ;

	/* fill rect */
	rtgui_widget_get_rect(RTGUI_WIDGET(textview), &rect);
	rtgui_dc_fill_rect(dc, &rect);

	rect.x1 += 3;
	rect.x2 -= 3;

	for (line_index = textview->line_current; 
		(line_index < textview->line_current + textview->line_page_count) &&
		(line_index < textview->line_count); 
		line_index ++)
	{
		line = (char* )_get_line_text(textview, line_index);
		rtgui_dc_draw_text(dc, line, &rect);

		rect.y1 += item_height;
	}

	rtgui_dc_end_drawing(dc);
}

static void _rtgui_textview_constructor(rtgui_textview_t *textview)
{
	/* init widget and set event handler */
	rtgui_widget_set_event_handler(RTGUI_WIDGET(textview), rtgui_textview_event_handler);
	RTGUI_WIDGET(textview)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;

	/* set field */
	textview->line_count = 0;
	textview->lines = RT_NULL;

	textview->line_current = -1;
	textview->line_page_count = 1;
}

static void _rtgui_textview_destructor(rtgui_textview_t *textview)
{
	/* release line memory */
	rt_free(textview->lines);
	textview->lines = RT_NULL;
}

DEFINE_CLASS_TYPE(textview, "textview", 
	RTGUI_WIDGET_TYPE,
	_rtgui_textview_constructor,
	_rtgui_textview_destructor,
	sizeof(struct rtgui_textview));

rt_bool_t rtgui_textview_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_textview* textview;

	RT_ASSERT(widget != RT_NULL);

	textview = (struct rtgui_textview*) widget;
	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		_draw_textview(textview);
		break;
	
	case RTGUI_EVENT_KBD:
		{
		struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
		if (ekbd->type == RTGUI_KEYDOWN)
		{
			rt_int16_t line_current_update;
			line_current_update = textview->line_current;
			if (ekbd->key == RTGUIK_LEFT)
			{
				if (textview->line_current > textview->line_page_count)
				{
					line_current_update -= textview->line_page_count;
				}
				else if (textview->line_current > 0)
				{
					line_current_update = 0;
				}
			}
			else if (ekbd->key == RTGUIK_RIGHT)
			{
				if (textview->line_current + textview->line_page_count < textview->line_count - 1)
				{
					line_current_update += textview->line_page_count;
				}
			}
			else if (ekbd->key == RTGUIK_UP)
			{
				if (textview->line_current > 0)
				{
					line_current_update --;
				}
			}
			else if (ekbd->key == RTGUIK_DOWN)
			{
				if (textview->line_current + textview->line_page_count < textview->line_count - 1)
				{
					line_current_update ++;
				}
			}

			if (textview->line_current != line_current_update)
			{
				textview->line_current = line_current_update;
				rtgui_widget_update(widget);
				return RT_TRUE;
			}
		}
		break;
		}
	}

	return RT_FALSE;
}

rtgui_textview_t* rtgui_textview_create(const char* text, const rtgui_rect_t *rect)
{
    struct rtgui_textview* textview;

    textview = (struct rtgui_textview*) rtgui_widget_create(RTGUI_TEXTVIEW_TYPE);
    if (textview != RT_NULL)
    {
		rtgui_widget_set_rect(RTGUI_WIDGET(textview), rect);

		/* calculate line width and line page count */
		_calc_width(textview);

		/* set text */
		_calc_line(textview, text);
    }

    return textview;
}

void rtgui_textview_destroy(rtgui_textview_t* textview)
{
	rtgui_widget_destroy(RTGUI_WIDGET(textview));
}

void rtgui_textview_set_text(rtgui_textview_t* textview, const char* text)
{
	RT_ASSERT(textview != RT_NULL);

	/* calculate line width and line page count */
	_calc_width(textview);

	/* set text */
	_calc_line(textview, text);

	/* update widget */
	rtgui_widget_update(RTGUI_WIDGET(textview));
}
