/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 * 2022-11-10     shelton      support spi dma
 * 2023-01-31     shelton      add support f421/f425
 * 2023-04-08     shelton      add support f423
 */

#include "drv_common.h"
#include "drv_spi.h"
#include "drv_config.h"
#include <string.h>

#ifdef RT_USING_SPI
#if !defined(BSP_USING_SPI1) && !defined(BSP_USING_SPI2) && \
    !defined(BSP_USING_SPI3) && !defined(BSP_USING_SPI4)
#error "Please define at least one BSP_USING_SPIx"
#endif

//#define DRV_DEBUG
#define LOG_TAG             "drv.pwm"
#include <drv_log.h>

enum
{
#ifdef BSP_USING_SPI1
    SPI1_INDEX,
#endif
#ifdef BSP_USING_SPI2
    SPI2_INDEX,
#endif
#ifdef BSP_USING_SPI3
    SPI3_INDEX,
#endif
#ifdef BSP_USING_SPI4
    SPI4_INDEX,
#endif
};

static struct at32_spi_config spi_config[] = {
#ifdef BSP_USING_SPI1
    SPI1_CONFIG,
#endif

#ifdef BSP_USING_SPI2
    SPI2_CONFIG,
#endif

#ifdef BSP_USING_SPI3
    SPI3_CONFIG,
#endif

#ifdef BSP_USING_SPI4
    SPI4_CONFIG,
#endif
};

/* private rt-thread spi ops function */
static rt_err_t configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration);
static rt_ssize_t xfer(struct rt_spi_device* device, struct rt_spi_message* message);

static struct rt_spi_ops at32_spi_ops =
{
    configure,
    xfer
};

