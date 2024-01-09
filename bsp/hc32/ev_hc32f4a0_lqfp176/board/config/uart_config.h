/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>
#include "irq_config.h"

#ifdef __cplusplus
extern "C" {
#endif


#if defined(BSP_USING_UART1)
#ifndef UART1_CONFIG
#define UART1_CONFIG                                            \
    {                                                           \
        .name     = "uart1",                                    \
        .Instance = CM_USART1,                                  \
        .clock    = FCG3_PERIPH_USART1,                         \
        .rxerr_irq.irq_config =                                 \
        {                                                       \
            .irq_num    = BSP_UART1_RXERR_IRQ_NUM,              \
            .irq_prio   = BSP_UART1_RXERR_IRQ_PRIO,             \
            .int_src    = INT_SRC_USART1_EI,                    \
        },                                                      \
        .rx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART1_RX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART1_RX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART1_RI,                    \
        },                                                      \
        .tx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART1_TX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART1_TX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART1_TI,                    \
        },                                                      \
    }
#endif /* UART1_CONFIG */

#if defined(BSP_UART1_RX_USING_DMA)
#ifndef UART1_DMA_RX_CONFIG
#define UART1_DMA_RX_CONFIG                                     \
    {                                                           \
        .Instance       = UART1_RX_DMA_INSTANCE,                \
        .channel        = UART1_RX_DMA_CHANNEL,                 \
        .clock          = UART1_RX_DMA_CLOCK,                   \
        .trigger_select = UART1_RX_DMA_TRIG_SELECT,             \
        .trigger_event  = EVT_SRC_USART1_RI,                    \
        .flag           = UART1_RX_DMA_TRANS_FLAG,              \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = UART1_RX_DMA_IRQn,                    \
            .irq_prio   = UART1_RX_DMA_INT_PRIO,                \
            .int_src    = UART1_RX_DMA_INT_SRC,                 \
        },                                                      \
    }
#endif /* UART1_DMA_RX_CONFIG */

#ifndef UART1_RXTO_CONFIG
#define UART1_RXTO_CONFIG                                       \
    {                                                           \
        .TMR0_Instance = CM_TMR0_1,                             \
        .channel       = TMR0_CH_A,                             \
        .clock         = FCG2_PERIPH_TMR0_1,                    \
        .timeout_bits  = 20UL,                                  \
        .irq_config    =                                        \
        {                                                       \
            .irq_num   = BSP_UART1_RXTO_IRQ_NUM,                \
            .irq_prio  = BSP_UART1_RXTO_IRQ_PRIO,               \
            .int_src   = INT_SRC_USART1_RTO,                    \
        },                                                      \
    }
#endif /* UART1_RXTO_CONFIG */
#endif /* BSP_UART1_RX_USING_DMA */

#if defined(RT_USING_SERIAL_V1) && defined(BSP_UART1_TX_USING_DMA)
#ifndef UART1_TX_CPLT_CONFIG
#define UART1_TX_CPLT_CONFIG                                    \
    {                                                           \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = BSP_UART1_TX_CPLT_IRQ_NUM,            \
            .irq_prio   = BSP_UART1_TX_CPLT_IRQ_PRIO,           \
            .int_src    = INT_SRC_USART1_TCI,                   \
        },                                                      \
    }
#endif
#elif defined(RT_USING_SERIAL_V2)
#ifndef UART1_TX_CPLT_CONFIG
#define UART1_TX_CPLT_CONFIG                                    \
    {                                                           \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = BSP_UART1_TX_CPLT_IRQ_NUM,            \
            .irq_prio   = BSP_UART1_TX_CPLT_IRQ_PRIO,           \
            .int_src    = INT_SRC_USART1_TCI,                   \
        },                                                      \
    }
#endif
#endif /* UART1_TX_CPLT_CONFIG */

