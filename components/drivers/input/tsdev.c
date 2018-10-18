/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * File       : tsdev.c
 *
 * Change Logs:
 * Date           Author        Notes
   2018-10-10     heyuanjie87   first version

 */

#include <rtdevice.h>
#include <rthw.h>

#define TSDEV_MAXCNT 16

#ifdef RT_USING_POSIX
#include <dfs_posix.h>
#include <dfs_poll.h>
#endif

struct tsdev_client
{
    struct input_event buf[TSDEV_MAXCNT];
    uint8_t head;
    uint8_t tail;
    uint8_t packet_head;
    rt_list_t node;
    struct input_handler *handler;
#ifdef RT_USING_POSIX
    rt_wqueue_t wait;
#endif
};

static int get_next(struct tsdev_client *client, struct input_event *ev)
{
    rt_base_t level;
    int have_event;

    level = rt_hw_interrupt_disable();
    have_event = client->packet_head != client->tail;
    if (have_event)
    {
        *ev = client->buf[client->tail];
        client->tail++;
        if (client->tail == TSDEV_MAXCNT)
            client->tail = 0;
    }
    rt_hw_interrupt_enable(level);

    return have_event;
}

#ifdef RT_USING_POSIX
static int _fops_open(struct dfs_fd *fd)
{
    struct tsdev_client *client;

    client = rt_malloc(sizeof(struct tsdev_client));
    if (!client)
        return -ENOMEM;

    rt_wqueue_init(&client->wait);
    rt_list_init(&client->node);
    client->head = 0;
    client->tail = 0;
    client->packet_head = 0;
    client->handler = (struct input_handler*)fd->data;
    rt_list_insert_after(&(client->handler->c_list), &client->node);

    fd->data = client;

    rt_input_device_open(client->handler);

    return 0;
}

static int _fops_close(struct dfs_fd *fd)
{
    struct tsdev_client *client;

    client = (struct tsdev_client *)fd->data;
    rt_input_device_close(client->handler);
    rt_free(client);

    return 0;
}

static int _fops_ioctl(struct dfs_fd *fd, int cmd, void *args)
{
    return 0;
}

static int _fops_read(struct dfs_fd *fd, void *buf, size_t count)
{
    int ret = 0;
    struct tsdev_client *client;
    struct input_event *ev = (struct input_event *)buf;

    client = (struct tsdev_client *)fd->data;

    if (count != 0 && count < sizeof(struct input_event))
        return -EINVAL;
    if (rt_list_isempty(&(client->handler->d_list)))
        return -ENODEV;

    while (!ret)
    {
        if (client->packet_head == client->tail)
        {
            if ((fd->flags & O_NONBLOCK))
                return -EAGAIN;
            else
                rt_wqueue_wait(&client->wait, 0, -1);
        }

        while (ret < count && get_next(client, ev))
        {
            ret += sizeof(struct input_event);
            ev++;
        }
    }

    return ret;
}

static int _fops_write(struct dfs_fd *fd, const void *buf, size_t count)
{
    return 0;
}

static int _fops_poll(struct dfs_fd *fd, struct rt_pollreq *req)
{
    int mask = 0;
    struct tsdev_client *client;

    client = (struct tsdev_client *)fd->data;
    if (rt_list_isempty(&(client->handler->d_list)))
        mask |= POLLHUP;
    else if (client->packet_head != client->tail)
        mask |= POLLIN;

    if (mask == 0)
        rt_poll_add(&client->wait, req);

    return mask;
}

const static struct dfs_file_ops _fops =
{
    _fops_open,
    _fops_close,
    _fops_ioctl,
    _fops_read,
    _fops_write,
    RT_NULL, /* flush */
    RT_NULL, /* lseek */
    RT_NULL, /* getdents */
    _fops_poll,
};
#endif

static rt_size_t rt_ts_read(struct rt_device *dev,
                                 rt_off_t    pos,
                                 void        *buf,
                                 rt_size_t   count)
{
    int ret = 0;
    struct tsdev_client *client;
    struct input_event *ev = (struct input_event *)buf;

    client = (struct tsdev_client *)dev->user_data;
    if (!client)
        return 0;

    if (count != 0 && count < sizeof(struct input_event))
        return 0;
    if (rt_list_isempty(&(client->handler->d_list)))
        return 0;

    while (!ret)
    {
        if (client->packet_head == client->tail)
            return 0;

        while (ret < count && get_next(client, ev))
        {
            ret += sizeof(struct input_event);
            ev++;
        }
    }

    return ret;
}

static rt_size_t rt_ts_write(struct rt_device *dev,
                                 rt_off_t     pos,
                                 const void   *buffer,
                                 rt_size_t    size)
{
    return 0;
}

static rt_err_t rt_ts_close(struct rt_device *dev)
{
    struct tsdev_client *client;

    client = (struct tsdev_client *)dev->user_data;
    rt_input_device_close(client->handler);
    rt_free(client);

    dev->user_data = 0;

    return 0;
}

static rt_err_t rt_ts_open(struct rt_device *dev, rt_uint16_t oflag)
{
    struct tsdev_client *client;

    if (dev->ref_count >= 1)
        return -RT_EBUSY;

    client = rt_malloc(sizeof(struct tsdev_client));
    if (!client)
        return -RT_ENOMEM;

#ifdef RT_USING_POSIX
    rt_wqueue_init(&client->wait);
#endif
    rt_list_init(&client->node);
    client->head = 0;
    client->tail = 0;
    client->packet_head = 0;
    client->handler = (struct input_handler*)dev;
    rt_list_insert_after(&(client->handler->c_list), &client->node);

    dev->user_data = client;

    rt_input_device_open(client->handler);

    return 0;
}

static rt_err_t rt_ts_init(struct rt_device *dev)
{
    return 0;
}

static rt_err_t rt_ts_control(struct rt_device *dev,
                                  int              cmd,
                                  void             *args)
{
    return 0;
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops _dops =
{
    rt_ts_init,
    rt_ts_open,
    rt_ts_close,
    rt_ts_read,
    rt_ts_write,
    rt_ts_control
};
#endif

static void _pass_event(struct tsdev_client *client,
                        const struct input_event *event)
{
    client->buf[client->head++] = *event;
    if (client->head == TSDEV_MAXCNT)
        client->head = 0;

    if (client->head == client->tail)
    {
        /*
              This effectively "drops" all unconsumed events, leaving
              EV_SYN/SYN_DROPPED plus the newest event in the queue.
            */
        client->tail = (client->head - 2) & (TSDEV_MAXCNT - 1);

        client->buf[client->tail].type = EV_SYN;
        client->buf[client->tail].code = SYN_DROPPED;

        client->packet_head = client->tail;
    }

    if (event->type == EV_SYN && event->code == SYN_REPORT)
    {
        client->packet_head = client->head;
    }
}

static void _pass_values(struct tsdev_client *client, struct input_value *val, int cnt)
{
    struct input_event e;
    int n;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    for (n = 0; n < cnt; n++)
    {
        e.type = val->type;
        e.code = val->code;
        e.value = val->value;
        if (e.type == EV_SYN && e.code == SYN_REPORT)
            _input_gettime(&e);

        _pass_event(client, &e);
        val ++;
    }
    rt_hw_interrupt_enable(level);

#ifdef RT_USING_POSIX
    rt_wqueue_wakeup(&client->wait, (void *)POLLIN);
#endif
}

static void tsdev_events(struct input_handler *handler, struct input_dev *dev,
                         struct input_value *val, int cnt)
{
    struct tsdev_client *entry;
    rt_list_t *node, *head;

    /* pass events to all connected client */
    head = &handler->c_list;
    for (node = head->next; node != head; node = node->next)
    {
        entry = rt_list_entry(node, struct tsdev_client, node);
        _pass_values(entry, val, cnt);
    }
}

static void tsdev_connection(struct input_handler *handler,
                             struct input_dev *dev, int state)
{
    /* do nothing for tsdev */
}

int rt_tsdev_init(void)
{
    static struct input_handler _handler;
    int ret;

    _handler.events = tsdev_events;
    _handler.connect = tsdev_connection;
    _handler.type = INPUT_DEVTYPE_TOUCH;

    {
        rt_device_t device = &_handler.parent;

        device->user_data = 0;
#ifdef RT_USING_DEVICE_OPS
        device->ops         = &_dops;
#else
        device->init        = rt_ts_init;
        device->open        = rt_ts_open;
        device->close       = rt_ts_close;
        device->read        = rt_ts_read;
        device->write       = rt_ts_write;
        device->control     = rt_ts_control;
#endif
    }

    ret = rt_device_register(&_handler.parent, "touch", 0);
    if (ret)
    {
        return ret;
    }
    rt_input_handler_register(&_handler);

#ifdef RT_USING_POSIX
    _handler.parent.fops = &_fops;
#endif

    return ret;
}
INIT_COMPONENT_EXPORT(rt_tsdev_init);
