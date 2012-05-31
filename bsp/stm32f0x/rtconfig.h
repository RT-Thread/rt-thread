/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

/* RT_NAME_MAX*/
#define RT_NAME_MAX	   8

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE	4

/* PRIORITY_MAX */
#define RT_THREAD_PRIORITY_MAX	8

/* Tick per Second */
#define RT_TICK_PER_SECOND	100

/* SECTION: RT_DEBUG */
/* Thread Debug */
/* #define RT_DEBUG */
/* #define RT_USING_OVERFLOW_CHECK */

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
/* #define RT_USING_MUTEX */

/* Using Event */
/* #define RT_USING_EVENT */

/* Using MailBox */
/* #define RT_USING_MAILBOX */

/* Using Message Queue */
/* #define RT_USING_MESSAGEQUEUE */

/* SECTION: Memory Management */
/* Using Memory Pool Management*/
/* #define RT_USING_MEMPOOL */

/* Using Dynamic Heap Management */
/* #define RT_USING_HEAP */

/* Using Small MM */
#define RT_USING_SMALL_MEM
#define RT_USING_TINY_SIZE

/* SECTION: Device System */
/* Using Device System */
/* #define RT_USING_DEVICE */

/* SECTION: Console options */
//#define RT_USING_CONSOLE
/* the buffer size of console*/
#define RT_CONSOLEBUF_SIZE	128

/* SECTION: finsh, a C-Express shell */
/* #define RT_USING_FINSH */
/* Using symbol table */
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION

/* SECTION: device filesystem */
/* #define RT_USING_DFS */
//#define RT_USING_DFS_ELMFAT
#define RT_DFS_ELM_WORD_ACCESS
/* Reentrancy (thread safe) of the FatFs module.  */
#define RT_DFS_ELM_REENTRANT
/* Number of volumes (logical drives) to be used. */
#define RT_DFS_ELM_DRIVES			2
/* #define RT_DFS_ELM_USE_LFN			1 */
#define RT_DFS_ELM_MAX_LFN			255
/* Maximum sector size to be handled. */
#define RT_DFS_ELM_MAX_SECTOR_SIZE  512

#define RT_USING_DFS_ROMFS

/* the max number of mounted filesystem */
#define DFS_FILESYSTEMS_MAX			2
/* the max number of opened files 		*/
#define DFS_FD_MAX					4

#endif
