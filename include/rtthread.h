/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-18     Bernard      the first version
 * 2006-04-26     Bernard      add semaphore APIs
 * 2006-08-10     Bernard      add version information
 * 2007-01-28     Bernard      rename RT_OBJECT_Class_Static to RT_Object_Class_Static
 * 2007-03-03     Bernard      clean up the definitions to rtdef.h
 * 2010-04-11     yi.qiu       add module feature
 * 2013-06-24     Bernard      add rt_kprintf re-define when not use RT_USING_CONSOLE.
 * 2016-08-09     ArdaFu       add new thread and interrupt hook.
 * 2018-11-22     Jesven       add all cpu's lock and ipi handler
 * 2021-02-28     Meco Man     add RT_KSERVICE_USING_STDLIB
 * 2021-11-14     Meco Man     add rtlegacy.h for compatibility
 * 2022-06-04     Meco Man     remove strnlen
 * 2023-05-20     Bernard      add rtatomic.h header file to included files.
 * 2023-06-30     ChuShicheng  move debug check from the rtdebug.h
 * 2023-10-16     Shell        Support a new backtrace framework
 * 2023-12-10     xqyjlj       fix spinlock in up
 * 2024-01-25     Shell        Add rt_susp_list for IPC primitives
 * 2024-03-10     Meco Man     move std libc related functions to rtklibc
 */

#ifndef __RT_THREAD_H__
#define __RT_THREAD_H__

#include <rtconfig.h>
#include <rtdef.h>
#include <rtservice.h>
#include <rtm.h>
#include <rtatomic.h>
#include <rtklibc.h>
#ifdef RT_USING_LEGACY
#include <rtlegacy.h>
#endif
#ifdef RT_USING_FINSH
#include <finsh.h>
#endif /* RT_USING_FINSH */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __GNUC__
int entry(void);
#endif

/**
 * @addtogroup KernelObject
 * @{
 */

/*
 * kernel object interface
 */
struct rt_object_information *
rt_object_get_information(enum rt_object_class_type type);
int rt_object_get_length(enum rt_object_class_type type);
int rt_object_get_pointers(enum rt_object_class_type type, rt_object_t *pointers, int maxlen);

void rt_object_init(struct rt_object         *object,
                    enum rt_object_class_type type,
                    const char               *name);
void rt_object_detach(rt_object_t object);
#ifdef RT_USING_HEAP
rt_object_t rt_object_allocate(enum rt_object_class_type type, const char *name);
void rt_object_delete(rt_object_t object);
/* custom object */
rt_object_t rt_custom_object_create(const char *name, void *data, rt_err_t (*data_destroy)(void *));
rt_err_t rt_custom_object_destroy(rt_object_t obj);
#endif /* RT_USING_HEAP */
rt_bool_t rt_object_is_systemobject(rt_object_t object);
rt_uint8_t rt_object_get_type(rt_object_t object);
rt_err_t rt_object_for_each(rt_uint8_t type, rt_object_iter_t iter, void *data);
rt_object_t rt_object_find(const char *name, rt_uint8_t type);
rt_err_t rt_object_get_name(rt_object_t object, char *name, rt_uint8_t name_size);

#ifdef RT_USING_HOOK
void rt_object_attach_sethook(void (*hook)(struct rt_object *object));
void rt_object_detach_sethook(void (*hook)(struct rt_object *object));
void rt_object_trytake_sethook(void (*hook)(struct rt_object *object));
void rt_object_take_sethook(void (*hook)(struct rt_object *object));
void rt_object_put_sethook(void (*hook)(struct rt_object *object));
#endif /* RT_USING_HOOK */

/**@}*/

/**
 * @addtogroup Clock
 * @{
 */

/*
 * clock & timer interface
 */
rt_tick_t rt_tick_get(void);
void rt_tick_set(rt_tick_t tick);
void rt_tick_increase(void);
void rt_tick_increase_tick(rt_tick_t tick);
rt_tick_t  rt_tick_from_millisecond(rt_int32_t ms);
rt_tick_t rt_tick_get_millisecond(void);
#ifdef RT_USING_HOOK
void rt_tick_sethook(void (*hook)(void));
#endif /* RT_USING_HOOK */

void rt_system_timer_init(void);
void rt_system_timer_thread_init(void);

void rt_timer_init(rt_timer_t  timer,
                   const char *name,
                   void (*timeout)(void *parameter),
                   void       *parameter,
                   rt_tick_t   time,
                   rt_uint8_t  flag);
