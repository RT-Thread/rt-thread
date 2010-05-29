#include <interface_kernel.h>

const struct rt_kservice_interface ikservice = 
{
	rt_kprintf
};

/*
 * thread  interface  
 */
const struct rt_thread_interface ithread = 
{
	rt_thread_init,
	rt_thread_detach,
	rt_thread_create,
	rt_thread_self,
	rt_thread_find,
	rt_thread_startup,
	rt_thread_delete,
	rt_thread_yield,
	rt_thread_delay,
	rt_thread_control,
	rt_thread_suspend,
	rt_thread_resume,
	rt_thread_timeout		
}; 


#ifdef RT_USING_SEMAPHORE
/*
 * semaphore interface 
 */
const struct rt_sem_interface isem = 
{ 
	rt_sem_init,
	rt_sem_detach,
	rt_sem_create,
	rt_sem_delete,
	rt_sem_take,
	rt_sem_trytake,
	rt_sem_release,
	rt_sem_control
};	
#endif

#ifdef RT_USING_MUTEX
/*
 * mutex interface 
 */
const struct rt_mutex_interface imutex =
{
	rt_mutex_init,
	rt_mutex_detach,
	rt_mutex_create,
	rt_mutex_delete,
	rt_mutex_take,
	rt_mutex_release,
	rt_mutex_control
};
#endif

#ifdef RT_USING_EVENT
/*
 * event interface 
 */
const struct rt_event_interface ievent =
{ 
	rt_event_init,
	rt_event_detach,
	rt_event_create,
	rt_event_delete,
	rt_event_send,
	rt_event_recv,
	rt_event_control 
};	
#endif

#ifdef RT_USING_MAILBOX
/*
 * mailbox interface 
 */
const struct rt_mb_interface imb =
{ 
	rt_mb_init,
	rt_mb_detach,
	rt_mb_create,
	rt_mb_delete,
	rt_mb_send,
	rt_mb_recv,
	rt_mb_control 
};	
#endif

#ifdef RT_USING_MESSAGEQUEUE
/*
 * message queue interface 
 */
const struct rt_mq_interface imq =
{
	rt_mq_init,
	rt_mq_detach,
	rt_mq_create,
	rt_mq_delete,
	rt_mq_send,
	rt_mq_urgent,
	rt_mq_recv,
	rt_mq_control  
};
#endif

#ifdef RT_USING_MEMPOOL
/*
 * memory pool interface 
 */
const struct rt_mp_interface imp =
{
	rt_mp_init,
	rt_mp_detach,
	rt_mp_create,
	rt_mp_delete,
	rt_mp_alloc,
	rt_mp_free
};
#endif

#ifdef RT_USING_HEAP
/*
 * heap memory interface 
 */
const struct rt_heap_interface iheap =
{
	rt_malloc,
	rt_free,
	rt_realloc,
	rt_calloc
};
#endif

#ifdef RT_USING_DEVICE
/*
 * device interface 
 */
const struct rt_device_interface idevice =
{
	rt_device_register,
	rt_device_unregister,
	rt_device_init_all,
	rt_device_find,
	rt_device_init,
	rt_device_open,
	rt_device_close,
	rt_device_read,
	rt_device_write,
	rt_device_control,
	rt_device_set_rx_indicate,
	rt_device_set_tx_complete
};
#endif

/*
 * clock & timer interface 
 */
const struct rt_timer_interface itimer =
{ 
	rt_tick_get,
	rt_tick_from_millisecond,
	rt_system_timer_init,
	rt_system_timer_thread_init,
	rt_timer_init,
	rt_timer_detach,
	rt_timer_create,
	rt_timer_delete,
	rt_timer_start,
	rt_timer_stop,
	rt_timer_control
};

/*
 * kernel interface
 */
const struct  rt_shell ishell = 
{
	(const rt_kservice_interface_t )&ikservice,
	(const rt_thread_interface_t )&ithread,
	(const rt_sem_interface_t )&isem,
	(const rt_mutex_interface_t )&imutex,
	(const rt_event_interface_t )&ievent,
	(const rt_mb_interface_t )&imb,
	(const rt_mq_interface_t )&imq,
	(const rt_mp_interface_t )&imp,
	(const rt_heap_interface_t )&iheap,	
	(const rt_device_interface_t )&idevice,
	(const rt_timer_interface_t )&itimer,	
};

