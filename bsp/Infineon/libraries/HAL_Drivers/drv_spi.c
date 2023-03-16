/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-18     Rbb666       first version
 */

#include <drv_spi.h>

#ifdef RT_USING_SPI

//#define DRV_DEBUG
#define DBG_TAG              "drv.spi"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

struct ifx_sw_spi_cs
{
    rt_uint32_t pin;
};

#ifdef BSP_USING_SPI3
    static struct rt_spi_bus spi_bus3;
#endif

static struct ifx_spi spi_bus_obj[] =
{
    #ifdef BSP_USING_SPI3
    {
        .bus_name = "spi3",
        .spi_bus = &spi_bus3,
        .sck_pin = GET_PIN(6, 2),
        .miso_pin = GET_PIN(6, 1),
        .mosi_pin = GET_PIN(6, 0),
    },
    #endif
};

/* private rt-thread spi ops function */
static rt_err_t spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration);
static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message);

static struct rt_spi_ops ifx_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer,
};

static void ifx_spi_init(struct ifx_spi *ifx_spi)
{
    int result = RT_EOK;

    result = cyhal_spi_init(ifx_spi->spi_obj, ifx_spi->mosi_pin, ifx_spi->miso_pin, ifx_spi->sck_pin,
                            NC, NULL, ifx_spi->spi_obj->data_bits, ifx_spi->spi_obj->mode, false);

    RT_ASSERT(result != RT_ERROR);

    rt_kprintf("[%s] Freq:[%d]HZ\n", ifx_spi->bus_name, ifx_spi->freq);

    result = cyhal_spi_set_frequency(ifx_spi->spi_obj, ifx_spi->freq);

    RT_ASSERT(result != CYHAL_SPI_RSLT_CLOCK_ERROR);
}

static rt_err_t spi_configure(struct rt_spi_device *device,
                              struct rt_spi_configuration *configuration)
{
    struct rt_spi_bus *spi_bus = (struct rt_spi_bus *)device->bus;
    struct ifx_spi *spi_device = (struct ifx_spi *)spi_bus->parent.user_data;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    /* data_width */
    if (configuration->data_width <= 8)
    {
        spi_device->spi_obj->data_bits = 8;
    }
    else if (configuration->data_width <= 16)
    {
        spi_device->spi_obj->data_bits = 16;
    }
    else
    {
        return -RT_EIO;
    }

    uint32_t max_hz;
    max_hz = configuration->max_hz;

    spi_device->freq = max_hz;

    /* MSB or LSB */
    switch (configuration->mode & RT_SPI_MODE_3)
    {
        case RT_SPI_MODE_0:
            spi_device->spi_obj->mode = CYHAL_SPI_MODE_00_MSB;
            break;

        case RT_SPI_MODE_1:
            spi_device->spi_obj->mode = CYHAL_SPI_MODE_01_MSB;
            break;

        case RT_SPI_MODE_2:
            spi_device->spi_obj->mode = CYHAL_SPI_MODE_10_MSB;
            break;

        case RT_SPI_MODE_3:
            spi_device->spi_obj->mode = CYHAL_SPI_MODE_11_MSB;
            break;
    }

    ifx_spi_init(spi_device);

    return RT_EOK;
}

static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    struct rt_spi_bus *spi_bus = (struct rt_spi_bus *)device->bus;
    struct ifx_spi *spi_device = (struct ifx_spi *)spi_bus->parent.user_data;

    struct rt_spi_configuration *config = &device->config;
    struct ifx_sw_spi_cs *cs = device->parent.user_data;

    /* take CS */
    if (message->cs_take)
    {
        cyhal_gpio_write(cs->pin, PIN_LOW);
        LOG_D("spi take cs\n");
    }

    int result = RT_EOK;

    if (message->length > 0)
    {
        if (message->send_buf == RT_NULL && message->recv_buf != RT_NULL)
        {
            /**< receive message */
            result = cyhal_spi_transfer(spi_device->spi_obj, RT_NULL, 0x00, message->recv_buf, message->length, 0x00);
        }
        else if (message->send_buf != RT_NULL && message->recv_buf == RT_NULL)
        {
            /**< send message */
            result = cyhal_spi_transfer(spi_device->spi_obj, message->send_buf, message->length, RT_NULL, 0x00, 0x00);
        }
        else if (message->send_buf != RT_NULL && message->recv_buf != RT_NULL)
        {
            /**< send and receive message */
            result = cyhal_spi_transfer(spi_device->spi_obj, message->send_buf, message->length, message->recv_buf, message->length, 0x00);
        }
    }

    if (message->cs_release && !(device->config.mode & RT_SPI_NO_CS))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
            cyhal_gpio_write(cs->pin, PIN_LOW);
        else
            cyhal_gpio_write(cs->pin, PIN_HIGH);
    }

    return message->length;
}

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, uint16_t cs_gpio_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;

    /* attach the device to spi bus */
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    struct ifx_sw_spi_cs *cs_pin = (struct ifx_sw_spi_cs *)rt_malloc(sizeof(struct ifx_sw_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);

    cs_pin->pin = cs_gpio_pin;

    if (cs_pin->pin != 0x00)
    {
        /* initialize the cs pin & select the slave*/
        cyhal_gpio_init(cs_pin->pin, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, 1);
        cyhal_gpio_write(cs_pin->pin, PIN_HIGH);
    }

    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

    RT_ASSERT(spi_device != RT_NULL);

    return result;
}

int rt_hw_spi_init(void)
{
    int result = RT_EOK;

    for (int i = 0; i < sizeof(spi_bus_obj) / sizeof(spi_bus_obj[0]); i++)
    {
        spi_bus_obj[i].spi_obj = rt_malloc(sizeof(cyhal_spi_t));

        RT_ASSERT(spi_bus_obj[i].spi_obj != RT_NULL);

        spi_bus_obj[i].spi_bus->parent.user_data = (void *)&spi_bus_obj[i];

        result = rt_spi_bus_register(spi_bus_obj[i].spi_bus, spi_bus_obj[i].bus_name, &ifx_spi_ops);

        RT_ASSERT(result == RT_EOK);

        LOG_D("%s bus init done", spi_bus_obj[i].bus_name);

        LOG_D("MOSI PIN:[%d], MISO PIN[%d], CLK PIN[%d]\n",
              spi_bus_obj[i].mosi_pin, spi_bus_obj[i].miso_pin,
              spi_bus_obj[i].sck_pin);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);
#endif /* RT_USING_SPI */
