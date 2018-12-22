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

#ifndef __X1000_H__
#define __X1000_H__

#include "../common/mips.h"

#ifndef __ASSEMBLY__

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

#define BIT(n)          (0x01u << (n))
#define BIT0            (0x01u <<  0)
#define BIT1            (0x01u <<  1)
#define BIT2            (0x01u <<  2)
#define BIT3            (0x01u <<  3)
#define BIT4            (0x01u <<  4)
#define BIT5            (0x01u <<  5)
#define BIT6            (0x01u <<  6)
#define BIT7            (0x01u <<  7)
#define BIT8            (0x01u <<  8)
#define BIT9            (0x01u <<  9)
#define BIT10           (0x01u << 10)
#define BIT11           (0x01u << 11)
#define BIT12           (0x01u << 12)
#define BIT13           (0x01u << 13)
#define BIT14           (0x01u << 14)
#define BIT15           (0x01u << 15)
#define BIT16           (0x01u << 16)
#define BIT17           (0x01u << 17)
#define BIT18           (0x01u << 18)
#define BIT19           (0x01u << 19)
#define BIT20           (0x01u << 20)
#define BIT21           (0x01u << 21)
#define BIT22           (0x01u << 22)
#define BIT23           (0x01u << 23)
#define BIT24           (0x01u << 24)
#define BIT25           (0x01u << 25)
#define BIT26           (0x01u << 26)
#define BIT27           (0x01u << 27)
#define BIT28           (0x01u << 28)
#define BIT29           (0x01u << 29)
#define BIT30           (0x01u << 30)
#define BIT31           (0x01u << 31)

/* Generate the bit field mask from msb to lsb */
#define BITS_H2L(msb, lsb)  ((0xFFFFFFFF >> (32-((msb)-(lsb)+1))) << (lsb))


/* Get the bit field value from the data which is read from the register */
#define get_bf_value(data, lsb, mask)  (((data) & (mask)) >> (lsb))

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
//#define UDC_BASE    0xB3440000
#define SFC_BASE	 0xB3440000
#define GPS_BASE    0xB3480000
#define ETHC_BASE   0xB34B0000
#define BCH_BASE    0xB34D0000
#define MSC0_BASE   0xB3450000
#define MSC1_BASE   0xB3460000
#define MSC2_BASE   0xB3470000
#define OTG_BASE    0xb3500000

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
#define SCC_BASE    0xB0040000
#define SSI0_BASE   0xB0043000
#define SSI1_BASE   0xB0044000
#define SSI2_BASE   0xB0045000
#define I2C0_BASE   0xB0050000
#define I2C1_BASE   0xB0051000
#define I2C2_BASE   0xB0052000
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
#define WDT_TDR         (0x00)
#define WDT_TCER        (0x04)
#define WDT_TCNT        (0x08)
#define WDT_TCSR        (0x0C)

#define REG_WDT_TDR     REG16(WDT_BASE + WDT_TDR)
#define REG_WDT_TCER    REG8(WDT_BASE + WDT_TCER)
#define REG_WDT_TCNT    REG16(WDT_BASE + WDT_TCNT)
#define REG_WDT_TCSR    REG16(WDT_BASE + WDT_TCSR)

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

/* RTC Reg */
#define RTC_RTCCR		(0x00)	/* rw, 32, 0x00000081 */
#define RTC_RTCSR		(0x04)	/* rw, 32, 0x???????? */
#define RTC_RTCSAR		(0x08)	/* rw, 32, 0x???????? */
#define RTC_RTCGR		(0x0c)	/* rw, 32, 0x0??????? */
#define RTC_HCR			(0x20)  /* rw, 32, 0x00000000 */
#define RTC_HWFCR		(0x24)  /* rw, 32, 0x0000???0 */
#define RTC_HRCR		(0x28)  /* rw, 32, 0x00000??0 */
#define RTC_HWCR		(0x2c)  /* rw, 32, 0x00000008 */
#define RTC_HWRSR		(0x30)  /* rw, 32, 0x00000000 */
#define RTC_HSPR		(0x34)  /* rw, 32, 0x???????? */
#define RTC_WENR		(0x3c)  /* rw, 32, 0x00000000 */
#define RTC_CKPCR		(0x40)  /* rw, 32, 0x00000010 */
#define RTC_OWIPCR		(0x44)  /* rw, 32, 0x00000010 */
#define RTC_PWRONCR		(0x48)  /* rw, 32, 0x???????? */

#define RTCCR_WRDY				BIT(7)
#define WENR_WEN                BIT(31)

#define RECOVERY_SIGNATURE	(0x001a1a)
#define REBOOT_SIGNATURE	(0x003535)
#define UNMSAK_SIGNATURE	(0x7c0000)//do not use these bits


#include "x1000_cpm.h"
#include "x1000_intc.h"
#include "x1000_otg_dwc.h"
#include "x1000_aic.h"
#include "x1000_slcdc.h"

#endif /* _JZ_M150_H_ */
