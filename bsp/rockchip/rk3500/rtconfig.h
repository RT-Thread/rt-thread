#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* RT-Thread Kernel */

/* klibc options */

/* rt_vsnprintf options */

#define RT_KLIBC_USING_VSNPRINTF_LONGLONG
#define RT_KLIBC_USING_VSNPRINTF_STANDARD
#define RT_KLIBC_USING_VSNPRINTF_DECIMAL_SPECIFIERS
#define RT_KLIBC_USING_VSNPRINTF_EXPONENTIAL_SPECIFIERS
#define RT_KLIBC_USING_VSNPRINTF_WRITEBACK_SPECIFIER
#define RT_KLIBC_USING_VSNPRINTF_CHECK_NUL_IN_FORMAT_SPECIFIER
#define RT_KLIBC_USING_VSNPRINTF_INTEGER_BUFFER_SIZE 32
#define RT_KLIBC_USING_VSNPRINTF_DECIMAL_BUFFER_SIZE 32
#define RT_KLIBC_USING_VSNPRINTF_FLOAT_PRECISION 6
#define RT_KLIBC_USING_VSNPRINTF_MAX_INTEGRAL_DIGITS_FOR_DECIMAL 9
#define RT_KLIBC_USING_VSNPRINTF_LOG10_TAYLOR_TERMS 4
/* end of rt_vsnprintf options */

/* rt_vsscanf options */

/* end of rt_vsscanf options */

/* rt_memset options */

/* end of rt_memset options */

/* rt_memcpy options */

/* end of rt_memcpy options */

/* rt_memmove options */

/* end of rt_memmove options */

/* rt_memcmp options */

/* end of rt_memcmp options */

/* rt_strstr options */

/* end of rt_strstr options */

/* rt_strcasecmp options */

/* end of rt_strcasecmp options */

/* rt_strncpy options */

/* end of rt_strncpy options */

/* rt_strcpy options */

/* end of rt_strcpy options */

/* rt_strncmp options */

/* end of rt_strncmp options */

/* rt_strcmp options */

/* end of rt_strcmp options */

/* rt_strlen options */

/* end of rt_strlen options */

/* rt_strnlen options */

/* end of rt_strnlen options */
/* end of klibc options */
#define RT_NAME_MAX 24
#define RT_USING_SMART
#define RT_USING_SMP
#define RT_CPUS_NR 4
#define RT_ALIGN_SIZE 8
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 1000
#define RT_USING_HOOK
#define RT_HOOK_USING_FUNC_PTR
#define RT_USING_HOOKLIST
#define RT_USING_IDLE_HOOK
#define RT_IDLE_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 16384
#define SYSTEM_THREAD_STACK_SIZE 16384
#define RT_USING_TIMER_SOFT
#define RT_TIMER_THREAD_PRIO 4
#define RT_TIMER_THREAD_STACK_SIZE 32768
#define RT_USING_TIMER_ALL_SOFT
#define RT_USING_CPU_USAGE_TRACER

/* kservice options */

/* end of kservice options */
#define RT_USING_DEBUG
#define RT_DEBUGING_COLOR

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE
#define RT_USING_MESSAGEQUEUE_PRIORITY
/* end of Inter-Thread communication */

/* Memory Management */

#define RT_USING_SLAB
#define RT_USING_MEMHEAP
#define RT_MEMHEAP_FAST_MODE
#define RT_USING_MEMHEAP_AS_HEAP
#define RT_USING_MEMHEAP_AUTO_BINDING
#define RT_USING_HEAP
/* end of Memory Management */
#define RT_USING_DEVICE
#define RT_USING_DEVICE_OPS
#define RT_USING_THREADSAFE_PRINTF
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 1024
#define RT_CONSOLE_DEVICE_NAME "uart2"
#define RT_VER_NUM 0x50300
#define RT_USING_STDC_ATOMIC
#define RT_BACKTRACE_LEVEL_MAX_NR 32
/* end of RT-Thread Kernel */

