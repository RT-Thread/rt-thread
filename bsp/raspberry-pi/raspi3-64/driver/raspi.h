/*
 * File      : rsapi.h
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#ifndef __RASPI_H__
#define __RASPI_H__

#include <rthw.h>

#define __REG32(x) (*((volatile unsigned int*)((rt_uint64_t)x)))

typedef enum
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
    BCM_GPIO_PIN_NULL,
} bcm_gpio_pin;

typedef enum
{
    BCM283X_GPIO_FSEL_INPT = 0x00,   /*!< Input 0b000 */
    BCM283X_GPIO_FSEL_OUTP = 0x01,   /*!< Output 0b001 */
    BCM283X_GPIO_FSEL_ALT0 = 0x04,   /*!< Alternate function 0 0b100 */
    BCM283X_GPIO_FSEL_ALT1 = 0x05,   /*!< Alternate function 1 0b101 */
    BCM283X_GPIO_FSEL_ALT2 = 0x06,   /*!< Alternate function 2 0b110, */
    BCM283X_GPIO_FSEL_ALT3 = 0x07,   /*!< Alternate function 3 0b111 */
    BCM283X_GPIO_FSEL_ALT4 = 0x03,   /*!< Alternate function 4 0b011 */
    BCM283X_GPIO_FSEL_ALT5 = 0x02,   /*!< Alternate function 5 0b010 */
    BCM283X_GPIO_FSEL_MASK = 0x07    /*!< Function select bits mask 0b111 */
} gpio_function_select;

typedef enum
{
    BCM283X_GPIO_PUD_OFF    = 0x00,   /*!< Off ? disable pull-up/down 0b00 */
    BCM283X_GPIO_PUD_DOWN   = 0x01,   /*!< Enable Pull Down control 0b01 */
    BCM283X_GPIO_PUD_UP     = 0x02    /*!< Enable Pull Up control 0b10  */
} gpio_pud_mode;

#define BCM283X_CORE_CLK_HZ 250000000    /* 50 MHz */

/* Base Address */
#define PER_BASE     (0x3F000000)
#define PER_BASE_40000000    (0x40000000)
//#define BCM283X_PERI_BASE     (0x3F000000)
//#define BCM283X_PER_BASE_40000000    (0x40000000)

/* Base Address Registers Offset */
#define ST_BASE_OFFSET     (0x003000)
#define GPIO_PAD_OFFSET     (0x100000)
#define CLOCK_BASE_OFFSET (0x101000)
#define GPIO_BASE_OFFSET (0x200000)
#define SPI0_BASE_OFFSET (0x204000)
#define BSC0_BASE_OFFSET (0x205000)
#define GPIO_PWM_OFFSET     (0x20C000)
#define AUX_BASE_OFFSET     (0x215000)
#define SPI1_BASE_OFFSET (0x215080)
#define SPI2_BASE_OFFSET (0x2150C0)
#define BSC1_BASE_OFFSET (0x804000)
#define BSC2_BASE_OFFSET (0x805000)

/* IRQ */
#define MAX_HANDLERS       72
#define IRQ_SYSTEM_TIMER_0 0
#define IRQ_SYSTEM_TIMER_1  1
#define IRQ_SYSTEM_TIMER_2 2
#define IRQ_SYSTEM_TIMER_3 3
#define IRQ_USB      9
#define IRQ_AUX      29
#define IRQ_PCM      55
#define IRQ_ARM_TIMER     64
#define IRQ_ARM_MAILBOX     65

/* Interrupt Controler */
#define IRQ_BASE     (PER_BASE + 0xB200)
#define IRQ_PEND_BASIC      __REG32(IRQ_BASE + 0x0000)
#define IRQ_PEND1    __REG32(IRQ_BASE + 0x0004)
#define IRQ_PEND2    __REG32(IRQ_BASE + 0x0008)
#define IRQ_FIQ_CONTROL     __REG32(IRQ_BASE + 0x000C)
#define IRQ_ENABLE1  __REG32(IRQ_BASE + 0x0010)
#define IRQ_ENABLE2  __REG32(IRQ_BASE + 0x0014)
#define IRQ_ENABLE_BASIC    __REG32(IRQ_BASE + 0x0018)
#define IRQ_DISABLE1 __REG32(IRQ_BASE + 0x001C)
#define IRQ_DISABLE2 __REG32(IRQ_BASE + 0x0020)
#define IRQ_DISABLE_BASIC   __REG32(IRQ_BASE + 0x0024)


/* Defines for WDT*/
#define PM_BASE  (PER_BASE  + GPIO_PAD_OFFSET)
#define PM_RSTC  __REG32(PM_BASE + 0x001C)
#define PM_RSTS  __REG32(PM_BASE + 0x0020)
#define PM_WDOG  __REG32(PM_BASE + 0x0024)

#define PM_PASSWORD     0x5a000000
#define PM_WDOG_TIME_SET    0x000fffff
#define PM_RSTC_WRCFG_CLR    0xffffffcf
#define PM_RSTS_HADWRH_SET    0x00000040
#define PM_RSTC_WRCFG_SET    0x00000030
#define PM_RSTC_WRCFG_FULL_RESET    0x00000020
#define PM_RSTC_RESET 0x00000102
#define PM_RSTS_PARTITION_CLR 0xfffffaaa

/* Defines for System Timer */
#define STIMER_BASE  (PER_BASE  + ST_BASE_OFFSET)
#define STIMER_CS    __REG32(STIMER_BASE + 0x0000)
#define STIMER_CLO   __REG32(STIMER_BASE + 0x0004)
#define STIMER_CHI   __REG32(STIMER_BASE + 0x0008)
#define STIMER_C0    __REG32(STIMER_BASE + 0x000C)
#define STIMER_C1    __REG32(STIMER_BASE + 0x0010)
#define STIMER_C2    __REG32(STIMER_BASE + 0x0014)
#define STIMER_C3    __REG32(STIMER_BASE + 0x0018)

#define DELAY_MICROS(micros) \
    do{ \
 rt_uint32_t compare = STIMER_CLO + micros * 25; \
 while (STIMER_CLO < compare); \
    } while (0) \

/* Defines for GPIO */
#define BCM283X_GPIO_BASE     (PER_BASE + GPIO_BASE_OFFSET)
#define BCM283X_GPIO_GPFSEL(n) __REG32(BCM283X_GPIO_BASE + 0x0000 + 0x4 * (n)) /* GPIO Function Select 32bit R/W */
#define BCM283X_GPIO_GPSET(n) __REG32(BCM283X_GPIO_BASE + 0x001C + 0x4 * (n)) /* GPIO Pin Output Set */
#define BCM283X_GPIO_GPCLR(n) __REG32(BCM283X_GPIO_BASE + 0x0028 + 0x4 * (n)) /* GPIO Pin Output Clear */
#define BCM2835_GPIO_GPLEV(n) __REG32(BCM283X_GPIO_BASE + 0x0034 + 0x4 * (n)) /* GPIO Pin Level */
#define BCM283X_GPIO_GPEDS(n) __REG32(BCM283X_GPIO_BASE + 0x0040 + 0x4 * (n)) /* GPIO Pin Event Detect Status */
#define BCM283X_GPIO_GPREN(n) __REG32(BCM283X_GPIO_BASE + 0x004c + 0x4 * (n)) /* GPIO Pin Rising Edge Detect Enable */
#define BCM283X_GPIO_GPFEN(n) __REG32(BCM283X_GPIO_BASE + 0x0058 + 0x4 * (n)) /* GPIO Pin Falling Edge Detect Enable */
#define BCM283X_GPIO_GPHEN(n) __REG32(BCM283X_GPIO_BASE + 0x0064 + 0x4 * (n)) /* GPIO Pin High Detect Enable  */
#define BCM283X_GPIO_GPLEN(n) __REG32(BCM283X_GPIO_BASE + 0x0070 + 0x4 * (n)) /* GPIO Pin Low Detect Enable */
#define BCM283X_GPIO_GPAREN(n) __REG32(BCM283X_GPIO_BASE + 0x007C + 0x4 * (n)) /* GPIO Pin Async. Rising Edge Detect */
#define BCM283X_GPIO_GPAFEN(n) __REG32(BCM283X_GPIO_BASE + 0x0088 + 0x4 * (n)) /* GPIO Pin Async. Falling Edge Detect */
#define BCM283X_GPIO_GPPUD     __REG32(BCM283X_GPIO_BASE + 0x0094)     /* GPIO Pin Pull-up/down Enable */
#define BCM283X_GPIO_GPPUDCLK(n)    __REG32(BCM283X_GPIO_BASE + 0x0098 + 0x4 * (n)) /* GPIO Pin Pull-up/down Enable Clock */

