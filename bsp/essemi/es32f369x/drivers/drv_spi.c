/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2020-01-14     wangyq        the first version
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

#define SPITIMEOUT 0xFFFF

rt_err_t spi_configure(struct rt_spi_device *device,
                       struct rt_spi_configuration *cfg)
{
    spi_handle_t *hspi;
    hspi = (spi_handle_t *)device->bus->parent.user_data;

    hspi->init.ss_en    = DISABLE;
    hspi->init.crc_calc = DISABLE;
    
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
    if (cfg->mode & RT_SPI_MSB)
    {
        hspi->init.first_bit = SPI_FIRSTBIT_MSB;
    }
    else
    {
        hspi->init.first_bit = SPI_FIRSTBIT_LSB;
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
    struct es32f3_hw_spi_cs *cs;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    
    hspi = (spi_handle_t *)device->bus->parent.user_data;
    cs = device->parent.user_data;

    if(message->send_buf != RT_NULL || message->recv_buf != RT_NULL)
    {
    /* send & receive */
    if ((message->send_buf != RT_NULL) && (message->recv_buf != RT_NULL))
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
    else
    {
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
    }

    }
    else
    {
         if (message->cs_take)
        {
            rt_pin_write(cs->pin, 0);
        }
        
        if (message->cs_release)
        {
            rt_pin_write(cs->pin, 1);
        }
            return RT_EOK;
    }
    return message->length;
}

const struct rt_spi_ops es32f3_spi_ops =
{
    spi_configure,
    spixfer,
};

rt_err_t es32f3_spi_device_attach(rt_uint32_t pin, const char *bus_name, const char *device_name)
{
    /* define spi Instance */
    struct rt_spi_device *spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    struct es32f3_hw_spi_cs *cs_pin = (struct es32f3_hw_spi_cs *)rt_malloc(sizeof(struct es32f3_hw_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->pin = pin;
    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_pin_write(pin, 1);
    return rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);
}

#ifdef BSP_USING_SPI0
    static struct rt_spi_bus _spi_bus0;
    static spi_handle_t _spi0;
#endif

#ifdef BSP_USING_SPI1
    static struct rt_spi_bus _spi_bus1;
    static spi_handle_t _spi1;
#endif

#ifdef BSP_USING_SPI2
    static struct rt_spi_bus _spi_bus2;
    static spi_handle_t _spi2;
#endif

int rt_hw_spi_init(void)
{
    int result = RT_EOK;

    struct rt_spi_bus *spi_bus;
    spi_handle_t *spi;
    gpio_init_t gpio_instruct;

#ifdef BSP_USING_SPI0
    _spi0.perh = SPI0;
    spi_bus = &_spi_bus0;
    spi = &_spi0;
    rt_device_t spi_bus_dev0;

    /* SPI0 gpio init */
    gpio_instruct.mode = GPIO_MODE_OUTPUT;
    gpio_instruct.odos = GPIO_PUSH_PULL;
    gpio_instruct.podrv = GPIO_OUT_DRIVE_1;
    gpio_instruct.nodrv = GPIO_OUT_DRIVE_1;
    gpio_instruct.func = GPIO_FUNC_4;
    gpio_instruct.type = GPIO_TYPE_TTL;
    gpio_instruct.flt  = GPIO_FILTER_DISABLE;

    /* PB3->SPI0_SCK, PB5->SPI0_MOSI */
    ald_gpio_init(GPIOB, GPIO_PIN_3 | GPIO_PIN_5, &gpio_instruct);

    /* PB4->SPI0_MISO */
    gpio_instruct.mode = GPIO_MODE_INPUT;
    ald_gpio_init(GPIOB, GPIO_PIN_4, &gpio_instruct);

    spi_bus->parent.user_data = spi;
    result = rt_spi_bus_register(spi_bus, "spi0", &es32f3_spi_ops);
    if (result != RT_EOK)
    {
        return result;
    }
    
    rt_device_register(spi_bus_dev0, "spi00", RT_DEVICE_FLAG_RDWR);
    
    /* SPI0_NSS = PA15 = PIN 50 */
    result = es32f3_spi_device_attach(50, "spi0", "spi00");
    
    if (result != RT_EOK)
    {
        return result;
    }
    
#endif

#ifdef BSP_USING_SPI1
    _spi1.perh = SPI1;
    spi_bus = &_spi_bus1;
    spi = &_spi1;
    rt_device_t spi_bus_dev0;

    /* SPI1 gpio init */
    gpio_instruct.mode = GPIO_MODE_OUTPUT;
    gpio_instruct.odos = GPIO_PUSH_PULL;
    gpio_instruct.podrv = GPIO_OUT_DRIVE_1;
    gpio_instruct.nodrv = GPIO_OUT_DRIVE_1;
    gpio_instruct.func = GPIO_FUNC_4;
    gpio_instruct.type = GPIO_TYPE_TTL;
    gpio_instruct.flt  = GPIO_FILTER_DISABLE;

    /* PC01->SPI1_SCK, PC03->SPI1_MOSI */
    ald_gpio_init(GPIOC, GPIO_PIN_1 | GPIO_PIN_3, &gpio_instruct);

    /* PC02->SPI1_MISO */
    gpio_instruct.mode = GPIO_MODE_INPUT;
    ald_gpio_init(GPIOC, GPIO_PIN_2, &gpio_instruct);

    spi_bus->parent.user_data = spi;
    result = rt_spi_bus_register(spi_bus, "spi1", &es32f3_spi_ops);
    if (result != RT_EOK)
    {
        return result;
    }
    
    rt_device_register(spi_bus_dev0, "spi10", RT_DEVICE_FLAG_RDWR);
    
    /* SPI1_NSS = PC00 = PIN 8 */
    result = es32f3_spi_device_attach(8, "spi1", "spi10");
    
    if (result != RT_EOK)
    {
        return result;
    }
    
#endif

#ifdef BSP_USING_SPI2
    _spi1.perh = SPI2;
    spi_bus = &_spi_bus2;
    spi = &_spi2;
    rt_device_t spi_bus_dev0;

    /* SPI2 gpio init */
    gpio_instruct.mode = GPIO_MODE_OUTPUT;
    gpio_instruct.odos = GPIO_PUSH_PULL;
    gpio_instruct.podrv = GPIO_OUT_DRIVE_1;
    gpio_instruct.nodrv = GPIO_OUT_DRIVE_1;
    gpio_instruct.func = GPIO_FUNC_5;
    gpio_instruct.type = GPIO_TYPE_TTL;
    gpio_instruct.flt  = GPIO_FILTER_DISABLE;

    /* PC05->SPI1_SCK, PB01->SPI1_MOSI */
    ald_gpio_init(GPIOC, GPIO_PIN_5 | GPIO_PIN_1, &gpio_instruct);

    /* PB00->SPI1_MISO */
    gpio_instruct.mode = GPIO_MODE_INPUT;
    ald_gpio_init(GPIOB, GPIO_PIN_0, &gpio_instruct);

    spi_bus->parent.user_data = spi;
    result = rt_spi_bus_register(spi_bus, "spi2", &es32f3_spi_ops);
    if (result != RT_EOK)
    {
        return result;
    }
    
    rt_device_register(spi_bus_dev0, "spi20", RT_DEVICE_FLAG_RDWR);
    
    /* SPI2_NSS = PC04 = PIN 24 */
    result = es32f3_spi_device_attach(39, "spi2", "spi20");
    
    if (result != RT_EOK)
    {
        return result;
    }
    
#endif
    return result;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif
