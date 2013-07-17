/*
 * File      : sep6200.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
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
 * 2013-7-17      Peng Fan     sep6200 implementation
 */

#ifndef __SEP6200_H
#define __SEP6200_H

#include <rtthread.h>

/*Core definations*/
#define PRIVMODE  0x13
#define	Mode_USR	0x10
#define	Mode_REAL	0x11
#define	Mode_IRQ	0x12
#define	Mode_PRIV	0x13
#define	Mode_TRAP	0x17
#define	Mode_EXT	0x1B
#define	Mode_SUSR	0x1F

/*
 *  Address
 */

#define	 SEP6200_VIC_BASE	0xb0000000
#define  SEP6200_PMU_BASE	0xb0001000
#define  SEP6200_RTC_BASE	0xb0002000
#define	 SEP6200_TIMER_BASE 0xb0003000
#define  SEP6200_PWM_BASE	0xb0004000
#define  SEP6200_GPIO_BASE	0xb0006000
#define  SEP6200_TOUCH_ADC	0xb0007000
#define  SEP6200_SYSCTL_BASE	0xb0008000
#define  SEP6200_UART0_BASE	0xb1000000
#define  SEP6200_UART1_BASE	0xb1001000
#define  SEP6200_UART2_BASE	0xb1002000
#define  SEP6200_UART3_BASE	0xb1003000
#define	 SEP6200_SSI1_BASE	0xb1004000
#define	 SEP6200_SSI2_BASE	0xb1005000
#define	 SEP6200_SSI3_BASE	0xb1006000
#define  SEP6200_I2C_BASE	0xb1007000
#define  SEP6200_I2S_BASE	0xb1008000
#define  SEP6200_USB_BASE    0xb1010000
#define  SEP6200_DMAC2_BASE  0xb1011000
#define  SEP6200_ESRAM_BASE  0xb2000000
#define	 SEP6200_NORREG_BASE0xb2020000
#define	 SEP6200_SDIO1_BASE	0xb2022000
#define	 SEP6200_SDIO2_BASE	0xb2023000
#define	 SEP6200_LCDC_BASE	0xb2025000
#define	 SEP6200_VPU_BASE	0xb2026000
#define	 SEP6200_DMAC1_BASE	0xb2027000
#define	 SEP6200_DDR2_REG	0xb3000000
#define	 SEP6200_DDR_MEM	0x40000000

#define SEP6200_UART0_DLBL	(SEP6200_UART0_BASE+0x00)
#define SEP6200_UART0_RXFIFO	(SEP6200_UART0_BASE+0x00)
#define SEP6200_UART0_TXFIFO	(SEP6200_UART0_BASE+0x00)
#define SEP6200_UART0_DLBH	(SEP6200_UART0_BASE+0x04)
#define SEP6200_UART0_IER	(SEP6200_UART0_BASE+0x04)
#define SEP6200_UART0_IIR	(SEP6200_UART0_BASE+0x08)
#define SEP6200_UART0_FCR	(SEP6200_UART0_BASE+0x08)
#define SEP6200_UART0_LCR	(SEP6200_UART0_BASE+0x0c)
#define SEP6200_UART0_MCR	(SEP6200_UART0_BASE+0x10)
#define SEP6200_UART0_LSR	(SEP6200_UART0_BASE+0x14)
#define SEP6200_UART0_MSR	(SEP6200_UART0_BASE+0x18)


