/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

/* RT_NAME_MAX*/
#define RT_NAME_MAX	8

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE	8

/* PRIORITY_MAX*/
#define RT_THREAD_PRIORITY_MAX	256

/* Tick per Second*/
#define RT_TICK_PER_SECOND	100

/* SECTION: RT_DEBUG */
/* Thread Debug*/
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
/* #define RT_USING_SMALL_MEM */

/* Using SLAB Allocator*/
#define RT_USING_SLAB

/* SECTION: Device System */
/* Using Device System*/
#define RT_USING_DEVICE

/* SECTION: Console options */
/* the buffer size of console*/
#define RT_CONSOLEBUF_SIZE	128

/* SECTION: FinSH shell options */
/* Using FinSH as Shell*/
/* #define RT_USING_FINSH */

/* SECTION: C++ support */
/* Using C++ support*/
/* #define RT_USING_CPLUSPLUS */

/* SECTION: lwip, a lighwight TCP/IP protocol stack */
/* Using lighweight TCP/IP protocol stack*/
/* #define RT_USING_LWIP */

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

/* Enable SNMP protocol*/
/* #define RT_LWIP_SNMP */

/* Using DHCP*/
/* #define RT_LWIP_DHCP */

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

#endif
