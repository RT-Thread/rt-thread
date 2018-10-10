/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * File       : input.c
 *
 * Change Logs:
 * Date           Author        Notes
   2018-10-10     heyuanjie87   first version

 */

#include <rtdevice.h>
#include <rtdbg.h>

#define INPUT_EVBUF_MAX 6

static rt_list_t _handler_list = RT_LIST_OBJECT_INIT(_handler_list);
static rt_list_t _dev_list = RT_LIST_OBJECT_INIT(_dev_list);

int rt_input_device_register(rt_input_t *dev, int devtype, const char *name)
{
    dev->wpos = 0;
    dev->numbuf = INPUT_EVBUF_MAX;

    dev->buf = rt_malloc(sizeof(struct input_value) * INPUT_EVBUF_MAX);

    if (!dev->buf)
        return -ENOMEM;

    dev->type = devtype;
    dev->handler = 0;
    rt_list_init(&dev->node);

    rt_list_insert_after(&_dev_list, &dev->node);

    return 0;
}

int rt_input_device_unregister(rt_input_t *dev)
{
    struct input_handler *h;

    h = dev->handler;
    if (!h)
        return 0;

    dev->handler = 0;
    rt_list_remove(&dev->node);

    if (h->disconnect)
    {
        h->disconnect(h, dev);
    }

    return 0;
}

int rt_input_report(rt_input_t *dev, int type, int code, int value)
{
    struct input_value ev;

    if (!dev->handler)
        return 0;
    if (!dev->buf)
        return 0;
    if (dev->wpos == dev->numbuf)
    {
        dev->wpos = 0;
        LOG_E("input: buf is too small\n");
    }

    ev.type = type;
    ev.code = code;
    ev.value = value;

    dev->buf[dev->wpos] = ev;
    dev->wpos++;

    if (type == EV_SYN && code == SYN_REPORT)
    {
        /* drop empty SYN_REPORT */
        if (dev->wpos > 1)
            dev->handler->events(dev->handler, dev, dev->buf, dev->wpos);
        dev->wpos = 0;
    }

    return 0;
}

int rt_input_key_report(rt_input_t *dev, int code, int value)
{
    return rt_input_report(dev, EV_KEY, code, value);
}

int rt_input_abs_report(rt_input_t *dev, int code, int value)
{
    return rt_input_report(dev, EV_ABS, code, value);
}

int rt_input_rel_report(rt_input_t *dev, int code, int value)
{
    return rt_input_report(dev, EV_REL, code, value);
}

int rt_input_sync(rt_input_t *dev)
{
    return rt_input_report(dev, EV_SYN, SYN_REPORT, 0);
}

int rt_input_handler_register(struct input_handler *handler, const char *name)
{
    int ret;
    struct input_dev *entry;
    rt_list_t *node, *head;

    rt_list_init(&handler->node);
    rt_list_init(&handler->c_list);
    rt_list_init(&handler->d_list);

    ret = rt_device_register(&handler->parent, name, 0);
    if (ret)
        return ret;

    rt_list_insert_after(&_handler_list, &handler->node);

    /* pass events to all connected client */
    head = &_dev_list;
    for (node = head->next; node != head; )
    {
        entry = rt_list_entry(node, struct input_dev, node);
        node = node->next;

        if (entry->type == handler->type)
        {
            rt_list_remove(&entry->node);
            rt_list_insert_after(&handler->d_list, &entry->node);
            entry->handler = handler;
        }
    }
    
    return 0;
}

int rt_input_device_open(struct input_handler *handler)
{
    struct input_dev *dev;
    rt_list_t *node, *head;
    int ret = 0;

    head = &handler->d_list;
    for (node = head->next; node != head; node = node->next)
    {
        dev = rt_list_entry(node, struct input_dev, node);

        if (handler->type != dev->type)
            continue;
        if (dev->parent.ref_count == 0)
        {   
            dev->parent.ref_count ++;
            if (dev->ops->init(dev) != 0)
                dev->parent.ref_count --;
        }
        ret ++;
    }

    return ret;
}

int rt_input_device_close(struct input_handler *handler)
{
    struct input_dev *dev;
    rt_list_t *node, *head;

    head = &handler->d_list;
    for (node = head->next; node != head; node = node->next)
    {
        dev = rt_list_entry(node, struct input_dev, node);
        if (dev->parent.ref_count == 1)
        {
            dev->ops->deinit(dev);
        }
        dev->parent.ref_count --;
    }

    return 0;
}
