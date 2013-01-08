#ifndef __JZ4740_H__
#define __JZ4740_H__

#include "jz47xx.h"

#define	WDT_BASE	0xB0002000

/* Watchdog */
#define WDT_TDR		__REG16(WDT_BASE + 0x00)	/* Watchdog Timer Data Register */
#define WDT_TCER	__REG8(WDT_BASE + 0x04)		/* Watchdog Counter Enable Register */
#define WDT_TCNT	__REG16(WDT_BASE + 0x08)	/* Watchdog Timer Counter Register */
#define WDT_TCSR	__REG16(WDT_BASE + 0x0C)	/* Watchdog Timer Control Register */

/* Clock Gate Register Definitions */
#define CPM_CLKGR_UART1   (1 << 15)
#define CPM_CLKGR_UHC     (1 << 14)
#define CPM_CLKGR_IPU     (1 << 13)
#define CPM_CLKGR_DMAC    (1 << 12)
#define CPM_CLKGR_UDC     (1 << 11)
#define CPM_CLKGR_LCD     (1 << 10)
#define CPM_CLKGR_CIM     (1 << 9)
#define CPM_CLKGR_SADC    (1 << 8)
#define CPM_CLKGR_MSC     (1 << 7)
#define CPM_CLKGR_AIC1    (1 << 6)
#define CPM_CLKGR_AIC2    (1 << 5)
#define CPM_CLKGR_SSI     (1 << 4)
#define CPM_CLKGR_I2C     (1 << 3)
#define CPM_CLKGR_RTC     (1 << 2)
#define CPM_CLKGR_TCU     (1 << 1)
#define CPM_CLKGR_UART0   (1 << 0)

/* Interrupt Definitions */
#define IRQ_I2C		1
#define IRQ_UHC		3
#define IRQ_UART0	9
#define IRQ_SADC	12
#define IRQ_MSC		14
#define IRQ_RTC		15
#define IRQ_SSI		16
#define IRQ_CIM		17
#define IRQ_AIC		18
#define IRQ_ETH		19
#define IRQ_DMAC	20
#define IRQ_TCU2	21
#define IRQ_TCU1	22
#define IRQ_TCU0	23
#define IRQ_UDC		24
#define IRQ_GPIO3	25
#define IRQ_GPIO2	26
#define IRQ_GPIO1	27
#define IRQ_GPIO0	28
#define IRQ_IPU		29
#define IRQ_LCD		30

#endif