rt_err_t rt_timer_detach(rt_timer_t timer);
#ifdef RT_USING_HEAP
rt_timer_t rt_timer_create(const char *name,
                           void (*timeout)(void *parameter),
                           void       *parameter,
                           rt_tick_t   time,
                           rt_uint8_t  flag);
rt_err_t rt_timer_delete(rt_timer_t timer);
#endif /* RT_USING_HEAP */
rt_err_t rt_timer_start(rt_timer_t timer);
rt_err_t rt_timer_stop(rt_timer_t timer);
rt_err_t rt_timer_control(rt_timer_t timer, int cmd, void *arg);
rt_tick_t rt_timer_next_timeout_tick(void);
void rt_timer_check(void);
#ifdef RT_USING_HOOK
void rt_timer_enter_sethook(void (*hook)(struct rt_timer *timer));
void rt_timer_exit_sethook(void (*hook)(struct rt_timer *timer));
#endif /* RT_USING_HOOK */

/**@}*/

/**
 * @addtogroup Thread
 * @{
 */

/*
 * thread interface
 */
rt_err_t rt_thread_init(struct rt_thread *thread,
                        const char       *name,
                        void (*entry)(void *parameter),
                        void             *parameter,
                        void             *stack_start,
                        rt_uint32_t       stack_size,
                        rt_uint8_t        priority,
                        rt_uint32_t       tick);
rt_err_t rt_thread_detach(rt_thread_t thread);
#ifdef RT_USING_HEAP
rt_thread_t rt_thread_create(const char *name,
                             void (*entry)(void *parameter),
                             void       *parameter,
                             rt_uint32_t stack_size,
                             rt_uint8_t  priority,
                             rt_uint32_t tick);
rt_err_t rt_thread_delete(rt_thread_t thread);
#endif /* RT_USING_HEAP */
rt_err_t rt_thread_close(rt_thread_t thread);
rt_thread_t rt_thread_self(void);
rt_thread_t rt_thread_find(char *name);
rt_err_t rt_thread_startup(rt_thread_t thread);
rt_err_t rt_thread_yield(void);
rt_err_t rt_thread_delay(rt_tick_t tick);
rt_err_t rt_thread_delay_until(rt_tick_t *tick, rt_tick_t inc_tick);
rt_err_t rt_thread_mdelay(rt_int32_t ms);
rt_err_t rt_thread_control(rt_thread_t thread, int cmd, void *arg);
rt_err_t rt_thread_suspend(rt_thread_t thread);
rt_err_t rt_thread_suspend_with_flag(rt_thread_t thread, int suspend_flag);
rt_err_t rt_thread_resume(rt_thread_t thread);
#ifdef RT_USING_SMART
rt_err_t rt_thread_wakeup(rt_thread_t thread);
void rt_thread_wakeup_set(struct rt_thread *thread, rt_wakeup_func_t func, void* user_data);
#endif /* RT_USING_SMART */
rt_err_t rt_thread_get_name(rt_thread_t thread, char *name, rt_uint8_t name_size);
#ifdef RT_USING_SIGNALS
void rt_thread_alloc_sig(rt_thread_t tid);
void rt_thread_free_sig(rt_thread_t tid);
int  rt_thread_kill(rt_thread_t tid, int sig);
#endif /* RT_USING_SIGNALS */
#ifdef RT_USING_HOOK
void rt_thread_suspend_sethook(void (*hook)(rt_thread_t thread));
void rt_thread_resume_sethook (void (*hook)(rt_thread_t thread));

/**
 * @brief Sets a hook function when a thread is initialized.
 *
 * @param thread is the target thread that initializing
 */
typedef void (*rt_thread_inited_hookproto_t)(rt_thread_t thread);
RT_OBJECT_HOOKLIST_DECLARE(rt_thread_inited_hookproto_t, rt_thread_inited);

#endif /* RT_USING_HOOK */

/*
 * idle thread interface
 */
void rt_thread_idle_init(void);
#if defined(RT_USING_HOOK) || defined(RT_USING_IDLE_HOOK)
rt_err_t rt_thread_idle_sethook(void (*hook)(void));
rt_err_t rt_thread_idle_delhook(void (*hook)(void));
#endif /* defined(RT_USING_HOOK) || defined(RT_USING_IDLE_HOOK) */
rt_thread_t rt_thread_idle_gethandler(void);

/*
 * schedule service
 */