/* AArch64 Architecture Configuration */

#define ARCH_TEXT_OFFSET 0x00480000
#define ARCH_RAM_OFFSET 0x200000
#define ARCH_SECONDARY_CPU_STACK_SIZE 16384
#define ARCH_HAVE_EFFICIENT_UNALIGNED_ACCESS
#define ARCH_USING_GENERIC_CPUID
#define ARCH_HEAP_SIZE 0x4000000
#define ARCH_INIT_PAGE_SIZE 0x200000
/* end of AArch64 Architecture Configuration */
#define ARCH_CPU_64BIT
#define RT_USING_CACHE
#define RT_USING_CPU_FFS
#define ARCH_MM_MMU
#define ARCH_ARM
#define ARCH_ARM_MMU
#define KERNEL_VADDR_START 0xffff000000000000
#define ARCH_ARMV8
#define ARCH_USING_ASID
#define ARCH_USING_HW_THREAD_SELF
#define ARCH_USING_IRQ_CTX_LIST

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 16384
#define RT_MAIN_THREAD_PRIORITY 10
#define RT_USING_MSH
#define RT_USING_FINSH
#define FINSH_USING_MSH
#define FINSH_THREAD_NAME "tshell"
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 16384
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
#define DFS_FD_MAX 512
#define RT_USING_DFS_V2
#define RT_USING_DFS_DEVFS
#define RT_USING_DFS_PTYFS
#define RT_USING_DFS_PROCFS
#define RT_USING_DFS_TMPFS
#define RT_USING_DFS_MQUEUE
#define RT_USING_PAGECACHE

/* page cache config */

#define RT_PAGECACHE_COUNT 128
#define RT_PAGECACHE_ASPACE_COUNT 32
#define RT_PAGECACHE_PRELOAD 4
#define RT_PAGECACHE_HASH_NR 180
#define RT_PAGECACHE_GC_WORK_LEVEL 90
#define RT_PAGECACHE_GC_STOP_LEVEL 70
/* end of page cache config */
/* end of DFS: device virtual file system */

/* Device Drivers */

