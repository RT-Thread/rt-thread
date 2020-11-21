/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-14     wangqiang    the first version
 */

#ifndef __MDIO_H__
#define __MDIO_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C"
{
#endif


struct rt_mdio_bus_ops
{
    rt_bool_t (*init)(void *bus, rt_uint32_t src_clock_hz);
    rt_size_t (*read)(void *bus, rt_uint32_t addr, rt_uint32_t reg, void *data, rt_uint32_t size);
    rt_size_t (*write)(void *bus, rt_uint32_t addr, rt_uint32_t reg, void *data, rt_uint32_t size);
    rt_bool_t (*uninit)(void *bus);
};

struct rt_mdio_bus
{
    void *hw_obj;
    char *name;
    struct rt_mdio_bus_ops *ops;
};

typedef struct rt_mdio_bus rt_mdio_t;

#ifdef __cplusplus
}
#endif

#endif
