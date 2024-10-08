/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-08     wumingzi      first implementation
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "rtdef.h"
#include "rttypes.h"
#include "sdkconfig.h"

#include "hal/spi_hal.h" /*bsp/ESP32_C3/packages/ESP-IDF-latest/components/hal/include/hal/spi_types.h*/
#include "driver/gpio.h" /*bsp/ESP32_C3/packages/ESP-IDF-latest/components/driver/include/driver/gpio.h*/
#include "driver/spi_master.h"

#include "drv_spi.h"

#ifdef RT_USING_SPI
#ifdef BSP_USING_SPI2
#define LOG_TAG     "drv.spi"
#include <rtdbg.h>

static struct rt_spi_bus spi_bus2;

static spi_device_handle_t spi;

static spi_bus_config_t buscfg;

static struct esp32_spi spi_bus_obj[] = {
#ifdef BSP_USING_SPI2
    {
        .bus_name = "spi2",
        .spi_bus = &spi_bus2,
        .esp32_spi_bus_cfg = &buscfg,
    },
#endif /* BSP_USING_SPI2 */
};

/* private rt-thread spi ops function */
static rt_err_t spi_configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration);
static rt_ssize_t spixfer(struct rt_spi_device* device, struct rt_spi_message* message);

static struct rt_spi_ops esp32_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer,
};

/**
* @brief SPI Initialization
* @param esp32_spi: SPI BUS
* @retval None
*/
static void esp32_spi_init(struct esp32_spi *esp32_spi)
{
    spi_configure(NULL,NULL);
}

static void spi_pin_mode(rt_base_t pin)
{
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << pin);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 1;
}

static rt_err_t spi_configure(struct rt_spi_device* device,
                          struct rt_spi_configuration* configuration)
{
    /* spi_pin_mode(RT_BSP_SPI_CS_PIN);*/
    static spi_bus_config_t buscfg =
    {
        .miso_io_num=SPI2_IOMUX_PIN_NUM_MISO,              /*MISO*/
        .mosi_io_num=SPI2_IOMUX_PIN_NUM_MOSI,              /*MOSI*/
        .sclk_io_num=SPI2_IOMUX_PIN_NUM_CLK,               /*CLK*/
        .quadwp_io_num=-1,                      /*不使用*/
        .quadhd_io_num=-1,                      /*不使用*/
        .max_transfer_sz=4092                    /*最大传送数据长度*/
    };

    esp_err_t err = spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(err);

    static spi_device_interface_config_t devcfg={
        .clock_speed_hz = SPI_MASTER_FREQ_8M,
        .mode = 0,
        .spics_io_num = RT_BSP_SPI_CS_PIN,
        .queue_size = 7,
    };

    err = spi_bus_add_device(SPI2_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(err);

    spi_bus_obj[0].bus_name = "spi2";
    spi_bus_obj[0].spi_bus = &spi_bus2;
    spi_bus_obj[0].esp32_spi_bus_cfg = &buscfg;

    return RT_EOK;
};

static rt_ssize_t spixfer(struct rt_spi_device* device, struct rt_spi_message* message)
{

    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    static spi_transaction_t trans;

    trans.tx_buffer = message->send_buf;
    trans.rx_buffer = message->recv_buf;
    trans.length = message->length;
    trans.rxlength = message->length;

    spi_device_acquire_bus(spi, portMAX_DELAY);
    esp_err_t err = spi_device_polling_transmit(spi, &trans);

    spi_device_release_bus(spi);

    ESP_ERROR_CHECK(err);
    return RT_EOK;
};

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;rt_device_t busp = RT_NULL;
    struct rt_spi_device *spi_device;

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

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
    int result = 0;

    spi_bus_obj[0].spi_bus->parent.user_data = (void *)&spi_bus_obj[0];
    result = rt_spi_bus_register(spi_bus_obj[0].spi_bus, spi_bus_obj[0].bus_name, &esp32_spi_ops);

    RT_ASSERT(result == RT_EOK);

    LOG_D("%s bus init done", spi_bus_obj[i].bus_name);

    return result;
}

INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* BSP_USING_SPI0 || BSP_USING_SPI1 || BSP_USING_SPI2 || BSP_USING_SPI3 || BSP_USING_SPI4*/
#endif /* RT_USING_SPI */
