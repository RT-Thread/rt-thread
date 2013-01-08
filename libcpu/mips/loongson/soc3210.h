#ifndef __SOC3210_H__
#define __SOC3210_H__

#include "../common/mipsregs.h"

/* registers */
#define __REG8(addr)		*((volatile unsigned char *)(addr))
#define __REG16(addr)		*((volatile unsigned short *)(addr))
#define __REG32(addr)		*((volatile unsigned int *)(addr))

#define EMI_BASE			0xBF000000
#define NN_BASE				0xBF000040
#define LCD_BASE			0xBF001000
#define HSB_MISC_BASE		0xBF003200
#define SPI_BASE			0xBF004000
#define PS2_BASE			0xBF004040
#define UART0_BASE			0xBF004080
#define UART1_BASE			0xBF004090
#define I2C_BASE			0xBF0040D0
#define LPB_MISC_BASE		0xBF004100
#define AC97_BASE			0xBF004200
#define AC97_DMA_BASE		0xBF004280
#define CAN1_BASE			0xBF004300
#define CAN0_BASE			0xBF004400
#define MAC0_BASE			0xBF005200
#define MAC1_BASE			0xBF005300

/* LCD registers */
#define LCD_CTRL			__REG32(LCD_BASE + 0x000)
#define LCD_STAT			__REG32(LCD_BASE + 0x004)
#define LCD_HTIM			__REG32(LCD_BASE + 0x008)
#define LCD_VTIM			__REG32(LCD_BASE + 0x00C)
#define LCD_HVLEN			__REG32(LCD_BASE + 0x010)
#define LCD_VBARA			__REG32(LCD_BASE + 0x014)
#define LCD_VBARB			__REG32(LCD_BASE + 0x018)
#define LCD_PCLT			__REG32(LCD_BASE + 0x800)

/* HSB misc registers */
#define HSB_MISC_REG		__REG32(HSB_MISC_BASE + 0x00)
#define INT_EDGE			__REG32(HSB_MISC_BASE + 0x04)
#define INT_STEER			__REG32(HSB_MISC_BASE + 0x08)
#define INT_POL				__REG32(HSB_MISC_BASE + 0x0C)
#define INT_SET				__REG32(HSB_MISC_BASE + 0x10)
#define INT_CLR				__REG32(HSB_MISC_BASE + 0x14)
#define INT_EN				__REG32(HSB_MISC_BASE + 0x18)
#define INT_ISR				__REG32(HSB_MISC_BASE + 0x1C)
#define GPIO_OE_60_29		__REG32(HSB_MISC_BASE + 0x20)
#define GPIO_I_60_29		__REG32(HSB_MISC_BASE + 0x24)
#define GPIO_O_60_29		__REG32(HSB_MISC_BASE + 0x28)
#define HSB_ARB_CFG			__REG32(HSB_MISC_BASE + 0x2C)
#define WD_TIMER			__REG32(HSB_MISC_BASE + 0x30)
#define WD_CTRL				__REG32(HSB_MISC_BASE + 0x34)

/* SPI registers */
#define SPI_SPCR			__REG8(SPI_BASE + 0x00)
#define SPI_SPSR			__REG8(SPI_BASE + 0x01)
#define SPI_TX_FIFO			__REG8(SPI_BASE + 0x02)
#define SPI_SPER			__REG8(SPI_BASE + 0x03)

/* PS/2 registers */
#define PS2_RIBUF			__REG8(PS2_BASE + 0x00)
#define PS2_WOBUF			__REG8(PS2_BASE + 0x00)
#define PS2_RSR				__REG8(PS2_BASE + 0x04)
#define PS2_WSC				__REG8(PS2_BASE + 0x04)
#define PS2_DLL				__REG8(PS2_BASE + 0x08)
#define PS2_DLH				__REG8(PS2_BASE + 0x09)
#define PS2_DL_KBD			__REG8(PS2_BASE + 0x0A)
#define PS2_DL_AUX			__REG8(PS2_BASE + 0x0B)

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

/* LPB misc registers */
#define GPIO_OE_7_0			__REG8(LPB_MISC_BASE + 0x00)
#define GPIO_OE_15_8		__REG8(LPB_MISC_BASE + 0x01)
#define GPIO_OE_23_16		__REG8(LPB_MISC_BASE + 0x02)
#define GPIO_OE_28_24		__REG8(LPB_MISC_BASE + 0x03)
#define GPIO_I_7_0			__REG8(LPB_MISC_BASE + 0x10)
#define GPIO_I_15_8			__REG8(LPB_MISC_BASE + 0x11)
#define GPIO_I_23_16		__REG8(LPB_MISC_BASE + 0x12)
#define GPIO_I_28_24		__REG8(LPB_MISC_BASE + 0x13)
#define GPIO_O_7_0			__REG8(LPB_MISC_BASE + 0x20)
#define GPIO_O_15_8			__REG8(LPB_MISC_BASE + 0x21)
#define GPIO_O_23_16		__REG8(LPB_MISC_BASE + 0x22)
#define GPIO_O_28_24		__REG8(LPB_MISC_BASE + 0x23)
#define LPB_MISC_CFG		__REG8(LPB_MISC_BASE + 0x40)

/* MAC0 registers */
#define MAC0_BUS_MODE		__REG32(MAC0_BASE + 0x00)
#define MAC0_TX_POLL_REQ	__REG32(MAC0_BASE + 0x08)
#define MAC0_RX_POLL_REQ	__REG32(MAC0_BASE + 0x10)
#define MAC0_RX_LIST_BASE_ADDR	__REG32(MAC0_BASE + 0x18)
#define MAC0_TX_LIST_BASE_ADDR	__REG32(MAC0_BASE + 0x20)
#define MAC0_STATUS			__REG32(MAC0_BASE + 0x28)
#define MAC0_OP_MODE		__REG32(MAC0_BASE + 0x30)
#define MAC0_INTERRUPT_EN	__REG32(MAC0_BASE + 0x38)
#define MAC0_MISSED_FRAME_STATISTIC	__REG32(MAC0_BASE + 0x40)
#define MAC0_SMI_EEPROM_CTL	__REG32(MAC0_BASE + 0x48)
#define MAC0_BYTE_ALIGN		__REG32(MAC0_BASE + 0x50)
#define MAC0_GPT_IM_CTL		__REG32(MAC0_BASE + 0x58)

/* MAC1 registers */
#define MAC1_BUS_MODE		__REG32(MAC1_BASE + 0x00)
#define MAC1_TX_POLL_REQ	__REG32(MAC1_BASE + 0x08)
#define MAC1_RX_POLL_REQ	__REG32(MAC1_BASE + 0x10)
#define MAC1_RX_LIST_BASE_ADDR	__REG32(MAC1_BASE + 0x18)
#define MAC1_TX_LIST_BASE_ADDR	__REG32(MAC1_BASE + 0x20)
#define MAC1_STATUS			__REG32(MAC1_BASE + 0x28)
#define MAC1_OP_MODE		__REG32(MAC1_BASE + 0x30)
#define MAC1_INTERRUPT_EN	__REG32(MAC1_BASE + 0x38)
#define MAC1_MISSED_FRAME_STATISTIC	__REG32(MAC1_BASE + 0x40)
#define MAC1_SMI_EEPROM_CTL	__REG32(MAC1_BASE + 0x48)
#define MAC1_BYTE_ALIGN		__REG32(MAC1_BASE + 0x50)
#define MAC1_GPT_IM_CTL		__REG32(MAC1_BASE + 0x58)

/* Peripheral Interrupt Number */
#define IRQ_LCD				0
#define IRQ_MAC1			1
#define IRQ_MAC2			2
#define IRQ_AC97			3
#define IRQ_SPI				8
#define IRQ_KEY				9
#define IRQ_MOUSE			10
#define IRQ_UART0			11
#define IRQ_UART1			12
#define IRQ_I2C				13
#define IRQ_CAN0			14
#define IRQ_CAN1			15
#define IRQ_GPIO15			20
#define IRQ_GPIO14			21
#define IRQ_GPIO13			22
#define IRQ_GPIO12			23

#define SYSTEM_STACK		0x80003fe8		/* the kernel system stack address */

#endif
