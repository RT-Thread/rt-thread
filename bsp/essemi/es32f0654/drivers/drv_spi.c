/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-01-24     wangyq        the first version
 * 2019-11-01     wangyq        update libraries
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include <rthw.h>
#include "board.h"
#include "drv_spi.h"
#include <ald_spi.h>
#include <ald_gpio.h>
#include <ald_cmu.h>

#ifdef RT_USING_SPI

#define SPITIMEOUT 0x0FFF

rt_err_t spi_configure(struct rt_spi_device *device,
                       struct rt_spi_configuration *cfg)
{
    spi_handle_t *hspi;
    hspi = (spi_handle_t *)device->bus->parent.user_data;

    /* config spi mode */
    if (cfg->mode & RT_SPI_SLAVE)
    {
        hspi->init.mode = SPI_MODE_SLAVER;
    }
    else
    {
        hspi->init.mode = SPI_MODE_MASTER;
    }
    if (cfg->mode & RT_SPI_3WIRE)
    {
        hspi->init.dir = SPI_DIRECTION_1LINE;
    }
    else
    {
        hspi->init.dir = SPI_DIRECTION_2LINES;
    }
    if (cfg->data_width == 8)
    {
        hspi->init.data_size = SPI_DATA_SIZE_8;
    }
    else if (cfg->data_width == 16)
    {
        hspi->init.data_size = SPI_DATA_SIZE_16;
    }

    if (cfg->mode & RT_SPI_CPHA)
    {
        hspi->init.phase = SPI_CPHA_SECOND;
    }
    else
    {
        hspi->init.phase = SPI_CPHA_FIRST;
    }
    if (cfg->mode & RT_SPI_CPOL)
    {
        hspi->init.polarity = SPI_CPOL_HIGH;
    }
    else
    {
        hspi->init.polarity = SPI_CPOL_LOW;
    }
    if (cfg->mode & RT_SPI_NO_CS)
    {
        hspi->init.ss_en = DISABLE;
    }
    else
    {
        hspi->init.ss_en = ENABLE;
    }

    /* config spi clock */
    if (cfg->max_hz >= ald_cmu_get_pclk1_clock() / 2)
    {
        /* pclk1 max speed 48MHz, spi master max speed 10MHz */
        if (ald_cmu_get_pclk1_clock() / 2 <= 10000000)
        {
            hspi->init.baud = SPI_BAUD_2;
        }
        else if (ald_cmu_get_pclk1_clock() / 4 <= 10000000)
        {
            hspi->init.baud = SPI_BAUD_4;
        }
        else
        {
            hspi->init.baud = SPI_BAUD_8;
        }
    }
    else if (cfg->max_hz >= ald_cmu_get_pclk1_clock() / 4)
    {
        /* pclk1 max speed 48MHz, spi master max speed 10MHz */
        if (ald_cmu_get_pclk1_clock() / 4 <= 10000000)
        {
            hspi->init.baud = SPI_BAUD_4;
        }
        else
        {
            hspi->init.baud = SPI_BAUD_8;
        }
    }
    else if (cfg->max_hz >= ald_cmu_get_pclk1_clock() / 8)
    {
        hspi->init.baud = SPI_BAUD_8;
    }
    else if (cfg->max_hz >= ald_cmu_get_pclk1_clock() / 16)
    {
        hspi->init.baud = SPI_BAUD_16;
    }
    else if (cfg->max_hz >= ald_cmu_get_pclk1_clock() / 32)
    {
        hspi->init.baud = SPI_BAUD_32;
    }
    else if (cfg->max_hz >= ald_cmu_get_pclk1_clock() / 64)
    {
        hspi->init.baud = SPI_BAUD_64;
    }
    else if (cfg->max_hz >= ald_cmu_get_pclk1_clock() / 128)
    {
        hspi->init.baud = SPI_BAUD_128;
    }
    else
    {
        hspi->init.baud = SPI_BAUD_256;
    }
    ald_spi_init(hspi);
    return RT_EOK;
}

