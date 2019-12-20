/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-12     fanwenl      1st version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "wm_hostspi.h"
#include "wm_spi_hal.h"
#include "wm_io.h"
#include "wm_gpio_afsel.h"
#include "pin_map.h"
#include "drv_spi.h"

#ifdef BSP_USING_SPI

#define BSP_SPI_MAX_HZ (20* 1000 *1000)

struct wm_sw_spi_cs
{
    rt_int16_t pin;
};

struct wm_spi
{
    struct rt_spi_configuration *cfg;
};

static rt_err_t wm_hostspi_init(struct rt_spi_configuration *cfg)
{

    spi_clear_fifo();
    spi_set_endian(1);
    if (cfg->data_width == 8)
    {
        tls_spi_trans_type(SPI_BYTE_TRANSFER);
    }
    if (cfg->data_width == 16)
    {
        tls_spi_trans_type(SPI_WORD_TRANSFER);
    }
    spi_set_mode(cfg->mode);
    spi_set_chipselect_mode(SPI_CS_INACTIVE_MODE);
    spi_force_cs_out(1);
    if(cfg->max_hz > BSP_SPI_MAX_HZ)
    {
        cfg->max_hz = BSP_SPI_MAX_HZ;
    }
    spi_set_sclk(cfg->max_hz);

    spi_set_tx_trigger_level(0);
    spi_set_rx_trigger_level(7);

    spi_set_rx_channel(1);
    spi_set_tx_channel(1);

    return RT_EOK;
}

static rt_err_t spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(cfg != RT_NULL);
    RT_ASSERT(device != RT_NULL);

    /*将cfg参数放到device中*/
    struct wm_spi *hspi = (struct wm_spi *)device->bus->parent.user_data;
    hspi->cfg = cfg;

    wm_hostspi_init(cfg);

    return RT_EOK;
}

static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);

    struct wm_sw_spi_cs *cs = device->parent.user_data;

    struct tls_spi_transfer tls_transfer;

    tls_transfer.tx_buf = message->send_buf;
    tls_transfer.rx_buf = message->recv_buf;
    tls_transfer.len = message->length;

    rt_int32_t length = 0;
    rt_int32_t remain_length = message->length;
    rt_int32_t int_status;

    tls_irq_disable(SPI0_INT);

    length = spi_fill_txfifo(&tls_transfer, remain_length);
    spi_set_sclk_length(length * 8, 0);
    if (message->cs_take && cs)
    {
        tls_gpio_write((enum tls_io_name)cs->pin, 0);
    }
    spi_sclk_start();

    while (remain_length > 0)
    {
        while (spi_i2s_get_busy_status() == 1)
            ;
        length = spi_get_rxfifo(&tls_transfer, remain_length);
        remain_length -= length;

        if (remain_length == 0)
        {
            while (spi_i2s_get_busy_status() == 1)
                ;
            if (message->cs_release && cs)
            {
                tls_gpio_write((enum tls_io_name)cs->pin, 1);
            }
        }
        while (spi_i2s_get_busy_status() == 1)
            ;
        length = spi_fill_txfifo(&tls_transfer, remain_length);
        if (length)
        {
            spi_set_sclk_length(length * 8, 0);
            spi_sclk_start();
        }
    }

    while (spi_i2s_get_busy_status() == 1)
        ;
    if (message->cs_release && cs)
    {
        tls_gpio_write((enum tls_io_name)cs->pin, 1);
    }

    int_status = spi_get_int_status();
    spi_clear_int_status(int_status);
    tls_irq_enable(SPI0_INT);

    return message->length - remain_length;
}

rt_err_t wm_spi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint32_t pin)
{
    rt_err_t ret;
    rt_int16_t gpio_pin;
    struct rt_spi_device *spi_device;
    struct wm_sw_spi_cs *cs_pin;

    gpio_pin = wm_get_pin(pin);
    if (gpio_pin == WM_PIN_DEFAULT)
    {
        return -RT_ERROR;
    }
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    cs_pin = (struct wm_sw_spi_cs *)rt_malloc(sizeof(struct wm_sw_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);

    cs_pin->pin = gpio_pin;
    tls_gpio_cfg((enum tls_io_name)gpio_pin, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLHIGH);
    tls_gpio_write((enum tls_io_name)gpio_pin, 1);

    ret = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

    return ret;
}

static struct rt_spi_ops wm_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer
};

struct wm_spi spi;
struct rt_spi_bus wm_spi_bus;

int wm_hw_spi_bus_init(void)
{
    rt_int16_t gpio_pin;

    gpio_pin = wm_get_pin(WM_SPI_CK_PIN);
    if (gpio_pin >= 0)
    {
        wm_spi_ck_config((enum tls_io_name)gpio_pin);
    }
    gpio_pin = wm_get_pin(WM_SPI_DI_PIN);
    if (gpio_pin >= 0)
    {
        wm_spi_di_config((enum tls_io_name)gpio_pin);
    }
    gpio_pin = wm_get_pin(WM_SPI_DO_PIN);
    if (gpio_pin >= 0)
    {
        wm_spi_do_config((enum tls_io_name)gpio_pin);
    }

    wm_spi_bus.parent.user_data = &spi;
#ifdef WM_SPI_BUS_NAME
    rt_spi_bus_register(&wm_spi_bus, WM_SPI_BUS_NAME, &wm_spi_ops);
#else
    rt_spi_bus_register(&wm_spi_bus, "spi0", &wm_spi_ops);
#endif

    return RT_EOK;
}
INIT_PREV_EXPORT(wm_hw_spi_bus_init);

#endif /* BSP_USING_SPI */
