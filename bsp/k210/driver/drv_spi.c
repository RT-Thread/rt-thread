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
#include "utils.h"

#define DRV_SPI_DEVICE(spi_bus)    (struct drv_spi_bus *)(spi_bus)

#define MAX_CLOCK   (40000000UL)

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
    int freq = 0;
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
    freq = spi_set_clk_rate(bus->spi_instance, configuration->max_hz > MAX_CLOCK ? MAX_CLOCK : configuration->max_hz);
    rt_kprintf("set spi freq %d\n", freq);
    return ret;
}


void __spi_set_tmod(uint8_t spi_num, uint32_t tmod)
{
    RT_ASSERT(spi_num < SPI_DEVICE_MAX);
    volatile spi_t *spi_handle = spi[spi_num];
    uint8_t tmod_offset = 0;
    switch(spi_num)
    {
        case 0:
        case 1:
        case 2:
            tmod_offset = 8;
            break;
        case 3:
        default:
            tmod_offset = 10;
            break;
    }
    set_bit(&spi_handle->ctrlr0, 3 << tmod_offset, tmod << tmod_offset);
}

static rt_uint32_t drv_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct drv_spi_bus *bus = DRV_SPI_DEVICE(device->bus);
    struct drv_cs * cs = (struct drv_cs *)device->parent.user_data;
    struct rt_spi_configuration *cfg = &device->config;
    uint32_t * tx_buff = RT_NULL;
    uint32_t * rx_buff = RT_NULL;
    int i;
    rt_ubase_t dummy = 0xFFFFFFFFU;

    __spi_set_tmod(bus->spi_instance, SPI_TMOD_TRANS_RECV);

    RT_ASSERT(bus != RT_NULL);

    if(message->cs_take)
    {
        gpiohs_set_pin(cs->cs_pin, GPIO_PV_LOW);
    }
    if(message->length)
    {
        spi_instance[bus->spi_instance]->dmacr = 0x3;
        spi_instance[bus->spi_instance]->ssienr = 0x01;

        sysctl_dma_select(bus->dma_send_channel, SYSCTL_DMA_SELECT_SSI0_TX_REQ + bus->spi_instance * 2);
        sysctl_dma_select(bus->dma_recv_channel, SYSCTL_DMA_SELECT_SSI0_RX_REQ + bus->spi_instance * 2);

        if(!message->recv_buf)
        {
            dmac_set_single_mode(bus->dma_recv_channel, (void *)(&spi_instance[bus->spi_instance]->dr[0]), &dummy, DMAC_ADDR_NOCHANGE, DMAC_ADDR_NOCHANGE,
                           DMAC_MSIZE_1, DMAC_TRANS_WIDTH_32, message->length);
        }
        else
        {
            rx_buff = rt_calloc(message->length * 4, 1);
            if(!rx_buff)
            {
                goto transfer_done;
            }
            
            dmac_set_single_mode(bus->dma_recv_channel, (void *)(&spi_instance[bus->spi_instance]->dr[0]), rx_buff, DMAC_ADDR_NOCHANGE, DMAC_ADDR_INCREMENT,
                           DMAC_MSIZE_1, DMAC_TRANS_WIDTH_32, message->length);
        }
        

        if(!message->send_buf)
        {
            dmac_set_single_mode(bus->dma_send_channel, &dummy, (void *)(&spi_instance[bus->spi_instance]->dr[0]), DMAC_ADDR_NOCHANGE, DMAC_ADDR_NOCHANGE,
                           DMAC_MSIZE_4, DMAC_TRANS_WIDTH_32, message->length);
        }
        else
        {
            tx_buff = rt_malloc(message->length * 4);
            if(!tx_buff)
            {
                goto transfer_done;
            }
            for(i = 0; i < message->length; i++)
            {
                tx_buff[i] = ((uint8_t *)message->send_buf)[i];
            }
            dmac_set_single_mode(bus->dma_send_channel, tx_buff, (void *)(&spi_instance[bus->spi_instance]->dr[0]), DMAC_ADDR_INCREMENT, DMAC_ADDR_NOCHANGE,
                           DMAC_MSIZE_4, DMAC_TRANS_WIDTH_32, message->length);
        }
        
        spi_instance[bus->spi_instance]->ser = 1U << cs->cs_index;
        dmac_wait_done(bus->dma_send_channel);
        dmac_wait_done(bus->dma_recv_channel);
        spi_instance[bus->spi_instance]->ser = 0x00;
        spi_instance[bus->spi_instance]->ssienr = 0x00;

        if(message->recv_buf)
        {
            for(i = 0; i < message->length; i++)
            {
                ((uint8_t *)message->recv_buf)[i] = (uint8_t)rx_buff[i];
            }
        }

transfer_done:
        if(tx_buff)
        {
            rt_free(tx_buff);
        }
        if(rx_buff)
        {
            rt_free(rx_buff);
        }
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
