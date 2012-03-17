/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

/* RT_NAME_MAX */
#define RT_NAME_MAX				8

/* RT_ALIGN_SIZE */
#define RT_ALIGN_SIZE			8

/* PRIORITY_MAX */
#define RT_THREAD_PRIORITY_MAX	32

/* Tick per Second */
#define RT_TICK_PER_SECOND		100

/* SECTION: RT_DEBUG */
/* Thread Debug */
#define RT_DEBUG
#define RT_USING_OVERFLOW_CHECK

/* Using Hook */
#define RT_USING_HOOK

/* SECTION: IPC */
/* Using Semaphore */
#define RT_USING_SEMAPHORE

/* Using Mutex */
#define RT_USING_MUTEX

/* Using Event */
#define RT_USING_EVENT

/* Using MailBox */
#define RT_USING_MAILBOX

/* Using Message Queue */
#define RT_USING_MESSAGEQUEUE

/* SECTION: Memory Management */
/* Using Memory Pool Management*/
#define RT_USING_MEMPOOL

/* Using Dynamic Heap Management */
#define RT_USING_HEAP

/* Using Small MM */
#define RT_USING_SMALL_MEM

/* SECTION: Device System */
/* Using Device System */
#define RT_USING_DEVICE
/* RT_USING_UART */
#define RT_USING_UART0
#define RT_UART_RX_BUFFER_SIZE	64

/* SECTION: Console options */
/* #define RT_TINY_SIZE */
#define RT_USING_CONSOLE
/* the buffer size of console */
#define RT_CONSOLEBUF_SIZE		128
/* the device used by console */
#define RT_CONSOLE_DEVICE_NAME	"uart0"

/* SECTION: finsh, a C-Express shell */
/* Using FinSH as Shell*/
#define RT_USING_FINSH
/* Using symbol table */
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION
#define FINSH_THREAD_STACK_SIZE	1024
#define FINSH_DEVICE_NAME		RT_CONSOLE_DEVICE_NAME

/* SECTION: Device filesystem support */
/* using DFS support */
#define RT_USING_DFS
#define RT_USING_DFS_ELMFAT
/* use long file name feature */
/* #define RT_DFS_ELM_USE_LFN */
/* the max number of file length */
#define RT_DFS_ELM_MAX_LFN		32
/* #define RT_USING_DFS_UFFS */
/* #define RT_USING_DFS_DEVFS */

/* the max number of mounted filesystem */
#define DFS_FILESYSTEMS_MAX		2
/* the max number of opened files */
#define DFS_FD_MAX				8
/* using working directory */
#define DFS_USING_WORKDIR

#endif
