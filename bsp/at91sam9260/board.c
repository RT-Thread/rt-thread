/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 */

#include <rtthread.h>
#include <rthw.h>

#include "board.h"

/**
 * @addtogroup at91sam9260
 */
/*@{*/


extern void rt_hw_clock_init(void);
extern void rt_hw_mmu_init(void);

extern void rt_hw_get_clock(void);
extern void rt_hw_set_dividor(rt_uint8_t hdivn, rt_uint8_t pdivn);
extern void rt_hw_set_clock(rt_uint8_t sdiv, rt_uint8_t pdiv, rt_uint8_t mdiv);

/*set debug serial port*/
//#define USE_UART1
//#define USE_UART3
//#define USE_DBGU

#define DBGU	((struct uartport *)0xfffff200)
#define UART0   ((struct uartport *)AT91SAM9260_BASE_US0)
#define UART1   ((struct uartport *)AT91SAM9260_BASE_US1)
#define UART2   ((struct uartport *)AT91SAM9260_BASE_US2)
#define UART3	((struct uartport *)AT91SAM9260_BASE_US3)
#define UART4   ((struct uartport *)AT91SAM9260_BASE_US4)
#define UART5   ((struct uartport *)AT91SAM9260_BASE_US5)

struct serial_int_rx uart0_int_rx;
struct serial_device uart0 =
{
	DBGU,
	&uart0_int_rx,
	RT_NULL
};
struct rt_device uart0_device;

struct serial_int_rx uart1_int_rx;
struct serial_device uart1 =
{
	UART0,
	&uart1_int_rx,
	RT_NULL
};
struct rt_device uart1_device;

struct serial_int_rx uart2_int_rx;
struct serial_device uart2 =
{
	UART1,
	&uart2_int_rx,
	RT_NULL
};
struct rt_device uart2_device;

struct serial_int_rx uart3_int_rx;
struct serial_device uart3 =
{
	UART2,
	&uart3_int_rx,
	RT_NULL
};
struct rt_device uart3_device;

struct serial_int_rx uart4_int_rx;
struct serial_device uart4 =
{
	UART3,
	&uart4_int_rx,
	RT_NULL
};
struct rt_device uart4_device;


/**
 * This function will handle serial
 */
void rt_serial_handler(int vector)
{
	int status;

	switch (vector) 
	{
	#ifdef RT_USING_UART0
	case AT91SAM9260_ID_US0:
		status = readl(AT91SAM9260_BASE_US0+AT91_US_CSR);
		if (!(status & readl(AT91SAM9260_BASE_US0+AT91_US_IMR)))
		{
			return;
		}
		rt_hw_serial_isr(&uart1_device);
		break;
	#endif
	#ifdef RT_USING_UART1
	case AT91SAM9260_ID_US1:
		status = readl(AT91SAM9260_BASE_US1+AT91_US_CSR);
		if (!(status & readl(AT91SAM9260_BASE_US1+AT91_US_IMR)))
		{
			return;
		}
		rt_hw_serial_isr(&uart2_device);
		break;
	#endif
	#ifdef RT_USING_UART2
	case AT91SAM9260_ID_US2:
		status = readl(AT91SAM9260_BASE_US2+AT91_US_CSR);
		if (!(status & readl(AT91SAM9260_BASE_US2+AT91_US_IMR)))
		{
			return;
		}
		rt_hw_serial_isr(&uart3_device);
		break;
	#endif
	#ifdef RT_USING_UART3
	case AT91SAM9260_ID_US3:
		status = readl(AT91SAM9260_BASE_US3+AT91_US_CSR);
		if (!(status & readl(AT91SAM9260_BASE_US3+AT91_US_IMR)))
		{
			return;
		}
		rt_hw_serial_isr(&uart4_device);
		break;
	#endif
	default: break;
	}

}

void uart_port_init(rt_uint32_t base)
{
	#define BAUDRATE  115200
	rt_uint32_t  cd;

	writel(AT91_US_RSTTX | AT91_US_RSTRX | 
	       AT91_US_RXDIS | AT91_US_TXDIS, 
	       base + AT91_US_CR);
	writel( AT91_US_USMODE_NORMAL | AT91_US_USCLKS_MCK | 
		AT91_US_CHRL_8 | AT91_US_PAR_NONE | 
		AT91_US_NBSTOP_1 | AT91_US_CHMODE_NORMAL, 
		base + AT91_US_MR);
	cd = (clk_get_rate(clk_get("mck")) / 16 + BAUDRATE/2) / BAUDRATE;
	writel(cd, base + AT91_US_BRGR);
	writel(AT91_US_RXEN | AT91_US_TXEN, base + AT91_US_CR);
	
	writel(0x1, base + AT91_US_IER);
}

