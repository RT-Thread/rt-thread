#include <rtthread.h>

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/label.h>
#include <rtgui/driver.h>

/* 在LCD上创建一个主窗口，这是第一个窗口 */
static void win_thread_entry(void *parameter)
{
    struct rtgui_app *app;
    struct rtgui_win *win;
    struct rtgui_label *label;
    struct rtgui_rect rect;

    app = rtgui_app_create(rt_thread_self(), "MyApp");
    RT_ASSERT(app != RT_NULL);

    /* create a full screen window */
    rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(), &rect);

    win = rtgui_win_create(RT_NULL, "MainWin", &rect,
                           RTGUI_WIN_STYLE_NO_BORDER | RTGUI_WIN_STYLE_NO_TITLE);
    if (win == RT_NULL)
    {
        rtgui_app_destroy(app);
        return;
    }

    /* 建立一个label，内容为helloworld */
    label = rtgui_label_create("Hello World!");

    /* 设置label的位置，这里是绝对坐标 */
	rect.x1 = 0;
	rect.y1 = 100;
	rect.x2 = 240;
	rect.y2 = 140;
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);

	rt_kprintf("bc: %x\n", RTGUI_WIDGET_BACKGROUND(label));
	rt_kprintf("fc: %x\n", RTGUI_WIDGET_FOREGROUND(label));
#if 0
	RTGUI_WIDGET_BACKGROUND(label) = 0;
	RTGUI_WIDGET_FOREGROUND(label) = RTGUI_RGB(0xFF, 0xFF, 0);
#endif

    /*添加label到主窗口*/
    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(label));

    /* 显示主窗口 */
    rtgui_win_show(win, RT_FALSE);

    /* 循环 */
    rtgui_app_run(app);

    rtgui_win_destroy(win);
    rtgui_app_destroy(app);
    rt_kprintf("MyApp Quit.\n");
}

int main()
{
    rt_thread_t tid;

    tid = rt_thread_create("win", win_thread_entry, RT_NULL,
                           2048, 20, 20);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }

    return 0;
}
