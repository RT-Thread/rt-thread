/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-06     BalanceTWK        first version
 * 2022-04-16     wolfJane          fix spixfer, add time out check
 */

#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_SPI
#ifdef BSP_USING_SPI

#if defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3) || defined(BSP_USING_SPI4) || defined(BSP_USING_SPI5) || defined(BSP_USING_SPI6)

#include "drv_spi.h"
#define DRV_DEBUG
#define LOG_TAG              "drv.spi"
#include <drv_log.h>

#define SPI_TIME_OUT    (1000)

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
#ifdef BSP_USING_SPI5
    SPI5_INDEX,
#endif
#ifdef BSP_USING_SPI6
    SPI6_INDEX,
#endif
};

struct n32_spi_config
{
    SPI_Module *module;
    char *bus_name;
};
/* n32 spi dirver class */
struct n32_spi
{
    SPI_InitType SPI_InitStructure;
    struct n32_spi_config *config;
    struct rt_spi_configuration *cfg;

    struct rt_spi_bus spi_bus;
};

static struct n32_spi_config spi_config[] =
{
#ifdef BSP_USING_SPI1
    {
        .module = SPI1,
        .bus_name = "spi1",
    },
#endif

#ifdef BSP_USING_SPI2
    {
        .module = SPI2,
        .bus_name = "spi2",
    },
#endif

#ifdef BSP_USING_SPI3
    {
        .module = SPI3,
        .bus_name = "spi3",
    },
#endif

};

static struct n32_spi spi_bus_obj[sizeof(spi_config) / sizeof(spi_config[0])] = {0};

