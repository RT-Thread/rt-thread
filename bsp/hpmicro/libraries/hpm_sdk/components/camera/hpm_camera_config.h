/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_CAMERA_CONFIG_H
#define HPM_CAMERA_CONFIG_H

#include "hpm_common.h"
#include "hpm_display_common.h"
#include "hpm_i2c_drv.h"

/* Macro to define video resolution. */
#define HPM_CAMERA_RESOLUTION(width, height) ((uint32_t)(width) | ((uint32_t)(height) << 16U))

typedef struct {
    I2C_Type *ptr;
    void (*delay_ms)(uint32_t ms);
    void (*write_rst)(uint8_t state);
    void (*write_pwdn)(uint8_t state);
    uint16_t i2c_device_addr;
} camera_context_t;

typedef struct {
    bool hsync_active_low;
    bool vsync_active_low;
} camera_param_dvp_t;

typedef struct {
    bool de_active_low;
    bool hsync_active_low;
    bool vsync_active_low;
} camera_param_mipi_t;

typedef enum {
    camera_interface_dvp,
    camera_interface_mipi,
} camera_interface_t;

typedef struct {
    uint32_t width;
    uint32_t height;
    display_pixel_format_t pixel_format;
    camera_interface_t interface;
    void *interface_param;
} camera_config_t;

/* Video Resolution definition. */
typedef enum {
    video_resolution_5mp     = HPM_CAMERA_RESOLUTION(2592, 1944), /* 5MP, 2592 * 1944 */
    video_resolution_sxga    = HPM_CAMERA_RESOLUTION(1280, 800),  /* SXGA, 1280 * 800 */
    video_resolution_1080p   = HPM_CAMERA_RESOLUTION(1920, 1080), /* 1080P, 1920 * 1280*/
    video_resolution_720p    = HPM_CAMERA_RESOLUTION(1280, 720),  /* 720P, 1280 * 720 */
    video_resolution_800_480 = HPM_CAMERA_RESOLUTION(800, 480),   /* 640 * 480 */
    video_resolution_vga     = HPM_CAMERA_RESOLUTION(640, 480),   /* VGA, 640 * 480 */
    video_resolution_480_272 = HPM_CAMERA_RESOLUTION(480, 272),   /* 480 * 272 */
    video_resolution_qvga    = HPM_CAMERA_RESOLUTION(320, 240),   /* QVGA, 320 * 240 */
} camera_resolution_t;

/* Camera light mode type. */
typedef enum {
    camera_light_mode_auto = 0,
    camera_light_mode_sunny,
    camera_light_mode_cloudy,
    camera_light_mode_office,
    camera_light_mode_home,
    camera_light_mode_night,
} camera_light_mode_t;

/* Camera special effect type. */
typedef enum {
    camera_special_effect_normal = 0,    /* Normal. */
    camera_special_effect_bw,            /* B & W */
    camera_special_effect_sepia,         /* Sepia. */
    camera_special_effect_bluish,        /* Bluish. */
    camera_special_effect_redish,        /* Redish. */
    camera_special_effect_greenish,      /* Greenish. */
    camera_special_effect_negtive,       /* Negtive. */
    camera_special_effect_over_exposure, /* OverExposure. */
    camera_special_effect_solarize,      /* Solarize. */
} camera_special_effect_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * camera device initialization
 */
hpm_stat_t camera_device_init(camera_context_t *camera_context, camera_config_t *camera_config);
hpm_stat_t camera_device_get_dvp_param(camera_context_t *camera_context, camera_config_t *camera_config);
hpm_stat_t camera_device_get_mipi_param(camera_context_t *camera_context, camera_config_t *camera_config);

#ifdef __cplusplus
}
#endif

#endif /* HPM_CAMERA_CONFIG_H */
