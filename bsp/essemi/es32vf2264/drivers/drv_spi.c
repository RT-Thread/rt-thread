/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-11-01     wangyq        update libraries
 * 2020-01-14     wangyq        the first version
 * 2021-04-20     liuhy         the second version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include <rthw.h>
#include "board.h"
#include "drv_spi.h"


#ifdef RT_USING_SPI

#define SPITIMEOUT 0xFFF

rt_err_t spi_configure(struct rt_spi_device *device,
                       struct rt_spi_configuration *cfg)
{
    ald_spi_handle_t *hspi;
    hspi = (ald_spi_handle_t *)device->bus->parent.user_data;

    hspi->init.ss_en    = DISABLE;
    hspi->init.crc_calc = DISABLE;
    hspi->init.frame    = ALD_SPI_FRAME_MOTOROLA;

    /* config spi mode */
    if (cfg->mode & RT_SPI_SLAVE)
    {
        hspi->init.mode = ALD_SPI_MODE_SLAVER;
    }
    else
    {
        hspi->init.mode = ALD_SPI_MODE_MASTER;
    }
    if (cfg->mode & RT_SPI_3WIRE)
    {
        hspi->init.dir = ALD_SPI_DIRECTION_1LINE;
    }
    else
    {
        hspi->init.dir = ALD_SPI_DIRECTION_2LINES;
    }
    if (cfg->data_width == 8)
    {
        hspi->init.data_size = ALD_SPI_DATA_SIZE_8;
    }
    else if (cfg->data_width == 16)
    {
        hspi->init.data_size = ALD_SPI_DATA_SIZE_16;
    }

    if (cfg->mode & RT_SPI_CPHA)
    {
        hspi->init.phase = ALD_SPI_CPHA_SECOND;
    }
    else
    {
        hspi->init.phase = ALD_SPI_CPHA_FIRST;
    }
    if (cfg->mode & RT_SPI_MSB)
    {
        hspi->init.first_bit = ALD_SPI_FIRSTBIT_MSB;
    }
    else
    {
        hspi->init.first_bit = ALD_SPI_FIRSTBIT_LSB;
    }

    if (cfg->mode & RT_SPI_CPOL)
    {
        hspi->init.polarity = ALD_SPI_CPOL_HIGH;
    }
    else
    {
        hspi->init.polarity = ALD_SPI_CPOL_LOW;
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
    if (cfg->max_hz >= ald_cmu_get_pclk_clock() / 2)
    {
        hspi->init.baud = ALD_SPI_BAUD_2;
    }
    else if (cfg->max_hz >= ald_cmu_get_pclk_clock() / 4)
    {
        hspi->init.baud = ALD_SPI_BAUD_4;
    }
    else if (cfg->max_hz >= ald_cmu_get_pclk_clock() / 8)
    {
        hspi->init.baud = ALD_SPI_BAUD_8;
    }
    else if (cfg->max_hz >= ald_cmu_get_pclk_clock() / 16)
    {
        hspi->init.baud = ALD_SPI_BAUD_16;
    }
    else if (cfg->max_hz >= ald_cmu_get_pclk_clock() / 32)
    {
        hspi->init.baud = ALD_SPI_BAUD_32;
    }
    else if (cfg->max_hz >= ald_cmu_get_pclk_clock() / 64)
    {
        hspi->init.baud = ALD_SPI_BAUD_64;
    }
    else if (cfg->max_hz >= ald_cmu_get_pclk_clock() / 128)
    {
        hspi->init.baud = ALD_SPI_BAUD_128;
    }
    else
    {
        hspi->init.baud = ALD_SPI_BAUD_256;
    }
    ALD_SPI_DISABLE(hspi);
    ald_spi_init(hspi);
    return RT_EOK;
}

static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_err_t res;
    ald_spi_handle_t *hspi;
    struct es32f3_hw_spi_cs *cs;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);

    hspi = (ald_spi_handle_t *)device->bus->parent.user_data;
    cs = device->parent.user_data;

    if (message->cs_take)
        {
            rt_pin_write(cs->pin, ES_SPI_CS_LEVEL);
        }

    if(message->send_buf != RT_NULL || message->recv_buf != RT_NULL)
    {
    /* send & receive */
    if ((message->send_buf != RT_NULL) && (message->recv_buf != RT_NULL))
    {
        res = ald_spi_send_recv(hspi, (rt_uint8_t *)message->send_buf, (rt_uint8_t *)message->recv_buf,
                                (rt_int32_t)message->length, SPITIMEOUT);
    }
    else
    {
        /* only send data */
        if (message->recv_buf == RT_NULL)
        {
            res = ald_spi_send(hspi, (rt_uint8_t *)message->send_buf, (rt_int32_t)message->length, SPITIMEOUT);
        }
        /* only receive data */
        if (message->send_buf == RT_NULL)
        {
            res = ald_spi_recv(hspi, (rt_uint8_t *)message->recv_buf, (rt_int32_t)message->length, SPITIMEOUT);
        }
    }

     if (message->cs_release)
     {
        rt_pin_write(cs->pin, !ES_SPI_CS_LEVEL);
     }

     if (res != RT_EOK)
         return RT_ERROR;
     else
         return message->length;

    }
    else
    {

        if (message->cs_release)
        {
            rt_pin_write(cs->pin, !ES_SPI_CS_LEVEL);
        }
            return RT_EOK;
    }

}
const struct rt_spi_ops es32f3_spi_i2s_ops =
{
    RT_NULL,
    RT_NULL,
};
const struct rt_spi_ops es32f3_spi_ops =
{
    spi_configure,
    spixfer,
};

