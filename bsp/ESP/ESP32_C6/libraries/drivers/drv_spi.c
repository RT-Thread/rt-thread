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
/* ESP-IDF v6.1's driver/spi_master.h no longer pulls in the FreeRTOS headers,
 * but portMAX_DELAY below comes from FreeRTOS's portmacro.h. */
#include <freertos/FreeRTOS.h>

#include "drv_spi.h"
#include "drivers/dev_spi.h"

#ifdef RT_USING_SPI
#ifdef BSP_USING_SPI2
#define LOG_TAG "drv.spi"
#include <rtdbg.h>

static struct rt_spi_bus spi_bus2;

static spi_device_handle_t spi;
static spi_bus_config_t buscfg;

/*
 * Width of one data unit of the transaction, in bits. spi_transaction_t counts
 * length/rxlength in bits, so spixfer() needs this to size the transfer and to
 * know how wide the received units it copies out are.
 * Only 8-bit words are supported; spi_configure() rejects anything else.
 */
static rt_uint32_t spi_bits_per_word = 8;

/*
 * Receive staging array. driver/spi_master.h says of spi_transaction_t.rx_buffer
 * "Written by 4 bytes-unit if DMA is used", so the received bytes are taken into
 * an aligned array of our own and only message->length of them are handed to the
 * caller -- whose buffer may be any size and alignment. Sized for
 * buscfg.max_transfer_sz. Where those bytes come from is chip specific and told
 * where the chip decides it: see spi_configure().
 */
#define RT_ESP_SPI_MAX_RX_BYTES 4092
static rt_uint32_t spi_rx_units[(RT_ESP_SPI_MAX_RX_BYTES + 3) / 4] __attribute__((aligned(4)));

/*
 * Largest number of bytes one spi_transaction_t may carry. With DMA enabled
 * this is buscfg.max_transfer_sz; with SPI_DMA_DISABLED (C6) spi_common.c sets
 * bus_attr->max_transfer_sz to SOC_SPI_MAXIMUM_BUFFER_SIZE (64 on C6) and
 * spi_master.c rejects a longer transaction with ESP_ERR_INVALID_ARG, so
 * spixfer() splits longer messages into chunks and keeps CS asserted between
 * them.
 */
#ifdef SOC_ESP32_C6
#define RT_ESP_SPI_MAX_CHUNK_BYTES SOC_SPI_MAXIMUM_BUFFER_SIZE
#else
#define RT_ESP_SPI_MAX_CHUNK_BYTES RT_ESP_SPI_MAX_RX_BYTES
#endif

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
static rt_err_t spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration);
static rt_ssize_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message);

static struct rt_spi_ops esp32_spi_ops = {
    .configure = spi_configure,
    .xfer = spixfer,
};

static rt_err_t spi_configure(struct rt_spi_device *device,
                              struct rt_spi_configuration *configuration)
{
    if (configuration == NULL)
    {
        return -RT_EINVAL;
    }

    /* Validate the word width before touching the hardware. An unsupported
     * width must not leave an initialized SPI bus behind: a caller that asks
     * for 16 bits and then retries with 8 would otherwise hit
     * spi_bus_initialize()'s "bus already initialized" abort. */
    if (configuration->data_width != 8)
    {
        LOG_E("data width %u is not supported\n", (rt_uint32_t)configuration->data_width);
        return -RT_ENOSYS;
    }
    /* One RT-Thread byte is 8 bits of transaction: this is what length and
     * rxlength are counted in. */
    spi_bits_per_word = 8;

    static spi_bus_config_t buscfg = {
        .miso_io_num = SPI2_IOMUX_PIN_NUM_MISO,              /*MISO*/
        .mosi_io_num = SPI2_IOMUX_PIN_NUM_MOSI,              /*MOSI*/
        .sclk_io_num = SPI2_IOMUX_PIN_NUM_CLK,               /*CLK*/
        .quadwp_io_num = -1,                      /*不使用*/
        .quadhd_io_num = -1,                      /*不使用*/
        .max_transfer_sz = 4092                    /*最大传送数据长度*/
    };

    esp_err_t err;

#ifdef SOC_ESP32_C6
    /* SPI_DMA_DISABLED: this transfer does not go through GDMA, even though GDMA
       is in the image -- BSP_USING_SPI makes idf_port/SConscript compile this
       BSP's own src/gdma.c, because spi_common.c's SOC_GDMA_SUPPORTED section
       calls it. The received bytes are instead read out by spi_ll_read_buffer()
       (hal/esp32c6/include/hal/spi_ll.h:425), which memcpys the low byte of each
       32-bit data_buf word to the start of the buffer -- its length is
       (len + 7) / 8, which is 1 for an 8-bit word -- and that is what fills the
       staging array above. */
    err = spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_DISABLED);
#else
    err = spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
