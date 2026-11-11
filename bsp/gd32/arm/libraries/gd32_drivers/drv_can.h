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

#if defined(SOC_SERIES_GD32H77x_H78X)
#ifdef RT_CAN_USING_CANFD
#define GD32_CAN_RX_MAILBOX_NUM    3U
#define GD32_CAN_TX_MAILBOX_NUM    4U
#else
#define GD32_CAN_RX_MAILBOX_NUM    16U
#define GD32_CAN_TX_MAILBOX_NUM    16U
#endif
#define GD32_CAN_TX_MAILBOX_FIRST  GD32_CAN_RX_MAILBOX_NUM
#define GD32_CAN_MAILBOX_NUM       (GD32_CAN_RX_MAILBOX_NUM + GD32_CAN_TX_MAILBOX_NUM)
#define GD32_CAN_RX_INT_MASK       BITS(0, GD32_CAN_RX_MAILBOX_NUM - 1U)
#define GD32_CAN_TX_INT_MASK       BITS(GD32_CAN_TX_MAILBOX_FIRST, GD32_CAN_MAILBOX_NUM - 1U)
#endif

struct gd32_can
{
    rcu_periph_enum can_clk;
#if defined(SOC_SERIES_GD32H77x_H78X)
    const char *tx_pin_name;
    const char *rx_pin_name;
    const char *tx_alternate;
    const char *rx_alternate;
#else
    rcu_periph_enum tx_clk;
    rcu_periph_enum rx_clk;
#if defined(SOC_SERIES_GD32F4xx) || defined(SOC_SERIES_GD32F5xx)
    uint32_t alt_func_num;
#endif
    rt_base_t tx_pin;
    rt_base_t rx_pin;
#endif
};

struct gd32_baudrate_tbl
{
    rt_uint32_t baudrate;
    rt_uint32_t sjw;
#if defined(SOC_SERIES_GD32H77x_H78X)
    rt_uint32_t prop_seg;
#endif
    rt_uint32_t tseg1;
    rt_uint32_t tseg2;
    rt_uint32_t prescaler;
};

/* gd32 can device */
struct gd32_can_device
{
    char *name;
    rt_uint32_t can_x;
#if defined(SOC_SERIES_GD32H77x_H78X)
    can_operation_modes_enum mode;
    can_mailbox_descriptor_struct tx_message[GD32_CAN_TX_MAILBOX_NUM];
    can_mailbox_descriptor_struct rx_message[GD32_CAN_RX_MAILBOX_NUM];
    rt_uint8_t rx_message_valid[GD32_CAN_RX_MAILBOX_NUM];
    rt_uint16_t tx_abort_mask;
#else
    can_filter_parameter_struct filter_config;
#endif
    struct rt_can_device device;     /* inherit from can device */
};

int rt_hw_can_init(void);

#ifdef __cplusplus
}
#endif

#endif /*__DRV_CAN_H__ */

/************************** end of file ******************/
