#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

// <RDTConfigurator URL="http://www.rt-thread.com/eclipse">

// <integer name="RT_NAME_MAX" description="Maximal size of kernel object name length" default="6" />
#define RT_NAME_MAX	10
// <integer name="RT_ALIGN_SIZE" description="Alignment size for CPU architecture data access" default="4" />
#define RT_ALIGN_SIZE	8
// <integer name="RT_THREAD_PRIORITY_MAX" description="Maximal level of thread priority" default="32">
// <item description="8">8</item>
// <item description="32">32</item>
// <item description="256">256</item>
// </integer>
#define RT_THREAD_PRIORITY_MAX	32
// <integer name="RT_TICK_PER_SECOND" description="OS tick per second" default="100" />
#define RT_TICK_PER_SECOND	1000
// <section name="RT_DEBUG" description="Kernel Debug Configuration" default="true" >
#define RT_DEBUG
// <bool name="RT_THREAD_DEBUG" description="Thread debug enable" default="false" />
// #define RT_THREAD_DEBUG
// <bool name="RT_USING_OVERFLOW_CHECK" description="Thread stack over flow detect" default="true" />
#define RT_USING_OVERFLOW_CHECK
// <bool name="RT_USING_INTERRUPT_INFO" description="Show more interrupt description" default="true" />
#define RT_USING_INTERRUPT_INFO
// <integer name="IDLE_THREAD_STACK_SIZE" description="The stack size of idle thread" default="1024" />
#define IDLE_THREAD_STACK_SIZE	1024
// </section>

// <bool name="RT_USING_HOOK" description="Using hook functions" default="true" />
#define RT_USING_HOOK
// <section name="RT_USING_TIMER_SOFT" description="Using software timer which will start a thread to handle soft-timer" default="true" >
// #define RT_USING_TIMER_SOFT
// <integer name="RT_TIMER_THREAD_PRIO" description="The priority level of timer thread" default="4" />
#define RT_TIMER_THREAD_PRIO	4
// <integer name="RT_TIMER_THREAD_STACK_SIZE" description="The stack size of timer thread" default="512" />
#define RT_TIMER_THREAD_STACK_SIZE	512
// <integer name="RT_TIMER_TICK_PER_SECOND" description="The soft-timer tick per second" default="10" />
#define RT_TIMER_TICK_PER_SECOND	10
// </section>

// <section name="IPC" description="Inter-Thread communication" default="always" >
// <bool name="RT_USING_SEMAPHORE" description="Using semaphore in the system" default="true" />
#define RT_USING_SEMAPHORE
// <bool name="RT_USING_MUTEX" description="Using mutex in the system" default="true" />
#define RT_USING_MUTEX
// <bool name="RT_USING_EVENT" description="Using event group in the system" default="true" />
#define RT_USING_EVENT
// <bool name="RT_USING_MAILBOX" description="Using mailbox in the system" default="true" />
#define RT_USING_MAILBOX
// <bool name="RT_USING_MESSAGEQUEUE" description="Using message queue in the system" default="true" />
#define RT_USING_MESSAGEQUEUE
// </section>

// <section name="MM" description="Memory Management" default="always" >
// <bool name="RT_USING_MEMPOOL" description="Using Memory Pool Management in the system" default="true" />
#define RT_USING_MEMPOOL
// <bool name="RT_USING_MEMHEAP" description="Using Memory Heap Object in the system" default="true" />
#define RT_USING_MEMHEAP
// <bool name="RT_USING_HEAP" description="Using Dynamic Heap Management in the system" default="true" />
#define RT_USING_HEAP
// <bool name="RT_USING_SMALL_MEM" description="Optimizing for small memory" default="false" />
#define RT_USING_SMALL_MEM
// <bool name="RT_USING_SLAB" description="Using SLAB memory management for large memory" default="false" />
// #define RT_USING_SLAB
// </section>

// <section name="RT_USING_DEVICE" description="Using Device Driver Framework" default="true" >
#define RT_USING_DEVICE
// <bool name="RT_USING_UART" description="Using UART" default="true" />
#define RT_USING_UART
// <bool name="RT_USING_UART2" description="Using UART0" default="true" />
#define RT_USING_UART2
// <integer name="RT_UART_RX_BUFFER_SIZE" description="The buffer size for UART reception" default="64" />
#define RT_UART_RX_BUFFER_SIZE	64
// </section>

#define RT_USING_FPU

// <section name="RT_USING_CONSOLE" description="Using console" default="true" >
#define RT_USING_CONSOLE
// <integer name="RT_CONSOLEBUF_SIZE" description="The buffer size for console output" default="128" />
#define RT_CONSOLEBUF_SIZE	128
// <string name="RT_CONSOLE_DEVICE_NAME" description="The device name for console" default="uart" />
#define RT_CONSOLE_DEVICE_NAME	"uart2"
// </section>

