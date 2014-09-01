/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

#define RT_HEAP_SIZE   (1024*1024*2)

#if  defined(_MSC_VER)
/* SECTION: port for visual studio */
#undef RT_USING_NEWLIB
#undef RT_USING_MINILIBC
#define NORESOURCE  //RT_VESRION in winuser.h
#define _CRT_ERRNO_DEFINED  //errno macro redefinition
#define _INC_WTIME_INL//dfs_elm.c time.h conflicts with wtime.inl
#define _INC_TIME_INL //dfs_elm.c time.h conflicts with wtime.inl

/* disable some warning in MSC */
#pragma warning(disable:4273)	/* to ignore: warning C4273: inconsistent dll linkage */
#pragma warning(disable:4312)   /* to ignore: warning C4312: 'type cast' : conversion from 'rt_uint32_t' to 'rt_uint32_t *' */
#pragma warning(disable:4311)   /* to ignore: warning C4311: 'type cast' : pointer truncation from 'short *__w64 ' to 'long' */
#pragma warning(disable:4996)   /* to ignore: warning C4996: The POSIX name for this item is deprecated. */
#pragma warning(disable:4267)   /* to ignore: warning C4267: conversion from 'size_t' to 'rt_size_t', possible loss of data */
#pragma warning(disable:4244)   /* to ignore: warning C4244: '=' : conversion from '__w64 int' to 'rt_size_t', possible loss of data */

#elif defined(__GNUC__)
#define RT_USING_NOLIBC

#if defined(__MINGW32__)
#define _NO_OLDNAMES   /* to ignore: mode_t in sys/type.h */
#endif
#endif

/* SECTION: basic kernel options */
/* RT_NAME_MAX*/
#define RT_NAME_MAX	8

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE	4

/* PRIORITY_MAX */
#define RT_THREAD_PRIORITY_MAX  32	

/* Tick per Second */
#define RT_TICK_PER_SECOND	100

/* SECTION: RT_DEBUG */
/* Thread Debug */
#define RT_DEBUG
//#define RT_DEBUG_SCHEDULER   1
#define RT_THREAD_DEBUG

#define RT_USING_OVERFLOW_CHECK

/* Using Hook */
#define RT_USING_HOOK

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
#define RT_USING_MAILBOX

/* Using Message Queue */
#define RT_USING_MESSAGEQUEUE

/* SECTION: Memory Management */
/* Using Memory Pool Management*/
/* #define RT_USING_MEMPOOL */

/* Using Dynamic Heap Management */
#define RT_USING_HEAP

/* Using Small MM */
#define RT_USING_SMALL_MEM
/* #define RT_TINY_SIZE */

/* SECTION: Device System */
/* Using Device System */
#define RT_USING_DEVICE
#define RT_USING_DEVICE_IPC
/* #define RT_USING_UART1 */

/* SECTION: Console options */
#define RT_USING_CONSOLE
/* the buffer size of console*/
#define RT_CONSOLEBUF_SIZE	128
#define RT_CONSOLE_DEVICE_NAME	"sci0"

/* SECTION: component options */
#define RT_USING_COMPONENTS_INIT

/* SECTION: APP MODULE  */
/* #define RT_USING_MODULE */

/* SECTION: MTD interface options */
/* using mtd nand flash */
#define RT_USING_MTD_NAND
/* using mtd nor flash */
/* #define RT_USING_MTD_NOR */

/* SECTION: finsh, a C-Express shell */
#define RT_USING_FINSH
/* Using symbol table */
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION

/* SECTION: device file system */
#define RT_USING_DFS
#define DFS_FILESYSTEM_TYPES_MAX  8

/* DFS: ELM FATFS options */
#define RT_USING_DFS_ELMFAT
#define RT_DFS_ELM_WORD_ACCESS
/* Reentrancy (thread safe) of the FatFs module.  */
#define RT_DFS_ELM_REENTRANT
/* Number of volumes (logical drives) to be used. */
#define RT_DFS_ELM_DRIVES			2
/* #define RT_DFS_ELM_USE_LFN			1 */
#define RT_DFS_ELM_MAX_LFN			255
/* Maximum sector size to be handled. */
#define RT_DFS_ELM_MAX_SECTOR_SIZE  512

