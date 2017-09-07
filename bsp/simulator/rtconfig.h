/* RT-Thread config file */

#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

// <RDTConfigurator URL="http://www.rt-thread.com/eclipse">

// <integer name="RT_NAME_MAX" description="Maximal size of kernel object name length" default="6" />
#define RT_NAME_MAX	6
// <integer name="RT_ALIGN_SIZE" description="Alignment size for CPU architecture data access" default="4" />
#define RT_ALIGN_SIZE	4
// <integer name="RT_THREAD_PRIORITY_MAX" description="Maximal level of thread priority" default="32">
// <item description="8">8</item>
// <item description="32">32</item>
// <item description="256">256</item>
// </integer>
#define RT_THREAD_PRIORITY_MAX	32
// <integer name="RT_TICK_PER_SECOND" description="OS tick per second" default="100" />
#define RT_TICK_PER_SECOND	100
// <section name="RT_DEBUG" description="Kernel Debug Configuration" default="true" >
#define RT_DEBUG
// <bool name="RT_THREAD_DEBUG" description="Thread debug enable" default="false" />
// #define RT_THREAD_DEBUG
// <bool name="RT_USING_OVERFLOW_CHECK" description="Thread stack over flow detect" default="true" />
#define RT_USING_OVERFLOW_CHECK
// </section>

// <bool name="RT_USING_HOOK" description="Using hook functions" default="true" />
#define RT_USING_HOOK
// <section name="RT_USING_TIMER_SOFT" description="Using software timer which will start a thread to handle soft-timer" default="true" >
// #define RT_USING_TIMER_SOFT
// <integer name="RT_TIMER_THREAD_PRIO" description="The priority level of timer thread" default="4" />
#define RT_TIMER_THREAD_PRIO	4
// <integer name="RT_TIMER_THREAD_STACK_SIZE" description="The stack size of timer thread" default="512" />
#define RT_TIMER_THREAD_STACK_SIZE	512
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
// <bool name="RT_USING_DEVICE_IPC" description="Using Inter-Thread communication for Device" default="true" >
#define RT_USING_DEVICE_IPC
// <bool name="RT_USING_SERIAL" description="Using serial device framework" default="true">
#define RT_USING_SERIAL
// <bool name="RT_USING_UART0" description="Using UART0" default="true" />
#define RT_USING_UART0
// </section>

// <section name="RT_USING_CONSOLE" description="Using console" default="true" >
#define RT_USING_CONSOLE
// <integer name="RT_CONSOLEBUF_SIZE" description="The buffer size for console output" default="128" />
#define RT_CONSOLEBUF_SIZE	128
// <string name="RT_CONSOLE_DEVICE_NAME" description="The device name for console" default="uart" />
#define RT_CONSOLE_DEVICE_NAME	"console"
// </section>

// <section name="RT_USING_FINSH" description="Using finsh as shell, which is a C-Express shell" default="true" >
#define RT_USING_FINSH
// <bool name="FINSH_USING_SYMTAB" description="Using symbol table in finsh shell" default="true" />
#define FINSH_USING_SYMTAB
// <bool name="FINSH_USING_DESCRIPTION" description="Keeping description in symbol table" default="true" />
#define FINSH_USING_DESCRIPTION
// <integer name="FINSH_THREAD_STACK_SIZE" description="The stack size for finsh thread" default="4096" />
#define FINSH_THREAD_STACK_SIZE	4096
// <bool name="FINSH_USING_MSH" description="Enable module shell feature" />
#define FINSH_USING_MSH
// <bool name="FINSH_USING_MSH_DEFAULT" description="Use module shell as the default shell" />
#define FINSH_USING_MSH_DEFAULT
// </section>

// <section name="LIBC" description="C Runtime library setting" default="always" >
// <bool name="RT_USING_LIBC" description="Using C library" default="true" />
// #define RT_USING_LIBC
// <bool name="RT_USING_PTHREADS" description="Using POSIX threads library" default="true" />
// #define RT_USING_PTHREADS
// <bool name="RT_USING_MODULE" description="Enable Moudle Application" default="true" />
// #define RT_USING_MODULE
// </section>

// <section name="RT_USING_DFS" description="Device file system" default="true" >
#define RT_USING_DFS
// <bool name="DFS_USING_WORKDIR" description="Using working directory" default="true" />
#define DFS_USING_WORKDIR
// <integer name="DFS_FILESYSTEMS_MAX" description="The maximal number of mounted file system" default="4" />
#define DFS_FILESYSTEMS_MAX	2
// <integer name="DFS_FD_MAX" description="The maximal number of opened files" default="4" />
#define DFS_FD_MAX	4
// <bool name="RT_USING_DFS_ELMFAT" description="Using ELM FatFs" default="true" />
#define RT_USING_DFS_ELMFAT
// <integer name="RT_DFS_ELM_USE_LFN" description="Support long file name" default="0">
// <item description="LFN with static LFN working buffer">1</item>
// <item description="LFN with dynamic LFN working buffer on the stack">2</item>
// <item description="LFN with dynamic LFN working buffer on the heap">3</item>
// </integer>
#define RT_DFS_ELM_USE_LFN	3
// <integer name="RT_DFS_ELM_CODE_PAGE" description="OEM code page" default="437">
#define RT_DFS_ELM_CODE_PAGE	437
// <integer name="RT_DFS_ELM_MAX_LFN" description="Maximal size of file name length" default="255" />
#define RT_DFS_ELM_MAX_LFN	128
// <bool name="RT_USING_DFS_YAFFS2" description="Using YAFFS2" default="false" />
// #define RT_USING_DFS_YAFFS2
// <bool name="RT_USING_DFS_UFFS" description="Using UFFS" default="false" />
// #define RT_USING_DFS_UFFS
// <bool name="RT_USING_DFS_DEVFS" description="Using devfs for device objects" default="true" />
// #define RT_USING_DFS_DEVFS
// <bool name="RT_USING_DFS_NFS" description="Using NFS v3 client file system" default="false" />
// #define RT_USING_DFS_NFS
// <string name="RT_NFS_HOST_EXPORT" description="NFSv3 host export" default="192.168.1.5:/" />
#define RT_NFS_HOST_EXPORT	"192.168.1.5:/"
// </section>

