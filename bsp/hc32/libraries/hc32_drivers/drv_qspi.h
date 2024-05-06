/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-15     CDT          first version
 */

#ifndef __DRV_QSPI_H__
#define __DRV_QSPI_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_dma.h"

#ifdef __cplusplus
extern "C" {
#endif


struct hc32_hw_qspi_cs
{
    rt_uint16_t pin;
};

struct hc32_qspi_irq_config
{
    struct hc32_irq_config irq_config;
    func_ptr_t             irq_callback;
};

struct hc32_qspi_config
{
    CM_QSPI_TypeDef             *Instance;
    rt_uint32_t                 clock;
    rt_uint32_t                 timeout;
    struct hc32_qspi_irq_config err_irq;
#ifdef BSP_QSPI_USING_DMA
    struct dma_config           *dma_qspi;
#if defined (HC32F448)
    rt_uint16_t                 *dma_tx_buf;
    rt_uint16_t                 dma_tx_buf_size;    /* unit: half-word, DMA data width of QSPI transmitting is 16bit */
#endif
#endif
};

struct hc32_qspi_bus
{
    struct hc32_qspi_config     *config;
    char                        *bus_name;
};

rt_err_t rt_hw_qspi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint32_t pin, rt_uint8_t data_line_width, void (*enter_qspi_mode)(), void (*exit_qspi_mode)());

#ifdef __cplusplus
}
#endif

#endif /* __DRV_QSPI_H__ */
