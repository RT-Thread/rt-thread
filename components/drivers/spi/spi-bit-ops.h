/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-11     kyle          first version
 */

#ifndef __SPI_BIT_OPS_H__
#define __SPI_BIT_OPS_H__

#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

struct rt_spi_bit_ops
{
    void *const data;            /* private data for lowlevel routines */
    void (*const tog_sclk)(void *data);
    void (*const set_sclk)(void *data, rt_int32_t state);
    void (*const set_mosi)(void *data, rt_int32_t state);
    void (*const set_miso)(void *data, rt_int32_t state);
    rt_int32_t (*const get_sclk)(void *data);
    rt_int32_t (*const get_mosi)(void *data);
    rt_int32_t (*const get_miso)(void *data);

    void (*const dir_mosi)(void *data, rt_int32_t state);
    void (*const dir_miso)(void *data, rt_int32_t state);

    void (*const udelay)(rt_uint32_t us);
    rt_uint32_t delay_us;  /* sclk, mosi and miso line delay */
};

struct rt_spi_bit_obj
{
    struct rt_spi_bus bus;
    struct rt_spi_bit_ops *ops;
    struct rt_spi_configuration config;
};

rt_err_t rt_spi_bit_add_bus(struct rt_spi_bit_obj *obj,
                            const char            *bus_name,
                            struct rt_spi_bit_ops *ops);

#ifdef __cplusplus
}
#endif

#endif
