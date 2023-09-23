/*
 * ===========================================================================================
 *
 *       Filename:  hal_mailbox.c
 *
 *    Description:  mbox impl.for hal.
 *
 *        Version:  Melis3.0
 *         Create:  2019-11-27 17:32:09
 *       Revision:  none
 *       Compiler:  GCC:version 7.2.1 20170904 (release),ARM/embedded-7-branch revision 255204
 *
 *         Author:  caozilong@allwinnertech.com
 *   Organization:  BU1-PSW
 *  Last Modified:  2019-11-27 18:02:12
 *
 * ===========================================================================================
 */

#include <hal_queue.h>
#include <rtdef.h>
#include <rtthread.h>
#include <log.h>

hal_mailbox_t hal_mailbox_create(const char *name, unsigned int size)
{
    return rt_mb_create("hal_layer", size, RT_IPC_FLAG_FIFO);
}

int hal_mailbox_delete(hal_mailbox_t mailbox)
{
    if (mailbox == NULL)
    {
        __err("fatal error, parameter is invalid.");
        return -1;
    }

    rt_mb_delete(mailbox);
    return 0;
}

int hal_mailbox_send(hal_mailbox_t mailbox, unsigned int value)
{
    rt_err_t ret;

    if (mailbox == NULL)
    {
        __err("fatal error, parameter is invalid.");
        return -1;
    }

    ret = rt_mb_send(mailbox, value);
    if (ret != RT_EOK)
    {
        // timeout.
        return -2;
    }

    return 0;
}

int hal_mailbox_send_wait(hal_mailbox_t mailbox, unsigned int value, int timeout)
{
    rt_err_t ret;

    if (mailbox == NULL)
    {
        __err("fatal error, parameter is invalid.");
        return -1;
    }

    ret = rt_mb_send_wait(mailbox, value, timeout);
    if (ret != RT_EOK)
    {
        // timeout.
        return -2;
    }

    return 0;
}

int hal_mailbox_recv(hal_mailbox_t mailbox, unsigned int *value, int timeout)
{
    rt_err_t ret;

    if (mailbox == NULL || value == NULL)
    {
        __err("fatal error, parameter is invalid.");
        return -1;
    }

    ret = rt_mb_recv(mailbox, (rt_ubase_t *)value, timeout);
    if (ret != RT_EOK)
    {
        // timeout.
        return -2;
    }

    return 0;
}

int hal_is_mailbox_empty(hal_mailbox_t mailbox)
{
    rt_err_t ret = -1;
    int arg;

    if (mailbox == NULL)
    {
        __err("fatal error, parameter is invalid.");
        return -1;
    }

    ret = rt_mb_control(mailbox, RT_IPC_CMD_GET_STATE, &arg);
    if (ret != RT_EOK)
        return -2;

    return (arg == 0)? 1: 0;
}

hal_workqueue *hal_workqueue_create(const char *name, unsigned short stack_size, unsigned char priority)
{
    return rt_workqueue_create(name, stack_size, priority);
}

int hal_workqueue_dowork(hal_workqueue *queue, hal_work *work)
{
    int ret = 0;
    ret = rt_workqueue_dowork(queue, work);
    return ret;
}

hal_queue_t hal_queue_create(const char *name, unsigned int item_size, unsigned int queue_size)
{
    return rt_mq_create("hal_layer", item_size, queue_size, RT_IPC_FLAG_FIFO);
}

int hal_queue_delete(hal_queue_t queue)
{
    if (queue == NULL)
    {
        __err("fatal error, parameter is invalid.");
        return -1;
    }

    rt_mq_delete(queue);
    return 0;

}

int hal_queue_send_wait(hal_queue_t queue, void *buffer, int timeout)
{
    rt_err_t ret;

    if (queue == NULL)
    {
        __err("fatal error, parameter is invalid.");
        return -1;
    }

    ret = rt_mq_send_wait(queue, buffer, queue->msg_size, timeout);
    if (ret != RT_EOK)
    {
        return -2;
    }

    return 0;
}

int hal_queue_send(hal_queue_t queue, void *buffer)
{
    return hal_queue_send_wait(queue, buffer, 0);
}

int hal_queue_recv(hal_queue_t queue, void *buffer, int timeout)
{
    rt_err_t ret;

    if (queue == NULL)
    {
        __err("fatal error, parameter is invalid.");
        return -1;
    }

    ret = rt_mq_recv(queue, buffer, queue->msg_size, timeout);
    if (ret < 0)
    {
        return -2;
    }

    return 0;

}

int hal_is_queue_empty(hal_queue_t queue)
{
    rt_err_t ret = -1;
    int arg;

    if (queue == NULL)
    {
        __err("fatal error, parameter is invalid.");
        return -1;
    }

    ret = rt_mq_control(queue, RT_IPC_CMD_GET_STATE, &arg);
    if (ret != RT_EOK)
        return -2;

    return (arg == 0)? 1: 0;
}
