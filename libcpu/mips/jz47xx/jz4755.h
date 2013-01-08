#ifndef __JZ4755_H__
#define __JZ4755_H__

#include "jz47xx.h"

#define	WDT_BASE	0xB0002000
#define	OST_BASE	0xB00020e0

/* Watchdog */
#define WDT_TDR		__REG16(WDT_BASE + 0x00)	/* Watchdog Timer Data Register */
#define WDT_TCER	__REG8(WDT_BASE + 0x04)		/* Watchdog Counter Enable Register */
#define WDT_TCNT	__REG16(WDT_BASE + 0x08)	/* Watchdog Timer Counter Register */
#define WDT_TCSR	__REG16(WDT_BASE + 0x0C)	/* Watchdog Timer Control Register */

/* OS Timer */
#define OST_DR		__REG32(OST_BASE + 0x00)	/* OS Timer Data Register */
#define OST_CNT		__REG32(OST_BASE + 0x08)	/* OS Timer Counter Register */
#define OST_CSR		__REG16(OST_BASE + 0x0C)	/* OS Timer Control Register */

/* OST Register Definitions */
#define OST_TCSR_EXT_EN		( 0x1 << 2)
#define OST_TCSR_RTC_EN		( 0x1 << 1)
#define OST_TCSR_PCLK_EN	( 0x1 << 0)

/* Clock Gate Register Definitions */
#define CPM_CLKGR_AUX_CPU      ( 1 << 24 )
#define CPM_CLKGR_AHB1         ( 1 << 23 )
#define CPM_CLKGR_IDCT         ( 1 << 22 )
#define CPM_CLKGR_DB           ( 1 << 21 )
#define CPM_CLKGR_ME           ( 1 << 20 )
#define CPM_CLKGR_MC           ( 1 << 19 )
#define CPM_CLKGR_TVE          ( 1 << 18 )
#define CPM_CLKGR_TSSI         ( 1 << 17 )
#define CPM_CLKGR_MSC1         ( 1 << 16 )
#define CPM_CLKGR_UART2        ( 1 << 15 )
#define CPM_CLKGR_UART1        ( 1 << 14 )
#define CPM_CLKGR_IPU          ( 1 << 13 )
#define CPM_CLKGR_DMAC         ( 1 << 12 )
#define CPM_CLKGR_BCH          ( 1 << 11 )
#define CPM_CLKGR_UDC          ( 1 << 10 )
#define CPM_CLKGR_LCD          ( 1 << 9 )
#define CPM_CLKGR_CIM          ( 1 << 8 )
#define CPM_CLKGR_SADC         ( 1 << 7 )
#define CPM_CLKGR_MSC0         ( 1 << 6 )
#define CPM_CLKGR_AIC          ( 1 << 5 )
#define CPM_CLKGR_SSI1         ( 1 << 4 )
#define CPM_CLKGR_I2C          ( 1 << 3 )
#define CPM_CLKGR_RTC          ( 1 << 2 )
#define CPM_CLKGR_TCU          ( 1 << 1 )
#define CPM_CLKGR_UART0        ( 1 << 0 )

/* Interrupt Definitions */
#define IRQ_ETH		0
#define IRQ_SFT		4
#define IRQ_I2C		5
#define IRQ_RTC		6
#define IRQ_UART2	7
#define IRQ_UART1	8
#define IRQ_UART0	9
#define IRQ_AIC		10
#define IRQ_GPIO5	11
#define IRQ_GPIO4	12
#define IRQ_GPIO3	13
#define IRQ_GPIO2	14
#define IRQ_GPIO1	15
#define IRQ_GPIO0	16
#define IRQ_BCH		17
#define IRQ_SADC	18
#define IRQ_CIM		19
#define IRQ_TSSI	20
#define IRQ_TCU2	21
#define IRQ_TCU1	22
#define IRQ_TCU0	23
#define IRQ_MSC1	24
#define IRQ_MSC0	25
#define IRQ_SSI		26
#define IRQ_UDC		27
#define IRQ_DMA1	28		/* Used for DMA channel 4-7 */
#define IRQ_DMA0	29		/* Used for DMA channel 0-3 */
#define IRQ_IPU		30
#define IRQ_LCD		31

#endif
