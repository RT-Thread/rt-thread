/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
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
        .irq_num  = BSP_UART1_IRQ_NUM,                          \
        .rxerr_int_src = INT_SRC_USART1_EI,                     \
        .rx_int_src    = INT_SRC_USART1_RI,                     \
        .tx_int_src    = INT_SRC_USART1_TI,                     \
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
        .irq_num  = BSP_UART2_IRQ_NUM,                          \
        .rxerr_int_src = INT_SRC_USART2_EI,                     \
        .rx_int_src    = INT_SRC_USART2_RI,                     \
        .tx_int_src    = INT_SRC_USART2_TI,                     \
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
            .irq_num    = UART2_TX_DMA_IRQn,                    \
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
        .irq_num  = BSP_UART3_IRQ_NUM,                          \
        .rxerr_int_src = INT_SRC_USART3_EI,                     \
        .rx_int_src    = INT_SRC_USART3_RI,                     \
        .tx_int_src    = INT_SRC_USART3_TI,                     \
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
        .irq_num  = BSP_UART4_IRQ_NUM,                          \
        .rxerr_int_src = INT_SRC_USART4_EI,                     \
        .rx_int_src    = INT_SRC_USART4_RI,                     \
        .tx_int_src    = INT_SRC_USART4_TI,                     \
    }
#endif /* UART4_CONFIG */

#if defined(BSP_UART4_RX_USING_DMA)
#ifndef UART4_DMA_RX_CONFIG
#define UART4_DMA_RX_CONFIG                                     \
    {                                                           \
        .Instance       = UART4_RX_DMA_INSTANCE,                \
        .channel        = UART4_RX_DMA_CHANNEL,                 \
        .clock          = UART4_RX_DMA_CLOCK,                   \
        .trigger_select = UART4_RX_DMA_TRIG_SELECT,             \
        .trigger_event  = EVT_SRC_USART4_RI,                    \
        .flag           = UART4_RX_DMA_TRANS_FLAG,              \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = UART4_RX_DMA_IRQn,                    \
            .irq_prio   = UART4_RX_DMA_INT_PRIO,                \
            .int_src    = UART4_RX_DMA_INT_SRC,                 \
        },                                                      \
    }
#endif /* UART4_DMA_RX_CONFIG */

#ifndef UART4_RXTO_CONFIG
#define UART4_RXTO_CONFIG                                       \
    {                                                           \
        .TMR0_Instance = CM_TMR0_2,                             \
        .channel       = TMR0_CH_A,                             \
        .clock         = FCG2_PERIPH_TMR0_2,                    \
        .timeout_bits  = 20UL,                                  \
    }
#endif /* UART4_RXTO_CONFIG */
#endif /* BSP_UART4_RX_USING_DMA */

#if defined(RT_USING_SERIAL_V1) && defined(BSP_UART4_TX_USING_DMA)
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
#elif defined(RT_USING_SERIAL_V2)
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

#if defined(BSP_UART4_TX_USING_DMA)
#ifndef UART4_DMA_TX_CONFIG
#define UART4_DMA_TX_CONFIG                                     \
    {                                                           \
        .Instance       = UART4_TX_DMA_INSTANCE,                \
        .channel        = UART4_TX_DMA_CHANNEL,                 \
        .clock          = UART4_TX_DMA_CLOCK,                   \
        .trigger_select = UART4_TX_DMA_TRIG_SELECT,             \
        .trigger_event  = EVT_SRC_USART4_TI,                    \
        .flag           = UART4_TX_DMA_TRANS_FLAG,              \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = UART4_TX_DMA_IRQn,                    \
            .irq_prio   = UART4_TX_DMA_INT_PRIO,                \
            .int_src    = UART4_TX_DMA_INT_SRC,                 \
        },                                                      \
    }
