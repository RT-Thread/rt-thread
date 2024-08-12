/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_TOUCH_H
#define HPM_TOUCH_H

#include "hpm_common.h"

#if defined(CONFIG_TOUCH_FT5406) && (CONFIG_TOUCH_FT5406 == 1)
#include "hpm_ft5406.h"
#define HPM_TOUCH_MAX_POINTS (FT5406_MAX_TOUCH_POINTS)
#elif defined(CONFIG_TOUCH_GT9XX) && (CONFIG_TOUCH_GT9XX == 1)
#include "hpm_gt9xx.h"
#define HPM_TOUCH_MAX_POINTS (GT9XX_MAX_TOUCH_POINTS)
#else
#error "unknown touch type, either have CONFIG_FT5406 or CONFIG_GT9XX defined"
#endif

enum {
    status_touch_buffer_no_ready = MAKE_STATUS(status_group_touch, 0),
    status_touch_points_over_number = MAKE_STATUS(status_group_touch, 1),
};

typedef struct {
    uint16_t x;
    uint16_t y;
} touch_point_t;

#ifdef __cplusplus
extern "C" {
#endif

hpm_stat_t touch_init(I2C_Type *i2c_ptr);
hpm_stat_t touch_config(bool exchange_xy, bool reverse_x, bool reverse_y);
hpm_stat_t touch_get_data(touch_point_t *points, uint8_t *num_of_points);

#ifdef __cplusplus
}
#endif

#endif /* HPM_TOUCH_H */
