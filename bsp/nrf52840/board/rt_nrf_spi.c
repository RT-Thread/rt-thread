/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-5      SummerGift   first version
 * 2018-12-11     greedyhao    Porting for nrff7xx
 * 2019-01-03     zylx         modify DMA initialization and spixfer function
 */

#include "board.h"

#ifdef RT_USING_SPI

#include "nrf_drv_spi.h"
#include "nrf_gpio.h"
#include "rt_nrf_spi.h"
#include <string.h>

#define DBG_TAG                        "drv.spi"
#define DBG_LVL                        DBG_INFO
#include <rtdbg.h>

#define DUMMY_DATA		0xFF

#define NRF_RETRY_PROCESS(delay, retry, result)                               \
    void (*__delay_temp)(void) = (void (*)(void))delay;                        \
    if (retry == 0) {result = 1;break;}                         \
    else {if (__delay_temp) {__delay_temp();} retry --;}


struct nrf_spi
{
    struct rt_spi_configuration *cfg;
		struct rt_spi_bus spi_bus;
};


static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(0);

struct nrf_spi nrf_spi0;

static rt_err_t nrf_spi_init(struct rt_spi_configuration *cfg)
{
    RT_ASSERT(cfg != RT_NULL);
		 
    nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
		
		spi_config.sck_pin  = NRF_GPIO_PIN_MAP(1, 15);
    spi_config.mosi_pin = NRF_GPIO_PIN_MAP(1, 13);
		spi_config.miso_pin = NRF_GPIO_PIN_MAP(1, 14);
		spi_config.ss_pin   = NRF_DRV_SPI_PIN_NOT_USED,
		spi_config.frequency = NRF_DRV_SPI_FREQ_8M;
    
    nrf_drv_spi_init(&spi, &spi_config, NULL, NULL);

		rt_pin_mode(NRF_GPIO_PIN_MAP(1, 12), PIN_MODE_OUTPUT);
		rt_pin_write(NRF_GPIO_PIN_MAP(1, 12), 1);

    return RT_EOK;
}

static rt_err_t spi_configure(struct rt_spi_device *device,
                              struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

		struct nrf_spi *spi_drv =  rt_container_of(device->bus, struct nrf_spi, spi_bus);
    spi_drv->cfg = configuration;

    return nrf_spi_init(configuration);
}

ret_code_t nrf_drv_spi_trans(NRF_SPI_Type *SPI,rt_uint8_t const * p_tx_buffer,rt_uint8_t tx_buffer_length,rt_uint8_t * p_rx_buffer,rt_uint8_t rx_buffer_length)
{
		rt_uint8_t send_data, read_data;
		ret_code_t result = 0;

		nrf_spi_enable(SPI);

    nrf_spi_event_clear(SPI, NRF_SPI_EVENT_READY);

		for(rt_uint16_t i = 0, retry_times; i < tx_buffer_length + rx_buffer_length; i++) 
		{
        if(i < tx_buffer_length) 
				{
            send_data = *p_tx_buffer++;
        } 
				else 
				{
            send_data = DUMMY_DATA;
        }
        
				nrf_spi_txd_set(SPI,send_data);

				retry_times = 2000;
        while (!nrf_spi_event_check(SPI, NRF_SPI_EVENT_READY)) 
        {
						NRF_RETRY_PROCESS(NULL, retry_times, result);
        }

        if (result != 0) 
        {
            return result;
        }
				
				nrf_spi_event_clear(SPI, NRF_SPI_EVENT_READY);
				
        read_data = nrf_spi_rxd_get(SPI);
				
        if(i >= tx_buffer_length)
				{
            *p_rx_buffer++ = read_data;
        }
    }

		nrf_spi_disable(SPI);

		return result;
}

static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
		ret_code_t state = 0;
    rt_size_t message_length, already_send_length;
    rt_uint16_t send_length;
    rt_uint8_t *recv_buf;
    const rt_uint8_t *send_buf;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    if (message->cs_take)
    {
        rt_pin_write(NRF_GPIO_PIN_MAP(1, 12), 0);
    }

    LOG_D("%s transfer prepare and start", spi_drv->config->bus_name);
    LOG_D("%s sendbuf: %X, recvbuf: %X, length: %d",
          spi_drv->config->bus_name,
          (uint32_t)message->send_buf,
          (uint32_t)message->recv_buf, message->length);

    message_length = message->length;
    recv_buf = message->recv_buf;
    send_buf = message->send_buf;
    while (message_length)
    {
        /* the HAL library use uint16 to save the data length */
        if (message_length > 255)
        {
            send_length = 255;
            message_length = message_length - 255;
        }
        else
        {
            send_length = message_length;
            message_length = 0;
        }

        /* calculate the start address */
        already_send_length = message->length - send_length - message_length;
        send_buf = (rt_uint8_t *)message->send_buf + already_send_length;
        recv_buf = (rt_uint8_t *)message->recv_buf + already_send_length;
        
        if (message->send_buf && message->recv_buf)
        {
            state = nrf_drv_spi_trans(spi.u.spi.p_reg, send_buf, send_length, (uint8_t *)recv_buf, send_length);
        }
        else if (message->send_buf)
        {
            state = nrf_drv_spi_trans(spi.u.spi.p_reg, (uint8_t *)send_buf, send_length, NULL, 0);
        }
        else
        {
            state = nrf_drv_spi_trans(spi.u.spi.p_reg, NULL, 0, (uint8_t *)recv_buf, send_length);
        }

        if (state != 0)
        {
            LOG_D("spi transfer error : %d", state);
            message->length = 0;
        }
        else
        {
            LOG_D("%s transfer done", "spi0");
        }
    }

    if (message->cs_release)
    {
        rt_pin_write(NRF_GPIO_PIN_MAP(1, 12), 1);
    }

    return message->length;
}

static const struct rt_spi_ops nrf_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer,
};

static int rt_hw_spi_bus_init(void)
{
    rt_err_t result;

		result = rt_spi_bus_register(&nrf_spi0.spi_bus, "spi0", &nrf_spi_ops);
		RT_ASSERT(result == RT_EOK);

		LOG_D("%s bus init done", "spi0");

    return result;
}


struct rt_spi_device *spi_device;	
/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, NULL);
    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    RT_ASSERT(result == RT_EOK);

    LOG_I("%s attach to %s done", device_name, bus_name);

    return result;
}

static int rt_hw_spi_init(void)
{
		rt_hw_spi_bus_init();
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* RT_USING_SPI */
