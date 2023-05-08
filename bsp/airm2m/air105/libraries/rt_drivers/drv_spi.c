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
#include "board.h"

#ifdef RT_USING_SPI

#if !defined(BSP_USING_HSPI0) && !defined(BSP_USING_SPI0) && !defined(BSP_USING_SPI1) && !defined(BSP_USING_SPI2) && !defined(BSP_USING_SPI0S)
    #error "Please define at least one BSP_USING_SPIx"
    /* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

#include "drv_spi.h"
#include "drv_config.h"
//#define DRV_DEBUG
#define LOG_TAG              "drv.spi"
#include <drv_log.h>

static struct air_spi spi_config[] =
{
#ifdef BSP_USING_HSPI0
    HSPI0_BUS_CONFIG,
#endif
#ifdef BSP_USING_SPI0
    SPI0_BUS_CONFIG,
#endif
#ifdef BSP_USING_SPI1
    SPI1_BUS_CONFIG,
#endif
#ifdef BSP_USING_SPI2
    SPI2_BUS_CONFIG,
#endif
#ifdef BSP_USING_SPI0S
    SPI0S_BUS_CONFIG,
#endif
};

static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    rt_uint32_t spi_id = device->bus->parent.user_data;
    rt_uint32_t cs_pin = device->parent.user_data;
    if (message->cs_take && !(device->config.mode & RT_SPI_NO_CS))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
            GPIO_Output(cs_pin, 1);
        else
            GPIO_Output(cs_pin, 0);
    }


    if (message->length)
    {
        LOG_D("spi%d 0x%X, 0x%X, %d",
                spi_id,
              (uint32_t)message->send_buf,
              (uint32_t)message->recv_buf, message->length);
        if (!message->send_buf)
        {
            SPI_BlockTransfer(spi_id, message->recv_buf, message->recv_buf, message->length);
        }
        else
        {
            SPI_BlockTransfer(spi_id, message->send_buf, message->recv_buf, message->length);
        }
        LOG_D("spi%d done", spi_id);
    }
    if (message->cs_release && !(device->config.mode & RT_SPI_NO_CS))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
            GPIO_Output(cs_pin, 0);
        else
            GPIO_Output(cs_pin, 1);
    }

    return message->length;
}

static rt_err_t spi_configure(struct rt_spi_device *device,
                              struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);
    rt_uint32_t spi_id = device->bus->parent.user_data;
    rt_uint8_t mode = configuration->mode & (RT_SPI_CPHA | RT_SPI_CPOL);
    if (configuration->mode & RT_SPI_SLAVE) return -RT_EINVAL;
    switch(spi_id)
    {
    case 0:
        GPIO_Iomux(GPIOC_12,3);
        GPIO_Iomux(GPIOC_13,3);
        GPIO_Iomux(GPIOC_15,3);
        break;
    case 1:
        GPIO_Iomux(GPIOB_12, 0);
        GPIO_Iomux(GPIOB_14, 0);
        GPIO_Iomux(GPIOB_15, 0);
        break;
    case 2:
        GPIO_Iomux(GPIOA_06,3);
        GPIO_Iomux(GPIOA_08,3);
        GPIO_Iomux(GPIOA_09,3);

        break;
    case 3:
        GPIO_Iomux(GPIOB_02,0);
        GPIO_Iomux(GPIOB_04,0);
        GPIO_Iomux(GPIOB_05,0);
        break;
    }
    SPI_MasterInit(spi_id, configuration->data_width, mode, configuration->max_hz, RT_NULL, RT_NULL);

    return RT_EOK;
}

static const struct rt_spi_ops air105_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer,
};

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint8_t cs_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    GPIO_Config(cs_pin, 0, 1);

    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    RT_ASSERT(result == RT_EOK);

    LOG_D("%s attach to %s done", device_name, bus_name);

    return result;
}


int rt_hw_spi_init(void)
{
    rt_err_t result;
    rt_size_t obj_num = sizeof(spi_config) / sizeof(struct air_spi);
    for (int spi_index = 0; spi_index < obj_num ; spi_index++)
    {
        result = rt_spi_bus_register(&(spi_config[spi_index].bus), spi_config[spi_index].bus_name, &air105_spi_ops);
        RT_ASSERT(result == RT_EOK);
        spi_config[spi_index].bus.parent.user_data = spi_config[spi_index].id;
    }
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);


#endif /* RT_USING_SPI */
