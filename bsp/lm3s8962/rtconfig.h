/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

/* RT_NAME_MAX*/
#define RT_NAME_MAX	8

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE	8

/* PRIORITY_MAX*/
#define RT_THREAD_PRIORITY_MAX	32

/* Tick per Second*/
#define RT_TICK_PER_SECOND	100

/* SECTION: RT_DEBUG */
/* Thread Debug*/
/* #define RT_DEBUG */
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
#define RT_USING_DEVICE_IPC

#define RT_USING_UART1
// #define RT_USING_UART2
// #define RT_USING_UART3

/* SECTION: Console options */
#define RT_USING_CONSOLE
/* the buffer size of console*/
#define RT_CONSOLEBUF_SIZE	128

/* SECTION: FinSH shell options */
/* Using FinSH as Shell*/
#define RT_USING_FINSH
/* Using symbol table */
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION

#define RT_USING_LIBC
#define RT_USING_DFS
#define RT_USING_POSIX_DEVIO
#define RT_USING_DFS_DEVFS
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

/* ip address of target */
#define RT_LWIP_IPADDR "192.168.1.30"

/* gateway address of target */
#define RT_LWIP_GWADDR  "192.168.1.1"

/* mask address of target */
#define RT_LWIP_MSKADDR  "255.255.255.0"

/* tcp thread options */
#define RT_LWIP_TCPTHREAD_PRIORITY		22
#define RT_LWIP_TCPTHREAD_MBOX_SIZE		4
#define RT_LWIP_TCPTHREAD_STACKSIZE		1024

/* ethernet if thread options */
#define RT_LWIP_ETHTHREAD_PRIORITY		23
#define RT_LWIP_ETHTHREAD_MBOX_SIZE		4
#define RT_LWIP_ETHTHREAD_STACKSIZE		512

/* the size of each pbuf in the pbuf pool. */
#define RT_LWIP_PBUF_POOL_BUFSIZE		1500

#define RT_USING_LWIP141
#endif