#define RT_USING_DM
#define RT_USING_DEV_BUS
#define RT_USING_DEVICE_IPC
#define RT_UNAMED_PIPE_NUMBER 64
#define RT_USING_SYSTEM_WORKQUEUE
#define RT_SYSTEM_WORKQUEUE_STACKSIZE 16384
#define RT_SYSTEM_WORKQUEUE_PRIORITY 23
#define RT_USING_SERIAL
#define RT_USING_SERIAL_V1
#define RT_SERIAL_RB_BUFSZ 64
#define RT_USING_SERIAL_BYPASS
#define RT_SERIAL_8250
#define RT_SERIAL_8250_DW
#define RT_USING_CAN
#define RT_CAN_USING_CANFD
#define RT_CANMSG_BOX_SZ 16
#define RT_CANSND_BOX_NUM 1
#define RT_CANSND_MSG_TIMEOUT 100
#define RT_CAN_NB_TX_FIFO_SIZE 256
#define RT_CAN_CANFD_ROCKCHIP
#define RT_USING_CLOCK_TIME
#define RT_CLOCK_TIME_ARM_ARCH
#define RT_CLOCK_TIMER_ROCKCHIP
#define RT_USING_I2C
#define RT_USING_I2C_BITOPS
#define RT_I2C_RK3X
#define RT_USING_ADC
#define RT_ADC_ROCKCHIP_SARADC
#define RT_USING_NULL
#define RT_USING_ZERO
#define RT_USING_RANDOM
#define RT_USING_PWM
#define RT_PWM_ROCKCHIP
#define RT_USING_MTD_NOR
#define RT_USING_MTD_NOR_SPI
#define RT_USING_RTC
#define RT_USING_ALARM
#define RT_ALARM_STACK_SIZE 16384
#define RT_ALARM_TIMESLICE 5
#define RT_ALARM_PRIORITY 10
#define RT_USING_SOFT_RTC
#define RT_RTC_HYM8563
#define RT_RTC_PCF8523
#define RT_RTC_PCF8563
#define RT_RTC_RX8010
#define RT_RTC_RK8XX
#define RT_USING_SDIO
#define RT_SDIO_STACK_SIZE 16384
#define RT_SDIO_THREAD_PRIORITY 15
#define RT_MMCSD_STACK_SIZE 16384
#define RT_MMCSD_THREAD_PRIORITY 22
#define RT_MMCSD_MAX_PARTITION 16
#define RT_SDIO_DW_MMC
#define RT_SDIO_DW_MMC_ROCKCHIP
#define RT_USING_SPI
#define RT_USING_SPI_ISR
#define RT_USING_QSPI
#define RT_USING_SFUD
#define RT_SFUD_USING_SFDP
#define RT_SFUD_USING_FLASH_INFO_TABLE
#define RT_SFUD_SPI_MAX_HZ 50000000
#define RT_SPI_ROCKCHIP
#define RT_USING_WDT
#define RT_WDT_DW
#define RT_WDT_RK8XX
#define RT_USING_HWCRYPTO
#define RT_HWCRYPTO_DEFAULT_NAME "hwcryto"
#define RT_HWCRYPTO_IV_MAX_SIZE 16
#define RT_HWCRYPTO_KEYBIT_MAX_SIZE 256
#define RT_HWCRYPTO_USING_RNG
#define RT_HWCRYPTO_RNG_ROCKCHIP
#define RT_USING_LED
#define RT_LED_GPIO
#define RT_USING_INPUT
#define RT_INPUT_POWER
#define RT_INPUT_MISC
#define RT_INPUT_MISC_PWRKEY_RK8XX
#define RT_USING_MBOX
#define RT_MBOX_PIC
#define RT_MBOX_ROCKCHIP
#define RT_USING_HWSPINLOCK
#define RT_HWSPINLOCK_ROCKCHIP
#define RT_USING_PHYE
#define RT_PHYE_ROCKCHIP_NANENG_COMBO
#define RT_PHYE_ROCKCHIP_SNPS_PCIE3
#define RT_USING_NVME
#define RT_USING_NVME_IO_QUEUE 4
#define RT_NVME_PCI
#define RT_USING_BLK

/* Partition Types */

#define RT_BLK_PARTITION_DFS
#define RT_BLK_PARTITION_EFI
/* end of Partition Types */
#define RT_USING_FIRMWARE
#define RT_FIRMWARE_ARM_SCMI
#define RT_FIRMWARE_ARM_SCMI_TRANSPORT_MAILBOX
#define RT_FIRMWARE_ARM_SCMI_TRANSPORT_SMC
#define RT_USING_REGULATOR
#define RT_REGULATOR_FIXED
#define RT_REGULATOR_GPIO
#define RT_REGULATOR_SCMI
#define RT_REGULATOR_RK8XX
#define RT_USING_RESET
#define RT_RESET_SCMI

/* Power Management (PM) Domains device drivers */

#define RT_PMDOMAIN_SCMI
#define RT_PMDOMAIN_ROCKCHIP
/* end of Power Management (PM) Domains device drivers */
#define RT_USING_THERMAL

/* Thermal Sensors Drivers */

#define RT_THERMAL_ROCKCHIP_TSADC

/* Thermal Cool Drivers */

#define RT_THERMAL_COOL_PWM_FAN
#define RT_USING_NVMEM
#define RT_NVMEM_ROCKCHIP_OTP
#define RT_USING_DMA
#define RT_DMA_PL330
#define RT_USING_MFD
#define RT_MFD_SYSCON
#define RT_MFD_RK8XX
#define RT_MFD_RK8XX_I2C
#define RT_MFD_RK8XX_SPI
#define RT_USING_OFW
#define RT_FDT_EARLYCON_MSG_SIZE 128
#define RT_USING_OFW_BUS_RANGES_NUMBER 8
#define RT_USING_PCI
#define RT_PCI_MSI
#define RT_PCI_ENDPOINT
#define RT_PCI_SYS_64BIT
#define RT_PCI_CACHE_LINE_SIZE 8

/* PCI Device Drivers */

#define RT_PCI_DW
#define RT_PCI_DW_HOST
#define RT_PCI_DW_EP
#define RT_PCI_DW_ROCKCHIP
#define RT_USING_PIC
#define MAX_HANDLERS 2048
#define RT_PIC_ARM_GIC_V3
#define RT_PIC_ARM_GIC_V3_ITS
#define RT_PIC_ARM_GIC_V3_ITS_IRQ_MAX 256
#define RT_USING_PIN
#define RT_PIN_ROCKCHIP
#define RT_USING_PINCTRL
#define RT_PINCTRL_ROCKCHIP_RK8XX
#define RT_PINCTRL_ROCKCHIP
#define RT_USING_CLK
#define RT_CLK_SCMI
#define RT_CLK_ROCKCHIP_RK8XX_CLKOUT
#define RT_CLK_ROCKCHIP_LINK
#define RT_CLK_ROCKCHIP
#define RT_CLK_ROCKCHIP_RK3568
#define RT_CLK_ROCKCHIP_RK3576
#define RT_CLK_ROCKCHIP_RK3588

/* SoC (System on Chip) Drivers */

#define RT_SOC_ROCKCHIP_FIQ_DEBUGGER
#define RT_SOC_ROCKCHIP_GRF
#define RT_SOC_ROCKCHIP_HW_DECOMPRESS
#define RT_SOC_ROCKCHIP_IODOMAIN
/* end of SoC (System on Chip) Drivers */
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
#define RT_USING_POSIX_DEVIO
#define RT_USING_POSIX_STDIO
#define RT_USING_POSIX_POLL
#define RT_USING_POSIX_SELECT
#define RT_USING_POSIX_EVENTFD
#define RT_USING_POSIX_EPOLL
#define RT_USING_POSIX_SIGNALFD
#define RT_SIGNALFD_MAX_NUM 10
#define RT_USING_POSIX_TIMERFD
#define RT_USING_POSIX_SOCKET
#define RT_USING_POSIX_TERMIOS
#define RT_USING_POSIX_MMAN
#define RT_USING_POSIX_DELAY
#define RT_USING_POSIX_CLOCK
#define RT_USING_POSIX_TIMER

/* Interprocess Communication (IPC) */

#define RT_USING_POSIX_PIPE
#define RT_USING_POSIX_PIPE_SIZE 2048
#define RT_USING_POSIX_MESSAGE_QUEUE

/* Socket is in the 'Network' category */

/* end of Interprocess Communication (IPC) */
/* end of POSIX (Portable Operating System Interface) layer */
/* end of C/C++ and POSIX layer */

/* Network */

#define RT_USING_SAL
#define SAL_INTERNET_CHECK
#define SOCKET_TABLE_STEP_LEN 4

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
#define RT_LWIP_MEM_ALIGNMENT 8
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
/* end of Static IPv4 Address */
#define RT_LWIP_UDP
#define RT_LWIP_TCP
#define RT_LWIP_RAW
#define RT_MEMP_NUM_NETCONN 64
#define RT_LWIP_PBUF_NUM 320
#define RT_LWIP_RAW_PCB_NUM 32
#define RT_LWIP_UDP_PCB_NUM 32
#define RT_LWIP_TCP_PCB_NUM 64
#define RT_LWIP_TCP_SEG_NUM 480
#define RT_LWIP_TCP_SND_BUF 65535
#define RT_LWIP_TCP_WND 49512
#define RT_LWIP_TCPTHREAD_PRIORITY 8
#define RT_LWIP_TCPTHREAD_MBOX_SIZE 256
#define RT_LWIP_TCPTHREAD_STACKSIZE 65536
#define LWIP_NO_TX_THREAD
#define RT_LWIP_ETHTHREAD_PRIORITY 9
#define RT_LWIP_ETHTHREAD_STACKSIZE 16384
#define RT_LWIP_ETHTHREAD_MBOX_SIZE 256
#define LWIP_NETIF_STATUS_CALLBACK 1
#define LWIP_NETIF_LINK_CALLBACK 1
#define RT_LWIP_NETIF_NAMESIZE 6
#define SO_REUSE 1
#define LWIP_SO_RCVTIMEO 1
#define LWIP_SO_SNDTIMEO 1
#define LWIP_SO_RCVBUF 1
#define LWIP_SO_LINGER 0
#define RT_LWIP_NETIF_LOOPBACK
#define LWIP_NETIF_LOOPBACK 1
#define RT_LWIP_USING_HW_CHECKSUM
#define RT_LWIP_USING_PING
/* end of Network */

