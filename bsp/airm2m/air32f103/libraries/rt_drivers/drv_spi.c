/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drivers/dev_spi.h"
#include "board.h"
#include "drv_spi.h"

#ifdef BSP_USING_SPI

#define LOG_TAG "drv.spi"
#include "drv_log.h"

#ifndef ITEM_NUM
#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])
#endif

struct spi_bus_device
{
    struct rt_spi_bus parent;
    char *name;
    SPI_TypeDef *periph;
    rt_base_t cs_pin;
    struct rt_spi_device spi_device;
};

static struct spi_bus_device spi_bus_device_list[] = {
#ifdef BSP_USING_SPI1
    {.periph = SPI1,
     .name = "spi1"},
#endif

#ifdef BSP_USING_SPI2
    {.periph = SPI2,
     .name = "spi2"},
#endif
};

/**
 * Attach the spi device to SPI bus, this function must be used after initialization.
 */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t pin)
{
    rt_err_t result;
    struct rt_spi_bus *spi_bus;
    struct spi_bus_device *spi_bus_dev;

    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    spi_bus = (struct rt_spi_bus *)rt_device_find(bus_name);

    RT_ASSERT(spi_bus != RT_NULL);

    spi_bus_dev = (struct spi_bus_device *)spi_bus;

    spi_bus_dev->cs_pin = pin;

    //often active low, output from master
    rt_pin_mode(spi_bus_dev->cs_pin, PIN_MODE_OUTPUT);
    rt_pin_write(spi_bus_dev->cs_pin, PIN_HIGH);

    result = rt_spi_bus_attach_device(&spi_bus_dev->spi_device, device_name, bus_name, RT_NULL);

    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    LOG_D("%s attach to %s done", device_name, bus_name);

    return result;
}

static rt_err_t air32_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
    struct rt_spi_bus *spi_bus;
    struct spi_bus_device *spi_bus_dev;
    rt_uint32_t spi_clock;

    SPI_InitTypeDef SPI_InitStruct;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    //device is not RT_NULL, so spi_bus not need check
    spi_bus = (struct rt_spi_bus *)device->bus;
    spi_bus_dev = (struct spi_bus_device *)spi_bus;

    air32_spi_clock_and_io_init(spi_bus_dev->periph);

    spi_clock = air32_spi_clock_get(spi_bus_dev->periph);

    if (configuration->data_width <= 8)
    {
        SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    }
    else if (configuration->data_width <= 16)
    {
        SPI_InitStruct.SPI_DataSize = SPI_DataSize_16b;
    }
    else
    {
        return -RT_EIO;
    }

    if (configuration->max_hz >= spi_clock / 2)
    {
        SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    }
    else if (configuration->max_hz >= spi_clock / 4)
    {
        SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    }
    else if (configuration->max_hz >= spi_clock / 8)
    {
        SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    }
    else if (configuration->max_hz >= spi_clock / 16)
    {
        SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
    }
    else if (configuration->max_hz >= spi_clock / 32)
    {
        SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
    }
    else if (configuration->max_hz >= spi_clock / 64)
    {
        SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
    }
    else if (configuration->max_hz >= spi_clock / 128)
    {
        SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
    }
    else
    {
        /*  min prescaler 256 */
        SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    }

    switch (configuration->mode & RT_SPI_MODE_3)
    {
    case RT_SPI_MODE_0:
        SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
        SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
        break;
    case RT_SPI_MODE_1:
        SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
        SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
        break;
    case RT_SPI_MODE_2:
        SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
        SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
        break;
    case RT_SPI_MODE_3:
        SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
        SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
        break;
    }

    /* MSB or LSB */
    if (configuration->mode & RT_SPI_MSB)
    {
        SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    }
    else
    {
        SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_LSB;
    }

    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;

    SPI_Init(spi_bus_dev->periph, &SPI_InitStruct);
    /* Enable SPI_MASTER */
    SPI_Cmd(spi_bus_dev->periph, ENABLE);

    return RT_EOK;
};

static rt_uint32_t air32_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct rt_spi_bus *spi_bus;
    struct spi_bus_device *spi_bus_dev;
    struct rt_spi_configuration *config;

    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    //device is not RT_NULL, so spi_bus not need check
    spi_bus = (struct rt_spi_bus *)device->bus;
    spi_bus_dev = (struct spi_bus_device *)spi_bus;
    config = &device->config;

    /* take CS */
    if (message->cs_take)
    {
        rt_pin_write(spi_bus_dev->cs_pin, PIN_LOW);
        LOG_D("spi take cs\n");
    }

    if (config->data_width <= 8)
    {
        const rt_uint8_t *send_ptr = message->send_buf;
        rt_uint8_t *recv_ptr = message->recv_buf;
        rt_uint32_t size = message->length;
        rt_uint8_t data;

        LOG_D("spi poll transfer start: %d\n", size);

        while (size--)
        {
            data = 0xFF;

            if (send_ptr != RT_NULL)
            {
                data = *send_ptr++;
            }

            //Wait until the transmit buffer is empty
            while (SPI_I2S_GetFlagStatus(spi_bus_dev->periph, SPI_I2S_FLAG_TXE) == RESET);
            // Send the byte
            SPI_I2S_SendData(spi_bus_dev->periph, data);

            //Wait until a data is received
            while (SPI_I2S_GetFlagStatus(spi_bus_dev->periph, SPI_I2S_FLAG_RXNE) == RESET);
            // Get the received data
            data = SPI_I2S_ReceiveData(spi_bus_dev->periph);

            if (recv_ptr != RT_NULL)
            {
                *recv_ptr++ = data;
            }
        }
        LOG_D("spi poll transfer finsh\n");
    }
    else if (config->data_width <= 16)
    {
        const rt_uint16_t *send_ptr = message->send_buf;
        rt_uint16_t *recv_ptr = message->recv_buf;
        rt_uint32_t size = message->length;
        rt_uint16_t data;

        while (size--)
        {
            data = 0xFF;

            if (send_ptr != RT_NULL)
            {
                data = *send_ptr++;
            }

            //Wait until the transmit buffer is empty
            while (RESET == SPI_I2S_GetFlagStatus(spi_bus_dev->periph, SPI_I2S_FLAG_TXE))
                ;
            // Send the byte
            SPI_I2S_SendData(spi_bus_dev->periph, data);

            //Wait until a data is received
            while (RESET == SPI_I2S_GetFlagStatus(spi_bus_dev->periph, SPI_I2S_FLAG_RXNE))
                ;
            // Get the received data
            data = SPI_I2S_ReceiveData(spi_bus_dev->periph);

            if (recv_ptr != RT_NULL)
            {
                *recv_ptr++ = data;
            }
        }
    }

    /* release CS */
    if (message->cs_release)
    {
        rt_pin_write(spi_bus_dev->cs_pin, PIN_HIGH);
        LOG_D("spi release cs\n");
    }

    return message->length;
};

static struct rt_spi_ops spi_ops = {
    .configure = air32_spi_configure,
    .xfer = air32_spi_xfer};

int rt_hw_spi_init(void)
{
    int index;

    for (index = 0; index < ITEM_NUM(spi_bus_device_list); index++)
    {
        rt_spi_bus_register(&spi_bus_device_list[index].parent, spi_bus_device_list[index].name, &spi_ops);
    }

    return RT_EOK;
}

INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* BSP_USING_SPI */
