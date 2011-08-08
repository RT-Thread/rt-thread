/*
 * File      : ls1b.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2011, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-08-08     lgnq         first version
 */
#ifndef __LS1B_H__
#define __LS1B_H__

#include "../common/mipsregs.h"

#define LS1B_ACPI_IRQ	0
#define LS1B_HPET_IRQ	1
#define LS1B_UART0_IRQ	2
#define LS1B_UART1_IRQ	3
#define LS1B_UART2_IRQ	4
#define LS1B_UART3_IRQ	5
#define LS1B_CAN0_IRQ	6
#define LS1B_CAN1_IRQ	7
#define LS1B_SPI0_IRQ	8
#define LS1B_SPI1_IRQ	9
#define LS1B_AC97_IRQ	10
#define LS1B_MS_IRQ		11
#define LS1B_KB_IRQ		12
#define LS1B_DMA0_IRQ	13
#define LS1B_DMA1_IRQ	14
#define LS1B_NAND_IRQ	15
#define LS1B_I2C0_IRQ	16
#define LS1B_I2C1_IRQ	17
#define LS1B_PWM0_IRQ	18
#define LS1B_PWM1_IRQ	19
#define LS1B_PWM2_IRQ	20
#define LS1B_PWM3_IRQ	21
#define LS1B_LPC_IRQ	22
#define LS1B_EHCI_IRQ	32
#define LS1B_OHCI_IRQ	33
#define LS1B_GMAC1_IRQ	34
#define LS1B_GMAC2_IRQ	35
#define LS1B_SATA_IRQ	36
#define LS1B_GPU_IRQ	37
#define LS1B_PCI_INTA_IRQ 38
#define LS1B_PCI_INTB_IRQ 39
#define LS1B_PCI_INTC_IRQ 40
#define LS1B_PCI_INTD_IRQ 41

#define LS1B_GPIO_IRQ 64
#define LS1B_GPIO_FIRST_IRQ 64
#define LS1B_GPIO_IRQ_COUNT 96
#define LS1B_GPIO_LAST_IRQ  (LS1B_GPIO_FIRST_IRQ + LS1B_GPIO_IRQ_COUNT-1)

#define INT_PCI_INTA	(1<<6)
#define INT_PCI_INTB	(1<<7)
#define INT_PCI_INTC	(1<<8)
#define INT_PCI_INTD	(1<<9)

#define LS1B_LAST_IRQ 159
#define MIPS_CPU_TIMER_IRQ	167
#define LS1B_INTREG_BASE 0xbfd01040

#define LS1B_DMA_IRQ_BASE 168
#define LS1B_DMA_IRQ_COUNT 16

struct ls1b_intc_regs
{
	volatile unsigned int int_isr;
	volatile unsigned int int_en;
	volatile unsigned int int_set;
	volatile unsigned int int_clr;		/* offset 0x10*/
	volatile unsigned int int_pol;
   	volatile unsigned int int_edge;		/* offset 0 */
}; 

struct ls1b_cop_global_regs
{
	volatile unsigned int control;
	volatile unsigned int rd_inten;
	volatile unsigned int wr_inten;
	volatile unsigned int rd_intisr;		/* offset 0x10*/
	volatile unsigned int wr_intisr;
	unsigned int unused[11];
} ; 

struct ls1b_cop_channel_regs
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

struct ls1b_cop_regs
{
	struct ls1b_cop_global_regs global;
	struct ls1b_cop_channel_regs chan[8][2];
} ;

#define __REG8(addr)		*((volatile unsigned char *)(addr))
#define __REG16(addr)		*((volatile unsigned short *)(addr))
#define __REG32(addr)		*((volatile unsigned int *)(addr))

#define GMAC0_BASE			0xBFE10000
#define GMAC0_DMA_BASE		0xBFE11000
#define GMAC1_BASE			0xBFE20000
#define GMAC1_DMA_BASE		0xBFE21000
#define UART0_BASE			0xBFE40000
#define UART0_1_BASE		0xBFE41000
#define UART0_2_BASE		0xBFE42000
#define UART0_3_BASE		0xBFE43000
#define UART1_BASE			0xBFE44000
#define UART1_1_BASE		0xBFE45000
#define UART1_2_BASE		0xBFE46000
#define UART1_3_BASE		0xBFE47000
#define UART2_BASE			0xBFE48000
#define UART3_BASE			0xBFE4C000
#define I2C0_BASE			0xBFE58000
#define PWM0_BASE			0xBFE5C000
#define PWM1_BASE			0xBFE5C010
#define PWM2_BASE			0xBFE5C020
#define PWM3_BASE			0xBFE5C030
#define WDT_BASE			0xBFE5C060
#define RTC_BASE			0xBFE64000
#define I2C1_BASE			0xBFE68000
#define UART4_BASE			0xBFE6C000
#define I2C2_BASE			0xBFE70000
#define AC97_BASE			0xBFE74000
#define NAND_BASE			0xBFE78000
#define UART5_BASE			0xBFE7C000
#define SPI_BASE			0xBFE80000
#define CAN1_BASE			0xBF004300
#define CAN0_BASE			0xBF004400

