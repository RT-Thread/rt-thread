/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-05     zylx         first version
 * 2019-01-08     SummerGift   clean up the code
 * 2026-04-13     wdfk-prog    Unify DMA config descriptors
 */

#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_SPI1
#ifndef SPI1_BUS_CONFIG
#define SPI1_BUS_CONFIG        \
    {                          \
        .Instance = SPI1,      \
        .bus_name = "spi1",    \
        .irq_type = SPI1_IRQn, \
    }
#endif /* SPI1_BUS_CONFIG */
#endif /* BSP_USING_SPI1 */

#ifdef BSP_SPI1_TX_USING_DMA
#ifndef SPI1_TX_DMA_PRIORITY
#define SPI1_TX_DMA_PRIORITY                  DMA_PRIORITY_LOW
#endif /* SPI1_TX_DMA_PRIORITY */

#ifndef SPI1_TX_DMA_PREEMPT_PRIORITY
#define SPI1_TX_DMA_PREEMPT_PRIORITY          1
#endif /* SPI1_TX_DMA_PREEMPT_PRIORITY */

#ifndef SPI1_TX_DMA_SUB_PRIORITY
#define SPI1_TX_DMA_SUB_PRIORITY              0
#endif /* SPI1_TX_DMA_SUB_PRIORITY */
#ifndef SPI1_TX_DMA_CONFIG
#define SPI1_TX_DMA_CONFIG            \
    STM32_DMA_TX_BYTE_CONFIG_INIT_EX( \
        SPI1_TX_DMA_INSTANCE,         \
        SPI1_TX_DMA_RCC,              \
        SPI1_TX_DMA_IRQ,              \
        0U,                           \
        SPI1_TX_DMA_REQUEST,          \
        SPI1_TX_DMA_PRIORITY,         \
        SPI1_TX_DMA_PREEMPT_PRIORITY, \
        SPI1_TX_DMA_SUB_PRIORITY)
#endif /* SPI1_TX_DMA_CONFIG */
#endif /* BSP_SPI1_TX_USING_DMA */

#ifdef BSP_SPI1_RX_USING_DMA
#ifndef SPI1_RX_DMA_PRIORITY
#define SPI1_RX_DMA_PRIORITY                  DMA_PRIORITY_HIGH
#endif /* SPI1_RX_DMA_PRIORITY */

#ifndef SPI1_RX_DMA_PREEMPT_PRIORITY
#define SPI1_RX_DMA_PREEMPT_PRIORITY          0
#endif /* SPI1_RX_DMA_PREEMPT_PRIORITY */

#ifndef SPI1_RX_DMA_SUB_PRIORITY
#define SPI1_RX_DMA_SUB_PRIORITY              0
#endif /* SPI1_RX_DMA_SUB_PRIORITY */
#ifndef SPI1_RX_DMA_CONFIG
#define SPI1_RX_DMA_CONFIG            \
    STM32_DMA_RX_BYTE_CONFIG_INIT_EX( \
        SPI1_RX_DMA_INSTANCE,         \
        SPI1_RX_DMA_RCC,              \
        SPI1_RX_DMA_IRQ,              \
        0U,                           \
        SPI1_RX_DMA_REQUEST,          \
        SPI1_RX_DMA_PRIORITY,         \
        SPI1_RX_DMA_PREEMPT_PRIORITY, \
        SPI1_RX_DMA_SUB_PRIORITY)
#endif /* SPI1_RX_DMA_CONFIG */
#endif /* BSP_SPI1_RX_USING_DMA */

#ifdef BSP_USING_SPI2
#ifndef SPI2_BUS_CONFIG
#if defined(STM32G0B0xx) || defined(STM32G0B1xx) || defined(STM32G0C1xx)
#define SPI2_BUS_CONFIG          \
    {                            \
        .Instance = SPI2,        \
        .bus_name = "spi2",      \
        .irq_type = SPI2_3_IRQn, \
    }
#else
#define SPI2_BUS_CONFIG        \
    {                          \
        .Instance = SPI2,      \
        .bus_name = "spi2",    \
        .irq_type = SPI2_IRQn, \
    }
#endif /* defined(STM32G0B0xx) || defined(STM32G0B1xx) || defined(STM32G0C1xx) */
#endif /* SPI2_BUS_CONFIG */
#endif /* BSP_USING_SPI2 */

#ifdef BSP_SPI2_TX_USING_DMA
#ifndef SPI2_TX_DMA_PRIORITY
#define SPI2_TX_DMA_PRIORITY                  DMA_PRIORITY_LOW
#endif /* SPI2_TX_DMA_PRIORITY */

#ifndef SPI2_TX_DMA_PREEMPT_PRIORITY
#define SPI2_TX_DMA_PREEMPT_PRIORITY          1
#endif /* SPI2_TX_DMA_PREEMPT_PRIORITY */

#ifndef SPI2_TX_DMA_SUB_PRIORITY
#define SPI2_TX_DMA_SUB_PRIORITY              0
#endif /* SPI2_TX_DMA_SUB_PRIORITY */
#ifndef SPI2_TX_DMA_CONFIG
#define SPI2_TX_DMA_CONFIG            \
    STM32_DMA_TX_BYTE_CONFIG_INIT_EX( \
        SPI2_TX_DMA_INSTANCE,         \
        SPI2_TX_DMA_RCC,              \
        SPI2_TX_DMA_IRQ,              \
        0U,                           \
        SPI2_TX_DMA_REQUEST,          \
        SPI2_TX_DMA_PRIORITY,         \
        SPI2_TX_DMA_PREEMPT_PRIORITY, \
        SPI2_TX_DMA_SUB_PRIORITY)
#endif /* SPI2_TX_DMA_CONFIG */
#endif /* BSP_SPI2_TX_USING_DMA */

#ifdef BSP_SPI2_RX_USING_DMA
#ifndef SPI2_RX_DMA_PRIORITY
#define SPI2_RX_DMA_PRIORITY                  DMA_PRIORITY_HIGH
#endif /* SPI2_RX_DMA_PRIORITY */

#ifndef SPI2_RX_DMA_PREEMPT_PRIORITY
#define SPI2_RX_DMA_PREEMPT_PRIORITY          0
#endif /* SPI2_RX_DMA_PREEMPT_PRIORITY */

#ifndef SPI2_RX_DMA_SUB_PRIORITY
#define SPI2_RX_DMA_SUB_PRIORITY              0
#endif /* SPI2_RX_DMA_SUB_PRIORITY */
#ifndef SPI2_RX_DMA_CONFIG
#define SPI2_RX_DMA_CONFIG            \
    STM32_DMA_RX_BYTE_CONFIG_INIT_EX( \
        SPI2_RX_DMA_INSTANCE,         \
        SPI2_RX_DMA_RCC,              \
        SPI2_RX_DMA_IRQ,              \
        0U,                           \
        SPI2_RX_DMA_REQUEST,          \
        SPI2_RX_DMA_PRIORITY,         \
        SPI2_RX_DMA_PREEMPT_PRIORITY, \
        SPI2_RX_DMA_SUB_PRIORITY)
#endif /* SPI2_RX_DMA_CONFIG */
#endif /* BSP_SPI2_RX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /*__SPI_CONFIG_H__ */