#define    SEP6200_TIMER_T1LCR              (SEP6200_TIMER_BASE + 0X000)
#define    SEP6200_TIMER_T1CCR              (SEP6200_TIMER_BASE + 0X004)
#define    SEP6200_TIMER_T1CR               (SEP6200_TIMER_BASE + 0X008)
#define    SEP6200_TIMER_T1ISCR             (SEP6200_TIMER_BASE + 0X00C)
#define    SEP6200_TIMER_T1IMSR             (SEP6200_TIMER_BASE + 0X010)
#define    SEP6200_TIMER_T2LCR              (SEP6200_TIMER_BASE + 0X020)
#define    SEP6200_TIMER_T2CCR              (SEP6200_TIMER_BASE + 0X024)
#define    SEP6200_TIMER_T2CR               (SEP6200_TIMER_BASE + 0X028)
#define    SEP6200_TIMER_T2ISCR             (SEP6200_TIMER_BASE + 0X02C)
#define    SEP6200_TIMER_T2IMSR             (SEP6200_TIMER_BASE + 0X030)
#define    SEP6200_TIMER_T3LCR              (SEP6200_TIMER_BASE + 0X040)
#define    SEP6200_TIMER_T3CCR              (SEP6200_TIMER_BASE + 0X044)
#define    SEP6200_TIMER_T3CR               (SEP6200_TIMER_BASE + 0X048)
#define    SEP6200_TIMER_T3ISCR             (SEP6200_TIMER_BASE + 0X04C)
#define    SEP6200_TIMER_T3IMSR             (SEP6200_TIMER_BASE + 0X050)
#define    SEP6200_TIMER_T3CAPR             (SEP6200_TIMER_BASE + 0X054)
#define    SEP6200_TIMER_T4LCR              (SEP6200_TIMER_BASE + 0X060)
#define    SEP6200_TIMER_T4CCR              (SEP6200_TIMER_BASE + 0X064)
#define    SEP6200_TIMER_T4CR               (SEP6200_TIMER_BASE + 0X068)
#define    SEP6200_TIMER_T4ISCR             (SEP6200_TIMER_BASE + 0X06C)
#define    SEP6200_TIMER_T4IMSR             (SEP6200_TIMER_BASE + 0X070)
#define    SEP6200_TIMER_T4CAPR             (SEP6200_TIMER_BASE + 0X074)
#define    SEP6200_TIMER_T5LCR              (SEP6200_TIMER_BASE + 0X080)
#define    SEP6200_TIMER_T5CCR              (SEP6200_TIMER_BASE + 0X084)
#define    SEP6200_TIMER_T5CR               (SEP6200_TIMER_BASE + 0X088)
#define    SEP6200_TIMER_T5ISCR             (SEP6200_TIMER_BASE + 0X08C)
#define    SEP6200_TIMER_T5IMSR             (SEP6200_TIMER_BASE + 0X090)
#define    SEP6200_TIMER_T5CAPR             (SEP6200_TIMER_BASE + 0X094)
#define    SEP6200_TIMER_T6LCR              (SEP6200_TIMER_BASE + 0X0A0)
#define    SEP6200_TIMER_T6CCR              (SEP6200_TIMER_BASE + 0X0A4)
#define    SEP6200_TIMER_T6CR               (SEP6200_TIMER_BASE + 0X0A8)
#define    SEP6200_TIMER_T6ISCR             (SEP6200_TIMER_BASE + 0X0AC)
#define    SEP6200_TIMER_T6IMSR             (SEP6200_TIMER_BASE + 0X0B0)
#define    SEP6200_TIMER_T6CAPR             (SEP6200_TIMER_BASE + 0X0B4)
#define    SEP6200_TIMER_T7LCR              (SEP6200_TIMER_BASE + 0X0C0)
#define    SEP6200_TIMER_T7CCR              (SEP6200_TIMER_BASE + 0X0C4)
#define    SEP6200_TIMER_T7CR               (SEP6200_TIMER_BASE + 0X0C8)
#define    SEP6200_TIMER_T7ISCR             (SEP6200_TIMER_BASE + 0X0CC)
#define    SEP6200_TIMER_T7IMSR             (SEP6200_TIMER_BASE + 0X0D0)
#define    SEP6200_TIMER_T8LCR              (SEP6200_TIMER_BASE + 0X0E0)
#define    SEP6200_TIMER_T8CCR              (SEP6200_TIMER_BASE + 0X0E4)
#define    SEP6200_TIMER_T8CR               (SEP6200_TIMER_BASE + 0X0E8)
#define    SEP6200_TIMER_T8ISCR             (SEP6200_TIMER_BASE + 0X0EC)
#define    SEP6200_TIMER_T8IMSR             (SEP6200_TIMER_BASE + 0X0F0)
#define    SEP6200_TIMER_T9LCR              (SEP6200_TIMER_BASE + 0X100)
#define    SEP6200_TIMER_T9CCR              (SEP6200_TIMER_BASE + 0X104)
#define    SEP6200_TIMER_T9CR               (SEP6200_TIMER_BASE + 0X108)
#define    SEP6200_TIMER_T9ISCR             (SEP6200_TIMER_BASE + 0X10C)
#define    SEP6200_TIMER_T9IMSR             (SEP6200_TIMER_BASE + 0X110)
#define    SEP6200_TIMER_T10LCR             (SEP6200_TIMER_BASE + 0X120)
#define    SEP6200_TIMER_T10CCR             (SEP6200_TIMER_BASE + 0X124)
#define    SEP6200_TIMER_T10CR              (SEP6200_TIMER_BASE + 0X128)
#define    SEP6200_TIMER_T10ISCR            (SEP6200_TIMER_BASE + 0X12C)
#define    SEP6200_TIMER_T10IMSR            (SEP6200_TIMER_BASE + 0X130)
#define    SEP6200_TIMER_TIMSR              (SEP6200_TIMER_BASE + 0X140)
#define    SEP6200_TIMER_TISCR              (SEP6200_TIMER_BASE + 0X144)
#define    SEP6200_TIMER_TISR               (SEP6200_TIMER_BASE + 0X148)

#define    SEP6200_VIC_INT_SLT_L            (SEP6200_VIC_BASE + 0x000)
#define    SEP6200_VIC_INT_SLT_H            (SEP6200_VIC_BASE + 0x004)
#define    SEP6200_VIC_INT_EN_L             (SEP6200_VIC_BASE + 0x008)
#define    SEP6200_VIC_INT_EN_H             (SEP6200_VIC_BASE + 0x00C)
#define    SEP6200_VIC_INT_EN_CLR_L         (SEP6200_VIC_BASE + 0x010)
#define    SEP6200_VIC_INT_EN_CLR_H         (SEP6200_VIC_BASE + 0x014)
#define    SEP6200_VIC_SFT_INT_L            (SEP6200_VIC_BASE + 0x018)
#define    SEP6200_VIC_SFT_INT_H            (SEP6200_VIC_BASE + 0x01C)
#define    SEP6200_VIC_SFT_INT_CLR_L        (SEP6200_VIC_BASE + 0x020)
#define    SEP6200_VIC_SFT_INT_CLR_H        (SEP6200_VIC_BASE + 0x024)
#define    SEP6200_VIC_INT_MSK_ALL          (SEP6200_VIC_BASE + 0x028)
#define    SEP6200_VIC_RAW_INT_SRC_L        (SEP6200_VIC_BASE + 0x030)
#define    SEP6200_VIC_RAW_INT_SRC_H        (SEP6200_VIC_BASE + 0x034)
#define    SEP6200_VIC_RAW_IRQ_STS_L        (SEP6200_VIC_BASE + 0x038)
#define    SEP6200_VIC_RAW_IRQ_STS_H        (SEP6200_VIC_BASE + 0x03C)
#define    SEP6200_VIC_RAW_FIQ_STS_L        (SEP6200_VIC_BASE + 0x040)
#define    SEP6200_VIC_RAW_FIQ_STS_H        (SEP6200_VIC_BASE + 0x044)
#define    SEP6200_VIC_MSK_IRQ_STS_L        (SEP6200_VIC_BASE + 0x048)
#define    SEP6200_VIC_MSK_IRQ_STS_H        (SEP6200_VIC_BASE + 0x04C)
#define    SEP6200_VIC_MSK_FIQ_STS_L        (SEP6200_VIC_BASE + 0x050)
#define    SEP6200_VIC_MSK_FIQ_STS_H        (SEP6200_VIC_BASE + 0x054)
#define    SEP6200_VIC_IRQ_PENDING_L        (SEP6200_VIC_BASE + 0x058)
#define    SEP6200_VIC_IRQ_PENDING_H        (SEP6200_VIC_BASE + 0x05C)
#define    SEP6200_VIC_FIQ_PENDING_L        (SEP6200_VIC_BASE + 0x060)
#define    SEP6200_VIC_FIQ_PENDING_H        (SEP6200_VIC_BASE + 0x064)
#define    SEP6200_VIC_IRQ_VECTOR_BASE      (SEP6200_VIC_BASE + 0x070)
#define    SEP6200_VIC_FIQ_VECTOR_BASE      (SEP6200_VIC_BASE + 0x074)
#define    SEP6200_VIC_IRQ_VECTOR_NUM       (SEP6200_VIC_BASE + 0x078)
#define    SEP6200_VIC_FIQ_VECTOR_NUM       (SEP6200_VIC_BASE + 0x07C)
#define    SEP6200_VIC_IRQ_VECTOR_ADDR      (SEP6200_VIC_BASE + 0x080)
#define    SEP6200_VIC_FIQ_VECTOR_ADDR      (SEP6200_VIC_BASE + 0x084)
#define    SEP6200_VIC_PROIRTY_MASK         (SEP6200_VIC_BASE + 0x090)
#define    SEP6200_VIC_VECTOR_PROIRTY00     (SEP6200_VIC_BASE + 0x100)
#define    SEP6200_VIC_VECTOR_PROIRTY01     (SEP6200_VIC_BASE + 0x104)
#define    SEP6200_VIC_VECTOR_PROIRTY02     (SEP6200_VIC_BASE + 0x108)
#define    SEP6200_VIC_VECTOR_PROIRTY03     (SEP6200_VIC_BASE + 0x10C)
#define    SEP6200_VIC_VECTOR_PROIRTY04     (SEP6200_VIC_BASE + 0x110)
#define    SEP6200_VIC_VECTOR_PROIRTY05     (SEP6200_VIC_BASE + 0x114)
#define    SEP6200_VIC_VECTOR_PROIRTY06     (SEP6200_VIC_BASE + 0x118)
#define    SEP6200_VIC_VECTOR_PROIRTY07     (SEP6200_VIC_BASE + 0x11C)
#define    SEP6200_VIC_VECTOR_PROIRTY08     (SEP6200_VIC_BASE + 0x120)
#define    SEP6200_VIC_VECTOR_PROIRTY09     (SEP6200_VIC_BASE + 0x124)
#define    SEP6200_VIC_VECTOR_PROIRTY10     (SEP6200_VIC_BASE + 0x128)
#define    SEP6200_VIC_VECTOR_PROIRTY11     (SEP6200_VIC_BASE + 0x12C)
#define    SEP6200_VIC_VECTOR_PROIRTY12     (SEP6200_VIC_BASE + 0x130)
#define    SEP6200_VIC_VECTOR_PROIRTY13     (SEP6200_VIC_BASE + 0x134)
#define    SEP6200_VIC_VECTOR_PROIRTY14     (SEP6200_VIC_BASE + 0x138)
#define    SEP6200_VIC_VECTOR_PROIRTY15     (SEP6200_VIC_BASE + 0x13C)
#define    SEP6200_VIC_VECTOR_PROIRTY16     (SEP6200_VIC_BASE + 0x140)
#define    SEP6200_VIC_VECTOR_PROIRTY17     (SEP6200_VIC_BASE + 0x144)
#define    SEP6200_VIC_VECTOR_PROIRTY18     (SEP6200_VIC_BASE + 0x148)
#define    SEP6200_VIC_VECTOR_PROIRTY19     (SEP6200_VIC_BASE + 0x14C)
#define    SEP6200_VIC_VECTOR_PROIRTY20     (SEP6200_VIC_BASE + 0x150)
#define    SEP6200_VIC_VECTOR_PROIRTY21     (SEP6200_VIC_BASE + 0x154)
#define    SEP6200_VIC_VECTOR_PROIRTY22     (SEP6200_VIC_BASE + 0x158)
#define    SEP6200_VIC_VECTOR_PROIRTY23     (SEP6200_VIC_BASE + 0x15C)
#define    SEP6200_VIC_VECTOR_PROIRTY24     (SEP6200_VIC_BASE + 0x160)
#define    SEP6200_VIC_VECTOR_PROIRTY25     (SEP6200_VIC_BASE + 0x164)
#define    SEP6200_VIC_VECTOR_PROIRTY26     (SEP6200_VIC_BASE + 0x168)
#define    SEP6200_VIC_VECTOR_PROIRTY27     (SEP6200_VIC_BASE + 0x16C)
#define    SEP6200_VIC_VECTOR_PROIRTY28     (SEP6200_VIC_BASE + 0x170)
#define    SEP6200_VIC_VECTOR_PROIRTY29     (SEP6200_VIC_BASE + 0x174)
#define    SEP6200_VIC_VECTOR_PROIRTY30     (SEP6200_VIC_BASE + 0x178)
#define    SEP6200_VIC_VECTOR_PROIRTY31     (SEP6200_VIC_BASE + 0x17C)
#define    SEP6200_VIC_VECTOR_PROIRTY32     (SEP6200_VIC_BASE + 0x180)
#define    SEP6200_VIC_VECTOR_PROIRTY33     (SEP6200_VIC_BASE + 0x184)
#define    SEP6200_VIC_VECTOR_PROIRTY34     (SEP6200_VIC_BASE + 0x188)
#define    SEP6200_VIC_VECTOR_PROIRTY35     (SEP6200_VIC_BASE + 0x18C)
#define    SEP6200_VIC_VECTOR_PROIRTY36     (SEP6200_VIC_BASE + 0x190)
#define    SEP6200_VIC_VECTOR_PROIRTY37     (SEP6200_VIC_BASE + 0x194)
#define    SEP6200_VIC_VECTOR_PROIRTY38     (SEP6200_VIC_BASE + 0x198)
#define    SEP6200_VIC_VECTOR_PROIRTY39     (SEP6200_VIC_BASE + 0x19C)
#define    SEP6200_VIC_VECTOR_PROIRTY40     (SEP6200_VIC_BASE + 0x1A0)
#define    SEP6200_VIC_VECTOR_PROIRTY41     (SEP6200_VIC_BASE + 0x1A4)
#define    SEP6200_VIC_VECTOR_PROIRTY42     (SEP6200_VIC_BASE + 0x1A8)
#define    SEP6200_VIC_VECTOR_PROIRTY43     (SEP6200_VIC_BASE + 0x1AC)
#define    SEP6200_VIC_VECTOR_PROIRTY44     (SEP6200_VIC_BASE + 0x1B0)
#define    SEP6200_VIC_VECTOR_PROIRTY45     (SEP6200_VIC_BASE + 0x1B4)
#define    SEP6200_VIC_VECTOR_PROIRTY46     (SEP6200_VIC_BASE + 0x1B8)
#define    SEP6200_VIC_VECTOR_PROIRTY47     (SEP6200_VIC_BASE + 0x1BC)
#define    SEP6200_VIC_VECTOR_PROIRTY48     (SEP6200_VIC_BASE + 0x1C0)
#define    SEP6200_VIC_VECTOR_PROIRTY49     (SEP6200_VIC_BASE + 0x1C4)
#define    SEP6200_VIC_VECTOR_PROIRTY50     (SEP6200_VIC_BASE + 0x1C8)
#define    SEP6200_VIC_VECTOR_PROIRTY51     (SEP6200_VIC_BASE + 0x1CC)
#define    SEP6200_VIC_VECTOR_PROIRTY52     (SEP6200_VIC_BASE + 0x1D0)
#define    SEP6200_VIC_VECTOR_PROIRTY53     (SEP6200_VIC_BASE + 0x1D4)
#define    SEP6200_VIC_VECTOR_PROIRTY54     (SEP6200_VIC_BASE + 0x1D8)
#define    SEP6200_VIC_VECTOR_PROIRTY55     (SEP6200_VIC_BASE + 0x1DC)
#define    SEP6200_VIC_VECTOR_PROIRTY56     (SEP6200_VIC_BASE + 0x1E0)
#define    SEP6200_VIC_VECTOR_PROIRTY57     (SEP6200_VIC_BASE + 0x1E4)
#define    SEP6200_VIC_VECTOR_PROIRTY58     (SEP6200_VIC_BASE + 0x1E8)
#define    SEP6200_VIC_VECTOR_PROIRTY59     (SEP6200_VIC_BASE + 0x1EC)
#define    SEP6200_VIC_VECTOR_PROIRTY60     (SEP6200_VIC_BASE + 0x1F0)
#define    SEP6200_VIC_VECTOR_PROIRTY61     (SEP6200_VIC_BASE + 0x1F4)
#define    SEP6200_VIC_VECTOR_PROIRTY62     (SEP6200_VIC_BASE + 0x1F8)
#define    SEP6200_VIC_VECTOR_PROIRTY63     (SEP6200_VIC_BASE + 0x1FC)

