/***************************************************************************//**
 * @file    rtconfig.h
 * @brief   RT-Thread config file
 * 	COPYRIGHT (C) 2009, RT-Thread Development Team
 * @author
 * @version 0.4 beta
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file
 *  LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 ******************************************************************************/
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* RT_NAME_MAX*/
#define RT_NAME_MAX					(8)

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE				(4)

/* PRIORITY_MAX */
#define RT_THREAD_PRIORITY_MAX		(32)

/* Tick per Second */
#define RT_TICK_PER_SECOND			(100)

/* SECTION: RT_DEBUG */
#define RT_DEBUG
//#define RT_DEBUG_MEM 				(1)
//#define RT_DEBUG_SCHEDULER 			(1)
//#define RT_DEBUG_IPC 				(1)
//#define THREAD_DEBUG
//#define IRQ_DEBUG
#define RT_USING_OVERFLOW_CHECK
//#define DFS_DEBUG
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
#define EFM32_ACCEL_DEBUG
#define EFM32_SFLASH_DEBUG
//#define EFM32_SDCARD_DEBUG
//#define EFM32_ETHERNET_DEBUG


/* Using Hook */
//#define RT_USING_HOOK

/* Using Software Timer */
/* #define RT_USING_TIMER_SOFT */
#define RT_TIMER_THREAD_PRIO		(4)
#define RT_TIMER_THREAD_STACK_SIZE	(512)
#define RT_TIMER_TICK_PER_SECOND	(10)

/* SECTION: IPC */
/* Using Semaphore*/
#define RT_USING_SEMAPHORE                  /* Using by DFS and lwIP */
/* Using Mutex */
#define RT_USING_MUTEX                      /* Using by DFS */
/* Using Event */
//#define RT_USING_EVENT
/* Using MailBox */
#define RT_USING_MAILBOX                    /* Using by lwIP */
/* Using Message Queue */
//#define RT_USING_MESSAGEQUEUE
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
#if defined(EFM32_G8XX_STK)
//#define RT_USING_USART0				(0x0UL)
//#define RT_USART0_SYNC_MODE			(0x1UL) 		/* Master */
//#define RT_USART0_NAME				"spi0"
//#define RT_USART0_USING_DMA			(0x1UL)
#elif defined(EFM32_GXXX_DK)
#define RT_USING_USART0             (0x2UL)
#define RT_USART0_SYNC_MODE         (0x1UL) 	/* Master */
#define RT_USART0_NAME              "spi0"
#define RT_USART0_USING_DMA         (0x1UL)

#define RT_USING_USART2             (0x1UL)
#define RT_USART2_SYNC_MODE         (0x1UL) 	/* Master */
#define RT_USART2_NAME              "spi2"
#define RT_USART2_USING_DMA         (0x2UL)

#elif defined(EFM32GG_DK3750)
#define RT_USING_USART0             (0x1UL)
#define RT_USART0_SYNC_MODE         (0x1UL)     /* Master */
#define RT_USART0_NAME              "spi0"
#define RT_USART0_USING_DMA         (0x1UL)

#define RT_USING_USART1             (0x1UL)
#define RT_USART1_SYNC_MODE         (0x1UL)     /* Master */
#define RT_USART1_NAME              "spi1"
#define RT_USART1_USING_DMA         (0x2UL)

#endif

/* SECTION: IIC options */
//#define RT_USING_IIC0				0x3UL
#define RT_IIC0_NAME				"iic0"

/* SECTION: ACMP options */
//#define RT_USING_ACMP0
#define RT_ACMP0_NAME 				"acmp0"

/* SECTION: ADC options */
#define RT_USING_ADC0
#define RT_ADC0_NAME 				"adc0"
#if defined(RT_USING_ADC0)
#define RT_USING_MISC
#endif

/* SECTION: TIMER options */
//#define RT_USING_TIMER2				(0x00) 		/* Continuous mode */
#define RT_TIMER2_NAME				"tmr2"

/* SECTION: RTC options */
#if (defined(EFM32_G8XX_STK) || defined(EFM32_GXXX_DK) || defined(EFM32GG_DK3750))
#define RT_USING_RTC
#define RT_RTC_NAME 				"rtc"
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
#define RT_CONSOLE_DEVICE			(EFM_USART1)
#elif defined(EFM32_GXXX_DK)
#define RT_CONSOLE_DEVICE			(EFM_USART1)
#elif defined(EFM32GG_DK3750)
 #if defined(EFM32GG_DK3750_USING_LEUART1)
 #define RT_CONSOLE_DEVICE          (EFM_LEUART1)
 #else
 #define RT_CONSOLE_DEVICE          (EFM_UART1)
 #endif
#endif

/* SECTION: Console options */
#define RT_USING_CONSOLE
/* the buffer size of console*/
#define RT_CONSOLEBUF_SIZE			(128)

