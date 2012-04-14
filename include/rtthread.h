/*
 * File      : rtthread.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-18     Bernard      the first version
 * 2006-04-26     Bernard      add semaphore APIs
 * 2006-08-10     Bernard      add version information
 * 2007-01-28     Bernard      rename RT_OBJECT_Class_Static to RT_Object_Class_Static
 * 2007-03-03     Bernard      clean up the definitions to rtdef.h
 * 2010-04-11     yi.qiu       add module feature
 */

#ifndef __RT_THREAD_H__
#define __RT_THREAD_H__

#include <rtdef.h>
#include <rtdebug.h>
#include <rtservice.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup KernelObject
 */

/*@{*/

/*
 * kernel object interface
 */
void rt_system_object_init(void);
struct rt_object_information *rt_object_get_information(enum rt_object_class_type type);
void rt_object_init(struct rt_object *object, enum rt_object_class_type type, const char *name);
void rt_object_detach(rt_object_t object);
rt_object_t rt_object_allocate(enum rt_object_class_type type, const char *name);
void rt_object_delete(rt_object_t object);
rt_err_t rt_object_is_systemobject(rt_object_t object);
rt_object_t rt_object_find(const char *name, rt_uint8_t type);

#ifdef RT_USING_HOOK
void rt_object_attach_sethook(void (*hook)(struct rt_object *object));
void rt_object_detach_sethook(void (*hook)(struct rt_object *object));
void rt_object_trytake_sethook(void (*hook)(struct rt_object *object));
void rt_object_take_sethook(void (*hook)(struct rt_object *object));
void rt_object_put_sethook(void (*hook)(struct rt_object *object));
#endif

/*@}*/

/**
 * @addtogroup Clock
 */

/*@{*/

/*
 * clock & timer interface
 */
void rt_system_tick_init(void);
rt_tick_t rt_tick_get(void);
void rt_tick_set(rt_tick_t tick);
void rt_tick_increase(void);
rt_tick_t rt_tick_from_millisecond(rt_uint32_t ms);

void rt_system_timer_init(void);
void rt_system_timer_thread_init(void);

void rt_timer_init(rt_timer_t timer,
	const char *name,
	void (*timeout)(void *parameter), void *parameter,
	rt_tick_t time, rt_uint8_t flag);
rt_err_t rt_timer_detach(rt_timer_t timer);
rt_timer_t rt_timer_create(const char *name,
	void (*timeout)(void *parameter), void *parameter,
	rt_tick_t time, rt_uint8_t flag);
rt_err_t rt_timer_delete(rt_timer_t timer);
rt_err_t rt_timer_start(rt_timer_t timer);
rt_err_t rt_timer_stop(rt_timer_t timer);
rt_err_t rt_timer_control(rt_timer_t timer, rt_uint8_t cmd, void *arg);

#ifdef RT_USING_HOOK
void rt_timer_timeout_sethook(void (*hook)(struct rt_timer *timer));
#endif

/*@}*/

/**
 * @addtogroup Thread
 */

/*@{*/

/*
 * thread interface
 */
rt_err_t rt_thread_init(struct rt_thread *thread,
	const char *name,
	void (*entry)(void *parameter), void *parameter,
	void *stack_start, rt_uint32_t stack_size,
	rt_uint8_t priority, rt_uint32_t tick);
rt_err_t rt_thread_detach(rt_thread_t thread);
rt_thread_t rt_thread_create(const char *name,
	void (*entry)(void *parameter), void *parameter,
	rt_uint32_t stack_size,
	rt_uint8_t priority, rt_uint32_t tick);
rt_thread_t rt_thread_self(void);
rt_thread_t rt_thread_find(char *name);
rt_err_t rt_thread_startup(rt_thread_t thread);
rt_err_t rt_thread_delete(rt_thread_t thread);

