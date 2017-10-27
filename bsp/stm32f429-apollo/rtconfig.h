#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

/* RT-Thread Kernel */

#define RT_NAME_MAX 8
#define RT_ALIGN_SIZE 4
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 1000
#define RT_DEBUG
#define RT_USING_OVERFLOW_CHECK
#define RT_DEBUG_INIT 1
/* RT_DEBUG_THREAD is not set */
#define RT_USING_HOOK
#define IDLE_THREAD_STACK_SIZE 1024
/* RT_USING_TIMER_SOFT is not set */

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_MEMHEAP
#define RT_USING_HEAP
#define RT_USING_SMALL_MEM
/* RT_USING_SLAB is not set */

/* Kernel Device Object */

#define RT_USING_DEVICE
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart"
/* RT_USING_MODULE is not set */

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
/* RT_USING_USER_MAIN is not set */

/* C++ features */

/* RT_USING_CPLUSPLUS is not set */

/* Command shell */

#define RT_USING_FINSH
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION
#define FINSH_THREAD_STACK_SIZE 2048
/* FINSH_USING_AUTH is not set */
#define FINSH_DEFAULT_PASSWORD "rtthread"
/* FINSH_USING_MSH is not set */
/* FINSH_USING_MSH_DEFAULT is not set */
/* FINSH_USING_MSH_ONLY is not set */

/* Device virtual file system */

#define RT_USING_DFS
/* DFS_USING_WORKDIR is not set */
#define DFS_FILESYSTEMS_MAX 4
#define DFS_FD_MAX 16
#define RT_USING_DFS_ELMFAT
#define RT_DFS_ELM_CODE_PAGE 437
#define RT_DFS_ELM_WORD_ACCESS
/* RT_DFS_ELM_USE_LFN_0 is not set */
/* RT_DFS_ELM_USE_LFN_1 is not set */
/* RT_DFS_ELM_USE_LFN_2 is not set */
#define RT_DFS_ELM_USE_LFN_3
#define RT_DFS_ELM_USE_LFN 3
#define RT_DFS_ELM_MAX_LFN 255
#define RT_DFS_ELM_DRIVES 2
#define RT_DFS_ELM_MAX_SECTOR_SIZE 4096
/* RT_DFS_ELM_USE_ERASE is not set */
#define RT_DFS_ELM_REENTRANT
#define RT_USING_DFS_DEVFS
/* RT_USING_DFS_NET is not set */
/* RT_USING_DFS_NFS is not set */

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_USING_SERIAL
/* RT_USING_CAN is not set */
/* RT_USING_HWTIMER is not set */
#define RT_USING_I2C
#define RT_USING_I2C_BITOPS
/* RT_USING_PIN is not set */
/* RT_USING_MTD_NOR is not set */
#define RT_USING_MTD_NAND
#define RT_MTD_NAND_DEBUG
#define RT_USING_RTC
#define RT_USING_SDIO
#define RT_USING_SPI
#define RT_USING_SFUD
#define RT_SFUD_USING_SFDP
#define RT_SFUD_USING_FLASH_INFO_TABLE
#define RT_SFUD_DEBUG
/* RT_USING_W25QXX is not set */
/* RT_USING_GD is not set */
/* RT_USING_ENC28J60 is not set */
/* RT_USING_SPI_WIFI is not set */
/* RT_USING_WDT is not set */
/* RT_USING_USB_HOST is not set */
/* RT_USING_USB_DEVICE is not set */

/* libc */

#define RT_USING_LIBC
/* RT_USING_PTHREADS is not set */

/* Network stack */

/* light weight TCP/IP stack */

/* RT_USING_LWIP is not set */

/* Modbus master and slave stack */

/* RT_USING_MODBUS is not set */

/* RT-Thread online packages */

/* IoT - internet of things */

/* PKG_USING_CJSON is not set */
/* PKG_USING_PAHOMQTT is not set */
/* PKG_USING_WEBCLIENT is not set */

/* language packages */

/* PKG_USING_JERRYSCRIPT is not set */

/* miscellaneous packages */

/* PKG_USING_HELLO is not set */

/* multimedia packages */

/* security packages */

/* system packages */

/* PKG_USING_CMBACKTRACE is not set */
/* PKG_USING_PARTITION is not set */

/* BSP_SPECIAL CONFIG */

#define RT_RTC_NAME "rtc"
#define RT_USING_EXT_SDRAM
#define RT_USING_UART1
#define RT_USING_UART2
#define RT_USING_UART3
#define RT_USING_SPI5

#endif
