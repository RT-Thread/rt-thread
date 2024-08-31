/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usb_osal.h"
#include "usb_errno.h"
#include "usb_config.h"
#include "usb_log.h"
#include <rtthread.h>
#include <rthw.h>

usb_osal_thread_t usb_osal_thread_create(const char *name, uint32_t stack_size, uint32_t prio, usb_thread_entry_t entry, void *args)
{
    rt_thread_t htask;
    htask = rt_thread_create(name, entry, args, stack_size, prio, 10);
    if (htask == NULL) {
        USB_LOG_ERR("Create thread %s failed\r\n", name);
        while (1) {
        }
    }
    rt_thread_startup(htask);
    return (usb_osal_thread_t)htask;
}

void usb_osal_thread_delete(usb_osal_thread_t thread)
{
    if (thread == NULL) {
        return;
    }

    rt_thread_delete(thread);
}

usb_osal_sem_t usb_osal_sem_create(uint32_t initial_count)
{
    usb_osal_sem_t sem = (usb_osal_sem_t)rt_sem_create("usbh_sem", initial_count, RT_IPC_FLAG_FIFO);
    if (sem == NULL) {
        USB_LOG_ERR("Create semaphore failed\r\n");
        while (1) {
        }
    }
    return sem;
}

void usb_osal_sem_delete(usb_osal_sem_t sem)
{
    rt_sem_delete((rt_sem_t)sem);
}

int usb_osal_sem_take(usb_osal_sem_t sem, uint32_t timeout)
{
    int ret = 0;
    rt_err_t result = RT_EOK;

    if (timeout == USB_OSAL_WAITING_FOREVER) {
        result = rt_sem_take((rt_sem_t)sem, RT_WAITING_FOREVER);
    } else {
        result = rt_sem_take((rt_sem_t)sem, rt_tick_from_millisecond(timeout));
    }
    if (result == -RT_ETIMEOUT) {
        ret = -USB_ERR_TIMEOUT;
    } else if (result == -RT_ERROR) {
        ret = -USB_ERR_INVAL;
    } else {
        ret = 0;
    }

    return (int)ret;
}

int usb_osal_sem_give(usb_osal_sem_t sem)
{
    return (int)rt_sem_release((rt_sem_t)sem);
}

void usb_osal_sem_reset(usb_osal_sem_t sem)
{
    rt_sem_control((rt_sem_t)sem, RT_IPC_CMD_RESET, (void *)0);
}

usb_osal_mutex_t usb_osal_mutex_create(void)
{
    usb_osal_mutex_t mutex = (usb_osal_mutex_t)rt_mutex_create("usbh_mutex", RT_IPC_FLAG_FIFO);
    if (mutex == NULL) {
        USB_LOG_ERR("Create mutex failed\r\n");
        while (1) {
        }
    }
    return mutex;
}

void usb_osal_mutex_delete(usb_osal_mutex_t mutex)
{
    rt_mutex_delete((rt_mutex_t)mutex);
}

int usb_osal_mutex_take(usb_osal_mutex_t mutex)
{
    return (int)rt_mutex_take((rt_mutex_t)mutex, RT_WAITING_FOREVER);
}

int usb_osal_mutex_give(usb_osal_mutex_t mutex)
{
    return (int)rt_mutex_release((rt_mutex_t)mutex);
}

usb_osal_mq_t usb_osal_mq_create(uint32_t max_msgs)
{
    return (usb_osal_mq_t)rt_mq_create("usbh_mq", sizeof(uintptr_t), max_msgs, RT_IPC_FLAG_FIFO);
}

void usb_osal_mq_delete(usb_osal_mq_t mq)
{
    rt_mq_delete((rt_mq_t)mq);
}

int usb_osal_mq_send(usb_osal_mq_t mq, uintptr_t addr)
{
    return rt_mq_send((rt_mq_t)mq, &addr, sizeof(uintptr_t));
}

int usb_osal_mq_recv(usb_osal_mq_t mq, uintptr_t *addr, uint32_t timeout)
{
    int ret = 0;
    rt_err_t result = RT_EOK;

    if (timeout == USB_OSAL_WAITING_FOREVER) {
        result = rt_mq_recv((rt_mq_t)mq, addr, sizeof(uintptr_t), RT_WAITING_FOREVER);
    } else {
        result = rt_mq_recv((rt_mq_t)mq, addr, sizeof(uintptr_t), rt_tick_from_millisecond(timeout));
    }
    if (result == -RT_ETIMEOUT) {
        ret = -USB_ERR_TIMEOUT;
    } else if (result == -RT_ERROR) {
        ret = -USB_ERR_INVAL;
    } else {
        ret = 0;
    }

    return (int)ret;
}

struct usb_osal_timer *usb_osal_timer_create(const char *name, uint32_t timeout_ms, usb_timer_handler_t handler, void *argument, bool is_period)
{
    struct usb_osal_timer *timer;

    timer = rt_malloc(sizeof(struct usb_osal_timer));
    if (timer == NULL) {
        USB_LOG_ERR("Create usb_osal_timer failed\r\n");
        while (1) {
        }
    }
    memset(timer, 0, sizeof(struct usb_osal_timer));

    timer->timer = (void *)rt_timer_create(name, handler, argument, timeout_ms, is_period ? (RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER) : (RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_SOFT_TIMER));
    if (timer->timer == NULL) {
        USB_LOG_ERR("Create timer failed\r\n");
        while (1) {
        }
    }
    return timer;
}

void usb_osal_timer_delete(struct usb_osal_timer *timer)
{
    rt_timer_stop(timer->timer);
    rt_timer_delete(timer->timer);
    rt_free(timer);
}

void usb_osal_timer_start(struct usb_osal_timer *timer)
{
    rt_timer_start(timer->timer);
}

void usb_osal_timer_stop(struct usb_osal_timer *timer)
{
    rt_timer_stop(timer->timer);
}

size_t usb_osal_enter_critical_section(void)
{
    return rt_hw_interrupt_disable();
}

void usb_osal_leave_critical_section(size_t flag)
{
    rt_hw_interrupt_enable(flag);
}

void usb_osal_msleep(uint32_t delay)
{
    rt_thread_mdelay(delay);
}

void *usb_osal_malloc(size_t size)
{
    return rt_malloc(size);
}

void usb_osal_free(void *ptr)
{
    rt_free(ptr);
}