static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_err_t res;
    spi_handle_t *hspi;
    struct es32f0_hw_spi_cs *cs;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    RT_ASSERT(message->send_buf != RT_NULL || message->recv_buf != RT_NULL);

    hspi = (spi_handle_t *)device->bus->parent.user_data;
    cs = device->parent.user_data;

    /* only send data */
    if (message->recv_buf == RT_NULL)
    {
        if (message->cs_take)
        {
            rt_pin_write(cs->pin, 0);
        }
        res = ald_spi_send(hspi, (rt_uint8_t *)message->send_buf, (rt_int32_t)message->length, SPITIMEOUT);
        if (message->cs_release)
        {
            rt_pin_write(cs->pin, 1);
        }
        if (res != RT_EOK)
            return RT_ERROR;
    }

    /* only receive data */
    if (message->send_buf == RT_NULL)
    {
        if (message->cs_take)
        {
            rt_pin_write(cs->pin, 0);
        }
        res = ald_spi_recv(hspi, (rt_uint8_t *)message->recv_buf, (rt_int32_t)message->length, SPITIMEOUT);
        if (message->cs_release)
        {
            rt_pin_write(cs->pin, 1);
        }
        if (res != RT_EOK)
            return RT_ERROR;
    }

    /* send & receive */
    else
    {
        if (message->cs_take)
        {
            rt_pin_write(cs->pin, 0);
        }
        res = ald_spi_send_recv(hspi, (rt_uint8_t *)message->send_buf, (rt_uint8_t *)message->recv_buf,
                                (rt_int32_t)message->length, SPITIMEOUT);
        if (message->cs_release)
        {
            rt_pin_write(cs->pin, 1);
        }
        if (res != RT_EOK)
            return RT_ERROR;
    }

    return message->length;
}

const struct rt_spi_ops es32f0_spi_ops =
{
    spi_configure,
    spixfer,
};

static struct rt_spi_bus _spi_bus0, _spi_bus1;
static spi_handle_t _spi0, _spi1;
int es32f0_spi_register_bus(SPI_TypeDef *SPIx, const char *name)
{
    struct rt_spi_bus *spi_bus;
    spi_handle_t *spi;
    gpio_init_t gpio_instruct;

    if (SPIx == SPI0)
    {
        _spi0.perh = SPI0;
        spi_bus = &_spi_bus0;
        spi = &_spi0;

        /* SPI0 gpio init */
        gpio_instruct.mode = GPIO_MODE_OUTPUT;
        gpio_instruct.odos = GPIO_PUSH_PULL;
        gpio_instruct.func = GPIO_FUNC_4;
        gpio_instruct.type = GPIO_TYPE_CMOS;
        gpio_instruct.flt  = GPIO_FILTER_DISABLE;

        /* PB3->SPI0_SCK, PB5->SPI0_MOSI */
        ald_gpio_init(GPIOB, GPIO_PIN_3 | GPIO_PIN_5, &gpio_instruct);

        /* PB4->SPI0_MISO */
        gpio_instruct.mode = GPIO_MODE_INPUT;
        ald_gpio_init(GPIOB, GPIO_PIN_4, &gpio_instruct);
    }
    else if (SPIx == SPI1)
    {
        _spi1.perh = SPI1;
        spi_bus = &_spi_bus1;
        spi = &_spi1;

        /* SPI1 gpio init */
        gpio_instruct.mode = GPIO_MODE_OUTPUT;
        gpio_instruct.odos = GPIO_PUSH_PULL;
        gpio_instruct.func = GPIO_FUNC_4;
        gpio_instruct.type = GPIO_TYPE_CMOS;
        gpio_instruct.flt  = GPIO_FILTER_DISABLE;

        /* PB13->SPI1_SCK, PB15->SPI1_MOSI */
        ald_gpio_init(GPIOB, GPIO_PIN_13 | GPIO_PIN_15, &gpio_instruct);

        /* PB14->SPI1_MISO */
        gpio_instruct.mode = GPIO_MODE_INPUT;
        ald_gpio_init(GPIOB, GPIO_PIN_14, &gpio_instruct);
    }
    else
    {
        return -1;
    }
    spi_bus->parent.user_data = spi;

    return rt_spi_bus_register(spi_bus, name, &es32f0_spi_ops);
}

rt_err_t es32f0_spi_device_attach(rt_uint32_t pin, const char *bus_name, const char *device_name)
{
    /* define spi Instance */
    struct rt_spi_device *spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    struct es32f0_hw_spi_cs *cs_pin = (struct es32f0_hw_spi_cs *)rt_malloc(sizeof(struct es32f0_hw_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->pin = pin;
    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_pin_write(pin, 1);
    return rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);
}

int rt_hw_spi_init(void)
{
    int result = 0;

#ifdef BSP_USING_SPI0
    result = es32f0_spi_register_bus(SPI0, "spi0");
#endif

#ifdef BSP_USING_SPI1
    result = es32f0_spi_register_bus(SPI1, "spi1");
#endif

    return result;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif
