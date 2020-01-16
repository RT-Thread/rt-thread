/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-15     RT-Thread    the first version
 * 2019-07-29     zdzn         add macro definition
 */

#ifndef __BCM283X_H__
#define __BCM283X_H__

#include <rthw.h>
#include <rtthread.h>

#define PER_BASE    		(0x3F000000)
#define PER_BASE_40000000 	(0x40000000)


#define HIGH 0x1
#define LOW  0x0

#define BCM283X_CORE_CLK_HZ		250000000	/* 50 MHz */

/*! Offsets for the bases of various peripherals within the peripherals block
 *   Base Address of the System Timer registers
 */
/*! Base Address of the Pads registers */
#define BCM283X_GPIO_PADS               0x100000
/*! Base Address of the Clock/timer registers */
#define BCM283X_CLOCK_BASE              0x101000
/*! Base Address of the GPIO registers */
//#define BCM283X_GPIO_BASE               0x200000
/*! Base Address of the SPI0 registers */
#define BCM283X_SPI0_BASE               0x204000
/*! Base Address of the PWM registers */
#define BCM283X_GPIO_PWM                0x20C000
/*! Base Address of the AUX registers */
#define BCM283X_AUX_BASE				0x215000
/*! Base Address of the AUX_SPI1 registers */
#define BCM283X_SPI1_BASE				0x215080
/*! Base Address of the AUX_SPI2 registers */
#define BCM283X_SPI2_BASE				0x2150C0

/*! Base Address of the BSC0 registers */
#define BCM283X_BSC0_BASE 				0x205000    //for i2c0
/*! Base Address of the BSC1 registers */
#define BCM283X_BSC1_BASE				0x804000    //for i2c1
/*! Base Address of the BSC1 registers */
#define BCM283X_BSC2_BASE				0x805000    //for hdmi i2c not use 

/*
 *  GPIO
 */
#define GPIO_BASE       (PER_BASE + 0x200000)
#define GPIO_GPFSEL0    HWREG32(GPIO_BASE + 0x0000)  /* GPIO Function Select 0 32bit R/W */
#define GPIO_GPFSEL1    HWREG32(GPIO_BASE + 0x0004)  /* GPIO Function Select 1 32bit R/W */
#define GPIO_GPFSEL2    HWREG32(GPIO_BASE + 0x0008)  /* GPIO Function Select 2 32bit R/W */
#define GPIO_GPFSEL4    HWREG32(GPIO_BASE + 0x0010)  /* GPIO Function Select 4 32bit R/W */
#define GPIO_GPFSEL5    HWREG32(GPIO_BASE + 0x0014)  /* GPIO Function Select 5 32bit R/W */
#define GPIO_GPSET0     HWREG32(GPIO_BASE + 0x001C)
#define GPIO_GPSET1     HWREG32(GPIO_BASE + 0x0020)
#define GPIO_GPCLR0     HWREG32(GPIO_BASE + 0x0028)
#define GPIO_GPCLR1     HWREG32(GPIO_BASE + 0x002C)
#define GPIO_GPEDS0     HWREG32(GPIO_BASE + 0x0040)  /* GPIO Pin Event Detect Status */
#define GPIO_GPEDS1     HWREG32(GPIO_BASE + 0x0044)
#define GPIO_GPREN0     HWREG32(GPIO_BASE + 0x004c)  /* GPIO Pin Rising Edge Detect Enable */
#define GPIO_GPREN1     HWREG32(GPIO_BASE + 0x0050)
#define GPIO_GPFEN0     HWREG32(GPIO_BASE + 0x0058) /* GPIO Pin Falling Edge Detect Enable */
#define GPIO_GPFEN1     HWREG32(GPIO_BASE + 0x005C) 
#define GPIO_GPHEN0     HWREG32(GPIO_BASE + 0x0064) /* GPIO Pin High Detect Enable  */
#define GPIO_GPHEN1     HWREG32(GPIO_BASE + 0x0068)
#define GPIO_GPLEN0     HWREG32(GPIO_BASE + 0x0070) /* GPIO Pin Low Detect Enable 0 */
#define GPIO_GPLEN1     HWREG32(GPIO_BASE + 0x0074)
#define GPIO_GPAREN0    HWREG32(GPIO_BASE + 0x007C) /* GPIO Pin Async. Rising Edge Detect */
#define GPIO_GPAREN1    HWREG32(GPIO_BASE + 0x0080)
#define GPIO_GPAFEN0    HWREG32(GPIO_BASE + 0x0088) /* GPIO Pin Async. Falling Edge Detect */
#define GPIO_GPAFEN1    HWREG32(GPIO_BASE + 0x008C)
#define GPIO_GPPUD      HWREG32(GPIO_BASE + 0x0094)  /* GPIO Pin Pull-up/down Enable */
#define GPIO_GPPUDCLK0  HWREG32(GPIO_BASE + 0x0098)  /* GPIO Pin Pull-up/down Enable Clock 0 */
#define GPIO_GPPUDCLK1  HWREG32(GPIO_BASE + 0x009C)  /* GPIO Pin Pull-up/down Enable Clock 1 */