#if defined(BSP_UART1_TX_USING_DMA)
#ifndef UART1_DMA_TX_CONFIG
#define UART1_DMA_TX_CONFIG                                     \
    {                                                           \
        .Instance       = UART1_TX_DMA_INSTANCE,                \
        .channel        = UART1_TX_DMA_CHANNEL,                 \
        .clock          = UART1_TX_DMA_CLOCK,                   \
        .trigger_select = UART1_TX_DMA_TRIG_SELECT,             \
        .trigger_event  = EVT_SRC_USART1_TI,                    \
        .flag           = UART1_TX_DMA_TRANS_FLAG,              \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = UART1_TX_DMA_IRQn,                    \
            .irq_prio   = UART1_TX_DMA_INT_PRIO,                \
            .int_src    = UART1_TX_DMA_INT_SRC,                 \
        },                                                      \
    }
#endif /* UART1_DMA_TX_CONFIG */
#endif /* BSP_UART1_TX_USING_DMA */
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#ifndef UART2_CONFIG
#define UART2_CONFIG                                            \
    {                                                           \
        .name     = "uart2",                                    \
        .Instance = CM_USART2,                                  \
        .clock    = FCG3_PERIPH_USART2,                         \
        .rxerr_irq.irq_config =                                 \
        {                                                       \
            .irq_num    = BSP_UART2_RXERR_IRQ_NUM,              \
            .irq_prio   = BSP_UART2_RXERR_IRQ_PRIO,             \
            .int_src    = INT_SRC_USART2_EI,                    \
        },                                                      \
        .rx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART2_RX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART2_RX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART2_RI,                    \
        },                                                      \
        .tx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART2_TX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART2_TX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART2_TI,                    \
        },                                                      \
    }
#endif /* UART2_CONFIG */

#if defined(BSP_UART2_RX_USING_DMA)
#ifndef UART2_DMA_RX_CONFIG
#define UART2_DMA_RX_CONFIG                                     \
    {                                                           \
        .Instance       = UART2_RX_DMA_INSTANCE,                \
        .channel        = UART2_RX_DMA_CHANNEL,                 \
        .clock          = UART2_RX_DMA_CLOCK,                   \
        .trigger_select = UART2_RX_DMA_TRIG_SELECT,             \
        .trigger_event  = EVT_SRC_USART2_RI,                    \
        .flag           = UART2_RX_DMA_TRANS_FLAG,              \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = UART2_RX_DMA_IRQn,                    \
            .irq_prio   = UART2_RX_DMA_INT_PRIO,                \
            .int_src    = UART2_RX_DMA_INT_SRC,                 \
        },                                                      \
    }
#endif /* UART2_DMA_RX_CONFIG */

#ifndef UART2_RXTO_CONFIG
#define UART2_RXTO_CONFIG                                       \
    {                                                           \
        .TMR0_Instance = CM_TMR0_1,                             \
        .channel       = TMR0_CH_B,                             \
        .clock         = FCG2_PERIPH_TMR0_1,                    \
        .timeout_bits  = 20UL,                                  \
        .irq_config    =                                        \
        {                                                       \
            .irq_num   = BSP_UART2_RXTO_IRQ_NUM,                \
            .irq_prio  = BSP_UART2_RXTO_IRQ_PRIO,               \
            .int_src   = INT_SRC_USART2_RTO,                    \
        },                                                      \
    }
#endif /* UART2_RXTO_CONFIG */
#endif /* BSP_UART2_RX_USING_DMA */

#if defined(RT_USING_SERIAL_V1) && defined(BSP_UART2_TX_USING_DMA)
#ifndef UART2_TX_CPLT_CONFIG
#define UART2_TX_CPLT_CONFIG                                    \
    {                                                           \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = BSP_UART2_TX_CPLT_IRQ_NUM,            \
            .irq_prio   = BSP_UART2_TX_CPLT_IRQ_PRIO,           \
            .int_src    = INT_SRC_USART2_TCI,                   \
        },                                                      \
    }
