#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

/* RT-Thread Kernel */

#define RT_NAME_MAX 32
#define RT_ALIGN_SIZE 4
/* RT_THREAD_PRIORITY_8 is not set */
/* RT_THREAD_PRIORITY_32 is not set */
#define RT_THREAD_PRIORITY_256
#define RT_THREAD_PRIORITY_MAX 256
#define RT_TICK_PER_SECOND 100
#define RT_DEBUG
#define RT_DEBUG_COLOR
#define RT_USING_OVERFLOW_CHECK
#define RT_DEBUG_INIT 0
#define RT_DEBUG_THREAD 0
#define RT_USING_HOOK
#define IDLE_THREAD_STACK_SIZE 1024
#define RT_USING_TIMER_SOFT
#define RT_TIMER_THREAD_PRIO 4
#define RT_TIMER_THREAD_STACK_SIZE 10240

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE
/* RT_USING_SIGNALS is not set */

/* Memory Management */

/* RT_USING_MEMPOOL is not set */
#define RT_USING_MEMHEAP
/* RT_USING_NOHEAP is not set */
#define RT_USING_SMALL_MEM
/* RT_USING_SLAB is not set */
/* RT_USING_MEMHEAP_AS_HEAP is not set */
/* RT_USING_MEMTRACE is not set */
#define RT_USING_HEAP

/* Kernel Device Object */

#define RT_USING_DEVICE
#define RT_USING_INTERRUPT_INFO
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart0"
/* RT_USING_MODULE is not set */

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 16384

/* C++ features */

#define RT_USING_CPLUSPLUS

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
/* FINSH_USING_MSH_ONLY is not set */

/* Device virtual file system */

#define RT_USING_DFS
#define DFS_USING_WORKDIR
#define DFS_FILESYSTEMS_MAX 9
#define DFS_FILESYSTEM_TYPES_MAX 9
#define DFS_FD_MAX 16
#define RT_USING_DFS_ELMFAT

/* elm-chan's FatFs, Generic FAT Filesystem Module */

#define RT_DFS_ELM_CODE_PAGE 437
#define RT_DFS_ELM_WORD_ACCESS
#define RT_DFS_ELM_USE_LFN_0
/* RT_DFS_ELM_USE_LFN_1 is not set */
/* RT_DFS_ELM_USE_LFN_2 is not set */
/* RT_DFS_ELM_USE_LFN_3 is not set */
#define RT_DFS_ELM_USE_LFN 0
#define RT_DFS_ELM_MAX_LFN 255
#define RT_DFS_ELM_DRIVES 2
#define RT_DFS_ELM_MAX_SECTOR_SIZE 4096
/* RT_DFS_ELM_USE_ERASE is not set */
#define RT_DFS_ELM_REENTRANT
#define RT_USING_DFS_DEVFS
/* RT_USING_DFS_NET is not set */
/* RT_USING_DFS_ROMFS is not set */
/* RT_USING_DFS_RAMFS is not set */
/* RT_USING_DFS_UFFS is not set */
#define RT_USING_DFS_JFFS2
#define RT_USING_DFS_NFS
#define RT_NFS_HOST_EXPORT "192.168.10.82:/"

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_USING_SERIAL
#define RT_SERIAL_USING_DMA
/* RT_USING_CAN is not set */
/* RT_USING_HWTIMER is not set */
/* RT_USING_CPUTIME is not set */
#define RT_USING_I2C
#define RT_USING_I2C_BITOPS
#define RT_USING_PIN
#define RT_USING_MTD_NOR
/* RT_USING_MTD_NAND is not set */
/* RT_USING_RTC is not set */
#define RT_USING_SDIO
#define RT_USING_SPI
/* RT_USING_SPI_MSD is not set */
/* RT_USING_SFUD is not set */
/* RT_USING_W25QXX is not set */
/* RT_USING_GD is not set */
/* RT_USING_ENC28J60 is not set */
/* RT_USING_SPI_WIFI is not set */
#define RT_USING_WDT
/* RT_USING_WIFI is not set */

/* Using USB */

/* RT_USING_USB_HOST is not set */
/* RT_USING_USB_DEVICE is not set */

