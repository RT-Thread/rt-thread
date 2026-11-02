/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     zhaohaisheng copy from sch and do some change
 */

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>

#include "ch32v30x_rcc.h"
#include "ch32v30x_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif /* ifdef __cplusplus */

struct ch32_hw_spi_cs
{
    GPIO_TypeDef* GPIOx;
    rt_uint16_t GPIO_Pin;
};

struct ch32_spi_config
{
    SPI_TypeDef *Instance;
    char *bus_name;
    IRQn_Type irq_type;

};

struct ch32_spi_device
{
    rt_uint32_t pin;
    char *bus_name;
    char *device_name;
};

typedef struct __SPI_HandleTypeDef
{

  SPI_TypeDef                *Instance;      /*!< SPI registers base address               */

  SPI_InitTypeDef            Init;           /*!< SPI communication parameters             */

  rt_uint8_t                    *pTxBuffPtr;    /*!< Pointer to SPI Tx transfer Buffer        */

  rt_uint16_t                   TxXferSize;     /*!< SPI Tx Transfer size                     */

  volatile rt_uint16_t          TxXferCount;    /*!< SPI Tx Transfer Counter                  */

  rt_uint8_t                    *pRxBuffPtr;    /*!< Pointer to SPI Rx transfer Buffer        */

  rt_uint16_t                   RxXferSize;     /*!< SPI Rx Transfer size                     */

  volatile rt_uint16_t          RxXferCount;    /*!< SPI Rx Transfer Counter                  */


} SPI_HandleTypeDef;

/* ch32 spi dirver class */
struct ch32_spi
{
    SPI_HandleTypeDef handle;

    struct ch32_spi_config *config;
    struct rt_spi_configuration *cfg;
    struct rt_spi_bus spi_bus;


};

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, GPIO_TypeDef* cs_gpiox, rt_uint16_t cs_gpio_pin);

#ifdef __cplusplus
}
#endif /* ifdef __cplusplus */

#endif /*__DRV_SPI_H__ */
