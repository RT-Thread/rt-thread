#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* RT-Thread Kernel */

#define RT_NAME_MAX 16
#define RT_CPUS_NR 1
#define RT_ALIGN_SIZE 8
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 1000
#define RT_USING_HOOK
#define RT_HOOK_USING_FUNC_PTR
#define RT_USING_IDLE_HOOK
#define RT_IDLE_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 2048

/* kservice optimization */

/* end of kservice optimization */

/* klibc optimization */

/* end of klibc optimization */
#define RT_USING_DEBUG
#define RT_DEBUGING_ASSERT
#define RT_DEBUGING_COLOR
#define RT_DEBUGING_CONTEXT
#define RT_USING_OVERFLOW_CHECK

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE
#define RT_USING_SIGNALS
/* end of Inter-Thread communication */

/* Memory Management */

#define RT_PAGE_MAX_ORDER 11
#define RT_USING_MEMPOOL
#define RT_USING_SMALL_MEM
#define RT_USING_MEMHEAP
#define RT_MEMHEAP_FAST_MODE
#define RT_USING_SMALL_MEM_AS_HEAP
#define RT_USING_MEMTRACE
#define RT_USING_HEAP
/* end of Memory Management */
#define RT_USING_DEVICE
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 256
#define RT_CONSOLE_DEVICE_NAME "uart0"
#define RT_VER_NUM 0x50200
#define RT_BACKTRACE_LEVEL_MAX_NR 32
/* end of RT-Thread Kernel */
#define RT_USING_CACHE
#define ARCH_MM_MMU
#define ARCH_ARM
#define ARCH_ARM_MMU
#define ARCH_ARM_ARM9

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 2048
#define RT_MAIN_THREAD_PRIORITY 20
#define RT_USING_MSH
#define RT_USING_FINSH
#define FINSH_USING_MSH
#define FINSH_THREAD_NAME "tshell"
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 4096
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB
#define FINSH_CMD_SIZE 80
#define MSH_USING_BUILT_IN_COMMANDS
#define FINSH_USING_DESCRIPTION
#define FINSH_ARG_MAX 10
#define FINSH_USING_OPTION_COMPLETION

/* DFS: device virtual file system */

#define RT_USING_DFS
#define DFS_USING_POSIX
#define DFS_USING_WORKDIR
#define RT_USING_DFS_MNTTABLE
#define DFS_FD_MAX 64
#define RT_USING_DFS_V1
#define DFS_FILESYSTEMS_MAX 16
#define DFS_FILESYSTEM_TYPES_MAX 16
#define RT_USING_DFS_ELMFAT

/* elm-chan's FatFs, Generic FAT Filesystem Module */

#define RT_DFS_ELM_CODE_PAGE 437
#define RT_DFS_ELM_WORD_ACCESS
#define RT_DFS_ELM_USE_LFN_3
#define RT_DFS_ELM_USE_LFN 3
#define RT_DFS_ELM_LFN_UNICODE_0
#define RT_DFS_ELM_LFN_UNICODE 0
#define RT_DFS_ELM_MAX_LFN 255
#define RT_DFS_ELM_DRIVES 8
#define RT_DFS_ELM_MAX_SECTOR_SIZE 4096
#define RT_DFS_ELM_REENTRANT
#define RT_DFS_ELM_MUTEX_TIMEOUT 3000
/* end of elm-chan's FatFs, Generic FAT Filesystem Module */
#define RT_USING_DFS_DEVFS
/* end of DFS: device virtual file system */

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_UNAMED_PIPE_NUMBER 64
#define RT_USING_SYSTEM_WORKQUEUE
#define RT_SYSTEM_WORKQUEUE_STACKSIZE 2048
#define RT_SYSTEM_WORKQUEUE_PRIORITY 23
#define RT_USING_SERIAL
#define RT_USING_SERIAL_V1
#define RT_SERIAL_USING_DMA
#define RT_SERIAL_RB_BUFSZ 2048
#define RT_USING_CAN
#define RT_CAN_USING_HDR
#define RT_USING_CPUTIME
#define CPUTIME_TIMER_FREQ 0
#define RT_USING_I2C
#define RT_USING_I2C_BITOPS
#define RT_USING_ADC
#define RT_USING_PWM
#define RT_USING_MTD_NAND
#define RT_MTD_NAND_DEBUG
#define RT_USING_RTC
#define RT_USING_ALARM
#define RT_USING_SPI
#define RT_USING_QSPI
#define RT_USING_WDT
#define RT_USING_AUDIO
#define RT_AUDIO_REPLAY_MP_BLOCK_SIZE 4096
#define RT_AUDIO_REPLAY_MP_BLOCK_COUNT 2
#define RT_AUDIO_RECORD_PIPE_SIZE 2048
#define RT_USING_HWCRYPTO
#define RT_HWCRYPTO_DEFAULT_NAME "hwcryto"
#define RT_HWCRYPTO_IV_MAX_SIZE 16
#define RT_HWCRYPTO_KEYBIT_MAX_SIZE 256
#define RT_HWCRYPTO_USING_AES
#define RT_HWCRYPTO_USING_AES_ECB
#define RT_HWCRYPTO_USING_AES_CBC
#define RT_HWCRYPTO_USING_AES_CFB
#define RT_HWCRYPTO_USING_AES_CTR
#define RT_HWCRYPTO_USING_AES_OFB
#define RT_HWCRYPTO_USING_SHA1
#define RT_HWCRYPTO_USING_SHA2
#define RT_HWCRYPTO_USING_SHA2_224
#define RT_HWCRYPTO_USING_SHA2_256
#define RT_HWCRYPTO_USING_SHA2_384
#define RT_HWCRYPTO_USING_SHA2_512
#define RT_HWCRYPTO_USING_RNG
#define RT_USING_PIN
#define RT_USING_HWTIMER
/* end of Device Drivers */

