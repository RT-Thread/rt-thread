/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

#define IDLE_THREAD_STACK_SIZE	2048

/* RT_NAME_MAX*/
#define RT_NAME_MAX	32

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE	8

/* PRIORITY_MAX*/
#define RT_THREAD_PRIORITY_MAX	32

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
#define RT_USING_SMALL_MEM

/* Using SLAB Allocator*/
/* #define RT_USING_SLAB */

/* SECTION: Device System */
/* Using Device System*/
#define RT_USING_DEVICE

/* buffer size for UART reception*/
#define RT_UART_RX_BUFFER_SIZE	64

/* buffer size for UART transmission*/
#define RT_UART_TX_BUFFER_SIZE	64

/* Using UART1*/
#define RT_USING_UART1

/* Using UART1*/
/* #define RT_USING_UART2 */

/* Using UART1*/
/* #define RT_USING_UART3 */

/* SECTION: Console options */
#define RT_USING_CONSOLE
/* the buffer size of console*/
#define RT_CONSOLEBUF_SIZE	256

/* SECTION: FinSH shell options */
/* Using FinSH as Shell*/
#define RT_USING_FINSH
/* use symbol table */
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION
#define FINSH_THREAD_STACK_SIZE 8192


/* SECTION: a runtime libc library */
/* a runtime libc library*/

/* SECTION: C++ support */
/* Using C++ support*/
/* #define RT_USING_CPLUSPLUS */

/* SECTION: RTGUI support */
/* using RTGUI support*/
/* #define RT_USING_RTGUI */

/* SECTION: Device filesystem support */
/* using DFS support*/
/* #define RT_USING_DFS */

/* SECTION: EFSL filesystem support */
/* using  EFSL filesystem  support*/
/* #define RT_USING_EFSL */

/* SECTION: lwip, a lighwight TCP/IP protocol stack */
/* Using lighweight TCP/IP protocol stack*/
/* #define RT_USING_LWIP */

/* Using webserver goahead support*/
/* #define RT_USING_WEBSERVER */

/* Using ftpserver support*/
/* #define RT_USING_FTPSERVER */

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

/* TCP sender buffer space*/
#define RT_LWIP_TCP_SND_BUF	10240

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

/* the number of blocks for pbuf*/
#define RT_LWIP_PBUF_NUM	16

/* thread priority of tcpip thread*/
#define RT_LWIP_TCPTHREAD_PRIORITY	128

/* mail box size of tcpip thread to wait for*/
#define RT_LWIP_TCPTHREAD_MBOX_SIZE	8

/* thread stack size of tcpip thread*/
#define RT_LWIP_TCPTHREAD_STACKSIZE	4096

/* thread priority of ethnetif thread*/
#define RT_LWIP_ETHTHREAD_PRIORITY	144

/* mail box size of ethnetif thread to wait for*/
#define RT_LWIP_ETHTHREAD_MBOX_SIZE	32

/* thread stack size of ethnetif thread*/
#define RT_LWIP_ETHTHREAD_STACKSIZE	1024

#endif