#define BCM283X_GPIO_BASE       (PER_BASE + 0x200000)
#define BCM283X_GPIO_GPFSEL0    (0x0000)  /* GPIO Function Select 0 32bit R/W */
#define BCM283X_GPIO_GPFSEL1    (0x0004)  /* GPIO Function Select 1 32bit R/W */
#define BCM283X_GPIO_GPFSEL2    (0x0008)  /* GPIO Function Select 2 32bit R/W */
#define BCM283X_GPIO_GPFSEL4    (0x0010)  /* GPIO Function Select 4 32bit R/W */
#define BCM283X_GPIO_GPFSEL5    (0x0014)  /* GPIO Function Select 5 32bit R/W */
#define BCM283X_GPIO_GPSET0     (0x001C)
#define BCM283X_GPIO_GPSET1     (0x0020)
#define BCM283X_GPIO_GPCLR0     (0x0028)
#define BCM283X_GPIO_GPCLR1     (0x002C)
#define BCM2835_GPIO_GPLEV0     (0x0034)  /*!< GPIO Pin Level 0 */
#define BCM2835_GPIO_GPLEV1     (0x0038)  /*!< GPIO Pin Level 1 */
#define BCM283X_GPIO_GPEDS0     (0x0040)  /* GPIO Pin Event Detect Status */
#define BCM283X_GPIO_GPEDS1     (0x0044)
#define BCM283X_GPIO_GPREN0     (0x004c)  /* GPIO Pin Rising Edge Detect Enable */
#define BCM283X_GPIO_GPREN1     (0x0050)
#define BCM283X_GPIO_GPFEN0     (0x0058) /* GPIO Pin Falling Edge Detect Enable */
#define BCM283X_GPIO_GPFEN1     (0x005C)
#define BCM283X_GPIO_GPHEN0     (0x0064) /* GPIO Pin High Detect Enable  */
#define BCM283X_GPIO_GPHEN1     (0x0068)
#define BCM283X_GPIO_GPLEN0     (0x0070) /* GPIO Pin Low Detect Enable 0 */
#define BCM283X_GPIO_GPLEN1     (0x0074)
#define BCM283X_GPIO_GPAREN0    (0x007C) /* GPIO Pin Async. Rising Edge Detect */
#define BCM283X_GPIO_GPAREN1    (0x0080)
#define BCM283X_GPIO_GPAFEN0    (0x0088) /* GPIO Pin Async. Falling Edge Detect */
#define BCM283X_GPIO_GPAFEN1    (0x008C)
#define BCM283X_GPIO_GPPUD      (0x0094)  /* GPIO Pin Pull-up/down Enable */
#define BCM283X_GPIO_GPPUDCLK0  (0x0098)  /* GPIO Pin Pull-up/down Enable Clock 0 */
#define BCM283X_GPIO_GPPUDCLK1  (0x009C)  /* GPIO Pin Pull-up/down Enable Clock 1 */

enum gpio_function_select
{
    BCM283X_GPIO_FSEL_INPT  = 0x00,   /*!< Input 0b000 */
    BCM283X_GPIO_FSEL_OUTP  = 0x01,   /*!< Output 0b001 */
    BCM283X_GPIO_FSEL_ALT0  = 0x04,   /*!< Alternate function 0 0b100 */
    BCM283X_GPIO_FSEL_ALT1  = 0x05,   /*!< Alternate function 1 0b101 */
    BCM283X_GPIO_FSEL_ALT2  = 0x06,   /*!< Alternate function 2 0b110, */
    BCM283X_GPIO_FSEL_ALT3  = 0x07,   /*!< Alternate function 3 0b111 */
    BCM283X_GPIO_FSEL_ALT4  = 0x03,   /*!< Alternate function 4 0b011 */
    BCM283X_GPIO_FSEL_ALT5  = 0x02,   /*!< Alternate function 5 0b010 */
    BCM283X_GPIO_FSEL_MASK  = 0x07    /*!< Function select bits mask 0b111 */
};

enum gpio_pud_mode
{
    BCM283X_GPIO_PUD_OFF     = 0x00,   /*!< Off ? disable pull-up/down 0b00 */
    BCM283X_GPIO_PUD_DOWN    = 0x01,   /*!< Enable Pull Down control 0b01 */
    BCM283X_GPIO_PUD_UP      = 0x02    /*!< Enable Pull Up control 0b10  */
};

/* Defines for BSC I2C
 * GPIO register offsets from BCM283X_BSC*_BASE.
 * Offsets into the BSC Peripheral block in bytes per 3.1 BSC Register Map
 */
/* I2C Address Map offset address */
#define BCM283X_BSC_C 			0x0000 /*!< BSC Master Control */
#define BCM283X_BSC_S 			0x0004 /*!< BSC Master Status */
#define BCM283X_BSC_DLEN		0x0008 /*!< BSC Master Data Length */
#define BCM283X_BSC_A 			0x000c /*!< BSC Master Slave Address */
#define BCM283X_BSC_FIFO		0x0010 /*!< BSC Master Data FIFO */
#define BCM283X_BSC_DIV			0x0014 /*!< BSC Master Clock Divider */
#define BCM283X_BSC_DEL			0x0018 /*!< BSC Master Data Delay */
#define BCM283X_BSC_CLKT		0x001c /*!< BSC Master Clock Stretch Timeout */

/* Register masks for C Register */
#define BCM283X_BSC_C_I2CEN 		0x00008000 /*!< I2C Enable, 0 = disabled, 1 = enabled */
#define BCM283X_BSC_C_INTR 		0x00000400 /*!< Interrupt on RX */
#define BCM283X_BSC_C_INTT 		0x00000200 /*!< Interrupt on TX */
#define BCM283X_BSC_C_INTD 		0x00000100 /*!< Interrupt on DONE */
#define BCM283X_BSC_C_ST 		0x00000080 /*!< Start transfer, 1 = Start a new transfer */
#define BCM283X_BSC_C_CLEAR_1 		0x00000020 /*!< Clear FIFO Clear */
#define BCM283X_BSC_C_CLEAR_2 		0x00000010 /*!< Clear FIFO Clear */
#define BCM283X_BSC_C_READ 		0x00000001 /*!<	Read transfer */

