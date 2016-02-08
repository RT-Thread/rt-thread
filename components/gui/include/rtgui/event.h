/*
 * File      : event.h
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-04     Bernard      first version
 */
#ifndef __RTGUI_EVENT_H__
#define __RTGUI_EVENT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtdevice.h>
#include <rtgui/rtgui.h>
#include <rtgui/kbddef.h>

/* NOTE: if you create a new event type, remember to add it into the union
 * rtgui_event_generic */
enum _rtgui_event_type
{
    /* applications event */
    RTGUI_EVENT_APP_CREATE,            /* create an application */
    RTGUI_EVENT_APP_DESTROY,           /* destroy an application */
    RTGUI_EVENT_APP_ACTIVATE,          /* activate an application */

    /* window event */
    RTGUI_EVENT_WIN_CREATE,            /* create a window       */
    RTGUI_EVENT_WIN_DESTROY,           /* destroy a window      */
    RTGUI_EVENT_WIN_SHOW,              /* show a window         */
    RTGUI_EVENT_WIN_HIDE,              /* hide a window         */
    RTGUI_EVENT_WIN_ACTIVATE,          /* activate a window     */
    RTGUI_EVENT_WIN_DEACTIVATE,        /* deactivate a window   */
    RTGUI_EVENT_WIN_CLOSE,             /* close a window        */
    RTGUI_EVENT_WIN_MOVE,              /* move a window         */
    RTGUI_EVENT_WIN_RESIZE,            /* resize a window       */
    RTGUI_EVENT_WIN_MODAL_ENTER,       /* the window is entering modal mode.
                                          This event should be sent after the
                                          window got setup and before the
                                          application got setup. */

    /* WM event */
    RTGUI_EVENT_SET_WM,                /* set window manager    */

    RTGUI_EVENT_UPDATE_BEGIN,          /* update a rect         */
    RTGUI_EVENT_UPDATE_END,            /* update a rect         */
    RTGUI_EVENT_MONITOR_ADD,           /* add a monitor rect    */
    RTGUI_EVENT_MONITOR_REMOVE,        /* remove a monitor rect */
    RTGUI_EVENT_SHOW,                  /* the widget is going to be shown */
    RTGUI_EVENT_HIDE,                  /* the widget is going to be hidden */
    RTGUI_EVENT_PAINT,                 /* paint on screen       */
    RTGUI_EVENT_TIMER,                 /* timer                 */
    RTGUI_EVENT_UPDATE_TOPLVL,         /* update the toplevel   */

    /* virtual paint event */
    RTGUI_EVENT_VPAINT_REQ,            /* virtual paint request (server -> client) */

    /* clip rect information */
    RTGUI_EVENT_CLIP_INFO,             /* clip rect info        */

    /* mouse and keyboard event */
    RTGUI_EVENT_MOUSE_MOTION,          /* mouse motion          */
    RTGUI_EVENT_MOUSE_BUTTON,          /* mouse button info     */
    RTGUI_EVENT_KBD,                   /* keyboard info         */
    RTGUI_EVENT_TOUCH,                 /* touch event to server */
    RTGUI_EVENT_GESTURE,               /* gesture event         */

    /* widget event */
    RTGUI_EVENT_FOCUSED,               /* widget focused        */
    RTGUI_EVENT_SCROLLED,              /* scroll bar scrolled   */
    RTGUI_EVENT_RESIZE,                /* widget resize         */
    RTGUI_EVENT_SELECTED,              /* widget selected       */
    RTGUI_EVENT_UNSELECTED,            /* widget un-selected    */
    RTGUI_EVENT_MV_MODEL,              /* data of a model has been changed */

    WBUS_NOTIFY_EVENT,

    /* user command event. It should always be the last command type. */
    RTGUI_EVENT_COMMAND = 0x0100,      /* user command          */
};
typedef enum _rtgui_event_type rtgui_event_type;

enum
{
    RTGUI_STATUS_OK = 0,        /* status ok         */
    RTGUI_STATUS_ERROR,         /* generic error     */
    RTGUI_STATUS_NRC,           /* no resource       */
};

