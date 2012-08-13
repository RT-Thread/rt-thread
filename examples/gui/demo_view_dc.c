/*
 * 程序清单：DC操作演示
 *
 * 这个例子会在创建出的view上进行DC操作的演示
 */

#include "demo_view.h"
#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/slider.h>
#include <rtgui/image_hdc.h>

#include "play.hdh"
#include "stop.hdh"
struct rtgui_image_hdcmm play_image = RTGUI_IMAGE_HDC_DEF(2, 0x1c, 0x16, play_hdh);
struct rtgui_image_hdcmm stop_image = RTGUI_IMAGE_HDC_DEF(2, 0x1c, 0x16, stop_hdh);

/*
 * view的事件处理函数
 */
rt_bool_t dc_event_handler(struct rtgui_object *object, rtgui_event_t *event)
{
    struct rtgui_widget *widget = RTGUI_WIDGET(object);

    /* 仅对PAINT事件进行处理 */
    if (event->type == RTGUI_EVENT_PAINT)
    {
        struct rtgui_dc *dc;
        rtgui_rect_t rect;
        const int vx[] = {20, 50, 60, 45, 60, 20};
        const int vy[] = {150, 50, 90, 60, 45, 50};

        /*
         * 因为用的是demo view，上面本身有一部分控件，所以在绘图时先要让demo view
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

        /* 获得demo view允许绘图的区域 */
        demo_view_get_logic_rect(RTGUI_CONTAINER(widget), &rect);

        RTGUI_DC_TEXTALIGN(dc) = RTGUI_ALIGN_BOTTOM | RTGUI_ALIGN_CENTER_HORIZONTAL;
        /* 显示GUI的版本信息 */
#ifdef RTGUI_USING_SMALL_SIZE
        rtgui_dc_draw_text(dc, "RT-Thread/GUI小型版本", &rect);
#else
        rtgui_dc_draw_text(dc, "RT-Thread/GUI标准版本", &rect);
#endif

        {
            rtgui_rect_t rect = {0, 0, 0x1c, 0x16};
            rtgui_rect_moveto(&rect, 80, 80);
            rtgui_image_blit((rtgui_image_t *)&play_image, dc, &rect);

            rect.x1 = 0;
            rect.y1 = 0;
            rect.x2 = 0x1c;
            rect.y2 = 0x16;
            rtgui_rect_moveto(&rect, 130, 80);
            rtgui_image_blit((rtgui_image_t *)&stop_image, dc, &rect);
        }
        /* 绘制一个圆形 */
        RTGUI_DC_FC(dc) = red;
        rtgui_dc_draw_circle(dc, rect.x1 + 10, rect.y1 + 10, 10);

        /* 填充一个圆形 */
        RTGUI_DC_FC(dc) = green;
        rtgui_dc_fill_circle(dc, rect.x1 + 30, rect.y1 + 10, 10);
#if 0
        /* 画一个圆角矩形 */
        rect.x1 = 150;
        rect.y1 = 180;
        rect.x2 = 210;
        rect.y2 = 260;
        RTGUI_DC_FC(dc) = RTGUI_RGB(25, 70, 150);
        rtgui_dc_draw_round_rect(dc, &rect, 10);

        rect.x1 = 160;
        rect.y1 = 190;
        rect.x2 = 200;
        rect.y2 = 250;
        RTGUI_DC_FC(dc) = RTGUI_RGB(170, 7, 80);
        rtgui_dc_fill_round_rect(dc, &rect, 7);

        /* 画一个圆弧 */
        RTGUI_DC_FC(dc) = RTGUI_RGB(250, 120, 120);
        rtgui_dc_draw_arc(dc, rect.x1 + 120, rect.y1 + 60, 30, 0, 120);

        /* 画一个扇形圆环 */
        RTGUI_DC_FC(dc) = RTGUI_RGB(150, 23, 100);
        rtgui_dc_draw_annulus(dc, 180, 170, 30, 50, 210, 330);

        /* 多边形 */
        RTGUI_DC_FC(dc) = blue;
        rtgui_dc_draw_polygon(dc, vx, vy, 6);

#endif
        RTGUI_DC_FC(dc) = blue;

        /* 绘制不同的边框 */
        {
            rtgui_rect_t rect = {0, 0, 16, 16};
            rtgui_rect_moveto(&rect, 30, 120);

            rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_RAISE);
            rect.x1 += 20;
            rect.x2 += 20 + 50;
            rtgui_dc_draw_text(dc, "raise", &rect);
            rect.x1 -= 20;
            rect.x2 -= 20 + 50;
            rect.y1 += 20;
            rect.y2 += 20;

            rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_SIMPLE);
            rect.x1 += 20;
            rect.x2 += 20 + 50;
            rtgui_dc_draw_text(dc, "simple", &rect);
            rect.x1 -= 20;
            rect.x2 -= 20 + 50;
            rect.y1 += 20;
            rect.y2 += 20;

            rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_SUNKEN);
            rect.x1 += 20;
            rect.x2 += 20 + 50;
            rtgui_dc_draw_text(dc, "sunken", &rect);
            rect.x1 -= 20;
            rect.x2 -= 20 + 50;
            rect.y1 += 20;
            rect.y2 += 20;

            rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_BOX);
            rect.x1 += 20;
            rect.x2 += 20 + 50;
            rtgui_dc_draw_text(dc, "box", &rect);
            rect.x1 -= 20;
            rect.x2 -= 20 + 50;
            rect.y1 += 20;
            rect.y2 += 20;

            rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_STATIC);
            rect.x1 += 20;
            rect.x2 += 20 + 50;
            rtgui_dc_draw_text(dc, "static", &rect);
            rect.x1 -= 20;
            rect.x2 -= 20 + 50;
            rect.y1 += 20;
            rect.y2 += 20;

            rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_EXTRA);
            rect.x1 += 20;
            rect.x2 += 20 + 50;
            rtgui_dc_draw_text(dc, "extera", &rect);
            rect.x1 -= 20;
            rect.x2 -= 20 + 50;
            rect.y1 += 20;
            rect.y2 += 20;
        }

        /* 绘图完成 */
        rtgui_dc_end_drawing(dc);
    }
    else
    {
        /* 其他事件，调用默认的事件处理函数 */
        return rtgui_container_event_handler(object, event);
    }

    return RT_FALSE;
}

/* 创建用于DC操作演示用的视图 */
rtgui_container_t *demo_view_dc(void)
{
    rtgui_container_t *view;

    view = demo_view("DC Demo");
    if (view != RT_NULL)
        /* 设置成自己的事件处理函数 */
        rtgui_object_set_event_handler(RTGUI_OBJECT(view), dc_event_handler);

    return view;
}
