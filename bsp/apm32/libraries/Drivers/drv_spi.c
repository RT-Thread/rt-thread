/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-04     stevetong459      first version
 * 2022-07-15     Aligagago         add APM32F4 series MCU support
 * 2022-12-26     luobeihai         add APM32F0 series MCU support
 * 2023-03-28     luobeihai         add APM32E1/S1 series MCU support
 */

#include "drv_spi.h"

//#define DRV_DEBUG
#define LOG_TAG               "drv.spi"
#include "drv_log.h"

#if defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3)

static struct apm32_spi_config spi_config[] = {
#ifdef BSP_USING_SPI1
    {SPI1, "spi1"},
#endif

#ifdef BSP_USING_SPI2
    {SPI2, "spi2"},
#endif

#ifdef BSP_USING_SPI3
    {SPI3, "spi3"},
#endif
};

static struct apm32_spi spi_bus_obj[sizeof(spi_config) / sizeof(spi_config[0])] = {0};

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, GPIO_T *cs_gpiox, uint16_t cs_gpio_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;
    struct apm32_spi_cs *cs_pin;
    GPIO_Config_T GPIO_InitStructure;

    /* initialize the cs pin && select the slave */
#if defined(SOC_SERIES_APM32F0)
    GPIO_ConfigStructInit(&GPIO_InitStructure);
    GPIO_InitStructure.pin = cs_gpio_pin;
    GPIO_InitStructure.speed = GPIO_SPEED_50MHz;
    GPIO_InitStructure.mode = GPIO_MODE_OUT;
    GPIO_InitStructure.outtype = GPIO_OUT_TYPE_PP;
    GPIO_InitStructure.pupd = GPIO_PUPD_NO;
    GPIO_Config(cs_gpiox, &GPIO_InitStructure);
    GPIO_WriteBitValue(cs_gpiox, cs_gpio_pin, Bit_SET);
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1)
    GPIO_ConfigStructInit(&GPIO_InitStructure);
    GPIO_InitStructure.pin = cs_gpio_pin;
    GPIO_InitStructure.mode = GPIO_MODE_OUT_PP;
    GPIO_InitStructure.speed = GPIO_SPEED_50MHz;
    GPIO_Config(cs_gpiox, &GPIO_InitStructure);
    GPIO_WriteBitValue(cs_gpiox, cs_gpio_pin, BIT_SET);
#elif defined(SOC_SERIES_APM32F4)
    GPIO_ConfigStructInit(&GPIO_InitStructure);
    GPIO_InitStructure.pin = cs_gpio_pin;
    GPIO_InitStructure.speed = GPIO_SPEED_100MHz;
    GPIO_InitStructure.mode = GPIO_MODE_OUT;
    GPIO_InitStructure.otype = GPIO_OTYPE_PP;
    GPIO_InitStructure.pupd = GPIO_PUPD_NOPULL;
    GPIO_Config(cs_gpiox, &GPIO_InitStructure);
    GPIO_WriteBitValue(cs_gpiox, cs_gpio_pin, BIT_SET);
#endif

    /* attach the device to spi bus */
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    cs_pin = (struct apm32_spi_cs *)rt_malloc(sizeof(struct apm32_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->GPIOx = cs_gpiox;
    cs_pin->GPIO_Pin = cs_gpio_pin;
    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    RT_ASSERT(result == RT_EOK);

    LOG_D("%s attach to %s done", device_name, bus_name);

    return result;
}

static rt_err_t apm32_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    SPI_Config_T hw_spi_config;

    struct rt_spi_bus * apm32_spi_bus = (struct rt_spi_bus *)device->bus;
    struct apm32_spi *spi_device = (struct apm32_spi *)apm32_spi_bus->parent.user_data;
    SPI_T *spi = spi_device->config->spi_x;

    uint32_t hw_spi_apb_clock;
#if (DBG_LVL == DBG_LOG)
    uint32_t hw_spi_sys_clock = RCM_ReadSYSCLKFreq();
#endif

    /* apm32 spi gpio init and enable clock */
    extern void apm32_msp_spi_init(void *Instance);
    apm32_msp_spi_init(spi);

    /* apm32 spi init */
    hw_spi_config.mode = (cfg->mode & RT_SPI_SLAVE) ? SPI_MODE_SLAVE : SPI_MODE_MASTER;
    hw_spi_config.direction = (cfg->mode & RT_SPI_3WIRE) ? SPI_DIRECTION_1LINE_RX : SPI_DIRECTION_2LINES_FULLDUPLEX;
    hw_spi_config.phase = (cfg->mode & RT_SPI_CPHA) ? SPI_CLKPHA_2EDGE : SPI_CLKPHA_1EDGE;
    hw_spi_config.polarity = (cfg->mode & RT_SPI_CPOL) ? SPI_CLKPOL_HIGH : SPI_CLKPOL_LOW;
#if defined(SOC_SERIES_APM32F0)
    hw_spi_config.slaveSelect = (cfg->mode & RT_SPI_NO_CS) ? SPI_SSC_DISABLE : SPI_SSC_ENABLE;
    hw_spi_config.firstBit = (cfg->mode & RT_SPI_MSB) ? SPI_FIRST_BIT_MSB : SPI_FIRST_BIT_LSB;
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
    hw_spi_config.nss = (cfg->mode & RT_SPI_NO_CS) ? SPI_NSS_HARD : SPI_NSS_SOFT;
    hw_spi_config.firstBit = (cfg->mode & RT_SPI_MSB) ? SPI_FIRSTBIT_MSB : SPI_FIRSTBIT_LSB;
#endif

    if (cfg->data_width == 8)
    {
        hw_spi_config.length = SPI_DATA_LENGTH_8B;
    }
    else if (cfg->data_width == 16)
    {
        hw_spi_config.length = SPI_DATA_LENGTH_16B;
    }
    else
    {
        return -RT_EIO;
    }

#if defined(SOC_SERIES_APM32F0)
    hw_spi_apb_clock = RCM_ReadPCLKFreq();
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
    if (spi == SPI1)
    {
        RCM_ReadPCLKFreq(NULL, &hw_spi_apb_clock);
    }
    else
    {
        RCM_ReadPCLKFreq(&hw_spi_apb_clock, NULL);
    }
#endif

    if (cfg->max_hz >= hw_spi_apb_clock / 2)
    {
        hw_spi_config.baudrateDiv = SPI_BAUDRATE_DIV_2;
    }
    else if (cfg->max_hz >= hw_spi_apb_clock / 4)
    {
        hw_spi_config.baudrateDiv = SPI_BAUDRATE_DIV_4;
    }
    else if (cfg->max_hz >= hw_spi_apb_clock / 8)
    {
        hw_spi_config.baudrateDiv = SPI_BAUDRATE_DIV_8;
    }
    else if (cfg->max_hz >= hw_spi_apb_clock / 16)
    {
        hw_spi_config.baudrateDiv = SPI_BAUDRATE_DIV_16;
    }
    else if (cfg->max_hz >= hw_spi_apb_clock / 32)
    {
        hw_spi_config.baudrateDiv = SPI_BAUDRATE_DIV_32;
    }
    else if (cfg->max_hz >= hw_spi_apb_clock / 64)
    {
        hw_spi_config.baudrateDiv = SPI_BAUDRATE_DIV_64;
    }
    else if (cfg->max_hz >= hw_spi_apb_clock / 128)
    {
        hw_spi_config.baudrateDiv = SPI_BAUDRATE_DIV_128;
    }
    else
    {
        /* min prescaler 256 */
        hw_spi_config.baudrateDiv = SPI_BAUDRATE_DIV_256;
    }

    LOG_D("sys freq: %d, pclk2 freq: %d, SPI limiting freq: %d, BaudRatePrescaler: %d",
          hw_spi_sys_clock, hw_spi_apb_clock, cfg->max_hz, hw_spi_config.baudrateDiv);

#if defined(SOC_SERIES_APM32F0)
    SPI_DisableCRC(spi);
    SPI_EnableSSoutput(spi);
    SPI_ConfigFIFOThreshold(spi, SPI_RXFIFO_QUARTER);
#endif

    SPI_Config(spi, &hw_spi_config);
    SPI_Enable(spi);

    return RT_EOK;
}

