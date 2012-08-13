/*
 * 程序清单：文件列表视图演示
 *
 * 这个例子会先创建出一个演示用的view，当点击上面的按钮时会按照模式显示的形式显示
 * 新的文件列表视图。
 */
#include "demo_view.h"
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/filelist_view.h>

#if defined(RTGUI_USING_DFS_FILERW) || defined(RTGUI_USING_STDIO_FILERW)
/* 用于显示选择文件名的文本标签 */
static rtgui_label_t *label;
/* 触发文件列表视图的按钮回调函数 */
static void open_btn_onbutton(rtgui_widget_t *widget, struct rtgui_event *event)
{
    rtgui_filelist_view_t *view;
    rtgui_workbench_t *workbench;
    rtgui_rect_t rect;

    /* 获得顶层的workbench对象 */
    workbench = RTGUI_APPLICATION(rtgui_widget_get_toplevel(widget));
    rtgui_widget_get_rect(RTGUI_WIDGET(workbench), &rect);

    /* 针对Win32平台和其他平台做的不同的其实目录位置 */
#ifdef _WIN32
    view = rtgui_filelist_view_create(workbench, "d:\\", "*.*", &rect);
#else
    view = rtgui_filelist_view_create(workbench, "/", "*.*", &rect);
#endif

    /* 采用模式形式显示文件列表视图 */
    if (rtgui_container_show(RTGUI_CONTAINER(view), RT_TRUE) == RTGUI_MODAL_OK)
    {
        char path[32];

        /* 在文件列表视图中成功选择文件，这里获得相应的路径名 */
        rtgui_filelist_view_get_fullpath(view, path, sizeof(path));

        /* 设置文件路径到文本标签 */
        rtgui_label_set_text(label, path);
    }

    /* 删除 文件列表 视图 */
    rtgui_container_destroy(RTGUI_CONTAINER(view));
}

/* 创建用于演示文件列表视图的视图 */
rtgui_container_t *demo_fn_view(rtgui_workbench_t *workbench)
{
    rtgui_rect_t rect;
    rtgui_container_t *view;
    rtgui_button_t *open_btn;
    rtgui_font_t *font;

    /* 默认采用12字体的显示 */
    font = rtgui_font_refer("asc", 12);

    /* 创建演示用的视图 */
    view = demo_view(workbench, "FileList View");
    /* 获得演示视图的位置信息 */
    demo_view_get_rect(view, &rect);

    rect.x1 += 5;
    rect.x2 -= 5;
    rect.y1 += 5;
    rect.y2 = rect.y1 + 20;
    /* 创建显示文件路径用的文本标签 */
    label = rtgui_label_create("fn: ");
    rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));
    rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
    RTGUI_WIDGET_FONT(RTGUI_WIDGET(label)) = font;

    /* 获得演示视图的位置信息 */
    demo_view_get_rect(view, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 80;
    rect.y1 += 30;
    rect.y2 = rect.y1 + 20;
    /* 创建按钮以触发一个新的文件列表视图 */
    open_btn = rtgui_button_create("Open File");
    rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(open_btn));
    rtgui_widget_set_rect(RTGUI_WIDGET(open_btn), &rect);
    RTGUI_WIDGET_FONT(RTGUI_WIDGET(open_btn)) = font;
    rtgui_button_set_onbutton(open_btn, open_btn_onbutton);

    return view;
}
#endif