void rt_system_scheduler_init(void);
void rt_system_scheduler_start(void);

void rt_schedule(void);
void rt_scheduler_do_irq_switch(void *context);

#ifdef RT_USING_OVERFLOW_CHECK
void rt_scheduler_stack_check(struct rt_thread *thread);

#define RT_SCHEDULER_STACK_CHECK(thr) rt_scheduler_stack_check(thr)

#else /* !RT_USING_OVERFLOW_CHECK */

#define RT_SCHEDULER_STACK_CHECK(thr)

#endif /* RT_USING_OVERFLOW_CHECK */

rt_base_t rt_enter_critical(void);
void rt_exit_critical(void);
void rt_exit_critical_safe(rt_base_t critical_level);
rt_uint16_t rt_critical_level(void);

#ifdef RT_USING_HOOK
void rt_scheduler_sethook(void (*hook)(rt_thread_t from, rt_thread_t to));
void rt_scheduler_switch_sethook(void (*hook)(struct rt_thread *tid));
#endif /* RT_USING_HOOK */

#ifdef RT_USING_SMP
void rt_secondary_cpu_entry(void);
void rt_scheduler_ipi_handler(int vector, void *param);
#endif /* RT_USING_SMP */

/**@}*/

/**
 * @addtogroup Signal
 * @{
 */
#ifdef RT_USING_SIGNALS
void rt_signal_mask(int signo);
void rt_signal_unmask(int signo);
rt_sighandler_t rt_signal_install(int signo, rt_sighandler_t handler);
int rt_signal_wait(const rt_sigset_t *set, rt_siginfo_t *si, rt_int32_t timeout);
int rt_system_signal_init(void);
#endif /* RT_USING_SIGNALS */
/**@}*/

/**
 * @addtogroup MM
 * @{
 */

/*
 * memory management interface
 */
#ifdef RT_USING_MEMPOOL
/*
 * memory pool interface
 */
rt_err_t rt_mp_init(struct rt_mempool *mp,
                    const char        *name,
                    void              *start,
                    rt_size_t          size,
                    rt_size_t          block_size);
rt_err_t rt_mp_detach(struct rt_mempool *mp);
#ifdef RT_USING_HEAP
rt_mp_t rt_mp_create(const char *name,
                     rt_size_t   block_count,
                     rt_size_t   block_size);
rt_err_t rt_mp_delete(rt_mp_t mp);
#endif /* RT_USING_HEAP */
void *rt_mp_alloc(rt_mp_t mp, rt_int32_t time);
void rt_mp_free(void *block);
#ifdef RT_USING_HOOK
void rt_mp_alloc_sethook(void (*hook)(struct rt_mempool *mp, void *block));
void rt_mp_free_sethook(void (*hook)(struct rt_mempool *mp, void *block));
#endif /* RT_USING_HOOK */

#endif /* RT_USING_MEMPOOL */

#ifdef RT_USING_HEAP
/*
 * heap memory interface
 */
void rt_system_heap_init(void *begin_addr, void *end_addr);
void rt_system_heap_init_generic(void *begin_addr, void *end_addr);

void *rt_malloc(rt_size_t size);
void rt_free(void *ptr);
void *rt_realloc(void *ptr, rt_size_t newsize);
void *rt_calloc(rt_size_t count, rt_size_t size);
void *rt_malloc_align(rt_size_t size, rt_size_t align);
void rt_free_align(void *ptr);

void rt_memory_info(rt_size_t *total,
                    rt_size_t *used,
                    rt_size_t *max_used);

#if defined(RT_USING_SLAB) && defined(RT_USING_SLAB_AS_HEAP)
void *rt_page_alloc(rt_size_t npages);
void rt_page_free(void *addr, rt_size_t npages);
#endif /* defined(RT_USING_SLAB) && defined(RT_USING_SLAB_AS_HEAP) */

/**
 * @ingroup Hook
 * @{
 */

#ifdef RT_USING_HOOK
void rt_malloc_sethook(void (*hook)(void **ptr, rt_size_t size));
void rt_realloc_set_entry_hook(void (*hook)(void **ptr, rt_size_t size));
void rt_realloc_set_exit_hook(void (*hook)(void **ptr, rt_size_t size));
void rt_free_sethook(void (*hook)(void **ptr));
#endif /* RT_USING_HOOK */
/**@}*/

#endif /* RT_USING_HEAP */

#ifdef RT_USING_SMALL_MEM
/**
 * small memory object interface
 */
