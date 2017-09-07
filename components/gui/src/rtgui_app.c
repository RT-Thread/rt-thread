/*
 * File      : rtgui_app.c
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-01-13     Grissiom     first version(just a prototype of application API)
 * 2012-07-07     Bernard      move the send/recv message to the rtgui_system.c
 */

#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_app.h>
#include <rtgui/widgets/window.h>

static void _rtgui_app_constructor(struct rtgui_app *app)
{
    /* set event handler */
    rtgui_object_set_event_handler(RTGUI_OBJECT(app),
                                   rtgui_app_event_handler);

    app->name           = RT_NULL;
    app->icon           = RT_NULL;
    /* set EXITED so we can destroy an application that just created */
    app->state_flag     = RTGUI_APP_FLAG_EXITED;
    app->ref_count      = 0;
    app->window_cnt     = 0;
    app->exit_code      = 0;
    app->tid            = RT_NULL;
    app->mq             = RT_NULL;
    app->main_object    = RT_NULL;
    app->on_idle        = RT_NULL;
}

static void _rtgui_app_destructor(struct rtgui_app *app)
{
    RT_ASSERT(app != RT_NULL);

    rt_free(app->name);
    app->name = RT_NULL;
}

DEFINE_CLASS_TYPE(application, "application",
                  RTGUI_PARENT_TYPE(object),
                  _rtgui_app_constructor,
                  _rtgui_app_destructor,
                  sizeof(struct rtgui_app));

struct rtgui_app *rtgui_app_create(const char *title)
{
    rt_thread_t tid = rt_thread_self();
    struct rtgui_app *app;
    struct rtgui_app *srv_app;
    struct rtgui_event_application event;
    char mq_name[RT_NAME_MAX];

    RT_ASSERT(tid != RT_NULL);
    RT_ASSERT(title != RT_NULL);

    /* create application */
    app = RTGUI_APP(rtgui_object_create(RTGUI_APP_TYPE));
    if (app == RT_NULL)
        return RT_NULL;

    /* one thread only can create one rtgui application */
    RT_ASSERT(tid->user_data == 0);
    app->tid = tid;

    rt_snprintf(mq_name, RT_NAME_MAX, "g%s", title);
    app->mq = rt_mq_create(mq_name,
                           sizeof(union rtgui_event_generic), 64,
                           RT_IPC_FLAG_FIFO);
    if (app->mq == RT_NULL)
    {
        rt_kprintf("create msgq failed.\n");
        goto __mq_err;
    }

    /* set application title */
    app->name = (unsigned char *)rt_strdup((char *)title);
    if (app->name == RT_NULL)
        goto __err;

    /* the first app should be the server */
    srv_app = rtgui_get_server();
    if (srv_app == RT_NULL)
    {
        /* set user thread */
        tid->user_data = (rt_uint32_t)app;
        return app;
    }

    RTGUI_EVENT_APP_CREATE_INIT(&event);
    event.app = app;

    /* notify rtgui server to one application has been created */
    if (rtgui_send_sync(srv_app, RTGUI_EVENT(&event), sizeof(event)) == RT_EOK)
    {
        /* set user thread */
        tid->user_data = (rt_uint32_t)app;
        return app;
    }

__err:
__mq_err:
    rtgui_object_destroy(RTGUI_OBJECT(app));
    return RT_NULL;
}
RTM_EXPORT(rtgui_app_create);

#define _rtgui_application_check(app)           \
    do {                                        \
        RT_ASSERT(app != RT_NULL);              \
        RT_ASSERT(app->tid != RT_NULL);         \
        RT_ASSERT(app->tid->user_data != 0);    \
        RT_ASSERT(app->mq != RT_NULL);          \
    } while (0)

void rtgui_app_destroy(struct rtgui_app *app)
{
    struct rtgui_app *srv_app;
    _rtgui_application_check(app);

    if (!(app->state_flag & RTGUI_APP_FLAG_EXITED))
    {
        rt_kprintf("cannot destroy a running application: %s.\n",
                   app->name);
        return;
    }

    /* send a message to notify rtgui server */
    srv_app = rtgui_get_server();
    if (srv_app != rtgui_app_self())
    {
        struct rtgui_event_application event;
        RTGUI_EVENT_APP_DESTROY_INIT(&event);
        event.app = app;

        if (rtgui_send_sync(srv_app, RTGUI_EVENT(&event), sizeof(event)) != RT_EOK)
        {
            rt_kprintf("destroy an application in server failed\n");
            return ;
        }
    }

    app->tid->user_data = 0;
    rt_mq_delete(app->mq);
    rtgui_object_destroy(RTGUI_OBJECT(app));
}
RTM_EXPORT(rtgui_app_destroy);

struct rtgui_app *rtgui_app_self(void)
{
    struct rtgui_app *app;
    rt_thread_t self;

    /* get current thread */
    self = rt_thread_self();
    app = (struct rtgui_app *)(self->user_data);

    return app;
}
RTM_EXPORT(rtgui_app_self);