#endif /* SOC_ESP32_C6 */
    ESP_ERROR_CHECK(err);

    static spi_device_interface_config_t devcfg;

    LOG_W("configuration->max_hz = %d \n", configuration->max_hz);
    if (configuration->max_hz >= SPI_MASTER_FREQ_80M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_80M;    /*/< 80MHz*/
    }
    else if (configuration->max_hz >= SPI_MASTER_FREQ_40M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_40M;    /*/< 40MHz*/
    }
    else if (configuration->max_hz >= SPI_MASTER_FREQ_26M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_26M;    /*/< 26.67MHz*/
    }
    else if (configuration->max_hz >= SPI_MASTER_FREQ_20M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_20M;    /*/< 20MHz*/
    }
    else if (configuration->max_hz >= SPI_MASTER_FREQ_16M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_16M;    /*/< 16MHz*/
    }
    else if (configuration->max_hz >= SPI_MASTER_FREQ_13M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_13M;    /*/< 13.33MHz*/
    }
    else if (configuration->max_hz >= SPI_MASTER_FREQ_11M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_11M;    /*/< 11.43MHz*/
    }
    else if (configuration->max_hz >= SPI_MASTER_FREQ_10M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_10M;    /*/< 10MHz*/
    }
    else if (configuration->max_hz >= SPI_MASTER_FREQ_9M)
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_9M;    /*/< 8.89MHz*/
    }
    else
    {
        devcfg.clock_speed_hz = SPI_MASTER_FREQ_8M;
    }

    switch (configuration->mode)
    {
    case RT_SPI_MODE_0: /*!< CPOL = 0, CPHA = 0 */
        devcfg.mode = 0;
        break;
    case RT_SPI_MODE_1: /*!< CPOL = 0, CPHA = 1 */
        devcfg.mode = 1;
        break;
    case RT_SPI_MODE_2: /*!< CPOL = 1, CPHA = 0 */
        devcfg.mode = 2;
        break;
    case RT_SPI_MODE_3: /*!< CPOL = 1, CPHA = 1 */
        devcfg.mode = 3;
        break;
    default:
        devcfg.mode = 0;
        break;
    }

    /* todo: support changing cs_pin,queue_size or specifing spi_device_interface_config_t and
    * spi_transaction_t by resever data.Meanwhile finish the initialization of interrupt
    * callback function and dma.
    */

    devcfg.spics_io_num = SPI2_IOMUX_PIN_NUM_CS;
    devcfg.queue_size = 7;

    err = spi_bus_add_device(SPI2_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(err);

    /* Although there is only one spi bus object, it will be a template for other bsps of ESP32 series */
    for (int i = 0; i < sizeof(spi_bus_obj) / sizeof(spi_bus_obj[0]); i++)
    {
        spi_bus_obj[i].bus_name = "spi2";
        spi_bus_obj[i].spi_bus = &spi_bus2;
        spi_bus_obj[i].esp32_spi_bus_cfg = &buscfg;
    }

    return RT_EOK;
};

static rt_ssize_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    if (message->recv_buf != RT_NULL && message->length > sizeof(spi_rx_units))
    {
        LOG_E("rx length %u is larger than %u\n",
              (rt_uint32_t)message->length, (rt_uint32_t)RT_ESP_SPI_MAX_RX_BYTES);
        return -RT_EINVAL;
    }

    rt_size_t total = message->length;
    rt_size_t done = 0;
    static spi_transaction_t trans;

    spi_device_acquire_bus(spi, portMAX_DELAY);

    while (done < total)
    {
        rt_size_t chunk = total - done;
        if (chunk > RT_ESP_SPI_MAX_CHUNK_BYTES)
        {
            chunk = RT_ESP_SPI_MAX_CHUNK_BYTES;
        }

        /* Zeroed per chunk: this transaction is reused, and cmd/addr/flags/user
           left over from the previous one would be sent out again. */
        rt_memset(&trans, 0, sizeof(trans));

        trans.length = chunk * spi_bits_per_word;
        if (message->send_buf != RT_NULL)
        {
            trans.tx_buffer = (const rt_uint8_t *)message->send_buf + done;
        }

        if (message->recv_buf != RT_NULL)
        {
            /* The driver writes the received units into this 4-byte aligned
               array, not into the caller's buffer. */
            trans.rx_buffer = spi_rx_units;
            trans.rxlength = trans.length;
        }

        /* Hold CS across chunk boundaries; the last chunk lets the driver
           release it. The bus is acquired above, which is what allows the
           KEEP_ACTIVE flag in a polling transaction. */
        if (done + chunk < total)
        {
            trans.flags |= SPI_TRANS_CS_KEEP_ACTIVE;
        }

        esp_err_t err = spi_device_polling_transmit(spi, &trans);
        if (err != ESP_OK)
        {
            LOG_E("spi transfer failed at offset %u: %d\n",
                  (rt_uint32_t)done, err);
            spi_device_release_bus(spi);
            return -RT_EIO;
        }

        if (message->recv_buf != RT_NULL)
        {
            /* Verbatim: the aligned array holds the received bytes in the order
               they came off the bus, and only the count the caller asked for is
               copied. */
            rt_memcpy((rt_uint8_t *)message->recv_buf + done, spi_rx_units, chunk);
        }

        done += chunk;
    }

    spi_device_release_bus(spi);

    return total;
};

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    rt_device_t busp = RT_NULL;
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

    for (int i = 0; i < sizeof(spi_bus_obj) / sizeof(spi_bus_obj[0]); i++)
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
