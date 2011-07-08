/***************************************************************************//**
 * @file 	rtconfig.h
 * @brief 	RT-Thread config file
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
//#define RT_MEM_DEBUG 				(1)
//#define RT_DEBUG_SCHEDULER 			(1)
//#define THREAD_DEBUG
//#define IRQ_DEBUG
#define RT_USING_OVERFLOW_CHECK
//#define DFS_DEBUG
#define RT_LWIP_DEBUG

//#define RT_IRQHDL_DEBUG
//#define RT_USART_DEBUG
//#define RT_IIC_DEBUG
//#define RT_MISC_DEBUG
//#define RT_ADC_DEBUG
//#define RT_ACMP_DEBUG
//#define RT_TIMER_DEBUG
//#define RT_RTC_DEBUG

#define EFM32_SFLASH_DEBUG
//#define EFM32_SDCARD_DEBUG
#define EFM32_ETHERNET_DEBUG


/* Using Hook */
//#define RT_USING_HOOK

/* Using Software Timer */
/* #define RT_USING_TIMER_SOFT */
#define RT_TIMER_THREAD_PRIO		(4)
#define RT_TIMER_THREAD_STACK_SIZE	(512)
#define RT_TIMER_TICK_PER_SECOND	(10)

/* SECTION: IPC */
/* Using Semaphore*/
#define RT_USING_SEMAPHORE 					/* Using by DFS and lwIP */
/* Using Mutex */
//#define RT_USING_MUTEX 						/* Using by DFS */
/* Using Event */
//#define RT_USING_EVENT
/* Using MailBox */
#define RT_USING_MAILBOX 					/* Using by lwIP */
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

/* USART Device for Console */
#if defined(EFM32_G290_DK)
#define RT_USING_USART1				(0x0UL)
#define RT_USART1_NAME				"debug"
//#define RT_USART1_USING_DMA			(0x0UL)
#elif defined(EFM32_G890_STK)
#define RT_USING_USART1				(0x1UL)
#define RT_USART1_NAME				"debug"
#define RT_USART1_USING_DMA			(0x0UL)
#endif

/* SECTION: SPI options */
#if defined(EFM32_G290_DK)
#define RT_USING_USART0				(0x2UL)
#define RT_USART0_SYNC_MODE			(0x1UL) 	/* Master */
#define RT_USART0_NAME				"spi0"
#define RT_USART0_USING_DMA			(0x1UL)

#define RT_USING_USART2				(0x1UL)
#define RT_USART2_SYNC_MODE			(0x1UL) 	/* Master */
#define RT_USART2_NAME				"spi2"
#define RT_USART2_USING_DMA			(0x2UL)
#elif defined(EFM32_G890_STK)
//#define RT_USING_USART0				(0x0UL)
//#define RT_USART0_SYNC_MODE			(0x1UL) 		/* Master */
//#define RT_USART0_NAME				"spi0"
//#define RT_USART0_USING_DMA			(0x1UL)
#endif

/* SECTION: IIC options */
//#define RT_USING_IIC0				0x1UL
#define RT_IIC0_NAME				"iic0"

/* SECTION: ACMP options */
//#define RT_USING_ACMP0
#define RT_ACMP0_NAME 				"acmp0"

/* SECTION: ADC options */
#define RT_USING_ADC0
#define RT_ADC0_NAME 				"adc"

/* SECTION: TIMER options */
//#define RT_USING_TIMER2				(0x00) 		/* Continuous mode */
#define RT_TIMER2_NAME				"tmr2"

/* SECTION: RTC options */
#if (defined(EFM32_G290_DK) || defined(EFM32_G890_STK))
//#define RT_USING_RTC
#define RT_RTC_NAME 				"rtc"
#endif

/* SECTION: Serial options */
#if defined(EFM32_G290_DK)
#define RT_CONSOLE_DEVICE			(0x1UL)
#elif defined(EFM32_G890_STK)
#define RT_CONSOLE_DEVICE			(0x1UL)
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

/* SECTION: SPI Flash, MicroSD card and Ethernet */
#if defined(EFM32_G290_DK)
//#define EFM32_USING_SFLASH
//#define EFM32_USING_SPISD
#define EFM32_USING_ETHERNET
#endif
#if defined(EFM32_USING_SFLASH)
#define SFLASH_USING_DEVICE_NAME 	RT_USART0_NAME
#endif
#if defined(EFM32_USING_SPISD)
#define SPISD_USING_DEVICE_NAME 	RT_USART0_NAME
#define SPISD_DEVICE_NAME 			"spiSd"
#endif
#if defined(EFM32_USING_ETHERNET)
#define ETH_USING_DEVICE_NAME 		RT_USART2_NAME
#define ETH_DEVICE_NAME 			"spiEth"
#define ETH_ADDR_DEFAULT 			{0x11, 0x22, 0x33, 0x44, 0x55, 0x66}
#endif

/* SECTION: device filesystem */
#if defined(EFM32_USING_SPISD)
//#define RT_USING_DFS
//#define RT_USING_DFS_ELMFAT
#define DFS_ELMFAT_INTERFACE_EFM
/* the max number of mounted filesystem */
#define DFS_FILESYSTEMS_MAX			(2)
/* the max number of opened files 		*/
#define DFS_FD_MAX					(4)
/* the max number of cached sector 		*/
#define DFS_CACHE_MAX_NUM   		(4)
#endif

/* SECTION: lwip, a lighwight TCP/IP protocol stack */
#if defined(EFM32_USING_ETHERNET)
#define RT_USING_LWIP
#define RT_USING_NETUTILS
//#define RT_LWIP_DHCP
/* LwIP uses RT-Thread Memory Management */
#define RT_LWIP_USING_RT_MEM
/* Enable ICMP protocol*/
#define RT_LWIP_ICMP
/* Enable UDP protocol*/
#define RT_LWIP_UDP
/* Enable TCP protocol*/
#define RT_LWIP_TCP
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
#define RT_LWIP_TCPTHREAD_STACKSIZE	(512)

/* ethernet if thread options */
#define RT_LWIP_ETHTHREAD_PRIORITY 	(15)
#define RT_LWIP_ETHTHREAD_MBOX_SIZE	(4)
#define RT_LWIP_ETHTHREAD_STACKSIZE	(512)
#endif

/* Exported functions ------------------------------------------------------- */

#endif /* __RTTHREAD_CFG_H__ */
