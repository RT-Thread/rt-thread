/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

/* RT_NAME_MAX*/
#define RT_NAME_MAX		8

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE	4

/* PRIORITY_MAX */
#define RT_THREAD_PRIORITY_MAX	32

/* Tick per Second */
#define RT_TICK_PER_SECOND	100

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
#define RT_USING_UART2
#define RT_UART_RX_BUFFER_SIZE	64

/* SECTION: Console options */
//#define RT_TINY_SIZE
#define RT_USING_CONSOLE
/* the buffer size of console */
#define RT_CONSOLEBUF_SIZE	128

/* SECTION: finsh, a C-Express shell */
/* Using FinSH as Shell*/
#define RT_USING_FINSH
/* Using symbol table */
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION
#define FINSH_THREAD_STACK_SIZE 4096

/* SECTION: Device filesystem support */
/* using DFS support */
/* #define RT_USING_DFS */
/* #define RT_USING_DFS_ELMFAT */
/* use long file name feature 			*/
#define RT_DFS_ELM_USE_LFN			1
/* the max number of file length 		*/
#define RT_DFS_ELM_MAX_LFN		32
/* #define RT_USING_DFS_YAFFS2 */
/* #define RT_USING_DFS_UFFS */
/* #define RT_USING_DFS_DEVFS */

//#define RT_USING_DFS_NFS
//#define RT_NFS_HOST_EXPORT		"192.168.1.5:/"

#define DFS_USING_WORKDIR

/* the max number of mounted filesystem */
#define DFS_FILESYSTEMS_MAX		4
/* the max number of opened files 		*/
#define DFS_FD_MAX					16
/* the max number of cached sector 		*/
#define DFS_CACHE_MAX_NUM   		4

/* SECTION: RTGUI support */
/* using RTGUI support */
//#define RT_USING_RTGUI

/* name length of RTGUI object */
#define RTGUI_NAME_MAX		16
/* support 16 weight font */
//#define RTGUI_USING_FONT16
/* support 12 weight font */
#define RTGUI_USING_FONT12
/* support Chinese font */
//#define RTGUI_USING_FONTHZ
/* use DFS as file interface */
//#define RTGUI_USING_DFS_FILERW
/* use font file as Chinese font */
/* #define RTGUI_USING_HZ_FILE */
/* use Chinese bitmap font */
//#define RTGUI_USING_HZ_BMP
/* use small size in RTGUI */
//#define RTGUI_USING_SMALL_SIZE
/* use mouse cursor */
/* #define RTGUI_USING_MOUSE_CURSOR */
#define RTGUI_DEFAULT_FONT_SIZE 12

#endif
