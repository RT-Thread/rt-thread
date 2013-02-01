/*
 * File      : digfont.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-12-21     pife         first version
 */

#include <rtgui/dc.h>
#include <rtgui/widgets/digtube.h>

static void _rtgui_digtube_constructor(struct rtgui_digtube * digtube)
{
    RTGUI_WIDGET_TEXTALIGN(digtube) = RTGUI_ALIGN_CENTER;

	/* init widget and set event handler */
	rtgui_object_set_event_handler(RTGUI_OBJECT(digtube), rtgui_digtube_event_handler);
}

static void _rtgui_digtube_destructor(struct rtgui_digtube *digtube)
{
#ifndef RTGUI_DIGTUBE_USE_CONST_FONT
	/* release font memory */
	rt_free(digtube->digitfont.data);
	digtube->digitfont.data = RT_NULL;
#endif
}

DEFINE_CLASS_TYPE(digtube, "digtube",
				  RTGUI_WIDGET_TYPE,
				  _rtgui_digtube_constructor,
				  _rtgui_digtube_destructor,
				  sizeof(struct rtgui_digtube));

rt_bool_t rtgui_digtube_event_handler(struct rtgui_object *object, struct rtgui_event *event)
{
	struct rtgui_digtube *digtube;
    struct rtgui_dc *dc;
    rtgui_rect_t rect;
    rtgui_rect_t text_rect;
	rtgui_color_t color;
	char * disbuf;
	char tempbuf[8];
	int i;

	RTGUI_WIDGET_EVENT_HANDLER_PREPARE

	digtube = RTGUI_DIGTUBE(object);
	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:

	    dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(object));
		if (dc == RT_NULL)
			break;
		rtgui_widget_get_rect(RTGUI_WIDGET(object), &rect);
		rtgui_dc_fill_rect(dc, &rect);

		if (! (digtube->tube_style & RTGUI_DIGTUBE_STYLE_NOBACKFONT))
		{
			color = RTGUI_DC_BC(dc);
			RTGUI_DC_BC(dc) = digtube->digit_bc;
		}
		
		if (digtube->tube_style & RTGUI_DIGTUBE_STYLE_DISCODES)
			disbuf = (char *) (digtube->value);
		else
		{
			const char * format =  
				digtube->tube_style & RTGUI_DIGTUBE_STYLE_DISHEXNUM ? 
				"%7x" : "%7d";

			disbuf = &tempbuf[0];
			rt_snprintf(disbuf, 8, format, digtube->value);
			
			/* */
			for (i=0; i<7; i++)
			{
				if (disbuf[i] == ' ')
					disbuf[i] = 0;
				else
				{
					disbuf[i] = (disbuf[i] >= '0' && disbuf[i] <= '9') ? disbuf[i] - '0':
						disbuf[i] - 'a' + 10;

					disbuf[i] = digtube_code_table[disbuf[i]];
				}
			}

			disbuf = tempbuf + 7 - digtube->tube_count;
		}

		text_rect.x1 = 0;
		text_rect.y1 = 0;
		text_rect.x2 = (digtube->digit_width + digtube->digit_space) * digtube->tube_count
		                -digtube->digit_space;
		text_rect.y2 = digtube->digit_hight;

		rtgui_rect_moveto_align(&rect, &text_rect, RTGUI_DC_TEXTALIGN(dc));
		for (i=0; i<digtube->tube_count; i++)
		{
			rtgui_dc_draw_digitfont_code(dc, &digtube->digitfont, &text_rect, disbuf[i]);
			text_rect.x1 += digtube->digit_width + digtube->digit_space;
		}

		if (! (digtube->tube_style & RTGUI_DIGTUBE_STYLE_NOBACKFONT))
			RTGUI_DC_BC(dc) = color;
		rtgui_dc_end_drawing(dc);
		break;
	default:
		return rtgui_widget_event_handler(object, event);
	}

	return RT_FALSE;
}

rtgui_digtube_t *rtgui_digtube_create(
	struct rtgui_digitfont * digitfont, 
	int count, 
	void * value, 
	int style)
{
	struct rtgui_digtube *digtube;
	rtgui_rect_t rect;

	RT_ASSERT(count <= 7 && count > 0)

	digtube = (struct rtgui_digtube *) rtgui_widget_create(RTGUI_DIGTUBE_TYPE);
	if (digtube == RT_NULL)
		return RT_NULL;

	/* set field */
	if (digitfont == RT_NULL)
		digitfont = &digitfont_40;

	rt_memcpy(& digtube->digitfont, digitfont, sizeof(struct rtgui_digitfont));

#ifndef RTGUI_DIGTUBE_USE_CONST_FONT
	if (digtube->digitfont.data == RT_NULL)
		rtgui_digitfont_create(& digtube->digitfont);
#endif

	/* set default rect */
	rtgui_get_digfont_metrics(&digtube->digitfont, &rect);
	digtube->digit_width = rect.x2;
	digtube->digit_hight = rect.y2;
	digtube->tube_count = count;
	digtube->digit_space = RTGUI_DIGTUBE_DEFAULT_SPACE;

	rect.x2 = (rect.x2 + digtube->digit_space) * count - digtube->digit_space;
	rect.y2 = rect.y2;

	RTGUI_WIDGET_BACKGROUND(digtube) = rtgui_theme_default_bc();
	RTGUI_WIDGET_FOREGROUND(digtube) = RTGUI_DIGTUBE_DEFAULT_FC;
	rtgui_widget_set_rect(RTGUI_WIDGET(digtube), &rect);

	/* set display value */
	digtube->digit_bc = RTGUI_DIGTUBE_DEFAULT_DIGIT_BC;
	digtube->value = value;
	digtube->tube_style = style;
	
	return digtube;
}

void rtgui_digtube_destroy(rtgui_digtube_t *digtube)
{
    rtgui_widget_destroy(RTGUI_WIDGET(digtube));
}