/* Register masks for S Register */
#define BCM283X_BSC_S_CLKT 		0x00000200 /*!< Clock stretch timeout */
#define BCM283X_BSC_S_ERR 		0x00000100 /*!< ACK error */
#define BCM283X_BSC_S_RXF 		0x00000080 /*!< RXF FIFO full, 0 = FIFO is not full, 1 = FIFO is full */
#define BCM283X_BSC_S_TXE 		0x00000040 /*!< TXE FIFO full, 0 = FIFO is not full, 1 = FIFO is full */
#define BCM283X_BSC_S_RXD 		0x00000020 /*!< RXD FIFO contains data */
#define BCM283X_BSC_S_TXD 		0x00000010 /*!< TXD FIFO can accept data */
#define BCM283X_BSC_S_RXR 		0x00000008 /*!< RXR FIFO needs reading (full) */
#define BCM283X_BSC_S_TXW 		0x00000004 /*!< TXW FIFO needs writing (full) */
#define BCM283X_BSC_S_DONE 		0x00000002 /*!< Transfer DONE */
#define BCM283X_BSC_S_TA 		0x00000001 /*!< Transfer Active */

#define BCM283X_BSC_FIFO_SIZE   	16  /*!< BSC FIFO size */

enum  i2c_clock_divider
{
    BCM283X_I2C_CLOCK_DIVIDER_2500   = 2500,      /*!< 2500 = 10us = 100 kHz */
    BCM283X_I2C_CLOCK_DIVIDER_626    = 626,       /*!< 622 = 2.504us = 399.3610 kHz */
    BCM283X_I2C_CLOCK_DIVIDER_150    = 150,       /*!< 150 = 60ns = 1.666 MHz (default at reset) */
    BCM283X_I2C_CLOCK_DIVIDER_148    = 148        /*!< 148 = 59ns = 1.689 MHz */
};

enum i2c_reason_codes
{
    BCM283X_I2C_REASON_OK   	     = 0x00,      /*!< Success */
    BCM283X_I2C_REASON_ERROR_NACK    = 0x01,      /*!< Received a NACK */
    BCM283X_I2C_REASON_ERROR_CLKT    = 0x02,      /*!< Received Clock Stretch Timeout */
    BCM283X_I2C_REASON_ERROR_DATA    = 0x04       /*!< Not all data is sent / received */
};

/*
 *  Interrupt Controler
 */
#define IRQ_BASE            (PER_BASE + 0xB200)
#define IRQ_PEND_BASIC      HWREG32(IRQ_BASE + 0x00)
#define IRQ_PEND1           HWREG32(IRQ_BASE + 0x04)
#define IRQ_PEND2           HWREG32(IRQ_BASE + 0x08)
#define IRQ_FIQ_CONTROL     HWREG32(IRQ_BASE + 0x0C)
#define IRQ_ENABLE1         HWREG32(IRQ_BASE + 0x10)
#define IRQ_ENABLE2         HWREG32(IRQ_BASE + 0x14)
#define IRQ_ENABLE_BASIC    HWREG32(IRQ_BASE + 0x18)
#define IRQ_DISABLE1        HWREG32(IRQ_BASE + 0x1C)
#define IRQ_DISABLE2        HWREG32(IRQ_BASE + 0x20)
#define IRQ_DISABLE_BASIC   HWREG32(IRQ_BASE + 0x24)

/*
 *  System Timer
 */
#define STIMER_BASE         (PER_BASE  + 0x3000)
#define STIMER_CS           HWREG32(STIMER_BASE + 0x00)
#define STIMER_CLO          HWREG32(STIMER_BASE + 0x04)
#define STIMER_CHI          HWREG32(STIMER_BASE + 0x08)
#define STIMER_C0           HWREG32(STIMER_BASE + 0x0C)
#define STIMER_C1           HWREG32(STIMER_BASE + 0x10)
#define STIMER_C2           HWREG32(STIMER_BASE + 0x14)
#define STIMER_C3           HWREG32(STIMER_BASE + 0x18)

/* Defines for ST */
#define BCM283X_ST_BASE 		(PER_BASE  + 0x3000)
#define BCM283X_ST_CS 			0x0000 /*!< System Timer Control/Status */
#define BCM283X_ST_CLO 			0x0004 /*!< System Timer Counter Lower 32 bits */
#define BCM283X_ST_CHI 			0x0008 /*!< System Timer Counter Upper 32 bits */
#define BCM283X_ST_C0 			0x000C
#define BCM283X_ST_C1 			0x0010
#define BCM283X_ST_C2 			0x0014
#define BCM283X_ST_C3 			0x0018

/*
 * ARM Timer
 */
