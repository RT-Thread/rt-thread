/*
 * File      : rtgui_system.c
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
 * 2016-03-23     Bernard      fix the default font initialization issue. 
 */

#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/font.h>
#include <rtgui/event.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/window.h>

#ifdef _WIN32_NATIVE
#define RTGUI_MEM_TRACE
#endif

const rtgui_color_t default_foreground = RTGUI_RGB(0x00, 0x00, 0x00);
const rtgui_color_t default_background = RTGUI_RGB(212, 208, 200);

extern struct rtgui_font rtgui_font_asc16;
extern struct rtgui_font rtgui_font_asc12;

static rtgui_rect_t _mainwin_rect;
static struct rt_mutex _screen_lock;

int rtgui_system_server_init(void)
{
    rt_mutex_init(&_screen_lock, "screen", RT_IPC_FLAG_FIFO);

    /* init image */
    rtgui_system_image_init();
    /* init font */
    rtgui_font_system_init();

    /* init rtgui server */
    rtgui_topwin_init();
    rtgui_server_init();

    /* use driver rect for main window */
    rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(), &_mainwin_rect);

    /* set the default font */
#if RTGUI_DEFAULT_FONT_SIZE == 16
    rtgui_font_set_defaut(&rtgui_font_asc16);
#elif RTGUI_DEFAULT_FONT_SIZE == 12
    rtgui_font_set_defaut(&rtgui_font_asc12);
#else
    rtgui_font_set_defaut(&rtgui_font_asc12);
#endif

    return 0;
}
INIT_APP_EXPORT(rtgui_system_server_init);

/************************************************************************/
/* RTGUI Timer                                                          */
/************************************************************************/
static void rtgui_time_out(void *parameter)
{
    rtgui_timer_t *timer;
    rtgui_event_timer_t event;
    timer = (rtgui_timer_t *)parameter;

    if (!(timer->state == RTGUI_TIMER_ST_RUNNING))
        return;
    /*
    * Note: event_timer can not use RTGUI_EVENT_TIMER_INIT to init, for there is no
    * thread context
    */
    event.parent.type = RTGUI_EVENT_TIMER;
    event.parent.sender = RT_NULL;

    event.timer = timer;
    timer->pending_cnt++;

    rtgui_send(timer->app, &(event.parent), sizeof(rtgui_event_timer_t));
}

rtgui_timer_t *rtgui_timer_create(rt_int32_t time, rt_int32_t flag, rtgui_timeout_func timeout, void *parameter)
{
    rtgui_timer_t *timer;

    timer = (rtgui_timer_t *) rtgui_malloc(sizeof(rtgui_timer_t));
    timer->app = rtgui_app_self();
    timer->timeout = timeout;
    timer->pending_cnt = 0;
    timer->state = RTGUI_TIMER_ST_INIT;
    timer->user_data = parameter;

    /* init rt-thread timer */
    rt_timer_init(&(timer->timer), "rtgui", rtgui_time_out, timer, time, (rt_uint8_t)flag);

    return timer;
}
RTM_EXPORT(rtgui_timer_create);

void rtgui_timer_destory(rtgui_timer_t *timer)
{
    RT_ASSERT(timer != RT_NULL);

    /* stop timer firstly */
    rtgui_timer_stop(timer);
    if (timer->pending_cnt != 0 && timer->app->ref_count != 0)
    {
        timer->state = RTGUI_TIMER_ST_DESTROY_PENDING;
    }
    else
    {
        /* detach rt-thread timer */
        rt_timer_detach(&(timer->timer));
        rtgui_free(timer);
    }
}
RTM_EXPORT(rtgui_timer_destory);

void rtgui_timer_set_timeout(rtgui_timer_t *timer, rt_int32_t time)
{
    RT_ASSERT(timer != RT_NULL);

    /* start rt-thread timer */
    if (timer->state == RTGUI_TIMER_ST_RUNNING)
    {
        rtgui_timer_stop(timer);
        rt_timer_control(&timer->timer, RT_TIMER_CTRL_SET_TIME, &time);
        rtgui_timer_start(timer);
    }
    else
    {
        rt_timer_control(&timer->timer, RT_TIMER_CTRL_SET_TIME, &time);
    }
}
RTM_EXPORT(rtgui_timer_set_timeout);

void rtgui_timer_start(rtgui_timer_t *timer)
{
    RT_ASSERT(timer != RT_NULL);

    /* start rt-thread timer */
    timer->state = RTGUI_TIMER_ST_RUNNING;
    rt_timer_start(&(timer->timer));
}
RTM_EXPORT(rtgui_timer_start);

void rtgui_timer_stop(rtgui_timer_t *timer)
{
    RT_ASSERT(timer != RT_NULL);

    /* stop rt-thread timer */
    timer->state = RTGUI_TIMER_ST_INIT;
    rt_timer_stop(&(timer->timer));
}
RTM_EXPORT(rtgui_timer_stop);

/************************************************************************/
/* RTGUI Memory Management                                              */
/************************************************************************/
#ifdef RTGUI_MEM_TRACE
struct rtgui_mem_info
{
    rt_uint32_t allocated_size;
    rt_uint32_t max_allocated;
};
struct rtgui_mem_info mem_info;

#define MEMTRACE_MAX        4096
#define MEMTRACE_HASH_SIZE  256

struct rti_memtrace_item
{
    void       *mb_ptr;     /* memory block pointer */
    rt_uint32_t mb_len;     /* memory block length */

    struct rti_memtrace_item *next;
};
struct rti_memtrace_item trace_list[MEMTRACE_MAX];
struct rti_memtrace_item *item_hash[MEMTRACE_HASH_SIZE];
struct rti_memtrace_item *item_free;

rt_bool_t rti_memtrace_inited = 0;
void rti_memtrace_init()
{
    struct rti_memtrace_item *item;
    rt_uint32_t index;

    rt_memset(trace_list, 0, sizeof(trace_list));
    rt_memset(item_hash, 0, sizeof(item_hash));

    item_free = &trace_list[0];
    item = &trace_list[0];

    for (index = 1; index < MEMTRACE_HASH_SIZE; index ++)
    {
        item->next = &trace_list[index];
        item = item->next;
    }

    item->next = RT_NULL;
}

void rti_malloc_hook(void *ptr, rt_uint32_t len)
{
    rt_uint32_t index;
    struct rti_memtrace_item *item;

    if (item_free == RT_NULL) return;

    mem_info.allocated_size += len;
    if (mem_info.max_allocated < mem_info.allocated_size)
        mem_info.max_allocated = mem_info.allocated_size;

    /* lock context */
    item = item_free;
    item_free = item->next;

    item->mb_ptr = ptr;
    item->mb_len = len;
    item->next   = RT_NULL;

    /* get hash item index */
    index = ((rt_uint32_t)ptr) % MEMTRACE_HASH_SIZE;
    if (item_hash[index] != RT_NULL)
    {
        /* add to list */
        item->next = item_hash[index];
        item_hash[index] = item;
    }
    else
    {
        /* set list header */
        item_hash[index] = item;
    }
    /* unlock context */
}

void rti_free_hook(void *ptr)
{
    rt_uint32_t index;
    struct rti_memtrace_item *item;

    /* get hash item index */
    index = ((rt_uint32_t)ptr) % MEMTRACE_HASH_SIZE;
    if (item_hash[index] != RT_NULL)
    {
        item = item_hash[index];
        if (item->mb_ptr == ptr)
        {
            /* delete item from list */
            item_hash[index] = item->next;
        }
        else
        {
            /* find ptr in list */
            while (item->next != RT_NULL && item->next->mb_ptr != ptr)
                item = item->next;

            /* delete item from list */
            if (item->next != RT_NULL)
            {
                struct rti_memtrace_item *i;

                i = item->next;
                item->next = item->next->next;

                item = i;
            }
            else
            {
                /* not found */
                return;
            }
        }

        /* reduce allocated size */
        mem_info.allocated_size -= item->mb_len;

        /* clear item */
        rt_memset(item, 0, sizeof(struct rti_memtrace_item));

        /* add item to the free list */
        item->next = item_free;
        item_free = item;
    }
}
#endif

//#define DEBUG_MEMLEAK