rt_err_t rt_thread_yield(void);
rt_err_t rt_thread_delay(rt_tick_t tick);
rt_err_t rt_thread_control(rt_thread_t thread, rt_uint8_t cmd, void *arg);
rt_err_t rt_thread_suspend(rt_thread_t thread);
rt_err_t rt_thread_resume(rt_thread_t thread);
void rt_thread_timeout(void *parameter);

/*
 * idle thread interface
 */
void rt_thread_idle_init(void);
#ifdef RT_USING_HOOK
void rt_thread_idle_sethook(void (*hook)(void));
#endif
void rt_thread_idle_excute(void);

/*
 * schedule service
 */
void rt_system_scheduler_init(void);
void rt_system_scheduler_start(void);

void rt_schedule(void);
void rt_schedule_insert_thread(struct rt_thread *thread);
void rt_schedule_remove_thread(struct rt_thread *thread);

void rt_enter_critical(void);
void rt_exit_critical(void);

#ifdef RT_USING_HOOK
void rt_scheduler_sethook(void (*hook)(rt_thread_t from, rt_thread_t to));
#endif

/*@}*/

/**
 * @addtogroup MM
 */

/*@{*/

/*
 * memory management interface
 */
#ifdef RT_USING_MEMPOOL
/*
 * memory pool interface
 */
rt_err_t rt_mp_init(struct rt_mempool *mp, const char *name, void *start, rt_size_t size, rt_size_t block_size);
rt_err_t rt_mp_detach(struct rt_mempool *mp);
rt_mp_t rt_mp_create(const char *name, rt_size_t block_count, rt_size_t block_size);
rt_err_t rt_mp_delete(rt_mp_t mp);

void *rt_mp_alloc(rt_mp_t mp, rt_int32_t time);
void rt_mp_free(void *block);

#ifdef RT_USING_HOOK
void rt_mp_alloc_sethook(void (*hook)(struct rt_mempool *mp, void *block));
void rt_mp_free_sethook(void (*hook)(struct rt_mempool *mp, void *block));
#endif

#endif

#ifdef RT_USING_HEAP
/*
 * heap memory interface
 */
void rt_system_heap_init(void *begin_addr, void *end_addr);

void *rt_malloc(rt_size_t nbytes);
void rt_free(void *ptr);
void *rt_realloc(void *ptr, rt_size_t nbytes);
void *rt_calloc(rt_size_t count, rt_size_t size);
void *rt_malloc_align(rt_size_t size, rt_size_t align);
void rt_free_align(void *ptr);

void rt_memory_info(rt_uint32_t *total, rt_uint32_t *used, rt_uint32_t *max_used);

#ifdef RT_USING_SLAB
void *rt_page_alloc(rt_size_t npages);
void rt_page_free(void *addr, rt_size_t npages);
#endif

#ifdef RT_USING_HOOK
void rt_malloc_sethook(void (*hook)(void *ptr, rt_uint32_t size));
void rt_free_sethook(void (*hook)(void *ptr));
#endif

#endif

#ifdef RT_USING_MEMHEAP
/**
 * memory heap object interface
 */
rt_err_t rt_memheap_init(struct rt_memheap* memheap, const char* name,
	void *start_addr, rt_uint32_t size);
rt_err_t rt_memheap_detach(struct rt_memheap* heap);
void* rt_memheap_alloc(struct rt_memheap *heap, 	rt_uint32_t size);
void rt_memheap_free(void* ptr);

#endif

/*@}*/

/**
 * @addtogroup IPC
 */

/*@{*/

#ifdef RT_USING_SEMAPHORE
/*
 * semaphore interface
 */
rt_err_t rt_sem_init(rt_sem_t sem, const char *name, rt_uint32_t value, rt_uint8_t flag);
rt_err_t rt_sem_detach(rt_sem_t sem);
rt_sem_t rt_sem_create(const char *name, rt_uint32_t value, rt_uint8_t flag);
rt_err_t rt_sem_delete(rt_sem_t sem);

