#include <rtgui/dc.h>
#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/notebook.h>
#include <rtgui/widgets/window.h>

#define RTGUI_NOTEBOOK_TAB_WIDTH     80

struct rtgui_notebook_tab
{
	struct rtgui_widget *widget;
	char *title;
};

static void _rtgui_notebook_get_bar_rect(struct rtgui_notebook *notebook, struct rtgui_rect* rect);
static void _rtgui_notebook_get_page_rect(struct rtgui_notebook *notebook, struct rtgui_rect* rect);

static void _rtgui_notebook_constructor(struct rtgui_notebook *notebook)
{
	notebook->flag    = 0;
	notebook->childs  = RT_NULL;
	notebook->count   = 0;
	notebook->current = 0;

	RTGUI_WIDGET(notebook)->gc.textalign = RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL;
	rtgui_object_set_event_handler(RTGUI_OBJECT(notebook), rtgui_notebook_event_handler);
}

static void _rtgui_notebook_destructor(struct rtgui_notebook *notebook)
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

DEFINE_CLASS_TYPE(notebook, "notebook",
	RTGUI_WIDGET_TYPE,
	_rtgui_notebook_constructor,
	_rtgui_notebook_destructor,
	sizeof(struct rtgui_notebook));

/* Draw tab bars of @param notebook. @param dc should be initialized and
 * finished outside this function. Don't pass @param notebook or @param dc as
 * RT_NULL, it should be checked outside.
 */
static void _rtgui_notebook_draw_bar(struct rtgui_notebook *notebook,
		struct rtgui_dc *dc)
{
	struct rtgui_rect rect;
	int index;

	RT_ASSERT((notebook != RT_NULL) && (dc != RT_NULL));

	if (notebook->flag & RTGUI_NOTEBOOK_NOTAB)
		return;

	_rtgui_notebook_get_bar_rect(notebook, &rect);
	rtgui_dc_fill_rect(dc, &rect);

	rect.x2 = rect.x1 + RTGUI_NOTEBOOK_TAB_WIDTH;
	/* draw tab bar */
	for (index = 0; index < notebook->count; index++)
	{
		if (notebook->current == index)
			rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_SUNKEN);
		else
			rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_BOX);

		rtgui_dc_draw_text(dc, notebook->childs[index].title, &rect);
		rect.x1 += RTGUI_NOTEBOOK_TAB_WIDTH;
		rect.x2 += RTGUI_NOTEBOOK_TAB_WIDTH;
	}

}

static void _rtgui_notebook_ondraw(struct rtgui_notebook *notebook)
{
	struct rtgui_dc* dc;

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(notebook));
	if (dc == RT_NULL) return;

	if (notebook->count == 0)
	{
		rtgui_rect_t rect;
		rtgui_widget_get_rect(RTGUI_WIDGET(notebook), &rect);
		rtgui_dc_fill_rect(dc, &rect);
	}
	else
	{
		if (notebook->current == RTGUI_NOT_FOUND)
			notebook->current = 0;

		_rtgui_notebook_draw_bar(notebook, dc);

		/* draw current tab */
		rtgui_widget_update(notebook->childs[notebook->current].widget);
	}
	rtgui_dc_end_drawing(dc);
}

static void _rtgui_notebook_onmouse(struct rtgui_notebook *notebook, struct rtgui_event_mouse* emouse)
{
	rtgui_rect_t rect;

	/* handle notebook bar */
	_rtgui_notebook_get_bar_rect(notebook, &rect);
	rtgui_widget_rect_to_device(RTGUI_WIDGET(notebook), &rect);
	if (rtgui_rect_contains_point(&rect, emouse->x, emouse->y) == RT_EOK)
	{
		int index;
		struct rtgui_dc* dc;

		index = (emouse->x - rect.x1) / RTGUI_NOTEBOOK_TAB_WIDTH;
		if (index < notebook->count && index != notebook->current)
		{
			/* update tab bar */
			dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(notebook));
			if (dc == RT_NULL) return;

			rtgui_notebook_set_current_by_index(notebook, index);

			_rtgui_notebook_draw_bar(notebook, dc);

			rtgui_dc_end_drawing(dc);
		}
	}
	else
	{
		/* handle on page */
		if (RTGUI_OBJECT(notebook->childs[notebook->current].widget)->event_handler != RT_NULL)
			RTGUI_OBJECT(notebook->childs[notebook->current].widget)->event_handler(
					RTGUI_OBJECT(notebook->childs[notebook->current].widget),
					&(emouse->parent));
	}
}

