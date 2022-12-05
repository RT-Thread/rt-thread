/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Maxime Ripard. All rights reserved.
 */

#ifndef _HAL_RESET_H_
#define _HAL_RESET_H_

#include <aw_list.h>
#include <sunxi_hal_common.h>
#include <platform_rst.h>

typedef enum {
    HAL_SUNXI_RESET = 0,
    HAL_SUNXI_R_RESET,
    HAL_SUNXI_RESET_NUMBER,
} hal_reset_type_t;

typedef u32 hal_reset_id_t;

struct reset_control_dev;

/**
 * struct reset_control_ops - reset controller driver callbacks
 *
 * @reset: for self-deasserting resets, does all necessary
 *         things to reset the device
 * @assert: manually assert the reset line, if supported
 * @deassert: manually deassert the reset line, if supported
 * @status: return the status of the reset line, if supported
 */
struct reset_control_ops {
    int (*reset)(struct reset_control_dev *rcdev, hal_reset_id_t id);
    int (*assert)(struct reset_control_dev *rcdev, hal_reset_id_t id);
    int (*deassert)(struct reset_control_dev *rcdev, hal_reset_id_t id);
    int (*status)(struct reset_control_dev *rcdev, hal_reset_id_t id);
};
/**
 * struct reset_control - reset controller entity that might
 *                               provide multiple reset controls
 * @ops: a pointer to device specific struct reset_control_ops
 * @owner: kernel module of the reset controller driver
 * @list: internal list of reset controller devices
 * @reset_control_head: head of internal list of requested reset controls
 * @dev: corresponding driver model device struct
 * @of_node: corresponding device tree node as phandle target
 * @of_reset_n_cells: number of cells in reset line specifiers
 * @of_xlate: translation function to translate from specifier as found in the
 *            device tree to id as given to the reset control ops
 * @nr_resets: number of reset controls in this reset controller device
 */
struct reset_control_dev {
    const struct reset_control_ops *ops;
    hal_reset_type_t type;
    u32 nr_resets;
    struct list_head node;
};

struct reset_control {
    struct reset_control_dev *rcdev;
    u32 enable_count;
    hal_reset_id_t id;
};

int reset_control_register(struct reset_control_dev *rcdev); //for reset system

int reset_control_unregister(struct reset_control *reset); //for reset system

struct reset_control *hal_reset_control_get(hal_reset_type_t type, hal_reset_id_t id);

int hal_reset_control_put(struct reset_control *reset);

int hal_reset_control_set(struct reset_control *reset); //for other module

int hal_reset_control_deassert(struct reset_control *reset); //for other module

int hal_reset_control_assert(struct reset_control *reset); //for other_module

int hal_reset_control_reset(struct reset_control *reset);  //for other_module

int hal_reset_control_status(struct reset_control *reset); //for other_module

#endif
