/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Maxime Ripard. All rights reserved.
 */

#ifndef _CCU_RESET_H_
#define _CCU_RESET_H_

#include <hal_atomic.h>
#include <hal_reset.h>

struct ccu_reset_map
{
    u32 reg;
    u32 bit;
};

struct ccu_reset
{
    unsigned long base;

    struct ccu_reset_map    *reset_map;
    hal_spinlock_t      lock;

    struct reset_control_dev  rcdev;
};

static inline struct ccu_reset *rc_to_ccu_reset(struct reset_control_dev *rcdev)
{
    return container_of(rcdev, struct ccu_reset, rcdev);
}

extern const struct reset_control_ops ccu_reset_ops;

#endif /* _CCU_RESET_H_ */