struct rtgui_event
{
    /* the event type */
    enum _rtgui_event_type type;
    /* user field of event */
    rt_uint16_t user;

    /* the event sender */
    struct rtgui_app *sender;

    /* mailbox to acknowledge request */
    rt_mailbox_t ack;
};
typedef struct rtgui_event rtgui_event_t;
#define RTGUI_EVENT(e)  ((struct rtgui_event*)(e))

extern struct rtgui_app* rtgui_app_self(void);

#define RTGUI_EVENT_INIT(e, t)  do      \
{                                       \
    (e)->type = (t);                    \
    (e)->user = 0;                      \
    (e)->sender = rtgui_app_self();     \
    (e)->ack = RT_NULL;                 \
} while (0)

/*
 * RTGUI Application Event
 */
struct rtgui_event_application
{
    struct rtgui_event parent;

    struct rtgui_app *app;
};

/* gui application init */
#define RTGUI_EVENT_APP_CREATE_INIT(e)      RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_APP_CREATE)
#define RTGUI_EVENT_APP_DESTROY_INIT(e)      RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_APP_DESTROY)
#define RTGUI_EVENT_APP_ACTIVATE_INIT(e)      RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_APP_ACTIVATE)

/*
 * RTGUI Window Event
 */
#define _RTGUI_EVENT_WIN_ELEMENTS \
    struct rtgui_event parent; \
    struct rtgui_win *wid;

/*
 * RTGUI Window Event
 */
struct rtgui_event_win
{
    _RTGUI_EVENT_WIN_ELEMENTS
};

struct rtgui_event_win_create
{
    _RTGUI_EVENT_WIN_ELEMENTS
    struct rtgui_win *parent_window;
};

struct rtgui_event_win_move
{
    _RTGUI_EVENT_WIN_ELEMENTS
    rt_int16_t x, y;
};

struct rtgui_event_win_resize
{
    _RTGUI_EVENT_WIN_ELEMENTS

    rtgui_rect_t rect;
};

#define rtgui_event_win_destroy      rtgui_event_win
#define rtgui_event_win_show         rtgui_event_win
#define rtgui_event_win_hide         rtgui_event_win
#define rtgui_event_win_activate     rtgui_event_win
#define rtgui_event_win_deactivate   rtgui_event_win
#define rtgui_event_win_close        rtgui_event_win
#define rtgui_event_win_modal_enter  rtgui_event_win

/* window event init */
#define RTGUI_EVENT_WIN_CREATE_INIT(e)      RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_WIN_CREATE)
#define RTGUI_EVENT_WIN_DESTROY_INIT(e)     RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_WIN_DESTROY)
#define RTGUI_EVENT_WIN_SHOW_INIT(e)        RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_WIN_SHOW)
#define RTGUI_EVENT_WIN_HIDE_INIT(e)        RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_WIN_HIDE)
#define RTGUI_EVENT_WIN_ACTIVATE_INIT(e)    RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_WIN_ACTIVATE)
#define RTGUI_EVENT_WIN_DEACTIVATE_INIT(e)  RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_WIN_DEACTIVATE)
#define RTGUI_EVENT_WIN_CLOSE_INIT(e)       RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_WIN_CLOSE)
#define RTGUI_EVENT_WIN_MOVE_INIT(e)        RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_WIN_MOVE)
#define RTGUI_EVENT_WIN_RESIZE_INIT(e)      RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_WIN_RESIZE)
#define RTGUI_EVENT_WIN_MODAL_ENTER_INIT(e) RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_WIN_MODAL_ENTER)

/*
 * RTGUI set window manager
 */
struct rtgui_event_set_wm
{
    struct rtgui_event parent;
    struct rtgui_app *app;
};
#define RTGUI_EVENT_SET_WM_INIT(e)          RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_SET_WM);

/*
 * RTGUI Other Event
 */
struct rtgui_event_update_begin
{
    struct rtgui_event parent;

    /* the update rect */
    rtgui_rect_t rect;
};

struct rtgui_event_update_end
{
    struct rtgui_event parent;

    /* the update rect */
    rtgui_rect_t rect;
};

struct rtgui_event_monitor
{
    _RTGUI_EVENT_WIN_ELEMENTS

