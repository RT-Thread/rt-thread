/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __CAN_CONFIG_H__
#define __CAN_CONFIG_H__

#include <board.h>

#ifdef BSP_USING_CAN1
#ifndef BSP_CAN1_TX_PIN
#define BSP_CAN1_TX_PIN       "PB4"
#endif
#ifndef BSP_CAN1_RX_PIN
#define BSP_CAN1_RX_PIN       "PB5"
#endif
#ifndef BSP_CAN1_TX_AFIO
#define BSP_CAN1_TX_AFIO      "AF4"
#endif
#ifndef BSP_CAN1_RX_AFIO
#define BSP_CAN1_RX_AFIO      "AF9"
#endif

#define CAN1_GPIO_CONFIG                    \
    {                                       \
        .can_clk = RCU_CAN1,                \
        .tx_pin_name = BSP_CAN1_TX_PIN,     \
        .rx_pin_name = BSP_CAN1_RX_PIN,     \
        .tx_alternate = BSP_CAN1_TX_AFIO,   \
        .rx_alternate = BSP_CAN1_RX_AFIO,   \
    }
#endif

#endif /* __CAN_CONFIG_H__ */
