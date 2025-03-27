/*
 * File      : drv_can.h
 * This file is part of RT-Thread RTOS
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author               Notes
 * 2025-18-03     Dmitriy Chernov      first implementation
 */

#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <board.h>
#include <rtdevice.h>

#define BS1SHIFT        16
#define BS2SHIFT        20
#define RRESCLSHIFT     0
#define SJWSHIFT        24
#define BS1MASK         ((0x0F) << BS1SHIFT )
#define BS2MASK         ((0x07) << BS2SHIFT )
#define RRESCLMASK      (0x3FF << RRESCLSHIFT )
#define SJWMASK         (0x3 << SJWSHIFT )

struct gd32_can
{
    rcu_periph_enum can_clk;
    rcu_periph_enum tx_clk;
    rcu_periph_enum rx_clk;
#if defined SOC_SERIES_GD32F4xx
    uint32_t alt_func_num;
#endif
    rt_base_t tx_pin;
    rt_base_t rx_pin;
};

struct gd32_baudrate_tbl
{
    rt_uint32_t baudrate;
    rt_uint32_t sjw;
    rt_uint32_t tseg1;
    rt_uint32_t tseg2;
    rt_uint32_t prescaler;
};

/* gd32 can device */
struct gd32_can_device
{
    char *name;
    rt_uint32_t can_x;
    can_filter_parameter_struct filter_config;
    struct rt_can_device device;     /* inherit from can device */
};

int rt_hw_can_init(void);

#ifdef __cplusplus
}
#endif

#endif /*__DRV_CAN_H__ */

/************************** end of file ******************/
