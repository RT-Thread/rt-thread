#include <rtgui/dc.h>
#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/notebook.h>

static void _rtgui_notebook_constructor(rtgui_notebook_t *notebook)
{
	notebook->childs = RT_NULL;
	notebook->count = 0;
	notebook->current = RTGUI_NOT_FOUND;
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
		/* draw tab bar */
		for (index = 0; index < notebook->count; index ++)
		{
		}

		/* draw current tab */
		rtgui_widget_update(notebook->childs[notebook->current].widget);
	}
	rtgui_dc_end_drawing(dc);
}

rtgui_type_t *rtgui_notebook_type_get(void)
{
	static rtgui_type_t *noteboot_type = RT_NULL;

	if (!noteboot_type)
	{
		noteboot_type = rtgui_type_create("notebook", RTGUI_WIDGET_TYPE,
			sizeof(rtgui_notebook_t), 
			RTGUI_CONSTRUCTOR(_rtgui_notebook_constructor), 
			RTGUI_DESTRUCTOR(_rtgui_notebook_destructor));
	}

	return noteboot_type;
}

rtgui_notebook_t* rtgui_notebook_create(const rtgui_rect_t* rect)
{
    struct rtgui_notebook* notebook;

    notebook = (struct rtgui_notebook*) rtgui_widget_create (RTGUI_NOTEBOOK_TYPE);
    if (notebook != RT_NULL)
    {
		rtgui_widget_set_rect(RTGUI_WIDGET(notebook), rect);
    }

    return notebook;
}

void rtgui_notebook_destroy(rtgui_notebook_t* notebook)
{
	rtgui_widget_destroy(RTGUI_WIDGET(notebook));
}

void rtgui_notebook_add(rtgui_notebook_t* notebook, const char* label, rtgui_widget_t* child)
{
	RT_ASSERT(notebook != RT_NULL);

	notebook->count += 1;
	notebook->childs = (struct rtgui_notebook_tab*) rtgui_realloc(notebook->childs, 
		sizeof(struct rtgui_notebook_tab) * notebook->count);

	notebook->childs[notebook->count - 1].title = rt_strdup(label);
	notebook->childs[notebook->count - 1].widget = child;
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
	if (event->type == RTGUI_EVENT_PAINT)
	{
		_rtgui_notebook_ondraw(RTGUI_NOTEBOOK(widget));
	}
	else
	{
		/* use parent event handler */
		return rtgui_widget_event_handler(widget, event);
	}

	return RT_FALSE;
}
