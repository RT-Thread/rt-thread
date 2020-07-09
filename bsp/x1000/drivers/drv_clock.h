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