#endif
#elif defined(RT_USING_SERIAL_V2)
#ifndef UART2_TX_CPLT_CONFIG
#define UART2_TX_CPLT_CONFIG                                    \
    {                                                           \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = BSP_UART2_TX_CPLT_IRQ_NUM,            \
            .irq_prio   = BSP_UART2_TX_CPLT_IRQ_PRIO,           \
            .int_src    = INT_SRC_USART2_TCI,                   \
        },                                                      \
    }
#endif
#endif /* UART2_TX_CPLT_CONFIG */

#if defined(BSP_UART2_TX_USING_DMA)
#ifndef UART2_DMA_TX_CONFIG
#define UART2_DMA_TX_CONFIG                                     \
    {                                                           \
        .Instance       = UART2_TX_DMA_INSTANCE,                \
        .channel        = UART2_TX_DMA_CHANNEL,                 \
        .clock          = UART2_TX_DMA_CLOCK,                   \
        .trigger_select = UART2_TX_DMA_TRIG_SELECT,             \
        .trigger_event  = EVT_SRC_USART2_TI,                    \
        .flag           = UART2_TX_DMA_TRANS_FLAG,              \
        .irq_config     =                                       \
        {                                                       \
            .irq_num     = UART2_TX_DMA_IRQn,                   \
            .irq_prio   = UART2_TX_DMA_INT_PRIO,                \
            .int_src    = UART2_TX_DMA_INT_SRC,                 \
        },                                                      \
    }
#endif /* UART2_DMA_TX_CONFIG */
#endif /* BSP_UART2_TX_USING_DMA */
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
#ifndef UART3_CONFIG
#define UART3_CONFIG                                            \
    {                                                           \
        .name     = "uart3",                                    \
        .Instance = CM_USART3,                                  \
        .clock    = FCG3_PERIPH_USART3,                         \
        .rxerr_irq.irq_config =                                 \
        {                                                       \
            .irq_num    = BSP_UART3_RXERR_IRQ_NUM,              \
            .irq_prio   = BSP_UART3_RXERR_IRQ_PRIO,             \
            .int_src    = INT_SRC_USART3_EI,                    \
        },                                                      \
        .rx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART3_RX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART3_RX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART3_RI,                    \
        },                                                      \
        .tx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART3_TX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART3_TX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART3_TI,                    \
        },                                                      \
    }
#endif /* UART3_CONFIG */

#if defined(RT_USING_SERIAL_V2)
#ifndef UART3_TX_CPLT_CONFIG
#define UART3_TX_CPLT_CONFIG                                    \
    {                                                           \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = BSP_UART3_TX_CPLT_IRQ_NUM,            \
            .irq_prio   = BSP_UART3_TX_CPLT_IRQ_PRIO,           \
            .int_src    = INT_SRC_USART3_TCI,                   \
        },                                                      \
    }
#endif
#endif /* UART3_TX_CPLT_CONFIG */
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
#ifndef UART4_CONFIG
#define UART4_CONFIG                                            \
    {                                                           \
        .name     = "uart4",                                    \
        .Instance = CM_USART4,                                  \
        .clock    = FCG3_PERIPH_USART4,                         \
        .rxerr_irq.irq_config =                                 \
        {                                                       \
            .irq_num    = BSP_UART4_RXERR_IRQ_NUM,              \
            .irq_prio   = BSP_UART4_RXERR_IRQ_PRIO,             \
            .int_src    = INT_SRC_USART4_EI,                    \
        },                                                      \
        .rx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART4_RX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART4_RX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART4_RI,                    \
        },                                                      \
        .tx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART4_TX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART4_TX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART4_TI,                    \
        },                                                      \
    }
#endif /* UART4_CONFIG */

#if defined(RT_USING_SERIAL_V2)
#ifndef UART4_TX_CPLT_CONFIG
#define UART4_TX_CPLT_CONFIG                                    \
    {                                                           \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = BSP_UART4_TX_CPLT_IRQ_NUM,            \
            .irq_prio   = BSP_UART4_TX_CPLT_IRQ_PRIO,           \
            .int_src    = INT_SRC_USART4_TCI,                   \
        },                                                      \
    }
#endif
#endif /* UART4_TX_CPLT_CONFIG */
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
#ifndef UART5_CONFIG
#define UART5_CONFIG                                            \
    {                                                           \
        .name     = "uart5",                                    \
        .Instance = CM_USART5,                                  \
        .clock    = FCG3_PERIPH_USART5,                         \
        .rxerr_irq.irq_config =                                 \
        {                                                       \
            .irq_num    = BSP_UART5_RXERR_IRQ_NUM,              \
            .irq_prio   = BSP_UART5_RXERR_IRQ_PRIO,             \
            .int_src    = INT_SRC_USART5_EI,                    \
        },                                                      \
        .rx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART5_RX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART5_RX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART5_RI,                    \
        },                                                      \
        .tx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART5_TX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART5_TX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART5_TI,                    \
        },                                                      \
    }
#endif /* UART5_CONFIG */

#if defined(RT_USING_SERIAL_V2)
#ifndef UART5_TX_CPLT_CONFIG
#define UART5_TX_CPLT_CONFIG                                    \
    {                                                           \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = BSP_UART5_TX_CPLT_IRQ_NUM,            \
            .irq_prio   = BSP_UART5_TX_CPLT_IRQ_PRIO,           \
            .int_src    = INT_SRC_USART5_TCI,                   \
        },                                                      \
    }
#endif
#endif /* UART5_TX_CPLT_CONFIG */
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
#ifndef UART6_CONFIG
#define UART6_CONFIG                                            \
    {                                                           \
        .name     = "uart6",                                    \
        .Instance = CM_USART6,                                  \
        .clock    = FCG3_PERIPH_USART6,                         \
        .rxerr_irq.irq_config =                                 \
        {                                                       \
            .irq_num    = BSP_UART6_RXERR_IRQ_NUM,              \
            .irq_prio   = BSP_UART6_RXERR_IRQ_PRIO,             \
            .int_src    = INT_SRC_USART6_EI,                    \
        },                                                      \
        .rx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART6_RX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART6_RX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART6_RI,                    \
        },                                                      \
        .tx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART6_TX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART6_TX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART6_TI,                    \
        },                                                      \
    }
#endif /* UART6_CONFIG */

#if defined(BSP_UART6_RX_USING_DMA)
#ifndef UART6_DMA_RX_CONFIG
#define UART6_DMA_RX_CONFIG                                     \
    {                                                           \
        .Instance       = UART6_RX_DMA_INSTANCE,                \
        .channel        = UART6_RX_DMA_CHANNEL,                 \
        .clock          = UART6_RX_DMA_CLOCK,                   \
        .trigger_select = UART6_RX_DMA_TRIG_SELECT,             \
        .trigger_event  = EVT_SRC_USART6_RI,                    \
        .flag           = UART6_RX_DMA_TRANS_FLAG,              \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = UART6_RX_DMA_IRQn,                    \
            .irq_prio   = UART6_RX_DMA_INT_PRIO,                \
            .int_src    = UART6_RX_DMA_INT_SRC,                 \
        },                                                      \
    }
#endif /* UART6_DMA_RX_CONFIG */

#ifndef UART6_RXTO_CONFIG
#define UART6_RXTO_CONFIG                                       \
    {                                                           \
        .TMR0_Instance = CM_TMR0_2,                             \
        .channel       = TMR0_CH_A,                             \
        .clock         = FCG2_PERIPH_TMR0_2,                    \
        .timeout_bits  = 20UL,                                  \
        .irq_config    =                                        \
        {                                                       \
            .irq_num   = BSP_UART6_RXTO_IRQ_NUM,                \
            .irq_prio  = BSP_UART6_RXTO_IRQ_PRIO,               \
            .int_src   = INT_SRC_USART6_RTO,                    \
        },                                                      \
    }
