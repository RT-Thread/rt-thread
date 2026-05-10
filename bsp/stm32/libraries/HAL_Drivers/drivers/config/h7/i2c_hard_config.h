/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-06     Dyyt587   first version
 * 2024-04-23     Zeidan    Add I2Cx_xx_DMA_CONFIG
 * 2024-06-23     wdfk-prog Add H7 hard I2C config
 * 2026-04-13     wdfk-prog    Unify DMA config descriptors
 */
#ifndef __I2C_HARD_CONFIG_H__
#define __I2C_HARD_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_HARD_I2C1
#ifndef I2C1_BUS_CONFIG
#define I2C1_BUS_CONFIG             \
    {                               \
        .Instance = I2C1,           \
        .timing = 0x307075B1,       \
        .timeout = 1000,            \
        .name = "hwi2c1",           \
        .evirq_type = I2C1_EV_IRQn, \
        .erirq_type = I2C1_ER_IRQn, \
    }
#endif /* I2C1_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C1 */

#ifdef BSP_I2C1_TX_USING_DMA
#ifndef I2C1_TX_DMA_PRIORITY
#define I2C1_TX_DMA_PRIORITY                  DMA_PRIORITY_LOW
#endif /* I2C1_TX_DMA_PRIORITY */

#ifndef I2C1_TX_DMA_PREEMPT_PRIORITY
#define I2C1_TX_DMA_PREEMPT_PRIORITY          1
#endif /* I2C1_TX_DMA_PREEMPT_PRIORITY */

#ifndef I2C1_TX_DMA_SUB_PRIORITY
#define I2C1_TX_DMA_SUB_PRIORITY              0
#endif /* I2C1_TX_DMA_SUB_PRIORITY */
#ifndef I2C1_TX_DMA_CONFIG
#define I2C1_TX_DMA_CONFIG            \
    STM32_DMA_TX_BYTE_CONFIG_INIT_EX( \
        I2C1_TX_DMA_INSTANCE,         \
        I2C1_TX_DMA_RCC,              \
        I2C1_TX_DMA_IRQ,              \
        0U,                           \
        DMA_REQUEST_I2C1_TX,          \
        I2C1_TX_DMA_PRIORITY,         \
        I2C1_TX_DMA_PREEMPT_PRIORITY, \
        I2C1_TX_DMA_SUB_PRIORITY)
#endif /* I2C1_TX_DMA_CONFIG */
#endif /* BSP_I2C1_TX_USING_DMA */

#ifdef BSP_I2C1_RX_USING_DMA
#ifndef I2C1_RX_DMA_PRIORITY
#define I2C1_RX_DMA_PRIORITY                  DMA_PRIORITY_LOW
#endif /* I2C1_RX_DMA_PRIORITY */

#ifndef I2C1_RX_DMA_PREEMPT_PRIORITY
#define I2C1_RX_DMA_PREEMPT_PRIORITY          0
#endif /* I2C1_RX_DMA_PREEMPT_PRIORITY */

#ifndef I2C1_RX_DMA_SUB_PRIORITY
#define I2C1_RX_DMA_SUB_PRIORITY              0
#endif /* I2C1_RX_DMA_SUB_PRIORITY */
#ifndef I2C1_RX_DMA_CONFIG
#define I2C1_RX_DMA_CONFIG            \
    STM32_DMA_RX_BYTE_CONFIG_INIT_EX( \
        I2C1_RX_DMA_INSTANCE,         \
        I2C1_RX_DMA_RCC,              \
        I2C1_RX_DMA_IRQ,              \
        0U,                           \
        DMA_REQUEST_I2C1_RX,          \
        I2C1_RX_DMA_PRIORITY,         \
        I2C1_RX_DMA_PREEMPT_PRIORITY, \
        I2C1_RX_DMA_SUB_PRIORITY)
#endif /* I2C1_RX_DMA_CONFIG */
#endif /* BSP_I2C1_RX_USING_DMA */

#ifdef BSP_USING_HARD_I2C2
#ifndef I2C2_BUS_CONFIG
#define I2C2_BUS_CONFIG             \
    {                               \
        .Instance = I2C2,           \
        .timing = 0x307075B1,       \
        .timeout = 1000,            \
        .name = "hwi2c2",           \
        .evirq_type = I2C2_EV_IRQn, \
        .erirq_type = I2C2_ER_IRQn, \
    }
#endif /* I2C2_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C2 */

#ifdef BSP_I2C2_TX_USING_DMA
#ifndef I2C2_TX_DMA_PRIORITY
#define I2C2_TX_DMA_PRIORITY                  DMA_PRIORITY_LOW
#endif /* I2C2_TX_DMA_PRIORITY */

