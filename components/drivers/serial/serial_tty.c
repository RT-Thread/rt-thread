/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-21     Shell        init ver.
 */

#define DBG_TAG "drivers.serial"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <terminal/terminal.h>

#include <sys/ioctl.h>

#define TTY_NAME_PREFIX            "S" /* (S)erial */
#define LWP_TTY_WORKQUEUE_PRIORITY 3

struct serial_tty_context
{
    struct rt_serial_device *parent;
    struct rt_work work;
};

static struct rt_workqueue *_ttyworkq; /* system work queue */

#ifdef RT_USING_COMPONENTS_INIT
struct _tty_pending_registration
{
    rt_slist_t node;
    struct rt_serial_device *serial;
};

static rt_slist_t _tty_pending_registrations =
    RT_SLIST_OBJECT_INIT(_tty_pending_registrations);
static rt_bool_t _tty_flush_done = RT_FALSE;
#endif /* RT_USING_COMPONENTS_INIT */

#ifndef RT_USING_DM
static rt_atomic_t _device_id_counter = 0;

static long get_dec_digits(rt_ubase_t val)
{
    long result = 1;
    while (1)
    {
        if (val < 10)
        {
            return result;
        }
        if (val < 100)
        {
            return result + 1;
        }
        if (val < 1000)
        {
            return result + 2;
        }
        if (val < 10000)
        {
            return result + 3;
        }
        val /= 10000U;
        result += 4;
    }
    return result;
}
#endif

static char *alloc_device_name(struct rt_serial_device *serial)
{
    char *tty_dev_name;
#ifdef RT_USING_DM
    char *serial_name = serial->parent.parent.name;
    /*
     * if RT_USING_DM is defined, the name of the serial device
     * must be obtained using the serial_dev_set_name function,
     * and it should begin with "uart".
     */
    if (!serial_name || rt_strlen(serial_name) < 4 || rt_strncmp(serial_name, "uart", 4))
    {
        return RT_NULL;
    }

    long digits_len = (sizeof(TTY_NAME_PREFIX) - 1)              /* raw prefix */
                      + strlen(serial_name + sizeof("uart") - 1) /* suffix of serial device name*/
                      + 1;                                       /* tailing \0 */

    tty_dev_name = rt_malloc(digits_len);
    if (tty_dev_name)
    {
        rt_sprintf(tty_dev_name, "%s%s", TTY_NAME_PREFIX, serial_name + sizeof("uart") - 1);
    }
#else
    RT_UNUSED(serial);
    unsigned int devid = rt_atomic_add(&_device_id_counter, 1);
    long digits_len = (sizeof(TTY_NAME_PREFIX) - 1) /* raw prefix */
                      + get_dec_digits(devid) + 1;  /* tailing \0 */

    tty_dev_name = rt_malloc(digits_len);
    if (tty_dev_name)
    {
        rt_sprintf(tty_dev_name, "%s%u", TTY_NAME_PREFIX, devid);
    }
#endif
    return tty_dev_name;
}

#ifdef LWP_DEBUG_INIT
static volatile int _early_input = 0;

static void _set_debug(rt_device_t dev, rt_size_t size);
RT_OBJECT_HOOKLIST_DEFINE_NODE(rt_hw_serial_rxind, _set_debug_node, _set_debug);

static void _set_debug(rt_device_t dev, rt_size_t size)
{
    rt_list_remove(&_set_debug_node.list_node);
    _early_input = 1;
}

static void _setup_debug_rxind_hook(void)
{
    rt_hw_serial_rxind_sethook(&_set_debug_node);
}

int lwp_startup_debug_request(void)
{
    return _early_input;
}

#else /* !LWP_DEBUG_INIT */

static void _setup_debug_rxind_hook(void)
{
    return;
}

#endif /* LWP_DEBUG_INIT */

static rt_err_t _serial_ty_bypass(struct rt_serial_device *serial, char ch, void *data)
{
    lwp_tty_t tp;
    tp = (lwp_tty_t)data;

    tty_lock(tp);
    ttydisc_rint(tp, ch, 0);
    ttydisc_rint_done(tp);
    tty_unlock(tp);

    return RT_EOK;
}

rt_inline void _setup_serial(struct rt_serial_device *serial, lwp_tty_t tp,
                             struct serial_tty_context *softc)
{
    rt_bypass_lower_register(serial, "tty", RT_BYPASS_PROTECT_LEVEL_1, _serial_ty_bypass, (void *)tp);
}

