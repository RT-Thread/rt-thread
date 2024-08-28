/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-31     shelton      first version
 */

#ifndef __DRV_HARD_I2C_H__
#define __DRV_HARD_I2C_H__

#include <rtthread.h>
#include <drivers/dev_i2c.h>
#include "drv_common.h"
#include "drv_dma.h"

#define I2C_START                        0
#define I2C_END                          1

#define I2C_EVENT_CHECK_NONE             ((uint32_t)0x00000000)
#define I2C_EVENT_CHECK_ACKFAIL          ((uint32_t)0x00000001)
#define I2C_EVENT_CHECK_STOP             ((uint32_t)0x00000002)

typedef enum
{
    I2C_INT_MA_TX = 0,
    I2C_INT_MA_RX,
    I2C_INT_SLA_TX,
    I2C_INT_SLA_RX,
    I2C_DMA_MA_TX,
    I2C_DMA_MA_RX,
    I2C_DMA_SLA_TX,
    I2C_DMA_SLA_RX,
} i2c_mode_type;

typedef enum
{
    I2C_OK = 0,
    I2C_ERR_STEP_1,
    I2C_ERR_STEP_2,
    I2C_ERR_STEP_3,
    I2C_ERR_STEP_4,
    I2C_ERR_STEP_5,
    I2C_ERR_STEP_6,
    I2C_ERR_STEP_7,
    I2C_ERR_STEP_8,
    I2C_ERR_STEP_9,
    I2C_ERR_STEP_10,
    I2C_ERR_STEP_11,
    I2C_ERR_STEP_12,
    I2C_ERR_START,
    I2C_ERR_ADDR10,
    I2C_ERR_TCRLD,
    I2C_ERR_TDC,
    I2C_ERR_ADDR,
    I2C_ERR_STOP,
    I2C_ERR_ACKFAIL,
    I2C_ERR_TIMEOUT,
    I2C_ERR_INTERRUPT,
} i2c_status_type;

struct i2c_comm_type
{
    rt_uint8_t *pbuff;
    rt_uint16_t psize;
    rt_uint16_t pcount;
    i2c_mode_type mode;
    rt_uint32_t timeout;
    rt_uint32_t status;
    i2c_status_type error_code;
};

struct at32_i2c_handle
{
    i2c_type *i2c_x;
    const char *i2c_name;
    rt_uint32_t timing;
    IRQn_Type ev_irqn;
    IRQn_Type er_irqn;
    struct dma_config *dma_rx;
    struct dma_config *dma_tx;
    struct i2c_comm_type comm;
    rt_uint16_t i2c_dma_flag;
    struct rt_completion completion;
};

struct at32_i2c
{
    struct at32_i2c_handle *handle;
    struct rt_i2c_bus_device i2c_bus;
};

#endif
