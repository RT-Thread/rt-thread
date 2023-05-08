/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-15     Jonas        first version
 */

#include <board.h>
#include "drv_spi.h"

#ifdef RT_USING_SPI
#if !defined(BSP_USING_SPI1) && !defined(BSP_USING_SPI2) && \
    !defined(BSP_USING_SPI3) && !defined(BSP_USING_SPI4)
    #error "Please define at least one SPIx"
#endif

//#define DEBUG

#define ARR_LEN(__N)      (sizeof(__N) / sizeof(__N[0]))

#ifdef DEBUG
    #define DEBUG_PRINTF(...)   rt_kprintf(__VA_ARGS__)
#else
    #define DEBUG_PRINTF(...)
#endif

/* private rt-thread spi ops function */
static rt_err_t configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration);
static rt_uint32_t xfer(struct rt_spi_device *device, struct rt_spi_message *message);

static struct rt_spi_ops hk32_spi_ops =
{
    configure,
    xfer
};

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, GPIO_TypeDef *cs_gpiox, uint16_t cs_gpio_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;
    struct hk32_spi_cs *cs_pin;

    /* initialize the cs pin && select the slave*/
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = cs_gpio_pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(cs_gpiox, &GPIO_InitStruct);
    GPIO_SetBits(cs_gpiox, cs_gpio_pin);

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    cs_pin = (struct hk32_spi_cs *)rt_malloc(sizeof(struct hk32_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->GPIOx = cs_gpiox;
    cs_pin->GPIO_Pin = cs_gpio_pin;
    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

    if (result != RT_EOK)
    {
        DEBUG_PRINTF("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    RT_ASSERT(result == RT_EOK);

    DEBUG_PRINTF("%s attach to %s done", device_name, bus_name);

    return result;
}

static rt_err_t configure(struct rt_spi_device *device,
                          struct rt_spi_configuration *configuration)
{
    struct rt_spi_bus *spi_bus = (struct rt_spi_bus *)device->bus;
    struct hk32_spi *spi_instance = (struct hk32_spi *)spi_bus->parent.user_data;

    SPI_InitTypeDef SPI_InitStruct;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    hk32_msp_spi_init(spi_instance->config->spix);

    /* data_width */
    if (configuration->data_width <= 8)
    {
        SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    }
    else if (configuration->data_width <= 16)
    {
        SPI_InitStruct.SPI_DataSize = SPI_DataSize_16b;
    }
    else
    {
        return -RT_EIO;
    }

    /* baudrate */
    {
        uint32_t spi_apb_clock;
        uint32_t max_hz;
        RCC_ClocksTypeDef  RCC_Clocks;

        max_hz = configuration->max_hz;

        RCC_GetClocksFreq(&RCC_Clocks);
        DEBUG_PRINTF("sys   freq: %d\n", RCC_Clocks.SYSCLK_Freq);
        DEBUG_PRINTF("max   freq: %d\n", max_hz);

        if (spi_instance->config->spix == SPI1)
        {
            spi_apb_clock = RCC_Clocks.PCLK_Frequency;
            DEBUG_PRINTF("pclk freq: %d\n", RCC_Clocks.PCLK_Frequency);
        }
        else
        {
            spi_apb_clock = RCC_Clocks.PCLK_Frequency;
            DEBUG_PRINTF("pclk1 freq: %d\n", RCC_Clocks.PCLK_Frequency);
        }

        if (max_hz >= spi_apb_clock / 2)
        {
            SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
        }
        else if (max_hz >= spi_apb_clock / 4)
        {
            SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
        }
        else if (max_hz >= spi_apb_clock / 8)
        {
            SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
        }
        else if (max_hz >= spi_apb_clock / 16)
        {
            SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
        }
        else if (max_hz >= spi_apb_clock / 32)
        {
            SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
        }
        else if (max_hz >= spi_apb_clock / 64)
        {
            SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
        }
        else if (max_hz >= spi_apb_clock / 128)
        {
            SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
        }
        else
        {
            /*  min prescaler 256 */
            SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
        }
    } /* baudrate */

    switch (configuration->mode & RT_SPI_MODE_3)
    {
    case RT_SPI_MODE_0:
        SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
        SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
        break;
    case RT_SPI_MODE_1:
        SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
        SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
        break;
    case RT_SPI_MODE_2:
        SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
        SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
        break;
    case RT_SPI_MODE_3:
        SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
        SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
        break;
    }

    /* MSB or LSB */
    if (configuration->mode & RT_SPI_MSB)
    {
        SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    }
    else
    {
        SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_LSB;
    }

    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;

    /* init SPI */
    SPI_Init(spi_instance->config->spix, &SPI_InitStruct);
    /* Enable SPI_MASTER */
    SPI_Cmd(spi_instance->config->spix, ENABLE);
    SPI_CalculateCRC(spi_instance->config->spix, DISABLE);

    return RT_EOK;
};

static rt_uint32_t xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct rt_spi_bus *hk32_spi_bus = (struct rt_spi_bus *)device->bus;
    struct hk32_spi *spi_instance = (struct hk32_spi *)hk32_spi_bus->parent.user_data;
    struct rt_spi_configuration *config = &device->config;
    struct hk32_spi_cs *hk32_spi_cs = device->parent.user_data;

    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    /* take CS */
    if (message->cs_take)
    {
        GPIO_ResetBits(hk32_spi_cs->GPIOx, hk32_spi_cs->GPIO_Pin);
        DEBUG_PRINTF("spi take cs\n");
    }

    {
        if (config->data_width <= 8)
        {
            const rt_uint8_t *send_ptr = message->send_buf;
            rt_uint8_t *recv_ptr = message->recv_buf;
            rt_uint32_t size = message->length;

            DEBUG_PRINTF("spi poll transfer start: %d\n", size);

            while (size--)
            {
                rt_uint8_t data = 0xFF;

                if (send_ptr != RT_NULL)
                {
                    data = *send_ptr++;
                }

                /* Todo: replace register read/write by hk32 lib */
                /* Wait until the transmit buffer is empty */
                while (RESET == SPI_I2S_GetFlagStatus(spi_instance->config->spix, SPI_I2S_FLAG_TXE));
                /*  Send the byte */
                SPI_SendData8(spi_instance->config->spix, data);

                /* Wait until a data is received */
                while (RESET == SPI_I2S_GetFlagStatus(spi_instance->config->spix, SPI_I2S_FLAG_RXNE));
                /* Get the received data */
                data = SPI_ReceiveData8(spi_instance->config->spix);

                if (recv_ptr != RT_NULL)
                {
                    *recv_ptr++ = data;
                }
            }
            DEBUG_PRINTF("spi poll transfer finsh\n");
        }
        else if (config->data_width <= 16)
        {
            const rt_uint16_t *send_ptr = message->send_buf;
            rt_uint16_t *recv_ptr = message->recv_buf;
            rt_uint32_t size = message->length;

            while (size--)
            {
                rt_uint16_t data = 0xFF;

                if (send_ptr != RT_NULL)
                {
                    data = *send_ptr++;
                }

                /* Wait until the transmit buffer is empty */
                while (RESET == SPI_I2S_GetFlagStatus(spi_instance->config->spix, SPI_I2S_FLAG_TXE));
                /* Send the byte */
                SPI_I2S_SendData16(spi_instance->config->spix, data);

                /* Wait until a data is received */
                while (RESET == SPI_I2S_GetFlagStatus(spi_instance->config->spix, SPI_I2S_FLAG_RXNE));
                /*  Get the received data */
                data = SPI_I2S_ReceiveData16(spi_instance->config->spix);

                if (recv_ptr != RT_NULL)
                {
                    *recv_ptr++ = data;
                }
            }
        }
    }

    /* release CS */
    if (message->cs_release)
    {
        GPIO_SetBits(hk32_spi_cs->GPIOx, hk32_spi_cs->GPIO_Pin);
        DEBUG_PRINTF("spi release cs\n");
    }

    return message->length;
};

static struct hk32_spi_config configs[] =
{
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

static struct hk32_spi spis[sizeof(configs) / sizeof(configs[0])] = {0};

int rt_hw_spi_init(void)
{
    int i;
    rt_err_t result;
    rt_size_t obj_num = sizeof(spis) / sizeof(struct hk32_spi);

    for (i = 0; i < obj_num; i++)
    {
        spis[i].config = &configs[i];
        spis[i].spi_bus.parent.user_data = (void *)&spis[i];
        result = rt_spi_bus_register(&(spis[i].spi_bus), spis[i].config->spi_name, &hk32_spi_ops);
    }

    return result;
}

INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif
