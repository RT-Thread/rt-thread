/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2012, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-06-25     Bernard      first version
 * 2011-08-08     lgnq            modified for Loongson LS1B
 * 2015-07-06     chinesebear  modified for Loongson LS1C
 */

#include <rtthread.h>
#include <rthw.h>

#include "board.h"
#include "uart.h"
#include "ls1c.h"

/**
 * @addtogroup Loongson LS1B
 */
 
/*@{*/

/**
 * This is the timer interrupt service routine.
 */
void rt_hw_timer_handler(void)
{
	unsigned int count;

	count = read_c0_compare();
	write_c0_compare(count);
	write_c0_count(0);

	/* increase a OS tick */
	rt_tick_increase();
}

/**
 * This function will initial OS timer
 */
void rt_hw_timer_init(void)
{
	write_c0_compare(CPU_HZ/2/RT_TICK_PER_SECOND);
	write_c0_count(0);
}


/**
 * init hardware FPU
 */
void rt_hw_fpu_init(void)
{
    rt_uint32_t c0_status = 0;
    rt_uint32_t c1_status = 0;

    // 使能协处理器1--FPU
    c0_status = read_c0_status();
    c0_status |= (ST0_CU1 | ST0_FR);
    write_c0_status(c0_status);

    // 配置FPU
    c1_status = read_c1_status();
    c1_status |= (FPU_CSR_FS | FPU_CSR_FO | FPU_CSR_FN);    // set FS, FO, FN
    c1_status &= ~(FPU_CSR_ALL_E);                          // disable exception
    c1_status = (c1_status & (~FPU_CSR_RM)) | FPU_CSR_RN;   // set RN
    write_c1_status(c1_status);

    return ;
}


/**
 * This function will initial sam7s64 board.
 */
void rt_hw_board_init(void)
{
#ifdef RT_USING_UART
	/* init hardware UART device */
	rt_hw_uart_init();
#endif

#ifdef RT_USING_CONSOLE
	/* set console device */
	rt_console_set_device("uart2");
#endif

	/* init operating system timer */
	rt_hw_timer_init();

#ifdef RT_USING_FPU
    /* init hardware fpu */
    rt_hw_fpu_init();
#endif

	rt_kprintf("current sr: 0x%08x\n", read_c0_status());
}

#define __raw_out_put(unr) \
	while (*ptr) \
	{ \
		if (*ptr == '\n') \
		{ \
			/* FIFO status, contain valid data */ \
			while (!(UART_LSR(UART##unr##_BASE) & (UARTLSR_TE | UARTLSR_TFE))); \
			/* write data */ \
			UART_DAT(UART##unr##_BASE) = '\r'; \
		} \
		/* FIFO status, contain valid data */ \
		while (!(UART_LSR(UART##unr##_BASE) & (UARTLSR_TE | UARTLSR_TFE))); \
		/* write data */ \
		UART_DAT(UART##unr##_BASE) = *ptr; \
		ptr ++; \
	}

/* UART line status register value */
#define UARTLSR_ERROR	(1 << 7)
#define UARTLSR_TE		(1 << 6)
#define UARTLSR_TFE		(1 << 5)
#define UARTLSR_BI		(1 << 4)
#define UARTLSR_FE		(1 << 3)
#define UARTLSR_PE		(1 << 2)
#define UARTLSR_OE		(1 << 1)
#define UARTLSR_DR		(1 << 0)
void rt_hw_console_output(const char *ptr)
{
#if defined(RT_USING_UART0)
    __raw_out_put(0);
#elif defined(RT_USING_UART2)
    __raw_out_put(2);
#elif defined(RT_USING_UART3)
    __raw_out_put(3);
#endif
}

/*@}*/
