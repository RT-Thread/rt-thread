/* RT-Thread config file */
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

// <RDTConfigurator URL="http://www.rt-thread.com/eclipse">

// <integer name="RT_NAME_MAX" description="Maximal size of kernel object name length" default="6" />
#define RT_NAME_MAX	8
// <integer name="RT_ALIGN_SIZE" description="Alignment size for CPU architecture data access" default="8" />
#define RT_ALIGN_SIZE	8
// <integer name="RT_THREAD_PRIORITY_MAX" description="Maximal level of thread priority" default="32">
// <item description="8">8</item>
// <item description="32">32</item>
// <item description="256">256</item>
// </integer>
#define RT_THREAD_PRIORITY_MAX	32
// <integer name="RT_TICK_PER_SECOND" description="OS tick per second" default="100" />
#define RT_TICK_PER_SECOND	100
// <section name="RT_DEBUG" description="Kernel Debug Configuration" default="true" >
// #define RT_DEBUG
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
#define RT_TIMER_THREAD_PRIO	8
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
// <bool name="RT_USING_MEMHEAP" description="Using Memory Heap Management in the system" default="true" />
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
// <bool name=RT_USING_DEVICE_IPC description="Using IPC in Device Driver Framework" default="true" />
#define RT_USING_DEVICE_IPC
// <bool name="RT_USING_SERIAL" description="Using Serial Device Driver Framework" default="true" />
#define RT_USING_SERIAL
#define RT_SERIAL_USING_DMA
// <bool name="RT_USING_UART0_0" description="Using UART0_0" default="true" />
#define RT_USING_UART0_0
// <bool name="RT_USING_UART0_1" description="Using UART0_1" default="false" />
// #define RT_USING_UART0_1
// <bool name="RT_USING_UART1_0" description="Using UART1_0" default="false" />
// #define RT_USING_UART1_0
// <bool name="RT_USING_UART1_1" description="Using UART1_1" default="false" />
// #define RT_USING_UART1_1
// <bool name="RT_USING_UART2_0" description="Using UART2_0" default="false" />
// #define RT_USING_UART2_0
// <bool name="RT_USING_UART2_1" description="Using UART2_1" default="false" />
// #define RT_USING_UART2_1
// <bool name="RT_USING_UART2_2" description="Using UART2_2" default="false" />
// #define RT_USING_UART2_2
// <bool name="RT_USING_UART3_0" description="Using UART3_0" default="false" />
// #define RT_USING_UART3_0
// <bool name="RT_USING_UART3_1" description="Using UART3_1" default="false" />
// #define RT_USING_UART3_1
// <bool name="RT_USING_UART3_2" description="Using UART3_2" default="false" />
// #define RT_USING_UART3_2
// <bool name="RT_USING_UART4_0" description="Using UART4_0" default="false" />
// #define RT_USING_UART4_0
// <bool name="RT_USING_UART4_1" description="Using UART4_1" default="false" />
// #define RT_USING_UART4_1
// <bool name="RT_USING_UART4_2" description="Using UART4_2" default="false" />
#define RT_USING_UART4_2
// <bool name="RT_USING_UART5_0" description="Using UART5_0" default="false" />
// #define RT_USING_UART5_0
// <bool name="RT_USING_UART5_1" description="Using UART5_1" default="false" />
// #define RT_USING_UART5_1
// <bool name="RT_USING_UART5_2" description="Using UART5_2" default="false" />
// #define RT_USING_UART5_2
// <bool name="RT_USING_UART6_0" description="Using UART6_0" default="false" />
// #define RT_USING_UART6_0
// <bool name="RT_USING_UART6_1" description="Using UART6_1" default="false" />
// #define RT_USING_UART6_1
// <bool name="RT_USING_UART7_0" description="Using UART7_0" default="false" />
#define RT_USING_UART7_0
// <bool name="RT_USING_UART7_1" description="Using UART7_1" default="false" />
// #define RT_USING_UART7_1
// <integer name="RT_UART_RX_BUFFER_SIZE" description="The buffer size for UART reception" default="64" />
#define RT_UART_RX_BUFFER_SIZE	64
// </section>

// <section name="RT_USING_CONSOLE" description="Using console" default="true" >
#define RT_USING_CONSOLE
// <integer name="RT_CONSOLEBUF_SIZE" description="The buffer size for console output" default="128" />
#define RT_CONSOLEBUF_SIZE	128
// <string name="RT_CONSOLE_DEVICE_NAME" description="The device name for console" default="uart" />
#define RT_CONSOLE_DEVICE_NAME	"uart0"
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
// </section>

// <bool name="RT_USING_PTHREADS" description="Using POSIX threads library" default="true" />
// #define RT_USING_PTHREADS
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
#define RT_NFS_HOST_EXPORT	"192.168.1.5:/"
// </section>

// <bool name="RT_USING_CMSIS_OS" description="Using CMSIS OS API" default="true" />
// #define RT_USING_CMSIS_OS
// <bool name="RT_USING_BSP_CMSIS" description="Using CMSIS in BSP" default="true" />
// #define RT_USING_BSP_CMSIS

// </RDTConfigurator>

#endif
