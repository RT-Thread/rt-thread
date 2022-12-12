/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Maxime Ripard. All rights reserved.
 */

#ifndef _CCU_COMMON_H_
#define _CCU_COMMON_H_

#include "ccu.h"
#include <hal_clk.h>
#include <hal_reset.h>

#define CCU_FEATURE_FRACTIONAL      BIT(0)
#define CCU_FEATURE_VARIABLE_PREDIV BIT(1)
#define CCU_FEATURE_FIXED_PREDIV    BIT(2)
#define CCU_FEATURE_FIXED_POSTDIV   BIT(3)
#define CCU_FEATURE_ALL_PREDIV      BIT(4)
#define CCU_FEATURE_LOCK_REG        BIT(5)
#define CCU_FEATURE_MMC_TIMING_SWITCH   BIT(6)
#define CCU_FEATURE_SIGMA_DELTA_MOD BIT(7)

/* Support key-field reg setting */
#define CCU_FEATURE_KEY_FIELD_MOD   BIT(8)

/* New formula support in MP: clk = parent / M / P */
#define CCU_FEATURE_MP_NO_INDEX_MODE    BIT(9)

/* Support fixed rate in gate-clk */
#define CCU_FEATURE_FIXED_RATE_GATE BIT(10)
/* MMC timing mode switch bit */
#define CCU_MMC_NEW_TIMING_MODE     BIT(30)

/**
 * struct ccu_reg_dump: register dump of clock controller registers.
 * @offset: clock register offset from the controller base address.
 * @value: the value to be register at offset.
 */
struct ccu_reg_dump
{
    u32 offset;
    u32 value;
};

struct ccu_common
{
    unsigned long    base;
    u32     reg;
    u32     lock_reg;
    u32     prediv;
    u32     key_value;

    hal_spinlock_t lock;
    unsigned long   features;
    struct clk_hw   hw;
};

static inline struct ccu_common *hw_to_ccu_common(struct clk_hw *hw)
{
    return container_of(hw, struct ccu_common, hw);
}

struct sunxi_ccu_desc
{
    struct ccu_common       **ccu_clks;
    u32             num_ccu_clks;

    struct clk_hw_onecell_data  *hw_clks;
    hal_clk_type_t          clk_type;

    struct ccu_reset_map        *resets;
    hal_reset_type_t        reset_type;
    u32             num_resets;
};

void ccu_helper_wait_for_lock(struct ccu_common *common, u32 lock);
int ccu_common_init(unsigned long reg, const struct sunxi_ccu_desc *desc);
void set_reg(unsigned long addr, u32 val, u8 bw, u8 bs);
void set_reg_key(unsigned long addr,
                 u32 key, u8 kbw, u8 kbs,
                 u32 val, u8 bw, u8 bs);

#endif /* _COMMON_H_ */