#define GPIO_FSEL_NUM(pin)  (pin/10)
#define GPIO_FSEL_SHIFT(pin)  ((pin%10)*3)
#define GPIO_FSEL(pin, mode) \
    do{ \
 __sync_synchronize(); \
 BCM283X_GPIO_GPFSEL(GPIO_FSEL_NUM(pin)) |= ((mode & BCM283X_GPIO_FSEL_MASK) << GPIO_FSEL_SHIFT(pin)); \
    } while (0) \

/* Defines for I2C */
#define BCM283X_BSC0_BASE     (PER_BASE + BSC0_BASE_OFFSET)    //for i2c0
#define BCM283X_BSC1_BASE     (PER_BASE + BSC1_BASE_OFFSET)    //for i2c1
#define BCM283X_BSC2_BASE     (PER_BASE + BSC2_BASE_OFFSET)    //for hdmi i2c not use

#define BCM283X_BSC_C(BASE)  __REG32(BASE + 0x0000)    /* BSC Master Control */
#define BCM283X_BSC_S(BASE)  __REG32(BASE + 0x0004)    /* BSC Master Status */
#define BCM283X_BSC_DLEN(BASE)      __REG32(BASE + 0x0008)    /* BSC Master Data Length */
#define BCM283X_BSC_A(BASE)  __REG32(BASE + 0x000c)    /* BSC Master Slave Address */
#define BCM283X_BSC_FIFO(BASE)      __REG32(BASE + 0x0010)    /* BSC Master Data FIFO */
#define BCM283X_BSC_DIV(BASE)       __REG32(BASE + 0x0014)    /* BSC Master Clock Divider */
#define BCM283X_BSC_DEL(BASE)       __REG32(BASE + 0x0018)    /* BSC Master Data Delay */
#define BCM283X_BSC_CLKT(BASE)      __REG32(BASE + 0x001c)    /* BSC Master Clock Stretch Timeout */

/* Register masks for C Register */
#define BSC_C_I2CEN      0x00008000 /* I2C Enable, 0 = disabled, 1 = enabled */
#define BSC_C_INTR      0x00000400 /* Interrupt on RX */
#define BSC_C_INTT      0x00000200 /* Interrupt on TX */
#define BSC_C_INTD      0x00000100 /* Interrupt on DONE */
#define BSC_C_ST      0x00000080 /* Start transfer, 1 = Start a new transfer */
#define BSC_C_CLEAR_1   0x00000020 /* Clear FIFO Clear */
#define BSC_C_CLEAR_2   0x00000010 /* Clear FIFO Clear */
#define BSC_C_READ       0x00000001 /* Read transfer */

/* Register masks for S Register */
#define BSC_S_CLKT      0x00000200 /* Clock stretch timeout */
#define BSC_S_ERR      0x00000100 /* ACK error */
#define BSC_S_RXF       0x00000080 /* RXF FIFO full, 0 = FIFO is not full, 1 = FIFO is full */
#define BSC_S_TXE       0x00000040 /* TXE FIFO full, 0 = FIFO is not full, 1 = FIFO is full */
#define BSC_S_RXD       0x00000020 /* RXD FIFO contains data */
#define BSC_S_TXD       0x00000010 /* TXD FIFO can accept data */
#define BSC_S_RXR      0x00000008 /* RXR FIFO needs reading (full) */
#define BSC_S_TXW      0x00000004 /* TXW FIFO needs writing (full) */
#define BSC_S_DONE      0x00000002 /* Transfer DONE */
#define BSC_S_TA      0x00000001 /* Transfer Active */

#define BSC_FIFO_SIZE  (16)  /* BSC FIFO size */

/* Defines for SPI */
#define BCM283X_SPI0_BASE     (PER_BASE + SPI0_BASE_OFFSET)
#define BCM283X_SPI1_BASE     (PER_BASE + SPI1_BASE_OFFSET)
#define BCM283X_SPI2_BASE     (PER_BASE + SPI2_BASE_OFFSET)

#define BCM283X_SPI0_CS(BASE) __REG32(BASE + 0x0000) /* SPI Master Control and Status */
#define BCM283X_SPI0_FIFO(BASE) __REG32(BASE + 0x0004) /* SPI Master TX and RX FIFOs */
#define BCM283X_SPI0_CLK(BASE) __REG32(BASE + 0x0008) /* SPI Master Clock Divider */
#define BCM283X_SPI0_DLEN(BASE) __REG32(BASE + 0x000c) /* SPI Master Data Length */
#define BCM283X_SPI0_LTOH(BASE) __REG32(BASE + 0x0010) /* SPI LOSSI mode TOH */
#define BCM283X_SPI0_DC(BASE) __REG32(BASE + 0x0014) /* SPI DMA DREQ Controls */

/* Register masks for SPI0_CS */
#define BCM283X_SPI0_CS_LEN_LONG    0x02000000 /* Enable Long data word in Lossi mode if DMA_LEN is set */
#define BCM283X_SPI0_CS_DMA_LEN 0x01000000 /* Enable DMA mode in Lossi mode */
#define BCM283X_SPI0_CS_CSPOL2 0x00800000 /* Chip Select 2 Polarity */
#define BCM283X_SPI0_CS_CSPOL1 0x00400000 /* Chip Select 1 Polarity */
#define BCM283X_SPI0_CS_CSPOL0 0x00200000 /* Chip Select 0 Polarity */
#define BCM283X_SPI0_CS_RXF     0x00100000 /* RXF - RX FIFO Full */
#define BCM283X_SPI0_CS_RXR     0x00080000 /* RXR RX FIFO needs Reading (full) */
#define BCM283X_SPI0_CS_TXD     0x00040000 /* TXD TX FIFO can accept Data */
#define BCM283X_SPI0_CS_RXD     0x00020000 /* RXD RX FIFO contains Data */
#define BCM283X_SPI0_CS_DONE 0x00010000 /* Done transfer Done */
#define BCM283X_SPI0_CS_TE_EN 0x00008000 /* Unused */
#define BCM283X_SPI0_CS_LMONO 0x00004000 /* Unused */
#define BCM283X_SPI0_CS_LEN     0x00002000 /* LEN LoSSI enable */
#define BCM283X_SPI0_CS_REN     0x00001000 /* REN Read Enable */
#define BCM283X_SPI0_CS_ADCS 0x00000800 /* ADCS Automatically Deassert Chip Select */
#define BCM283X_SPI0_CS_INTR 0x00000400 /* INTR Interrupt on RXR */
#define BCM283X_SPI0_CS_INTD 0x00000200 /* INTD Interrupt on Done */
#define BCM283X_SPI0_CS_DMAEN 0x00000100 /* DMAEN DMA Enable */
#define BCM283X_SPI0_CS_TA     0x00000080 /* Transfer Active */
#define BCM283X_SPI0_CS_CSPOL 0x00000040 /* Chip Select Polarity */
#define BCM283X_SPI0_CS_CLEAR 0x00000030 /* Clear FIFO Clear RX and TX */
#define BCM283X_SPI0_CS_CLEAR_RX    0x00000020 /* Clear FIFO Clear RX  */
#define BCM283X_SPI0_CS_CLEAR_TX    0x00000010 /* Clear FIFO Clear TX  */
#define BCM283X_SPI0_CS_CPOL 0x00000008 /* Clock Polarity */
#define BCM283X_SPI0_CS_CPHA 0x00000004 /* Clock Phase */
#define BCM283X_SPI0_CS_CS     0x00000003 /* Chip Select */

