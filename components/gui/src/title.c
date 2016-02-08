/*
 * File      : title.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 */
#include <rtgui/rtgui_system.h>
//#include <rtgui/rtgui_theme.h>

#include <rtgui/widgets/window.h>
#include <rtgui/widgets/title.h>

//#include "../server/mouse.h"

/* there is no event handler in wintitle but handle the event on topwin of server */
static void _rtgui_wintitle_constructor(rtgui_wintitle_t *wintitle)
{
    RTGUI_WIDGET(wintitle)->flag = RTGUI_WIDGET_FLAG_DEFAULT;
    RTGUI_WIDGET_TEXTALIGN(wintitle) = RTGUI_ALIGN_CENTER_VERTICAL;

    rtgui_object_set_event_handler(RTGUI_OBJECT(wintitle),
                                   rtgui_wintile_event_handler);
}

static void _rtgui_wintitle_deconstructor(rtgui_wintitle_t *wintitle)
{
}

DEFINE_CLASS_TYPE(wintitle, "wintitle",
                  RTGUI_PARENT_TYPE(widget),
                  _rtgui_wintitle_constructor,
                  _rtgui_wintitle_deconstructor,
                  sizeof(struct rtgui_wintitle));

rtgui_wintitle_t *rtgui_wintitle_create(struct rtgui_win *window)
{
    rtgui_wintitle_t *wintitle;

    wintitle = (rtgui_wintitle_t *)rtgui_widget_create(RTGUI_WINTITLE_TYPE);
    if (wintitle != RT_NULL)
    {
        RTGUI_WIDGET(wintitle)->toplevel = window;
    }

    return wintitle;
}

void rtgui_wintitle_destroy(rtgui_wintitle_t *wintitle)
{
    rtgui_widget_destroy(RTGUI_WIDGET(wintitle));
}

rt_bool_t rtgui_wintile_event_handler(struct rtgui_object *obj, rtgui_event_t *eve)
{
    struct rtgui_wintitle *wint;
    struct rtgui_win *win;

    RT_ASSERT(obj);
    RT_ASSERT(eve);

    wint = RTGUI_WINTITLE(obj);
    win = RTGUI_WIDGET(wint)->toplevel;
    RT_ASSERT(win);

    switch (eve->type)
    {
    case RTGUI_EVENT_PAINT:
        rtgui_theme_draw_win(wint);
        return RT_FALSE;

    case RTGUI_EVENT_MOUSE_BUTTON: {
        struct rtgui_event_mouse *emou = (struct rtgui_event_mouse *)eve;

        if (win->style & RTGUI_WIN_STYLE_CLOSEBOX)
        {
            rtgui_rect_t rect;

            /* get close button rect (device value) */
            rect.x1 = RTGUI_WIDGET(wint)->extent.x2 - WINTITLE_BORDER_SIZE - WINTITLE_CB_WIDTH - 3;
            rect.y1 = RTGUI_WIDGET(wint)->extent.y1 + WINTITLE_BORDER_SIZE + 3;
            rect.x2 = rect.x1 + WINTITLE_CB_WIDTH;
            rect.y2 = rect.y1 + WINTITLE_CB_HEIGHT;

            if (emou->button & RTGUI_MOUSE_BUTTON_LEFT)
            {
                if (emou->button & RTGUI_MOUSE_BUTTON_DOWN)
                {
                    if (rtgui_rect_contains_point(&rect, emou->x, emou->y) == RT_EOK)
                    {
                        win->flag |= RTGUI_WIN_FLAG_CB_PRESSED;
                        rtgui_theme_draw_win(wint);
                    }
#ifdef RTGUI_USING_WINMOVE
                    else
                    {
                        rtgui_winrect_set(win);
                    }
#endif
                }
                else if (emou->button & RTGUI_MOUSE_BUTTON_UP)
                {
                    if (win->flag & RTGUI_WIN_FLAG_CB_PRESSED &&
                        rtgui_rect_contains_point(&rect,
                                                  emou->x, emou->y) == RT_EOK)
                    {
                        rtgui_win_close(win);
                        return RT_TRUE;
                    }

                    win->flag &= ~RTGUI_WIN_FLAG_CB_PRESSED;
                    rtgui_theme_draw_win(wint);
#ifdef RTGUI_USING_WINMOVE
                    /* Reset the window movement state machine. */
                    rtgui_winrect_moved_done(RT_NULL, RT_NULL);
#endif
                }
            }
        }
        else if (emou->button & RTGUI_MOUSE_BUTTON_DOWN)
        {
#ifdef RTGUI_USING_WINMOVE
            rtgui_winrect_set(win);
#endif
        }
    }
        return RT_TRUE;
    default:
        return rtgui_widget_event_handler(obj, eve);
    }
}