    /* the monitor rect */
    rtgui_rect_t rect;
};

struct rtgui_event_paint
{
    _RTGUI_EVENT_WIN_ELEMENTS

    rtgui_rect_t rect;      /* rect to be updated */
};

struct rtgui_timer;
struct rtgui_event_timer
{
    struct rtgui_event parent;

    struct rtgui_timer *timer;
};
typedef struct rtgui_event_timer rtgui_event_timer_t;


struct rtgui_event_clip_info
{
    _RTGUI_EVENT_WIN_ELEMENTS

    /* the number of rects */
    //rt_uint32_t num_rect;

    /* rtgui_rect_t *rects */
};
#define RTGUI_EVENT_GET_RECT(e, i)          &(((rtgui_rect_t*)(e + 1))[i])

#define RTGUI_EVENT_UPDATE_BEGIN_INIT(e)    RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_UPDATE_BEGIN)
#define RTGUI_EVENT_UPDATE_END_INIT(e)      RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_UPDATE_END)
#define RTGUI_EVENT_MONITOR_ADD_INIT(e)     RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_MONITOR_ADD)
#define RTGUI_EVENT_MONITOR_REMOVE_INIT(e)  RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_MONITOR_REMOVE)
#define RTGUI_EVENT_CLIP_INFO_INIT(e)       RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_CLIP_INFO)
#define RTGUI_EVENT_PAINT_INIT(e)           RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_PAINT)
#define RTGUI_EVENT_TIMER_INIT(e)           RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_TIMER)

#define rtgui_event_show rtgui_event
#define rtgui_event_hide rtgui_event

#define RTGUI_EVENT_SHOW_INIT(e)            RTGUI_EVENT_INIT((e), RTGUI_EVENT_SHOW)
#define RTGUI_EVENT_HIDE_INIT(e)            RTGUI_EVENT_INIT((e), RTGUI_EVENT_HIDE)

struct rtgui_event_update_toplvl
{
    struct rtgui_event parent;
    struct rtgui_win   *toplvl;
};

#define RTGUI_EVENT_UPDATE_TOPLVL_INIT(e)   \
    do { \
        RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_UPDATE_TOPLVL); \
        (e)->toplvl = RT_NULL; \
    } while (0)

struct rtgui_event_vpaint_req
{
    _RTGUI_EVENT_WIN_ELEMENTS

    struct rtgui_event_vpaint_req *sender;
    struct rt_completion *cmp;
    struct rtgui_dc* buffer;
};

#define RTGUI_EVENT_VPAINT_REQ_INIT(e, win, cm) \
    do { \
        RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_VPAINT_REQ); \
        (e)->wid = win; \
        (e)->cmp = cm; \
        (e)->sender = (e); \
        (e)->buffer = RT_NULL; \
        rt_completion_init((e)->cmp); \
    } while (0)

/**
 * RTGUI Gesture Event
 */
enum rtgui_gesture_type
{
    RTGUI_GESTURE_NONE      = 0x0000,
    RTGUI_GESTURE_TAP       = 0x0001,
    /* Usually used to zoom in and out. */
    RTGUI_GESTURE_PINCH     = 0x0002,
    RTGUI_GESTURE_DRAG      = 0x0004,
    RTGUI_GESTURE_LONGPRESS = 0x0008,
    /* PINCH, DRAG finished. */
    RTGUI_GESTURE_FINISH    = 0x8000,
    /* The corresponding gesture should be canceled. */
    RTGUI_GESTURE_CANCEL    = 0x4000,
    RTGUI_GESTURE_TYPE_MASK = 0x0FFF,
};

struct rtgui_event_gesture
{
    _RTGUI_EVENT_WIN_ELEMENTS

    enum rtgui_gesture_type type;
};

/*
 * RTGUI Mouse and Keyboard Event
 */
struct rtgui_event_mouse
{
    _RTGUI_EVENT_WIN_ELEMENTS

    rt_uint16_t x, y;
    rt_uint16_t button;

    /* Timestamp of this event sampled in driver. */
    rt_tick_t ts;
    /* id of touch session(from down to up). Different session should have
     * different id. id should never be 0. */
    rt_uint32_t id;
};
#define RTGUI_MOUSE_BUTTON_LEFT         0x01
#define RTGUI_MOUSE_BUTTON_RIGHT        0x02
#define RTGUI_MOUSE_BUTTON_MIDDLE       0x03
#define RTGUI_MOUSE_BUTTON_WHEELUP      0x04
#define RTGUI_MOUSE_BUTTON_WHEELDOWN    0x08

#define RTGUI_MOUSE_BUTTON_DOWN         0x10
#define RTGUI_MOUSE_BUTTON_UP           0x20

#define RTGUI_EVENT_GESTURE_INIT(e, gtype) \
    do { \
        RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_GESTURE); \
        (e)->type = gtype; \
    } while (0)

struct rtgui_event_kbd
{
    _RTGUI_EVENT_WIN_ELEMENTS

    rt_uint16_t type;       /* key down or up */
    rt_uint16_t key;        /* current key */
    rt_uint16_t mod;        /* current key modifiers */
    rt_uint16_t unicode;    /* translated character */
};
#define RTGUI_KBD_IS_SET_CTRL(e)    ((e)->mod & (RTGUI_KMOD_LCTRL | RTGUI_KMOD_RCTRL))
#define RTGUI_KBD_IS_SET_ALT(e)     ((e)->mod & (RTGUI_KMOD_LALT  | RTGUI_KMOD_RALT))
#define RTGUI_KBD_IS_SET_SHIFT(e)   ((e)->mod & (RTGUI_KMOD_LSHIFT| RTGUI_KMOD_RSHIFT))
#define RTGUI_KBD_IS_UP(e)          ((e)->type == RTGUI_KEYUP)
#define RTGUI_KBD_IS_DOWN(e)        ((e)->type == RTGUI_KEYDOWN)

#define RTGUI_EVENT_MOUSE_MOTION_INIT(e)    RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_MOUSE_MOTION)
#define RTGUI_EVENT_MOUSE_BUTTON_INIT(e)    RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_MOUSE_BUTTON)
#define RTGUI_EVENT_KBD_INIT(e)             RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_KBD)

/**
 * RTGUI Touch Event 
 * NOTE: There is not touch event to user applications, it's handled by server.
 */
struct rtgui_event_touch
{
    struct rtgui_event parent;

    rt_uint16_t x, y;
    rt_uint16_t up_down;
    rt_uint16_t resv;
};
#define RTGUI_TOUCH_UP                  0x01
#define RTGUI_TOUCH_DOWN                0x02
#define RTGUI_TOUCH_MOTION              0x03
#define RTGUI_EVENT_TOUCH_INIT(e)       RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_TOUCH)

struct rtgui_event_command
{
    _RTGUI_EVENT_WIN_ELEMENTS

    /* command type */
    rt_int32_t type;

    /* command id */
    rt_int32_t command_id;

    /* command string */
    char command_string[RTGUI_NAME_MAX];
};
#define RTGUI_EVENT_COMMAND_INIT(e) RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_COMMAND)

#define RTGUI_CMD_UNKNOWN       0x00
#define RTGUI_CMD_WM_CLOSE      0x10

#define RTGUI_CMD_USER_INT      0x20
#define RTGUI_CMD_USER_STRING   0x21

/************************************************************************/
/* Widget Event                                                         */
/************************************************************************/
#define RTGUI_WIDGET_EVENT_INIT(e, t)   do      \
{                                       \
    (e)->type = (t);                    \
    (e)->sender = RT_NULL;              \
    (e)->ack = RT_NULL;                 \
} while (0)

/*
 * RTGUI Scrollbar Event
 */
struct rtgui_event_scrollbar
{
    struct rtgui_event parent;

    rt_uint8_t event;
};
#define RTGUI_SCROLL_LINEUP             0x01
#define RTGUI_SCROLL_LINEDOWN           0x02
#define RTGUI_SCROLL_PAGEUP             0x03
#define RTGUI_SCROLL_PAGEDOWN           0x04
#define RTGUI_EVENT_SCROLLED_INIT(e)    RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_SCROLLED)

/*
 * RTGUI Widget Focused Event
 */
struct rtgui_event_focused
{
    struct rtgui_event parent;

    struct rtgui_widget *widget;
};
#define RTGUI_EVENT_FOCUSED_INIT(e)     RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_FOCUSED)

/*
 * RTGUI Widget Resize Event
 */
struct rtgui_event_resize
{
    struct rtgui_event parent;
    rt_int16_t x, y;
    rt_int16_t w, h;
};
#define RTGUI_EVENT_RESIZE_INIT(e) RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_RESIZE)

/*
 * RTGUI Model/View Event
 */
enum rtgui_event_model_mode
{
    RTGUI_MV_DATA_ADDED,
    RTGUI_MV_DATA_CHANGED,
    RTGUI_MV_DATA_DELETED,
};

struct rtgui_event_mv_model
{
    struct rtgui_event parent;
    struct rtgui_mv_model *model;
    struct rtgui_mv_view  *view;
    rt_size_t first_data_changed_idx;
    rt_size_t last_data_changed_idx;
};

#define _RTGUI_EVENT_MV_INIT_TYPE(T) \
rt_inline void RTGUI_EVENT_MV_MODEL_##T##_INIT(struct rtgui_event_mv_model *e) \
{ \
    RTGUI_EVENT_INIT(&((e)->parent), RTGUI_EVENT_MV_MODEL); \
    (e)->parent.user = RTGUI_MV_DATA_##T; \
} \
/* useless struct to allow trailing semicolon */ \
struct dummy

_RTGUI_EVENT_MV_INIT_TYPE(ADDED);
_RTGUI_EVENT_MV_INIT_TYPE(CHANGED);
_RTGUI_EVENT_MV_INIT_TYPE(DELETED);
#undef _RTGUI_EVENT_MV_INIT_TYPE

#define _RTGUI_EVENT_MV_IS_TYPE(T) \
rt_inline rt_bool_t RTGUI_EVENT_MV_MODEL_IS_##T(struct rtgui_event_mv_model *e) \
{ \
    return e->parent.user == RTGUI_MV_DATA_##T; \
} \
/* useless struct to allow trailing semicolon */ \
struct dummy

_RTGUI_EVENT_MV_IS_TYPE(ADDED);
_RTGUI_EVENT_MV_IS_TYPE(CHANGED);
_RTGUI_EVENT_MV_IS_TYPE(DELETED);
#undef _RTGUI_EVENT_MV_IS_TYPE

#undef _RTGUI_EVENT_WIN_ELEMENTS

union rtgui_event_generic
{
    struct rtgui_event base;

    struct rtgui_event_application app_create;
    struct rtgui_event_application app_destroy;
    struct rtgui_event_application app_activate;

    struct rtgui_event_set_wm set_wm;
    struct rtgui_event_win win_base;
    struct rtgui_event_win_create win_create;
    struct rtgui_event_win_move win_move;
    struct rtgui_event_win_resize win_resize;
    struct rtgui_event_win_destroy win_destroy;
    struct rtgui_event_win_show win_show;
    struct rtgui_event_win_hide win_hide;
    struct rtgui_event_win_activate win_activate;
    struct rtgui_event_win_deactivate win_deactivate;
    struct rtgui_event_win_close win_close;
    struct rtgui_event_win_modal_enter win_modal_enter;
    struct rtgui_event_update_begin update_begin;
    struct rtgui_event_update_end update_end;
    struct rtgui_event_monitor monitor;
    struct rtgui_event_paint paint;
    struct rtgui_event_timer timer;
    struct rtgui_event_update_toplvl update_toplvl;
    struct rtgui_event_vpaint_req vpaint_req;
    struct rtgui_event_clip_info clip_info;
    struct rtgui_event_mouse mouse;
    struct rtgui_event_kbd kbd;
    struct rtgui_event_touch touch;
    struct rtgui_event_gesture gesture;
    struct rtgui_event_scrollbar scrollbar;
    struct rtgui_event_focused focused;
    struct rtgui_event_resize resize;
    struct rtgui_event_mv_model model;
    struct rtgui_event_command command;
};

#ifdef __cplusplus
}
#endif

#endif