/* ARM Timer */
#define ARM_TIMER_BASE  (PER_BASE + 0xB000)
#define ARM_TIMER_LOAD  __REG32(ARM_TIMER_BASE + 0x400)
#define ARM_TIMER_VALUE  __REG32(ARM_TIMER_BASE + 0x404)
#define ARM_TIMER_CTRL  __REG32(ARM_TIMER_BASE + 0x408)
#define ARM_TIMER_IRQCLR     __REG32(ARM_TIMER_BASE + 0x40C)
#define ARM_TIMER_RAWIRQ     __REG32(ARM_TIMER_BASE + 0x410)
#define ARM_TIMER_MASKIRQ     __REG32(ARM_TIMER_BASE + 0x414)
#define ARM_TIMER_RELOAD     __REG32(ARM_TIMER_BASE + 0x418)
#define ARM_TIMER_PREDIV     __REG32(ARM_TIMER_BASE + 0x41C)
#define ARM_TIMER_CNTR  __REG32(ARM_TIMER_BASE + 0x420)

/* ARM Core Timer */
#define C0TIMER_INTCTL   __REG32(PER_BASE_40000000 + 0x40)  /* Core0 timers Interrupt control */
#define C1TIMER_INTCTL  __REG32(PER_BASE_40000000 + 0x44)  /* Core1 timers Interrupt control */
#define C2TIMER_INTCTL  __REG32(PER_BASE_40000000 + 0x48)  /* Core2 timers Interrupt control */
#define C3TIMER_INTCTL  __REG32(PER_BASE_40000000 + 0x4C)  /* Core3 timers Interrupt control */
#define CORETIMER_INTCTL(n)     __REG32(PER_BASE_40000000 + 0x40 + n*4)  /* Coren timers Interrupt control */

/*
 *  Gtimer IRQ flag
 */
#define SYSTEM_TIMER_IRQ_0    (1 << 0)
#define SYSTEM_TIMER_IRQ_1    (1 << 1)
#define SYSTEM_TIMER_IRQ_2    (1 << 2)
#define SYSTEM_TIMER_IRQ_3    (1 << 3)

#define NON_SECURE_TIMER_IRQ    (1 << 1)
rt_inline void core_timer_enable(int cpu_id)
{
    CORETIMER_INTCTL(cpu_id) |= NON_SECURE_TIMER_IRQ;
}

/* ARM Core Mailbox interrupt */
#define C0MB_INTCTL      __REG32(PER_BASE_40000000 + 0x50)  /* Core0 Mailboxes Interrupt control */
#define C1MB_INTCTL      __REG32(PER_BASE_40000000 + 0x54)  /* Core1 Mailboxes Interrupt control */
#define C2MB_INTCTL      __REG32(PER_BASE_40000000 + 0x58)  /* Core2 Mailboxes Interrupt control */
#define C3MB_INTCTL      __REG32(PER_BASE_40000000 + 0x5C)  /* Core3 Mailboxes Interrupt control */
#define COREMB_INTCTL(n)     __REG32(PER_BASE_40000000 + 0x50 + 4*n)  /* Coren Mailboxes Interrupt control */

/* ARM Core IRQ/FIQ status */
#define C0_IRQSOURCE  __REG32(PER_BASE_40000000 + 0x60)  /* Core0 IRQ Source */
#define C1_IRQSOURCE  __REG32(PER_BASE_40000000 + 0x64)  /* Core1 IRQ Source */
#define C2_IRQSOURCE  __REG32(PER_BASE_40000000 + 0x68)  /* Core2 IRQ Source */
#define C3_IRQSOURCE  __REG32(PER_BASE_40000000 + 0x6C)  /* Core3 IRQ Source */
#define C0_FIQSOURCE  __REG32(PER_BASE_40000000 + 0x70)  /* Core0 FIQ Source */
#define C1_FIQSOURCE  __REG32(PER_BASE_40000000 + 0x74)  /* Core1 FIQ Source */
#define C2_FIQSOURCE  __REG32(PER_BASE_40000000 + 0x78)  /* Core2 FIQ Source */
#define C3_FIQSOURCE  __REG32(PER_BASE_40000000 + 0x7C)  /* Core3 FIQ Source */
#define CORE_IRQSOURCE(n)     __REG32(PER_BASE_40000000 + 0x60+ n*0x4)
#define CORE_FIQSOURCE(n)     __REG32(PER_BASE_40000000 + 0x70+ n*0x4)

#define CORE_MAILBOX3_SET(n) __REG32(PER_BASE_40000000 + 0x8C + n*0x10)
#define CORE_MAILBOX3_CLEAR(n)      __REG32(PER_BASE_40000000 + 0xCC + n*0x10)
#define CORE_MAILBOX2_SET(n) __REG32(PER_BASE_40000000 + 0x88 + n*0x10)
#define CORE_MAILBOX2_CLEAR(n)      __REG32(PER_BASE_40000000 + 0xC8 + n*0x10)
#define CORE_MAILBOX1_SET(n) __REG32(PER_BASE_40000000 + 0x84 + n*0x10)
#define CORE_MAILBOX1_CLEAR(n)      __REG32(PER_BASE_40000000 + 0xC4 + n*0x10)
#define CORE_MAILBOX0_SET(n) __REG32(PER_BASE_40000000 + 0x80 + n*0x10)
#define CORE_MAILBOX0_CLEAR(n)      __REG32(PER_BASE_40000000 + 0xC0 + n*0x10)

/* For SMP IPI use MailBox0 */
#define IPI_MAILBOX_SET  CORE_MAILBOX0_SET
#define IPI_MAILBOX_CLEAR     CORE_MAILBOX0_CLEAR
#define IPI_MAILBOX_INT_MASK (0x01)
rt_inline void enable_cpu_ipi_intr(int cpu_id)
{
    COREMB_INTCTL(cpu_id) = IPI_MAILBOX_INT_MASK;
}

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
    BCM283X_SPI_CLOCK_DIVIDER_8192 = 8192,    /*!< 8192 = 30.51757813kHz on Rpi2, 48.828125kHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_4096 = 4096,    /*!< 4096 = 61.03515625kHz on Rpi2, 97.65625kHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_2048 = 2048,    /*!< 2048 = 122.0703125kHz on Rpi2, 195.3125kHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_1024 = 1024,    /*!< 1024 = 244.140625kHz on Rpi2, 390.625kHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_512  = 512,     /*!< 512 = 488.28125kHz on Rpi2, 781.25kHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_256  = 256,     /*!< 256 = 976.5625kHz on Rpi2, 1.5625MHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_128  = 128,     /*!< 128 = 1.953125MHz on Rpi2, 3.125MHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_64   = 64,      /*!< 64 = 3.90625MHz on Rpi2, 6.250MHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_32   = 32,      /*!< 32 = 7.8125MHz on Rpi2, 12.5MHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_16   = 16,      /*!< 16 = 15.625MHz on Rpi2, 25MHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_8    = 8,       /*!< 8 = 31.25MHz on Rpi2, 50MHz on RPI3 */
    BCM283X_SPI_CLOCK_DIVIDER_4    = 4,       /*!< 4 = 62.5MHz on Rpi2, 100MHz on RPI3. Dont expect this speed to work reliably. */
    BCM283X_SPI_CLOCK_DIVIDER_2    = 2,       /*!< 2 = 125MHz on Rpi2, 200MHz on RPI3, fastest you can get. Dont expect this speed to work reliably.*/
    BCM283X_SPI_CLOCK_DIVIDER_1    = 1 /*!< 1 = 3.814697260kHz on Rpi2, 6.1035156kHz on RPI3, same as 0/65536 */
};

