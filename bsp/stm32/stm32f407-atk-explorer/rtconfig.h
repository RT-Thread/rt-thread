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
#define RT_USING_HOOK
#define RT_USING_IDLE_HOOK
#define RT_IDEL_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 1024
#define RT_USING_TIMER_SOFT
#define RT_TIMER_THREAD_PRIO 4
#define RT_TIMER_THREAD_STACK_SIZE 512
#define RT_DEBUG
#define RT_DEBUG_COLOR

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
#define RT_USING_HEAP

/* Kernel Device Object */

#define RT_USING_DEVICE
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 256
#define RT_CONSOLE_DEVICE_NAME "uart1"
#define RT_VER_NUM 0x30104
#define ARCH_ARM
#define ARCH_ARM_CORTEX_M
#define ARCH_ARM_CORTEX_M4

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 2048
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
#define FINSH_THREAD_STACK_SIZE 2048
#define FINSH_CMD_SIZE 80
#define FINSH_USING_MSH
#define FINSH_USING_MSH_DEFAULT
#define FINSH_USING_MSH_ONLY
#define FINSH_ARG_MAX 10

/* Device virtual file system */

#define RT_USING_DFS
#define DFS_USING_WORKDIR
#define DFS_FILESYSTEMS_MAX 8
#define DFS_FILESYSTEM_TYPES_MAX 8
#define DFS_FD_MAX 16
#define RT_USING_DFS_ELMFAT

/* elm-chan's FatFs, Generic FAT Filesystem Module */

#define RT_DFS_ELM_CODE_PAGE 437
#define RT_DFS_ELM_WORD_ACCESS
#define RT_DFS_ELM_USE_LFN_3
#define RT_DFS_ELM_USE_LFN 3
#define RT_DFS_ELM_MAX_LFN 255
#define RT_DFS_ELM_DRIVES 2
#define RT_DFS_ELM_MAX_SECTOR_SIZE 4096
#define RT_DFS_ELM_REENTRANT
#define RT_USING_DFS_DEVFS
#define RT_USING_DFS_RAMFS

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_PIPE_BUFSZ 512
#define RT_USING_SYSTEM_WORKQUEUE
#define RT_SYSTEM_WORKQUEUE_STACKSIZE 2048
#define RT_SYSTEM_WORKQUEUE_PRIORITY 23
#define RT_USING_SERIAL
#define RT_SERIAL_USING_DMA
#define RT_SERIAL_RB_BUFSZ 64
#define RT_USING_PIN
#define RT_USING_SPI
#define RT_USING_SFUD
#define RT_SFUD_USING_SFDP
#define RT_SFUD_USING_FLASH_INFO_TABLE

/* Using WiFi */


/* Using USB */


/* POSIX layer and C standard library */

#define RT_USING_LIBC
#define RT_USING_PTHREADS
#define PTHREAD_NUM_MAX 8
#define RT_USING_POSIX

/* Network */

/* Socket abstraction layer */

#define RT_USING_SAL

/* protocol stack implement */

#define SAL_USING_LWIP
#define SAL_USING_AT
#define SAL_USING_POSIX

/* Network interface device */

#define RT_USING_NETDEV
#define NETDEV_USING_IFCONFIG
#define NETDEV_USING_PING
#define NETDEV_USING_NETSTAT
#define NETDEV_USING_AUTO_DEFAULT

/* light weight TCP/IP stack */

#define RT_USING_LWIP
#define RT_USING_LWIP202
#define RT_LWIP_IGMP
#define RT_LWIP_ICMP
#define RT_LWIP_DNS
#define RT_LWIP_DHCP
#define IP_SOF_BROADCAST 1
#define IP_SOF_BROADCAST_RECV 1

/* Static IPv4 Address */

#define RT_LWIP_IPADDR "192.168.1.30"
#define RT_LWIP_GWADDR "192.168.1.1"
#define RT_LWIP_MSKADDR "255.255.255.0"
#define RT_LWIP_UDP
#define RT_LWIP_TCP
#define RT_LWIP_RAW
#define RT_MEMP_NUM_NETCONN 8
#define RT_LWIP_PBUF_NUM 16
#define RT_LWIP_RAW_PCB_NUM 4
#define RT_LWIP_UDP_PCB_NUM 4
#define RT_LWIP_TCP_PCB_NUM 4
#define RT_LWIP_TCP_SEG_NUM 40
#define RT_LWIP_TCP_SND_BUF 8196
#define RT_LWIP_TCP_WND 8196
#define RT_LWIP_TCPTHREAD_PRIORITY 10
#define RT_LWIP_TCPTHREAD_MBOX_SIZE 8
#define RT_LWIP_TCPTHREAD_STACKSIZE 1024
#define RT_LWIP_ETHTHREAD_PRIORITY 12
#define RT_LWIP_ETHTHREAD_STACKSIZE 1024
#define RT_LWIP_ETHTHREAD_MBOX_SIZE 8
#define LWIP_NETIF_STATUS_CALLBACK 1
#define LWIP_NETIF_LINK_CALLBACK 1
#define SO_REUSE 1
#define LWIP_SO_RCVTIMEO 1
#define LWIP_SO_SNDTIMEO 1
#define LWIP_SO_RCVBUF 1
#define RT_LWIP_NETIF_LOOPBACK
#define LWIP_NETIF_LOOPBACK 1
#define RT_LWIP_USING_PING