static rt_ssize_t apm32_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    struct rt_spi_configuration *config = &device->config;

    struct apm32_spi_cs *cs = device->parent.user_data;

    struct rt_spi_bus * apm32_spi_bus = (struct rt_spi_bus *)device->bus;
    struct apm32_spi *spi_device = (struct apm32_spi *)apm32_spi_bus->parent.user_data;
    SPI_T *spi = spi_device->config->spi_x;

    /* take CS */
    if (message->cs_take)
    {
#if defined(SOC_SERIES_APM32F0)
        GPIO_WriteBitValue(cs->GPIOx, cs->GPIO_Pin, (GPIO_BSRET_T)RESET);
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
        GPIO_WriteBitValue(cs->GPIOx, cs->GPIO_Pin, RESET);
#endif
        LOG_D("spi take cs\n");
    }

    if (config->data_width <= 8)
    {
        const rt_uint8_t *send_ptr = message->send_buf;
        rt_uint8_t *recv_ptr = message->recv_buf;
        rt_uint32_t size = message->length;

        LOG_D("spi poll transfer start: %d\n", size);

        while (size--)
        {
            rt_uint8_t data = 0xFF;

            if (send_ptr != RT_NULL)
            {
                data = *send_ptr++;
            }

#if defined(SOC_SERIES_APM32F0)
            /* Wait until the transmit buffer is empty */
            while (SPI_ReadStatusFlag(spi, SPI_FLAG_TXBE) == RESET);
            SPI_TxData8(spi, data);

            /* Wait until a data is received */
            while (SPI_ReadStatusFlag(spi, SPI_FLAG_RXBNE) == RESET);
            data = SPI_RxData8(spi);
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32F4)
            /* Wait until the transmit buffer is empty */
            while (SPI_I2S_ReadStatusFlag(spi, SPI_FLAG_TXBE) == RESET);
            SPI_I2S_TxData(spi, data);

            /* Wait until a data is received */
            while (SPI_I2S_ReadStatusFlag(spi, SPI_FLAG_RXBNE) == RESET);
            data = SPI_I2S_RxData(spi);
#elif defined(SOC_SERIES_APM32S1)
            /* Wait until the transmit buffer is empty */
            while (SPI_ReadStatusFlag(spi, SPI_FLAG_TXBE) == RESET);
            SPI_TxData(spi, data);

            /* Wait until a data is received */
            while (SPI_ReadStatusFlag(spi, SPI_FLAG_RXBNE) == RESET);
            data = SPI_RxData(spi);
#endif

            if (recv_ptr != RT_NULL)
            {
                *recv_ptr++ = data;
            }
        }
        LOG_D("spi poll transfer finsh\n");
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

#if defined(SOC_SERIES_APM32F0)
            /* Wait until the transmit buffer is empty */
            while (SPI_ReadStatusFlag(spi, SPI_FLAG_TXBE) == RESET);
            SPI_I2S_TxData16(spi, data);

            /* Wait until a data is received */
            while (SPI_ReadStatusFlag(spi, SPI_FLAG_RXBNE) == RESET);
            data = SPI_I2S_RxData16(spi);
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32F4)
            /* Wait until the transmit buffer is empty */
            while (SPI_I2S_ReadStatusFlag(spi, SPI_FLAG_TXBE) == RESET);
            /* Send the byte */
            SPI_I2S_TxData(spi, data);

            /* Wait until a data is received */
            while (SPI_I2S_ReadStatusFlag(spi, SPI_FLAG_RXBNE) == RESET);
            /* Get the received data */
            data = SPI_I2S_RxData(spi);
#elif defined(SOC_SERIES_APM32S1)
            /* Wait until the transmit buffer is empty */
            while (SPI_ReadStatusFlag(spi, SPI_FLAG_TXBE) == RESET);
            /* Send the byte */
            SPI_TxData(spi, data);

            /* Wait until a data is received */
            while (SPI_ReadStatusFlag(spi, SPI_FLAG_RXBNE) == RESET);
            /* Get the received data */
            data = SPI_RxData(spi);
#endif

            if (recv_ptr != RT_NULL)
            {
                *recv_ptr++ = data;
            }
        }
    }

    /* release CS */
    if (message->cs_release)
    {
#if defined(SOC_SERIES_APM32F0)
        GPIO_WriteBitValue(cs->GPIOx, cs->GPIO_Pin, (GPIO_BSRET_T)SET);
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
        GPIO_WriteBitValue(cs->GPIOx, cs->GPIO_Pin, SET);
#endif
        LOG_D("spi release cs\n");
    }

    return message->length;
};

static const struct rt_spi_ops apm32_spi_ops =
{
    apm32_spi_configure,
    apm32_spi_xfer
};

static int rt_hw_spi_init(void)
{
    rt_err_t result;

    for (int i = 0; i < sizeof(spi_config) / sizeof(spi_config[0]); i++)
    {
        spi_bus_obj[i].config = &spi_config[i];
        spi_bus_obj[i].spi_bus.parent.user_data = (void *)&spi_bus_obj[i];
        result = rt_spi_bus_register(&spi_bus_obj[i].spi_bus, spi_config[i].spi_bus_name, &apm32_spi_ops);
        RT_ASSERT(result == RT_EOK);

        LOG_D("%s bus init done", spi_config[i].spi_bus_name);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* RT_USING_SPI */
