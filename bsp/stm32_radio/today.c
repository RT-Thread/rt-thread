#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>

#include <rtgui/widgets/view.h>
#include <rtgui/widgets/workbench.h>

static rtgui_image_t *background = RT_NULL;
static rt_bool_t view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		struct rtgui_rect rect;

		dc = rtgui_dc_begin_drawing(widget);
		if (dc == RT_NULL) return RT_FALSE;
		rtgui_widget_get_rect(widget, &rect);

		rtgui_dc_fill_rect(dc, &rect);

		if (background != RT_NULL)
            rtgui_image_blit(background, dc, &rect);

		rtgui_dc_draw_text(dc, "Radio Today", &rect);

		rtgui_dc_end_drawing(dc);

		return RT_FALSE;
	}

	return rtgui_view_event_handler(widget, event);
}

static void today_entry(void* parameter)
{
	rt_mq_t mq;
	struct rtgui_view* view;
	struct rtgui_workbench* workbench;

	mq = rt_mq_create("qToday", 256, 4, RT_IPC_FLAG_FIFO);
	rtgui_thread_register(rt_thread_self(), mq);

    /* create background image */
    background = rtgui_image_create_from_file("png",
        "/bg.png", RT_FALSE);

	workbench = rtgui_workbench_create("main", "workbench");
	if (workbench == RT_NULL) return;

	view = rtgui_view_create("Today");
	rtgui_widget_set_event_handler(RTGUI_WIDGET(view), view_event_handler);

	rtgui_workbench_add_view(workbench, view);

	rtgui_view_show(view);

	rtgui_workbench_event_loop(workbench);

	rtgui_thread_deregister(rt_thread_self());
	rt_mq_delete(mq);
}

void today_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("today",
        today_entry, RT_NULL,
        2048, 25, 10);

    if (tid != RT_NULL) rt_thread_startup(tid);
}