static rt_err_t n32_spi_init(struct n32_spi *spi_drv, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(spi_drv != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    SPI_InitType *SPI_InitStructure = &spi_drv->SPI_InitStructure;
    SPI_Module *spi_handle = spi_drv->config->module;

    /* GPIO configuration ------------------------------------------------------*/
    n32_msp_spi_init(spi_drv->config->module);

    if (cfg->mode & RT_SPI_SLAVE)
    {
        /* SPI_InitStructure->SpiMode = SPI_MODE_SLAVE; */
        return -RT_ERROR;
    }
    else
    {
        SPI_InitStructure->SpiMode = SPI_MODE_MASTER;
    }

    if (cfg->mode & RT_SPI_3WIRE)
    {
        SPI_InitStructure->DataDirection = SPI_DIR_SINGLELINE_TX;
    }
    else
    {
        SPI_InitStructure->DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    }

    if (cfg->data_width == 8)
    {
        SPI_InitStructure->DataLen = SPI_DATA_SIZE_8BITS;
    }
    else if (cfg->data_width == 16)
    {
        SPI_InitStructure->DataLen = SPI_DATA_SIZE_16BITS;
    }
    else
    {
        return -RT_EIO;
    }

    if (cfg->mode & RT_SPI_CPHA)
    {
        SPI_InitStructure->CLKPHA = SPI_CLKPHA_SECOND_EDGE;
    }
    else
    {
        SPI_InitStructure->CLKPHA = SPI_CLKPHA_FIRST_EDGE;
    }

    if (cfg->mode & RT_SPI_CPOL)
    {
        SPI_InitStructure->CLKPOL = SPI_CLKPOL_HIGH;
    }
    else
    {
        SPI_InitStructure->CLKPOL = SPI_CLKPOL_LOW;
    }

    if (cfg->mode & RT_SPI_NO_CS)
    {
        SPI_InitStructure->NSS = SPI_NSS_HARD;
    }
    else
    {
        SPI_InitStructure->NSS = SPI_NSS_SOFT;
    }

    RCC_ClocksType RCC_Clock;
    RCC_GetClocksFreqValue(&RCC_Clock);
    rt_uint64_t SPI_APB_CLOCK;

    if (SPI1 == spi_handle)
    {
        SPI_APB_CLOCK = RCC_Clock.Pclk1Freq;
    }
    else if (SPI2 == spi_handle ||  SPI3 == spi_handle)
    {
        SPI_APB_CLOCK = RCC_Clock.Pclk2Freq;
    }

    if (cfg->max_hz >= SPI_APB_CLOCK / 2)
    {
        SPI_InitStructure->BaudRatePres = SPI_BR_PRESCALER_2;
    }
    else if (cfg->max_hz >= SPI_APB_CLOCK / 4)
    {
        SPI_InitStructure->BaudRatePres = SPI_BR_PRESCALER_4;
    }
    else if (cfg->max_hz >= SPI_APB_CLOCK / 8)
    {
        SPI_InitStructure->BaudRatePres = SPI_BR_PRESCALER_8;
    }
    else if (cfg->max_hz >= SPI_APB_CLOCK / 16)
    {
        SPI_InitStructure->BaudRatePres = SPI_BR_PRESCALER_16;
    }
    else if (cfg->max_hz >= SPI_APB_CLOCK / 32)
    {
        SPI_InitStructure->BaudRatePres = SPI_BR_PRESCALER_32;
    }
    else if (cfg->max_hz >= SPI_APB_CLOCK / 64)
    {
        SPI_InitStructure->BaudRatePres = SPI_BR_PRESCALER_64;
    }
    else if (cfg->max_hz >= SPI_APB_CLOCK / 128)
    {
        SPI_InitStructure->BaudRatePres = SPI_BR_PRESCALER_128;
    }
    else
    {
        SPI_InitStructure->BaudRatePres = SPI_BR_PRESCALER_256;
    }

    if (cfg->mode & RT_SPI_MSB)
    {
        SPI_InitStructure->FirstBit = SPI_FB_MSB;
    }
    else
    {
        SPI_InitStructure->FirstBit = SPI_FB_LSB;
    }

    SPI_InitStructure->CRCPoly       = 7;

    SPI_Init(spi_handle, SPI_InitStructure);
    /* Enable SPI_MASTER TXE interrupt */
    SPI_I2S_EnableInt(spi_handle, SPI_I2S_INT_TE, ENABLE);

    /* Enable SPI_MASTER */
    SPI_Enable(spi_handle, ENABLE);

    return RT_EOK;
}

static rt_err_t spi_configure(struct rt_spi_device *device,
                              struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    struct n32_spi *spi_drv =  rt_container_of(device->bus, struct n32_spi, spi_bus);
    spi_drv->cfg = configuration;

    return n32_spi_init(spi_drv, configuration);
}

static rt_ssize_t _spi_recv(SPI_Module *hspi,
        uint8_t *tx_buff,
        uint8_t *rx_buff,
        uint32_t length,
        uint32_t timeout)
{
    /* Init tickstart for timeout management*/
    uint32_t tickstart = rt_tick_get();
    uint8_t dat = 0;

    if ((tx_buff == RT_NULL) && (rx_buff == RT_NULL) || (length == 0))
    {
        return -RT_EIO;
    }

    while (length--)
    {
        while (SPI_I2S_GetStatus(hspi, SPI_I2S_TE_FLAG) == RESET)
        {
            if ((rt_tick_get() - tickstart) > timeout)
            {
                return -RT_ETIMEOUT;
            }
        }
        SPI_I2S_TransmitData(hspi, *tx_buff++);

        while (SPI_I2S_GetStatus(hspi, SPI_I2S_RNE_FLAG) == RESET)
        {
            if ((rt_tick_get() - tickstart) > timeout)
            {
                return -RT_ETIMEOUT;
            }
        }
        dat = SPI_I2S_ReceiveData(hspi);

        if (rx_buff)
        {
            *rx_buff++ = dat;
        }
    }
    return RT_EOK;
}

static rt_ssize_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_size_t send_length;
    rt_uint8_t *recv_buf;
    const rt_uint8_t *send_buf;
    rt_ssize_t stat = RT_EOK;

    /* Check Direction parameter */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    struct n32_spi *spi_drv =  rt_container_of(device->bus, struct n32_spi, spi_bus);
    struct n32_hw_spi_cs *cs = device->parent.user_data;
    SPI_Module *spi_handle = spi_drv->config->module;

    if (message->cs_take && !(device->config.mode & RT_SPI_NO_CS))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
        {
            GPIO_SetBits(cs->module, cs->pin);
        }
        else
        {
            GPIO_ResetBits(cs->module, cs->pin);
        }
    }

    send_length = message->length;
    recv_buf = message->recv_buf;
    send_buf = message->send_buf;

    /* start once data exchange in DMA mode */
    if (message->send_buf && message->recv_buf)
    {
        LOG_D("%s:%d", __FUNCTION__, __LINE__);
        stat = -RT_EIO;
    }
    else if (message->send_buf)
    {
        stat = _spi_recv(spi_handle,
                         (uint8_t *)send_buf,
                         RT_NULL,
                         send_length,
                         SPI_TIME_OUT);
    }
    else
    {
        rt_memset(recv_buf, 0xff, send_length);
        stat = _spi_recv(spi_handle,
                         (uint8_t *)recv_buf,
                         (uint8_t *)recv_buf,
                         send_length,
                         SPI_TIME_OUT);
    }

    if (message->cs_release && !(device->config.mode & RT_SPI_NO_CS))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
        {
            GPIO_ResetBits(cs->module, cs->pin);
        }
        else
        {
            GPIO_SetBits(cs->module, cs->pin);
        }
    }

    if (stat != RT_EOK)
    {
        send_length = 0;
    }

    return send_length;
}

