/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_OV5640_H
#define HPM_OV5640_H

#include "hpm_common.h"
#include "hpm_camera_config.h"

#define OV5640_ACTIVE_IMAGE_WIDTH  (2592U)
#define OV5640_ACTIVE_IMAGE_HEIGHT (1944U)
#define OV5640_I2C_ADDR (0x3CU)
#define OV5640_CHIP_ID_HIGH_BYTE_ADDR             (0x300A)
#define OV5640_CHIP_ID_HIGH_BYTE_VALUE            (0x56)
#define OV5640_CHIP_ID_LOW_BYTE_ADDR              (0x300B)
#define OV5640_CHIP_ID_LOW_BYTE_VALUE             (0x40)

#define OV5640_RST_ACTIVE    0
#define OV5640_RST_INACTIVE  1
#define OV5640_PWDN_ACTIVE   1
#define OV5640_PWDN_INACTIVE 0

/* Camera clock configuration elements. */
typedef struct {
    uint32_t resolution;
    uint8_t fps;
    uint8_t pllctrl1;
    uint8_t pllctrl2;
    uint8_t vfifoctrl0c;
    uint8_t pclkdiv;
    uint8_t pclkperiod;
} ov5640_clock_config_t;

typedef struct {
    uint8_t lightmode;
    uint8_t awbctrl;
    uint8_t awbr_h;
    uint8_t awbr_l;
    uint8_t awbg_h;
    uint8_t awbg_l;
    uint8_t awbb_h;
    uint8_t awbb_l;
} ov5640_light_mode_config_t;

typedef struct {
    uint8_t effect;
    uint8_t sdectrl0;
    uint8_t sdectrl3;
    uint8_t sdectrl4;
} ov5640_special_effect_config_t;

typedef struct {
    uint16_t regaddr;
    uint8_t regval;
} ov5640_reg_val_t;

typedef struct {
    uint32_t resolution; /*!< Resolution. */
    ov5640_reg_val_t param[]; /*!< register value from 0x3800 to 0x3813. */
} ov5640_resolution_param_t;


#ifdef __cplusplus
extern "C" {
#endif

/*
 * ov5640 initialization
 */
hpm_stat_t ov5640_init(camera_context_t *context, camera_config_t *ov_config);

/*
 * ov5640 read register
 */
hpm_stat_t ov5640_read_register(camera_context_t *context, uint16_t reg, uint8_t *buf);

/*
 * ov5640 write register
 */
hpm_stat_t ov5640_write_register(camera_context_t *context, uint16_t reg, uint8_t val);

/*
 * ov5640 write multi register
 */
hpm_stat_t ov5640_write_multi_registers(camera_context_t *context, const ov5640_reg_val_t regval[], uint32_t len);

/*
 * ov5640 softreset
 */
hpm_stat_t ov5640_software_reset(camera_context_t *context);

/*
 * ov5640 set pixel format
 */
hpm_stat_t ov5640_set_pixel_format(camera_context_t *context, display_pixel_format_t pixel_format);

/*
 * ov5640 check chip id
 */
hpm_stat_t ov5640_check_chip_id(camera_context_t *context);

/*
 * ov5640 set image size
 */
hpm_stat_t ov5640_set_image_size(camera_context_t *context, camera_config_t *ov_config);

/*
 * ov5640 set clock config
 */
hpm_stat_t ov5640_set_clock_config(camera_context_t *context, camera_config_t *ov_config);

/*
 * ov5640 set interface
 */
hpm_stat_t ov5640_set_interface(camera_context_t *context, camera_config_t *ov_config);

/**
 * @brief set ov5640 flip
 *
 * @param context @ref camera_context_t
 * @return hpm_stat_t
 */
hpm_stat_t ov5640_flip(camera_context_t *context);

/*
 * ov5640 start
 */
hpm_stat_t ov5640_start(camera_context_t *context);

/*
 * ov5640 stop
 */
hpm_stat_t ov5640_stop(camera_context_t *context);

/*
 * ov5640 set brightness
 */
hpm_stat_t ov5640_set_brightness(camera_context_t *context, int32_t brightness);

/*
 * ov5640 set contrast
 */
hpm_stat_t ov5640_set_contrast(camera_context_t *context, int32_t contrast);

/*
 * ov5640 set saturation
 */
hpm_stat_t ov5640_set_saturation(camera_context_t *context, int32_t saturation);

/*
 * ov5640 set environment light mode
 */
hpm_stat_t ov5640_set_light_mode(camera_context_t *context, int32_t lightmode);

/*
 * ov5640 set special effect
 */
hpm_stat_t ov5640_set_special_effect(camera_context_t *context, int32_t effect);

/**
 * @brief ov5640 power up
 *
 * @param [in] context camera_context_t
 */
void ov5640_power_up(camera_context_t *context);

#ifdef __cplusplus
}
#endif
#endif /* HPM_OV5640_H */
