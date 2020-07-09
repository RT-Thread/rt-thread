/*
 * File      : focaltech_ts.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * 2017-01-01     Urey      first version
 */
#ifndef _FOCALTECH_TS_H_
#define _FOCALTECH_TS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* -- dirver configure -- */
#define FTS_SLAVE_ADDR                      (0x70 >> 1)
#define CFG_MAX_TOUCH_POINTS                10
#define FTS_PRESS_MAX                       0xFF
#define FTS_PRESS                           0x08
#define FTS_NAME                            "FTS"
#define FTS_INPUT_DEV_NAME                  "focal-touchscreen"
#define FTS_MAX_ID                          0x0F
#define FTS_TOUCH_STEP                      6
#define FTS_TOUCH_X_H_POS                   3
#define FTS_TOUCH_X_L_POS                   4
#define FTS_TOUCH_Y_H_POS                   5
#define FTS_TOUCH_Y_L_POS                   6
#define FTS_TOUCH_XY_POS                    7
#define FTS_TOUCH_MISC                      8
#define FTS_TOUCH_EVENT_POS                 3
#define FTS_TOUCH_ID_POS                    5
#define FT_TOUCH_POINT_NUM                  2
#define POINT_READ_BUF                      (3 + FTS_TOUCH_STEP * CFG_MAX_TOUCH_POINTS)

/*register address*/
#define FTS_REG_CHIP_ID                     0xA3    //chip ID
#define FTS_REG_FW_VER                      0xA6
#define FTS_REG_POINT_RATE                  0x88
#define FTS_REG_THGROUP                     0x80
#define FTS_REG_VENDOR_ID                   0xA8

#define FTS_ENABLE_IRQ                      1
#define FTS_DISABLE_IRQ                     0
#define TPD_MAX_POINTS_2                    2
#define TPD_MAX_POINTS_5                    5
#define TPD_MAXPOINTS_10                    10
#define AUTO_CLB_NEED                       1
#define AUTO_CLB_NONEED                     0

#define TOUCH_SWAP_XY           1
#define TOUCH_SWAP_X            0
#define TOUCH_SWAP_Y            1

struct Upgrade_Info
{
    uint8_t  CHIP_ID;
    uint8_t  FTS_NAME_INFO[20];
    uint8_t  TPD_MAX_POINTS;
    uint8_t  AUTO_CLB;
    uint16_t delay_aa; /*delay of write FTS_UPGRADE_AA */
    uint16_t delay_55; /*delay of write FTS_UPGRADE_55 */
    uint8_t  upgrade_id_1; /*upgrade id 1 */
    uint8_t  upgrade_id_2; /*upgrade id 2 */
    uint16_t delay_readid; /*delay of read id */
    uint16_t delay_earse_flash; /*delay of earse flash*/
};

/* The platform data for the Focaltech focaltech touchscreen driver */
struct fts_platform_data
{
    uint32_t gpio_irq;                                                  /* IRQ port*/
    uint32_t irq_cfg;
    uint32_t gpio_wakeup;                                           /* Wakeup support*/
    uint32_t wakeup_cfg;
    uint32_t gpio_reset;                                                /* Reset support*/
    uint32_t reset_cfg;
    int screen_max_x;
    int screen_max_y;
    int pressure_max;
};

struct fts_event
{
    uint16_t au16_x[CFG_MAX_TOUCH_POINTS];                            /*x coordinate */
    uint16_t au16_y[CFG_MAX_TOUCH_POINTS];                            /*y coordinate */
    uint8_t  au8_touch_event[CFG_MAX_TOUCH_POINTS];                   /*touch event:0 -- down; 1-- contact; 2 -- contact */
    uint8_t  au8_finger_id[CFG_MAX_TOUCH_POINTS];                     /*touch ID */
    uint8_t  au8_finger_weight[CFG_MAX_TOUCH_POINTS];                 /*touch weight */
    uint8_t  pressure[CFG_MAX_TOUCH_POINTS];
    uint8_t  area[CFG_MAX_TOUCH_POINTS];
    uint8_t  touch_point;
    uint8_t  touch_point_num;
};

struct focal_i2c_platform_data
{
    uint16_t version;
    int abs_x_min;
    int abs_x_max;
    int abs_y_min;
    int abs_y_max;
    int intr_gpio;
    int rst_gpio;
};

struct fts_ts_data
{
    uint8_t  addr;
    uint8_t  fw_ver;     //firmware version
    uint32_t x_min,x_max;
    uint32_t y_min,y_max;
    uint32_t init_success;
    struct fts_event event;

    struct rt_i2c_bus_device *i2c_bus;
    struct rt_semaphore     sem;
    int touchs;
};

void fts_ts_interrupt_cb(struct fts_ts_data *fts_ts);
int  fts_ts_probe(struct fts_ts_data *fts_ts,struct rt_i2c_bus_device *i2c_bus, const uint8_t addr);

#ifdef __cplusplus
}
#endif

#endif /* _FOCALTECH_TS_H_ */