/* SECTION: finsh, a C-Express shell */
#define RT_USING_FINSH
/* Using symbol table */
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION

/* SECTION: Peripheral devices */
#define EFM32_INTERFACE_ADC 		(0)
#define EFM32_INTERFACE_IIC 		(1)
#define EFM32_INTERFACE_SPI 		(2)
#if (defined(EFM32_GXXX_DK) || defined(EFM32GG_DK3750))
//#define EFM32_USING_ACCEL 			EFM32_INTERFACE_IIC	/* Three axis accelerometer */
//#define EFM32_USING_SFLASH 							/* SPI Flash */
#define EFM32_USING_SPISD                       /* MicroSD card */
//#define EFM32_USING_ETHERNET                    /* Ethernet controller */
#endif

#if defined(EFM32_USING_ACCEL)
#if (EFM32_USING_ACCEL == EFM32_INTERFACE_ADC)
#define ACCEL_USING_DEVICE_NAME 	RT_ADC0_NAME
#define ACCEL_USING_DMA				(0x3UL) 			/* For multiple channels scan mode */
#elif (EFM32_USING_ACCEL == EFM32_INTERFACE_IIC)
#define ACCEL_USING_DEVICE_NAME 	RT_IIC0_NAME
#endif
#endif

#if defined(EFM32_USING_SFLASH)
#define SFLASH_USING_DEVICE_NAME 	RT_USART0_NAME
#endif

#if defined(EFM32_USING_SPISD)
#define SPISD_USING_DEVICE_NAME 	RT_USART0_NAME
#define SPISD_DEVICE_NAME 			"spiSd"
#endif

#if defined(EFM32_USING_ETHERNET)
 #if defined(EFM32_GXXX_DK)
 #define ETH_USING_DEVICE_NAME 		RT_USART2_NAME
 #elif defined(EFM32GG_DK3750)
 #define ETH_USING_DEVICE_NAME 		RT_USART1_NAME
 #endif
#define ETH_DEVICE_NAME 			"spiEth"
#define ETH_ADDR_DEFAULT 			{0x00, 0x01, 0x02, 0x03, 0x04, 0x05}
#endif

/* SECTION: device filesystem */
#if defined(EFM32_USING_SPISD)
#define RT_USING_DFS
#define RT_USING_DFS_ELMFAT
#define DFS_ELMFAT_INTERFACE_EFM
/* the max number of mounted filesystem */
#define DFS_FILESYSTEMS_MAX         (2)
/* the max number of opened files 		*/
#define DFS_FD_MAX                  (4)
/* the max number of cached sector 		*/
#define DFS_CACHE_MAX_NUM           (4)
#endif /* defined(EFM32_USING_SPISD) */

/* SECTION: lwip, a lighwight TCP/IP protocol stack */
#if defined(EFM32_USING_ETHERNET)
#define EFM32_USING_ETH_HTTPD
//#define EFM32_USING_ETH_UTILS
//#define hostName 					"onelife.dyndns.org"
//#define userPwdB64 					"dXNlcjpwYXNzd2Q="

//#define RT_USING_LWIP
//#define RT_USING_NETUTILS
/* LwIP uses RT-Thread Memory Management */
#define RT_LWIP_USING_RT_MEM
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
#define RT_LWIP_TCP_PCB_NUM			(2)

/* ip address of target*/
#define RT_LWIP_IPADDR0				(192)
#define RT_LWIP_IPADDR1				(168)
#define RT_LWIP_IPADDR2				(1)
#define RT_LWIP_IPADDR3				(118)

/* gateway address of target*/
#define RT_LWIP_GWADDR0				(192)
#define RT_LWIP_GWADDR1				(168)
#define RT_LWIP_GWADDR2				(1)
#define RT_LWIP_GWADDR3				(1)

/* mask address of target*/
#define RT_LWIP_MSKADDR0 			(255)
#define RT_LWIP_MSKADDR1 			(255)
#define RT_LWIP_MSKADDR2 			(255)
#define RT_LWIP_MSKADDR3 			(0)

/* tcp thread options */
#define RT_LWIP_TCPTHREAD_PRIORITY	(12)
#define RT_LWIP_TCPTHREAD_MBOX_SIZE	(4)
#define RT_LWIP_TCPTHREAD_STACKSIZE	(1024)

/* ethernet if thread options */
#define RT_LWIP_ETHTHREAD_PRIORITY 	(15)
#define RT_LWIP_ETHTHREAD_MBOX_SIZE	(4)
#define RT_LWIP_ETHTHREAD_STACKSIZE	(512)
#endif /* defined(EFM32_USING_ETHERNET) */

/* Exported functions ------------------------------------------------------- */

#endif /* __RTTHREAD_CFG_H__ */
