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
#elif defined(CONFIG_TOUCH_GT911) && (CONFIG_TOUCH_GT911 == 1)
#include "hpm_gt911.h"
#define HPM_TOUCH_MAX_POINTS (GT911_MAX_TOUCH_POINTS)
#else
#error "unknown touch type, either have CONFIG_FT5406 or CONFIG_GT911 defined"
#endif

typedef struct {
    uint16_t x;
    uint16_t y;
} touch_point_t;

#ifdef __cplusplus
extern "C" {
#endif

hpm_stat_t touch_init(I2C_Type *i2c_ptr);

hpm_stat_t touch_get_data(touch_point_t *points, uint8_t *num_of_points);

#ifdef __cplusplus
}
#endif

#endif /* HPM_TOUCH_H */