#endif /* UART6_RXTO_CONFIG */
#endif /* BSP_UART6_RX_USING_DMA */

#if defined(RT_USING_SERIAL_V1) && defined(BSP_UART6_TX_USING_DMA)
#ifndef UART6_TX_CPLT_CONFIG
#define UART6_TX_CPLT_CONFIG                                    \
    {                                                           \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = BSP_UART6_TX_CPLT_IRQ_NUM,            \
            .irq_prio   = BSP_UART6_TX_CPLT_IRQ_PRIO,           \
            .int_src    = INT_SRC_USART6_TCI,                   \
        },                                                      \
    }
#endif
#elif defined(RT_USING_SERIAL_V2)
#ifndef UART6_TX_CPLT_CONFIG
#define UART6_TX_CPLT_CONFIG                                    \
    {                                                           \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = BSP_UART6_TX_CPLT_IRQ_NUM,            \
            .irq_prio   = BSP_UART6_TX_CPLT_IRQ_PRIO,           \
            .int_src    = INT_SRC_USART6_TCI,                   \
        },                                                      \
    }
#endif
#endif /* UART6_TX_CPLT_CONFIG */

#if defined(BSP_UART6_TX_USING_DMA)
#ifndef UART6_DMA_TX_CONFIG
#define UART6_DMA_TX_CONFIG                                     \
    {                                                           \
        .Instance       = UART6_TX_DMA_INSTANCE,                \
        .channel        = UART6_TX_DMA_CHANNEL,                 \
        .clock          = UART6_TX_DMA_CLOCK,                   \
        .trigger_select = UART6_TX_DMA_TRIG_SELECT,             \
        .trigger_event  = EVT_SRC_USART6_TI,                    \
        .flag           = UART6_TX_DMA_TRANS_FLAG,              \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = UART6_TX_DMA_IRQn,                    \
            .irq_prio   = UART6_TX_DMA_INT_PRIO,                \
            .int_src    = UART6_TX_DMA_INT_SRC,                 \
        },                                                      \
    }
#endif /* UART6_DMA_TX_CONFIG */
#endif /* BSP_UART6_TX_USING_DMA */
#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
#ifndef UART7_CONFIG
#define UART7_CONFIG                                            \
    {                                                           \
        .name     = "uart7",                                    \
        .Instance = CM_USART7,                                  \
        .clock    = FCG3_PERIPH_USART7,                         \
        .rxerr_irq.irq_config =                                 \
        {                                                       \
            .irq_num    = BSP_UART7_RXERR_IRQ_NUM,              \
            .irq_prio   = BSP_UART7_RXERR_IRQ_PRIO,             \
            .int_src    = INT_SRC_USART7_EI,                    \
        },                                                      \
        .rx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART7_RX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART7_RX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART7_RI,                    \
        },                                                      \
        .tx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART7_TX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART7_TX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART7_TI,                    \
        },                                                      \
    }
#endif /* UART7_CONFIG */

#if defined(BSP_UART7_RX_USING_DMA)
#ifndef UART7_DMA_RX_CONFIG
#define UART7_DMA_RX_CONFIG                                     \
    {                                                           \
        .Instance       = UART7_RX_DMA_INSTANCE,                \
        .channel        = UART7_RX_DMA_CHANNEL,                 \
        .clock          = UART7_RX_DMA_CLOCK,                   \
        .trigger_select = UART7_RX_DMA_TRIG_SELECT,             \
        .trigger_event  = EVT_SRC_USART7_RI,                    \
        .flag           = UART7_RX_DMA_TRANS_FLAG,              \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = UART7_RX_DMA_IRQn,                    \
            .irq_prio   = UART7_RX_DMA_INT_PRIO,                \
            .int_src    = UART7_RX_DMA_INT_SRC,                 \
        },                                                      \
    }
#endif /* UART7_DMA_RX_CONFIG */

#ifndef UART7_RXTO_CONFIG
#define UART7_RXTO_CONFIG                                       \
    {                                                           \
        .TMR0_Instance = CM_TMR0_2,                             \
        .channel       = TMR0_CH_B,                             \
        .clock         = FCG2_PERIPH_TMR0_2,                    \
        .timeout_bits  = 20UL,                                  \
        .irq_config    =                                        \
        {                                                       \
            .irq_num   = BSP_UART7_RXTO_IRQ_NUM,                \
            .irq_prio  = BSP_UART7_RXTO_IRQ_PRIO,               \
            .int_src   = INT_SRC_USART7_RTO,                    \
        },                                                      \
    }
#endif /* UART7_RXTO_CONFIG */
#endif /* BSP_UART7_RX_USING_DMA */

#if defined(RT_USING_SERIAL_V1) && defined(BSP_UART7_TX_USING_DMA)
#ifndef UART7_TX_CPLT_CONFIG
#define UART7_TX_CPLT_CONFIG                                    \
    {                                                           \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = BSP_UART7_TX_CPLT_IRQ_NUM,            \
            .irq_prio   = BSP_UART7_TX_CPLT_IRQ_PRIO,           \
            .int_src    = INT_SRC_USART7_TCI,                   \
        },                                                      \
    }
#endif
#elif defined(RT_USING_SERIAL_V2)
#ifndef UART7_TX_CPLT_CONFIG
#define UART7_TX_CPLT_CONFIG                                    \
    {                                                           \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = BSP_UART7_TX_CPLT_IRQ_NUM,            \
            .irq_prio   = BSP_UART7_TX_CPLT_IRQ_PRIO,           \
            .int_src    = INT_SRC_USART7_TCI,                   \
        },                                                      \
    }
#endif
#endif /* UART7_TX_CPLT_CONFIG */

#if defined(BSP_UART7_TX_USING_DMA)
#ifndef UART7_DMA_TX_CONFIG
#define UART7_DMA_TX_CONFIG                                     \
    {                                                           \
        .Instance       = UART7_TX_DMA_INSTANCE,                \
        .channel        = UART7_TX_DMA_CHANNEL,                 \
        .clock          = UART7_TX_DMA_CLOCK,                   \
        .trigger_select = UART7_TX_DMA_TRIG_SELECT,             \
        .trigger_event  = EVT_SRC_USART7_TI,                    \
        .flag           = UART1_TX_DMA_TRANS_FLAG,              \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = UART7_TX_DMA_IRQn,                    \
            .irq_prio   = UART7_TX_DMA_INT_PRIO,                \
            .int_src    = UART7_TX_DMA_INT_SRC,                 \
        },                                                      \
    }
#endif /* UART7_DMA_TX_CONFIG */
#endif /* BSP_UART7_TX_USING_DMA */
#endif /* BSP_USING_UART7 */

#if defined(BSP_USING_UART8)
#ifndef UART8_CONFIG
#define UART8_CONFIG                                            \
    {                                                           \
        .name     = "uart8",                                    \
        .Instance = CM_USART8,                                  \
        .clock    = FCG3_PERIPH_USART8,                         \
        .rxerr_irq.irq_config =                                 \
        {                                                       \
            .irq_num    = BSP_UART8_RXERR_IRQ_NUM,              \
            .irq_prio   = BSP_UART8_RXERR_IRQ_PRIO,             \
            .int_src    = INT_SRC_USART8_EI,                    \
        },                                                      \
        .rx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART8_RX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART8_RX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART8_RI,                    \
        },                                                      \
        .tx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART8_TX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART8_TX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART8_TI,                    \
        },                                                      \
    }
