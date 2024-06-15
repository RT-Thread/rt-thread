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

#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include <rtthread.h>
#include "irq_config.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifdef BSP_USING_SPI1
#ifndef SPI1_BUS_CONFIG
#define SPI1_BUS_CONFIG                                     \
    {                                                       \
        .Instance = CM_SPI1,                                \
        .bus_name = "spi1",                                 \
        .clock    = FCG1_PERIPH_SPI1,                       \
        .timeout  = 5000UL,                                 \
        .err_irq.irq_config =                               \
        {                                                   \
            .irq_num    = BSP_SPI1_ERR_IRQ_NUM,             \
            .irq_prio   = BSP_SPI1_ERR_IRQ_PRIO,            \
            .int_src    = INT_SRC_SPI1_SPEI,                \
        },                                                  \
    }
#endif /* SPI1_BUS_CONFIG */
#endif /* BSP_USING_SPI1 */

#ifdef BSP_SPI1_TX_USING_DMA
#ifndef SPI1_TX_DMA_CONFIG
#define SPI1_TX_DMA_CONFIG                                  \
    {                                                       \
        .Instance       = SPI1_TX_DMA_INSTANCE,             \
        .channel        = SPI1_TX_DMA_CHANNEL,              \
        .clock          = SPI1_TX_DMA_CLOCK,                \
        .trigger_select = SPI1_TX_DMA_TRIG_SELECT,          \
        .trigger_event  = EVT_SRC_SPI1_SPTI,                \
        .flag           = SPI1_TX_DMA_TRANS_FLAG,           \
        .irq_config     =                                   \
        {                                                   \
            .irq_num    = SPI1_TX_DMA_IRQn,                 \
            .irq_prio   = SPI1_TX_DMA_INT_PRIO,             \
            .int_src    = SPI1_TX_DMA_INT_SRC,              \
        }                                                   \
    }
#endif /* SPI1_TX_DMA_CONFIG */
#endif /* BSP_SPI1_TX_USING_DMA */

#ifdef BSP_SPI1_RX_USING_DMA
#ifndef SPI1_RX_DMA_CONFIG
#define SPI1_RX_DMA_CONFIG                                  \
    {                                                       \
        .Instance       = SPI1_RX_DMA_INSTANCE,             \
        .channel        = SPI1_RX_DMA_CHANNEL,              \
        .clock          = SPI1_RX_DMA_CLOCK,                \
        .trigger_select = SPI1_RX_DMA_TRIG_SELECT,          \
        .trigger_event  = EVT_SRC_SPI1_SPRI,                \
        .flag           = SPI1_RX_DMA_TRANS_FLAG,           \
        .irq_config     =                                   \
        {                                                   \
            .irq_num    = SPI1_RX_DMA_IRQn,                 \
            .irq_prio   = SPI1_RX_DMA_INT_PRIO,             \
            .int_src    = SPI1_RX_DMA_INT_SRC,              \
        }                                                   \
    }
#endif /* SPI1_RX_DMA_CONFIG */
#endif /* BSP_SPI1_RX_USING_DMA */

#ifdef BSP_USING_SPI2
#ifndef SPI2_BUS_CONFIG
#define SPI2_BUS_CONFIG                                     \
    {                                                       \
        .Instance = CM_SPI2,                                \
        .bus_name = "spi2",                                 \
        .clock    = FCG1_PERIPH_SPI2,                       \
        .timeout  = 5000UL,                                 \
        .err_irq.irq_config =                               \
        {                                                   \
            .irq_num    = BSP_SPI2_ERR_IRQ_NUM,             \
            .irq_prio   = BSP_SPI2_ERR_IRQ_PRIO,            \
            .int_src    = INT_SRC_SPI2_SPEI,                \
        },                                                  \
    }
#endif /* SPI2_BUS_CONFIG */
#endif /* BSP_USING_SPI2 */

#ifdef BSP_SPI2_TX_USING_DMA
#ifndef SPI2_TX_DMA_CONFIG
#define SPI2_TX_DMA_CONFIG                                  \
    {                                                       \
        .Instance       = SPI2_TX_DMA_INSTANCE,             \
        .channel        = SPI2_TX_DMA_CHANNEL,              \
        .clock          = SPI2_TX_DMA_CLOCK,                \
        .trigger_select = SPI2_TX_DMA_TRIG_SELECT,          \
        .trigger_event  = EVT_SRC_SPI2_SPTI,                \
        .flag           = SPI2_TX_DMA_TRANS_FLAG,           \
        .irq_config     =                                   \
        {                                                   \
            .irq_num    = SPI2_TX_DMA_IRQn,                 \
            .irq_prio   = SPI2_TX_DMA_INT_PRIO,             \
            .int_src    = SPI2_TX_DMA_INT_SRC,              \
        }                                                   \
    }
