/*
 * Copyright (C) 2022, xiaoxiaolisunny
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author             Notes
 * 2022-05-25     xiaoxiaolisunny    first version
 */

#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif


#if defined(BSP_USING_UART1)
#ifndef UART1_CONFIG
#define UART1_CONFIG                                            \
    {                                                           \
        .name     = "uart1",                                    \
        .Instance = CM_USART1,                                  \
        .clock    = FCG1_PERIPH_USART1,                         \
        .rxerr_irq.irq_config =                                 \
        {                                                       \
            .irq_num    = INT010_IRQn,                          \
            .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
            .int_src    = INT_SRC_USART1_EI,                    \
        },                                                      \
        .rx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = INT011_IRQn,                          \
            .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
            .int_src    = INT_SRC_USART1_RI,                    \
        },                                                      \
        .tx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = INT012_IRQn,                          \
            .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
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
            .irq_num   = INT006_IRQn,                           \
            .irq_prio  = DDL_IRQ_PRIO_DEFAULT,                  \
            .int_src   = INT_SRC_USART1_RTO,                    \
        },                                                      \
    }
#endif /* UART1_RXTO_CONFIG */
#endif /* BSP_UART1_RX_USING_DMA */

#if defined(BSP_UART1_TX_USING_DMA)
#ifndef UART1_TX_CPLT_CONFIG
#define UART1_TX_CPLT_CONFIG                                    \
    {                                                           \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = INT013_IRQn,                          \
            .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
            .int_src    = INT_SRC_USART1_TCI,                   \
        },                                                      \
    }
#endif /* UART1_TX_CPLT_CONFIG */

#ifndef UART1_DMA_TX_CONFIG
#define UART1_DMA_TX_CONFIG                                     \
    {                                                           \
        .Instance       = UART1_TX_DMA_INSTANCE,                \
        .channel        = UART1_TX_DMA_CHANNEL,                 \
        .clock          = UART1_TX_DMA_CLOCK,                   \
        .trigger_select = UART1_TX_DMA_TRIG_SELECT,             \
        .trigger_event  = EVT_SRC_USART1_TI,                    \
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
        .clock    = FCG1_PERIPH_USART2,                         \
        .rxerr_irq.irq_config =                                 \
        {                                                       \
            .irq_num    = INT014_IRQn,                          \
            .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
            .int_src    = INT_SRC_USART2_EI,                    \
        },                                                      \
        .rx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = INT015_IRQn,                          \
            .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
            .int_src    = INT_SRC_USART2_RI,                    \
        },                                                      \
        .tx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = INT016_IRQn,                          \
            .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
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
            .irq_num   = INT007_IRQn,                           \
            .irq_prio  = DDL_IRQ_PRIO_DEFAULT,                  \
            .int_src   = INT_SRC_USART2_RTO,                    \
        },                                                      \
    }
#endif /* UART2_RXTO_CONFIG */
#endif /* BSP_UART2_RX_USING_DMA */

#if defined(BSP_UART2_TX_USING_DMA)
#ifndef UART2_TX_CPLT_CONFIG
#define UART2_TX_CPLT_CONFIG                                    \
    {                                                           \
        .irq_config     =                                       \
        {                                                       \
            .irq_num    = INT017_IRQn,                          \
            .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
            .int_src    = INT_SRC_USART2_TCI,                   \
        },                                                      \
    }
#endif /* UART2_TX_CPLT_CONFIG */

#ifndef UART2_DMA_TX_CONFIG
#define UART2_DMA_TX_CONFIG                                     \
    {                                                           \
        .Instance       = UART2_TX_DMA_INSTANCE,                \
        .channel        = UART2_TX_DMA_CHANNEL,                 \
        .clock          = UART2_TX_DMA_CLOCK,                   \
        .trigger_select = UART2_TX_DMA_TRIG_SELECT,             \
        .trigger_event  = EVT_SRC_USART2_TI,                    \
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
        .clock    = FCG1_PERIPH_USART3,                         \
        .rxerr_irq.irq_config =                                 \
        {                                                       \
            .irq_num    = INT018_IRQn,                          \
            .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
            .int_src    = INT_SRC_USART3_EI,                    \
        },                                                      \
        .rx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = INT019_IRQn,                          \
            .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
            .int_src    = INT_SRC_USART3_RI,                    \
        },                                                      \
        .tx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = INT020_IRQn,                          \
            .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
            .int_src    = INT_SRC_USART3_TI,                    \
        },                                                      \
    }
#endif /* UART3_CONFIG */
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
#ifndef UART4_CONFIG
#define UART4_CONFIG                                            \
    {                                                           \
        .name     = "uart4",                                    \
        .Instance = CM_USART4,                                  \
        .clock    = FCG1_PERIPH_USART4,                         \
        .rxerr_irq.irq_config =                                 \
        {                                                       \
            .irq_num    = INT021_IRQn,                          \
            .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
            .int_src    = INT_SRC_USART4_EI,                    \
        },                                                      \
        .rx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = INT022_IRQn,                          \
            .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
            .int_src    = INT_SRC_USART4_RI,                    \
        },                                                      \
        .tx_irq.irq_config =                                    \
        {                                                       \
            .irq_num    = INT023_IRQn,                          \
            .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
            .int_src    = INT_SRC_USART4_TI,                    \
        },                                                      \
    }
#endif /* UART4_CONFIG */
#endif /* BSP_USING_UART4 */

#ifdef __cplusplus
}
#endif

#endif