rt_err_t rt_sem_take(rt_sem_t sem, rt_int32_t time);
rt_err_t rt_sem_trytake(rt_sem_t sem);
rt_err_t rt_sem_release(rt_sem_t sem);
rt_err_t rt_sem_control(rt_sem_t sem, rt_uint8_t cmd, void *arg);
#endif

#ifdef RT_USING_MUTEX
/*
 * mutex interface
 */
rt_err_t rt_mutex_init(rt_mutex_t mutex, const char *name, rt_uint8_t flag);
rt_err_t rt_mutex_detach(rt_mutex_t mutex);
rt_mutex_t rt_mutex_create(const char *name, rt_uint8_t flag);
rt_err_t rt_mutex_delete(rt_mutex_t mutex);

rt_err_t rt_mutex_take(rt_mutex_t mutex, rt_int32_t time);
rt_err_t rt_mutex_release(rt_mutex_t mutex);
rt_err_t rt_mutex_control(rt_mutex_t mutex, rt_uint8_t cmd, void *arg);
#endif

#ifdef RT_USING_EVENT
/*
 * event interface
 */
rt_err_t rt_event_init(rt_event_t event, const char *name, rt_uint8_t flag);
rt_err_t rt_event_detach(rt_event_t event);
rt_event_t rt_event_create(const char *name, rt_uint8_t flag);
rt_err_t rt_event_delete(rt_event_t event);

rt_err_t rt_event_send(rt_event_t event, rt_uint32_t set);
rt_err_t rt_event_recv(rt_event_t event, rt_uint32_t set, rt_uint8_t opt, rt_int32_t timeout, rt_uint32_t *recved);
rt_err_t rt_event_control(rt_event_t event, rt_uint8_t cmd, void *arg);
#endif

#ifdef RT_USING_MAILBOX
/*
 * mailbox interface
 */
rt_err_t rt_mb_init(rt_mailbox_t mb, const char *name, void *msgpool, rt_size_t size, rt_uint8_t flag);
rt_err_t rt_mb_detach(rt_mailbox_t mb);
rt_mailbox_t rt_mb_create(const char *name, rt_size_t size, rt_uint8_t flag);
rt_err_t rt_mb_delete(rt_mailbox_t mb);

rt_err_t rt_mb_send(rt_mailbox_t mb, rt_uint32_t value);
rt_err_t rt_mb_send_wait(rt_mailbox_t mb, rt_uint32_t value, rt_int32_t timeout);
rt_err_t rt_mb_recv(rt_mailbox_t mb, rt_uint32_t *value, rt_int32_t timeout);
rt_err_t rt_mb_control(rt_mailbox_t mb, rt_uint8_t cmd, void *arg);
#endif

#ifdef RT_USING_MESSAGEQUEUE
/*
 * message queue interface
 */
rt_err_t rt_mq_init(rt_mq_t mq, const char *name, void *msgpool, rt_size_t msg_size, rt_size_t pool_size, rt_uint8_t flag);
rt_err_t rt_mq_detach(rt_mq_t mq);
rt_mq_t rt_mq_create(const char *name, rt_size_t msg_size, rt_size_t max_msgs, rt_uint8_t flag);
rt_err_t rt_mq_delete(rt_mq_t mq);

rt_err_t rt_mq_send(rt_mq_t mq, void *buffer, rt_size_t size);
rt_err_t rt_mq_urgent(rt_mq_t mq, void *buffer, rt_size_t size);
rt_err_t rt_mq_recv(rt_mq_t mq, void *buffer, rt_size_t size, rt_int32_t timeout);
rt_err_t rt_mq_control(rt_mq_t mq, rt_uint8_t cmd, void *arg);
#endif

/*@}*/

#ifdef RT_USING_DEVICE
/**
 * @addtogroup Device
 */

/*@{*/

/*
 * device (I/O) system interface
 */
rt_device_t rt_device_find(const char *name);