/* Modbus master and slave stack */


/* AT commands */

#define RT_USING_AT
#define AT_USING_CLIENT
#define AT_CLIENT_NUM_MAX 4
#define AT_USING_SOCKET
#define AT_USING_CLI
#define AT_CMD_MAX_LEN 128
#define AT_SW_VERSION_NUM 0x10300

/* VBUS(Virtual Software BUS) */


/* Utilities */

#define RT_USING_ULOG
#define ULOG_OUTPUT_LVL_D
#define ULOG_OUTPUT_LVL 7
#define ULOG_USING_ISR_LOG
#define ULOG_ASSERT_ENABLE
#define ULOG_LINE_BUF_SIZE 256

/* log format */

#define ULOG_OUTPUT_FLOAT
#define ULOG_USING_COLOR
#define ULOG_OUTPUT_TIME
#define ULOG_OUTPUT_LEVEL
#define ULOG_OUTPUT_TAG
#define ULOG_BACKEND_USING_CONSOLE
#define ULOG_USING_FILTER
#define RT_USING_UTEST
#define UTEST_THR_STACK_SIZE 4096
#define UTEST_THR_PRIORITY 20

/* RT-Thread online packages */

/* IoT - internet of things */

#define PKG_USING_PAHOMQTT
#define PAHOMQTT_PIPE_MODE
#define RT_PKG_MQTT_THREAD_STACK_SIZE 4096
#define PKG_PAHOMQTT_SUBSCRIBE_HANDLERS 4
#define MQTT_DEBUG
#define PKG_USING_PAHOMQTT_LATEST
#define PKG_USING_WEBCLIENT
#define WEBCLIENT_NOT_USE_TLS
#define PKG_USING_WEBCLIENT_LATEST_VERSION

/* Wi-Fi */

/* Marvell WiFi */


/* Wiced WiFi */

#define PKG_USING_NETUTILS
#define PKG_NETUTILS_IPERF
#define PKG_USING_NETUTILS_LATEST_VERSION
#define PKG_USING_AT_DEVICE
#define AT_DEVICE_USING_ESP8266
#define AT_DEVICE_ESP8266_SAMPLE
#define ESP8266_SAMPLE_WIFI_SSID "aptest"
#define ESP8266_SAMPLE_WIFI_PASSWORD "123456789"
#define ESP8266_SAMPLE_CLIENT_NAME "uart3"
#define ESP8266_SAMPLE_RECV_BUFF_LEN 512
#define PKG_USING_AT_DEVICE_LATEST_VERSION
#define PKG_AT_DEVICE_VER_NUM 0x99999

/* IoT Cloud */


/* security packages */


/* language packages */


/* multimedia packages */


/* tools packages */


/* system packages */

#define PKG_USING_FAL
#define FAL_DEBUG_CONFIG
#define FAL_DEBUG 1
#define FAL_PART_HAS_TABLE_CFG
#define PKG_USING_FAL_LATEST_VERSION
#define PKG_FAL_VER_NUM 0x99999

/* peripheral libraries and drivers */


/* miscellaneous packages */


/* samples: kernel and components samples */


/* Privated Packages of RealThread */


/* Network Utilities */

#define RT_USING_TESTCASE

/* cmsis test */

/* ipc */


/* thread */


/* memory */


/* timer */


/* kernel */


/* kernel test */

/* ipc */

#define TC_USING_IPC_SEMAPHORE_TC
#define TC_USING_IPC_MUTEX_TC
#define TC_USING_IPC_MAILBOX_TC

/* kservice test */

#define TC_USING_LIBC_SPRINTF_TC

/* thread */


/* memory */


/* timer */


/* component test */

/* dfs: Device virtual file system */

#define TC_USING_FS_DFS_TC
#define TC_FS_DFS_BLOCK_DEV_NAME "W25Q128"
#define TC_FS_DFS_NAME "elm"
#define TC_FS_DFS_MOUNT_PATH_ "/"
#define TC_USING_FS_POSIX_TC
#define TC_FS_POSIX_BLOCK_DEV_NAME "W25Q128"
#define TC_FS_POSIX_NAME "elm"
#define TC_FS_POSIX_MOUNT_PATH_ "/"
#define TC_USING_MULTIPLE_FS_TC
#define TC_MULTI_FS_BLOCK_DEV_NAME "W25Q128"
#define TC_MULTI_FS_NAME "elm"

/* drivers */

/* i2c */


/* spi */


/* wlan */


/* uart */


/* hwcrypto */


/* sensor */


/* advanced configuration */

#define TC_ACCE_DATA_MAX 8000
#define TC_ACCE_DATA_MIN -8000
#define TC_GYRO_DATA_MAX 2000000
#define TC_GYRO_DATA_MIN -2000000
#define TC_MAG_DATA_MAX 50000
#define TC_MAG_DATA_MIN -50000
#define TC_TEMP_DATA_MAX 1200
#define TC_TEMP_DATA_MIN -500
#define TC_HUMI_DATA_MAX 1000
#define TC_HUMI_DATA_MIN 0
#define TC_BARO_DATA_MAX 200000
#define TC_BARO_DATA_MIN 20000
#define TC_LIGHT_DATA_MAX 50000
#define TC_LIGHT_DATA_MIN -50000
#define TC_PROXIMITY_DATA_MAX 50000
#define TC_PROXIMITY_DATA_MIN -50000
#define TC_HR_DATA_MAX 50000
#define TC_HR_DATA_MIN -50000
#define TC_TVOC_DATA_MAX 1000
#define TC_TVOC_DATA_MIN 0
#define TC_NOISE_DATA_MAX 5000
#define TC_NOISE_DATA_MIN 1
#define TC_STEP_DATA_MAX 50000
#define TC_FORCE_DATA_MAX 50000
#define TC_FORCE_DATA_MIN 0

/* finsh shell */

#define TC_USING_SHELL_TC

/* libc */

#define TC_USING_FS_STDLIB_TC
#define TC_FS_STDLIB_BLOCK_DEV_NAME "W25Q128"
#define TC_FS_STDLIB_NAME "elm"
#define TC_FS_STDLIB_MOUNT_PATH_ "/"
#define TC_USING_POSIX_PTHREAD_TC

/* at */

#define TC_USING_AT_TC
#define TC_AT_CLIENT_UART_NAME "uart3"

/* netdev */

#define TC_USING_NETDEV_TC
#define TC_NETDEV_LWIP_NAME "e0"
#define TC_NETDEV_AT_NAME "esp0"
#define TC_NETDEV_LWIP_MAC_ADDR "00-80-e1-10-41-54"
#define TC_NETDEV_AT_MAC_ADDR "80-7d-3a-4e-0b-e4"
#define TC_NETDEV_TEST_TCP_SERVER_ADDR "192.168.10.104"
#define TC_NETDEV_TEST_SERVER_PORT 12345

/* lwIP */

#define TC_USING_LWIP_TC

/* SAL */

#define TC_USING_SAL_SOCKET_TC
#define SAL_TCP_TEST_SERVER_ADDR "192.168.10.104"
#define SAL_TCP_TEST_SERVER_PORT 1234
#define SAL_UDP_TEST_SERVER_ADDR "192.168.10.104"
#define SAL_UDP_TEST_SERVER_PORT 1236

/* Utilities */

/* utest selftest */

#define TC_USING_UTEST_PASS_TC
#define TC_USING_ULOG_TC

/* packages test */

/* iot */

/* netutils */

#define TC_USING_IPERF_CLIENT_TC
#define TC_IPERF_HOST "192.168.10.104"
#define TC_IPERF_PORT 5001

/* webclient */

#define TC_USING_WEB_CLIENT_TC

/* Paho MQTT */

#define TC_USING_PAHO_MQTT_TC
#define TC_PAHO_MQTT_TEST_SERVER_URI "tcp://iot.rt-thread.com:1883"
#define TC_PAHO_MQTT_TEST_USER_NAME "rtt_bot"
#define TC_PAHO_MQTT_TEST_PASSWORD "79DF59219AB3FFC16EDBF92CD2DD8531"

/* system */

/* fal */

#define TC_USING_FAL_TC
#define TC_USING_FAL_ONCHIP_TC
#define TC_FAL_ONCHIP_FLASH_DEV_NAME "onchip_flash_128k"
#define TC_FAL_ONCHIP_PARTITION_NAME "test"
#define TC_USING_FAL_NORFLASH_TC
#define TC_FAL_NOR_FLASH_DEV_NAME "nor_flash"
#define TC_FAL_NOR_FLASH_PARTITION_NAME "download"

/* realthread-packages test */

#define PKG_USING_TESTCASES_LATEST_VERSION
#define SOC_FAMILY_STM32
#define SOC_SERIES_STM32F4

/* Hardware Drivers Config */

#define SOC_STM32F407ZG

/* Onboard Peripheral Drivers */

#define BSP_USING_USB_TO_USART
#define BSP_USING_COM3
#define BSP_USING_SPI_FLASH
#define PHY_USING_LAN8720A
#define BSP_USING_ETH

/* On-chip Peripheral Drivers */

#define BSP_USING_GPIO
#define BSP_USING_UART
#define BSP_USING_UART1
#define BSP_USING_UART3
#define BSP_USING_ON_CHIP_FLASH
#define BSP_USING_SPI
#define BSP_USING_SPI1

/* Board extended module Drivers */


#endif
