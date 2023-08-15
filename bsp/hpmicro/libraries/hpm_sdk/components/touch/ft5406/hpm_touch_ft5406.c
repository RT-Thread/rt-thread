/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_touch.h"
ft5406_context_t ft5406 = {0};

hpm_stat_t touch_get_data(touch_point_t *points, uint8_t *num_of_points)
{
    hpm_stat_t stat = status_success;
    uint8_t i = 0;
    ft5406_touch_data_t touch_data = {0};

    stat = ft5406_read_touch_data(&ft5406, &touch_data);
    if (stat != status_success) {
        return stat;
    }

    if ((touch_data.status < FT5406_MAX_TOUCH_POINTS) && (touch_data.status)) {
        for (i = 0; touch_data.points[i].x_h > 0 && touch_data.points[i].x_h < 0xFF; i++) {
            points[i].x = (touch_data.points[i].x_h & 0xF) << 8 | touch_data.points[i].x_l;
            points[i].y = (touch_data.points[i].y_h & 0xF) << 8 | touch_data.points[i].y_l;
        }
    }

    *num_of_points = i;
    return stat;
}

hpm_stat_t touch_init(I2C_Type *i2c_ptr)
{
    hpm_stat_t stat;

    ft5406.ptr = i2c_ptr;
    stat = ft5406_init(&ft5406);
    if (stat != status_success) {
        return stat;
    }

#ifdef USE_CAP_INT
    stat = ft5406_write_register(&ft5406, FT5406_ID_G_MODE, 0);
    if (stat != status_success) {
        return stat;
    }
    cap_int_setup();
#endif
    return stat;
}
