#include "appmgr.h"
#include <rtgui/widgets/panel.h>
#include <rtgui/widgets/notebook.h>
#include <rtgui/widgets/listbox.h>

#include "apps_list.h"
#include "block_panel.h"
#include "statusbar.h"

#include "xpm/home.xpm"
#include "xpm/home_gray.xpm"

rt_bool_t event_handler(struct rtgui_object* object, rtgui_event_t* event)
{
    rt_bool_t result;

    RT_ASSERT(object != RT_NULL);
    RT_ASSERT(event  != RT_NULL);

    result = RT_TRUE;
    switch (event->type)
    {
    case RTGUI_EVENT_APP_CREATE:
    case RTGUI_EVENT_APP_DESTROY:
        return apps_list_event_handler(object, event);

    default:
        /* invoke parent event handler */
        result = rtgui_app_event_handler(object, event);
        break;
    }

    return result;
}

void app_mgr_win_init(void)
{
    struct rtgui_win* win;
    rtgui_rect_t rect;
    struct rtgui_notebook *notebook;
    struct rtgui_image* pressed_image;
    struct rtgui_image* unpressed_image;
    int font_size;
    struct block_panel* block;
    int angle_y;
    
    /* create main window of Application Manager */
    win = rtgui_mainwin_create(RT_NULL, "AppMgr", RTGUI_WIN_STYLE_MAINWIN);
    RTGUI_WIDGET_BACKGROUND(win) = RTGUI_RGB(241, 241, 241);

    /* create icon image */
    pressed_image = rtgui_image_create_from_mem("xpm", (const rt_uint8_t*)home_xpm, sizeof(home_xpm), RT_FALSE);
    unpressed_image = rtgui_image_create_from_mem("xpm", (const rt_uint8_t*)home_gray_xpm, sizeof(home_gray_xpm), RT_FALSE);
    rtgui_font_get_metrics(RTGUI_WIDGET_FONT(win), "AppMgr", &rect);
    font_size = rtgui_rect_height(rect);

    /* create notebook */
    rtgui_widget_get_extent(RTGUI_WIDGET(win), &rect);
    notebook = rtgui_notebook_create(&rect, RTGUI_NOTEBOOK_LEFT);
    RTGUI_WIDGET_BACKGROUND(notebook) = RTGUI_RGB(241, 241, 241);
    rtgui_notebook_set_tab_height(notebook, pressed_image->h + font_size + 4 * RTGUI_WIDGET_DEFAULT_MARGIN);
    rtgui_notebook_set_tab_width(notebook, 80);
    angle_y = rect.x1;

    /* create navigation */
    block = block_panel_create(angle_y + notebook->tab_h/2, &rect);
    RTGUI_WIDGET_BACKGROUND(block) = RTGUI_RGB(241, 241, 241);
#ifdef _WIN32
    rtgui_notebook_add_image(notebook, "Programs", RTGUI_WIDGET(block),
        pressed_image, unpressed_image);
#endif
#ifndef _WIN32
    program_create(RTGUI_PANEL(block));
#endif
    angle_y += notebook->tab_h;

    rtgui_notebook_get_client_rect(notebook, &rect);
    block = block_panel_create(angle_y + notebook->tab_h/2, &rect);
    RTGUI_WIDGET_BACKGROUND(block) = RTGUI_RGB(241, 241, 241);
#ifdef _WIN32
    rtgui_notebook_add_image(notebook, "Task", RTGUI_WIDGET(block),
        pressed_image, unpressed_image);
#endif
    apps_list_create(RTGUI_PANEL(block));
    angle_y += notebook->tab_h;

    block = block_panel_create(angle_y + notebook->tab_h/2, &rect);
    RTGUI_WIDGET_BACKGROUND(block) = RTGUI_RGB(241, 241, 241);
#ifdef _WIN32
    rtgui_notebook_add_image(notebook, "Setting", RTGUI_WIDGET(block), 
        pressed_image, unpressed_image);
#endif
    angle_y += notebook->tab_h;

    rtgui_container_add_child(RTGUI_CONTAINER(win), RTGUI_WIDGET(notebook));

    rtgui_win_show(win, RT_FALSE);

    /* set as main window */
    rtgui_app_set_main_win(win);
}

void app_mgr_entry(void* parameter)
{
    struct rtgui_app* application;

    application = rtgui_app_create(rt_thread_self(), "AppMgr");
    if (application != RT_NULL)
    {
        /* set as window manager */
        rtgui_app_set_as_wm();

        /* initialize status bar */
        statusbar_init();
        app_mgr_win_init();

        /* set our event handler */
        rtgui_object_set_event_handler(RTGUI_OBJECT(application), 
            event_handler);
        rtgui_app_run(application);
        rtgui_app_destroy(application);
    }
}

void app_mgr_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("app_mgr", app_mgr_entry, RT_NULL, 4096, 20, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);
}

