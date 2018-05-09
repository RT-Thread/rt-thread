#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

/* RT-Thread Kernel */

#define RT_NAME_MAX 8
#define RT_ALIGN_SIZE 4
/* RT_THREAD_PRIORITY_8 is not set */
#define RT_THREAD_PRIORITY_32
/* RT_THREAD_PRIORITY_256 is not set */
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 100
#define RT_DEBUG
#define RT_USING_OVERFLOW_CHECK
#define RT_DEBUG_INIT 0
#define RT_DEBUG_THREAD 0
#define RT_USING_HOOK
#define IDLE_THREAD_STACK_SIZE 256
/* RT_USING_TIMER_SOFT is not set */

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE
/* RT_USING_SIGNALS is not set */

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_MEMHEAP
/* RT_USING_NOHEAP is not set */
#define RT_USING_SMALL_MEM
/* RT_USING_SLAB is not set */
/* RT_USING_MEMHEAP_AS_HEAP is not set */
/* RT_USING_MEMTRACE is not set */
#define RT_USING_HEAP

/* Kernel Device Object */

#define RT_USING_DEVICE
/* RT_USING_INTERRUPT_INFO is not set */
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart1"
/* RT_USING_MODULE is not set */

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN

/* C++ features */

/* RT_USING_CPLUSPLUS is not set */

/* Command shell */

#define RT_USING_FINSH
#define FINSH_THREAD_NAME "tshell"
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 4096
#define FINSH_CMD_SIZE 80
/* FINSH_USING_AUTH is not set */
#define FINSH_USING_MSH
#define FINSH_USING_MSH_DEFAULT
#define FINSH_USING_MSH_ONLY

/* Device virtual file system */

/* RT_USING_DFS is not set */

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_USING_SERIAL
/* RT_USING_CAN is not set */
/* RT_USING_HWTIMER is not set */
/* RT_USING_CPUTIME is not set */
/* RT_USING_I2C is not set */
#define RT_USING_PIN
/* RT_USING_MTD_NOR is not set */
/* RT_USING_MTD_NAND is not set */
/* RT_USING_RTC is not set */
/* RT_USING_SDIO is not set */
/* RT_USING_SPI is not set */
/* RT_USING_WDT is not set */
/* RT_USING_WIFI is not set */

/* Using USB */

/* RT_USING_USB_HOST is not set */
/* RT_USING_USB_DEVICE is not set */

/* POSIX layer and C standard library */

#define RT_USING_LIBC
/* RT_USING_PTHREADS is not set */

/* Network stack */

/* light weight TCP/IP stack */

/* RT_USING_LWIP is not set */

/* Modbus master and slave stack */

/* RT_USING_MODBUS is not set */

/* RT-Thread UI Engine */

/* PKG_USING_GUIENGINE is not set */

/* VBUS(Virtual Software BUS) */

/* RT_USING_VBUS is not set */

/* Utilities */

/* RT_USING_LOGTRACE is not set */
/* RT_USING_RYM is not set */

/* RT-Thread online packages */

/* system packages */

/* PKG_USING_PARTITION is not set */
/* PKG_USING_SQLITE is not set */
/* PKG_USING_RTI is not set */

/* IoT - internet of things */

/* PKG_USING_PAHOMQTT is not set */
/* PKG_USING_WEBCLIENT is not set */
/* PKG_USING_MONGOOSE is not set */
/* PKG_USING_WEBTERMINAL is not set */
/* PKG_USING_CJSON is not set */
/* PKG_USING_LJSON is not set */
/* PKG_USING_EZXML is not set */
/* PKG_USING_NANOPB is not set */
/* PKG_USING_GAGENT_CLOUD is not set */

/* Wi-Fi */

/* Marvell WiFi */

/* PKG_USING_WLANMARVELL is not set */

/* Wiced WiFi */

/* PKG_USING_WLAN_WICED is not set */
/* PKG_USING_COAP is not set */
/* PKG_USING_NOPOLL is not set */

/* security packages */

/* PKG_USING_MBEDTLS is not set */
/* PKG_USING_libsodium is not set */
/* PKG_USING_TINYCRYPT is not set */

/* language packages */

/* PKG_USING_JERRYSCRIPT is not set */
/* PKG_USING_MICROPYTHON is not set */

/* multimedia packages */

/* PKG_USING_OPENMV is not set */

/* tools packages */

/* PKG_USING_CMBACKTRACE is not set */
/* PKG_USING_EASYLOGGER is not set */
/* PKG_USING_SYSTEMVIEW is not set */
/* PKG_USING_IPERF is not set */

/* miscellaneous packages */

/* PKG_USING_FASTLZ is not set */
/* PKG_USING_MINILZO is not set */

/* example package: hello */

/* PKG_USING_HELLO is not set */
/* STM32F100RC is not set */
/* STM32F100RD is not set */
/* STM32F100RE is not set */
/* STM32F100VC is not set */
/* STM32F100VD is not set */
/* STM32F100VE is not set */
/* STM32F100ZC is not set */
/* STM32F100ZD is not set */
/* STM32F100ZE is not set */
/* STM32F101CB is not set */
/* STM32F101RB is not set */
/* STM32F101RC is not set */
/* STM32F101RD is not set */
/* STM32F101RE is not set */
/* STM32F101RF is not set */
/* STM32F101RG is not set */
/* STM32F101TB is not set */
/* STM32F101VB is not set */
/* STM32F101VC is not set */
/* STM32F101VD is not set */
/* STM32F101VE is not set */
/* STM32F101VF is not set */
/* STM32F101VG is not set */
/* STM32F101ZC is not set */
/* STM32F101ZD is not set */
/* STM32F101ZE is not set */
/* STM32F101ZF is not set */
/* STM32F101ZG is not set */
/* STM32F102CB is not set */
/* STM32F102RB is not set */
/* STM32F103C8 is not set */
/* STM32F103CB is not set */
/* STM32F103R8 is not set */
/* STM32F103RB is not set */
#define STM32F103RC
/* STM32F103RD is not set */
/* STM32F103RE is not set */
/* STM32F103RF is not set */
/* STM32F103RG is not set */
/* STM32F103T8 is not set */
/* STM32F103TB is not set */
/* STM32F103V8 is not set */
/* STM32F103VB is not set */
/* STM32F103VC is not set */
/* STM32F103VD is not set */
/* STM32F103VE is not set */
/* STM32F103VF is not set */
/* STM32F103VG is not set */
/* STM32F103ZC is not set */
/* STM32F103ZD is not set */
/* STM32F103ZE is not set */
/* STM32F103ZF is not set */
/* STM32F103ZG is not set */
/* STM32F105R8 is not set */
/* STM32F105RB is not set */
/* STM32F105RC is not set */
/* STM32F105V8 is not set */
/* STM32F105VB is not set */
/* STM32F105VC is not set */
/* STM32F107RB is not set */
/* STM32F107RC is not set */
/* STM32F107VB is not set */
/* STM32F107VC is not set */
/* RT_USING_HSI is not set */
#define RT_HSE_VALUE 8000000
#define RT_USING_UART1
/* RT_USING_UART2 is not set */
/* RT_USING_UART3 is not set */
/* RT_USING_SDCARD is not set */

#endif
