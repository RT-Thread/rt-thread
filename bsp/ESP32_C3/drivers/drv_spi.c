/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-20     BruceOu      first implementation
 */
#include "drv_spi.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <time.h>
#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "hal/spi_hal.h"
#include "rtdef.h"
#include "rttypes.h"
#include "sdkconfig.h"
#include "soc/spi_struct.h"
#include "/home/lzx/myrtt/rt-thread/bsp/ESP32_C3/rtconfig.h"

#include "/home/lzx/myrtt/rt-thread/bsp/ESP32_C3/packages/ESP-IDF-latest/components/soc/esp32c3/include/soc/spi_pins.h"
#include "/home/lzx/myrtt/rt-thread/bsp/ESP32_C3/packages/ESP-IDF-latest/components/hal/include/hal/spi_types.h"
#include "/home/lzx/myrtt/rt-thread/bsp/ESP32_C3/idf_port/include/freertos/portmacro.h"
#include "/home/lzx/myrtt/rt-thread/bsp/ESP32_C3/packages/ESP-IDF-latest/components/hal/include/hal/gpio_types.h"
#include "/home/lzx/myrtt/rt-thread/bsp/ESP32_C3/packages/ESP-IDF-latest/components/driver/include/driver/gpio.h"

#if defined(BSP_USING_SPI2)
#define LOG_TAG              "drv.spi"
#include <rtdbg.h>

#define RT_USING_SPI
#define BSP_USING_SPI2

#ifdef RT_USING_SPI
#ifdef BSP_USING_SPI2

#endif

static struct rt_spi_bus spi_bus2;

// spi_hal_trans_config_t esp32_spi_cfg;

// spi_hal_context_t hal[] = {
//     {
//         .dmadesc_tx = NULL,
//         .dmadesc_rx = NULL,  
//         .hw = &SPI2,       
//         .dma_in = NULL,   
//         .dma_out = NULL,  
//         .dma_enabled = false,       
//         .tx_dma_chan = 0,    
//         .rx_dma_chan = 0,    
//         .dmadesc_n = 0,           

//         /* Internal parameters, don't touch */
//         esp32_spi_cfg,
//     },
// };

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

static void cs_high(spi_transaction_t* t)
{
    gpio_set_level(RT_BSP_SPI_CS_PIN, 1);
}

static void cs_low(spi_transaction_t* t)
{
    gpio_set_level(RT_BSP_SPI_CS_PIN, 0);
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
    spi_pin_mode(RT_BSP_SPI_CS_PIN);
    static spi_bus_config_t buscfg = 
    {
        .miso_io_num=SPI2_IOMUX_PIN_NUM_MISO,              //MISO
        .mosi_io_num=SPI2_IOMUX_PIN_NUM_MOSI,              //MOSI
        .sclk_io_num=SPI2_IOMUX_PIN_NUM_CLK,               //CLK
        .quadwp_io_num=-1,                      //不使用
        .quadhd_io_num=-1,                      //不使用
        .max_transfer_sz=4092                    //最大传送数据长度
    };
    rt_kprintf("line=%d func=%s\n",__LINE__,__FUNCTION__);

    esp_err_t err = spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO); 
    ESP_ERROR_CHECK(err);
    rt_kprintf("line=%d func=%s\n",__LINE__,__FUNCTION__);

    static spi_device_interface_config_t devcfg={
        .clock_speed_hz = SPI_MASTER_FREQ_8M,
        .mode = 0,
        .spics_io_num = RT_BSP_SPI_CS_PIN,
        .queue_size = 7,
        //.pre_cb = cs_low,
        //.post_cb = cs_high,
    };
    rt_kprintf("line=%d func=%s\n",__LINE__,__FUNCTION__);

    err = spi_bus_add_device(SPI2_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(err);
    rt_kprintf("line=%d func=%s\n",__LINE__,__FUNCTION__);

    spi_bus_obj[0].bus_name = "spi2";
    spi_bus_obj[0].spi_bus = &spi_bus2;
    spi_bus_obj[0].esp32_spi_bus_cfg = &buscfg;

    return RT_EOK;
};