rt_err_t rt_device_register(rt_device_t dev, const char *name, rt_uint16_t flags);
rt_err_t rt_device_unregister(rt_device_t dev);
rt_err_t rt_device_init_all(void);

rt_err_t rt_device_set_rx_indicate(rt_device_t dev, rt_err_t (*rx_ind )(rt_device_t dev, rt_size_t size));
rt_err_t rt_device_set_tx_complete(rt_device_t dev, rt_err_t (*tx_done)(rt_device_t dev, void *buffer));

rt_err_t  rt_device_init (rt_device_t dev);
rt_err_t  rt_device_open (rt_device_t dev, rt_uint16_t oflag);
rt_err_t  rt_device_close(rt_device_t dev);
rt_size_t rt_device_read (rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
rt_size_t rt_device_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
rt_err_t  rt_device_control(rt_device_t dev, rt_uint8_t cmd, void *arg);

/*@}*/
#endif

#ifdef RT_USING_MODULE
/**
 * @addtogroup Module
 */

/*@{*/

/*
 * module interface
 */
rt_module_t rt_module_load(const char *name, void *module_ptr);
rt_err_t rt_module_unload(rt_module_t module);
rt_module_t rt_module_open(const char *filename);
void *rt_module_malloc(rt_size_t size);
void *rt_module_realloc(void *ptr, rt_size_t size);
void rt_module_free(rt_module_t module, void *addr);
rt_module_t rt_module_self(void);
rt_err_t rt_module_set(rt_module_t module);
rt_module_t rt_module_find(const char *name);

#ifdef RT_USING_HOOK
void rt_module_load_sethook(void (*hook)(rt_module_t module));
void rt_module_unload_sethook(void (*hook)(rt_module_t module));
#endif

/*@}*/
#endif
 
/*
 * interrupt service
 */
typedef void (*rt_isr_handler_t)(int vector);

/*
 * rt_interrupt_enter and rt_interrupt_leave only can be called by BSP
 */
void rt_interrupt_enter(void);
void rt_interrupt_leave(void);

/*
 * the number of nested interrupts.
 */
rt_uint8_t rt_interrupt_get_nest(void);

/**
 * @addtogroup KernelService
 */

/*@{*/

/*
 * general kernel service
 */
void rt_kprintf(const char *fmt, ...);
rt_int32_t rt_vsprintf(char *dest, const char *format, va_list arg_ptr);
rt_int32_t rt_sprintf(char *buf ,const char *format, ...);
rt_int32_t rt_snprintf(char *buf, rt_size_t size, const char *format, ...);

#ifdef RT_USING_DEVICE
rt_device_t rt_console_set_device(const char *name);
#endif

rt_err_t rt_get_errno(void);
void rt_set_errno(rt_err_t no);
int *_rt_errno(void);
#ifndef RT_USING_NEWLIB
#ifndef errno
#define errno	*_rt_errno()
#endif
#endif

void *rt_memset(void *src, int c, rt_ubase_t n);
void *rt_memcpy(void *dest, const void *src, rt_ubase_t n);

rt_ubase_t rt_strncmp(const char *cs, const char *ct, rt_ubase_t count);
rt_ubase_t rt_strcmp (const char *cs, const char *ct);
rt_ubase_t rt_strlen (const char *src);
char *rt_strdup(const char *s);

char *rt_strstr(const char *str1, const char *str2);
rt_int32_t rt_sscanf(const char *buf, const char *fmt, ...);
char *rt_strncpy(char *dest, const char *src, rt_ubase_t n);
void *rt_memmove(void *dest, const void *src, rt_ubase_t n);
rt_int32_t rt_memcmp(const void *cs, const void *ct, rt_ubase_t count);
rt_uint32_t rt_strcasecmp(const char *a, const char *b);

void rt_show_version(void);

/*@}*/

#ifdef __cplusplus
}
#endif

#endif
