/*
 * Misc define for GS232
 * 
 * Copyright (c) 2006-2019, RT-Thread Development Team
 * 
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 */

#ifndef __GS232_H__
#define __GS232_H__

#include <mips.h>

#define INTC_BASE			0xBFD01040

#define GS232_INTC_CELLS		5
#define GS232_NR_IRQS			(32 * GS232_INTC_CELLS)

#define GMAC0_BASE			0xBFE10000
#define GMAC0_DMA_BASE		0xBFE11000
#define GMAC1_BASE			0xBFE20000
#define GMAC1_DMA_BASE		0xBFE21000
#define I2C0_BASE			0xBFE58000
#define PWM0_BASE			0xBFE5C000
#define PWM1_BASE			0xBFE5C010
#define PWM2_BASE			0xBFE5C020
#define PWM3_BASE			0xBFE5C030
#define WDT_BASE			0xBFE5C060
#define RTC_BASE			0xBFE64000
#define I2C1_BASE			0xBFE68000
#define I2C2_BASE			0xBFE70000
#define AC97_BASE			0xBFE74000
#define NAND_BASE			0xBFE78000
#define SPI_BASE			0xBFE80000
#define CAN1_BASE			0xBF004300
#define CAN0_BASE			0xBF004400

#ifndef __ASSEMBLY__
#include <rthw.h>

/* Watch Dog registers */
#define WDT_EN				HWREG32(WDT_BASE + 0x00)
#define WDT_SET				HWREG32(WDT_BASE + 0x04)
#define WDT_TIMER			HWREG32(WDT_BASE + 0x08)

#define PLL_FREQ 			HWREG32(0xbfe78030)
#define PLL_DIV_PARAM 		HWREG32(0xbfe78034)

struct gs232_intc_regs
{
    volatile unsigned int int_isr;
    volatile unsigned int int_en;
    volatile unsigned int int_set;
    volatile unsigned int int_clr;        /* offset 0x10*/
    volatile unsigned int int_pol;
    volatile unsigned int int_edge;        /* offset 0 */
}; 

extern void rt_hw_timer_init(void);

#endif

#endif