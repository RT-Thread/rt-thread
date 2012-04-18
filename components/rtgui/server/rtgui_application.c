/*
 * File      : rtgui_application.c
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
 */

#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_application.h>
#include <rtgui/widgets/window.h>

#ifdef _WIN32
#define RTGUI_EVENT_DEBUG
#endif

#ifdef RTGUI_EVENT_DEBUG
const char *event_string[] =
{
	/* window event */
	"WIN_CREATE",			/* create a window 	*/
	"WIN_DESTROY",			/* destroy a window 	*/
	"WIN_SHOW",				/* show a window 		*/
	"WIN_HIDE",				/* hide a window 		*/
	"WIN_ACTIVATE", 		/* activate a window 	*/
	"WIN_DEACTIVATE",		/* deactivate a window 	*/
	"WIN_CLOSE",			/* close a window 		*/
	"WIN_MOVE",				/* move a window 		*/
	"WIN_RESIZE", 			/* resize a window 		*/
	"WIN_MODAL_ENTER", 			/* a window modals		*/

	"SET_WM", 				/* set window manager	*/

	"UPDATE_BEGIN",			/* begin of update rect */
	"UPDATE_END",			/* end of update rect	*/
	"MONITOR_ADD",			/* add a monitor rect 	*/
	"MONITOR_REMOVE", 		/* remove a monitor rect*/
	"PAINT",				/* paint on screen 		*/
	"TIMER",				/* timer 				*/

	/* clip rect information */
	"CLIP_INFO",			/* clip rect info		*/

	/* mouse and keyboard event */
	"MOUSE_MOTION",			/* mouse motion */
	"MOUSE_BUTTON",			/* mouse button info 	*/
	"KBD",					/* keyboard info		*/

	/* user command event */
	"COMMAND",				/* user command 		*/

	/* request's status event */
	"STATUS",				/* request result 		*/
	"SCROLLED",           	/* scroll bar scrolled  */
	"RESIZE",				/* widget resize 		*/
};

#define DBG_MSG(x)	rt_kprintf x

static void rtgui_event_dump(rt_thread_t tid, rtgui_event_t* event)
{
	char* sender = "(unknown)";

	if ((event->type == RTGUI_EVENT_TIMER) ||
		(event->type == RTGUI_EVENT_UPDATE_BEGIN) ||
		(event->type == RTGUI_EVENT_MOUSE_MOTION) ||
		(event->type == RTGUI_EVENT_UPDATE_END))
	{
		/* don't dump timer event */
		return ;
	}

	if (event->sender != RT_NULL)
		sender = event->sender->name;

	rt_kprintf("%s -- %s --> %s ", sender, event_string[event->type], tid->name);
	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		{
			struct rtgui_event_paint *paint = (struct rtgui_event_paint *)event;

			if(paint->wid != RT_NULL)
				rt_kprintf("win: %s", paint->wid->title);
		}
		break;

	case RTGUI_EVENT_KBD:
		{
			struct rtgui_event_kbd *ekbd = (struct rtgui_event_kbd*) event;
			if (ekbd->wid != RT_NULL)
				rt_kprintf("win: %s", ekbd->wid->title);
			if (RTGUI_KBD_IS_UP(ekbd)) rt_kprintf(", up");
			else rt_kprintf(", down");
		}
		break;

	case RTGUI_EVENT_CLIP_INFO:
		{
			struct rtgui_event_clip_info *info = (struct rtgui_event_clip_info *)event;

			if(info->wid != RT_NULL)
				rt_kprintf("win: %s", info->wid->title);
		}
		break;

	case RTGUI_EVENT_WIN_CREATE:
		{
			struct rtgui_event_win_create *create = (struct rtgui_event_win_create*)event;

			rt_kprintf(" win: %s at (x1:%d, y1:%d, x2:%d, y2:%d), addr: %p",
#ifdef RTGUI_USING_SMALL_SIZE
				create->wid->title,
				RTGUI_WIDGET(create->wid)->extent.x1,
				RTGUI_WIDGET(create->wid)->extent.y1,
				RTGUI_WIDGET(create->wid)->extent.x2,
				RTGUI_WIDGET(create->wid)->extent.y2,
#else
				create->title,
				create->extent.x1,
				create->extent.y1,
				create->extent.x2,
				create->extent.y2,
#endif
				create->wid
                );
		}
		break;

	case RTGUI_EVENT_UPDATE_END:
		{
			struct rtgui_event_update_end* update_end = (struct rtgui_event_update_end*)event;
			rt_kprintf("(x:%d, y1:%d, x2:%d, y2:%d)", update_end->rect.x1,
				update_end->rect.y1,
				update_end->rect.x2,
				update_end->rect.y2);
		}
		break;

	case RTGUI_EVENT_WIN_ACTIVATE:
	case RTGUI_EVENT_WIN_DEACTIVATE:
	case RTGUI_EVENT_WIN_SHOW:
	case RTGUI_EVENT_WIN_MODAL_ENTER:
		{
			struct rtgui_event_win *win = (struct rtgui_event_win *)event;

			if(win->wid != RT_NULL)
				rt_kprintf("win: %s", win->wid->title);
		}
		break;

	case RTGUI_EVENT_WIN_MOVE:
		{
			struct rtgui_event_win_move *win = (struct rtgui_event_win_move *)event;

			if(win->wid != RT_NULL)
			{
				rt_kprintf("win: %s", win->wid->title);
				rt_kprintf(" to (x:%d, y:%d)", win->x, win->y);
			}
		}
		break;

	case RTGUI_EVENT_WIN_RESIZE:
		{
			struct rtgui_event_win_resize* win = (struct rtgui_event_win_resize *)event;

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
			struct rtgui_event_mouse *mouse = (struct rtgui_event_mouse*)event;

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
			struct rtgui_event_monitor *monitor = (struct rtgui_event_monitor*)event;
			if (monitor->wid != RT_NULL)
			{
				rt_kprintf("win: %s, the rect is:(%d, %d) - (%d, %d)", monitor->wid->title,
					monitor->rect.x1, monitor->rect.y1,
					monitor->rect.x2, monitor->rect.y2);
			}
		}
		break;
	}

	rt_kprintf("\n");
}
#else
#define DBG_MSG(x)
#define rtgui_event_dump(tid, event)
#endif

rt_bool_t rtgui_application_event_handler(struct rtgui_object* obj, rtgui_event_t* event);

static void _rtgui_application_constructor(struct rtgui_application *app)
{
	/* set event handler */
	rtgui_object_set_event_handler(RTGUI_OBJECT(app),
			                       rtgui_application_event_handler);

	app->name           = RT_NULL;
	/* set EXITED so we can destroy an application that just created */
	app->state_flag     = RTGUI_APPLICATION_FLAG_EXITED;
	app->ref_count      = 0;
	app->exit_code      = 0;
	app->tid            = RT_NULL;
	app->server         = RT_NULL;
	app->mq             = RT_NULL;
	app->modal_object   = RT_NULL;
	app->on_idle        = RT_NULL;
}

static void _rtgui_application_destructor(struct rtgui_application *app)
{
	RT_ASSERT(app != RT_NULL);

	rt_free(app->name);
	app->name = RT_NULL;
}

DEFINE_CLASS_TYPE(application, "application",
	RTGUI_OBJECT_TYPE,
	_rtgui_application_constructor,
	_rtgui_application_destructor,
	sizeof(struct rtgui_application));