#define ARM_TIMER_BASE		(PER_BASE + 0xB000)
#define ARM_TIMER_LOAD		HWREG32(ARM_TIMER_BASE + 0x400)
#define ARM_TIMER_VALUE		HWREG32(ARM_TIMER_BASE + 0x404)
#define ARM_TIMER_CTRL		HWREG32(ARM_TIMER_BASE + 0x408)
#define ARM_TIMER_IRQCLR	HWREG32(ARM_TIMER_BASE + 0x40C)
#define ARM_TIMER_RAWIRQ	HWREG32(ARM_TIMER_BASE + 0x410)
#define ARM_TIMER_MASKIRQ	HWREG32(ARM_TIMER_BASE + 0x414)
#define ARM_TIMER_RELOAD	HWREG32(ARM_TIMER_BASE + 0x418)
#define ARM_TIMER_PREDIV	HWREG32(ARM_TIMER_BASE + 0x41C)
#define ARM_TIMER_CNTR		HWREG32(ARM_TIMER_BASE + 0x420)

/*
 *  Core Timer
 */
#define CTIMER_CTL          HWREG32(PER_BASE_40000000 + 0x00)  /* Control register */
#define CTIMER_PRE          HWREG32(PER_BASE_40000000 + 0x08)  /* Core timer prescaler */
#define CTIMER_LS32B        HWREG32(PER_BASE_40000000 + 0x1C)  /* Core timer access LS 32 bits */
#define CTIMER_MS32B        HWREG32(PER_BASE_40000000 + 0x20)  /* Core timer access MS 32 bits */

/*
 *  ARM Core Timer
 */
#define C0TIMER_INTCTL      HWREG32(PER_BASE_40000000 + 0x40)  /* Core0 timers Interrupt control */
#define C1TIMER_INTCTL      HWREG32(PER_BASE_40000000 + 0x44)  /* Core1 timers Interrupt control */
#define C2TIMER_INTCTL      HWREG32(PER_BASE_40000000 + 0x48)  /* Core2 timers Interrupt control */
#define C3TIMER_INTCTL      HWREG32(PER_BASE_40000000 + 0x4C)  /* Core3 timers Interrupt control */
#define CORETIMER_INTCTL(n)      HWREG32(PER_BASE_40000000 + 0x40 + n*4)  /* Core3 timers Interrupt control */
/*
 *  ARM Core Mailbox interrupt
 */
#define C0MB_INTCTL         HWREG32(PER_BASE_40000000 + 0x50)  /* Core0 Mailboxes Interrupt control */
#define C1MB_INTCTL         HWREG32(PER_BASE_40000000 + 0x54)  /* Core1 Mailboxes Interrupt control */
#define C2MB_INTCTL         HWREG32(PER_BASE_40000000 + 0x58)  /* Core2 Mailboxes Interrupt control */
#define C3MB_INTCTL         HWREG32(PER_BASE_40000000 + 0x5C)  /* Core3 Mailboxes Interrupt control */
#define COREMB_INTCTL(n)    HWREG32(PER_BASE_40000000 + 0x50 + 4*n)  /* Core3 Mailboxes Interrupt control */
/*
 *  ARM Core IRQ/FIQ status
 */
#define C0_IRQSOURCE        HWREG32(PER_BASE_40000000 + 0x60)  /* Core0 IRQ Source */
#define C1_IRQSOURCE        HWREG32(PER_BASE_40000000 + 0x64)  /* Core1 IRQ Source */
#define C2_IRQSOURCE        HWREG32(PER_BASE_40000000 + 0x68)  /* Core2 IRQ Source */
#define C3_IRQSOURCE        HWREG32(PER_BASE_40000000 + 0x6C)  /* Core3 IRQ Source */
#define C0_FIQSOURCE        HWREG32(PER_BASE_40000000 + 0x70)  /* Core0 FIQ Source */
#define C1_FIQSOURCE        HWREG32(PER_BASE_40000000 + 0x74)  /* Core1 FIQ Source */
#define C2_FIQSOURCE        HWREG32(PER_BASE_40000000 + 0x78)  /* Core2 FIQ Source */
#define C3_FIQSOURCE        HWREG32(PER_BASE_40000000 + 0x7C)  /* Core3 FIQ Source */
#define CORE_IRQSOURCE(n)        HWREG32(PER_BASE_40000000 + 0x60+ n*0x4)
#define CORE_FIQSOURCE(n)        HWREG32(PER_BASE_40000000 + 0x70+ n*0x4)

#define CORE_MAILBOX3_SET(n)        HWREG32(PER_BASE_40000000 + 0x8C + n*0x10)
#define CORE_MAILBOX3_CLEAR(n)      HWREG32(PER_BASE_40000000 + 0xCC + n*0x10)
#define CORE_MAILBOX2_SET(n)        HWREG32(PER_BASE_40000000 + 0x88 + n*0x10)
#define CORE_MAILBOX2_CLEAR(n)      HWREG32(PER_BASE_40000000 + 0xC8 + n*0x10)
#define CORE_MAILBOX1_SET(n)        HWREG32(PER_BASE_40000000 + 0x84 + n*0x10)
#define CORE_MAILBOX1_CLEAR(n)      HWREG32(PER_BASE_40000000 + 0xC4 + n*0x10)
#define CORE_MAILBOX0_SET(n)        HWREG32(PER_BASE_40000000 + 0x80 + n*0x10)
#define CORE_MAILBOX0_CLEAR(n)      HWREG32(PER_BASE_40000000 + 0xC0 + n*0x10)

/* for smp ipi using mailbox0 */
#define IPI_MAILBOX_SET   CORE_MAILBOX0_SET

#define IPI_MAILBOX_CLEAR CORE_MAILBOX0_CLEAR
#define IPI_MAILBOX_INT_MASK     (0x01)

