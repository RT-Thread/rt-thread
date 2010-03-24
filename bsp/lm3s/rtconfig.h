/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

/* RT_NAME_MAX*/
#define RT_NAME_MAX	8

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE	4

/* PRIORITY_MAX*/
#define RT_THREAD_PRIORITY_MAX	32

/* Tick per Second*/
#define RT_TICK_PER_SECOND	100

/* SECTION: RT_DEBUG */
/* Thread Debug*/
/* #define RT_DEBUG*/
/* #define RT_THREAD_DEBUG */

/* Using Hook*/
#define RT_USING_HOOK

/* SECTION: IPC */
/* Using Semaphore*/
#define RT_USING_SEMAPHORE

/* Using Mutex*/
#define RT_USING_MUTEX

/* Using Event*/
#define RT_USING_EVENT

/* Using Faset Event*/
/* #define RT_USING_FASTEVENT */

/* Using MailBox*/
#define RT_USING_MAILBOX

/* Using Message Queue*/
#define RT_USING_MESSAGEQUEUE

/* SECTION: Memory Management */
/* Using Memory Pool Management*/
#define RT_USING_MEMPOOL

/* Using Dynamic Heap Management*/
#define RT_USING_HEAP

/* Using Small MM*/
#define RT_USING_SMALL_MEM

/* Using SLAB Allocator*/
/* #define RT_USING_SLAB */

/* SECTION: Device System */
/* Using Device System*/
#define RT_USING_DEVICE

#define RT_USING_UART1
// #define RT_USING_UART2
// #define RT_USING_UART3

/* SECTION: Console options */
/* the buffer size of console*/
#define RT_CONSOLEBUF_SIZE	128

/* SECTION: FinSH shell options */
/* Using FinSH as Shell*/
#define RT_USING_FINSH
/* Using symbol table */
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION

/* SECTION: a mini libc */
/* Using mini libc library*/
/* #define RT_USING_MINILIBC */

/* SECTION: C++ support */
/* Using C++ support*/
/* #define RT_USING_CPLUSPLUS */

#define RT_USING_DFS
/* SECTION: DFS options */
#define RT_USING_DFS_ELMFAT
#define RT_DFS_ELM_WORD_ACCESS

/* the max number of mounted filesystem */
#define DFS_FILESYSTEMS_MAX		1
/* the max number of opened files 		*/
#define DFS_FD_MAX					4
/* the max number of cached sector 		*/
#define DFS_CACHE_MAX_NUM   		4

/* SECTION: lwip, a lighwight TCP/IP protocol stack */
/* Using lighweight TCP/IP protocol stack*/
#define RT_USING_LWIP

/* Trace LwIP protocol*/
/* #define RT_LWIP_DEBUG */

#define RT_LWIP_USING_RT_MEM

/* Enable ICMP protocol*/
#define RT_LWIP_ICMP

/* Enable IGMP protocol*/
#define RT_LWIP_IGMP

/* Enable UDP protocol*/
#define RT_LWIP_UDP

/* Enable TCP protocol*/
#define RT_LWIP_TCP

/* the number of simulatenously active TCP connections*/
#define RT_LWIP_TCP_PCB_NUM	5

/* Ethernet padding size */
#define RT_LWIP_ETH_PAD_SIZE 2

/* TCP sender buffer space*/
#define RT_LWIP_TCP_SND_BUF	1024*8
/* Enable SNMP protocol*/
#define RT_LWIP_SNMP

/* Using DHCP*/
/* #define RT_LWIP_DHCP */

#define RT_LWIP_DNS

/* ip address of target*/
#define RT_LWIP_IPADDR0	192
#define RT_LWIP_IPADDR1	168
#define RT_LWIP_IPADDR2	0
#define RT_LWIP_IPADDR3	30

/* gateway address of target*/
#define RT_LWIP_GWADDR0	192
#define RT_LWIP_GWADDR1	168
#define RT_LWIP_GWADDR2	0
#define RT_LWIP_GWADDR3	1

/* mask address of target*/
#define RT_LWIP_MSKADDR0	255
#define RT_LWIP_MSKADDR1	255
#define RT_LWIP_MSKADDR2	255
#define RT_LWIP_MSKADDR3	0

/* tcp thread options */
#define RT_LWIP_TCPTHREAD_PRIORITY		22
#define RT_LWIP_TCPTHREAD_MBOX_SIZE		4
#define RT_LWIP_TCPTHREAD_STACKSIZE		1024

/* ethernet if thread options */
#define RT_LWIP_ETHTHREAD_PRIORITY		23
#define RT_LWIP_ETHTHREAD_MBOX_SIZE		4
#define RT_LWIP_ETHTHREAD_STACKSIZE		512
#endif