static rt_ssize_t spixfer(struct rt_spi_device* device, struct rt_spi_message* message)
{
    // struct rt_spi_bus * esp32_spi_bus = (struct rt_spi_bus *)device->bus;
    // struct esp32_spi *spi_device = (struct esp32_spi *)esp32_spi_bus->parent.user_data;
    // struct rt_spi_configuration * config = &device->config;
    // struct esp32_spi_cs * esp32_spi_cs = device->parent.user_data;
    rt_kprintf("line=%d func=%s\n",__LINE__,__FUNCTION__);

    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    // rt_uint8_t* sb = (rt_uint8_t* )(message->send_buf);
    // rt_uint8_t *rb = (rt_uint8_t*)(message->recv_buf);
    // rt_kprintf("tx_buffer=%x rx_buffer=%x%x\n",*sb,(rb)[3],(rb)[4]);
// rt_kprintf("tx_buffer=%x rx_buffer=%x%x\n",*sb,rb[3],rb[4]);

    static spi_transaction_t trans;
    // spi_transaction_t* trans_queue[1];
    // trans_queue[0] = &trans;  
    
    // if(rb == RT_NULL)
    // {
    //     rt_kprintf("rb is null ! line=%d func=%s\n",__LINE__,__FUNCTION__);
    // }

    trans.tx_buffer = message->send_buf;
    trans.rx_buffer = message->recv_buf;
    trans.length = message->length;
    trans.rxlength = message->length;
    
    if(trans.rx_buffer == RT_NULL || trans.tx_buffer == RT_NULL)
    {
        rt_kprintf("trans.rx_buffer == RT_NULL || trans.tx_buffer == RT_NULL! line=%d func=%s\n",__LINE__,__FUNCTION__);
    }

    rt_kprintf("line=%d func=%s\n",__LINE__,__FUNCTION__);
    esp_err_t buserr = spi_device_acquire_bus(spi, portMAX_DELAY);
    if(buserr != ESP_OK)
    {
        rt_kprintf("buserr != ESP_OK  line=%d func=%s\n",__LINE__,__FUNCTION__);

    }
     //cs_low(&trans);
    esp_err_t err = spi_device_polling_transmit(spi, &trans);
    rt_kprintf("rxdata=%x\n",*(rt_uint8_t*)trans.rx_buffer);
     //cs_high(&trans);
    
    //esp_err_t err = spi_device_queue_trans(spi, &trans, portMAX_DELAY);
    // spi_device_get_trans_result(spi, trans_queue, 1000);

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
    rt_kprintf("line=%d func=%s\n",__LINE__,__FUNCTION__);

    rt_err_t result;rt_device_t busp = RT_NULL;
    struct rt_spi_device *spi_device;

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    // if(cs_pin != PIN_NONE)
    // {
    //     /* initialize the cs pin && select the slave*/
    //     rt_pin_mode(cs_pin, PIN_MODE_OUTPUT);
    //     rt_pin_write(cs_pin, PIN_HIGH);
    // }
    rt_kprintf("line=%d func=%s\n",__LINE__,__FUNCTION__);

    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d\n", device_name, bus_name, result);
        

    }
    rt_kprintf("line=%d func=%s\n",__LINE__,__FUNCTION__);

    RT_ASSERT(result == RT_EOK);

    LOG_D("%s attach to %s done", device_name, bus_name);

    return result;
}

int rt_hw_spi_init(void)
{
    int result = 0;
    // int i;

    // for (i = 0; i < sizeof(spi_bus_obj) / sizeof(spi_bus_obj[0]); i++)
    // {
        // spi_bus_obj[i].spi_bus->parent.user_data = (void *)&spi_bus_obj[i];
    rt_kprintf("line=%d func=%s\n",__LINE__,__FUNCTION__);
        spi_bus_obj[0].spi_bus->parent.user_data = (void *)&spi_bus_obj[0];
        result = rt_spi_bus_register(spi_bus_obj[0].spi_bus, spi_bus_obj[0].bus_name, &esp32_spi_ops);
    rt_kprintf("line=%d func=%s\n",__LINE__,__FUNCTION__);

        RT_ASSERT(result == RT_EOK);

        LOG_D("%s bus init done", spi_bus_obj[i].bus_name);
    // }

    return result;
}

INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* BSP_USING_SPI0 || BSP_USING_SPI1 || BSP_USING_SPI2 || BSP_USING_SPI3 || BSP_USING_SPI4*/
#endif /* RT_USING_SPI */
