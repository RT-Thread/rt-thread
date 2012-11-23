#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/window.h>
#include <rtgui/rtgui_app.h>

#include <dfs_posix.h>
#include <string.h>

#define PICTURE_DIR "/picture"

/* current picture file name */
rt_bool_t key_pressed = RT_FALSE;
static char current_fn[32] = {0};
static struct rtgui_win *win;

static void picture_show_prev(struct rtgui_widget* widget)
{
    DIR* dir;
    struct dirent* entry;
    rt_bool_t is_last;
    char fn[32];
    struct rtgui_image_engine* engine;
    
    fn[0] = '\0';
    is_last = RT_FALSE;

    dir = opendir(PICTURE_DIR);
    if (dir == RT_NULL)
    {
        rt_kprintf("open directory failed\n");
        return;
    }

    do
    {
        entry = readdir(dir);
        if (entry != RT_NULL)
        {
            engine = rtgui_image_get_engine_by_filename(entry->d_name);
            if (engine != RT_NULL)
            {
                /* it's a HDC image */
                if ((strcmp(entry->d_name, current_fn) == 0) &&
                    is_last != RT_TRUE)
                {
                    if (fn[0] == '\0')
                    {
                        /* it should be the last image */
                        is_last = RT_TRUE;
                    }
                    else
                    {
                        /* display image */
                        strcpy(current_fn, fn);
                        rtgui_widget_update(widget);
                        closedir(dir);
                        return;
                    }
                }
                strcpy(fn, entry->d_name);
            }
        }
    } while(entry != RT_NULL);

    /* close directory */
    closedir(dir);

    if ((is_last == RT_TRUE) && fn[0] != '\0')
    {
        strcpy(current_fn, fn);
        rtgui_widget_update(widget);
    }
}

static void picture_show_next(struct rtgui_widget* widget)
{
    DIR* dir;
    struct dirent* entry;
    rt_bool_t found, has_image;
    struct rtgui_image_engine* engine;

    found = RT_FALSE; has_image = RT_FALSE;

__restart:
    dir = opendir(PICTURE_DIR);
    if (dir == RT_NULL)
    {
        rt_kprintf("open directory failed\n");
        return;
    }

    do
    {
        entry = readdir(dir);
        if (entry != RT_NULL)
        {
            engine = rtgui_image_get_engine_by_filename(entry->d_name);
            if (engine != RT_NULL)
            {
                /* this directory includes image */
                has_image = RT_TRUE;

                if (found == RT_TRUE || current_fn[0] == '\0')
                {
                    strcpy(current_fn, entry->d_name);
                    rtgui_widget_update(widget);

                    closedir(dir);
                    return;
                }

                /* it's a HDC image */
                if (strcmp(entry->d_name, current_fn) == 0)
                    found = RT_TRUE;
            }
        }
    } while(entry != RT_NULL);

    /* close directory */
    closedir(dir);

    if (has_image != RT_TRUE) return;
    current_fn[0] = '\0';
    goto __restart;
}

static rt_bool_t onkey_handle(struct rtgui_object* object, struct rtgui_event* event)
{
    struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;

    if (ekbd->type == RTGUI_KEYDOWN)
    {
        if (ekbd->key == RTGUIK_RIGHT)
        {
            key_pressed = RT_TRUE;
            picture_show_next(RTGUI_WIDGET(object));
            return RT_TRUE;
        }
        else if (ekbd->key == RTGUIK_LEFT)
        {
            key_pressed = RT_TRUE;
            picture_show_prev(RTGUI_WIDGET(object));
            return RT_TRUE;
        }
    }
    return RT_TRUE;
}

static rt_bool_t picture_view_event_handler(rtgui_object_t *object, rtgui_event_t *event)
{
    if (event->type == RTGUI_EVENT_PAINT)
    {
        struct rtgui_dc* dc;
        struct rtgui_rect rect;
        struct rtgui_image* image = RT_NULL;
        char fn[32];

        dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(object));
        if (dc == RT_NULL) return RT_FALSE;
        rtgui_widget_get_rect(RTGUI_WIDGET(object), &rect);

        /* open image */
        rt_snprintf(fn, sizeof(fn), "%s/%s", PICTURE_DIR, current_fn);
        rt_kprintf("pic fn: %s\n", fn);
        image = rtgui_image_create(fn, RT_FALSE);

        if (image != RT_NULL)
        {
            /* blit image */
            rtgui_image_blit(image, dc, &rect);
            /* destroy image */
            rtgui_image_destroy(image);
        }
        else
        {
            rtgui_dc_fill_rect(dc, &rect);
            rtgui_dc_draw_text(dc, "没有文件被打开", &rect);
        }
        rtgui_dc_end_drawing(dc);

        return RT_FALSE;
    }

    return rtgui_win_event_handler(object, event);
}

static void timeout(struct rtgui_timer* timer, void* parameter)
{
    struct rtgui_widget* widget;

    widget = (struct rtgui_widget*)parameter;

    if (key_pressed == RT_TRUE)
        key_pressed = RT_FALSE;
    else
        picture_show_next(widget);
}

void picture_show(void* parameter)
{
    /* create application */
    struct rtgui_app *app;
    struct rtgui_rect rect1;
    rtgui_timer_t *timer;
    
    app = rtgui_app_create(rt_thread_self(), "picture");
    if (app == RT_NULL)
    {
        rt_kprintf("Create application \"picture\" failed!\n");
        return;
    }

    rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(), &rect1);

    /* create main window */
    win = rtgui_mainwin_create(RT_NULL, "main",
                    RTGUI_WIN_STYLE_NO_BORDER | RTGUI_WIN_STYLE_NO_TITLE);
    if (win == RT_NULL)
    {
        rt_kprintf("Create window \"main\" failed!\n");
                rtgui_app_destroy(app);
        return;
    }

    timer = rtgui_timer_create(500, RT_TIMER_FLAG_PERIODIC, timeout, (void*)win);
    rtgui_timer_start(timer);
    
    rtgui_object_set_event_handler(RTGUI_OBJECT(win), picture_view_event_handler);
    rtgui_win_set_onkey(win, onkey_handle);
    rtgui_win_show(win, RT_FALSE);

    /* show next picture */
    picture_show_next(RTGUI_WIDGET(win));

    rtgui_app_run(app);
    rtgui_app_destroy(app);
}

void picture_app_create(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("pic", picture_show, RT_NULL,
        2048, 20, 8);
    if (tid != RT_NULL) rt_thread_startup(tid);
}

