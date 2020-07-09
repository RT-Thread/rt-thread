/*
 * File      : board_timer.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
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

#ifndef DRV_OST_H__
#define DRV_OST_H__

#define TCU_TSTR    (0xF0)   /* Timer Status Register,Only Used In Tcu2 Mode */
#define TCU_TSTSR   (0xF4)   /* Timer Status Set Register */
#define TCU_TSTCR   (0xF8)   /* Timer Status Clear Register */
#define TCU_TSR     (0x1C)   /* Timer Stop Register */
#define TCU_TSSR    (0x2C)   /* Timer Stop Set Register */
#define TCU_TSCR    (0x3C)   /* Timer Stop Clear Register */
#define TCU_TER     (0x10)   /* Timer Counter Enable Register */
#define TCU_TESR    (0x14)   /* Timer Counter Enable Set Register */
#define TCU_TECR    (0x18)   /* Timer Counter Enable Clear Register */
#define TCU_TFR     (0x20)   /* Timer Flag Register */
#define TCU_TFSR    (0x24)   /* Timer Flag Set Register */
#define TCU_TFCR    (0x28)   /* Timer Flag Clear Register */
#define TCU_TMR     (0x30)   /* Timer Mask Register */
#define TCU_TMSR    (0x34)   /* Timer Mask Set Register */
#define TCU_TMCR    (0x38)   /* Timer Mask Clear Register */

#define CH_TDFR(n)  (0x40 + (n)*0x10) /* Timer Data Full Reg */
#define CH_TDHR(n)  (0x44 + (n)*0x10) /* Timer Data Half Reg */
#define CH_TCNT(n)  (0x48 + (n)*0x10) /* Timer Counter Reg */
#define CH_TCSR(n)  (0x4C + (n)*0x10) /* Timer Control Reg */

#define REG_TCU_TSTR    REG32(TCU_BASE + (0xF0))
#define REG_TCU_TSTSR   REG32(TCU_BASE + (0xF4))
#define REG_TCU_TSTCR   REG32(TCU_BASE + (0xF8))
#define REG_TCU_TSR     REG32(TCU_BASE + (0x1C))
#define REG_TCU_TSSR    REG32(TCU_BASE + (0x2C))
#define REG_TCU_TSCR    REG32(TCU_BASE + (0x3C))
#define REG_TCU_TER     REG32(TCU_BASE + (0x10))
#define REG_TCU_TESR    REG32(TCU_BASE + (0x14))
#define REG_TCU_TECR    REG16(TCU_BASE + (0x18))
#define REG_TCU_TFR     REG32(TCU_BASE + (0x20))
#define REG_TCU_TFSR    REG32(TCU_BASE + (0x24))
#define REG_TCU_TFCR    REG32(TCU_BASE + (0x28))
#define REG_TCU_TMR     REG32(TCU_BASE + (0x30))
#define REG_TCU_TMSR    REG32(TCU_BASE + (0x34))
#define REG_TCU_TMCR    REG32(TCU_BASE + (0x38))

#define REG_CH_TDFR(n)  REG32(TCU_BASE + (0x40 + (n)*0x10))
#define REG_CH_TDHR(n)  REG32(TCU_BASE + (0x44 + (n)*0x10))
#define REG_CH_TCNT(n)  REG32(TCU_BASE + (0x48 + (n)*0x10))
#define REG_CH_TCSR(n)  REG32(TCU_BASE + (0x4C + (n)*0x10))

#define TER_OSTEN   (1 << 15)   /* enable the counter in ost */
#define TMR_OSTM    (1 << 15)   /* ost comparison match interrupt mask */
#define TFR_OSTF    (1 << 15)   /* ost interrupt flag */
#define TSR_OSTS    (1 << 15)   /*the clock supplies to osts is stopped */

#define TSR_WDTS    (1 << 16)   /*the clock supplies to wdt is stopped */

// Register bits definitions
#define TSTR_REAL2          (1 << 18) /* only used in TCU2 mode */
#define TSTR_REAL1          (1 << 17) /* only used in TCU2 mode */
#define TSTR_BUSY2          (1 << 2)  /* only used in TCU2 mode */
#define TSTR_BUSY1          (1 << 1)  /* only used in TCU2 mode */

#define TCSR_CNT_CLRZ       (1 << 10) /* clear counter to 0, only used in TCU2 mode */
#define TCSR_PWM_SD         (1 << 9)  /* shut down the pwm output only used in TCU1 mode */
#define TCSR_PWM_HIGH       (1 << 8)  /* selects an initial output level for pwm output */
#define TCSR_PWM_EN         (1 << 7)  /* pwm pin output enable */

/*********************************************************************************************************
**   OST
*********************************************************************************************************/

#define REG_OSTCCR          REG32(OST_BASE + 0x00)
#define REG_OSTER           REG32(OST_BASE + 0x04)
#define REG_OSTCR           REG32(OST_BASE + 0x08)
#define REG_OSTFR           REG32(OST_BASE + 0x0C)
#define REG_OSTMR           REG32(OST_BASE + 0x10)
#define REG_OST1DFR         REG32(OST_BASE + 0x14)
#define REG_OST1CNT         REG32(OST_BASE + 0x18)
#define REG_OST2CNTL        REG32(OST_BASE + 0x20)
#define REG_OSTCNT2HBUF     REG32(OST_BASE + 0x24)
#define REG_OSTESR          REG32(OST_BASE + 0x34)
#define REG_OSTECR          REG32(OST_BASE + 0x38)

/*
 * Operating system timer module(OST) address definition
 */

#define OST_DR          (0xE0)
#define OST_CNTL        (0xE4)
#define OST_CNTH        (0xE8)
#define OST_CSR         (0xEC)
#define OST_CNTH_BUF    (0xFC)

#define REG_OST_DR          REG32(OST_BASE + (0xE0))
#define REG_OST_CNTL        REG32(OST_BASE + (0xE4))
#define REG_OST_CNTH        REG32(OST_BASE + (0xE8))
#define REG_OST_CSR         REG16(OST_BASE + (0xEC))
#define REG_OST_CNTH_BUF    REG32(OST_BASE + (0xFC))

/* Operating system control register(OSTCSR) */
#define OST_CSR_CNT_MD      (1 << 15)

#define CSR_EXT_EN          (1 << 2)  /* select extal as the timer clock input */
#define CSR_RTC_EN          (1 << 1)  /* select rtcclk as the timer clock input */
#define CSR_PCK_EN          (1 << 0)  /* select pclk as the timer clock input */
#define CSR_CLK_MSK         (0x7)

#define CSR_DIV1    (0x0 << 3)
#define CSR_DIV4    (0x1 << 3)
#define CSR_DIV16   (0x2 << 3)
#define CSR_DIV64   (0x3 << 3)
#define CSR_DIV256  (0x4 << 3)
#define CSR_DIV1024 (0x5 << 3)
#define CSR_DIV_MSK (0x7 << 3)

#define OST_DIV1    (0x0)
#define OST_DIV4    (0x1)
#define OST_DIV16   (0x2)

int rt_hw_ost_init(void);

#endif