#define IRQ_ARM_TIMER           64
#define IRQ_ARM_MAILBOX         65
#define IRQ_ARM_DB0             66
#define IRQ_ARM_DB1             67
#define IRQ_ARM_GPU0_HALT       68
#define IRQ_ARM_GPU1_HALT       69
#define IRQ_ARM_ILLEGAL_ACC1    70
#define IRQ_ARM_ILLEGAL_ACC0    71

#define IRQ_SYSTIMER_MATCH_1    1
#define IRQ_SYSTIMER_MATCH_3    3

#define IRQ_AUX                 29
#define IRQ_IIC_SPI_SLV         43
#define IRQ_PWA0                45
#define IRQ_PWA1                46
#define IRQ_SMI                 48
#define IRQ_GPIO0               49
#define IRQ_GPIO1               50
#define IRQ_GPIO2               51
#define IRQ_GPIO3               52
#define IRQ_IIC                 53
#define IRQ_SPI                 54
#define IRQ_PCM                 55
#define IRQ_UART                57

/* CLOCK */
#define BCM283X_PLLA			0
#define BCM283X_PLLB			1
#define BCM283X_PLLC			2
#define BCM283X_PLLD			3
#define BCM283X_PLLH			4

#define BCM283X_PLLA_CORE		5
#define BCM283X_PLLA_PER		6
#define BCM283X_PLLB_ARM		7
#define BCM283X_PLLC_CORE0		8
#define BCM283X_PLLC_CORE1		9
#define BCM283X_PLLC_CORE2		10
#define BCM283X_PLLC_PER		11
#define BCM283X_PLLD_CORE		12
#define BCM283X_PLLD_PER		13
#define BCM283X_PLLH_RCAL		14
#define BCM283X_PLLH_AUX		15
#define BCM283X_PLLH_PIX		16

#define BCM283X_CLOCK_TIMER		17
#define BCM283X_CLOCK_OTP		18
#define BCM283X_CLOCK_UART		19
#define BCM283X_CLOCK_VPU		20
#define BCM283X_CLOCK_V3D		21
#define BCM283X_CLOCK_ISP		22
#define BCM283X_CLOCK_H264		23
#define BCM283X_CLOCK_VEC		24
#define BCM283X_CLOCK_HSM		25
#define BCM283X_CLOCK_SDRAM		26
#define BCM283X_CLOCK_TSENS		27
#define BCM283X_CLOCK_EMMC		28
#define BCM283X_CLOCK_PERI_IMAGE	29
#define BCM283X_CLOCK_COUNT		30

#define CM_PASSWORD		0x5a000000

#define CM_GNRICCTL		0x000
#define CM_GNRICDIV		0x004
#define CM_VPUCTL		0x008
#define CM_VPUDIV		0x00c
#define CM_SYSCTL		0x010
#define CM_SYSDIV		0x014
#define CM_PERIACTL		0x018
#define CM_PERIADIV		0x01c
#define CM_PERIICTL		0x020
#define CM_PERIIDIV		0x024
#define CM_H264CTL		0x028
#define CM_H264DIV		0x02c
#define CM_ISPCTL		0x030
#define CM_ISPDIV		0x034
#define CM_V3DCTL		0x038
#define CM_V3DDIV		0x03c
#define CM_CAM0CTL		0x040
#define CM_CAM0DIV		0x044
#define CM_CAM1CTL		0x048
#define CM_CAM1DIV		0x04c
#define CM_CCP2CTL		0x050
#define CM_CCP2DIV		0x054
#define CM_DSI0ECTL		0x058
#define CM_DSI0EDIV		0x05c
#define CM_DSI0PCTL		0x060
#define CM_DSI0PDIV		0x064
#define CM_DPICTL		0x068
#define CM_DPIDIV		0x06c
#define CM_GP0CTL		0x070
#define CM_GP0DIV		0x074
#define CM_GP1CTL		0x078
#define CM_GP1DIV		0x07c
#define CM_GP2CTL		0x080
#define CM_GP2DIV		0x084
#define CM_HSMCTL		0x088
#define CM_HSMDIV		0x08c
#define CM_OTPCTL		0x090
#define CM_OTPDIV		0x094
#define CM_PWMCTL		0x0a0
#define CM_PWMDIV		0x0a4
#define CM_SMICTL		0x0b0
#define CM_SMIDIV		0x0b4
#define CM_TSENSCTL		0x0e0
#define CM_TSENSDIV		0x0e4
#define CM_TIMERCTL		0x0e8
#define CM_TIMERDIV		0x0ec
#define CM_UARTCTL		0x0f0
#define CM_UARTDIV		0x0f4
#define CM_VECCTL		0x0f8
#define CM_VECDIV		0x0fc
#define CM_PULSECTL		0x190
#define CM_PULSEDIV		0x194
#define CM_SDCCTL		0x1a8
#define CM_SDCDIV		0x1ac
#define CM_ARMCTL		0x1b0
#define CM_EMMCCTL		0x1c0
#define CM_EMMCDIV		0x1c4

