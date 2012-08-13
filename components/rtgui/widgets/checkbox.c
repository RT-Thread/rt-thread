#include <rtgui/dc.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/checkbox.h>

static void _rtgui_checkbox_constructor(rtgui_checkbox_t *box)
{
	/* init widget and set event handler */
	RTGUI_WIDGET(box)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	rtgui_object_set_event_handler(RTGUI_OBJECT(box), rtgui_checkbox_event_handler);

	/* set status */
	box->status_down = RTGUI_CHECKBOX_STATUS_UNCHECKED;
	box->on_button = RT_NULL;

	/* set default gc */
	RTGUI_WIDGET_TEXTALIGN(box) = RTGUI_ALIGN_LEFT | RTGUI_ALIGN_CENTER_VERTICAL;
}

DEFINE_CLASS_TYPE(checkbox, "checkbox",
	RTGUI_LABEL_TYPE,
	_rtgui_checkbox_constructor,
	RT_NULL,
	sizeof(struct rtgui_checkbox));

void rtgui_checkbox_set_onbutton(rtgui_checkbox_t* checkbox, rtgui_onbutton_func_t func)
{
	RT_ASSERT(checkbox != RT_NULL);

	checkbox->on_button = func;
}

rt_bool_t rtgui_checkbox_event_handler(struct rtgui_object* object, struct rtgui_event* event)
{
	struct rtgui_checkbox *box;

	RTGUI_WIDGET_EVENT_HANDLER_PREPARE

	box = RTGUI_CHECKBOX(object);

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_draw != RT_NULL)
		{
			return widget->on_draw(RTGUI_OBJECT(widget), event);
		}
		else
#endif
			rtgui_theme_draw_checkbox(box);
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		{
			if (RTGUI_WIDGET_IS_ENABLE(widget) && !RTGUI_WIDGET_IS_HIDE(widget))
			{
				struct rtgui_event_mouse* emouse = (struct rtgui_event_mouse*)event;
				if (emouse->button & RTGUI_MOUSE_BUTTON_LEFT &&
					emouse->button & RTGUI_MOUSE_BUTTON_UP)
				{
					/* set focus */
					rtgui_widget_focus(widget);

					if (box->status_down & RTGUI_CHECKBOX_STATUS_UNCHECKED)
					{
						/* check it */
						box->status_down = RTGUI_CHECKBOX_STATUS_CHECKED;
					}
					else
					{
						/* un-check it */
						box->status_down = RTGUI_CHECKBOX_STATUS_UNCHECKED;
					}
				}

				/* draw checkbox */
				rtgui_theme_draw_checkbox(box);

#ifndef RTGUI_USING_SMALL_SIZE
				/* call user callback */
				if (widget->on_mouseclick != RT_NULL)
				{
					return widget->on_mouseclick(RTGUI_OBJECT(widget), event);
				}
#endif
				if (box->on_button != RT_NULL)
				{
					box->on_button(RTGUI_OBJECT(widget), event);
					return RT_TRUE;
				}
			}

			return RT_TRUE;
		}
	default:
		return rtgui_widget_event_handler(object, event);
	}

	return RT_FALSE;
}

struct rtgui_checkbox* rtgui_checkbox_create(const char* text, rt_bool_t checked)
{
    struct rtgui_checkbox* box;

    box = (struct rtgui_checkbox*) rtgui_widget_create (RTGUI_CHECKBOX_TYPE);
    if (box != RT_NULL)
    {
		rtgui_rect_t rect;

		/* set default rect */
		rtgui_font_get_metrics(rtgui_font_default(), text, &rect);
		rect.x2 += RTGUI_BORDER_DEFAULT_WIDTH + 5 + (RTGUI_BORDER_DEFAULT_WIDTH << 1);
		rect.y2 += (RTGUI_BORDER_DEFAULT_WIDTH << 1);

		rtgui_widget_set_rect(RTGUI_WIDGET(box), &rect);
		rtgui_label_set_text(RTGUI_LABEL(box), text);
		
		if (checked == RT_TRUE)
			box->status_down = RTGUI_CHECKBOX_STATUS_CHECKED;
		else
			box->status_down = RTGUI_CHECKBOX_STATUS_UNCHECKED;
	}

	return box;
}

void rtgui_checkbox_destroy(rtgui_checkbox_t* box)
{
	rtgui_widget_destroy(RTGUI_WIDGET(box));
}

void rtgui_checkbox_set_checked(rtgui_checkbox_t* checkbox, rt_bool_t checked)
{
	RT_ASSERT(checkbox != RT_NULL);
	if (checked == RT_TRUE)
		checkbox->status_down = RTGUI_CHECKBOX_STATUS_CHECKED;
	else
		checkbox->status_down = RTGUI_CHECKBOX_STATUS_UNCHECKED;
		
}

rt_bool_t rtgui_checkbox_get_checked(rtgui_checkbox_t* checkbox)
{
	RT_ASSERT(checkbox != RT_NULL);

	if (checkbox->status_down == RTGUI_CHECKBOX_STATUS_CHECKED)
		return RT_TRUE;

	return RT_FALSE;
}

