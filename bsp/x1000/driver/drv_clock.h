/*
 * File      : drv_clock.h
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

#ifndef DRV_CLOCK_H_
#define DRV_CLOCK_H_

#include "board.h"

#define CPM_CPCCR   (0x00)
#define CPM_CPCSR   (0xd4)

#define CPM_DDRCDR  (0x2c)
#define CPM_I2SCDR  (0x60)
#define CPM_I2SCDR1 (0x70)
#define CPM_LPCDR   (0x64)
#define CPM_MSC0CDR (0x68)
#define CPM_MSC1CDR (0xa4)
#define CPM_USBCDR  (0x50)
#define CPM_MACCDR  (0x54)
#define CPM_UHCCDR  (0x6c)
#define CPM_SFCCDR  (0x74)
#define CPM_CIMCDR  (0x7c)
#define CPM_PCMCDR  (0x84)
#define CPM_PCMCDR1 (0xe0)
#define CPM_MPHYC   (0xe8)

#define CPM_INTR    (0xb0)
#define CPM_INTRE   (0xb4)
#define CPM_DRCG    (0xd0)
#define CPM_CPSPPR  (0x38)
#define CPM_CPPSR   (0x34)

#define CPM_USBPCR  (0x3c)
#define CPM_USBRDT  (0x40)
#define CPM_USBVBFIL    (0x44)
#define CPM_USBPCR1 (0x48)

#define CPM_CPAPCR  (0x10)
#define CPM_CPMPCR  (0x14)

#define CPM_LCR     (0x04)
#define CPM_PSWC0ST     (0x90)
#define CPM_PSWC1ST     (0x94)
#define CPM_PSWC2ST     (0x98)
#define CPM_PSWC3ST     (0x9c)
#define CPM_CLKGR   (0x20)
#define CPM_MESTSEL (0xec)
#define CPM_SRBC    (0xc4)
#define CPM_ERNG    (0xd8)
#define CPM_RNG         (0xdc)
#define CPM_SLBC    (0xc8)
#define CPM_SLPC    (0xcc)
#define CPM_OPCR    (0x24)
#define CPM_RSR     (0x08)

#define LCR_LPM_MASK        (0x3)
#define LCR_LPM_SLEEP       (0x1)

#define OPCR_ERCS       (0x1<<2)
#define OPCR_PD         (0x1<<3)
#define OPCR_IDLE       (0x1<<31)

#define cpm_inl(off)            readl(CPM_BASE + (off))
#define cpm_outl(val,off)       writel(val, CPM_BASE + (off))
#define cpm_test_bit(bit,off)   (cpm_inl(off) & 0x1<<(bit))
#define cpm_set_bit(bit,off)    (cpm_outl((cpm_inl(off) | 0x1<<(bit)),off))
#define cpm_clear_bit(bit,off)  (cpm_outl(cpm_inl(off) & ~(0x1 << bit), off))


#define I2S_PRI_DIV 0xb0020030
#define PCM_PRI_DIV 0xb0030014

struct clk;

struct clk_ops {
    int             (*enable)           (struct clk *,int);
    struct clk*     (*get_parent)       (struct clk *);
    int             (*set_parent)       (struct clk *,struct clk *);
    uint32_t        (*get_rate)         (struct clk *);
    int             (*set_rate)         (struct clk *,uint32_t);
    int             (*set_round_rate)   (struct clk *,uint32_t);
};

struct clk {
    const char *name;
    uint32_t rate;
    struct clk *parent;
    uint32_t flags;
#define CLK_FLG_NOALLOC     BIT(0)
#define CLK_FLG_ENABLE      BIT(1)
#define CLK_GATE_BIT(flg)   ((flg) >> 24)
#define CLK_FLG_GATE        BIT(2)
#define CLK_CPCCR_NO(flg)   (((flg) >> 24) & 0xff)
#define CLK_FLG_CPCCR       BIT(3)
#define CLK_CGU_NO(flg)     (((flg) >> 24) & 0xff)
#define CLK_FLG_CGU         BIT(4)
#define CLK_PLL_NO(flg)     (((flg) >> 24) & 0xff)
#define CLK_FLG_PLL         BIT(5)
#define CLK_CGU_AUDIO_NO(flg)   (((flg) >> 24) & 0xff)
#define CLK_FLG_CGU_AUDIO   BIT(6)
#define CLK_PARENT(flg)     (((flg) >> 16) & 0xff)
#define CLK_RELATIVE(flg)   (((flg) >> 16) & 0xff)
#define CLK_FLG_PARENT      BIT(7)
#define CLK_FLG_RELATIVE    BIT(8)
    struct clk_ops *ops;
    int count;
    int init_state;
    struct clk *source;
    struct clk *child;
    unsigned int CLK_ID;
};

int         init_all_clk(void);
struct clk *clk_get(const char *id);
int         clk_enable(struct clk *clk);
int         clk_is_enabled(struct clk *clk);
void        clk_disable(struct clk *clk);
uint32_t    clk_get_rate(struct clk *clk);
void        clk_put(struct clk *clk);
int         clk_set_rate(struct clk *clk, uint32_t rate);

#endif
