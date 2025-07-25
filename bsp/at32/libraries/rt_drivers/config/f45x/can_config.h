/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-18     shelton      first version
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

#define CAN2_TX_IRQHandler         CAN2_TX_IRQHandler
#define CAN2_RX_IRQHandler         CAN2_RX_IRQHandler
#define CAN2_STAT_IRQHandler       CAN2_STAT_IRQHandler
#define CAN2_ERR_IRQHandler        CAN2_ERR_IRQHandler

#define CAN3_TX_IRQHandler         CAN3_TX_IRQHandler
#define CAN3_RX_IRQHandler         CAN3_RX_IRQHandler
#define CAN3_STAT_IRQHandler       CAN3_STAT_IRQHandler
#define CAN3_ERR_IRQHandler        CAN3_ERR_IRQHandler

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

#if defined(BSP_USING_CAN2)
#define CAN2_CONFIG                                                 \
    {                                                               \
        .name = "can2",                                             \
        .can_x = CAN2,                                              \
        .tx_irqn = CAN2_TX_IRQn,                                    \
        .rx_irqn = CAN2_RX_IRQn,                                    \
        .stat_irqn = CAN2_STAT_IRQn,                                \
        .err_irqn = CAN2_ERR_IRQn,                                  \
    }
#endif /* BSP_USING_CAN2 */

#if defined(BSP_USING_CAN3)
#define CAN3_CONFIG                                                 \
    {                                                               \
        .name = "can3",                                             \
        .can_x = CAN3,                                              \
        .tx_irqn = CAN3_TX_IRQn,                                    \
        .rx_irqn = CAN3_RX_IRQn,                                    \
        .stat_irqn = CAN3_STAT_IRQn,                                \
        .err_irqn = CAN3_ERR_IRQn,                                  \
    }
#endif /* BSP_USING_CAN3 */

#ifdef __cplusplus
}
#endif

#endif
