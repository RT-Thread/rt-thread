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

#ifdef RT_USING_SPI

#if defined(BSP_USING_SPI0) || defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3) || defined(BSP_USING_SPI4)
#define LOG_TAG              "drv.spi"

#include <rtdbg.h>

#ifdef BSP_USING_SPI0
static struct rt_spi_bus spi_bus0;
#endif
#ifdef BSP_USING_SPI1
static struct rt_spi_bus spi_bus1;
#endif
#ifdef BSP_USING_SPI2
static struct rt_spi_bus spi_bus2;
#endif
#ifdef BSP_USING_SPI3
static struct rt_spi_bus spi_bus3;
#endif
#ifdef BSP_USING_SPI4
static struct rt_spi_bus spi_bus4;
#endif

static const struct gd32_spi spi_bus_obj[] = {

#ifdef BSP_USING_SPI0
    {
        SPI0,
        "spi0",
        RCU_SPI0,
        RCU_GPIOA,
        &spi_bus0,
        GPIOA,
#if defined SOC_SERIES_GD32F4xx
        GPIO_AF_5,
#endif
        GPIO_PIN_5,
        GPIO_PIN_6,
        GPIO_PIN_7,
    },
#endif /* BSP_USING_SPI0 */

#ifdef BSP_USING_SPI1
    {
        SPI1,
        "spi1",
        RCU_SPI1,
        RCU_GPIOB,
        &spi_bus1,
        GPIOB,
#if defined SOC_SERIES_GD32F4xx
        GPIO_AF_5,
#endif
        GPIO_PIN_12,
        GPIO_PIN_14,
        GPIO_PIN_15,
    },
#endif /* BSP_USING_SPI1 */

#ifdef BSP_USING_SPI2
    {
        SPI2,
        "spi2",
        RCU_SPI2,
        RCU_GPIOB,
        &spi_bus2,
        GPIOB,
#if defined SOC_SERIES_GD32F4xx
        GPIO_AF_6,
#endif
        GPIO_PIN_3,
        GPIO_PIN_4,
        GPIO_PIN_5,
    },
#endif /* BSP_USING_SPI2 */

#ifdef BSP_USING_SPI3
    {
        SPI2,
        "spi2",
        RCU_SPI3,
        RCU_GPIOE,
        &spi_bus3,
        GPIOB,
#if defined SOC_SERIES_GD32F4xx
        GPIO_AF_5,
#endif
        GPIO_PIN_2,
        GPIO_PIN_5,
        GPIO_PIN_6,
    },
#endif /* BSP_USING_SPI3 */

#ifdef BSP_USING_SPI4
    {
        SPI4,
        "spi4",
        RCU_SPI4,
        RCU_GPIOF,
        &spi_bus4,
        GPIOF,
#if defined SOC_SERIES_GD32F4xx
        GPIO_AF_5,
#endif
        GPIO_PIN_7,
        GPIO_PIN_8,
        GPIO_PIN_9,
    }
#endif /* BSP_USING_SPI4 */
};

/* private rt-thread spi ops function */
static rt_err_t spi_configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration);
static rt_ssize_t spixfer(struct rt_spi_device* device, struct rt_spi_message* message);

static struct rt_spi_ops gd32_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer,
};

/**
* @brief SPI Initialization
* @param gd32_spi: SPI BUS
* @retval None
*/
static void gd32_spi_init(struct gd32_spi *gd32_spi)
{
    /* enable SPI clock */
    rcu_periph_clock_enable(gd32_spi->spi_clk);
    rcu_periph_clock_enable(gd32_spi->gpio_clk);

#if defined SOC_SERIES_GD32F4xx
    /*GPIO pin configuration*/
    gpio_af_set(gd32_spi->spi_port, gd32_spi->alt_func_num, gd32_spi->sck_pin | gd32_spi->mosi_pin | gd32_spi->miso_pin);

    gpio_mode_set(gd32_spi->spi_port, GPIO_MODE_AF, GPIO_PUPD_NONE, gd32_spi->sck_pin | gd32_spi->mosi_pin | gd32_spi->miso_pin);
    gpio_output_options_set(gd32_spi->spi_port, GPIO_OTYPE_PP, GPIO_OSPEED_200MHZ, gd32_spi->sck_pin | gd32_spi->mosi_pin | gd32_spi->miso_pin);
#else
    /* Init SPI SCK MOSI */
    gpio_init(gd32_spi->spi_port, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, gd32_spi->sck_pin | gd32_spi->mosi_pin);

    /* Init SPI MISO */
    gpio_init(gd32_spi->spi_port, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, gd32_spi->miso_pin);
#endif

}