rt_smem_t rt_smem_init(const char    *name,
                     void          *begin_addr,
                     rt_size_t      size);
rt_err_t rt_smem_detach(rt_smem_t m);
void *rt_smem_alloc(rt_smem_t m, rt_size_t size);
void *rt_smem_realloc(rt_smem_t m, void *rmem, rt_size_t newsize);
void rt_smem_free(void *rmem);
#endif /* RT_USING_SMALL_MEM */

#ifdef RT_USING_MEMHEAP
/**
 * memory heap object interface
 */
rt_err_t rt_memheap_init(struct rt_memheap *memheap,
                         const char        *name,
                         void              *start_addr,
                         rt_size_t         size);
rt_err_t rt_memheap_detach(struct rt_memheap *heap);
void *rt_memheap_alloc(struct rt_memheap *heap, rt_size_t size);
void *rt_memheap_realloc(struct rt_memheap *heap, void *ptr, rt_size_t newsize);
void rt_memheap_free(void *ptr);
void rt_memheap_info(struct rt_memheap *heap,
                     rt_size_t *total,
                     rt_size_t *used,
                     rt_size_t *max_used);
#endif /* RT_USING_MEMHEAP */

#ifdef RT_USING_MEMHEAP_AS_HEAP
/**
 * memory heap as heap
 */
void *_memheap_alloc(struct rt_memheap *heap, rt_size_t size);
void _memheap_free(void *rmem);
void *_memheap_realloc(struct rt_memheap *heap, void *rmem, rt_size_t newsize);
#endif

#ifdef RT_USING_SLAB
/**
 * slab object interface
 */
rt_slab_t rt_slab_init(const char *name, void *begin_addr, rt_size_t size);
rt_err_t rt_slab_detach(rt_slab_t m);
void *rt_slab_page_alloc(rt_slab_t m, rt_size_t npages);
void rt_slab_page_free(rt_slab_t m, void *addr, rt_size_t npages);
void *rt_slab_alloc(rt_slab_t m, rt_size_t size);
void *rt_slab_realloc(rt_slab_t m, void *ptr, rt_size_t size);
void rt_slab_free(rt_slab_t m, void *ptr);
#endif /* RT_USING_SLAB */

/**@}*/

/**
 * @addtogroup IPC
 * @{
 */

/**
 * Suspend list - A basic building block for IPC primitives which interacts with
 *                scheduler directly. Its API is similar to a FIFO list.
 *
 * Note: don't use in application codes directly
 */
void rt_susp_list_print(rt_list_t *list);
/* reserve thread error while resuming it */
#define RT_THREAD_RESUME_RES_THR_ERR (-1)
struct rt_thread *rt_susp_list_dequeue(rt_list_t *susp_list, rt_err_t thread_error);
rt_err_t rt_susp_list_resume_all(rt_list_t *susp_list, rt_err_t thread_error);
rt_err_t rt_susp_list_resume_all_irq(rt_list_t *susp_list,
                                     rt_err_t thread_error,
                                     struct rt_spinlock *lock);

/* suspend and enqueue */
rt_err_t rt_thread_suspend_to_list(rt_thread_t thread, rt_list_t *susp_list, int ipc_flags, int suspend_flag);
/* only for a suspended thread, and caller must hold the scheduler lock */
rt_err_t rt_susp_list_enqueue(rt_list_t *susp_list, rt_thread_t thread, int ipc_flags);

/**
 * @addtogroup semaphore
 * @{
 */

#ifdef RT_USING_SEMAPHORE
/*
 * semaphore interface
 */
rt_err_t rt_sem_init(rt_sem_t    sem,
                     const char *name,
                     rt_uint32_t value,
                     rt_uint8_t  flag);
rt_err_t rt_sem_detach(rt_sem_t sem);
#ifdef RT_USING_HEAP
rt_sem_t rt_sem_create(const char *name, rt_uint32_t value, rt_uint8_t flag);
rt_err_t rt_sem_delete(rt_sem_t sem);
#endif /* RT_USING_HEAP */

rt_err_t rt_sem_take(rt_sem_t sem, rt_int32_t timeout);
rt_err_t rt_sem_take_interruptible(rt_sem_t sem, rt_int32_t timeout);
rt_err_t rt_sem_take_killable(rt_sem_t sem, rt_int32_t timeout);
rt_err_t rt_sem_trytake(rt_sem_t sem);
rt_err_t rt_sem_release(rt_sem_t sem);
rt_err_t rt_sem_control(rt_sem_t sem, int cmd, void *arg);
#endif /* RT_USING_SEMAPHORE */

