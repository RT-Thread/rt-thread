/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __CAN_CONFIG_H__
#define __CAN_CONFIG_H__

#include <rtthread.h>
#include "n32h49x_fdcan.h"

#ifdef __cplusplus
extern "C" {
#endif

struct n32_fdcan_config
{
    const char *name;
    FDCAN_Module *Instance;
    uint32_t std_filter_size;
    uint32_t ext_filter_size;
    uint32_t rx_fifo0_size;
    uint32_t rx_fifo0_data_bytes;
    uint32_t rx_fifo1_size;
    uint32_t rx_fifo1_data_bytes;
    uint32_t rx_buffer_size;
    uint32_t rx_buffer_data_bytes;
    uint32_t tx_event_size;
    uint32_t tx_buffer_size;
    uint32_t tx_buffer_data_bytes;
    uint32_t tx_fifo_queue_size;
    uint32_t tx_fifo_queue_mode;
    uint32_t tdc_offset;
    uint32_t tdc_filter;
    rt_bool_t tdc_enabled;
};

#define FDCAN_RESOURCE_CONFIG(number)                                 \
    .std_filter_size = BSP_FDCAN##number##_STD_FILTER_SIZE,           \
    .ext_filter_size = BSP_FDCAN##number##_EXT_FILTER_SIZE,           \
    .rx_fifo0_size = BSP_FDCAN##number##_RX_FIFO0_SIZE,               \
    .rx_fifo0_data_bytes = BSP_FDCAN##number##_RX_FIFO0_DATA_BYTES,   \
    .rx_fifo1_size = BSP_FDCAN##number##_RX_FIFO1_SIZE,               \
    .rx_fifo1_data_bytes = BSP_FDCAN##number##_RX_FIFO1_DATA_BYTES,   \
    .rx_buffer_size = BSP_FDCAN##number##_RX_BUFFER_SIZE,             \
    .rx_buffer_data_bytes = BSP_FDCAN##number##_RX_BUFFER_DATA_BYTES, \
    .tx_event_size = BSP_FDCAN##number##_TX_EVENT_FIFO_SIZE,          \
    .tx_buffer_size = BSP_FDCAN##number##_TX_BUFFER_SIZE,             \
    .tx_buffer_data_bytes = BSP_FDCAN##number##_TX_BUFFER_DATA_BYTES, \
    .tx_fifo_queue_size = BSP_FDCAN##number##_TX_FIFO_QUEUE_SIZE

#define FDCAN_INSTANCE_CONFIG(number)  \
    {                                  \
        .name = "fdcan" #number,       \
        .Instance = FDCAN##number,     \
        FDCAN_RESOURCE_CONFIG(number), \
        FDCAN##number##_MODE_CONFIG,   \
        FDCAN##number##_TDC_CONFIG,    \
    }

#define FDCAN_TX_FIFO_CONFIG(number) \
    .tx_fifo_queue_mode = FDCAN_TX_FIFO_MODE
#define FDCAN_TX_QUEUE_CONFIG(number) \
    .tx_fifo_queue_mode = FDCAN_TX_QUEUE_MODE
#define FDCAN_TDC_DISABLED_CONFIG(number) \
    .tdc_enabled = RT_FALSE, .tdc_offset = 0, .tdc_filter = 0
#define FDCAN_TDC_ENABLED_CONFIG(number)          \
    .tdc_enabled = RT_TRUE,                       \
    .tdc_offset = BSP_FDCAN##number##_TDC_OFFSET, \
    .tdc_filter = BSP_FDCAN##number##_TDC_FILTER

#if defined(BSP_USING_FDCAN1)
#if defined(BSP_FDCAN1_TX_QUEUE_MODE)
#define FDCAN1_MODE_CONFIG FDCAN_TX_QUEUE_CONFIG(1)
#else
#define FDCAN1_MODE_CONFIG FDCAN_TX_FIFO_CONFIG(1)
#endif
#if defined(BSP_FDCAN1_USING_TDC)
#define FDCAN1_TDC_CONFIG FDCAN_TDC_ENABLED_CONFIG(1)
#else
#define FDCAN1_TDC_CONFIG FDCAN_TDC_DISABLED_CONFIG(1)
#endif
#define FDCAN1_CONFIG FDCAN_INSTANCE_CONFIG(1)
#endif

#if defined(BSP_USING_FDCAN2)
#if defined(BSP_FDCAN2_TX_QUEUE_MODE)
#define FDCAN2_MODE_CONFIG FDCAN_TX_QUEUE_CONFIG(2)
#else
#define FDCAN2_MODE_CONFIG FDCAN_TX_FIFO_CONFIG(2)
#endif
#if defined(BSP_FDCAN2_USING_TDC)
#define FDCAN2_TDC_CONFIG FDCAN_TDC_ENABLED_CONFIG(2)
#else
#define FDCAN2_TDC_CONFIG FDCAN_TDC_DISABLED_CONFIG(2)
#endif
#define FDCAN2_CONFIG FDCAN_INSTANCE_CONFIG(2)
#endif

#if defined(BSP_USING_FDCAN3)
#if defined(BSP_FDCAN3_TX_QUEUE_MODE)
#define FDCAN3_MODE_CONFIG FDCAN_TX_QUEUE_CONFIG(3)
#else
#define FDCAN3_MODE_CONFIG FDCAN_TX_FIFO_CONFIG(3)
#endif
#if defined(BSP_FDCAN3_USING_TDC)
#define FDCAN3_TDC_CONFIG FDCAN_TDC_ENABLED_CONFIG(3)
#else
#define FDCAN3_TDC_CONFIG FDCAN_TDC_DISABLED_CONFIG(3)
#endif
#define FDCAN3_CONFIG FDCAN_INSTANCE_CONFIG(3)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __CAN_CONFIG_H__ */
