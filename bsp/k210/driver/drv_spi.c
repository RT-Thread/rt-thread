/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-18     ZYH          first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_SPI
#include "drv_spi.h"
#include <drv_io_config.h>
#include <spi.h>
#include <dmac.h>
#include <sysctl.h>
#include <gpiohs.h>
#include <string.h>

#define DRV_SPI_DEVICE(spi_bus)    (struct drv_spi_bus *)(spi_bus)

struct drv_spi_bus
{
    struct rt_spi_bus parent;
    spi_device_num_t spi_instance;
    dmac_channel_number_t dma_send_channel;
    dmac_channel_number_t dma_recv_channel;
};

struct drv_cs
{
    int cs_index;
    int cs_pin;
};

static volatile spi_t *const spi_instance[4] =
{
    (volatile spi_t *)SPI0_BASE_ADDR,
    (volatile spi_t *)SPI1_BASE_ADDR,
    (volatile spi_t *)SPI_SLAVE_BASE_ADDR,
    (volatile spi_t *)SPI3_BASE_ADDR
};

static rt_err_t drv_spi_configure(struct rt_spi_device *device,
                                  struct rt_spi_configuration *configuration)
{
    rt_err_t ret = RT_EOK;
    struct drv_spi_bus *bus = DRV_SPI_DEVICE(device->bus);
    struct drv_cs * cs = (struct drv_cs *)device->parent.user_data;
    RT_ASSERT(bus != RT_NULL);

    gpiohs_set_drive_mode(cs->cs_pin, GPIO_DM_OUTPUT);
    gpiohs_set_pin(cs->cs_pin, GPIO_PV_HIGH);

#ifdef BSP_USING_SPI1_AS_QSPI
    /* Todo:QSPI*/
#else
    spi_init(bus->spi_instance, configuration->mode & RT_SPI_MODE_3, SPI_FF_STANDARD, configuration->data_width, 0);
#endif
    spi_set_clk_rate(bus->spi_instance, configuration->max_hz);

    return ret;
}

extern void spi_receive_data_normal_dma(dmac_channel_number_t dma_send_channel_num,
                                  dmac_channel_number_t dma_receive_channel_num,
                                  spi_device_num_t spi_num, spi_chip_select_t chip_select, const void *cmd_buff,
                                  size_t cmd_len, void *rx_buff, size_t rx_len);




static rt_uint32_t drv_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct drv_spi_bus *bus = DRV_SPI_DEVICE(device->bus);
    struct drv_cs * cs = (struct drv_cs *)device->parent.user_data;
    struct rt_spi_configuration *cfg = &device->config;
    const uint8_t * tx_buff = message->send_buf;
    uint8_t * rx_buff = message->recv_buf;
    uint32_t dummy[1024];
    size_t send_size, recv_size;

    send_size = message->length;
    recv_size = message->length;

    RT_ASSERT(bus != RT_NULL);

    if(message->cs_take)
    {
        gpiohs_set_pin(cs->cs_pin, GPIO_PV_LOW);
    }
    if(message->length)
    {
        if(!tx_buff)
        {
            tx_buff = (uint8_t *)&dummy;
            send_size = 1;
        }

        if(!rx_buff)
        {
            rx_buff = (uint8_t *)&dummy;
            recv_size = 1;
        }
        spi_dup_send_receive_data_dma(bus->dma_send_channel, bus->dma_recv_channel, bus->spi_instance, cs->cs_index, tx_buff, send_size, rx_buff, recv_size);
    }

    if(message->cs_release)
    {
        gpiohs_set_pin(cs->cs_pin, GPIO_PV_HIGH);
    }

    return message->length;
}

const static struct rt_spi_ops drv_spi_ops =
{
    drv_spi_configure,
    drv_spi_xfer
};

int rt_hw_spi_init(void)
{
    rt_err_t ret = RT_EOK;
    
#ifdef BSP_USING_SPI1
    {
        static struct drv_spi_bus spi_bus1;
        spi_bus1.spi_instance = SPI_DEVICE_1;
        spi_bus1.dma_send_channel = DMAC_CHANNEL1;
        spi_bus1.dma_recv_channel = DMAC_CHANNEL2;
        ret = rt_spi_bus_register(&spi_bus1.parent, "spi1", &drv_spi_ops);

#ifdef BSP_SPI1_USING_SS0
        {
            static struct rt_spi_device spi_device10;
            static struct drv_cs cs10 = 
            {
                .cs_index = SPI_CHIP_SELECT_0,
                .cs_pin = SPI1_CS0_PIN
            };
            
            rt_spi_bus_attach_device(&spi_device10, "spi10", "spi1", (void *)&cs10);
        }
#endif

#ifdef BSP_SPI1_USING_SS1
        {
            static struct rt_spi_device spi_device11;
            static struct drv_cs cs11 = 
            {
                .cs_index = SPI_CHIP_SELECT_1,
                .cs_pin = SPI1_CS1_PIN
            };
            rt_spi_bus_attach_device(&spi_device11, "spi11", "spi1", (void *)&cs11);
        }
#endif

#ifdef BSP_SPI1_USING_SS2
        {
            static struct rt_spi_device spi_device12;
            static struct drv_cs cs12 = 
            {
                .cs_index = SPI_CHIP_SELECT_2,
                .cs_pin = SPI1_CS2_PIN
            };
            rt_spi_bus_attach_device(&spi_device12, "spi12", "spi1", (void *)&cs12);
        }
#endif

#ifdef BSP_SPI1_USING_SS3
        {
            static struct rt_spi_device spi_device13;
            static struct drv_cs cs13 = 
            {
                .cs_index = SPI_CHIP_SELECT_2,
                .cs_pin = SPI1_CS2_PIN
            };
            rt_spi_bus_attach_device(&spi_device13, "spi13", "spi1", (void *)&cs13);
        }
#endif
    }
#endif
    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_spi_init);
#endif