void rtgui_app_set_onidle(struct rtgui_app *app, rtgui_idle_func_t onidle)
{
    _rtgui_application_check(app);
    app->on_idle = onidle;
}
RTM_EXPORT(rtgui_app_set_onidle);

rtgui_idle_func_t rtgui_app_get_onidle(struct rtgui_app *app)
{

    _rtgui_application_check(app);
    return app->on_idle;
}
RTM_EXPORT(rtgui_app_get_onidle);

rt_inline rt_bool_t _rtgui_application_dest_handle(
    struct rtgui_app *app,
    struct rtgui_event *event)
{
    struct rtgui_event_win *wevent = (struct rtgui_event_win *)event;
    struct rtgui_object *dest_object;

    if (wevent->wid == RT_NULL)
        return RT_FALSE;

    /* this window has been closed. */
    if (wevent->wid != RT_NULL && wevent->wid->flag & RTGUI_WIN_FLAG_CLOSED)
        return RT_TRUE;

    /* The dest window may have been destroyed when this event arrived. Check
     * against this condition. NOTE: we cannot use the RTGUI_OBJECT because it
     * may be invalid already. */
    dest_object = (struct rtgui_object*)wevent->wid;
    if ((dest_object->flag & RTGUI_OBJECT_FLAG_VALID) !=
            RTGUI_OBJECT_FLAG_VALID)
    {
        return RT_TRUE;
    }

    dest_object = RTGUI_OBJECT(wevent->wid);
    if (dest_object != RT_NULL)
    {
        if (dest_object->event_handler != RT_NULL)
            return dest_object->event_handler(dest_object, event);
        else
            return RT_FALSE;
    }
    else
    {
        rt_kprintf("RTGUI ERROR:server sent a event(%d) without wid\n", event->type);
        return RT_FALSE;
    }
}

rt_bool_t rtgui_app_event_handler(struct rtgui_object *object, rtgui_event_t *event)
{
    struct rtgui_app *app;

    RT_ASSERT(object != RT_NULL);
    RT_ASSERT(event != RT_NULL);

    app = RTGUI_APP(object);

    switch (event->type)
    {
    case RTGUI_EVENT_PAINT:
    case RTGUI_EVENT_VPAINT_REQ:
    case RTGUI_EVENT_MOUSE_BUTTON:
    case RTGUI_EVENT_MOUSE_MOTION:
    case RTGUI_EVENT_CLIP_INFO:
    case RTGUI_EVENT_WIN_ACTIVATE:
    case RTGUI_EVENT_WIN_DEACTIVATE:
    case RTGUI_EVENT_WIN_CLOSE:
    case RTGUI_EVENT_WIN_MOVE:
    case RTGUI_EVENT_WIN_SHOW:
    case RTGUI_EVENT_WIN_HIDE:
    case RTGUI_EVENT_KBD:
    case RTGUI_EVENT_GESTURE:
        _rtgui_application_dest_handle(app, event);
        break;

    case RTGUI_EVENT_APP_ACTIVATE:
        if (app->main_object != RT_NULL)
        {
            /* Let the polymorphism work. */
            struct rtgui_event_win_show wev;

            RTGUI_EVENT_WIN_SHOW_INIT(&wev);
            wev.wid = (struct rtgui_win*)app->main_object;

            rtgui_object_handle(app->main_object, &wev.parent);
        }
        break;

    case RTGUI_EVENT_APP_DESTROY:
        rtgui_app_exit(app, 0);
        break;

    case RTGUI_EVENT_TIMER:
    {
        struct rtgui_timer *timer;
        struct rtgui_event_timer *etimer = (struct rtgui_event_timer *) event;

        timer = etimer->timer;
        timer->pending_cnt--;
        RT_ASSERT(timer->pending_cnt >= 0);
        if (timer->state == RTGUI_TIMER_ST_DESTROY_PENDING)
        {
            /* Truly destroy the timer when there is no pending event. */
            if (timer->pending_cnt == 0)
                rtgui_timer_destory(timer);
        }
        else if (timer->state == RTGUI_TIMER_ST_RUNNING && timer->timeout != RT_NULL)
        {
            /* call timeout function */
            timer->timeout(timer, timer->user_data);
        }
    }
    break;

    case RTGUI_EVENT_MV_MODEL:
    {
        struct rtgui_event_mv_model *emodel = (struct rtgui_event_mv_model *)event;
        RT_ASSERT(emodel->view);
        return rtgui_object_handle(RTGUI_OBJECT(emodel->view), event);
    }

    case RTGUI_EVENT_COMMAND:
    {
        struct rtgui_event_command *ecmd = (struct rtgui_event_command *)event;

        if (ecmd->wid != RT_NULL)
            return _rtgui_application_dest_handle(app, event);
    }
    default:
        return rtgui_object_event_handler(object, event);
    }

    return RT_TRUE;
}
RTM_EXPORT(rtgui_app_event_handler);

