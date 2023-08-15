/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "board.h"
#include "hpm_touch.h"
#include "hpm_gpio_drv.h"
#include "hpm_gt911.h"

gt911_context_t gt911 = {0};

hpm_stat_t touch_get_data(touch_point_t *points, uint8_t *num_of_points)
{
    hpm_stat_t stat = status_success;
    gt911_touch_data_t touch_data = {0};
    uint8_t num, i;

    stat = gt911_read_touch_data(&gt911, &touch_data);
    if (stat != status_success) {
        printf("gt911 read data failed\n");
        return stat;
    }

    num = GT911_GET_STATUS_NUM_OF_POINTS(touch_data.status);
    *num_of_points = num;
    if (num > 0 && num < GT911_MAX_TOUCH_POINTS) {
        for (i = 0; i < num; i++) {
            points[i].x = (touch_data.points[i].x_h & 0xF) << 8 | touch_data.points[i].x_l;
            points[i].y = (touch_data.points[i].y_h & 0xF) << 8 | touch_data.points[i].y_l;
        }
    }

    gt911_write_register(&gt911, GT911_STATUS, 0);
    return stat;
}

void pull_int_pin(bool high)
{
    gpio_set_pin_output(BOARD_CAP_INTR_GPIO, BOARD_CAP_INTR_GPIO_INDEX, BOARD_CAP_INTR_GPIO_PIN);
    gpio_write_pin(BOARD_CAP_INTR_GPIO, BOARD_CAP_INTR_GPIO_INDEX, BOARD_CAP_INTR_GPIO_PIN, 1);
}

void float_int_pin(void)
{
    gpio_set_pin_input(BOARD_CAP_INTR_GPIO, BOARD_CAP_INTR_GPIO_INDEX, BOARD_CAP_INTR_GPIO_PIN);
}

hpm_stat_t touch_init(I2C_Type *i2c_ptr)
{
    hpm_stat_t stat = status_success;

    gt911.ptr = i2c_ptr;

    stat = gt911_init(&gt911, BOARD_LCD_WIDTH, BOARD_LCD_HEIGHT);
    if (stat != status_success) {
        return stat;
    }
    gt911_write_register(&gt911, GT911_CMD, GT911_CMD_READ_COORD_STAT);

    return stat;
}
