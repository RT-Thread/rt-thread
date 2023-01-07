/**
 * @file hal_i2c.h
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#ifndef __HAL_I2C__H__
#define __HAL_I2C__H__

#include "hal_common.h"
#include "drv_device.h"
#include "bl808_config.h"

enum i2c_index_type {
#ifdef BSP_USING_I2C0
    I2C0_INDEX,
#endif
#ifdef BSP_USING_I2C1
    I2C1_INDEX,
#endif
#ifdef BSP_USING_I2C2
    I2C2_INDEX,
#endif
#ifdef BSP_USING_I2C3
    I2C3_INDEX,
#endif
    I2C_MAX_INDEX
};

#define I2C_WR      0x0000
#define I2C_RD      0x0001
#define I2C_RW_MASK 0x0001

#define SUB_ADDR_0BYTE 0x0010
#define SUB_ADDR_1BYTE 0x0020
#define SUB_ADDR_2BYTE 0x0040

#define I2C_HW_MODE 0
#define I2C_SW_MODE 1

typedef struct i2c_msg {
    uint8_t slaveaddr;
    uint32_t subaddr;
    uint16_t flags;
    uint16_t len;
    uint8_t *buf;
} i2c_msg_t;

typedef struct i2c_device {
    struct device parent;
    uint8_t id;
    uint8_t mode;
    uint32_t phase;
} i2c_device_t;

#define I2C_DEV(dev) ((i2c_device_t *)dev)

int i2c_register(enum i2c_index_type index, const char *name);
int i2c_transfer(struct device *dev, i2c_msg_t msgs[], uint32_t num);

#endif