#define    SEP6200_PMU_PLL_SET              (SEP6200_PMU_BASE + 0x000)
#define    SEP6200_PMU_APLL_CFG             (SEP6200_PMU_BASE + 0x004)
#define    SEP6200_PMU_MPLL_GFG             (SEP6200_PMU_BASE + 0x008)
#define    SEP6200_PMU_DPLL_CFG             (SEP6200_PMU_BASE + 0x00C)
#define    SEP6200_PMU_PMDR                 (SEP6200_PMU_BASE + 0x010)
#define    SEP6200_PMU_CLK_GT_CFG1          (SEP6200_PMU_BASE + 0x014)
#define    SEP6200_PMU_CLK_GT_CFG2          (SEP6200_PMU_BASE + 0x018)
#define    SEP6200_PMU_PWR_GT_CFG           (SEP6200_PMU_BASE + 0x01C)
#define    SEP6200_PMU_AHB_CLK_CFG          (SEP6200_PMU_BASE + 0x020)
#define    SEP6200_PMU_ARM_CLK_CFG          (SEP6200_PMU_BASE + 0x024)
#define    SEP6200_PMU_DDR_CLK_CFG          (SEP6200_PMU_BASE + 0x028)
#define    SEP6200_PMU_PIX_CLK_CFG          (SEP6200_PMU_BASE + 0x02C)
#define    SEP6200_PMU_GPU_CLK2X_CFG        (SEP6200_PMU_BASE + 0x030)
#define    SEP6200_PMU_DIV_SET              (SEP6200_PMU_BASE + 0x034)
#define    SEP6200_PMU_CRYSTAL_CFG          (SEP6200_PMU_BASE + 0x038)
#define    SEP6200_PMU_MSK_WAKEUP           (SEP6200_PMU_BASE + 0x03C)
#define    SEP6200_PMU_RTCR                 (SEP6200_PMU_BASE + 0x040)
#define    SEP6200_PMU_CLR_WAKEUP           (SEP6200_PMU_BASE + 0x044)
#define    SEP6200_PMU_WAKEUP_TIME          (SEP6200_PMU_BASE + 0x048)
#define    SEP6200_PMU_SLEEP_FLAG           (SEP6200_PMU_BASE + 0x04C)
#define    SEP6200_PMU_WAIT_PWR_SWITCH      (SEP6200_PMU_BASE + 0x050)
#define    SEP6200_PMU_PWR_STATE            (SEP6200_PMU_BASE + 0x054)
#define    SEP6200_PMU_INT_POL_SEL          (SEP6200_PMU_BASE + 0x058)
#define    SEP6200_PMU_PLLLD                (SEP6200_PMU_BASE + 0x05C)
#define    SEP6200_PMU_IC_ENABLE            (SEP6200_PMU_BASE + 0x060)
#define    SEP6200_PMU_IC_TAR               (SEP6200_PMU_BASE + 0x064)
#define    SEP6200_PMU_IC_SCL_LCNT          (SEP6200_PMU_BASE + 0x068)
#define    SEP6200_PMU_IC_SCL_HCNT          (SEP6200_PMU_BASE + 0x06C)
#define    SEP6200_PMU_IC_DATA_CMD          (SEP6200_PMU_BASE + 0x070)
#define    SEP6200_PMU_IC_STATE             (SEP6200_PMU_BASE + 0x074)
#define    SEP6200_PMU_IC_SET               (SEP6200_PMU_BASE + 0x078)
#define    SEP6200_PMU_HA_PWR_OFF_DAT       (SEP6200_PMU_BASE + 0x07C)
#define    SEP6200_PMU_HA_PWR_ON_DAT        (SEP6200_PMU_BASE + 0x080)
#define    SEP6200_PMU_HA_PWR_OFF_DAT_CNT   (SEP6200_PMU_BASE + 0x084)
#define    SEP6200_PMU_HA_PWR_ON_DAT_CNT    (SEP6200_PMU_BASE + 0x088)
#define    SEP6200_PMU_PWR_OFF_TIME         (SEP6200_PMU_BASE + 0x08C)
#define    SEP6200_PMU_PWR_ON_TIME          (SEP6200_PMU_BASE + 0x090)
#define    SEP6200_PMU_PWR_ON_POL_SEL       (SEP6200_PMU_BASE + 0x094)
#define    SEP6200_PMU_RETURN_ADDR          (SEP6200_PMU_BASE + 0x098)
#define    SEP6200_PMU_INT                  (SEP6200_PMU_BASE + 0x09C)

/* define the interrupt source number */
#define    INTSRC_RESERVE2      63
#define    INTSRC_RESERVE1      62
#define    INTSRC_LCDC          61
#define    INTSRC_GPU           60
#define    INTSRC_VPU           59
#define    INTSRC_TIMER3        58
#define    INTSRC_TIMER2        57
#define    INTSRC_TIMER1        56
#define    INTSRC_NAND          55
#define    INTSRC_I2S           54
#define    INTSRC_I2C3          53
#define    INTSRC_I2C2          52
#define    INTSRC_I2C1          51
#define    INTSRC_SSI3          50
#define    INTSRC_SSI2          49
#define    INTSRC_SSI1          48
#define    INTSRC_SDIO2         47
#define    INTSRC_SDIO1         46
#define    INTSRC_UART3         45
#define    INTSRC_UART2         44
#define    INTSRC_UART1         43
#define    INTSRC_UART0         42
#define    INTSRC_PWM           41
#define    INTSRC_USB           40
#define    INTSRC_USBDMA        39
#define    INTSRC_DMAC2         38
#define    INTSRC_DMAC1         37
#define    INTSRC_PMUIRQ_A11    36
#define    INTSRC_DMAIRQ_A11    35
#define    INTSRC_GPS           34
#define    INTSRC_RTC           33
#define    INTSRC_RESERVED16    32
#define    INTSRC_PORTE12       31
#define    INTSRC_PORTE11       30
#define    INTSRC_PORTE10       29
#define    INTSRC_PORTE9        28
#define    INTSRC_PORTE5        27
#define    INTSRC_PORTE4        26
#define    INTSRC_PORTD9        25
#define    INTSRC_PORTD8        24
#define    INTSRC_PORTD3        23
#define    INTSRC_PORTD2        22
#define    INTSRC_PORTD1        21
#define    INTSRC_PORTD0        20
#define    INTSRC_PORTC3        19
#define    INTSRC_PORTC2        18
#define    INTSRC_PORTC1        17
#define    INTSRC_PORTC0        16
#define    INTSRC_EXT15         15
#define    INTSRC_EXT14         14
#define    INTSRC_EXT13         13
#define    INTSRC_EXT12         12
#define    INTSRC_EXT11         11
#define    INTSRC_EXT10         10
#define    INTSRC_EXT9          9
#define    INTSRC_EXT8          8
#define    INTSRC_EXT7          7
#define    INTSRC_EXT6          6
#define    INTSRC_EXT5          5
#define    INTSRC_EXT4          4
#define    INTSRC_AO_EXT3       3
#define    INTSRC_AO_EXT2       2
#define    INTSRC_AO_EXT1       1
#define    INTSRC_AO_EXT0       0


