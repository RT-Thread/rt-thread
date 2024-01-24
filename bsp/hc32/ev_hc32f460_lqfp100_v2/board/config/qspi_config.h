/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-15     CDT          first version
 */

#ifndef __QSPI_CONFIG_H__
#define __QSPI_CONFIG_H__

#include <rtthread.h>
#include "irq_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_QSPI
#ifndef QSPI_BUS_CONFIG
#define QSPI_BUS_CONFIG                                     \
    {                                                       \
        .Instance = CM_QSPI,                                \
        .clock    = FCG1_PERIPH_QSPI,                       \
        .timeout  = 5000UL,                                 \
        .err_irq.irq_config =                               \
        {                                                   \
            .irq_num    = BSP_QSPI_ERR_IRQ_NUM,             \
            .irq_prio   = BSP_QSPI_ERR_IRQ_PRIO,            \
            .int_src    = INT_SRC_QSPI_INTR,                \
        },                                                  \
    }
#endif /* QSPI_BUS_CONFIG */

#ifndef QSPI_INIT_PARAMS
#define QSPI_INIT_PARAMS                                        \
    {                                                           \
        .u32PrefetchMode   = QSPI_PREFETCH_MD_INVD,             \
        .u32SetupTime      = QSPI_QSSN_SETUP_ADVANCE_QSCK0P5,   \
        .u32ReleaseTime    = QSPI_QSSN_RELEASE_DELAY_QSCK32,    \
        .u32IntervalTime   = QSPI_QSSN_INTERVAL_QSCK1,          \
    }
#endif /* QSPI_INIT_PARAMS */

#define QSPI_WP_PIN_LEVEL               QSPI_WP_PIN_HIGH

#ifdef BSP_QSPI_USING_DMA
#ifndef QSPI_DMA_CONFIG
#define QSPI_DMA_CONFIG                                     \
    {                                                       \
        .Instance       = QSPI_DMA_INSTANCE,                \
        .channel        = QSPI_DMA_CHANNEL,                 \
        .clock          = QSPI_DMA_CLOCK,                   \
        .trigger_select = QSPI_DMA_TRIG_SELECT,             \
        .trigger_event  = EVT_SRC_AOS_STRG,                 \
        .flag           = QSPI_DMA_TRANS_FLAG,              \
        .irq_config     =                                   \
        {                                                   \
            .irq_num    = QSPI_DMA_IRQn,                    \
            .irq_prio   = QSPI_DMA_INT_PRIO,                \
            .int_src    = QSPI_DMA_INT_SRC,                 \
        }                                                   \
    }
#endif /* QSPI_DMA_CONFIG */
#endif /* BSP_QSPI_USING_DMA */
#endif /* BSP_USING_SPI1 */

#ifdef __cplusplus
}
#endif

#endif /*__QSPI_CONFIG_H__ */