#endif /* UART8_CONFIG */

#if defined(RT_USING_SERIAL_V2)
#ifndef UART8_TX_CPLT_CONFIG
#define UART8_TX_CPLT_CONFIG                                    \
    {                                                           \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = BSP_UART8_TX_CPLT_IRQ_NUM,            \
            .irq_prio   = BSP_UART8_TX_CPLT_IRQ_PRIO,           \
            .int_src    = INT_SRC_USART8_TCI,                   \
        },                                                      \
    }
#endif
#endif /* UART8_TX_CPLT_CONFIG */
#endif /* BSP_USING_UART8 */

#if defined(BSP_USING_UART9)
#ifndef UART9_CONFIG
#define UART9_CONFIG                                            \
    {                                                           \
        .name     = "uart9",                                    \
        .Instance = CM_USART9,                                  \
        .clock    = FCG3_PERIPH_USART9,                         \
        .rxerr_irq.irq_config =                                 \
        {                                                       \
            .irq_num    = BSP_UART9_RXERR_IRQ_NUM,              \
            .irq_prio   = BSP_UART9_RXERR_IRQ_PRIO,             \
            .int_src    = INT_SRC_USART9_EI,                    \
        },                                                      \
        .rx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART9_RX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART9_RX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART9_RI,                    \
        },                                                      \
        .tx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART9_TX_IRQ_NUM,                 \
            .irq_prio   = BSP_UART9_TX_IRQ_PRIO,                \
            .int_src    = INT_SRC_USART9_TI,                    \
        },                                                      \
    }
#endif /* UART9_CONFIG */

#if defined(RT_USING_SERIAL_V2)
#ifndef UART9_TX_CPLT_CONFIG
#define UART9_TX_CPLT_CONFIG                                    \
    {                                                           \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = BSP_UART9_TX_CPLT_IRQ_NUM,            \
            .irq_prio   = BSP_UART9_TX_CPLT_IRQ_PRIO,           \
            .int_src    = INT_SRC_USART9_TCI,                   \
        },                                                      \
    }
#endif
#endif /* UART9_TX_CPLT_CONFIG */
#endif /* BSP_USING_UART9 */

#if defined(BSP_USING_UART10)
#ifndef UART10_CONFIG
#define UART10_CONFIG                                           \
    {                                                           \
        .name     = "uart10",                                   \
        .Instance = CM_USART10,                                 \
        .clock    = FCG3_PERIPH_USART10,                        \
        .rxerr_irq.irq_config =                                 \
        {                                                       \
            .irq_num    = BSP_UART10_RXERR_IRQ_NUM,             \
            .irq_prio   = BSP_UART10_RXERR_IRQ_PRIO,            \
            .int_src    = INT_SRC_USART10_EI,                   \
        },                                                      \
        .rx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART10_RX_IRQ_NUM,                \
            .irq_prio   = BSP_UART10_RX_IRQ_PRIO,               \
            .int_src    = INT_SRC_USART10_RI,                   \
        },                                                      \
        .tx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = BSP_UART10_TX_IRQ_NUM,                \
            .irq_prio   = BSP_UART10_TX_IRQ_PRIO,               \
            .int_src    = INT_SRC_USART10_TI,                   \
        },                                                      \
    }
#endif /* UART10_CONFIG */

#if defined(RT_USING_SERIAL_V2)
#ifndef UART10_TX_CPLT_CONFIG
#define UART10_TX_CPLT_CONFIG                                   \
    {                                                           \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = BSP_UART10_TX_CPLT_IRQ_NUM,           \
            .irq_prio   = BSP_UART10_TX_CPLT_IRQ_PRIO,          \
            .int_src    = INT_SRC_USART10_TCI,                  \
        },                                                      \
    }
#endif
#endif /* UART10_TX_CPLT_CONFIG */
#endif /* BSP_USING_UART10 */

#ifdef __cplusplus
}
#endif

#endif
