#ifndef __JZ47XX_H__
#define __JZ47XX_H__

#include "../common/mipsregs.h"

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
#define TCU_BASE	0xB0002000
#define	RTC_BASE	0xB0003000
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

/* CPM Register */
#define CPM_CPCCR			__REG32(CPM_BASE + 0x00)	/* Clock Control Register */
#define CPM_LCR				__REG32(CPM_BASE + 0x04)	/* Low Power Control Register */
#define CPM_RSR				__REG32(CPM_BASE + 0x08)	/* Reset Status Register */
#define CPM_CPPCR			__REG32(CPM_BASE + 0x10)	/* PLL Control Register */
#define CPM_CPPSR			__REG32(CPM_BASE + 0x14)	/* PLL Switch and Status Register */
#define CPM_CLKGR			__REG32(CPM_BASE + 0x20)	/* Clock Gate Register */
#define CPM_OPCR			__REG32(CPM_BASE + 0x24)	/* Osillator and Power Control Register */
#define CPM_I2SCDR			__REG32(CPM_BASE + 0x60)	/* I2S Device Clock Divider Register */
#define CPM_LPCDR			__REG32(CPM_BASE + 0x64)	/* LCD Pixel Clock Divider Register */
#define CPM_MSCCDR			__REG32(CPM_BASE + 0x68)	/* MSC Clock Divider Register */
#define CPM_SSICDR			__REG32(CPM_BASE + 0x74)	/* SSI Clock Divider Register */
#define CPM_CIMCDR			__REG32(CPM_BASE + 0x7C)	/* CIM MCLK Clock Divider Register */

/* Interrupt Controller Regester */
#define INTC_ISR			__REG32(INTC_BASE + 0x00)
#define INTC_IMR			__REG32(INTC_BASE + 0x04)
#define INTC_IMSR			__REG32(INTC_BASE + 0x08)
#define INTC_IMCR			__REG32(INTC_BASE + 0x0c)
#define INTC_IPR			__REG32(INTC_BASE + 0x10)

/* TCU Register */
#define TCU_TSTR			__REG32(TCU_BASE + 0xF0)
#define TCU_TSTSR			__REG32(TCU_BASE + 0xF4)
#define TCU_TSTCR			__REG32(TCU_BASE + 0xF8)
#define TCU_TSR				__REG32(TCU_BASE + 0x1C)
#define TCU_TSSR			__REG32(TCU_BASE + 0x2C)
#define TCU_TSCR			__REG32(TCU_BASE + 0x3C)
#define TCU_TER				__REG32(TCU_BASE + 0x10)
#define TCU_TESR			__REG32(TCU_BASE + 0x14)
#define TCU_TECR			__REG32(TCU_BASE + 0x18)
#define TCU_TFR				__REG32(TCU_BASE + 0x20)
#define TCU_TFSR			__REG32(TCU_BASE + 0x24)
#define TCU_TFCR			__REG32(TCU_BASE + 0x28)
#define TCU_TMR				__REG32(TCU_BASE + 0x30)
#define TCU_TMSR			__REG32(TCU_BASE + 0x34)
#define TCU_TMCR			__REG32(TCU_BASE + 0x38)
#define TCU_TDFR0_OFFSET	0x40
#define TCU_TDFR(x)			__REG16(TCU_BASE + (x) * 0x10 + TCU_TDFR0_OFFSET)
#define TCU_TDHR0_OFFSET	0x44
#define TCU_TDHR(x)			__REG16(TCU_BASE + (x) * 0x10 + TCU_TDHR0_OFFSET)
#define TCU_TCNT0_OFFSET	0x48
#define TCU_TCNT(x)			__REG16(TCU_BASE + (x) * 0x10 + TCU_TCNT0_OFFSET)
#define TCU_TCSR0_OFFSET	0x4C
#define TCU_TCSR(x)			__REG16(TCU_BASE + (x) * 0x10 + TCU_TCSR0_OFFSET)

/* TCU Register Definitions */
#define TCU_TCSR_PWM_SD         (1 << 9)
#define TCU_TCSR_PWM_INITL_HIGH (1 << 8)
#define TCU_TCSR_PWM_EN         (1 << 7)
#define TCU_TCSR_PRESCALE_BIT   3
#define TCU_TCSR_PRESCALE_MASK  (0x7 << TCU_TCSR_PRESCALE_BIT)
#define TCU_TCSR_PRESCALE1      (0x0 << TCU_TCSR_PRESCALE_BIT)
#define TCU_TCSR_PRESCALE4      (0x1 << TCU_TCSR_PRESCALE_BIT)
#define TCU_TCSR_PRESCALE16     (0x2 << TCU_TCSR_PRESCALE_BIT)
#define TCU_TCSR_PRESCALE64     (0x3 << TCU_TCSR_PRESCALE_BIT)
#define TCU_TCSR_PRESCALE256    (0x4 << TCU_TCSR_PRESCALE_BIT)
#define TCU_TCSR_PRESCALE1024   (0x5 << TCU_TCSR_PRESCALE_BIT)
#define TCU_TCSR_EXT_EN         (1 << 2)
#define TCU_TCSR_RTC_EN         (1 << 1)
#define TCU_TCSR_PCK_EN         (1 << 0)

#define TCU_TER_OSTEN   (1 << 15)
#define TCU_TER_TCEN5   (1 << 5)
#define TCU_TER_TCEN4   (1 << 4)
#define TCU_TER_TCEN3   (1 << 3)
#define TCU_TER_TCEN2   (1 << 2)
#define TCU_TER_TCEN1   (1 << 1)
#define TCU_TER_TCEN0   (1 << 0)

#define TCU_TESR_OSTST  (1 << 15)
#define TCU_TESR_TCST5  (1 << 5)
#define TCU_TESR_TCST4  (1 << 4)
#define TCU_TESR_TCST3  (1 << 3)
#define TCU_TESR_TCST2  (1 << 2)
#define TCU_TESR_TCST1  (1 << 1)
#define TCU_TESR_TCST0  (1 << 0)

#define TCU_TECR_OSTCL  (1 << 15)
#define TCU_TECR_TCCL5  (1 << 5)
#define TCU_TECR_TCCL4  (1 << 4)
#define TCU_TECR_TCCL3  (1 << 3)
#define TCU_TECR_TCCL2  (1 << 2)
#define TCU_TECR_TCCL1  (1 << 1)
#define TCU_TECR_TCCL0  (1 << 0)

#define TCU_TFR_HFLAG5  (1 << 21)
#define TCU_TFR_HFLAG4  (1 << 20)
#define TCU_TFR_HFLAG3  (1 << 19)
#define TCU_TFR_HFLAG2  (1 << 18)
#define TCU_TFR_HFLAG1  (1 << 17)
#define TCU_TFR_HFLAG0  (1 << 16)
#define TCU_TFR_FFLAG5  (1 << 5)
#define TCU_TFR_FFLAG4  (1 << 4)
#define TCU_TFR_FFLAG3  (1 << 3)
#define TCU_TFR_FFLAG2  (1 << 2)
#define TCU_TFR_FFLAG1  (1 << 1)
#define TCU_TFR_FFLAG0  (1 << 0)

#define TCU_TFSR_HFLAG5 (1 << 21)
#define TCU_TFSR_HFLAG4 (1 << 20)
#define TCU_TFSR_HFLAG3 (1 << 19)
#define TCU_TFSR_HFLAG2 (1 << 18)
#define TCU_TFSR_HFLAG1 (1 << 17)
#define TCU_TFSR_HFLAG0 (1 << 16)
#define TCU_TFSR_OSTFLAG (1 << 15)
#define TCU_TFSR_FFLAG5 (1 << 5)
#define TCU_TFSR_FFLAG4 (1 << 4)
#define TCU_TFSR_FFLAG3 (1 << 3)
#define TCU_TFSR_FFLAG2 (1 << 2)
#define TCU_TFSR_FFLAG1 (1 << 1)
#define TCU_TFSR_FFLAG0 (1 << 0)

#define TCU_TFCR_HFLAG5 (1 << 21)
#define TCU_TFCR_HFLAG4 (1 << 20)
#define TCU_TFCR_HFLAG3 (1 << 19)
#define TCU_TFCR_HFLAG2 (1 << 18)
#define TCU_TFCR_HFLAG1 (1 << 17)
#define TCU_TFCR_HFLAG0 (1 << 16)
#define TCU_TFCR_OSTFLAG (1 << 15)
#define TCU_TFCR_FFLAG5 (1 << 5)
#define TCU_TFCR_FFLAG4 (1 << 4)
#define TCU_TFCR_FFLAG3 (1 << 3)
#define TCU_TFCR_FFLAG2 (1 << 2)
#define TCU_TFCR_FFLAG1 (1 << 1)
#define TCU_TFCR_FFLAG0 (1 << 0)

