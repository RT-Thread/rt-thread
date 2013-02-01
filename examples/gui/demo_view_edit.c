/*
 * 程序清单：edit控件演示
 *
 * 这个例子会在conatiner上进行edit控件的演示
 */

#include "demo_view.h"
#include <rtgui/dc.h>
#include <rtgui/filerw.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/edit.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>

#ifdef RTGUI_USING_DFS_FILERW
void demo_edit_readin_file(struct rtgui_object *object, struct rtgui_event *event)
{
    rtgui_button_t *button;
    struct rtgui_edit *edit;
    const char *filename = "/test_readin.txt";
    struct rtgui_filerw *file;

    RT_ASSERT(object != RT_NULL);
    button = RTGUI_BUTTON(object);
    /* 取得edit指针 */
    edit = RTGUI_EDIT(RTGUI_WIDGET(button)->user_data);

    /* 判断文件是否存在 */
    file = rtgui_filerw_create_file(filename, "rb");
    if (file == RT_NULL)
    {
        /* 不存在存在,则创建它 */
        rt_kprintf("file:\"%s\" does not exist!\n", filename);

        return;
    }
    rtgui_filerw_close(file);

    rt_kprintf("read-in file:\"%s\"\n", filename);
    rtgui_edit_readin_file(edit, filename);
}

void demo_edit_saveas_file(struct rtgui_object *object, struct rtgui_event *event)
{
    rtgui_button_t *button;
    struct rtgui_edit *edit;
    const char* filename = "/test_saveas.txt";
    struct rtgui_filerw *file;

    RT_ASSERT(object != RT_NULL);
    button = RTGUI_BUTTON(object);
    /* 取得edit指针 */
    edit = RTGUI_EDIT(RTGUI_WIDGET(button)->user_data);

    /* 判断文件是否存在, 如果存在则删除之 */
    file = rtgui_filerw_create_file(filename, "rb");
    if (file != RT_NULL)
    {
        rtgui_filerw_close(file);
        /* 如果是在win32中调试, 请手工删除该文件吧, NT中文件是只读的,unlink删除不掉 */
        if (rtgui_filerw_unlink(filename) == -1)
            rt_kprintf("Could not delete %s\n", filename);
    }

    rt_kprintf("save as file:\"%s\"\n", filename);
    rtgui_edit_saveas_file(edit, filename);
}

void demo_edit_get_mem(struct rtgui_object* object, struct rtgui_event* event)
{
	rtgui_button_t *button;
	struct rtgui_edit *edit;

	RT_ASSERT(object != RT_NULL);

	button = RTGUI_BUTTON(object);
	edit = RTGUI_EDIT( RTGUI_WIDGET(button)->user_data );
	rt_kprintf("edit mem consume: %d\n", rtgui_edit_get_mem_consume(edit));
}

rt_bool_t demo_edit_event_handler(struct rtgui_object* object, struct rtgui_event *event)
{
	rt_bool_t result;
	char buf[32];
	rtgui_point_t p;
	struct rtgui_edit *edit = RTGUI_EDIT(object);
	struct rtgui_label *label = (struct rtgui_label*)RTGUI_WIDGET(edit)->user_data;

	result = rtgui_edit_event_handler(object, event);

	p = rtgui_edit_get_current_point(edit);
	rt_sprintf(buf, "TRACK: line:%d, col:%d", p.y, p.x);
	rtgui_label_set_text(label, buf);
	
	return result;
}

/* 创建用于演示edit控件的视图 */
rtgui_container_t *demo_view_edit(void)
{
    rtgui_rect_t rect;
    rtgui_container_t *container;
    struct rtgui_edit *edit;
	struct rtgui_label *label;
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
						"双字节测试\n"
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

	/* 创建一个标签, 显示EDIT的主要参数 */
	demo_view_get_rect(container, &rect);
	rect.x1 += 10;
	rect.x2 = rect.x1 + 220;
	rect.y1 += 225;
	rect.y2 = rect.y1 + 18;
	label = rtgui_label_create("TRACK:");
	RTGUI_WIDGET_TEXTALIGN(label) = RTGUI_ALIGN_LEFT | RTGUI_ALIGN_CENTER_VERTICAL;
	RTGUI_WIDGET_FOREGROUND(label) = blue;
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	rtgui_container_add_child(container, RTGUI_WIDGET(label));

	RTGUI_WIDGET(edit)->user_data = (rt_uint32_t)label;
	rtgui_object_set_event_handler(RTGUI_OBJECT(edit), demo_edit_event_handler);
	
	/* 创建一个按钮, 读取EDIT的内存消耗 */
	demo_view_get_rect(container, &rect);
	rect.x1 += 150;
	rect.x2 = rect.x1 + 80;
	rect.y1 -= 42;
	rect.y2 = rect.y1 + 20;
	button = rtgui_button_create("Get Mem");
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(container, RTGUI_WIDGET(button));
	rtgui_button_set_onbutton(button, demo_edit_get_mem);
	RTGUI_WIDGET(button)->user_data = (rt_uint32_t)edit;

    return container;
}
#endif
