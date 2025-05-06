/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-08     wumingzi      first implementation
 * 2024-10-08     wumingzi      add custom configuration and support muti spi obj
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <time.h>

#include "rtdef.h"
#include "rttypes.h"
#include "sdkconfig.h"

#include "hal/spi_hal.h" /*bsp/ESP32_C3/packages/ESP-IDF-latest/components/hal/include/hal/spi_types.h*/
#include "driver/gpio.h" /*bsp/ESP32_C3/packages/ESP-IDF-latest/components/driver/include/driver/gpio.h*/
#include "driver/spi_master.h"

#include "drv_spi.h"
#include "drivers/dev_spi.h"

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

static rt_err_t spi_configure(struct rt_spi_device* device,
                          struct rt_spi_configuration* configuration)
{
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

    static spi_device_interface_config_t devcfg;
    if(configuration->data_width == 8)
    {
        size_t length;                  /*/< Total data length, in bits*/
        size_t rxlength;                /*/< Total data length received, should be not greater than ``length`` in full-duplex mode (0 defaults this to the value of ``length``)*/
    }

    LOG_W("configuration->max_hz = %d \n",configuration->max_hz);
    if(configuration->max_hz >= SPI_MASTER_FREQ_80M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_80M;    /*/< 80MHz*/
    }
    else if(configuration->max_hz >= SPI_MASTER_FREQ_40M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_40M;    /*/< 40MHz*/
    }
    else if(configuration->max_hz >= SPI_MASTER_FREQ_26M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_26M;    /*/< 26.67MHz*/
    }
    else if(configuration->max_hz >= SPI_MASTER_FREQ_20M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_20M;    /*/< 20MHz*/
    }
    else if(configuration->max_hz >= SPI_MASTER_FREQ_16M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_16M;    /*/< 16MHz*/
    }
    else if(configuration->max_hz >= SPI_MASTER_FREQ_13M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_13M;    /*/< 13.33MHz*/
    }
    else if(configuration->max_hz >= SPI_MASTER_FREQ_11M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_11M;    /*/< 11.43MHz*/
    }
    else if(configuration->max_hz >= SPI_MASTER_FREQ_10M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_10M;    /*/< 10MHz*/
    }
    else if(configuration->max_hz >= SPI_MASTER_FREQ_9M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_9M ;    /*/< 8.89MHz*/
    }
    else
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_8M ;
    }

    switch (configuration->mode)
    {
        case RT_SPI_MODE_0: /*!< CPOL = 0, CPHA = 0 */
            devcfg.mode = 0;
        case RT_SPI_MODE_1: /*!< CPOL = 0, CPHA = 1 */
            devcfg.mode = 1;
        case RT_SPI_MODE_2: /*!< CPOL = 1, CPHA = 0 */
            devcfg.mode = 2;
        case RT_SPI_MODE_3: /*!< CPOL = 1, CPHA = 1 */
            devcfg.mode = 3;
        default:
            devcfg.mode = 0;
    }

    /* todo: support changing cs_pin,queue_size or specifing spi_device_interface_config_t and
    * spi_transaction_t by resever data.Meanwhile finish the initialization of interrupt
    * callback function and dma.
    */

    devcfg.spics_io_num = RT_BSP_SPI_CS_PIN;
    devcfg.queue_size = 7;

    err = spi_bus_add_device(SPI2_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(err);

    /* Although there is only one spi bus object, it will be a template for other bsps of ESP32 series */
    for(int i = 0; i < sizeof(spi_bus_obj)/sizeof(spi_bus_obj[0]); i++)
    {
        spi_bus_obj[i].bus_name = "spi2";
        spi_bus_obj[i].spi_bus = &spi_bus2;
        spi_bus_obj[i].esp32_spi_bus_cfg = &buscfg;
    }

    return RT_EOK;
};

static rt_ssize_t spixfer(struct rt_spi_device* device, struct rt_spi_message* message)
{

    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    static spi_transaction_t trans;

    trans.tx_buffer = message->send_buf;
    trans.rx_buffer = message->recv_buf;
    trans.length = (message->length)*8;
    trans.rxlength = (message->length)*8;

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

    for(int i = 0; i < sizeof(spi_bus_obj)/sizeof(spi_bus_obj[0]); i++)
    {
        spi_bus_obj[i].spi_bus->parent.user_data = (void *)&spi_bus_obj[i];
        result = rt_spi_bus_register(spi_bus_obj[i].spi_bus, spi_bus_obj[i].bus_name, &esp32_spi_ops);

        RT_ASSERT(result == RT_EOK);

        LOG_D("%s bus init done", spi_bus_obj[i].bus_name);
    }

    return result;
}

INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* BSP_USING_SPI0 || BSP_USING_SPI1 || BSP_USING_SPI2 || BSP_USING_SPI3 || BSP_USING_SPI4*/
#endif /* RT_USING_SPI */