#endif /* SPI2_TX_DMA_CONFIG */
#endif /* BSP_SPI2_TX_USING_DMA */

#ifdef BSP_SPI2_RX_USING_DMA
#ifndef SPI2_RX_DMA_CONFIG
#define SPI2_RX_DMA_CONFIG                                  \
    {                                                       \
        .Instance       = SPI2_RX_DMA_INSTANCE,             \
        .channel        = SPI2_RX_DMA_CHANNEL,              \
        .clock          = SPI2_RX_DMA_CLOCK,                \
        .trigger_select = SPI2_RX_DMA_TRIG_SELECT,          \
        .trigger_event  = EVT_SRC_SPI2_SPRI,                \
        .flag           = SPI2_RX_DMA_TRANS_FLAG,           \
        .irq_config     =                                   \
        {                                                   \
            .irq_num    = SPI2_RX_DMA_IRQn,                 \
            .irq_prio   = SPI2_RX_DMA_INT_PRIO,             \
            .int_src    = SPI2_RX_DMA_INT_SRC,              \
        }                                                   \
    }
#endif /* SPI2_RX_DMA_CONFIG */
#endif /* BSP_SPI2_RX_USING_DMA */

#ifdef BSP_USING_SPI3
#ifndef SPI3_BUS_CONFIG
#define SPI3_BUS_CONFIG                                     \
    {                                                       \
        .Instance = CM_SPI3,                                \
        .bus_name = "spi3",                                 \
        .clock    = FCG1_PERIPH_SPI3,                       \
        .timeout  = 5000UL,                                 \
        .err_irq.irq_config =                               \
        {                                                   \
            .irq_num    = BSP_SPI3_ERR_IRQ_NUM,             \
            .irq_prio   = BSP_SPI3_ERR_IRQ_PRIO,            \
            .int_src    = INT_SRC_SPI3_SPEI,                \
        },                                                  \
    }
#endif /* SPI3_BUS_CONFIG */
#endif /* BSP_USING_SPI3 */


#ifdef BSP_SPI3_TX_USING_DMA
#ifndef SPI3_TX_DMA_CONFIG
#define SPI3_TX_DMA_CONFIG                                  \
    {                                                       \
        .Instance       = SPI3_TX_DMA_INSTANCE,             \
        .channel        = SPI3_TX_DMA_CHANNEL,              \
        .clock          = SPI3_TX_DMA_CLOCK,                \
        .trigger_select = SPI3_TX_DMA_TRIG_SELECT,          \
        .trigger_event  = EVT_SRC_SPI3_SPTI,                \
        .flag           = SPI3_TX_DMA_TRANS_FLAG,           \
        .irq_config     =                                   \
        {                                                   \
            .irq_num    = SPI3_TX_DMA_IRQn,                 \
            .irq_prio   = SPI3_TX_DMA_INT_PRIO,             \
            .int_src    = SPI3_TX_DMA_INT_SRC,              \
        }                                                   \
    }
#endif /* SPI3_TX_DMA_CONFIG */
#endif /* BSP_SPI3_TX_USING_DMA */

#ifdef BSP_SPI3_RX_USING_DMA
#ifndef SPI3_RX_DMA_CONFIG
#define SPI3_RX_DMA_CONFIG                                  \
    {                                                       \
        .Instance       = SPI3_RX_DMA_INSTANCE,             \
        .channel        = SPI3_RX_DMA_CHANNEL,              \
        .clock          = SPI3_RX_DMA_CLOCK,                \
        .trigger_select = SPI3_RX_DMA_TRIG_SELECT,          \
        .trigger_event  = EVT_SRC_SPI3_SPRI,                \
        .flag           = SPI3_RX_DMA_TRANS_FLAG,           \
        .irq_config     =                                   \
        {                                                   \
            .irq_num    = SPI3_RX_DMA_IRQn,                 \
            .irq_prio   = SPI3_RX_DMA_INT_PRIO,             \
            .int_src    = SPI3_RX_DMA_INT_SRC,              \
        }                                                   \
    }
#endif /* SPI3_RX_DMA_CONFIG */
#endif /* BSP_SPI3_RX_USING_DMA */

#ifdef BSP_USING_SPI4
#ifndef SPI4_BUS_CONFIG
#define SPI4_BUS_CONFIG                                     \
    {                                                       \
        .Instance = CM_SPI4,                                \
        .bus_name = "spi4",                                 \
        .clock    = FCG1_PERIPH_SPI4,                       \
        .timeout  = 5000UL,                                 \
        .err_irq.irq_config =                               \
        {                                                   \
            .irq_num    = BSP_SPI4_ERR_IRQ_NUM,             \
            .irq_prio   = BSP_SPI4_ERR_IRQ_PRIO,            \
            .int_src    = INT_SRC_SPI4_SPEI,                \
        },                                                  \
    }
#endif /* SPI4_BUS_CONFIG */
#endif /* BSP_USING_SPI4 */

#ifdef BSP_SPI4_TX_USING_DMA
#ifndef SPI4_TX_DMA_CONFIG
#define SPI4_TX_DMA_CONFIG                                  \
    {                                                       \
        .Instance       = SPI4_TX_DMA_INSTANCE,             \
        .channel        = SPI4_TX_DMA_CHANNEL,              \
        .clock          = SPI4_TX_DMA_CLOCK,                \
        .trigger_select = SPI4_TX_DMA_TRIG_SELECT,          \
        .trigger_event  = EVT_SRC_SPI4_SPTI,                \
        .flag           = SPI4_TX_DMA_TRANS_FLAG,           \
        .irq_config     =                                   \
        {                                                   \
            .irq_num    = SPI4_TX_DMA_IRQn,                 \
            .irq_prio   = SPI4_TX_DMA_INT_PRIO,             \
            .int_src    = SPI4_TX_DMA_INT_SRC,              \
        }                                                   \
    }
#endif /* SPI4_TX_DMA_CONFIG */
#endif /* BSP_SPI4_TX_USING_DMA */

#ifdef BSP_SPI4_RX_USING_DMA
#ifndef SPI4_RX_DMA_CONFIG
#define SPI4_RX_DMA_CONFIG                                  \
    {                                                       \
        .Instance       = SPI4_RX_DMA_INSTANCE,             \
        .channel        = SPI4_RX_DMA_CHANNEL,              \
        .clock          = SPI4_RX_DMA_CLOCK,                \
        .trigger_select = SPI4_RX_DMA_TRIG_SELECT,          \
        .trigger_event  = EVT_SRC_SPI4_SPRI,                \
        .flag           = SPI4_RX_DMA_TRANS_FLAG,           \
        .irq_config     =                                   \
        {                                                   \
            .irq_num    = SPI4_RX_DMA_IRQn,                 \
            .irq_prio   = SPI4_RX_DMA_INT_PRIO,             \
            .int_src    = SPI4_RX_DMA_INT_SRC,              \
        }                                                   \
    }
#endif /* SPI4_RX_DMA_CONFIG */
#endif /* BSP_SPI4_RX_USING_DMA */

#ifdef BSP_USING_SPI5
#ifndef SPI5_BUS_CONFIG
#define SPI5_BUS_CONFIG                                     \
    {                                                       \
        .Instance = CM_SPI5,                                \
        .bus_name = "spi5",                                 \
        .clock    = FCG1_PERIPH_SPI5,                       \
        .timeout  = 5000UL,                                 \
        .err_irq.irq_config =                               \
        {                                                   \
            .irq_num    = BSP_SPI5_ERR_IRQ_NUM,             \
            .irq_prio   = BSP_SPI5_ERR_IRQ_PRIO,            \
            .int_src    = INT_SRC_SPI5_SPEI,                \
        },                                                  \
    }
#endif /* SPI5_BUS_CONFIG */
#endif /* BSP_USING_SPI5 */

#ifdef BSP_SPI5_TX_USING_DMA
#ifndef SPI5_TX_DMA_CONFIG
#define SPI5_TX_DMA_CONFIG                                  \
    {                                                       \
        .Instance       = SPI5_TX_DMA_INSTANCE,             \
        .channel        = SPI5_TX_DMA_CHANNEL,              \
        .clock          = SPI5_TX_DMA_CLOCK,                \
        .trigger_select = SPI5_TX_DMA_TRIG_SELECT,          \
        .trigger_event  = EVT_SRC_SPI5_SPTI,                \
        .flag           = SPI5_TX_DMA_TRANS_FLAG,           \
        .irq_config     =                                   \
        {                                                   \
            .irq_num    = SPI5_TX_DMA_IRQn,                 \
            .irq_prio   = SPI5_TX_DMA_INT_PRIO,             \
            .int_src    = SPI5_TX_DMA_INT_SRC,              \
        }                                                   \
    }
