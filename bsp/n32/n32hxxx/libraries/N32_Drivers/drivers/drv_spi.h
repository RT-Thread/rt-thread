/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include "drv_dma.h"
#include <ipc/completion.h>

#ifdef __cplusplus
extern "C" {
#endif

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin);

#ifdef __cplusplus
}
#endif

struct n32_spi_config
{
    SPI_Module *SPIx;
    char *bus_name;
    IRQn_Type irq_type;
    struct dma_config *dma_rx, *dma_tx;
};

struct n32_spi_device
{
    rt_uint32_t pin;
    char *bus_name;
    char *device_name;
};


#define SPI_USING_RX_DMA_FLAG   (1<<0)
#define SPI_USING_TX_DMA_FLAG   (1<<1)

typedef enum
{
    SPI_Tx_Rx = 0U,
    SPI_Tx,
    SPI_Rx,
    SPI_Idle,
} SPI_Work_Direct_t;

/* n32 spi dirver class */
struct n32_spi
{
    struct n32_spi_config *config;
    struct rt_spi_configuration *cfg;

    SPI_InitType SPI_InitStructure;
    SPI_Work_Direct_t Direct;

    struct
    {
        rt_bool_t DMA_Tx_Init;
        DMA_ChInitType TX_DMA_ChInitStr;

        rt_bool_t DMA_Rx_Init;
        DMA_ChInitType RX_DMA_ChInitStr;
    } dma;

    rt_uint8_t spi_dma_flag;
    struct rt_spi_bus spi_bus;

    struct rt_completion cpt;
};

#endif /*__DRV_SPI_H__ */
