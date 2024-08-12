/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_GT9XX_H
#define HPM_GT9XX_H
#include "board.h"
#include "hpm_common.h"
#include "hpm_i2c_drv.h"

#ifdef BOARD_GT9XX_ADDR
/* if i2c addres is specified by board, use it */
#define GT9XX_I2C_ADDR BOARD_GT9XX_ADDR
/* no auto probe in this case */
#define GT9XX_NO_AUTO_PROBE 1
#else
#undef GT9XX_I2C_ADDR

/* enable auto probe */
#ifndef GT9XX_NO_AUTO_PROBE
#define GT9XX_NO_AUTO_PROBE 0
#endif

/* i2c device address candidates */
#define GT9XX_I2C_ADDR0 (0x14U)
#define GT9XX_I2C_ADDR1 (0x5DU)
#endif

#define GT9XX_PRODUCT_ID (0x313139U)
/*
 * GT9XX registers at operation mode
 */

#define GT9XX_CMD                    (0x8040U)
#define   GT9XX_CMD_READ_COORD_STAT  (0U)
#define   GT9XX_CMD_READ_RAW_DATA    (1U)
#define   GT9XX_CMD_SOFT_RESET       (2U)
#define   GT9XX_CMD_READ_SCREEN_OFF  (5U)

#define GT9XX_CONFIG                    (0x8047U)

#define GT9XX_ID_B0                     (0x8140U)
#define GT9XX_ID_B1                     (0x8141U)
#define GT9XX_ID_B2                     (0x8142U)
#define GT9XX_ID_B4                     (0x8143U)
#define GT9XX_FW_VERSION_L              (0x8144U)
#define GT9XX_FW_VERSION_H              (0x8145U)
#define GT9XX_TOUCH_XL                  (0x8146U)
#define GT9XX_TOUCH_XH                  (0x8147U)
#define GT9XX_TOUCH_YL                  (0x8148U)
#define GT9XX_TOUCH_YH                  (0x8149U)
#define GT9XX_VENDOR_ID                 (0x814AU)
#define GT9XX_STATUS                    (0x814EU)
#define GT9XX_GET_STATUS_NUM_OF_POINTS(x)  ((x) & 0xFU)
#define GT9XX_GET_STATUS_LARGE_DETECT(x)   (((x) & 0x40U) >> 6)
#define GT9XX_GET_STATUS_BUFFER_STAT(x)    (((x) & 0x80U) >> 7)
#define GT9XX_FIRST_POINT               (0x814FU)

#define GT9XX_MAX_TOUCH_POINTS             (5U)
#define GT9XX_CONFIG_DATA_SIZE             (186U)
#define GT9XX_CONFIG_DATA_CONFIG_VERSION   (0U)
#define GT9XX_CONFIG_DATA_RESOLUTION_XL    (1U)
#define GT9XX_CONFIG_DATA_RESOLUTION_XH    (2U)
#define GT9XX_CONFIG_DATA_RESOLUTION_YL    (3U)
#define GT9XX_CONFIG_DATA_RESOLUTION_YH    (4U)
#define GT9XX_CONFIG_DATA_TOUCH_NUMBER     (5U)
#define GT9XX_CONFIG_DATA_MODULE_SWITCH1   (6U)

typedef struct {
    uint8_t track_id;
    uint8_t x_l;
    uint8_t x_h;
    uint8_t y_l;
    uint8_t y_h;
    uint8_t size_l;
    uint8_t size_h;
    uint8_t reserved;
} gt9xx_touch_point_t;

typedef struct {
    uint8_t status;
    gt9xx_touch_point_t points[GT9XX_MAX_TOUCH_POINTS];
} gt9xx_touch_data_t;

typedef struct {
    I2C_Type *ptr;
    uint16_t abs_x_max;
    uint16_t abs_y_max;
    bool exchange_xy;
    bool reverse_x;
    bool reverse_y;
} gt9xx_context_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * gt9xx initialization routine
 */
hpm_stat_t gt9xx_init(gt9xx_context_t *context, uint16_t width, uint16_t height);

/*
 * gt9xx read touch data
 */
hpm_stat_t gt9xx_read_touch_data(gt9xx_context_t *context,
                                  gt9xx_touch_data_t *touch_data);

/*
 * gt9xx read data
 */
hpm_stat_t gt9xx_read_data(gt9xx_context_t *context, uint16_t addr,
                            uint8_t *buf, uint32_t size);

/*
 * gt9xx write value to given register
 */
hpm_stat_t gt9xx_write_register(gt9xx_context_t *context,
                                 uint16_t reg, uint8_t val);

/*
 * gt9xx read value of given register
 */
hpm_stat_t gt9xx_read_register(gt9xx_context_t *context, uint16_t reg, uint8_t *buf);

/*
 * gt9xx read config data
 */
hpm_stat_t gt9xx_read_config(gt9xx_context_t *context, uint8_t *buf, uint8_t size);
#ifdef __cplusplus
}
#endif
#endif /* HPM_GT9XX_H */