/**
 * This function will handle init uart
 */
void rt_hw_uart_init(void)
{
#ifdef RT_USING_UART0
	at91_sys_write(AT91_PMC_PCER, 1 << AT91SAM9260_ID_US0);
	at91_sys_write(AT91_PIOB + PIO_IDR, (1<<4)|(1<<5));
	at91_sys_write(AT91_PIOB + PIO_PUER, (1<<4));
	at91_sys_write(AT91_PIOB + PIO_PUDR, (1<<5));
	at91_sys_write(AT91_PIOB + PIO_ASR, (1<<4)|(1<<5));
	at91_sys_write(AT91_PIOB + PIO_PDR, (1<<4)|(1<<5));
	uart_port_init(AT91SAM9260_BASE_US0);
	/* install interrupt handler */
	rt_hw_interrupt_install(AT91SAM9260_ID_US0, rt_serial_handler, RT_NULL);
	rt_hw_interrupt_umask(AT91SAM9260_ID_US0);
#endif
#ifdef RT_USING_UART1
	at91_sys_write(AT91_PMC_PCER, 1 << AT91SAM9260_ID_US1);
	at91_sys_write(AT91_PIOB + PIO_IDR, (1<<6)|(1<<7));
	at91_sys_write(AT91_PIOB + PIO_PUER, (1<<6));
	at91_sys_write(AT91_PIOB + PIO_PUDR, (1<<7));
	at91_sys_write(AT91_PIOB + PIO_ASR, (1<<6)|(1<<7));
	at91_sys_write(AT91_PIOB + PIO_PDR, (1<<6)|(1<<7));
	uart_port_init(AT91SAM9260_BASE_US1);
	/* install interrupt handler */
	rt_hw_interrupt_install(AT91SAM9260_ID_US1, rt_serial_handler, RT_NULL);
	rt_hw_interrupt_umask(AT91SAM9260_ID_US1);
#endif
#ifdef RT_USING_UART2
	at91_sys_write(AT91_PMC_PCER, 1 << AT91SAM9260_ID_US2);
	at91_sys_write(AT91_PIOB + PIO_IDR, (1<<8)|(1<<9));
	at91_sys_write(AT91_PIOB + PIO_PUER, (1<<8));
	at91_sys_write(AT91_PIOB + PIO_PUDR, (1<<9));
	at91_sys_write(AT91_PIOB + PIO_ASR, (1<<8)|(1<<9));
	at91_sys_write(AT91_PIOB + PIO_PDR, (1<<8)|(1<<9));
	uart_port_init(AT91SAM9260_BASE_US2);
	/* install interrupt handler */
	rt_hw_interrupt_install(AT91SAM9260_ID_US2, rt_serial_handler, RT_NULL);
	rt_hw_interrupt_umask(AT91SAM9260_ID_US2);
#endif
#ifdef RT_USING_UART3
	at91_sys_write(AT91_PMC_PCER, 1<<AT91SAM9260_ID_US3);
	at91_sys_write(AT91_PIOB + PIO_IDR, (1<<10)|(1<<11));
	at91_sys_write(AT91_PIOB + PIO_PUER, (1<<10));
	at91_sys_write(AT91_PIOB + PIO_PUDR, (1<<11));
	at91_sys_write(AT91_PIOB + PIO_ASR, (1<<10)|(1<<11));
	at91_sys_write(AT91_PIOB + PIO_PDR, (1<<10)|(1<<11));
	uart_port_init(AT91SAM9260_BASE_US3);
	/* install interrupt handler */
	rt_hw_interrupt_install(AT91SAM9260_ID_US3, rt_serial_handler, RT_NULL);
	rt_hw_interrupt_umask(AT91SAM9260_ID_US3);
	
#endif
#ifdef RT_USING_DBGU
	#define BAUDRATE  115200
	rt_uint32_t  cd;
	at91_sys_write(AT91_PIOB + PIO_IDR, (1<<14)|(1<<15));
	//at91_sys_write(AT91_PIOB + PIO_PUER, (1<<6));
	at91_sys_write(AT91_PIOB + PIO_PUDR, (1<<14)|(1<<15));
	at91_sys_write(AT91_PIOB + PIO_ASR, (1<<14)|(1<<15));
	at91_sys_write(AT91_PIOB + PIO_PDR, (1<<14)|(1<<15));
	at91_sys_write(AT91_PMC_PCER, 1 << AT91_ID_SYS);
	at91_sys_write(AT91_DBGU + AT91_US_CR, AT91_US_RSTTX | AT91_US_RSTRX | AT91_US_RXDIS | AT91_US_TXDIS);
	at91_sys_write(AT91_DBGU + AT91_US_IDR, 0xffffffff);
	at91_sys_write(AT91_DBGU + AT91_US_MR, AT91_US_USMODE_NORMAL | AT91_US_PAR_NONE);
	cd = (clk_get_rate(clk_get("mck")) / 16 + BAUDRATE/2) / BAUDRATE;
	at91_sys_write(AT91_DBGU + AT91_US_BRGR, cd);
	at91_sys_write(AT91_DBGU + AT91_US_CR, AT91_US_RXEN | AT91_US_TXEN);
	
	at91_sys_read(AT91_DBGU + AT91_US_CSR); //read for clearing interrupt
	at91_sys_write(AT91_DBGU + AT91_US_IER, 0x1);
#endif
}

#define PIT_CPIV(x)	((x) & AT91_PIT_CPIV)
#define PIT_PICNT(x)	(((x) & AT91_PIT_PICNT) >> 20)

static rt_uint32_t pit_cycle;		/* write-once */
static rt_uint32_t pit_cnt;		/* access only w/system irq blocked */

/**
 * This function will handle rtos timer
 */
void rt_timer_handler(int vector)
{
	#ifdef RT_USING_DBGU
	if (at91_sys_read(AT91_DBGU + AT91_US_CSR) & 0x1) {
		//rt_kprintf("DBGU interrupt occur\n");
		rt_hw_serial_isr(&uart0_device);
	}
	#endif
	if (at91_sys_read(AT91_PIT_SR) & AT91_PIT_PITS) {
		unsigned nr_ticks;

		/* Get number of ticks performed before irq, and ack it */
		nr_ticks = PIT_PICNT(at91_sys_read(AT91_PIT_PIVR));
		rt_tick_increase();
	}
}

static void at91sam926x_pit_reset(void)
{
	/* Disable timer and irqs */
	at91_sys_write(AT91_PIT_MR, 0);

	/* Clear any pending interrupts, wait for PIT to stop counting */
	while (PIT_CPIV(at91_sys_read(AT91_PIT_PIVR)) != 0)
		;

	/* Start PIT but don't enable IRQ */
	//at91_sys_write(AT91_PIT_MR, (pit_cycle - 1) | AT91_PIT_PITEN);
	pit_cnt += pit_cycle * PIT_PICNT(at91_sys_read(AT91_PIT_PIVR));
	at91_sys_write(AT91_PIT_MR, (pit_cycle - 1) | AT91_PIT_PITEN
			| AT91_PIT_PITIEN);
	rt_kprintf("PIT_MR=0x%08x\n", at91_sys_read(AT91_PIT_MR));
}

/*
 * Set up both clocksource and clockevent support.
 */
static void at91sam926x_pit_init(void)
{
	rt_uint32_t	pit_rate;
	rt_uint32_t	bits;

	/*
	 * Use our actual MCK to figure out how many MCK/16 ticks per
	 * 1/HZ period (instead of a compile-time constant LATCH).
	 */
	pit_rate = clk_get_rate(clk_get("mck")) / 16;
	rt_kprintf("pit_rate=%dHZ\n", pit_rate);
	pit_cycle = (pit_rate + RT_TICK_PER_SECOND/2) / RT_TICK_PER_SECOND;

	/* Initialize and enable the timer */
	at91sam926x_pit_reset();

}

/**
 * This function will init pit for system ticks
 */
 void rt_hw_timer_init()
 {
 	at91sam926x_pit_init();

	/* install interrupt handler */
	rt_hw_interrupt_install(AT91_ID_SYS, rt_timer_handler, RT_NULL);
	rt_hw_interrupt_umask(AT91_ID_SYS);

 }
 
 void at91_tc1_init()
 {
 	at91_sys_write(AT91_PMC_PCER, 1<<AT91SAM9260_ID_TC0);
 	writel(AT91_TC_TC0XC0S_NONE | AT91_TC_TC1XC1S_NONE | AT91_TC_TC2XC2S_NONE, AT91SAM9260_BASE_TCB0 + AT91_TC_BMR);
 	writel(AT91_TC_CLKDIS, AT91SAM9260_BASE_TC0 + AT91_TC_CCR);
 	writel(AT91_TC_TIMER_CLOCK4, AT91SAM9260_BASE_TC0 + AT91_TC_CMR);
 	writel(0xffff, AT91SAM9260_BASE_TC0 + AT91_TC_CV);
 }

/**
 * This function will init at91sam9260 board
 */
void rt_hw_board_init()
{
	/* initialize the system clock */
	rt_hw_clock_init();

	/* initialize uart */
	rt_hw_uart_init();

	/* initialize mmu */
	//rt_hw_mmu_init();

	/* initialize timer0 */
	rt_hw_timer_init();

}

/*@}*/