static const struct rt_spi_ops n32_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer,
};

static int rt_hw_spi_bus_init(void)
{
    rt_err_t result;
    for (int i = 0; i < sizeof(spi_config) / sizeof(spi_config[0]); i++)
    {
        spi_bus_obj[i].config = &spi_config[i];
        spi_bus_obj[i].spi_bus.parent.user_data = &spi_config[i];
        result = rt_spi_bus_register(&spi_bus_obj[i].spi_bus, spi_config[i].bus_name, &n32_spi_ops);
        RT_ASSERT(result == RT_EOK);

        LOG_D("%s bus init done", spi_config[i].bus_name);
    }

    return result;
}
int rt_hw_spi_init(void)
{
    /* TODO: n32_get_dma_info(); */
    return rt_hw_spi_bus_init();
}
INIT_BOARD_EXPORT(rt_hw_spi_init);


/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, GPIO_Module *cs_gpiox, uint32_t cs_gpio_pin)
{
    rt_err_t result;
    struct rt_spi_device *spi_device;
    struct n32_hw_spi_cs *cs_pin;
    GPIO_InitType GPIO_InitStructure;

    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);


    /* Enable the GPIO Clock */
    if (cs_gpiox == GPIOA)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    }
    else if (cs_gpiox == GPIOB)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    }
    else if (cs_gpiox == GPIOC)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    }
    else if (cs_gpiox == GPIOD)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
    }
    else if (cs_gpiox == GPIOE)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOE, ENABLE);
    }
    else if (cs_gpiox == GPIOF)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOF, ENABLE);
    }
    else if (cs_gpiox == GPIOG)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOG, ENABLE);
    }

    /* Configure the GPIO pin */
    if (cs_gpio_pin <= GPIO_PIN_ALL)
    {
        GPIO_InitStructure.Pin        = cs_gpio_pin;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitPeripheral(cs_gpiox, &GPIO_InitStructure);
    }

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    cs_pin = (struct n32_hw_spi_cs *)rt_malloc(sizeof(struct n32_hw_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->module = cs_gpiox;
    cs_pin->pin = cs_gpio_pin;

    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    RT_ASSERT(result == RT_EOK);

    LOG_D("%s attach to %s done", device_name, bus_name);

    return result;
}

#endif /* BSP_USING_SPIx */

#endif /* BSP_USING_SPI */
#endif /* RT_USING_SPI */

