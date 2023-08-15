/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_FT5406_H
#define HPM_FT5406_H
#include "hpm_common.h"
#include "hpm_i2c_drv.h"

#define FT5406_I2C_ADDR (0x38U)

/*
 * FT5406 registers at operation mode
 */
#define FT5406_DEVICE_MODE              (0U)
#define FT5406_GEST_ID                  (0x1U)
#define FT5406_TD_STATUS                (0x2U)
#define FT5406_TOUCH1_XH                (0x3U)
#define FT5406_TOUCH1_XL                (0x4U)
#define FT5406_TOUCH1_YH                (0x5U)
#define FT5406_TOUCH1_YL                (0x6U)

#define FT5406_TOUCH2_XH                (0x9U)
#define FT5406_TOUCH2_XL                (0xAU)
#define FT5406_TOUCH2_YH                (0xBU)
#define FT5406_TOUCH2_YL                (0xCU)

#define FT5406_TOUCH3_XH                (0xFU)
#define FT5406_TOUCH3_XL                (0x10U)
#define FT5406_TOUCH3_YH                (0x11U)
#define FT5406_TOUCH3_YL                (0x12U)

#define FT5406_TOUCH4_XH                (0x15U)
#define FT5406_TOUCH4_XL                (0x16U)
#define FT5406_TOUCH4_YH                (0x17U)
#define FT5406_TOUCH4_YL                (0x18U)

#define FT5406_TOUCH5_XH                (0x1BU)
#define FT5406_TOUCH5_XL                (0x1CU)
#define FT5406_TOUCH5_YH                (0x1DU)
#define FT5406_TOUCH5_YL                (0x1EU)

#define FT5406_ID_G_THGROUP             (0x80U)
#define FT5406_ID_G_THPEAK              (0x81U)
#define FT5406_ID_G_THCAL               (0x82U)
#define FT5406_ID_G_THWARTER            (0x83U)
#define FT5406_ID_G_THTEMP              (0x84U)

#define FT5406_ID_G_CTRL                (0x86U)
#define FT5406_ID_G_TIME_ENTER_MONITOR  (0x87U)
#define FT5406_ID_G_PERIODACTIVE        (0x88U)
#define FT5406_ID_G_PERIODMONITOR       (0x89U)

#define FT5406_ID_G_AUTO_CLB_MODE       (0xA0U)
#define FT5406_ID_G_LIB_VERSION_H       (0xA1U)
#define FT5406_ID_G_LIB_VERSION_L       (0xA2U)
#define FT5406_ID_G_CIPHER              (0xA3U)
#define FT5406_ID_G_MODE                (0xA4U)
#define FT5406_ID_G_PMODE               (0xA5U)
#define FT5406_ID_G_FIRM_ID             (0xA6U)
#define FT5406_ID_G_STATE               (0xA7U)
#define FT5406_ID_G_FT5201ID            (0xA8U)
#define FT5406_ID_G_ERR                 (0xA9U)
#define FT5406_ID_G_CLB                 (0xAAU)
#define FT5406_ID_G_B_AREA_TH           (0xAEU)

#define FT5406_DEVICE_MODE_NORMAL           (0)
#define FT5406_DEVICE_MODE_SYS_INFO         (1U)
#define FT5406_DEVICE_MODE_TEST             (2U)

#define FT5406_STATUS_CONFIGURE             (0)
#define FT5406_STATUS_WORK                  (1U)
#define FT5406_STATUS_CALIBRATION           (2U)
#define FT5406_STATUS_FACTORY               (3U)
#define FT5406_STATUS_AUTO_CALIBRATION      (4U)

#define FT5406_GESTURE_NO_GESTURE           (0)
#define FT5406_GESTURE_MOVE_UP              (0x10U)
#define FT5406_GESTURE_MOVE_LEFT            (0x14U)
#define FT5406_GESTURE_MOVE_DOWN            (0x18U)
#define FT5406_GESTURE_MOVE_RIGHT           (0x1CU)
#define FT5406_GESTURE_ZOOM_IN              (0x48U)
#define FT5406_GESTURE_ZOOM_OUT             (0x49U)

#define FT5406_MAX_TOUCH_POINTS             (5U)

typedef struct {
    uint8_t x_h;
    uint8_t x_l;
    uint8_t y_h;
    uint8_t y_l;
    uint16_t reserved;
} ft5406_touch_point_t;

typedef struct {
    uint8_t gesture;
    uint8_t status;
    ft5406_touch_point_t points[FT5406_MAX_TOUCH_POINTS];
} ft5406_touch_data_t;

typedef struct {
    I2C_Type *ptr;
} ft5406_context_t;

typedef struct {
    uint8_t mode;
    uint8_t bist_comm;
    uint8_t bist_stat;
    uint8_t reserved0[4];
    uint8_t uid[8];
    uint8_t bl_verh;
    uint8_t bl_verl;
    uint8_t fts_ic_verh;
    uint8_t fts_ic_verl;
    uint8_t app_idh;
    uint8_t app_idl;
    uint8_t app_verh;
    uint8_t app_verl;
    uint8_t reserved1[4];
    uint8_t cid[5];
} ft5406_sys_info_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ft5406 initialization routine
 */
hpm_stat_t ft5406_init(ft5406_context_t *context);

/*
 * ft5406 set working mode
 */
hpm_stat_t ft5406_set_mode(ft5406_context_t *context, uint8_t mode);

/*
 * ft5406 get system information
 */
hpm_stat_t ft5406_get_sys_info(ft5406_context_t *context,
                               ft5406_sys_info_t *info);

/*
 * ft5406 read touch data
 */
hpm_stat_t ft5406_read_touch_data(ft5406_context_t *context,
                                  ft5406_touch_data_t *touch_data);

/*
 * ft5406 read data
 */
hpm_stat_t ft5406_read_data(ft5406_context_t *context, uint8_t addr,
                            uint8_t *buf, uint32_t size);

/*
 * ft5406 write value to given register
 */
hpm_stat_t ft5406_write_register(ft5406_context_t *context,
                                 uint8_t reg, uint8_t val);

/*
 * ft5406 read value of given register
 */
hpm_stat_t ft5406_read_register(ft5406_context_t *context, uint8_t reg, uint8_t *buf);

#ifdef __cplusplus
}
#endif
#endif /* HPM_FT5406_H */