rt_inline void _rtgui_application_event_loop(struct rtgui_app *app)
{
    rt_err_t result;
    rt_uint16_t current_ref;
    struct rtgui_event *event;

    _rtgui_application_check(app);

    /* point to event buffer */
    event = (struct rtgui_event *)app->event_buffer;

    current_ref = ++app->ref_count;
    while (current_ref <= app->ref_count)
    {
        RT_ASSERT(current_ref == app->ref_count);

        if (app->on_idle != RT_NULL)
        {
            result = rtgui_recv(event, sizeof(union rtgui_event_generic), 0);
            if (result == RT_EOK)
                RTGUI_OBJECT(app)->event_handler(RTGUI_OBJECT(app), event);
            else if (result == -RT_ETIMEOUT)
                app->on_idle(RTGUI_OBJECT(app), RT_NULL);
        }
        else
        {
            result = rtgui_recv(event, sizeof(union rtgui_event_generic), RT_WAITING_FOREVER);
            if (result == RT_EOK)
                RTGUI_OBJECT(app)->event_handler(RTGUI_OBJECT(app), event);
        }
    }
}

rt_base_t rtgui_app_run(struct rtgui_app *app)
{
    _rtgui_application_check(app);

    app->state_flag &= ~RTGUI_APP_FLAG_EXITED;

    _rtgui_application_event_loop(app);

    if (app->ref_count == 0)
        app->state_flag |= RTGUI_APP_FLAG_EXITED;

    return app->exit_code;
}
RTM_EXPORT(rtgui_app_run);

void rtgui_app_exit(struct rtgui_app *app, rt_uint16_t code)
{
    if (app->ref_count == 0)
        return;

    --app->ref_count;
    app->exit_code = code;
}
RTM_EXPORT(rtgui_app_exit);

void rtgui_app_activate(struct rtgui_app *app)
{
    struct rtgui_event_application event;

    RTGUI_EVENT_APP_ACTIVATE_INIT(&event);
    event.app = app;

    rtgui_send(app, RTGUI_EVENT(&event), sizeof(struct rtgui_event_application));
}
RTM_EXPORT(rtgui_app_activate);

void rtgui_app_sleep(struct rtgui_app *app, int millisecond)
{
    rt_err_t result;
    rt_uint16_t current_ref;
    struct rtgui_event *event;
	rt_tick_t tick, sleep_tick;
	int delta_tick;

	tick = rt_tick_get();
	millisecond = rt_tick_from_millisecond(millisecond);
	if (millisecond == 0) return;

	sleep_tick = tick + millisecond;
	delta_tick = millisecond;

    /* point to event buffer */
    event = (struct rtgui_event *)app->event_buffer;

    current_ref = ++app->ref_count;
    while (current_ref <= app->ref_count && delta_tick)
    {
        RT_ASSERT(current_ref == app->ref_count);

        if (app->on_idle != RT_NULL)
        {
            result = rtgui_recv(event, sizeof(union rtgui_event_generic), 0);
            if (result == RT_EOK)
                RTGUI_OBJECT(app)->event_handler(RTGUI_OBJECT(app), event);
            else if (result == -RT_ETIMEOUT)
                app->on_idle(RTGUI_OBJECT(app), RT_NULL);
        }
        else
        {
            result = rtgui_recv(event, sizeof(union rtgui_event_generic), sleep_tick - rt_tick_get());
            if (result == RT_EOK)
                RTGUI_OBJECT(app)->event_handler(RTGUI_OBJECT(app), event);
        }

        delta_tick = sleep_tick - rt_tick_get();
    }

	app->ref_count --;
}
RTM_EXPORT(rtgui_app_sleep);

void rtgui_app_close(struct rtgui_app *app)
{
    struct rtgui_event_application event;

    RTGUI_EVENT_APP_DESTROY_INIT(&event);
    event.app = app;

    rtgui_send(app, RTGUI_EVENT(&event), sizeof(struct rtgui_event_application));
}
RTM_EXPORT(rtgui_app_close);

/**
 * set this application as window manager
 */
rt_err_t rtgui_app_set_as_wm(struct rtgui_app *app)
{
    struct rtgui_app *srv_app;
    struct rtgui_event_set_wm event;

    _rtgui_application_check(app);

    srv_app = rtgui_get_server();
    if (srv_app != RT_NULL)
    {
        /* notify rtgui server, this is a window manager */
        RTGUI_EVENT_SET_WM_INIT(&event);
        event.app = app;

        rtgui_send_sync(srv_app, RTGUI_EVENT(&event), sizeof(event));
        return RT_EOK;
    }

    return RT_ERROR;
}
RTM_EXPORT(rtgui_app_set_as_wm);

void rtgui_app_set_main_win(struct rtgui_app *app, struct rtgui_win *win)
{
    _rtgui_application_check(app);
    app->main_object = RTGUI_OBJECT(win);
}
RTM_EXPORT(rtgui_app_set_main_win);

struct rtgui_win *rtgui_app_get_main_win(struct rtgui_app *app)
{
    return RTGUI_WIN(app->main_object);
}
RTM_EXPORT(rtgui_app_get_main_win);

