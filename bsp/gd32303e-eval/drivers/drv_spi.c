/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-06-05     tanek        first implementation.
 * 2018-04-19     misonyo      Porting for gd32f30x
 */

#include "drv_spi.h"
#include "gd32f30x.h"
#include <rtthread.h>

#if defined(RT_USING_SPI) && defined(RT_USING_PIN)
#include <rtdevice.h>

#if !defined(RT_USING_SPI0) && !defined(RT_USING_SPI1) && \
    !defined(RT_USING_SPI2)
#error "Please define at least one SPIx"
#endif

/* #define DEBUG */
#ifdef DEBUG
#define DEBUG_PRINTF(...)   rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)
#endif

/* private rt-thread spi ops function */
static rt_err_t configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration);
static rt_uint32_t xfer(struct rt_spi_device* device, struct rt_spi_message* message);

static struct rt_spi_ops gd32_spi_ops =
{
    configure,
    xfer
};

static rt_err_t configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration)
{
    spi_parameter_struct spi_init_struct;

    rt_uint32_t spi_periph = (rt_uint32_t)device->bus->parent.user_data;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    if(configuration->data_width <= 8)
    {
        spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;
    }
    else if(configuration->data_width <= 16)
    {
        spi_init_struct.frame_size = SPI_FRAMESIZE_16BIT;
    }
    else
    {
        return -RT_EIO;
    }

    {
        rcu_clock_freq_enum spi_src;
        rt_uint32_t spi_apb_clock;
        rt_uint32_t max_hz;

        max_hz = configuration->max_hz;

        DEBUG_PRINTF("sys   freq: %d\n", rcu_clock_freq_get(CK_SYS));
        DEBUG_PRINTF("CK_APB2 freq: %d\n", rcu_clock_freq_get(CK_APB2));
        DEBUG_PRINTF("max   freq: %d\n", max_hz);

        if (spi_periph == SPI1 || spi_periph == SPI2)
        {
            spi_src = CK_APB1;
        }
        else
        {
            spi_src = CK_APB2;
        }
        spi_apb_clock = rcu_clock_freq_get(spi_src);

        if(max_hz >= spi_apb_clock/2)
        {
            spi_init_struct.prescale = SPI_PSC_2;
        }
        else if (max_hz >= spi_apb_clock/4)
        {
            spi_init_struct.prescale = SPI_PSC_4;
        }
        else if (max_hz >= spi_apb_clock/8)
        {
            spi_init_struct.prescale = SPI_PSC_8;
        }
        else if (max_hz >= spi_apb_clock/16)
        {
            spi_init_struct.prescale = SPI_PSC_16;
        }
        else if (max_hz >= spi_apb_clock/32)
        {
            spi_init_struct.prescale = SPI_PSC_32;
        }
        else if (max_hz >= spi_apb_clock/64)
        {
            spi_init_struct.prescale = SPI_PSC_64;
        }
        else if (max_hz >= spi_apb_clock/128)
        {
            spi_init_struct.prescale = SPI_PSC_128;
        }
        else
        {
            /*  min prescaler 256 */
            spi_init_struct.prescale = SPI_PSC_256;
        }
    } /* baudrate */

    switch(configuration->mode & RT_SPI_MODE_3)
    {
    case RT_SPI_MODE_0:
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
        break;
    case RT_SPI_MODE_1:
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_2EDGE;
        break;
    case RT_SPI_MODE_2:
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_1EDGE;
        break;
    case RT_SPI_MODE_3:
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
        break;
    }

    /* MSB or LSB */
    if(configuration->mode & RT_SPI_MSB)
    {
        spi_init_struct.endian = SPI_ENDIAN_MSB;
    }
    else
    {
        spi_init_struct.endian = SPI_ENDIAN_LSB;
    }

    spi_init_struct.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode = SPI_MASTER;
    spi_init_struct.nss = SPI_NSS_SOFT;

    spi_init(spi_periph, &spi_init_struct);

    spi_crc_off(spi_periph);

    spi_enable(spi_periph);

    return RT_EOK;
};

