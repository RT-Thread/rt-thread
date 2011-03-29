/******************************************************************//**
 * @file 		rtconfig.h
 * @brief 	RT-Thread config file
 * 	COPYRIGHT (C) 2009, RT-Thread Development Team
 * @author 	
 * @version 	0.4 beta
 **********************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file LICENSE in this 
 * distribution or at http://www.rt-thread.org/license/LICENSE
 *********************************************************************/
#ifndef __RTTHREAD_CFG_H__
#define __RTTHREAD_CFG_H__

/* Includes -------------------------------------------------------------------*/
/* Exported types -------------------------------------------------------------*/
/* Exported constants ---------------------------------------------------------*/
/* Exported macro -------------------------------------------------------------*/
/* RT_NAME_MAX*/
#define RT_NAME_MAX				8

/* RT_ALIGN_SIZE*/
#define RT_ALIGN_SIZE			4

/* PRIORITY_MAX */
#define RT_THREAD_PRIORITY_MAX	32

/* Tick per Second */
#define RT_TICK_PER_SECOND		100

/* SECTION: RT_DEBUG */
#define RT_DEBUG
#define RT_MEM_DEBUG
//#define THREAD_DEBUG
//#define IRQ_DEBUG
#define RT_USING_OVERFLOW_CHECK

//#define RT_IRQHDL_DEBUG
//#define RT_ADC_DEBUG
//#define RT_ACMP_DEBUG
//#define RT_TIMER_DEBUG
//#define RT_USART_DEBUG

/* Using Hook */
//#define RT_USING_HOOK

/* Using Software Timer */
/* #define RT_USING_TIMER_SOFT */
#define RT_TIMER_THREAD_PRIO		4
#define RT_TIMER_THREAD_STACK_SIZE	512
#define RT_TIMER_TICK_PER_SECOND	10

/* SECTION: IPC */
/* Using Semaphore*/
#define RT_USING_SEMAPHORE

/* Using Mutex */
//#define RT_USING_MUTEX

/* Using Event */
//#define RT_USING_EVENT

/* Using MailBox */
//#define RT_USING_MAILBOX

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
#define RT_USING_USART0			0x2UL
#define RT_USART0_NAME			"debug"
#define RT_USART0_USING_DMA		0x0UL
#elif defined(EFM32_G890_STK)
#define RT_USING_USART1			0x1UL
#define RT_USART1_NAME			"debug"
#define RT_USART1_USING_DMA		0x0UL
#endif

/* SECTION: RTC options */
#if (defined(EFM32_G290_DK) || defined(EFM32_G890_STK))
#define RT_USING_RTC
#endif
#define RT_RTC_NAME 			"rtc"

/* SECTION: ADC options */
#define RT_USING_ACMP0
#define RT_ACMP0_NAME 			"acmp0"

/* SECTION: ADC options */
#define RT_USING_ADC0
#define RT_ADC0_NAME 			"adc"

/* SECTION: Serial options */
#if defined(EFM32_G290_DK)
#define RT_CONSOLE_DEVICE		0x0UL
#elif defined(EFM32_G890_STK)
#define RT_CONSOLE_DEVICE		0x1UL
#endif

/* SECTION: Console options */
#define RT_USING_CONSOLE
/* the buffer size of console*/
#define RT_CONSOLEBUF_SIZE		128

/* SECTION: finsh, a C-Express shell */
#define RT_USING_FINSH
/* Using symbol table */
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION

/* Exported functions --------------------------------------------------------- */

#endif /* __RTTHREAD_CFG_H__ */