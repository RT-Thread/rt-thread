#include <rtgui/dc.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/radiobox.h>

#define RTGUI_RADIOBOX_DEFAULT_WIDTH	100
#define RTGUI_RADIOBOX_DEFAULT_HEIGHT	20

static void _rtgui_radiobox_constructor(rtgui_radiobox_t *radiobox)
{
	rtgui_rect_t rect = {0, 0, RTGUI_RADIOBOX_DEFAULT_WIDTH, RTGUI_RADIOBOX_DEFAULT_HEIGHT};

	/* init widget and set event handler */
	RTGUI_WIDGET(radiobox)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	RTGUI_WIDGET_TEXTALIGN(RTGUI_WIDGET(radiobox)) = RTGUI_ALIGN_LEFT | RTGUI_ALIGN_CENTER_VERTICAL;
	rtgui_widget_set_rect(RTGUI_WIDGET(radiobox), &rect);
	rtgui_widget_set_event_handler(RTGUI_WIDGET(radiobox), rtgui_radiobox_event_handler);

	/* set proper of control */
	radiobox->items = RT_NULL;
	radiobox->item_count = 0;
	radiobox->item_selection = -1;
	radiobox->orient = RTGUI_HORIZONTAL;
}

DEFINE_CLASS_TYPE(radiobox, "radiobox", 
	RTGUI_WIDGET_TYPE,
	_rtgui_radiobox_constructor,
	RT_NULL,
	sizeof(struct rtgui_radiobox));

static void rtgui_radiobox_onmouse(struct rtgui_radiobox* radiobox, struct rtgui_event_mouse* event)
{
	RT_ASSERT(radiobox != RT_NULL);
	RT_ASSERT(event  != RT_NULL);

	/* widget is hide, return */
	if (RTGUI_WIDGET_IS_HIDE(RTGUI_WIDGET(radiobox)) || 
		!RTGUI_WIDGET_IS_ENABLE(RTGUI_WIDGET(radiobox))) return;

	if (event->button & RTGUI_MOUSE_BUTTON_DOWN &&
		event->button & RTGUI_MOUSE_BUTTON_LEFT)
	{
		int bord_size;
		struct rtgui_rect rect;

		/* focus widgets */
		rtgui_widget_focus(RTGUI_WIDGET(radiobox));

		/* get widget physical rect */
		rtgui_widget_get_rect(RTGUI_WIDGET(radiobox), &rect);
		rtgui_widget_rect_to_device(RTGUI_WIDGET(radiobox), &rect);

		/* get board size */
		if (radiobox->orient == RTGUI_VERTICAL)
			bord_size = radiobox->item_size;
		else
		{
			struct rtgui_rect bord_rect;
			
			rtgui_font_get_metrics(RTGUI_WIDGET_FONT(RTGUI_WIDGET(radiobox)), "H", &bord_rect);
			bord_size = rtgui_rect_height(bord_rect);
		}
		rtgui_rect_inflate(&rect, - bord_size);
		if (rtgui_rect_contains_point(&rect, event->x, event->y) != RT_EOK) return;

		if (radiobox->orient == RTGUI_VERTICAL)
		{
			int delta_y = event->y - rect.y1;
			rtgui_radiobox_set_selection(radiobox, delta_y / radiobox->item_size);
		}
		else
		{
			int delta_x = event->x - rect.x1;
			rtgui_radiobox_set_selection(radiobox, delta_x / radiobox->item_size);
		}
	}
}

rt_bool_t rtgui_radiobox_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_radiobox* radiobox = (struct rtgui_radiobox*)widget;

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_draw != RT_NULL) widget->on_draw(widget, event);
		else
#endif
		{
			rtgui_theme_draw_radiobox(radiobox);
		}

		break;

	case RTGUI_EVENT_KBD:
		if (RTGUI_WIDGET_IS_HIDE(RTGUI_WIDGET(radiobox))) return RT_FALSE;

#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_key != RT_NULL) widget->on_key(widget, event);
		else
