/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-11     shelton      first version
 */

#include "board.h"
#include "drv_spi.h"

#ifdef RT_USING_SPI
#if !defined(BSP_USING_SPI1) && !defined(BSP_USING_SPI2) && \
    !defined(BSP_USING_SPI3) && !defined(BSP_USING_SPI4)
#error "Please define at least one BSP_USING_SPIx"
#endif

#define ARR_LEN(__N)      (sizeof(__N) / sizeof(__N[0]))

//#define DRV_DEBUG
#define LOG_TAG             "drv.pwm"
#include <drv_log.h>

/* private rt-thread spi ops function */
static rt_err_t configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration);
static rt_uint32_t xfer(struct rt_spi_device* device, struct rt_spi_message* message);

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
    struct at32_spi *spi_instance = (struct at32_spi *)spi_bus->parent.user_data;

    spi_init_type spi_init_struct;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    at32_msp_spi_init(spi_instance->config->spi_x);

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
        return RT_EIO;
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

        if (spi_instance->config->spi_x == SPI1)
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
            /*  min prescaler 256 */
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
    /* init spi */
    spi_init(spi_instance->config->spi_x, &spi_init_struct);

    /* enable spi */
    spi_enable(spi_instance->config->spi_x, TRUE);
    /* disable spi crc */
    spi_crc_enable(spi_instance->config->spi_x, FALSE);

    return RT_EOK;
};

static rt_uint32_t xfer(struct rt_spi_device* device, struct rt_spi_message* message)
{
    struct rt_spi_bus * at32_spi_bus = (struct rt_spi_bus *)device->bus;
    struct at32_spi *spi_instance = (struct at32_spi *)at32_spi_bus->parent.user_data;
    struct rt_spi_configuration * config = &device->config;
    struct at32_spi_cs * at32_spi_cs = device->parent.user_data;

    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    /* take cs */
    if(message->cs_take)
    {
        gpio_bits_reset(at32_spi_cs->gpio_x, at32_spi_cs->gpio_pin);
        LOG_D("spi take cs\n");
    }

    if(config->data_width <= 8)
    {
        const rt_uint8_t *send_ptr = message->send_buf;
        rt_uint8_t * recv_ptr = message->recv_buf;
        rt_uint32_t size = message->length;

        LOG_D("spi poll transfer start: %d\n", size);

        while(size--)
        {
            rt_uint8_t data = 0xFF;

            if(send_ptr != RT_NULL)
            {
                data = *send_ptr++;
            }

            /* wait until the transmit buffer is empty */
            while(spi_i2s_flag_get(spi_instance->config->spi_x, SPI_I2S_TDBE_FLAG) == RESET);
            /* send the byte */
            spi_i2s_data_transmit(spi_instance->config->spi_x, data);

            /* wait until a data is received */
            while(spi_i2s_flag_get(spi_instance->config->spi_x, SPI_I2S_RDBF_FLAG) == RESET);
            /* get the received data */
            data = spi_i2s_data_receive(spi_instance->config->spi_x);

            if(recv_ptr != RT_NULL)
            {
                *recv_ptr++ = data;
            }
        }
        LOG_D("spi poll transfer finsh\n");
    }
    else if(config->data_width <= 16)
    {
        const rt_uint16_t * send_ptr = message->send_buf;
        rt_uint16_t * recv_ptr = message->recv_buf;
        rt_uint32_t size = message->length;

        while(size--)
        {
            rt_uint16_t data = 0xFF;

            if(send_ptr != RT_NULL)
            {
                data = *send_ptr++;
            }

            /* wait until the transmit buffer is empty */
            while(spi_i2s_flag_get(spi_instance->config->spi_x, SPI_I2S_TDBE_FLAG) == RESET);
            /* send the byte */
            spi_i2s_data_transmit(spi_instance->config->spi_x, data);

            /* wait until a data is received */
            while(spi_i2s_flag_get(spi_instance->config->spi_x, SPI_I2S_RDBF_FLAG) == RESET);
            /* get the received data */
            data = spi_i2s_data_receive(spi_instance->config->spi_x);

            if(recv_ptr != RT_NULL)
            {
                *recv_ptr++ = data;
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
};

static struct at32_spi_config configs[] = {
#ifdef BSP_USING_SPI1
    {SPI1, "spi1"},
#endif

#ifdef BSP_USING_SPI2
    {SPI2, "spi2"},
#endif

#ifdef BSP_USING_SPI3
    {SPI3, "spi3"},
#endif

#ifdef BSP_USING_SPI4
    {SPI4, "spi4"},
#endif
};

static struct at32_spi spis[sizeof(configs) / sizeof(configs[0])] = {0};

int rt_hw_spi_init(void)
{
    int i;
    rt_err_t result;
    rt_size_t obj_num = sizeof(spis) / sizeof(struct at32_spi);

    for (i = 0; i < obj_num; i++)
    {
        spis[i].config = &configs[i];
        spis[i].spi_bus.parent.user_data = (void *)&spis[i];
        result = rt_spi_bus_register(&(spis[i].spi_bus), spis[i].config->spi_name, &at32_spi_ops);
    }

    return result;
}

INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif
