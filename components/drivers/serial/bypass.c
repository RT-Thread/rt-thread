/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-11-20     zhujiale     the first version
 */

#include<rtdevice.h>
#define DBG_TAG    "UART"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

static struct rt_serial_bypass_func* rt_bypass_alloc_func(const char* name, rt_uint8_t level, bypass_function_t func, void* data)
{
    struct rt_serial_bypass_func* bypass;

    if (!func)
        return RT_NULL;

    bypass = rt_malloc(sizeof(struct rt_serial_bypass_func));
    rt_memset(bypass, 0, sizeof(struct rt_serial_bypass_func));

    if (rt_strlen(name) > RT_NAME_MAX - 1)
        rt_memcpy(bypass->name, name, RT_NAME_MAX);
    else
        rt_memcpy(bypass->name, name, rt_strlen(name) + 1);

    bypass->level = level;

    rt_list_init(&bypass->node);
    bypass->bypass = func;
    bypass->data = data;

    return bypass;
}

rt_err_t rt_serial_bypass_init(struct rt_serial_device* serial)
{
    serial->bypass = rt_malloc(sizeof(struct rt_serial_bypass));
    rt_memset(serial->bypass, 0, sizeof(struct rt_serial_bypass));
    serial->bypass->pipe = rt_ringbuffer_create(serial->config.bufsz);
    serial->bypass->mutex = rt_mutex_create("serial_bypass", RT_IPC_FLAG_FIFO);

    return RT_EOK;
}

static rt_err_t rt_bypass_register(struct rt_serial_bypass_head* bypass, const char* name, rt_uint8_t level, bypass_function_t func, void* data)
{
    struct rt_serial_bypass_func* pass = RT_NULL;
    struct rt_list_node* node;
    int flags;

    RT_DEBUG_NOT_IN_INTERRUPT;

    pass = rt_bypass_alloc_func(name, level, func, data);

    RT_ASSERT(bypass != RT_NULL);

    node = bypass->head.next;

    if (node == &bypass->head)
    {
        rt_list_insert_before(&pass->node, node);
        return RT_EOK;
    }
    flags = rt_spin_lock_irqsave(&(bypass->spinlock));
    do {
        struct rt_serial_bypass_func* temp_curr;
        temp_curr = rt_container_of(node, struct rt_serial_bypass_func, node);

        if (level < temp_curr->level)
        {
            rt_list_insert_before(node, &pass->node);

            rt_spin_unlock_irqrestore(&(bypass->spinlock), flags);
            return RT_EOK;
        }
        else if (level == temp_curr->level)
        {
            rt_spin_unlock_irqrestore(&(bypass->spinlock), flags);
            LOG_E("Conflict: bypass [%s] level conflicts with [%s] at level [%d]\n", name, temp_curr->name, level);
            rt_free(pass);
            return -RT_ERROR;
        }

        node = node->next;

    } while (node != &bypass->head);

    rt_list_insert_before(&bypass->head, &pass->node);

    rt_spin_unlock_irqrestore(&(bypass->spinlock), flags);
    return RT_EOK;

}

rt_err_t rt_bypass_upper_register(struct rt_serial_device* serial, const char* name, rt_uint8_t level, bypass_function_t func, void* data)
{
    if (!serial->bypass)
        rt_serial_bypass_init(serial);

    if (!serial->bypass->upper_h)
    {
        serial->bypass->upper_h = rt_malloc(sizeof(struct rt_serial_bypass_head));
        rt_spin_lock_init(&serial->bypass->upper_h->spinlock);
        rt_list_init(&serial->bypass->upper_h->head);

    }

    return rt_bypass_register(serial->bypass->upper_h, name, level, func, data);
}



void rt_bypass_putchar(struct rt_serial_device* serial, rt_uint8_t ch)
{
    rt_mutex_take(serial->bypass->mutex, RT_WAITING_FOREVER);
    rt_ringbuffer_putchar(serial->bypass->pipe, ch);
    rt_mutex_release(serial->bypass->mutex);
}

rt_size_t rt_bypass_getchar(struct rt_serial_device* serial, rt_uint8_t* ch)
{
    int flags;
    rt_mutex_take(serial->bypass->mutex, RT_WAITING_FOREVER);
    flags = rt_ringbuffer_getchar(serial->bypass->pipe, ch);
    rt_mutex_release(serial->bypass->mutex);
    return flags;
}

static inline rt_err_t _bypass_getchar_form_serial_fifo(struct rt_serial_device* serial, char* ch)
{
    rt_base_t level;
    struct rt_serial_rx_fifo* rx_fifo;
    rx_fifo = (struct rt_serial_rx_fifo*)serial->serial_rx;
    /* disable interrupt */
    level = rt_spin_lock_irqsave(&(serial->spinlock));

    /* there's no data: */
    if ((rx_fifo->get_index == rx_fifo->put_index) && (rx_fifo->is_full == RT_FALSE))
    {
        /* no data, enable interrupt and break out */
        rt_spin_unlock_irqrestore(&(serial->spinlock), level);
        return -RT_EEMPTY;
    }

    /* otherwise there's the data: */
    *ch = rx_fifo->buffer[rx_fifo->get_index];
    rx_fifo->get_index += 1;
    if (rx_fifo->get_index >= serial->config.bufsz) rx_fifo->get_index = 0;

    if (rx_fifo->is_full == RT_TRUE)
    {
        rx_fifo->is_full = RT_FALSE;
    }

    /* enable interrupt */
    rt_spin_unlock_irqrestore(&(serial->spinlock), level);

    return RT_EOK;
}

static void _lower_work(struct rt_serial_device* serial)
{
    struct rt_list_node* node;
    struct rt_serial_bypass_func* temp_curr = RT_NULL;
    if (serial->bypass && serial->bypass->lower_h)
    {
        while (1)
        {
            char ch;
            if (_bypass_getchar_form_serial_fifo(serial, &ch))
                return;

            node = serial->bypass->lower_h->head.next;

            while (node != &serial->bypass->lower_h->head)
            {
                temp_curr = rt_container_of(node, struct rt_serial_bypass_func, node);

                if (!temp_curr->bypass(serial, ch, temp_curr->data))
                {
                    break;
                }

                node = node->next;
            }
            if (node == &serial->bypass->lower_h->head)
            {
                rt_bypass_putchar(serial, ch);
            }
        }
    }
}


static void rt_lower_work(struct rt_work* work, void* work_data)
{
    struct rt_serial_device* serial = (struct rt_serial_device*)work_data;

    RT_ASSERT(serial != RT_NULL);

    _lower_work(serial);
}

rt_err_t rt_bypass_lower_register(struct rt_serial_device* serial, const char* name, rt_uint8_t level, bypass_function_t func, void* data)
{
    if (!serial->bypass)
        rt_serial_bypass_init(serial);

    if (!serial->bypass->lower_h)
    {
        serial->bypass->lower_workq = rt_workqueue_create("serial bypass", RT_SYSTEM_WORKQUEUE_STACKSIZE,
            RT_SYSTEM_WORKQUEUE_PRIORITY);
        rt_work_init(&serial->bypass->work, rt_lower_work, (void*)serial);

        serial->bypass->lower_h = rt_malloc(sizeof(struct rt_serial_bypass_head));
        rt_spin_lock_init(&serial->bypass->lower_h->spinlock);
        rt_list_init(&serial->bypass->lower_h->head);

    }

    return rt_bypass_register(serial->bypass->lower_h, name, level, func, data);
}

void rt_bypass_work_straight(struct rt_serial_device* serial)
{
    if (serial->bypass && serial->bypass->lower_h)
    {
        _lower_work(serial);
        return;
    }

    while (1)
    {
        char ch;
        if (_bypass_getchar_form_serial_fifo(serial, &ch))
            return;

        rt_bypass_putchar(serial, ch);
    }

}