#ifndef I2C2_TX_DMA_PREEMPT_PRIORITY
#define I2C2_TX_DMA_PREEMPT_PRIORITY          1
#endif /* I2C2_TX_DMA_PREEMPT_PRIORITY */

#ifndef I2C2_TX_DMA_SUB_PRIORITY
#define I2C2_TX_DMA_SUB_PRIORITY              0
#endif /* I2C2_TX_DMA_SUB_PRIORITY */
#ifndef I2C2_TX_DMA_CONFIG
#define I2C2_TX_DMA_CONFIG            \
    STM32_DMA_TX_BYTE_CONFIG_INIT_EX( \
        I2C2_TX_DMA_INSTANCE,         \
        I2C2_TX_DMA_RCC,              \
        I2C2_TX_DMA_IRQ,              \
        0U,                           \
        DMA_REQUEST_I2C2_TX,          \
        I2C2_TX_DMA_PRIORITY,         \
        I2C2_TX_DMA_PREEMPT_PRIORITY, \
        I2C2_TX_DMA_SUB_PRIORITY)
#endif /* I2C2_TX_DMA_CONFIG */
#endif /* BSP_I2C2_TX_USING_DMA */

#ifdef BSP_I2C2_RX_USING_DMA
#ifndef I2C2_RX_DMA_PRIORITY
#define I2C2_RX_DMA_PRIORITY                  DMA_PRIORITY_LOW
#endif /* I2C2_RX_DMA_PRIORITY */

#ifndef I2C2_RX_DMA_PREEMPT_PRIORITY
#define I2C2_RX_DMA_PREEMPT_PRIORITY          0
#endif /* I2C2_RX_DMA_PREEMPT_PRIORITY */

#ifndef I2C2_RX_DMA_SUB_PRIORITY
#define I2C2_RX_DMA_SUB_PRIORITY              0
#endif /* I2C2_RX_DMA_SUB_PRIORITY */
#ifndef I2C2_RX_DMA_CONFIG
#define I2C2_RX_DMA_CONFIG            \
    STM32_DMA_RX_BYTE_CONFIG_INIT_EX( \
        I2C2_RX_DMA_INSTANCE,         \
        I2C2_RX_DMA_RCC,              \
        I2C2_RX_DMA_IRQ,              \
        0U,                           \
        DMA_REQUEST_I2C2_RX,          \
        I2C2_RX_DMA_PRIORITY,         \
        I2C2_RX_DMA_PREEMPT_PRIORITY, \
        I2C2_RX_DMA_SUB_PRIORITY)
#endif /* I2C2_RX_DMA_CONFIG */
#endif /* BSP_I2C2_RX_USING_DMA */

#ifdef BSP_USING_HARD_I2C3
#ifndef I2C3_BUS_CONFIG
#define I2C3_BUS_CONFIG             \
    {                               \
        .Instance = I2C3,           \
        .timing = 0x307075B1,       \
        .timeout = 1000,            \
        .name = "hwi2c3",           \
        .evirq_type = I2C3_EV_IRQn, \
        .erirq_type = I2C3_ER_IRQn, \
    }
#endif /* I2C3_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C3 */

#ifdef BSP_I2C3_TX_USING_DMA
#ifndef I2C3_TX_DMA_PRIORITY
#define I2C3_TX_DMA_PRIORITY                  DMA_PRIORITY_LOW
#endif /* I2C3_TX_DMA_PRIORITY */

#ifndef I2C3_TX_DMA_PREEMPT_PRIORITY
#define I2C3_TX_DMA_PREEMPT_PRIORITY          1
#endif /* I2C3_TX_DMA_PREEMPT_PRIORITY */

#ifndef I2C3_TX_DMA_SUB_PRIORITY
#define I2C3_TX_DMA_SUB_PRIORITY              0
#endif /* I2C3_TX_DMA_SUB_PRIORITY */
#ifndef I2C3_TX_DMA_CONFIG
#define I2C3_TX_DMA_CONFIG            \
    STM32_DMA_TX_BYTE_CONFIG_INIT_EX( \
        I2C3_TX_DMA_INSTANCE,         \
        I2C3_TX_DMA_RCC,              \
        I2C3_TX_DMA_IRQ,              \
        0U,                           \
        DMA_REQUEST_I2C3_TX,          \
        I2C3_TX_DMA_PRIORITY,         \
        I2C3_TX_DMA_PREEMPT_PRIORITY, \
        I2C3_TX_DMA_SUB_PRIORITY)
#endif /* I2C3_TX_DMA_CONFIG */
#endif /* BSP_I2C3_TX_USING_DMA */

#ifdef BSP_I2C3_RX_USING_DMA
#ifndef I2C3_RX_DMA_PRIORITY
#define I2C3_RX_DMA_PRIORITY                  DMA_PRIORITY_LOW
#endif /* I2C3_RX_DMA_PRIORITY */