struct rtgui_application* rtgui_application_create(
        rt_thread_t tid,
        const char *myname)
{
	struct rtgui_application *app;

	RT_ASSERT(tid != RT_NULL);
	RT_ASSERT(myname != RT_NULL);

	/* create application */
	app = RTGUI_APPLICATION(rtgui_object_create(RTGUI_APPLICATION_TYPE));
	if (app == RT_NULL)
		return RT_NULL;

	DBG_MSG(("register a rtgui application(%s) on thread %s\n", myname, tid->name));

	app->tid     = tid;
	/* set user thread */
	tid->user_data = (rt_uint32_t)app;

	app->mq = rt_mq_create("rtgui", sizeof(union rtgui_event_generic), 32, RT_IPC_FLAG_FIFO);
	if (app->mq == RT_NULL)
	{
		rt_kprintf("mq err\n");
		goto __mq_err;
	}

	/* set application title */
	app->name = (unsigned char*)rt_strdup((char*)myname);
	if (app->name != RT_NULL)
		return app;

__mq_err:
	rtgui_object_destroy(RTGUI_OBJECT(app));
	tid->user_data = 0;
	return RT_NULL;
}

#define _rtgui_application_check(app) \
do { \
    RT_ASSERT(app != RT_NULL); \
    RT_ASSERT(app->tid != RT_NULL); \
    RT_ASSERT(app->tid->user_data != 0); \
    RT_ASSERT(app->mq != RT_NULL); \
} while (0)

void rtgui_application_destroy(struct rtgui_application *app)
{
    _rtgui_application_check(app);

	if (!(app->state_flag & RTGUI_APPLICATION_FLAG_EXITED))
	{
		rt_kprintf("cannot destroy a running application: %s.\n",
				   app->name);
		return;
	}

	app->tid->user_data = 0;
	rt_mq_delete(app->mq);
	rtgui_object_destroy(RTGUI_OBJECT(app));
}

struct rtgui_application* rtgui_application_self(void)
{
	struct rtgui_application *app;
	rt_thread_t self;

	/* get current thread */
	self = rt_thread_self();
	app = (struct rtgui_application*)(self->user_data);

	return app;
}

void rtgui_application_set_onidle(rtgui_idle_func onidle)
{
	struct rtgui_application *app;

	app = rtgui_application_self();
	if (app != RT_NULL)
		app->on_idle = onidle;
}

rtgui_idle_func rtgui_application_get_onidle(void)
{
	struct rtgui_application *app;

	app = rtgui_application_self();
	if (app != RT_NULL)
		return app->on_idle;
	else
		return RT_NULL;
}

extern rt_thread_t rt_thread_find(char* name);
rt_thread_t rtgui_application_get_server(void)
{
	return rt_thread_find("rtgui");
}

rt_err_t rtgui_application_send(rt_thread_t tid, rtgui_event_t* event, rt_size_t event_size)
{
	rt_err_t result;
	struct rtgui_application *app;

	RT_ASSERT(tid != RT_NULL);
	RT_ASSERT(event != RT_NULL);
	RT_ASSERT(event_size != 0);

	rtgui_event_dump(tid, event);

	/* find struct rtgui_application */
	app = (struct rtgui_application*) (tid->user_data);
	if (app == RT_NULL)
		return -RT_ERROR;

	result = rt_mq_send(app->mq, event, event_size);
	if (result != RT_EOK)
	{
		if (event->type != RTGUI_EVENT_TIMER)
			rt_kprintf("send event to %s failed\n", app->tid->name);
	}

	return result;
}

rt_err_t rtgui_application_send_urgent(rt_thread_t tid, rtgui_event_t* event, rt_size_t event_size)
{
	rt_err_t result;
	struct rtgui_application *app;

	RT_ASSERT(tid != RT_NULL);
	RT_ASSERT(event != RT_NULL);
	RT_ASSERT(event_size != 0);

	rtgui_event_dump(tid, event);

	/* find rtgui_application */
	app = (struct rtgui_application*) (tid->user_data);
	if (app == RT_NULL)
		return -RT_ERROR;

	result = rt_mq_urgent(app->mq, event, event_size);
	if (result != RT_EOK)
		rt_kprintf("send ergent event failed\n");

	return result;
}

rt_err_t rtgui_application_send_sync(rt_thread_t tid, rtgui_event_t* event, rt_size_t event_size)
{
	rt_err_t r;
	struct rtgui_application *app;
	rt_int32_t ack_buffer, ack_status;
	struct rt_mailbox ack_mb;

	RT_ASSERT(tid != RT_NULL);
	RT_ASSERT(event != RT_NULL);
	RT_ASSERT(event_size != 0);

	rtgui_event_dump(tid, event);

	/* init ack mailbox */
	r = rt_mb_init(&ack_mb, "ack", &ack_buffer, 1, 0);
	if (r!= RT_EOK)
		goto __return;

	app = (struct rtgui_application*) (tid->user_data);
	if (app == RT_NULL)
	{
		r = -RT_ERROR;
		goto __return;
	}

	event->ack = &ack_mb;
	r = rt_mq_send(app->mq, event, event_size);
	if (r != RT_EOK)
	{
		rt_kprintf("send sync event failed\n");
		goto __return;
	}

	r = rt_mb_recv(&ack_mb, (rt_uint32_t*)&ack_status, RT_WAITING_FOREVER);
	if (r!= RT_EOK)
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

rt_err_t rtgui_application_ack(rtgui_event_t* event, rt_int32_t status)
{
	RT_ASSERT(event != RT_NULL);
	RT_ASSERT(event->ack != RT_NULL);

	rt_mb_send(event->ack, status);

	return RT_EOK;
}

rt_err_t rtgui_application_recv(rtgui_event_t* event, rt_size_t event_size)
{
	struct rtgui_application* app;
	rt_err_t r;

	RT_ASSERT(event != RT_NULL);
	RT_ASSERT(event_size != 0);

	app = (struct rtgui_application*) (rt_thread_self()->user_data);
	if (app == RT_NULL)
		return -RT_ERROR;

	r = rt_mq_recv(app->mq, event, event_size, RT_WAITING_FOREVER);

	return r;
}

rt_err_t rtgui_application_recv_nosuspend(rtgui_event_t* event, rt_size_t event_size)
{
	struct rtgui_application *app;
	rt_err_t r;

	RT_ASSERT(event != RT_NULL);
	RT_ASSERT(event != 0);

	app = (struct rtgui_application*) (rt_thread_self()->user_data);
	if (app == RT_NULL)
		return -RT_ERROR;

	r = rt_mq_recv(app->mq, event, event_size, 0);

	return r;
}

rt_err_t rtgui_application_recv_filter(rt_uint32_t type, rtgui_event_t* event, rt_size_t event_size)
{
	struct rtgui_application *app;

	RT_ASSERT(event != RT_NULL);
	RT_ASSERT(event_size != 0);

	app = (struct rtgui_application*) (rt_thread_self()->user_data);
	if (app == RT_NULL)
		return -RT_ERROR;

	while (rt_mq_recv(app->mq, event, event_size, RT_WAITING_FOREVER) == RT_EOK)
	{
		if (event->type == type)
		{
			return RT_EOK;
		}
		else
		{
			if (RTGUI_OBJECT(app)->event_handler != RT_NULL)
			{
				RTGUI_OBJECT(app)->event_handler(RTGUI_OBJECT(app), event);
			}
		}
	}

	return -RT_ERROR;
}

rt_inline rt_bool_t _rtgui_application_dest_handle(
		struct rtgui_application *app,
		struct rtgui_event *event)
{
	struct rtgui_event_win* wevent = (struct rtgui_event_win*)event;

	struct rtgui_object* dest_object = RTGUI_OBJECT(wevent->wid);

	if (dest_object != RT_NULL)
	{
		if (dest_object->event_handler != RT_NULL)
			return dest_object->event_handler(RTGUI_OBJECT(dest_object), event);
		else
			return RT_FALSE;
	}
	else
	{
		rt_kprintf("RTGUI ERROR:server sent a event(%d) without wid\n", event->type);
		return RT_FALSE;
	}
}

rt_bool_t rtgui_application_event_handler(struct rtgui_object* object, rtgui_event_t* event)
{
	struct rtgui_application* app;

	RT_ASSERT(object != RT_NULL);
	RT_ASSERT(event != RT_NULL);

	app = RTGUI_APPLICATION(object);

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
	case RTGUI_EVENT_CLIP_INFO:
	case RTGUI_EVENT_WIN_ACTIVATE:
	case RTGUI_EVENT_WIN_DEACTIVATE:
	case RTGUI_EVENT_WIN_CLOSE:
	case RTGUI_EVENT_WIN_MOVE:
	case RTGUI_EVENT_KBD:
		_rtgui_application_dest_handle(app, event);
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
	case RTGUI_EVENT_MOUSE_MOTION:
		{
			struct rtgui_event_win* wevent = (struct rtgui_event_win*)event;
			struct rtgui_object* dest_object = RTGUI_OBJECT(wevent->wid);

			// FIXME: let application determine the dest_wiget but not in sever
			// so we can combine this handler with above one
			if (app->modal_object != RT_NULL &&
				dest_object != app->modal_object)
			{
//				rt_kprintf("discard event %s that is not sent to modal object\n",
//						   event_string[event->type]);
			}
			else
			{
				_rtgui_application_dest_handle(app, event);
			}
		}
		break;

	case RTGUI_EVENT_TIMER:
		{
			struct rtgui_timer* timer;
			struct rtgui_event_timer* etimer = (struct rtgui_event_timer*) event;

			timer = etimer->timer;
			if (timer->timeout != RT_NULL)
			{
				/* call timeout function */
				timer->timeout(timer, timer->user_data);
			}
		}
		break;

        case RTGUI_EVENT_COMMAND:
                {
                        struct rtgui_event_command *ecmd = (struct rtgui_event_command*)event;

                        if (ecmd->wid != RT_NULL)
                                return _rtgui_application_dest_handle(app, event);
                }

	default:
		return rtgui_object_event_handler(object, event);
	}

	return RT_TRUE;
}