#define BCM283X_AUX_IRQ			0x0000  /*!< xxx */
#define BCM283X_AUX_ENABLE		0x0004  /*!< */
#define BCM283X_AUX_ENABLE_UART1	0x01    /*!<  */
#define BCM283X_AUX_ENABLE_SPI0		0x02	/*!< SPI0 (SPI1 in the device) */
#define BCM283X_AUX_ENABLE_SPI1		0x04	/*!< SPI1 (SPI2 in the device) */
#define BCM283X_AUX_SPI_CNTL0		0x0000  /*!< */
#define BCM283X_AUX_SPI_CNTL1 		0x0004  /*!< */
#define BCM283X_AUX_SPI_STAT 		0x0008  /*!< */
#define BCM283X_AUX_SPI_PEEK		0x000C  /*!< Read but do not take from FF */
#define BCM283X_AUX_SPI_IO		0x0020  /*!< Write = TX, read=RX */
#define BCM283X_AUX_SPI_TXHOLD		0x0030  /*!< Write = TX keep CS, read=RX */
#define BCM283X_AUX_SPI_CLOCK_MIN	30500		/*!< 30,5kHz */
#define BCM283X_AUX_SPI_CLOCK_MAX	125000000 	/*!< 125Mhz */
#define BCM283X_AUX_SPI_CNTL0_SPEED	0xFFF00000  /*!< */
#define BCM283X_AUX_SPI_CNTL0_SPEED_MAX	0xFFF      /*!< */
#define BCM283X_AUX_SPI_CNTL0_SPEED_SHIFT 20        /*!< */
#define BCM283X_AUX_SPI_CNTL0_CS0_N     0x000C0000 /*!< CS 0 low */
#define BCM283X_AUX_SPI_CNTL0_CS1_N     0x000A0000 /*!< CS 1 low */
#define BCM283X_AUX_SPI_CNTL0_CS2_N 	0x00060000 /*!< CS 2 low */
#define BCM283X_AUX_SPI_CNTL0_POSTINPUT	0x00010000  /*!< */
#define BCM283X_AUX_SPI_CNTL0_VAR_CS	0x00008000  /*!< */
#define BCM283X_AUX_SPI_CNTL0_VAR_WIDTH	0x00004000  /*!< */
#define BCM283X_AUX_SPI_CNTL0_DOUTHOLD	0x00003000  /*!< */
#define BCM283X_AUX_SPI_CNTL0_ENABLE	0x00000800  /*!< */
#define BCM283X_AUX_SPI_CNTL0_CPHA_IN	0x00000400  /*!< */
#define BCM283X_AUX_SPI_CNTL0_CLEARFIFO	0x00000200  /*!< */
#define BCM283X_AUX_SPI_CNTL0_CPHA_OUT	0x00000100  /*!< */
#define BCM283X_AUX_SPI_CNTL0_CPOL	0x00000080  /*!< */
#define BCM283X_AUX_SPI_CNTL0_MSBF_OUT	0x00000040  /*!< */
#define BCM283X_AUX_SPI_CNTL0_SHIFTLEN	0x0000003F  /*!< */
#define BCM283X_AUX_SPI_CNTL1_CSHIGH	0x00000700  /*!< */
#define BCM283X_AUX_SPI_CNTL1_IDLE	0x00000080  /*!< */
#define BCM283X_AUX_SPI_CNTL1_TXEMPTY	0x00000040  /*!< */
#define BCM283X_AUX_SPI_CNTL1_MSBF_IN	0x00000002  /*!< */
#define BCM283X_AUX_SPI_CNTL1_KEEP_IN	0x00000001  /*!< */
#define BCM283X_AUX_SPI_STAT_TX_LVL	0xFF000000  /*!< */
#define BCM283X_AUX_SPI_STAT_RX_LVL	0x00FF0000  /*!< */
#define BCM283X_AUX_SPI_STAT_TX_FULL	0x00000400  /*!< */
#define BCM283X_AUX_SPI_STAT_TX_EMPTY	0x00000200  /*!< */
#define BCM283X_AUX_SPI_STAT_RX_FULL	0x00000100  /*!< */
#define BCM283X_AUX_SPI_STAT_RX_EMPTY	0x00000080  /*!< */
#define BCM283X_AUX_SPI_STAT_BUSY	0x00000040  /*!< */
#define BCM283X_AUX_SPI_STAT_BITCOUNT	0x0000003F  /*!< */

/* Defines for SPI */
#define BCM283X_SPI0_CS                      0x0000 /*!< SPI Master Control and Status */
#define BCM283X_SPI0_FIFO                    0x0004 /*!< SPI Master TX and RX FIFOs */
#define BCM283X_SPI0_CLK                     0x0008 /*!< SPI Master Clock Divider */
#define BCM283X_SPI0_DLEN                    0x000c /*!< SPI Master Data Length */
#define BCM283X_SPI0_LTOH                    0x0010 /*!< SPI LOSSI mode TOH */
#define BCM283X_SPI0_DC                      0x0014 /*!< SPI DMA DREQ Controls */

