/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

/* RT_NAME_MAX*/
#define RT_NAME_MAX	8

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE	8

/* PRIORITY_MAX */
#define RT_THREAD_PRIORITY_MAX	256

/* Tick per Second */
#define RT_TICK_PER_SECOND	100

/* SECTION: RT_DEBUG */
/* Thread Debug */
#define RT_DEBUG
#define RT_DEBUG_COLOR
/* #define RT_THREAD_DEBUG */

#define RT_USING_OVERFLOW_CHECK

/* Using Hook */
#define RT_USING_HOOK

/* Using Software Timer */
#define RT_USING_TIMER_SOFT
#define RT_TIMER_THREAD_PRIO		8
#define RT_TIMER_THREAD_STACK_SIZE	512
#define RT_TICK_PER_SECOND	10

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
/* #define RT_USING_SMALL_MEM */

/* Using SLAB Allocator */
#define RT_USING_SLAB

#define RT_USING_CONSOLE
/* SECTION: Device System */
/* Using Device System */
#define RT_USING_DEVICE

/* SECTION: Console options */
/* the buffer size of console */
#define RT_CONSOLEBUF_SIZE	128

/* SECTION: finsh, a C-Express shell */
/* Using FinSH as Shell*/
#define RT_USING_FINSH
#define FINSH_USING_SYMTAB
#define FINSH USING DESCRIPTION

/* SECTION: a runtime libc library */
/* a runtime libc library */

/* SECTION: a mini libc */

/* SECTION: C++ support */
/* Using C++ support */
/* #define RT_USING_CPLUSPLUS */

/* SECTION: Device filesystem support */
/* using DFS support */
/* #define RT_USING_DFS */
/* #define RT_USING_DFS_ELMFAT */
/* #define RT_USING_DFS_YAFFS2 */

/* #define DFS_USING_WORKDIR */

/* the max number of mounted filesystem */
#define DFS_FILESYSTEMS_MAX		2
/* the max number of opened files 		*/
#define DFS_FD_MAX					16
/* the max number of cached sector 		*/
#define DFS_CACHE_MAX_NUM   		4

/* SECTION: lwip, a lighwight TCP/IP protocol stack */
/* Using lighweight TCP/IP protocol stack */
/* #define RT_USING_LWIP */
/* #define RT_LWIP_DNS */

/* Trace LwIP protocol */
/* #define RT_LWIP_DEBUG */

/* Enable ICMP protocol */
#define RT_LWIP_ICMP

/* Enable IGMP protocol */
#define RT_LWIP_IGMP

/* Enable UDP protocol */
#define RT_LWIP_UDP

/* Enable TCP protocol */
#define RT_LWIP_TCP

/* the number of simulatenously active TCP connections*/
#define RT_LWIP_TCP_PCB_NUM	5

/* TCP sender buffer space */
#define RT_LWIP_TCP_SND_BUF	1024*10

/* TCP receive window. */
#define RT_LWIP_TCP_WND	1024

/* Enable SNMP protocol */
/* #define RT_LWIP_SNMP */

/* Using DHCP */
/* #define RT_LWIP_DHCP */

/* ip address of target */
#define RT_LWIP_IPADDR0	192
#define RT_LWIP_IPADDR1	168
#define RT_LWIP_IPADDR2	1
#define RT_LWIP_IPADDR3	30

/* gateway address of target */
#define RT_LWIP_GWADDR0	192
#define RT_LWIP_GWADDR1	168
#define RT_LWIP_GWADDR2	1
#define RT_LWIP_GWADDR3	1

/* mask address of target */
#define RT_LWIP_MSKADDR0	255
#define RT_LWIP_MSKADDR1	255
#define RT_LWIP_MSKADDR2	255
#define RT_LWIP_MSKADDR3	0

/* the number of blocks for pbuf */
#define RT_LWIP_PBUF_NUM	16

/* thread priority of tcpip thread */
#define RT_LWIP_TCPTHREAD_PRIORITY	128

/* mail box size of tcpip thread to wait for */
#define RT_LWIP_TCPTHREAD_MBOX_SIZE	8

/* thread stack size of tcpip thread */
#define RT_LWIP_TCPTHREAD_STACKSIZE	4096

/* thread priority of ethnetif thread */
#define RT_LWIP_ETHTHREAD_PRIORITY	144

/* mail box size of ethnetif thread to wait for */
#define RT_LWIP_ETHTHREAD_MBOX_SIZE	32

/* thread stack size of ethnetif thread */
#define RT_LWIP_ETHTHREAD_STACKSIZE	1024

/* SECTION: RTGUI support */
/* using RTGUI support */
/* #define RT_USING_RTGUI */

/* name length of RTGUI object */
#define RTGUI_NAME_MAX		16
/* support 16 weight font */
#define RTGUI_USING_FONT16
/* support 16 weight font */
#define RTGUI_USING_FONT12
/* support Chinese font */
#define RTGUI_USING_FONTHZ
/* use DFS as file interface */
#define RTGUI_USING_DFS_FILERW
/* use font file as Chinese font */
/* #define RTGUI_USING_HZ_FILE */
/* use Chinese bitmap font */
#define RTGUI_USING_HZ_BMP
/* use small size in RTGUI */
/* #define RTGUI_USING_SMALL_SIZE */
/* use mouse cursor */
/* #define RTGUI_USING_MOUSE_CURSOR */
#endif
