#include <rtgui/rtgui.h>
#include <rtgui/widgets/view.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/workbench.h>

static rtgui_view_t* demo_view_list[32];
static rt_uint32_t demo_view_current = 0;
static rt_uint32_t demo_view_number = 0;

static void demo_view_next(struct rtgui_widget* widget, rtgui_event_t *event)
{
	RT_ASSERT(widget != RT_NULL);

	if (demo_view_current + 1< demo_view_number)
	{
		demo_view_current ++;
		rtgui_view_show(demo_view_list[demo_view_current], RT_FALSE);
	}
}

static void demo_view_prev(struct rtgui_widget* widget, rtgui_event_t *event)
{
	RT_ASSERT(widget != RT_NULL);

	if (demo_view_current != 0)
	{
		demo_view_current --;
		rtgui_view_show(demo_view_list[demo_view_current], RT_FALSE);
	}
}

rtgui_view_t* demo_view(rtgui_workbench_t* workbench)
{
    char view_name[32];
    struct rtgui_view* view;

    rt_sprintf(view_name, "view %d", demo_view_number + 1);

    view = rtgui_view_create(view_name);

	/* add to the list */
	demo_view_list[demo_view_number] = view;
	demo_view_number ++;

	rtgui_workbench_add_view(workbench, view);

    /* add next and prev button */
    {
    	struct rtgui_rect rect;
        struct rtgui_button *next_btn, *prev_btn;

		/* get view's rect */
		rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);
		rect.x2 -= 5; rect.y2 -= 5;
		rect.x1 = rect.x2 - 50; rect.y1 = rect.y2 - 20;

		/* create next button */
        next_btn = rtgui_button_create("Next");
		rtgui_button_set_onbutton(next_btn, demo_view_next);
		rtgui_widget_set_rect(RTGUI_WIDGET(next_btn), &rect);
		rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(next_btn));

		/* get view's rect */
		rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);
		rect.x1 += 5; rect.y2 -= 5;
		rect.x2 = rect.x1 + 50; rect.y1 = rect.y2 - 20;

		/* create previous button */
		prev_btn = rtgui_button_create("Prev");
		rtgui_button_set_onbutton(prev_btn, demo_view_prev);
		rtgui_widget_set_rect(RTGUI_WIDGET(prev_btn), &rect);
		rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(prev_btn));
    }

	return view;
}

void demo_view_get_rect(rtgui_view_t* view, rtgui_rect_t *rect)
{
	RT_ASSERT(view != RT_NULL);
	RT_ASSERT(rect != RT_NULL);

	rtgui_widget_get_rect(RTGUI_WIDGET(view), rect);
	/* remove the command button rect */
	rect->y2 -= 25;
}

#ifndef RTGUI_USING_SMALL_SIZE
rtgui_box_t* demo_view_create_box(rtgui_view_t* view, int orient)
{
	rtgui_rect_t rect;
	rtgui_box_t* box;

	/* get rect of view */
	rtgui_widget_get_rect(RTGUI_WIDGET(view), &rect);
	rect.y2 -= 25;

	box = rtgui_box_create(orient, &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(box));

	return box;
}
#endif

void demo_view_show()
{
	if (demo_view_number != 0)
	{
		rtgui_view_show(demo_view_list[demo_view_current], RT_FALSE);		
	}
}

