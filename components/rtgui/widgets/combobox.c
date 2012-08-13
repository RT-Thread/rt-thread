#include <rtgui/dc.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/combobox.h>

static rt_bool_t rtgui_combobox_pulldown_hide(struct rtgui_object* object, struct rtgui_event* event);
const static rt_uint8_t down_arrow[]  = {0xff, 0x7e, 0x3c, 0x18};

static void _rtgui_combobox_constructor(rtgui_combobox_t *box)
{
	rtgui_rect_t rect = {0, 0, RTGUI_COMBOBOX_WIDTH, RTGUI_COMBOBOX_HEIGHT};

	/* init widget and set event handler */
	rtgui_object_set_event_handler(RTGUI_OBJECT(box), rtgui_combobox_event_handler);
	rtgui_widget_set_rect(RTGUI_WIDGET(box), &rect);

	RTGUI_WIDGET_TEXTALIGN(box) = RTGUI_ALIGN_CENTER_VERTICAL;

	box->pd_pressed = RT_FALSE;
	box->current_item = 0;
	box->on_selected = RT_NULL;
	box->pd_win    = RT_NULL;
}

static void _rtgui_combobox_destructor(rtgui_combobox_t *box)
{
	/* destroy pull down window */
	rtgui_win_destroy(box->pd_win);

	/* reset box field */
	box->pd_win    = RT_NULL;
}

rt_bool_t rtgui_combobox_pdwin_onitem(struct rtgui_object* object, struct rtgui_event* event)
{
	struct rtgui_widget *widget;
	rtgui_win_t* pd_win;
	rtgui_combobox_t* combo;
	rtgui_listbox_t* list;

	RT_ASSERT(object != RT_NULL);

	widget = RTGUI_WIDGET(object);
	list = RTGUI_LISTBOX(widget);
	pd_win = RTGUI_WIN(rtgui_widget_get_toplevel(widget));
	combo = RTGUI_COMBOBOX(pd_win->user_data);
	combo->current_item = list->current_item;

	if (combo->on_selected != RT_NULL)
		combo->on_selected(RTGUI_OBJECT(combo), RT_NULL);

	rtgui_win_hiden(pd_win);
	rtgui_widget_update(RTGUI_WIDGET(combo));

	return RT_FALSE;
}

rt_bool_t rtgui_combobox_pdwin_ondeactive(struct rtgui_object* object, struct rtgui_event* event)
{
	rtgui_win_hiden(RTGUI_WIN(object));
	return RT_TRUE;
}

DEFINE_CLASS_TYPE(combobox, "combobox", 
	RTGUI_WIDGET_TYPE,
	_rtgui_combobox_constructor,
	_rtgui_combobox_destructor,
	sizeof(struct rtgui_combobox));

rtgui_combobox_t *rtgui_combobox_create(struct rtgui_listbox_item* items, rt_uint16_t count, struct rtgui_rect* rect)
{
	rtgui_combobox_t *box;

	box = (rtgui_combobox_t*)rtgui_widget_create(RTGUI_COMBOBOX_TYPE);
	box->items_count = count;
	box->items = items;
	rtgui_widget_set_rect(RTGUI_WIDGET(box), rect);
	
	box->pd_win = RT_NULL;

	return box;
}

void rtgui_combobox_destroy(rtgui_combobox_t* box)
{
	rtgui_widget_destroy(RTGUI_WIDGET(box));
}