static rt_uint32_t xfer(struct rt_spi_device* device, struct rt_spi_message* message)
{
    rt_base_t gd32_cs_pin = (rt_base_t)device->parent.user_data;
    rt_uint32_t spi_periph = (rt_uint32_t)device->bus->parent.user_data;
    struct rt_spi_configuration * config = &device->config;

    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    /* take CS */
    if(message->cs_take)
    {
        rt_pin_write(gd32_cs_pin, PIN_LOW);
        DEBUG_PRINTF("spi take cs\n");
    }

    {
        if(config->data_width <= 8)
        {
            const rt_uint8_t * send_ptr = message->send_buf;
            rt_uint8_t * recv_ptr = message->recv_buf;
            rt_uint32_t size = message->length;

            DEBUG_PRINTF("spi poll transfer start: %d\n", size);

            while(size--)
            {
                rt_uint8_t data = 0xFF;

                if(send_ptr != RT_NULL)
                {
                    data = *send_ptr++;
                }

                // Todo: replace register read/write by gd32f3 lib
                //Wait until the transmit buffer is empty
                while(RESET == spi_i2s_flag_get(spi_periph, SPI_FLAG_TBE));
                // Send the byte
                spi_i2s_data_transmit(spi_periph, data);

                //Wait until a data is received
                while(RESET == spi_i2s_flag_get(spi_periph, SPI_FLAG_RBNE));
                // Get the received data
                data = spi_i2s_data_receive(spi_periph);

                if(recv_ptr != RT_NULL)
                {
                    *recv_ptr++ = data;
                }
            }
            DEBUG_PRINTF("spi poll transfer finsh\n");
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

                //Wait until the transmit buffer is empty
                while(RESET == spi_i2s_flag_get(spi_periph, SPI_FLAG_TBE));
                // Send the byte
                spi_i2s_data_transmit(spi_periph, data);

                //Wait until a data is received
                while(RESET == spi_i2s_flag_get(spi_periph, SPI_FLAG_RBNE));
                // Get the received data
                data = spi_i2s_data_receive(spi_periph);

                if(recv_ptr != RT_NULL)
                {
                    *recv_ptr++ = data;
                }
            }
        }
    }

    /* release CS */
    if(message->cs_release)
    {
        rt_pin_write(gd32_cs_pin, PIN_HIGH);
        DEBUG_PRINTF("spi release cs\n");
    }

    return message->length;
};

int gd32_hw_spi_init(void)
{
    int result = 0;
#ifdef RT_USING_SPI0
    static struct rt_spi_bus spi_bus0;
    spi_bus0.parent.user_data = (void *)SPI0;

    result = rt_spi_bus_register(&spi_bus0, "spi0", &gd32_spi_ops);

    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_SPI0);
    /* SPI0_SCK(PA5), SPI0_MISO(PA6) and SPI0_MOSI(PA7) GPIO pin configuration */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5 | GPIO_PIN_7);
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_6);

#endif
#ifdef RT_USING_SPI1
    static struct rt_spi_bus spi_bus1;
    spi_bus1.parent.user_data = (void *)SPI1;

    result = rt_spi_bus_register(&spi_bus1, "spi1", &gd32_spi_ops);

    rcu_periph_clock_enable(RCU_SPI1);
    rcu_periph_clock_enable(RCU_GPIOB);

    /* SPI1_SCK(PB13), SPI1_MISO(PB14) and SPI1_MOSI(PB15) GPIO pin configuration */
    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13 | GPIO_PIN_15);
    gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_14);
#endif
#ifdef RT_USING_SPI2
    static struct rt_spi_bus spi_bus2;
    spi_bus2.parent.user_data = (void *)SPI2;

    result = rt_spi_bus_register(&spi_bus2, "spi2", &gd32_spi_ops);

    rcu_periph_clock_enable(RCU_SPI2);
    rcu_periph_clock_enable(RCU_GPIOB);

    /* SPI2_SCK(PB3), SPI2_MISO(PB4) and SPI2_MOSI(PB5) GPIO pin configuration */
    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3 | GPIO_PIN_5);
    gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_4);
#endif
    return result;
}
INIT_BOARD_EXPORT(gd32_hw_spi_init);
#endif
