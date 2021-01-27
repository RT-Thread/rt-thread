/*
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-30     CDT          first version
 */
 

#ifndef __DRV_I2C_H__
#define __DRV_I2C_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtdevice.h>
#include "hc32_ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
struct hc32_soft_i2c_config
{
    rt_uint16_t scl_pin;
    rt_uint16_t sda_pin;
    const char *bus_name;
};

#ifdef BSP_USING_I2C1
#define I2C1_BUS_CONFIG                                  \
    {                                                    \
        .scl_pin  = BSP_I2C1_SCL_PIN,                    \
        .sda_pin  = BSP_I2C1_SDA_PIN,                    \
        .bus_name = "i2c1",                              \
    }
#endif

#ifdef BSP_USING_I2C2
#define I2C2_BUS_CONFIG                                  \
    {                                                    \
        .scl = BSP_I2C2_SCL_PIN,                         \
        .sda = BSP_I2C2_SDA_PIN,                         \
        .bus_name = "i2c2",                              \
    }
#endif
    
#ifdef BSP_USING_I2C3
#define I2C3_BUS_CONFIG                                  \
    {                                                    \
        .scl = BSP_I2C3_SCL_PIN,                         \
        .sda = BSP_I2C3_SDA_PIN,                         \
        .bus_name = "i2c3",                              \
    }
#endif
		
#ifdef BSP_USING_I2C4
#define I2C4_BUS_CONFIG                                  \
    {                                                    \
        .scl = BSP_I2C4_SCL_PIN,                         \
        .sda = BSP_I2C4_SDA_PIN,                         \
        .bus_name = "i2c4",                              \
    }
#endif

#ifdef BSP_USING_I2C5
#define I2C5_BUS_CONFIG                                  \
    {                                                    \
        .scl = BSP_I2C5_SCL_PIN,                         \
        .sda = BSP_I2C5_SDA_PIN,                         \
        .bus_name = "i2c5",                              \
    }
#endif
		
#ifdef BSP_USING_I2C6
#define I2C6_BUS_CONFIG                                  \
    {                                                    \
        .scl = BSP_I2C6_SCL_PIN,                         \
        .sda = BSP_I2C6_SDA_PIN,                         \
        .bus_name = "i2c6",                              \
    }
#endif

/**
 *******************************************************************************
 ** \brief Open parameters.
 *******************************************************************************
 */
struct hc32_i2c_config
{
    rt_uint8_t scl;
    rt_uint8_t sda;
    const char *bus_name;
};

struct hc32_i2c
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device i2c1_bus;
};


typedef struct hc32_i2c_instance
{
    rt_uint32_t id;
    void *handle;
    stc_i2c_init_t init;
} hc32_i2c_instance_t;


int hc32_hw_i2c_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_I2C_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
