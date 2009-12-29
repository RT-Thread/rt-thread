#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/label.h>

#include <finsh.h>

static struct rtgui_timer *timer;
static struct rtgui_label* label;
static struct rtgui_win* msgbox;
static rt_uint8_t label_text[80];
static int cnt = 5;

void diag_close(struct rtgui_timer* timer, void* parameter)
{
	rt_sprintf(label_text, "closed then %d second!", cnt);

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

void msg()
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
		rt_sprintf(label_text, "closed then %d second!", cnt);
		label = rtgui_label_create(label_text);

		rtgui_win_set_box(msgbox, box);
		RTGUI_WIDGET(label)->align = RTGUI_ALIGN_CENTER_HORIZONTAL |
			RTGUI_ALIGN_CENTER_VERTICAL;
		rtgui_widget_set_miniwidth(RTGUI_WIDGET(label),130);
		rtgui_box_append(box, RTGUI_WIDGET(label));
		rtgui_box_layout(box);

		rtgui_win_show(msgbox, RT_TRUE);
	}

	timer = rtgui_timer_create(200, RT_TIMER_FLAG_PERIODIC,
		diag_close, RT_NULL);
	rtgui_timer_start(timer);

	rtgui_win_event_loop(msgbox);

	rtgui_thread_deregister(rt_thread_self());
	/* remove RTGUI message queue */
	rt_mq_delete(mq);

	/* recover user data */
	tid->user_data = user_data;
}
FINSH_FUNCTION_EXPORT(msg, msg on gui)

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>

#include <rtgui/widgets/box.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/textbox.h>
#include <rtgui/widgets/iconbox.h>
#include <rtgui/widgets/view.h>
#include <rtgui/widgets/workbench.h>

/* XPM */
static const char *goto_xpm[] = {
/* columns rows colors chars-per-pixel */
"16 16 43 1",
". c Black",
"e c #0F0F0F",
"= c #2D2D2D",
"> c #3C3C3C",
"X c #010101",
"$ c #101010",
"% c #1F1F1F",
"r c #090909",
"- c #272727",
"3 c #363636",
"+ c #020202",
"# c #111111",
"2 c #3E3E3E",
"i c #4D4D4D",
"q c #191919",
", c #373737",
"f c #464646",
"o c #030303",
"u c #121212",
"p c #212121",
"; c #0B0B0B",
"  c None",
"7 c #292929",
"O c #040404",
"6 c #131313",
"5 c #222222",
"t c #313131",
"4 c #4F4F4F",
"@ c #0C0C0C",
"a c #1B1B1B",
"* c #2A2A2A",
"0 c #141414",
"< c #0D0D0D",
": c #3A3A3A",
"9 c #060606",
"& c #151515",
"w c #242424",
"s c #424242",
"d c #1D1D1D",
"8 c #070707",
"1 c #161616",
"g c #252525",
"y c #343434",
/* pixels */
"         .XX.   ",
"        oOOO+   ",
"       @####o   ",
"      $%%%%&    ",
"     .*===-+    ",
"      ;:>,;     ",
"    <# 12O      ",
"    345   .X.   ",
"    678 .X++X   ",
"       +9999o   ",
"      o0&&&6+   ",
"      qwwwwe    ",
"      rtyy%     ",
"    +; uip      ",
"    asd o       ",
"    $fg         "
};
static struct rtgui_image* image = RT_NULL;
static void rtgui_demo_workbench_entry(void* parameter)
{
	rt_mq_t mq;
	struct rtgui_view* view;
	struct rtgui_workbench* workbench;

	/* init rtgui demo message queue */
	mq = rt_mq_create("mqWB", 256, 4, RT_IPC_FLAG_FIFO);

	/* register thread and message queue */
	rtgui_thread_register(rt_thread_self(), mq);

	/* create container */
	workbench = rtgui_workbench_create("main", "widget");
	if (workbench == RT_NULL) return;

	/************************************************************************/
	/* Create View                                                          */
	/************************************************************************/
	view = rtgui_view_create("widget");
	rtgui_workbench_add_view(workbench, view);

	image = rtgui_image_create_from_mem("xpm", (rt_uint8_t*)goto_xpm, sizeof(goto_xpm), RT_TRUE);

	{
		struct rtgui_box *box = rtgui_box_create(RTGUI_VERTICAL, &rtgui_empty_rect);
		struct rtgui_box *hbox = rtgui_box_create(RTGUI_HORIZONTAL, &rtgui_empty_rect);
		struct rtgui_button* button = rtgui_button_create("OK");
		struct rtgui_textbox *textbox = rtgui_textbox_create("text edit box");
		struct rtgui_iconbox *iconbox = rtgui_iconbox_create(image, "icon",
			RTGUI_ICONBOX_TEXT_RIGHT);

		RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(view)) = RTGUI_RGB(255, 255, 224);

		rtgui_view_set_box(view, box);

		RTGUI_WIDGET(button)->align = RTGUI_ALIGN_CENTER_VERTICAL;
		rtgui_widget_set_miniwidth(RTGUI_WIDGET(button), 80);
		rtgui_widget_set_miniheight(RTGUI_WIDGET(button), 25);
		rtgui_box_append(box, RTGUI_WIDGET(button));

		/* add a horizontal box */
		rtgui_widget_set_miniwidth(RTGUI_WIDGET(hbox), 20);
		rtgui_widget_set_miniheight(RTGUI_WIDGET(hbox), 100);
		RTGUI_WIDGET(hbox)->align = RTGUI_ALIGN_EXPAND;

		rtgui_box_layout(hbox);
		rtgui_box_append(box, RTGUI_WIDGET(hbox));

		rtgui_box_append(box, RTGUI_WIDGET(textbox));

		/* add icon box */
		RTGUI_WIDGET(iconbox)->gc.font = rtgui_font_refer("hz", 16);
		rtgui_box_append(box, RTGUI_WIDGET(iconbox));
		rtgui_box_layout(box);
	}

	/* show view */
	rtgui_view_show(view, RT_TRUE);
	rtgui_workbench_event_loop(workbench);
}

void rtgui_demo_workbench_init()
{
	static rt_bool_t inited = RT_FALSE;

	if (inited == RT_FALSE)
	{
		rt_thread_t tid;

		tid = rt_thread_create("tWB",
			rtgui_demo_workbench_entry, RT_NULL,
			2048, 25, 10);

		if (tid != RT_NULL) rt_thread_startup(tid);

		inited = RT_TRUE;
	}
}

#ifdef RT_USING_RTGUI
#include <finsh.h>
void w()
{
	rtgui_demo_workbench_init();
}
FINSH_FUNCTION_EXPORT(w, workbench demo)
#endif

