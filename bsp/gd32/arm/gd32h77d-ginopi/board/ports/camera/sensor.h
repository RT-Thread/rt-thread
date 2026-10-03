/*
 * This file is part of the OpenMV project.
 *
 * Copyright (c) 2013-2021 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * Copyright (c) 2013-2021 Kwabena W. Agyeman <kwagyeman@openmv.io>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * Minimal sensor abstraction used by the GD32 OV7670 port.
 */
#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "omv_i2c.h"

#define OV_CHIP_ID                  (0x0AU)
#define OV7670_ID                   (0x76U)
#define SENSOR_HW_FLAGS_YVU422      (1U)

typedef enum
{
    PIXFORMAT_INVALID = 0,
    PIXFORMAT_RGB565,
    PIXFORMAT_YUV422,
    PIXFORMAT_GRAYSCALE
} pixformat_t;

typedef enum
{
    FRAMESIZE_INVALID = 0,
    FRAMESIZE_QQVGA,
    FRAMESIZE_QVGA,
    FRAMESIZE_VGA
} framesize_t;

typedef struct _sensor sensor_t;

struct _sensor
{
    rt_uint8_t chip_id;
    rt_uint8_t slv_addr;
    struct
    {
        rt_uint32_t vsync : 1;
        rt_uint32_t hsync : 1;
        rt_uint32_t pixck : 1;
        rt_uint32_t fsync : 1;
        rt_uint32_t jpege : 1;
        rt_uint32_t gs_bpp : 2;
        rt_uint32_t rgb_swap : 1;
        rt_uint32_t yuv_order : 1;
    } hw_flags;
    bool disable_delays;
    bool detected;
    pixformat_t pixformat;
    framesize_t framesize;
    bool hmirror;
    bool vflip;
    omv_i2c_t i2c_bus;

    int (*reset)(sensor_t *sensor);
    int (*sleep)(sensor_t *sensor, int enable);
    int (*read_reg)(sensor_t *sensor, uint16_t reg_addr);
    int (*write_reg)(sensor_t *sensor, uint16_t reg_addr, uint16_t reg_data);
    int (*set_pixformat)(sensor_t *sensor, pixformat_t pixformat);
    int (*set_framesize)(sensor_t *sensor, framesize_t framesize);
    int (*set_hmirror)(sensor_t *sensor, int enable);
    int (*set_vflip)(sensor_t *sensor, int enable);
};

extern sensor_t sensor;

int ov7670_init(sensor_t *sensor);
int sensor_init(void);
int sensor_reset(void);
int sensor_read_reg(uint16_t reg_addr);
int sensor_write_reg(uint16_t reg_addr, uint16_t reg_data);
int sensor_set_pixformat(pixformat_t pixformat);
int sensor_set_framesize(framesize_t framesize);
int sensor_set_hmirror(int enable);
int sensor_set_vflip(int enable);
bool sensor_is_detected(void);

#endif /* __SENSOR_H__ */
