/*
 * A simple workbench
 */
#include <rtthread.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/workbench.h>

static void workbench_entry(void *parameter)
{
    rt_mq_t mq;
    rtgui_container_t *view;
    rtgui_label_t *label;
    struct rtgui_workbench *workbench;
    rtgui_rect_t rect;

    mq = rt_mq_create("wmq", 256, 8, RT_IPC_FLAG_FIFO);
    /* 注册当前线程为GUI线程 */
    rtgui_thread_register(rt_thread_self(), mq);
    /* 创建一个工作台 */
    workbench = rtgui_workbench_create("main", "workbench #1");
    if (workbench == RT_NULL) return;

    view = rtgui_container_create("view");
    if (view == RT_NULL) return;
    /* 指定视图的背景色 */
    RTGUI_WIDGET_BACKGROUND(RTGUI_WIDGET(view)) = white;

    /* 添加一个label */
    label = rtgui_label_create("你好！RT-Thread！");
    rect.x1 = 10;
    rect.y1 = 10;
    rect.x2 = 210;
    rect.y2 = 30;
    /* 设置label的位置 */
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));

    /* 添加到父workbench中 */
    rtgui_workbench_add_view(workbench, view);
    /* 非模式方式显示视图 */
    rtgui_container_show(view, RT_FALSE);

    /* 执行工作台事件循环 */
    rtgui_workbench_event_loop(workbench);

    /* 去注册GUI线程 */
    rtgui_thread_deregister(rt_thread_self());

    /* delete message queue */
    rt_mq_delete(mq);
}

/* 初始化workbench */
void wb_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("wb1", workbench_entry, RT_NULL, 2048, 20, 5);
    if (tid != RT_NULL) rt_thread_startup(tid);
}
