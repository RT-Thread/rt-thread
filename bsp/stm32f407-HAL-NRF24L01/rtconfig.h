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
#define RT_CONSOLE_DEVICE_NAME "uart1"

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


/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_PIPE_BUFSZ 512
#define RT_USING_SERIAL
#define RT_USING_PIN
#define RT_USING_RTC
#define RT_USING_SPI

/* Using USB */


/* POSIX layer and C standard library */

#define RT_USING_LIBC

/* Network */

/* Socket abstraction layer */


/* light weight TCP/IP stack */


/* Modbus master and slave stack */


/* AT commands */


/* VBUS(Virtual Software BUS) */


/* Utilities */


/* RT-Thread online packages */

/* IoT - internet of things */

#define PKG_USING_NRF24L01_NETWORK
#define PKG_USING_NRF24L01_NETWORK_LATEST_VERSION
#define NRF_SPI_BUS_NAME "spi2"
#define NRF_SPI_DEV_NAME "spi20"
#define NRF_SPI_CS_PIN 81
#define NRF_CE_PIN 80
#define NRF_IRQ_PIN 82
#define NRF24L01_USING_GATEWAY
#define NRF24L01_USING_EXAMPLE
#define NRF24L01_USING_NRF_LOG

/* Wi-Fi */

/* Marvell WiFi */


/* Wiced WiFi */


/* IoT Cloud */


/* security packages */

#define PKG_USING_TINYCRYPT
#define PKG_USING_TINYCRYPT_V110
#define TINY_CRYPT_MD5

/* language packages */


/* multimedia packages */


/* tools packages */


/* system packages */


/* peripheral libraries and drivers */


/* miscellaneous packages */

#define PKG_USING_MULTIBUTTON
#define PKG_USING_MULTIBUTTON_LATEST_VERSION

/* MultiButton Options */


/* sample package */

/* samples: kernel and components samples */


/* example package: hello */

#define SOC_STM32F407ZG
#define RT_HSE_VALUE 8000000
#define RT_HSE_HCLK 168000000

/* Serial Select */

#define RT_USING_UART1

/* SPI Select */

#define RT_USING_SPI2

#endif