/*redefine for raspi*/
typedef gpio_function_select raspi_pin_select;
typedef enum
{
    RPI_GPIO_P1_01 = BCM_GPIO_PIN_NULL,
    RPI_GPIO_P1_02 = BCM_GPIO_PIN_NULL,
    RPI_GPIO_P1_03 = BCM_GPIO_PIN_2,
    RPI_GPIO_P1_04 = BCM_GPIO_PIN_NULL,
    RPI_GPIO_P1_05 = BCM_GPIO_PIN_3,
    RPI_GPIO_P1_06 = BCM_GPIO_PIN_NULL,
    RPI_GPIO_P1_07 = BCM_GPIO_PIN_4,
    RPI_GPIO_P1_08 = BCM_GPIO_PIN_14,
    RPI_GPIO_P1_09 = BCM_GPIO_PIN_NULL,
    RPI_GPIO_P1_10 = BCM_GPIO_PIN_15,
    RPI_GPIO_P1_11 = BCM_GPIO_PIN_17,
    RPI_GPIO_P1_12 = BCM_GPIO_PIN_18,
    RPI_GPIO_P1_13 = BCM_GPIO_PIN_27,
    RPI_GPIO_P1_14 = BCM_GPIO_PIN_NULL,
    RPI_GPIO_P1_15 = BCM_GPIO_PIN_22,
    RPI_GPIO_P1_16 = BCM_GPIO_PIN_23,
    RPI_GPIO_P1_17 = BCM_GPIO_PIN_NULL,
    RPI_GPIO_P1_18 = BCM_GPIO_PIN_24,
    RPI_GPIO_P1_19 = BCM_GPIO_PIN_10,
    RPI_GPIO_P1_20 = BCM_GPIO_PIN_NULL,
    RPI_GPIO_P1_21 = BCM_GPIO_PIN_9,
    RPI_GPIO_P1_22 = BCM_GPIO_PIN_25,
    RPI_GPIO_P1_23 = BCM_GPIO_PIN_11,
    RPI_GPIO_P1_24 = BCM_GPIO_PIN_8,
    RPI_GPIO_P1_25 = BCM_GPIO_PIN_NULL,
    RPI_GPIO_P1_26 = BCM_GPIO_PIN_7,
    RPI_GPIO_P1_27 = BCM_GPIO_PIN_0,
    RPI_GPIO_P1_28 = BCM_GPIO_PIN_1,
    RPI_GPIO_P1_29 = BCM_GPIO_PIN_5,
    RPI_GPIO_P1_30 = BCM_GPIO_PIN_NULL,
    RPI_GPIO_P1_31 = BCM_GPIO_PIN_6,
    RPI_GPIO_P1_32 = BCM_GPIO_PIN_12,
    RPI_GPIO_P1_33 = BCM_GPIO_PIN_13,
    RPI_GPIO_P1_34 = BCM_GPIO_PIN_NULL,
    RPI_GPIO_P1_35 = BCM_GPIO_PIN_19,
    RPI_GPIO_P1_36 = BCM_GPIO_PIN_16,
    RPI_GPIO_P1_37 = BCM_GPIO_PIN_26,
    RPI_GPIO_P1_38 = BCM_GPIO_PIN_20,
    RPI_GPIO_P1_39 = BCM_GPIO_PIN_NULL,
    RPI_GPIO_P1_40 = BCM_GPIO_PIN_21,
} raspi_gpio_pin;

typedef enum
{
    BCM283X_I2C_CLOCK_DIVIDER_2500  = 2500,      /* 2500 = 10us = 100 kHz */
    BCM283X_I2C_CLOCK_DIVIDER_626   = 626,       /* 622 = 2.504us = 399.3610 kHz */
    BCM283X_I2C_CLOCK_DIVIDER_150   = 150,       /* 150 = 60ns = 1.666 MHz (default at reset) */
    BCM283X_I2C_CLOCK_DIVIDER_148   = 148 /* 148 = 59ns = 1.689 MHz */
} i2c_clock_divider;

typedef enum
{
    BCM283X_I2C_REASON_OK    = 0x00,      /* Success */
    BCM283X_I2C_REASON_ERROR_NACK   = 0x01,      /* Received a NACK */
    BCM283X_I2C_REASON_ERROR_CLKT   = 0x02,      /* Received Clock Stretch Timeout */
    BCM283X_I2C_REASON_ERROR_DATA   = 0x04       /* Not all data is sent / received */
} i2c_reason_codes;

#endif
