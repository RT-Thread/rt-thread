#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include "demo_view.h"

static struct rtgui_timer *timer;
static struct rtgui_label* label;
static struct rtgui_win* msgbox;
static rt_uint8_t label_text[80];
static int cnt = 5;

void diag_close(struct rtgui_timer* timer, void* parameter)
{
	sprintf(label_text, "closed then %d second!", cnt);

	rtgui_label_set_text(label, label_text);
	rtgui_widget_update(RTGUI_WIDGET(label));
	if (cnt == 0)
	{
		rtgui_win_destroy(msgbox);
		rtgui_timer_stop(timer);
		rtgui_timer_destory(timer);
	}

	cnt --;
}

void window_demo()
{
	rt_mq_t mq;
	rt_thread_t tid;
	rt_uint32_t user_data;
	struct rtgui_rect rect = {50, 50, 200, 200};

	tid = rt_thread_self();
	if (tid == RT_NULL) return; /* can't use in none-scheduler environement */
	user_data = tid->user_data;

	/* create gui message queue */
	mq = rt_mq_create("msgbox", 256, 4, RT_IPC_FLAG_FIFO);
	/* register message queue on current thread */
	rtgui_thread_register(rt_thread_self(), mq);

	msgbox = rtgui_win_create(RT_NULL, "Information", &rect, RTGUI_WIN_STYLE_DEFAULT);
	if (msgbox != RT_NULL)
	{
		struct rtgui_box* box = rtgui_box_create(RTGUI_VERTICAL, RT_NULL);

		cnt = 5;
		sprintf(label_text, "closed then %d second!", cnt);
		label = rtgui_label_create(label_text);

		rtgui_win_set_box(msgbox, box);
		RTGUI_WIDGET(label)->align = RTGUI_ALIGN_CENTER_HORIZONTAL |
			RTGUI_ALIGN_CENTER_VERTICAL;
		rtgui_widget_set_miniwidth(RTGUI_WIDGET(label),130);
		rtgui_box_append(box, RTGUI_WIDGET(label));
		rtgui_box_layout(box);

		rtgui_win_show(msgbox, RT_FALSE);
	}

	timer = rtgui_timer_create(200, RT_TIMER_FLAG_PERIODIC, diag_close, RT_NULL);
	rtgui_timer_start(timer);

	rtgui_win_event_loop(msgbox);

	rtgui_thread_deregister(rt_thread_self());
	/* remove RTGUI message queue */
	rt_mq_delete(mq);

	/* recover user data */
	tid->user_data = user_data;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void win_demo()
{
	window_demo();
}
FINSH_FUNCTION_EXPORT(win_demo, a window demo)
#endif

static void demo_win_onbutton(struct rtgui_widget* widget, rtgui_event_t* event)
{
    window_demo();
}

static void demo_autowin_onbutton(struct rtgui_widget* widget, rtgui_event_t* event)
{
}

static void demo_modalwin_onbutton(struct rtgui_widget* widget, rtgui_event_t* event)
{
}

static void demo_ntitlewin_onbutton(struct rtgui_widget* widget, rtgui_event_t* event)
{
}

rtgui_view_t* demo_view_window(rtgui_workbench_t* workbench)
{
    rtgui_rect_t  rect;
    rtgui_view_t* view;
    rtgui_button_t *button;

    view = demo_view(workbench);
    demo_view_get_rect(view, &rect);

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 = rect.x1 + 100;
	rect.y1 += 5; rect.y2 = rect.y1 + 20;
	button = rtgui_button_create("Normal Win");
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, demo_win_onbutton);

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 = rect.x1 + 100;
	rect.y1 += 5 + 25; rect.y2 = rect.y1 + 20;
	button = rtgui_button_create("Auto Win");
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, demo_autowin_onbutton);

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 = rect.x1 + 100;
	rect.y1 += 5 + 25 + 25; rect.y2 = rect.y1 + 20;
	button = rtgui_button_create("Modal Win");
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, demo_modalwin_onbutton);

	demo_view_get_rect(view, &rect);
	rect.x1 += 5; rect.x2 = rect.x1 + 100;
	rect.y1 += 5 + 25 + 25 + 25; rect.y2 = rect.y1 + 20;
	button = rtgui_button_create("NoTitle Win");
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, demo_ntitlewin_onbutton);

    return view;
}