rt_err_t rt_bypass_unregister(struct rt_serial_bypass_head* bypass, rt_uint8_t level)
{
    struct rt_list_node* node;
    struct rt_serial_bypass_func* temp_curr = RT_NULL;
    int flags;

    /*Can not unregister protect level in bypass it general be msh or tty*/
    if (level > RT_BYPASS_PROTECT_LEVEL_1)
        return -RT_ERROR;

    if (!bypass)
        return -RT_ERROR;

    node = bypass->head.next;
    flags = rt_spin_lock_irqsave(&(bypass->spinlock));

    do {
        temp_curr = rt_container_of(node, struct rt_serial_bypass_func, node);

        if (level == temp_curr->level)
        {
            rt_list_remove(node);
            rt_spin_unlock_irqrestore(&(bypass->spinlock), flags);
            rt_free(temp_curr);
            return RT_EOK;
        }

        node = node->next;
    } while (node != &bypass->head);

    LOG_E("Can't find bypass with level [%d]", level);
    rt_spin_unlock_irqrestore(&(bypass->spinlock), flags);
    return -RT_ERROR;
}

rt_err_t rt_bypass_upper_unregister(struct rt_serial_device* serial, rt_uint8_t level)
{
    if (!serial->bypass || !serial->bypass->upper_h)
        return -RT_ERROR;
    return rt_bypass_unregister(serial->bypass->upper_h, level);
}

rt_err_t rt_bypass_lower_unregister(struct rt_serial_device* serial, rt_uint8_t level)
{
    if (!serial->bypass || !serial->bypass->lower_h)
        return -RT_ERROR;
    return rt_bypass_unregister(serial->bypass->lower_h, level);
}

int serial_bypass_list(int argc, char** argv)
{
    struct rt_serial_device* serial = RT_NULL;
    struct rt_serial_bypass_func* current;
    struct rt_list_node* node;
    int flags;

    serial = (struct rt_serial_device*)rt_console_get_device();
    if (!serial || !serial->bypass)
    {
        rt_kprintf("Serial bypass not initialized.\n");
        return -1;
    }

    /* 遍历 Upper Bypass 链表 */
    if (serial->bypass->upper_h)
    {
        rt_kprintf("Upper bypass chain:\n");
        node = serial->bypass->upper_h->head.next;

        flags = rt_spin_lock_irqsave(&(serial->bypass->upper_h->spinlock)); /* 加锁*/
        while (node != &serial->bypass->upper_h->head)
        {
            current = rt_container_of(node, struct rt_serial_bypass_func, node);
            rt_kprintf(" - Name: [%s], Level: [%d]\n", current->name, current->level);
            node = node->next;
        }
        rt_spin_unlock_irqrestore(&(serial->bypass->upper_h->spinlock), flags); /* 解锁*/
    }
    else
    {
        rt_kprintf("Upper bypass chain is empty.\n");
    }

    /* 遍历 Lower Bypass 链表 */
    if (serial->bypass->lower_h)
    {
        rt_kprintf("Lower bypass chain:\n");
        node = serial->bypass->lower_h->head.next;

        flags = rt_spin_lock_irqsave(&(serial->bypass->lower_h->spinlock)); /* 加锁*/
        while (node != &serial->bypass->lower_h->head)
        {
            current = rt_container_of(node, struct rt_serial_bypass_func, node);
            rt_kprintf(" - Name: [%s], Level: [%d]\n", current->name, current->level);
            node = node->next;
        }
        rt_spin_unlock_irqrestore(&(serial->bypass->lower_h->spinlock), flags); /* 解锁*/
    }
    else
    {
        rt_kprintf("Lower bypass chain is empty.\n");
    }

    return 0;
}


MSH_CMD_EXPORT(serial_bypass_list, serial bypass list)
