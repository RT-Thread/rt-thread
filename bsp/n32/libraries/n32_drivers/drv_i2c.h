/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file drv_i2c.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */

#ifndef __DRV_I2C__
#define __DRV_I2C__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

/* n32 config class */
struct n32_soft_i2c_config
{
    rt_uint8_t scl;
    rt_uint8_t sda;
    const char *bus_name;
};

/* n32 i2c dirver class */
struct n32_i2c
{
    struct rt_i2c_bit_ops ops;
    struct rt_i2c_bus_device i2c2_bus;
};

#ifdef BSP_USING_I2C1
#define I2C1_BUS_CONFIG                                  \
    {                                                    \
        .scl = BSP_I2C1_SCL_PIN,                         \
        .sda = BSP_I2C1_SDA_PIN,                         \
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

struct rt_i2c_bus
{
    struct rt_i2c_bus_device parent;
    rt_uint32_t i2c_periph;
};

int rt_hw_i2c_init(void);

#endif /* __DRV_I2C__ */
