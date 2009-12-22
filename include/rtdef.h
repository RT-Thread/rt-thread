/*
 * File      : rtdef.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2007-01-10     Bernard      the first version
 * 2008-07-12	  Bernard	   remove all rt_int8, rt_uint32_t etc typedef
 */
#ifndef __RT_DEF_H__
#define __RT_DEF_H__

#include <rtconfig.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef signed char  rt_int8_t;
typedef signed short rt_int16_t;
typedef signed long  rt_int32_t;
typedef unsigned char  rt_uint8_t;
typedef unsigned short rt_uint16_t;
typedef unsigned long  rt_uint32_t;
typedef int rt_bool_t;

#define RT_UINT8_MAX	0xff
#define RT_UINT16_MAX	0xffff
#define RT_UINT32_MAX	0xffffffff

/* 32bit CPU */
typedef long rt_base_t;
typedef unsigned long rt_ubase_t;

/* RT-Thread bool type definitions */
#define RT_TRUE 			1
#define RT_FALSE 			0

#ifdef __CC_ARM                 /* ARM Compiler */
    #include <stdarg.h>
    #define SECTION(x)  __attribute__((section(x)))
    #define UNUSED  __attribute__((unused))
    #define rt_inline   static __inline

#elif defined (__ICCARM__)        /* for IAR Compiler */
    #include <stdarg.h>
    #define SECTION(x)  @ x
    #define UNUSED
    #define rt_inline inline

