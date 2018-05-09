/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

/* RT_NAME_MAX*/
#define RT_NAME_MAX	   8

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE	4

/* PRIORITY_MAX */
#define RT_THREAD_PRIORITY_MAX	32

/* Tick per Second */
#define RT_TICK_PER_SECOND	1000

/* SECTION: RT_DEBUG */
/* Thread Debug */
#define RT_DEBUG
#define RT_DEBUG_INIT    1
#define RT_USING_OVERFLOW_CHECK

/* Using Hook */
#define RT_USING_HOOK
//#define RT_USING_TRACE

#define IDLE_THREAD_STACK_SIZE     1024

/* Using Software Timer */
/* #define RT_USING_TIMER_SOFT */
#define RT_TIMER_THREAD_PRIO		4
#define RT_TIMER_THREAD_STACK_SIZE	512
// <bool name="RT_USING_MODULE" description="Using Application Module" default="true" />
#define RT_USING_MODULE
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
#define RT_USING_MEMPOOL

/* Using Dynamic Heap Management */
#define RT_USING_HEAP
#define RT_USING_MEMHEAP
/* Using Small MM */
#define RT_USING_SMALL_MEM

#define RT_USING_COMPONENTS_INIT

/* SECTION: Device System */
/* Using Device System */
#define RT_USING_DEVICE
#define RT_USING_DEVICE_IPC

/* SECTION: RTGUI support */
/* using RTGUI support */
// #define PKG_USING_GUIENGINE

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

/* Using serial framework */
#define RT_USING_SERIAL

#define RT_USING_USART0
#define RT_USING_USART1
#define RT_USING_USART2
#define RT_USING_UART3
#define RT_USING_UART4
#define RT_USING_USART5
#define RT_USING_UART6
#define RT_USING_UART7

/* Using GPIO pin framework */
//#define RT_USING_PIN

/* Using Hardware Timer framework */
//#define RT_USING_HWTIMER

#define RT_USING_EXT_SDRAM

/* SECTION: Console options */
#define RT_USING_CONSOLE
/* the buffer size of console*/
#define RT_CONSOLEBUF_SIZE	128

/* SECTION: finsh, a C-Express shell */
#define RT_USING_FINSH
/* Using symbol table */
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION
//#define FINSH_USING_MSH

#define RT_USING_RTC
#ifdef RT_USING_RTC
#define RT_RTC_NAME 				"rtc"
#endif

// <section name="LIBC" description="C Runtime library setting" default="always" >
// <bool name="RT_USING_LIBC" description="Using libc library" default="true" />
//#define RT_USING_LIBC

/* SECTION: device filesystem */
/* Using Device file system */
#define RT_USING_DFS /**/
// <bool name="RT_USING_DFS_DEVFS" description="Using devfs for device objects" default="true" />
#define RT_USING_DFS_DEVFS
//// <integer name="DFS_FILESYSTEM_TYPES_MAX" description="The maximal number of the supported file system type" default="4" />
//#define DFS_FILESYSTEM_TYPES_MAX    2
/* the max number of mounted filesystem */
#define DFS_FILESYSTEMS_MAX			2
/* the max number of opened files 		*/
#define DFS_FD_MAX					4
//#define DFS_USING_WORKDIR

/* Using ELM FATFS */
#define RT_USING_DFS_ELMFAT
////#define RT_DFS_ELM_WORD_ACCESS
///* Reentrancy (thread safe) of the FatFs module.  */
//#define RT_DFS_ELM_REENTRANT
///* Number of volumes (logical drives) to be used. */
#define RT_DFS_ELM_DRIVES			2
//#define RT_DFS_ELM_USE_LFN			3 /* */
#define RT_DFS_ELM_MAX_LFN			255
///* Maximum sector size to be handled. */
#define RT_DFS_ELM_MAX_SECTOR_SIZE  4096

/* SECTION: lwip, a lighwight TCP/IP protocol stack */
#define RT_USING_LWIP
/* Enable ICMP protocol*/
#define RT_LWIP_ICMP
/* Enable UDP protocol*/
#define RT_LWIP_UDP
/* Enable TCP protocol*/
#define RT_LWIP_TCP
/* Enable DNS */
#define RT_LWIP_DNS
/* Enable DHCP */
#define RT_LWIP_DHCP
/* Enable DEBUG */
#define RT_LWIP_DEBUG

/* the number of simulatenously active TCP connections*/
#define RT_LWIP_TCP_PCB_NUM	5

/* ip address of target*/
#define RT_LWIP_IPADDR0	192
#define RT_LWIP_IPADDR1	168
#define RT_LWIP_IPADDR2	10
#define RT_LWIP_IPADDR3	241

/* gateway address of target*/
#define RT_LWIP_GWADDR0	192
#define RT_LWIP_GWADDR1	168
#define RT_LWIP_GWADDR2	10
#define RT_LWIP_GWADDR3	1

/* mask address of target*/
#define RT_LWIP_MSKADDR0	255
#define RT_LWIP_MSKADDR1	255
#define RT_LWIP_MSKADDR2	255
#define RT_LWIP_MSKADDR3	0

/* tcp thread options */
#define RT_LWIP_TCPTHREAD_PRIORITY		12
#define RT_LWIP_TCPTHREAD_MBOX_SIZE		4
#define RT_LWIP_TCPTHREAD_STACKSIZE		1024

/* ethernet if thread options */
#define RT_LWIP_ETHTHREAD_PRIORITY		15
#define RT_LWIP_ETHTHREAD_MBOX_SIZE		4
#define RT_LWIP_ETHTHREAD_STACKSIZE		512

/* TCP sender buffer space */
#define RT_LWIP_TCP_SND_BUF	8192
/* TCP receive window. */
#define RT_LWIP_TCP_WND		8192

#define CHECKSUM_CHECK_TCP              0
#define CHECKSUM_CHECK_IP               0
#define CHECKSUM_CHECK_UDP              0

//#define CHECKSUM_GEN_TCP                0
//#define CHECKSUM_GEN_IP                 0
//#define CHECKSUM_GEN_UDP                0

/* RT_GDB_STUB */
//#define RT_USING_GDB

/* spi driver */
#define RT_USING_SPI
#define RT_USING_SPI0
#define RT_USING_SPI1
#define RT_USING_SPI2
#define RT_USING_SPI3
#define RT_USING_SPI4
#define RT_USING_SPI5
//#define RT_USING_W25QXX
//#define FLASH_DEBUG

#define RT_USING_SFUD
//#define RT_SFUD_USING_SFDP
#define RT_SFUD_USING_FLASH_INFO_TABLE

#define RT_USING_I2C
#define RT_USING_I2C_BITOPS

//#define RT_USING_CPU_FFS

#endif