/**
  * attach the spi device to spi bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, gpio_type *cs_gpiox, uint16_t cs_gpio_pin)
{
    gpio_init_type gpio_init_struct;

    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;
    struct at32_spi_cs *cs_pin;

    /* initialize the cs pin & select the slave*/
    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_pins = cs_gpio_pin;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(cs_gpiox, &gpio_init_struct);
    gpio_bits_set(cs_gpiox, cs_gpio_pin);

    /* attach the device to spi bus */
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    cs_pin = (struct at32_spi_cs *)rt_malloc(sizeof(struct at32_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->gpio_x = cs_gpiox;
    cs_pin->gpio_pin = cs_gpio_pin;
    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

    if (result != RT_EOK)
    {
        LOG_D("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    RT_ASSERT(result == RT_EOK);

    LOG_D("%s attach to %s done", device_name, bus_name);

    return result;
}

static rt_err_t configure(struct rt_spi_device* device,
                          struct rt_spi_configuration* configuration)
{
    struct rt_spi_bus * spi_bus = (struct rt_spi_bus *)device->bus;
    struct at32_spi *instance = (struct at32_spi *)spi_bus->parent.user_data;

    spi_init_type spi_init_struct;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    at32_msp_spi_init(instance->config->spi_x);

    /* data_width */
    if(configuration->data_width <= 8)
    {
        spi_init_struct.frame_bit_num = SPI_FRAME_8BIT;
    }
    else if(configuration->data_width <= 16)
    {
        spi_init_struct.frame_bit_num = SPI_FRAME_16BIT;
    }
    else
    {
        return -RT_EIO;
    }

    /* baudrate */
    {
        uint32_t spi_apb_clock;
        uint32_t max_hz;
        crm_clocks_freq_type clocks_struct;

        max_hz = configuration->max_hz;

        crm_clocks_freq_get(&clocks_struct);
        LOG_D("sys freq: %d\n", clocks_struct.sclk_freq);
        LOG_D("max freq: %d\n", max_hz);

        if (instance->config->spi_x == SPI1)
        {
            spi_apb_clock = clocks_struct.apb2_freq;
            LOG_D("pclk2 freq: %d\n", clocks_struct.apb2_freq);
        }
        else
        {
            spi_apb_clock = clocks_struct.apb1_freq;
            LOG_D("pclk1 freq: %d\n", clocks_struct.apb1_freq);
        }

        if(max_hz >= (spi_apb_clock / 2))
        {
            spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_2;
        }
        else if (max_hz >= (spi_apb_clock / 4))
        {
            spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_4;
        }
        else if (max_hz >= (spi_apb_clock / 8))
        {
            spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_8;
        }
        else if (max_hz >= (spi_apb_clock / 16))
        {
            spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_16;
        }
        else if (max_hz >= (spi_apb_clock / 32))
        {
            spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_32;
        }
        else if (max_hz >= (spi_apb_clock / 64))
        {
            spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_64;
        }
        else if (max_hz >= (spi_apb_clock / 128))
        {
            spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_128;
        }
        else
        {
            /* min prescaler 256 */
            spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_256;
        }
    } /* baudrate */

    switch(configuration->mode & RT_SPI_MODE_3)
    {
    case RT_SPI_MODE_0:
        spi_init_struct.clock_phase = SPI_CLOCK_PHASE_1EDGE;
        spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_LOW;
        break;
    case RT_SPI_MODE_1:
        spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;
        spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_LOW;
        break;
    case RT_SPI_MODE_2:
        spi_init_struct.clock_phase = SPI_CLOCK_PHASE_1EDGE;
        spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_HIGH;
        break;
    case RT_SPI_MODE_3:
        spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;
        spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_HIGH;
        break;
    }

    /* msb or lsb */
    if(configuration->mode & RT_SPI_MSB)
    {
        spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_MSB;
    }
    else
    {
        spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_LSB;
    }

    spi_init_struct.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;
    spi_init_struct.master_slave_mode = SPI_MODE_MASTER;
    spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;
    /* disable spi to change transfer size */
    spi_enable(instance->config->spi_x, FALSE);
    /* init spi */
    spi_init(instance->config->spi_x, &spi_init_struct);

    /* enable spi */
    spi_enable(instance->config->spi_x, TRUE);
    /* disable spi crc */
    spi_crc_enable(instance->config->spi_x, FALSE);

    return RT_EOK;
};

static void _spi_dma_receive(struct at32_spi *instance, rt_uint8_t *buffer, rt_uint32_t size)
{
    dma_channel_type* dma_channel = instance->config->dma_rx->dma_channel;

    dma_channel->dtcnt = size;
    dma_channel->paddr = (rt_uint32_t)&(instance->config->spi_x->dt);
    dma_channel->maddr = (rt_uint32_t)buffer;

    /* enable transmit complete interrupt */
    dma_interrupt_enable(dma_channel, DMA_FDT_INT, TRUE);
    /* enable dma receive */
    spi_i2s_dma_receiver_enable(instance->config->spi_x, TRUE);

    /* mark dma flag */
    instance->config->dma_rx->dma_done = RT_FALSE;
    /* enable dma channel */
    dma_channel_enable(dma_channel, TRUE);
}

static void _spi_dma_transmit(struct at32_spi *instance, rt_uint8_t *buffer, rt_uint32_t size)
{
    dma_channel_type *dma_channel = instance->config->dma_tx->dma_channel;

    dma_channel->dtcnt = size;
    dma_channel->paddr = (rt_uint32_t)&(instance->config->spi_x->dt);
    dma_channel->maddr = (rt_uint32_t)buffer;

    /* enable spi error interrupt */
    spi_i2s_interrupt_enable(instance->config->spi_x, SPI_I2S_ERROR_INT, TRUE);
    /* enable transmit complete interrupt */
    dma_interrupt_enable(dma_channel, DMA_FDT_INT, TRUE);
    /* enable dma transmit */
    spi_i2s_dma_transmitter_enable(instance->config->spi_x, TRUE);

    /* mark dma flag */
    instance->config->dma_tx->dma_done = RT_FALSE;
    /* enable dma channel */
    dma_channel_enable(dma_channel, TRUE);
}

static void _spi_polling_receive_transmit(struct at32_spi *instance, rt_uint8_t *recv_buf, rt_uint8_t *send_buf, \
                                          rt_uint32_t size, rt_uint8_t data_mode)
{
    /* data frame length 8 bit */
    if(data_mode <= 8)
    {
        const rt_uint8_t *send_ptr = send_buf;
        rt_uint8_t * recv_ptr = recv_buf;

        LOG_D("spi poll transfer start: %d\n", size);

        while(size--)
        {
            rt_uint8_t data = 0xFF;

            if(send_ptr != RT_NULL)
            {
                data = *send_ptr++;
            }

            /* wait until the transmit buffer is empty */
            while(spi_i2s_flag_get(instance->config->spi_x, SPI_I2S_TDBE_FLAG) == RESET);
            /* send the byte */
            spi_i2s_data_transmit(instance->config->spi_x, data);

            /* wait until a data is received */
            while(spi_i2s_flag_get(instance->config->spi_x, SPI_I2S_RDBF_FLAG) == RESET);
            /* get the received data */
            data = spi_i2s_data_receive(instance->config->spi_x);

            if(recv_ptr != RT_NULL)
            {
                *recv_ptr++ = data;
            }
        }
        LOG_D("spi poll transfer finsh\n");
    }
    /* data frame length 16 bit */
    else if(data_mode <= 16)
    {
        const rt_uint16_t * send_ptr = (rt_uint16_t *)send_buf;
        rt_uint16_t * recv_ptr = (rt_uint16_t *)recv_buf;

        while(size--)
        {
            rt_uint16_t data = 0xFF;

            if(send_ptr != RT_NULL)
            {
                data = *send_ptr++;
            }

            /* wait until the transmit buffer is empty */
            while(spi_i2s_flag_get(instance->config->spi_x, SPI_I2S_TDBE_FLAG) == RESET);
            /* send the byte */
            spi_i2s_data_transmit(instance->config->spi_x, data);

            /* wait until a data is received */
            while(spi_i2s_flag_get(instance->config->spi_x, SPI_I2S_RDBF_FLAG) == RESET);
            /* get the received data */
            data = spi_i2s_data_receive(instance->config->spi_x);

            if(recv_ptr != RT_NULL)
            {
                *recv_ptr++ = data;
            }
        }
    }
}

static rt_ssize_t xfer(struct rt_spi_device* device, struct rt_spi_message* message)
{
    struct rt_spi_bus * at32_spi_bus = (struct rt_spi_bus *)device->bus;
    struct at32_spi *instance = (struct at32_spi *)at32_spi_bus->parent.user_data;
    struct rt_spi_configuration *config = &device->config;
    struct at32_spi_cs * at32_spi_cs = device->parent.user_data;
    rt_size_t message_length = 0, already_send_length = 0;
    rt_uint16_t send_length = 0;
    rt_uint8_t *recv_buf;
    const rt_uint8_t *send_buf;

    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    /* take cs */
    if(message->cs_take)
    {
        gpio_bits_reset(at32_spi_cs->gpio_x, at32_spi_cs->gpio_pin);
        LOG_D("spi take cs\n");
    }

    message_length = message->length;
    recv_buf = message->recv_buf;
    send_buf = message->send_buf;
    while (message_length)
    {
        /* the HAL library use uint16 to save the data length */
        if (message_length > 65535)
        {
            send_length = 65535;
            message_length = message_length - 65535;
        }
        else
        {
            send_length = message_length;
            message_length = 0;
        }

        /* calculate the start address */
        already_send_length = message->length - send_length - message_length;
        /* avoid null pointer problems */
        if (message->send_buf)
        {
            send_buf = (rt_uint8_t *)message->send_buf + already_send_length;
        }
        if (message->recv_buf)
        {
            recv_buf = (rt_uint8_t *)message->recv_buf + already_send_length;
        }

        /* start once data exchange in dma mode */
        if (message->send_buf && message->recv_buf)
        {
            if ((instance->config->spi_dma_flag & RT_DEVICE_FLAG_DMA_RX) && \
                (instance->config->spi_dma_flag & RT_DEVICE_FLAG_DMA_TX))
            {
                _spi_dma_receive(instance, (uint8_t *)recv_buf, send_length);
                _spi_dma_transmit(instance, (uint8_t *)send_buf, send_length);
                /* wait transfer complete */
                while(spi_i2s_flag_get(instance->config->spi_x, SPI_I2S_BF_FLAG) != RESET);
                while((instance->config->dma_tx->dma_done == RT_FALSE) || (instance->config->dma_rx->dma_done == RT_FALSE));
                /* clear rx overrun flag */
                spi_i2s_flag_clear(instance->config->spi_x, SPI_I2S_ROERR_FLAG);
                spi_enable(instance->config->spi_x, FALSE);
                spi_enable(instance->config->spi_x, TRUE);
            }
            else
            {
                _spi_polling_receive_transmit(instance, (uint8_t *)recv_buf, (uint8_t *)send_buf, send_length, config->data_width);
            }
        }
        else if (message->send_buf)
        {
            if (instance->config->spi_dma_flag & RT_DEVICE_FLAG_DMA_TX)
            {
                _spi_dma_transmit(instance, (uint8_t *)send_buf, send_length);
                /* wait transfer complete */
                while(spi_i2s_flag_get(instance->config->spi_x, SPI_I2S_BF_FLAG) != RESET);
                while(instance->config->dma_tx->dma_done == RT_FALSE);
                /* clear rx overrun flag */
                spi_i2s_flag_clear(instance->config->spi_x, SPI_I2S_ROERR_FLAG);
                spi_enable(instance->config->spi_x, FALSE);
                spi_enable(instance->config->spi_x, TRUE);
            }
            else
            {
                _spi_polling_receive_transmit(instance, RT_NULL, (uint8_t *)send_buf, send_length, config->data_width);
            }

            if (message->cs_release && (device->config.mode & RT_SPI_3WIRE))
            {
                /* release the cs by disable spi when using 3 wires spi */
                spi_enable(instance->config->spi_x, FALSE);
            }
        }
        else
        {
            memset((void *)recv_buf, 0xff, send_length);
            if (instance->config->spi_dma_flag & RT_DEVICE_FLAG_DMA_RX)
            {
                _spi_dma_receive(instance, (uint8_t *)recv_buf, send_length);
                _spi_dma_transmit(instance, (uint8_t *)recv_buf, send_length);
                /* wait transfer complete */
                while(spi_i2s_flag_get(instance->config->spi_x, SPI_I2S_BF_FLAG) != RESET);
                while((instance->config->dma_tx->dma_done == RT_FALSE) || (instance->config->dma_rx->dma_done == RT_FALSE));
                /* clear rx overrun flag */
                spi_i2s_flag_clear(instance->config->spi_x, SPI_I2S_ROERR_FLAG);
                spi_enable(instance->config->spi_x, FALSE);
                spi_enable(instance->config->spi_x, TRUE);
            }
            else
            {
                /* clear the old error flag */
                spi_i2s_flag_clear(instance->config->spi_x, SPI_I2S_ROERR_FLAG);
                _spi_polling_receive_transmit(instance, (uint8_t *)recv_buf, (uint8_t *)recv_buf, send_length, config->data_width);
            }
        }
    }

    /* release cs */
    if(message->cs_release)
    {
        gpio_bits_set(at32_spi_cs->gpio_x, at32_spi_cs->gpio_pin);
        LOG_D("spi release cs\n");
    }

    return message->length;
}

static void _dma_base_channel_check(struct at32_spi *instance)
{
    dma_channel_type *rx_channel = instance->config->dma_rx->dma_channel;
    dma_channel_type *tx_channel = instance->config->dma_tx->dma_channel;

    if(instance->config->spi_dma_flag & RT_DEVICE_FLAG_DMA_RX)
    {
        instance->config->dma_rx->dma_done = RT_TRUE;
        instance->config->dma_rx->dma_x = (dma_type *)((rt_uint32_t)rx_channel & ~0xFF);
        instance->config->dma_rx->channel_index = ((((rt_uint32_t)rx_channel & 0xFF) - 8) / 0x14) + 1;
    }

    if(instance->config->spi_dma_flag & RT_DEVICE_FLAG_DMA_TX)
    {
        instance->config->dma_tx->dma_done = RT_TRUE;
        instance->config->dma_tx->dma_x = (dma_type *)((rt_uint32_t)tx_channel & ~0xFF);
        instance->config->dma_tx->channel_index = ((((rt_uint32_t)tx_channel & 0xFF) - 8) / 0x14) + 1;
    }
}

static void at32_spi_dma_init(struct at32_spi *instance)
{
    dma_init_type dma_init_struct;

    /* search dma base and channel index */
    _dma_base_channel_check(instance);

    /* config dma channel */
    dma_default_para_init(&dma_init_struct);
    dma_init_struct.peripheral_inc_enable = FALSE;
    dma_init_struct.memory_inc_enable = TRUE;
    dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
    dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
    dma_init_struct.priority = DMA_PRIORITY_MEDIUM;
    dma_init_struct.loop_mode_enable = FALSE;

    if (instance->config->spi_dma_flag & RT_DEVICE_FLAG_DMA_RX)
    {
        crm_periph_clock_enable(instance->config->dma_rx->dma_clock, TRUE);
        dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;

        dma_reset(instance->config->dma_rx->dma_channel);
        dma_init(instance->config->dma_rx->dma_channel, &dma_init_struct);
#if defined (SOC_SERIES_AT32F425)
        dma_flexible_config(instance->config->dma_rx->dma_x, instance->config->dma_rx->flex_channel, \
                           (dma_flexible_request_type)instance->config->dma_rx->request_id);
#endif
#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32F423)
        dmamux_enable(instance->config->dma_rx->dma_x, TRUE);
        dmamux_init(instance->config->dma_rx->dmamux_channel, (dmamux_requst_id_sel_type)instance->config->dma_rx->request_id);
#endif
        /* dma irq should set in dma rx mode */
        nvic_irq_enable(instance->config->dma_rx->dma_irqn, 0, 1);
    }

    if (instance->config->spi_dma_flag & RT_DEVICE_FLAG_DMA_TX)
    {
        crm_periph_clock_enable(instance->config->dma_tx->dma_clock, TRUE);
        dma_init_struct.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;

        dma_reset(instance->config->dma_tx->dma_channel);
        dma_init(instance->config->dma_tx->dma_channel, &dma_init_struct);
#if defined (SOC_SERIES_AT32F425)
        dma_flexible_config(instance->config->dma_tx->dma_x, instance->config->dma_tx->flex_channel, \
                           (dma_flexible_request_type)instance->config->dma_tx->request_id);
#endif
#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32F423)
        dmamux_enable(instance->config->dma_tx->dma_x, TRUE);
        dmamux_init(instance->config->dma_tx->dmamux_channel, (dmamux_requst_id_sel_type)instance->config->dma_tx->request_id);
#endif
        /* dma irq should set in dma tx mode */
        nvic_irq_enable(instance->config->dma_tx->dma_irqn, 0, 1);
    }

    if((instance->config->spi_dma_flag & RT_DEVICE_FLAG_DMA_TX) || \
       (instance->config->spi_dma_flag & RT_DEVICE_FLAG_DMA_RX))
    {
        nvic_irq_enable(instance->config->irqn, 0, 0);
    }
}

void dma_isr(struct dma_config *dma_instance)
{
    volatile rt_uint32_t reg_sts = 0, index = 0;

    reg_sts = dma_instance->dma_x->sts;
    index = dma_instance->channel_index;

    if ((reg_sts & (DMA_FDT_FLAG << (4 * (index - 1)))) != RESET)
    {
        /* clear dma flag */
        dma_instance->dma_x->clr |= (rt_uint32_t)((DMA_FDT_FLAG << (4 * (index - 1))) | \
                                                  (DMA_HDT_FLAG << (4 * (index - 1))));
        /* disable interrupt */
        dma_interrupt_enable(dma_instance->dma_channel, DMA_FDT_INT, FALSE);
        /* disable dma channel */
        dma_channel_enable(dma_instance->dma_channel, FALSE);
        /* mark done flag */
        dma_instance->dma_done = RT_TRUE;
    }
}

void spi_isr(spi_type *spi_x)
{
    if(spi_i2s_flag_get(spi_x, SPI_I2S_ROERR_FLAG) != RESET)
    {
        /* clear rx overrun error flag */
        spi_i2s_flag_clear(spi_x, SPI_I2S_ROERR_FLAG);
    }

    if(spi_i2s_flag_get(spi_x, SPI_MMERR_FLAG) != RESET)
    {
        /* clear master mode error flag */
        spi_i2s_flag_clear(spi_x, SPI_MMERR_FLAG);
    }
}

#ifdef BSP_USING_SPI1
void SPI1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(spi_config[SPI1_INDEX].spi_x);

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(BSP_SPI1_RX_USING_DMA)
void SPI1_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_isr(spi_config[SPI1_INDEX].dma_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI1_RX_USING_DMA) */
#if defined(BSP_SPI1_TX_USING_DMA)
void SPI1_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_isr(spi_config[SPI1_INDEX].dma_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI1_TX_USING_DMA) */
#endif
#ifdef BSP_USING_SPI2
void SPI2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(spi_config[SPI2_INDEX].spi_x);

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(BSP_SPI2_RX_USING_DMA)
void SPI2_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_isr(spi_config[SPI2_INDEX].dma_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI2_RX_USING_DMA) */
#if defined(BSP_SPI2_TX_USING_DMA)
void SPI2_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_isr(spi_config[SPI2_INDEX].dma_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI2_TX_USING_DMA) */
#endif
#ifdef BSP_USING_SPI3
void SPI3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(spi_config[SPI3_INDEX].spi_x);

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(BSP_SPI3_RX_USING_DMA)
void SPI3_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_isr(spi_config[SPI3_INDEX].dma_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI3_RX_USING_DMA) */
#if defined(BSP_SPI3_TX_USING_DMA)
void SPI3_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_isr(spi_config[SPI3_INDEX].dma_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI3_TX_USING_DMA) */
#endif
#ifdef BSP_USING_SPI4
void SPI4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    spi_isr(spi_config[SPI4_INDEX].spi_x);

    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined(BSP_SPI4_RX_USING_DMA)
void SPI4_RX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_isr(spi_config[SPI4_INDEX].dma_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI4_RX_USING_DMA) */
#if defined(BSP_SPI4_TX_USING_DMA)
void SPI4_TX_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_isr(spi_config[SPI4_INDEX].dma_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_SPI14_TX_USING_DMA) */
#endif

#if defined (SOC_SERIES_AT32F421)
void SPI1_TX_RX_DMA_IRQHandler(void)
{
#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_TX_USING_DMA)
    SPI1_TX_DMA_IRQHandler();
#endif

#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_RX_USING_DMA)
    SPI1_RX_DMA_IRQHandler();
#endif
}

void SPI2_TX_RX_DMA_IRQHandler(void)
{
#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_TX_USING_DMA)
    SPI2_TX_DMA_IRQHandler();
#endif

#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_RX_USING_DMA)
    SPI2_RX_DMA_IRQHandler();
#endif
}
#endif

#if defined (SOC_SERIES_AT32F425)
void SPI1_TX_RX_DMA_IRQHandler(void)
{
#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_TX_USING_DMA)
    SPI1_TX_DMA_IRQHandler();
#endif

#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_RX_USING_DMA)
    SPI1_RX_DMA_IRQHandler();
#endif
}

void SPI3_2_TX_RX_DMA_IRQHandler(void)
{
#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_TX_USING_DMA)
    SPI2_TX_DMA_IRQHandler();
#endif

#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_RX_USING_DMA)
    SPI2_RX_DMA_IRQHandler();
#endif

#if defined(BSP_USING_SPI3) && defined(BSP_SPI3_TX_USING_DMA)
    SPI3_TX_DMA_IRQHandler();
#endif

#if defined(BSP_USING_SPI3) && defined(BSP_SPI3_RX_USING_DMA)
    SPI3_RX_DMA_IRQHandler();
#endif
}
#endif

static struct at32_spi spis[sizeof(spi_config) / sizeof(spi_config[0])] = {0};

static void at32_spi_get_dma_config(void)
{
#ifdef BSP_USING_SPI1
    spi_config[SPI1_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI1_RX_USING_DMA
    spi_config[SPI1_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config spi1_dma_rx = SPI1_RX_DMA_CONFIG;
    spi_config[SPI1_INDEX].dma_rx = &spi1_dma_rx;
#endif
#ifdef BSP_SPI1_TX_USING_DMA
    spi_config[SPI1_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config spi1_dma_tx = SPI1_TX_DMA_CONFIG;
    spi_config[SPI1_INDEX].dma_tx = &spi1_dma_tx;
#endif
#endif

#ifdef BSP_USING_SPI2
    spi_config[SPI2_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI2_RX_USING_DMA
    spi_config[SPI2_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config spi2_dma_rx = SPI2_RX_DMA_CONFIG;
    spi_config[SPI2_INDEX].dma_rx = &spi2_dma_rx;
#endif
#ifdef BSP_SPI2_TX_USING_DMA
    spi_config[SPI2_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config spi2_dma_tx = SPI2_TX_DMA_CONFIG;
    spi_config[SPI2_INDEX].dma_tx = &spi2_dma_tx;
#endif
#endif

#ifdef BSP_USING_SPI3
    spi_config[SPI3_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI3_RX_USING_DMA
    spi_config[SPI3_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config spi3_dma_rx = SPI3_RX_DMA_CONFIG;
    spi_config[SPI3_INDEX].dma_rx = &spi3_dma_rx;
#endif
#ifdef BSP_SPI3_TX_USING_DMA
    spi_config[SPI3_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config spi3_dma_tx = SPI3_TX_DMA_CONFIG;
    spi_config[SPI3_INDEX].dma_tx = &spi3_dma_tx;
#endif
#endif

#ifdef BSP_USING_SPI4
    spi_config[SPI4_INDEX].spi_dma_flag = 0;
#ifdef BSP_SPI4_RX_USING_DMA
    spi_config[SPI4_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config spi4_dma_rx = SPI4_RX_DMA_CONFIG;
    spi_config[SPI4_INDEX].dma_rx = &spi4_dma_rx;
#endif
#ifdef BSP_SPI4_TX_USING_DMA
    spi_config[SPI4_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config spi4_dma_tx = SPI4_TX_DMA_CONFIG;
    spi_config[SPI4_INDEX].dma_tx = &spi4_dma_tx;
#endif
#endif
}

int rt_hw_spi_init(void)
{
    int i;
    rt_err_t result;
    rt_size_t obj_num = sizeof(spi_config) / sizeof(spi_config[0]);

    at32_spi_get_dma_config();

    for (i = 0; i < obj_num; i++)
    {
        spis[i].config = &spi_config[i];
        spis[i].spi_bus.parent.user_data = (void *)&spis[i];

        if(spis[i].config->spi_dma_flag & (RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX))
        {
            at32_spi_dma_init(&spis[i]);
        }
        result = rt_spi_bus_register(&(spis[i].spi_bus), spis[i].config->spi_name, &at32_spi_ops);
    }

    return result;
}

INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif
