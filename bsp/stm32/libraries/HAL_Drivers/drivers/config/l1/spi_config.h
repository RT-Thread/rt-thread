/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 * 2019-01-05     SummerGift   modify DMA support
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
        SPI1_TX_DMA_CHANNEL,          \
        0U,                           \
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
        SPI1_RX_DMA_CHANNEL,          \
        0U,                           \
        SPI1_RX_DMA_PRIORITY,         \
        SPI1_RX_DMA_PREEMPT_PRIORITY, \
        SPI1_RX_DMA_SUB_PRIORITY)
#endif /* SPI1_RX_DMA_CONFIG */
#endif /* BSP_SPI1_RX_USING_DMA */

#ifdef BSP_USING_SPI2
#ifndef SPI2_BUS_CONFIG
#define SPI2_BUS_CONFIG        \
    {                          \
        .Instance = SPI2,      \
        .bus_name = "spi2",    \
        .irq_type = SPI2_IRQn, \
    }
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
        SPI2_TX_DMA_CHANNEL,          \
        0U,                           \
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
        SPI2_RX_DMA_CHANNEL,          \
        0U,                           \
        SPI2_RX_DMA_PRIORITY,         \
        SPI2_RX_DMA_PREEMPT_PRIORITY, \
        SPI2_RX_DMA_SUB_PRIORITY)
#endif /* SPI2_RX_DMA_CONFIG */
#endif /* BSP_SPI2_RX_USING_DMA */

#ifdef BSP_USING_SPI3
#ifndef SPI3_BUS_CONFIG
#define SPI3_BUS_CONFIG        \
    {                          \
        .Instance = SPI3,      \
        .bus_name = "spi3",    \
        .irq_type = SPI3_IRQn, \
    }
#endif /* SPI3_BUS_CONFIG */
#endif /* BSP_USING_SPI3 */

#ifdef BSP_SPI3_TX_USING_DMA
#ifndef SPI3_TX_DMA_PRIORITY
#define SPI3_TX_DMA_PRIORITY                  DMA_PRIORITY_LOW
#endif /* SPI3_TX_DMA_PRIORITY */

#ifndef SPI3_TX_DMA_PREEMPT_PRIORITY
#define SPI3_TX_DMA_PREEMPT_PRIORITY          1
#endif /* SPI3_TX_DMA_PREEMPT_PRIORITY */

#ifndef SPI3_TX_DMA_SUB_PRIORITY
#define SPI3_TX_DMA_SUB_PRIORITY              0
#endif /* SPI3_TX_DMA_SUB_PRIORITY */
#ifndef SPI3_TX_DMA_CONFIG
#define SPI3_TX_DMA_CONFIG            \
    STM32_DMA_TX_BYTE_CONFIG_INIT_EX( \
        SPI3_TX_DMA_INSTANCE,         \
        SPI3_TX_DMA_RCC,              \
        SPI3_TX_DMA_IRQ,              \
        SPI3_TX_DMA_CHANNEL,          \
        0U,                           \
        SPI3_TX_DMA_PRIORITY,         \
        SPI3_TX_DMA_PREEMPT_PRIORITY, \
        SPI3_TX_DMA_SUB_PRIORITY)
#endif /* SPI3_TX_DMA_CONFIG */
#endif /* BSP_SPI3_TX_USING_DMA */

#ifdef BSP_SPI3_RX_USING_DMA
#ifndef SPI3_RX_DMA_PRIORITY
#define SPI3_RX_DMA_PRIORITY                  DMA_PRIORITY_HIGH
#endif /* SPI3_RX_DMA_PRIORITY */

#ifndef SPI3_RX_DMA_PREEMPT_PRIORITY
#define SPI3_RX_DMA_PREEMPT_PRIORITY          0
#endif /* SPI3_RX_DMA_PREEMPT_PRIORITY */

#ifndef SPI3_RX_DMA_SUB_PRIORITY
#define SPI3_RX_DMA_SUB_PRIORITY              0
#endif /* SPI3_RX_DMA_SUB_PRIORITY */
#ifndef SPI3_RX_DMA_CONFIG
#define SPI3_RX_DMA_CONFIG            \
    STM32_DMA_RX_BYTE_CONFIG_INIT_EX( \
        SPI3_RX_DMA_INSTANCE,         \
        SPI3_RX_DMA_RCC,              \
        SPI3_RX_DMA_IRQ,              \
        SPI3_RX_DMA_CHANNEL,          \
        0U,                           \
        SPI3_RX_DMA_PRIORITY,         \
        SPI3_RX_DMA_PREEMPT_PRIORITY, \
        SPI3_RX_DMA_SUB_PRIORITY)
#endif /* SPI3_RX_DMA_CONFIG */
#endif /* BSP_SPI3_RX_USING_DMA */

#ifdef __cplusplus
}
#endif

#endif /*__SPI_CONFIG_H__ */