/* POSIX layer and C standard library */

#define RT_USING_LIBC
#define RT_USING_PTHREADS
/* RT_USING_POSIX is not set */

/* Network stack */

/* light weight TCP/IP stack */

#define RT_USING_LWIP
/* RT_USING_LWIP141 is not set */
#define RT_USING_LWIP202
/* RT_USING_LWIP_IPV6 is not set */
#define RT_LWIP_IGMP
#define RT_LWIP_ICMP
/* RT_LWIP_SNMP is not set */
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
/* RT_LWIP_RAW is not set */
/* RT_LWIP_PPP is not set */
#define RT_MEMP_NUM_NETCONN 64
#define RT_LWIP_PBUF_NUM 16
#define RT_LWIP_RAW_PCB_NUM 10
#define RT_LWIP_UDP_PCB_NUM 64
#define RT_LWIP_TCP_PCB_NUM 8
#define RT_LWIP_TCP_SEG_NUM 256
#define RT_LWIP_TCP_SND_BUF 12040
#define RT_LWIP_TCP_WND 11680
#define RT_LWIP_TCPTHREAD_PRIORITY 100
#define RT_LWIP_TCPTHREAD_MBOX_SIZE 32
#define RT_LWIP_TCPTHREAD_STACKSIZE 32768
#define RT_LWIP_ETHTHREAD_PRIORITY 126
#define RT_LWIP_ETHTHREAD_STACKSIZE 1024
#define RT_LWIP_ETHTHREAD_MBOX_SIZE 32
#define RT_LWIP_REASSEMBLY_FRAG
#define LWIP_NETIF_STATUS_CALLBACK 1
#define SO_REUSE 1
#define LWIP_SO_RCVTIMEO 1
#define LWIP_SO_SNDTIMEO 1
#define LWIP_SO_RCVBUF 1
/* RT_LWIP_NETIF_LOOPBACK is not set */
#define LWIP_NETIF_LOOPBACK 0

/* Modbus master and slave stack */

/* RT_USING_MODBUS is not set */
#define LWIP_USING_DHCPD
/* RT_USING_NETUTILS is not set */

/* RT-Thread UI Engine */

/* RT_USING_GUIENGINE is not set */

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

/* Privated Packages of RealThread */

/* PKG_USING_CODEC is not set */
/* PKG_USING_PLAYER is not set */
/* PKG_USING_PERSIMMON_SRC is not set */

/* Network Utilities */

/* PKG_USING_MDNS is not set */
/* PKG_USING_UPNP is not set */
/* PKG_USING_WLAN_WICED_SRC is not set */

/* Cloudsdk: RT_thread IOT Cloudsdk */

/* PKG_USING_CLOUDSDK is not set */

/* Webnet: A web server package for rt-thread */

/* PKG_USING_WEBNET is not set */
/* PKG_USING_COREMARK is not set */
/* PKG_USING_POWER_MANAGER is not set */
/* SOC_GK7101 is not set */
/* SOC_GK7102 is not set */
/* SOC_GK7101S is not set */
/* SOC_GK7102S is not set */
#define SOC_GK7102C
#define BOARD_GK7102C_EVB
#define SENSOR_TYPE_SC1135
/* SENSOR_TYPE_SC1145 is not set */
/* SENSOR_TYPE_JXH65 is not set */
/* SENSOR_TYPE_OV9750 is not set */
/* SENSOR_TYPE_AR0130 is not set */
/* SENSOR_TYPE_JXH42 is not set */
#define TUNNING_TOOL_SUPPORT
#define RT_USING_DMA_MEM
#define ARM1176_USE_VFP
#define RT_USING_VFP
#define RT_USING_CPU_FFS

/* Goke Peripheral Device Config */

#define RT_USING_ADC
#define RT_USING_GMAC
#define RT_USING_PWM
#define RT_USING_GK_DMA
#define RT_USING_LIBZ
#define RT_USING_LOGCAPTURE
#define RT_ALIGN_UC_SIZE 8
#define RT_ALIGN_DSP_SIZE 32
#define RT_DEBUG_UC_MEM 0
#define RT_DEBUG_DSP_MEM 0

#endif