#endif
		{
            struct rtgui_event_kbd *e = (struct rtgui_event_kbd*)event;

            /* set focused */
            rtgui_widget_focus(RTGUI_WIDGET(radiobox));
            if (!(RTGUI_KBD_IS_UP(e))) return RT_FALSE;

			if (radiobox->orient == RTGUI_VERTICAL)
			{
	            if (e->key == RTGUIK_UP)
	            {
	                if (radiobox->item_selection > 0)
	                    rtgui_radiobox_set_selection(radiobox, radiobox->item_selection - 1);
	            }
	            else if (e->key == RTGUIK_DOWN)
	            {
	                if (radiobox->item_selection < radiobox->item_count - 1)
	                    rtgui_radiobox_set_selection(radiobox, radiobox->item_selection + 1);
	            }
			}
			else
			{
	            if (e->key == RTGUIK_LEFT)
	            {
	                if (radiobox->item_selection > 0)
	                    rtgui_radiobox_set_selection(radiobox, radiobox->item_selection - 1);
	            }
	            else if (e->key == RTGUIK_RIGHT)
	            {
	                if (radiobox->item_selection < radiobox->item_count - 1)
	                    rtgui_radiobox_set_selection(radiobox, radiobox->item_selection + 1);
	            }
			}
        }
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_mouseclick != RT_NULL) widget->on_mouseclick(widget, event);
		else
#endif
		{
			rtgui_radiobox_onmouse(radiobox, (struct rtgui_event_mouse*)event);
		}
		break;
	}

	return RT_FALSE;
}

struct rtgui_radiobox* rtgui_radiobox_create(const char* label, int orient, char** radio_items, int number)
{
    struct rtgui_radiobox* radiobox;

    radiobox = (struct rtgui_radiobox*) rtgui_widget_create (RTGUI_RADIOBOX_TYPE);
    if (radiobox != RT_NULL)
    {
    	rt_uint8_t board_size;
		struct rtgui_rect rect;
		
        radiobox->items = radio_items;
        radiobox->item_count = number;
        radiobox->item_selection = -1;
		radiobox->text = rt_strdup(label);

		/* set proper of control */
		rtgui_radiobox_set_orientation(radiobox, orient);
		rtgui_font_get_metrics(RTGUI_WIDGET_FONT(RTGUI_WIDGET(radiobox)), "H", &rect);
		board_size = rtgui_rect_height(rect);

		if (orient == RTGUI_VERTICAL)
		{
			radiobox->item_size = board_size;
		}
		else
		{
			int index;
			struct rtgui_font* font;
			struct rtgui_rect rect;

			/* set init item size */
			radiobox->item_size = 0;
			
			font = RTGUI_WIDGET_FONT(RTGUI_WIDGET(radiobox));
			for (index = 0; index < number; index ++)
			{
				rtgui_font_get_metrics(font, radio_items[index], &rect);
				if ( (board_size + 3 + rtgui_rect_width(rect)) > radiobox->item_size)
					radiobox->item_size = board_size + 3 + rtgui_rect_width(rect);
			}
		}

		if (radiobox->item_size < RADIO_BOX_H + 2)
			radiobox->item_size = RADIO_BOX_H + 2;
	}

	return radiobox;
}

void rtgui_radiobox_set_orientation(struct rtgui_radiobox* radiobox, int orientation)
{
	RT_ASSERT(radiobox != RT_NULL);

	/* set orientation */
	radiobox->orient = orientation;
#ifndef RTGUI_USING_SMALL_SIZE
	if (radiobox->orient == RTGUI_HORIZONTAL)
	{
		/* HORIZONTAL */
		rtgui_widget_set_miniheight(RTGUI_WIDGET(radiobox), RTGUI_RADIOBOX_DEFAULT_HEIGHT);
		rtgui_widget_set_miniwidth(RTGUI_WIDGET(radiobox), RTGUI_RADIOBOX_DEFAULT_WIDTH);
	}
	else
	{
		/* VERTICAL */
		rtgui_widget_set_miniwidth(RTGUI_WIDGET(radiobox), RTGUI_RADIOBOX_DEFAULT_HEIGHT);
		rtgui_widget_set_miniheight(RTGUI_WIDGET(radiobox), RTGUI_RADIOBOX_DEFAULT_WIDTH);
	}
#endif
}

void rtgui_radiobox_set_selection(struct rtgui_radiobox* radiobox, int selection)
{
	rt_uint16_t old_item;

	if (selection == radiobox->item_selection) return;

	old_item = radiobox->item_selection;
    if (selection >= 0 && selection < radiobox->item_count)
    {
    	radiobox->item_selection = selection;
    }

    /* update radiobox widget */
	rtgui_theme_draw_radiobutton(radiobox, old_item);
	rtgui_theme_draw_radiobutton(radiobox, radiobox->item_selection);
}

int rtgui_radiobox_get_selection(struct rtgui_radiobox* radiobox)
{
    return radiobox->item_selection;
}