/* Register masks for SPI0_CS */
#define BCM283X_SPI0_CS_LEN_LONG             0x02000000 /*!< Enable Long data word in Lossi mode if DMA_LEN is set */
#define BCM283X_SPI0_CS_DMA_LEN              0x01000000 /*!< Enable DMA mode in Lossi mode */
#define BCM283X_SPI0_CS_CSPOL2               0x00800000 /*!< Chip Select 2 Polarity */
#define BCM283X_SPI0_CS_CSPOL1               0x00400000 /*!< Chip Select 1 Polarity */
#define BCM283X_SPI0_CS_CSPOL0               0x00200000 /*!< Chip Select 0 Polarity */
#define BCM283X_SPI0_CS_RXF                  0x00100000 /*!< RXF - RX FIFO Full */
#define BCM283X_SPI0_CS_RXR                  0x00080000 /*!< RXR RX FIFO needs Reading (full) */
#define BCM283X_SPI0_CS_TXD                  0x00040000 /*!< TXD TX FIFO can accept Data */
#define BCM283X_SPI0_CS_RXD                  0x00020000 /*!< RXD RX FIFO contains Data */
#define BCM283X_SPI0_CS_DONE                 0x00010000 /*!< Done transfer Done */
#define BCM283X_SPI0_CS_TE_EN                0x00008000 /*!< Unused */
#define BCM283X_SPI0_CS_LMONO                0x00004000 /*!< Unused */
#define BCM283X_SPI0_CS_LEN                  0x00002000 /*!< LEN LoSSI enable */
#define BCM283X_SPI0_CS_REN                  0x00001000 /*!< REN Read Enable */
#define BCM283X_SPI0_CS_ADCS                 0x00000800 /*!< ADCS Automatically Deassert Chip Select */
#define BCM283X_SPI0_CS_INTR                 0x00000400 /*!< INTR Interrupt on RXR */
#define BCM283X_SPI0_CS_INTD                 0x00000200 /*!< INTD Interrupt on Done */
#define BCM283X_SPI0_CS_DMAEN                0x00000100 /*!< DMAEN DMA Enable */
#define BCM283X_SPI0_CS_TA                   0x00000080 /*!< Transfer Active */
#define BCM283X_SPI0_CS_CSPOL                0x00000040 /*!< Chip Select Polarity */
#define BCM283X_SPI0_CS_CLEAR                0x00000030 /*!< Clear FIFO Clear RX and TX */
#define BCM283X_SPI0_CS_CLEAR_RX             0x00000020 /*!< Clear FIFO Clear RX  */
#define BCM283X_SPI0_CS_CLEAR_TX             0x00000010 /*!< Clear FIFO Clear TX  */
#define BCM283X_SPI0_CS_CPOL                 0x00000008 /*!< Clock Polarity */
#define BCM283X_SPI0_CS_CPHA                 0x00000004 /*!< Clock Phase */
#define BCM283X_SPI0_CS_CS                   0x00000003 /*!< Chip Select */

enum spi_bit_order
{
    BCM283X_SPI_BIT_ORDER_LSBFIRST = 0,  /*!< LSB First */
    BCM283X_SPI_BIT_ORDER_MSBFIRST = 1   /*!< MSB First */
};

enum spi_mode
{
    BCM283X_SPI_MODE0 = 0,  /*!< CPOL = 0, CPHA = 0 */
    BCM283X_SPI_MODE1 = 1,  /*!< CPOL = 0, CPHA = 1 */
    BCM283X_SPI_MODE2 = 2,  /*!< CPOL = 1, CPHA = 0 */
    BCM283X_SPI_MODE3 = 3   /*!< CPOL = 1, CPHA = 1 */
};

enum spi_chip_select
{
    BCM283X_SPI_CS0 = 0,     /*!< Chip Select 0 */
    BCM283X_SPI_CS1 = 1,     /*!< Chip Select 1 */
    BCM283X_SPI_CS2 = 2,     /*!< Chip Select 2 (ie pins CS1 and CS2 are asserted) */
    BCM283X_SPI_CS_NONE = 3  /*!< No CS, control it yourself */
};

enum spi_clock_divider
{
    BCM283X_SPI_CLOCK_DIVIDER_65536 = 0,       /*!< 65536 = 3.814697260kHz on Rpi2, 6.1035156kHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_32768 = 32768,   /*!< 32768 = 7.629394531kHz on Rpi2, 12.20703125kHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_16384 = 16384,   /*!< 16384 = 15.25878906kHz on Rpi2, 24.4140625kHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_8192  = 8192,    /*!< 8192 = 30.51757813kHz on Rpi2, 48.828125kHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_4096  = 4096,    /*!< 4096 = 61.03515625kHz on Rpi2, 97.65625kHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_2048  = 2048,    /*!< 2048 = 122.0703125kHz on Rpi2, 195.3125kHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_1024  = 1024,    /*!< 1024 = 244.140625kHz on Rpi2, 390.625kHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_512   = 512,     /*!< 512 = 488.28125kHz on Rpi2, 781.25kHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_256   = 256,     /*!< 256 = 976.5625kHz on Rpi2, 1.5625MHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_128   = 128,     /*!< 128 = 1.953125MHz on Rpi2, 3.125MHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_64    = 64,      /*!< 64 = 3.90625MHz on Rpi2, 6.250MHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_32    = 32,      /*!< 32 = 7.8125MHz on Rpi2, 12.5MHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_16    = 16,      /*!< 16 = 15.625MHz on Rpi2, 25MHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_8     = 8,       /*!< 8 = 31.25MHz on Rpi2, 50MHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_4     = 4,       /*!< 4 = 62.5MHz on Rpi2, 100MHz on RPI3. Dont expect this speed to work reliably. */
    BCM283X_SPI_CLOCK_DIVIDER_2     = 2,       /*!< 2 = 125MHz on Rpi2, 200MHz on RPI3, fastest you can get. Dont expect this speed to work reliably.*/
    BCM283X_SPI_CLOCK_DIVIDER_1     = 1        /*!< 1 = 3.814697260kHz on Rpi2, 6.1035156kHz on RPI3, same as 0/65536 */
};

/* BCM IO pin */
enum bcm_gpio_pin
{
    BCM_GPIO_PIN_0 = 0,
    BCM_GPIO_PIN_1,
    BCM_GPIO_PIN_2,
    BCM_GPIO_PIN_3,
    BCM_GPIO_PIN_4,
    BCM_GPIO_PIN_5,
    BCM_GPIO_PIN_6,
    BCM_GPIO_PIN_7,
    BCM_GPIO_PIN_8,
    BCM_GPIO_PIN_9,
    BCM_GPIO_PIN_10,
    BCM_GPIO_PIN_11,
    BCM_GPIO_PIN_12,
    BCM_GPIO_PIN_13,
    BCM_GPIO_PIN_14,
    BCM_GPIO_PIN_15,
    BCM_GPIO_PIN_16,
    BCM_GPIO_PIN_17,
    BCM_GPIO_PIN_18,
    BCM_GPIO_PIN_19,
    BCM_GPIO_PIN_20,
    BCM_GPIO_PIN_21,
    BCM_GPIO_PIN_22,
    BCM_GPIO_PIN_23,
    BCM_GPIO_PIN_24,
    BCM_GPIO_PIN_25,
    BCM_GPIO_PIN_26,
    BCM_GPIO_PIN_27,
    BCM_GPIO_PIN_28,
    BCM_GPIO_PIN_29,
    BCM_GPIO_PIN_30,
    BCM_GPIO_PIN_31,
    BCM_GPIO_PIN_32,
    BCM_GPIO_PIN_33,
    BCM_GPIO_PIN_34,
    BCM_GPIO_PIN_35,
    BCM_GPIO_PIN_36,
    BCM_GPIO_PIN_37,
    BCM_GPIO_PIN_38,
    BCM_GPIO_PIN_39,
    BCM_GPIO_PIN_40,
    BCM_GPIO_PIN_41,
    BCM_GPIO_PIN_42,
    BCM_GPIO_PIN_43,
    BCM_GPIO_PIN_44,
    BCM_GPIO_PIN_45,
    BCM_GPIO_PIN_46,
    BCM_GPIO_PIN_47,
    BCM_GPIO_PIN_48,
    BCM_GPIO_PIN_49,
    BCM_GPIO_PIN_50,
    BCM_GPIO_PIN_51,
    BCM_GPIO_PIN_52,
    BCM_GPIO_PIN_53,
    BCM_GPIO_PIN_NUM,
};

rt_uint32_t bcm283x_peri_read(volatile rt_ubase_t addr);
rt_uint32_t bcm283x_peri_read_nb(volatile rt_ubase_t addr);
void bcm283x_peri_write(volatile rt_ubase_t addr, rt_uint32_t value);
void bcm283x_peri_write_nb(volatile rt_ubase_t addr, rt_uint32_t value);
void bcm283x_peri_set_bits(volatile rt_ubase_t addr, rt_uint32_t value, rt_uint32_t mask);

void bcm283x_gpio_fsel(rt_uint8_t pin, rt_uint8_t mode);
void bcm283x_gpio_set(rt_uint8_t pin);
void bcm283x_gpio_clr(rt_uint8_t pin);

rt_uint8_t bcm283x_gpio_lev(rt_uint8_t pin);
rt_uint8_t bcm283x_gpio_eds(rt_uint8_t pin);
void bcm283x_gpio_set_eds(rt_uint8_t pin);
void bcm283x_gpio_ren(rt_uint8_t pin);
void bcm283x_gpio_clr_ren(rt_uint8_t pin);
void bcm283x_gpio_fen(rt_uint8_t pin);
void bcm283x_gpio_clr_fen(rt_uint8_t pin);
void bcm283x_gpio_hen(rt_uint8_t pin);
void bcm283x_gpio_clr_hen(rt_uint8_t pin);
void bcm283x_gpio_len(rt_uint8_t pin);
void bcm283x_gpio_clr_len(rt_uint8_t pin);
void bcm283x_gpio_aren(rt_uint8_t pin);
void bcm283x_gpio_clr_aren(rt_uint8_t pin);
void bcm283x_gpio_afen(rt_uint8_t pin);
void bcm283x_gpio_clr_afen(rt_uint8_t pin);
void bcm283x_gpio_pud(rt_uint8_t pud);
void bcm283x_gpio_pudclk(rt_uint8_t pin, rt_uint8_t on);
void bcm283x_gpio_set_pud(rt_uint8_t pin, rt_uint8_t pud);
void bcm283x_gpio_write(rt_uint8_t pin, rt_uint8_t val);
void bcm283x_st_delay(rt_uint64_t offset_micros, rt_uint64_t micros);
rt_uint64_t bcm283x_st_read(void);
void bcm283x_delayMicroseconds(rt_uint64_t micros);
void bcm283x_clo_delayMicros(rt_uint32_t micros);

int bcm283x_i2c_begin(int no);
void bcm283x_i2c_end(int no);
void bcm283x_i2c_setSlaveAddress(int no, rt_uint8_t saddr);
void bcm283x_i2c_setClockDivider(int no, rt_uint16_t divider);
void bcm283x_i2c_set_baudrate(int no, rt_uint32_t baudrate);
rt_uint8_t bcm283x_i2c_read(rt_uint32_t base, rt_uint8_t* buf, rt_uint32_t len);
rt_uint8_t bcm283x_i2c_write(rt_uint32_t base, const rt_uint8_t * buf, rt_uint32_t len);
rt_uint8_t bcm283x_i2c_write_read_rs(char* cmds, rt_uint32_t cmds_len, char* buf, rt_uint32_t buf_len);

#endif