rt_inline void _rtgui_application_event_loop(struct rtgui_application *app)
{
	rt_err_t result;
	rt_uint16_t current_ref;
	struct rtgui_event *event;

	_rtgui_application_check(app);

	/* point to event buffer */
	event = (struct rtgui_event*)app->event_buffer;

	current_ref = ++app->ref_count;

	while (current_ref <= app->ref_count)
	{
		RT_ASSERT(current_ref == app->ref_count);

		if (app->on_idle != RT_NULL)
		{
			result = rtgui_application_recv_nosuspend(event, sizeof(union rtgui_event_generic));
			if (result == RT_EOK)
				RTGUI_OBJECT(app)->event_handler(RTGUI_OBJECT(app), event);
			else if (result == -RT_ETIMEOUT)
				app->on_idle(RTGUI_OBJECT(app), RT_NULL);
		}
		else
		{
			result = rtgui_application_recv(event, sizeof(union rtgui_event_generic));
			if (result == RT_EOK)
				RTGUI_OBJECT(app)->event_handler(RTGUI_OBJECT(app), event);
		}
	}
}

rt_base_t rtgui_application_run(struct rtgui_application *app)
{
	_rtgui_application_check(app);

	app->state_flag &= ~RTGUI_APPLICATION_FLAG_EXITED;

	_rtgui_application_event_loop(app);

	if (app->ref_count == 0)
		app->state_flag |= RTGUI_APPLICATION_FLAG_EXITED;

	return app->exit_code;
}

void rtgui_application_exit(struct rtgui_application* app, rt_uint16_t code)
{
	--app->ref_count;
	app->exit_code = code;
}