static void rtgui_combobox_ondraw(struct rtgui_combobox* box)
{
	/* draw button */
	rtgui_color_t bc;
	struct rtgui_dc* dc;
	struct rtgui_rect rect, r;

	/* begin drawing */
	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(box));
	if (dc == RT_NULL) return;

	bc = RTGUI_WIDGET_BACKGROUND(box);

	/* get widget rect */
	rtgui_widget_get_rect(RTGUI_WIDGET(box), &rect);
	RTGUI_WIDGET_BACKGROUND(box) = white;

	/* fill widget rect with background color */
	rtgui_dc_fill_rect(dc, &rect);
	rtgui_dc_draw_rect(dc, &rect);

	/* draw current item */
	if (box->current_item < box->items_count)
	{
		rect.x1 += 5;
		rtgui_dc_draw_text(dc, box->items[box->current_item].name, &rect);
	}

	/* restore background color */
	RTGUI_WIDGET_BACKGROUND(box) = bc;

	/* draw pull down button */
	rect.x1 = rect.x2 - RTGUI_COMBOBOX_BUTTON_WIDTH;
	rtgui_rect_inflate(&rect, -1);
	rtgui_dc_fill_rect(dc, &rect);
	if (box->pd_pressed == RT_TRUE) rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_SUNKEN);
	else rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_RAISE);

	r.x1 = 0; r.y1 = 0; r.x2 = 8; r.y2 = 4;
	rtgui_rect_moveto_align(&rect, &r, RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL);
	rtgui_dc_draw_byte(dc, r.x1, r.y1, 4, down_arrow);

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
			if (box->pd_win == RT_NULL)
			{
				rtgui_listbox_t  *list;

				/* create pull down window */
				rect = RTGUI_WIDGET(box)->extent;
				rect.y1 = rect.y2;
				rect.y2 = rect.y1 + 5 * (2 + rtgui_theme_get_selected_height());
				box->pd_win = rtgui_win_create(RT_NULL, "combo", &rect, RTGUI_WIN_STYLE_NO_TITLE);
				rtgui_win_set_ondeactivate(RTGUI_WIN(box->pd_win), rtgui_combobox_pulldown_hide);
				/* set user data to parent combobox */
				box->pd_win->user_data = (rt_uint32_t)box;

				/* create list box */
				rtgui_rect_inflate(&rect, -1);
				list = rtgui_listbox_create(box->items, box->items_count, &rect);
				rtgui_container_add_child(RTGUI_CONTAINER(box->pd_win), RTGUI_WIDGET(list));
				rtgui_widget_focus(RTGUI_WIDGET(list));

				rtgui_listbox_set_onitem(list, rtgui_combobox_pdwin_onitem);
				rtgui_win_set_ondeactivate(box->pd_win, rtgui_combobox_pdwin_ondeactive);
			}

			/* show combo box pull down window */
			rtgui_win_show(RTGUI_WIN(box->pd_win), RT_FALSE);
		}

		return RT_TRUE;
	}

	return RT_FALSE;
}

rt_bool_t rtgui_combobox_event_handler(struct rtgui_object* object, struct rtgui_event* event)
{
	struct rtgui_combobox *box;
	RTGUI_WIDGET_EVENT_HANDLER_PREPARE

	box = RTGUI_COMBOBOX(object);

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
#ifndef RTGUI_USING_SMALL_SIZE
		if (widget->on_draw != RT_NULL)
			widget->on_draw(RTGUI_OBJECT(widget), event);
		else
#endif
			rtgui_combobox_ondraw(box);

		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		return rtgui_combobox_onmouse_button(box, (struct rtgui_event_mouse*)event);

	case RTGUI_EVENT_FOCUSED:
		{
			/* item focused */
			struct rtgui_event_focused* focused;

			focused = (struct rtgui_event_focused*) event;

			if (focused->widget != RT_NULL)
			{
				/* hide pull down window */
				rtgui_win_hiden(RTGUI_WIN(box->pd_win));
				rtgui_combobox_ondraw(box);
			}
		}
		break;
	default:
		return rtgui_widget_event_handler(object, event);
	}

	return RT_FALSE;
}

static rt_bool_t rtgui_combobox_pulldown_hide(struct rtgui_object* object, struct rtgui_event* event)
{
	struct rtgui_widget *widget;
	struct rtgui_combobox *box;

	RT_ASSERT(object != RT_NULL);
	RT_ASSERT(event != RT_NULL);

	widget = RTGUI_WIDGET(object);
	box = RTGUI_COMBOBOX(object);

	if (widget == RT_NULL) return RT_TRUE;

	box = (struct rtgui_combobox*) (((struct rtgui_win*)widget)->user_data);
	if (box == RT_NULL) return RT_TRUE;

	/* hide pull down window */
	rtgui_win_hiden(RTGUI_WIN(box->pd_win));

	/* clear pull down button state */
	box->pd_pressed = RT_FALSE;
	rtgui_widget_update(RTGUI_WIDGET(box));

	return RT_TRUE;
}

struct rtgui_listbox_item* rtgui_combox_get_select(struct rtgui_combobox* box)
{
	if ((box != RT_NULL) && (box->current_item < box->items_count))
	{
		return &(box->items[box->current_item]);
	}

	return RT_NULL;
}

void rtgui_combobox_set_onselected(struct rtgui_combobox* box, rtgui_event_handler_ptr func)
{
	box->on_selected = func;
}