#endif /* UART4_DMA_TX_CONFIG */
#endif /* BSP_UART4_TX_USING_DMA */
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
#ifndef UART5_CONFIG
#define UART5_CONFIG                                            \
    {                                                           \
        .name     = "uart5",                                    \
        .Instance = CM_USART5,                                  \
        .clock    = FCG3_PERIPH_USART5,                         \
        .irq_num  = BSP_UART5_IRQ_NUM,                          \
        .rxerr_int_src = INT_SRC_USART5_EI,                     \
        .rx_int_src    = INT_SRC_USART5_RI,                     \
        .tx_int_src    = INT_SRC_USART5_TI,                     \
    }
#endif /* UART5_CONFIG */

#if defined(BSP_UART5_RX_USING_DMA)
#ifndef UART5_DMA_RX_CONFIG
#define UART5_DMA_RX_CONFIG                                     \
    {                                                           \
        .Instance       = UART5_RX_DMA_INSTANCE,                \
        .channel        = UART5_RX_DMA_CHANNEL,                 \
        .clock          = UART5_RX_DMA_CLOCK,                   \
        .trigger_select = UART5_RX_DMA_TRIG_SELECT,             \
        .trigger_event  = EVT_SRC_USART5_RI,                    \
        .flag           = UART5_RX_DMA_TRANS_FLAG,              \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = UART5_RX_DMA_IRQn,                    \
            .irq_prio   = UART5_RX_DMA_INT_PRIO,                \
            .int_src    = UART5_RX_DMA_INT_SRC,                 \
        },                                                      \
    }
#endif /* UART5_DMA_RX_CONFIG */

#ifndef UART5_RXTO_CONFIG
#define UART5_RXTO_CONFIG                                       \
    {                                                           \
        .TMR0_Instance = CM_TMR0_2,                             \
        .channel       = TMR0_CH_B,                             \
        .clock         = FCG2_PERIPH_TMR0_2,                    \
        .timeout_bits  = 20UL,                                  \
    }
#endif /* UART5_RXTO_CONFIG */
#endif /* BSP_UART5_RX_USING_DMA */

#if defined(RT_USING_SERIAL_V1) && defined(BSP_UART5_TX_USING_DMA)
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
#elif defined(RT_USING_SERIAL_V2)
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

#if defined(BSP_UART5_TX_USING_DMA)
#ifndef UART5_DMA_TX_CONFIG
#define UART5_DMA_TX_CONFIG                                     \
    {                                                           \
        .Instance       = UART5_TX_DMA_INSTANCE,                \
        .channel        = UART5_TX_DMA_CHANNEL,                 \
        .clock          = UART5_TX_DMA_CLOCK,                   \
        .trigger_select = UART5_TX_DMA_TRIG_SELECT,             \
        .trigger_event  = EVT_SRC_USART5_TI,                    \
        .flag           = UART5_TX_DMA_TRANS_FLAG,              \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = UART5_TX_DMA_IRQn,                    \
            .irq_prio   = UART5_TX_DMA_INT_PRIO,                \
            .int_src    = UART5_TX_DMA_INT_SRC,                 \
        },                                                      \
    }
#endif /* UART5_DMA_TX_CONFIG */
#endif /* BSP_UART5_TX_USING_DMA */
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
#ifndef UART6_CONFIG
#define UART6_CONFIG                                            \
    {                                                           \
        .name     = "uart6",                                    \
        .Instance = CM_USART6,                                  \
        .clock    = FCG3_PERIPH_USART6,                         \
        .irq_num  = BSP_UART6_IRQ_NUM,                          \
        .rxerr_int_src = INT_SRC_USART6_EI,                     \
        .rx_int_src    = INT_SRC_USART6_RI,                     \
        .tx_int_src    = INT_SRC_USART6_TI,                     \
    }
#endif /* UART6_CONFIG */

#if defined(RT_USING_SERIAL_V2)
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
#endif /* BSP_USING_UART6 */

#ifdef __cplusplus
}
#endif

#endif
