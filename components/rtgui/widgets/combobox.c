#include <rtgui/dc.h>
#include <rtgui/widgets/combobox.h>

static rt_bool_t rtgui_combobox_pulldown_hide(struct rtgui_widget* widget, struct rtgui_event* event);

static void _rtgui_combobox_constructor(rtgui_combobox_t *box)
{
	rtgui_rect_t rect = {0, 0, RTGUI_COMBOBOX_WIDTH, RTGUI_COMBOBOX_HEIGHT};

	/* init widget and set event handler */
	rtgui_widget_set_event_handler(RTGUI_WIDGET(box), rtgui_combobox_event_handler);
	rtgui_widget_set_rect(RTGUI_WIDGET(box), &rect);

	RTGUI_WIDGET_TEXTALIGN(RTGUI_WIDGET(box)) = RTGUI_ALIGN_CENTER_VERTICAL;

	box->pd_pressed = RT_FALSE;
	box->current_item = 0;
	box->on_selected = RT_NULL;

	box->pd_win = rtgui_win_create(RT_NULL, "combo", &rect, RTGUI_WIN_STYLE_NO_TITLE);
	box->pd_win->user_data = (rt_uint32_t)box;
	rtgui_win_set_ondeactivate(RTGUI_WIN(box->pd_win), rtgui_combobox_pulldown_hide);
}

static void _rtgui_combobox_destructor(rtgui_combobox_t *box)
{
	/* destroy pull down window */
	rtgui_win_destroy(box->pd_win);

	/* reset box field */
	box->pd_win    = RT_NULL;
}

rtgui_type_t *rtgui_combobox_type_get(void)
{
	static rtgui_type_t *combobox_type = RT_NULL;

	if (!combobox_type)
	{
		combobox_type = rtgui_type_create("combobox", RTGUI_WIDGET_TYPE,
			sizeof(rtgui_combobox_t),
			RTGUI_CONSTRUCTOR(_rtgui_combobox_constructor),
			RTGUI_DESTRUCTOR(_rtgui_combobox_destructor));
	}

	return combobox_type;
}

rtgui_combobox_t *rtgui_combobox_create()
{
	rtgui_combobox_t* box;

	box = (rtgui_combobox_t*)rtgui_widget_create(RTGUI_COMBOBOX_TYPE);

	return box;
}

void rtgui_combobox_destroy(rtgui_combobox_t* box)
{
	rtgui_widget_destroy(RTGUI_WIDGET(box));
}

static void rtgui_combobox_ondraw(struct rtgui_combobox* box)
{
	/* draw button */
	struct rtgui_dc* dc;
	struct rtgui_rect rect;

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(box));
	if (dc == RT_NULL) return;

	/* get widget rect */
	rtgui_widget_get_rect(RTGUI_WIDGET(box), &rect);
	/* fill widget rect with background color */
	rtgui_dc_fill_rect(dc, &rect);
	rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_RAISE);

	/* draw current item */
	if (box->current_item < box->items_count)
	{
		rect.x1 += 5;
		rtgui_dc_draw_text(dc, box->items[box->current_item].name, &rect);
	}

	/* draw pull down button */
	rect.x1 = rect.x2 - RTGUI_COMBOBOX_BUTTON_WIDTH;
	rtgui_rect_inflate(&rect, -1);
	if (box->pd_pressed == RT_TRUE) rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_SUNKEN);
	else rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_RAISE);
	rtgui_dc_draw_arraw(dc, &rect, RTGUI_ARRAW_DOWN);

	/* end drawing */
	rtgui_dc_end_drawing(dc);
	return;
}

