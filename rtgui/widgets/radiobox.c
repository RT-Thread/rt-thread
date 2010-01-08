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
	rtgui_widget_set_rect(RTGUI_WIDGET(radiobox), &rect);
	rtgui_widget_set_event_handler(RTGUI_WIDGET(radiobox), rtgui_radiobox_event_handler);

	/* set proper of control */
	radiobox->items = RT_NULL;
	radiobox->item_count = 0;
	radiobox->item_selection = -1;
	radiobox->orient = RTGUI_HORIZONTAL;
}

rtgui_type_t *rtgui_radiobox_type_get(void)
{
	static rtgui_type_t *radiobox_type = RT_NULL;

	if (!radiobox_type)
	{
		radiobox_type = rtgui_type_create("radiobox", RTGUI_WIDGET_TYPE,
			sizeof(rtgui_radiobox_t), RTGUI_CONSTRUCTOR(_rtgui_radiobox_constructor), RT_NULL);
	}

	return radiobox_type;
}

static void rtgui_radiobox_onmouse(struct rtgui_radiobox* radiobox, struct rtgui_event_mouse* event)
{
	RT_ASSERT(radiobox != RT_NULL);
	RT_ASSERT(event  != RT_NULL);

	if (event->button & RTGUI_MOUSE_BUTTON_DOWN &&
		event->button & RTGUI_MOUSE_BUTTON_LEFT)
	{
		if (radiobox->orient == RTGUI_VERTICAL)
		{
		}
		else
		{
		}

		rtgui_widget_focus(RTGUI_WIDGET(radiobox));
	}
}

void rtgui_theme_draw_radiobox(struct rtgui_radiobox* radiobox)
{
	struct rtgui_dc* dc;
	struct rtgui_rect rect, item_rect, radio_rect;
	rt_size_t item_height;

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(label));
	if (dc == RT_NULL) return;

	rtgui_widget_get_rect(RTGUI_WIDGET(label), &rect);
    rtgui_dc_fill_rect(dc, &rect);

    rtgui_dc_get_text_metrix(dc, "H", &item_rect);
    item_height = rtgui_rect_height(item_rect);
    radio_rect.x1 = 0; radio_rect.y1 = 0;
    radio_rect.x2 = radio_rect.x1 + item_height;
    radio_rect.y2 = radio_rect.y1 + item_height;

    /* draw box */
    rtgui_rect_inflat(&rect, -3);
    rtgui_dc_draw_round_rect(dc, &rect);
    if (radiobox->text != RT_NULL)
    {
        /* draw group text */
        rtgui_dc_get_text_metrix(dc, radiobox->text, &item_rect);
        rtgui_rect_moveto(&item_rect, rect.x1 + 5, rect.y1);
        rtgui_dc_fill_rect(dc, &item_rect);

        rtgui_dc_draw_text(dc, radiobox->text, &item_rect);
    }

    /* set the first text rect */
    item_rect = rect;
    item_rect.x1 += 5;
    item_rect.y1 += item_height;
    item_rect.y2 = item_rect.y1 + item_height;

    /* draw each radio button */
    for (index = 0; index < radiobox->item_count; index ++)
    {
        if (text_rect.y2 > rect.y2 - item_height) break;

        /* draw radio */
        rtgui_dc_draw_circyle(dc, );
        if (radiobox->item_selection == index)
        {
            rtgui_dc_draw_focus_rect(dc, );
            rtgui_dc_fill_circyle(dc, );
        }

        /* draw text */
        rtgui_dc_draw_text(dc, radiobox->items[index], text_rect);

        text_rect.y1 += item_height;
        text_rect.y2 += item_height;
    }

    /* end drawing */
	rtgui_dc_end_drawing(dc);
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
#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_key != RT_NULL) widget->on_key(widget, event);
		else
#endif
		{
            struct rtgui_event_kbd *e = (struct rtgui_event_kbd*)event;

            /* set focused */
            rtgui_widget_focus(RTGUI_WIDGET(radiobox));
            if (!(RTGUI_KBD_IS_UP(e))) return;

            if (e->key == RTGUIK_UP)
            {
                if (radiobox->item_selection > 0)
                    rtgui_radiobox_set_selection(radiobox->item_selection - 1);
            }
            else if (e->key == RTGUIK_DOWN)
            {
                if (radiobox->item_selection < radiobox->item_count - 1)
                    rtgui_radiobox_set_selection(radiobox->item_selection + 1);
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

struct rtgui_radiobox* rtgui_radiobox_create(int orient, char** radio_items, int number)
{
    struct rtgui_radiobox* radiobox;

    radiobox = (struct rtgui_radiobox*) rtgui_widget_create (RTGUI_RADIOBOX_TYPE);
    if (radiobox != RT_NULL)
    {
        radiobox->items = radio_items;
        radiobox->item_count = number;
        radiobox->item_selection = -1;

		/* set proper of control */
		rtgui_radiobox_set_orientation(radiobox, orient);
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
		rtgui_widget_set_miniheight(RTGUI_WIDGET(slider), RTGUI_RADIOBOX_DEFAULT_WIDTH);
	}
#endif
}

void rtgui_radiobox_set_selection(struct rtgui_radiobox* radiobox, int selection)
{
    if (selection >= 0 && selection < radiobox->item_count)
    {
    	radiobox->item_selection = selection;
    }

    /* update radiobox widget */
    rtgui_theme_draw_radiobox(radiobox);
}

int rtgui_radiobox_get_selection(struct rtgui_radiobox* radiobox)
{
    return radiobox->item_selection;
}