/* Memory protection */

/* end of Memory protection */

/* Utilities */

#define RT_USING_UTEST
#define UTEST_THR_STACK_SIZE 32768
#define UTEST_THR_PRIORITY 20
#define RT_UTEST_MAX_OPTIONS 64
#define RT_USING_RESOURCE_ID
#define RT_USING_ADT
#define RT_USING_ADT_AVL
#define RT_USING_ADT_BITMAP
#define RT_USING_ADT_HASHMAP
#define RT_USING_ADT_REF
/* end of Utilities */

/* Memory management */

#define RT_PAGE_AFFINITY_BLOCK_SIZE 0x1000
#define RT_PAGE_MAX_ORDER 11
#define RT_USING_MEMBLOCK
#define RT_INIT_MEMORY_REGIONS 128

/* Debugging */

/* end of Debugging */
/* end of Memory management */
#define RT_USING_LWP
#define LWP_DEBUG
#define LWP_DEBUG_INIT
#define LWP_USING_RUNTIME
#define RT_LWP_MAX_NR 128
#define LWP_TASK_STACK_SIZE 32768
#define RT_CH_MSG_MAX_NR 1024
#define LWP_TID_MAX_NR 128
#define RT_LWP_SHM_MAX_NR 64
#define RT_USING_LDSO
#define LWP_USING_TERMINAL
#define LWP_PTY_MAX_PARIS_LIMIT 64
#define RT_USING_VDSO

/* Using USB legacy version */

/* end of Using USB legacy version */
/* end of RT-Thread Components */

/* RT-Thread Utestcases */

#define RT_USING_UTESTCASES

/* Kernel Core */


/* SMP Test */

/* end of SMP Test */
/* end of Kernel Core */

/* Kernel Components */

/* Drivers */


/* IPC Test */

/* end of IPC Test */

/* Serial Test */

/* end of Serial Test */

/* SMP-Call Test */

#define RT_UTEST_SMP_CALL_FUNC
/* end of SMP-Call Test */
/* end of Drivers */

/* File System */

/* end of File System */

/* CPP11 */

/* end of CPP11 */

/* Network */

/* end of Network */

/* Utest Framework */

/* end of Utest Framework */
/* end of Kernel Components */

/* Memory Management Subsytem Testcase */

/* end of Memory Management Subsytem Testcase */

/* Tmpfs Testcase */

/* end of Tmpfs Testcase */
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

/* WCH HAL & SDK Drivers */

/* end of WCH HAL & SDK Drivers */

/* AT32 HAL & SDK Drivers */

/* end of AT32 HAL & SDK Drivers */

/* HC32 DDL Drivers */

/* end of HC32 DDL Drivers */

/* NXP HAL & SDK Drivers */

/* end of NXP HAL & SDK Drivers */

/* NUVOTON Drivers */

/* end of NUVOTON Drivers */

/* GD32 Drivers */

/* end of GD32 Drivers */
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
#define PKG_USING_ZLIB
#define PKG_USING_ZLIB_LATEST_VERSION
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
#define SOC_RK3500

#endif
