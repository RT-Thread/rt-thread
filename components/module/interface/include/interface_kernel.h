#include <rtdef.h>
#include <rtthread.h>

/* RT-Thread kernel component guid */
#define RTTHREAD_GUID_KERNEL			1000
#define RTTHREAD_GUID_KSERVICE       	RTTHREAD_GUID_KERNEL
#define RTTHREAD_GUID_THREAD          	(RTTHREAD_GUID_KERNEL + 1)
#define RTTHREAD_GUID_SEMAPHORE		(RTTHREAD_GUID_KERNEL + 2)
#define RTTHREAD_GUID_MUTEX			(RTTHREAD_GUID_KERNEL + 3)
#define RTTHREAD_GUID_MAILBOX          	(RTTHREAD_GUID_KERNEL + 4)
#define RTTHREAD_GUID_MESSAGEQUEUE	(RTTHREAD_GUID_KERNEL + 5)
#define RTTHREAD_GUID_MEMPOOL 		(RTTHREAD_GUID_KERNEL + 6)
#define RTTHREAD_GUID_DEVICE      	 	(RTTHREAD_GUID_KERNEL + 7)
#define RTTHREAD_GUID_TIMER      		(RTTHREAD_GUID_KERNEL + 8)

/* file system component guid */
#define RTTHREAD_GUID_FILESYSTEM		2000
/* net component guid */
#define RTTHREAD_GUID_NET				3000
/* gui component guid */
#define RTTHREAD_GUID_GUI				4000
/* application guid */
#define RTTHREAD_GUID_APP_START		10000
/* service guid */
#define RTTHREAD_GUID_SEVICE_START	20000

/* 
 * kservice interface
 */
struct rt_kservice_interface
{
	void (*rt_kprintf)(const char *fmt, ...);
}; 
typedef struct rt_kservice_interface* rt_kservice_interface_t;

/*
 * thread  interface 
 */
struct rt_thread_interface
{
	rt_err_t (*rt_thread_init)(struct rt_thread* thread,
		const char* name,
		void (*entry)(void* parameter), void* parameter,
		void* stack_start, rt_uint32_t stack_size,
		rt_uint8_t priority, rt_uint32_t tick);
	rt_err_t (*rt_thread_detach)(rt_thread_t thread);
	rt_thread_t (*rt_thread_create)(const char* name,
		void (*entry)(void* parameter), void* parameter,
		rt_uint32_t stack_size,
		rt_uint8_t priority,
		rt_uint32_t tick);
	rt_thread_t (*rt_thread_self)(void);
	rt_thread_t (*rt_thread_find)(char* name);
	rt_err_t (*rt_thread_startup)(rt_thread_t thread);
	rt_err_t (*rt_thread_delete)(rt_thread_t thread);
	rt_err_t (*rt_thread_yield)(void);
	rt_err_t (*rt_thread_delay)(rt_tick_t tick);
	rt_err_t (*rt_thread_control)(rt_thread_t thread, rt_uint8_t cmd, void* arg);
	rt_err_t (*rt_thread_suspend)(rt_thread_t thread);
	rt_err_t (*rt_thread_resume)(rt_thread_t thread);
	void (*rt_thread_timeout)(void* parameter);
};
typedef struct rt_thread_interface* rt_thread_interface_t;

#ifdef RT_USING_SEMAPHORE
/*
 * semaphore interface
 */
 struct rt_sem_interface
{
	rt_err_t (*rt_sem_init)(rt_sem_t sem, const char* name, rt_uint32_t value, rt_uint8_t flag);
	rt_err_t (*rt_sem_detach)(rt_sem_t sem);
	rt_sem_t (*rt_sem_create)(const char* name, rt_uint32_t value, rt_uint8_t flag);
	rt_err_t (*rt_sem_delete)(rt_sem_t sem);
	rt_err_t (*rt_sem_take)(rt_sem_t sem, rt_int32_t time);
	rt_err_t (*rt_sem_trytake)(rt_sem_t sem);
	rt_err_t (*rt_sem_release)(rt_sem_t sem);
	rt_err_t (*rt_sem_control)(rt_sem_t sem, rt_uint8_t cmd, void* arg);
};
typedef struct rt_sem_interface* rt_sem_interface_t;
#endif

#ifdef RT_USING_MUTEX
/*
 * mutex interface
 */
 struct rt_mutex_interface
{
	rt_err_t (*rt_mutex_init) (rt_mutex_t mutex, const char* name, rt_uint8_t flag);
	rt_err_t (*rt_mutex_detach)(rt_mutex_t mutex);
	rt_mutex_t (*rt_mutex_create)(const char* name, rt_uint8_t flag);
	rt_err_t (*rt_mutex_delete)(rt_mutex_t mutex);
	rt_err_t (*rt_mutex_take)(rt_mutex_t mutex, rt_int32_t time);
	rt_err_t (*rt_mutex_release)(rt_mutex_t mutex);
	rt_err_t (*rt_mutex_control)(rt_mutex_t mutex, rt_uint8_t cmd, void* arg);
};
typedef struct rt_mutex_interface* rt_mutex_interface_t;
#endif

#ifdef RT_USING_EVENT
/*
 * event interface
 */
 struct rt_event_interface
{
	rt_err_t (*rt_event_init)(rt_event_t event, const char* name, rt_uint8_t flag);
	rt_err_t (*rt_event_detach)(rt_event_t event);
	rt_event_t (*rt_event_create)(const char* name, rt_uint8_t flag);
	rt_err_t (*rt_event_delete)(rt_event_t event);
	rt_err_t (*rt_event_send)(rt_event_t event, rt_uint32_t set);
	rt_err_t (*rt_event_recv)(rt_event_t event, rt_uint32_t set, rt_uint8_t option, rt_int32_t timeout, rt_uint32_t* recved);
	rt_err_t (*rt_event_control)(rt_event_t event, rt_uint8_t cmd, void* arg);
};
typedef struct rt_event_interface* rt_event_interface_t;
#endif

#ifdef RT_USING_MAILBOX
/*
 * mailbox interface
 */
struct rt_mb_interface
{
	rt_err_t (*rt_mb_init)(rt_mailbox_t mb, const char* name, void* msgpool, rt_size_t size, rt_uint8_t flag);
	rt_err_t (*rt_mb_detach)(rt_mailbox_t mb);
	rt_mailbox_t (*rt_mb_create)(const char* name, rt_size_t size, rt_uint8_t flag);
	rt_err_t (*rt_mb_delete)(rt_mailbox_t mb);
	rt_err_t (*rt_mb_send)(rt_mailbox_t mb, rt_uint32_t value);
	rt_err_t (*rt_mb_recv)(rt_mailbox_t mb, rt_uint32_t* value, rt_int32_t timeout);
	rt_err_t (*rt_mb_control)(rt_mailbox_t mb, rt_uint8_t cmd, void* arg);
};
typedef struct rt_mb_interface* rt_mb_interface_t;
#endif

#ifdef RT_USING_MESSAGEQUEUE
/*
 * message queue interface
 */
struct rt_mq_interface
{
	rt_err_t (*rt_mq_init)(rt_mq_t mq, const char* name, void *msgpool, rt_size_t msg_size, rt_size_t pool_size, rt_uint8_t flag);
	rt_err_t (*rt_mq_detach)(rt_mq_t mq);
	rt_mq_t (*rt_mq_create)(const char* name, rt_size_t msg_size, rt_size_t max_msgs, rt_uint8_t flag);
	rt_err_t (*rt_mq_delete)(rt_mq_t mq);
	rt_err_t (*rt_mq_send)(rt_mq_t mq, void* buffer, rt_size_t size);
	rt_err_t (*rt_mq_urgent)(rt_mq_t mq, void* buffer, rt_size_t size);
	rt_err_t (*rt_mq_recv)(rt_mq_t mq, void* buffer, rt_size_t size, rt_int32_t timeout);
	rt_err_t (*rt_mq_control)(rt_mq_t mq, rt_uint8_t cmd, void* arg);
};
typedef struct rt_mq_interface* rt_mq_interface_t;
#endif

#ifdef RT_USING_MEMPOOL
/*
 * memory pool interface
 */
struct rt_mp_interface
{
	rt_err_t (*rt_mp_init)(struct rt_mempool* mp, const char* name, void *start, rt_size_t size, rt_size_t block_size);
	rt_err_t (*rt_mp_detach)(struct rt_mempool* mp);
	rt_mp_t (*rt_mp_create)(const char* name, rt_size_t block_count, rt_size_t block_size);
	rt_err_t (*rt_mp_delete)(rt_mp_t mp);
	void* (*rt_mp_alloc)(rt_mp_t mp, rt_int32_t time);
	void (*rt_mp_free)(void *block);
};
typedef struct rt_mp_interface* rt_mp_interface_t;
#endif

#ifdef RT_USING_HEAP
/*
 * heap memory interface
 */
struct rt_heap_interface
{
	void* (*rt_malloc)(rt_size_t size);
	void (*rt_free)(void *ptr);
	void* (*rt_realloc)(void *ptr, rt_size_t size);
	void* (*rt_calloc)(rt_size_t count, rt_size_t size);
};
typedef struct rt_heap_interface* rt_heap_interface_t;
#endif

#ifdef RT_USING_DEVICE
/*
 * device interface
 */
struct rt_device_interface
{ 
	rt_err_t (*rt_device_register)(rt_device_t dev, const char* name, rt_uint16_t flags);
	rt_err_t (*rt_device_unregister)(rt_device_t dev);
	rt_err_t (*rt_device_init_all)(void);
	rt_device_t (*rt_device_find)(const char* name);
	rt_err_t (*rt_device_init)(rt_device_t dev);
	rt_err_t (*rt_device_open)(rt_device_t dev, rt_uint16_t oflag);
	rt_err_t (*rt_device_close)(rt_device_t dev);
	rt_size_t (*rt_device_read)(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size);
	rt_size_t (*rt_device_write)(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size);
	rt_err_t (*rt_device_control)(rt_device_t dev, rt_uint8_t cmd, void* arg);
	rt_err_t (*rt_device_set_rx_indicate)(rt_device_t dev, rt_err_t (*rx_ind )(rt_device_t dev, rt_size_t size));
	rt_err_t (*rt_device_set_tx_complete)(rt_device_t dev, rt_err_t (*tx_done)(rt_device_t dev, void *buffer));
};
typedef struct rt_device_interface* rt_device_interface_t;
#endif

/*
 * clock & timer interface
 */
struct rt_timer_interface
{
	rt_tick_t (*rt_tick_get)(void);
	rt_tick_t (*rt_tick_from_millisecond)(rt_uint32_t ms);
	void (*rt_system_timer_init)(void);
	void (*rt_system_timer_thread_init)(void);
	void (*rt_timer_init)(rt_timer_t timer,
					   const char* name,
					   void (*timeout)(void* parameter), void* parameter,
					   rt_tick_t time, rt_uint8_t flag);
	rt_err_t (*rt_timer_detach)(rt_timer_t timer);
	rt_timer_t (*rt_timer_create)(const char* name, void (*timeout)(void* parameter), void* parameter, rt_tick_t time, rt_uint8_t flag);
	rt_err_t (*rt_timer_delete)(rt_timer_t timer);
	rt_err_t (*rt_timer_start)(rt_timer_t timer);
	rt_err_t (*rt_timer_stop)(rt_timer_t timer);
	rt_err_t (*rt_timer_control)(rt_timer_t timer, rt_uint8_t cmd, void* arg);
};
typedef struct rt_timer_interface* rt_timer_interface_t;

/*
 * kernel interface
 */
struct  rt_shell
{
    const rt_kservice_interface_t i_kservice;
    const rt_thread_interface_t i_thread;
    const rt_sem_interface_t i_sem;
    const rt_mutex_interface_t i_mutex;
    const rt_event_interface_t i_event;
    const rt_mb_interface_t i_mb;
    const rt_mq_interface_t i_mq;
    const rt_mp_interface_t i_mp;
    const rt_heap_interface_t i_heap;
    const rt_device_interface_t i_device;
    const rt_timer_interface_t i_timer;	
};
typedef struct rt_shell* rt_shell_t;

