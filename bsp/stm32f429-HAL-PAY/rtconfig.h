#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

/* RT-Thread Kernel */

#define RT_NAME_MAX 8
#define RT_ALIGN_SIZE 4
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 1000
#define RT_USING_OVERFLOW_CHECK
#define IDLE_THREAD_STACK_SIZE 256
#define RT_USING_TIMER_SOFT
#define RT_TIMER_THREAD_PRIO 4
#define RT_TIMER_THREAD_STACK_SIZE 512
#define RT_DEBUG

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_MEMHEAP
#define RT_USING_SMALL_MEM
#define RT_USING_MEMTRACE
#define RT_USING_HEAP

/* Kernel Device Object */

#define RT_USING_DEVICE
#define RT_USING_INTERRUPT_INFO
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart6"

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 30720
#define RT_MAIN_THREAD_PRIORITY 10

/* C++ features */


/* Command shell */

#define RT_USING_FINSH
#define FINSH_THREAD_NAME "tshell"
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 30720
#define FINSH_CMD_SIZE 80
#define FINSH_USING_MSH
#define FINSH_USING_MSH_DEFAULT
#define FINSH_ARG_MAX 10

/* Device virtual file system */

#define RT_USING_DFS
#define DFS_USING_WORKDIR
#define DFS_FILESYSTEMS_MAX 4
#define DFS_FILESYSTEM_TYPES_MAX 4
#define DFS_FD_MAX 16
#define RT_USING_DFS_ELMFAT

/* elm-chan's FatFs, Generic FAT Filesystem Module */

#define RT_DFS_ELM_CODE_PAGE 437
#define RT_DFS_ELM_WORD_ACCESS
#define RT_DFS_ELM_USE_LFN_3
#define RT_DFS_ELM_USE_LFN 3
#define RT_DFS_ELM_MAX_LFN 255
#define RT_DFS_ELM_DRIVES 4
#define RT_DFS_ELM_MAX_SECTOR_SIZE 512
#define RT_DFS_ELM_REENTRANT
#define RT_USING_DFS_DEVFS
#define RT_USING_DFS_ROMFS
#define RT_USING_DFS_UFFS
#define RT_UFFS_ECC_MODE_3
#define RT_UFFS_ECC_MODE 3

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_PIPE_BUFSZ 512
#define RT_USING_SERIAL
#define RT_USING_I2C
#define RT_USING_I2C_BITOPS
#define RT_USING_PIN
#define RT_USING_MTD_NAND
#define RT_MTD_NAND_DEBUG
#define RT_USING_RTC
#define RT_USING_SPI

/* Using WiFi */


/* Using USB */


/* POSIX layer and C standard library */

#define RT_USING_LIBC
#define RT_USING_POSIX

/* Network */

/* Socket abstraction layer */

#define RT_USING_SAL

/* protocol stack implement */

#define SAL_USING_AT
#define SAL_SOCKETS_NUM 16
#define SAL_PROTO_FAMILIES_NUM 4

/* light weight TCP/IP stack */


/* Modbus master and slave stack */


/* AT commands */

#define RT_USING_AT
#define AT_DEBUG
#define AT_USING_CLIENT
#define AT_CLIENT_NUM_MAX 1
#define AT_USING_SOCKET
#define AT_USING_CLI
#define AT_PRINT_RAW_CMD
#define AT_SW_VERSION_NUM 0x10200

/* VBUS(Virtual Software BUS) */


/* Utilities */


/* RT-Thread online packages */

/* IoT - internet of things */


/* Wi-Fi */

/* Marvell WiFi */


/* Wiced WiFi */

#define PKG_USING_AT_DEVICE
#define PKG_AT_INIT_BY_THREAD
#define AT_DEVICE_NOT_SELECTED
#define AT_DEVICE_SOCKETS_NUM 0
#define PKG_USING_AT_DEVICE_LATEST_VERSION
#define PKG_AT_DEVICE_VER_NUM 0x10400

/* IoT Cloud */


/* security packages */


/* language packages */


/* multimedia packages */


/* tools packages */


/* system packages */

#define PKG_USING_SQLITE

/* peripheral libraries and drivers */


/* miscellaneous packages */


/* sample package */

/* samples: kernel and components samples */


/* example package: hello */

#define SOC_STM32F429IG
#define RT_HSE_VALUE 25000000
#define RT_HSE_HCLK 168000000
#define RT_USING_EXT_SDRAM
#define RT_USING_EXT_EEPROM

/* Serial Select */

#define RT_USING_UART1
#define RT_USING_UART2
#define RT_USING_UART3
#define RT_USING_UART4
#define RT_USING_UART6
#define RT_USING_UART7

/* SPI Select */

#define RT_USING_SPI2

#endif