/**@}*/

/**
 * @addtogroup mutex
 * @{
 */

#ifdef RT_USING_MUTEX
/*
 * mutex interface
 */
rt_err_t rt_mutex_init(rt_mutex_t mutex, const char *name, rt_uint8_t flag);
rt_err_t rt_mutex_detach(rt_mutex_t mutex);
#ifdef RT_USING_HEAP
rt_mutex_t rt_mutex_create(const char *name, rt_uint8_t flag);
rt_err_t rt_mutex_delete(rt_mutex_t mutex);
#endif /* RT_USING_HEAP */
void rt_mutex_drop_thread(rt_mutex_t mutex, rt_thread_t thread);
rt_uint8_t rt_mutex_setprioceiling(rt_mutex_t mutex, rt_uint8_t priority);
rt_uint8_t rt_mutex_getprioceiling(rt_mutex_t mutex);

rt_err_t rt_mutex_take(rt_mutex_t mutex, rt_int32_t timeout);
rt_err_t rt_mutex_trytake(rt_mutex_t mutex);
rt_err_t rt_mutex_take_interruptible(rt_mutex_t mutex, rt_int32_t time);
rt_err_t rt_mutex_take_killable(rt_mutex_t mutex, rt_int32_t time);
rt_err_t rt_mutex_release(rt_mutex_t mutex);
rt_err_t rt_mutex_control(rt_mutex_t mutex, int cmd, void *arg);

rt_inline rt_thread_t rt_mutex_get_owner(rt_mutex_t mutex)
{
    return mutex->owner;
}
rt_inline rt_ubase_t rt_mutex_get_hold(rt_mutex_t mutex)
{
    return mutex->hold;
}

#endif /* RT_USING_MUTEX */

/**@}*/

/**
 * @addtogroup event
 * @{
 */

#ifdef RT_USING_EVENT
/*
 * event interface
 */
rt_err_t rt_event_init(rt_event_t event, const char *name, rt_uint8_t flag);
rt_err_t rt_event_detach(rt_event_t event);
#ifdef RT_USING_HEAP
rt_event_t rt_event_create(const char *name, rt_uint8_t flag);
rt_err_t rt_event_delete(rt_event_t event);
#endif /* RT_USING_HEAP */

rt_err_t rt_event_send(rt_event_t event, rt_uint32_t set);
rt_err_t rt_event_recv(rt_event_t   event,
                       rt_uint32_t  set,
                       rt_uint8_t   opt,
                       rt_int32_t   timeout,
                       rt_uint32_t *recved);
rt_err_t rt_event_recv_interruptible(rt_event_t   event,
                       rt_uint32_t  set,
                       rt_uint8_t   opt,
                       rt_int32_t   timeout,
                       rt_uint32_t *recved);
rt_err_t rt_event_recv_killable(rt_event_t   event,
                       rt_uint32_t  set,
                       rt_uint8_t   opt,
                       rt_int32_t   timeout,
                       rt_uint32_t *recved);
rt_err_t rt_event_control(rt_event_t event, int cmd, void *arg);
#endif /* RT_USING_EVENT */

/**@}*/

/**
 * @addtogroup mailbox
 * @{
 */

#ifdef RT_USING_MAILBOX
/*
 * mailbox interface
 */
rt_err_t rt_mb_init(rt_mailbox_t mb,
                    const char  *name,
                    void        *msgpool,
                    rt_size_t    size,
                    rt_uint8_t   flag);
rt_err_t rt_mb_detach(rt_mailbox_t mb);
#ifdef RT_USING_HEAP
rt_mailbox_t rt_mb_create(const char *name, rt_size_t size, rt_uint8_t flag);
rt_err_t rt_mb_delete(rt_mailbox_t mb);
#endif /* RT_USING_HEAP */

rt_err_t rt_mb_send(rt_mailbox_t mb, rt_ubase_t value);
rt_err_t rt_mb_send_interruptible(rt_mailbox_t mb, rt_ubase_t value);
rt_err_t rt_mb_send_killable(rt_mailbox_t mb, rt_ubase_t value);
rt_err_t rt_mb_send_wait(rt_mailbox_t mb,
                         rt_ubase_t  value,
                         rt_int32_t   timeout);
rt_err_t rt_mb_send_wait_interruptible(rt_mailbox_t mb,
                         rt_ubase_t  value,
                         rt_int32_t   timeout);
rt_err_t rt_mb_send_wait_killable(rt_mailbox_t mb,
                         rt_ubase_t  value,
                         rt_int32_t   timeout);
rt_err_t rt_mb_urgent(rt_mailbox_t mb, rt_ubase_t value);
rt_err_t rt_mb_recv(rt_mailbox_t mb, rt_ubase_t *value, rt_int32_t timeout);
rt_err_t rt_mb_recv_interruptible(rt_mailbox_t mb, rt_ubase_t *value, rt_int32_t timeout);
rt_err_t rt_mb_recv_killable(rt_mailbox_t mb, rt_ubase_t *value, rt_int32_t timeout);
rt_err_t rt_mb_control(rt_mailbox_t mb, int cmd, void *arg);
#endif /* RT_USING_MAILBOX */

/**@}*/

/**
 * @addtogroup messagequeue
 * @{
 */
#ifdef RT_USING_MESSAGEQUEUE

struct rt_mq_message
{
    struct rt_mq_message *next;
    rt_ssize_t length;
#ifdef RT_USING_MESSAGEQUEUE_PRIORITY
    rt_int32_t prio;
#endif /* RT_USING_MESSAGEQUEUE_PRIORITY */
};

#define RT_MQ_BUF_SIZE(msg_size, max_msgs) \
((RT_ALIGN((msg_size), RT_ALIGN_SIZE) + sizeof(struct rt_mq_message)) * (max_msgs))

/*
 * message queue interface
 */
rt_err_t rt_mq_init(rt_mq_t     mq,
                    const char *name,
                    void       *msgpool,
                    rt_size_t   msg_size,
                    rt_size_t   pool_size,
                    rt_uint8_t  flag);
rt_err_t rt_mq_detach(rt_mq_t mq);
#ifdef RT_USING_HEAP
rt_mq_t rt_mq_create(const char *name,
                     rt_size_t   msg_size,
                     rt_size_t   max_msgs,
                     rt_uint8_t  flag);
rt_err_t rt_mq_delete(rt_mq_t mq);
#endif /* RT_USING_HEAP */

rt_err_t rt_mq_send(rt_mq_t mq, const void *buffer, rt_size_t size);
rt_err_t rt_mq_send_interruptible(rt_mq_t mq, const void *buffer, rt_size_t size);
rt_err_t rt_mq_send_killable(rt_mq_t mq, const void *buffer, rt_size_t size);
rt_err_t rt_mq_send_wait(rt_mq_t     mq,
                         const void *buffer,
                         rt_size_t   size,
                         rt_int32_t  timeout);
rt_err_t rt_mq_send_wait_interruptible(rt_mq_t     mq,
                         const void *buffer,
                         rt_size_t   size,
                         rt_int32_t  timeout);
rt_err_t rt_mq_send_wait_killable(rt_mq_t     mq,
                         const void *buffer,
                         rt_size_t   size,
                         rt_int32_t  timeout);
rt_err_t rt_mq_urgent(rt_mq_t mq, const void *buffer, rt_size_t size);
rt_ssize_t rt_mq_recv(rt_mq_t    mq,
                    void      *buffer,
                    rt_size_t  size,
                    rt_int32_t timeout);
rt_ssize_t rt_mq_recv_interruptible(rt_mq_t    mq,
                    void      *buffer,
                    rt_size_t  size,
                    rt_int32_t timeout);
rt_ssize_t rt_mq_recv_killable(rt_mq_t    mq,
                    void      *buffer,
                    rt_size_t  size,
                    rt_int32_t timeout);
rt_err_t rt_mq_control(rt_mq_t mq, int cmd, void *arg);

#ifdef RT_USING_MESSAGEQUEUE_PRIORITY
rt_err_t rt_mq_send_wait_prio(rt_mq_t mq,
                              const void *buffer,
                              rt_size_t size,
                              rt_int32_t prio,
                              rt_int32_t timeout,
                              int suspend_flag);
rt_ssize_t rt_mq_recv_prio(rt_mq_t mq,
                           void *buffer,
                           rt_size_t size,
                           rt_int32_t *prio,
                           rt_int32_t timeout,
                           int suspend_flag);
#endif /* RT_USING_MESSAGEQUEUE_PRIORITY */
#endif /* RT_USING_MESSAGEQUEUE */

/**@}*/

