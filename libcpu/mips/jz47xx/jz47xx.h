#ifndef __JZ47XX_H__
#define __JZ47XX_H__

#define __REG8(addr)	*((volatile unsigned char *)(addr))
#define __REG16(addr)	*((volatile unsigned short *)(addr))
#define __REG32(addr)	*((volatile unsigned int *)(addr))

#define	HARB_BASE	0xB3000000
#define	EMC_BASE	0xB3010000
#define	DMAC_BASE	0xB3020000
#define	UHC_BASE	0xB3030000
#define	UDC_BASE	0xB3040000
#define	LCD_BASE	0xB3050000
#define	CIM_BASE	0xB3060000
#define	ETH_BASE	0xB3100000
#define	NBM_BASE	0xB3F00000

#define	CPM_BASE	0xB0000000
#define	INTC_BASE	0xB0001000
#define	OST_BASE	0xB0002000
#define	RTC_BASE	0xB0003000
#define	WDT_BASE	0xB0004000
#define	GPIO_BASE	0xB0010000
#define	AIC_BASE	0xB0020000
#define	MSC_BASE	0xB0021000
#define	UART0_BASE	0xB0030000
#define	UART1_BASE	0xB0031000
#define	UART2_BASE	0xB0032000
#define	UART3_BASE	0xB0033000
#define	FIR_BASE	0xB0040000
#define	SCC_BASE	0xB0041000
#define	SCC0_BASE	0xB0041000
#define	I2C_BASE	0xB0042000
#define	SSI_BASE	0xB0043000
#define	SCC1_BASE	0xB0044000
#define	PWM0_BASE	0xB0050000
#define	PWM1_BASE	0xB0051000
#define	DES_BASE	0xB0060000
#define	UPRT_BASE	0xB0061000
#define KBC_BASE	0xB0062000

/* uart offset */
#define UART_RDR(base)		__REG8((base) + 0x00)	/* R  8b H'xx */
#define UART_TDR(base)		__REG8((base) + 0x00)	/* W  8b H'xx */
#define UART_DLLR(base)		__REG8((base) + 0x00)	/* RW 8b H'00 */
#define UART_DLHR(base)		__REG8((base) + 0x04)	/* RW 8b H'00 */
#define UART_IER(base)		__REG8((base) + 0x04)	/* RW 8b H'00 */
#define UART_ISR(base)		__REG8((base) + 0x08)	/* R  8b H'01 */
#define UART_FCR(base)		__REG8((base) + 0x08)	/* W  8b H'00 */
#define UART_LCR(base)		__REG8((base) + 0x0C)	/* RW 8b H'00 */
#define UART_MCR(base)		__REG8((base) + 0x10)	/* RW 8b H'00 */
#define UART_LSR(base)		__REG8((base) + 0x14)	/* R  8b H'00 */
#define UART_MSR(base)		__REG8((base) + 0x18)	/* R  8b H'00 */
#define UART_SPR(base)		__REG8((base) + 0x1C)	/* RW 8b H'00 */
#define UART_MCR(base)		__REG8((base) + 0x10)	/* RW 8b H'00 */
#define UART_SIRCR(base)	__REG8((base) + 0x20)	/* RW 8b H'00 */

/* interrupt controller */
#define INTC_ISR			__REG32(INTC_BASE + 0x00)
#define INTC_IMR			__REG32(INTC_BASE + 0x04)
#define INTC_IMSR			__REG32(INTC_BASE + 0x08)
#define INTC_IMCR			__REG32(INTC_BASE + 0x0c)
#define INTC_IPR			__REG32(INTC_BASE + 0x10)

#define IRQ_I2C		1
#define IRQ_PS2		2
#define IRQ_UPRT	3
#define IRQ_CORE	4
#define IRQ_UART3	6
#define IRQ_UART2	7
#define IRQ_UART1	8
#define IRQ_UART0	9
#define IRQ_SCC1	10
#define IRQ_SCC0	11
#define IRQ_UDC		12
#define IRQ_UHC		13
#define IRQ_MSC		14
#define IRQ_RTC		15
#define IRQ_FIR		16
#define IRQ_SSI		17
#define IRQ_CIM		18
#define IRQ_ETH		19
#define IRQ_AIC		20
#define IRQ_DMAC	21
#define IRQ_OST2	22
#define IRQ_OST1	23
#define IRQ_OST0	24
#define IRQ_GPIO3	25
#define IRQ_GPIO2	26
#define IRQ_GPIO1	27
#define IRQ_GPIO0	28
#define IRQ_LCD		30

#define SYSTEM_STACK          0x8000ffe8		/* the kernel system stack address */

#endif
