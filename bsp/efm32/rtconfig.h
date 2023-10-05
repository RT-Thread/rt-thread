/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 */

#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* EFM32_BOARD */
//#define EFM32_G8XX_STK
//#define EFM32_GXXX_DK
#define EFM32GG_DK3750

/* RT_NAME_MAX */
#define RT_NAME_MAX                 (8)

/* RT_ALIGN_SIZE */
#define RT_ALIGN_SIZE               (8)

/* PRIORITY_MAX */
#define RT_THREAD_PRIORITY_MAX      (32)

/* Tick per Second */
#define RT_TICK_PER_SECOND          (100)

/* SECTION: RT_DEBUG */
#define RT_DEBUG
#define RT_DEBUG_COLOR
#define RT_LWIP_DEBUG

//#define RT_IRQHDL_DEBUG
//#define RT_USART_DEBUG
//#define RT_LEUART_DEBUG
//#define RT_IIC_DEBUG
//#define RT_MISC_DEBUG
//#define RT_ADC_DEBUG
//#define RT_ACMP_DEBUG
//#define RT_TIMER_DEBUG
//#define RT_RTC_DEBUG

#define EFM32_DEBUG
#define EFM32_EMU_DEBUG
#define EFM32_ACCEL_DEBUG
#define EFM32_SFLASH_DEBUG
//#define EFM32_SDCARD_DEBUG
#define EFM32_ETHERNET_DEBUG
#define EFM32_LCD_DEBUG
#define EFM32_KEYS_DEBUG

/* Using Hook */
//#define RT_USING_HOOK

/* Using Software Timer */
/* #define RT_USING_TIMER_SOFT */
#define RT_TIMER_THREAD_PRIO        (4)
#define RT_TIMER_THREAD_STACK_SIZE  (512)
#define RT_TIMER_TICK_PER_SECOND    (10)

/* SECTION: IPC */
/* Using Semaphore*/
#define RT_USING_SEMAPHORE                  /* Required by DFS and lwIP */
/* Using Mutex */
#define RT_USING_MUTEX                      /* Required by DFS */
/* Using Event */
//#define RT_USING_EVENT
/* Using MailBox */
#define RT_USING_MAILBOX                    /* Required by lwIP */
/* Using Message Queue */
#define RT_USING_MESSAGEQUEUE               /* Required by RTGUI */
/* SECTION: Memory Management */
/* Using Memory Pool Management*/
//#define RT_USING_MEMPOOL

/* Using Dynamic Heap Management */
#define RT_USING_HEAP

/* Using Small MM */
#define RT_USING_SMALL_MEM

/* SECTION: Device System */
/* Using Device System */
#define RT_USING_DEVICE

/* SECTION: UART options */
/* USART/UART/LEUART Device for Console */
#if defined(EFM32_G8XX_STK)
#define RT_USING_USART1             (0x1UL)
#define RT_USART1_NAME              "debug"
//#define RT_USART1_USING_DMA           (0x0UL)
#elif defined(EFM32_GXXX_DK)
#define RT_USING_USART1             (0x0UL)
#define RT_USART1_NAME              "debug"
//#define RT_USART1_USING_DMA           (0x0UL)
#elif defined(EFM32GG_DK3750)
#define EFM32GG_DK3750_USING_LEUART1
 #if defined(EFM32GG_DK3750_USING_LEUART1)
 #define RT_USING_LEUART1           (0x0UL)
 #define RT_LEUART1_NAME            "debug0"
 //#define RT_LEUART1_USING_DMA       (0x0UL)
 #else
 #define RT_USING_UART1              (0x2UL)
 #define RT_UART1_NAME               "debug"
 //#define RT_UART1_USING_DMA          (0x0UL)
 #endif
#endif

/* SECTION: SPI options */
#define EFM32_SPI_MASTER            (1 << 0)    /* Master mode */
#define EFM32_SPI_AUTOCS            (1 << 1)    /* Auto chip select */
#define EFM32_SPI_9BIT              (1 << 2)    /* 9-bit data */
/*
    0: Clock idle low, sample on rising edge
    1: Clock idle low, sample on falling edge
    2: Clock idle high, sample on falling edge
    3: Clock idle high, sample on rising edge.
*/
#define EFM32_SPI_CLK_MODE(mode)    (mode << 3) /* clock mode */

#if defined(EFM32_G8XX_STK)
//#define RT_USING_USART0               (0x0UL)
//#define RT_USART0_SYNC_MODE           (EFM32_SPI_MASTER)
//#define RT_USART0_NAME                "spi0"
//#define RT_USART0_USING_DMA           (0x1UL)
#elif defined(EFM32_GXXX_DK)
#define RT_USING_USART0             (0x2UL)
#define RT_USART0_SYNC_MODE         (EFM32_SPI_MASTER | EFM32_SPI_AUTOCS | \
                                    EFM32_SPI_CLK_MODE(0))
