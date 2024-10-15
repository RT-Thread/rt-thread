/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "board.h"
#include "hpm_touch.h"
#include "hpm_gpio_drv.h"
#include "hpm_gt9xx.h"
#include "hpm_touch.h"

gt9xx_context_t gt9xx = {0};

hpm_stat_t touch_get_data(touch_point_t *points, uint8_t *num_of_points)
{
    hpm_stat_t stat = status_success;
    gt9xx_touch_data_t touch_data = {0};
    uint8_t num, i;
    uint16_t tmp;

    stat = gt9xx_read_touch_data(&gt9xx, &touch_data);
    if (stat != status_success) {
        printf("gt9xx read data failed\n");
        return stat;
    }
    /* the buffer status is ready*/
    if (GT9XX_GET_STATUS_BUFFER_STAT(touch_data.status) == 1) {
        num = GT9XX_GET_STATUS_NUM_OF_POINTS(touch_data.status);
        *num_of_points = num;
        if (num > 0 && num <= GT9XX_MAX_TOUCH_POINTS) {
            for (i = 0; i < num; i++) {
                points[i].x = (touch_data.points[i].x_h & 0xF) << 8 | touch_data.points[i].x_l;
                points[i].y = (touch_data.points[i].y_h & 0xF) << 8 | touch_data.points[i].y_l;

                if (gt9xx.reverse_x)
                    points[i].x = gt9xx.abs_x_max - points[i].x;

                if (gt9xx.reverse_y)
                    points[i].y = gt9xx.abs_y_max - points[i].y;

                if (gt9xx.exchange_xy) {
                    tmp = points[i].x;
                    points[i].x = points[i].y;
                    points[i].y = tmp;
                }
            }
        } else {
            stat = status_touch_points_over_number;
        }
        gt9xx_write_register(&gt9xx, GT9XX_STATUS, 0);
    } else {
        stat = status_touch_buffer_no_ready;
    }

    return stat;
}

void pull_int_pin(bool high)
{
    gpio_set_pin_output(BOARD_CAP_INTR_GPIO, BOARD_CAP_INTR_GPIO_INDEX, BOARD_CAP_INTR_GPIO_PIN);
    gpio_write_pin(BOARD_CAP_INTR_GPIO, BOARD_CAP_INTR_GPIO_INDEX, BOARD_CAP_INTR_GPIO_PIN, high);
}

void float_int_pin(void)
{
    gpio_set_pin_input(BOARD_CAP_INTR_GPIO, BOARD_CAP_INTR_GPIO_INDEX, BOARD_CAP_INTR_GPIO_PIN);
}

hpm_stat_t touch_init(I2C_Type *i2c_ptr)
{
    hpm_stat_t stat = status_success;

    gt9xx.ptr = i2c_ptr;

    stat = gt9xx_init(&gt9xx, BOARD_LCD_WIDTH, BOARD_LCD_HEIGHT);
    if (stat != status_success) {
        return stat;
    }
    gt9xx_write_register(&gt9xx, GT9XX_CMD, GT9XX_CMD_READ_COORD_STAT);

    return stat;
}

hpm_stat_t touch_config(bool exchange_xy, bool reverse_x, bool reverse_y)
{
    gt9xx.exchange_xy = exchange_xy;
    gt9xx.reverse_x = reverse_x;
    gt9xx.reverse_y = reverse_y;

    return status_success;
}