/* DFS: network file system options */
/* #define RT_USING_DFS_NFS */

/* DFS: UFFS nand file system options */
#define RT_USING_DFS_UFFS
/* configuration for uffs, more to see dfs_uffs.h and uffs_config.h */
#define RT_CONFIG_UFFS_ECC_MODE  UFFS_ECC_HW_AUTO
/* enable this ,you need provide a mark_badblock/check_block function */
/* #define RT_UFFS_USE_CHECK_MARK_FUNCITON */

/* DFS: JFFS2 nor flash file system options */
//#define RT_USING_DFS_JFFS2

/* DFS: windows share directory mounted to rt-thread/dfs  */
/* only used in bsp/simulator */
#ifdef _WIN32
#define RT_USING_DFS_WINSHAREDIR
#endif

/* the max number of mounted file system */
#define DFS_FILESYSTEMS_MAX			4
/* the max number of opened files 		*/
#define DFS_FD_MAX					4

/* SECTION: lwip, a lightweight TCP/IP protocol stack */
/* #define RT_USING_LWIP */
/* LwIP uses RT-Thread Memory Management */
#define RT_LWIP_USING_RT_MEM
/* Enable ICMP protocol*/
#define RT_LWIP_ICMP
/* Enable UDP protocol*/
#define RT_LWIP_UDP
/* Enable TCP protocol*/
#define RT_LWIP_TCP
/* Enable DNS */
#define RT_LWIP_DNS

/* the number of simultaneously active TCP connections*/
#define RT_LWIP_TCP_PCB_NUM	5

/* Using DHCP */
/* #define RT_LWIP_DHCP */

/* ip address of target*/
#define RT_LWIP_IPADDR0	192
#define RT_LWIP_IPADDR1	168
#define RT_LWIP_IPADDR2	126
#define RT_LWIP_IPADDR3	30

/* gateway address of target*/
#define RT_LWIP_GWADDR0	192
#define RT_LWIP_GWADDR1	168
#define RT_LWIP_GWADDR2	126
#define RT_LWIP_GWADDR3	1

/* mask address of target*/
#define RT_LWIP_MSKADDR0	255
#define RT_LWIP_MSKADDR1	255
#define RT_LWIP_MSKADDR2	255
#define RT_LWIP_MSKADDR3	0

/* tcp thread options */
#define RT_LWIP_TCPTHREAD_PRIORITY		12
#define RT_LWIP_TCPTHREAD_MBOX_SIZE		10
#define RT_LWIP_TCPTHREAD_STACKSIZE		1024

/* Ethernet if thread options */
#define RT_LWIP_ETHTHREAD_PRIORITY		15
#define RT_LWIP_ETHTHREAD_MBOX_SIZE		10
#define RT_LWIP_ETHTHREAD_STACKSIZE		512

/* TCP sender buffer space */
#define RT_LWIP_TCP_SND_BUF	8192
/* TCP receive window. */
#define RT_LWIP_TCP_WND		8192

/* SECTION: RT-Thread/GUI */
/* #define RT_USING_RTGUI */

/* name length of RTGUI object */
#define RTGUI_NAME_MAX		12
/* support 16 weight font */
#define RTGUI_USING_FONT16
/* support Chinese font */
#define RTGUI_USING_FONTHZ
/* use DFS as file interface */
#define RTGUI_USING_DFS_FILERW
/* use font file as Chinese font */
/* #define RTGUI_USING_HZ_FILE */
/* use Chinese bitmap font */
#define RTGUI_USING_HZ_BMP
/* use small size in RTGUI */
#define RTGUI_USING_SMALL_SIZE
/* use mouse cursor */
/* #define RTGUI_USING_MOUSE_CURSOR */
/* default font size in RTGUI */
#define RTGUI_DEFAULT_FONT_SIZE	16

/* image support */
#define RTGUI_IMAGE_XPM
#define RTGUI_IMAGE_BMP
/* #define RTGUI_IMAGE_JPEG */
/* #define RTGUI_IMAGE_PNG */
#define RTGUI_USING_NOTEBOOK_IMAGE

#endif