#define DC_BASE				0xBC301240  //Display Control

/* UART registers */
#define UART_DAT(base)		__REG8(base + 0x00)
#define UART_IER(base)		__REG8(base + 0x01)
#define UART_IIR(base)		__REG8(base + 0x02)
#define UART_FCR(base)		__REG8(base + 0x02)
#define UART_LCR(base)		__REG8(base + 0x03)
#define UART_MCR(base)		__REG8(base + 0x04)
#define UART_LSR(base)		__REG8(base + 0x05)
#define UART_MSR(base)		__REG8(base + 0x06)

#define UART_LSB(base)		__REG8(base + 0x00)
#define UART_MSB(base)		__REG8(base + 0x01)

/* UART0 registers */
#define UART0_DAT			__REG8(UART0_BASE + 0x00)
#define UART0_IER			__REG8(UART0_BASE + 0x01)
#define UART0_IIR			__REG8(UART0_BASE + 0x02)
#define UART0_FCR			__REG8(UART0_BASE + 0x02)
#define UART0_LCR			__REG8(UART0_BASE + 0x03)
#define UART0_MCR			__REG8(UART0_BASE + 0x04)
#define UART0_LSR			__REG8(UART0_BASE + 0x05)
#define UART0_MSR			__REG8(UART0_BASE + 0x06)

#define UART0_LSB			__REG8(UART0_BASE + 0x00)
#define UART0_MSB			__REG8(UART0_BASE + 0x01)

/* UART1 registers */
#define UART1_DAT			__REG8(UART1_BASE + 0x00)
#define UART1_IER			__REG8(UART1_BASE + 0x01)
#define UART1_IIR			__REG8(UART1_BASE + 0x02)
#define UART1_FCR			__REG8(UART1_BASE + 0x02)
#define UART1_LCR			__REG8(UART1_BASE + 0x03)
#define UART1_MCR			__REG8(UART1_BASE + 0x04)
#define UART1_LSR			__REG8(UART1_BASE + 0x05)
#define UART1_MSR			__REG8(UART1_BASE + 0x06)

#define UART1_LSB			__REG8(UART1_BASE + 0x00)
#define UART1_MSB			__REG8(UART1_BASE + 0x01)

/* Watch Dog registers */
#define WDT_EN				__REG32(WDT_BASE + 0x00)
#define WDT_SET				__REG32(WDT_BASE + 0x04)
#define WDT_TIMER			__REG32(WDT_BASE + 0x08)

/* Frame Buffer registers */
#define DC_FB_CONFIG			__REG32(DC_BASE + 0x000)
#define DC_FB_BUFFER_ADDR0		__REG32(DC_BASE + 0x020)
#define DC_FB_BUFFER_STRIDE		__REG32(DC_BASE + 0x040)
#define DC_FB_BUFFER_ORIGIN		__REG32(DC_BASE + 0x060)
#define DC_DITHER_CONFIG		__REG32(DC_BASE + 0x120)
#define DC_DITHER_TABLE_LOW		__REG32(DC_BASE + 0x140)
#define DC_DITHER_TABLE_HIGH	__REG32(DC_BASE + 0x160)
#define DC_PANEL_CONFIG			__REG32(DC_BASE + 0x180)
#define DC_PANEL_TIMING			__REG32(DC_BASE + 0x1A0)
#define DC_HDISPLAY				__REG32(DC_BASE + 0x1C0)
#define DC_HSYNC				__REG32(DC_BASE + 0x1E0)
#define DC_VDISPLAY				__REG32(DC_BASE + 0x240)
#define DC_VSYNC				__REG32(DC_BASE + 0x260)
#define DC_FB_BUFFER_ADDR1		__REG32(DC_BASE + 0x340)

#define PLL_FREQ 				__REG32(0xbfe78030)
#define PLL_DIV_PARAM 			__REG32(0xbfe78034)

#endif