/* defunct */
void rt_thread_defunct_init(void);
void rt_thread_defunct_enqueue(rt_thread_t thread);
rt_thread_t rt_thread_defunct_dequeue(void);
void rt_defunct_execute(void);

/*
 * spinlock
 */
struct rt_spinlock;

void rt_spin_lock_init(struct rt_spinlock *lock);
void rt_spin_lock(struct rt_spinlock *lock);
void rt_spin_unlock(struct rt_spinlock *lock);
rt_base_t rt_spin_lock_irqsave(struct rt_spinlock *lock);
void rt_spin_unlock_irqrestore(struct rt_spinlock *lock, rt_base_t level);

/**@}*/

#ifdef RT_USING_DEVICE
/**
 * @addtogroup Device
 * @{
 */

/*
 * device (I/O) system interface
 */
rt_device_t rt_device_find(const char *name);

rt_err_t rt_device_register(rt_device_t dev,
                            const char *name,
                            rt_uint16_t flags);
rt_err_t rt_device_unregister(rt_device_t dev);

#ifdef RT_USING_HEAP
rt_device_t rt_device_create(int type, int attach_size);
void rt_device_destroy(rt_device_t device);
#endif /* RT_USING_HEAP */

rt_err_t
rt_device_set_rx_indicate(rt_device_t dev,
                          rt_err_t (*rx_ind)(rt_device_t dev, rt_size_t size));
rt_err_t
rt_device_set_tx_complete(rt_device_t dev,
                          rt_err_t (*tx_done)(rt_device_t dev, void *buffer));

rt_err_t  rt_device_init (rt_device_t dev);
rt_err_t  rt_device_open (rt_device_t dev, rt_uint16_t oflag);
rt_err_t  rt_device_close(rt_device_t dev);
rt_ssize_t rt_device_read(rt_device_t dev,
                          rt_off_t    pos,
                          void       *buffer,
                          rt_size_t   size);
rt_ssize_t rt_device_write(rt_device_t dev,
                          rt_off_t    pos,
                          const void *buffer,
                          rt_size_t   size);
rt_err_t  rt_device_control(rt_device_t dev, int cmd, void *arg);

/**@}*/
#endif /* RT_USING_DEVICE */

/*
 * interrupt service
 */

/*
 * rt_interrupt_enter and rt_interrupt_leave only can be called by BSP
 */
void rt_interrupt_enter(void);
void rt_interrupt_leave(void);

void rt_interrupt_context_push(rt_interrupt_context_t this_ctx);
void rt_interrupt_context_pop(void);
void *rt_interrupt_context_get(void);

/**
 * CPU object
 */
struct rt_cpu *rt_cpu_self(void);
struct rt_cpu *rt_cpu_index(int index);

#ifdef RT_USING_SMP

/*
 * smp cpus lock service
 */

rt_base_t rt_cpus_lock(void);
void rt_cpus_unlock(rt_base_t level);
void rt_cpus_lock_status_restore(struct rt_thread *thread);

#ifdef RT_USING_DEBUG
    rt_base_t rt_cpu_get_id(void);
#else /* !RT_USING_DEBUG */
    #define rt_cpu_get_id rt_hw_cpu_id
#endif /* RT_USING_DEBUG */

#else /* !RT_USING_SMP */
#define rt_cpu_get_id()  (0)

#endif /* RT_USING_SMP */

/*
 * the number of nested interrupts.
 */
rt_uint8_t rt_interrupt_get_nest(void);

#ifdef RT_USING_HOOK
void rt_interrupt_enter_sethook(void (*hook)(void));
void rt_interrupt_leave_sethook(void (*hook)(void));
#endif /* RT_USING_HOOK */

#ifdef RT_USING_COMPONENTS_INIT
void rt_components_init(void);
void rt_components_board_init(void);
#endif /* RT_USING_COMPONENTS_INIT */

/**
 * @addtogroup KernelService
 * @{
 */

/*
 * general kernel service
 */
#ifndef RT_USING_CONSOLE
#define rt_kprintf(...)
#define rt_kputs(str)
#else
int rt_kprintf(const char *fmt, ...);
void rt_kputs(const char *str);
#endif /* RT_USING_CONSOLE */

rt_err_t rt_backtrace(void);
rt_err_t rt_backtrace_thread(rt_thread_t thread);
rt_err_t rt_backtrace_frame(rt_thread_t thread, struct rt_hw_backtrace_frame *frame);
rt_err_t rt_backtrace_formatted_print(rt_ubase_t *buffer, long buflen);
rt_err_t rt_backtrace_to_buffer(rt_thread_t thread, struct rt_hw_backtrace_frame *frame,
                                long skip, rt_ubase_t *buffer, long buflen);