rt_err_t es32f3_spi_device_attach(rt_uint32_t pin, const char *bus_name, const char *device_name)
{
    int result;
    /* define spi Instance */
    struct rt_spi_device *spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    struct es32f3_hw_spi_cs *cs_pin = (struct es32f3_hw_spi_cs *)rt_malloc(sizeof(struct es32f3_hw_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->pin = pin;
    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_pin_write(pin, 1);

    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

#ifdef BSP_USING_SPI0
    if(!(strcmp(bus_name,ES_DEVICE_NAME_SPI0_BUS)))SPI_BUS_CONFIG(spi_device->config,0);
#endif
#ifdef BSP_USING_SPI1
    if(!(strcmp(bus_name,ES_DEVICE_NAME_SPI1_BUS)))SPI_BUS_CONFIG(spi_device->config,1);
#endif
#ifdef BSP_USING_SPI2
    if(!(strcmp(bus_name,ES_DEVICE_NAME_SPI2_BUS)))SPI_BUS_CONFIG(spi_device->config,2);
#endif

    return result;
}

#ifdef BSP_USING_SPI0
    static struct rt_spi_bus _spi_bus0;
    static ald_spi_handle_t _spi0;
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
    ald_spi_handle_t *spi;
    ald_gpio_init_t gpio_instruct;

    gpio_instruct.pupd = ALD_GPIO_PUSH_UP_DOWN;
    gpio_instruct.od = ALD_GPIO_PUSH_PULL;
    gpio_instruct.odrv = ALD_GPIO_OUT_DRIVE_NORMAL;
    gpio_instruct.type = ALD_GPIO_TYPE_CMOS;
    gpio_instruct.flt  = ALD_GPIO_FILTER_DISABLE;

#ifdef BSP_USING_SPI0
    _spi0.perh = SPI0;
    spi_bus = &_spi_bus0;
    spi = &_spi0;
    /* SPI0 gpio init */
    gpio_instruct.mode = ALD_GPIO_MODE_OUTPUT;

#if  defined(ES_SPI0_SCK_GPIO_FUNC)&&defined(ES_SPI0_SCK_GPIO_PORT)&&defined(ES_SPI0_SCK_GPIO_PIN)
    gpio_instruct.func = ES_SPI0_SCK_GPIO_FUNC;
    ald_gpio_init(ES_SPI0_SCK_GPIO_PORT, ES_SPI0_SCK_GPIO_PIN, &gpio_instruct);
#endif

#if  defined(ES_SPI0_MOSI_GPIO_FUNC)&&defined(ES_SPI0_MOSI_GPIO_PORT)&&defined(ES_SPI0_MOSI_GPIO_PIN)
    gpio_instruct.func = ES_SPI0_MOSI_GPIO_FUNC;
    ald_gpio_init(ES_SPI0_MOSI_GPIO_PORT, ES_SPI0_MOSI_GPIO_PIN, &gpio_instruct);
#endif

#if !defined(ES_SPI0_I2S_MODE)
    gpio_instruct.mode = ALD_GPIO_MODE_INPUT;
#endif

#if  defined(ES_SPI0_MISO_GPIO_FUNC)&&defined(ES_SPI0_MISO_GPIO_PORT)&&defined(ES_SPI0_MISO_GPIO_PIN)
    gpio_instruct.func = ES_SPI0_MISO_GPIO_FUNC;
    ald_gpio_init(ES_SPI0_MISO_GPIO_PORT, ES_SPI0_MISO_GPIO_PIN, &gpio_instruct);
#endif

#if defined(ES_SPI0_I2S_MODE)&&defined(ES_SPI0_NSS_GPIO_FUNC)&&defined(ES_SPI0_NSS_GPIO_PORT)&&defined(ES_SPI0_NSS_GPIO_PIN)
    gpio_instruct.func = ES_SPI0_NSS_GPIO_FUNC;
    ald_gpio_init(ES_SPI0_NSS_GPIO_PORT, ES_SPI0_NSS_GPIO_PIN, &gpio_instruct);
#endif

    spi_bus->parent.user_data = spi;
    #if defined(ES_SPI0_I2S_MODE)
    result = rt_spi_bus_register(spi_bus, ES_DEVICE_NAME_SPI0_BUS, &es32f3_spi_i2s_ops);
    #else
    result = rt_spi_bus_register(spi_bus, ES_DEVICE_NAME_SPI0_BUS, &es32f3_spi_ops);
    if (result != RT_EOK)
    {
        return result;
    }

    result = es32f3_spi_device_attach(ES_SPI0_NSS_PIN, ES_DEVICE_NAME_SPI0_BUS, ES_DEVICE_NAME_SPI0_DEV0);

    if (result != RT_EOK)
    {
        return result;
    }
    #endif

#endif

#ifdef BSP_USING_SPI1
    _spi1.perh = SPI1;
    spi_bus = &_spi_bus1;
    spi = &_spi1;

    /* SPI1 gpio init */
    gpio_instruct.mode = GPIO_MODE_OUTPUT;

#if  defined(ES_SPI1_SCK_GPIO_FUNC)&&defined(ES_SPI1_SCK_GPIO_PORT)&&defined(ES_SPI1_SCK_GPIO_PIN)
    gpio_instruct.func = ES_SPI1_SCK_GPIO_FUNC;
    ald_gpio_init(ES_SPI1_SCK_GPIO_PORT, ES_SPI1_SCK_GPIO_PIN, &gpio_instruct);
#endif

#if  defined(ES_SPI1_MOSI_GPIO_FUNC)&&defined(ES_SPI1_MOSI_GPIO_PORT)&&defined(ES_SPI1_MOSI_GPIO_PIN)
    gpio_instruct.func = ES_SPI1_MOSI_GPIO_FUNC;
    ald_gpio_init(ES_SPI1_MOSI_GPIO_PORT, ES_SPI1_MOSI_GPIO_PIN, &gpio_instruct);
#endif

#if !defined(ES_SPI1_I2S_MODE)
    gpio_instruct.mode = GPIO_MODE_INPUT;
#endif

#if  defined(ES_SPI1_MISO_GPIO_FUNC)&&defined(ES_SPI1_MISO_GPIO_PORT)&&defined(ES_SPI1_MISO_GPIO_PIN)
    gpio_instruct.func = ES_SPI1_MISO_GPIO_FUNC;
    ald_gpio_init(ES_SPI1_MISO_GPIO_PORT, ES_SPI1_MISO_GPIO_PIN, &gpio_instruct);
#endif

#if defined(ES_SPI1_I2S_MODE)&&defined(ES_SPI1_NSS_GPIO_FUNC)&&defined(ES_SPI1_NSS_GPIO_PORT)&&defined(ES_SPI1_NSS_GPIO_PIN)
    gpio_instruct.func = ES_SPI1_NSS_GPIO_FUNC;
    ald_gpio_init(ES_SPI1_NSS_GPIO_PORT, ES_SPI1_NSS_GPIO_PIN, &gpio_instruct);
#endif

    spi_bus->parent.user_data = spi;
    #if defined(ES_SPI1_I2S_MODE)
    result = rt_spi_bus_register(spi_bus, ES_DEVICE_NAME_SPI1_BUS, &es32f3_spi_i2s_ops);
    #else
    result = rt_spi_bus_register(spi_bus, ES_DEVICE_NAME_SPI1_BUS, &es32f3_spi_ops);
    if (result != RT_EOK)
    {
        return result;
    }

    result = es32f3_spi_device_attach(ES_SPI1_NSS_PIN, ES_DEVICE_NAME_SPI1_BUS, ES_DEVICE_NAME_SPI1_DEV0);

    if (result != RT_EOK)
    {
        return result;
    }
    #endif
#endif

#ifdef BSP_USING_SPI2
    _spi2.perh = SPI2;
    spi_bus = &_spi_bus2;
    spi = &_spi2;

    /* SPI2 gpio init */
    gpio_instruct.mode = GPIO_MODE_OUTPUT;

#if  defined(ES_SPI2_SCK_GPIO_FUNC)&&defined(ES_SPI2_SCK_GPIO_PORT)&&defined(ES_SPI2_SCK_GPIO_PIN)
    gpio_instruct.func = ES_SPI2_SCK_GPIO_FUNC;
    ald_gpio_init(ES_SPI2_SCK_GPIO_PORT, ES_SPI2_SCK_GPIO_PIN, &gpio_instruct);
#endif

#if  defined(ES_SPI2_MOSI_GPIO_FUNC)&&defined(ES_SPI2_MOSI_GPIO_PORT)&&defined(ES_SPI2_MOSI_GPIO_PIN)
    gpio_instruct.func = ES_SPI2_MOSI_GPIO_FUNC;
    ald_gpio_init(ES_SPI2_MOSI_GPIO_PORT, ES_SPI2_MOSI_GPIO_PIN, &gpio_instruct);
#endif

#if !defined(ES_SPI2_I2S_MODE)
    gpio_instruct.mode = GPIO_MODE_INPUT;
#endif

#if  defined(ES_SPI2_MISO_GPIO_FUNC)&&defined(ES_SPI2_MISO_GPIO_PORT)&&defined(ES_SPI2_MISO_GPIO_PIN)
    gpio_instruct.func = ES_SPI2_MISO_GPIO_FUNC;
    ald_gpio_init(ES_SPI2_MISO_GPIO_PORT, ES_SPI2_MISO_GPIO_PIN, &gpio_instruct);
#endif

#if defined(ES_SPI2_I2S_MODE)&&defined(ES_SPI2_NSS_GPIO_FUNC)&&defined(ES_SPI2_NSS_GPIO_PORT)&&defined(ES_SPI2_NSS_GPIO_PIN)
    gpio_instruct.func = ES_SPI2_NSS_GPIO_FUNC;
    ald_gpio_init(ES_SPI2_NSS_GPIO_PORT, ES_SPI2_NSS_GPIO_PIN, &gpio_instruct);
#endif

    spi_bus->parent.user_data = spi;
    #if defined(ES_SPI2_I2S_MODE)
    result = rt_spi_bus_register(spi_bus, ES_DEVICE_NAME_SPI0_BUS, &es32f3_spi_i2s_ops);
    #else
    result = rt_spi_bus_register(spi_bus, ES_DEVICE_NAME_SPI2_BUS, &es32f3_spi_ops);
    if (result != RT_EOK)
    {
        return result;
    }

    result = es32f3_spi_device_attach(ES_SPI2_NSS_PIN, ES_DEVICE_NAME_SPI2_BUS, ES_DEVICE_NAME_SPI1_DEV0);

    if (result != RT_EOK)
    {
        return result;
    }
    #endif
#endif
    return result;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif
