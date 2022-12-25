/**
 * @file hal_i2c.c
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
#include "hal_i2c.h"
#include "hal_gpio.h"
#include "bl808_i2c.h"
#include "bl808_glb.h"

static i2c_device_t i2cx_device[I2C_MAX_INDEX] = {
#ifdef BSP_USING_I2C0
    I2C0_CONFIG,
#endif
#ifdef BSP_USING_I2C1
    I2C1_CONFIG,
#endif
#ifdef BSP_USING_I2C2
    I2C2_CONFIG,
#endif
#ifdef BSP_USING_I2C3
    I2C3_CONFIG,
#endif
};
/**
 * @brief
 *
 * @param dev
 * @param oflag
 * @return int
 */
int i2c_open(struct device *dev, uint16_t oflag)
{
    i2c_device_t *i2c_device = (i2c_device_t *)dev;

    if (i2c_device->mode == I2C_HW_MODE) {
        I2C_SetPrd(i2c_device->id, i2c_device->phase);
    }

    return 0;
}

/**
 * @brief
 *
 * @param index
 * @param name
 * @param flag
 * @return int
 */
int i2c_register(enum i2c_index_type index, const char *name)
{
    struct device *dev;

    if (I2C_MAX_INDEX == 0) {
        return -DEVICE_EINVAL;
    }

    dev = &(i2cx_device[index].parent);

    dev->open = i2c_open;
    dev->close = NULL;
    dev->control = NULL;
    dev->write = NULL;
    dev->read = NULL;

    dev->type = DEVICE_CLASS_I2C;
    dev->handle = NULL;

    return device_register(dev, name);
}
/**
 * @brief
 *
 * @param dev
 * @param msgs
 * @param num
 * @return uint32_t
 */
int i2c_transfer(struct device *dev, i2c_msg_t msgs[], uint32_t num)
{
    i2c_msg_t *msg;
    I2C_Transfer_Cfg i2cCfg = { 0 };

    i2c_device_t *i2c_device = (i2c_device_t *)dev;

    if (i2c_device->mode == I2C_HW_MODE) {
        for (uint32_t i = 0; i < num; i++) {
            msg = &msgs[i];
            i2cCfg.slaveAddr = msg->slaveaddr;
            i2cCfg.stopEveryByte = DISABLE;
            i2cCfg.subAddr = msg->subaddr;
            i2cCfg.dataSize = msg->len;
            i2cCfg.data = msg->buf;

            if (msg->flags & SUB_ADDR_0BYTE) {
                i2cCfg.subAddrSize = 0;
            } else if (msg->flags & SUB_ADDR_1BYTE) {
                i2cCfg.subAddrSize = 1;
            } else if (msg->flags & SUB_ADDR_2BYTE) {
                i2cCfg.subAddrSize = 2;
            }

            if ((msg->flags & I2C_RW_MASK) == I2C_WR) {
                return I2C_MasterSendBlocking(i2c_device->id, &i2cCfg);
            } else if ((msg->flags & I2C_RW_MASK) == I2C_RD) {
                return I2C_MasterReceiveBlocking(i2c_device->id, &i2cCfg);
            }
        }
    } else {
    }

    return 0;
}