/* C/C++ and POSIX layer */

/* ISO-ANSI C layer */

/* Timezone and Daylight Saving Time */

#define RT_LIBC_USING_LIGHT_TZ_DST
#define RT_LIBC_TZ_DEFAULT_HOUR 8
#define RT_LIBC_TZ_DEFAULT_MIN 0
#define RT_LIBC_TZ_DEFAULT_SEC 0
/* end of Timezone and Daylight Saving Time */
/* end of ISO-ANSI C layer */

/* POSIX (Portable Operating System Interface) layer */

#define RT_USING_POSIX_FS
#define RT_USING_POSIX_POLL
#define RT_USING_POSIX_SELECT
#define RT_USING_POSIX_SOCKET

/* Interprocess Communication (IPC) */


/* Socket is in the 'Network' category */

/* end of Interprocess Communication (IPC) */
/* end of POSIX (Portable Operating System Interface) layer */
/* end of C/C++ and POSIX layer */

/* Network */

#define RT_USING_SAL

/* Docking with protocol stacks */

#define SAL_USING_LWIP
/* end of Docking with protocol stacks */
#define SAL_USING_POSIX
#define RT_USING_NETDEV
#define NETDEV_USING_IFCONFIG
#define NETDEV_USING_PING
#define NETDEV_USING_NETSTAT
#define NETDEV_USING_AUTO_DEFAULT
#define NETDEV_IPV4 1
#define NETDEV_IPV6 0
#define RT_USING_LWIP
#define RT_USING_LWIP212
#define RT_USING_LWIP_VER_NUM 0x20102
#define RT_LWIP_MEM_ALIGNMENT 4
#define RT_LWIP_IGMP
#define RT_LWIP_ICMP
#define RT_LWIP_DNS
#define RT_LWIP_DHCP
#define IP_SOF_BROADCAST 1
#define IP_SOF_BROADCAST_RECV 1

/* Static IPv4 Address */

#define RT_LWIP_IPADDR "192.168.31.55"
#define RT_LWIP_GWADDR "192.168.31.1"
#define RT_LWIP_MSKADDR "255.255.255.0"
/* end of Static IPv4 Address */
#define RT_LWIP_UDP
#define RT_LWIP_TCP
#define RT_LWIP_RAW
#define RT_MEMP_NUM_NETCONN 16
#define RT_LWIP_PBUF_NUM 256
#define RT_LWIP_RAW_PCB_NUM 16
#define RT_LWIP_UDP_PCB_NUM 16
#define RT_LWIP_TCP_PCB_NUM 16
#define RT_LWIP_TCP_SEG_NUM 64
#define RT_LWIP_TCP_SND_BUF 16384
#define RT_LWIP_TCP_WND 65535
#define RT_LWIP_TCPTHREAD_PRIORITY 21
#define RT_LWIP_TCPTHREAD_MBOX_SIZE 256
#define RT_LWIP_TCPTHREAD_STACKSIZE 4096
#define LWIP_NO_TX_THREAD
#define RT_LWIP_ETHTHREAD_PRIORITY 22
#define RT_LWIP_ETHTHREAD_STACKSIZE 4096
#define RT_LWIP_ETHTHREAD_MBOX_SIZE 256
#define RT_LWIP_REASSEMBLY_FRAG
#define LWIP_NETIF_STATUS_CALLBACK 1
#define LWIP_NETIF_LINK_CALLBACK 1
#define RT_LWIP_NETIF_NAMESIZE 6
#define SO_REUSE 1
#define LWIP_SO_RCVTIMEO 1
#define LWIP_SO_SNDTIMEO 1
#define LWIP_SO_RCVBUF 1
#define LWIP_SO_LINGER 1
#define RT_LWIP_NETIF_LOOPBACK
#define LWIP_NETIF_LOOPBACK 1
#define RT_LWIP_STATS
#define RT_LWIP_USING_PING
/* end of Network */

