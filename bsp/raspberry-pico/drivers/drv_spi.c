/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-27   Chushicheng    the first version
 */

#include "drv_spi.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/dma.h"

#ifdef BSP_USING_SPI
#define DBG_TAG              "drv.spi"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

struct pico_spi
{
    struct rt_spi_bus parent;
    spi_inst_t *handle;
    rt_uint8_t spi_rx_pin;
    rt_uint8_t spi_tx_pin;
    rt_uint8_t spi_sck_pin;
    rt_uint8_t spi_cs_pin;
    rt_uint8_t dma_tx;
    rt_uint8_t dma_rx;
    char *device_name;

};

static struct pico_spi pico_spi_obj[] =
{
#ifdef BSP_USING_SPI0
    {
        .handle = spi0,
        .spi_rx_pin  = BSP_SPI0_MISO_PIN,
        .spi_tx_pin  = BSP_SPI0_MOSI_PIN,
        .spi_sck_pin = BSP_SPI0_SCK_PIN,
        .spi_cs_pin  = BSP_SPI0_CS_PIN,
        .device_name = "spi0",
    },
#endif
#ifdef BSP_USING_SPI1
    {
        .handle = spi1,
        .spi_rx_pin  = BSP_SPI1_MISO_PIN,
        .spi_tx_pin  = BSP_SPI1_MOSI_PIN,
        .spi_sck_pin = BSP_SPI1_SCK_PIN,
        .spi_cs_pin  = BSP_SPI1_CS_PIN,
        .device_name = "spi1",
    },
#endif
};

static rt_err_t pico_spi_init(struct pico_spi *spi_drv, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(spi_drv != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    spi_inst_t *spi_handle = spi_drv->handle;
    spi_cpol_t  cpol;
    spi_cpha_t  cpha;
    rt_uint8_t  dma_transfer_size;

    if (cfg->mode & RT_SPI_SLAVE)
    {
        spi_set_slave(spi_handle, true);
    }
    else
    {
        spi_set_slave(spi_handle, false);
    }

    if (cfg->mode & RT_SPI_CPHA)
    {
        cpha = SPI_CPHA_1;
    }
    else
    {
        cpha = SPI_CPHA_0;
    }

    if (cfg->mode & RT_SPI_CPOL)
    {
        cpol = SPI_CPOL_1;
    }
    else
    {
        cpol = SPI_CPOL_0;
    }

    if (cfg->data_width >= 4
        && cfg->data_width <= 16)
    {
        spi_set_format(spi_handle, cfg->data_width, cpol, cpha, SPI_MSB_FIRST);
    }
    else
    {
        return -RT_EIO;
    }

    LOG_D("spi baudrate:%d", cfg->max_hz);
    spi_init(spi_handle, cfg->max_hz);
    gpio_set_function(spi_drv->spi_rx_pin, GPIO_FUNC_SPI);
    gpio_init(spi_drv->spi_cs_pin);
    gpio_set_function(spi_drv->spi_sck_pin, GPIO_FUNC_SPI);
    gpio_set_function(spi_drv->spi_tx_pin, GPIO_FUNC_SPI);
    // Make the SPI pins available to picotool
    bi_decl(bi_3pins_with_func(spi_drv->spi_rx_pin, spi_drv->spi_tx_pin, spi_drv->spi_sck_pin, GPIO_FUNC_SPI));
    // Make the CS pin available to picotool
    bi_decl(bi_1pin_with_name(spi_drv->spi_cs_pin, "SPI CS"));

    // Grab some unused dma channels
    spi_drv->dma_tx = dma_claim_unused_channel(true);
    spi_drv->dma_rx = dma_claim_unused_channel(true);
    /* DMA configuration */
    if(cfg->data_width == 8)
    {
        dma_transfer_size = DMA_SIZE_8;
    }
    else if(cfg->data_width == 16)
    {
        dma_transfer_size = DMA_SIZE_16;
    }
    else if(cfg->data_width == 32)
    {
        dma_transfer_size = DMA_SIZE_32;
    }
    dma_channel_config c = dma_channel_get_default_config(spi_drv->dma_tx);
    channel_config_set_transfer_data_size(&c, dma_transfer_size);
    channel_config_set_dreq(&c, spi_get_index(spi_handle) ? DREQ_SPI1_TX : DREQ_SPI0_TX);
    dma_channel_set_config(spi_drv->dma_tx, &c, false);

    c = dma_channel_get_default_config(spi_drv->dma_rx);
    channel_config_set_transfer_data_size(&c, dma_transfer_size);
    channel_config_set_dreq(&c, spi_get_index(spi_handle) ? DREQ_SPI1_RX : DREQ_SPI0_RX);
    channel_config_set_read_increment(&c, false);
    channel_config_set_write_increment(&c, true);
    dma_channel_set_config(spi_drv->dma_rx, &c, false);
    return RT_EOK;
}

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin)
{
    rt_err_t ret = RT_EOK;

    struct rt_spi_device *spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));

    ret = rt_spi_bus_attach_device_cspin(spi_device, device_name, bus_name, cs_pin, RT_NULL);

    return ret;
}

static rt_ssize_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    int i;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);

    struct pico_spi *spi = rt_container_of(device->bus, struct pico_spi, parent);

    if(message->cs_take && (device->cs_pin != PIN_NONE))
    {
        rt_pin_write(device->cs_pin, PIN_LOW);
    }

    dma_channel_config c = dma_get_channel_config(spi->dma_tx);
    dma_channel_configure(spi->dma_tx, &c,
                          &spi_get_hw(spi->handle)->dr, // write address
                          (uint8_t *)(message->send_buf), // read address
                          message->length, // element count (each element is of size transfer_data_size)
                          false); // don't start yet

    c = dma_get_channel_config(spi->dma_rx);
    dma_channel_configure(spi->dma_rx, &c,
                          (uint8_t *)(message->recv_buf), // write address
                          &spi_get_hw(spi->handle)->dr, // read address
                          message->length, // element count (each element is of size transfer_data_size)
                          false); // don't start yet

    dma_start_channel_mask((1u << spi->dma_tx) | (1u << spi->dma_rx));
    dma_channel_wait_for_finish_blocking(spi->dma_tx);
    dma_channel_wait_for_finish_blocking(spi->dma_rx);

    if(message->cs_release && (device->cs_pin != PIN_NONE))
    {
        rt_pin_write(device->cs_pin, PIN_HIGH);
    }

    return message->length;
}

static rt_err_t spi_configure(struct rt_spi_device *device,
                              struct rt_spi_configuration *configuration)
{
    rt_err_t ret = RT_EOK;
    struct pico_spi *spi = rt_container_of(device->bus, struct pico_spi, parent);
    ret = pico_spi_init(spi, configuration);

    return ret;
}

static const struct rt_spi_ops pico_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer,
};

int rt_hw_spi_init(void)
{
    int result = RT_EOK;

    for (rt_size_t i = 0; i < sizeof(pico_spi_obj) / sizeof(struct pico_spi); i++)
    {
        LOG_D("%s initing", pico_spi_obj[i].device_name);
        /* register spi device */
        if (rt_spi_bus_register(&pico_spi_obj[i].parent, pico_spi_obj[i].device_name, &pico_spi_ops) == RT_EOK)
        {
            LOG_D("%s init success", pico_spi_obj[i].device_name);
        }
        else
        {
            LOG_E("%s register failed", pico_spi_obj[i].device_name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* BSP_USING_SPI */
