/*
 * File      : textview.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-05     Bernard      first version
 */
#ifndef __RTGUI_TEXTVIEW_H__
#define __RTGUI_TEXTVIEW_H__

#include <rtgui/widgets/widget.h>

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @defgroup rtgui_textview
     * @{
     */

    DECLARE_CLASS_TYPE(textview);

    /** Gets the type of a textview */
#define RTGUI_TEXTVIEW_TYPE       (RTGUI_TYPE(textview))
    /** Casts the object to an rtgui_textview */
#define RTGUI_TEXTVIEW(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_TEXTVIEW_TYPE, rtgui_textview_t))
    /** Checks if the object is an rtgui_textview */
#define RTGUI_IS_TEXTVIEW(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_TEXTVIEW_TYPE))

    /*
     * the textview widget
     */
    struct rtgui_textview
    {
        /* inherit from widget */
        struct rtgui_widget parent;

        rt_uint16_t line_width;
        rt_uint16_t line_count;

        char *lines;

        rt_int16_t line_current;
        rt_uint16_t line_page_count;
    };
    typedef struct rtgui_textview rtgui_textview_t;

    rtgui_textview_t *rtgui_textview_create(const char *text, const rtgui_rect_t *rect);
    void rtgui_textview_destroy(rtgui_textview_t *textview);

    rt_bool_t rtgui_textview_event_handler(struct rtgui_object *object, struct rtgui_event *event);
    void rtgui_textview_set_text(rtgui_textview_t *textview, const char *text);

    /** @} */

#ifdef __cplusplus
}
#endif

#endif
