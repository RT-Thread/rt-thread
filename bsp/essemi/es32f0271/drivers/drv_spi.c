/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-10-23     yuzrain       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include <rthw.h>
#include "board.h"
#include "drv_spi.h"
#include "md_spi.h"
#include "md_gpio.h"

#ifdef RT_USING_SPI

#define SPITIMEOUT 0x0FFF

static rt_err_t __spi_send(struct rt_spi_device *device, rt_uint8_t *buf,
                                            rt_int32_t len, rt_uint32_t tmout);
static rt_err_t __spi_recv(struct rt_spi_device *device, rt_uint8_t *buf,
                                            rt_int32_t len, rt_uint32_t tmout);
static rt_err_t __spi_send_recv(struct rt_spi_device *device, rt_uint8_t *tbuf,
                            rt_uint8_t *rbuf, rt_int32_t len, rt_uint32_t tmout);

/**
  * @brief:  SPI single line send.
  * @param:  device, pointer to the SPI device
  * @param:  buf, send data buffer
  * @param:  len, the length of buf
  * @param:  tmout, timeout
  * @retval: rt_err_t
  */
static rt_err_t __spi_send(struct rt_spi_device *device, rt_uint8_t *buf,
                                            rt_int32_t len, rt_uint32_t tmout)
{
    SPI_TypeDef *hspi;
    rt_uint32_t rt_timout;
    rt_uint8_t temp_data;

    /* Get the SPI port */
    hspi = (SPI_TypeDef *)device->bus->parent.user_data;

    /* Open SPI if it is disabled */
    if (READ_BIT(hspi->CON1, SPI_CON1_SPIEN_MSK) != SPI_CON1_SPIEN_MSK)
        SET_BIT(hspi->CON1, SPI_CON1_SPIEN_MSK);

    while (len > 0)
    {
        /* Confirm that no data is being transmitted */
        rt_timout   = tmout;
        while (((hspi->STAT & SPI_STAT_TXE_MSK) == 0) && (--rt_timout));
        if (rt_timout == 0)
            return RT_ETIMEOUT;

        /* Send data */
        if (device->config.data_width == 8)
        {
            hspi->DATA  = *(rt_uint8_t *)buf;
            buf++;
            len--;
        }
        else if (device->config.data_width == 16)
        {
            hspi->DATA  = *(rt_uint16_t *)buf;
            buf        += 2;
            len        -= 2;
        }
        else
            return RT_EINVAL;
    }

    /* At here, we have transmitted all the data.
     * The next step is to clear the IT flag.
     */
    for (rt_uint8_t i = 0; i < md_spi_get_stat_rxflv(hspi); i++)
        temp_data = hspi->DATA;
    UNUSED(temp_data);
    hspi->ICR   = hspi->RIF;

    return RT_EOK;
}

/**
  * @brief:  SPI single line receive.
  * @param:  device, pointer to the SPI device
  * @param:  buf, receive data buffer
  * @param:  len, the length of buf
  * @param:  tmout, timeout
  * @retval: rt_err_t
  */
static rt_err_t __spi_recv(struct rt_spi_device *device, rt_uint8_t *buf,
                                            rt_int32_t len, rt_uint32_t tmout)
{
    SPI_TypeDef *hspi;
    rt_uint32_t rt_timout;

    /* Get the SPI port */
    hspi = (SPI_TypeDef *)device->bus->parent.user_data;

    /* Open SPI if it is disabled */
    if (READ_BIT(hspi->CON1, SPI_CON1_SPIEN_MSK) != SPI_CON1_SPIEN_MSK)
        SET_BIT(hspi->CON1, SPI_CON1_SPIEN_MSK);

    /* Handle data in __spi_send_recv() function */
    if (((device->config.mode & RT_SPI_SLAVE) == 0)
                            && ((device->config.mode & RT_SPI_3WIRE) == 0))
        __spi_send_recv(device, buf, buf, len, tmout);

    while (len > 0)
    {
        /* Waiting for data */
        rt_timout   = tmout;
        while (((hspi->STAT & SPI_STAT_RXTH_MSK) == 0) && (--rt_timout));
        if (rt_timout == 0)
            return RT_ETIMEOUT;

        /* Send data */
        if (device->config.data_width == 8)
        {
             *(rt_uint8_t *)buf = hspi->DATA;
            buf++;
            len--;
        }
        else if (device->config.data_width == 16)
        {
            *(rt_uint16_t *)buf  = hspi->DATA;
            buf                 += 2;
            len                 -= 2;
        }
        else
            return RT_EINVAL;
    }

    /* At here, we have transmitted all the data.
     * The next step is to clear the IT flag.
     */
    hspi->ICR   = hspi->RIF;

    return RT_EOK;
}