static void _serial_tty_set_speed(struct lwp_tty *tp)
{
    struct serial_tty_context *softc = (struct serial_tty_context *)(tp->t_devswsoftc);
    struct rt_serial_device *serial;
    struct termios serial_hw_config;

    RT_ASSERT(softc);
    serial = softc->parent;

    rt_device_control(&(serial->parent), TCGETS, &serial_hw_config);
    tp->t_termios_init_in.c_cflag |= serial_hw_config.c_cflag;

    tp->t_termios_init_in.__c_ispeed = tp->t_termios_init_in.__c_ospeed = cfgetospeed(&tp->t_termios_init_in);
}

static void _serial_tty_update_winsize(struct lwp_tty *tp,
                                       struct rt_serial_device *serial)
{
    struct winsize winsz;

    rt_memset(&winsz, 0, sizeof(winsz));
    if (rt_device_control(&serial->parent, TIOCGWINSZ, &winsz) == RT_EOK &&
        winsz.ws_row != 0 && winsz.ws_col != 0)
    {
        tp->t_winsize = winsz;
    }
}

static int _serial_isbusy(struct rt_serial_device *serial)
{
    rt_thread_t user_thread = rt_console_current_user();
    rt_thread_t self_thread = rt_thread_self();

    return rt_console_get_device() == &serial->parent &&
           (user_thread != RT_NULL && user_thread != self_thread);
}

static void serial_tty_outwakeup(struct lwp_tty *tp)
{
    char out_char;
    int len;
    struct serial_tty_context *context = tty_softc(tp);
    struct rt_serial_device *device;

    if (!context || !context->parent)
    {
        LOG_E("%s: Data corruption", __func__);
        return;
    }

    device = context->parent;

    if (_serial_isbusy(device))
    {
        return;
    }

    while ((len = ttydisc_getc(tp, &out_char, sizeof(out_char))) != 0)
    {
        device->ops->putc(device, out_char);

        /* discard remaining if emergency output is happened */
        if (_serial_isbusy(device))
        {
            break;
        }
    }
}

static int serial_tty_open(struct lwp_tty *tp)
{
    struct serial_tty_context *softc;
    struct rt_serial_device *serial;
    rt_err_t error;
    int oflags;

    softc = tty_softc(tp);
    serial = softc->parent;

    LOG_D("%s", __func__);

    rt_device_control(&serial->parent, RT_DEVICE_CTRL_CONSOLE_OFLAG, &oflags);

    error = rt_device_open(&serial->parent, oflags);

    if (!error)
    {
        /**
         * to avoid driver accesssing null data,
         * these are setup only after tty is registered
         */
        if (rt_console_get_device() == &serial->parent)
        {
            /* Query before the bypass is installed so the response stays in
             * the raw serial receive queue instead of being delivered as
             * input. */
            _serial_tty_update_winsize(tp, serial);
        }
        _setup_serial(serial, tp, softc);
    }
    return error;
}

static void serial_tty_close(struct lwp_tty *tp)
{
    struct serial_tty_context *softc;
    struct rt_serial_device *serial;
    softc = tty_softc(tp);
    serial = softc->parent;

    LOG_D("%s", __func__);

    rt_bypass_lower_unregister(serial, RT_BYPASS_PROTECT_LEVEL_1);
    rt_device_close(&serial->parent);
}

static int serial_tty_ioctl(struct lwp_tty *tp, rt_ubase_t cmd, rt_caddr_t data,
                            struct rt_thread *td)
{
    /* Let the TTY layer handle process state and cached terminal settings. */
    return -ENOSYS;
}

static int serial_tty_param(struct lwp_tty *tp, struct termios *t)
{
    struct serial_tty_context *softc = (struct serial_tty_context *)(tp->t_devswsoftc);
    struct rt_serial_device *serial;

    RT_ASSERT(softc);
    serial = softc->parent;

    if (!tty_opened(tp))
    {
        /**
         * skip configure on open since all configs are copied from the current
         * configuration on device. So we don't bother to set it back to device
         * again.
         */
        return RT_EOK;
    }

    cfsetispeed(t, t->__c_ispeed);
    return rt_device_control(&(serial->parent), TCSETS, t);
}

static void serial_tty_free(void *softc)
{
    /*
     * lwp_tty_delete() calls the destructor of the tty device switch, both for
     * a TTY that was opened as well as for one that never was.
     */
    rt_free(softc);
}

static struct lwp_ttydevsw serial_ttydevsw = {
    .tsw_open = serial_tty_open,
    .tsw_close = serial_tty_close,
    .tsw_ioctl = serial_tty_ioctl,
    .tsw_param = serial_tty_param,
    .tsw_outwakeup = serial_tty_outwakeup,
    .tsw_free = serial_tty_free,
};

rt_err_t rt_hw_serial_register_tty(struct rt_serial_device *serial)
{
    rt_err_t rc;
    lwp_tty_t tty;
    char *dev_name;
    struct serial_tty_context *softc;

    if (serial->ttydev)
    {
        return -RT_EBUSY;
    }

#ifdef RT_USING_COMPONENTS_INIT
    /*
     * Board code can register a serial device before INIT_PREV_EXPORT creates the
     * tty workqueue.
     *
     * NOTE: The pending registrations list is accessed ONLY during the early
     * initialization phase before the scheduler starts (single-threaded context).
     * Once _tty_pending_flush has executed (_tty_flush_done == RT_TRUE), no further
     * registrations may be queued onto the pending list; if the workqueue is still
     * unavailable after flush, registration returns an error immediately.
     */
    if (!_tty_flush_done && _ttyworkq == RT_NULL)
    {
        struct _tty_pending_registration *pending;

        pending = rt_malloc(sizeof(*pending));
        if (pending == RT_NULL)
        {
            return -RT_ENOMEM;
        }

        pending->serial = serial;
        rt_slist_append(&_tty_pending_registrations, &pending->node);

        return RT_EOK;
    }
    else if (_tty_flush_done && _ttyworkq == RT_NULL)
    {
        /* flush has completed but workqueue creation failed */
        return -RT_ERROR;
    }
#endif /* RT_USING_COMPONENTS_INIT */

    softc = rt_malloc(sizeof(struct serial_tty_context));
    if (softc)
    {
        dev_name = alloc_device_name(serial);

        if (dev_name)
        {
            softc->parent = serial;
            tty = lwp_tty_create(&serial_ttydevsw, softc);
            if (tty)
            {
                _serial_tty_set_speed(tty);
                rc = lwp_tty_register(tty, dev_name);

                if (rc != RT_EOK)
                {
                    rt_free(tty);
                    rt_free(softc);
                }
                else
                {
                    /*
                     * Keep the TTY here instead of relying on rx_notify.dev: the
                     * notify belongs to whoever uses it, so it cannot tell "no TTY
                     * was ever created" from "the TTY exists but was never
                     * opened".
                     */
                    serial->ttydev = &tty->parent;
                }
            }
            else
            {
                rt_free(softc);
                rc = -RT_ENOMEM;
            }

            rt_free(dev_name);
        }
        else
        {
            rt_free(softc);
            rc = -RT_ENOMEM;
        }
    }
    else
    {
        rc = -RT_ENOMEM;
    }

    return rc;
}

rt_err_t rt_hw_serial_unregister_tty(struct rt_serial_device *serial)
{
    rt_device_t tty_dev;
    lwp_tty_t tp;

#ifdef RT_USING_COMPONENTS_INIT
    if (!_tty_flush_done)
    {
        rt_slist_t *node = _tty_pending_registrations.next;

        while (node != RT_NULL)
        {
            struct _tty_pending_registration *pending;
            rt_slist_t *next = node->next;

            pending = rt_slist_entry(node, struct _tty_pending_registration, node);
            if (pending->serial == serial)
            {
                rt_slist_remove(&_tty_pending_registrations, node);
                rt_free(pending);
                return RT_EOK;
            }

            node = next;
        }
    }
#endif /* RT_USING_COMPONENTS_INIT */

    /*
     * Registration may never have produced a TTY: the request could still be
     * queued and be dropped by _tty_pending_flush(), the flush could fail, or
     * TTY creation could have failed. rt_hw_serial_register_tty() reports
     * RT_EOK for a queued request, so only a recorded TTY proves that one was
     * created. A TTY that exists but was never opened must still be torn down;
     * only the absence of the pointer means there is nothing to do.
     */
    tty_dev = serial->ttydev;
    if (tty_dev == RT_NULL)
    {
        return RT_EOK;
    }
    serial->ttydev = RT_NULL;

    tp = rt_container_of(tty_dev, struct lwp_tty, parent);

    /*
     * serial->rx_notify is left alone on purpose. The TTY receives through the
     * bypass hook installed by serial_tty_open() and never installs a notify of
     * its own, so there is nothing here to revoke. Writing back a notify saved
     * at registration time would silently replace a callback that somebody else
     * installed with RT_DEVICE_CTRL_NOTIFY_SET in the meantime.
     */
    tty_lock(tp);

    /*
     * tty_rel_gone() marks the TTY as gone and releases it: it deletes the TTY
     * (device object, queues and our context through serial_tty_free()) once the
     * last session has left, or right away when the TTY was never opened. The
     * TTY must not be freed here as well.
     */
    tty_rel_gone(tp);

    return RT_EOK;
}

