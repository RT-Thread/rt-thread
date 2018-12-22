/*
 * File      : x1000.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-11-19     Urey         the first version
 */

#ifndef X1000_H__
#define X1000_H__

#ifndef __ASSEMBLY__

// typedef unsigned int size_t;
#define u64 unsigned long long
#define u32 unsigned int
#define u16 unsigned short
#define u8  unsigned char

#define U64 unsigned long long
#define U32 unsigned int
#define U16 unsigned short
#define U8  unsigned char

#define S64 signed long long
#define S32 int
#define S16 short int
#define S8  signed char

#define cache_unroll(base,op)               \
    __asm__ __volatile__("                  \
        .set noreorder;                     \
        .set mips3;                         \
        cache %1, (%0);                     \
        .set mips0;                         \
        .set reorder"                       \
        :                                   \
        : "r" (base),                       \
          "i" (op));

/* cpu pipeline flush */
static inline void jz_sync(void)
{
    __asm__ volatile ("sync");
}

static inline void writeb(u8 value, u32 address)
{
    *((volatile u8 *) address) = value;
}
static inline void writew( u16 value, u32 address)
{
    *((volatile u16 *) address) = value;
}
static inline void writel(u32 value, u32 address)
{
    *((volatile u32 *) address) = value;
}

static inline u8 readb(u32 address)
{
    return *((volatile u8 *)address);
}

static inline u16 readw(u32 address)
{
    return *((volatile u16 *)address);
}

static inline u32 readl(u32 address)
{
    return *((volatile u32 *)address);
}

static inline void jz_writeb(u32 address, u8 value)
{
    *((volatile u8 *)address) = value;
}

static inline void jz_writew(u32 address, u16 value)
{
    *((volatile u16 *)address) = value;
}

static inline void jz_writel(u32 address, u32 value)
{
    *((volatile u32 *)address) = value;
}

static inline u8 jz_readb(u32 address)
{
    return *((volatile u8 *)address);
}

static inline u16 jz_readw(u32 address)
{
    return *((volatile u16 *)address);
}

static inline u32 jz_readl(u32 address)
{
    return *((volatile u32 *)address);
}

#define REG8(addr)      *((volatile u8 *)(addr))
#define REG16(addr)     *((volatile u16 *)(addr))
#define REG32(addr)     *((volatile u32 *)(addr))

#define BIT(n)          (0x01u << (n))

#else

#define REG8(addr)  (addr)
#define REG16(addr) (addr)
#define REG32(addr) (addr)

#endif /* !ASSEMBLY */


//----------------------------------------------------------------------
// Register Definitions
//
/* AHB0 BUS Devices Base */
#define HARB0_BASE  0xB3000000
#define EMC_BASE    0xB3010000
#define DDRC_BASE   0xB3020000
#define MDMAC_BASE  0xB3030000
#define LCD_BASE    0xB3050000
#define TVE_BASE    0xB3050000
#define SLCD_BASE   0xB3050000
#define CIM_BASE    0xB3060000
#define IPU_BASE    0xB3080000
/* AHB1 BUS Devices Base */
#define HARB1_BASE  0xB3200000
#define DMAGP0_BASE 0xB3210000
#define DMAGP1_BASE 0xB3220000
#define DMAGP2_BASE 0xB3230000
#define MC_BASE     0xB3250000
#define ME_BASE     0xB3260000
#define DEBLK_BASE  0xB3270000
#define IDCT_BASE   0xB3280000
#define CABAC_BASE  0xB3290000
#define TCSM0_BASE  0xB32B0000
#define TCSM1_BASE  0xB32C0000
#define SRAM_BASE   0xB32D0000
/* AHB2 BUS Devices Base */
#define HARB2_BASE  0xB3400000
#define NEMC_BASE   0xB3410000
#define DMAC_BASE   0xB3420000
#define UHC_BASE    0xB3430000
#define UDC_BASE    0xB3440000
#define GPS_BASE    0xB3480000
#define ETHC_BASE   0xB34B0000
#define BCH_BASE    0xB34D0000
#define MSC0_BASE   0xB3450000
#define MSC1_BASE   0xB3460000
#define MSC2_BASE   0xB3470000

/* APB BUS Devices Base */
#define CPM_BASE    0xB0000000
#define INTC_BASE   0xB0001000
#define TCU_BASE    0xB0002000
#define WDT_BASE    0xB0002000
#define OST_BASE    0xB2000000      /* OS Timer */
#define RTC_BASE    0xB0003000
#define GPIO_BASE   0xB0010000
#define AIC_BASE    0xB0020000
#define DMIC_BASE   0xB0021000
#define ICDC_BASE   0xB0020000
#define UART0_BASE  0xB0030000
#define UART1_BASE  0xB0031000
#define UART2_BASE  0xB0032000
#define UART3_BASE  0xB0033000
#define SCC_BASE    0xB0040000
#define SSI0_BASE   0xB0043000
#define SSI1_BASE   0xB0044000
#define SSI2_BASE   0xB0045000
#define I2C0_BASE   0xB0050000
#define I2C1_BASE   0xB0051000
#define PS2_BASE    0xB0060000
#define SADC_BASE   0xB0070000
#define OWI_BASE    0xB0072000
#define TSSI_BASE   0xB0073000

/* NAND CHIP Base Address*/
#define NEMC_CS1_IOBASE 0Xbb000000
#define NEMC_CS2_IOBASE 0Xba000000
#define NEMC_CS3_IOBASE 0Xb9000000
#define NEMC_CS4_IOBASE 0Xb8000000
#define NEMC_CS5_IOBASE 0Xb7000000
#define NEMC_CS6_IOBASE 0Xb6000000

/*********************************************************************************************************
**   WDT
*********************************************************************************************************/
#define WDT_TDR         (WDT_BASE + 0x00)
#define WDT_TCER        (WDT_BASE + 0x04)
#define WDT_TCNT        (WDT_BASE + 0x08)
#define WDT_TCSR        (WDT_BASE + 0x0C)

#define REG_WDT_TDR     REG16(WDT_TDR)
#define REG_WDT_TCER    REG8(WDT_TCER)
#define REG_WDT_TCNT    REG16(WDT_TCNT)
#define REG_WDT_TCSR    REG16(WDT_TCSR)

#define WDT_TSCR_WDTSC          (1 << 16)

#define WDT_TCSR_PRESCALE_1         (0 << 3)
#define WDT_TCSR_PRESCALE_4         (1 << 3)
#define WDT_TCSR_PRESCALE_16        (2 << 3)
#define WDT_TCSR_PRESCALE_64        (3 << 3)
#define WDT_TCSR_PRESCALE_256       (4 << 3)
#define WDT_TCSR_PRESCALE_1024      (5 << 3)

#define WDT_TCSR_EXT_EN         (1 << 2)
#define WDT_TCSR_RTC_EN         (1 << 1)
#define WDT_TCSR_PCK_EN         (1 << 0)

#define WDT_TCER_TCEN           (1 << 0)

/*********************************************************************************************************
**   ÖÐ¶ÏÔ´
*********************************************************************************************************/
/* INTC (Interrupt Controller) */
#define INTC_ISR(n)             (INTC_BASE + 0x00 + (n) * 0x20)
#define INTC_IMR(n)             (INTC_BASE + 0x04 + (n) * 0x20)
#define INTC_IMSR(n)            (INTC_BASE + 0x08 + (n) * 0x20)
#define INTC_IMCR(n)            (INTC_BASE + 0x0c + (n) * 0x20)
#define INTC_IPR(n)             (INTC_BASE + 0x10 + (n) * 0x20)

#define REG_INTC_ISR(n)         REG32(INTC_ISR((n)))
#define REG_INTC_IMR(n)         REG32(INTC_IMR((n)))
#define REG_INTC_IMSR(n)        REG32(INTC_IMSR((n)))
#define REG_INTC_IMCR(n)        REG32(INTC_IMCR((n)))
#define REG_INTC_IPR(n)         REG32(INTC_IPR((n)))

// interrupt controller interrupts
#define IRQ_DMIC                0
#define IRQ_AIC0                1
#define IRQ_RESERVED2           2
#define IRQ_RESERVED3           3
#define IRQ_RESERVED4           4
#define IRQ_RESERVED5           5
#define IRQ_RESERVED6           6
#define IRQ_SFC                 7
#define IRQ_SSI0                8
#define IRQ_RESERVED9           9
#define IRQ_PDMA                10
#define IRQ_PDMAD               11
#define IRQ_RESERVED12          12
#define IRQ_RESERVED13          13
#define IRQ_GPIO3               14
#define IRQ_GPIO2               15
#define IRQ_GPIO1               16
#define IRQ_GPIO0               17
#define IRQ_RESERVED18          18
#define IRQ_RESERVED19          19
#define IRQ_RESERVED20          20
#define IRQ_OTG                 21
#define IRQ_RESERVED22          22
#define IRQ_AES                 23
#define IRQ_RESERVED24          24
#define IRQ_TCU2                25
#define IRQ_TCU1                26
#define IRQ_TCU0                27
#define IRQ_RESERVED28          28
#define IRQ_RESERVED29          29
#define IRQ_CIM                 30
#define IRQ_LCD                 31
#define IRQ_RTC                 32
#define IRQ_RESERVED33          33
#define IRQ_RESERVED34          34
#define IRQ_RESERVED35          35
#define IRQ_MSC1                36
#define IRQ_MSC0                37
#define IRQ_SCC                 38
#define IRQ_RESERVED39          39
#define IRQ_PCM0                40
#define IRQ_RESERVED41          41
#define IRQ_RESERVED42          42
#define IRQ_RESERVED43          43
#define IRQ_HARB2               44
#define IRQ_RESERVED45          45
#define IRQ_HARB0               46
#define IRQ_CPM                 47
#define IRQ_RESERVED48          48
#define IRQ_UART2               49
#define IRQ_UART1               50
#define IRQ_UART0               51
#define IRQ_DDR                 52
#define IRQ_RESERVED53          53
#define IRQ_EFUSE               54
#define IRQ_MAC                 55
#define IRQ_RESERVED56          56
#define IRQ_RESERVED57          57
#define IRQ_I2C2                58
#define IRQ_I2C1                59
#define IRQ_I2C0                60
#define IRQ_PDMAM               61
#define IRQ_JPEG                62
#define IRQ_RESERVED63          63

#define IRQ_INTC_MAX            63

#ifndef __ASSEMBLY__

#define __intc_unmask_irq(n)    (REG_INTC_IMCR((n)/32) = (1 << ((n)%32)))
#define __intc_mask_irq(n)      (REG_INTC_IMSR((n)/32) = (1 << ((n)%32)))
#define __intc_ack_irq(n)       (REG_INTC_IPR((n)/32) = (1 << ((n)%32)))        /* A dummy ack, as the Pending Register is Read Only. Should we remove __intc_ack_irq() */

#endif /* !__ASSEMBLY__ */

#endif /* _JZ_M150_H_ */