/* Memory protection */

/* end of Memory protection */

/* Utilities */

#define RT_USING_UTEST
#define UTEST_THR_STACK_SIZE 4096
#define UTEST_THR_PRIORITY 20
#define RT_USING_ADT
#define RT_USING_ADT_AVL
#define RT_USING_ADT_BITMAP
#define RT_USING_ADT_HASHMAP
#define RT_USING_ADT_REF
/* end of Utilities */

/* Using USB legacy version */

#define RT_USING_USB
#define RT_USING_USB_HOST
#define RT_USBH_MSTORAGE
#define UDISK_MOUNTPOINT "/mnt/udisk"
#define RT_USING_USB_DEVICE
#define RT_USBD_THREAD_STACK_SZ 4096
#define USB_VENDOR_ID 0x0FFE
#define USB_PRODUCT_ID 0x0001
#define RT_USB_DEVICE_COMPOSITE
#define RT_USB_DEVICE_CDC
#define RT_USB_DEVICE_NONE
#define RT_USB_DEVICE_MSTORAGE
#define RT_VCOM_TASK_STK_SIZE 2048
#define RT_CDC_RX_BUFSIZE 128
#define RT_VCOM_SERNO "32021919830108"
#define RT_VCOM_SER_LEN 14
#define RT_VCOM_TX_TIMEOUT 1000
#define RT_USB_MSTORAGE_DISK_NAME "ramdisk1"
/* end of Using USB legacy version */
/* end of RT-Thread Components */

/* RT-Thread Utestcases */

/* end of RT-Thread Utestcases */

/* RT-Thread online packages */

/* IoT - internet of things */


/* Wi-Fi */

/* Marvell WiFi */

/* end of Marvell WiFi */

/* Wiced WiFi */

/* end of Wiced WiFi */

/* CYW43012 WiFi */

/* end of CYW43012 WiFi */

/* BL808 WiFi */

/* end of BL808 WiFi */

/* CYW43439 WiFi */

/* end of CYW43439 WiFi */
/* end of Wi-Fi */

/* IoT Cloud */

/* end of IoT Cloud */
/* end of IoT - internet of things */

/* security packages */

/* end of security packages */

/* language packages */

/* JSON: JavaScript Object Notation, a lightweight data-interchange format */

/* end of JSON: JavaScript Object Notation, a lightweight data-interchange format */

/* XML: Extensible Markup Language */

/* end of XML: Extensible Markup Language */
/* end of language packages */

/* multimedia packages */

/* LVGL: powerful and easy-to-use embedded GUI library */

/* end of LVGL: powerful and easy-to-use embedded GUI library */

/* u8g2: a monochrome graphic library */

/* end of u8g2: a monochrome graphic library */
/* end of multimedia packages */

/* tools packages */

/* end of tools packages */

/* system packages */

/* enhanced kernel services */

/* end of enhanced kernel services */

/* acceleration: Assembly language or algorithmic acceleration packages */

/* end of acceleration: Assembly language or algorithmic acceleration packages */

/* CMSIS: ARM Cortex-M Microcontroller Software Interface Standard */

/* end of CMSIS: ARM Cortex-M Microcontroller Software Interface Standard */

/* Micrium: Micrium software products porting for RT-Thread */

/* end of Micrium: Micrium software products porting for RT-Thread */
/* end of system packages */

/* peripheral libraries and drivers */

/* HAL & SDK Drivers */

/* STM32 HAL & SDK Drivers */

