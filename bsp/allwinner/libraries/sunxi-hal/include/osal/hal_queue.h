#ifndef SUNXI_HAL_MAILBOX_H
#define SUNXI_HAL_MAILBOX_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>

#ifdef CONFIG_KERNEL_FREERTOS
#include <FreeRTOS.h>
#include <queue.h>
typedef QueueHandle_t hal_mailbox_t;
typedef QueueHandle_t hal_queue_t;
#else
#include <rtthread.h>
#include <rtdevice.h>
// #include <workqueue.h>
typedef rt_mailbox_t hal_mailbox_t;
typedef rt_mq_t hal_queue_t;
typedef struct rt_workqueue hal_workqueue;
typedef struct rt_work hal_work;

#define hal_work_init rt_work_init
hal_workqueue *hal_workqueue_create(const char *name, unsigned short stack_size, unsigned char priority);
int hal_workqueue_dowork(hal_workqueue *queue, hal_work *work);
#endif


enum IPC_MAILBOX_CMD
{
    IPC_MAILBOX_CMD_GET_STATE,
    IPC_MAILBOX_CMD_NUMS,
};


hal_mailbox_t hal_mailbox_create(const char *name, unsigned int size);
int hal_mailbox_delete(hal_mailbox_t mailbox);
int hal_mailbox_send(hal_mailbox_t mailbox, unsigned int value);
int hal_mailbox_send_wait(hal_mailbox_t mailbox, unsigned int value, int timeout);
int hal_mailbox_recv(hal_mailbox_t mailbox, unsigned int *value, int timeout);
int hal_is_mailbox_empty(hal_mailbox_t mailbox);

hal_queue_t hal_queue_create(const char *name, unsigned int item_size, unsigned int queue_size);
int hal_queue_delete(hal_queue_t queue);
int hal_queue_send(hal_queue_t queue, void *buffer);
int hal_queue_send_wait(hal_queue_t queue, void *buffer, int timeout);
int hal_queue_recv(hal_queue_t queue, void *buffer, int timeout);
int hal_is_queue_empty(hal_queue_t queue);

#ifdef __cplusplus
}
#endif
#endif