#endif /* SPI5_TX_DMA_CONFIG */
#endif /* BSP_SPI5_TX_USING_DMA */

#ifdef BSP_SPI5_RX_USING_DMA
#ifndef SPI5_RX_DMA_CONFIG
#define SPI5_RX_DMA_CONFIG                                  \
    {                                                       \
        .Instance       = SPI5_RX_DMA_INSTANCE,             \
        .channel        = SPI5_RX_DMA_CHANNEL,              \
        .clock          = SPI5_RX_DMA_CLOCK,                \
        .trigger_select = SPI5_RX_DMA_TRIG_SELECT,          \
        .trigger_event  = EVT_SRC_SPI5_SPRI,                \
        .flag           = SPI5_RX_DMA_TRANS_FLAG,           \
        .irq_config     =                                   \
        {                                                   \
            .irq_num    = SPI5_RX_DMA_IRQn,                 \
            .irq_prio   = SPI5_RX_DMA_INT_PRIO,             \
            .int_src    = SPI5_RX_DMA_INT_SRC,              \
        }                                                   \
    }
#endif /* SPI5_RX_DMA_CONFIG */
#endif /* BSP_SPI5_RX_USING_DMA */

#ifdef BSP_USING_SPI6
#ifndef SPI6_BUS_CONFIG
#define SPI6_BUS_CONFIG                                     \
    {                                                       \
        .Instance = CM_SPI6,                                \
        .bus_name = "spi6",                                 \
        .clock    = FCG1_PERIPH_SPI6,                       \
        .timeout  = 5000UL,                                 \
        .err_irq.irq_config =                               \
        {                                                   \
            .irq_num    = BSP_SPI6_ERR_IRQ_NUM,             \
            .irq_prio   = BSP_SPI6_ERR_IRQ_PRIO,            \
            .int_src    = INT_SRC_SPI6_SPEI,                \
        },                                                  \
    }
#endif /* SPI6_BUS_CONFIG */
#endif /* BSP_USING_SPI6 */

#ifdef BSP_SPI6_TX_USING_DMA
#ifndef SPI6_TX_DMA_CONFIG
#define SPI6_TX_DMA_CONFIG                                  \
    {                                                       \
        .Instance       = SPI6_TX_DMA_INSTANCE,             \
        .channel        = SPI6_TX_DMA_CHANNEL,              \
        .clock          = SPI6_TX_DMA_CLOCK,                \
        .trigger_select = SPI6_TX_DMA_TRIG_SELECT,          \
        .trigger_event  = EVT_SRC_SPI6_SPTI,                \
        .flag           = SPI6_TX_DMA_TRANS_FLAG,           \
        .irq_config     =                                   \
        {                                                   \
            .irq_num    = SPI6_TX_DMA_IRQn,                 \
            .irq_prio   = SPI6_TX_DMA_INT_PRIO,             \
            .int_src    = SPI6_TX_DMA_INT_SRC,              \
        }                                                   \
    }
#endif /* SPI6_TX_DMA_CONFIG */
#endif /* BSP_SPI6_TX_USING_DMA */

#ifdef BSP_SPI6_RX_USING_DMA
#ifndef SPI6_RX_DMA_CONFIG
#define SPI6_RX_DMA_CONFIG                                  \
    {                                                       \
        .Instance       = SPI6_RX_DMA_INSTANCE,             \
        .channel        = SPI6_RX_DMA_CHANNEL,              \
        .clock          = SPI6_RX_DMA_CLOCK,                \
        .trigger_select = SPI6_RX_DMA_TRIG_SELECT,          \
        .trigger_event  = EVT_SRC_SPI6_SPRI,                \
        .flag           = SPI6_RX_DMA_TRANS_FLAG,           \
        .irq_config     =                                   \
        {                                                   \
            .irq_num    = SPI6_RX_DMA_IRQn,                 \
            .irq_prio   = SPI6_RX_DMA_INT_PRIO,             \
            .int_src    = SPI6_RX_DMA_INT_SRC,              \
        }                                                   \
    }
#endif /* SPI6_RX_DMA_CONFIG */
#endif /* BSP_SPI6_RX_USING_DMA */


#ifdef __cplusplus
}
#endif

#endif /*__SPI_CONFIG_H__ */
