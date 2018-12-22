/*
 * File      : ls1c.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2011, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date               Author             Notes
 * 2011-08-08     lgnq                first version
 * 2015-07-06     chinesebear      modified for loongson 1c
 */

#ifndef __LS1C_H__
#define __LS1C_H__

#include "../common/mipsregs.h"

#define LS1C_ACPI_IRQ	0
#define LS1C_HPET_IRQ	1
//#define LS1C_UART0_IRQ	3  // linux中是3，v1.4版本的1c手册中是2，暂屏蔽，待确认
#define LS1C_UART1_IRQ	4
#define LS1C_UART2_IRQ	5
#define LS1C_CAN0_IRQ	6
#define LS1C_CAN1_IRQ	7
#define LS1C_SPI0_IRQ	8
#define LS1C_SPI1_IRQ	9
#define LS1C_AC97_IRQ	10
#define LS1C_MS_IRQ		11
#define LS1C_KB_IRQ		12
#define LS1C_DMA0_IRQ	13
#define LS1C_DMA1_IRQ	14
#define LS1C_DMA2_IRQ   15
#define LS1C_NAND_IRQ	16
#define LS1C_PWM0_IRQ	17
#define LS1C_PWM1_IRQ	18
#define LS1C_PWM2_IRQ	19
#define LS1C_PWM3_IRQ	20
#define LS1C_RTC_INT0_IRQ  21
#define LS1C_RTC_INT1_IRQ  22
#define LS1C_RTC_INT2_IRQ  23
#define LS1C_UART3_IRQ  29
#define LS1C_ADC_IRQ    30
#define LS1C_SDIO_IRQ   31


#define LS1C_EHCI_IRQ	(32+0)
#define LS1C_OHCI_IRQ	(32+1)
#define LS1C_OTG_IRQ    (32+2)
#define LS1C_MAC_IRQ    (32+3)
#define LS1C_CAM_IRQ    (32+4)
#define LS1C_UART4_IRQ  (32+5)
#define LS1C_UART5_IRQ  (32+6)
#define LS1C_UART6_IRQ  (32+7)
#define LS1C_UART7_IRQ  (32+8)
#define LS1C_UART8_IRQ  (32+9)
#define LS1C_UART9_IRQ  (32+13)
#define LS1C_UART10_IRQ (32+14)
#define LS1C_UART11_IRQ (32+15)
#define LS1C_I2C2_IRQ   (32+17)
#define LS1C_I2C1_IRQ   (32+18)
#define LS1C_I2C0_IRQ   (32+19)


#define LS1C_GPIO_IRQ 64
#define LS1C_GPIO_FIRST_IRQ 64
#define LS1C_GPIO_IRQ_COUNT 96
#define LS1C_GPIO_LAST_IRQ  (LS1C_GPIO_FIRST_IRQ + LS1C_GPIO_IRQ_COUNT-1)


#define LS1C_LAST_IRQ 159
#define LS1C_INTREG_BASE 0xbfd01040

// 龙芯1c的中断分为五组，每组32个
#define LS1C_NR_IRQS    (32*5)


// GPIO编号和中断号之间的互相转换
#define LS1C_GPIO_TO_IRQ(GPIOn)     (LS1C_GPIO_FIRST_IRQ + (GPIOn))
#define LS1C_IRQ_TO_GPIO(IRQn)      ((IRQn) - LS1C_GPIO_FIRST_IRQ)


struct ls1c_intc_regs
{
	volatile unsigned int int_isr;
	volatile unsigned int int_en;
	volatile unsigned int int_set;
	volatile unsigned int int_clr;		/* offset 0x10*/
	volatile unsigned int int_pol;
   	volatile unsigned int int_edge;		/* offset 0 */
}; 

struct ls1c_cop_global_regs
{
	volatile unsigned int control;
	volatile unsigned int rd_inten;
	volatile unsigned int wr_inten;
	volatile unsigned int rd_intisr;		/* offset 0x10*/
	volatile unsigned int wr_intisr;
	unsigned int unused[11];
} ; 

struct ls1c_cop_channel_regs
{
	volatile unsigned int rd_control;
	volatile unsigned int rd_src;
	volatile unsigned int rd_cnt;
	volatile unsigned int rd_status;		/* offset 0x10*/
	volatile unsigned int wr_control;
	volatile unsigned int wr_src;
	volatile unsigned int wr_cnt;
	volatile unsigned int wr_status;		/* offset 0x10*/
} ; 

struct ls1c_cop_regs
{
	struct ls1c_cop_global_regs global;
	struct ls1c_cop_channel_regs chan[8][2];
} ;

#define __REG8(addr)		*((volatile unsigned char *)(addr))
#define __REG16(addr)		*((volatile unsigned short *)(addr))
#define __REG32(addr)		*((volatile unsigned int *)(addr))

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

/* Watch Dog registers */
#define WDT_EN				__REG32(WDT_BASE + 0x00)
#define WDT_SET				__REG32(WDT_BASE + 0x04)
#define WDT_TIMER			__REG32(WDT_BASE + 0x08)

#define PLL_FREQ 				__REG32(0xbfe78030)
#define PLL_DIV_PARAM 			__REG32(0xbfe78034)

#endif