// <bool name="RT_USING_COMPONENTS_INIT" description="Using RT-Thread components initialization" default="true" />
#define RT_USING_COMPONENTS_INIT
// <section name="RT_USING_FINSH" description="Using finsh as shell, which is a C-Express shell" default="true" >
#define RT_USING_FINSH
// <bool name="FINSH_USING_SYMTAB" description="Using symbol table in finsh shell" default="true" />
#define FINSH_USING_SYMTAB
// <bool name="FINSH_USING_DESCRIPTION" description="Keeping description in symbol table" default="true" />
#define FINSH_USING_DESCRIPTION
// <integer name="FINSH_THREAD_STACK_SIZE" description="The stack size for finsh thread" default="4096" />
#define FINSH_THREAD_STACK_SIZE	4096
// <bool name="FINSH_USING_MSH" description="Using module shell" default="true" />
#define FINSH_USING_MSH
// <bool name="FINSH_USING_MSH_DEFAULT" description="Using module shell as the default shell" default="true" />
#define FINSH_USING_MSH_DEFAULT
// </section>

// <section name="LIBC" description="C Runtime library setting" default="always" >
#define RT_USING_LIBC
// <bool name="RT_USING_PTHREADS" description="Using POSIX threads library" default="true" />
#define RT_USING_PTHREADS
// </section>

// <section name="RT_USING_DFS" description="Device file system" default="true" >
// #define RT_USING_DFS
// <bool name="DFS_USING_WORKDIR" description="Using working directory" default="true" />
// #define DFS_USING_WORKDIR
// <integer name="DFS_FILESYSTEMS_MAX" description="The maximal number of mounted file system" default="4" />
#define DFS_FILESYSTEMS_MAX	2
// <integer name="DFS_FD_MAX" description="The maximal number of opened files" default="4" />
#define DFS_FD_MAX	4
// <bool name="RT_USING_DFS_ELMFAT" description="Using ELM FatFs" default="true" />
#define RT_USING_DFS_ELMFAT
// <integer name="RT_DFS_ELM_USE_LFN" description="Support long file name" default="0">
// <item description="LFN1">1</item>
// <item description="LFN1">2</item>
// </integer>
#define RT_DFS_ELM_USE_LFN	1
// <integer name="RT_DFS_ELM_MAX_LFN" description="Maximal size of file name length" default="255" />
#define RT_DFS_ELM_MAX_LFN	64
// <bool name="RT_USING_DFS_YAFFS2" description="Using YAFFS2" default="false" />
// #define RT_USING_DFS_YAFFS2
// <bool name="RT_USING_DFS_UFFS" description="Using UFFS" default="false" />
// #define RT_USING_DFS_UFFS
// <bool name="RT_USING_DFS_DEVFS" description="Using devfs for device objects" default="true" />
// #define RT_USING_DFS_DEVFS
// <bool name="RT_USING_DFS_NFS" description="Using NFS v3 client file system" default="false" />
// #define RT_USING_DFS_NFS
// <string name="RT_NFS_HOST_EXPORT" description="NFSv3 host export" default="192.168.1.5:/" />
#define RT_NFS_HOST_EXPORT	"192.168.1.254:/"
// </section>

// <section name="RT_USING_LWIP" description="lwip, a lightweight TCP/IP protocol stack" default="true" >
#define RT_USING_LWIP
#define RT_USING_GMAC_INT_MODE
#define RT_USING_LWIP141
//#define RT_LWIP_DEBUG
#define RT_LWIP_USING_RT_MEM


// <bool name="RT_LWIP_ICMP" description="Enable ICMP protocol" default="true" />
#define RT_LWIP_ICMP
// <bool name="RT_LWIP_IGMP" description="Enable IGMP protocol" default="false" />
#define RT_LWIP_IGMP
// <bool name="RT_LWIP_UDP" description="Enable UDP protocol" default="true" />
#define RT_LWIP_UDP
// <bool name="RT_LWIP_TCP" description="Enable TCP protocol" default="true" />
#define RT_LWIP_TCP
// <bool name="RT_LWIP_DNS" description="Enable DNS protocol" default="true" />
#define RT_LWIP_DNS
// <integer name="RT_LWIP_PBUF_NUM" description="Maximal number of buffers in the pbuf pool" default="4" />
#define RT_LWIP_PBUF_NUM	4
#define RT_LWIP_PBUF_POOL_BUFSIZE 2048
// <integer name="RT_LWIP_TCP_PCB_NUM" description="Maximal number of simultaneously active TCP connections" default="5" />
#define RT_LWIP_TCP_PCB_NUM	3
// <integer name="RT_LWIP_TCP_SND_BUF" description="TCP sender buffer size" default="8192" />
#define RT_LWIP_TCP_SND_BUF	4096
// <integer name="RT_LWIP_TCP_WND" description="TCP receive window" default="8192" />
#define RT_LWIP_TCP_WND	2048
// <bool name="RT_LWIP_SNMP" description="Enable SNMP protocol" default="false" />
// #define RT_LWIP_SNMP
// <bool name="RT_LWIP_DHCP" description="Enable DHCP client to get IP address" default="false" />
// #define RT_LWIP_DHCP
// <integer name="RT_LWIP_TCP_SEG_NUM" description="the number of simultaneously queued TCP" default="4" />
#define RT_LWIP_TCP_SEG_NUM	40
// <integer name="RT_LWIP_TCPTHREAD_PRIORITY" description="the thread priority of TCP thread" default="128" />
#define RT_LWIP_TCPTHREAD_PRIORITY	12
// <integer name="RT_LWIP_TCPTHREAD_MBOX_SIZE" description="the mail box size of TCP thread to wait for" default="32" />
#define RT_LWIP_TCPTHREAD_MBOX_SIZE	8
// <integer name="RT_LWIP_TCPTHREAD_STACKSIZE" description="the thread stack size of TCP thread" default="4096" />
#define RT_LWIP_TCPTHREAD_STACKSIZE	4096
// <integer name="RT_LWIP_ETHTHREAD_PRIORITY" description="the thread priority of ethnetif thread" default="144" />
#define RT_LWIP_ETHTHREAD_PRIORITY	14
// <integer name="RT_LWIP_ETHTHREAD_MBOX_SIZE" description="the mail box size of ethnetif thread to wait for" default="8" />
#define RT_LWIP_ETHTHREAD_MBOX_SIZE	8
// <integer name="RT_LWIP_ETHTHREAD_STACKSIZE" description="the stack size of ethnetif thread" default="512" />
#define RT_LWIP_ETHTHREAD_STACKSIZE	512
// <ipaddr name="RT_LWIP_IPADDR" description="IP address of device" default="192.168.1.30" />
#define RT_LWIP_IPADDR0 192
#define RT_LWIP_IPADDR1 168
#define RT_LWIP_IPADDR2 1
#define RT_LWIP_IPADDR3 254
// <ipaddr name="RT_LWIP_GWADDR" description="Gateway address of device" default="192.168.1.1" />
#define RT_LWIP_GWADDR0 192
#define RT_LWIP_GWADDR1 168
#define RT_LWIP_GWADDR2 1
#define RT_LWIP_GWADDR3 3
// <ipaddr name="RT_LWIP_MSKADDR" description="Mask address of device" default="255.255.255.0" />
#define RT_LWIP_MSKADDR0 255
#define RT_LWIP_MSKADDR1 255
#define RT_LWIP_MSKADDR2 255
#define RT_LWIP_MSKADDR3 0
// </section>

// <section name="RT_USING_MODULE" description="Application module" default="true" >
// #define RT_USING_MODULE
// <bool name="RT_USING_LIBDL" description="Using dynamic library" default="true" />
// #define RT_USING_LIBDL
// </section>

// <section name="RT_USING_RTGUI" description="RTGUI, a graphic user interface" default="true" >
// #define RT_USING_RTGUI
// <integer name="RTGUI_NAME_MAX" description="Maximal size of RTGUI object name length" default="16" />
#define RTGUI_NAME_MAX	16
// <bool name="RTGUI_USING_FONT16" description="Support 16 weight font" default="true" />
#define RTGUI_USING_FONT16
// <bool name="RTGUI_USING_FONT12" description="Support 12 weight font" default="true" />
#define RTGUI_USING_FONT12
// <bool name="RTGUI_USING_FONTHZ" description="Support Chinese font" default="true" />
#define RTGUI_USING_FONTHZ
// <bool name="RTGUI_USING_DFS_FILERW" description="Using DFS as file interface " default="true" />
#define RTGUI_USING_DFS_FILERW
// <bool name="RTGUI_USING_HZ_FILE" description="Using font file as Chinese font" default="false" />
// #define RTGUI_USING_HZ_FILE
// <bool name="RTGUI_USING_HZ_BMP" description="Using Chinese bitmap font" default="true" />
#define RTGUI_USING_HZ_BMP
// <bool name="RTGUI_USING_SMALL_SIZE" description="Using small size in RTGUI" default="false" />
#define RTGUI_USING_SMALL_SIZE
// <bool name="RTGUI_USING_MOUSE_CURSOR" description="Using mouse cursor in RTGUI" default="false" />
// #define RTGUI_USING_MOUSE_CURSOR
// <bool name="RTGUI_IMAGE_XPM" description="Using xpm image in RTGUI" default="true" />
#define RTGUI_IMAGE_XPM
// <bool name="RTGUI_IMAGE_JPEG" description="Using jpeg image in RTGUI" default="true" />
// #define RTGUI_IMAGE_JPEG
// <bool name="RTGUI_IMAGE_PNG" description="Using png image in RTGUI" default="true" />
// #define RTGUI_IMAGE_PNG
// <bool name="RTGUI_IMAGE_BMP" description="Using bmp image in RTGUI" default="true" />
#define RTGUI_IMAGE_BMP
// </section>

// </RDTConfigurator>

#endif