// <section name="RT_USING_LWIP" description="lwip, a lightweight TCP/IP protocol stack" default="true" >
// #define RT_USING_LWIP
// <bool name="RT_LWIP_ICMP" description="Enable ICMP protocol" default="true" />
#define RT_LWIP_ICMP
// <bool name="RT_LWIP_IGMP" description="Enable IGMP protocol" default="false" />
// #define RT_LWIP_IGMP
// <bool name="RT_LWIP_UDP" description="Enable UDP protocol" default="true" />
#define RT_LWIP_UDP
// <bool name="RT_LWIP_TCP" description="Enable TCP protocol" default="true" />
#define RT_LWIP_TCP
// <bool name="RT_LWIP_DNS" description="Enable DNS protocol" default="true" />
#define RT_LWIP_DNS
// <bool name="RT_LWIP_SNMP" description="Enable SNMP protocol" default="false" />
// #define RT_LWIP_SNMP
// <bool name="RT_LWIP_DHCP" description="Enable DHCP client to get IP address" default="false" />
// #define RT_LWIP_DHCP
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
#define RT_LWIP_IPADDR3 30
// <ipaddr name="RT_LWIP_GWADDR" description="Gateway address of device" default="192.168.1.1" />
#define RT_LWIP_GWADDR0 192
#define RT_LWIP_GWADDR1 168
#define RT_LWIP_GWADDR2 1
#define RT_LWIP_GWADDR3 1
// <ipaddr name="RT_LWIP_MSKADDR" description="Mask address of device" default="255.255.255.0" />
#define RT_LWIP_MSKADDR0 255
#define RT_LWIP_MSKADDR1 255
#define RT_LWIP_MSKADDR2 255
#define RT_LWIP_MSKADDR3 0
// </section>

// <section name="RT_USING_RTGUI" description="RT-Thread/GUI" default="true" >
// #define RT_USING_RTGUI
// <integer name="RTGUI_NAME_MAX" description="the name size of RT-Thread/GUI widget/objects" default="12" />
#define RTGUI_NAME_MAX	12
// <bool name="RTGUI_USING_SMALL_SIZE" description="use small size in RT-Thread/GUI" default="true" />
#define RTGUI_USING_SMALL_SIZE
// <bool name="RTGUI_USING_FONT16" description="support 16 weight font" default="true" />
#define RTGUI_USING_FONT16
// <bool name="RTGUI_USING_FONT12" description="support 12 weight font" default="true" />
// #define RTGUI_USING_FONT12
// <bool name="RTGUI_USING_FONTHZ" description="support Chinese font" default="true" />
#define RTGUI_USING_FONTHZ
// <integer name="RTGUI_DEFAULT_FONT_SIZE" description="default font size in RT-Thread/GUI" default="16" />
#define RTGUI_DEFAULT_FONT_SIZE	16
// <bool name="RTGUI_USING_DFS_FILERW" description="use RT-Thread/DFS as file interface" default="true" />
#define RTGUI_USING_DFS_FILERW
// <bool name="RTGUI_USING_HZ_BMP" description="use Chinese font bitmap engine" default="true" />
#define RTGUI_USING_HZ_BMP
// <bool name="RTGUI_IMAGE_XPM" description="Using xpm image in RTGUI" default="true" />
#define RTGUI_IMAGE_XPM
// <bool name="RTGUI_IMAGE_JPEG" description="Using jpeg image in RTGUI" default="true" />
// #define RTGUI_IMAGE_JPEG
// <bool name="RTGUI_IMAGE_PNG" description="Using PNG image in RTGUI" default="true" />
// #define RTGUI_IMAGE_PNG
// <bool name="RTGUI_IMAGE_PNG" description="Using PNG image in RTGUI" default="true" />
#define RTGUI_IMAGE_BMP
// <bool name="RTGUI_USING_HZ_FILE" description="use font file as Chinese font" default="false" />
 #define RTGUI_USING_HZ_FILE
// <bool name="RTGUI_USING_MOUSE_CURSOR" description="use mouse cursor" default="false" />
#define RTGUI_USING_MOUSE_CURSOR
// </section>

// </RDTConfigurator>

#define RT_HEAP_SIZE   (1024*1024*2)

#if defined(_MSC_VER)
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
#endif /* end of __MINGW32__ */

#endif /* end of _MSC_VER */

#ifdef _Win32
#define RT_USING_DFS_WINSHAREDIR
#endif

#endif
