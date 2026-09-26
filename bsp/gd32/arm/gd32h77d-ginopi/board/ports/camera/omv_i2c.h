/*
 * This file is part of the OpenMV project.
 *
 * Copyright (c) 2013-2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * Copyright (c) 2013-2023 Kwabena W. Agyeman <kwagyeman@openmv.io>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#ifndef __OMV_I2C_H__
#define __OMV_I2C_H__

#include <stdint.h>
#include <stdbool.h>

#include "omv_portconfig.h"

typedef enum
{
    OMV_I2C_SPEED_STANDARD = 0U,
    OMV_I2C_SPEED_FULL = 1U,
    OMV_I2C_SPEED_FAST = 2U,
    OMV_I2C_SPEED_MAX = 3U
} omv_i2c_speed_t;

typedef enum
{
    OMV_I2C_XFER_NO_FLAGS = 0U,
    OMV_I2C_XFER_NO_STOP = 1U << 0,
    OMV_I2C_XFER_SUSPEND = 1U << 1
} omv_i2c_xfer_flags_t;

typedef struct
{
    rt_uint32_t id;
    rt_uint32_t speed;
    rt_uint32_t initialized;
    omv_gpio_t scl_pin;
    omv_gpio_t sda_pin;
    omv_i2c_dev_t inst;
} omv_i2c_t;

int omv_i2c_init(omv_i2c_t *bus, rt_uint32_t bus_id, rt_uint32_t speed);
int omv_i2c_deinit(omv_i2c_t *bus);
int omv_i2c_scan(omv_i2c_t *bus, rt_uint8_t *list, rt_uint8_t size);
int omv_i2c_enable(omv_i2c_t *bus, bool enable);
int omv_i2c_readb(omv_i2c_t *bus, rt_uint8_t slv_addr,
                  rt_uint8_t reg_addr, rt_uint8_t *reg_data);
int omv_i2c_writeb(omv_i2c_t *bus, rt_uint8_t slv_addr,
                   rt_uint8_t reg_addr, rt_uint8_t reg_data);

int gd32_camera_sccb_read(rt_uint8_t slv_addr, rt_uint8_t reg,
                          rt_uint8_t *value);
int gd32_camera_sccb_write(rt_uint8_t slv_addr, rt_uint8_t reg,
                           rt_uint8_t value);

#endif /* __OMV_I2C_H__ */