static rt_err_t spi_configure(struct rt_spi_device* device,
                          struct rt_spi_configuration* configuration)
{
    struct rt_spi_bus * spi_bus = (struct rt_spi_bus *)device->bus;
    struct gd32_spi *spi_device = (struct gd32_spi *)spi_bus->parent.user_data;
    spi_parameter_struct spi_init_struct;
    uint32_t spi_periph = spi_device->spi_periph;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    //Init SPI
    gd32_spi_init(spi_device);

    /* data_width */
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

    /* baudrate */
    {
        rcu_clock_freq_enum spi_src;
        uint32_t spi_apb_clock;
        uint32_t max_hz;

        max_hz = configuration->max_hz;

        LOG_D("sys   freq: %d\n", rcu_clock_freq_get(CK_SYS));
        LOG_D("CK_APB2 freq: %d\n", rcu_clock_freq_get(CK_APB2));
        LOG_D("max   freq: %d\n", max_hz);

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

    spi_crc_off(spi_periph);

    /* init SPI */
    spi_init(spi_periph, &spi_init_struct);
    /* Enable SPI_MASTER */
    spi_enable(spi_periph);

    return RT_EOK;
};

static rt_ssize_t spixfer(struct rt_spi_device* device, struct rt_spi_message* message)
{
    struct rt_spi_bus * gd32_spi_bus = (struct rt_spi_bus *)device->bus;
    struct gd32_spi *spi_device = (struct gd32_spi *)gd32_spi_bus->parent.user_data;
    struct rt_spi_configuration * config = &device->config;
    struct gd32_spi_cs * gd32_spi_cs = device->parent.user_data;
    uint32_t spi_periph = spi_device->spi_periph;

    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    /* take CS */
    if(message->cs_take)
    {
        gpio_bit_reset(gd32_spi_cs->GPIOx, gd32_spi_cs->GPIO_Pin);
        LOG_D("spi take cs\n");
    }

    {
        if(config->data_width <= 8)
        {
            const rt_uint8_t * send_ptr = message->send_buf;
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

                // Todo: replace register read/write by gd32f4 lib
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
        gpio_bit_set(gd32_spi_cs->GPIOx, gd32_spi_cs->GPIO_Pin);
        LOG_D("spi release cs\n");
    }

    return message->length;
};

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    if(cs_pin != PIN_NONE)
    {
        /* initialize the cs pin && select the slave*/
        rt_pin_mode(cs_pin, PIN_MODE_OUTPUT);
        rt_pin_write(cs_pin, PIN_HIGH);
    }

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
    int i;

    for (i = 0; i < sizeof(spi_bus_obj) / sizeof(spi_bus_obj[0]); i++)
    {
        spi_bus_obj[i].spi_bus->parent.user_data = (void *)&spi_bus_obj[i];

        result = rt_spi_bus_register(spi_bus_obj[i].spi_bus, spi_bus_obj[i].bus_name, &gd32_spi_ops);

        RT_ASSERT(result == RT_EOK);

        LOG_D("%s bus init done", spi_bus_obj[i].bus_name);
    }

    return result;
}

INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* BSP_USING_SPI0 || BSP_USING_SPI1 || BSP_USING_SPI2 || BSP_USING_SPI3 || BSP_USING_SPI4*/
#endif /* RT_USING_SPI */
