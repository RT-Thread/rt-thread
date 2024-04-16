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

#define TTY_NAME_PREFIX "S" /* (S)erial */
#define LWP_TTY_WORKQUEUE_PRIORITY 3

struct serial_tty_context
{
    struct rt_serial_device *parent;
    struct rt_device_notify backup_notify;
    struct rt_work work;
};

static struct rt_workqueue *_ttyworkq; /* system work queue */

#ifndef RT_USING_DM
static rt_atomic_t _device_id_counter = 0;

static long get_dec_digits(rt_ubase_t val)
{
    long result = 1;
    while (1)
    {
        if (val < 10)
            return result;
        if (val < 100)
            return result + 1;
        if (val < 1000)
            return result + 2;
        if (val < 10000)
            return result + 3;
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
    RT_ASSERT((strlen(serial_name) > strlen("uart")) && (strncmp(serial_name, "uart", 4) == 0));
    long digits_len = (sizeof(TTY_NAME_PREFIX) - 1) /* raw prefix */
                      + strlen(serial_name + sizeof("uart") - 1) /* suffix of serial device name*/
                      + 1;  /* tailing \0 */

    tty_dev_name = rt_malloc(digits_len);
    if (tty_dev_name)
        rt_sprintf(tty_dev_name, "%s%s", TTY_NAME_PREFIX, serial_name + sizeof("uart") - 1);
#else
    RT_UNUSED(serial);
    unsigned int devid = rt_atomic_add(&_device_id_counter, 1);
    long digits_len = (sizeof(TTY_NAME_PREFIX) - 1) /* raw prefix */
                      + get_dec_digits(devid) + 1;  /* tailing \0 */

    tty_dev_name = rt_malloc(digits_len);
    if (tty_dev_name)
        rt_sprintf(tty_dev_name, "%s%u", TTY_NAME_PREFIX, devid);
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
    return ;
}

#endif /* LWP_DEBUG_INIT */

static void _tty_rx_notify(struct rt_device *device)
{
    lwp_tty_t tp;
    struct serial_tty_context *softc;

    tp = rt_container_of(device, struct lwp_tty, parent);
    RT_ASSERT(tp);

    softc = tty_softc(tp);

    if (_ttyworkq)
        rt_workqueue_submit_work(_ttyworkq, &softc->work, 0);
}

static void _tty_rx_worker(struct rt_work *work, void *data)
{
    char input;
    rt_ssize_t readbytes;
    lwp_tty_t tp = data;
    struct serial_tty_context *softc;
    struct rt_serial_device *serial;

    tty_lock(tp);

    while (1)
    {
        softc = tty_softc(tp);
        serial = softc->parent;
        readbytes = rt_device_read(&serial->parent, -1, &input, 1);
        if (readbytes != 1)
        {
            break;
        }

        ttydisc_rint(tp, input, 0);
    }

    ttydisc_rint_done(tp);
    tty_unlock(tp);
}

rt_inline void _setup_serial(struct rt_serial_device *serial, lwp_tty_t tp,
                             struct serial_tty_context *softc)
{
    struct rt_device_notify notify;

    softc->backup_notify = serial->rx_notify;
    notify.dev = &tp->parent;
    notify.notify = _tty_rx_notify;

    rt_device_init(&serial->parent);

    rt_work_init(&softc->work, _tty_rx_worker, tp);
    rt_device_control(&serial->parent, RT_DEVICE_CTRL_NOTIFY_SET, &notify);
}

rt_inline void _restore_serial(struct rt_serial_device *serial, lwp_tty_t tp,
                               struct serial_tty_context *softc)
{
    rt_device_control(&serial->parent, RT_DEVICE_CTRL_NOTIFY_SET, &softc->backup_notify);
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
        return ;
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

    _restore_serial(serial, tp, softc);
    rt_device_close(&serial->parent);
}

static int serial_tty_ioctl(struct lwp_tty *tp, rt_ubase_t cmd, rt_caddr_t data,
                            struct rt_thread *td)
{
    int error;
    switch (cmd)
    {
        case TCSETS:
        case TCSETSW:
        case TCSETSF:
            RT_ASSERT(tp->t_devswsoftc);
            struct serial_tty_context *softc = (struct serial_tty_context *)(tp->t_devswsoftc);
            struct rt_serial_device *serial = softc->parent;
            struct termios *termios = (struct termios *)data;
            rt_device_control(&(serial->parent), cmd, termios);
            error = -ENOIOCTL;
        default:
            /**
             * Note: for the most case, we don't let serial layer handle ioctl,
             * for that they can't act properly regarding to the process
             * management system, since it is unawared of that. So a ENOSYS is
             * returned and caused the TTY layer to handle ioctl itself.
             */
            error = -ENOSYS;
            break;
    }
    return error;
}

static struct lwp_ttydevsw serial_ttydevsw = {
    .tsw_open = serial_tty_open,
    .tsw_close = serial_tty_close,
    .tsw_ioctl = serial_tty_ioctl,
    .tsw_outwakeup = serial_tty_outwakeup,
};

rt_err_t rt_hw_serial_register_tty(struct rt_serial_device *serial)
{
    rt_err_t rc;
    lwp_tty_t tty;
    char *dev_name;
    struct serial_tty_context *softc;

    if (serial->rx_notify.dev)
    {
        return -RT_EBUSY;
    }

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
                rc = lwp_tty_register(tty, dev_name);

                if (rc != RT_EOK)
                {
                    rt_free(tty);
                    rt_free(softc);
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
    struct serial_tty_context *softc;

    tty_dev = serial->rx_notify.dev;
    tp = rt_container_of(tty_dev, struct lwp_tty, parent);

    /* restore serial setting */
    softc = tty_softc(tp);
    serial->rx_notify = softc->backup_notify;

    tty_rel_gone(tp);

    /* device unregister? */
    rt_device_destroy(&tp->parent);
    /* resource free? */
    lwp_tty_delete(tp);

    return RT_EOK;
}

static int _tty_workqueue_init(void)
{
    if (_ttyworkq != RT_NULL)
        return RT_EOK;

    _ttyworkq = rt_workqueue_create("ttyworkq", RT_SYSTEM_WORKQUEUE_STACKSIZE,
                                    LWP_TTY_WORKQUEUE_PRIORITY);
    RT_ASSERT(_ttyworkq != RT_NULL);

    _setup_debug_rxind_hook();

    return RT_EOK;
}
INIT_PREV_EXPORT(_tty_workqueue_init);