/* end of STM32 HAL & SDK Drivers */

/* Infineon HAL Packages */

/* end of Infineon HAL Packages */

/* Kendryte SDK */

/* end of Kendryte SDK */
/* end of HAL & SDK Drivers */

/* sensors drivers */

/* end of sensors drivers */

/* touch drivers */

/* end of touch drivers */
/* end of peripheral libraries and drivers */

/* AI packages */

/* end of AI packages */

/* Signal Processing and Control Algorithm Packages */

/* end of Signal Processing and Control Algorithm Packages */

/* miscellaneous packages */

/* project laboratory */

/* end of project laboratory */

/* samples: kernel and components samples */

/* end of samples: kernel and components samples */

/* entertainment: terminal games and other interesting software packages */

/* end of entertainment: terminal games and other interesting software packages */
/* end of miscellaneous packages */

/* Arduino libraries */


/* Projects and Demos */

/* end of Projects and Demos */

/* Sensors */

/* end of Sensors */

/* Display */

/* end of Display */

/* Timing */

/* end of Timing */

/* Data Processing */

/* end of Data Processing */

/* Data Storage */

/* Communication */

/* end of Communication */

/* Device Control */

/* end of Device Control */

/* Other */

/* end of Other */

/* Signal IO */

/* end of Signal IO */

/* Uncategorized */

/* end of Arduino libraries */
/* end of RT-Thread online packages */

/* Hardware Drivers Config */

/* On-chip Peripheral Drivers */

#define SOC_SERIES_NUC980
#define BSP_USE_STDDRIVER_SOURCE
#define BSP_USING_MMU
#define BSP_USING_PDMA
#define NU_PDMA_MEMFUN_ACTOR_MAX 2
#define BSP_USING_GPIO
#define BSP_USING_EMAC
#define BSP_USING_EMAC0
#define BSP_USING_RTC
#define NU_RTC_SUPPORT_IO_RW
#define NU_RTC_SUPPORT_MSH_CMD
#define BSP_USING_ADC
#define BSP_USING_TMR
#define BSP_USING_TIMER
#define BSP_USING_TMR0
#define BSP_USING_TIMER0
#define BSP_USING_TMR1
#define BSP_USING_TIMER1
#define BSP_USING_TMR2
#define BSP_USING_TIMER2
#define BSP_USING_TMR3
#define BSP_USING_TIMER3
#define BSP_USING_TMR4
#define BSP_USING_TIMER4
#define BSP_USING_UART
#define BSP_USING_UART0
#define BSP_USING_UART1
#define BSP_USING_UART1_TX_DMA
#define BSP_USING_UART1_RX_DMA
#define BSP_USING_I2C
#define BSP_USING_I2C0
#define BSP_USING_I2C2
#define BSP_USING_SDH
#define BSP_USING_SDH1
#define NU_SDH_USING_PDMA
#define NU_SDH_HOTPLUG
#define BSP_USING_PWM
#define BSP_USING_PWM0
#define BSP_USING_SPI
#define BSP_USING_SPI_PDMA
#define BSP_USING_SPI0
#define BSP_USING_SPI0_PDMA
#define BSP_USING_SPI1_NONE
#define BSP_USING_I2S
#define NU_I2S_DMA_FIFO_SIZE 4096
#define BSP_USING_QSPI
#define BSP_USING_QSPI_PDMA
#define BSP_USING_QSPI0
#define BSP_USING_QSPI0_PDMA
#define BSP_USING_CRYPTO
#define BSP_USING_WDT
#define BSP_USING_USBD
#define BSP_USING_USBH
/* end of On-chip Peripheral Drivers */

/* On-board Peripheral Drivers */

#define BSP_USING_CONSOLE
#define BOARD_USING_IP101GR
#define BOARD_USING_NAU8822
#define BOARD_USING_STORAGE_SDCARD
#define BOARD_USING_STORAGE_SPINAND
#define BOARD_USING_USB0_DEVICE_HOST
#define BOARD_USING_USB1_HOST
/* end of On-board Peripheral Drivers */

/* Board extended module drivers */

/* end of Board extended module drivers */

/* Nuvoton Packages Config */

#define NU_PKG_USING_UTILS
#define NU_PKG_USING_DEMO
#define NU_PKG_USING_NAU8822
#define NU_PKG_USING_SPINAND
/* end of Nuvoton Packages Config */
/* end of Hardware Drivers Config */

#endif
