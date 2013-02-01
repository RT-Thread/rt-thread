/*
 * File      : digfont.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-12-21     pife         first version
 */
#ifndef __RTGUI_DIGTUBE_H__
#define __RTGUI_DIGTUBE_H__

#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/widget.h>
#include <rtgui/widgets/digfont.h>

DECLARE_CLASS_TYPE(digtube);

/** Gets the type of a digit tubes */
#define RTGUI_DIGTUBE_TYPE       (RTGUI_TYPE(digtube))
/** Casts the object to an rtgui_digtube */
#define RTGUI_DIGTUBE(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_DIGTUBE_TYPE, rtgui_digtube_t))
/** Checks if the object is an rtgui_digtube */
#define RTGUI_IS_DIGTUBE(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_DIGTUBE_TYPE))

/*
 * the digit tube widget
 */
struct rtgui_digtube
{
    struct rtgui_widget parent;

    struct rtgui_digitfont digitfont;

    /* number of tubes */
    rt_uint8_t tube_count;
    rt_uint8_t tube_style;
    rt_uint8_t digit_hight;
    rt_uint8_t digit_width;
    rt_uint8_t digit_space;
    rtgui_color_t digit_bc;
    void * value; 
};
typedef struct rtgui_digtube rtgui_digtube_t;

rtgui_digtube_t *rtgui_digtube_create( struct rtgui_digitfont * digitfont, int count, void * value, int style);
void rtgui_digtube_destroy(rtgui_digtube_t *digtube);

rt_bool_t rtgui_digtube_event_handler(struct rtgui_object *object, struct rtgui_event *event);

#define RTGUI_DIGTUBE_DEFAULT_BC         RTGUI_RGB(0, 0, 0)
#define RTGUI_DIGTUBE_DEFAULT_FC         RTGUI_RGB(0xFF, 0, 0)
#define RTGUI_DIGTUBE_DEFAULT_DIGIT_BC   RTGUI_RGB(100, 100, 100)

#define RTGUI_DIGTUBE_DEFAULT_SPACE      10

#define RTGUI_DIGTUBE_STYLE_NOBACKFONT   0x01
#define RTGUI_DIGTUBE_STYLE_DISHEXNUM    0x02
#define RTGUI_DIGTUBE_STYLE_DISCODES     0x04

//void rtgui_digtube_set_text(rtgui_digtube_t *digtube, const char *text);
//char *rtgui_digtube_get_text(rtgui_digtube_t *digtube);
#endif