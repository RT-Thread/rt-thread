/*
 * File      : spi.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-23     Bernard      Add extern "C"
 */

#ifndef __SPI_H__
#define __SPI_H__

#include <stdlib.h>
#include <rtthread.h>

#ifdef __cplusplus
extern "C"{
#endif

#define RT_SPI_CPHA     (1<<0)                             /* bit[0]:CPHA, clock phase */
#define RT_SPI_CPOL     (1<<1)                             /* bit[1]:CPOL, clock polarity */
/**
 * At CPOL=0 the base value of the clock is zero
 *  - For CPHA=0, data are captured on the clock's rising edge (low¡úhigh transition)
 *    and data are propagated on a falling edge (high¡úlow clock transition).
 *  - For CPHA=1, data are captured on the clock's falling edge and data are
 *    propagated on a rising edge.
 * At CPOL=1 the base value of the clock is one (inversion of CPOL=0)
 *  - For CPHA=0, data are captured on clock's falling edge and data are propagated
 *    on a rising edge.
 *  - For CPHA=1, data are captured on clock's rising edge and data are propagated
 *    on a falling edge.
 */
#define RT_SPI_LSB      (0<<2)                             /* bit[2]: 0-LSB */
#define RT_SPI_MSB      (1<<2)                             /* bit[2]: 1-MSB */

#define RT_SPI_MASTER   (0<<3)                             /* SPI master device */
#define RT_SPI_SLAVE    (1<<3)                             /* SPI slave device */

#define RT_SPI_MODE_0       (0 | 0)                        /* CPOL = 0, CPHA = 0 */
#define RT_SPI_MODE_1       (0 | RT_SPI_CPHA)              /* CPOL = 0, CPHA = 1 */
#define RT_SPI_MODE_2       (RT_SPI_CPOL | 0)              /* CPOL = 1, CPHA = 0 */
#define RT_SPI_MODE_3       (RT_SPI_CPOL | RT_SPI_CPHA)    /* CPOL = 1, CPHA = 1 */

#define RT_SPI_MODE_MASK    (RT_SPI_CPHA | RT_SPI_CPOL | RT_SPI_MSB)

#define RT_SPI_CS_HIGH  (1<<4)                             /* Chipselect active high */
#define RT_SPI_NO_CS    (1<<5)                             /* No chipselect */
#define RT_SPI_3WIRE    (1<<6)                             /* SI/SO pin shared */
#define RT_SPI_READY    (1<<7)                             /* Slave pulls low to pause */

/**
 * SPI message structure
 */
struct rt_spi_message
{
    const void *send_buf;
    void *recv_buf;
    rt_size_t length;
    struct rt_spi_message *next;

    unsigned cs_take    : 1;
    unsigned cs_release : 1;
};

/**
 * SPI configuration structure
 */
struct rt_spi_configuration
{
    rt_uint8_t mode;
    rt_uint8_t data_width;
    rt_uint16_t reserved;

    rt_uint32_t max_hz;
};

struct rt_spi_ops;
struct rt_spi_bus
{
    struct rt_device parent;
    const struct rt_spi_ops *ops;

    struct rt_mutex lock;
    struct rt_spi_device *owner;
};

/**
 * SPI operators
 */
struct rt_spi_ops
{
    rt_err_t (*configure)(struct rt_spi_device *device, struct rt_spi_configuration *configuration);
    rt_uint32_t (*xfer)(struct rt_spi_device *device, struct rt_spi_message *message);
};

/**
 * SPI Virtual BUS, one device must connected to a virtual BUS
 */
struct rt_spi_device
{
    struct rt_device parent;
    struct rt_spi_bus *bus;

    struct rt_spi_configuration config;
};
#define SPI_DEVICE(dev) ((struct rt_spi_device *)(dev))

/* register a SPI bus */
rt_err_t rt_spi_bus_register(struct rt_spi_bus       *bus,
                             const char              *name,
                             const struct rt_spi_ops *ops);

/* attach a device on SPI bus */
rt_err_t rt_spi_bus_attach_device(struct rt_spi_device *device,
                                  const char           *name,
                                  const char           *bus_name,
                                  void                 *user_data);

/**
 * This function takes SPI bus.
 *
 * @param device the SPI device attached to SPI bus
 *
 * @return RT_EOK on taken SPI bus successfully. others on taken SPI bus failed.
 */
rt_err_t rt_spi_take_bus(struct rt_spi_device *device);

/**
 * This function releases SPI bus.
 *
 * @param device the SPI device attached to SPI bus
 *
 * @return RT_EOK on release SPI bus successfully.
 */
rt_err_t rt_spi_release_bus(struct rt_spi_device *device);

/**
 * This function take SPI device (takes CS of SPI device).
 *
 * @param device the SPI device attached to SPI bus
 *
 * @return RT_EOK on release SPI bus successfully. others on taken SPI bus failed.
 */
rt_err_t rt_spi_take(struct rt_spi_device *device);

/**
 * This function releases SPI device (releases CS of SPI device).
 *
 * @param device the SPI device attached to SPI bus
 *
 * @return RT_EOK on release SPI device successfully.
 */
rt_err_t rt_spi_release(struct rt_spi_device *device);

/* set configuration on SPI device */
rt_err_t rt_spi_configure(struct rt_spi_device        *device,
                          struct rt_spi_configuration *cfg);

/* send data then receive data from SPI device */
rt_err_t rt_spi_send_then_recv(struct rt_spi_device *device,
                               const void           *send_buf,
                               rt_size_t             send_length,
                               void                 *recv_buf,
                               rt_size_t             recv_length);

rt_err_t rt_spi_send_then_send(struct rt_spi_device *device,
                               const void           *send_buf1,
                               rt_size_t             send_length1,
                               const void           *send_buf2,
                               rt_size_t             send_length2);

/**
 * This function transmits data to SPI device.
 *
 * @param device the SPI device attached to SPI bus
 * @param send_buf the buffer to be transmitted to SPI device.
 * @param recv_buf the buffer to save received data from SPI device.
 * @param length the length of transmitted data.
 *
 * @return the actual length of transmitted.
 */
rt_size_t rt_spi_transfer(struct rt_spi_device *device,
                          const void           *send_buf,
                          void                 *recv_buf,
                          rt_size_t             length);

/**
 * This function transfers a message list to the SPI device.
 *
 * @param device the SPI device attached to SPI bus
 * @param message the message list to be transmitted to SPI device
 *
 * @return RT_NULL if transmits message list successfully,
 *         SPI message which be transmitted failed.
 */
struct rt_spi_message *rt_spi_transfer_message(struct rt_spi_device  *device,
                                               struct rt_spi_message *message);

rt_inline rt_size_t rt_spi_recv(struct rt_spi_device *device,
                                void                 *recv_buf,
                                rt_size_t             length)
{
    return rt_spi_transfer(device, RT_NULL, recv_buf, length);
}

rt_inline rt_size_t rt_spi_send(struct rt_spi_device *device,
                                const void           *send_buf,
                                rt_size_t             length)
{
    return rt_spi_transfer(device, send_buf, RT_NULL, length);
}

rt_inline rt_uint8_t rt_spi_sendrecv8(struct rt_spi_device *device,
                                      rt_uint8_t            data)
{
    rt_uint8_t value;

    rt_spi_send_then_recv(device, &data, 1, &value, 1);

    return value;
}

rt_inline rt_uint16_t rt_spi_sendrecv16(struct rt_spi_device *device,
                                        rt_uint16_t           data)
{
    rt_uint16_t value;

    rt_spi_send_then_recv(device, &data, 2, &value, 2);

    return value;
}

/**
 * This function appends a message to the SPI message list.
 *
 * @param list the SPI message list header.
 * @param message the message pointer to be appended to the message list.
 */
rt_inline void rt_spi_message_append(struct rt_spi_message *list,
                                     struct rt_spi_message *message)
{
    RT_ASSERT(list != RT_NULL);
    if (message == RT_NULL)
        return; /* not append */

    while (list->next != RT_NULL)
    {
        list = list->next;
    }

    list->next = message;
    message->next = RT_NULL;
}

#ifdef __cplusplus
}
#endif

#endif
