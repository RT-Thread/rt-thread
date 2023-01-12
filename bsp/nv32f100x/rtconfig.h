/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

/* RT_NAME_MAX*/
#define RT_NAME_MAX	   8

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE	8

/* PRIORITY_MAX */
#define RT_THREAD_PRIORITY_MAX	32

/* Tick per Second */
#define RT_TICK_PER_SECOND	1000

/* SECTION: RT_DEBUG */
/* Thread Debug */
//#define RT_DEBUG
//#define RT_DEBUG_INIT 1
//#define RT_USING_OVERFLOW_CHECK

/* Using Hook */
/* #define RT_USING_HOOK */

/* Using Software Timer */
/* #define RT_USING_TIMER_SOFT */
#define RT_TIMER_THREAD_PRIO		4
#define RT_TIMER_THREAD_STACK_SIZE	512
#define RT_TIMER_TICK_PER_SECOND	10

/* SECTION: IPC */
/* Using Semaphore*/
#define RT_USING_SEMAPHORE

/* Using Mutex */
#define RT_USING_MUTEX

/* Using Event */
#define RT_USING_EVENT

/* Using MailBox */
/* #define RT_USING_MAILBOX */

/* Using Message Queue */
/* #define RT_USING_MESSAGEQUEUE */

/* SECTION: Memory Management */
/* Using Memory Pool Management*/
/* #define RT_USING_MEMPOOL */

/* Using Dynamic Heap Management */
#define RT_USING_HEAP

/* Using Small MM */
#define RT_USING_SMALL_MEM
#define RT_USING_TINY_SIZE

// <bool name="RT_USING_COMPONENTS_INIT" description="Using RT-Thread components initialization" default="true" />
#define RT_USING_COMPONENTS_INIT

/* SECTION: Device System */
/* Using Device System */
#define RT_USING_DEVICE
// <bool name="RT_USING_DEVICE_IPC" description="Using device communication" default="true" />
#define RT_USING_DEVICE_IPC
// <bool name="RT_USING_SERIAL" description="Using Serial" default="true" />
#define RT_USING_SERIAL
#define RT_SERIAL_USING_DMA
#define RT_USING_HOOK
#define RT_USING_CPU_USAGE
/* SECTION: Console options */
#define RT_USING_CONSOLE
#define RT_USING_RTTTERMINAL
/* the buffer size of console*/
#define RT_CONSOLEBUF_SIZE	128
// <string name="RT_CONSOLE_DEVICE_NAME" description="The device name for console" default="uart1" />
#define RT_CONSOLE_DEVICE_NAME	    "uart0"


/* SECTION: finsh, a C-Express shell */
#define RT_USING_FINSH
#define RT_FINSHPROMRT_SIZE 16
/* configure finsh parameters */
#define FINSH_THREAD_PRIORITY 25
#define FINSH_THREAD_STACK_SIZE	512
#define FINSH_HISTORY_LINES	1
/* Using symbol table */
#define FINSH_USING_SYMTAB
//#define FINSH_USING_DESCRIPTION
#define FINSH_USING_MSH
#define FINSH_USING_MSH_ONLY

#define RT_USING_PIN
#define RT_USING_SPI
#define RT_DBG_APP

#define RT_USING_UART0

#define RT_USING_USER_MAIN

#endif