static void _rtgui_notebook_get_page_rect(struct rtgui_notebook *notebook, struct rtgui_rect* rect)
{
	RT_ASSERT(notebook != RT_NULL);
	RT_ASSERT(rect != RT_NULL);

	rtgui_widget_get_rect(RTGUI_WIDGET(notebook), rect);

	if (notebook->flag == RTGUI_NOTEBOOK_NOTAB)
		return;
	else if (notebook->flag == RTGUI_NOTEBOOK_TOP)
		rect->y1 = rect->y1 + 25;
	else if (notebook->flag == RTGUI_NOTEBOOK_BOTTOM)
		rect->y2 = rect->y2 - 25;
}

static void _rtgui_notebook_get_bar_rect(struct rtgui_notebook *notebook, struct rtgui_rect* rect)
{
	RT_ASSERT(notebook != RT_NULL);
	RT_ASSERT(rect != RT_NULL);

	rtgui_widget_get_rect(RTGUI_WIDGET(notebook), rect);
	if (notebook->flag == RTGUI_NOTEBOOK_NOTAB)
	{
		rect->x1 = rect->y1 = rect->x2 = rect->y2 = 0;
	}
	else if (notebook->flag == RTGUI_NOTEBOOK_TOP)
		rect->y2 = rect->y1 + 25;
	else if (notebook->flag == RTGUI_NOTEBOOK_BOTTOM)
		rect->y1 = rect->y2 - 25;
}

struct rtgui_notebook* rtgui_notebook_create(const rtgui_rect_t* rect, rt_uint8_t style)
{
    struct rtgui_notebook* notebook;

    notebook = (struct rtgui_notebook*) rtgui_widget_create(RTGUI_NOTEBOOK_TYPE);
    if (notebook != RT_NULL)
    {
		notebook->flag = style;
		rtgui_widget_set_rect(RTGUI_WIDGET(notebook), rect);
    }

    return notebook;
}

void rtgui_notebook_destroy(struct rtgui_notebook* notebook)
{
	rtgui_widget_destroy(RTGUI_WIDGET(notebook));
}

void rtgui_notebook_add(struct rtgui_notebook* notebook, const char* label, struct rtgui_widget* child)
{
	rtgui_rect_t rect;
	RT_ASSERT(notebook != RT_NULL);

	notebook->count += 1;
	notebook->childs = (struct rtgui_notebook_tab*)
						rtgui_realloc(notebook->childs,
									  sizeof(struct rtgui_notebook_tab) * notebook->count);

	notebook->childs[notebook->count - 1].title = rt_strdup(label);
	notebook->childs[notebook->count - 1].widget = child;

	/* set parent */
	rtgui_widget_set_parent(child, RTGUI_WIDGET(notebook));

	_rtgui_notebook_get_page_rect(notebook, &rect);
	rtgui_widget_rect_to_device(RTGUI_WIDGET(notebook), &rect);
	rtgui_widget_set_rect(child, &rect);

    if (notebook->count - 1 != notebook->current)
        rtgui_widget_hide(child);

	if (RTGUI_WIDGET(notebook)->toplevel != RT_NULL &&
		RTGUI_IS_TOPLEVEL(RTGUI_WIDGET(notebook)->toplevel))
	{
		struct rtgui_event_update_toplvl eup;
		RTGUI_EVENT_UPDATE_TOPLVL_INIT(&eup);
		eup.toplvl = RTGUI_WIDGET(notebook)->toplevel;
		if (RTGUI_OBJECT(child)->event_handler)
			RTGUI_OBJECT(child)->event_handler(RTGUI_OBJECT(child), (struct rtgui_event*)&eup);
	}
}

void rtgui_notebook_remove(struct rtgui_notebook* notebook, rt_uint16_t index)
{
	struct rtgui_notebook_tab tab;
    rt_bool_t need_update = RT_FALSE;

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
            if (notebook->current == index)
                need_update = RT_TRUE;

			tab = notebook->childs[index];
			for (;index < notebook->count - 1; index++)
			{
				notebook->childs[index] = notebook->childs[index + 1];
			}

			notebook->count -= 1;
			notebook->childs = (struct rtgui_notebook_tab*) rtgui_realloc(notebook->childs, 
				sizeof(struct rtgui_notebook_tab) * notebook->count);
		}

		rtgui_free(tab.title);

		if (need_update)
		{
			if (notebook->current > notebook->count - 1)
				notebook->current = notebook->count - 1;

            rtgui_widget_hide(tab.widget);
            rtgui_widget_show(notebook->childs[notebook->current].widget);
			rtgui_widget_update(RTGUI_WIDGET(notebook));
            rtgui_widget_set_parent(tab.widget, RT_NULL);
		}
	}
}

