#include <rtthread.h>

#if defined(RT_USING_GUIENGINE) && defined(RTGUI_USING_DEMO)

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/image.h>
#include <rtgui/widgets/window.h>
#include <rtgui/dc.h>

extern const unsigned char _picture_png[];
extern int _picture_png_length_get(void);

static rt_bool_t show_demo(struct rtgui_win *win)
{
    struct rtgui_dc *dc;
    rtgui_rect_t rect;

    dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(win));
    if (dc == RT_NULL)
    {
        rt_kprintf("dc is null \n");
        return RT_FALSE;
    }
    rtgui_dc_get_rect(dc, &rect);

    /* draw circular */
    {
        rt_int16_t x, y, r;

        x = rect.x2 / 2 / 2;
        y = rect.y2 / 2 / 2;
        r = x > y ? y : x;
        r -= y / 10;
        rtgui_dc_draw_circle(dc, x, y, r);
    }

    /* draw image */
    {
        rtgui_rect_t draw_rect;
        struct rtgui_image *img;

        img = rtgui_image_create_from_mem("png", _picture_png, _picture_png_length_get(), RT_TRUE);
        if (img != RT_NULL)
        {
            draw_rect.x1 = rect.x2 / 2 + (rect.x2 / 2 - img->w) / 2;
            draw_rect.y1 = (rect.y2 / 2 - img->h) / 2;
            draw_rect.x2 = draw_rect.x1 + img->w;
            draw_rect.y2 = draw_rect.y1 + img->h;
            rtgui_image_blit(img, dc, &draw_rect);
        }
    }

    /* draw text */
    {
        rtgui_color_t fc;
        rtgui_rect_t draw_rect;
        char *text_buf = "Hello RT-thread!";

        fc = RTGUI_DC_FC(dc);
        RTGUI_DC_FC(dc) = RED;
        draw_rect.x1 = rect.x2 * 2 / 5;
        draw_rect.y1 = rect.y2 * 3 / 4;
        draw_rect.x2 = rect.x2;
        draw_rect.y2 = rect.y2;
        rtgui_dc_draw_text(dc, text_buf, &draw_rect);
        RTGUI_DC_FC(dc) = fc;
    }

    rtgui_dc_end_drawing(dc, RT_TRUE);

    return RT_TRUE;
}

rt_bool_t dc_event_handler(struct rtgui_object *object, rtgui_event_t *event)
{
    rt_bool_t err;
    struct rtgui_win *win = RTGUI_WIN(object);

    err = rtgui_win_event_handler(RTGUI_OBJECT(win), event);
    if (event->type == RTGUI_EVENT_PAINT)
        show_demo(win);

    return err;
}

static void rt_gui_demo_entry(void *parameter)
{
    struct rtgui_win *main_win;
    struct rtgui_app *app;

    /* create gui app */
    app = rtgui_app_create("gui_demo");
    if (app == RT_NULL)
        return;

    main_win = rtgui_mainwin_create(RT_NULL, "UiWindow", RTGUI_WIN_STYLE_NO_TITLE);
    if (main_win == RT_NULL)
    {
        rtgui_app_destroy(app);
        return;
    }
    rtgui_object_set_event_handler(RTGUI_OBJECT(main_win), dc_event_handler);
    rtgui_win_show(main_win, RT_FALSE);

    rtgui_app_run(app);
    rtgui_win_destroy(main_win);
    rtgui_app_destroy(app);
}

int rt_gui_demo_init(void)
{
    rt_thread_t tid;
    
    tid = rt_thread_create("mygui",
        rt_gui_demo_entry, RT_NULL,
        2048, 25, 10);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
INIT_APP_EXPORT(rt_gui_demo_init);
#endif /* RT_USING_RTGUI */