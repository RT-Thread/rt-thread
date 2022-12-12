/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */


#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>
#include "rtdevice.h"
#include "drv_dma.h"
#include "drv_irq.h"

#ifdef __cplusplus
extern "C" {
#endif


struct hc32_hw_spi_cs
{
    rt_uint8_t  port;
    rt_uint16_t pin;
};

struct hc32_spi_config
{
    CM_SPI_TypeDef          *Instance;
    char                    *bus_name;
    rt_uint32_t             clock;
    // struct hc32_irq_config  irq_config;
    struct dma_config       *dma_rx;
    struct dma_config       *dma_tx;
};

struct hc32_spi
{
    struct hc32_spi_config      *config;
    struct rt_spi_configuration *cfg;
    struct rt_spi_bus           spi_bus;
    rt_uint8_t                  spi_dma_flag;
};

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, uint8_t cs_gpio_port, uint16_t cs_gpio_pin);


#ifdef __cplusplus
}
#endif

#endif /* __DRV_SPI_H__ */

