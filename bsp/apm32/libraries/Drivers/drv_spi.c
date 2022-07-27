/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-04     stevetong459      first version
 * 2022-07-15     Aligagago         add apm32F4 serie MCU support
 */

#include "drv_spi.h"

#define LOG_TAG               "drv.spi"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

#if defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3)

static rt_err_t _spi_configure(struct rt_spi_device *spi_drv, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(spi_drv != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    SPI_Config_T hw_spi_config;
    SPI_T *spi = (SPI_T *)spi_drv->bus->parent.user_data;
    uint32_t hw_spi_apb_clock;
#if (DBG_LVL == DBG_LOG)
    uint32_t hw_spi_sys_clock = RCM_ReadSYSCLKFreq();
#endif

    hw_spi_config.mode = (cfg->mode & RT_SPI_SLAVE) ? SPI_MODE_SLAVE : SPI_MODE_MASTER;
    hw_spi_config.direction = (cfg->mode & RT_SPI_3WIRE) ? SPI_DIRECTION_1LINE_RX : SPI_DIRECTION_2LINES_FULLDUPLEX;
    hw_spi_config.phase = (cfg->mode & RT_SPI_CPHA) ? SPI_CLKPHA_2EDGE : SPI_CLKPHA_1EDGE;
    hw_spi_config.polarity = (cfg->mode & RT_SPI_CPOL) ? SPI_CLKPOL_HIGH : SPI_CLKPOL_LOW;
    hw_spi_config.nss = (cfg->mode & RT_SPI_NO_CS) ? SPI_NSS_HARD : SPI_NSS_SOFT;
    hw_spi_config.firstBit = (cfg->mode & RT_SPI_MSB) ? SPI_FIRSTBIT_MSB : SPI_FIRSTBIT_LSB;

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
        return RT_EIO;
    }

    RCM_ReadPCLKFreq(NULL, &hw_spi_apb_clock);

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
        /*  min prescaler 256 */
        hw_spi_config.baudrateDiv = SPI_BAUDRATE_DIV_256;
    }

    LOG_D("sys freq: %d, pclk2 freq: %d, SPI limiting freq: %d, BaudRatePrescaler: %d",
          hw_spi_sys_clock, hw_spi_apb_clock, cfg->max_hz, hw_spi_config.baudrateDiv);

    SPI_Config(spi, &hw_spi_config);
    SPI_Enable(spi);

    return RT_EOK;
}

static rt_uint32_t _spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    rt_base_t cs_pin = (rt_base_t)device->parent.user_data;
    SPI_T *spi = (SPI_T *)device->bus->parent.user_data;
    struct rt_spi_configuration *config = &device->config;

    /* take CS */
    if (message->cs_take)
    {
        rt_pin_write(cs_pin, PIN_LOW);
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

            /* Wait until the transmit buffer is empty */
            while (SPI_I2S_ReadStatusFlag(spi, SPI_FLAG_TXBE) == RESET);

            SPI_I2S_TxData(spi, data);

            /* Wait until a data is received */
            while (SPI_I2S_ReadStatusFlag(spi, SPI_FLAG_RXBNE) == RESET);

            data = SPI_I2S_RxData(spi);

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

            /*Wait until the transmit buffer is empty */
            while (SPI_I2S_ReadStatusFlag(spi, SPI_FLAG_TXBE) == RESET);
            /* Send the byte */
            SPI_I2S_TxData(spi, data);

            /*Wait until a data is received */
            while (SPI_I2S_ReadStatusFlag(spi, SPI_FLAG_RXBNE) == RESET);
            /* Get the received data */
            data = SPI_I2S_RxData(spi);

            if (recv_ptr != RT_NULL)
            {
                *recv_ptr++ = data;
            }
        }
    }

    /* release CS */
    if (message->cs_release)
    {
        rt_pin_write(cs_pin, PIN_HIGH);
        LOG_D("spi release cs\n");
    }

    return message->length;
};

static const struct rt_spi_ops _spi_ops =
{
    _spi_configure,
    _spi_xfer
};

static int rt_hw_spi_init(void)
{
    int result = 0;
    GPIO_Config_T gpio_config;

#ifdef APM32F10X_HD
#ifdef BSP_USING_SPI1
    static struct rt_spi_bus spi_bus1;
    spi_bus1.parent.user_data = (void *)SPI1;

    result = rt_spi_bus_register(&spi_bus1, "spi1", &_spi_ops);

    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SPI1);

    /* SPI1_SCK(PA5)  SPI1_MOSI(PA7) */
    gpio_config.mode = GPIO_MODE_AF_PP;
    gpio_config.speed = GPIO_SPEED_50MHz;
    gpio_config.pin = (GPIO_PIN_5 | GPIO_PIN_7);
    GPIO_Config(GPIOA, &gpio_config);
    /* SPI1_MISO(PA6) */
    gpio_config.mode = GPIO_MODE_IN_FLOATING;
    gpio_config.speed = GPIO_SPEED_50MHz;
    gpio_config.pin = GPIO_PIN_6;
    GPIO_Config(GPIOA, &gpio_config);
#endif

#ifdef BSP_USING_SPI2
    static struct rt_spi_bus spi_bus2;
    spi_bus2.parent.user_data = (void *)SPI2;

    result = rt_spi_bus_register(&spi_bus2, "spi2", &_spi_ops);

    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOB);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_SPI2);

    /* SPI2_SCK(PB13)  SPI2_MOSI(PB15) */
    gpio_config.mode = GPIO_MODE_AF_PP;
    gpio_config.speed = GPIO_SPEED_50MHz;
    gpio_config.pin = (GPIO_PIN_13 | GPIO_PIN_15);
    GPIO_Config(GPIOB, &gpio_config);
    /* SPI2_MISO(PB14) */
    gpio_config.mode = GPIO_MODE_IN_FLOATING;
    gpio_config.speed = GPIO_SPEED_50MHz;
    gpio_config.pin = GPIO_PIN_14;
    GPIO_Config(GPIOB, &gpio_config);
#endif

#ifdef BSP_USING_SPI3
    static struct rt_spi_bus spi_bus3;
    spi_bus3.parent.user_data = (void *)SPI3;

    result = rt_spi_bus_register(&spi_bus3, "spi3", &_spi_ops);

    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOB);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_SPI3);

    /* SPI3_SCK(PB3)  SPI3_MOSI(PB5) */
    gpio_config.mode = GPIO_MODE_AF_PP;
    gpio_config.speed = GPIO_SPEED_50MHz;
    gpio_config.pin = (GPIO_PIN_3 | GPIO_PIN_5);
    GPIO_Config(GPIOB, &gpio_config);
    /* SPI3_MISO(PB4) */
    gpio_config.mode = GPIO_MODE_IN_FLOATING;
    gpio_config.speed = GPIO_SPEED_50MHz;
    gpio_config.pin = GPIO_PIN_4;
    GPIO_Config(GPIOB, &gpio_config);
#endif
#elif APM32F40X
#ifdef BSP_USING_SPI1
    static struct rt_spi_bus spi_bus1;
    spi_bus1.parent.user_data = (void *)SPI1;

    result = rt_spi_bus_register(&spi_bus1, "spi1", &_spi_ops);

    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SPI1);

    /* Config SPI1 PinAF */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_4, GPIO_AF_SPI1);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_5, GPIO_AF_SPI1);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_6, GPIO_AF_SPI1);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_7, GPIO_AF_SPI1);

    /* SPI1_NSS(PA4) SPI1_SCK(PA5) SPI1_MISO(PA6) SPI1_MOSI(PA7) */
    gpio_config.mode = GPIO_MODE_AF;
    gpio_config.speed = GPIO_SPEED_100MHz;
    gpio_config.otype = GPIO_OTYPE_PP;
    gpio_config.pupd = GPIO_PUPD_NOPULL;
    gpio_config.pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_Config(GPIOA, &gpio_config);
#endif

#ifdef BSP_USING_SPI2
    static struct rt_spi_bus spi_bus2;
    spi_bus2.parent.user_data = (void *)SPI2;

    result = rt_spi_bus_register(&spi_bus2, "spi2", &_spi_ops);

    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOB);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_SPI2);

    /* Config SPI2 PinAF */
    GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_12, GPIO_AF_SPI2);
    GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_13, GPIO_AF_SPI2);
    GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_14, GPIO_AF_SPI2);
    GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_15, GPIO_AF_SPI2);

    /* SPI2_NSS(PB12) SPI2_SCK(PB13) SPI2_MISO(PB14) SPI2_MOSI(PB15) */
    gpio_config.mode = GPIO_MODE_AF;
    gpio_config.speed = GPIO_SPEED_100MHz;
    gpio_config.otype = GPIO_OTYPE_PP;
    gpio_config.pupd = GPIO_PUPD_NOPULL;
    gpio_config.pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_Config(GPIOB, &gpio_config);
#endif

#ifdef BSP_USING_SPI3
    static struct rt_spi_bus spi_bus3;
    spi_bus3.parent.user_data = (void *)SPI3;

    result = rt_spi_bus_register(&spi_bus3, "spi3", &_spi_ops);

    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA);
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOB);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_SPI3);

    /* Config SPI3 PinAF */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_4, GPIO_AF_SPI3);
    GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_3, GPIO_AF_SPI3);
    GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_4, GPIO_AF_SPI3);
    GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_5, GPIO_AF_SPI3);

    /* SPI3_SCK(PB3) SPI3_MISO(PB4) SPI3_MOSI(PB5) */
    gpio_config.mode = GPIO_MODE_AF;
    gpio_config.speed = GPIO_SPEED_100MHz;
    gpio_config.otype = GPIO_OTYPE_PP;
    gpio_config.pupd = GPIO_PUPD_NOPULL;
    gpio_config.pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
    GPIO_Config(GPIOB, &gpio_config);
    /* SPI3_NSS(PA4) */
    gpio_config.pin = GPIO_PIN_4;
    GPIO_Config(GPIOA, &gpio_config);
#endif
#endif
    return result;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* RT_USING_SPI */