#undef rtgui_malloc
void *rtgui_malloc(rt_size_t size)
{
    void *ptr;

    ptr = rt_malloc(size);
#ifdef RTGUI_MEM_TRACE
    if (rti_memtrace_inited == 0)
    {
        rti_memtrace_init();
        rti_memtrace_inited = 1;
    }

    if (ptr != RT_NULL)
        rti_malloc_hook(ptr, size);
#endif

#ifdef DEBUG_MEMLEAK
    rt_kprintf("alloc %p (%d) on %p %.*s\n",
               ptr, size, __builtin_return_address(0),
               RT_NAME_MAX, rt_thread_self()->name);
#endif

    return ptr;
}
RTM_EXPORT(rtgui_malloc);

#undef rtgui_realloc
void *rtgui_realloc(void *ptr, rt_size_t size)
{
    void *new_ptr;

#ifdef RTGUI_MEM_TRACE
    new_ptr = rtgui_malloc(size);
    if ((new_ptr != RT_NULL) && (ptr != RT_NULL))
    {
        rt_memcpy(new_ptr, ptr, size);
        rtgui_free(ptr);
    }
#else
    new_ptr = rt_realloc(ptr, size);
#endif

#ifdef DEBUG_MEMLEAK
    rt_kprintf("realloc %p to %p (%d) on %p %*.s\n",
               ptr, new_ptr, size, __builtin_return_address(0),
               RT_NAME_MAX, rt_thread_self()->name);
#endif

    return new_ptr;
}
RTM_EXPORT(rtgui_realloc);

#undef rtgui_free
void rtgui_free(void *ptr)
{
#ifdef DEBUG_MEMLEAK
    rt_kprintf("dealloc %p on %p\n",
               ptr, __builtin_return_address(0));
#endif
#ifdef RTGUI_MEM_TRACE
    if (ptr != RT_NULL)
        rti_free_hook(ptr);
#endif

    rt_free(ptr);
}
RTM_EXPORT(rtgui_free);

#if defined(RTGUI_MEM_TRACE) && defined(RT_USING_FINSH)
#include <finsh.h>
void list_guimem(void)
{
    rt_kprintf("Current Used: %d, Maximal Used: %d\n", mem_info.allocated_size, mem_info.max_allocated);
}
FINSH_FUNCTION_EXPORT(list_guimem, display memory information);
#endif

/************************************************************************/
/* RTGUI Event Dump                                                     */
/************************************************************************/

// #define RTGUI_EVENT_DEBUG

#ifdef RTGUI_EVENT_DEBUG
const char *rtgui_event_string[] =
{
    /* application event */
    "APP_CREATE",           /* create an application */
    "APP_DESTROY",          /* destroy an application */
    "APP_ACTIVATE",         /* activate an application */

    /* window event */
    "WIN_CREATE",           /* create a window  */
    "WIN_DESTROY",          /* destroy a window     */
    "WIN_SHOW",             /* show a window        */
    "WIN_HIDE",             /* hide a window        */
    "WIN_ACTIVATE",         /* activate a window    */
    "WIN_DEACTIVATE",       /* deactivate a window  */
    "WIN_CLOSE",            /* close a window       */
    "WIN_MOVE",             /* move a window        */
    "WIN_RESIZE",           /* resize a window      */
    "WIN_MODAL_ENTER",          /* a window modals      */

    "SET_WM",               /* set window manager   */

    "UPDATE_BEGIN",         /* begin of update rect */
    "UPDATE_END",           /* end of update rect   */
    "MONITOR_ADD",          /* add a monitor rect   */
    "MONITOR_REMOVE",       /* remove a monitor rect*/
    "SHOW",                 /* the widget is going to be shown */
    "HIDE",                 /* the widget is going to be hidden */
    "PAINT",                /* paint on screen      */
    "TIMER",                /* timer                */
    "UPDATE_TOPLVL",        /* update toplevel      */

	"VPAINT_REQ", 			/* virtual paint request */

    /* clip rect information */
    "CLIP_INFO",            /* clip rect info       */

    /* mouse and keyboard event */
    "MOUSE_MOTION",         /* mouse motion */
    "MOUSE_BUTTON",         /* mouse button info    */
    "KBD",                  /* keyboard info        */
    "TOUCH",                /* touch info           */
	"GESTURE", 				/* gesture              */

    "FOCUSED",              /* widget got focuse    */
    "SCROLLED",             /* scroll bar scrolled  */
    "RESIZE",               /* widget resize        */
    "SELECTED",             /* widget selected      */
    "UNSELECTED",           /* widget unselected    */
    "MV_MODEL",             /* modal chaned in MV   */
    "BUS_NOTIFY_EVENT",
};

#define DBG_MSG(x)  rt_kprintf x

static void rtgui_event_dump(struct rtgui_app* app, rtgui_event_t *event)
{
    char *sender = "(unknown)";

    if ((event->type == RTGUI_EVENT_TIMER) ||
            (event->type == RTGUI_EVENT_UPDATE_BEGIN) ||
            (event->type == RTGUI_EVENT_MOUSE_MOTION) ||
            (event->type == RTGUI_EVENT_UPDATE_END))
    {
        /* don't dump timer event */
        return ;
    }

    if (event->sender != RT_NULL)
        sender = (char*)event->sender->name;

    if (event->type >= RTGUI_EVENT_COMMAND)
    {
        rt_kprintf("%s -- USER COMMAND EVENT --> %s \n", sender, app->name);
        return ;
    }
    else
    {
        rt_kprintf("%s -- %s --> %s ", sender, rtgui_event_string[event->type], app->name);
    }

    switch (event->type)
    {
    case RTGUI_EVENT_APP_CREATE:
    case RTGUI_EVENT_APP_DESTROY:
    case RTGUI_EVENT_APP_ACTIVATE:
    {
        struct rtgui_event_application *eapp = (struct rtgui_event_application *)event;

        rt_kprintf("app: %s", eapp->app->name);
    }
    break;

    case RTGUI_EVENT_PAINT:
    {
        struct rtgui_event_paint *paint = (struct rtgui_event_paint *)event;

        if (paint->wid != RT_NULL)
            rt_kprintf("win: %s", paint->wid->title);
    }
    break;

    case RTGUI_EVENT_KBD:
    {
        struct rtgui_event_kbd *ekbd = (struct rtgui_event_kbd *) event;
        if (ekbd->wid != RT_NULL)
            rt_kprintf("win: %s", ekbd->wid->title);
        if (RTGUI_KBD_IS_UP(ekbd)) rt_kprintf(", up");
        else rt_kprintf(", down");
    }
    break;

    case RTGUI_EVENT_CLIP_INFO:
    {
        struct rtgui_event_clip_info *info = (struct rtgui_event_clip_info *)event;

        if (info->wid != RT_NULL)
            rt_kprintf("win: %s", info->wid->title);
    }
    break;

    case RTGUI_EVENT_WIN_CREATE:
    {
        struct rtgui_event_win_create *create = (struct rtgui_event_win_create *)event;

        rt_kprintf(" win: %s at (x1:%d, y1:%d, x2:%d, y2:%d), addr: %p",
                   create->wid->title,
                   RTGUI_WIDGET(create->wid)->extent.x1,
                   RTGUI_WIDGET(create->wid)->extent.y1,
                   RTGUI_WIDGET(create->wid)->extent.x2,
                   RTGUI_WIDGET(create->wid)->extent.y2,
                   create->wid
                  );
    }
    break;

    case RTGUI_EVENT_UPDATE_END:
    {
        struct rtgui_event_update_end *update_end = (struct rtgui_event_update_end *)event;
        rt_kprintf("(x:%d, y1:%d, x2:%d, y2:%d)", update_end->rect.x1,
                   update_end->rect.y1,
                   update_end->rect.x2,
                   update_end->rect.y2);
    }
    break;

    case RTGUI_EVENT_WIN_ACTIVATE:
    case RTGUI_EVENT_WIN_DEACTIVATE:
    case RTGUI_EVENT_WIN_SHOW:
    case RTGUI_EVENT_WIN_HIDE:
    case RTGUI_EVENT_WIN_MODAL_ENTER:
    {
        struct rtgui_event_win *win = (struct rtgui_event_win *)event;

        if (win->wid != RT_NULL)
            rt_kprintf("win: %s", win->wid->title);
    }
    break;

    case RTGUI_EVENT_WIN_MOVE:
    {
        struct rtgui_event_win_move *win = (struct rtgui_event_win_move *)event;

        if (win->wid != RT_NULL)
        {
            rt_kprintf("win: %s", win->wid->title);
            rt_kprintf(" to (x:%d, y:%d)", win->x, win->y);
        }
    }
    break;

    case RTGUI_EVENT_WIN_RESIZE:
    {
        struct rtgui_event_win_resize *win = (struct rtgui_event_win_resize *)event;

        if (win->wid != RT_NULL)
        {
            rt_kprintf("win: %s, rect(x1:%d, y1:%d, x2:%d, y2:%d)", win->wid->title,
                       RTGUI_WIDGET(win->wid)->extent.x1,
                       RTGUI_WIDGET(win->wid)->extent.y1,
                       RTGUI_WIDGET(win->wid)->extent.x2,
                       RTGUI_WIDGET(win->wid)->extent.y2);
        }
    }
    break;

    case RTGUI_EVENT_MOUSE_BUTTON:
    case RTGUI_EVENT_MOUSE_MOTION:
    {
        struct rtgui_event_mouse *mouse = (struct rtgui_event_mouse *)event;

        if (mouse->button & RTGUI_MOUSE_BUTTON_LEFT) rt_kprintf("left ");
        else rt_kprintf("right ");

        if (mouse->button & RTGUI_MOUSE_BUTTON_DOWN) rt_kprintf("down ");
        else rt_kprintf("up ");

        if (mouse->wid != RT_NULL)
            rt_kprintf("win: %s at (%d, %d)", mouse->wid->title,
                       mouse->x, mouse->y);
        else
            rt_kprintf("(%d, %d)", mouse->x, mouse->y);
    }
    break;

    case RTGUI_EVENT_MONITOR_ADD:
    {
        struct rtgui_event_monitor *monitor = (struct rtgui_event_monitor *)event;
        if (monitor->wid != RT_NULL)
        {
            rt_kprintf("win: %s, the rect is:(%d, %d) - (%d, %d)", monitor->wid->title,
                       monitor->rect.x1, monitor->rect.y1,
                       monitor->rect.x2, monitor->rect.y2);
        }
    }
    break;

    default:
    break;
    }

    rt_kprintf("\n");
}
#else
#define DBG_MSG(x)
#define rtgui_event_dump(app, event)
#endif

/************************************************************************/
/* RTGUI IPC APIs                                                       */
/************************************************************************/
rt_err_t rtgui_send(struct rtgui_app* app, rtgui_event_t *event, rt_size_t event_size)
{
    rt_err_t result;

    RT_ASSERT(app != RT_NULL);
    RT_ASSERT(event != RT_NULL);
    RT_ASSERT(event_size != 0);

    rtgui_event_dump(app, event);

    result = rt_mq_send(app->mq, event, event_size);
    if (result != RT_EOK)
    {
        if (event->type != RTGUI_EVENT_TIMER)
            rt_kprintf("send event to %s failed\n", app->name);
    }

    return result;
}
RTM_EXPORT(rtgui_send);

rt_err_t rtgui_send_urgent(struct rtgui_app* app, rtgui_event_t *event, rt_size_t event_size)
{
    rt_err_t result;

    RT_ASSERT(app != RT_NULL);
    RT_ASSERT(event != RT_NULL);
    RT_ASSERT(event_size != 0);

    rtgui_event_dump(app, event);

    result = rt_mq_urgent(app->mq, event, event_size);
    if (result != RT_EOK)
        rt_kprintf("send ergent event to %s failed\n", app->name);

    return result;
}
RTM_EXPORT(rtgui_send_urgent);

rt_err_t rtgui_send_sync(struct rtgui_app* app, rtgui_event_t *event, rt_size_t event_size)
{
    rt_err_t r;
    rt_int32_t ack_buffer, ack_status;
    struct rt_mailbox ack_mb;

    RT_ASSERT(app != RT_NULL);
    RT_ASSERT(event != RT_NULL);
    RT_ASSERT(event_size != 0);

    rtgui_event_dump(app, event);

    /* init ack mailbox */
    r = rt_mb_init(&ack_mb, "ack", &ack_buffer, 1, 0);
    if (r != RT_EOK)
        goto __return;

    event->ack = &ack_mb;
    r = rt_mq_send(app->mq, event, event_size);
    if (r != RT_EOK)
    {
        rt_kprintf("send sync event failed\n");
        goto __return;
    }

    r = rt_mb_recv(&ack_mb, (rt_uint32_t *)&ack_status, RT_WAITING_FOREVER);
    if (r != RT_EOK)
        goto __return;

    if (ack_status != RTGUI_STATUS_OK)
        r = -RT_ERROR;
    else
        r = RT_EOK;

__return:
    /* fini ack mailbox */
    rt_mb_detach(&ack_mb);
    return r;
}
RTM_EXPORT(rtgui_send_sync);

rt_err_t rtgui_ack(rtgui_event_t *event, rt_int32_t status)
{
    RT_ASSERT(event != RT_NULL);
    RT_ASSERT(event->ack != RT_NULL);

    rt_mb_send(event->ack, status);

    return RT_EOK;
}
RTM_EXPORT(rtgui_ack);

rt_err_t rtgui_recv(rtgui_event_t *event, rt_size_t event_size, rt_int32_t timeout)
{
    struct rtgui_app *app;
    rt_err_t r;

    RT_ASSERT(event != RT_NULL);
    RT_ASSERT(event_size != 0);

    app = (struct rtgui_app *)(rt_thread_self()->user_data);
    if (app == RT_NULL) return -RT_ERROR;

    r = rt_mq_recv(app->mq, event, event_size, timeout);

    return r;
}
RTM_EXPORT(rtgui_recv);

rt_err_t rtgui_recv_filter(rt_uint32_t type, rtgui_event_t *event, rt_size_t event_size)
{
	rtgui_event_t *e;
    struct rtgui_app *app;

    RT_ASSERT(event != RT_NULL);
    RT_ASSERT(event_size != 0);

    app = (struct rtgui_app *)(rt_thread_self()->user_data);
    if (app == RT_NULL)
        return -RT_ERROR;

	e = (rtgui_event_t*)&app->event_buffer[0];
    while (rt_mq_recv(app->mq, e, sizeof(union rtgui_event_generic), RT_WAITING_FOREVER) == RT_EOK)
    {
        if (e->type == type)
        {
            rt_memcpy(event, e, event_size);
            return RT_EOK;
        }
        else
        {
            if (RTGUI_OBJECT(app)->event_handler != RT_NULL)
            {
                RTGUI_OBJECT(app)->event_handler(RTGUI_OBJECT(app), e);
            }
        }
    }

    return -RT_ERROR;
}
RTM_EXPORT(rtgui_recv_filter);

void rtgui_set_mainwin_rect(struct rtgui_rect *rect)
{
    _mainwin_rect = *rect;
}
RTM_EXPORT(rtgui_set_mainwin_rect);

void rtgui_get_mainwin_rect(struct rtgui_rect *rect)
{
    *rect = _mainwin_rect;
}
RTM_EXPORT(rtgui_get_mainwin_rect);

void rtgui_get_screen_rect(struct rtgui_rect *rect)
{
    rtgui_graphic_driver_get_rect(rtgui_graphic_driver_get_default(), rect);
}
RTM_EXPORT(rtgui_get_screen_rect);

void rtgui_screen_lock(rt_int32_t timeout)
{
    rt_mutex_take(&_screen_lock, timeout);
}
RTM_EXPORT(rtgui_screen_lock);

void rtgui_screen_unlock(void)
{
    rt_mutex_release(&_screen_lock);
}
RTM_EXPORT(rtgui_screen_unlock);

int rtgui_screen_lock_freeze(void)
{
	int hold = 0;

	if (_screen_lock.owner == rt_thread_self())
	{
		int index;

		index = hold = _screen_lock.hold;
		while (index --) rt_mutex_release(&_screen_lock);
	}

	return hold;
}
RTM_EXPORT(rtgui_screen_lock_freeze);

void rtgui_screen_lock_thaw(int value)
{
	while (value--) rt_mutex_take(&_screen_lock, RT_WAITING_FOREVER);
}
RTM_EXPORT(rtgui_screen_lock_thaw);