int rtgui_notebook_get_count(struct rtgui_notebook* notebook)
{
	RT_ASSERT(notebook != RT_NULL);
	return notebook->count;
}

struct rtgui_widget* rtgui_notebook_get_current(struct rtgui_notebook* notebook)
{
	RT_ASSERT(notebook != RT_NULL);
	if (notebook->current != RTGUI_NOT_FOUND)
		return notebook->childs[notebook->current].widget;

	return RT_NULL;
}

rt_int16_t rtgui_notebook_get_current_index(struct rtgui_notebook* notebook)
{
	RT_ASSERT(notebook != RT_NULL);
	return notebook->current;
}

void rtgui_notebook_set_current(struct rtgui_notebook* notebook, struct rtgui_widget* widget)
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

void rtgui_notebook_set_current_by_index(struct rtgui_notebook* notebook, rt_uint16_t index)
{
	RT_ASSERT(notebook != RT_NULL);

	if ((index < notebook->count) && (notebook->current != index))
	{
		struct rtgui_widget *widget;

		if (notebook->current != RTGUI_NOT_FOUND)
			rtgui_widget_hide(notebook->childs[notebook->current].widget);

		notebook->current = index;
		widget = notebook->childs[notebook->current].widget;
		rtgui_widget_show(widget);
		rtgui_widget_update(widget);
		rtgui_widget_focus(widget);
	}
}

struct rtgui_widget* rtgui_notebook_get_widget_at(struct rtgui_notebook* notebook, rt_uint16_t index)
{
	RT_ASSERT(notebook != RT_NULL);
	if (index < notebook->count)
		return notebook->childs[index].widget;

	return RT_NULL;
}

static rt_bool_t _rtgui_notebook_current_widget_handle(struct rtgui_notebook *notebook,
		                                               struct rtgui_event *event)
{
	struct rtgui_widget *widget = rtgui_notebook_get_current(notebook);
	if (widget && widget != RTGUI_WIDGET(notebook))
		return RTGUI_OBJECT(widget)->event_handler(RTGUI_OBJECT(widget), event);
	else
		return RT_FALSE;
}

static void _rtgui_notebook_all_widget_handle(struct rtgui_notebook *notebook,
		                                           struct rtgui_event *event)
{
	struct rtgui_object *object;
	int i;
	for (i = 0; i < notebook->count; i++)
	{
		object = RTGUI_OBJECT(notebook->childs[i].widget);
		if (object->event_handler)
			object->event_handler(object, event);
	}
}

rt_bool_t rtgui_notebook_event_handler(struct rtgui_object* object, struct rtgui_event* event)
{
	struct rtgui_notebook* notebook;

	RT_ASSERT(object != RT_NULL);
	RT_ASSERT(event != RT_NULL);

	notebook = RTGUI_NOTEBOOK(object);

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		_rtgui_notebook_ondraw(notebook);
		break;
	case RTGUI_EVENT_MOUSE_BUTTON:
		_rtgui_notebook_onmouse(notebook, (struct rtgui_event_mouse*)event);
		break;
	case RTGUI_EVENT_SHOW:
		/* show myself */
		rtgui_widget_onshow(object, event);
		/* show the tab widget */
		return _rtgui_notebook_current_widget_handle(notebook, event);
	case RTGUI_EVENT_HIDE:
		/* hide myself */
		rtgui_widget_onhide(object, event);
		/* hide the tab widget */
		return _rtgui_notebook_current_widget_handle(notebook, event);
	case RTGUI_EVENT_KBD:
		return _rtgui_notebook_current_widget_handle(notebook, event);
	case RTGUI_EVENT_UPDATE_TOPLVL:
		/* update myself */
		rtgui_widget_onupdate_toplvl(object, event);
		/* update all the widgets in myself */
		_rtgui_notebook_all_widget_handle(notebook, event);
		return RT_FALSE;
	default:
		/* use parent event handler */
		return rtgui_widget_event_handler(object, event);
	}

	return RT_FALSE;
}