/**
  * @brief:  SPI two line transmission.
  * @param:  device, pointer to the SPI device
  * @param:  tbuf, send data buffer
  * @param:  rbuf, receive data buffer
  * @param:  len, the length of buf
  * @param:  tmout, timeout
  * @retval: rt_err_t
  */
static rt_err_t __spi_send_recv(struct rt_spi_device *device, rt_uint8_t *tbuf,
                            rt_uint8_t *rbuf, rt_int32_t len, rt_uint32_t tmout)
{
    SPI_TypeDef *hspi;
    rt_uint32_t rt_timout;

    /* Get the SPI port */
    hspi = (SPI_TypeDef *)device->bus->parent.user_data;

    /* Open SPI if it is disabled */
    if (READ_BIT(hspi->CON1, SPI_CON1_SPIEN_MSK) != SPI_CON1_SPIEN_MSK)
        SET_BIT(hspi->CON1, SPI_CON1_SPIEN_MSK);

    /* return error if SPI is in 1-line mode */
    if ((device->config.mode & RT_SPI_3WIRE) == RT_SPI_3WIRE)
        return RT_ERROR;

    while (len > 0)
    {
        /* Confirm that no data is being transmitted */
        rt_timout   = tmout;
        while (((hspi->STAT & SPI_STAT_TXE_MSK) == 0) && (--rt_timout));
        if (rt_timout == 0)
            return RT_ETIMEOUT;

        /* Send data */
        if (device->config.data_width == 8)
        {
            hspi->DATA  = *(rt_uint8_t *)tbuf;
            tbuf++;
            len--;
        }
        else if (device->config.data_width == 16)
        {
            hspi->DATA  = *(rt_uint16_t *)tbuf;
            tbuf       += 2;
            len        -= 2;
        }
        else
            return RT_EINVAL;

        /* Waiting for data */
        rt_timout   = tmout;
        while (((hspi->STAT & SPI_STAT_RXTH_MSK) == 0) && (--rt_timout));
        if (rt_timout == 0)
            return RT_ETIMEOUT;

        /* Send data */
        if (device->config.data_width == 8)
        {
             *(rt_uint8_t *)rbuf = hspi->DATA;
            rbuf++;
        }
        else if (device->config.data_width == 16)
        {
            *(rt_uint16_t *)rbuf  = hspi->DATA;
            rbuf                 += 2;
        }
    }

    /* At here, we have transmitted all the data.
     * The next step is to clear the IT flag.
     */
    hspi->ICR   = hspi->RIF;

    return RT_EOK;
}

rt_err_t spi_configure(struct rt_spi_device *device,
                       struct rt_spi_configuration *cfg)
{
    SPI_TypeDef *hspi;
    hspi = (SPI_TypeDef *)device->bus->parent.user_data;

    /* Close SPI temporarily  */
    md_spi_disable_con1_spien(hspi);

    /* config spi mode */
    if (cfg->mode & RT_SPI_SLAVE)
        md_spi_set_con1_mstren(hspi, MD_SPI_MODE_SLAVE);
    else
        md_spi_set_con1_mstren(hspi, MD_SPI_MODE_MASTER);

    /* Config data mode */
    if (cfg->mode & RT_SPI_3WIRE)
        md_spi_set_con1_bidimode(hspi, MD_SPI_HALF_DUPLEX);
    else
        md_spi_set_con1_bidimode(hspi, MD_SPI_FULL_DUPLEX);

    /* Config data width */
    if (cfg->data_width == 8)
        md_spi_set_con1_flen(hspi, MD_SPI_FRAME_FORMAT_8BIT);
    else if (cfg->data_width == 16)
        md_spi_set_con1_flen(hspi, SPI_CON1_FLEN_MSK);

    /* Config phase */
    if (cfg->mode & RT_SPI_CPHA)
        md_spi_set_con1_cpha(hspi, MD_SPI_PHASE_2EDGE);
    else
        md_spi_set_con1_cpha(hspi, MD_SPI_PHASE_1EDGE);

    /* Config polarity */
    if (cfg->mode & RT_SPI_CPOL)
        md_spi_set_con1_cpol(hspi, MD_SPI_POLARITY_HIGH);
    else
        md_spi_set_con1_cpol(hspi, MD_SPI_POLARITY_LOW);

    /* Config if NSS pin is managed by software */
    md_spi_disable_con1_ssen(hspi);

    /* config spi clock */
    if (cfg->max_hz >= SystemCoreClock / 2)
    {
        /* pclk1 max speed 48MHz, spi master max speed 10MHz */
        if (SystemCoreClock / 2 <= 10000000)
            md_spi_set_con1_baud(hspi, MD_SPI_BAUDRATEPRESCALER_DIV2);
        else if (SystemCoreClock / 4 <= 10000000)
            md_spi_set_con1_baud(hspi, MD_SPI_BAUDRATEPRESCALER_DIV4);
        else
            md_spi_set_con1_baud(hspi, MD_SPI_BAUDRATEPRESCALER_DIV8);
    }
    else if (cfg->max_hz >= SystemCoreClock / 4)
    {
        /* pclk1 max speed 48MHz, spi master max speed 10MHz */
        if (SystemCoreClock / 4 <= 10000000)
            md_spi_set_con1_baud(hspi, MD_SPI_BAUDRATEPRESCALER_DIV4);
        else
            md_spi_set_con1_baud(hspi, MD_SPI_BAUDRATEPRESCALER_DIV8);
    }
    else if (cfg->max_hz >= SystemCoreClock / 8)
        md_spi_set_con1_baud(hspi, MD_SPI_BAUDRATEPRESCALER_DIV8);
    else if (cfg->max_hz >= SystemCoreClock / 16)
        md_spi_set_con1_baud(hspi, MD_SPI_BAUDRATEPRESCALER_DIV16);
    else if (cfg->max_hz >= SystemCoreClock / 32)
        md_spi_set_con1_baud(hspi, MD_SPI_BAUDRATEPRESCALER_DIV32);
    else if (cfg->max_hz >= SystemCoreClock / 64)
        md_spi_set_con1_baud(hspi, MD_SPI_BAUDRATEPRESCALER_DIV64);
    else if (cfg->max_hz >= SystemCoreClock / 128)
        md_spi_set_con1_baud(hspi, MD_SPI_BAUDRATEPRESCALER_DIV128);
    else
        md_spi_set_con1_baud(hspi, MD_SPI_BAUDRATEPRESCALER_DIV256);

    /* Enable SPI */
    md_spi_enable_con1_spien(hspi);

    return RT_EOK;
}

static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_err_t res;
    rt_uint32_t *cs;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    RT_ASSERT(message->send_buf != RT_NULL || message->recv_buf != RT_NULL);

    cs = (rt_uint32_t *)device->parent.user_data;

    /* only send data */
    if (message->recv_buf == RT_NULL)
    {
        if (message->cs_take)
        {
            rt_pin_write(*cs, 0);
        }
        res = __spi_send(device, (rt_uint8_t *)message->send_buf, (rt_int32_t)message->length, SPITIMEOUT);
        if (message->cs_release)
        {
            rt_pin_write(*cs, 1);
        }
        if (res != RT_EOK)
            return RT_ERROR;
    }

    /* only receive data */
    if (message->send_buf == RT_NULL)
    {
        if (message->cs_take)
        {
            rt_pin_write(*cs, 0);
        }
        res = __spi_recv(device, (rt_uint8_t *)message->recv_buf, (rt_int32_t)message->length, SPITIMEOUT);
        if (message->cs_release)
        {
            rt_pin_write(*cs, 1);
        }
        if (res != RT_EOK)
            return RT_ERROR;
    }

    /* send & receive */
    else
    {
        if (message->cs_take)
        {
            rt_pin_write(*cs, 0);
        }
        res = __spi_send_recv(device, (rt_uint8_t *)message->send_buf, (rt_uint8_t *)message->recv_buf,
                            (rt_int32_t)message->length, SPITIMEOUT);
        if (message->cs_release)
        {
            rt_pin_write(*cs, 1);
        }
        if (res != RT_EOK)
            return RT_ERROR;
    }

    return message->length;
}

const struct rt_spi_ops es32f0_spi_ops =
{
    spi_configure,
    spixfer,
};

static struct rt_spi_bus _spi_bus1, _spi_bus2;
int es32f0_spi_register_bus(SPI_TypeDef *SPIx, const char *name)
{
    struct rt_spi_bus *spi_bus;

    if (SPIx == SPI2)
    {
        /* Open GPIO and SPI clock */
        SET_BIT(RCU->APB1EN, RCU_APB1EN_SPI2EN_MSK);
        SET_BIT(RCU->AHBEN, RCU_AHBEN_GPBEN_MSK);

        /* Config SPI2 GPIO */
        md_gpio_set_mode         (GPIOB, MD_GPIO_PIN_13,   MD_GPIO_MODE_FUNCTION);
        md_gpio_set_mode         (GPIOB, MD_GPIO_PIN_14,   MD_GPIO_MODE_FUNCTION);
        md_gpio_set_mode         (GPIOB, MD_GPIO_PIN_15,   MD_GPIO_MODE_FUNCTION);
        md_gpio_set_function8_15 (GPIOB, MD_GPIO_PIN_13,   MD_GPIO_AF0);
        md_gpio_set_function8_15 (GPIOB, MD_GPIO_PIN_14,   MD_GPIO_AF0);
        md_gpio_set_function8_15 (GPIOB, MD_GPIO_PIN_15,   MD_GPIO_AF0);

        /* Remember SPI bus2 */
        spi_bus = &_spi_bus2;
    }
    else if (SPIx == SPI1)
    {
        /* Open GPIO and SPI clock */
        SET_BIT(RCU->APB2EN, RCU_APB2EN_SPI1EN_MSK);
        SET_BIT(RCU->AHBEN, RCU_AHBEN_GPBEN_MSK);

        /* Config SPI1 GPIO */
        md_gpio_set_mode        (GPIOB, MD_GPIO_PIN_3,   MD_GPIO_MODE_FUNCTION);
        md_gpio_set_mode        (GPIOB, MD_GPIO_PIN_4,   MD_GPIO_MODE_FUNCTION);
        md_gpio_set_mode        (GPIOB, MD_GPIO_PIN_5,   MD_GPIO_MODE_FUNCTION);
        md_gpio_set_function0_7 (GPIOB, MD_GPIO_PIN_3,   MD_GPIO_AF0);
        md_gpio_set_function0_7 (GPIOB, MD_GPIO_PIN_4,   MD_GPIO_AF0);
        md_gpio_set_function0_7 (GPIOB, MD_GPIO_PIN_5,   MD_GPIO_AF0);

        /* Remember SPI bus1 */
        spi_bus = &_spi_bus1;
    }
    else
    {
        return -1;
    }
    spi_bus->parent.user_data = SPIx;

    return rt_spi_bus_register(spi_bus, name, &es32f0_spi_ops);
}

int rt_hw_spi_init(void)
{
    int result = 0;

#ifdef BSP_USING_SPI2
    result = es32f0_spi_register_bus(SPI2, "spi2");
#endif

#ifdef BSP_USING_SPI1
    result = es32f0_spi_register_bus(SPI1, "spi1");
#endif

    return result;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif
