/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-11     kyle          first version
 */

#include <dev_spi_bit_ops.h>
#include <rtdevice.h>

#define DBG_TAG               "SPI"
#ifdef RT_SPI_BITOPS_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_ERROR
#endif
#include <rtdbg.h>

#define TOG_SCLK(ops)        ops->tog_sclk(ops->data)
#define SET_SCLK(ops, val)   ops->set_sclk(ops->data, val)
#define SET_MOSI(ops, val)   ops->set_mosi(ops->data, val)
#define SET_MISO(ops, val)   ops->set_miso(ops->data, val)
#define GET_SCLK(ops)        ops->get_sclk(ops->data)
#define GET_MOSI(ops)        ops->get_mosi(ops->data)
#define GET_MISO(ops)        ops->get_miso(ops->data)
#define DIR_MOSI(ops, val)   ops->dir_mosi(ops->data, val)
#define DIR_MISO(ops, val)   ops->dir_miso(ops->data, val)

rt_inline void spi_delay(struct rt_spi_bit_ops *ops)
{
    ops->udelay((ops->delay_us + 1) >> 1);
}

rt_inline void spi_delay2(struct rt_spi_bit_ops *ops)
{
    ops->udelay(ops->delay_us);
}

#define SCLK_H(ops)          SET_SCLK(ops, 1)
#define SCLK_L(ops)          SET_SCLK(ops, 0)
#define MOSI_H(ops)          SET_MOSI(ops, 1)
#define MOSI_L(ops)          SET_MOSI(ops, 0)
#define MOSI_IN(ops)         DIR_MOSI(ops, 1)
#define MOSI_OUT(ops)        DIR_MOSI(ops, 0)
#define MISO_IN(ops)         DIR_MISO(ops, 1)
#define MISO_OUT(ops)        DIR_MISO(ops, 0)

rt_inline rt_ssize_t spi_xfer_4line_data8(struct rt_spi_bit_ops       *ops,
                                         struct rt_spi_configuration *config,
                                         const void                  *send_buf,
                                         void                        *recv_buf,
                                         rt_size_t                    length)
{
    int i = 0;

    RT_ASSERT(ops != RT_NULL);
    RT_ASSERT(length != 0);

    {
        const rt_uint8_t *send_ptr = send_buf;
        rt_uint8_t *recv_ptr = recv_buf;
        rt_uint32_t size = length;

        while (size--)
        {
            rt_uint8_t tx_data = 0xFF;
            rt_uint8_t rx_data = 0xFF;
            rt_uint8_t bit  = 0;

            if (send_buf != RT_NULL)
            {
                tx_data = *send_ptr++;
            }

            for (i = 0; i < 8; i++)
            {
                if (config->mode & RT_SPI_MSB) { bit = tx_data & (0x1 << (7 - i)); }
                else                           { bit = tx_data & (0x1 << i); }

                if (bit) MOSI_H(ops);
                else     MOSI_L(ops);

                spi_delay2(ops);

                TOG_SCLK(ops);

                if (config->mode & RT_SPI_MSB) { rx_data <<= 1; bit = 0x01; }
                else                           { rx_data >>= 1; bit = 0x80; }

                if (GET_MISO(ops)) { rx_data |=  bit; }
                else               { rx_data &= ~bit; }

                spi_delay2(ops);

                if (!(config->mode & RT_SPI_CPHA) || (size != 0) || (i < 7))
                {
                    TOG_SCLK(ops);
                }
            }

            if (recv_buf != RT_NULL)
            {
                *recv_ptr++ = rx_data;
            }
        }
    }

    return length;
}

rt_inline rt_ssize_t spi_xfer_4line_data16(struct rt_spi_bit_ops       *ops,
                                          struct rt_spi_configuration *config,
                                          const void                  *send_buf,
                                          void                        *recv_buf,
                                          rt_size_t                    length)
{
    int i = 0;

    RT_ASSERT(ops != RT_NULL);
    RT_ASSERT(length != 0);

    {
        const rt_uint16_t *send_ptr = send_buf;
        rt_uint16_t *recv_ptr = recv_buf;
        rt_uint32_t size = length;

        while (size--)
        {
            rt_uint16_t tx_data = 0xFFFF;
            rt_uint16_t rx_data = 0xFFFF;
            rt_uint16_t bit  = 0;

            if (send_buf != RT_NULL)
            {
                tx_data = *send_ptr++;
            }

            for (i = 0; i < 16; i++)
            {
                if (config->mode & RT_SPI_MSB) { bit = tx_data & (0x1 << (15 - i)); }
                else                           { bit = tx_data & (0x1 << i); }

                if (bit) MOSI_H(ops);
                else     MOSI_L(ops);

                spi_delay2(ops);

                TOG_SCLK(ops);

                if (config->mode & RT_SPI_MSB) { rx_data <<= 1; bit = 0x0001; }
                else                           { rx_data >>= 1; bit = 0x8000; }

                if (GET_MISO(ops)) { rx_data |=  bit; }
                else               { rx_data &= ~bit; }

                spi_delay2(ops);

                if (!(config->mode & RT_SPI_CPHA) || (size != 0) || (i < 15))
                {
                    TOG_SCLK(ops);
                }
            }

            if (recv_buf != RT_NULL)
            {
                *recv_ptr++ = rx_data;
            }
        }
    }

    return length;
}

rt_inline rt_ssize_t spi_xfer_3line_data8(struct rt_spi_bit_ops       *ops,
                                         struct rt_spi_configuration *config,
                                         const void                  *send_buf,
                                         void                        *recv_buf,
                                         rt_size_t                    length)
{
    int i = 0;

    RT_ASSERT(ops != RT_NULL);
    RT_ASSERT(length != 0);

    {
        const rt_uint8_t *send_ptr = send_buf;
        rt_uint8_t *recv_ptr = recv_buf;
        rt_uint32_t size = length;
        rt_uint8_t send_flg = 0;

        if ((send_buf != RT_NULL) || (recv_buf == RT_NULL))
        {
            MOSI_OUT(ops);
            send_flg = 1;
        }
        else
        {
            MOSI_IN(ops);
        }

        while (size--)
        {
            rt_uint8_t tx_data = 0xFF;
            rt_uint8_t rx_data = 0xFF;
            rt_uint8_t bit  = 0;

            if (send_buf != RT_NULL)
            {
                tx_data = *send_ptr++;
            }

            if (send_flg)
            {
                for (i = 0; i < 8; i++)
                {
                    if (config->mode & RT_SPI_MSB) { bit = tx_data & (0x1 << (7 - i)); }
                    else                           { bit = tx_data & (0x1 << i); }

                    if (bit) MOSI_H(ops);
                    else     MOSI_L(ops);

                    spi_delay2(ops);

                    TOG_SCLK(ops);

                    spi_delay2(ops);

                    if (!(config->mode & RT_SPI_CPHA) || (size != 0) || (i < 7))
                    {
                        TOG_SCLK(ops);
                    }
                }

                rx_data = tx_data;
            }
            else
            {
                for (i = 0; i < 8; i++)
                {
                    spi_delay2(ops);

                    TOG_SCLK(ops);

                    if (config->mode & RT_SPI_MSB) { rx_data <<= 1; bit = 0x01; }
                    else                           { rx_data >>= 1; bit = 0x80; }

                    if (GET_MOSI(ops)) { rx_data |=  bit; }
                    else               { rx_data &= ~bit; }

                    spi_delay2(ops);

                    if (!(config->mode & RT_SPI_CPHA) || (size != 0) || (i < 7))
                    {
                        TOG_SCLK(ops);
                    }
                }

            }

            if (recv_buf != RT_NULL)
            {
                *recv_ptr++ = rx_data;
            }
        }

        if (!send_flg)
        {
            MOSI_OUT(ops);
        }
    }

    return length;
}

rt_inline rt_ssize_t spi_xfer_3line_data16(struct rt_spi_bit_ops       *ops,
                                          struct rt_spi_configuration *config,
                                          const void                  *send_buf,
                                          void                        *recv_buf,
                                          rt_size_t                    length)
{
    int i = 0;

    RT_ASSERT(ops != RT_NULL);
    RT_ASSERT(length != 0);

    {
        const rt_uint16_t *send_ptr = send_buf;
        rt_uint16_t *recv_ptr = recv_buf;
        rt_uint32_t size = length;
        rt_uint8_t send_flg = 0;

        if ((send_buf != RT_NULL) || (recv_buf == RT_NULL))
        {
            MOSI_OUT(ops);
            send_flg = 1;
        }
        else
        {
            MOSI_IN(ops);
        }

        while (size--)
        {
            rt_uint16_t tx_data = 0xFFFF;
            rt_uint16_t rx_data = 0xFFFF;
            rt_uint16_t bit  = 0;

            if (send_buf != RT_NULL)
            {
                tx_data = *send_ptr++;
            }

            if (send_flg)
            {
                for (i = 0; i < 16; i++)
                {
                    if (config->mode & RT_SPI_MSB) { bit = tx_data & (0x1 << (15 - i)); }
                    else                           { bit = tx_data & (0x1 << i); }

                    if (bit) MOSI_H(ops);
                    else     MOSI_L(ops);

                    spi_delay2(ops);

                    TOG_SCLK(ops);

                    spi_delay2(ops);

                    if (!(config->mode & RT_SPI_CPHA) || (size != 0) || (i < 15))
                    {
                        TOG_SCLK(ops);
                    }
                }

                rx_data = tx_data;
            }
            else
            {
                for (i = 0; i < 16; i++)
                {
                    spi_delay2(ops);

                    TOG_SCLK(ops);

                    if (config->mode & RT_SPI_MSB) { rx_data <<= 1; bit = 0x0001; }
                    else                           { rx_data >>= 1; bit = 0x8000; }

                    if (GET_MOSI(ops)) { rx_data |=  bit; }
                    else               { rx_data &= ~bit; }

                    spi_delay2(ops);

                    if (!(config->mode & RT_SPI_CPHA) || (size != 0) || (i < 15))
                    {
                        TOG_SCLK(ops);
                    }
                }

            }

            if (recv_buf != RT_NULL)
            {
                *recv_ptr++ = rx_data;
            }
        }

        if (!send_flg)
        {
            MOSI_OUT(ops);
        }
    }

    return length;
}

rt_err_t spi_bit_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
    struct rt_spi_bit_obj *obj = rt_container_of(device->bus, struct rt_spi_bit_obj, bus);
    struct rt_spi_bit_ops *ops = obj->ops;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    if(ops->pin_init != RT_NULL)
    {
        ops->pin_init();
    }

    if (configuration->mode & RT_SPI_SLAVE)
    {
        return -RT_EIO;
    }

    if (configuration->mode & RT_SPI_CPOL)
    {
        SCLK_H(ops);
    }
    else
    {
        SCLK_L(ops);
    }

    if (configuration->max_hz < 200000)
    {
        ops->delay_us = 1;
    }
    else
    {
        ops->delay_us = 0;
    }

    rt_memcpy(&obj->config, configuration, sizeof(struct rt_spi_configuration));

    return RT_EOK;
}

rt_ssize_t spi_bit_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct rt_spi_bit_obj *obj = rt_container_of(device->bus, struct rt_spi_bit_obj, bus);
    struct rt_spi_bit_ops *ops = obj->ops;
    struct rt_spi_configuration *config = &obj->config;
    rt_base_t cs_pin = device->cs_pin;
    rt_ssize_t length = 0;

    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

#ifdef RT_SPI_BITOPS_DEBUG
    if (!ops->tog_sclk || !ops->set_sclk || !ops->get_sclk)
    {
        LOG_E("SPI bus error, SCLK line not defined");
    }
    if (!ops->set_mosi || !ops->get_mosi)
    {
        LOG_E("SPI bus error, MOSI line not defined");
    }
    if (!ops->set_miso || !ops->get_miso)
    {
        LOG_E("SPI bus error, MISO line not defined");
    }
#endif

    /* take CS */
    if (message->cs_take && !(device->config.mode & RT_SPI_NO_CS) && (cs_pin != PIN_NONE))
    {
        LOG_I("spi take cs\n");
        if (device->config.mode & RT_SPI_CS_HIGH)
        {
            rt_pin_write(cs_pin, PIN_HIGH);
        }
        else
        {
            rt_pin_write(cs_pin, PIN_LOW);
        }
        spi_delay(ops);

        /* spi phase */
        if (config->mode & RT_SPI_CPHA)
        {
            spi_delay(ops);
            TOG_SCLK(ops);
        }
    }

    if (config->mode & RT_SPI_3WIRE)
    {
        if (config->data_width <= 8)
        {
            length = spi_xfer_3line_data8(ops, config, message->send_buf, message->recv_buf, message->length);
        }
        else if (config->data_width <= 16)
        {
            length = spi_xfer_3line_data16(ops, config, message->send_buf, message->recv_buf, message->length);
        }
    }
    else
    {
        if (config->data_width <= 8)
        {
            length = spi_xfer_4line_data8(ops, config, message->send_buf, message->recv_buf, message->length);
        }
        else if (config->data_width <= 16)
        {
            length = spi_xfer_4line_data16(ops, config, message->send_buf, message->recv_buf, message->length);
        }
    }

    /* release CS */
    if (message->cs_take && !(device->config.mode & RT_SPI_NO_CS) && (cs_pin != PIN_NONE))
    {
        spi_delay(ops);
        if (device->config.mode & RT_SPI_CS_HIGH)
        {
            rt_pin_write(cs_pin, PIN_LOW);
        }
        else
        {
            rt_pin_write(cs_pin, PIN_HIGH);
        }
        LOG_I("spi release cs\n");
    }

    return length;
}

static const struct rt_spi_ops spi_bit_bus_ops =
{
    .configure = spi_bit_configure,
    .xfer      = spi_bit_xfer,
};

rt_err_t rt_spi_bit_add_bus(struct rt_spi_bit_obj *obj,
                            const char            *bus_name,
                            struct rt_spi_bit_ops *ops)
{
    obj->ops = ops;
    obj->config.data_width = 8;
    obj->config.max_hz     = 1 * 1000 * 1000;
    obj->config.mode       = RT_SPI_MASTER | RT_SPI_MSB | RT_SPI_MODE_0;

    return rt_spi_bus_register(&obj->bus, bus_name, &spi_bit_bus_ops);
}
