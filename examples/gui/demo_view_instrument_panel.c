/*
 * 程序清单：DC操作演示
 *
 * 这个例子会在创建出的container上进行DC操作的演示
 */

#include "demo_view.h"
#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/slider.h>
#include <rtgui/image_hdc.h>
#include <math.h>

/*
 * container的事件处理函数
 */
rt_bool_t instrument_panel_event_handler(struct rtgui_object *object, rtgui_event_t *event)
{
    struct rtgui_widget *widget = RTGUI_WIDGET(object);
    char ac[4];
    int i;
    int x0 = 120;
    int y0 = 170;
    int x, y;
    int default_color;

    /* 仅对PAINT事件进行处理 */
    if (event->type == RTGUI_EVENT_PAINT)
    {
        struct rtgui_dc *dc;
        rtgui_rect_t rect;
        const int arrowx[] = {120 + 75, 120 + 75, 120 + 85};
        const int arrowy[] = {170 - 5,  170 + 5,  170};

        /*
         * 因为用的是demo container，上面本身有一部分控件，所以在绘图时先要让demo container
         * 先绘图
         */
        rtgui_container_event_handler(RTGUI_OBJECT(widget), event);

        /************************************************************************/
        /* 下面的是DC的操作                                                     */
        /************************************************************************/

        /* 获得控件所属的DC */
        dc = rtgui_dc_begin_drawing(widget);
        /* 如果不能正常获得DC，返回（如果控件或父控件是隐藏状态，DC是获取不成功的） */
        if (dc == RT_NULL)
            return RT_FALSE;

        /* 获得demo container允许绘图的区域 */
        demo_view_get_rect(RTGUI_CONTAINER(widget), &rect);

        RTGUI_DC_TEXTALIGN(dc) = RTGUI_ALIGN_BOTTOM | RTGUI_ALIGN_CENTER_HORIZONTAL;
        /* 显示GUI的版本信息 */
#ifdef RTGUI_USING_SMALL_SIZE
        rtgui_dc_draw_text(dc, "RT-Thread/GUI小型版本", &rect);
#else
        rtgui_dc_draw_text(dc, "RT-Thread/GUI标准版本", &rect);
#endif


        RTGUI_DC_TEXTALIGN(dc) = RTGUI_ALIGN_CENTER_VERTICAL | RTGUI_ALIGN_CENTER_HORIZONTAL;
        RTGUI_DC_FC(dc) = blue;
        rect.y2 = 270;
        rtgui_dc_draw_text(dc, "rtgui-panel", &rect);

        for (i = 0; i < 6; i++)
        {
            rtgui_dc_draw_arc(dc, x0, y0, 117 - i, 150, 30);
        }

        RTGUI_DC_FC(dc) = black;

        RTGUI_DC_TEXTALIGN(dc) = RTGUI_ALIGN_LEFT;
        for (i = 0; i <= 23; i++)
        {
            if (i < 12)
            {
                x = x0 + 105 * cos((150 + i * 10) * 3.1415926 / 180);
                y = y0 + 105 * sin((150 + i * 10) * 3.1415926 / 180);
                rect.x1 = x;
                rect.y1 = y;
                rect.x2 = rect.x1 + 12 * 3;
                rect.y2 = rect.y1 + 12;
                rt_sprintf(ac, "%d", 10 * i);
                rtgui_dc_draw_text(dc, ac, &rect);
            }
            else
            {
                RTGUI_DC_TEXTALIGN(dc) = RTGUI_ALIGN_RIGHT;

                x = x0 + 105 * cos((160 + i * 10) * 3.1415926 / 180);
                y = y0 + 105 * sin((160 + i * 10) * 3.1415926 / 180);

                rect.x1 = x  - 12 * 3;
                rect.y1 = y;
                rect.x2 = rect.x1 + 12 * 3;
                rect.y2 = rect.y1 + 12;
                rt_sprintf(ac, "%d", 10 * i);
                rtgui_dc_draw_text(dc, ac, &rect);
            }

            x = x0 + 107 * cos((150 + i * 10) * 3.1415926 / 180);
            y = y0 + 107 * sin((150 + i * 10) * 3.1415926 / 180);
            rtgui_dc_fill_circle(dc, x, y, 3);
        }
        RTGUI_DC_FC(dc) = RTGUI_RGB(166, 0, 166);
        rtgui_dc_fill_circle(dc, x0, y0, 3);
        RTGUI_DC_FC(dc) = RTGUI_RGB(120, 141, 30);
        rtgui_dc_draw_circle(dc, x0, y0, 5);

        default_color = RTGUI_DC_BC(dc);
        RTGUI_DC_BC(dc) = red;
        rect.x1 = x0 + 7;
        rect.y1 = y0 - 1;
        rect.x2 = x0 + 75;
        rect.y2 = y0 + 1;
        rtgui_dc_fill_rect(dc, &rect);

        RTGUI_DC_BC(dc) = default_color;

        rtgui_dc_fill_polygon(dc, arrowx, arrowy, 3);

        /* 绘图完成 */
        rtgui_dc_end_drawing(dc);
    }
    else
    {
        /* 其他事件，调用默认的事件处理函数 */
        return rtgui_container_event_handler(RTGUI_OBJECT(widget), event);
    }

    return RT_FALSE;
}

/* 创建用于DC操作演示用的视图 */
rtgui_container_t *demo_view_instrument_panel(void)
{
    rtgui_container_t *container;

    container = demo_view("instrument panel Demo");
    if (container != RT_NULL)
        /* 设置成自己的事件处理函数 */
        rtgui_object_set_event_handler(RTGUI_OBJECT(container), instrument_panel_event_handler);

    return container;
}