#elif defined (__GNUC__)        /* GNU GCC Compiler */
    #ifdef RT_USING_NEWLIB
        #include <stdarg.h>
    #else
        typedef void *__sys_va_list;
        typedef __sys_va_list va_list;
        #define __va_rounded_size(type)	\
            (((sizeof (type) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))
        #define va_start(ap, lastarg)	\
            (ap = ((char *) &(lastarg) + __va_rounded_size(lastarg)))
        #define va_end(ap)	((void)0)
        /*	little endian */
        #define va_arg(ap, type)	\
            (ap = (__sys_va_list) ((char *) (ap) + __va_rounded_size (type)),  \
            *((type *) (void *) ((char *) (ap) - __va_rounded_size (type))))
    #endif

    #define SECTION(x) __attribute__((section(x)))
    #define UNUSED __attribute__((unused))
    #define rt_inline static __inline
#endif

/* event length */
#define RT_EVENT_LENGTH		32

/* memory management option */
#define RT_MM_PAGE_SIZE		4096
#define RT_MM_PAGE_MASK 	(RT_MM_PAGE_SIZE - 1)
#define RT_MM_PAGE_BITS		12

/* RT-Thread definitions */
typedef rt_base_t	rt_err_t;		/* Type for error number.	*/
typedef rt_uint32_t	rt_time_t;		/* Type for time stamp. 	*/
typedef rt_uint32_t	rt_tick_t;		/* Type for tick count. 	*/
typedef rt_base_t	rt_flag_t;		/* Type for flags. 			*/
typedef rt_ubase_t	rt_size_t;		/* Type for size number.	*/
typedef rt_ubase_t	rt_dev_t;		/* Type for device.			*/
typedef rt_uint32_t	rt_off_t;		/* Type for offset.			*/

/* maximun value of base type */
#define RT_UINT8_MAX	0xff		/* Maxium number of UINT8.	*/
#define RT_UINT16_MAX	0xffff		/* Maxium number of UINT16.	*/
#define RT_UINT32_MAX	0xffffffff	/* Maxium number of UINT32.	*/

/* RT-Thread version information */
#define RT_VERSION			3
#define RT_SUBVERSION		0

/**
 * @addtogroup Error
 */
/*@{*/
/* RT-Thread error code definitions */
#define RT_EOK				0		/* There is no error 		*/
#define RT_ERROR			1		/* A generic error happens 	*/
#define RT_ETIMEOUT			2		/* Timed out 				*/
#define RT_EFULL			3		/* The resource is full		*/
#define RT_EEMPTY			4		/* The resource is empty 	*/
#define RT_ENOMEM			5		/* No memory				*/
#define RT_ENOSYS			6		/* No system 				*/
#define RT_EBUSY			7		/* Busy						*/
/*@}*/

#ifdef RT_DEBUG
#define RT_ASSERT(EX)		if (!(EX)) { rt_kprintf("(%s) assert failed at %s:%d \n", #EX, __FUNCTION__, __LINE__); while (1);}
#else
#define RT_ASSERT(EX)
#endif

/**
 * @def RT_ALIGN(size, align)
 * Return the most contiguous size aligned at specified width. RT_ALIGN(13, 4)
 * would equal to 16. It is needed in some critical contexts.
 */
#define RT_ALIGN(size, align)	(((size) + (align) - 1) & ~((align)-1))

/**
 * @def RT_NULL
 * Similar as the \c NULL in C library.
 */
#define RT_NULL 				((void *)0)

struct rt_list_node
{
	struct rt_list_node *next;	/* point to next node. */
	struct rt_list_node *prev;	/* point to prev node. */
};
typedef struct rt_list_node rt_list_t;	/* Type for lists. */

/**
 * @addtogroup KernelObject
 */
/*@{*/
/*
 * Base structure of Kernel object
 */
struct rt_object
{
	/* name of kernel object			*/
	char      name[RT_NAME_MAX];
	/* type of kernel object 			*/
	rt_uint8_t  type;
	/* flag of kernel object			*/
	rt_uint8_t  flag;
	/* list pointer of kernel object 	*/
	rt_list_t	list;
};
typedef struct rt_object* rt_object_t;	/* Type for kernel objects. */

/**
 *	The object type can be one of the follows with specific
 *	macros enabled:
 *	- Thread
 *	- Process
 *	- Semaphore
 *	- Mutex
 *	- Event
 *	- MailBox
 *	- MessageQueue
 *	- MemPool
 *  - Device
 *	- Timer
 *	- Unknown
 *	- Static
 */
enum rt_object_class_type
{
	RT_Object_Class_Thread = 0,	/* The object is a thread. */
#ifdef RT_USING_SEMAPHORE
	RT_Object_Class_Semaphore,	/* The object is a semaphore. */
#endif
#ifdef RT_USING_MUTEX
	RT_Object_Class_Mutex,		/* The object is a mutex. */
#endif
#ifdef RT_USING_EVENT
	RT_Object_Class_Event,		/* The object is a event. */
#endif
#ifdef RT_USING_MAILBOX
	RT_Object_Class_MailBox,	/* The object is a mail box. */
#endif
#ifdef RT_USING_MESSAGEQUEUE
	RT_Object_Class_MessageQueue,/* The object is a message queue. */
#endif
#ifdef RT_USING_MEMPOOL
	RT_Object_Class_MemPool,	/* The object is a memory pool. */
#endif
#ifdef RT_USING_DEVICE
	RT_Object_Class_Device,		/* The object is a device */
#endif
	RT_Object_Class_Timer,		/* The object is a timer. */
#ifdef RT_USING_MODULE
	RT_Object_Class_Module,		/* The object is a module. */
#endif
	RT_Object_Class_Unknown,	/* The object is unknown. */
	RT_Object_Class_Static = 0x80/* The object is a static object. */
};

/*
 * the information of the kernel object
 */
struct rt_object_information
{
	enum rt_object_class_type type;		/* object class type. */
	rt_list_t object_list;				/* object list. */
	rt_size_t object_size;				/* object size. */
};
/*@}*/

/**
 * @addtogroup Clock
 */
/*@{*/

/*
 * clock & timer macros
 */
#define RT_TIMER_FLAG_DEACTIVATED	0x0	/* timer is deactive. */
#define RT_TIMER_FLAG_ACTIVATED		0x1	/* timer is active. */
#define RT_TIMER_FLAG_ONE_SHOT		0x0	/* one shot timer. */
#define RT_TIMER_FLAG_PERIODIC		0x2	/* periodic timer. */

#define RT_TIMER_FLAG_HARD_TIMER	0x0	/* hard timer,the timer's callback function will be called in tick isr. */
#define RT_TIMER_FLAG_SOFT_TIMER	0x4	/* soft timer,the timer's callback function will be called in timer thread. */

#define RT_TIMER_CTRL_SET_TIME		0x0	/* set timer. */
#define RT_TIMER_CTRL_GET_TIME		0x1	/* get timer. */
#define RT_TIMER_CTRL_SET_ONESHOT	0x2	/* change timer to one shot. */
#define RT_TIMER_CTRL_SET_PERIODIC	0x3	/* change timer to periodic. */

/*
 * timer structure
 *
 */
struct rt_timer
{
	struct rt_object parent;

	rt_list_t list;						/* the node of timer list. */

	void (*timeout_func)(void* parameter);/* timeout function. */
	void *parameter;					/* timeout function's parameter. */

	rt_tick_t init_tick;				/* timer timeout tick. */
	rt_tick_t timeout_tick;				/* timeout tick. */
};
typedef struct rt_timer* rt_timer_t;
/*@}*/

/**
 * @addtogroup Thread
 */
/*@{*/

/*
 * Thread
 */

/* thread state definitions */
#define RT_THREAD_RUNNING	0x0					/* Running. */
#define RT_THREAD_READY		0x1					/* Ready. */
#define RT_THREAD_SUSPEND	0x2					/* Suspend. */
#define RT_THREAD_BLOCK		RT_THREAD_SUSPEND	/* Blocked. */
#define RT_THREAD_CLOSE		0x3					/* Closed. */
#define RT_THREAD_INIT		RT_THREAD_CLOSE		/* Inited. */

#define RT_THREAD_FLAGS_TIMERSLICE 		0x01

#define RT_THREAD_CTRL_STARTUP			0x00	/* Starup thread. */
#define RT_THREAD_CTRL_CLOSE			0x01	/* Close thread. */
#define RT_THREAD_CTRL_CHANGE_PRIORITY	0x02	/* Change thread priority. */
#define RT_THREAD_CTRL_INFO				0x03	/* Get thread information. */

typedef struct rt_thread* rt_thread_t;
typedef struct rt_module* rt_module_t;

/*
 * Thread related structure
 */
struct rt_thread
{
	/* rt object */
	char        name[RT_NAME_MAX];			/* the name of thread */
	rt_uint8_t	type;						/* type of object */
	rt_uint8_t  flags;						/* thread's flags */

	rt_list_t	list;						/* the object list */

	rt_thread_t tid;						/* the thread id */
	rt_list_t	tlist;						/* the thread list */

	/* stack point and entry */
	void*		sp;							/* stack point */
	void*		entry;						/* entry */
	void*       parameter;					/* parameter */
	void*       stack_addr;					/* stack address */
	rt_uint16_t stack_size;					/* stack size */

	/* error code */
	rt_err_t    error;						/* error code */

	/* priority */
	rt_uint8_t	current_priority;			/* current priority */
	rt_uint8_t	init_priority;				/* initialized priority */
#if RT_THREAD_PRIORITY_MAX > 32
	rt_uint8_t 	number;
	rt_uint8_t	high_mask;
#endif
	rt_uint32_t	number_mask;

#if defined(RT_USING_EVENT)
	/* thread event */
	rt_uint32_t event_set;
	rt_uint8_t	event_info;
#endif

	rt_uint8_t	stat;						/* thread stat */

	rt_ubase_t	init_tick;					/* thread's tick */
	rt_ubase_t 	remaining_tick;				/* remaining tick */

	struct rt_timer thread_timer;			/* thread timer */

#ifdef RT_USING_MODULE
	rt_module_t module_parent;				/* module parent */
#endif

	rt_uint32_t user_data;					/* user data */
};
/*@}*/

#ifdef RT_USING_MODULE
struct rt_module
{
	/* inherit from object */
	struct rt_object parent;

	rt_uint32_t module_data;
	void* module_space;

	void* module_entry;
	rt_uint32_t stack_size;
	rt_uint32_t thread_priority;
	rt_thread_t module_thread;

	/* module memory pool */
	rt_uint32_t mempool_size;
	void* module_mempool;

	/* object in this module, module object is the last basic object type */
	struct rt_object_information module_object[RT_Object_Class_Module];
};
#endif

/**
 * @addtogroup IPC
 */
/*@{*/
/*
 * ipc & sync
 */
#define RT_IPC_FLAG_FIFO	0x00	/* FIFOed IPC. @ref IPC. */
#define RT_IPC_FLAG_PRIO	0x01	/* PRIOed IPC. @ref IPC. */

#define RT_WAITING_FOREVER	-1		/* Block forever until get resource. */
#define RT_WAITING_NO		0		/* Non-block. */

/*
 * Base structure of IPC object
 */
struct rt_ipc_object
{
	struct rt_object parent;

	rt_list_t suspend_thread;		/* threads pended on this resource. */
	rt_uint32_t suspend_thread_count;	/* numbers of thread pended on this resource. */
};

#ifdef RT_USING_SEMAPHORE
/*
 * semaphore
 *
 * Binary and counter semaphore are both supported.
 */
struct rt_semaphore
{
	struct rt_ipc_object parent;

	rt_ubase_t value;				/* value of semaphore. */
};
typedef struct rt_semaphore* rt_sem_t;
#endif

#ifdef RT_USING_MUTEX
/*
 * mutex
 */
struct rt_mutex
{
	struct rt_ipc_object parent;

	rt_ubase_t value;				/* value of mutex. */

	struct rt_thread* owner;		/* current owner of mutex. */
	rt_uint8_t original_priority;	/* priority of last thread hold the mutex. */

	rt_ubase_t hold;			 	/* numbers of thread hold the mutex. */
};
typedef struct rt_mutex* rt_mutex_t;
#endif

#if defined(RT_USING_EVENT)
#define RT_EVENT_FLAG_AND		0x01
#define RT_EVENT_FLAG_OR		0x02
#define RT_EVENT_FLAG_CLEAR		0x04
#endif

#ifdef RT_USING_EVENT
/*
 * event
 */
struct rt_event
{
	struct rt_ipc_object parent;

	rt_uint32_t set;				/* event set. */
};
typedef struct rt_event* rt_event_t;
#endif

#ifdef RT_USING_MAILBOX
/*
 * mailbox
 *
 */
struct rt_mailbox
{
	struct rt_ipc_object parent;

	rt_uint32_t* msg_pool;	/* start address of message buffer. */

	rt_size_t size;			/* size of message pool. */

	rt_ubase_t entry;		/* index of messages in msg_pool. */
	rt_ubase_t in_offset, out_offset;	/* in/output offset of the message buffer. */
};
typedef struct rt_mailbox* rt_mailbox_t;
#endif

#ifdef RT_USING_MESSAGEQUEUE
/*
 * messagequeue
 */
struct rt_messagequeue
{
	struct rt_ipc_object parent;

	void* msg_pool;			/* start address of message queue. */

	rt_size_t msg_size;		/* message size of each message. */
	rt_size_t max_msgs;		/* max number of messages. */

	void* msg_queue_head;	/* list head. */
	void* msg_queue_tail;	/* list tail. */
	void* msg_queue_free;	/* pointer indicated the free node of queue. */

	rt_ubase_t entry;		/* index of messages in the queue. */
};
typedef struct rt_messagequeue* rt_mq_t;
#endif
/*@}*/

/**
 * @addtogroup MM
 */
/*@{*/
/*
 * memory management
 * heap & partition
 */
#ifdef RT_USING_MEMPOOL
/*
 * Base structure of Memory pool object
 */
struct rt_mempool
{
	struct rt_object parent;

	void* start_address;			/* memory pool start */
	rt_size_t size;					/* size of memory pool */

	rt_size_t block_size;			/* size of memory blocks */
	rt_uint8_t* block_list;			/* memory blocks list */

	rt_size_t block_total_count;	/* numbers of memory block */
	rt_size_t block_free_count;		/* numbers of free memory block */

	rt_list_t suspend_thread;		/* threads pended on this resource */
	rt_size_t suspend_thread_count;	/* numbers of thread pended on this resource */
};
typedef struct rt_mempool* rt_mp_t;
#endif
/*@}*/

#ifdef RT_USING_DEVICE
/**
 * @addtogroup Device
 */
/*@{*/

/*
 * device (I/O) system
 */
enum rt_device_class_type
{
	RT_Device_Class_Char = 0,	/* character device	*/
	RT_Device_Class_Block,		/* block device */
	RT_Device_Class_NetIf,		/* net interface */
	RT_Device_Class_MTD,		/* memory device */
	RT_Device_Class_CAN,		/* CAN device */
	RT_Device_Class_RTC,		/* RTC device */
	RT_Device_Class_Unknown		/* unknown device */
};

/* device flags */
#define RT_DEVICE_FLAG_DEACTIVATE	0x000	/* not inited 			*/

#define RT_DEVICE_FLAG_RDONLY		0x001	/* read only 			*/
#define RT_DEVICE_FLAG_WRONLY		0x002	/* write only 			*/
#define RT_DEVICE_FLAG_RDWR			0x003	/* read and write 		*/

#define RT_DEVICE_FLAG_REMOVABLE	0x004	/* removable device 	*/
#define RT_DEVICE_FLAG_STANDALONE	0x008	/* standalone device	*/
#define RT_DEVICE_FLAG_ACTIVATED	0x010	/* device is activated 	*/
#define RT_DEVICE_FLAG_SUSPENDED	0x020	/* device is suspended 	*/
#define RT_DEVICE_FLAG_STREAM		0x040	/* stream mode 			*/

#define RT_DEVICE_FLAG_INT_RX		0x100	/* INT mode on Rx 		*/
#define RT_DEVICE_FLAG_DMA_RX		0x200	/* DMA mode on Rx 		*/
#define RT_DEVICE_FLAG_INT_TX		0x400	/* INT mode on Tx 		*/
#define RT_DEVICE_FLAG_DMA_TX		0x800	/* DMA mode on Tx		*/

#define RT_DEVICE_OFLAG_CLOSE		0x000	/* device is closed 	*/
#define RT_DEVICE_OFLAG_RDONLY		0x001	/* read only access		*/
#define RT_DEVICE_OFLAG_WRONLY		0x002	/* write only access	*/
#define RT_DEVICE_OFLAG_RDWR		0x003	/* read and write 		*/
#define RT_DEVICE_OFLAG_OPEN		0x008	/* device is opened 	*/

/* general device commands */
#define RT_DEVICE_CTRL_RESUME	    0x01	/* resume device 	*/
#define RT_DEVICE_CTRL_SUSPEND	    0x02	/* suspend device 	*/

/* special device commands */
#define RT_DEVICE_CTRL_CHAR_STREAM	0x10	/* stream mode on char device 	*/
#define RT_DEVICE_CTRL_BLK_GETGEOME	0x10	/* get geometry information 	*/
#define RT_DEVICE_CTRL_NETIF_GETMAC	0x10	/* get mac address 				*/
#define RT_DEVICE_CTRL_MTD_FORMAT	0x10	/* format a MTD device 			*/
#define RT_DEVICE_CTRL_RTC_GET_TIME	0x10	/* get time */
#define RT_DEVICE_CTRL_RTC_SET_TIME	0x11	/* set time */

typedef struct rt_device* rt_device_t;
/*
 * Device related structure
 */
struct rt_device
{
	struct rt_object parent;

	/* device type */
	enum rt_device_class_type type;
	/* device flag and device open flag*/
	rt_uint16_t flag, open_flag;

	/* device call back */
	rt_err_t (*rx_indicate)(rt_device_t dev, rt_size_t size);
	rt_err_t (*tx_complete)(rt_device_t dev, void* buffer);

	/* common device interface */
	rt_err_t  (*init)	(rt_device_t dev);
	rt_err_t  (*open)	(rt_device_t dev, rt_uint16_t oflag);
	rt_err_t  (*close)	(rt_device_t dev);
	rt_size_t (*read)	(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size);
	rt_size_t (*write)	(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size);
	rt_err_t  (*control)(rt_device_t dev, rt_uint8_t cmd, void *args);

#ifdef RT_USING_DEVICE_SUSPEND
	rt_err_t (*suspend) (rt_device_t dev);
	rt_err_t (*resumed) (rt_device_t dev);
#endif

	/* device private data */
	void* private;
};

/*@}*/
#endif

#ifdef __cplusplus
}
#endif

#endif
