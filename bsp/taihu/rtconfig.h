/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

/* RT_NAME_MAX*/
#define RT_NAME_MAX 8

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE   8

/* PRIORITY_MAX*/
#define RT_THREAD_PRIORITY_MAX  32
#define IDLE_THREAD_STACK_SIZE  1024

/* Tick per Second*/
#define RT_TICK_PER_SECOND  100
/* CPU Frequency 200MHz */
#define RT_CPU_FREQ         200

/* SECTION: RT_DEBUG */
/* open debug for system assert */
// #define RT_DEBUG
/* Thread Debug*/
/* #define RT_THREAD_DEBUG */
/* #define RT_SCHEDULER_DEBUG */

/* Using Hook*/
#define RT_USING_HOOK

/* SECTION: IPC */
/* Using Semaphore*/
#define RT_USING_SEMAPHORE

/* Using Mutex*/
#define RT_USING_MUTEX

/* Using Event*/
#define RT_USING_EVENT

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

#define RT_TINY_SIZE

/* SECTION: Device System */
/* Using Device System*/
#define RT_USING_DEVICE
#define RT_USING_UART1
#define RT_UART_RX_BUFFER_SIZE  64

/* SECTION: Console options */
#define RT_USING_CONSOLE
/* the buffer size of console*/
#define RT_CONSOLEBUF_SIZE  128

/* SECTION: FinSH shell options */
/* Using FinSH as Shell*/
#define RT_USING_FINSH
/* Using symbol table */
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION

/* SECTION: lwip, a lighwight TCP/IP protocol stack */
/* #define RT_USING_LWIP */
/* Enable ICMP protocol*/
#define RT_LWIP_ICMP
/* Enable UDP protocol*/
#define RT_LWIP_UDP
/* Enable TCP protocol*/
#define RT_LWIP_TCP
/* Enable DNS */
#define RT_LWIP_DNS

/* the number of simulatenously active TCP connections*/
#define RT_LWIP_TCP_PCB_NUM 5

/* ip address of target*/
#define RT_LWIP_IPADDR0 192
#define RT_LWIP_IPADDR1 168
#define RT_LWIP_IPADDR2 1
#define RT_LWIP_IPADDR3 30

/* gateway address of target*/
#define RT_LWIP_GWADDR0 192
#define RT_LWIP_GWADDR1 168
#define RT_LWIP_GWADDR2 1
#define RT_LWIP_GWADDR3 1

/* mask address of target*/
#define RT_LWIP_MSKADDR0    255
#define RT_LWIP_MSKADDR1    255
#define RT_LWIP_MSKADDR2    255
#define RT_LWIP_MSKADDR3    0

/* tcp thread options */
#define RT_LWIP_TCPTHREAD_PRIORITY      12
#define RT_LWIP_TCPTHREAD_MBOX_SIZE     4
#define RT_LWIP_TCPTHREAD_STACKSIZE     1024

/* ethernet if thread options */
#define RT_LWIP_ETHTHREAD_PRIORITY      15
#define RT_LWIP_ETHTHREAD_MBOX_SIZE     4
#define RT_LWIP_ETHTHREAD_STACKSIZE     512

#endif
