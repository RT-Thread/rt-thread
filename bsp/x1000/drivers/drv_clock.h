/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
