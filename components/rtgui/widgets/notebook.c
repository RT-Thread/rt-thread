#include <rtgui/rtgui.h>
#include <rtgui/widgets/notebook.h>

rtgui_type_t *rtgui_notebook_type_get(void)
{
}

rtgui_notebook_t* rtgui_notebook_create(const rtgui_rect_t* rect)
{
}

void rtgui_notebook_destroy(rtgui_notebook_t* notebook)
{
}

void rtgui_notebook_add(rtgui_notebook_t* notebook, const char* label, rtgui_widget_t* child)
{
}

int rtgui_notebook_get_count(rtgui_notebootk_t* notebook)
{
	return notebook->count;
}

rtgui_widget_t* rtgui_notebook_get_current(rtgui_notebook_t* notebook)
{
	RT_ASSERT(notebook != RT_NULL);
	if (notebook->current != RTGUI_NOT_FOUND)
		return &notebook->childs[notebook->current];

	return RT_NULL;
}
void rtgui_notebook_set_current(rtgui_notebook_t* notebook, rtgui_widget_t* widget)
{
	rt_int16_t index;

	RT_ASSERT(notebook != RT_NULL);

	for (index = 0; index < notebook->count; index ++)
	{
		if (widget == &notebook->childs[index])
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
			rtgui_widget_hide(&notebook->childs[notebook->current]);
		
		notebook->current = index;
		rtgui_widget_show(&notebook->childs[notebook->current]);
		rtgui_widget_update(&notebook->childs[notebook->current]);
	}
}

rtgui_widget_t* rtgui_notebook_get_index(rtgui_notebook_t* notebook, rt_uint16_t index)
{
	RT_ASSERT(notebook != RT_NULL);
	if (index < notebook->count)
		return &notebook->childs[index];

	return RT_NULL;
}

rt_bool_t rtgui_notebook_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	return RT_FALSE;
}
