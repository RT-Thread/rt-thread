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
/* RT_USING_PIN is not set */
/* RT_USING_MTD_NOR is not set */
#define RT_USING_MTD_NAND
#define RT_USING_RTC
/* RT_USING_SDIO is not set */
#define RT_USING_SPI
#define RT_USING_SFUD
#define RT_SFUD_USING_SFDP
/* RT_SFUD_USING_FLASH_INFO_TABLE is not set */
/* RT_SFUD_DEBUG is not set */
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

#define RT_USING_LWIP
#define RT_USING_LWIP141
/* RT_USING_LWIP200 is not set */
/* RT_USING_LWIP202 is not set */
/* RT_LWIP_IGMP is not set */
#define RT_LWIP_ICMP
/* RT_LWIP_SNMP is not set */
#define RT_LWIP_DNS
#define RT_LWIP_DHCP
#define IP_SOF_BROADCAST 1
#define IP_SOF_BROADCAST_RECV 1
/* LWIP_USING_DHCPD is not set */
#define RT_LWIP_UDP
#define RT_LWIP_TCP
/* RT_LWIP_PPP is not set */
/* RT_LWIP_PPPOE is not set */
/* RT_LWIP_PPPOS is not set */
#define RT_LWIP_PBUF_NUM 16
#define RT_LWIP_RAW_PCB_NUM 4
#define RT_LWIP_UDP_PCB_NUM 4
#define RT_LWIP_TCP_PCB_NUM 5
#define RT_LWIP_TCP_SEG_NUM 40
#define RT_LWIP_TCP_SND_BUF 8192
#define RT_LWIP_TCP_WND 8192
#define RT_LWIP_TCPTHREAD_PRIORITY 12
#define RT_LWIP_TCPTHREAD_MBOX_SIZE 4
#define RT_LWIP_TCPTHREAD_STACKSIZE 1024
#define RT_LWIP_ETHTHREAD_PRIORITY 15
#define RT_LWIP_ETHTHREAD_STACKSIZE 512
#define RT_LWIP_ETHTHREAD_MBOX_SIZE 4
/* RT_LWIP_REASSEMBLY_FRAG is not set */
#define LWIP_NETIF_STATUS_CALLBACK 1
#define SO_REUSE 1
#define LWIP_SO_RCVTIMEO 1
#define LWIP_SO_SNDTIMEO 1
#define LWIP_SO_RCVBUF 1

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

/* RT_GUI CONFIG */

#define RT_USING_GUIENGINE
#define RTGUI_NAME_MAX 16
#define RTGUI_USING_FONT16
#define RTGUI_USING_FONT12
#define RTGUI_USING_FONTHZ
#define RTGUI_USING_DFS_FILERW
#define RTGUI_USING_HZ_BMP

/* BSP_UASRT CONFIG */

#define RT_RTC_NAME "rtc"
#define RT_USING_EXT_SDRAM
#define RT_USING_I2C_BITOPS
#define RT_USING_UART1
#define RT_USING_UART2
#define RT_USING_UART3

/* BSP_LWIP CONFIG */

#define RT_LWIP_IPADDR0 192
#define RT_LWIP_IPADDR1 168
#define RT_LWIP_IPADDR2 1
#define RT_LWIP_IPADDR3 201
#define RT_LWIP_GWADDR0 192
#define RT_LWIP_GWADDR1 168
#define RT_LWIP_GWADDR2 1
#define RT_LWIP_GWADDR3 1
#define RT_LWIP_MSKADDR0 255
#define RT_LWIP_MSKADDR1 255
#define RT_LWIP_MSKADDR2 255
#define RT_LWIP_MSKADDR3 0
#define CHECKSUM_CHECK_TCP 0
#define CHECKSUM_CHECK_IP 0
#define CHECKSUM_CHECK_UDP 0

/* BSP_SPECIAL CONFIG */

#define IDLE_THREAD_STACK_SIZE 1024
#define RT_DFS_ELM_WORD_ACCESS
#define RT_USING_SPI5
#define RT_USING_DFS_UFFS
#define RT_MTD_NAND_DEBUG
#define RT_LWIP_USING_RT_MEM
#define DFS_FILESYSTEM_TYPES_MAX 4
#define RT_DFS_ELM_USE_LFN 3

#endif