#define RT_USART0_NAME              "spi0"
#define RT_USART0_USING_DMA         (0x1UL)

#define RT_USING_USART2             (0x1UL)
#define RT_USART2_SYNC_MODE         (EFM32_SPI_MASTER | EFM32_SPI_CLK_MODE(0))
#define RT_USART2_NAME              "spi2"
#define RT_USART2_USING_DMA         (0x2UL)

#elif defined(EFM32GG_DK3750)
#define RT_USING_USART0             (0x1UL)
#define RT_USART0_SYNC_MODE         (EFM32_SPI_MASTER | EFM32_SPI_AUTOCS | \
                                    EFM32_SPI_CLK_MODE(0))
#define RT_USART0_NAME              "spi0"
#define RT_USART0_USING_DMA         (0x1UL)

#define RT_USING_USART1             (0x1UL)
#define RT_USART1_SYNC_MODE         (EFM32_SPI_MASTER | EFM32_SPI_AUTOCS | \
                                    EFM32_SPI_9BIT | EFM32_SPI_CLK_MODE(3))
#define RT_USART1_NAME              "spi1"
#define RT_USART1_USING_DMA         (0x2UL)
#endif

/* SECTION: IIC options */
//#define RT_USING_IIC0             0x3UL
#define RT_IIC0_NAME                "iic0"

/* SECTION: ACMP options */
//#define RT_USING_ACMP0
#define RT_ACMP0_NAME               "acmp0"

/* SECTION: ADC options */
#define RT_USING_ADC0
#define RT_ADC0_NAME                "adc0"
#if defined(RT_USING_ADC0)
#define RT_USING_MISC
#endif

/* SECTION: TIMER options */
//#define RT_USING_TIMER2               (0x00)      /* Continuous mode */
#define RT_TIMER2_NAME              "tmr2"

/* SECTION: RTC options */
#if (defined(EFM32_G8XX_STK) || defined(EFM32_GXXX_DK) || defined(EFM32GG_DK3750))
#define RT_USING_RTC
#define RT_RTC_NAME                 "rtc"
#endif

/* SECTION: Serial options */
#define EFM_USART0                  (0x00UL)
#define EFM_USART1                  (0x01UL)
#define EFM_USART2                  (0x02UL)
#define EFM_UART0                   (0x10UL)
#define EFM_UART1                   (0x11UL)
#define EFM_LEUART0                 (0x20UL)
#define EFM_LEUART1                 (0x21UL)

#if defined(EFM32_G8XX_STK)
#define RT_CONSOLE_DEVICE           (EFM_USART1)
#elif defined(EFM32_GXXX_DK)
#define RT_CONSOLE_DEVICE           (EFM_USART1)
#elif defined(EFM32GG_DK3750)
 #if defined(EFM32GG_DK3750_USING_LEUART1)
 #define RT_CONSOLE_DEVICE          (EFM_LEUART1)
 #else
 #define RT_CONSOLE_DEVICE          (EFM_UART1)
 #endif
#endif

/* SECTION: Runtime library */
#define RT_LIBC_USING_TIME

/* SECTION: Console options */
#define RT_USING_CONSOLE
/* the buffer size of console*/
#define RT_CONSOLEBUF_SIZE          (128)

/* SECTION: finsh, a C-Express shell */
#define RT_USING_FINSH
/* Using symbol table */
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION

/* SECTION: Peripheral devices */
#define EFM32_INTERFACE_ADC         (0)
#define EFM32_INTERFACE_IIC         (1)
#define EFM32_INTERFACE_SPI         (2)
#if (defined(EFM32_GXXX_DK) || defined(EFM32GG_DK3750))
//#define EFM32_USING_ACCEL             EFM32_INTERFACE_IIC /* Three axis accelerometer */
//#define EFM32_USING_SFLASH                            /* SPI Flash */
#define EFM32_USING_SPISD                       /* MicroSD card */
//#define EFM32_USING_ETHERNET                    /* Ethernet controller */
//#define EFM32_USING_LCD                         /* TFT LCD */
//#define EFM32_USING_KEYS                        /* Keys and joystick */
#endif

#if defined(EFM32_USING_ACCEL)
#if (EFM32_USING_ACCEL == EFM32_INTERFACE_ADC)
#define ACCEL_USING_DEVICE_NAME     RT_ADC0_NAME
#define ACCEL_USING_DMA             (0x3UL)             /* For multiple channels scan mode */
#elif (EFM32_USING_ACCEL == EFM32_INTERFACE_IIC)
#define ACCEL_USING_DEVICE_NAME     RT_IIC0_NAME
#endif
#endif

#if defined(EFM32_USING_SFLASH)
#define SFLASH_USING_DEVICE_NAME    RT_USART0_NAME
#endif

#if defined(EFM32_USING_SPISD)
#define SPISD_USING_DEVICE_NAME     RT_USART0_NAME
#define SPISD_DEVICE_NAME           "spiSd"
#endif

#if defined(EFM32_USING_ETHERNET)
 #if defined(EFM32_GXXX_DK)
 #define ETH_USING_DEVICE_NAME      RT_USART2_NAME
 #elif defined(EFM32GG_DK3750)
 #define ETH_USING_DEVICE_NAME      RT_USART1_NAME
 #endif
#define ETH_DEVICE_NAME             "spiEth"
#define ETH_ADDR_DEFAULT            {0x00, 0x01, 0x02, 0x03, 0x04, 0x05}
#endif

/* SECTION: device filesystem */
#ifdef EFM32_USING_SPISD
#define RT_USING_DFS
/* the max number of mounted filesystem */
#define DFS_FILESYSTEMS_MAX         (2)
/* the max number of opened files       */
#define DFS_FD_MAX                  (4)
/* the max number of cached sector      */
#define DFS_CACHE_MAX_NUM           (4)
#endif /* EFM32_USING_SPISD */
#if defined(EFM32_USING_SPISD)
#define RT_USING_DFS_ELMFAT
#define DFS_ELMFAT_INTERFACE_EFM
#endif /* defined(EFM32_USING_SPISD) */
#define RT_USING_DFS_DEVFS

/* SECTION: lwip, a lighwight TCP/IP protocol stack */
#if defined(EFM32_USING_ETHERNET)
#define EFM32_USING_ETH_HTTPD
//#define EFM32_USING_ETH_UTILS
//#define hostName                  "onelife.dyndns.org"
//#define userPwdB64                    "dXNlcjpwYXNzd2Q="

//#define RT_USING_LWIP
//#define RT_USING_NETUTILS
//#define RT_LWIP_DHCP
/* Enable ICMP protocol*/
#define RT_LWIP_ICMP
/* Enable ICMP protocol*/
//#define RT_LWIP_IGMP
/* Enable UDP protocol*/
#define RT_LWIP_UDP
/* Enable TCP protocol*/
#define RT_LWIP_TCP
/* Enable DHCP */
//#define RT_LWIP_DHCP
/* Enable DNS */
//#define RT_LWIP_DNS

/* the number of simulatenously active TCP connections*/
#define RT_LWIP_TCP_PCB_NUM         (2)

/* ip address of target*/
#define RT_LWIP_IPADDR0             (192)
#define RT_LWIP_IPADDR1             (168)
#define RT_LWIP_IPADDR2             (1)
#define RT_LWIP_IPADDR3             (118)
/* gateway address of target*/
#define RT_LWIP_GWADDR0             (192)
#define RT_LWIP_GWADDR1             (168)
#define RT_LWIP_GWADDR2             (1)
#define RT_LWIP_GWADDR3             (1)
/* mask address of target*/
#define RT_LWIP_MSKADDR0            (255)
#define RT_LWIP_MSKADDR1            (255)
#define RT_LWIP_MSKADDR2            (255)
#define RT_LWIP_MSKADDR3            (0)

/* tcp thread options */
#define RT_LWIP_TCPTHREAD_PRIORITY  (12)
#define RT_LWIP_TCPTHREAD_MBOX_SIZE (4)
#define RT_LWIP_TCPTHREAD_STACKSIZE (1024)
/* ethernet if thread options */
#define RT_LWIP_ETHTHREAD_PRIORITY  (15)
#define RT_LWIP_ETHTHREAD_MBOX_SIZE (4)
#define RT_LWIP_ETHTHREAD_STACKSIZE (512)
#endif /* defined(EFM32_USING_ETHERNET) */

/* SECTION: RTGUI support */
#if defined(EFM32_USING_LCD)
#define LCD_USING_DEVICE_NAME       RT_USART1_NAME
#define LCD_DEVICE_NAME             "lcd"
/* using RTGUI support */
// #define RT_USING_RTGUI

/* name length of RTGUI object */
#define RTGUI_NAME_MAX              (16)
/* support 16 weight font */
#define RTGUI_USING_FONT16
/* support 12 weight font */
#define RTGUI_USING_FONT12
/* support Chinese font */
#define RTGUI_USING_FONTHZ
/* use DFS as file interface */
#define RTGUI_USING_DFS_FILERW
/* use font file as Chinese font */
/* #define RTGUI_USING_HZ_FILE */
/* use Chinese bitmap font */
#define RTGUI_USING_HZ_BMP
/* use small size in RTGUI */
/* #define RTGUI_USING_SMALL_SIZE */
/* use mouse cursor */
#define RTGUI_USING_MOUSE_CURSOR
/* RTGUI image options */
#define RTGUI_IMAGE_XPM
//#define RTGUI_IMAGE_JPEG
#define RTGUI_IMAGE_TJPGD
//#define RTGUI_IMAGE_PNG
#define RTGUI_IMAGE_BMP
#endif /* defined(EFM32_USING_LCD) */

/* Exported functions ------------------------------------------------------- */

#endif /* __RTTHREAD_CFG_H__ */
