#include <rtgui/dc.h>
#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/notebook.h>

static void _rtgui_notebook_get_bar_rect(rtgui_notebook_t *notebook, struct rtgui_rect* rect);
static void _rtgui_notebook_get_page_rect(rtgui_notebook_t *notebook, struct rtgui_rect* rect);

static void _rtgui_notebook_constructor(rtgui_notebook_t *notebook)
{
	notebook->flag = 0;
	notebook->childs = RT_NULL;
	notebook->count = 0;
	notebook->current = RTGUI_NOT_FOUND;

	RTGUI_WIDGET(notebook)->gc.textalign = RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL;
	rtgui_widget_set_event_handler(RTGUI_WIDGET(notebook), rtgui_notebook_event_handler);
}

static void _rtgui_notebook_destructor(rtgui_notebook_t *notebook)
{
	int index;

	if (notebook->childs != RT_NULL)
	{
		for (index = 0; index < notebook->count; index ++)
		{
			rtgui_widget_destroy(notebook->childs[index].widget);
			rt_free(notebook->childs[index].title);
		}

		rtgui_free(notebook->childs);
	}
}

static void _rtgui_notebook_ondraw(rtgui_notebook_t *notebook)
{
	struct rtgui_dc* dc;
	rtgui_rect_t rect;
	int index;

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(notebook));
	if (dc == RT_NULL) return;

	rtgui_widget_get_rect(RTGUI_WIDGET(notebook), &rect);

	if (notebook->count == 0)
	{
		rtgui_dc_fill_rect(dc, &rect);
	}
	else
	{
		if (notebook->current == RTGUI_NOT_FOUND)
			notebook->current = 0;

		_rtgui_notebook_get_bar_rect(notebook, &rect);
		rtgui_dc_fill_rect(dc, &rect);
		rect.x2 = rect.x1 + 80;
		/* draw tab bar */
		for (index = 0; index < notebook->count; index ++)
		{
			if (notebook->current == index)
				rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_SUNKEN);
			else
				rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_BOX);
			rtgui_dc_draw_text(dc, notebook->childs[index].title, &rect);
			rect.x1 += 80; rect.x2 += 80;
		}

		/* draw current tab */
		rtgui_widget_update(notebook->childs[notebook->current].widget);
	}
	rtgui_dc_end_drawing(dc);
}

static void _rtgui_notebook_onmouse(rtgui_notebook_t *notebook, struct rtgui_event_mouse* emouse)
{
	rtgui_rect_t rect;
	
	/* handle notebook bar */
	_rtgui_notebook_get_bar_rect(notebook, &rect);
	rtgui_widget_rect_to_device(RTGUI_WIDGET(notebook), &rect);
	if (rtgui_rect_contains_point(&rect, emouse->x, emouse->y) == RT_EOK)
	{
		int index;
		struct rtgui_dc* dc;

		index = (emouse->x - rect.x1) / 80;
		if (index < notebook->count)
		{
			/* update tab bar */
			dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(notebook));
			if (dc == RT_NULL) return;

			rtgui_notebook_set_current_by_index(notebook, index);

			_rtgui_notebook_get_bar_rect(notebook, &rect);
			rtgui_dc_fill_rect(dc, &rect);
			rect.x2 = rect.x1 + 80;
			/* draw tab bar */
			for (index = 0; index < notebook->count; index ++)
			{
				if (notebook->current == index)
					rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_SUNKEN);
				else
					rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_BOX);
				rtgui_dc_draw_text(dc, notebook->childs[index].title, &rect);
				rect.x1 += 80; rect.x2 += 80;
			}

			rtgui_dc_end_drawing(dc);

			return;
		}
	}

	/* handle on page */
	if (notebook->childs[notebook->current].widget->event_handler != RT_NULL)
		notebook->childs[notebook->current].widget->event_handler(notebook->childs[notebook->current].widget, 
			&(emouse->parent));
}

static void _rtgui_notebook_get_page_rect(rtgui_notebook_t *notebook, struct rtgui_rect* rect)
{
	RT_ASSERT(notebook != RT_NULL);
	RT_ASSERT(rect != RT_NULL);

	rtgui_widget_get_rect(RTGUI_WIDGET(notebook), rect);

	if (notebook->flag == RTGUI_NOTEBOOK_NOTAB) return;
	else if (notebook->flag == RTGUI_NOTEBOOK_TOP)
		rect->y1 = rect->y1 + 25;
	else if (notebook->flag == RTGUI_NOTEBOOK_BOTTOM)
		rect->y2 = rect->y2 - 25;
}

static void _rtgui_notebook_get_bar_rect(rtgui_notebook_t *notebook, struct rtgui_rect* rect)
{
	RT_ASSERT(notebook != RT_NULL);
	RT_ASSERT(rect != RT_NULL);

	rtgui_widget_get_rect(RTGUI_WIDGET(notebook), rect);
	if (notebook->flag == RTGUI_NOTEBOOK_NOTAB) return;
	else if (notebook->flag == RTGUI_NOTEBOOK_TOP)
		rect->y2 = rect->y1 + 25;
	else if (notebook->flag == RTGUI_NOTEBOOK_BOTTOM)
		rect->y1 = rect->y2 - 25;
}

DEFINE_CLASS_TYPE(notebook, "notebook", 
	RTGUI_CONTAINER_TYPE,
	_rtgui_notebook_constructor,
	_rtgui_notebook_destructor,
	sizeof(struct rtgui_notebook));

rtgui_notebook_tab_t *tabs;
struct rtgui_notebook *_notebook;
rtgui_notebook_t* rtgui_notebook_create(const rtgui_rect_t* rect, rt_uint8_t style)
{
    struct rtgui_notebook* notebook;

    notebook = (struct rtgui_notebook*) rtgui_widget_create (RTGUI_NOTEBOOK_TYPE);
    if (notebook != RT_NULL)
    {
		notebook->flag = style;
		rtgui_widget_set_rect(RTGUI_WIDGET(notebook), rect);
    }

	_notebook = notebook;
    return notebook;
}

void rtgui_notebook_destroy(rtgui_notebook_t* notebook)
{
	rtgui_widget_destroy(RTGUI_WIDGET(notebook));
}

void rtgui_notebook_add(rtgui_notebook_t* notebook, const char* label, rtgui_widget_t* child)
{
	rtgui_rect_t rect;
	RT_ASSERT(notebook != RT_NULL);

	notebook->count += 1;
	notebook->childs = (struct rtgui_notebook_tab*) rtgui_realloc(notebook->childs, 
		sizeof(struct rtgui_notebook_tab) * notebook->count);

	notebook->childs[notebook->count - 1].title = rt_strdup(label);
	notebook->childs[notebook->count - 1].widget = child;

	tabs = notebook->childs;

	/* set parent */
	rtgui_widget_set_parent(child, RTGUI_WIDGET(notebook));

	_rtgui_notebook_get_page_rect(notebook, &rect);
	rtgui_widget_rect_to_device(RTGUI_WIDGET(notebook), &rect);
	rtgui_widget_set_rect(child, &rect);
}

void rtgui_notebook_remove(rtgui_notebook_t* notebook, rt_uint16_t index)
{
	struct rtgui_notebook_tab tab;
	RT_ASSERT(notebook != RT_NULL);

	if (index < notebook->count)
	{
		if (notebook->count == 1)
		{
			tab = notebook->childs[0];
			rtgui_free(notebook->childs);
			notebook->childs = RT_NULL;
			notebook->count = 0;
		}
		else
		{
			tab = notebook->childs[index];
			for (;index < notebook->count - 1; index ++)
			{
				notebook->childs[index] = notebook->childs[index + 1];
			}

			notebook->count -= 1;
			notebook->childs = (struct rtgui_notebook_tab*) rtgui_realloc(notebook->childs, 
				sizeof(struct rtgui_notebook_tab) * notebook->count);
		}

		rtgui_widget_destroy(tab.widget);
		rtgui_free(tab.title);

		if (notebook->current == index)
		{
			/* update tab */
			if (notebook->current > notebook->count - 1)
				notebook->current = notebook->count - 1;
			rtgui_widget_update(RTGUI_WIDGET(notebook));
		}
	}
}

int rtgui_notebook_get_count(rtgui_notebook_t* notebook)
{
	return notebook->count;
}

rtgui_widget_t* rtgui_notebook_get_current(rtgui_notebook_t* notebook)
{
	RT_ASSERT(notebook != RT_NULL);
	if (notebook->current != RTGUI_NOT_FOUND)
		return notebook->childs[notebook->current].widget;

	return RT_NULL;
}
void rtgui_notebook_set_current(rtgui_notebook_t* notebook, rtgui_widget_t* widget)
{
	rt_int16_t index;

	RT_ASSERT(notebook != RT_NULL);

	for (index = 0; index < notebook->count; index ++)
	{
		if (widget == notebook->childs[index].widget)
		{
			rtgui_notebook_set_current_by_index(notebook, index);
			return;
		}
	}
}

void rtgui_notebook_set_current_by_index(rtgui_notebook_t* notebook, rt_uint16_t index)
{
	RT_ASSERT(notebook != RT_NULL);

	if ((index < notebook->count) && (notebook->current != index))
	{
		if (notebook->current != RTGUI_NOT_FOUND)
			rtgui_widget_hide(notebook->childs[notebook->current].widget);

		notebook->current = index;
		rtgui_widget_show(notebook->childs[notebook->current].widget);
		rtgui_widget_update(notebook->childs[notebook->current].widget);
	}
}

rtgui_widget_t* rtgui_notebook_get_index(rtgui_notebook_t* notebook, rt_uint16_t index)
{
	RT_ASSERT(notebook != RT_NULL);
	if (index < notebook->count)
		return notebook->childs[index].widget;

	return RT_NULL;
}

rt_bool_t rtgui_notebook_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	struct rtgui_notebook* notebook;

	notebook = RTGUI_NOTEBOOK(widget);
	if (event->type == RTGUI_EVENT_PAINT)
	{
		_rtgui_notebook_ondraw(notebook);
	}
	else if (event->type == RTGUI_EVENT_MOUSE_BUTTON)
	{
		_rtgui_notebook_onmouse(notebook, (struct rtgui_event_mouse*)event);
	}
	else if (event->type == RTGUI_EVENT_KBD)
	{
		if (notebook->current != RTGUI_NOT_FOUND)
		{
			if (notebook->childs[notebook->current].widget->event_handler != RT_NULL)
				return notebook->childs[notebook->current].widget->event_handler(notebook->childs[notebook->current].widget,
					event);
		}
	}
	else
	{
		/* use parent event handler */
		return rtgui_widget_event_handler(widget, event);
	}

	return RT_FALSE;
}