#if defined(RT_USING_DEVICE) && defined(RT_USING_CONSOLE)
rt_device_t rt_console_set_device(const char *name);
rt_device_t rt_console_get_device(void);
#ifdef RT_USING_THREADSAFE_PRINTF
    rt_thread_t rt_console_current_user(void);
#else
    rt_inline void *rt_console_current_user(void) { return RT_NULL; }
#endif /* RT_USING_THREADSAFE_PRINTF */
#endif /* defined(RT_USING_DEVICE) && defined(RT_USING_CONSOLE) */

int __rt_ffs(int value);
unsigned long __rt_ffsl(unsigned long value);
unsigned long __rt_clz(unsigned long value);

void rt_show_version(void);

#ifdef RT_DEBUGING_ASSERT
extern void (*rt_assert_hook)(const char *ex, const char *func, rt_size_t line);
void rt_assert_set_hook(void (*hook)(const char *ex, const char *func, rt_size_t line));
void rt_assert_handler(const char *ex, const char *func, rt_size_t line);

#define RT_ASSERT(EX)                                                         \
if (!(EX))                                                                    \
{                                                                             \
    rt_assert_handler(#EX, __FUNCTION__, __LINE__);                           \
}
#else
#define RT_ASSERT(EX) {RT_UNUSED(EX);}
#endif /* RT_DEBUGING_ASSERT */

#ifdef RT_DEBUGING_CONTEXT
/* Macro to check current context */
#define RT_DEBUG_NOT_IN_INTERRUPT                                             \
do                                                                            \
{                                                                             \
    if (rt_interrupt_get_nest() != 0)                                         \
    {                                                                         \
        rt_kprintf("Function[%s] shall not be used in ISR\n", __FUNCTION__);  \
        RT_ASSERT(0)                                                          \
    }                                                                         \
}                                                                             \
while (0)

/* "In thread context" means:
 *     1) the scheduler has been started
 *     2) not in interrupt context.
 */
#define RT_DEBUG_IN_THREAD_CONTEXT                                            \
do                                                                            \
{                                                                             \
    if (rt_thread_self() == RT_NULL)                                          \
    {                                                                         \
        rt_kprintf("Function[%s] shall not be used before scheduler start\n", \
                   __FUNCTION__);                                             \
        RT_ASSERT(0)                                                          \
    }                                                                         \
    RT_DEBUG_NOT_IN_INTERRUPT;                                                \
}                                                                             \
while (0)

/* "scheduler available" means:
 *     1) the scheduler has been started.
 *     2) not in interrupt context.
 *     3) scheduler is not locked.
 */
#define RT_DEBUG_SCHEDULER_AVAILABLE(need_check)                              \
do                                                                            \
{                                                                             \
    if (need_check)                                                           \
    {                                                                         \
        if (rt_critical_level() != 0)                                         \
        {                                                                     \
            rt_kprintf("Function[%s]: scheduler is not available\n",          \
                    __FUNCTION__);                                            \
            RT_ASSERT(0)                                                      \
        }                                                                     \
        RT_DEBUG_IN_THREAD_CONTEXT;                                           \
    }                                                                         \
}                                                                             \
while (0)
#else
#define RT_DEBUG_NOT_IN_INTERRUPT
#define RT_DEBUG_IN_THREAD_CONTEXT
#define RT_DEBUG_SCHEDULER_AVAILABLE(need_check)
#endif /* RT_DEBUGING_CONTEXT */

rt_inline rt_bool_t rt_in_thread_context(void)
{
    return rt_thread_self() != RT_NULL && rt_interrupt_get_nest() == 0;
}

/* is scheduler available */
rt_inline rt_bool_t rt_scheduler_is_available(void)
{
    return rt_critical_level() == 0 && rt_in_thread_context();
}

#ifdef RT_USING_SMP
/* is thread bond on core */
rt_inline rt_bool_t rt_sched_thread_is_binding(rt_thread_t thread)
{
    if (thread == RT_NULL)
    {
        thread = rt_thread_self();
    }
    return !thread || RT_SCHED_CTX(thread).bind_cpu != RT_CPUS_NR;
}

#else
#define rt_sched_thread_is_binding(thread) (RT_TRUE)
#endif

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* __RT_THREAD_H__ */
