#include <rtdef.h>
#include <interface_kernel.h>

extern rt_shell_t ishell;
#define SHELL()				ishell				

#define IKSERVICE()			(SHELL()->i_kservice)
#define ITHREAD()			(SHELL()->i_thread)
#define ISEM()				(SHELL()->i_sem)
#define IMUTEX()				(SHELL()->i_mutex)
#define IEVENT()				(SHELL()->i_event)
#define IMB()					(SHELL()->i_mb)
#define IMQ()					(SHELL()->i_mq)
#define IMP()					(SHELL()->i_mp)
#define IHEAP()				(SHELL()->i_heap)
#define IDEVICE()				(SHELL()->i_device)
#define ITIMER()				(SHELL()->i_timer)	

/* kernel service */
#define rt_kprintf			 	IKSERVICE()->rt_kprintf

/* thread */
#define rt_thread_init			ITHREAD()->rt_thread_init
#define rt_thread_create		ITHREAD()->rt_thread_create
#define rt_thread_detach		ITHREAD()->rt_thread_detach
#define rt_thread_find		ITHREAD()->rt_thread_find
#define rt_thread_self		ITHREAD()->rt_thread_self
#define rt_thread_startup		ITHREAD()->rt_thread_startup
#define rt_thread_delete		ITHREAD()->rt_thread_delete
#define rt_thread_yield		ITHREAD()->rt_thread_yield
#define rt_thread_delay		ITHREAD()->rt_thread_delay
#define rt_thread_control		ITHREAD()->rt_thread_control
#define rt_thread_suspend	ITHREAD()->rt_thread_suspend
#define rt_thread_resume		ITHREAD()->rt_thread_resume
#define rt_thread_timeout	ITHREAD()->rt_thread_timeout

/* semaphore */
#define rt_sem_init			ISEM()->rt_sem_init
#define rt_sem_detach		ISEM()->rt_sem_detach
#define rt_sem_create		ISEM()->rt_sem_create
#define rt_sem_delete		ISEM()->rt_sem_delete
#define rt_sem_take			ISEM()->rt_sem_take
#define rt_sem_trytake		ISEM()->rt_sem_trytake
#define rt_sem_release		ISEM()->rt_sem_release
#define rt_sem_control		ISEM()->rt_sem_control

/* mutex */
#define rt_mutex_init			IMUTEX()->rt_mutex_init
#define rt_mutex_detach		IMUTEX()->rt_mutex_detach
#define rt_mutex_create		IMUTEX()->rt_mutex_create
#define rt_mutex_delete		IMUTEX()->rt_mutex_delete
#define rt_mutex_take		IMUTEX()->rt_mutex_take
#define rt_mutex_trytake		IMUTEX()->rt_mutex_trytake
#define rt_mutex_release		IMUTEX()->rt_mutex_release
#define rt_mutex_control		IMUTEX()->rt_mutex_control

/* event */
#define rt_event_init			IEVENT()->rt_event_init
#define rt_event_detach		IEVENT()->rt_event_detach
#define rt_event_create		IEVENT()->rt_event_create
#define rt_event_delete		IEVENT()->rt_event_delete
#define rt_event_send		IEVENT()->rt_event_send
#define rt_event_recv		IEVENT()->rt_event_recv
#define rt_event_control		IEVENT()->rt_event_control

/* mailbox */
#define rt_mb_init			IMB()->rt_mb_init
#define rt_mb_detach			IMB()->rt_mb_detach
#define rt_mb_create			IMB()->rt_mb_create
#define rt_mb_delete			IMB()->rt_mb_delete
#define rt_mb_send			IMB()->rt_mb_send
#define rt_mb_recv			IMB()->rt_mb_recv
#define rt_mb_control		IMB()->rt_mb_control

/* message queue interface */
#define rt_mq_init			IMQ()->rt_mq_init
#define rt_mq_detach			IMQ()->rt_mq_detach
#define rt_mq_create			IMQ()->rt_mq_create
#define rt_mq_delete			IMQ()->rt_mq_delete
#define rt_mq_send			IMQ()->rt_mq_send
#define rt_mq_urgent			IMQ()->rt_mq_urgent
#define rt_mq_recv			IMQ()->rt_mq_recv
#define rt_mq_control		IMQ()->rt_mq_control

/* memory pool */
#define rt_mp_init			IMP()->rt_mp_init
#define rt_mp_detach			IMP()->rt_mp_detach
#define rt_mp_create			IMP()->rt_mp_create
#define rt_mp_delete			IMP()->rt_mp_delete
#define rt_mp_alloc			IMP()->rt_mp_alloc
#define rt_mp_free			IMP()->rt_mp_free

/* heap memory */
#define rt_malloc				IHEAP()->rt_malloc
#define rt_free				IHEAP()->rt_free
#define rt_realloc			IHEAP()->rt_realloc
#define rt_calloc				IHEAP()->rt_calloc

/* device */
#define rt_device_register	IDEVICE()->rt_device_register
#define rt_device_unregister	IDEVICE()->rt_device_unregister
#define rt_device_init_all		IDEVICE()->rt_device_init_all
#define rt_device_find		IDEVICE()->rt_device_find
#define rt_device_init			IDEVICE()->rt_device_init
#define rt_device_open		IDEVICE()->rt_device_open
#define rt_device_close		IDEVICE()->rt_device_close
#define rt_device_read		IDEVICE()->rt_device_read
#define rt_device_write		IDEVICE()->rt_device_write
#define rt_device_control		IDEVICE()->rt_device_control
#define rt_device_set_rx_indicate		IDEVICE()->rt_device_set_rx_indicate
#define rt_device_set_tx_complete	IDEVICE()->rt_device_set_tx_complete

/* timer */
#define rt_tick_get			ITIMER()->rt_tick_get
#define rt_system_timer_init	ITIMER()->rt_system_timer_init
#define rt_timer_init			ITIMER()->rt_timer_init
#define rt_timer_detach		ITIMER()->rt_timer_detach
#define rt_timer_create		ITIMER()->rt_timer_create
#define rt_timer_delete		ITIMER()->rt_timer_delete
#define rt_timer_start		ITIMER()->rt_timer_start
#define rt_timer_stop			ITIMER()->rt_timer_stop
#define rt_timer_control		ITIMER()->rt_timer_control
#define rt_tick_from_millisecond		ITIMER()->rt_tick_from_millisecond
#define rt_system_timer_thread_init	ITIMER()->rt_system_timer_thread_init
