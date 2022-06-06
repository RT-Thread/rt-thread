/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-27     AHTYDHD      the first version
 */

#include "drv_spi.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/ssi.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#ifdef RT_USING_SPI

#if defined(BSP_USING_SPI0) || defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3)
/* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#include "tm4c123_config.h"
#include "spi_config.h"
#include <string.h>

//#define DRV_DEBUG
#define LOG_TAG              "drv.spi"
#include <drv_log.h>

enum
{
#ifdef BSP_USING_SPI0
    SPI0_INDEX,
#endif
#ifdef BSP_USING_SPI1
    SPI1_INDEX,
#endif
#ifdef BSP_USING_SPI2
    SPI2_INDEX,
#endif
#ifdef BSP_USING_SPI3
    SPI3_INDEX,
#endif
};

static struct tm4c123_spi_config spi_config[] =
{
#ifdef BSP_USING_SPI0
    SPI0_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI1
    SPI1_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI2
    SPI2_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI3
    SPI3_BUS_CONFIG,
#endif

};

static struct tm4c123_spi spi_bus_obj[sizeof(spi_config) / sizeof(spi_config[0])] = {0};

static rt_err_t tm4c123_spi_configure(struct tm4c123_spi *spi_drv, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(spi_drv != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uint32_t ui32Protocol, ui32Mode;
    uint32_t ui32BitRate = (uint32_t)cfg->max_hz;
    uint32_t ui32DataWidth = (uint32_t)cfg->data_width;
    uint32_t pui32DataRx[1];
    rt_uint8_t   ui8Protocol = 0;

    if (cfg->mode & RT_SPI_SLAVE)
    {
        ui32Mode = SSI_MODE_SLAVE;
    }
    else
    {
        ui32Mode = SSI_MODE_MASTER;
    }

    if (cfg->mode & RT_SPI_CPHA)
    {
        ui8Protocol += 1;
    }
    else
    {
        ui8Protocol += 0;
    }

    if (cfg->mode & RT_SPI_CPOL)
    {
        ui8Protocol += 2;
    }
    else
    {
        ui8Protocol += 0;
    }

    switch (ui8Protocol)
    {
    case 0:
        ui32Protocol =  SSI_FRF_MOTO_MODE_0;
        break;
    case 1:
        ui32Protocol =  SSI_FRF_MOTO_MODE_1;
        break;
    case 2:
        ui32Protocol =  SSI_FRF_MOTO_MODE_2;
        break;
    case 3:
        ui32Protocol =  SSI_FRF_MOTO_MODE_3;
        break;
    default:
        ui32Protocol =  SSI_FRF_MOTO_MODE_0;
        break;
    }

    SSIConfigSetExpClk(spi_drv->config->base, SysCtlClockGet(), ui32Protocol,
                       ui32Mode, ui32BitRate, ui32DataWidth);

    LOG_D("ssiclk freq: %d, SPI limiting freq: %d", SysCtlClockGet(), cfg->max_hz);

    SSIEnable(spi_drv->config->base);

    while (SSIDataGetNonBlocking(SSI0_BASE, &pui32DataRx[0]))
    {
    }

    LOG_D("%s init done", spi_drv->config->bus_name);

    return RT_EOK;
}

static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{

    rt_size_t message_length;
    rt_uint8_t *recv_buf;
    const rt_uint8_t *send_buf;
    uint32_t  ReadData = 0;
    int    i = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    struct tm4c123_spi *spi_drv =  rt_container_of(device->bus, struct tm4c123_spi, spi_bus);
    struct tm4c123_hw_spi_cs *cs = device->parent.user_data;

    if (message->cs_take)
    {
        GPIOPinWrite(cs->portbase, cs->GPIO_Pin, 0);
    }

    LOG_D("%s transfer prepare and start", spi_drv->config->bus_name);
    LOG_D("%s sendbuf: %X, recvbuf: %X, length: %d",
          spi_drv->config->bus_name,
          (uint32_t)message->send_buf,
          (uint32_t)message->recv_buf, message->length);

    message_length = message->length;
    recv_buf = message->recv_buf;
    send_buf = message->send_buf;

    if (message->send_buf && message->recv_buf)
    {
        for (i = 0; i < message_length; i++)
        {
            SSIDataPut(spi_drv->config->base, (uint32_t)send_buf[i]);
            while (SSIBusy(spi_drv->config->base))
            {
            }
            SSIDataGet(spi_drv->config->base, &ReadData);
            recv_buf[i] = (unsigned char)ReadData;
        }

    }
    else if (message->send_buf)
    {
        for (i = 0; i < message_length; i++)
        {
            SSIDataPut(spi_drv->config->base, (uint32_t)send_buf[i]);
            while (SSIBusy(spi_drv->config->base))
            {
            }
            SSIDataGet(spi_drv->config->base, &ReadData);
        }
    }
    else
    {
        for (i = 0; i < message_length; i++)
        {
            SSIDataPut(spi_drv->config->base, (uint32_t)0xff);
            while (SSIBusy(spi_drv->config->base))
            {
            }
            SSIDataGet(spi_drv->config->base, &ReadData);
            recv_buf[i] = (unsigned char)ReadData;
        }
    }

    LOG_D("%s transfer done", spi_drv->config->bus_name);

    if (message->cs_release)
    {
        GPIOPinWrite(cs->portbase, cs->GPIO_Pin, cs->GPIO_Pin);
    }

    return message->length;
}


static rt_err_t spi_configure(struct rt_spi_device *device,
                              struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    struct tm4c123_spi *spi_drv =  rt_container_of(device->bus, struct tm4c123_spi, spi_bus);
    spi_drv->cfg = configuration;

    return tm4c123_spi_configure(spi_drv, configuration);
}

static const struct rt_spi_ops tm4c123_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer,
};


static int rt_hw_spi_bus_init(void)
{
    rt_err_t result;
    for (int i = 0; i < sizeof(spi_config) / sizeof(spi_config[0]); i++)
    {
        spi_bus_obj[i].config = &spi_config[i];
        spi_bus_obj[i].spi_bus.parent.user_data = &spi_config[i];


        result = rt_spi_bus_register(&spi_bus_obj[i].spi_bus, spi_config[i].bus_name, &tm4c123_spi_ops);
        RT_ASSERT(result == RT_EOK);

        LOG_D("%s bus init done", spi_config[i].bus_name);
    }

    return result;
}

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, uint32_t portindex, uint32_t cs_gpiobase, uint32_t cs_gpio_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;
    struct tm4c123_hw_spi_cs *cs_pin;

    /* initialize the cs pin && select the slave*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA + portindex);
    GPIOPinTypeGPIOOutput(cs_gpiobase, cs_gpio_pin);
    GPIOPinWrite(cs_gpiobase, cs_gpio_pin, cs_gpio_pin);

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    cs_pin = (struct tm4c123_hw_spi_cs *)rt_malloc(sizeof(struct tm4c123_hw_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->portbase = cs_gpiobase;
    cs_pin->GPIO_Pin = cs_gpio_pin;
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
    spi_hw_config();

    return rt_hw_spi_bus_init();
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* defined(BSP_USING_SPI0) || defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3)  */
#endif  /*RT_USING_SPI*/

/************************** end of file ******************/
