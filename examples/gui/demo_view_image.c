/*
 * 程序清单：DC上显示图像演示
 *
 * 这个例子会在创建出的container上显示图像
 */

#include "demo_view.h"
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/filelist_view.h>
#include <string.h>

static rtgui_image_t *image = RT_NULL;
static rtgui_container_t *_container = RT_NULL;

#if defined(RTGUI_USING_DFS_FILERW) || defined(RTGUI_USING_STDIO_FILERW)
/* 打开按钮的回调函数 */
static void open_btn_onbutton(rtgui_widget_t *widget, struct rtgui_event *event)
{
    rtgui_filelist_view_t *filelist;
    struct rtgui_rect rect = {0, 100, 240, 280};

    /* WIN32平台上和真实设备上的初始路径处理 */
#ifdef _WIN32
    filelist = rtgui_filelist_view_create("e:\\", "*.*", &rect);
#else
    filelist = rtgui_filelist_view_create("/", "*.*", &rect);
#endif
    /* 模态显示一个文件列表视图，以提供给用户选择图像文件 */
    if (rtgui_widget_show(RTGUI_WIDGET(filelist), RT_TRUE) == RTGUI_MODAL_OK)
    {
        char path[32], image_type[8];

        /* 设置文件路径的标签 */
        rtgui_filelist_view_get_fullpath(filelist, path, sizeof(path));
        if (image != RT_NULL)
        {
            rtgui_image_destroy(image);
            image = RT_NULL;
        }

        rt_memset(image_type, 0, sizeof(image_type));

        /* 获得图像的类型 */
        if (rt_strstr(path, ".bmp") != RT_NULL ||
                rt_strstr(path, ".BMP") != RT_NULL)
            strcat(image_type, "bmp");
        if (rt_strstr(path, ".png") != RT_NULL ||
                rt_strstr(path, ".PNG") != RT_NULL)
            strcat(image_type, "png");
        if (rt_strstr(path, ".jpg") != RT_NULL ||
                rt_strstr(path, ".JPG") != RT_NULL)
            strcat(image_type, "jpeg");
        if (rt_strstr(path, ".hdc") != RT_NULL ||
                rt_strstr(path, ".HDC") != RT_NULL)
            strcat(image_type, "hdc");

        /* 如果图像文件有效，创建相应的rtgui_image对象 */
        if (image_type[0] != '\0')
            image = rtgui_image_create_from_file(image_type, path, RT_TRUE);
    }

    /* 删除 文件列表 视图 */
    rtgui_container_destroy(RTGUI_CONTAINER(filelist));
    rtgui_container_show(_container, RT_FALSE);
}

/* 演示视图的事件处理函数 */
static rt_bool_t demo_view_event_handler(rtgui_widget_t *widget, rtgui_event_t *event)
{
    rt_bool_t result;

    /* 先调用默认的事件处理函数(这里只关心PAINT事件，但演示视图还有本身的一些控件) */
    result = rtgui_container_event_handler(widget, event);

    if (event->type == RTGUI_EVENT_PAINT)
    {
        struct rtgui_dc *dc;
        rtgui_rect_t rect;

        /* 获得控件所属的DC */
        dc = rtgui_dc_begin_drawing(widget);
        if (dc == RT_NULL)
            /* 如果不能正常获得DC，返回(如果控件或父控件是隐藏状态，DC是获取不成功的) */
            return RT_FALSE;

        /* 获得demo container允许绘图的区域 */
        demo_view_get_rect(RTGUI_CONTAINER(widget), &rect);

        /* 获得图像显示区域 */
        rect.x1 += 5;
        rect.x2 -= 5;
        rect.y1 += 30;

        if (image != RT_NULL)
            rtgui_image_blit(image, dc, &rect);

        /* 绘图完成 */
        rtgui_dc_end_drawing(dc);
    }

    return result;
}

/* 创建用于显示图像的演示视图 */
rtgui_container_t *demo_view_image(void)
{
    rtgui_rect_t rect;
    rtgui_button_t *open_btn;

    /* 先创建一个演示视图 */
    _container = demo_view("图像演示");
    if (_container != RT_NULL)
        /* 设置默认的事件处理函数到demo_view_event_handler函数 */
        rtgui_object_set_event_handler(RTGUI_WIDGET(_container), demo_view_event_handler);

    /* 添加一个按钮 */
    demo_view_get_rect(_container, &rect);
    rect.x1 += 5;
    rect.x2 = rect.x1 + 120;
    rect.y2 = rect.y1 + 20;
    open_btn = rtgui_button_create("打开图像文件");
    rtgui_container_add_child(RTGUI_CONTAINER(_container), RTGUI_WIDGET(open_btn));
    rtgui_widget_set_rect(RTGUI_WIDGET(open_btn), &rect);
    rtgui_button_set_onbutton(open_btn, open_btn_onbutton);

    return _container;
}
#endif
