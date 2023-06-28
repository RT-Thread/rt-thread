/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-13     Lyons        first version
 * 2021-06-23     RiceChen     refactor
 */

#include <rthw.h>
#include <rtdevice.h>

#ifdef BSP_USING_SPI

#define LOG_TAG              "drv.spi"
#include <drv_log.h>

#include "fsl_iomuxc.h"
#include "drv_spi.h"

static struct imx6ull_spi_config spi_config[] =
{
#ifdef BSP_USING_SPI1
    SPI1_BUS_CONFIG,
#endif
#ifdef BSP_USING_SPI2
    SPI2_BUS_CONFIG,
#endif
#ifdef BSP_USING_SPI3
    SPI3_BUS_CONFIG,
#endif
#ifdef BSP_USING_SPI4
    SPI4_BUS_CONFIG,
#endif
};

static struct imx6ull_spi_bus spi_obj[sizeof(spi_config) / sizeof(spi_config[0])];

static rt_err_t imx6ull_ecspi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    struct imx6ull_spi_bus *spi_dev = RT_NULL;
    ecspi_master_config_t config;
    rt_uint32_t scr_clock = 0;

    spi_dev = (struct imx6ull_spi_bus *)(device->bus->parent.user_data);

    ECSPI_MasterGetDefaultConfig(&config);

    config.samplePeriod = 10;
    config.txFifoThreshold = 0;
    config.channelConfig.dataLineInactiveState = kECSPI_DataLineInactiveStateHigh;

    if (cfg->data_width == 8)
    {
        config.burstLength = 8;
    }
    else
    {
        return -RT_EINVAL;
    }

    if (cfg->mode & RT_SPI_SLAVE)
    {
        config.channelConfig.channelMode = kECSPI_Slave;
    }
    else
    {
        config.channelConfig.channelMode = kECSPI_Master;
    }

    if(cfg->mode & RT_SPI_CPHA)
    {
        config.channelConfig.phase = kECSPI_ClockPhaseSecondEdge;
    }
    else
    {
        config.channelConfig.phase = kECSPI_ClockPhaseFirstEdge;
    }

    if(cfg->mode & RT_SPI_CPOL)
    {
        config.channelConfig.polarity = kECSPI_PolarityActiveLow;
    }
    else
    {
        config.channelConfig.polarity = kECSPI_PolarityActiveHigh;
    }

    config.baudRate_Bps = cfg->max_hz;

    scr_clock = (CLOCK_GetPllFreq(kCLOCK_PllUsb1) / 8U);
    ECSPI_MasterInit(spi_dev->config->ECSPI, &config, scr_clock);
    return RT_EOK;
}

static rt_ssize_t imx6ull_ecspi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct imx6ull_spi_bus *spi_dev = RT_NULL;
    struct imx6ull_spi_cs *cs = RT_NULL;

    const rt_uint8_t *send_ptr = RT_NULL;
    rt_uint8_t *recv_ptr = RT_NULL;
    rt_uint16_t size = 0;
    rt_uint8_t temp_data;

    spi_dev = (struct imx6ull_spi_bus *)(device->bus->parent.user_data);
    cs = (struct imx6ull_spi_cs *)device->parent.user_data;

    recv_ptr = (rt_uint8_t *)message->recv_buf;
    send_ptr = (rt_uint8_t *)message->send_buf;
    size     = message->length;

    if(message->cs_take && cs)
    {
        rt_pin_write(cs->pin, PIN_LOW);
    }

    ECSPI_SetChannelSelect(spi_dev->config->ECSPI, kECSPI_Channel0);
    while (size--)
    {
        temp_data = (send_ptr != RT_NULL) ? (*send_ptr++) : 0xff;

        while (!(spi_dev->config->ECSPI->STATREG & ECSPI_STATREG_TE_MASK));
        ECSPI_WriteData(spi_dev->config->ECSPI, temp_data);

        while (!(spi_dev->config->ECSPI->STATREG & ECSPI_STATREG_RR_MASK));
        temp_data = ECSPI_ReadData(spi_dev->config->ECSPI);

        if (recv_ptr != RT_NULL)
        {
            *recv_ptr++ = temp_data;
        }
    }

    if(message->cs_release && cs)
    {
        rt_pin_write(cs->pin, PIN_HIGH);
    }

    return message->length;
}

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t pin)
{
    rt_err_t ret = RT_EOK;

    struct rt_spi_device *spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    struct imx6ull_spi_cs *cs_pin = (struct imx6ull_spi_cs *)rt_malloc(sizeof(struct imx6ull_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);

    cs_pin->pin = pin;
    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_pin_write(pin, PIN_HIGH);

    ret = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

    return ret;
}

static rt_err_t imx6ull_spi_gpio_init(struct imx6ull_spi_bus *bus)
{
    struct imx6ull_spi_bus *spi_bus = RT_NULL;

    spi_bus = (struct imx6ull_spi_bus *)bus;

    imx6ull_gpio_init(&spi_bus->config->clk_gpio);
    imx6ull_gpio_init(&spi_bus->config->miso_gpio);
    imx6ull_gpio_init(&spi_bus->config->mosi_gpio);

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_spi_ops imxrt_spi_ops =
{
    .configure = imx6ull_ecspi_configure,
    .xfer      = imx6ull_ecspi_xfer,
};
#endif

int rt_hw_spi_init(void)
{
    rt_uint16_t obj_num = 0;

    obj_num = sizeof(spi_config) / sizeof(spi_config[0]);

    for(int i = 0; i < obj_num; i++)
    {
        spi_obj[i].config = &spi_config[i];
        spi_obj[i].config->ECSPI = (ECSPI_Type *)imx6ull_get_periph_vaddr((rt_uint32_t)(spi_obj[i].config->ECSPI));
        imx6ull_spi_gpio_init(&spi_obj[i]);

        CLOCK_EnableClock(spi_obj[i].config->clk_ip_name);

        spi_obj[i].parent.parent.user_data = &spi_obj[i];
        rt_spi_bus_register(&spi_obj[i].parent, spi_obj[i].config->name, &imxrt_spi_ops);
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_spi_init);

#endif
