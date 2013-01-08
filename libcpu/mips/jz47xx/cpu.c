/*
 * File      : cpu.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-07-09     Bernard      first version
 * 2010-09-11     Bernard      add CPU reset implementation
 */
#include <rtthread.h>
#include <jz4755.h>

/* Watchdog definitions */
#define	WDT_CLK_PRESCALE_CLK1			( 0x0 << 3)
#define	WDT_CLK_PRESCALE_CLK4			( 0x1 << 3)
#define	WDT_CLK_PRESCALE_CLK16			( 0x2 << 3)
#define	WDT_CLK_PRESCALE_CLK64			( 0x3 << 3)
#define	WDT_CLK_PRESCALE_CLK256			( 0x4 << 3)
#define	WDT_CLK_PRESCALE_CLK1024		( 0x5 << 3)
#define	WDT_CLK_PRESCALE_MASK			( 0x3F << 3)

#define	WDT_CLK_EXTAL					( 0x1 << 2)
#define	WDT_CLK_RTC						( 0x1 << 1)
#define	WDT_CLK_PCLK					( 0x1 << 0)
#define	WDT_CLK_MASK					( 7 )

#define	WDT_ENABLE			( 1 << 0 )

/**
 * @addtogroup Jz47xx
 */
/*@{*/

/**
 * this function will reset CPU
 *
 */
void rt_hw_cpu_reset()
{
	/* open the watch-dog */
	WDT_TCSR = WDT_CLK_EXTAL;
	WDT_TCSR |= WDT_CLK_PRESCALE_CLK1024;
	WDT_TDR  = 0x03;
	WDT_TCNT = 0x00;
	WDT_TCER |= WDT_ENABLE;

	rt_kprintf("reboot system...\n");
	while (1);
}

/**
 * this function will shutdown CPU
 *
 */
void rt_hw_cpu_shutdown()
{
	rt_kprintf("shutdown...\n");

	while (1);
}

/*@}*/