#ifndef I2C3_RX_DMA_PREEMPT_PRIORITY
#define I2C3_RX_DMA_PREEMPT_PRIORITY          0
#endif /* I2C3_RX_DMA_PREEMPT_PRIORITY */

#ifndef I2C3_RX_DMA_SUB_PRIORITY
#define I2C3_RX_DMA_SUB_PRIORITY              0
#endif /* I2C3_RX_DMA_SUB_PRIORITY */
#ifndef I2C3_RX_DMA_CONFIG
#define I2C3_RX_DMA_CONFIG            \
    STM32_DMA_RX_BYTE_CONFIG_INIT_EX( \
        I2C3_RX_DMA_INSTANCE,         \
        I2C3_RX_DMA_RCC,              \
        I2C3_RX_DMA_IRQ,              \
        0U,                           \
        DMA_REQUEST_I2C3_RX,          \
        I2C3_RX_DMA_PRIORITY,         \
        I2C3_RX_DMA_PREEMPT_PRIORITY, \
        I2C3_RX_DMA_SUB_PRIORITY)
#endif /* I2C3_RX_DMA_CONFIG */
#endif /* BSP_I2C3_RX_USING_DMA */

#ifdef BSP_USING_HARD_I2C4
#ifndef I2C4_BUS_CONFIG
#define I2C4_BUS_CONFIG             \
    {                               \
        .Instance = I2C4,           \
        .timing = 0x307075B1,       \
        .timeout = 1000,            \
        .name = "hwi2c4",           \
        .evirq_type = I2C4_EV_IRQn, \
        .erirq_type = I2C4_ER_IRQn, \
    }
#endif /* I2C4_BUS_CONFIG */
#endif /* BSP_USING_HARD_I2C4 */

#ifdef BSP_I2C4_TX_USING_DMA
#ifndef I2C4_TX_DMA_PRIORITY
#define I2C4_TX_DMA_PRIORITY                  DMA_PRIORITY_LOW
#endif /* I2C4_TX_DMA_PRIORITY */

#ifndef I2C4_TX_DMA_PREEMPT_PRIORITY
#define I2C4_TX_DMA_PREEMPT_PRIORITY          1
#endif /* I2C4_TX_DMA_PREEMPT_PRIORITY */

#ifndef I2C4_TX_DMA_SUB_PRIORITY
#define I2C4_TX_DMA_SUB_PRIORITY              0
#endif /* I2C4_TX_DMA_SUB_PRIORITY */
#ifndef I2C4_TX_DMA_CONFIG
#define I2C4_TX_DMA_CONFIG            \
    STM32_DMA_TX_BYTE_CONFIG_INIT_EX( \
        I2C4_TX_DMA_INSTANCE,         \
        I2C4_TX_DMA_RCC,              \
        I2C4_TX_DMA_IRQ,              \
        0U,                           \
        DMA_REQUEST_I2C4_TX,          \
        I2C4_TX_DMA_PRIORITY,         \
        I2C4_TX_DMA_PREEMPT_PRIORITY, \
        I2C4_TX_DMA_SUB_PRIORITY)
#endif /* I2C4_TX_DMA_CONFIG */
#endif /* BSP_I2C4_TX_USING_DMA */

#ifdef BSP_I2C4_RX_USING_DMA
#ifndef I2C4_RX_DMA_PRIORITY
#define I2C4_RX_DMA_PRIORITY                  DMA_PRIORITY_LOW
#endif /* I2C4_RX_DMA_PRIORITY */

#ifndef I2C4_RX_DMA_PREEMPT_PRIORITY
#define I2C4_RX_DMA_PREEMPT_PRIORITY          0
#endif /* I2C4_RX_DMA_PREEMPT_PRIORITY */

#ifndef I2C4_RX_DMA_SUB_PRIORITY
#define I2C4_RX_DMA_SUB_PRIORITY              0
#endif /* I2C4_RX_DMA_SUB_PRIORITY */
#ifndef I2C4_RX_DMA_CONFIG
#define I2C4_RX_DMA_CONFIG            \
    STM32_DMA_RX_BYTE_CONFIG_INIT_EX( \
        I2C4_RX_DMA_INSTANCE,         \
        I2C4_RX_DMA_RCC,              \
        I2C4_RX_DMA_IRQ,              \
        0U,                           \
        DMA_REQUEST_I2C4_RX,          \
        I2C4_RX_DMA_PRIORITY,         \
        I2C4_RX_DMA_PREEMPT_PRIORITY, \
        I2C4_RX_DMA_SUB_PRIORITY)
#endif /* I2C4_RX_DMA_CONFIG */
#endif /* BSP_I2C4_RX_USING_DMA */


#ifdef __cplusplus
}
#endif

#endif /*__I2C_HARD_CONFIG_H__ */
