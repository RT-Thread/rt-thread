/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-30     shelton      first version
 */

#ifndef __CAN_CONFIG_H__
#define __CAN_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CAN1_TX_IRQHandler         CAN1_TX_IRQHandler
#define CAN1_RX_IRQHandler         CAN1_RX_IRQHandler
#define CAN1_STAT_IRQHandler       CAN1_STAT_IRQHandler
#define CAN1_ERR_IRQHandler        CAN1_ERR_IRQHandler

#if defined(BSP_USING_CAN1)
#define CAN1_CONFIG                                                 \
    {                                                               \
        .name = "can1",                                             \
        .can_x = CAN1,                                              \
        .tx_irqn = CAN1_TX_IRQn,                                    \
        .rx_irqn = CAN1_RX_IRQn,                                    \
        .stat_irqn = CAN1_STAT_IRQn,                                \
        .err_irqn = CAN1_ERR_IRQn,                                  \
    }
#endif /* BSP_USING_CAN1 */

#ifdef __cplusplus
}
#endif

#endif
