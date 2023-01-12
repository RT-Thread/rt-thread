/* RT-Thread config file */

#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

// <<< Use Configuration Wizard in Context Menu >>>
// <h>Basic Configuration
// <o>Maximal level of thread priority <8-256>
//  <i>Default: 32
#define RT_THREAD_PRIORITY_MAX  8
// <o>OS tick per second
//  <i>Default: 1000   (1ms)
#define RT_TICK_PER_SECOND  100
// <o>Alignment size for CPU architecture data access
//  <i>Default: 4
#define RT_ALIGN_SIZE   8
// <o>the max length of object name<2-16>
//  <i>Default: 8
#define RT_NAME_MAX    8
// <c1>Using RT-Thread components initialization
//  <i>Using RT-Thread components initialization
#define RT_USING_COMPONENTS_INIT
// </c>
// <c1>Using user main
//  <i>Using user main
//#define RT_USING_USER_MAIN
// </c>
// <o>the size of main thread<1-4086>
//  <i>Default: 512
#define RT_MAIN_THREAD_STACK_SIZE     256

// </h>

// <h>Debug Configuration
// <c1>enable kernel debug configuration
//  <i>Default: enable kernel debug configuration
//#define RT_DEBUG
// </c>
// <o>enable components initialization debug configuration<0-1>
//  <i>Default: 0
#define RT_DEBUG_INIT 0
// <c1>thread stack over flow detect
//  <i> Diable Thread stack over flow detect
//#define RT_USING_OVERFLOW_CHECK
// </c>
// </h>

// <h>Hook Configuration
// <c1>using hook
//  <i>using hook
//#define RT_USING_HOOK
// </c>
// <c1>using idle hook
//  <i>using idle hook
//#define RT_USING_IDLE_HOOK
// </c>
// </h>

// <e>Software timers Configuration
// <i> Enables user timers
#define RT_USING_TIMER_SOFT         0
#if RT_USING_TIMER_SOFT == 0
#undef RT_USING_TIMER_SOFT
#endif
// <o>The priority level of timer thread <0-31>
//  <i>Default: 4
#define RT_TIMER_THREAD_PRIO        4
// <o>The stack size of timer thread <0-8192>
//  <i>Default: 512
#define RT_TIMER_THREAD_STACK_SIZE  512
// <o>The soft-timer tick per second <0-1000>
//  <i>Default: 100
#define RT_TIMER_TICK_PER_SECOND    100
// </e>

// <h>IPC(Inter-process communication) Configuration
// <c1>Using Semaphore
//  <i>Using Semaphore
#define RT_USING_SEMAPHORE
// </c>
// <c1>Using Mutex
//  <i>Using Mutex
#define RT_USING_MUTEX
// </c>
// <c1>Using Event
//  <i>Using Event
//#define RT_USING_EVENT
// </c>
// <c1>Using MailBox
//  <i>Using MailBox
#define RT_USING_MAILBOX
// </c>
// <c1>Using Message Queue
//  <i>Using Message Queue
//#define RT_USING_MESSAGEQUEUE
// </c>
// </h>

// <h>Memory Management Configuration
// <c1>Using Memory Pool Management
//  <i>Using Memory Pool Management
//#define RT_USING_MEMPOOL
// </c>
// <c1>Dynamic Heap Management
//  <i>Dynamic Heap Management
#define RT_USING_HEAP
// </c>
// <c1>using small memory
//  <i>using small memory
#define RT_USING_SMALL_MEM
// </c>
// <c1>using tiny size of memory
//  <i>using tiny size of memory
#define RT_USING_TINY_SIZE
// </c>
// </h>


// <h>Device System Configuration
// <c1>Using Device System
//  <i>Using Device System
#define RT_USING_DEVICE
// </c>
// <c1>Using device communication
//  <i>Using device communication
#define RT_USING_DEVICE_IPC
// </c>
// <c1>Using Serial
//  <i>Using Serial
//#define RT_USING_SERIAL
#define RT_SERIAL_USING_DMA
// </c>
// </h>

// <h>Console Configuration
// <c1>Using console
//  <i>Using console
#define RT_USING_CONSOLE
// </c>
// <o>the buffer size of console <1-1024>
//  <i>the buffer size of console
//  <i>Default: 128  (128Byte)
#define RT_CONSOLEBUF_SIZE          128
// <s>The device name for console
//  <i>The device name for console
//  <i>Default: uart1
#define RT_CONSOLE_DEVICE_NAME      "uart1"
// </h>


// <h>Finsh Configuration
// <c1>Using finsh as shell, which is a C-Express shell
//  <i>Using finsh as shell, which is a C-Express shell
#define RT_USING_FINSH
// </c>
// <o>the priority of finsh thread <1-7>
//  <i>the priority of finsh thread
//  <i>Default: 6
#define FINSH_THREAD_PRIORITY       (RT_THREAD_PRIORITY_MAX / 8 * 5 + 1)
// <o>the stack of finsh thread <1-4096>
//  <i>the stack of finsh thread
//  <i>Default: 4096  (4096Byte)
#define FINSH_THREAD_STACK_SIZE     512
// <o>the history lines of finsh thread <1-32>
//  <i>the history lines of finsh thread
//  <i>Default: 5
#define FINSH_HISTORY_LINES         1
// <c1>Using symbol table in finsh shell
//  <i>Using symbol table in finsh shell
#define FINSH_USING_SYMTAB
// </c>
// <c1>Using module shell in finsh
//  <i>Using module shell in finsh
#define FINSH_USING_MSH
// </c>
// <c1>Only using module shell in finsh
//  <i>Only using module shell in finsh
#define FINSH_USING_MSH_ONLY
// </c>
// </h>

// <<< end of configuration section >>>

#define RT_USING_UART
#define RT_USING_UART1

#endif
