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
static struct rt_serial_bypass *rt_bypass_alloc(const char* name, rt_uint8_t level,bypass_function_t func)
{
    struct rt_serial_bypass* bypass;

    if (!func)
        return RT_NULL;

    bypass = rt_malloc(sizeof(struct rt_serial_bypass));
    rt_memset(bypass, 0, sizeof(struct rt_serial_bypass));

    if (rt_strlen(name) > RT_NAME_MAX - 1)
        rt_memcpy(bypass->name, name, RT_NAME_MAX);
    else
        rt_memcpy(bypass->name, name, rt_strlen(name) + 1);

    bypass->level = level;
    rt_list_init(&bypass->list);
    bypass->bypass = func;

    return bypass;
}

rt_err_t rt_bypass_register(struct rt_serial_device* serial, const char* name, rt_uint8_t level, bypass_function_t func)
{
    struct rt_serial_bypass* bypass = RT_NULL;
    struct rt_list_node* node;
    int flags;


    bypass = rt_bypass_alloc(name, level, func);

    RT_ASSERT(bypass != RT_NULL);

    flags = rt_spin_lock_irqsave(&(serial->spinlock));
    if (!serial->bypass)
    {
        serial->bypass = bypass;
        rt_spin_unlock_irqrestore(&(serial->spinlock), flags);
        return RT_EOK;
    }

    node = &serial->bypass->list;
    do {
        struct rt_serial_bypass* temp_curr = rt_container_of(node, struct rt_serial_bypass, list);

        if (level < temp_curr->level)
        {
            rt_list_insert_before(node, &bypass->list);
            if (node == &serial->bypass->list)
                serial->bypass = bypass;

            rt_spin_unlock_irqrestore(&(serial->spinlock), flags);
            return RT_EOK;
        } else if (level == temp_curr->level)
        {
            rt_spin_unlock_irqrestore(&(serial->spinlock), flags);
            LOG_E("Conflict: bypass [%s] level conflicts with [%s] at level [%d]\n", name, temp_curr->name, level);
            rt_free(bypass);
            return -RT_ERROR;
        }

        node = node -> next;

    } while (node != &serial->bypass->list);

    rt_list_insert_before(&serial->bypass->list, &bypass->list);

    rt_spin_unlock_irqrestore(&(serial->spinlock), flags);
    return RT_EOK;

}

rt_err_t rt_bypass_unregister(struct rt_serial_device* serial, rt_uint8_t level)
{
    struct rt_list_node* node;
    struct rt_serial_bypass* temp_curr = RT_NULL;
    int flags;

    if (!serial->bypass)
        return -RT_ERROR;

    node = &serial->bypass->list;

    flags = rt_spin_lock_irqsave(&(serial->spinlock));

    do {
        temp_curr = rt_container_of(node, struct rt_serial_bypass, list);
        if (level == temp_curr->level)
        {
            if (&temp_curr->list == &serial->bypass->list)
            {
                if (node->next != &serial->bypass->list)
                {
                    struct rt_serial_bypass* temp_next = rt_container_of(node->next, struct rt_serial_bypass, list);
                    serial->bypass = temp_next;
                } else {
                    serial->bypass = RT_NULL;
                }

            }
            rt_list_remove(node);
            rt_spin_unlock_irqrestore(&(serial->spinlock), flags);
            rt_free(temp_curr);
            return RT_EOK;
        }
        node = node -> next;
    } while (node != &serial->bypass->list);

    LOG_E("Can't find bypass with level [%d]", flags);
    rt_spin_unlock_irqrestore(&(serial->spinlock), flags);
    return -RT_ERROR;
}

int serial_bypass_list(int argc, char** argv)
{
    struct rt_serial_device* serial;
    struct rt_serial_bypass* temp_curr = RT_NULL;
    serial = (struct rt_serial_device*)rt_console_get_device();
    if (!serial->bypass)
    {
        rt_kprintf("There is no bypass registered\n");
        return 0;
    }

    rt_list_t* node = &serial->bypass->list;

    do {
        temp_curr = rt_container_of(node, struct rt_serial_bypass, list);
        rt_kprintf("The bypass of this serial name: [%s] level: [%d]\n", temp_curr->name, temp_curr->level);
        node = node->next;
    } while (node != &serial->bypass->list);

    return 0;

}
MSH_CMD_EXPORT(serial_bypass_list, serial bypass list)