#define TCU_TMR_HMASK5  (1 << 21)
#define TCU_TMR_HMASK4  (1 << 20)
#define TCU_TMR_HMASK3  (1 << 19)
#define TCU_TMR_HMASK2  (1 << 18)
#define TCU_TMR_HMASK1  (1 << 17)
#define TCU_TMR_HMASK0  (1 << 16)
#define TCU_TMR_OSTMASK (1 << 15)
#define TCU_TMR_FMASK5  (1 << 5)
#define TCU_TMR_FMASK4  (1 << 4)
#define TCU_TMR_FMASK3  (1 << 3)
#define TCU_TMR_FMASK2  (1 << 2)
#define TCU_TMR_FMASK1  (1 << 1)
#define TCU_TMR_FMASK0  (1 << 0)

#define TCU_TMSR_HMST5  (1 << 21)
#define TCU_TMSR_HMST4  (1 << 20)
#define TCU_TMSR_HMST3  (1 << 19)
#define TCU_TMSR_HMST2  (1 << 18)
#define TCU_TMSR_HMST1  (1 << 17)
#define TCU_TMSR_HMST0  (1 << 16)
#define TCU_TMSR_OSTMST (1 << 15)
#define TCU_TMSR_FMST5  (1 << 5)
#define TCU_TMSR_FMST4  (1 << 4)
#define TCU_TMSR_FMST3  (1 << 3)
#define TCU_TMSR_FMST2  (1 << 2)
#define TCU_TMSR_FMST1  (1 << 1)
#define TCU_TMSR_FMST0  (1 << 0)

#define TCU_TMCR_HMCL5  (1 << 21)
#define TCU_TMCR_HMCL4  (1 << 20)
#define TCU_TMCR_HMCL3  (1 << 19)
#define TCU_TMCR_HMCL2  (1 << 18)
#define TCU_TMCR_HMCL1  (1 << 17)
#define TCU_TMCR_HMCL0  (1 << 16)
#define TCU_TMCR_OSTMCL (1 << 15)
#define TCU_TMCR_FMCL5  (1 << 5)
#define TCU_TMCR_FMCL4  (1 << 4)
#define TCU_TMCR_FMCL3  (1 << 3)
#define TCU_TMCR_FMCL2  (1 << 2)
#define TCU_TMCR_FMCL1  (1 << 1)
#define TCU_TMCR_FMCL0  (1 << 0)

#define TCU_TSR_WDTS    (1 << 16)
#define TCU_TSR_STOP5   (1 << 5)
#define TCU_TSR_STOP4   (1 << 4)
#define TCU_TSR_STOP3   (1 << 3)
#define TCU_TSR_STOP2   (1 << 2)
#define TCU_TSR_STOP1   (1 << 1)
#define TCU_TSR_STOP0   (1 << 0)

#define TCU_TSSR_WDTSS  (1 << 16)
#define TCU_TSSR_STPS5  (1 << 5)
#define TCU_TSSR_STPS4  (1 << 4)
#define TCU_TSSR_STPS3  (1 << 3)
#define TCU_TSSR_STPS2  (1 << 2)
#define TCU_TSSR_STPS1  (1 << 1)
#define TCU_TSSR_STPS0  (1 << 0)

#define TCU_TSSR_WDTSC  (1 << 16)
#define TCU_TSSR_STPC5  (1 << 5)
#define TCU_TSSR_STPC4  (1 << 4)
#define TCU_TSSR_STPC3  (1 << 3)
#define TCU_TSSR_STPC2  (1 << 2)
#define TCU_TSSR_STPC1  (1 << 1)
#define TCU_TSSR_STPC0  (1 << 0)

#define OST_TCSR_CNT_MD                  ( 1 << 15 )
#define OST_TCSR_PWM_SHUT_ABRUPT         ( 1 << 9 )
#define OST_TCSR_PRESCALE1               ( 0x0 << 3)
#define OST_TCSR_PRESCALE4               ( 0x1 << 3)
#define OST_TCSR_PRESCALE16              ( 0x2 << 3)
#define OST_TCSR_PRESCALE64              ( 0x3 << 3)
#define OST_TCSR_PRESCALE256             ( 0x4 << 3)
#define OST_TCSR_PRESCALE1024            ( 0x5 << 3)

/* Uart Register */
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

#define SYSTEM_STACK          0x80003fe8		/* the kernel system stack address */

#endif
