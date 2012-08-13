/*
 * 程序清单：edit控件演示
 *
 * 这个例子会在conatiner上进行edit控件的演示
 */

#include "demo_view.h"
#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/edit.h>
#include <rtgui/widgets/button.h>

void demo_edit_readin_file(struct rtgui_object *object, struct rtgui_event *event)
{
    rtgui_button_t *button;
    struct rtgui_edit *edit;
    const char *filename = "/test_readin.txt";
    int fd;

    RT_ASSERT(object != RT_NULL);
    button = RTGUI_BUTTON(object);
    /* 取得edit指针 */
    edit = RTGUI_EDIT(RTGUI_WIDGET(button)->user_data);

    /* 判断文件是否存在 */
    fd = open(filename, O_RDONLY, 0);
    if (fd < 0)
    {
        /* 不存在存在,则创建它 */
        rt_kprintf("file:\"%s\" does not exist!\n", filename);

        return;
    }
    close(fd);

    rt_kprintf("read-in file:\"%s\"\n", filename);
    rtgui_edit_readin_file(edit, filename);
}

void demo_edit_saveas_file(struct rtgui_object *object, struct rtgui_event *event)
{
    rtgui_button_t *button;
    struct rtgui_edit *edit;
    const char* filename = "/test_saveas.txt";
    int fd;

    RT_ASSERT(object != RT_NULL);
    button = RTGUI_BUTTON(object);
    /* 取得edit指针 */
    edit = RTGUI_EDIT(RTGUI_WIDGET(button)->user_data);

    /* 判断文件是否存在, 如果存在则删除之 */
    fd = open(filename, O_RDONLY, 0);
    if (fd > 0)
    {
        close(fd);
        /* 如果是在win32中调试, 请手工删除该文件吧, NT中文件是只读的,unlink删除不掉 */
        if (unlink(filename) == -1)
            rt_kprintf("Could not delete %s\n", filename);
    }

    rt_kprintf("save as file:\"%s\"\n", filename);
    rtgui_edit_saveas_file(edit, filename);
}

/* 创建用于演示edit控件的视图 */
rtgui_container_t *demo_view_edit(void)
{
    rtgui_rect_t rect;
    rtgui_container_t *container;
    struct rtgui_edit *edit;
    struct rtgui_button *button;

    /* 先创建一个演示用的视图 */
    container = demo_view("Edit View");

    edit = rtgui_edit_create(container, 10, 35, 220, 200);
    rtgui_edit_set_text(edit, 
                        "Edit beta v0.1\n"
                        "Hello RT-Thread\n"
                        "this's edit demo\n"
                        "rtgui_edit_create\n"
                        "rtgui_edit_append_line\n"
                        "rtgui_edit_insert_line\n"
                        "rtgui_edit_delete_line\n"
                        "rtgui_edit_connect_line\n"
                        "a\n"
                        "b\n"
                        "c\n"
                        "d\n"
                        "1234567890\n");

    /* 创建一个按钮, 读取某个文件 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 10;
    rect.x2 = rect.x1 + 100;
    rect.y1 += 200;
    rect.y2 = rect.y1 + 22;
    button = rtgui_button_create("ReadIn File");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, demo_edit_readin_file);
    /* 使用user_data传递edit指针 */
    RTGUI_WIDGET(button)->user_data = (rt_uint32_t)edit;

    /* 创建一个按钮, 保存为某个文件 */
    demo_view_get_rect(container, &rect);
    rect.x1 += 130;
    rect.x2 = rect.x1 + 100;
    rect.y1 += 200;
    rect.y2 = rect.y1 + 22;
    button = rtgui_button_create("SaveAs File");
    rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
    rtgui_container_add_child(container, RTGUI_WIDGET(button));
    rtgui_button_set_onbutton(button, demo_edit_saveas_file);
    /* 使用user_data传递edit指针 */
    RTGUI_WIDGET(button)->user_data = (rt_uint32_t)edit;

    return container;
}