static int _tty_workqueue_init(void)
{
    if (_ttyworkq != RT_NULL)
    {
        return RT_EOK;
    }

    _ttyworkq = rt_workqueue_create("ttyworkq", RT_SYSTEM_WORKQUEUE_STACKSIZE,
                                    LWP_TTY_WORKQUEUE_PRIORITY);
    RT_ASSERT(_ttyworkq != RT_NULL);

    _setup_debug_rxind_hook();

    return RT_EOK;
}
INIT_PREV_EXPORT(_tty_workqueue_init);

#ifdef RT_USING_COMPONENTS_INIT
static int _tty_pending_flush(void)
{
    rt_slist_t *node;

    _tty_flush_done = RT_TRUE;

    if (_ttyworkq == RT_NULL)
    {
        LOG_E("tty workqueue is not available, cannot flush deferred registrations");
        while ((node = rt_slist_pop(&_tty_pending_registrations)) != RT_NULL)
        {
            struct _tty_pending_registration *pending;

            pending = rt_slist_entry(node, struct _tty_pending_registration, node);
            rt_free(pending);
        }
        return -RT_ERROR;
    }

    while ((node = rt_slist_pop(&_tty_pending_registrations)) != RT_NULL)
    {
        struct _tty_pending_registration *pending;
        rt_err_t rc;

        pending = rt_slist_entry(node, struct _tty_pending_registration, node);
        rc = rt_hw_serial_register_tty(pending->serial);
        if (rc != RT_EOK)
        {
            LOG_E("deferred tty registration failed: %d", rc);
        }

        rt_free(pending);
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(_tty_pending_flush);
#endif /* RT_USING_COMPONENTS_INIT */

static rt_err_t _match_tty_iter(struct rt_object *obj, void *data)
{
    rt_device_t target = *(rt_device_t *)data;
    rt_device_t device = rt_container_of(obj, struct rt_device, parent);
    if (device->type == RT_Device_Class_Char)
    {
        lwp_tty_t tp;
        if (rt_strncmp(obj->name, "tty" TTY_NAME_PREFIX,
                       sizeof("tty" TTY_NAME_PREFIX) - 1) == 0)
        {
            struct serial_tty_context *softc;

            tp = rt_container_of(device, struct lwp_tty, parent);
            softc = tty_softc(tp);

            if (&softc->parent->parent == target)
            {
                /* matched, early return */
                *(rt_device_t *)data = device;
                return 1;
            }
        }
    }

    return RT_EOK;
}

/**
 * @brief The default console is only a backup device with lowest priority.
 *        It's always recommended to scratch the console from the boot arguments.
 *        And dont forget to register the device with a higher priority.
 */
static int _default_console_setup(void)
{
    rt_err_t rc;
    rt_device_t bakdev;
    rt_device_t ttydev;

    bakdev = rt_console_get_device();
    if (!bakdev)
    {
        return -RT_ENOENT;
    }

    ttydev = bakdev;
    rt_object_for_each(RT_Object_Class_Device, _match_tty_iter, &ttydev);

    if (ttydev != bakdev)
    {
        LOG_I("Using /dev/%.*s as default console", RT_NAME_MAX, ttydev->parent.name);
        lwp_console_register_backend(ttydev, LWP_CONSOLE_LOWEST_PRIOR);
        rc = RT_EOK;
    }
    else
    {
        rc = -RT_EINVAL;
    }

    return rc;
}

INIT_COMPONENT_EXPORT(_default_console_setup);
