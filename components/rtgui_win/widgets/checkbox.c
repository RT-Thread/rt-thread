#include <rtgui/dc.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/container.h>
#include <rtgui/widgets/checkbox.h>

static rt_bool_t rtgui_checkbox_onunfocus(PVOID wdt, rtgui_event_t* event);

static void _rtgui_checkbox_constructor(rtgui_checkbox_t *checkbox)
{
	/* init widget and set event handler */
	RTGUI_WIDGET_FLAG(checkbox) |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	rtgui_widget_set_event_handler(checkbox, rtgui_checkbox_event_handler);

	rtgui_widget_set_onunfocus(checkbox, rtgui_checkbox_onunfocus);
	/* set status */
	checkbox->value = 0;

	/* set default gc */
	RTGUI_WIDGET_TEXTALIGN(checkbox) = RTGUI_ALIGN_LEFT | RTGUI_ALIGN_CENTER_VERTICAL;
}

static void _rtgui_checkbox_destructor(rtgui_checkbox_t *checkbox)
{
	
}

rtgui_type_t *rtgui_checkbox_type_get(void)
{
	static rtgui_type_t *checkbox_type = RT_NULL;

	if(!checkbox_type)
	{
		checkbox_type = rtgui_type_create("checkbox", RTGUI_LABEL_TYPE,
			sizeof(rtgui_checkbox_t), 
			RTGUI_CONSTRUCTOR(_rtgui_checkbox_constructor), 
			RTGUI_DESTRUCTOR(_rtgui_checkbox_destructor));
	}

	return checkbox_type;
}

rtgui_checkbox_t* rtgui_checkbox_create(PVOID parent,const char* text, rt_bool_t checked,rtgui_color_t fc,int left,int top)
{
    rtgui_checkbox_t* box;
	
	RT_ASSERT(parent != RT_NULL);

    box = rtgui_widget_create (RTGUI_CHECKBOX_TYPE);
    if(box != RT_NULL)
    {
		rtgui_rect_t rect,text_rect;

		rtgui_widget_get_rect(parent, &rect);
		rtgui_widget_rect_to_device(parent,&rect);
		/* set default rect */
		rtgui_font_get_string_rect(RTGUI_WIDGET_FONT(box), text, &text_rect);
		text_rect.x2 += RTGUI_WIDGET_BORDER(box) + 5 + (RTGUI_WIDGET_BORDER(box) << 1);
		text_rect.y2 += (RTGUI_WIDGET_BORDER(box) << 1);

		rect.x1 += left;
		rect.y1 += top;
		rect.x2 = rect.x1 + CHECK_BOX_W + rtgui_rect_width(text_rect);
		rect.y2 = rect.y1 + rtgui_rect_height(text_rect);

		rtgui_widget_set_rect(box, &rect);

		rtgui_checkbox_set_text(box, text);
		RTGUI_WIDGET_FOREGROUND(box) = fc;
		if(checked == RT_TRUE)
			box->value = 1;
		else
			box->value = 0;
		rtgui_container_add_child(parent, box);  
	}

	return box;
}

void rtgui_checkbox_destroy(rtgui_checkbox_t* box)
{
	rtgui_widget_destroy(box);
}

rt_bool_t rtgui_checkbox_event_handler(PVOID wdt, rtgui_event_t* event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_checkbox_t* box = (rtgui_checkbox_t*)widget;

	switch (event->type)
	{
		case RTGUI_EVENT_PAINT:
			if(widget->on_draw != RT_NULL)
			{
				return widget->on_draw(widget, event);
			}
			else
				rtgui_theme_draw_checkbox(box);
			break;
	
		case RTGUI_EVENT_MOUSE_BUTTON:
			if(RTGUI_WIDGET_IS_ENABLE(widget) && !RTGUI_WIDGET_IS_HIDE(widget))
			{
				rtgui_event_mouse_t* emouse = (rtgui_event_mouse_t*)event;
				if(emouse->button & RTGUI_MOUSE_BUTTON_LEFT && emouse->button & RTGUI_MOUSE_BUTTON_UP)
				{
					if(box->value)
					{
						/* check it */
						box->value = 0;
					}
					else
					{
						/* un-check it */
						box->value = 1;
					}
				}
				else if(emouse->button & RTGUI_MOUSE_BUTTON_LEFT && emouse->button & RTGUI_MOUSE_BUTTON_DOWN)
				{
					/* set focus */
					rtgui_widget_focus(widget);
				}
				/* draw checkbox */
				rtgui_theme_draw_checkbox(box);
	
				/* call user callback */
				if(widget->on_mouseclick != RT_NULL)
				{
					return widget->on_mouseclick(widget, event);
				}
			}
	
			return RT_TRUE;
		default:
			break;
	}

	return RT_FALSE;
}

void rtgui_checkbox_set_checked(rtgui_checkbox_t* checkbox, rt_bool_t checked)
{
	RT_ASSERT(checkbox != RT_NULL);
	if(checked == RT_TRUE)
		checkbox->value = 1;
	else
		checkbox->value = 0;
		
}

rt_bool_t rtgui_checkbox_get_checked(rtgui_checkbox_t* checkbox)
{
	RT_ASSERT(checkbox != RT_NULL);

	if(checkbox->value)
		return RT_TRUE;

	return RT_FALSE;
}

static rt_bool_t rtgui_checkbox_onunfocus(PVOID wdt, rtgui_event_t* event)
{
	rtgui_rect_t rect;
	rtgui_checkbox_t* box = (rtgui_checkbox_t*)wdt;
	rtgui_dc_t *dc;

	RT_ASSERT(box != RT_NULL);

	dc = rtgui_dc_begin_drawing(box);
	if(dc == RT_NULL)return RT_FALSE;

	rtgui_widget_get_rect(box, &rect);

	if(!RTGUI_WIDGET_IS_FOCUSED(box))
	{//Çå³ý½¹µã¿ò
		rtgui_rect_t tmp_rect;
		rtgui_color_t color;
		rtgui_font_get_string_rect(RTGUI_WIDGET_FONT(box), rtgui_label_get_text(RTGUI_LABEL(box)), &tmp_rect);
		
		rtgui_rect_moveto(&tmp_rect,rect.x1+CHECK_BOX_W+7, rect.y1);
		tmp_rect.x1 -= 1;
		tmp_rect.x2 += 2;
		tmp_rect.y2 = rect.y2-1;
		
		/* draw focused border */
		color = RTGUI_DC_FC(dc);
		RTGUI_DC_FC(dc) = RTGUI_DC_BC(dc);
		rtgui_dc_draw_focus_rect(dc,&tmp_rect);
		RTGUI_DC_FC(dc) = color;
	}

	rtgui_dc_end_drawing(dc);

	return RT_TRUE;
}

void rtgui_checkbox_set_text(rtgui_checkbox_t *box, const char* text)
{
	RT_ASSERT(box != RT_NULL);

	if(RTGUI_LABEL(box)->text != RT_NULL)
	{
		/* release old text memory */
		rt_free(RTGUI_LABEL(box)->text);
		RTGUI_LABEL(box)->text = RT_NULL;
	}

	if(text != RT_NULL) 
		RTGUI_LABEL(box)->text = rt_strdup(text);
	else 
		RTGUI_LABEL(box)->text = RT_NULL;	
}