typedef    char                 S8;        /* signed 8-bit integer */
typedef    short                S16;       /* signed 16-bit integer */
typedef    long                 S32;       /* signed 32-bit integer */
typedef    unsigned char        U8;        /* unsigned 8-bit integer */
typedef    unsigned short       U16;       /* unsigned 16-bit integer */
typedef    unsigned long        U32;       /* unsigned 32-bit integer */

typedef    volatile U32 *       RP;
typedef    volatile U16 *       RP16;
typedef    volatile U8  *       RP8;

typedef    void                 *VP;       /* pointer to an unpredictable data type */
typedef    void                 (*FP)();   /* program start address */

#ifndef    _BOOL_TYPE_
#define    _BOOL_TYPE_
typedef    int                  BOOL;	     /* Boolean value.  TRUE (1) or FALSE (0). */
#endif

typedef    int                  ER;         /* Error code.  A signed integer. */

/**
 * IO definitions
 *
 * define access restrictions to peripheral registers
 */

#define     __I     volatile const            /*!< defines 'read only' permissions      */
#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */
#define     __iomem volatile


/*Macros for debug*/

#define EOUT(fmt,...) \
	do \
	{ 	\
		rt_kprintf("EOUT:(%s:%i)  ",__FILE__,__LINE__); \
		rt_kprintf(fmt,##__VA_ARGS__); \
	}while(0)

#define RT_DEBUG
#ifdef RT_DEBUG
	#define DBOUT(fmt,...) \
	do \
	{ 	\
		rt_kprintf("DBOUT:(%s:%i)  ",__FILE__,__LINE__); \
		rt_kprintf(fmt,##__VA_ARGS__); \
	}while(0)
#else
	#define DBOUT(fmt,...) \
	do{}while(0)
#endif

#ifdef	RT_DEBUG
	#define ASSERT(arg) \
	if((arg) == 0) \
	{		\
		while(1) \
		{		  \
			rt_kprintf("have a assert failure\n"); \
		}										 \
	}
#else
	#define ASSERT(arg) \
	do		\
	{		 \
	}while(0)
#endif


#define write_reg(reg,value) \
	do \
	{ \
		*(RP)(reg) = value; \
	}while(0)

#define read_reg(reg) (*(RP)reg)


struct rt_hw_register
{
	rt_uint32_t r0;
	rt_uint32_t r1;
	rt_uint32_t r2;
	rt_uint32_t r3;
	rt_uint32_t r4;
	rt_uint32_t r5;
	rt_uint32_t r6;
	rt_uint32_t r7;
	rt_uint32_t r8;
	rt_uint32_t r9;
	rt_uint32_t r10;
	rt_uint32_t r11;
	rt_uint32_t r12;
	rt_uint32_t r13;
	rt_uint32_t r14;
	rt_uint32_t r15;
	rt_uint32_t r16;
	rt_uint32_t r17;
	rt_uint32_t r18;
	rt_uint32_t r19;
	rt_uint32_t r20;
	rt_uint32_t r21;
	rt_uint32_t r22;
	rt_uint32_t r23;
	rt_uint32_t r24;
	rt_uint32_t sb;
	rt_uint32_t sl;
	rt_uint32_t fp;
	rt_uint32_t ip;
	rt_uint32_t sp;
	rt_uint32_t lr;
	rt_uint32_t pc;
	rt_uint32_t asr;
	rt_uint32_t bsr;
	rt_uint32_t ORIG_r0;
};

/*@}*/

#endif