static rt_bool_t rtgui_combobox_onmouse_button(struct rtgui_combobox* box, struct rtgui_event_mouse* event)
{
	struct rtgui_rect rect;

	/* get widget rect */
	rect = RTGUI_WIDGET(box)->extent;

	/* move to the pull down button */
	rect.x1 = rect.x2 - RTGUI_COMBOBOX_BUTTON_WIDTH;
	if (rtgui_rect_contains_point(&rect, event->x, event->y) == RT_EOK)
	{
		/* handle mouse button on pull down button */
		if (event->button & RTGUI_MOUSE_BUTTON_LEFT &&
			event->button & RTGUI_MOUSE_BUTTON_DOWN)
		{
			box->pd_pressed = RT_TRUE;
			rtgui_widget_update(RTGUI_WIDGET(box));
		}
		else if (event->button & RTGUI_MOUSE_BUTTON_LEFT &&
			event->button & RTGUI_MOUSE_BUTTON_UP)
		{
			box->pd_pressed = RT_FALSE;
			rtgui_widget_update(RTGUI_WIDGET(box));

			/* pop pull down window */
			if (box->pd_win != RT_NULL)
			{
				struct rtgui_rect r;
				rtgui_box_t* pd_win_box;

				r.x1 = RTGUI_WIDGET(box)->extent.x1;
				r.y1 = RTGUI_WIDGET(box)->extent.y2 + 2;
				r.x2 = RTGUI_WIDGET(box)->extent.x2;
				r.y2 = r.y1 + box->pd_win_height;

				rtgui_win_set_rect(RTGUI_WIN(box->pd_win), &r);
				pd_win_box = (rtgui_box_t*) rtgui_container_get_first_child(RTGUI_CONTAINER(box->pd_win));
				if (pd_win_box != RT_NULL)
				{
					RTGUI_WIDGET(pd_win_box)->extent = RTGUI_WIDGET(box->pd_win)->extent;
					rtgui_box_layout(pd_win_box);
				}

				/* show combo box pull down window */
				rtgui_win_show(RTGUI_WIN(box->pd_win), RT_FALSE);
			}
		}

		return RT_TRUE;
	}

	return RT_FALSE;
}

rt_bool_t rtgui_combobox_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_combobox* box = (struct rtgui_combobox*)widget;

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_draw != RT_NULL) widget->on_draw(widget, event);
		else
#endif
			rtgui_combobox_ondraw(box);

		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		return rtgui_combobox_onmouse_button(box, (struct rtgui_event_mouse*)event);

	case RTGUI_EVENT_FOCUSED:
		{
			/* item focused */
			struct rtgui_item* item;
			struct rtgui_event_focused* focused;

			focused = (struct rtgui_event_focused*) event;

			item = (struct rtgui_item*) (focused->widget);
			if (item != RT_NULL)
			{
				if (box->pd_select != RT_NULL)
				{
					/* un-select old item */
					rtgui_item_selected(box->pd_select, RT_FALSE);
				}

				box->pd_select = item;
				if (box->on_selected != RT_NULL)
				{
					box->on_selected(RTGUI_WIDGET(box), RT_NULL);
				}

				/* hide pull down window */
				rtgui_win_hiden(RTGUI_WIN(box->pd_win));
				rtgui_combobox_ondraw(box);
			}
		}
		break;
	}

	return RT_FALSE;
}

static rt_bool_t rtgui_combobox_pulldown_hide(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_combobox* box;

	if (widget == RT_NULL) return RT_TRUE;

	box = (struct rtgui_combobox*) (((struct rtgui_win*)widget)->user_data);
	if (box == RT_NULL) return RT_TRUE;

	/* clear select item */
	if (box->pd_select != RT_NULL)
	{
		rtgui_item_selected(box->pd_select, RT_FALSE);
	}

	/* hide pull down window */
	rtgui_win_hiden(RTGUI_WIN(box->pd_win));

	/* clear pull down button state */
	box->pd_pressed = RT_FALSE;
	rtgui_widget_update(RTGUI_WIDGET(box));

	return RT_TRUE;
}

struct rtgui_item* rtgui_combox_get_select(struct rtgui_combobox* box)
{
	if ((box != RT_NULL) && (box->current_item < box->items_count))
	{
		return &(box->items[box->current_item]);
	}

	return RT_NULL;
}
