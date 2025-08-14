/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#ifndef __DRV_HW_I2C_H__
#define __DRV_HW_I2C_H__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

/* I2C hardware configuration */
struct gd32_i2c_config
{
    rt_uint32_t i2c_periph;     /* I2C peripheral base address */
    rcu_periph_enum periph_clk; /* I2C peripheral clock */

    rcu_periph_enum scl_clk;    /* SCL pin clock */
    rt_uint32_t scl_port;       /* SCL pin port */
    rt_uint32_t scl_pin;        /* SCL pin */
    rt_uint32_t scl_af;         /* SCL pin alternate function */

    rcu_periph_enum sda_clk;    /* SDA pin clock */
    rt_uint32_t sda_port;       /* SDA pin port */
    rt_uint32_t sda_pin;        /* SDA pin */
    rt_uint32_t sda_af;         /* SDA pin alternate function */

    IRQn_Type ev_irq_type;      /* Event IRQn */
    IRQn_Type er_irq_type;      /* Error IRQn */

    rt_uint32_t i2c_clock_hz;        /* I2C clock speed in Hz, e.g., 100000 for 100kHz */

    const char *device_name;    /* Device name */
};

/* I2C runtime context */
struct gd32_i2c
{
    struct rt_i2c_bus_device parent;
    const struct gd32_i2c_config *config;

    struct rt_mutex bus_mutex;
    struct rt_completion sync_sem;
    uint32_t dev_config;
    uint16_t addr1;
    uint16_t addr2;
    uint32_t xfer_len;
    struct rt_i2c_msg *current;
    uint8_t errs;
    rt_bool_t is_restart;
};

int rt_hw_i2c_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_HW_I2C_H__ */

